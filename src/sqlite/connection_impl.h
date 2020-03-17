#pragma once

#include "sqlite3.h"
#include "../connection_impl.h"

namespace SqliteImpl
{
	class Connection : public DbImpl::Connection
	{
	public:
		Connection(const std::string & connectionString);

		void connect() override;
		void disconnect() override;
		sqlite3* connection() const;

	private:
		sqlite3* conn_;
	};
}