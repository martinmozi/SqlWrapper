#pragma once

#include "statement_base_impl.h"

namespace PqImpl
{
    class Statement : public StatementBase
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