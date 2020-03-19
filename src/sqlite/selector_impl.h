#pragma once

#include "../../include/selector.h"
#include "statement_impl.h"

namespace SqliteImpl
{
    class SelectorBase : public virtual Sql::SelectorBase
    {
    public:
        SelectorBase(sqlite3* conn);
        #include "../statement.inl"

    protected:
        void selectData();

    protected:
        SqliteImpl::Statement statement_;
    };
    
    class Selector : public SelectorBase, public virtual Sql::Selector
    {
    public:
        Selector(sqlite3* conn);
        void select(std::function<void(const Sql::DbRow & dbRow)> && selectFunction) override;

    protected:
        void setData(std::unique_ptr<Sql::DbRow> dbRow) override;

    private:
        std::function<void(const Sql::DbRow & dbRow)> selectFunction_;
    };

    class SingleSelector : public SelectorBase, public virtual Sql::SingleSelector
    {
    public:
        SingleSelector(sqlite3* conn);
        std::unique_ptr<Sql::DbRow> select() override;

    protected:
        void setData(std::unique_ptr<Sql::DbRow> dbRow) override;

    private:
        int counter_;
        std::unique_ptr<Sql::DbRow> dbRow_;
    };
}