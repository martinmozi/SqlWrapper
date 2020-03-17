#include "statement_impl.h"
#include <stdexcept>

namespace DbImpl
{
    Statement::Data::Data()
    :   value_(nullptr),
        type_(DataType::Null)
    {
    }

    Statement::Data::Data(Data&& d)
    :   name_(d.name_),
        value_(d.value_),
        type_(d.type_)
    {
        d.name_ = "";
        d.value_ = nullptr;
        d.type_ = DataType::Null;
    }

    Statement::Data& Statement::Data::operator=(Data&& d)
    {
        name_ = d.name_;
        value_ = d.value_;
        type_ = d.type_;
        d.name_ = "";
        d.value_ = nullptr;
        d.type_ = DataType::Null;
        return *this;
    }

    Statement::Data::~Data()
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

    template<> void Statement::Data::setValue(std::string name, const bool& value)
    {
        value_ = new bool(value);
        type_ = DataType::Bool;
        name_ = name;
    }

    template<> void Statement::Data::setValue(std::string name, const int32_t& value)
    {
        value_ = new int32_t(value);
        type_ = DataType::Int;
        name_ = name;
    }

    template<> void Statement::Data::setValue(std::string name, const int64_t&  value)
    {
        value_ = new int64_t(value);
        type_ = DataType::BigInt;
        name_ = name;
    }

    template<> void Statement::Data::setValue(std::string name, const double& value)
    {
        value_ = new double(value);
        type_ = DataType::Double;
        name_ = name;
    }

    template<> void Statement::Data::setValue(std::string name, const std::string& value)
    {
        value_ = new std::string(value);
        type_ = DataType::String;
        name_ = name;
    }

    template<> void Statement::Data::setValue(std::string name, const std::vector<unsigned char>& value)
    {
        value_ = new std::vector<unsigned char>(value);
        type_ = DataType::Blob;
        name_ = name;
    }

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

    const char* Statement::query() const
    {
        return query_.c_str();
    }

    const std::vector<Statement::Data>& Statement::data() const
    {
        return data_;
    }

    void Statement::replaceBindedParameter(const std::string& bindedName, bool isNull, int& index)
    {
        size_t sz = 0;
        std::string bindName(":" + bindedName);
        bool bFound = false;
        while (true)
        {
            std::string bindValue = isNull ? "NULL" : ("$" + std::to_string(index));
            sz = query_.find(bindName, sz);
            if (sz == std::string::npos)
                break;

            // check whole word
            if (query_.size() > sz + bindName.size())
            {
                char ch = query_.at(sz + bindName.size());
                if (std::isalpha(ch) || std::isdigit(ch) || ch == '_')
                {
                    sz += bindName.size();
                    continue;
                }
            }

            bFound = true;
            query_.replace(sz, bindName.length(), bindValue);
            sz += bindValue.size();
        }

        if (!bFound)
            throw std::runtime_error("Unknown binded parameter " + bindedName);

        if (!isNull)
            index++;
    }

    void Statement::prepare(const std::string& query)
    {
        query_ = query;
        data_.clear();
    }

    void Statement::append(const std::string& appendQuery)
    {
        query_ += appendQuery;
    }

    void Statement::bind(const std::string& key, int32_t value)
    {
        bindData(key, value);
    }

    void Statement::bind(const std::string& key, int32_t value, int32_t nullValue)
    {
        bindData(key, value, nullValue);
    }

    void Statement::bind(const std::string& key, int64_t value)
    {
        bindData(key, value);
    }

    void Statement::bind(const std::string& key, int64_t value, int64_t nullValue)
    {
        bindData(key, value, nullValue);
    }

    void Statement::bind(const std::string& key, bool value)
    {
        bindData(key, value);
    }

    void Statement::bind(const std::string& key, bool value, bool nullValue)
    {
        bindData(key, value, nullValue);
    }

    void Statement::bind(const std::string& key, double value)
    {
        bindData(key, value);
    }

    void Statement::bind(const std::string& key, double value, double nullValue)
    {
        bindData(key, value, nullValue);
    }

    void Statement::bind(const std::string& key, const std::string& value)
    {
        bindData(key, value);
    }

    void Statement::bind(const std::string& key, const std::string& value, std::string nullValue)
    {
        bindData(key, value, nullValue);
    }

    void Statement::bind(const std::string& key, const char * value)
    {
        bind(key, std::string(value));
    }

    void Statement::bind(const std::string& key, const char * value, const char * nullValue)
    {
        bind(key, std::string(value), std::string(nullValue));
    }

    void Statement::bindBlob(const std::string& key, const std::vector<unsigned char>& value)
    {
        bindData(key, value);
    }

    void Statement::bindBlob(const std::string& key, const std::vector<unsigned char>& value, std::vector<unsigned char> nullValue)
    {
        bindData(key, value, nullValue);
    }

    void Statement::bindAndAppend(const std::string& appendedQuery, const std::string& key, int32_t value)
    {
        query_ += appendedQuery;
        bind(key, value);
    }

    void Statement::bindAndAppend(const std::string& appendedQuery, const std::string& key, int32_t value, int32_t nullValue)
    {
        query_ += appendedQuery;
        bind(key, value, nullValue);
    }

    void Statement::bindAndAppend(const std::string& appendedQuery, const std::string& key, int64_t value)
    {
        query_ += appendedQuery;
        bind(key, value);
    }

    void Statement::bindAndAppend(const std::string& appendedQuery, const std::string& key, int64_t value, int64_t nullValue)
    {
        query_ += appendedQuery;
        bind(key, value, nullValue);
    }

    void Statement::bindAndAppend(const std::string& appendedQuery, const std::string& key, bool value)
    {
        query_ += appendedQuery;
        bind(key, value);
    }

    void Statement::bindAndAppend(const std::string& appendedQuery, const std::string& key, bool value, bool nullValue)
    {
        query_ += appendedQuery;
        bind(key, value, nullValue);
    }

    void Statement::bindAndAppend(const std::string& appendedQuery, const std::string& key, double value)
    {
        query_ += appendedQuery;
        bind(key, value);
    }

    void Statement::bindAndAppend(const std::string& appendedQuery, const std::string& key, double value, double nullValue)
    {
        query_ += appendedQuery;
        bind(key, value, nullValue);
    }

    void Statement::bindAndAppend(const std::string& appendedQuery, const std::string& key, const std::string& value)
    {
        query_ += appendedQuery;
        bind(key, value);
    }

    void Statement::bindAndAppend(const std::string& appendedQuery, const std::string& key, const std::string& value, std::string nullValue)
    {
        query_ += appendedQuery;
        bind(key, value, nullValue);
    }

    void Statement::bindAndAppend(const std::string& appendedQuery, const std::string& key, const char * value)
    {
        query_ += appendedQuery;
        bind(key, std::string(value));
    }

    void Statement::bindAndAppend(const std::string& appendedQuery, const std::string& key, const char* value, const char* nullValue)
    {
        query_ += appendedQuery;
        bind(key, std::string(value), std::string(nullValue));
    }

    void Statement::bindBlobAndAppend(const std::string& appendedQuery, const std::string& key, const std::vector<unsigned char>& value)
    {
        query_ += appendedQuery;
        bindBlob(key, value);
    }

    void Statement::bindBlobAndAppend(const std::string& appendedQuery, const std::string& key, const std::vector<unsigned char>& value, std::vector<unsigned char> nullValue)
    {
        query_ += appendedQuery;
        bindBlob(key, value, nullValue);
    }
}
