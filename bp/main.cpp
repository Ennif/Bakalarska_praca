
#include <iostream>
#include <vector>
#include <string>
#include "CSV/csv_handler.h"
#include "data/Generated/generated_data.h"
#include <chrono>
#include <thread>
#include "Database/db_handler.h"

using namespace std;
using namespace chrono;
using namespace this_thread;
int main() {

    const int CSV_THRESHOLD = 200000;
    const int STACK_THRESHOLD = 10000;

    vector<vector<int>> firstSensor;
    vector<vector<int>> secondSensor;

    auto *generatedData = new generated_data();
    auto *dbHandler = new db_handler();
    auto *csvHandler = new csv_handler();

    int counter = 0;
    //default time of sleep
    milliseconds timeForSleep(2000);

    //till file will be created
    while(1){
        if(csvHandler->createCSVFile() == -1){
            cout << "Trying to create file again\n";
            continue;
        }else{
            cout << "File was created successfully!\n";
            break;
        }
    }

    /*chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    cout << "Time difference = " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << " [ms]" << endl;*/

    while(1) {
        if(csvHandler->getNumberOfRowsOfCSVFile() == CSV_THRESHOLD){
            //pushing to database when number of data in csv are over threshold
            if(dbHandler->pushDataFromCSVToDatabase() == -1){
                sleep_for(timeForSleep);
                continue;
            }else if(dbHandler->pushDataFromCSVToDatabase() == -2){
                csvHandler->cleanCSV();
                continue;
            }else if(dbHandler->pushDataFromCSVToDatabase() == 0){
                csvHandler->cleanCSV();
                continue;
            }
        }else{
            if(firstSensor.size() == STACK_THRESHOLD){
                if(csvHandler->updateDataToCSVFile(firstSensor) == -1){
                    sleep_for(timeForSleep);
                    continue;
                }
            }
            if(secondSensor.size() == STACK_THRESHOLD){
                if(csvHandler->updateDataToCSVFile(secondSensor) == -1){
                    sleep_for(timeForSleep);
                    continue;
                }
            }
            // filling stacks -- maybe add sleep function.
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
            if(counter == 1000000){
                break;
            }
        }
    }
    return 0;
}









