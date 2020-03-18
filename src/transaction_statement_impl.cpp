#include "transaction_statement_impl.h"

namespace DbImpl
{
    TransactionStatement::TransactionStatement(std::unique_ptr<Transaction> transaction)
    :   transaction_(std::move(transaction))
    {
        transaction_->begin();
    }

    TransactionStatement::~TransactionStatement()
    {
        transaction_->rollback();
    }

    void TransactionStatement::begin()
    {
        transaction_->begin();
    }

    void TransactionStatement::commit()
    {
        transaction_->commit();
    }

    void TransactionStatement::rollback()
    {
        transaction_->rollback();
    }
}
