#include "connection_impl.h"

namespace SqliteImpl
{
    Connection::Connection(const std::string& connectionString)
    :   DbImpl::Connection(Sql::DbType::Sqlite, connectionString),
        conn_(nullptr)
    {
    }

    void Connection::connect()
    {
        int rc = SQLITE_OK;
        if (connectionString_ == ":memory:")
        {
            rc = sqlite3_open(connectionString_.c_str(), &conn_);
        }
        else
        {
            // always the database file must exists
            rc = sqlite3_open_v2(connectionString_.c_str(), &conn_, SQLITE_OPEN_READWRITE, NULL);
        }

        if (rc != SQLITE_OK)
            throw std::runtime_error(sqlite3_errmsg(conn_));
    }

    void Connection::disconnect()
    {
        if (conn_)
        {
            sqlite3_close(conn_);
            conn_ = nullptr;
        }
    }

    sqlite3* Connection::connection() const
    {
        return conn_;
    }
}
