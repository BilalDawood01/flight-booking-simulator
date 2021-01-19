// ENSF 337 TERM PROJECT 
// BY BILAL DAWOOD 
// UCID: 30092405
// FILE: passenger.cpp

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <regex>
#include <algorithm>
#include "seat.h"
#include "passenger.h"

using namespace std;

void Passenger::assignSeatValues(string seat){//Assigns row and col for the seat obj in the calling passenger
            s.row= stoi(seat); 
            s.col=seat[seat.length()-1];
        }
