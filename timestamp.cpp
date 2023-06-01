//
// Created by grimy on 25.05.2023.
//
#include <iostream>
#include <chrono>
#include <fstream>
#include <cstring>
#include <iomanip>
#include "timestamp.h"

Timestamp::Timestamp() {
    std::time_t currentTime = std::time(nullptr);
    std::tm* localTime = std::localtime(&currentTime);

    int hours = localTime->tm_hour;
    int minutes = localTime->tm_min;
    int seconds = localTime->tm_sec;
    num_sec = hours * 3600 + minutes * 60 + seconds;
}
void Timestamp::writeTimestamp(const string& filepath) const{
    char name[1000];
    strcpy(name, filepath.c_str());
    ifstream inputFile(filepath); // Open the input file for reading
    ofstream tempFile("temp.txt"); // Create a temporary output file

    if (inputFile.is_open() && tempFile.is_open()) {
        string line;
        int lineNumber = 1;
        int lineToModify = 1;

        while (getline(inputFile, line)) {
            if (lineNumber == lineToModify) {
                // Find and modify the target word within the line
                istringstream iss(line);
                ostringstream oss;
                string word;
                bool isFirstWord = true;
                int x = num_sec;
                int i = 9;
                //cout <<num_sec << endl;
                while (iss >> word) {
                        if (!isFirstWord) {
                            oss << ' ';
                        }
                        for(int j=0;j<word.length()&&i>0;j++) {
                            word[j] &= 0b111111;
                            word[j] |= ((x << 6) & 0b11000000);
                            x>>=2;
                            i--;
                        }
                        oss << word;
                    isFirstWord = false;
                }
                line = oss.str();
            }
            tempFile << line << endl; // Write the line to the temporary file
            lineNumber++;
        }
        inputFile.close();
        tempFile.close();

        remove(name);
        rename("temp.txt", name);
    }
    else {
        cout << "Failed to open the input or temporary file." << std::endl;
    }



}
string Timestamp::readTimestamp(const string& filepath) {
    ifstream inputFile(filepath);
    int n = 0;
    if (inputFile.is_open()) {
        string line;
        getline(inputFile, line);
        line.erase(remove(line.begin(), line.end(), ' '), line.end());

        for(int i=0;i<9;i++) {
           // cout << hex<<((line[i]&0xF0)>>4)<<(line[i] & 0xF) <<" ";
            n |= ((line[i] >> 6) & 3) << (i*2);
        }
        inputFile.close();
    } else {
        cout << "Failed to open the input or temporary file." << std::endl;
    }
    int h = n/3600;
    int m = (n-h*3600)/60;
    int s = n-h*3600-m*60;
    std::ostringstream oss;
    oss << setfill('0') << setw(2) << h << ":"
        << setfill('0') << setw(2) << m << ":"
        << setfill('0') << setw(2) << s;
    string formattedTime = oss.str();
    return formattedTime;
}