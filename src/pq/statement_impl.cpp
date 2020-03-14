#include "statement_impl.h"

namespace PqImpl
{
    Statement::Statement(PGconn* conn)
    :   StatementBase(conn),
        bRunningTransaction_(true)
    {
        _begin();
    }

    void Statement::_begin()
    {
        PGresult* res = PQexec(conn_, "BEGIN");
        if (PQresultStatus(res) != PGRES_COMMAND_OK)
        {
            std::string errorStr = std::string("BEGIN command failed: ") + PQerrorMessage(conn_);
            PQclear(res);
            throw std::runtime_error(errorStr);
        }
    }

    void Statement::begin()
    {
        _begin();
    }

    void Statement::exec()
    {
        std::string errorMessage;
        PGresult* res = StatementBase::execute();
        ExecStatusType execStatusType = PQresultStatus(res);
        if (execStatusType != PGRES_COMMAND_OK)
        {
            errorMessage = PQresultErrorMessage(res);
            if (errorMessage.empty())
                errorMessage = "Pq error without message with code " + std::to_string(execStatusType);
        }

        PQclear(res);
        if (!errorMessage.empty())
            throw std::runtime_error(errorMessage);
    }

    void Statement::commit()
    {
        if (bRunningTransaction_)
        {
            PGresult* res = PQexec(conn_, "COMMIT");
            if (PQresultStatus(res) != PGRES_COMMAND_OK)
            {
                std::string errorStr = std::string("COMMIT command failed: ") + PQerrorMessage(conn_);
                PQclear(res);
                throw std::runtime_error(errorStr);
            }
        }

        bRunningTransaction_ = false;
    }

    void Statement::rollback()
    {
        if (bRunningTransaction_)
        {
            PGresult* res = PQexec(conn_, "ROLLBACK");
            if (PQresultStatus(res) != PGRES_COMMAND_OK)
            {
                std::string errorStr = std::string("ROLLBACK command failed: ") + PQerrorMessage(conn_);
                PQclear(res);
            }
        }

        bRunningTransaction_ = false;
    }
}