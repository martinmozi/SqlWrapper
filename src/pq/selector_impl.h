#pragma once

#include "../../include/selector.h"
#include "statement_impl.h"

namespace PqImpl
{
    class SelectorBase : public virtual Sql::SelectorBase
    {
    public:
        SelectorBase(PGconn* conn, bool isSingle);
        #include "../statement.inl"

    protected:
        void selectData();
     
    private:
        std::unique_ptr<Sql::DbRow> readRow(PGresult* res, int row, int columns) const;

    protected:
        PGconn* conn_;
        PqImpl::Statement statement_;
        bool isSingle_;
    };

    class Selector : public SelectorBase, public virtual Sql::Selector
    {
    public:
        Selector(PGconn* conn);
        void select(std::function<void(const Sql::DbRow & dbRow)>&& selectFunction) override;

    protected:
        void setData(std::unique_ptr<Sql::DbRow> dbRow) override;

    private:
        std::function<void(const Sql::DbRow & dbRow)> selectFunction_;
    };

    class SingleSelector : public SelectorBase, public virtual Sql::SingleSelector
    {
    public:
        SingleSelector(PGconn* conn);
        std::unique_ptr<Sql::DbRow> select() override;

    protected:
        void setData(std::unique_ptr<Sql::DbRow> dbRow) override;

    private:
        std::unique_ptr<Sql::DbRow> dbRow_;
    };
}