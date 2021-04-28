#include "transaction_impl.h"
#include "error_impl.h"

namespace OracleImpl
{
    Transaction::Transaction(dpiConn* conn)
        : conn_(conn)
    {
    }

    void Transaction::_begin()
    {
       // in oracle without starting transaction
    }

    void Transaction::_commit()
    {
        if (dpiConn_commit(conn_) < 0)
            throw std::runtime_error(oracleErrorMsg());
    }

    void Transaction::_rollback()
    {
        if (dpiConn_rollback(conn_) < 0)
            throw std::runtime_error(oracleErrorMsg());
    }
}
