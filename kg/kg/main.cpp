//
//  main.cpp
//  kg
//
//  Created by Kgomotso Monnakgotla on 4/17/19.
//  Copyright © 2019 Kgomotso Monnakgotla. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <sstream>
#include <limits>

// When we create a variable we are telling the computer
// how much memory to set aside for its value and what
// name we want to associate with that data

// Variable names can contain letters, numbers, underscores
// but not math operators, spaces and can't start with a number

// Global variables are declared outside of any functions
// and can be accessed any where in the code
// This is a global integer variable with a name using
// Hungarian notation
int g_iRandNum = 0;

// const defines constant values that won't change
const double PI = 3.1415926535897932;

int main() {
    bool bMarried = true;
    char chMyGrade = 'A';
    unsigned short int u16age = 43;
    short int siWeught = 180;
    int nDays = 7;
    float fPi = 3.14159;
    double dbBigFloat = 1.111111111111111;
    long double  ldpi =3.14159;
    auto whatWillIbe = true;
    
    std::cout << " Min bool " << std::numeric_limits<bool>::min() << "\n";
    std::cout << " Max bool " << std::numeric_limits<bool>::max() << "\n";
    return 0;
}
