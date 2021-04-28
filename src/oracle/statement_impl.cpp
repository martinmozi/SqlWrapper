#include "statement_impl.h"
#include <stdexcept>
#include "error_impl.h"
#include <string.h>

namespace OracleImpl
{
    Statement::Statement(dpiConn* conn)
    :   conn_(conn)
    {
    }

    dpiStmt* Statement::execute()
    {
        dpiStmt *stmt = nullptr;
        if (dpiConn_prepareStmt(conn_, 0, query_.c_str(), query_.size(), NULL, 0, &stmt) < 0)
            throw std::runtime_error(oracleErrorMsg());

        const std::vector<DbImpl::BindData>& data = DbImpl::Statement::data();
        try
        {
            dpiData bindValue;
            for (const DbImpl::BindData& _data : data)
            {
                bindValue.isNull = 0;
                switch (_data.type_)
                {
                case DbImpl::DataType::Null:
                    bindValue.isNull = 1;
                    if (dpiStmt_bindValueByName(stmt, _data.name_.c_str(), _data.name_.size(), DPI_NATIVE_TYPE_NULL, &bindValue) < 0)
                        throw std::runtime_error(oracleErrorMsg());
                    break;

                case DbImpl::DataType::Bool:
                    bindValue.value.asBoolean = (_data.value<bool>()) ? 1 : 0;
                    if (dpiStmt_bindValueByName(stmt, _data.name_.c_str(), _data.name_.size(), DPI_NATIVE_TYPE_BOOLEAN, &bindValue) < 0)
                        throw std::runtime_error(oracleErrorMsg());

                    break;

                case DbImpl::DataType::Int:
                    bindValue.value.asInt64 = _data.value<int32_t>();
                    if (dpiStmt_bindValueByName(stmt, _data.name_.c_str(), _data.name_.size(), DPI_NATIVE_TYPE_INT64, &bindValue) < 0)
                        throw std::runtime_error(oracleErrorMsg());
                    break;

                case DbImpl::DataType::BigInt:
                    bindValue.value.asInt64 = _data.value<int64_t>();
                    if (dpiStmt_bindValueByName(stmt, _data.name_.c_str(), _data.name_.size(), DPI_NATIVE_TYPE_INT64, &bindValue) < 0)
                        throw std::runtime_error(oracleErrorMsg());
                    break;

                case DbImpl::DataType::Double:
                    bindValue.value.asInt64 = _data.value<double>();
                    if (dpiStmt_bindValueByName(stmt, _data.name_.c_str(), _data.name_.size(), DPI_NATIVE_TYPE_DOUBLE, &bindValue) < 0)
                        throw std::runtime_error(oracleErrorMsg());
                    break;

                case DbImpl::DataType::String:
                    {
                        const auto& d = _data.value<std::string>();
                        bindValue.value.asBytes.encoding = "UTF-8";
                        bindValue.value.asBytes.length = d.size();
                        bindValue.value.asBytes.ptr = (char*)d.data();
                        if (dpiStmt_bindValueByName(stmt, _data.name_.c_str(), _data.name_.size(), DPI_NATIVE_TYPE_BYTES, &bindValue) < 0)
                            throw std::runtime_error(oracleErrorMsg());
                    }
                    break;

                case DbImpl::DataType::Blob:
                    {
                        const auto & d = _data.value<std::vector<unsigned char>>();
                        bindValue.value.asBytes.ptr = (char*)d.data();
                        bindValue.value.asBytes.length = d.size();
                        bindValue.value.asBytes.encoding = "UTF-8";
                        if (dpiStmt_bindValueByName(stmt, _data.name_.c_str(), _data.name_.size(), DPI_NATIVE_TYPE_LOB, &bindValue) < 0)
                            throw std::runtime_error(oracleErrorMsg());
                    }
                    break;

                default:
                    throw std::runtime_error("Unsupported binding parameter type");
                }
            }
        }
        catch (std::exception & ex)
        {
            dpiStmt_release(stmt);
            throw std::runtime_error(ex.what());
        }

        return stmt;
    }
}