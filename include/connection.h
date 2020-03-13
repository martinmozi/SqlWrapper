#pragma once

#include <memory>
#include "statement.h"
#include "selector.h"

namespace Sql
{
    enum DbType
    {
        Postgres,
        Sqlite,
    };

    class Connection
    {
    public:
        Connection(DbType dbType);
        virtual void connect() = 0;
        virtual void disconnect() = 0;
        std::unique_ptr<Statement> createStatement();
        std::unique_ptr<Selector> createSelector();

    private:
        DbType dbType_;
    };

    std::unique_ptr<Connection> createConnection(DbType dbType, const std::string& connectionStr);
}