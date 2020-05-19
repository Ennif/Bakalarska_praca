//
// Created by sounteg on 14. 5. 2020.
//

#include "csv_handler.h"
#include <fstream>
#include <iostream>
#include <vector>
#include "../APP/app_handler.h"

using namespace std;

csv_handler::csv_handler(const string &csvFilename) : csv_filename(csvFilename) {}

csv_handler::~csv_handler() = default;

csv_handler::csv_handler() = default;

char csv_handler::getDelimiter() const {
    return delimiter;
}

const string &csv_handler::getCsvFilename() const {
    return csv_filename;
}

void csv_handler::setCsvFilename(const string &csvFilename) {
    csv_filename = csvFilename;
}

int csv_handler::createCSVFile() {
    fstream csv_file;

    csv_file.open(csv_filename, ios::out | ios::app | ios::in);

    if(!csv_file.is_open()){
        return -1;
    }
    csv_file.close();
    return 0;
}

vector<string> csv_handler::splitCSVline(string line){
    string word = "";
    vector<string> result;
    for(auto letter : line){
        if(letter == delimiter){
            result.push_back(word);
            word = "";
        }else{
            word += letter;
        }
    }
    result.push_back(word);
    return result;
}

int csv_handler::updateDataToCSVFile(vector<sensorDataType> data) {
    fstream csv_file(csv_filename, ios::in | ios::app);
    if (!csv_file.is_open()) {
        cout << "Error while opening the file for update\n" << endl;
        return -1;
    }

    for (auto & item : data) {
        csv_file << item.sensorData << delimiter << item.timeStamp << delimiter << item.dataFlag << "\n";
    }
    csv_file.close();
    return 0;
}

int csv_handler::getNumberOfRowsOfCSVFile() {
    int rows = 0;
    ifstream csv_file(csv_filename);
    string line;
    if(!csv_file.is_open()){
        cout << "File cannot be opened for counting rows!";
        return -1;
    }
    while(getline(csv_file,line)){
        rows++;
    }
    return rows;
}

int csv_handler::cleanCSV(){
    fstream csv_file(csv_filename, ios::out);

    if(!csv_file.is_open()){
        cout<< "Nepodarilo sa vycistit subor\n";
        return -1;
    }
    csv_file << "";
    csv_file.close();
    return 0;
}

int csv_handler::toAverageCSV() {
    fstream csv_file(csv_filename, ios::in);

    if(!csv_file.is_open()){
        cerr << "File cannot be opened to average CSV data!\n";
        return -1;
    }
    string line;
    vector<sensorDataType> dataFromCSV;
    sensorDataType item;
    vector<string> row;

     while(getline(csv_file,line)){
         row = splitCSVline(line);
         item.sensorData = stof(row[0]);
         item.timeStamp = stoll(row[1]);
         item.dataFlag = stoi(row[2]);

         dataFromCSV.emplace_back(item);
     }
    csv_file.close();
    cleanCSV();
    vector<sensorDataType> result;
    result = app_handler::makeAverageOfData(dataFromCSV);
    updateDataToCSVFile(result);

}

bool csv_handler::areAllRowsWithAverageFlag() {
    fstream csv_file(csv_filename, ios::in);

    if(!csv_file.is_open()){
        cerr << "File cannot be opened!\n";
    }
    string line;
    vector<sensorDataType> data;
    sensorDataType item;
    vector<string> row;

    while(getline(csv_file,line)){
        row = splitCSVline(line);
        item.sensorData = stof(row[0]);
        item.timeStamp = stoull(row[1]);
        item.dataFlag = stoi(row[2]);

        data.emplace_back(item);
    }
    csv_file.close();
    vector<sensorDataType> dataWithFlag2 = app_handler::getDataByFlag(data,2);

    return getNumberOfRowsOfCSVFile() == dataWithFlag2.size();
}
