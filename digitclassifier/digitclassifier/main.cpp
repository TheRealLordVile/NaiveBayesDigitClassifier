//
//  main.cpp
//  digitclassifier
//
//  Created by A.Kadri Türker on 10/19/18.
//  Copyright © 2018 A.Kadri Türker. All rights reserved.
//

#include <iostream>
#include "digitclassifier.hpp"

int main(int argc, const char * argv[]) {
    digitClassifier digit;
    digit.ImportData("/Users/a.kadri/Desktop/digitdata/trainingimages", "/Users/a.kadri/Desktop/digitdata/traininglabels");
    for(int i=0;i<28;i++){
        for(int j=0;j<28;j++){
          std::cout << digit.data_set[0][std::make_pair(j, i)][0];
        }
        std::cout << "\n";
    }
    std::cout << "Hello, World!\n";
    return 0;
}
