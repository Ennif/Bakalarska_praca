//
// Created by sounteg on 18. 5. 2020.
//

#ifndef BP_APP_HANDLER_H
#define BP_APP_HANDLER_H
#include "app_handler.h"
#include <vector>
#include <iostream>
#include "../Database/db_handler.h"
#include "../CSV/csv_handler.h"
#include "../data/Generated/generated_data.h"
#include "../data/vector_type.h"
#include "../data/pathToConfig.h"
#include "../Database/nlohmann/json.hpp"
#include "../data/configuration.h"
#include <chrono>
#include <thread>
#include <math.h>

using namespace std;
using namespace chrono;
using namespace this_thread;

class app_handler {
private:
    unsigned int CSV_THRESHOLD;
    int STACK_THRESHOLD;
    int counter = 0;
    vector<sensorDataType> first_sensor;
    vector<sensorDataType> second_sensor;
    int timeForSleep;

    static vector<sensorDataType> getDataToMakeAverage(vector<sensorDataType>);

    configuration initializeVariablesFromConfig();

    void createCSVFile(csv_handler&);

    void pushingToDatabaseStage(db_handler&,csv_handler&, milliseconds);

    void pushingToStackStage(csv_handler&,vector<sensorDataType>&);

public:
    int getTimeForSleep() const;

    void setTimeForSleep(int timeForSleep);

    int getCounter() const;

    void setCounter(int counter);

    const vector<sensorDataType> &getFirstSensor() const;

    void setFirstSensor(const vector<sensorDataType> &firstSensor);

    const vector<sensorDataType> &getSecondSensor() const;

    void setSecondSensor(const vector<sensorDataType> &secondSensor);

    app_handler();

    unsigned int getCsvThreshold() const;

    void setCsvThreshold(unsigned int csvThreshold);

    int getStackThreshold() const;

    void setStackThreshold(int stackThreshold);

    virtual ~app_handler();

    void mainProgram();

    static vector<sensorDataType> makeAverageOfData(const vector<sensorDataType>&);

    static vector<sensorDataType> getDataByFlag(const vector<sensorDataType>&, int data_flag);

};


#endif //BP_APP_HANDLER_H
