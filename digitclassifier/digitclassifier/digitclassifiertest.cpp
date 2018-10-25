//
//  digitclassifiertest.cpp
//  digitclassifier
//
//  Created by A.Kadri Türker on 10/24/18.
//  Copyright © 2018 A.Kadri Türker. All rights reserved.
//
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "digitclassifier.hpp"

TEST_CASE("Import Data Tests"){
    digitClassifier digit;
    digit.ImportData("/Users/a.kadri/Documents/naive-bayes-TheRealLordVile/"
                     "digitclassifier/digitclassifier/digitdata/trainingimages",
                     "/Users/a.kadri/Documents/naive-bayes-TheRealLordVile"
                     "/digitclassifier/digitclassifier/"
                     "digitdata/traininglabels");
    
    SECTION("Number of Images Tests"){
        REQUIRE(digit.num_train_exmp == 5000);
        int num_elements = 0;
        for (int num = 0; num <= 9; num++) {
                    num_elements += digit.data_set[num]
                    [std::make_pair(0, 0)].first;
            num_elements += digit.data_set[num]
                    [std::make_pair(0, 0)].second;
            }
        REQUIRE(num_elements == 5000);
        
        //Since all images have 00 pixel as white.
        int num_white_pix_in00 = 0;
        for (int num = 0; num <= 9; num++) {
            num_white_pix_in00 += digit.data_set[num]
                                  [std::make_pair(0, 0)].first;
            
        }
        REQUIRE(num_white_pix_in00==5000);
    }
    SECTION("Probabilities Valid Tests"){
        for (int num = 0; num <= 9; num++) {
            for(int i=0;i<28;i++){
                for(int j=0;j<28;j++){
                    double prob_white = digit.prob_set[num]
                                        [std::make_pair(j, i)].first;
                    
                    double prob_blackgray = digit.prob_set[num]
                                            [std::make_pair(j, i)].second;
                    bool isValidWhite = prob_white <= 1 && prob_white >= 0;
                    bool isValidBlackGray = prob_blackgray <= 1 &&
                                            prob_blackgray >= 0;
                    bool isValid =isValidWhite && isValidBlackGray;
                    REQUIRE(isValid);
                }
            }
        }
    }
}

TEST_CASE("File Writing/ Reading Tests"){
    digitClassifier digit;
    digit.ImportData("/Users/a.kadri/Documents/naive-bayes-TheRealLordVile/"
                     "digitclassifier/digitclassifier/digitdata/trainingimages",
                     "/Users/a.kadri/Documents/naive-bayes-TheRealLordVile"
                     "/digitclassifier/digitclassifier/"
                     "digitdata/traininglabels");
    
    SECTION("Check If File Writting/Reading is consistent") {
        digit.WriteModelToFile("/Users/a.kadri/Documents/"
                               "naive-bayes-TheRealLordVile/digitclassifier"
                               "/digitclassifier/datamodel.txt");
        int num_elem = digit.num_train_exmp;
        std::map<int,std::map<Coordinates,std::pair<int, int>>> data =
        digit.data_set;
        
        std::map<int,std::map<Coordinates,std::pair<double, double>>> prob =
        digit.prob_set;
        
        digitClassifier new_digit;
        new_digit.ImportModelFromFile("/Users/a.kadri/Documents/"
                                  "naive-bayes-TheRealLordVile/digitclassifier/"
                                  "digitclassifier/datamodel.txt");
        REQUIRE(new_digit.num_train_exmp == num_elem);
        REQUIRE(new_digit.data_set == data);
        REQUIRE(new_digit.prob_set == prob);
    }
    
    SECTION("Check If reading/writing is succesfull"){
        
        REQUIRE(digit.WriteModelToFile("/Users/a.kadri/Documents/"
                                       "naive-bayes-TheRealLordVile/"
                                       "digitclassifier"
                                       "/digitclassifier/datamodel.txt"));
        REQUIRE(digit.ImportModelFromFile("/Users/a.kadri/Documents/"
                                          "naive-bayes-TheRealLordVile/"
                                          "digitclassifier/"
                                          "digitclassifier/datamodel.txt"));
        
    }
    
}
TEST_CASE("Image classification Tests"){
    
}
