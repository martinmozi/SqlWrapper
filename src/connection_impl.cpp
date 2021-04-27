#include "connection_impl.h"

#ifdef PQ_BACKEND
#include "pq/connection_impl.h"
#include "pq/transaction_statement_impl.h"
#include "pq/selector_impl.h"
#endif

#ifdef SQLITE_BACKEND
#include "sqlite/connection_impl.h"
#include "sqlite/transaction_statement_impl.h"
#include "sqlite/selector_impl.h"
#endif

#ifdef ORACLE_BACKEND
#include "oracle/connection_impl.h"
#include "oracle/transaction_statement_impl.h"
#include "oracle/selector_impl.h"
#endif

namespace DbImpl
{
    Connection::Connection(Sql::DbType dbType, const std::string & connectionStr)
    :   dbType_(dbType),
        connectionString_(connectionStr)
    {
    }

    Connection::~Connection()
    {
        disconnect();
    }

    std::unique_ptr<Sql::TransactionStatement> Connection::createStatement()
    {
        switch (dbType_)
        {
#ifdef PQ_BACKEND
        case Sql::DbType::Postgres:
            {
                PqImpl::Connection* pConnection = dynamic_cast<PqImpl::Connection*>(this);
                return std::make_unique<PqImpl::TransactionStatement>(pConnection->connection());
            }
            break;
#endif
#ifdef SQLITE_BACKEND
        case Sql::DbType::Sqlite:
            {
                SqliteImpl::Connection* pConnection = dynamic_cast<SqliteImpl::Connection*>(this);
                return std::make_unique<SqliteImpl::TransactionStatement>(pConnection->connection());
            }
            break;
#endif
#ifdef ORACLE_BACKEND
        case Sql::DbType::Oracle:
        {
            OracleImpl::Connection* pConnection = dynamic_cast<OracleImpl::Connection*>(this);
            return std::make_unique<OracleImpl::TransactionStatement>(pConnection->connection());
        }
        break;
#endif

        default:
            throw std::runtime_error("Unsupported database engine");
        }

        return nullptr;
    }

    std::unique_ptr<Sql::Selector> Connection::createSelector()
    {
        switch (dbType_)
        {
#ifdef PQ_BACKEND
        case Sql::DbType::Postgres:
        {
            PqImpl::Connection* pConnection = dynamic_cast<PqImpl::Connection*>(this);
            return std::make_unique<PqImpl::Selector>(pConnection->connection());
        }
        break;
#endif

#ifdef SQLITE_BACKEND
        case Sql::DbType::Sqlite:
            {
                SqliteImpl::Connection* pConnection = dynamic_cast<SqliteImpl::Connection*>(this);
                return std::make_unique<SqliteImpl::Selector>(pConnection->connection());
            }
        break;
#endif
#ifdef ORACLE_BACKEND
        case Sql::DbType::Oracle:
        {
            OracleImpl::Connection* pConnection = dynamic_cast<OracleImpl::Connection*>(this);
            return std::make_unique<OracleImpl::Selector>(pConnection->connection());
        }
        break;
#endif

        default:
            break;
        }

        return nullptr;
    }

    std::unique_ptr<Sql::SingleSelector> Connection::createSingleSelector()
    {
        switch (dbType_)
        {
#ifdef PQ_BACKEND
        case Sql::DbType::Postgres:
        {
            PqImpl::Connection* pConnection = dynamic_cast<PqImpl::Connection*>(this);
            return std::make_unique<PqImpl::SingleSelector>(pConnection->connection());
        }
        break;
#endif

#ifdef SQLITE_BACKEND
        case Sql::DbType::Sqlite:
        {
            SqliteImpl::Connection* pConnection = dynamic_cast<SqliteImpl::Connection*>(this);
            return std::make_unique<SqliteImpl::SingleSelector>(pConnection->connection());
        }
        break;
#endif

#ifdef ORACLE_BACKEND
        case Sql::DbType::Oracle:
        {
            OracleImpl::Connection* pConnection = dynamic_cast<OracleImpl::Connection*>(this);
            return std::make_unique<OracleImpl::SingleSelector>(pConnection->connection());
        }
        break;
#endif

        default:
            break;
        }

        return nullptr;
    }
}

namespace Sql
{
    std::unique_ptr<Connection> createConnection(DbType dbType, const std::string& connectionStr)
    {
        std::unique_ptr<DbImpl::Connection> connection;
        switch (dbType)
        {
#ifdef PQ_BACKEND
        case DbType::Postgres:
            connection = std::make_unique<PqImpl::Connection>(connectionStr);
            break;
#endif
#ifdef SQLITE_BACKEND
        case DbType::Sqlite:
            connection = std::make_unique<SqliteImpl::Connection>(connectionStr);
            break;
#endif
#ifdef ORACLE_BACKEND
        case DbType::Oracle:
            connection = std::make_unique<OracleImpl::Connection>(connectionStr);
            break;
#endif

        default:
            break;
        }

        connection->connect();
        return connection;
    }
}
