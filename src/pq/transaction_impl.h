#pragma once

#include "../transaction.h"
#include "connection_impl.h"

namespace PqImpl
{
    class Transaction : public DbImpl::Transaction
    {
    public:
        Transaction(PGconn* conn);

    protected:
        void _begin() override;
        void _commit() override;
        void _rollback() override;

    private:
        PGconn* conn_;
    };
}