#pragma once

#include <string>

namespace DbImpl
{
    enum DataType
    {
        Null,
        Bool,
        BigInt,
        Int,
        Double,
        String,
        Blob,
    };

    struct Data
    {
        void* value_;
        DataType type_;

        Data();
        Data(bool val) { setValue(val); }
        Data(int32_t val) { setValue(val); }
        Data(int64_t val) { setValue(val); }
        Data(double val) { setValue(val); }
        Data(const char * val) { setValue(std::string(val)); }
        Data(const unsigned char* val) { setValue(std::string((const char*)val)); }
        Data(const std::string & val) { setValue(val); }
        Data(const std::vector<unsigned char>& val) { setValue(val); }
        Data(Data&& d);
        Data& operator=(Data&& d) = delete;
        Data(const Data&) = delete;
        Data& operator=(const Data&) = delete;
        virtual ~Data();

        void setValue(const bool& value);
        void setValue(const int32_t& value);
        void setValue(const int64_t& value);
        void setValue(const double& value);
        void setValue(const std::string& value);
        void setValue(const std::vector<unsigned char>& value);

        template<typename T> const T& value() const { return *((T*)value_); }
    };

    struct BindData : Data
    {
        std::string name_;

        BindData() = default;
        BindData(BindData&& d);
        BindData& operator=(BindData&& d) = delete;
        BindData(const BindData&) = delete;
        BindData& operator=(const BindData&) = delete;

        template<typename T> void setValue(std::string name, const T& value)
        {
            name_ = name;
            Data::setValue(value);
        }
    };
}