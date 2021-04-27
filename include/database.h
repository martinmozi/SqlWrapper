#pragma once

#include <memory>
#include "statement.h"
#include "transaction_statement.h"
#include "selector.h"

namespace Sql
{
    enum DbType
    {
        Postgres,
        Sqlite,
        Oracle
    };

    class Connection
    {
    public:
        virtual ~Connection() = default;
        virtual std::unique_ptr<TransactionStatement> createStatement() = 0;
        virtual std::unique_ptr<Selector> createSelector() = 0;
        virtual std::unique_ptr<SingleSelector> createSingleSelector() = 0;
    };

    std::unique_ptr<Connection> createConnection(DbType dbType, const std::string& connectionStr);
}