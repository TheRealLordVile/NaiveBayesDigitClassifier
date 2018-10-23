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

typedef std::pair<int,int> Coordinates;
class digitClassifier{
public:
    digitClassifier();
    const double kClassifyConst = 0.1;
    int num_train_exmp;
    std::vector<double> class_prob;
    void InitializeDataSet();
    void InitializeProbabilitySet();
    void ImportData(std::string data_path, std::string label_path);
    void CalculateProbabilities();
    int GetMostLikelyDigit(std::map<Coordinates,int> image_set);
    double GetDigitProbability(int digit, std::map<Coordinates,int> image_set);
    double GetPixelProbability(int digit, Coordinates coord, int color);
    bool WriteModelToFile(std::string file_path);
    std::string GetDigitString(int digit);
    bool ImportModelFromFile(std::string file_path);
    std::vector<int> num_images;
    std::map<int,std::map<Coordinates,std::vector<int>>> data_set;
    std::map<int,std::map<Coordinates,std::pair<double, double>>> prob_set;
private:
};
#endif /* digitclassifier_hpp */
