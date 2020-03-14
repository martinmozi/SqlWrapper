#pragma once

#include <memory>
#include <functional>
#include "db_row.h"

namespace Sql   
{
    class Selector
    {
    public:
        virtual void select(std::function<void(std::unique_ptr<Sql::DbRow> dbRow)> && selectFunction) = 0;
    };
}
