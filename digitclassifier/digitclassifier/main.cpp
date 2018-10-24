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
    //std::cout<< "Please Enter 0 to read training data to create a model, "
    //            "1 to write an existing model to a file, 2 to read an existing "
    //            "model from a file, 3 to clasify data";
    
    digit.ImportData("/Users/a.kadri/Documents/naive-bayes-TheRealLordVile/digitclassifier/digitclassifier/digitdata/trainingimages",
                     "/Users/a.kadri/Documents/naive-bayes-TheRealLordVile/digitclassifier/digitclassifier/digitdata/traininglabels");
    for(int i=0;i<28;i++){
        for(int j=0;j<28;j++){
          //std::cout << digit.data_set[5][std::make_pair(j, i)][460];
        }
        //std::cout << "\n";
    }
    digit.WriteModelToFile("/Users/a.kadri/Documents/naive-bayes-TheRealLordVile/digitclassifier/digitclassifier/datamodel.txt");
    digit.ImportModelFromFile("/Users/a.kadri/Documents/naive-bayes-TheRealLordVile/digitclassifier/digitclassifier/datamodel.txt");
    //std::cout << digit.num_train_exmp;
    digit.ClassifyImages("/Users/a.kadri/Documents/naive-bayes-TheRealLordVile/digitclassifier/digitclassifier/digitdata/testimages",
                         "/Users/a.kadri/Documents/naive-bayes-TheRealLordVile/digitclassifier/digitclassifier/digitdata/testlabels");
    return 0;
}
