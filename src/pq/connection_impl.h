#pragma once

#include <postgresql/libpq-fe.h>
#include "../connection_impl.h"

namespace PqImpl
{
	class Connection : public DbImpl::Connection
	{
	public:
		Connection(const std::string & connectionString);

		void connect() override;
		void disconnect() override;
		PGconn* connection() const;

	private:
		void _connect();

	private:
		PGconn *conn_;
	};
}