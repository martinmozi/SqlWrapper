#pragma once

#include <dpi.h>
#include "../statement_impl.h"

namespace OracleImpl
{
    class Statement : public DbImpl::Statement
    {
    public:
        Statement(dpiConn* conn);
        dpiStmt* execute();

    private:
        dpiConn* conn_;
    };
}