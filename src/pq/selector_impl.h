#pragma once

#include "../../include/selector.h"
#include "statement_base_impl.h"

namespace PqImpl
{
    class Selector : public StatementBase, public Sql::Selector
    {
    public:
        Selector(PGconn* conn, bool isSingle);
        void select(std::function<void(std::unique_ptr<Sql::DbRow> dbRow)> && selectFunction) override;

    private:
        bool isSingle_;
    };
}