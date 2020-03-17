#pragma once

#include "../transaction_statement_impl.h"
#include "statement_impl.h"

namespace PqImpl
{
    class TransactionStatement : public DbImpl::TransactionStatement
    {
    public:
        TransactionStatement(PGconn* conn);
        void exec() override;
        #include "../statement.inl"

    private:
        PqImpl::Statement statement_;
    };
}