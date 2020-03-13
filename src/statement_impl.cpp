#include "statement_impl.h"

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

    void Statement::prepare(const std::string& query)
    {
        query_ = query;
        data_.clear();
    }

    void Statement::append(const std::string& appendQuery)
    {
        query_ += appendQuery;
    }

    void Statement::bind(const std::string& key, int32_t value, std::optional<int32_t> nullValue)
    {
        bindData(key, value, nullValue, DataType::Int);
    }

    void Statement::bind(const std::string& key, int64_t value, std::optional<int64_t> nullValue)
    {
        bindData(key, value, nullValue, DataType::BigInt);
    }

    void Statement::bind(const std::string& key, bool value, std::optional<bool> nullValue)
    {
        bindData(key, value, nullValue, DataType::Bool);
    }

    void Statement::bind(const std::string& key, double value, std::optional<double> nullValue)
    {
        bindData(key, value, nullValue, DataType::Double);
    }

    void Statement::bind(const std::string& key, const std::string& value, std::optional<std::string> nullValue)
    {
        bindData(key, value, nullValue, DataType::String);
    }

    void Statement::bindBlob(const std::string& key, const std::string& value, std::optional<std::string> nullValue)
    {
        bindData(key, value, nullValue, DataType::Blob);
    }

    void Statement::bindAndAppend(const std::string& appendedQuery, const std::string& key, int32_t value, std::optional<int> nullValue)
    {
        query_ += appendedQuery;
        bind(key, value, nullValue);
    }

    void Statement::bindAndAppend(const std::string& appendedQuery, const std::string& key, int64_t value, std::optional<int64_t> nullValue)
    {
        query_ += appendedQuery;
        bind(key, value, nullValue);
    }

    void Statement::bindAndAppend(const std::string& appendedQuery, const std::string& key, bool value, std::optional<bool> nullValue)
    {
        query_ += appendedQuery;
        bind(key, value, nullValue);
    }

    void Statement::bindAndAppend(const std::string& appendedQuery, const std::string& key, double value, std::optional<double> nullValue)
    {
        query_ += appendedQuery;
        bind(key, value, nullValue);
    }

    void Statement::bindAndAppend(const std::string& appendedQuery, const std::string& key, const std::string& value, std::optional<std::string> nullValue)
    {
        query_ += appendedQuery;
        bind(key, value, nullValue);
    }

    void Statement::bindBlobAndAppend(const std::string& appendedQuery, const std::string& key, const std::string& value, std::optional<std::string> nullValue)
    {
        query_ += appendedQuery;
        bind(key, value, nullValue);
    }
}
