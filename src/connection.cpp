#include "../include/connection.h"

#ifdef PQ_BACKEND
#include "pq/connection_impl.h"
#include "pq/statement_impl.h"
#endif

#ifdef SQLITE_BACKEND
#include "sqlite/sqlitedb.h"
#endif

namespace Sql
{
	std::unique_ptr<Connection> createConnection(DbType dbType, const std::string& connectionStr)
	{
		switch (dbType)
		{
		case DbType::Postgres:
            return std::make_unique<PqImpl::Connection>(connectionStr);

		case DbType::Sqlite:
			break;

		default:
			break;
		}

        return nullptr;
	}

    Connection::Connection(DbType dbType)
    :   dbType_(dbType)
    {
    }

    std::unique_ptr<Statement> Connection::createStatement()
    {
        switch (dbType_)
        {
        case DbType::Postgres:
        {
            PqImpl::Connection * pConnection = dynamic_cast<PqImpl::Connection*>(this);
            return std::make_unique<PqImpl::Statement>(pConnection->connection());
        }

        case DbType::Sqlite:
            break;

        default:
            break;
        }

        return nullptr;
    }

    std::unique_ptr<Selector> Connection::createSelector()
    {
        switch(dbType_)
        {
        case DbType::Postgres:
        {
           /* DbImpl::PqConnection* pConnection = dynamic_cast<DbImpl::PqConnection*>(this);
            return std::make_unique<DbImpl::PqStatement>(pConnection->connection());*/
        }
        break;

        case DbType::Sqlite:
            break;

        default:
            break;
        }

        return nullptr;
    }

   /* class Statement : public DbImpl::PqStatement
    {
    public:
        Statement(const Connection& connection) : DbImpl::PqStatement(connection.connection()) {}
        virtual ~Statement() { rollback(); }
    };

    class Selector : public DbImpl::PqSelector
    {
    public:
        Selector(const Connection& connection) : DbImpl::PqSelector(connection.connection(), false) {}
    };

    class SingleSelector : public DbImpl::PqSelector
    {
    public:
        SingleSelector(const Connection& connection) : DbImpl::PqSelector(connection.connection(), true) {}
    };*/
}
//#ifdef PQ_BACKEND
//    Postgres = 1,
//#endif
//#ifdef SQLITE_BACKEND
//        Sqlite = 2,
//#endif