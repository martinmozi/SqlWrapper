#include <assert.h>
#include <stdexcept>
#include "db_row_impl.h"

namespace DbImpl
{
    void DbRow::append(Data&& val)
    {
        rowData_.push_back(std::move(val));
    }

    void DbRow::appendNull()
    {
        rowData_.push_back(Data());
    }

    bool DbRow::isNull(int index) const
    {
        checkIndex(index);
        return (rowData_.at(index).type_ == DataType::Null);
    }

    void DbRow::value(int index, bool& val) const
    {
        checkIndex(index);
        val = rowData_.at(index).value<bool>();
    }

    void DbRow::value(int index, std::vector<unsigned char>& val) const
    {
        checkIndex(index);
        val = rowData_.at(index).value<std::vector<unsigned char>>();
    }

    void DbRow::value(int index, int32_t& val) const
    {
        checkIndex(index);
        val = rowData_.at(index).value<int32_t>();
    }

    void DbRow::value(int index, int64_t& val) const
    {
        checkIndex(index);
        val = rowData_.at(index).value<int64_t>();
    }

    void DbRow::value(int index, double& val) const
    {
        checkIndex(index);
        val = rowData_.at(index).value<double>();
    }

    void DbRow::value(int index, std::string& val) const
    {
        checkIndex(index);
        val = rowData_.at(index).value<std::string>();
    }

    void DbRow::nvlValue(int index, int32_t& val, int32_t valWhenNull) const
    {
        _value(index, val, valWhenNull);
    }

    void DbRow::nvlValue(int index, int64_t& val, int64_t valWhenNull) const
    {
        _value(index, val, valWhenNull);
    }

    void DbRow::nvlValue(int index, bool& val, bool valWhenNull) const
    {
        _value(index, val, valWhenNull);
    }

    void DbRow::nvlValue(int index, double& val, double valWhenNull) const
    {
        _value(index, val, valWhenNull);
    }

    void DbRow::nvlValue(int index, std::string& val, std::string valWhenNull) const
    {
        _value(index, val, valWhenNull);
    }

    void DbRow::nvlValue(int index, std::vector<unsigned char>& val, std::vector<unsigned char> valWhenNull) const
    {
        _value(index, val, valWhenNull);
    }

    void DbRow::checkIndex(int index) const
    {
        if (index > (int)rowData_.size())
            throw std::runtime_error("Selector index is out of the row size");
    }
}
