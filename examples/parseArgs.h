#pragma once

#include <iostream>

void printHelp()
{
}

bool parseArgs(int argc, char* argv[], std::string &connectionString, Sql::DbType &dbType)
{
    if (argc != 3)
    {
        printHelp();
        return false;
    }

    int _dbType = std::stoi(argv[1]);
    if (_dbType == Sql::DbType::Postgres || _dbType == Sql::DbType::Sqlite)
    {
        dbType = (Sql::DbType)_dbType;
        connectionString = argv[2];
        //std::string connectionString = "user=" + userId + " password=" + password + " host=" + host + " port=" + port + " dbname=" + database;
        return true;
    }
    
    printHelp();
    return false;
}