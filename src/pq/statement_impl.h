#pragma once

#include "connection_impl.h"
#include "../statement_impl.h"

namespace PqImpl
{
    class Statement : public DbImpl::Statement
    {
    public:
        Statement(PGconn* conn);
        PGresult* execute();

    protected:
        PGconn* conn_;
    };
}