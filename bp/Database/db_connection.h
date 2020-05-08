//
// Created by sounteg on 6. 5. 2020.
//

#ifndef BP_DB_CONNECTION_H
#define BP_DB_CONNECTION_H
#include <string>
#include <pqxx/connection.hxx>

using namespace std;

class db_connection {

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

    void initializeConnectionFromConfig();
public:
    db_connection(const string &databaseName, const string &userName,
                  const string &password, const string &hostAddress,
                  const string &port);
    db_connection(){}

    virtual ~db_connection();

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

    void connectToDatabase();

    void closeDbConnection();

};

#endif //BP_DB_CONNECTION_H
