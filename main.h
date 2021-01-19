// ENSF 337 TERM PROJECT 
// BY BILAL DAWOOD 
// UCID: 30092405
// FILE: main.h

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <regex>
#include <algorithm>
#include "seat.h"
#include "flight.h"
#include "passenger.h"

using namespace std;

#ifndef functions
#define functions

void header();
//PRINTS PROJECT HEADER INTO CONSOLE AND WAITS FOR USER TO PRESS ENTER
         
int getInput();
//GETS USER MENU CHOICE

Flight processFile();
//opens file flight_info.txt and reads it while getting values
         
vector<string> stringToVector(string s);
//CONVERTS PASSENGER INFO FROM THE TXT FILE TO A LIST OF WORDS FOR EASIER ASSIGNMENT
         
 void end();
 //TERMINATES THE PROGRAM WHEN CALLED
 
 #endif