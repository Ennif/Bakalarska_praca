//
// Created by sounteg on 12. 5. 2020.
//

#ifndef BP_GENERATED_DATA_H
#define BP_GENERATED_DATA_H
#include <utility>
#include <ctime>

using namespace std;

class generated_data {
private:
    int max_range;
public:
     generated_data();

    explicit generated_data(int maxRange);

    virtual ~generated_data();

    float getRandomSensorData();

    static time_t getTimestamp();

    int getMaxRange() const;

    void setMaxRange(int maxRange);

    int getRandomNum();

};

#endif //BP_GENERATED_DATA_H
