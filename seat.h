// BY BILAL DAWOOD and GUFRAN SABRI
// FILE: seat.h

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <regex>
#include <algorithm>

using namespace std;

#ifndef SeatClass
#define SeatClass

class Seat{ //seat class that deals with all the seat info of passenger class such as col and row
    public: 
        string col; 
        int row;
}; 

#endif

