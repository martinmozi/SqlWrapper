#pragma once

#include <vector>
#include "data.h"
#include "../include/db_row.h"

namespace DbImpl
{
	class DbRow : public Sql::DbRow
	{
    protected:
		std::vector<Data> rowData_;

	public:
		DbRow() = default;
        bool isNull(int index) const override;
        void value(int index, bool& val) const override;
        void value(int index, std::vector<unsigned char>& val) const override;
        void value(int index, int32_t& val) const override;
        void value(int index, int64_t& val) const override;
        void value(int index, double& val) const override;
        void value(int index, std::string& val) const override;
        void nvlValue(int index, int32_t& val, int32_t valWhenNull) const override;
        void nvlValue(int index, int64_t& val, int64_t valWhenNull) const override;
        void nvlValue(int index, bool& val, bool valWhenNull) const override;
        void nvlValue(int index, double& val, double valWhenNull) const override;
        void nvlValue(int index, std::string& val, std::string valWhenNull) const override;
        void nvlValue(int index, std::vector<unsigned char>& val, std::vector<unsigned char> valWhenNull) const override;

		void append(Data && val);
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
