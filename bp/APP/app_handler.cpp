//
// Created by sounteg on 18. 5. 2020.
//

#include "app_handler.h"

using namespace std;
using namespace chrono;
using namespace this_thread;

app_handler::app_handler() = default;

app_handler::~app_handler() = default;

const vector<sensorDataType> &app_handler::getFirstSensor() const {
    return first_sensor;
}

void app_handler::setFirstSensor(const vector<sensorDataType> &firstSensor) {
    first_sensor = firstSensor;
}

const vector<sensorDataType> &app_handler::getSecondSensor() const {
    return second_sensor;
}

void app_handler::setSecondSensor(const vector<sensorDataType> &secondSensor) {
    second_sensor = secondSensor;
}

unsigned int app_handler::getCsvThreshold() const {
    return CSV_THRESHOLD;
}

void app_handler::setCsvThreshold(unsigned int csvThreshold) {
    CSV_THRESHOLD = csvThreshold;
}

int app_handler::getStackThreshold() const {
    return STACK_THRESHOLD;
}

void app_handler::setStackThreshold(int stackThreshold) {
    STACK_THRESHOLD = stackThreshold;
}

int app_handler::getCounter() const {
    return counter;
}

void app_handler::setCounter(int counter) {
    app_handler::counter = counter;
}

int app_handler::mainProgram() {
    auto *dbHandler = new db_handler();
    auto *csvHandler = new csv_handler();
    auto *generatedData = new generated_data(100);
    milliseconds sleep(2000);

    //till file will be created
    while(1){
        if(csvHandler->createCSVFile() == -1){
            cerr << "File cannot be created! Trying to create again\n";
            continue;
        }else{
            break;
        }
    }
    csvHandler->cleanCSV();
    //main program
    while(true) {
        if(csvHandler->getNumberOfRowsOfCSVFile() >= CSV_THRESHOLD){
            //pushing to database, when number of data in csv are over threshold
            //chrono::steady_clock::time_point begin = chrono::steady_clock::now();
            int checkPushData = dbHandler->pushDataFromCSVToDatabase();
            /*chrono::steady_clock::time_point end = chrono::steady_clock::now();
            cout << "Time difference = " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << " [ms]" << endl;
            cout << "Number of rows before clean: " << csvHandler->getNumberOfRowsOfCSVFile() << endl;*/

            if(checkPushData == -1){
                sleep_for(sleep);
            }
            else if(checkPushData == -2){
                //TODO: average data in CSV
                //Increasing CSV_THRESHOLD till date will be pushed
                csvHandler->cleanCSV();
            }
            else if(checkPushData == 0){
                csvHandler->cleanCSV();
            }
        }else{
            counter++;
            if(counter == 1000000){
                break;
            }


            // filling stacks -- maybe add sleep function.
            if (counter % 1000 == 0) {
                sensorDataType temp(generatedData->getRandomSensorData(),generatedData->getTimestamp(),1);
                second_sensor.emplace_back(temp);
            }
            sensorDataType temp(generatedData->getRandomSensorData(),generatedData->getTimestamp(),1);
            first_sensor.emplace_back(temp);

            if(first_sensor.size() == STACK_THRESHOLD){
                cout << counter << endl;
                int checkUpdateCSV = csvHandler->updateDataToCSVFile(first_sensor);

                if(checkUpdateCSV == -1){
                    if(getDataFromStackByFlag(first_sensor,2).size() == STACK_THRESHOLD){ //extrem case
                        first_sensor.clear();
                    }else{
                        first_sensor = makeAverageOfSensorsData(first_sensor);
                    }
                }else{
                    first_sensor.clear();

                }
            }
            if(second_sensor.size() == STACK_THRESHOLD){
                int checkUpdateCSV = csvHandler->updateDataToCSVFile(second_sensor);

                if( checkUpdateCSV == -1){
                    if(getDataFromStackByFlag(second_sensor,2).size() == STACK_THRESHOLD) { //extrem case
                        second_sensor.clear();
                    }else{
                        second_sensor = makeAverageOfSensorsData(second_sensor);
                    }
                }else{
                    second_sensor.clear();
                }
            }

        }
    }
}
vector<sensorDataType> app_handler::getDataFromSensorToMakeAverage(vector<sensorDataType> sensor) {
    vector<sensorDataType> notAveragedData = getDataFromStackByFlag(sensor,1);
    vector<sensorDataType> temp;

    int iterator = 50;
    if(notAveragedData.size() < 50)
        iterator = notAveragedData.size();

    for(int i = 0; i < iterator; i++){
        temp.emplace_back(notAveragedData.at(i));
    }
    return temp;
}

vector<sensorDataType> app_handler::makeAverageOfSensorsData(const vector<sensorDataType>& dataToMakeAverage) {
    vector<sensorDataType> dataToAverage = getDataFromSensorToMakeAverage(dataToMakeAverage);
    vector<sensorDataType> result = getDataFromStackByFlag(dataToMakeAverage,2);
    float randomData = 0;
    unsigned long long int timeStamp = 0;
    for(auto & data : dataToAverage){
        randomData += data.sensorData;
        timeStamp += data.timeStamp;
    }
    float averagedData = floorf((randomData / dataToAverage.size())*100)/100;
    auto averagedTimeStamp = (unsigned long long int)(timeStamp / dataToAverage.size());

    result.emplace_back(sensorDataType(averagedData,averagedTimeStamp,2));
    return result;
}

vector<sensorDataType> app_handler::getDataFromStackByFlag(const vector<sensorDataType>& data, int data_flag) {
    vector<sensorDataType> result;

    for(auto &item : data){
        if(item.dataFlag == data_flag){
            result.emplace_back(item);
        }
    }
    return result;
}








