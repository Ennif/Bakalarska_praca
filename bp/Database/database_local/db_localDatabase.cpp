//
// Created by sounteg on 11. 5. 2020.
//

#include "db_localDatabase.h"
#include "sqlite_local_path.h"

#include <iostream>

using namespace std;

db_localDatabase::~db_localDatabase() {
    this->setLocalDatabasePath(sqliteLocalPath);
}
db_localDatabase::db_localDatabase() {}

void db_localDatabase::setLocalDatabasePath(const char *localDatabasePath) {
    db_localDatabase::localDatabasePath = localDatabasePath;
}

void db_localDatabase::setDataBase(sqlite3 *dataBase) {
    db_localDatabase::dataBase = dataBase;
}

const char *db_localDatabase::getLocalDatabasePath() const {
    return localDatabasePath;
}

void db_localDatabase::initializeLocalDatabasePath() {
    if(localDatabasePath == nullptr){
        this->setLocalDatabasePath(sqliteLocalPath);
    }
}

sqlite3 *db_localDatabase::getDataBase() const {
    return dataBase;
}
int db_localDatabase::selectCallback(void *NotUsed, int argc, char **argv, char **azColName) {
    for(int i = 0; i < argc; i++){
        cout << azColName[i] << ": " << argv[i] << endl;
    }
    cout << endl;
    return 0;
}

int db_localDatabase::insertSenzorsData(pair<int,float> senzorValue) {
    this->initializeLocalDatabasePath();  // if path to DB doesn't exists, it will be initialized

    char* messageError;
    sqlite3* database = getDataBase();
    int exit = sqlite3_open(localDatabasePath,&database);

    int id_senzor = senzorValue.first;
    float measuredValue = senzorValue.second;
    int id_meranie = 1;

    string sqlInsertData("INSERT INTO hodnota (value_value, id_senzor, id_meranie) "
              "VALUES ("+ to_string(measuredValue) + "," + to_string(id_senzor) + "," + to_string(id_meranie) + ");");
    exit = sqlite3_exec(database,sqlInsertData.c_str(),NULL,0,&messageError);

    if(exit != SQLITE_OK){
        cerr << "Error Insert Data" << endl;
        cerr << messageError;
        sqlite3_free(messageError);
    } else
        cout << "Record created Successfully" << endl;
    return 0;
}

int db_localDatabase::selectSenzorData() {
    this->initializeLocalDatabasePath();

    sqlite3* database = getDataBase();
    int exit = sqlite3_open(localDatabasePath,&database);

    string sqlSelectDataFromSenzors = "SELECT * FROM hodnota;";
    sqlite3_exec(database,sqlSelectDataFromSenzors.c_str(),selectCallback,NULL,NULL);

    return 0;
}

int db_localDatabase::deleteSenzorData() {
    this->initializeLocalDatabasePath();

    char* messageError;
    sqlite3* database = getDataBase();
    int exit = sqlite3_open(localDatabasePath,&database);

    string sql = "DELETE FROM hodnota;";
    sqlite3_exec(database,sql.c_str(),NULL,0,&messageError);

    if(exit != SQLITE_OK){
        cerr << "Error Delete Data" << endl;
        cerr << messageError;
        sqlite3_free(messageError);
    } else
        cout << "Records deleted Successfully" << endl;
    return 0;


}











