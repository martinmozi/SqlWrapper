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
        const std::vector<DbImpl::BindData>& data = DbImpl::Statement::data();
        if (sqlite3_prepare_v2(conn_, query_.c_str(), -1, &stmt, 0) != SQLITE_OK)
            throw std::runtime_error(sqlite3_errmsg(conn_));

        try
        {
            for (const DbImpl::BindData& _data : data)
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
                    {
                        const auto& d = _data.value<std::string>();
                        sqlite3_bind_text(stmt, sqlite3_bind_parameter_index(stmt, paramName.c_str()), d.c_str(), d.size(), SQLITE_TRANSIENT);
                    }
                    break;

                case DbImpl::DataType::Blob:
                    {
                        const auto & d = _data.value<std::vector<unsigned char>>();
                        sqlite3_bind_blob(stmt, sqlite3_bind_parameter_index(stmt, paramName.c_str()), d.data(), d.size(), SQLITE_TRANSIENT);
                    }
                    break;

                default:
                    throw std::runtime_error("Unsupported binding parameter type");
                }
            }
        }
        catch (std::exception & ex)
        {
            sqlite3_clear_bindings(stmt);
            sqlite3_reset(stmt);
            throw std::runtime_error(ex.what());
        }

        return stmt;
    }
}