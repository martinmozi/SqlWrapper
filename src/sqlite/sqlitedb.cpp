/*
sqlite3* conn;
sqlite3_stmt* stmt = 0;

int rc = sqlite3_open(db_name, &conn);
//  Good idea to always check the return value of sqlite3 function calls. 
//  Only done once in this example:
if ( rc != SQLITE_OK ) { // Do something }

rc = sqlite3_prepare_v2( conn, "SELECT id FROM myTable WHERE id = ? or id = ?", -1, &stmt, 0 );

//  Optional, but will most likely increase performance.
rc = sqlite3_exec( conn, "BEGIN TRANSACTION", 0, 0, 0 );    

for ( int bindIndex = 0; bindIndex < number_of_times_you_wish_to_bind; bindIndex++ ) {
    //  Binding integer values in this example.
    //  Bind functions for other data-types are available - see end of post.

    //  Bind-parameter indexing is 1-based.
    rc = sqlite3_bind_int( stmt, 1, int_you_wish_to_bind ); // Bind first parameter.
    rc = sqlite3_bind_int( stmt, 2, int_you_wish_to_bind ); // Bind second parameter.

    //  Reading interger results in this example.
    //  Read functions for other data-types are available - see end of post.
    while ( sqlite3_step( stmt ) == SQLITE_ROW ) { // While query has result-rows.
        //  In your example the column count will be 1.
        for ( int colIndex = 0; colIndex < sqlite3_column_count( stmt ); colIndex++ ) { 
            int result = sqlite3_column_int( stmt, colIndex );
            //  Do something with the result.
        }
    }
    //  Step, Clear and Reset the statement after each bind.
    rc = sqlite3_step( stmt );
    rc = sqlite3_clear_bindings( stmt );
    rc = sqlite3_reset( stmt );
}
char *zErrMsg = 0;  //  Can perhaps display the error message if rc != SQLITE_OK.
rc = sqlite3_exec( conn, "END TRANSACTION", 0, 0, &zErrMsg );   //  End the transaction.

rc = sqlite3_finalize( stmt );  //  Finalize the prepared statement.
*/
