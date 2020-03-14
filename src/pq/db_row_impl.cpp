#include "db_row_impl.h"

namespace PqImpl
{
    DbRow::DbRow()
    {
    }

    void DbRow::value(int index, bool& val) const
    {
        checkIndex(index);
        val = (rowData_.at(index) == "t");
    }
}
