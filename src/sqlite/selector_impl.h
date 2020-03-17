#pragma once

#include "../../include/selector.h"
#include "statement_impl.h"

namespace SqliteImpl
{
    class Selector : public Sql::Selector
    {
    public:
        Selector(sqlite3* conn, bool isSingle);
        void select(std::function<void(const Sql::DbRow & dbRow)> && selectFunction) override;
        #include "../statement.inl"

    private:
        SqliteImpl::Statement statement_;
        bool isSingle_;
    };
}