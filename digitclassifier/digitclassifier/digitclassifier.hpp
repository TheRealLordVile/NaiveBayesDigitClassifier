//
//  digitclassifier.hpp
//  digitclassifier
//
//  Created by A.Kadri Türker on 10/19/18.
//  Copyright © 2018 A.Kadri Türker. All rights reserved.
//

#ifndef digitclassifier_hpp
#define digitclassifier_hpp

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

class digitClassifier{
public:
    void ImportData(std::string file_path);
    std::vector<std::vector<int>> data_set;
};
#endif /* digitclassifier_hpp */
