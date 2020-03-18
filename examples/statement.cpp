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
        auto statement = connection->createStatement();

        statement->prepare("INSERT INTO countries(id, iso, name, strvalue, iso3, numcode, phonecode) VALUES(:id, :iso, :name, :strvalue, :iso3, :numcode, :phonecode)");
        statement->bind("id", (int64_t)1205);
        statement->bind("iso", "isoX");
        statement->bind("name", "nameX");
        statement->bind("strvalue", "strvalueX");
        statement->bind("iso3", "iso3X");
        statement->bind("numcode", 1026);
        statement->bind("phonecode", 1028);
        statement->exec();

       statement->prepare("INSERT INTO countries(id, iso, name, strvalue, iso3, numcode, phonecode) VALUES(:id, :iso, :name, :strvalue, :iso3, :numcode, :phonecode)");
        statement->bind("id", (int64_t)1206);
        statement->bind("iso", "isoX");
        statement->bind("name", "nameX");
        statement->bind("strvalue", "strvalueX");
        statement->bind("iso3", "iso3X");
        statement->bind("numcode", 1026);
        statement->bind("phonecode", 1028);
        statement->exec();
        statement->commit();
    }
    catch (const std::exception & ex)
    {
        std::cout << "some error: " << ex.what() << std::flush;
    }

    return 0;
}
