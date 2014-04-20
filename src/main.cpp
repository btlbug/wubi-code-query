#include <iostream>
#include <sqlite3.h>
#include <string>
#include <cstring>
#include <sstream>
using namespace std;

inline char fetch_char(char *str){
	if(str != NULL && strlen(str) > 0){
		istringstream strin(str);
		int i = 0;
		strin >> i;
		return (char)('a' + i - 1);
	}
	return '\0';
}
static int _callback_exec(void *notused, int argc, char **argv, char **aszColName){
		cout << fetch_char(argv[1])
			<< fetch_char(argv[2])
			<< fetch_char(argv[3])
			<< fetch_char(argv[4]) << endl;
	return 0;
}
int main(int argc, char **argv){
	const char *file = "wubi-jidian86.db";
	stringstream sql;
	sql <<  "select * from goucima where zi=";
	char *pErrMsg = 0;
	int ret = 0;
	sqlite3 *db = NULL;
	ret = sqlite3_open(file, &db);
	if(ret != SQLITE_OK){
		cerr << "Could not open database: " << sqlite3_errmsg(db) << endl;
		return 1;
	}	
	cout << "Connected to the wubi database." << endl;
	if ( argc > 1 ){
		cout << "query char: " << argv[1] << endl;
		sql << "'" << argv[1] << "';";
	}
	ret = sqlite3_exec(db, sql.str().c_str(),  _callback_exec, NULL, &pErrMsg);
	if( ret != SQLITE_OK){
		cerr << "SQL Query error: " << pErrMsg << endl;
		sqlite3_free(pErrMsg);
	}
	sqlite3_close(db);
	db = NULL;
	return 0;
}
