#include "transaction.h"

namespace DbImpl
{
    Transaction::Transaction()
    :   bRunningTransaction_(false)
    {
    }

    void Transaction::begin()
    {
        if (!bRunningTransaction_)
            _begin();

        bRunningTransaction_ = true;
    }

    void Transaction::commit()
    {
        if (bRunningTransaction_)
            _commit();

        bRunningTransaction_ = false;
    }

    void Transaction::rollback()
    {
        if (bRunningTransaction_)
            _rollback();

        bRunningTransaction_ = false;
    }
}
