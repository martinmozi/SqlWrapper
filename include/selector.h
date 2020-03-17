#pragma once

#include <functional>
#include "statement.h"
#include "db_row.h"

namespace Sql   
{
    class Selector : public Statement
    {
    public:
        virtual ~Selector() = default;
        virtual void select(std::function<void(const Sql::DbRow & dbRow)> && selectFunction) = 0;
    };
}
