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
    digit.ImportData("/Users/a.kadri/Documents/naive-bayes-TheRealLordVile/digitclassifier/digitclassifier/digitdata/trainingimages",
                     "/Users/a.kadri/Documents/naive-bayes-TheRealLordVile/digitclassifier/digitclassifier/digitdata/traininglabels");
    for(int i=0;i<28;i++){
        for(int j=0;j<28;j++){
          //std::cout << digit.data_set[5][std::make_pair(j, i)][460];
        }
        //std::cout << "\n";
    }
    digit.WriteModelToFile("/Users/a.kadri/Documents/naive-bayes-TheRealLordVile/digitclassifier/digitclassifier/datamodel.txt");
    //digit.ImportModelFromFile("/Users/a.kadri/Documents/naive-bayes-TheRealLordVile/digitclassifier/digitclassifier/datamodel.json");
    //std::cout << digit.num_train_exmp;
    return 0;
}
