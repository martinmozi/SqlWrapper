#pragma once

#include "statement.h"

namespace Sql
{
    class TransactionStatement : public Statement
    {
    public:
        virtual ~TransactionStatement() = default;
        virtual void exec() = 0;
        virtual void begin() = 0;
        virtual void commit() = 0;
        virtual void rollback() = 0;
    };
}
