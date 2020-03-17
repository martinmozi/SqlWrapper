#include "statement_impl.h"
#include <stdexcept>

namespace SqliteImpl
{
    Statement::Statement(sqlite3* conn)
    :   conn_(conn)
    {
    }

    sqlite3_stmt * Statement::execute()
    {
        sqlite3_stmt *stmt;
        const std::vector<DbImpl::Statement::Data>& data = DbImpl::Statement::data();
        if (sqlite3_prepare_v2(conn_, "SELECT id FROM myTable WHERE id = ? or id = ?", -1, &stmt, 0) != SQLITE_OK)
            throw std::runtime_error(sqlite3_errmsg(conn_));

        for (const DbImpl::Statement::Data& _data : data)
        {
            std::string paramName = std::string(":") + _data.name_;
            switch (_data.type_)
            {
            case DbImpl::DataType::Null:
                sqlite3_bind_null(stmt, sqlite3_bind_parameter_index(stmt, paramName.c_str()));
                break;

            case DbImpl::DataType::Bool:
                sqlite3_bind_int(stmt, sqlite3_bind_parameter_index(stmt, paramName.c_str()), (_data.value<bool>()) ? 1 : 0);
                break;

            case DbImpl::DataType::Int:
                sqlite3_bind_int(stmt, sqlite3_bind_parameter_index(stmt, paramName.c_str()), _data.value<int32_t>());
                break;

            case DbImpl::DataType::BigInt:
                sqlite3_bind_int64(stmt, sqlite3_bind_parameter_index(stmt, paramName.c_str()), _data.value<int64_t>());
                break;

            case DbImpl::DataType::Double:
                sqlite3_bind_double(stmt, sqlite3_bind_parameter_index(stmt, paramName.c_str()), _data.value<double>());
                break;

            case DbImpl::DataType::String:
               // sqlite3_bind_text(stmt, sqlite3_bind_parameter_index(stmt, paramName.c_str()), std::any_cast<double>(_data.value));
                break;

            case DbImpl::DataType::Blob:
            {
                /*size_t outLength = 0;
                auto dataVector = std::any_cast<std::vector<unsigned char>>(_data.value);
                unsigned char* dataStr = PQescapeByteaConn(conn_, dataVector.data(), dataVector.size(), &outLength);
                if (dataStr == nullptr)
                {
                    throw std::runtime_error("Unable to escape blob");
                }
                else
                {
                    std::string _str((const char*)dataStr, outLength);
                    appendStringPqBind(_str.c_str(), values, lengths, binaries);
                    PQfreemem(dataStr);
                }*/
            }
            break;

            default:
                //bError = true;
                break;

            }
        }

        int rc = sqlite3_step(stmt);
       // rc = sqlite3_clear_bindings(stmt);
       // rc = sqlite3_reset(stmt);

      /*  if (bError)
            throw std::runtime_error("Unsupported binding parameter type");*/

        return stmt;
    }
}