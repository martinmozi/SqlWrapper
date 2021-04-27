#pragma once

#include "../../include/selector.h"
#include "statement_impl.h"

namespace OracleImpl
{
    class SelectorBase : public virtual Sql::SelectorBase
    {
    public:
        SelectorBase(dpiConn* conn);
        #include "../statement.inl"

    protected:
        void selectData();

    protected:
        OracleImpl::Statement statement_;
    };
    
    class Selector : public SelectorBase, public Sql::Selector
    {
    public:
        Selector(dpiConn* conn);
        void select(std::function<void(const Sql::DbRow & dbRow)> && selectFunction) override;

    protected:
        void setData(std::unique_ptr<Sql::DbRow> dbRow) override;

    private:
        std::function<void(const Sql::DbRow & dbRow)> selectFunction_;
    };

    class SingleSelector : public SelectorBase, public Sql::SingleSelector
    {
    public:
        SingleSelector(dpiConn* conn);
        std::unique_ptr<Sql::DbRow> select() override;

    protected:
        void setData(std::unique_ptr<Sql::DbRow> dbRow) override;

    private:
        int counter_;
        std::unique_ptr<Sql::DbRow> dbRow_;
    };
}