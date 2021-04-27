#pragma once

#include "../transaction.h"
#include "connection_impl.h"

namespace OracleImpl
{
    class Transaction : public DbImpl::Transaction
    {
    public:
        Transaction(dpiConn* conn);

    protected:
        void _begin() override;
        void _commit() override;
        void _rollback() override;

    private:
        dpiConn* conn_;
    };
}