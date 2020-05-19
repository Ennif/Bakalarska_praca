//
// Created by sounteg on 19. 5. 2020.
//

#include "configuration.h"

configuration::configuration() = default;

configuration::~configuration() = default;

const string &configuration::getConnectionString() const {
    return connectionString;
}

void configuration::setConnectionString(const string &connectionString) {
    configuration::connectionString = connectionString;
}

int configuration::getMaxRangeForGeneratedData() const {
    return max_range_for_generated_data;
}

void configuration::setMaxRangeForGeneratedData(int maxRangeForGeneratedData) {
    max_range_for_generated_data = maxRangeForGeneratedData;
}
