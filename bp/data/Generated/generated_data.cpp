//
// Created by Jakub Trstensky on 12. 5. 2020.
//

#include "generated_data.h"
#include <cmath>
#include <random>

using namespace std;

generated_data::generated_data()= default;

generated_data::generated_data(int maxRange) : max_range(maxRange) {}

generated_data::~generated_data() = default;

int generated_data::getMaxRange() const {
    return max_range;
}

void generated_data::setMaxRange(int maxRange) {
    max_range = maxRange;
}

float generated_data::getRandomSensorData() {
    random_device randomDevice;
    mt19937 mt(randomDevice());
    uniform_real_distribution<float> distribution(0.0,(float)max_range);
    return floorf(distribution(mt) *100) / 100;
}

time_t generated_data::getTimestamp() {
    time_t result = time(nullptr);
    asctime(localtime(&result));
    return result;
}

int generated_data::getRandomNum() {
    return (int)getRandomSensorData();
}








