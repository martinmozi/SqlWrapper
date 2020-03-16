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
        virtual ~Connection() = default;
        virtual std::unique_ptr<Statement> createStatement(/*todo default start transaction to true*/) = 0;
        virtual std::unique_ptr<Selector> createSelector() = 0;
    };

    std::unique_ptr<Connection> createConnection(DbType dbType, const std::string& connectionStr);
}