#pragma once

#include <memory>
#include "transaction.h"
#include "statement_impl.h"
#include "../include/transaction_statement.h"

namespace DbImpl
{
    class TransactionStatement : public DbImpl::Statement, public Sql::TransactionStatement
    {
    public:
        TransactionStatement(std::unique_ptr<Transaction> transaction);
        virtual ~TransactionStatement();
        virtual void exec(){}
        void begin() override;
        void commit() override;
        void rollback() override;

    private:
        std::unique_ptr<Transaction> transaction_;
    };
}