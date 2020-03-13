#pragma once

#include <postgresql/libpq-fe.h>
#include "../../include/connection.h"

namespace PqImpl
{
	class Connection : public Sql::Connection
	{
	public:
		Connection(const std::string & connectionString);
		virtual ~Connection();

		void connect() override;
		void disconnect() override;
		PGconn* connection() const;

	private:
		void _connect();

	private:
		std::string connectionString_;
		PGconn *conn_;
	};
}