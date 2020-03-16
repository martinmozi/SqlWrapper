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

        selector->prepare("SELECT id, name from countries WHERE numcode > :numcode AND iso3 = :iso3");
        selector->bind("numcode", 24);
        selector->bind("iso3", "ATG");
        selector->select([](const Sql::DbRow& dbRow)
        {
            int64_t id;
            std::string name;
            dbRow.value(0, id);
            dbRow.value(1, name);
            std::cout << id << name << std::flush;
        });
    }
    catch (const std::exception & ex)
    {
        std::cout << "some error: " << ex.what() << std::flush;
    }

    return 0;
}
