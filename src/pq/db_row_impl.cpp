#include <postgresql/libpq-fe.h>
#include <stdexcept>
#include "db_row_impl.h"

namespace PqImpl
{
    void DbRow::value(int index, bool& val) const
    {
        checkIndex(index);
        val = (rowData_.at(index).value<std::string>() == "t");
    }

    void DbRow::value(int index, std::vector<unsigned char>& val) const
    {
        std::vector<unsigned char> inData = rowData_.at(index).value<std::vector<unsigned char>>();
        if (! inData.empty())
        {
            size_t length = 0;
            unsigned char* pData = PQunescapeBytea(inData.data(), &length);
            val.assign(pData, pData + length);
            PQfreemem(pData);
        }
    }

    void DbRow::value(int index, int32_t& val) const
    {
        size_t sz = 0;
        checkIndex(index);
        const std::string& dataStr = rowData_.at(index).value<std::string>();
        val = std::stoi(dataStr, &sz);
        if (sz != dataStr.size())
            throw std::runtime_error(std::string("Bad conversion of string to int32_t: ") + dataStr);
    }

    void DbRow::value(int index, int64_t& val) const
    {
        size_t sz = 0;
        checkIndex(index);
        const std::string& dataStr = rowData_.at(index).value<std::string>();
        val = std::stoll(dataStr, &sz);
        if (sz != dataStr.size())
            throw std::runtime_error(std::string("Bad conversion of string to int32_t: ") + dataStr);
    }

    void DbRow::value(int index, double& val) const
    {
        size_t sz = 0;
        checkIndex(index);
        const std::string& dataStr = rowData_.at(index).value<std::string>();
        val = std::stod(dataStr, &sz);
        if (sz != dataStr.size())
            throw std::runtime_error(std::string("Bad conversion of string to int32_t: ") + dataStr);
    }
}
