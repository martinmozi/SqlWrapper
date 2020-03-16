#pragma once

#include <vector>
#include <string>
#include "transaction.h"

namespace Sql
{
    class Statement : public Transaction
	{
	public:
        virtual ~Statement() = default;
        virtual void exec() = 0;
        virtual void prepare(const std::string& query) = 0;
        virtual void append(const std::string& appendQuery) = 0;
        virtual void bind(const std::string& key, int32_t value) = 0;
        virtual void bind(const std::string& key, int64_t value) = 0;
        virtual void bind(const std::string& key, bool value) = 0;
        virtual void bind(const std::string& key, double value) = 0;
        virtual void bind(const std::string& key, const std::string& value) = 0;
        virtual void bind(const std::string& key, const char* value) = 0;
        virtual void bindBlob(const std::string& key, const std::vector<unsigned char>& value) = 0;
        virtual void bind(const std::string& key, int32_t value, int32_t nullValue) = 0;
        virtual void bind(const std::string& key, int64_t value, int64_t nullValue) = 0;
        virtual void bind(const std::string& key, bool value, bool nullValue) = 0;
        virtual void bind(const std::string& key, double value, double nullValue) = 0;
        virtual void bind(const std::string& key, const std::string& value, std::string nullValue) = 0;
        virtual void bind(const std::string& key, const char* value, const char* nullValue)  = 0;
        virtual void bindBlob(const std::string& key, const std::vector<unsigned char>& value, std::vector<unsigned char> nullValue) = 0;
        virtual void bindAndAppend(const std::string& appendedQuery, const std::string& key, int32_t value) = 0;
        virtual void bindAndAppend(const std::string& appendedQuery, const std::string& key, int64_t value) = 0;
        virtual void bindAndAppend(const std::string& appendedQuery, const std::string& key, bool value) = 0;
        virtual void bindAndAppend(const std::string& appendedQuery, const std::string& key, double value) = 0;
        virtual void bindAndAppend(const std::string& appendedQuery, const std::string& key, const std::string& value) = 0;
        virtual void bindAndAppend(const std::string& appendedQuery, const std::string& key, const char* value) = 0;
        virtual void bindBlobAndAppend(const std::string& appendedQuery, const std::string& key, const std::vector<unsigned char>& value) = 0;
        virtual void bindAndAppend(const std::string& appendedQuery, const std::string& key, int32_t value, int32_t nullValue) = 0;
        virtual void bindAndAppend(const std::string& appendedQuery, const std::string& key, int64_t value, int64_t nullValue) = 0;
        virtual void bindAndAppend(const std::string& appendedQuery, const std::string& key, bool value, bool nullValue) = 0;
        virtual void bindAndAppend(const std::string& appendedQuery, const std::string& key, double value, double nullValue) = 0;
        virtual void bindAndAppend(const std::string& appendedQuery, const std::string& key, const std::string& value, std::string nullValue) = 0;
        virtual void bindAndAppend(const std::string& appendedQuery, const std::string& key, const char * value, const char * nullValue) = 0;
        virtual void bindBlobAndAppend(const std::string& appendedQuery, const std::string& key, const std::vector<unsigned char>& value, std::vector<unsigned char> nullValue) = 0;
    };
}
