//
//  digitclassifier.cpp
//  digitclassifier
//
//  Created by A.Kadri Türker on 10/19/18.
//  Copyright © 2018 A.Kadri Türker. All rights reserved.
//

#include "digitclassifier.hpp"

digitClassifier::digitClassifier(){
    num_train_exmp = 0;
    InitializeProbabilitySet();
    InitializeDataSet();
}

void digitClassifier::InitializeDataSet(){
    data_set = std::map<int,std::map<Coordinates,std::pair<int, int>>>();
    for (int digit = kFirstDigit; digit <= kLastDigit; digit++) {
        std::map<Coordinates,std::pair<int, int>> numRepeatance;
        for (int row = 0; row < kImgSideLen; row++) {
            for (int col = 0; col < kImgSideLen; col++) {
                numRepeatance[std::make_pair(col,row)] = kDefualtPairVal;
            }
        }
        
        data_set[digit] = numRepeatance;
    }
}

void digitClassifier::InitializeProbabilitySet(){
    class_prob = std::vector<double>();
    prob_set = std::map<int,std::map<Coordinates,std::pair<double, double>>>();
    for (int digit = kFirstDigit; digit <= kLastDigit; digit++) {
        std::map<Coordinates,std::pair<double,double>> numRepeatance;
        for (int row = 0; row < kImgSideLen; row++) {
            for (int col = 0; col < kImgSideLen; col++) {
                numRepeatance[std::make_pair(col, row)] = kDefualtPairVal;
            }
        }
        
        prob_set[digit] = numRepeatance;
    }
    
}

void digitClassifier::ImportData(const std::string &data_path,
                                 const std::string &label_path) {
    std::ifstream train_file(data_path);
    std::string line;
    std::ifstream label_file(label_path);
    std::string label;
    
    while (true) {
        if (!std::getline(label_file,label)) {
            break;
        }
        int label_ind = stoi(label);
        num_train_exmp++;
        for (int row = 0; row < kImgSideLen; row++) {
            std::getline(train_file,line);
            for (int col = 0; col < kImgSideLen; col++) {
                Coordinates coord = std::make_pair(col,row);
                if (line.at(col) == '+' || line.at(col) == '#') {
                    data_set[label_ind][coord].second++;
                } else{
                    data_set[label_ind][coord].first++;
                }
            }
        }

    }
    CalculateProbabilities();
    
}

void digitClassifier::CalculateProbabilities(){
    for (int digit = kFirstDigit; digit <= kLastDigit; digit++){
        int num_digit_repeat = data_set[digit][kDefualtPairVal].first +
                               data_set[digit][kDefualtPairVal].second;
        double prob_digit = (kClassifyConst + num_digit_repeat) /
                            (num_train_exmp + 2 * kClassifyConst);
        class_prob.push_back(prob_digit);
        
        for (int row = 0; row < kImgSideLen; row++) {
            for (int col = 0; col < kImgSideLen; col++) {
                Coordinates coord = std::make_pair(col, row);
                int num_whit = data_set[digit][coord].first;
                int num_grblack = data_set[digit][coord].second;
                int num_repeatence = num_whit + num_grblack;
                double prob_white = (num_whit + kClassifyConst) /
                                    (num_repeatence+ 2 * kClassifyConst);
                double prob_grblack = (num_grblack + kClassifyConst) /
                                      (num_repeatence+ 2 * kClassifyConst);
                
                prob_set[digit][coord] = std::make_pair(prob_white,
                                                        prob_grblack);
            }
        }
    }
}

int digitClassifier::GetMostLikelyDigit(std::map<Coordinates,int> &image_set){
    double highest_prob = GetDigitProbability(0 ,image_set);
    int digit_highest_prob = 0;
    for (int digit = 1; digit <= 9; digit++) {
        double digit_prob = GetDigitProbability(digit ,image_set);
        if (digit_prob > highest_prob) {
            highest_prob = digit_prob;
            digit_highest_prob = digit;
        }
    }
    
    return digit_highest_prob;
}

double digitClassifier::GetDigitProbability(const int &digit,
                                            std::map<Coordinates,int> &image_set
                                            ){
    
    double digit_prob = log(class_prob[digit]);
    for (int row = 0; row < kImgSideLen; row++) {
        for (int col = 0; col < kImgSideLen; col++) {
            Coordinates coord = std::make_pair(col, row);
            digit_prob += GetPixelProbability(digit, image_set[coord], coord);
        }
    }
    
    return digit_prob;
}

double digitClassifier::GetPixelProbability(const int &digit, const int &color,
                                            const Coordinates &coord){
    if(color == kWhitePixVal){
        return log(prob_set[digit][coord].first);
    }
    
    return log(prob_set[digit][coord].second);
}

