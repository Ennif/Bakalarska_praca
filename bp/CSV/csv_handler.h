//
// Created by sounteg on 14. 5. 2020.
//

#ifndef BP_CSV_HANDLER_H
#define BP_CSV_HANDLER_H
#include <string>
#include <vector>


using namespace std;

class csv_handler {
private:
    string csv_filename = "data/sensorData.csv";
    char delimiter = ',';

public:
    csv_handler(const string &csvFilename);

    virtual ~csv_handler();

    char getDelimiter() const;

    csv_handler();

    const string &getCsvFilename() const;

    void setCsvFilename(const string &csvFilename);

    void createCSVFile();

    void writeToCSVFile(vector<vector<int>>);

    int pushCsvDataToDatabase();

    vector<string> splitCSVline(string);
};


#endif //BP_CSV_HANDLER_H
