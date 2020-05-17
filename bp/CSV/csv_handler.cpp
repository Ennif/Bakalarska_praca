//
// Created by sounteg on 14. 5. 2020.
//

#include "csv_handler.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <pqxx/pqxx>
#include "../Database/db_handler.h"

using namespace std;
using namespace pqxx;

csv_handler::csv_handler(const string &csvFilename) : csv_filename(csvFilename) {}

csv_handler::~csv_handler() {}

csv_handler::csv_handler() {}

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
            word = word + letter;
        }
    }
    result.push_back(word);
    return result;
}

int csv_handler::updateDataToCSVFile(vector<vector<int>> data) {
    fstream csv_file(csv_filename, ios::in | ios::app);
    if (!csv_file.is_open()) {
        cout << "Error while opening the file for update\n" << endl;
        return -1;
    }
    else
        cout << "File for update opened successfully\n" << endl;

    for (int i = 0; i < data.size(); ++i) {
        for (int j = 0; j < data.at(i).size(); ++j) {

            csv_file << data.at(i).at(j);
            if( j != data.at(i).size() -1 ){
                csv_file << ",";
            }
        }
        if(i != data.size()){
            csv_file << "\n";
        }
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
