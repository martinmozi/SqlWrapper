#pragma once

#include <vector>
#include <string>
#include <any>
#include <type_traits>

namespace Sql
{
	class DbRow
	{
		std::vector<std::string> rowData_;
		std::vector<bool> nullData_;

	public:
		void append(const std::string & value);
		void appendNull();

	public:
		DbRow();
		bool isNull(int index) const;
		void blobValue(int , std::string & ) const;
		void blobValue(int , std::string & , const std::string &) const;

		template<typename T> void value(int index, T & t, T nullValue) const
		{
			if (isNull(index))
				t = nullValue;
			else
				value(index, t);
		}

		template<typename T> void value(int /*index*/, T & /*t*/) const;

	private:
		void checkIndex(int index) const;
	};
}
