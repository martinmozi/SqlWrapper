#pragma once

#include "../../include/selector.h"
#include "statement_impl.h"

namespace PqImpl
{
    class Selector : public Sql::Selector
    {
    public:
        Selector(PGconn* conn, bool isSingle);
        void select(std::function<void(const Sql::DbRow & dbRow)> && selectFunction) override;
        #include "../statement.inl"

    private:
        PGconn* conn_;
        PqImpl::Statement statement_;
        bool isSingle_;
    };
}