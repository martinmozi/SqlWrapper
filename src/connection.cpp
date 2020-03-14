#include "../include/connection.h"

#ifdef PQ_BACKEND
#include "pq/connection_impl.h"
#include "pq/statement_impl.h"
#include "pq/selector_impl.h"
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
            PqImpl::Connection* pConnection = dynamic_cast<PqImpl::Connection*>(this);
            return std::make_unique<PqImpl::Selector>(pConnection->connection(), false);
        }
        break;

        case DbType::Sqlite:
            break;

        default:
            break;
        }

        return nullptr;
    }
}
//#ifdef PQ_BACKEND
//    Postgres = 1,
//#endif
//#ifdef SQLITE_BACKEND
//        Sqlite = 2,
//#endif