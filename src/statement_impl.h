#include <any>
#include <vector>
#include <string>
#include "../include/statement.h"

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
        Statement() {}
        virtual ~Statement() {}

        void prepare(const std::string& query) override;
        void append(const std::string& appendQuery) override;
        void bind(const std::string& key, int32_t value, std::optional<int32_t> nullValue = {}) override;
        void bind(const std::string& key, int64_t value, std::optional<int64_t> nullValue = {}) override;
        void bind(const std::string& key, bool value, std::optional<bool> nullValue = {}) override;
        void bind(const std::string& key, double value, std::optional<double> nullValue = {}) override;
        void bind(const std::string& key, const std::string& value, std::optional<std::string> nullValue = {}) override;
        void bindBlob(const std::string& key, const std::string& value, std::optional<std::string> nullValue = {}) override;
        void bindAndAppend(const std::string& appendedQuery, const std::string& key, int32_t value, std::optional<int> nullValue = {}) override;
        void bindAndAppend(const std::string& appendedQuery, const std::string& key, int64_t value, std::optional<int64_t> nullValue = {}) override;
        void bindAndAppend(const std::string& appendedQuery, const std::string& key, bool value, std::optional<bool> nullValue = {}) override;
        void bindAndAppend(const std::string& appendedQuery, const std::string& key, double value, std::optional<double> nullValue = {}) override;
        void bindAndAppend(const std::string& appendedQuery, const std::string& key, const std::string& value, std::optional<std::string> nullValue = {}) override;
        void bindBlobAndAppend(const std::string& appendedQuery, const std::string& key, const std::string& value, std::optional<std::string> nullValue = {}) override;

    private:
        template<class T> void bindData(const std::string& key, const T& value, std::optional<T> nullValue, DataType type)
        {
            Data data;
            data.name = key;
            if (nullValue && *nullValue == value)
            {
                //tuto to nefunguje
    //				2018-04-08 16:40:09 CEST ERROR:  bind message supplies 3 parameters, but prepared statement "" requires 4
    //				2018-04-08 16:40:09 CEST STATEMENT:  INSERT INTO draft_participants(id, draftid, addressid, address, type) VALUES(nextval('seq_draft_participants') , $1, $4, $2, $3)

                data.type = DataType::Null;
            }
            else
            {
                data.type = type;
                data.value = value;
            }

            data_.push_back(data);
        }
    };
}