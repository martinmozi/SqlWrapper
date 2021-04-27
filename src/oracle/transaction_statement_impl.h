#pragma once

#include "../transaction_statement_impl.h"
#include "statement_impl.h"

namespace OracleImpl
{
    class TransactionStatement : public DbImpl::TransactionStatement
    {
    public:
        TransactionStatement(dpiConn* conn);
        void exec() override;
        #include "../statement.inl"

    private:
        OracleImpl::Statement statement_;
        dpiConn* conn_;
    };
}