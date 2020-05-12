//
// Created by sounteg on 12. 5. 2020.
//

#ifndef BP_GENERATED_DATA_H
#define BP_GENERATED_DATA_H
#include <utility>

using namespace std;

class generated_data {
private:
    int countOfSensors;

    float floatRandomGeneratorForValues();

    int intRandomGeneratorForSensors();

public:
    generated_data(int countOfSensors);

    generated_data();

    virtual ~generated_data();

    int getCountOfSensors() const;

    void setCountOfSensors(int countOfSensors);

    pair<int,float> generateSensorData();

};


#endif //BP_GENERATED_DATA_H
