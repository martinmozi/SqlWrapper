#include "db_row_impl.h"

namespace OracleImpl
{
    void DbRow::value(int index, bool& val) const
    {
        checkIndex(index);
        val = (rowData_.at(index).value<int64_t>() == 1);
    }
}
