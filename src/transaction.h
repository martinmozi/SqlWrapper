#pragma once

namespace DbImpl
{
    class Transaction
    {
    public:
        Transaction();
        virtual ~Transaction() = default;
        void begin();
        void commit();
        void rollback();

    protected:
        virtual void _begin() = 0;
        virtual void _commit() = 0;
        virtual void _rollback() = 0;

    private:
        bool bRunningTransaction_;
    };
}
