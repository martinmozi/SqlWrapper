#include <memory>
#include "selector_impl.h"
#include "db_row_impl.h"
#include "error_impl.h"

namespace OracleImpl
{
    SelectorBase::SelectorBase(dpiConn* conn)
    :   statement_(conn)
    {
    }

    void SelectorBase::selectData()
    {
        uint32_t nFields = 0;
        dpiStmt* stmt = statement_.execute();
        if (dpiStmt_execute(stmt, 0, &nFields) < 0)
        {
            dpiStmt_release(stmt);
            throw std::runtime_error(oracleErrorMsg());
        }

        while (1) 
        {
            int found = 0;
            uint32_t bufferRowIndex = 0;
            if (dpiStmt_fetch(stmt, &found, &bufferRowIndex) < 0)
            {
                dpiStmt_release(stmt);
                throw std::runtime_error(oracleErrorMsg());
            }

            if (!found)
                break;

            std::unique_ptr<OracleImpl::DbRow> rowData = std::make_unique<OracleImpl::DbRow>();
            for (uint32_t i = 1; i <= nFields; i++)
            {
                dpiData* outData;
                uint32_t oracleTypeNum = 0;
                if (dpiStmt_getQueryValue(stmt, i, &oracleTypeNum, &outData) < 0)
                {
                    dpiStmt_release(stmt);
                    throw std::runtime_error(oracleErrorMsg());
                }

                switch (oracleTypeNum)
                {
                case DPI_NATIVE_TYPE_NULL:
                    rowData->appendNull();
                    break;

                case DPI_NATIVE_TYPE_INT64:
                case DPI_NATIVE_TYPE_UINT64:
                    rowData->append(DbImpl::Data((int64_t)outData->value.asInt64));
                    break;

                case DPI_NATIVE_TYPE_FLOAT:
                case DPI_NATIVE_TYPE_DOUBLE:
                    rowData->append(DbImpl::Data((double)outData->value.asDouble));
                    break;

                case DPI_NATIVE_TYPE_BYTES:
                    rowData->append(DbImpl::Data(std::string((const char*)outData->value.asBytes.ptr, outData->value.asBytes.length)));
                    break;

                case DPI_NATIVE_TYPE_BOOLEAN:
                    rowData->append(DbImpl::Data(outData->value.asBoolean > 0 ? true : false));
                    break;

                //case DPI_NATIVE_TYPE_TIMESTAMP                   3005
                //case DPI_NATIVE_TYPE_INTERVAL_DS                 3006
                //case DPI_NATIVE_TYPE_INTERVAL_YM                 3007
                //case DPI_NATIVE_TYPE_LOB                         3008
                //case DPI_NATIVE_TYPE_OBJECT                      3009
                //case DPI_NATIVE_TYPE_STMT                        3010
                //case DPI_NATIVE_TYPE_ROWID                       3012
                //case DPI_NATIVE_TYPE_JSON                        3013
                //case DPI_NATIVE_TYPE_JSON_OBJECT                 3014
                //case DPI_NATIVE_TYPE_JSON_ARRAY                  3015

                default:
                    throw std::runtime_error("Unsupported binding parameter type");
                }
            }

            setData(std::move(rowData));
        }

        dpiStmt_release(stmt);
    }

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

    Selector::Selector(dpiConn* conn)
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

    SingleSelector::SingleSelector(dpiConn* conn)
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
