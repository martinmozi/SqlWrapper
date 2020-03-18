#include <memory>
#include "selector_impl.h"
#include "db_row_impl.h"

namespace SqliteImpl
{
    Selector::Selector(sqlite3* conn, bool isSingle)
    :   statement_(conn),
        isSingle_(isSingle)
    {
    }

    void Selector::select(std::function<void(const Sql::DbRow & dbRow)> && selectFunction)
    {
        sqlite3_stmt *stmt = statement_.execute();
        int nFields = sqlite3_column_count(stmt);
        while (sqlite3_step(stmt) == SQLITE_ROW) 
        {
            std::unique_ptr<SqliteImpl::DbRow> rowData = std::make_unique<SqliteImpl::DbRow>();
            for (int i = 0; i < nFields; i++)
            {
                switch (sqlite3_column_type(stmt, i))
                {
                    case SQLITE_INTEGER:
                        rowData->append(DbImpl::Data((int64_t)sqlite3_column_int64(stmt, i)));
                        break;

                    case SQLITE_FLOAT:
                        rowData->append(DbImpl::Data(sqlite3_column_double(stmt, i)));
                        break;

                    case SQLITE_BLOB:
                        {
                            int bytes = sqlite3_column_bytes(stmt, i);
                            auto *pData = (const unsigned char*)sqlite3_column_blob(stmt, i);
                            rowData->append(DbImpl::Data(std::vector<unsigned char>(pData, pData + bytes)));
                        }
                        break;

                    case SQLITE_TEXT:
                        rowData->append(DbImpl::Data(sqlite3_column_text(stmt, i)));
                        break;

                    case SQLITE_NULL:
                        rowData->appendNull();
                        break;

                    default:
                        break;
                }
            }

            selectFunction(*rowData.get());
        }

        sqlite3_clear_bindings(stmt);
        sqlite3_finalize(stmt);
    }
}
