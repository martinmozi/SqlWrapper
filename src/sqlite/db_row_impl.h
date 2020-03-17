#pragma once

#include "../db_row_impl.h"

namespace SqliteImpl
{
    class DbRow : public DbImpl::DbRow
    {
    public:
        DbRow() = default;
        void value(int index, bool& val) const override;
        void value(int index, std::vector<char>& val) const override;
    };
}