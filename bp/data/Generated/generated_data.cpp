//
// Created by sounteg on 12. 5. 2020.
//

#include "generated_data.h"
#include <iostream>
#include <random>

using namespace std;

generated_data::generated_data() {}

generated_data::~generated_data() {}

int generated_data::getRandomSensorData() {
    random_device randomDevice;
    mt19937 mt(randomDevice());
    uniform_int_distribution<int> dist(1 ,100);

    return dist(mt);
}

time_t generated_data::getTimestamp() {
    time_t result = time(nullptr);
    asctime(localtime(&result));
    return result;
}


