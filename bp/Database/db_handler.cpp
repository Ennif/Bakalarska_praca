//
// Created by sounteg on 6. 5. 2020.
//

#include "db_handler.h"
#include <iostream>
#include <string>
#include <pqxx/pqxx>
#include <fstream>
#include "../Database/nlohmann/json.hpp"
#include "../data/pathToConfig.h"
#include "../CSV/csv_handler.h"

using json = nlohmann::json;
using namespace pqxx;

db_handler::db_handler(const string &databaseName, const string &userName, const string &password,
                       const string &hostAddress, const string &port) : databaseName(databaseName),
                                                                          userName(userName), password(password),
                                                                          hostAddress(hostAddress), port(port) {}

const string &db_handler::getDatabaseName() const {
    return databaseName;
}

void db_handler::setDatabaseName(const string &databaseName) {
    db_handler::databaseName = databaseName;
}

const string &db_handler::getUserName() const {
    return userName;
}

void db_handler::setUserName(const string &userName) {
    db_handler::userName = userName;
}

const string &db_handler::getPassword() const {
    return password;
}

void db_handler::setPassword(const string &password) {
    db_handler::password = password;
}

const string &db_handler::getHostAddress() const {
    return hostAddress;
}

void db_handler::setHostAddress(const string &hostAddress) {
    db_handler::hostAddress = hostAddress;
}

const string &db_handler::getPort() const {
    return port;
}

void db_handler::setPort(const string &port) {
    db_handler::port = port;
}

string db_handler::getConnectionString() {
    string connectionString = "dbname = " + getDatabaseName() + " user = " + getUserName()
            + " password = " + getPassword() + " hostaddr = " + getHostAddress() + " port = " + getPort();
    return connectionString;
};

void db_handler::connectToDatabase() {
    this->initializeConnectionFromConfig();

    this->Conn = new pqxx::connection(getConnectionString());
    if (this->Conn->is_open()){
        cout << "Database opened successfully " << this->Conn->dbname();
    } else {
        cout << "Can't open database";
    }
}

void db_handler::initializeConnectionFromConfig() {
    ifstream inFile(pathToConfig);
    json jsonFile = json::parse(inFile);

    this->setDatabaseName(jsonFile["databaseName"]);
    this->setUserName(jsonFile["userName"]);
    this->setHostAddress(jsonFile["hostAddress"]);
    this->setPassword(jsonFile["password"]);
    this->setPort(jsonFile["port"]);
}

void db_handler::closeDbConnection() {
    this->Conn->close();
}

db_handler::~db_handler() {
    delete this->Conn;
    cout << "\nDeleted Conn";
}

pqxx::connection *db_handler::getConn() const {
    return Conn;
}

const string &db_handler::getTableName() const {
    return table_name;
}

void db_handler::setTableName(const string &tableName) {
    table_name = tableName;
}

const vector<string> &db_handler::getColumnNames() const {
    return column_names;
}

void db_handler::setColumnNames(const vector<string> &columnNames) {
    column_names = columnNames;
}

int db_handler::pushDataFromCSVToDatabase() {
    auto *csvHandler = new csv_handler();
    string csv_filename = csvHandler->getCsvFilename();
    try{
        connectToDatabase();
        work transaction(*this->getConn());

        ifstream csv_file(csv_filename);
        if (!csv_file.is_open()){
            cerr << "File cannot be opened!\n";
            return -1;
        }
        string line;
        stream_to stream(transaction,getTableName(),getColumnNames());

        while(getline(csv_file,line)){
            vector<string> values = csvHandler->splitCSVline(line);

            string value = values[0];
            string timestamp = values[1];

            stream << make_tuple(value,timestamp);
        }
        stream.complete();
        transaction.commit();

        csv_file.close();
        closeDbConnection();
    }catch(const exception &e){
        cerr << "PQXX exception: " << e.what() << endl;
        return -2;
    }
    return 0;
}
