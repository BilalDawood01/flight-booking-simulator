// BY: BILAL DAWOOD and GUFRAN SABRI
// FILE: flight.cpp

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <regex>
#include <algorithm>
#include <iomanip>
#include "seat.h"
#include "flight.h"
#include "passenger.h"
using namespace std;


int Flight::getCol(string col){  //converts col to int, used in seatmap
    if (col.length() == 1)
	{
		if (col[0] >= 'A' && col[0] < 'A' + r)
		{
			return (int) (col[0] - 'A');
		}
		else if (col[0] >= 'a' && col[0] < 'a' + r)
		{
			return (int) (col[0] - 'a');
		}
	}
    return -1;
}
void  Flight::sortPassengers(){ //use "temp" (organised passenger) here used selection sort algorithm for sorting
    for(int i=0;i<(int)temp.size();i++){
        int min = i;
        for(int j=i+1;j<(int)temp.size();j++){
            if(temp.at(j).s.row<temp.at(min).s.row)
            min=j;
            if(temp.at(j).s.row==temp.at(min).s.row){
                if(temp.at(j).s.col.compare(temp.at(min).s.col)<0)
                min=j;
            }
        }
        Passenger tempPass = temp.at(min);
        temp.at(min)= temp.at(i);
        temp.at(i)=tempPass;
    }
}
void Flight::createPassenger(vector<string> pInfo){
    Passenger tempPass;
    tempPass.fName=pInfo.at(0);
    tempPass.lName=pInfo.at(1);
    tempPass.phoneNo=pInfo.at(2);
    tempPass.assignSeatValues(pInfo.at(3));
    tempPass.pId=stoi(pInfo.at(4));
    temp.push_back(tempPass);
    p.push_back(tempPass);
    sortPassengers();
}
string Flight::replaceSpaces(string s){
    int stringLength = s.length();
    string newString;
    for(int i=0;i<stringLength;i++){
        if(s[i]==' ')
            newString+="-";
        else
            newString+=s[i];
    }
    return newString;
}
bool Flight::validateId(string id){
    try{
        int trigger= stoi(id);//takes integer part of ID, if there is anything else, throws invalid argument
        trigger++;//code was presenting "unused variable" warning. Only used to get rid of warning
        trigger--;//otherwise trigger is only used when there is a invalid argument.
    }
    catch(invalid_argument&){//
        return false;
    }
    for(int i=0;i<(int)p.size();i++){
        try{
            if(p.at(i).pId==stoi(id))
                return false;
        }
        catch(invalid_argument&){
            return false;
        }
    }
    return true;
}
int Flight::validateName(string nameFL){
    string onlySpaces(nameFL.length(),' ');
    if(nameFL==onlySpaces) return 1;
    else if(nameFL.length()>20) return 2;
    else return 0;
}
bool Flight::validateSeat(string row,string col){
    string seat = row+col;
    if(getCol(col)==-1)
        return false;
    try{
        int trigger= stoi(row);
        if(trigger>r||trigger<0)
            return false;
    }
    catch(invalid_argument&){
        return false;
    }
    for(int i=0;i<(int)p.size();i++){
        string s= to_string(p.at(i).s.row)+p.at(i).s.col;
        if(s==seat)
            return false;
    }
    return true;
}
bool Flight::validatePhoneNumber(string& phoneNo){
    regex r1("[0-9]{3}-[0-9]{3}-[0-9]{4}");
    regex r2("[0-9]{3}[0-9]{3}[0-9]{4}");
    if(regex_match(phoneNo,r2)){
        string fixedPhoneNum="";
        for(int i=0;i<10;i++){
            if(i==3||i==6){
                fixedPhoneNum+="-";
                fixedPhoneNum.push_back(phoneNo[i]);
            }
            else
                fixedPhoneNum.push_back(phoneNo[i]);
        }
        phoneNo=fixedPhoneNum;
    }
    phoneNo= replaceSpaces(phoneNo);
    return regex_match(phoneNo,r1);
}
vector<string> Flight::getSeatInput(){
    string seat,row,col;
    cout<<"Enter the passenger's desired row:";
    getline(cin,row);
    cout<<"Enter the passenger's desired seat:";
    getline(cin,col);
    transform(col.begin(), col.end(),col.begin(), ::toupper);//converts all letters to upper in seat col.
    seat= row+col;
    vector<string> seatInfo{row,col,seat};
    return seatInfo;
}
void Flight::addPassenger(){
    string fname,lname,phoneNo,id;
    vector<string> seatInfo;

    cout<<"Please enter the passenger id: ";
    getline(cin,id);//initial input
    while(!validateId(id)){ //if validateId returns false, code will display the following and ask for input again:
        cout<<"ID unavailable or invalid. Please enter a valid ID: ";
        getline(cin,id);
    }

    cout<<"Please enter the passenger first name: ";
    getline(cin,fname);
    int validFName = validateName(fname);
    while(validFName!=0){//makes sure there is input for fname(numbers and spaces will not cause an...
        if(validFName==1) cout<<"Invalid! Please enter the passenger first name:";//...errors as some names have numbers and spaces)
        validFName = validateName(fname);
        if(validFName==2) cout<<"Name too long! First name must be less than 20 characters: ";
        getline(cin,fname);
        validFName = validateName(fname);
    }

    cout<<"Please enter the passenger last name:";
    getline(cin,lname);
     int validLName = validateName(lname);
    while(validLName!=0){//makes sure there is input for fname(same invalid input rule as fname)
        if(validLName==1) cout<<"Invalid! Please enter the passenger's last name:";
        if(validLName==2) cout<<"Name too long! Last name must be less than 20 characters: ";
        getline(cin,lname);
        validLName = validateName(lname);
    }

    cout<<"Please enter the passenger phone number: ";
    getline(cin,phoneNo);
    while(!validatePhoneNumber(phoneNo)){//valid numbers have 10 digits, no letters. '-' and ' ' will not...
        cout<<"Invalid phone number. Please enter a valid number: "; //...return invalid input if placed at index 3 and 6
        getline(cin,phoneNo);
    }

    seatInfo= getSeatInput();
    while(!validateSeat(seatInfo.at(0),seatInfo.at(1))){
        cout<<"Seat unavailable or invalid... Please try again. "<<endl;
        seatInfo=getSeatInput();
    }
    cout<<endl;

    vector<string> newPassengerData{fname,lname,phoneNo,seatInfo.at(2),id};
    createPassenger(newPassengerData);
    cout<<"Passenger added!"<<endl<<endl;
}
void Flight::removePassenger(){
    string idTemp;
    bool found=false;
    cout<<"Please enter the id of the passenger that needs to be removed:";
    getline(cin,idTemp);
    try{
        int id=stoi(idTemp);//takes integer part of string input...invalid arg thrown
        for(int i=0;i<(int)p.size();i++){//loop searches for matching id in passenger p
            if(p.at(i).pId==id){
                p.erase(p.begin()+i);
                i--;
                found=true;//removes from passenger p if found
            }
        }
        for(int i=0;i<(int)temp.size();i++){//loop searches for matching id in passenger in temp (organised...
            if(temp.at(i).pId==id){//...passenger by seat number
                temp.erase(temp.begin()+i);
                i--;
                found=true;//removes passenger from temp if found
            }
        }
        cout<<endl;
        if(found)
            cout<<"Passenger removed."<<endl<<endl;
        else
            cout<<"Passenger not found..."<<endl<<endl;//if found =false
    }
    catch (invalid_argument&){//invalid arg caught
        cout<<endl<<"Invalid ID..."<<endl<<endl;
    }
}
void Flight::showSeatMap(){
    if((int)temp.size()!=0){
        int passengerIndex=0;
        int row=temp.at(passengerIndex).s.row;
        int col=getCol(temp.at(passengerIndex).s.col);
        string a="+---+",b="---+",bar="";//combination for neat table
        cout<<"  ";
        string seperateRows="\n   +";
        for(int i=0; i<c;i++){
            cout<<"   "<<(char)('A'+i);
            seperateRows+=b;
        }
        seperateRows+="\n";
        cout<<seperateRows;
        for(int i=0; i<=r;i++){
            cout<<left<< setw(3) <<i<<"|";
            for(int j=0;j<c;j++){//for printing rows
                if(j==col&&i==row){//if j and col match passenger info, X will be printed onto the council
                    cout<<" X |";
                    passengerIndex++;//updating passengerIndex to point to next passenger
                    if(passengerIndex<(int)temp.size()){ //getting row and column of passenger object...
                        row= temp.at(passengerIndex).s.row; //...that passengerIndex is pointing at
                        col= getCol(temp.at(passengerIndex).s.col);
                    }
                    //else cout<<"   |";
                }
                else cout<<"   |";
            }
            cout<<seperateRows;
        }
        cout<<endl;
    }
    else cout<<endl<<"Flight is empty!!!"<<endl<<endl;
}
void Flight::printSpaces(string s){
    for(int i=s.length();i<20;i++)
        cout<<" ";
}
void Flight::showPassengerInfo(){
    for(int i=0;i<6;i++){
        string title;
        if(i==0)title= "First Name";
        if(i==1)title= "Last Name";
        if(i==2)title= "Phone";
        if(i==3)title= "Row";
        if(i==4)title= "Seat";
        if(i==5)title= "ID";
        cout<<title;
        printSpaces(title);
    }
    for(int i=0;i<(int)p.size();i++){
        cout<<endl<<"-----------------------------------------------------------------------------------------------------------------"<<endl;
        cout<<p.at(i).fName;
        printSpaces(p.at(i).fName);
        cout<<p.at(i).lName;
        printSpaces(p.at(i).lName);
        cout<<p.at(i).phoneNo;
        printSpaces(p.at(i).phoneNo);
        cout<<p.at(i).s.row;
        printSpaces(to_string(p.at(i).s.row));
        cout<<p.at(i).s.col;
        printSpaces(p.at(i).s.col);
        cout<<p.at(i).pId;
    }
    cout<<endl<<"-----------------------------------------------------------------------------------------------------------------"<<endl<<endl;
}
bool Flight::saveData(){
    string s;
    cout<<"Do you want to save the data in the flight_info.txt? Please answer <Y or N>";
    getline(cin,s);
    if(s=="Y"||s=="y"){
        cout<<"All the data in the passenger list was saved into the flight_info.txt."<<endl<<endl;
        ofstream ofile;
        ofile.open("flight_info.txt",ios::trunc);
        ofile<<flightName+" " + to_string(r) + " " + to_string(c)<<endl;
        for(int i=0;i<(int)p.size();i++){
            ofile<<p.at(i).fName;
            for(int j=p.at(i).fName.length();j<20;j++){
                ofile<<" ";
            }
            ofile<<p.at(i).lName;
            for(int j=p.at(i).lName.length();j<20;j++){
                ofile<<" ";
            }
            ofile<<p.at(i).phoneNo;
            for(int j=p.at(i).phoneNo.length();j<20;j++){
                ofile<<" ";
            }
            string seat = to_string(p.at(i).s.row) + p.at(i).s.col;
            ofile<<seat;
            for(int j=seat.length();j<20;j++){
                ofile<<" ";
            }
            ofile<<to_string(p.at(i).pId);
            ofile<<endl;
        }
        ofile.close();
        return true;
    }
    return false;
}
