#include "transaction_impl.h"

namespace PqImpl
{
    Transaction::Transaction(PGconn* conn)
    :   conn_(conn)
    {
    }

    void Transaction::_begin()
    {
        PGresult* res = PQexec(conn_, "BEGIN");
        if (PQresultStatus(res) != PGRES_COMMAND_OK)
        {
            std::string errorStr = std::string("BEGIN command failed: ") + PQerrorMessage(conn_);
            PQclear(res);
            throw std::runtime_error(errorStr);
        }
    }

    void Transaction::_commit()
    {
        PGresult* res = PQexec(conn_, "COMMIT");
        if (PQresultStatus(res) != PGRES_COMMAND_OK)
        {
            std::string errorStr = std::string("COMMIT command failed: ") + PQerrorMessage(conn_);
            PQclear(res);
            throw std::runtime_error(errorStr);
        }
    }

    void Transaction::_rollback()
    {
        PGresult* res = PQexec(conn_, "ROLLBACK");
        if (PQresultStatus(res) != PGRES_COMMAND_OK)
        {
            std::string errorStr = std::string("ROLLBACK command failed: ") + PQerrorMessage(conn_);
            PQclear(res);
        }
    }
}
