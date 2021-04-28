#include "transaction_statement_impl.h"
#include "transaction_impl.h"
#include "error_impl.h"

namespace OracleImpl
{
    TransactionStatement::TransactionStatement(dpiConn* conn)
    :   DbImpl::TransactionStatement(std::move(std::make_unique<Transaction>(conn))),
        statement_(conn),
        conn_(conn)
    {
    }

    void TransactionStatement::exec()
    {
        std::string errorMessage;
        dpiStmt* stmt = statement_.execute();
        if (dpiStmt_execute(stmt, 0, NULL) < 0)
        {
            dpiStmt_release(stmt);
            throw std::runtime_error(oracleErrorMsg());
        }
      
        dpiStmt_release(stmt);
    }
}