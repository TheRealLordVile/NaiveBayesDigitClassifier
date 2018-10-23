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
    data_set = std::map<int,std::map<Coordinates,std::vector<int>>>();
    std::vector<int> initial_vec;
    for(int i =0; i<=9;i++) {
        std::map<Coordinates,std::vector<int>> numRepeatance;
        for(int j = 0; j<28; j++) {
            for(int k = 0; k<28; k++) {
                numRepeatance[std::make_pair(k, j)] = initial_vec;
            }
        }
        data_set[i] = numRepeatance;
    }
}

void digitClassifier::InitializeProbabilitySet(){
    class_prob = std::vector<double>();
    prob_set = std::map<int,std::map<Coordinates,std::pair<double, double>>>();
    std::pair<double,double> initial_values = std::make_pair(0, 0);
    for(int i =0; i<=9;i++) {
        std::map<Coordinates,std::pair<double,double>> numRepeatance;
        for(int j = 0; j<28; j++) {
            for(int k = 0; k<28; k++) {
                numRepeatance[std::make_pair(k, j)] = initial_values;
            }
        }
        
        prob_set[i] = numRepeatance;
    }
    
}

void digitClassifier::ImportData(std::string data_path, std::string label_path){
    std::ifstream train_file(data_path);
    std::string line;
    
    std::ifstream label_file(label_path);
    std::string label;
    
    
    while(true) {
        if(!std::getline(label_file,label)){
            break;
        }
        int label_ind = stoi(label);
        num_train_exmp++;
        for (int i = 0; i < 28; i++) {
            std::getline(train_file,line);
            for (int j=0; j < 28; j++) {
                Coordinates coord = std::make_pair(j,i);
                if(line.at(j) == '+' || line.at(j) == '#'){
                    data_set[label_ind][coord].push_back(1);
                } else{
                    data_set[label_ind][coord].push_back(0);
                }
            }
           

        }

    }
    std::cout<<num_train_exmp<<"\n";
    CalculateProbabilities();
    
}

void digitClassifier::CalculateProbabilities(){
    for(int i = 0; i <= 9; i++){
        Coordinates default_coord = std::make_pair(0, 0);
        int num_digit_repeat = data_set[i][default_coord].size();
        double prob_digit = (kClassifyConst + num_digit_repeat) /
                            (num_train_exmp + 2 * kClassifyConst);
        class_prob.push_back(prob_digit) ;
        for (int j = 0; j < 28; j++) {
            for (int k = 0; k < 28; k++) {
                Coordinates coord = std::make_pair(k, j);
                int num_repeatence = data_set[i][coord].size();
                int num_whit = std::count(data_set[i][coord].begin(),
                                          data_set[i][coord].end() , 0);
                int num_grblack = std::count(data_set[i][coord].begin(),
                                             data_set[i][coord].end() , 1);
                double prob_white = (num_whit + kClassifyConst) /
                                    (num_repeatence+ 2 * kClassifyConst);
                double prob_grblack = (num_grblack + kClassifyConst) /
                                      (num_repeatence+ 2 * kClassifyConst);
                prob_set[i][coord] = std::make_pair(prob_white, prob_grblack);
            }
        }
    }
}

int digitClassifier::GetMostLikelyDigit(std::map<Coordinates,int> image_set){
    double highest_prob = 0;
    int digit_highest_prob = -1;
    for (int digit = 0; digit <= 9; digit++) {
        double digit_prob = GetDigitProbability(digit ,image_set);
        if (digit_prob > highest_prob) {
            highest_prob = digit_prob;
            digit_highest_prob = digit;
        }
    }
    return digit_highest_prob;
}

double digitClassifier::GetDigitProbability(int digit, std::map<Coordinates,int> image_set){
    double digit_prob = log(class_prob[digit]);
    for (int i = 0; i < 28; i++) {
        for (int j = 0; j < 28; j++) {
            Coordinates coord = std::make_pair(j, i);
            digit_prob += GetPixelProbability(digit,coord, image_set[coord]);
        }
    }
    
    return digit_prob;
}

double digitClassifier::GetPixelProbability(int digit, Coordinates coord, int color){
    if(color == 0){
        return log(prob_set[digit][coord].first);
    }
    
    return log(prob_set[digit][coord].second);
}

bool digitClassifier::WriteModelToFile(std::string file_path){
    if (data_set.empty() || num_train_exmp == 0){
        return false;
    }
    std::ofstream output_file;
    output_file.open(file_path);
    output_file << num_train_exmp;
    output_file << "\n";
    for (int digit = 0; digit <= 9; digit++) {
        output_file << GetDigitString(digit);
        
    }
    output_file.close();
    return true;
}

std::string digitClassifier::GetDigitString(int digit){
    std::string digit_string;
    for (int i = 0; i<28; i++) {
        for (int j = 0; j<28; j++) {
            Coordinates coord = std::make_pair(j, i);
            for (int k=0; k < data_set[digit][coord].size();k++){
                digit_string += std::to_string(data_set[digit][coord][k]) + ",";
            }
            digit_string += ";";
        }
    }
    
    return digit_string + "\n";
}

bool digitClassifier::ImportModelFromFile(std::string file_path){
    std::ifstream input_file;
    std::string line;
    std::getline(input_file, line);
    num_train_exmp = std::stoi(line);
    for (int digit = 0;digit <= 10;digit++) {
        
    }
    std::cout << line<<"\n";
   
    
    return true;
}

