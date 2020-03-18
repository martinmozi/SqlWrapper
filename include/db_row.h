#pragma once

#include <vector>
#include <string>

namespace Sql
{
	class DbRow
	{
    public:
        virtual ~DbRow() = default;
        virtual bool isNull(int index) const = 0;
        virtual void value(int index, int32_t & val) const = 0;
        virtual void value(int index, int64_t & val) const = 0;
        virtual void value(int index, bool & val) const = 0;
        virtual void value(int index, double & val) const = 0;
        virtual void value(int index, std::string& val) const = 0;
        virtual void value(int index, std::vector<unsigned char>& val) const = 0;
        virtual void nvlValue(int index, int32_t& val, int32_t valWhenNull) const = 0;
        virtual void nvlValue(int index, int64_t& val, int64_t valWhenNull) const = 0;
        virtual void nvlValue(int index, bool& val, bool valWhenNull) const = 0;
        virtual void nvlValue(int index, double& val, double valWhenNull) const = 0;
        virtual void nvlValue(int index, std::string& val, std::string valWhenNull) const = 0;
        virtual void nvlValue(int index, std::vector<unsigned char>& val, std::vector<unsigned char> valWhenNull) const = 0;
	};
}
