#pragma once

#include <functional>
#include "db_row.h"

namespace Sql   
{
    class Selector
    {
    public:
        virtual void select(std::function<void(const DbRow & dbRow)> selectFunction) = 0;
    };
}
