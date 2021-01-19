// ENSF 337 TERM PROJECT 
// BY BILAL DAWOOD 
// UCID: 30092405
// FILE: passenger.h

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <regex>
#include <algorithm>
#include "seat.h"
using namespace std;

#ifndef PassengerClass
#define PassengerClass
 
 class Passenger{ //passenger class that deals with all passenger info of flight class
    public:
        string fName,lName,phoneNo;
        Seat s;
        int pId; 
        void assignSeatValues(string seat);
        // s.row= stoi(seat);
        //s.col=seat[seat.length()-1];
        
};
#endif