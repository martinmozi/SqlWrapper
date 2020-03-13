#pragma once

#include "../../include/transaction.h"
#include "statement_base_impl.h"

namespace PqImpl
{
    class Statement : public StatementBase, public Sql::Transaction
    {
    public:
        Statement(PGconn* conn);
        void exec() override;
        void begin() override;
        void commit() override;
        void rollback() override;

    private:
        void _begin();

    private:
        bool bRunningTransaction_;
    };
}