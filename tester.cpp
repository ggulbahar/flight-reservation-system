/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: gamze
 *
 * Created on 29 Aralık 2018 Cumartesi, 10:09
 */

#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>
#include <vector>
#include <fstream>
#include <ctype.h>

using namespace std;

vector<int> seatNumbers;
vector<int> repeatedSeatNumbers;

vector<int> clientNumbers;

fstream input;

void readFile (string filename){
    input.open(filename);
    string line;
    int at;
    string delimiter = "reserves seat";
    int seatNumber;
    while (getline(input,line)) {
        at = line.find(delimiter);
        if(at == string::npos) continue;
        line.erase(0, at + delimiter.length());
        seatNumber = atoi (line.c_str());
        seatNumbers.push_back(seatNumber);
    }
}

bool repeatedSeat (){
    bool repeated = false;
    bool alreadyCounted = false;
    for (int i=0; i<seatNumbers.size()-1; i++) {
        for (int j=i+1; j<seatNumbers.size(); j++) {
            if (seatNumbers.at(i)==seatNumbers.at(j)) {
                repeated=true;
                for(int k=0; k<repeatedSeatNumbers.size(); k++){
                    if(repeatedSeatNumbers.at(k)==seatNumbers.at(i)) {
                        alreadyCounted=true;
                        break;
                    }
                }
                if(!alreadyCounted) repeatedSeatNumbers.push_back(seatNumbers.at(i));
                alreadyCounted=false;
            }
        }
    }
    return repeated;
}

int main(int argc, char** argv) {
    
    readFile(argv[1]);
    
    if (repeatedSeat()) {
        int repeatedSeatNumber = repeatedSeatNumbers.size();
        if (repeatedSeatNumber > 1) {
            cout << "Seats ";
            for (int i=0; i<repeatedSeatNumber-1; i++) {
                cout << repeatedSeatNumbers.at(i) << ", " ;
            }
            cout << "and " << repeatedSeatNumbers.at(repeatedSeatNumber-1) << " are reserved more than once." << endl;
        } else {
            cout << "Seat " << repeatedSeatNumbers.at(0) << " is reserved more than once." << endl;
        }
    } else {
        cout << "There's no seat repetition." << endl;
    }

    return 0;
}

