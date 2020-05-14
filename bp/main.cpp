
#include <iostream>
#include <vector>
#include <chrono>
#include <string>
#include "CSV/csv_handler.h"
#include "data/Generated/generated_data.h"

using namespace std;

//declarations
int getRandValue();
time_t getTimeStamp();

void read_csv(string csv_filename);
vector<string> split(string,char);


int main() {
    vector<vector<int>> firstSensor;
    vector<vector<int>> secondSensor;
    int counter = 0;

    vector<vector<int>> data;

    csv_handler *csvHandler = new csv_handler();
    csvHandler->createCSVFile();

    generated_data *generatedData = new generated_data();

   chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    while(1) {
        if(counter == 50){
            break;
        }
        if(counter % 10 == 0){
            vector<int> temp;
            temp.push_back(generatedData->getRandomSensorData());
            temp.push_back(generatedData->getTimestamp());
            secondSensor.push_back(temp);
        }
        vector<int> temp;
        temp.push_back(generatedData->getRandomSensorData());
        temp.push_back(generatedData->getTimestamp());
        firstSensor.push_back(temp);
        counter++;
    }

    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    cout << "Time difference = " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << " [ms]" << endl;

    return 0;
}









