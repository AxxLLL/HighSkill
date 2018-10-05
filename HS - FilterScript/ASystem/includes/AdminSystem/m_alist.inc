/*



*/
//===============================================================
//---------------------------------------------------------------
//===============================================================
CMD:admins(playerid) {
	new str[150], bool:isAdmin, alvl;
	SendClientMessage(playerid, 0xF4FA25FF, " === Lista Administratorow On-Line ===");
	forplayers(i) {
   		if((alvl = IsAdmin(i)) != 0) {
            if(GetPVarType(i, PV_ALOG_HIDE) == PLAYER_VARTYPE_NONE) {
	            isAdmin = true;
	            if(alvl < 0) format(str, sizeof(str),"  %s  ( "C_WHITE"%s  "C_YELLOW"|  "C_ADMIN"Niezalogowany(a) "C_YELLOW")", getPlayerName(i), GetAdminNameByLvL(alvl));
				else format(str, sizeof(str),"  %s  ( "C_WHITE"%s  "C_YELLOW"|  "C_LIGHTGREEN"Zalogowany(a) "C_YELLOW")", getPlayerName(i), GetAdminNameByLvL(alvl));
				SendClientMessage(playerid, COLOR_YELLOW, str);
			} else {
			     if(IsAdmin(playerid) >= ALVL_HEAD_ADMIN) {
		            isAdmin = true;
		            if(alvl < 0) format(str, sizeof(str),"  %s  ( "C_WHITE"%s  "C_YELLOW"|  "C_ADMIN"Niezalogowany(a) "C_YELLOW"  |  "C_ADMIN"UKRYTY"C_YELLOW")", getPlayerName(i), GetAdminNameByLvL(alvl));
					else format(str, sizeof(str),"  %s  ( "C_WHITE"%s  "C_YELLOW"|  "C_LIGHTGREEN"Zalogowany(a) "C_YELLOW"  |  "C_ADMIN"UKRYTY"C_YELLOW")", getPlayerName(i), GetAdminNameByLvL(alvl));
		            SendClientMessage(playerid, COLOR_YELLOW, str);
			     }
			}
        }
    }
    if(isAdmin == false) SendClientMessage(playerid, COLOR_ADMIN, "        Brak administratorow On-Line.");
	return _TRUE;
}
//---------------------------------------------------------------
CMD:alist(playerid) return cmd_adminlist(playerid);
CMD:adminlist(playerid) {
	ShowPlayerAdminList(playerid);
	return 1;
}
//===============================================================
ShowPlayerAdminList(playerid, adminlvl = -1) {
	new string[256];
	new DBResult: result, Result:sql_result;
	SetHelpVarValue(playerid, 1, 0);
	
	if(0 <= adminlvl <= 6) {	
		if(adminlvl == 0) {
			AdminListSearch(playerid);			
		} else if(adminlvl == 5) {
			format(string, sizeof(string), "SELECT `"TK_UID"` FROM `"T_KONTA"` WHERE `"TK_ADMIN_LVL"`!='0' AND `"TK_ADMIN_STAMP"` >= '%d' AND `"TK_LAST_DISCONNECT"`<='%d' LIMIT 1", timestamp(), timestamp() - ToSeconds(getSettingIntValueByIndex(s_NonActiveAdminInfoID), _DAY));
			result = sendQueryResult(string, sql_result);
			if(numRows(result, sql_result) == 0) {		
				format(string, sizeof(string),"Nieodnaleziono nieaktywnych administratorow przez dluzej niz %d dni.", getSettingIntValueByIndex(s_NonActiveAdminInfoID));
				ShowPlayerInfoDialog(playerid, BACK_ADMIN_LIST, "Lista administratorow - Nieaktywni administratorzy", string);
			} else {
				freeResult(result, sql_result);
				SetPlayerPage(playerid, 0);
				ShowPlayerAdminListPage(playerid, -1, 0);
			}
		} else if(adminlvl == 6) {
			ShowPlayerAdminListPage(playerid, -3, 0);
		} else {
			format(string, sizeof(string), "SELECT `"TK_UID"` FROM `"T_KONTA"` WHERE `"TK_ADMIN_LVL"`='%d' AND `"TK_ADMIN_STAMP"` >= '%d' LIMIT 1", adminlvl , timestamp());
			result = sendQueryResult(string, sql_result);
			if(numRows(result, sql_result) == 0) {		
				new head_string[64];
				format(head_string, sizeof(head_string), "Lista administratorow - %s", GetAdminNameByLvL(adminlvl));
				format(string, sizeof(string),"Nieodnaleziono administratorow o poziomie praw '"TEXT_DIALOG_NORMAL"%s"TEXT_DIALOG_HEAD"'.", GetAdminNameByLvL(adminlvl));
				ShowPlayerInfoDialog(playerid, BACK_ADMIN_LIST, head_string, string);
			} else {		
				freeResult(result, sql_result);
				SetPlayerPage(playerid, 0);
				ShowPlayerAdminListPage(playerid, adminlvl, 0);
			}
		}
	} else {
		new j_admin, admin, h_admin, g_master, r_admins, t_stamp = timestamp();
		format(string, sizeof(string), "SELECT `"TK_UID"` FROM `"T_KONTA"` WHERE `"TK_ADMIN_LVL"`='"#ALVL_JUNIOR_ADMIN"' AND `"TK_ADMIN_STAMP"` >= '%d'", t_stamp);
		result = sendQueryResult(string, sql_result);
		j_admin = numRows(result, sql_result);
		freeResult(result, sql_result);

		format(string, sizeof(string), "SELECT `"TK_UID"` FROM `"T_KONTA"` WHERE `"TK_ADMIN_LVL"`='"#ALVL_ADMIN"' AND `"TK_ADMIN_STAMP"` >= '%d'", t_stamp);
		result = sendQueryResult(string, sql_result);
		admin = numRows(result, sql_result);
		freeResult(result, sql_result);

		format(string, sizeof(string), "SELECT `"TK_UID"` FROM `"T_KONTA"` WHERE `"TK_ADMIN_LVL"`='"#ALVL_HEAD_ADMIN"' AND `"TK_ADMIN_STAMP"` >= '%d'", t_stamp);
		result = sendQueryResult(string, sql_result);
		h_admin = numRows(result, sql_result);
		freeResult(result, sql_result);

		format(string, sizeof(string), "SELECT `"TK_UID"` FROM `"T_KONTA"` WHERE `"TK_ADMIN_LVL"`='"#ALVL_GAME_MASTER "' AND `"TK_ADMIN_STAMP"` >= '%d'", t_stamp);
		result = sendQueryResult(string, sql_result);
		g_master = numRows(result, sql_result);
		freeResult(result, sql_result);		
		
		result = sendQueryResult("SELECT `"TK_UID"` FROM `"T_KONTA"` WHERE `"TK_RCON_ADMIN"`='1'", sql_result);
		r_admins = numRows(result, sql_result);
		freeResult(result, sql_result);			
		
		if(IsAdmin(playerid) >= ALVL_HEAD_ADMIN) {
			if(IsAdmin(playerid) == ALVL_GAME_MASTER) 
				format(string, sizeof(string), "1) Wyszukaj\n2) Junior Admin\t\t\t\t[ "TEXT_DIALOG_NORMAL"%d"TEXT_DIALOG_BODY" ]\n3) Admin\t\t\t\t[ "TEXT_DIALOG_NORMAL"%d"TEXT_DIALOG_BODY" ]\n4) Head Admin\t\t\t\t[ "TEXT_DIALOG_NORMAL"%d"TEXT_DIALOG_BODY" ]\n5) Game Master\t\t\t\t[ "TEXT_DIALOG_NORMAL"%d"TEXT_DIALOG_BODY" ]\n6) Nieaktywni administratorzy\n7) Administratorzy RCON\t\t[ "TEXT_DIALOG_NORMAL"%d"TEXT_DIALOG_BODY" ]", j_admin, admin, h_admin, g_master, r_admins);
			else format(string, sizeof(string), "1) Wyszukaj\n2) Junior Admin\t\t\t\t[ "TEXT_DIALOG_NORMAL"%d"TEXT_DIALOG_BODY" ]\n3) Admin\t\t\t\t[ "TEXT_DIALOG_NORMAL"%d"TEXT_DIALOG_BODY" ]\n4) Head Admin\t\t\t\t[ "TEXT_DIALOG_NORMAL"%d"TEXT_DIALOG_BODY" ]\n5) Game Master\t\t\t\t[ "TEXT_DIALOG_NORMAL"%d"TEXT_DIALOG_BODY" ]\n6) Nieaktywni administratorzy", j_admin, admin, h_admin, g_master);
		} else {
			format(string, sizeof(string), "1) Wyszukaj\n2) Junior Admin\t\t\t\t[ "TEXT_DIALOG_NORMAL"%d"TEXT_DIALOG_BODY" ]\n3) Admin\t\t\t\t[ "TEXT_DIALOG_NORMAL"%d"TEXT_DIALOG_BODY" ]\n4) Head Admin\t\t\t\t[ "TEXT_DIALOG_NORMAL"%d"TEXT_DIALOG_BODY" ]\n5) Game Master\t\t\t\t[ "TEXT_DIALOG_NORMAL"%d"TEXT_DIALOG_BODY" ]", j_admin, admin, h_admin, g_master);		
		}
		ShowPlayerDialogEx(playerid, DIALOG_ADMIN_LIST, DIALOG_STYLE_LIST, "Lista administratorow - Poziom praw", string, "Sprawdz", "Wyjdz");
	}
	return _TRUE;
}
//---------------------------------------------------------------
ShowPlayerAdminListPage(playerid, adminlvl, page) {
	new string[600], h_name[64];		
	new DBResult: result, Result:sql_result;
	new rows;	
	
	if(page < 0) page = 0;
	
	if(ALVL_JUNIOR_ADMIN <= adminlvl <= ALVL_GAME_MASTER) {						
		format(h_name, sizeof(h_name), "Lista administratorow - %s", GetAdminNameByLvL(adminlvl));		
		format(string, sizeof(string), "SELECT `"TK_NICK"` FROM `"T_KONTA"` WHERE `"TK_ADMIN_LVL"`='%d' AND `"TK_ADMIN_STAMP"` >= '%d' LIMIT %d, 11", adminlvl, timestamp(), page * 10);		
	} else {
		if(adminlvl == -1 AND IsAdmin(playerid) >= ALVL_HEAD_ADMIN) {
			format(h_name, sizeof(h_name), "Lista administratorow - Nieaktywni administratorzy");
			format(string, sizeof(string), "SELECT `"TK_NICK"`,`"TK_LAST_DISCONNECT"` FROM `"T_KONTA"` WHERE `"TK_ADMIN_LVL"`!='0' AND `"TK_ADMIN_STAMP"` >= '%d' AND `"TK_LAST_DISCONNECT"`<='%d' ORDER BY `"TK_LAST_DISCONNECT"` ASC LIMIT %d, 11", timestamp(), timestamp() - ToSeconds(getSettingIntValueByIndex(s_NonActiveAdminInfoID), _DAY), page * 10);
		} else if(adminlvl == -2) {
			format(h_name, sizeof(h_name), "Lista administratorow - Wyszukaj");
			if(GetHelpVarValue(playerid, 2) == -1) format(string, sizeof(string), "SELECT `"TK_NICK"`,`"TK_ADMIN_LVL"` FROM `"T_KONTA"` WHERE `"TK_ADMIN_LVL"`!='0' AND `"TK_ADMIN_STAMP"` >= '%d' AND `"TK_NICK"` LIKE '%s' ORDER BY `"TK_ADMIN_LVL"` DESC LIMIT %d, 11", timestamp(), GetHelpStringValue(playerid, 0), page * 10);
			else format(string, sizeof(string), "SELECT `"TK_NICK"`,`"TK_ADMIN_LVL"` FROM `"T_KONTA"` WHERE `"TK_ADMIN_LVL"`=='%d' AND `"TK_ADMIN_STAMP"` >= '%d' AND `"TK_NICK"` LIKE '%s' ORDER BY `"TK_ADMIN_LVL"` DESC LIMIT %d, 11", GetHelpVarValue(playerid, 2), timestamp(), GetHelpStringValue(playerid, 0), page * 10);
		} else if(adminlvl == -3 and IsAdmin(playerid) == ALVL_GAME_MASTER) {
			format(h_name, sizeof(h_name), "Lista administratorow - Administratorzy RCON");
			format(string, sizeof(string), "SELECT `"TK_NICK"`,`"TK_UID"` FROM `"T_KONTA"` WHERE `"TK_RCON_ADMIN"`='1' LIMIT %d, 11", page * 10);			
		}
	}	
	result = sendQueryResult(string, sql_result);
	//_______________________	
	strdel(string, 0, 128);
	rows = numRows(result, sql_result);
	if(numRows(result, sql_result) > 0) {
		new bool:isNextPage = rows == 11 ? true : false;
		new nick[32];

		for(new i, limit = rows == 11 ? 10 : rows; i < limit; i ++) {
			strdel(nick, 0, MAX_PLAYER_NAME);
			strins(nick, getFieldAssoc_32(TK_NICK, result, sql_result), 0);
			DeconvertNick(nick);
				
			switch(adminlvl) {
				case -1: format(string, sizeof(string), "%s\n%d) %s\t[ "TEXT_DIALOG_NORMAL"%s"TEXT_DIALOG_BODY" ]", string, page * 10 + i + 1, CutName(nick), convertSeconds(timestamp() - strval(getFieldAssoc_16(TK_LAST_DISCONNECT, result, sql_result))));
				case -2: format(string, sizeof(string), "%s\n%d) %s\t\t[ "TEXT_DIALOG_NORMAL"%s"TEXT_DIALOG_BODY" ]", string, page * 10 + i + 1, CutName(nick), GetAdminNameByLvL(strval(getFieldAssoc_16(TK_ADMIN_LVL, result, sql_result))));
				case -3: format(string, sizeof(string), "%s\n%d) %s\t\t[ UID: "TEXT_DIALOG_NORMAL"%d"TEXT_DIALOG_BODY" ]", string, page * 10 + i + 1, CutName(nick), strval(getFieldAssoc_8(TK_UID, result, sql_result)));
				default: format(string, sizeof(string), "%s\n%d) %s", string, page * 10 + i + 1, nick);
			}
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
		SetHelpVarValue(playerid, 0, adminlvl);
		ShowPlayerDialogEx(playerid, DIALOG_ADMIN_LIST_LIST, DIALOG_STYLE_LIST, h_name, string, "Sprawdz", "Wroc");
		return _TRUE;
	} else ShowPlayerInfoDialog(playerid, BACK_ADMIN_LIST, h_name, "Wystapil blad: Niepoprawny numer strony lub brak wynikow.");				
	//_______________________
	return _FALSE;
}
//---------------------------------------------------------------
AdminListPageResponse(playerid, listitem) {
	new adminlvl;	
	if(ALVL_JUNIOR_ADMIN <= (adminlvl = GetHelpVarValue(playerid, 0)) <= ALVL_GAME_MASTER or (adminlvl == -1 and IsAdmin(playerid) >= ALVL_HEAD_ADMIN) or adminlvl == -2 or (adminlvl == -3 and IsAdmin(playerid) == ALVL_GAME_MASTER)) {
		new DBResult: result, Result:sql_result;
		new rows;
		new string[400];		
		
		switch(adminlvl) {
			case -1: format(string, sizeof(string), "SELECT `"TK_UID"` FROM `"T_KONTA"` WHERE `"TK_ADMIN_LVL"`!='0' AND `"TK_ADMIN_STAMP"` >= '%d' AND `"TK_LAST_DISCONNECT"`<='%d' ORDER BY `"TK_LAST_DISCONNECT"` ASC LIMIT %d, 11", timestamp(), timestamp() - ToSeconds(getSettingIntValueByIndex(s_NonActiveAdminInfoID), _DAY), GetPlayerPage(playerid) * 10);	
			case -2: {
				if(GetHelpVarValue(playerid, 2) == -1) format(string, sizeof(string), "SELECT `"TK_UID"` FROM `"T_KONTA"` WHERE `"TK_ADMIN_LVL"`!='0' AND `"TK_ADMIN_STAMP"` >= '%d' AND `"TK_NICK"` LIKE '%s' ORDER BY `"TK_ADMIN_LVL"` DESC LIMIT %d, 11", timestamp(), GetHelpStringValue(playerid, 0), GetPlayerPage(playerid) * 10);
				else format(string, sizeof(string), "SELECT `"TK_UID"` FROM `"T_KONTA"` WHERE `"TK_ADMIN_LVL"`=='%d' AND `"TK_ADMIN_STAMP"` >= '%d' AND `"TK_NICK"` LIKE '%s' ORDER BY `"TK_ADMIN_LVL"` DESC LIMIT %d, 11", GetHelpVarValue(playerid, 2), timestamp(), GetHelpStringValue(playerid, 0), GetPlayerPage(playerid) * 10);
			}
			case -3: format(string, sizeof(string), "SELECT `"TK_UID"` FROM `"T_KONTA"` WHERE `"TK_RCON_ADMIN"`='1' LIMIT %d, 11", GetPlayerPage(playerid) * 10);		
			default: format(string, sizeof(string), "SELECT `"TK_UID"` FROM `"T_KONTA"` WHERE `"TK_ADMIN_LVL"`='%d' AND `"TK_ADMIN_STAMP"` >= '%d' LIMIT %d, 11", adminlvl, timestamp(), GetPlayerPage(playerid) * 10);
		}

		result = sendQueryResult(string, sql_result);
		rows = numRows(result, sql_result);
		if(rows > 0) {

			new bool:pvpage = GetPlayerPage(playerid) > 0 ? true : false;
			new bool:nxpage = rows == 11 ? true : false;
		
			if(listitem == 0 and (pvpage == true or nxpage == true)) {
				freeResult(result, sql_result);
				if(pvpage == true) ShowPlayerAdminListPage(playerid, adminlvl, GetPlayerPage(playerid) - 1);
				else {
					ShowPlayerAdminListPage(playerid, adminlvl, GetPlayerPage(playerid) + 1);
				}
			} else if(listitem == 1 and (pvpage == true and nxpage == true)) {
				freeResult(result, sql_result);
				ShowPlayerAdminListPage(playerid, adminlvl, GetPlayerPage(playerid) + 1);
			} else {
				new userid, index, dest[8];
				if(pvpage == true) listitem --;
				if(nxpage == true) listitem --;			
			
				for(index = 0; index < rows; index ++) {
					if(index == listitem) {
						if(UseMySQL() == 1) sql_get_field(sql_result, 0, dest, sizeof(dest));
						else db_get_field(result, 0, dest, sizeof(dest));
						userid = strval(dest);
						break;
					}		
					nextRow(result, sql_result);
				}				
								
				freeResult(result, sql_result);
				if(IsValidUserID(userid)) {
					format(string, sizeof(string), "SELECT `"TK_NICK"`, `"TK_ADMIN_STAMP"`, `"TK_LAST_DISCONNECT"`, `"TK_LAST_LOGIN_STAMP"`, `"TK_ADMIN_LVL"`, `"TK_RCON_ADMIN"` FROM `"T_KONTA"` WHERE `"TK_UID"`='%d' LIMIT 1", userid);
					result = sendQueryResult(string, sql_result);
					if(numRows(result, sql_result) > 0) {
						new nick[MAX_PLAYER_NAME], a_stamp, last_disconnect;
						new year, month, day, hour, minute;
						new h_name[64];
						new last_login = strval(getFieldAssoc_16(TK_LAST_LOGIN_STAMP, result, sql_result));
						new pa_lvl = strval(getFieldAssoc_16(TK_ADMIN_LVL, result, sql_result));
						new rcon_admin = strval(getFieldAssoc_16(TK_RCON_ADMIN, result, sql_result));
						strins(nick, getFieldAssoc_32(TK_NICK, result, sql_result), 0);
						a_stamp = strval(getFieldAssoc_16(TK_ADMIN_STAMP, result, sql_result));
						last_disconnect = strval(getFieldAssoc_16(TK_LAST_DISCONNECT, result, sql_result));
						freeResult(result, sql_result);
						
						if(last_login > last_disconnect) {
							for(new i; i < MAX_PLAYERS; i ++) {
								if(userid == getPlayerUserID(i)) {
									last_login = -1;
									break;
								}
							}	
						}						
						
						last_disconnect = last_login != -1 ? last_disconnect : timestamp();
						dtimestamp(last_disconnect, year, month, day, hour, minute);
						
						DeconvertNick(nick);
						format(string, sizeof(string), "\
								Nick: "TEXT_DIALOG_NORMAL"%s  "TEXT_DIALOG_HEAD"(User ID: "TEXT_DIALOG_NORMAL"%d"TEXT_DIALOG_HEAD")\n\
								Poziom praw: "TEXT_DIALOG_NORMAL"%s"TEXT_DIALOG_HEAD"\n\
								Ostatnio aktywny(a): "TEXT_DIALOG_NORMAL"%s  "TEXT_DIALOG_HEAD"[ "TEXT_DIALOG_NORMAL"%d:%02d "TEXT_DIALOG_HEAD"]\n\
								Nieaktywny(a) przez: "TEXT_DIALOG_NORMAL"%s"TEXT_DIALOG_HEAD"\n\
								Administrator RCON: %s\n",
							nick, userid, 
							GetAdminNameByLvL(pa_lvl), 
							strData(year, month, day, " / ", false, false, true, false), hour, minute,
							last_login == -1 ? ("On Line") : convertSeconds(timestamp() - last_disconnect),
							rcon_admin == 0 ? (C_ADMIN"Nie") : (C_LIGHTGREEN"Tak")
							);
							
						if(IsAdmin(playerid) >= ALVL_HEAD_ADMIN) {
							dtimestamp(a_stamp, year, month, day, hour, minute);
							format(string, sizeof(string), "%s"TEXT_DIALOG_HEAD"Czas trwania: "TEXT_DIALOG_NORMAL"%s  "TEXT_DIALOG_HEAD"[ "TEXT_DIALOG_NORMAL"%d:%02d "TEXT_DIALOG_HEAD"]\n", string, strData(year, month, day, " / ", false, false, true, false), hour, minute);
						}

						switch(adminlvl) {
							case -1: format(h_name, sizeof(h_name), "Lista administratorow - Nieaktywni administratorzy");
							case -2: format(h_name, sizeof(h_name), "Lista administratorow - Wyszukaj");
							case -3: format(h_name, sizeof(h_name), "Lista administratorow - Administratorzy RCON");
							default: format(h_name, sizeof(h_name), "Lista administratorow - %s", GetAdminNameByLvL(adminlvl));
						}
	
						ShowPlayerDialogEx(playerid, DIALOG_ADMIN_LIST_INFO, DIALOG_STYLE_MSGBOX, h_name, string, "Wroc", "Wyjdz");
						return _TRUE;
					} else ShowPlayerAdminListPage(playerid, adminlvl, GetPlayerPage(playerid));				
				} else ShowPlayerAdminListPage(playerid, adminlvl, GetPlayerPage(playerid));			
			}		
		} else ShowPlayerAdminListPage(playerid, adminlvl, 0);
	} else ShowPlayerInfoDialog(playerid, BACK_ADMIN_LIST, "Lista administratorow", "Wystapil blad: Niepoprawny poziom praw administratora.");	
	return _FALSE;
}
//---------------------------------------------------------------
AdminListSearch(playerid, adminname[] = "") {
	new string[350];
	DeleteSpaces(adminname);
	if(!isnull(adminname)) {
		new userid, bool:founded;
		new len;
		new searchLvL = -1;
		new index_1, index_2;	
		
		if((index_1 = strfind(adminname, "<")) != -1 and (index_2 = strfind(adminname, ">", true, index_1)) != -1) {			
			if(index_2 - index_1 == 2) {
				new cut[2];
				strmid(cut, adminname, index_1 + 1, index_2);
				if(ALVL_JUNIOR_ADMIN <= (searchLvL = strval(cut)) <= ALVL_GAME_MASTER) {
					strdel(adminname, index_1, index_2 + 1);
				} else searchLvL = -2;
			} else {
				strdel(adminname, index_1, index_2 + 1);
			}
		}		
		
		if(searchLvL != -2) {
			if(!(isNumeric(adminname) and strlen(adminname) < 9 and (userid = strval(adminname)) > 0)) {			
				if(MAX_PLAYER_NAME >= (len = strlen(adminname)) > 0) {
					len --;
					founded = true;
					for(new i = len; i >= 0; i --) {
						if(!(adminname[i] == '*' and (i == len or i == 0)) and !('A' <= adminname[i] <= 'Z' or 'a' <= adminname[i] <= 'z' or '0' <= adminname[i] <= '9' or adminname[i] == '(' or adminname[i] == ')' or adminname[i] == '[' or adminname[i] == ']' or adminname[i] == '.' or adminname[i] == '_' or adminname[i] == '$' or adminname[i] == '@' or adminname[i] == '=')) {
							founded = false;
							break;
						}					
					}
				}
			} else founded = true;
			if(founded == true) {
				new DBResult: result, Result:sql_result;
				if(userid != 0) {				
					format(string, sizeof(string), "SELECT `"TK_NICK"`, `"TK_ADMIN_STAMP"`, `"TK_LAST_DISCONNECT"`, `"TK_LAST_LOGIN_STAMP"`, `"TK_ADMIN_LVL"` FROM `"T_KONTA"` WHERE `"TK_UID"`='%d' AND `"TK_ADMIN_LVL"` != 0 AND `"TK_ADMIN_STAMP"` >= '%d' LIMIT 1", userid, timestamp());
					result = sendQueryResult(string, sql_result);
					if(numRows(result, sql_result) > 0) {
						new nick[MAX_PLAYER_NAME], a_stamp, last_disconnect;
						new year, month, day, hour, minute;
						new last_login = strval(getFieldAssoc_16(TK_ADMIN_LVL, result, sql_result));
						new adminlvl = strval(getFieldAssoc_16(TK_LAST_LOGIN_STAMP, result, sql_result));
						strins(nick, getFieldAssoc_32(TK_NICK, result, sql_result), 0);
						a_stamp = strval(getFieldAssoc_16(TK_ADMIN_STAMP, result, sql_result));
						last_disconnect = strval(getFieldAssoc_16(TK_LAST_DISCONNECT, result, sql_result));
						freeResult(result, sql_result);
							
						if(last_login > last_disconnect) {
							for(new i; i < MAX_PLAYERS; i ++) {
								if(userid == getPlayerUserID(i)) {
									last_login = -1;
									break;
								}
							}	
						}						
							
						last_disconnect = last_login != -1 ? last_disconnect : timestamp();
						dtimestamp(last_disconnect, year, month, day, hour, minute);
							
						DeconvertNick(nick);
						format(string, sizeof(string), "\
								Nick: "TEXT_DIALOG_NORMAL"%s  "TEXT_DIALOG_HEAD"(User ID: "TEXT_DIALOG_NORMAL"%d"TEXT_DIALOG_HEAD")\n\
								Poziom praw: "TEXT_DIALOG_NORMAL"%s"TEXT_DIALOG_HEAD"\n\
								Ostatnio aktywny(a): "TEXT_DIALOG_NORMAL"%s  "TEXT_DIALOG_HEAD"[ "TEXT_DIALOG_NORMAL"%d:%02d "TEXT_DIALOG_HEAD"]\n\
								Nieaktywny(a) przez: "TEXT_DIALOG_NORMAL"%s\n", 
							nick, userid, 
							GetAdminNameByLvL(adminlvl), 
							strData(year, month, day, " / ", false, false, true, false), hour, minute,
							last_login == -1 ? ("On Line") : convertSeconds(timestamp() - last_disconnect)
						);
								
						if(IsAdmin(playerid) >= ALVL_HEAD_ADMIN) {
							dtimestamp(a_stamp, year, month, day, hour, minute);
							format(string, sizeof(string), "%s"TEXT_DIALOG_HEAD"Czas trwania: "TEXT_DIALOG_NORMAL"%s  "TEXT_DIALOG_HEAD"[ "TEXT_DIALOG_NORMAL"%d:%02d "TEXT_DIALOG_HEAD"]\n", string, strData(year, month, day, " / ", false, false, true, false), hour, minute);
						}			
						ShowPlayerInfoDialog(playerid, BACK_SEARCH_LIST, "Lista administratorow - Wyszukaj", string);
						return _TRUE;
					} else format(string, sizeof(string), "\tNie odnaleziono administratora o User ID: %d", userid);		
				} else {
					new bool:first_s, bool:last_s;
					new conNick[MAX_PLAYER_NAME + 6];
					
					if(adminname[0] == '*') {
						first_s = true;
						strdel(adminname, 0, 1);
						len --;
					}
					if(adminname[len] == '*') {
						if(len > 0) {
							last_s = true;
							adminname[len] = EOS;
						} else strdel(adminname, len, len + 1);
					}			
					
					strins(conNick, adminname, 0);
					ConvertNick(conNick);					
						
					if(first_s == true) strins(conNick, "%%", 0);
					if(last_s == true) strins(conNick, "%%", strlen(conNick));
						
						
					if(searchLvL == -1) format(string, sizeof(string), "SELECT `"TK_NICK"` FROM `"T_KONTA"` WHERE `"TK_NICK"` LIKE '%s' AND `"TK_ADMIN_LVL"` != '0' AND `"TK_ADMIN_STAMP"` >= '%d' LIMIT 1", conNick, timestamp());
					else format(string, sizeof(string), "SELECT `"TK_NICK"` FROM `"T_KONTA"` WHERE `"TK_NICK"` LIKE '%s' AND `"TK_ADMIN_LVL"` == '%d' AND `"TK_ADMIN_STAMP"` >= '%d' LIMIT 1", conNick, searchLvL, timestamp());
					
					result = sendQueryResult(string, sql_result);
					if(numRows(result, sql_result) > 0) { 
						SetHelpStringValue(playerid, 0, conNick);
						freeResult(result, sql_result);		
						SetHelpVarValue(playerid, 1, 1);
						SetHelpVarValue(playerid, 2, searchLvL);
						ShowPlayerAdminListPage(playerid, -2, 0);
						return _TRUE;
					} else {
						while(((userid = strfind(conNick, "%")) != -1)) {
							strdel(conNick, userid, userid + 1);
						}
						DeconvertNick(conNick);
						if(searchLvL == -1) format(string, sizeof(string), "\tNie odnaleziono administratora o nicku '%s'.", strlen(conNick) > 0 ? conNick : ("*Wszyscy*"));
						else format(string, sizeof(string), "    Nie odnaleziono administratora o nicku '%s' i poziomie\n\t\t         praw '%s'.", strlen(conNick) > 0 ? conNick : ("*Wszyscy*"), GetAdminNameByLvL(searchLvL));
					}						
				}		
			} else strins(string, "\tNiepoprawny format wprowadzanych danych.", 0);		
		} else strins(string, "\t        Niepoprawny poziom administratora.", 0);		
	}
	DeleteHelpStringValue(playerid, 0);
	format(string, sizeof(string), "\
		Podaj nick lub User ID gracza, ktorego dane chcesz zobaczyc.\
		\n\nInfo: Uzyj symbolu gwiazdki '*' zeby wyszukac administratora\
		\n        nie znajac jego pelnego nicku np. 'Ax*', '*xL_', '*xL*'.\n\
		\t         Info: Wielkosc liter nie ma znaczenia.\
		\n\n"TEXT_DIALOG_ALERT"%s", string);
	ShowPlayerDialogEx(playerid, DIALOG_ADMIN_LIST_SEARCH, DIALOG_STYLE_INPUT, "Lista administratorow - Wyszukaj", string, "Szukaj", "Wroc");
	return _TRUE;
}	
//---------------------------------------------------------------