#pragma once

#include "../transaction_statement_impl.h"
#include "statement_impl.h"

namespace SqliteImpl
{
    class TransactionStatement : public DbImpl::TransactionStatement
    {
    public:
        TransactionStatement(sqlite3* conn);
        void exec() override;
        #include "../statement.inl"

    private:
        SqliteImpl::Statement statement_;
        sqlite3 *conn_;
    };
}