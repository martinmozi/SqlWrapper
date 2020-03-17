#pragma once

#include "../include/database.h"

namespace DbImpl
{
    class Connection : public Sql::Connection
    {
    public:
        static std::unique_ptr<Sql::Connection> createConnection(Sql::DbType dbType, const std::string& connectionStr);
        Connection(Sql::DbType dbType, const std::string& connectionStr);
        virtual ~Connection();
        std::unique_ptr<Sql::TransactionStatement> createStatement() override;
        std::unique_ptr<Sql::Selector> createSelector() override;

        virtual void connect() = 0;
        virtual void disconnect() {};

    protected:
        Sql::DbType dbType_;
        std::string connectionString_;
    };
}
