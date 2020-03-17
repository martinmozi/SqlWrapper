#include "transaction_impl.h"

namespace SqliteImpl
{
    Transaction::Transaction(sqlite3* conn)
        : conn_(conn)
    {
    }

    void Transaction::_begin()
    {
        if (sqlite3_exec(conn_, "BEGIN TRANSACTION", 0, 0, 0) != SQLITE_OK)
            throw std::runtime_error(sqlite3_errmsg(conn_));
    }

    void Transaction::_commit()
    {
        if (sqlite3_exec(conn_, "COMMIT", 0, 0, 0) != SQLITE_OK)
            throw std::runtime_error(sqlite3_errmsg(conn_));
    }

    void Transaction::_rollback()
    {
        if (sqlite3_exec(conn_, "ROLLBACK", 0, 0, 0) != SQLITE_OK)
            throw std::runtime_error(sqlite3_errmsg(conn_));
    }
}
