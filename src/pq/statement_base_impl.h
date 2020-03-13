#pragma once

#include <any>
#include "connection_impl.h"
#include "../statement_impl.h"

namespace PqImpl
{
    class StatementBase : public DbImpl::Statement
    {
    public:
        StatementBase(PGconn* conn);

    protected:
        PGresult* _exec();

    protected:
        PGconn* conn_;
    };
}