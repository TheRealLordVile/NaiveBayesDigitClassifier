//
//  digitclassifier.hpp
//  digitclassifier
//
//  Created by A.Kadri Türker on 10/19/18.
//  Copyright © 2018 A.Kadri Türker. All rights reserved.
//

#ifndef DIGITCLASSIFIER_hpp
#define DIGITCLASSIFIER_hpp

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <math.h>
#include <sstream>

typedef std::pair<int,int> Coordinates;
typedef std::vector<std::vector<double>> ConfusionMatrix;
class digitClassifier{
public:
    digitClassifier();
    void UserInterface();
    void ImportData(const std::string &data_path,
                    const std::string &label_path);
    bool WriteModelToFile(const std::string &file_path);
    bool ImportModelFromFile(const std::string &file_path);
    ConfusionMatrix ClassifyImages(const std::string &file_path,
                        const std::string &label_path);
private:
    const std::pair<int, int> kDefualtPairVal = std::make_pair(0,0);
    const double kClassifyConst = 0.00000009;
    const int kFirstDigit = 0;
    const int kLastDigit = 9;
    const int kImgSideLen = 28;
    const int kWhitePixVal = 0;
    const int kGrayBlackPixVal = 1;
    const char kPixValSeparator = ' ';
    const char kCoorValSeperator = ',';
    const std::string kDefTrainDataPath = "/Users/a.kadri/Documents/"
                                          "naive-bayes-TheRealLordVile/"
                                          "digitclassifier/digitclassifier/"
                                          "digitdata/trainingimages";
    const std::string kDefTrainLabelPath = "/Users/a.kadri/Documents/"
                                           "naive-bayes-TheRealLordVile/"
                                           "digitclassifier/digitclassifier/"
                                           "digitdata/traininglabels";
    const std::string kDefTestDataPath = "/Users/a.kadri/Documents/"
                                             "naive-bayes-TheRealLordVile/"
                                             "digitclassifier/digitclassifier/"
                                             "digitdata/testimages";
    const std::string kDefTestLabelPath = "/Users/a.kadri/Documents/"
                                          "naive-bayes-TheRealLordVile/"
                                          "digitclassifier/digitclassifier/"
                                          "digitdata/testlabels";
    const std::string kDefModelWriteReadPath = "/Users/a.kadri/Documents/"
                                               "naive-bayes-TheRealLordVile/"
                                               "digitclassifier/"
                                               "digitclassifier/datamodel.txt";
    
    int num_train_exmp;
    std::map<int,std::map<Coordinates,std::pair<int, int>>> data_set;
    std::map<int,std::map<Coordinates,std::pair<double, double>>> prob_set;
    std::vector<double> class_prob;
    
    ConfusionMatrix CreateConfusionMatrix();
    void InitializeDataSet();
    void InitializeProbabilitySet();
    void CalculateProbabilities();
    
    
    int GetMostLikelyDigit(std::map<Coordinates,int> &image_set);
    double GetDigitProbability(const int &digit,
                               std::map<Coordinates,int> &image_set);
    double GetPixelProbability(const int &digit, const int &color,
                               const Coordinates &coord);
    
    std::string GetDigitString(const int &digit);
    std::vector<std::string> SplitString(const std::string &string,
                                         const char &split_point);
    void EvaluateUserInput(const int &user_choice);
};
#endif /* digitclassifier_hpp */
