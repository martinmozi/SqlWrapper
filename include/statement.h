#pragma once

#include <optional>

namespace Sql
{
	// todo remove optionals here
    class Statement
	{
	public:
		virtual void exec() = 0;
		virtual void prepare(const std::string & query) = 0;
		virtual void append(const std::string & appendQuery) = 0;
		virtual void bind(const std::string & key, int32_t value, std::optional<int32_t> nullValue = {}) = 0;
		virtual void bind(const std::string & key, int64_t value, std::optional<int64_t> nullValue = {}) = 0;
		virtual void bind(const std::string & key, bool value, std::optional<bool> nullValue = {}) = 0;
		virtual void bind(const std::string & key, double value, std::optional<double> nullValue = {}) = 0;
		virtual void bind(const std::string & key, const std::string & value, std::optional<std::string> nullValue = {}) = 0;
		virtual void bindBlob(const std::string & key, const std::string & value, std::optional<std::string> nullValue = {}) = 0;
		virtual void bindAndAppend(const std::string & appendedQuery, const std::string & key, int32_t value, std::optional<int> nullValue = {}) = 0;
		virtual void bindAndAppend(const std::string & appendedQuery, const std::string & key, int64_t value, std::optional<int64_t> nullValue = {}) = 0;
		virtual void bindAndAppend(const std::string & appendedQuery, const std::string & key, bool value, std::optional<bool> nullValue = {}) = 0;
		virtual void bindAndAppend(const std::string & appendedQuery, const std::string & key, double value, std::optional<double> nullValue = {}) = 0;
		virtual void bindAndAppend(const std::string & appendedQuery, const std::string & key, const std::string & value, std::optional<std::string> nullValue = {}) = 0;
		virtual void bindBlobAndAppend(const std::string & appendedQuery, const std::string & key, const std::string & value, std::optional<std::string> nullValue = {}) = 0;
    };
}
