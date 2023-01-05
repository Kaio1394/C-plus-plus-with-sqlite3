#include <iostream>
#include "sqlite3.h"

using namespace std;
typedef string STR;

static int callback(void*, int, char**, char**);
void COMMAND_SQL(sqlite3* DB, STR sql, STR data);

int main()
{
	sqlite3* DB;
	bool connect = sqlite3_open("termina-root.db", &DB);

	STR data("CALLBACK FUNCTION");
	STR sql("SELECT * FROM dados");
	STR nome, sobrenome;

	while (true) {
		char yesorNo;
		cout << "Entre com o nome: " << endl;
		cin >> nome;
		cout << "Entre com o sobrenome: " << endl;
		cin >> sobrenome;
		STR sql_command("INSERT INTO dados (nome, sobrenome) VALUES ('"+nome+"', '"+sobrenome+"');");
		cout << "Gostaria de adicionar mais nomes?S/N" << endl;
		cin >> yesorNo;
		COMMAND_SQL(DB, sql_command, data);
		if (yesorNo == 'N')
			break;
	}
	COMMAND_SQL(DB, sql, data);
	sqlite3_close(DB);

	return 0;
}
void COMMAND_SQL(sqlite3* DB, STR sql, STR data) {
	int rc = sqlite3_exec(DB, sql.c_str(), callback, (void*)data.c_str(), NULL);
	
	if (rc != SQLITE_OK) {
		cerr << "Comando não foi executado." << endl;
	}
	
}
static int callback(void* data, int argc, char** argv, char** az_col_name) {
	for (size_t i = 0; i < argc; ++i)
	{
		cout << argv[i] << " ";
	}
	cout << endl;
	return 0;
}