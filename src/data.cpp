#include <vector>
#include "data.h"

namespace DbImpl
{
    Data::Data()
    :   value_(nullptr),
        type_(DataType::Null)
    {
    }

    Data::Data(Data&& d)
    :   value_(d.value_),
        type_(d.type_)
    {
        d.value_ = nullptr;
        d.type_ = DataType::Null;
    }

    Data::~Data()
    {
        switch (type_)
        {
        case Null:
            break;

        case Bool:
            delete ((bool*)value_);
            break;

        case BigInt:
            delete ((int64_t*)value_);
            break;

        case Int:
            delete ((int32_t*)value_);
            break;

        case Double:
            delete ((double*)value_);
            break;

        case String:
            delete ((std::string*)value_);
            break;

        case Blob:
            delete ((std::vector<unsigned char>*)value_);
            break;

        default:
            break;
        }
    }

    void Data::setValue(const bool& value)
    {
        value_ = new bool(value);
        type_ = DataType::Bool;
    }

    void Data::setValue(const int32_t& value)
    {
        value_ = new int32_t(value);
        type_ = DataType::Int;
    }

    void Data::setValue(const int64_t& value)
    {
        value_ = new int64_t(value);
        type_ = DataType::BigInt;
    }

    void Data::setValue(const double& value)
    {
        value_ = new double(value);
        type_ = DataType::Double;
    }

    void Data::setValue(const std::string& value)
    {
        value_ = new std::string(value);
        type_ = DataType::String;
    }

    void Data::setValue(const std::vector<unsigned char>& value)
    {
        value_ = new std::vector<unsigned char>(value);
        type_ = DataType::Blob;
    }

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

    BindData::BindData(BindData&& d)
    :   Data(std::move(d)),
        name_(d.name_)
    {
        d.name_ = "";
    }
}
