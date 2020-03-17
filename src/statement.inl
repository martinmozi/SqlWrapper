void prepare(const std::string& query) override { statement_.prepare(query); }
void append(const std::string& appendQuery) override { statement_.append(appendQuery); }
void bind(const std::string& key, int32_t value) override { statement_.bind(key, value); }
void bind(const std::string& key, int64_t value) override { statement_.bind(key, value); }
void bind(const std::string& key, bool value) override { statement_.bind(key, value); }
void bind(const std::string& key, double value) override { statement_.bind(key, value); }
void bind(const std::string& key, const std::string& value) override { statement_.bind(key, value); }
void bind(const std::string& key, const char* value) override { statement_.bind(key, value); }
void bindBlob(const std::string& key, const std::vector<unsigned char>& value) override { statement_.bindBlob(key, value); }
void bind(const std::string& key, int32_t value, int32_t nullValue) override { statement_.bind(key, value, nullValue); }
void bind(const std::string& key, int64_t value, int64_t nullValue) override { statement_.bind(key, value, nullValue); }
void bind(const std::string& key, bool value, bool nullValue) override { statement_.bind(key, value, nullValue); }
void bind(const std::string& key, double value, double nullValue) override { statement_.bind(key, value, nullValue); }
void bind(const std::string& key, const std::string& value, std::string nullValue) override { statement_.bind(key, value, nullValue); }
void bind(const std::string& key, const char* value, const char* nullValue) override { statement_.bind(key, value, nullValue); }
void bindBlob(const std::string& key, const std::vector<unsigned char>& value, std::vector<unsigned char> nullValue) override { statement_.bindBlob(key, value, nullValue); }
void bindAndAppend(const std::string& appendedQuery, const std::string& key, int32_t value) override { statement_.bindAndAppend(appendedQuery, key, value); }
void bindAndAppend(const std::string& appendedQuery, const std::string& key, int64_t value) override { statement_.bindAndAppend(appendedQuery, key, value); }
void bindAndAppend(const std::string& appendedQuery, const std::string& key, bool value) override { statement_.bindAndAppend(appendedQuery, key, value); }
void bindAndAppend(const std::string& appendedQuery, const std::string& key, double value) override { statement_.bindAndAppend(appendedQuery, key, value); }
void bindAndAppend(const std::string& appendedQuery, const std::string& key, const std::string& value) override { statement_.bindAndAppend(appendedQuery, key, value); }
void bindAndAppend(const std::string& appendedQuery, const std::string& key, const char* value) override { statement_.bindAndAppend(appendedQuery, key, value); }
void bindBlobAndAppend(const std::string& appendedQuery, const std::string& key, const std::vector<unsigned char>& value) override { statement_.bindBlobAndAppend(appendedQuery, key, value); }
void bindAndAppend(const std::string& appendedQuery, const std::string& key, int32_t value, int32_t nullValue) override { statement_.bindAndAppend(appendedQuery, key, value, nullValue); }
void bindAndAppend(const std::string& appendedQuery, const std::string& key, int64_t value, int64_t nullValue) override { statement_.bindAndAppend(appendedQuery, key, value, nullValue); }
void bindAndAppend(const std::string& appendedQuery, const std::string& key, bool value, bool nullValue) override { statement_.bindAndAppend(appendedQuery, key, value, nullValue); }
void bindAndAppend(const std::string& appendedQuery, const std::string& key, double value, double nullValue) override { statement_.bindAndAppend(appendedQuery, key, value, nullValue); }
void bindAndAppend(const std::string& appendedQuery, const std::string& key, const std::string& value, std::string nullValue) override { statement_.bindAndAppend(appendedQuery, key, value, nullValue); }
void bindAndAppend(const std::string& appendedQuery, const std::string& key, const char* value, const char* nullValue) override { statement_.bindAndAppend(appendedQuery, key, value, nullValue); }
void bindBlobAndAppend(const std::string& appendedQuery, const std::string& key, const std::vector<unsigned char>& value, std::vector<unsigned char> nullValue) override { statement_.bindBlobAndAppend(appendedQuery, key, value, nullValue); }
