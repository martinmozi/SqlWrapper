#pragma once

#include "../db_row_impl.h"

namespace PqImpl
{
    class DbRow : public DbImpl::DbRow
    {
    public:
        DbRow();
        void value(int index, bool& val) const override;
    };
}