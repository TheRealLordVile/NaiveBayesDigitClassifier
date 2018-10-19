//
//  digitclassifier.cpp
//  digitclassifier
//
//  Created by A.Kadri Türker on 10/19/18.
//  Copyright © 2018 A.Kadri Türker. All rights reserved.
//

#include "digitclassifier.hpp"

void digitClassifier::ImportData(std::string filePath){
    std::ifstream train_file(filePath);
    std::string line;
    while (std::getline(train_file, line)) {
        std::string picture;
        for (int i=0; i<=28; i++) {
            std::getline(train_file,line);
            picture += line;
        }
        std::vector<int> num_pixels;
        int num_white_pix = std::count(line.begin(), line.end(), ' ');
        num_pixels.push_back(num_white_pix);
        int num_gray_black_pix = std::count(line.begin(), line.end(), '#');
        num_gray_black_pix += std::count(line.begin(), line.end(), '+');
        num_pixels.push_back(num_gray_black_pix);
        data_set.push_back(num_pixels);
    }
}
