//
// Created by sounteg on 6. 5. 2020.
//

#include "db_connection.h"
#include <iostream>
#include <string>
#include <pqxx/pqxx>
#include <fstream>
#include "../Database/nlohmann/json.hpp"
#include "../data/pathToConfig.h"

using json = nlohmann::json;

db_connection::db_connection(const string &databaseName, const string &userName, const string &password,
                             const string &hostAddress, const string &port) : databaseName(databaseName),
                                                                          userName(userName), password(password),
                                                                          hostAddress(hostAddress), port(port) {}

const string &db_connection::getDatabaseName() const {
    return databaseName;
}

void db_connection::setDatabaseName(const string &databaseName) {
    db_connection::databaseName = databaseName;
}

const string &db_connection::getUserName() const {
    return userName;
}

void db_connection::setUserName(const string &userName) {
    db_connection::userName = userName;
}

const string &db_connection::getPassword() const {
    return password;
}

void db_connection::setPassword(const string &password) {
    db_connection::password = password;
}

const string &db_connection::getHostAddress() const {
    return hostAddress;
}

void db_connection::setHostAddress(const string &hostAddress) {
    db_connection::hostAddress = hostAddress;
}

const string &db_connection::getPort() const {
    return port;
}

void db_connection::setPort(const string &port) {
    db_connection::port = port;
}

string db_connection::getConnectionString() {
    string connectionString = "dbname = " + getDatabaseName() + " user = " + getUserName()
            + " password = " + getPassword() + " hostaddr = " + getHostAddress() + " port = " + getPort() + "";
    return connectionString;
};

void db_connection::connectToDatabase() {
    this->initializeConnectionFromConfig();
    try {
        this->Conn = new pqxx::connection(getConnectionString());
        if (this->Conn->is_open()){
            cout << "Database opened successfully " << this->Conn->dbname();
        } else {
            cout << "Can't open database";
        }
    } catch (const std::exception &e) {
        cerr << e.what() << std::endl;
    }
}

void db_connection::initializeConnectionFromConfig() {
    ifstream inFile(pathToConfig);
    json jsonFile = json::parse(inFile);

    this->setDatabaseName(jsonFile["databaseName"]);
    this->setUserName(jsonFile["userName"]);
    this->setHostAddress(jsonFile["hostAddress"]);
    this->setPassword(jsonFile["password"]);
    this->setPort(jsonFile["port"]);
}

void db_connection::closeDbConnection() {
    this->Conn->close();
}

db_connection::~db_connection() {
    delete this->Conn;
    cout << "\nDeleted Conn";
}

pqxx::connection *db_connection::getConn() const {
    return Conn;
}
