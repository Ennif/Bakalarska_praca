//
// Created by sounteg on 18. 5. 2020.
//

#ifndef BP_VECTOR_TYPE_H
#define BP_VECTOR_TYPE_H

struct sensorDataType{
    float sensorData;
    time_t timeStamp;
    int dataFlag;
    sensorDataType(const float sensor_data, time_t time_stamp, const int data_flag)
        : sensorData(sensor_data), timeStamp(time_stamp), dataFlag(data_flag){}
};

#endif //BP_VECTOR_TYPE_H