#pragma once

#include "sqlite3.h"
#include "../statement_impl.h"

namespace SqliteImpl
{
    class Statement : public DbImpl::Statement
    {
    public:
        Statement(sqlite3* conn);
       // void exec() override;

    private:
        sqlite3 * conn_;
    };
}