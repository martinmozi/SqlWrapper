#include <assert.h>
#include <stdexcept>
#include "../include/db_row.h"

namespace Sql
{
    DbRow::DbRow()
    {
    }

    void DbRow::append(const std::string& value)
    {
        rowData_.push_back(value);
        nullData_.push_back(bool(false));
    }

    void DbRow::appendNull()
    {
        rowData_.push_back(std::string());
        nullData_.push_back(bool(true));
    }

    bool DbRow::isNull(int index) const
    {
        checkIndex(index);
        bool nullValue = nullData_.at(index);
        return nullValue;
    }

    void DbRow::checkIndex(int index) const
    {
        if (index > (int)rowData_.size() || index > (int)nullData_.size())
            throw std::runtime_error("Selector index is out of the row size");
    }

    void DbRow::blobValue(int, std::string&) const
    {
        assert(0);
    }

    void DbRow::blobValue(int, std::string&, const std::string&) const
    {
        assert(0);
    }
}
