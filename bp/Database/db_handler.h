//
// Created by Jakub Trstensky on 6. 5. 2020.
//

#ifndef BP_DB_HANDLER_H
#define BP_DB_HANDLER_H
#include <string>
#include <pqxx/connection.hxx>

using namespace std;

class db_handler {

private:
    pqxx::connection *Conn;
    string connection_string;
    string table_name = "data_from_sensors";
    vector<string> column_names = {"data","timestamp"};

public:
    explicit db_handler(string connectionString);

    const string &getConnectionString() const;

    void setConnectionString(const string &connectionString);

    pqxx::connection *getConn() const;

    const string &getTableName() const;

    void setTableName(const string &tableName);

    const vector<string> &getColumnNames() const;

    void setColumnNames(const vector<string> &columnNames);

    db_handler()= default;

    virtual ~db_handler();

    int pushDataFromCSVToDatabase();

    void connectToDatabase();

    void closeDbConnection();

};

#endif //BP_DB_HANDLER_H
