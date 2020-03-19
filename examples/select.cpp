#include "../include/database.h"
#include "parseArgs.h"

int main(int argc, char* argv[])
{
    std::string connectionString;
    Sql::DbType dbType;
    if (!parseArgs(argc, argv, connectionString, dbType))
        return -1;
     
    try
    {
        auto connection = Sql::createConnection(dbType, connectionString);
        auto selector = connection->createSelector();

        selector->prepare("SELECT id, name, strvalue from countries WHERE numcode = :numcode OR iso3 = :iso3");
        selector->bind("numcode", 16);
        selector->bind("iso3", "ATG");
        selector->select([](const Sql::DbRow& dbRow)
        {
            int64_t id;
            std::string name, strvalue;
            dbRow.value(0, id);
            dbRow.value(1, name);
            dbRow.value(2, strvalue);
            std::cout << id << name << std::flush;
        });

        auto singleSelector = connection->createSingleSelector();
        singleSelector->prepare("SELECT id, name, strvalue from countries WHERE id = :id");
        singleSelector->bind("id", (int64_t)10);
        auto dbRow = singleSelector->select();
        int64_t id;
        std::string name, strvalue;
        dbRow->value(0, id);
        dbRow->value(1, name);
        dbRow->value(2, strvalue);
    }
    catch (const std::exception & ex)
    {
        std::cout << "some error: " << ex.what() << std::flush;
    }

    return 0;
}
