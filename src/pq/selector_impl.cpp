#include "selector_impl.h"
#include "db_row_impl.h"

namespace PqImpl
{

    SelectorBase::SelectorBase(PGconn* conn, bool isSingle)
    :   statement_(conn),
        isSingle_(isSingle)
    {
    }

    std::unique_ptr<Sql::DbRow> SelectorBase::readRow(PGresult* res, int row, int columns) const
    {
        std::unique_ptr<PqImpl::DbRow> rowData = std::make_unique<PqImpl::DbRow>();
        for (int i = 0; i < columns; i++)
        {
            if (PQgetisnull(res, row, i) == 1)
                rowData->appendNull();
            else
                rowData->append(std::string(PQgetvalue(res, row, i)));
        }

        return std::move(rowData);
    }

    void SelectorBase::selectData()
    {
        PGresult* res = statement_.execute();
        if (PQresultStatus(res) != PGRES_TUPLES_OK)
        {
            std::string errorStr = PQerrorMessage(conn_);
            PQclear(res);
            throw std::runtime_error(errorStr);
        }

        int rows = PQntuples(res);
        int columns = PQnfields(res);

        if (isSingle_)
        {
            if (rows == 0)
            {
                PQclear(res);
                throw std::runtime_error("No data for single selection");
            }
            else if (rows > 1)
            {
                PQclear(res);
                throw std::runtime_error("Multiply rows for single selection");
            }

            setData(std::move(readRow(res, 0, columns)));
        }

        for (int i = 0; i < rows; i++)
            setData(std::move(readRow(res, i, columns)));

        PQclear(res);
    }

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

    Selector::Selector(PGconn* conn)
    :   SelectorBase(conn, false)
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
    
    SingleSelector::SingleSelector(PGconn* conn)
    :  SelectorBase(conn, true)
    {
    }

    void SingleSelector::setData(std::unique_ptr<Sql::DbRow> dbRow)
    {
        dbRow_ = std::move(dbRow);
    }

    std::unique_ptr<Sql::DbRow> SingleSelector::select()
    {
        SelectorBase::selectData();
        return std::move(dbRow_);
    }
}
