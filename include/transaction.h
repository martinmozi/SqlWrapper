#pragma once

namespace Sql
{
    class Transaction
	{
	public:
		virtual void begin() {};
		virtual void commit() {};
		virtual void rollback() {};
	};
}