#include "transaction_statement_impl.h"
#include "transaction_impl.h"

namespace SqliteImpl
{
    TransactionStatement::TransactionStatement(sqlite3* conn)
    :   DbImpl::TransactionStatement(std::move(std::make_unique<Transaction>(conn))),
        statement_(conn),
        conn_(conn)
    {
    }

    void TransactionStatement::exec()
    {
        std::string errorMessage;
        sqlite3_stmt* stmt = statement_.execute();
        if (sqlite3_step(stmt) != SQLITE_DONE)
            errorMessage = sqlite3_errmsg(conn_);

        sqlite3_clear_bindings(stmt);
        sqlite3_finalize(stmt);
        if (!errorMessage.empty())
            throw std::runtime_error(errorMessage);
    }
}