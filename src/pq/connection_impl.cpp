#include "connection_impl.h"

namespace PqImpl
{
    Connection::Connection(const std::string& connectionString)
    :   Sql::Connection(Sql::DbType::Postgres),
        connectionString_(connectionString),
        conn_(nullptr)
    {
    }

    Connection::~Connection()
    {
        disconnect();
    }

    void Connection::connect()
    {
        if (conn_ == NULL)
        {
            _connect();
        }
        else
        {
            if (PQstatus(conn_) != CONNECTION_OK)
            {
                PQfinish(conn_);
                conn_ = NULL;
                _connect();
            }
        }
    }

    void Connection::_connect()
    {
        conn_ = PQconnectdb(connectionString_.c_str());
        ConnStatusType connStatusType = PQstatus(conn_);
        if (connStatusType == CONNECTION_OK)
            return;

        PQfinish(conn_);
        conn_ = nullptr;
        std::string err = "Connection error with code " + std::to_string(connStatusType);
        throw std::runtime_error(err);
    }

    void Connection::disconnect()
    {
        if (conn_)
        {
            PQfinish(conn_);
            conn_ = nullptr;
        }
    }

    PGconn* Connection::connection() const
    {
        return conn_;
    }
}