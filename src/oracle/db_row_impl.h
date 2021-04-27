#pragma once

#include "../db_row_impl.h"

namespace OracleImpl
{
    class DbRow : public DbImpl::DbRow
    {
    public:
        DbRow() = default;
        void value(int index, bool& val) const override;
    };
}