bool digitClassifier::WriteModelToFile(const std::string &file_path){
    if (data_set.empty() || num_train_exmp == 0){
        return false;
    }
    
    std::ofstream output_file;
    output_file.open(file_path);
    output_file << num_train_exmp;
    output_file << "\n";
    for (int digit = kFirstDigit; digit <= kLastDigit; digit++) {
        output_file << GetDigitString(digit) + "\n";
        
    }
    output_file.close();
    return true;
}

std::string digitClassifier::GetDigitString(const int &digit){
    std::string digit_string;
    for (int row = 0; row < kImgSideLen; row++) {
        for (int col = 0; col < kImgSideLen; col++) {
            Coordinates coord = std::make_pair(col, row);
            int num_whit = data_set[digit][coord].first;
            int num_grblack = data_set[digit][coord].second;
            digit_string += std::to_string(num_whit) +
                            kPixValSeparator +
                            std::to_string(num_grblack);
            
            digit_string += kCoorValSeperator;
        }
    }
    digit_string.pop_back();
    return digit_string;
}

bool digitClassifier::ImportModelFromFile(const std::string &file_path) {
    InitializeProbabilitySet();
    InitializeDataSet();
    std::ifstream input_file(file_path);
    std::string line;
    std::getline(input_file, line);
    num_train_exmp = std::stoi(line);
    for (int digit = kFirstDigit; digit <= kLastDigit; digit++) {
        std::getline(input_file, line);
        std::vector<std::string> pairs = SplitString(line, kCoorValSeperator);
        for (int row = 0; row < kImgSideLen; row++) {
            for (int col = 0; col < kImgSideLen; col++) {
                std::string pixel_data = pairs[col + kImgSideLen * row];
                std::vector<std::string> bwg_freq =
                SplitString(pixel_data,kPixValSeparator);
                int num_white = std::stoi(bwg_freq[0]);
                int num_grblack = std::stoi(bwg_freq[1]);
                Coordinates coord = std::make_pair(col,row);
                for(int i = 0; i < num_white; i++){
                    data_set[digit][coord].first++;
                }
                for(int i = 0; i < num_grblack; i++){
                    data_set[digit][coord].second++;
                }
            }
            
        }
    }
    
    CalculateProbabilities();
    return true;

}

ConfusionMatrix digitClassifier::ClassifyImages(const std::string &file_path,
                                                const std::string &label_path) {
    ConfusionMatrix confusion_matrix = CreateConfusionMatrix();
    std::ifstream train_file(file_path);
    std::string line;
    
    std::ifstream label_file(label_path);
    std::string label;
    
    std::vector<int> digits;
    int correct_digits = 0;
    int n_digits = 0;
    while(true) {
        if (!std::getline(label_file,label)) {
            break;
        }
        
        n_digits++;
        int label_ind = stoi(label);
        std::map<Coordinates,int> img;
        for (int row = 0; row < kImgSideLen; row++) {
            std::getline(train_file,line);
            for (int col = 0; col < kImgSideLen; col++) {
                Coordinates coord = std::make_pair(col, row);
                if(line.at(col) == '+' || line.at(col) == '#'){
                    img[coord] = kGrayBlackPixVal;
                } else{
                    img[coord] = kWhitePixVal;
                }
            }
        }
        confusion_matrix[label_ind][GetMostLikelyDigit(img)]++;
        
        if (GetMostLikelyDigit(img) == label_ind) {
            correct_digits++;
        }
        
    }
    for (int i = 0; i < confusion_matrix.size(); i++) {
        int num_elements = 0;
        for (int j = 0; j < confusion_matrix[i].size(); j++) {
            num_elements += confusion_matrix[i][j];
        }
        for (int j = 0; j < confusion_matrix[i].size(); j++) {
            confusion_matrix[i][j] /= num_elements;
        }
    }
    double percentage = 100 * correct_digits/n_digits;
    std::cout << percentage <<std::endl;
    return confusion_matrix;
}

std::vector<std::string> digitClassifier::SplitString(const std::string &string,
                                                      const char &split_point) {
    std::vector<std::string> strings;
    std::stringstream ss(string);
    std::string part;
    while (getline(ss, part, split_point)) {
        strings.push_back(part);
    }
    
    return strings;
}

ConfusionMatrix digitClassifier::CreateConfusionMatrix(){
    ConfusionMatrix matrix;
    for (int row = kFirstDigit; row <= kLastDigit; row++) {
        std::vector<double> values;
        for (int col = kFirstDigit; col <= kLastDigit; col++) {
            values.push_back(0);
        }
        matrix.push_back(values);
    }
    return matrix;
}
