#include "connection_impl.h"
#include <set>
#include "error_impl.h"

namespace
{
    std::vector<std::string> tokenize(std::string const& str, const char delim)
    {
        size_t start;
        size_t end = 0;
        std::vector<std::string> out;
        while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
        {
            end = str.find(delim, start);
            std::string s = str.substr(start, end - start);
            if (! s.empty())
                out.push_back(str.substr(start, end - start));
        }

        return out;
    }
}

namespace OracleImpl
{
    dpiContext* gDpiContext = nullptr;
    dpiErrorInfo gErrorInfo;
    void destroyContext()
    {
        if (gDpiContext)
        {
            dpiContext_destroy(gDpiContext);
            gDpiContext = nullptr;
        }
    }

    Connection::Connection(const std::string& connectionString)
    :   DbImpl::Connection(Sql::DbType::Oracle, connectionString),
        conn_(nullptr)
    {
    }

    void Connection::connect()
    {
        if (!gDpiContext)
        {
            atexit(destroyContext);
            if (dpiContext_createWithParams(DPI_MAJOR_VERSION, DPI_MINOR_VERSION, NULL, &gDpiContext, &gErrorInfo) < 0)
            {
                throw std::runtime_error("Unable to create oracle odpi context");
            }
        }

        ConnectionParams c = connectionParamsFromConnectionString();
        if (dpiConn_create(gDpiContext, c.user.c_str(), c.user.size(), c.password.c_str(), c.password.size(), c.service.c_str(), c.service.size(), NULL, NULL, &conn_) < 0)
        {
            throw std::runtime_error(oracleErrorMsg());
        }

        if (c.timeout > 0)
        {
            if (dpiConn_setCallTimeout(conn_, c.timeout) < 0)
            {
                throw std::runtime_error(oracleErrorMsg());
            }
        }
    }

    void Connection::disconnect()
    {
        if (conn_)
        {
            dpiConn_release(conn_);
            conn_ = nullptr;
        }
    }

    dpiConn* Connection::connection() const
    {
        return conn_;
    }

    Connection::ConnectionParams Connection::connectionParamsFromConnectionString() const
    {
        Connection::ConnectionParams connectionParams;
        std::vector<std::string> params = tokenize(connectionString_, ';');
        for (auto it : params)
        {
            std::vector<std::string> p = tokenize(it, '=');
            if (p.size() != 2)
                continue;

            if (p[0] == "user")
                connectionParams.user = p[1];
            else if (p[0] == "password")
                connectionParams.password = p[1];
            else if (p[0] == "service")
                connectionParams.service = p[1];
            else if (p[0] == "timeout")
                connectionParams.timeout = std::stoi(p[1]);
        }

        if (connectionParams.user.empty() || connectionParams.password.empty() || connectionParams.service.empty())
        {
            throw std::runtime_error("Empty string for user, password or service");
        }

        return connectionParams;
    }
}
