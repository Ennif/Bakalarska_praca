//
// Created by sounteg on 18. 5. 2020.
//

#include <fstream>
#include "app_handler.h"
#include "../data/configuration.h"
#include "../data/pathToConfig.h"

using namespace std;
using namespace chrono;
using namespace this_thread;
using json = nlohmann::json;

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

int app_handler::getTimeForSleep() const {
    return timeForSleep;
}

void app_handler::setTimeForSleep(int timeForSleep) {
    app_handler::timeForSleep = timeForSleep;
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

vector<sensorDataType> app_handler::getDataToMakeAverage(vector<sensorDataType> sensor) {
    vector<sensorDataType> notAveragedData = getDataByFlag(sensor,1);
    vector<sensorDataType> temp;

    int iterator = 50;
    if(notAveragedData.size() < 50)
        iterator = notAveragedData.size();

    for(int i = 0; i < iterator; i++){
        temp.emplace_back(notAveragedData.at(i));
    }
    return temp;
}

vector<sensorDataType> app_handler::makeAverageOfData(const vector<sensorDataType>& dataToMakeAverage) {
    vector<sensorDataType> dataToAverage = getDataToMakeAverage(dataToMakeAverage);
    vector<sensorDataType> result = getDataByFlag(dataToMakeAverage,2);
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

vector<sensorDataType> app_handler::getDataByFlag(const vector<sensorDataType>& data, int data_flag) {
    vector<sensorDataType> result;

    for(auto &item : data){
        if(item.dataFlag == data_flag){
            result.emplace_back(item);
        }
    }
    return result;
}

configuration app_handler::initializeVariablesFromConfig() {
    auto *conf = new configuration();

    ifstream inFile(pathToConfig);
    json jsonFile = json::parse(inFile);

    this->setCsvThreshold(jsonFile["csv_threshold"]);
    this->setStackThreshold(jsonFile["stack_threshold"]);
    this->setTimeForSleep(jsonFile["sleep_time"]);
    conf->setMaxRangeForGeneratedData(jsonFile["max_range_for_generated_data"]);
    conf->setConnectionString(jsonFile["connection_string"]);

    return *conf;
}

void app_handler::createCSVFile(csv_handler &csvHandler){
    for(int i = 0 ;i < 10;i++){
        if(csvHandler.createCSVFile() == -1){
            cerr << "File cannot be created! Trying to create again\n";
            continue;
        }else{
            break;
        }
    }
    csvHandler.cleanCSV();
}

void app_handler::pushingToDatabaseStage(db_handler &dbHandler, csv_handler &csvHandler, milliseconds sleep) {
    int checkPushData = dbHandler.pushDataFromCSVToDatabase();

    if(checkPushData == -1){
        sleep_for(sleep);

    }else if(checkPushData == -2){

        if(csvHandler.areAllRowsWithAverageFlag()){
            csvHandler.cleanCSV();
        }else{
            csvHandler.toAverageCSV();
        }
    }
    else if(checkPushData == 0){
        csvHandler.cleanCSV();
    }
}

void app_handler::pushingToStackStage(csv_handler &csvHandler, vector<sensorDataType> &stackData) {
    if(stackData.size() == STACK_THRESHOLD){

        int checkUpdateCSV = csvHandler.updateDataToCSVFile(stackData);

        if(checkUpdateCSV == -1){
            if(getDataByFlag(stackData,2).size() == STACK_THRESHOLD){ //extrem case
                stackData.clear();
            }else{
                stackData = makeAverageOfData(stackData);
            }
        }else{
            stackData.clear();
        }
    }
}

void app_handler::mainProgram() {
    configuration conf = initializeVariablesFromConfig();
    auto *dbHandler = new db_handler(conf.getConnectionString());
    auto *csvHandler = new csv_handler();
    auto *generatedData = new generated_data(conf.getMaxRangeForGeneratedData());

    milliseconds sleep(timeForSleep);

    createCSVFile(*csvHandler);

    /*chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    cout << "Time difference = " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << " [ms]" << endl;*/

    //main program
    while(true) {
        if(csvHandler->getNumberOfRowsOfCSVFile() >= CSV_THRESHOLD){
            pushingToDatabaseStage(*dbHandler,*csvHandler,sleep);
        }else{
            counter++;
            if(counter == 100000){
                break;
            }
            pushingToStackStage(*csvHandler,first_sensor);
            pushingToStackStage(*csvHandler,second_sensor);

            // filling stacks -- maybe add sleep function.
            if (counter % 100 == 0) {
                sensorDataType temp(generatedData->getRandomSensorData(),generatedData->getTimestamp(),1);
                second_sensor.emplace_back(temp);
            }
            sensorDataType temp(generatedData->getRandomSensorData(),generatedData->getTimestamp(),1);
            first_sensor.emplace_back(temp);
        }
    }
}