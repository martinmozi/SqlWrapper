#include "transaction_statement_impl.h"
#include "transaction_impl.h"

namespace PqImpl
{
    TransactionStatement::TransactionStatement(PGconn* conn)
    :   DbImpl::TransactionStatement(std::move(std::make_unique<Transaction>(conn))),
        statement_(conn)
    {
    }

    void TransactionStatement::exec()
    {
        std::string errorMessage;
        PGresult* res = statement_.execute();
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
}