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
        if(csvHandler->getNumberOfRowsOfCSVFile() == CSV_THRESHOLD){
            //pushing to database, when number of data in csv are over threshold
            int checkPushData = dbHandler->pushDataFromCSVToDatabase();
            if(checkPushData == -1){
                sleep_for(sleep);

            }
            else if(checkPushData == -2){
                //TODO: average data in CSV
                csvHandler->cleanCSV();

            }
            else if(checkPushData == 0){
                csvHandler->cleanCSV();

            }
        }else{
            if(first_sensor.size() == STACK_THRESHOLD){
                int checkUpdateCSV = csvHandler->updateDataToCSVFile(first_sensor);

                if(checkUpdateCSV == -1){
                    makeAverageOfSensorsData(first_sensor);
                }else{
                    first_sensor.clear();
                }
            }
            if(second_sensor.size() == STACK_THRESHOLD){
                int checkUpdateCSV = csvHandler->updateDataToCSVFile(second_sensor);

                if( checkUpdateCSV == -1){
                    makeAverageOfSensorsData(second_sensor);
                }else{
                    second_sensor.clear();
                }
            }
            // filling stacks -- maybe add sleep function.
            if (counter % 10 == 0) {
                sensorDataType temp(generatedData->getRandomSensorData(),generatedData->getTimestamp(),1);
                second_sensor.emplace_back(temp);
            }
            sensorDataType temp(generatedData->getRandomSensorData(),generatedData->getTimestamp(),1);
            first_sensor.emplace_back(temp);
            counter++;
            if(counter == 1000){
                break;
            }
        }
    }
}
vector<sensorDataType> app_handler::getDataFromSensorToMakeAverage(vector<sensorDataType> sensor) {
    auto *generatedData = new generated_data(sensor.size());
    vector<sensorDataType> temp;
    for(int i = 0; i < 50; i++){
        int sensorDataPositionInStack = generatedData->getRandomNum();
        if(sensor.at(sensorDataPositionInStack).dataFlag == 2) {
            i--;
            continue;
        }
        temp.emplace_back(sensor.at(sensorDataPositionInStack));
    }
    return temp;
}

vector<sensorDataType> app_handler::makeAverageOfSensorsData(const vector<sensorDataType>& dataToMakeAverage) {
    vector<sensorDataType> dataToAverage = getDataFromSensorToMakeAverage(dataToMakeAverage);
    vector<sensorDataType> result = getAveragedDataFromStack(dataToMakeAverage);
    float randomData = 0;
    unsigned long long int timeStamp = 0;
    for(auto & data : dataToAverage){
        randomData += data.sensorData;
        timeStamp += data.timeStamp;
    }
    float averagedData = randomData / dataToAverage.size();
    auto averagedTimeStamp = (unsigned long long int)(timeStamp / dataToAverage.size());

    result.emplace_back(sensorDataType(averagedData,averagedTimeStamp,2));
    return result;
}

vector<sensorDataType> app_handler::getAveragedDataFromStack(const vector<sensorDataType>& data) {
    vector<sensorDataType> result;

    for(auto &item : data){
        if(item.dataFlag == 2){
            result.emplace_back(item);
        }
    }
    return result;
}






