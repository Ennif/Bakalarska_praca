//
// Created by Jakub Trstensky on 14. 5. 2020.
//

#ifndef BP_CSV_HANDLER_H
#define BP_CSV_HANDLER_H
#include <string>
#include <vector>
#include "../data/vector_type.h"



using namespace std;

class csv_handler {
private:
    string csv_filename = "sensorData.csv";
    char delimiter = ',';

public:
    explicit csv_handler(const string &csvFilename);

    virtual ~csv_handler();

    char getDelimiter() const;

    csv_handler();

    const string &getCsvFilename() const;

    void setCsvFilename(const string &csvFilename);

    int createCSVFile();

    vector<string> splitCSVline(string);

    int updateDataToCSVFile(vector<sensorDataType>);

    int getNumberOfRowsOfCSVFile();

    int cleanCSV();

    bool areAllRowsWithAverageFlag();

    int toAverageCSV();
};


#endif //BP_CSV_HANDLER_H
