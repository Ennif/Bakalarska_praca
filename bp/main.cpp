#include "Database/database_local/db_localDatabase.h"

#include <iostream>

int selectSenzorData();

using namespace std;

int main() {

   /* db_connection *dbConnection = new db_connection();
    dbConnection->connectToDatabase();
    delete dbConnection;*/

   db_localDatabase *localDatabaseHandler = new db_localDatabase();
   //localDatabaseHandler->insertSenzorsData(); //  pair<int,float>
   localDatabaseHandler->selectSenzorData();
   localDatabaseHandler->deleteSenzorData();
   delete localDatabaseHandler;

}





