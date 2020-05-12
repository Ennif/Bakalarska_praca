//
// Created by sounteg on 12. 5. 2020.
//

#include "generated_data.h"
#include <utility>
#include <iostream>
#include <random>

using namespace std;

generated_data::generated_data(int countOfSensors) : countOfSensors(countOfSensors) {}

generated_data::~generated_data() {}

generated_data::generated_data() {}

int generated_data::getCountOfSensors() const {
    return countOfSensors;
}

void generated_data::setCountOfSensors(int countOfSensors) {
    generated_data::countOfSensors = countOfSensors;
}

pair<int,float> generated_data::generateSensorData() {
    pair<int,float> sensorData;

    sensorData.first = intRandomGeneratorForSensors();
    sensorData.second = floatRandomGeneratorForValues();

    return sensorData;
}

float generated_data::floatRandomGeneratorForValues() {
    random_device randomDevice;
    mt19937 mt(randomDevice());
    uniform_real_distribution<float> dist(0.0, 100.0);

    return dist(mt);
}

int generated_data::intRandomGeneratorForSensors() {
    random_device randomDevice;
    mt19937 mt(randomDevice());
    uniform_int_distribution<int> dist(1,7);

    return dist(mt);
}

