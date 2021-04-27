#pragma once

#include <dpi.h>
#include "../connection_impl.h"

namespace OracleImpl
{
	class Connection : public DbImpl::Connection
	{
		struct ConnectionParams
		{
			std::string user;
			std::string password;
			std::string service;
			uint32_t timeout = 0;
 		};
	public:
		Connection(const std::string & connectionString);

		void connect() override;
		void disconnect() override;
		dpiConn* connection() const;

	private:
		ConnectionParams connectionParamsFromConnectionString() const;

	private:
		dpiConn* conn_;
	};
}