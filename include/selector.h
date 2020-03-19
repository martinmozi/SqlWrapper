#pragma once

#include <memory>
#include <functional>
#include "statement.h"
#include "db_row.h"

namespace Sql   
{
    class SelectorBase : public Statement
    {
    public:
        virtual ~SelectorBase() = default;

    protected:
        virtual void setData(std::unique_ptr<Sql::DbRow> dbRow) = 0;
    };

    class Selector : public virtual SelectorBase
    {
    public:
        virtual ~Selector() = default;
        virtual void select(std::function<void(const Sql::DbRow & dbRow)> && selectFunction) = 0;
    };

    class SingleSelector : public virtual SelectorBase
    {
    public:
        virtual ~SingleSelector() = default;
        virtual std::unique_ptr<Sql::DbRow> select() = 0;
    };
}
