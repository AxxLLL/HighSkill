/*
	1) Admin Panel - Head
	2) Admin Panel - Last Disconnect List
	3) Admin Panel - Time Ban
	4) Admin Panel - Player Info
	5) Admin Panel - Prawdopodobne nicki gracza
*/
//===============================================================
//---------------------------------------------------------------
//===============================================================
/*
	Admin Panel - Head
*/
//===============================================================
//---------------------------------------------------------------
//===============================================================
CMD:apanel(playerid) {
	if(IsAdmin(playerid) != 0) {
		if(IsAdmin(playerid) > 0) {
			ShowNormalAdminPanel(playerid);
			return _TRUE;
		} else {
			return SendClientMessage(playerid, COLOR_DIALOG_BODY, " (Admin Panel) Musisz byc zalogowany(a) na konto administratora, zeby moc uzyc tej funkcji.");
		}
	}
	return _FALSE;
}
//===============================================================
ShowNormalAdminPanel(playerid, listitem = -1) {
	if(IsAdmin(playerid) > 0) {
		switch(listitem) {
			case 0: PlayerTBanMenuResponse(playerid);
			case 1: LastDisconnectList(playerid, 0);
			case 2: ShowPlayerInfoMenu(playerid);
			case 3: SetHelpVarValue(playerid, 50, 0), ShowPlayerNameCheckMenu(playerid);
			default: ShowPlayerDialogEx(playerid, DIALOG_ADMIN_PANEL, DIALOG_STYLE_LIST, "Admin Panel", "1) Lista banow czasowych\n2) Ostatnie wyjscia\n3) Sprawdz poprzednie nicki gracza (Konto)\n5) Sprawdz prawdopodobne poprzednie nicki gracza", "Dalej", "Wyjdz");
		}
		return _TRUE;
	}
	return _FALSE;
}
//===============================================================
//---------------------------------------------------------------
//===============================================================
/*
	Admin Panel - Last Disconnect List
*/
//===============================================================
//---------------------------------------------------------------
//===============================================================
LastDisconnectList(playerid, page, listitem = -1) {
	if(IsAdmin(playerid) > 0) {
		new string[512];
		if(listitem == -1) {
			new head[40],
				bool:nextpage;
			SetPlayerPage(playerid, page);
			if(page == 0) {
				for(new i; i < 10; i ++) {
					if(GetIntFromLDL(i, LDL_TIME) == 0) {
						if(i == 0) {
							ShowPlayerInfoDialog(playerid, BACK_NADMIN_PANEL, "Ostatnie wyjscia", "Brak informacji na temat ostatnich wyjsc z serwera.");
							return _TRUE;
						}					
						break;
					}
					format(string, sizeof(string), "%s\n%d) %s", string, i + 1, GetStringFromLDL(i));
				}				
				if(GetIntFromLDL(11, LDL_TIME) != 0) {
					nextpage = true; 
					strins(string, "\t\t\t>>> Nastepna strona >>>", 0);
				}
			} else {			
				nextpage = true;
				format(string, sizeof(string),"\t\t\t<<< Poprzednia strona <<<");
				for(new i = 10; i < 20; i ++) {
					if(GetIntFromLDL(i, LDL_TIME) == 0) {
						if(i == 10) {
							LastDisconnectList(playerid, 0);
							return _TRUE;
						}
						break;
					}
					format(string, sizeof(string), "%s\n%d) %s", string, i + 1, GetStringFromLDL(i));
				}			
			}
			format(head, sizeof(head), "Ostatnie wyjscia  ( Strona %d / %d )", page + 1, nextpage == true ? 2 : 1);
			ShowPlayerDialogEx(playerid, DIALOG_LDL, DIALOG_STYLE_LIST, head, string, "Sprawdz", "Wroc");
		} else {
			if(listitem == 0 and (page == 1 or GetIntFromLDL(11, LDL_TIME) != 0)) LastDisconnectList(playerid, page == 0 ? 1 : 0);
			else {				
				new index = (page == 0 ? (GetIntFromLDL(11, LDL_TIME) == 0 ? 1 : 0) : 10) + listitem - 1;

				if(GetIntFromLDL(index, LDL_TIME) != 0) {
					new year, month, day, hour, minute;
					
					dtimestamp(GetIntFromLDL(index, LDL_TIME), year, month, day, hour, minute);
					format(string, sizeof(string), "\
							Nick: "TEXT_DIALOG_NORMAL"%s "TEXT_DIALOG_HEAD"(User ID: "TEXT_DIALOG_NORMAL"%d"TEXT_DIALOG_HEAD")\n\
							Admin: "TEXT_DIALOG_NORMAL"%s"TEXT_DIALOG_HEAD"\n\
							IP: "TEXT_DIALOG_NORMAL"%s"TEXT_DIALOG_HEAD"\n\
							Opuscil(a) serwer: "TEXT_DIALOG_NORMAL"%s  "TEXT_DIALOG_HEAD"[ "TEXT_DIALOG_NORMAL"%d:%02d "TEXT_DIALOG_HEAD"]\
							",
						GetStringFromLDL(index),
						GetIntFromLDL(index, LDL_UID),
						GetAdminNameByLvL(GetIntFromLDL(index, LDL_ADMIN)),
						GetStringFromLDL(index, LDL_IP),
						strData(year, month, day, " / ", false, false, true, false), hour, minute
					);
					SetHelpVarValue(playerid, 1, index);
					SetHelpStringValue(playerid, 0, GetStringFromLDL(index));
					SetHelpVarValue(playerid, 0, listitem);
					ShowPlayerDialogEx(playerid, DIALOG_LDL_INFO, DIALOG_STYLE_MSGBOX, "Ostatnie wyjscia", string, "Zbanuj", "Wroc");
				} else ShowPlayerInfoDialog(playerid, BACK_LDL, "Ostatnie wyjscia", "Ten slot nie jest zapisany.");
			}
		}
		return _TRUE;		
	}
	return _FALSE;
}
//---------------------------------------------------------------
LastDisconnectListBanTime(playerid, time[] = "") {
	if(IsAdmin(playerid) > 0) {
		if(GetIntFromLDL(GetHelpVarValue(playerid, 1), LDL_ADMIN) >= IsAdmin(playerid)) {
			ShowPlayerInfoDialog(playerid, BACK_LDL_INFO, "Ostatnie wyjscia", "Nie mozesz zbanowac administratora wyszego, lub rownego ranga sobie.");
		} else {
			new string[200];
			new max_ban_min = (IsAdmin(playerid) == ALVL_JUNIOR_ADMIN ? getSettingIntValueByIndex(s_BanTimeJAdminID) : getSettingIntValueByIndex(s_BanTimeAdminID) * 60);
			if(!isnull(time)) {
				if(strlen(time) <= 6 and max_ban_min >= strval(time) > 0) {
					if(strcmp(GetStringFromLDL(GetHelpVarValue(playerid, 1)), GetHelpStringValue(playerid, 0)) == 0) {				
						SetHelpVarValue(playerid, 2, strval(time));
						LastDisconnectListBanReason(playerid);					
					} else {
						ShowPlayerInfoDialog(playerid, BACK_LDL, "Ostatnie wyjscia", "Dane dotyczace tego slotu zostaly zmienione.");
					}
					return _TRUE;
				} else strins(string, "\t    Niepoprawny czas trwania blokady", 0);	
			}
			format(string, sizeof(string), "Podaj czas trwania blokady. Dla Twojego poziomu praw\n  administratora maksymalny czas bana to "TEXT_DIALOG_NORMAL"%d "TEXT_DIALOG_HEAD"minut.\n\n"TEXT_DIALOG_ALERT"%s", max_ban_min, string);
			ShowPlayerDialogEx(playerid, DIALOG_LDL_BAN_TIME, DIALOG_STYLE_INPUT, "Ostatnie wyjscia", string, "Dalej", "Wroc");	
		}
		return _TRUE;
	}
	return _FALSE;
}
//---------------------------------------------------------------
LastDisconnectListBanReason(playerid, reason[] = "") {
	if(IsAdmin(playerid) > 0) {			
		new string[180];
		if(!isnull(reason)) {
			DeleteDoubleSpaces(reason);
			new length;
			if(3 <= (length = strlen(reason)) <= 120) {
				new bool:symbols = false;
				for(-- length; length >= 0; length --) {
					if(!(
						'a' <= reason[length] <= 'z' or 'A' <= reason[length] <= 'Z' or 
						'0' <= reason[length] <= '9' or reason[length] == ' ' or reason[length] == '_' or 
						reason[length] == '.' or reason[length] == ',' or reason[length] == '(' or 
						reason[length] == ')' or reason[length] == ']' or reason[length] == '[' or 
						reason[length] == '#' or reason[length] == '!' or reason[length] == '?' or
						reason[length] == ':' or reason[length] == '+' or reason[length] == '-')
					) {
						symbols = true;
						break;
					}
				}
				if(symbols == false) {
					if(strcmp(GetStringFromLDL(GetHelpVarValue(playerid, 1)), GetHelpStringValue(playerid, 0)) == 0) {	
						SetHelpStringValue(playerid, 1, reason);
						LastDisconnectListBanConfirm(playerid);
					} else {
						ShowPlayerInfoDialog(playerid, BACK_LDL, "Ostatnie wyjscia", "Dane dotyczace tego slotu zostaly zmienione.");
					}	
					return _TRUE;
				} else strins(string, "Powod blokady musi skladac sie wylacznie z liter i cyfr.", 0);				
			} else strins(string, "        Powod blokady musi zawierac sie w przedziale\n\t\t    od 3 do 120 znakow.", 0);
		}
		format(string, sizeof(string), "Podaj powod blokady w przedziale od "TEXT_DIALOG_NORMAL"3"TEXT_DIALOG_HEAD" do "TEXT_DIALOG_NORMAL"120"TEXT_DIALOG_HEAD" znakow.\n\n"TEXT_DIALOG_ALERT"%s", string);
		
		ShowPlayerDialogEx(playerid, DIALOG_LDL_BAN_REASON, DIALOG_STYLE_INPUT, "Ostatnie wyjscia", string, "Dalej", "Wroc");		
		return _TRUE;		
	}
	return _FALSE;
}
//---------------------------------------------------------------
LastDisconnectListBanConfirm(playerid, bool:confirm = false) {
	if(IsAdmin(playerid) > 0) {	
		new p_name[MAX_PLAYER_NAME];
		strins(p_name, GetStringFromLDL(GetHelpVarValue(playerid, 1)), 0);
		if(strcmp(p_name, GetHelpStringValue(playerid, 0)) == 0) {	
			new string[400];
			if(confirm == false) {
				new t_stamp = timestamp() + ToSeconds(GetHelpVarValue(playerid, 2), _MINUTE);
				new year, month, day, hour, minute;				
				dtimestamp(t_stamp, year, month, day, hour, minute);
				strins(string, GetHelpStringValue(playerid, 1), 0);
				if(strlen(string) > 55) strins(string, "\n", 54);
				format(string, sizeof(string), "Czy potwierdzasz chec zablokowania gracza '"TEXT_DIALOG_NORMAL"%s"TEXT_DIALOG_HEAD"' (UID: "TEXT_DIALOG_NORMAL"%d"TEXT_DIALOG_HEAD")\n\tdo "TEXT_DIALOG_NORMAL"%s"TEXT_DIALOG_HEAD"  [ "TEXT_DIALOG_NORMAL"%d:%02d"TEXT_DIALOG_HEAD" ] ( Czas trwania: "TEXT_DIALOG_NORMAL"%s"TEXT_DIALOG_HEAD" )?\n\nPowod: "TEXT_DIALOG_NORMAL"%s", 
					p_name,
					GetIntFromLDL(GetHelpVarValue(playerid, 1), LDL_UID),
					strData(year, month, day, " / ", false, false, true, false), hour, minute, convertSeconds(ToSeconds(GetHelpVarValue(playerid, 2), _MINUTE)), 
					string);	
				ShowPlayerDialogEx(playerid, DIALOG_LDL_BAN_CONFIRM, DIALOG_STYLE_MSGBOX, "Ostatnie wyjscia", string, "Tak", "Nie");
			} else {
				new host[8];
				strins(host, GetHostFromIP(GetStringFromLDL(GetHelpVarValue(playerid, 1), LDL_IP)), 0);
				format(string, sizeof(string), "Gracz '"TEXT_DIALOG_NORMAL"%s"TEXT_DIALOG_HEAD"' (Host: '"TEXT_DIALOG_NORMAL"%s"TEXT_DIALOG_HEAD"') zostal(a) dodany do Listy Banow Czasowych.", p_name, host);
				ShowPlayerInfoDialog(playerid, BACK_LDL, "Ostatnie wyjscia", string);
				AddToTimeBan(host, ToSeconds(GetHelpVarValue(playerid, 2), _MINUTE), GetIntFromLDL(GetHelpVarValue(playerid, 1), LDL_UID), p_name, getPlayerUserID(playerid), GetHelpStringValue(playerid, 1));
			}		
		} else {
			ShowPlayerInfoDialog(playerid, BACK_LDL, "Ostatnie wyjscia", "Dane dotyczace tego slotu zostaly zmienione.");
		}		
		return _TRUE;
	}
	return _FALSE;
}
//===============================================================
//---------------------------------------------------------------
//===============================================================
/*
	Admin Panel - Time Ban
*/
//===============================================================
//---------------------------------------------------------------
//===============================================================
PlayerTBanMenuResponse(playerid, listitem = -1) {
	if(IsAdmin(playerid) > 0) {
		switch(listitem) {
			case 0: PlayerTBanSearch(playerid);
			case 1: {
				SetHelpVarValue(playerid, 99, 0);
				ShowPlayerTimeBanList(playerid);
			}
			default: ShowPlayerDialogEx(playerid, DIALOG_TBAN_MENU, DIALOG_STYLE_LIST, "Bany czasowe", "1) Wyszukaj\n2) Lista banow", "Dalej", "Wroc");//
		}
		return _TRUE;
	}
	return _FALSE;
}
//===============================================================
PlayerTBanSearch(playerid, data[] = "") {
	if(IsAdmin(playerid) > 0) {
		new string[256];
		if(!isnull(data)) {			
			new type, date_from, date_to, bool:search_front, bool:search_end, bool:sorttype_desc, errorid;
			if(SearchDataSplit(data, type, date_from, date_to, search_front, search_end, sorttype_desc, errorid) == _TRUE) {
				switch(type) {
					case DATA_TYPE_NON: 	strins(string, "Niepoprawny typ danych do wyszukania.", 0);
					case DATA_TYPE_ONLINE, DATA_TYPE_IP: 	strins(string, "Ten typ wyszukiwania nie jest obslugiwany w tym menu.", 0);
					default: {
						SetHelpVarValue(playerid, 99, 1);
						SetHelpVarValue(playerid, 21, type);
						SetHelpVarValue(playerid, 22, date_from);
						SetHelpVarValue(playerid, 23, date_to);
						SetHelpVarValue(playerid, 24, _:search_front);
						SetHelpVarValue(playerid, 25, _:search_end);
						SetHelpVarValue(playerid, 26, _:sorttype_desc);
						SetHelpStringValue(playerid, 20, data);
						ShowPlayerTimeBanList(playerid);
						return _TRUE;
					}
				}
			} else {
				switch(errorid) {
					case DATA_ERROR_HELP: {
						ShowPlayerSearchInfo(playerid, SI_TIME_BAN);
						return _TRUE;
					}
					case DATA_ERROR_INVALID_LENGTH:		strins(string, "\t    Niepoprawne dane do wyszukania.", 0);
					case DATA_ERROR_INVALID_TYPE:		strins(string, "\tNiepoprawny typ danych do wyszukania.", 0);
					case DATA_ERROR_INVALID_SPECIAL:	strins(string, "          Niepoprawne znaki w danych do wyszukania.", 0);
					case DATA_ERROR_DATE_FROM:			strins(string, "Niepoprawna najwczesniejsza data danych do wyszukania.", 0);
					case DATA_ERROR_DATE_TO:			strins(string, "Niepoprawna najpozniejsza data danych do wyszukania.", 0);
					case DATA_ERROR_NO_TYPE:			strins(string, "           Niezdefiniowany typ danych do wyszukania.", 0);
					case DATA_ERROR_NO_DATA:			strins(string, "Brak danych do wyszukania.", 0);
					case DATA_ERROR_NO_MATCH_DATA_TYPE:	strins(string, "   Niepoprawne typ z formatem danych do wyszukania.", 0);
					case DATA_ERROR_INVALID_SORT_TYPE:	strins(string, "\t      Niepoprawny rodzaj sortowania.", 0);
				}
			}
		}		
		format(string, sizeof(string), "   Podaj interesujacy Cie typ danych pod katem, ktorych\nma zostac przeszukana baza danych 'Banow Czasowych'.\n   Info: Jesli nie wiesz jak poslugiwac sie wyszukiwarka,\n\t\twpisz polecenie '<INFO>'.\n\n"TEXT_DIALOG_ALERT"%s", string);
		ShowPlayerDialogEx(playerid, DIALOG_TBAN_SEARCH_MENU, DIALOG_STYLE_INPUT, "Bany czasowe - Wyszukiwarka", string, "Wyszukaj", "Wroc");
		
		return _TRUE;
	}	
	return _FALSE;
}
//---------------------------------------------------------------
TTimeBanMakeQuery(playerid, page) {
	new string[256];
	switch(GetHelpVarValue(playerid, 21)) {
		case DATA_TYPE_NICK: {
			strins(string, GetHelpStringValue(playerid, 20), 0);
			ConvertNick(string);
			format(string, sizeof(string), "SELECT `"TTB_UNIQUE_ID"`, `"TTB_PLAYER_NAME "`, `"TTB_ADMINID"`, `"TTB_HOST"` FROM `"T_TIME_BAN"` WHERE `"TTB_UNBANTIME"` > '%d' AND `"TTB_PLAYER_NAME"` LIKE '%s%s%s' AND `"TTB_DATE_STAMP"` >= '%d' AND `"TTB_DATE_STAMP"` <= '%d' ORDER BY `"TTB_DATE_STAMP"` %s LIMIT %d, 11", 
				timestamp(), 
				GetHelpVarValue(playerid, 24) == 1 ? ("%") : (""), string, GetHelpVarValue(playerid, 25) == 1 ? ("%") : (""), 
				GetHelpVarValue(playerid, 22), GetHelpVarValue(playerid, 23),						
				GetHelpVarValue(playerid, 26) == 0 ? ("ASC") : ("DESC"), 
				page * 10);
		}
		case DATA_TYPE_HOST: {
			format(string, sizeof(string), "SELECT `"TTB_UNIQUE_ID"`, `"TTB_PLAYER_NAME "`, `"TTB_ADMINID"`, `"TTB_HOST"` FROM `"T_TIME_BAN"` WHERE `"TTB_UNBANTIME"` > '%d' AND `"TTB_HOST"` LIKE '%s%s%s' AND `"TTB_DATE_STAMP"` >= '%d' AND `"TTB_DATE_STAMP"` <= '%d' ORDER BY `"TTB_DATE_STAMP"` %s LIMIT %d, 11", 
				timestamp(), 
				GetHelpVarValue(playerid, 24) == 1 ? ("%") : (""), GetHelpStringValue(playerid, 20), GetHelpVarValue(playerid, 25) == 1 ? ("%") : (""), 
				GetHelpVarValue(playerid, 22), GetHelpVarValue(playerid, 23),		
				GetHelpVarValue(playerid, 26) == 0 ? ("ASC") : ("DESC"),
				page * 10);				
		}
		case DATA_TYPE_USERID: {
			format(string, sizeof(string), "SELECT `"TTB_UNIQUE_ID"`, `"TTB_PLAYER_NAME "`, `"TTB_ADMINID"`, `"TTB_HOST"` FROM `"T_TIME_BAN"` WHERE `"TTB_UNBANTIME"` > '%d' AND `"TTB_UID"` = '%s' AND `"TTB_DATE_STAMP"` >= '%d' AND `"TTB_DATE_STAMP"` <= '%d' ORDER BY `"TTB_DATE_STAMP"` %s LIMIT %d, 11", 
				timestamp(), 
				GetHelpStringValue(playerid, 20),
				GetHelpVarValue(playerid, 22), GetHelpVarValue(playerid, 23),		
				GetHelpVarValue(playerid, 26) == 0 ? ("ASC") : ("DESC"),
				page * 10);					
		}
		case DATA_TYPE_ADMINID: {
			format(string, sizeof(string), "SELECT `"TTB_UNIQUE_ID"`, `"TTB_PLAYER_NAME "`, `"TTB_ADMINID"`, `"TTB_HOST"` FROM `"T_TIME_BAN"` WHERE `"TTB_UNBANTIME"` > '%d' AND `"TTB_ADMINID"` = '%s' AND `"TTB_DATE_STAMP"` >= '%d' AND `"TTB_DATE_STAMP"` <= '%d' ORDER BY `"TTB_DATE_STAMP"` %s LIMIT %d, 11", 
				timestamp(), 
				GetHelpStringValue(playerid, 20),
				GetHelpVarValue(playerid, 22), GetHelpVarValue(playerid, 23),	
				GetHelpVarValue(playerid, 26) == 0 ? ("ASC") : ("DESC"),
				page * 10);					
		}
		case DATA_TYPE_ADMIN_NICK: {
			strins(string, GetHelpStringValue(playerid, 20), 0);
			ConvertNick(string);
			format(string, sizeof(string), "SELECT `"TTB_UNIQUE_ID"`, `"TTB_PLAYER_NAME "`, `"TTB_ADMINID"`, `"TTB_HOST"` FROM `"T_TIME_BAN"` WHERE `"TTB_UNBANTIME"` > '%d' AND `"TTB_ADMIN_NAME"` LIKE '%s%s%s' AND `"TTB_DATE_STAMP"` >= '%d' AND `"TTB_DATE_STAMP"` <= '%d' ORDER BY `"TTB_DATE_STAMP"` %s LIMIT %d, 11", 
				timestamp(), 
				GetHelpVarValue(playerid, 24) == 1 ? ("%") : (""), string, GetHelpVarValue(playerid, 25) == 1 ? ("%") : (""), 
				GetHelpVarValue(playerid, 22), GetHelpVarValue(playerid, 23),	
				GetHelpVarValue(playerid, 26) == 0 ? ("ASC") : ("DESC"),
				page * 10);				
		}
	}
	return string;
}
//===============================================================
ShowPlayerTimeBanList(playerid, page = 0) {
	if(IsAdmin(playerid) > 0) {
		new string[800];		
		new DBResult: result, Result:sql_result;
		new rows;	
		new uadmin = getPlayerUserID(playerid); 
		new alvl = IsAdmin(playerid) < 0 ? -IsAdmin(playerid) : IsAdmin(playerid);
		if(page < 0) page = 0;
		
		if(GetHelpVarValue(playerid, 99) == 0) {		
			format(string, sizeof(string), "SELECT `"TTB_PLAYER_NAME "`, `"TTB_ADMINID"`, `"TTB_HOST"` FROM `"T_TIME_BAN"` WHERE `"TTB_UNBANTIME"` > '%d' ORDER BY `"TTB_DATE_STAMP"` DESC LIMIT %d, 11",
					timestamp(), page * 10);
		} else {
			strins(string, TTimeBanMakeQuery(playerid, page), 0);
		}
		result = sendQueryResult(string, sql_result);
		//_______________________	
		strdel(string, 0, 256);
		rows = numRows(result, sql_result);
		if(numRows(result, sql_result) > 0) {
			new bool:isNextPage = rows == 11 ? true : false;
			
			
			new nick[32];
			for(new i, limit = rows == 11 ? 10 : rows; i < limit; i ++) {
				strdel(nick, 0, MAX_PLAYER_NAME);
				strins(nick, getFieldAssoc_32(TTB_PLAYER_NAME, result, sql_result), 0);
				DeconvertNick(nick);
				format(string, sizeof(string), "%s\n%d) %s%s\t"TEXT_DIALOG_HEAD"[ "TEXT_DIALOG_NORMAL"%s"TEXT_DIALOG_HEAD" ]", string, page * 10 + i + 1, (strval(getFieldAssoc_16(TTB_ADMINID, result, sql_result)) == uadmin or alvl >= ALVL_HEAD_ADMIN ? (C_LIGHTGREEN) : ("") ), CutName(nick), getFieldAssoc_16(TTB_HOST, result, sql_result));
				nextRow(result, sql_result);
			}
			
			
			freeResult(result, sql_result);
			
			if(isNextPage == true) {
				strins(string, "\t\t\t>>> Nastepna strona >>>", 0);
			}

			if(page > 0) {
				if(isNextPage == true) strins(string, "\t\t\t<<< Poprzednia strona <<<\n", 0);
				else strins(string, "\t\t\t<<< Poprzednia strona <<<", 0);
			}
						
			SetPlayerPage(playerid, page);
			ShowPlayerDialogEx(playerid, DIALOG_ADMIN_TBAN_LIST, DIALOG_STYLE_LIST, "Bany czasowe - Lista", string, "Sprawdz", "Wroc");
			return _TRUE;
		} else {
			if(GetHelpVarValue(playerid, 99) == 0) {
				ShowPlayerInfoDialog(playerid, BACK_TIME_BAN_MENU, "Bany czasowe - Lista", "Brak banow, mamy dobrych graczy :)");	
			} else {
				ShowPlayerInfoDialog(playerid, BACK_TIME_SEARCH_MENU, "Bany czasowe - Wyszukiwarka", "Nieznaleziono rezultatow dla podanych danych.");	
			}
		}
		//_______________________
	}
	return _FALSE;
}
//---------------------------------------------------------------
TimeBanListResponse(playerid, listitem) {
	if(IsAdmin(playerid) > 0) {
		new DBResult: result, Result:sql_result;
		new rows;
		new string[350];		
		
		if(GetHelpVarValue(playerid, 99) == 0) {		
			format(string, sizeof(string), "SELECT `"TTB_UNIQUE_ID"` FROM `"T_TIME_BAN"` WHERE `"TTB_UNBANTIME"` > '%d' ORDER BY `"TTB_DATE_STAMP"` DESC LIMIT %d, 11",
					timestamp(), GetPlayerPage(playerid) * 10);
		} else {
			strins(string, TTimeBanMakeQuery(playerid, GetPlayerPage(playerid)), 0);
		}
		result = sendQueryResult(string, sql_result);
		rows = numRows(result, sql_result);
		if(rows > 0) {
			
			new bool:pvpage = GetPlayerPage(playerid) > 0 ? true : false;
			new bool:nxpage = rows == 11 ? true : false;
		
			if(listitem == 0 and (pvpage == true or nxpage == true)) {
				freeResult(result, sql_result);
				if(pvpage == true) ShowPlayerTimeBanList(playerid, GetPlayerPage(playerid) - 1);
				else {
					ShowPlayerTimeBanList(playerid, GetPlayerPage(playerid) + 1);
				}
			} else if(listitem == 1 and (pvpage == true and nxpage == true)) {
				freeResult(result, sql_result);
				ShowPlayerTimeBanList(playerid, GetPlayerPage(playerid) + 1);
			} else {
				new uniqueid;
				if(pvpage == true) listitem --;
				if(nxpage == true) listitem --;
		

				new index;
				new dest[8];
				for(index = 0; index < rows; index ++) {
					if(index == listitem) {
						if(UseMySQL() == 1) sql_get_field(sql_result, 0, dest, sizeof(dest));
						else db_get_field(result, 0, dest, sizeof(dest));
						uniqueid = strval(dest);
						break;
					}		
					nextRow(result, sql_result);
				}	
				
				freeResult(result, sql_result);

				format(string, sizeof(string), "SELECT `"TTB_HOST"`, `"TTB_UID"`, `"TTB_PLAYER_NAME"`, `"TTB_ADMINID"`, `"TTB_ADMIN_NAME"`, `"TTB_UNBANTIME"`, `"TTB_REASON"` FROM `"T_TIME_BAN"` WHERE `"TTB_UNIQUE_ID"`='%d' LIMIT 1", uniqueid);
				result = sendQueryResult(string, sql_result);
				if(numRows(result, sql_result) > 0) {				
					new p_name[MAX_PLAYER_NAME],
						userid = strval(getFieldAssoc_16(TTB_UID, result, sql_result)),
						host[8],
						a_name[MAX_PLAYER_NAME],
						adminid = strval(getFieldAssoc_16(TTB_ADMINID, result, sql_result)),
						unbantime = strval(getFieldAssoc_16(TTB_UNBANTIME, result, sql_result));			
						
					new ubtime[32], ub_hour, ub_minute;
					new year, month, day;
					
					strdel(string, 0, 256);
					strins(string, getFieldAssoc_128(TTB_REASON, result, sql_result), 0);	
					strins(host, getFieldAssoc_16(TTB_HOST, result, sql_result), 0);
					strins(p_name, getFieldAssoc_32(TTB_PLAYER_NAME, result, sql_result), 0);
					strins(a_name, getFieldAssoc_32(TTB_ADMIN_NAME, result, sql_result), 0);
					DeconvertNick(p_name);	
					DeconvertNick(a_name);	
					
					freeResult(result, sql_result);
					
					dtimestamp(unbantime, year, month, day, ub_hour, ub_minute);
					strins(ubtime, strData(year, month, day, " / ", false, false, true, false), 0);						
					
					if(strlen(string) > 54) strins(string, "\n", 54);					
					
					format(string, sizeof(string), "\	
						Unban time: "TEXT_DIALOG_NORMAL"%s  "TEXT_DIALOG_HEAD"[ "TEXT_DIALOG_NORMAL"%d:%02d "TEXT_DIALOG_HEAD"]\n\n\
						Powod: "TEXT_DIALOG_NORMAL"%s",
					ubtime, ub_hour, ub_minute,
					string);	
	
					format(string, sizeof(string), "\
						Nick: "TEXT_DIALOG_NORMAL"%s  "TEXT_DIALOG_HEAD"(UID: "TEXT_DIALOG_NORMAL"%d"TEXT_DIALOG_HEAD")\n\
						Host: "TEXT_DIALOG_NORMAL"%s"TEXT_DIALOG_HEAD"\n\
						Admin: "TEXT_DIALOG_NORMAL"%s  "TEXT_DIALOG_HEAD"(UID: "TEXT_DIALOG_NORMAL"%d"TEXT_DIALOG_HEAD")\n%s",
					p_name, userid,
					host,
					a_name, adminid,
					string);						

					if(adminid == getPlayerUserID(playerid) or IsAdmin(playerid) >= ALVL_HEAD_ADMIN) {
						SetHelpVarValue(playerid, 0, uniqueid);
						ShowPlayerDialogEx(playerid, DIALOG_ADMIN_UNBAN_TIME_LIST, DIALOG_STYLE_MSGBOX, "Bany czasowe", string, "Odbanuj", "Wroc");
					} else {
						ShowPlayerInfoDialog(playerid, BACK_TIME_BAN_LIST, "Bany czasowe - Info", string);	
					}				
				
					return _TRUE;			
				} else ShowPlayerInfoDialog(playerid, BACK_TIME_BAN_MENU, "Bany czasowe - Info", "Wystapil blad :( Daj znac komus kto moze to naprawic.");				
			}		
		} else ShowPlayerTimeBanList(playerid, 0);
	} 
	return _FALSE;
}
//---------------------------------------------------------------
TimeBanListUnban(playerid, bool:confirm = false) {
	if(IsAdmin(playerid) > 0) {
		new string[140];		
		if(confirm == true) {
			if(DeleteTimeBanByIndex(GetHelpVarValue(playerid, 0), getPlayerUserID(playerid)) == _TRUE) {				
				format(string, sizeof(string), "Ban dla gracza '"TEXT_DIALOG_NORMAL"%s"TEXT_DIALOG_HEAD"' zostal usuniety.\n\t    ( Ban Unique ID: "TEXT_DIALOG_NORMAL"%d"TEXT_DIALOG_HEAD" )",  GetHelpStringValue(playerid, 0), GetHelpVarValue(playerid, 0));			
				ShowPlayerInfoDialog(playerid, BACK_TIME_BAN_LIST, "Bany czasowe - Info", string);	
			} else ShowPlayerInfoDialog(playerid, BACK_TIME_BAN_LIST, "Bany czasowe - Info", "Nieznaleziono bana o podanym Unique ID");
		} else {		
			new DBResult: result, Result:sql_result;
			format(string, sizeof(string), "SELECT `"TTB_PLAYER_NAME "` FROM `"T_TIME_BAN"` WHERE `"TTB_UNIQUE_ID"`='%d' LIMIT 1", GetHelpVarValue(playerid, 0));
			result = sendQueryResult(string, sql_result);
			if(numRows(result, sql_result) > 0) {
				strdel(string, 0, 128);
				strins(string, getFieldAssoc_32(TTB_PLAYER_NAME, result, sql_result), 0);
				freeResult(result, sql_result);
				DeconvertNick(string);
				SetHelpStringValue(playerid, 0, string);
				format(string, sizeof(string),"Czy na pewno chcesz odbanowac gracza '"TEXT_DIALOG_NORMAL"%s"TEXT_DIALOG_HEAD"'?\n\t\t  (Ban Unique ID: "TEXT_DIALOG_NORMAL"%d"TEXT_DIALOG_HEAD")", string, GetHelpVarValue(playerid, 0));
				ShowPlayerDialogEx(playerid, DIALOG_ADMIN_UNBAN_TIME_LIST_2, DIALOG_STYLE_MSGBOX, "Bany czasowe - Info", string, "Tak", "Nie");
			} else ShowPlayerInfoDialog(playerid, BACK_TIME_BAN_LIST, "Bany czasowe - Info", "Nieznaleziono bana o podanym Unique ID");
		}
		return _TRUE;
	}
	return _FALSE;
}
//===============================================================
//---------------------------------------------------------------
//===============================================================
/*
	Admin Panel - Player Info
*/
//===============================================================
//---------------------------------------------------------------
//===============================================================
ShowPlayerInfoMenu(playerid, s_player[] = "") {
	if(IsAdmin(playerid) > 0) {
		new string[1024];
		setPlayerTabListInfo(playerid, TAB_LIST_APANEL_PLAYER_SEARCH);
		if(!isnull(s_player) and strlen(s_player) < MAX_PLAYER_NAME) {
			new checkID = INVALID_PLAYER_ID;
			if(isNumeric(s_player) == _TRUE) {
				if(!(MAX_PLAYERS > (checkID = strval(s_player)) >= 0)) checkID = INVALID_PLAYER_ID;
			} else {
				if(IsValidNick(s_player)) {
					forplayers(i) {
						if(strcmp(s_player, getPlayerName(i)) == 0) {
							checkID = i;
							break;
						}
					}
				}
			}
			if(checkID != INVALID_PLAYER_ID) {
				new userid;
				if((userid = getPlayerUserID(checkID)) > 0) {
					new DBResult: result, Result:sql_result;
					format(string, sizeof(string), "SELECT `"TNC_OLD_NICK"`,`"TNC_NEW_NICK"`,`"TNC_STAMP"` FROM `"T_NICK_CHANGE"` WHERE `"TNC_UID"`='%d' ORDER BY `"TNC_STAMP"` DESC LIMIT 5", userid); 
					result = sendQueryResult(string, sql_result);
					strdel(string, 0, 128);
					if(numRows(result, sql_result) > 0) {	
						new oldNick[MAX_PLAYER_NAME], newNick[MAX_PLAYER_NAME], stamp;
						new year, month, day, hour, minute;
						for(new limit = numRows(result, sql_result), index; index < limit; index ++) {
							strdel(oldNick, 0, 24);
							strdel(newNick, 0, 24);
							strins(oldNick, getFieldAssoc_32(TNC_OLD_NICK, result, sql_result), 0);
							strins(newNick, getFieldAssoc_32(TNC_NEW_NICK, result, sql_result), 0);
							stamp = strval(getFieldAssoc_32(TNC_STAMP, result, sql_result));
							DeconvertNick(oldNick);
							DeconvertNick(newNick);
							dtimestamp(stamp, year, month, day, hour, minute);
							format(string, sizeof(string), "%s\n"C_WHITE"%s "TEXT_DIALOG_BODY"<- "C_WHITE"%s  "TEXT_DIALOG_BODY"( "C_WHITE"%s  "TEXT_DIALOG_BODY"[ "C_WHITE"%d:%02d "TEXT_DIALOG_BODY"] )", string, newNick, oldNick, strData(year, month, day, " / ", false, false, true, true), hour, minute);
							nextRow(result, sql_result);	
						}					
						freeResult(result, sql_result);							
					} else strins(string, "Brak zmian nicku", 0);
				} else strins(string, "Brak zmian nicku", 0);
				
				
				format(string, sizeof(string), "Nick: "C_WHITE"%s\n"TEXT_DIALOG_HEAD"User ID: "C_WHITE"%d %s\n"TEXT_DIALOG_HEAD"IP: "C_WHITE"%s\n"TEXT_DIALOG_HEAD"Poziom admina: "C_WHITE"%s\n"TEXT_DIALOG_HEAD"Czas pobytu na serwerze: "C_WHITE"%s\n\n   "TEXT_DIALOG_HEAD"___ Ostatnie zmiany nicku ___\n%s",
					getPlayerName(checkID), 
					userid, userid == 0 ? ("(Niezarejestrowany)") : (""),
					getPlayerIp(checkID),
					GetAdminNameByLvL(IsAdmin(checkID)), 
					convertSeconds(getPlayerConnectTime(playerid)),
					string
				);
				ShowPlayerInfoDialog(playerid, BACK_ADMIN_INFO_MENU, "Admin Panel - Player Info", string);
				return _TRUE;
			} else strins(string, "\t\t       Podane ID lub nick gracza nie sa poprawne.", 0);
		}
		format(string, sizeof(string), "Podaj ID lub nick gracza OnLine, lub wybierz go z 'TabListy' zeby zobaczyc informacje.\n\n"C_ADMIN"%s", string);
		ShowPlayerDialogEx(playerid, DIALOG_ADMIN_ONLINE_CHECK, DIALOG_STYLE_INPUT, "Admin Panel - Player Info", string, "Dalej", "Wroc");	
		return _TRUE;
	}
	return _FALSE;
}
//===============================================================
//---------------------------------------------------------------
//===============================================================
/*
	Admin Panel - Player Info
*/
//===============================================================
//---------------------------------------------------------------
//===============================================================
ShowPlayerNameCheckMenu(playerid, checktype = -1) {
	if(IsAdmin(playerid) > 0) {
		if(checktype == -1) ShowPlayerDialogEx(playerid, DIALOG_NAME_CHECK_TYPE, DIALOG_STYLE_LIST, 
			"Admin Panel - Prawdopodobne nicki gracza", "1) IP + GPCI\t\t\t\t("C_WHITE"Bardzo duze prawdopodobienstwo"TEXT_DIALOG_BODY")\n2) IP\t\t\t\t\t("C_WHITE"Duze prawdopodobienstwo"TEXT_DIALOG_BODY")\n3) Host + GPCI\t\t\t\t("C_WHITE"Srednie prawdopodobienstwo"TEXT_DIALOG_BODY")\n4) Host\t\t\t\t\t("C_WHITE"Niskie prawdopodobienstwo"TEXT_DIALOG_BODY")", "Sprawdz", GetHelpVarValue(playerid, 50) == 0 ? ("Wroc") : ("Wyjdz"));
		else {
			SetHelpVarValue(playerid, 51, checktype);
			NameCheckMenuSelectPlayer(playerid);
		}
		return 1;
	}
	return 0;
}
//---------------------------------------------------------------
NameCheckMenuSelectPlayer(playerid, selected[] = "") {
	if(IsAdmin(playerid) > 0) {
		new string[1024], warning_str[64];
		if(!isnull(selected)) {
			if('9' >= selected[0] >= '0' and isNumeric(selected) and strlen(selected) <= 3) {
				new IDGracza;
				if(IsPlayerConnected((IDGracza = strval(selected)))) {
					new DBResult: result, Result:sql_result, rows;					
					new p_gpci[64], nick[MAX_PLAYER_NAME];
					GetPlayerName(IDGracza, nick, sizeof(nick));
					gpci(IDGracza, p_gpci, sizeof(p_gpci));
					ConvertNick(nick);
					switch(GetHelpVarValue(playerid, 51)) {
						case 0: format(string, sizeof(string), "SELECT * FROM `"T_PLAYER_INFO"` WHERE `"TPI_IP"`='%s' AND `"TPI_GPCI"`='%s' AND `"TPI_NICK"` != '%s' ORDER BY `"TPI_STAMP"` DESC LIMIT 10", getPlayerIp(IDGracza), p_gpci, nick);
						case 1: format(string, sizeof(string), "SELECT * FROM `"T_PLAYER_INFO"` WHERE `"TPI_IP"`='%s' AND `"TPI_NICK"`!='%s' ORDER BY `"TPI_STAMP"` DESC LIMIT 10", getPlayerIp(IDGracza), nick);
						case 2: format(string, sizeof(string), "SELECT * FROM `"T_PLAYER_INFO"` WHERE `"TPI_IP"` LIKE '%s.%%' AND `"TPI_GPCI"`='%s' ORDER BY `"TPI_STAMP"` DESC LIMIT 10", GetHostFromIP(getPlayerIp(IDGracza)), p_gpci);
						case 3: format(string, sizeof(string), "SELECT * FROM `"T_PLAYER_INFO"` WHERE `"TPI_IP"` LIKE '%s.%%' ORDER BY `"TPI_STAMP"` DESC LIMIT 10", GetHostFromIP(getPlayerIp(IDGracza)));
						default: return ShowPlayerNameCheckMenu(playerid);
					}
					result = sendQueryResult(string, sql_result);

					strdel(string, 0, 256);
					if((rows = numRows(result, sql_result)) > 0) {
						strins(string, TEXT_DIALOG_BODY, 0);
						for(new i, year, month, day, hour, minute, account, str_account[16]; i < rows; i ++) {
							strdel(nick, 0, 24);
							strdel(p_gpci, 0, 64);
							strdel(str_account, 0, 16);
							
							if((account = strval(getFieldAssoc_8(TPI_UID, result, sql_result))) <= 0) {
								strins(str_account, "Brak konta", 0);
							} else {
								format(str_account, sizeof(str_account), "UID: %d", account);
							}
							
							strins(nick, getFieldAssoc_32(TPI_NICK, result, sql_result), 0);
							strins(p_gpci, getFieldAssoc_32(TPI_IP, result, sql_result), 0);
							DeconvertNick(nick);
							dtimestamp(strval(getFieldAssoc_16(TPI_STAMP, result, sql_result)), year, month, day, hour, minute);
							format(string, sizeof(string),"%s(%s [%02d:%02d]) %s  |  %s  |  %s\n", string, strData(year, month, day, " / ", false, false, true, false), hour, minute, nick, p_gpci, str_account);
							nextRow(result, sql_result);
						}					
						freeResult(result, sql_result);
					} else strins(warning_str, "\t           Brak rezultatow :(", 0);
				} else strins(warning_str, "\t Wybrane ID nie jest uzywane.", 0);
			} else strins(warning_str, "\t      Niepoprawne ID gracza.", 0);
		}
		setPlayerTabListInfo(playerid, TAB_LIST_NAME_CHECK_SEARCH);
		format(string, sizeof(string), "%s\n"TEXT_DIALOG_HEAD"Podaj ID gracza, lub wybierz go z 'Tab Listy'.\n\n"C_ADMIN"%s", string, warning_str);
		ShowPlayerDialogEx(playerid, DIALOG_NAME_CHECK_PLAYER, DIALOG_STYLE_INPUT, "Admin Panel - Prawdopodobne nicki gracza", string, "Sprawdz", "Wroc");
		return 1;
	}
	return 0;
}