#include "statement_impl.h"
#include <stdexcept>

namespace DbImpl
{
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

    void Statement::exec()
    {
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
        bindData(key, value, DataType::Int);
    }

    void Statement::bind(const std::string& key, int32_t value, int32_t nullValue)
    {
        bindData(key, value, nullValue, DataType::Int);
    }

    void Statement::bind(const std::string& key, int64_t value)
    {
        bindData(key, value, DataType::BigInt);
    }

    void Statement::bind(const std::string& key, int64_t value, int64_t nullValue)
    {
        bindData(key, value, nullValue, DataType::BigInt);
    }

    void Statement::bind(const std::string& key, bool value)
    {
        bindData(key, value, DataType::Bool);
    }

    void Statement::bind(const std::string& key, bool value, bool nullValue)
    {
        bindData(key, value, nullValue, DataType::Bool);
    }

    void Statement::bind(const std::string& key, double value)
    {
        bindData(key, value, DataType::Double);
    }

    void Statement::bind(const std::string& key, double value, double nullValue)
    {
        bindData(key, value, nullValue, DataType::Double);
    }

    void Statement::bind(const std::string& key, const std::string& value)
    {
        bindData(key, value, DataType::String);
    }

    void Statement::bind(const std::string& key, const std::string& value, std::string nullValue)
    {
        bindData(key, value, nullValue, DataType::String);
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
        bindData(key, value, DataType::Blob);
    }

    void Statement::bindBlob(const std::string& key, const std::vector<unsigned char>& value, std::vector<unsigned char> nullValue)
    {
        bindData(key, value, nullValue, DataType::Blob);
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
