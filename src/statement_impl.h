#pragma once

#include <any>
#include <vector>
#include <string>
#include "../include/statement.h"

// todo replace any with something non c++17

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

    class Statement : public Sql::Statement
    {
    protected:
        struct Data
        {
            std::string name;
            std::any value;
            DataType type;
        };

    private:
        std::string query_;
        std::vector<Data> data_;

    protected:
        void replaceBindedParameter(const std::string& bindedName, bool isNull, int& index);
        const char* query() const;
        const std::vector<Data>& data() const;

    public:
        Statement() = default;

        void prepare(const std::string& query) override;
        void append(const std::string& appendQuery) override;
        void bind(const std::string& key, int32_t value) override;
        void bind(const std::string& key, int64_t value) override;
        void bind(const std::string& key, bool value) override;
        void bind(const std::string& key, double value) override;
        void bind(const std::string& key, const std::string& value) override;
        void bind(const std::string& key, const char * value) override;
        void bindBlob(const std::string& key, const std::vector<unsigned char>& value) override;
        void bind(const std::string& key, int32_t value, int32_t nullValue) override;
        void bind(const std::string& key, int64_t value, int64_t nullValue) override;
        void bind(const std::string& key, bool value, bool nullValue) override;
        void bind(const std::string& key, double value, double nullValue) override;
        void bind(const std::string& key, const std::string& value, std::string nullValue) override;
        void bind(const std::string& key, const char * value, const char * nullValue) override;
        void bindBlob(const std::string& key, const std::vector<unsigned char>& value, std::vector<unsigned char> nullValue) override;
        void bindAndAppend(const std::string& appendedQuery, const std::string& key, int32_t value) override;
        void bindAndAppend(const std::string& appendedQuery, const std::string& key, int64_t value) override;
        void bindAndAppend(const std::string& appendedQuery, const std::string& key, bool value) override;
        void bindAndAppend(const std::string& appendedQuery, const std::string& key, double value) override;
        void bindAndAppend(const std::string& appendedQuery, const std::string& key, const std::string& value) override;
        void bindAndAppend(const std::string& appendedQuery, const std::string& key, const char* value) override;
        void bindBlobAndAppend(const std::string& appendedQuery, const std::string& key, const std::vector<unsigned char>& value) override;
        void bindAndAppend(const std::string& appendedQuery, const std::string& key, int32_t value, int32_t nullValue) override;
        void bindAndAppend(const std::string& appendedQuery, const std::string& key, int64_t value, int64_t nullValue) override;
        void bindAndAppend(const std::string& appendedQuery, const std::string& key, bool value, bool nullValue) override;
        void bindAndAppend(const std::string& appendedQuery, const std::string& key, double value, double nullValue) override;
        void bindAndAppend(const std::string& appendedQuery, const std::string& key, const std::string& value, std::string nullValue) override;
        void bindAndAppend(const std::string& appendedQuery, const std::string& key, const char* value, const char* nullValue) override;
        void bindBlobAndAppend(const std::string& appendedQuery, const std::string& key, const std::vector<unsigned char>& value, std::vector<unsigned char> nullValue) override;

    private:
        template<class T> void bindData(const std::string& key, const T& value, DataType type)
        {
            Data data;
            data.name = key;
            data.type = type;
            data.value = value;
            data_.push_back(data);
        }

        template<class T> void bindData(const std::string& key, const T& value, T nullValue, DataType type)
        {
            bindData(key, value, (nullValue == value) ? DataType::Null : type);
        }
    };
}