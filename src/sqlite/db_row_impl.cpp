#include <postgresql/libpq-fe.h>
#include "db_row_impl.h"

namespace SqliteImpl
{
    void DbRow::value(int index, bool& val) const
    {
        checkIndex(index);
        val = (rowData_.at(index) == 1);
    }

    void DbRow::value(int index, std::vector<char>& val) const
    {
        size_t length = 0;
        const unsigned char* inData = (const unsigned char*)rowData_.at(index).data();
        if (inData && length > 0)
        {
            unsigned char* pData = PQunescapeBytea(inData, &length);
            val.assign(pData, pData + length);
            PQfreemem(pData);
        }
    }
}
