/*
	___________________________________________
	Funkcje obslugi baz danych SQL i MySQL. 
	Za ich pomoca mozliwe jest tworzenie jednego spojnego kodu dla dwoch typow baz danych.
	___________________________________________
	
	___________________________________________
	UseMySQL() - Funkcja sprawdzajaca czy baza danych MySQL zostala poprawnie wlaczona.
		Zwracane wartosci: 1 - Baza danych MySQL aktywna, 0 - Baza danych MySQL nieaktywna.
	___________________________________________
	DBResult:sendQuery(query[], bool:forceSQL = false) - Funkcja wysylajaca zapytanie do bazy danych, oraz zwracajaca jego wynik. Parametr 'forceSQL' z wartoscia 'true' pozwala na wymuszenie wykonania zapytania dla bazy SQL.
		Zwracane wartosci: Wynik zapytania.
	___________________________________________
	freeResult(DBResult:result) - Funkcja czyszczaca wynik ostatniego zapytania do bazy danych.
		Zwracane wartości: 1.
	___________________________________________
	numRows(DBResult:result) - Funkcja zwracająca ilość wierszy uzyskanych w wyniku wykonania ostatniego zapytania.
		Zwracane wartości: Ilość wierszy z zapytania.
	___________________________________________
	nextRow(DBResult:result) - Funkcja przechodząca do następnego wiersza w wyniku ostatniego zapytania.
		Zwracane watrtości: 1.
	___________________________________________
	getFieldAssoc_x (x = 8, 16, 32, 64, 128) - Funkcja zwracająca wartość konkretnego pola w wyniku zapytania. X w nazwie funkcji określa maksymalny rozmiar rezultatu.
		Zwracane wartości - Wynik w poszukiwanym polu ostatniego zapytania.
	___________________________________________
*/
//===============================================================
//---------------------------------------------------------------
//===============================================================
UseMySQL() {
	return (getSettingIntValueByIndex(s_MySQLID) == 1 and _:MySQLID != 0) ? _TRUE : _FALSE;
}
//---------------------------------------------------------------

sendQueryWithout(query[], bool:forceSQL = false) {
	if(!isnull(query)) {
		if(UseMySQL() == _TRUE and forceSQL == false) {
			if(sql_ping(MySQLID) != 0) {
				MySQLID = sql_connect(SQL_HANDLER_MYSQL, MYSQL_HOST, MYSQL_USER, MYSQL_PASSWORD, MYSQL_DATABASE);
				sql_set_charset(MySQLID, "utf8");		
			}
			sql_query(MySQLID, query);
		} else {
			db_query(dbase, query);
		}
	}
	return 1;
}

//---------------------------------------------------------------

DBResult:sendQueryResult(query[], &Result:sql_result, bool:forceSQL = false) {
	new DBResult:result;
	if(!isnull(query)) {
		if(UseMySQL() == _TRUE and forceSQL == false) {
			if(sql_ping(MySQLID) != 0) {
				MySQLID = sql_connect(SQL_HANDLER_MYSQL, MYSQL_HOST, MYSQL_USER, MYSQL_PASSWORD, MYSQL_DATABASE);
				sql_set_charset(MySQLID, "utf8");		
			}
			sql_result = sql_query(MySQLID, query);
			sql_store_result(sql_result);
		} else {
			result = db_query(dbase, query);
		}
	}
	return result;
}
//---------------------------------------------------------------
nextRow(DBResult:result, Result:sql_result) {
	if(UseMySQL() == _TRUE) {
		sql_next_row(sql_result);
	} else {
		db_next_row(result);
	}
	return _TRUE;
}
//---------------------------------------------------------------
freeResult(DBResult:result, Result:sql_result) {
	if(UseMySQL() == _TRUE) {
		sql_free_result(sql_result);
	} else {
		db_free_result(result);
	}
	return _TRUE;
}
//---------------------------------------------------------------
numRows(DBResult:result, Result:sql_result) {
	if(UseMySQL() == _TRUE) {
		return sql_num_rows(sql_result);
	} else {
		return db_num_rows(result);
	}
}
//---------------------------------------------------------------
stock getFieldAssoc_256(field_name[], DBResult:result, Result:sql_result) {
	new s_result[256];
	if(!isnull(field_name)) {
		if(UseMySQL() == _TRUE) {
			mysql_fetch_field(field_name, s_result, MySQLID);
		} else {
			db_get_field_assoc(result, field_name, s_result, sizeof(s_result));
		}
	}
	return s_result;
}
//---------------------------------------------------------------
stock getFieldAssoc_128(field_name[], DBResult:result, Result:sql_result) {
	new s_result[128];
	if(!isnull(field_name)) {
		if(UseMySQL() == _TRUE) {
			sql_get_field_assoc(sql_result, field_name, s_result, sizeof(s_result));
		} else {
			db_get_field_assoc(result, field_name, s_result, sizeof(s_result));
		}
	}
	return s_result;
}
//---------------------------------------------------------------
stock getFieldAssoc_64(field_name[], DBResult:result, Result:sql_result) {
	new s_result[64];
	if(!isnull(field_name)) {
		if(UseMySQL() == _TRUE) {
			sql_get_field_assoc(sql_result, field_name, s_result, sizeof(s_result));
		} else {
			db_get_field_assoc(result, field_name, s_result, sizeof(s_result));
		}
	}
	return s_result;
}
//---------------------------------------------------------------
stock getFieldAssoc_32(field_name[], DBResult:result, Result:sql_result) {
	new s_result[32];
	if(!isnull(field_name)) {
		if(UseMySQL() == _TRUE) {
			sql_get_field_assoc(sql_result, field_name, s_result, sizeof(s_result));
		} else {
			db_get_field_assoc(result, field_name, s_result, sizeof(s_result));
		}
	}
	return s_result;
}
//---------------------------------------------------------------
stock getFieldAssoc_16(field_name[], DBResult:result, Result:sql_result) {
	new s_result[16];
	if(!isnull(field_name)) {
		if(UseMySQL() == _TRUE) {
			sql_get_field_assoc(sql_result, field_name, s_result, sizeof(s_result));
		} else {
			db_get_field_assoc(result, field_name, s_result, sizeof(s_result));
		}
	}
	return s_result;
}
//---------------------------------------------------------------
stock getFieldAssoc_8(field_name[], DBResult:result, Result:sql_result) {
	new s_result[8];
	if(!isnull(field_name)) {
		if(UseMySQL() == _TRUE) {
			sql_get_field_assoc(sql_result, field_name, s_result, sizeof(s_result));
		} else {
			db_get_field_assoc(result, field_name, s_result, sizeof(s_result));
		}
	}
	return s_result;
}