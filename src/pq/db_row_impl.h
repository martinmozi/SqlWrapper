#pragma once

#include "../db_row_impl.h"

namespace PqImpl
{
    class DbRow : public DbImpl::DbRow
    {
    public:
        DbRow() = default;
        void value(int index, bool& val) const override;
        void value(int index, std::vector<unsigned char>& val) const override;
        void value(int index, int32_t& val) const override;
        void value(int index, int64_t& val) const override;
        void value(int index, double& val) const override;
    };
}