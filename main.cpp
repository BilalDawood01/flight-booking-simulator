// BY BILAL DAWOOD 
// FILE: main.cpp

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <regex>
#include <algorithm>
#include "seat.h"
#include "flight.h"
#include "passenger.h"
#include "main.h"
using namespace std;


int main(){
    int choice;
    header();
    Flight f= processFile(); 
    while((choice=getInput())){
        switch (choice) {
            case 1: 
                f.showSeatMap();        
                break;
            case 2: 
                f.showPassengerInfo();  
                break;
            case 3: 
                f.addPassenger();       
                break;
            case 4: 
                f.removePassenger();    
                break;
            case 5: 
                f.saveData();           
                break;
            case 6: 
                end();                  
                break;
            default: 
                cout<<endl<<"Invalid choice"<<endl<<endl;
        }
    }
}

void header(){
    cout<<"Term Project - Flight  Management Program in C++"<<endl<<"Produced by: Bilal Dawood";
    cout<<endl<<"<<< Press Return to Continue >>>"<<endl; 
    cin.get(); 
}
int getInput(){  
    string choiceS; 
    int choice;
    cout<<"Please select one the following options: " <<endl<<
        "1. Display Flight Seat Map."                <<endl<<
        "2. Display Passengers Information."         <<endl<<
        "3. Add a New Passenger."                    <<endl<<
        "4. Remove an Existing Passenger"            <<endl<<
        "5. Save data"                               <<endl<<
        "6. Quit. "                                  <<endl<<
        "Enter your choice:  (1, 2, 3, 4, 5 or 6): "; 
        getline(cin,choiceS);
    cout<<endl;
    try{
        choice= stoi(choiceS); 
        return choice;
    }
    catch(invalid_argument&){}
    return 7;
}
vector<string> stringToVector(string s){//this function takes a sentence, splits it word by word and stores
    //each word in a vector. used for reading from a line from the file and seperating the info in each column 
    bool wordEncountered=true;
    vector<string> words;
    string word="";
    for(int i=0;i<(int)s.length();i++){
        if(s[i]==' '){
            if(wordEncountered)words.push_back(word);
            word="";
            wordEncountered=false;
        }
        else{
            word+=s[i];
            wordEncountered=true;
        }
    }
    words.push_back(word);
    return words;
}
Flight processFile(){//this function reads from the file to process the data and then create an object of flight class
    int count=0; 
    Flight f; 
    ifstream file;
    file.open("flight_info.txt");
    if(file){ //checking if file exists
        string text="";
        while (getline(file,text)){
            if(text.length()==0)
                continue;
            vector<string> words = stringToVector(text);
            if(count==0){
                f.flightName= words.at(0);
                f.r= stoi(words.at(1));
                f.c= stoi(words.at(2));
                count++;
            }
            else {
                if(words.size()>5){
                    string fname,lname;
                    vector<string> names;
                    int phoneNumberIndex,mid;
                    for(int i=0;i<(int)words.size();i++){
                        try{
                            int trigger= stoi(words.at(i));
                            phoneNumberIndex=i;
                            break;
                            trigger++;
                            trigger--;
                        }
                        catch(invalid_argument&){
                            names.push_back(words.at(i));
                        }
                    }
                    for(int i=0;i<phoneNumberIndex;i++){
                        words.erase(words.begin());
                    }
                    if(names.size()%2==0)
                        mid=names.size()/2;
                    else 
                        mid= (names.size()/2)+1;
                    for(int i=mid;i<(int)names.size();i++){
                        lname+=names.at(i)+" ";
                    }
                    for(int i=0;i<mid;i++){
                        fname+=names.at(i)+" ";
                    }
                    words.insert(words.begin(),lname);
                    words.insert(words.begin(),fname);
                }
                f.createPassenger(words);
            }
        }
        file.close();
    }
    else 
        cout<<"File doesn't exist";
    return f;
}
void end(){
    cout<<"Program Terminated.";
    exit(1);
}