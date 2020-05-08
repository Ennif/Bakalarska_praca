#include <iostream>
#include "Database/db_connection.h"


using namespace pqxx;
using namespace std;

int main() {

    db_connection *dbConnection = new db_connection();
    dbConnection->connectToDatabase();
    delete dbConnection;
    }


