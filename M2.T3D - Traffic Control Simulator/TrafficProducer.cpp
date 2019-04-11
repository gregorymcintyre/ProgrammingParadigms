/* TrafficProducer.cpp
 * Greg McIntyre
 * 11 APR 2019
 * 
 * This file is designed to be run by a scheduler to log traffic information to the log.txt file 
 * 
 */

#include <iostream>
#include <random>
#include <ctime>
#include <fstream>

using namespace std;

#define NUM_LIGHTS 12       //number of traffic lights

int main(){

    string output;
    time_t result = time(nullptr);
    string dateStamp = asctime(gmtime(&result));

    if ( dateStamp.size() > 0 && dateStamp[dateStamp.length()-1] == '\n' ) 
        dateStamp.resize( dateStamp.length()-1 );           //removes \n from end of stamp

    for (int i = 1 ; i <= NUM_LIGHTS ; i++){
        
        output+= dateStamp + ";";
        output+= to_string(i) + ";";
        int cars = rand() % ((10 - 1) + 1) + 1;
        output+= to_string(cars) + ";\n";                   //log entry std::stamp ; light no. ; number of cars (random)
    }

    fstream log("log.txt", ios::app);                       //append to log file
    if(!log.is_open()){
        cout<<"Error: Log file not found"<<endl;
    } else {
        log<<output;
        cout<<"log.txt has been updated at "<<dateStamp<<endl;
    }

    //cout<<output<<endl;
    return 0;
}