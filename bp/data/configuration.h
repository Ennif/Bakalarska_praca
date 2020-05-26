//
// Created by Jakub Trstensky on 19. 5. 2020.
//

#ifndef BP_CONFIGURATION_H
#define BP_CONFIGURATION_H
#include <string>

using namespace std;

class configuration {
private:
    string connectionString;
    int max_range_for_generated_data;
public:
    configuration();

    virtual ~configuration();

    const string &getConnectionString() const;

    void setConnectionString(const string &connectionString);

    int getMaxRangeForGeneratedData() const;

    void setMaxRangeForGeneratedData(int maxRangeForGeneratedData);

};


#endif //BP_CONFIGURATION_H
