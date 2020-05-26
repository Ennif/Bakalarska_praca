//
// Created by Jakub Trstensky on 11. 5. 2020.
//

#ifndef BP_DB_LOCALDATABASE_H
#define BP_DB_LOCALDATABASE_H

#include <string>
#include <sqlite3.h>

using namespace std;


class db_localDatabase {
private:
    const char* localDatabasePath = nullptr;
    sqlite3* dataBase;

    void initializeLocalDatabasePath();
public:
    sqlite3 *getDataBase() const;

    const char *getLocalDatabasePath() const;

    virtual ~db_localDatabase();

    db_localDatabase();

    void setLocalDatabasePath(const char *localDatabasePath);

    int insertSensorsData(pair<int,float> sensorValue);

    int selectSensorData();

    static int selectCallback(void *NotUsed, int argc, char** argv, char** azColName);

    int deleteSensorData();

};


#endif //BP_DB_LOCALDATABASE_H
