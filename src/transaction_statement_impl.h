#pragma once

#include <memory>
#include "transaction.h"
#include "../include/transaction_statement.h"

namespace DbImpl
{
    class TransactionStatement : public Sql::TransactionStatement
    {
    public:
        TransactionStatement(std::unique_ptr<Transaction> transaction);
        virtual ~TransactionStatement();
        void begin() override;
        void commit() override;
        void rollback() override;

    private:
        std::unique_ptr<Transaction> transaction_;
    };
}