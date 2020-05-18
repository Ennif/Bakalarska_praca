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
#include <chrono>
#include <thread>


using namespace std;
using namespace chrono;
using namespace this_thread;


class app_handler {
private:
    unsigned int CSV_THRESHOLD = 200000;
    int STACK_THRESHOLD = 50;
    int counter = 0;
    vector<sensorDataType> first_sensor;
    vector<sensorDataType> second_sensor;
    int timeForSleep = 2000; //milliseconds

    static vector<sensorDataType> getAveragedDataFromStack(const vector<sensorDataType>&);

    static vector<sensorDataType> getDataFromSensorToMakeAverage(vector<sensorDataType>);

    static vector<sensorDataType> makeAverageOfSensorsData(const vector<sensorDataType>&);

public:

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

    int mainProgram();

};


#endif //BP_APP_HANDLER_H