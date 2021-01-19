// ENSF 337 TERM PROJECT 
// BY BILAL DAWOOD 
// UCID: 30092405
// FILE: flight.h

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <regex>
#include <algorithm>
#include "seat.h"
#include "passenger.h"
using namespace std;

#ifndef FlightClass
#define FlightClass

class Flight{// main class that handles all the flight information
    public:
        vector<Passenger> p,temp; //created 2 vectors here for holding passinfo. temps is sorted according to seat no. 
        //we need a sorted vector for showing seat map(option 1 in menu) and an unsorted vector for showing passenger info table(option 2 in menu)

        int r,c; 
        string flightName;

        int getCol(string col);
         //PROMISES: TAKES COLUMN STRING INPUT 
        //AND CONVERTS IT TO CORRESPONDING INTEGER 

        void sortPassengers();
        //PROMISES: SORTS PASSENGERS BASED ON SEAT

        void createPassenger(vector<string> pInfo);
        //PROMISES: CREATES A PASSENGER OBJECT
        //STORED IN THE VECTOR OF CLASS FLIGHT

        string replaceSpaces(string s);
        //PROMISES: REPLACES THE SPACES WITH DASHES '-' IN PHONE NUMBER

        bool validateId(string id);
        //PROMISES: TAKES STRING ID AND CHECKS IF IT IS VALID
        
        int validateName(string nameFL);
        //PROMISES: MAKES SURE INPUTTED NAME HAS VALID INPUT FOR NAME
        //RETURNS INT WHICH CORRESPONDS TO STATEMENTS USED LATER

        bool validateSeat(string row,string col);
        //PROMISES: TAKES ROW AND COLUMN AND CHECKS IF THE SEAT IS VALID OR AVAILABLE
            
        bool validatePhoneNumber(string& phoneNo);
        //TAKES PHONE NUMBER AND CHECKS IF THE SEAT IS VALID

        vector<string> getSeatInput();
        //GETS USER INPUT FOR SEAT WHILE ADDING NEW PASSENGER
        
        void addPassenger();
        //ADDS A NEW PASSENGER TO THE LIST BASED ON USER INPUT
        
        void removePassenger();
        //REMOVES A PASSENGER FROM THE LIST WITH AN ID SPECIFIED BY USER

        void showSeatMap();
        //PRINTS THE SEAT MAP 

        void printSpaces(string s);
        //Prints spaces to allign all text on console.
        //ensure theres 20 char available for every first name and last name

        void showPassengerInfo();
        //PRINTS THE PASSENGER INFO TABLE
         
        bool saveData();
        //SAVES THE CHANGES MADE TO PASSENGER LIST
};
#endif

