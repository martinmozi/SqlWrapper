#include <memory>
#include "selector_impl.h"
#include "db_row_impl.h"

namespace SqliteImpl
{
    SelectorBase::SelectorBase(sqlite3* conn)
    :   statement_(conn)
    {
    }

    void SelectorBase::selectData()
    {
        sqlite3_stmt* stmt = statement_.execute();
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
                    auto* pData = (const unsigned char*)sqlite3_column_blob(stmt, i);
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

            setData(std::move(rowData));
        }

        sqlite3_clear_bindings(stmt);
        sqlite3_finalize(stmt);
    }

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

    Selector::Selector(sqlite3* conn)
    :   SelectorBase(conn)
    {
    }

    void Selector::select(std::function<void(const Sql::DbRow & dbRow)> && selectFunction)
    {
        selectFunction_ = std::move(selectFunction);
        SelectorBase::selectData();    
    }

    void Selector::setData(std::unique_ptr<Sql::DbRow> dbRow)
    {
        selectFunction_(*dbRow.get());
    }

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

    SingleSelector::SingleSelector(sqlite3* conn)
    :   SelectorBase(conn),
        counter_(0)
    {
    }

    std::unique_ptr<Sql::DbRow> SingleSelector::select()
    {
        counter_ = 0;
        SelectorBase::selectData();
        if (counter_ == 0)
            throw std::runtime_error("No data for the statement");
        else if (counter_ > 1)
            throw std::runtime_error("Multiply rows for the statement");

        return std::move(dbRow_);
    }

    void SingleSelector::setData(std::unique_ptr<Sql::DbRow> dbRow)
    {
        dbRow_ = std::move(dbRow);
        counter_++;
    }
}
