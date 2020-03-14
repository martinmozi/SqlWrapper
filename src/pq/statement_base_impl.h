#pragma once

#include "connection_impl.h"
#include "../statement_impl.h"

namespace PqImpl
{
    class StatementBase : public DbImpl::Statement
    {
    public:
        StatementBase(PGconn* conn);

    protected:
        PGresult* execute();

    protected:
        PGconn* conn_;
    };
}