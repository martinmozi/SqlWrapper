#include "statement_impl.h"

namespace SqliteImpl
{
    Statement::Statement(sqlite3* conn)
    :   conn_(conn)
    {
    }

   /* void Statement::exec()
    {
        
    }*/
}