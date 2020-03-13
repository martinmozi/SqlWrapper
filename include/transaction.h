#pragma once

namespace Sql
{
    class Transaction
	{
	public:
		virtual void begin() = 0;
		virtual void commit() = 0;
		virtual void rollback() = 0;
	};
}