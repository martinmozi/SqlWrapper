#pragma once

#include "../transaction.h"
#include "connection_impl.h"

namespace SqliteImpl
{
    class Transaction : public DbImpl::Transaction
    {
    public:
        Transaction(sqlite3* conn);

    protected:
        void _begin() override;
        void _commit() override;
        void _rollback() override;

    private:
        sqlite3* conn_;
    };
}