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
    digit.ImportData("digitdata/trainingimages");
    std::cout<<digit.data_set[0][0];
    std::cout << "Hello, World!\n";
    return 0;
}
