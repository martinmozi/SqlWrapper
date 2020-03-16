#pragma once

#include <vector>
#include <string>
#include "../include/db_row.h"

namespace DbImpl
{
	class DbRow : public Sql::DbRow
	{
    protected:
		std::vector<std::string> rowData_;
		std::vector<bool> nullData_;

	public:
		DbRow() = default;
        bool isNull(int index) const override;
        virtual void value(int index, bool& val) const = 0;
        virtual void value(int index, std::vector<char>& val) const = 0;
        void value(int index, int32_t& val) const override;
        void value(int index, int64_t& val) const override;
        void value(int index, double& val) const override;
        void value(int index, std::string& val) const override;
        void nvlValue(int index, int32_t& val, int32_t valWhenNull) const override;
        void nvlValue(int index, int64_t& val, int64_t valWhenNull) const override;
        void nvlValue(int index, bool& val, bool valWhenNull) const override;
        void nvlValue(int index, double& val, double valWhenNull) const override;
        void nvlValue(int index, std::string& val, std::string valWhenNull) const override;
        void nvlValue(int index, std::vector<char>& val, std::vector<char> valWhenNull) const override;

		void append(const std::string & val);
		void appendNull();

	protected:
        template<typename T> void _value(int index, T& t, T valWhenNull) const
        {
            if (isNull(index))
                t = valWhenNull;
            else
                value(index, t);
        }

		void checkIndex(int index) const;
	};
}
