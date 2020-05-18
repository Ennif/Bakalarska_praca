//
// Created by sounteg on 6. 5. 2020.
//

#ifndef BP_DB_HANDLER_H
#define BP_DB_HANDLER_H
#include <string>
#include <pqxx/connection.hxx>

using namespace std;

class db_handler {

private:
    pqxx::connection *Conn;
public:
    pqxx::connection *getConn() const;

private:
    string databaseName;
    string userName;
    string password;
    string hostAddress;
    string port;
    string table_name = "data_from_sensors";
    vector<string> column_names = {"data","timestamp"};

    void initializeConnectionFromConfig();
public:
    db_handler(const string &databaseName, const string &userName,
               const string &password, const string &hostAddress,
               const string &port);

    const string &getTableName() const;

    void setTableName(const string &tableName);

    const vector<string> &getColumnNames() const;

    void setColumnNames(const vector<string> &columnNames);

    db_handler(){}

    virtual ~db_handler();

    const string &getDatabaseName() const;

    void setDatabaseName(const string &databaseName);

    const string &getUserName() const;

    void setUserName(const string &userName);

    const string &getPassword() const;

    void setPassword(const string &password);

    const string &getHostAddress() const;

    void setHostAddress(const string &hostAddress);

    const string &getPort() const;

    void setPort(const string &port);

    string getConnectionString();

    int pushDataFromCSVToDatabase();

    void connectToDatabase();

    void closeDbConnection();

};

#endif //BP_DB_HANDLER_H
