#include <assert.h>
#include <stdexcept>
#include "db_row_impl.h"

namespace DbImpl
{
    void DbRow::append(const std::string& val)
    {
        rowData_.push_back(val);
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
        return nullData_.at(index);
    }

    void DbRow::value(int index, int32_t& val) const
    {
        size_t sz = 0;
        checkIndex(index);
        const std::string& dataStr = rowData_.at(index);
        val = std::stoi(dataStr, &sz);
        if (sz != dataStr.size())
        {
            std::string errorStr = "Bad conversion of string to int32_t: " + dataStr;
            throw std::runtime_error(errorStr);
        }
    }

    void DbRow::value(int index, int64_t& val) const
    {
        size_t sz = 0;
        checkIndex(index);
        const std::string& dataStr = rowData_.at(index);
        val = std::stoll(dataStr, &sz);
        if (sz != dataStr.size())
        {
            std::string errorStr = "Bad conversion of string to int64_t: " + dataStr;
            throw std::runtime_error(errorStr);
        }
    }

    void DbRow::value(int index, double& val) const
    {
        size_t sz = 0;
        checkIndex(index);
        const std::string& dataStr = rowData_.at(index);
        val = std::stod(dataStr, &sz);
        if (sz != dataStr.size())
        {
            std::string errorStr = "Bad conversion of string to int64_t: " + dataStr;
            throw std::runtime_error(errorStr);
        }
    }

    void DbRow::value(int index, std::string& val) const
    {
        checkIndex(index);
        val = rowData_.at(index);
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

    void DbRow::nvlValue(int index, std::vector<char>& val, std::vector<char> valWhenNull) const
    {
        _value(index, val, valWhenNull);
    }

    void DbRow::checkIndex(int index) const
    {
        if (index > (int)rowData_.size() || index > (int)nullData_.size())
            throw std::runtime_error("Selector index is out of the row size");
    }
}
