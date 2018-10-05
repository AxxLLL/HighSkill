/*

*/
//===============================================================
//---------------------------------------------------------------
//===============================================================
CMD:hapanel(playerid) {
	if(IsAdmin(playerid) <= -ALVL_HEAD_ADMIN) {
		SendClientMessage(playerid, COLOR_DIALOG_BODY, " (Head Admin Panel) Musisz byc zalogowany(a) na konto administratora, zeby moc uzyc tej funkcji.");
	} else HAPanelStart(playerid);
	return _TRUE;
}
//---------------------------------------------------------------
HAPanelStart(playerid, listitem = -1) {
	if(IsAdmin(playerid) >= ALVL_HEAD_ADMIN) {
		switch(listitem) {
			case 0: HAPanelPlayerAccount(playerid);
			case 1: HAPanelRegisterBase(playerid);
			case 2: HAPanelStaticBan(playerid);
			case 3: HAPanelAccRegisterNick(playerid);
			case 4: {
				SetHelpVarValue(playerid, 98, 1);
				HACheckDataMenu(playerid);
			}
			case 5: HAStatisticsReset(playerid);
			case 6: HABaseMenu(playerid);
			case 7: HAServerSettings(playerid, -1);
			case 8: HAVipMenu(playerid);
			default: {
				if(IsAdmin(playerid) == ALVL_GAME_MASTER) ShowPlayerDialogEx(playerid, DIALOG_HA_PANEL, DIALOG_STYLE_LIST, "Head Admin Panel", "1) Operacje na koncie gracza\n2) Baza rejestrowanych kont\n3) Obsluga banow stalych\n4) Zarejestruj nowe konto\n5) Sprawdz dane\n6) Reset kont\n7) Obsluga baz danych\n8) Ustawienia serwera\n9) Operacje na kontach VIP", "Dalej", "Wyjdz");
				else ShowPlayerDialogEx(playerid, DIALOG_HA_PANEL, DIALOG_STYLE_LIST, "Head Admin Panel", "1) Operacje na koncie gracza\n2) Baza rejestrowanych kont\n3) Obsluga banow stalych\n4) Zarejestruj nowe konto\n5) Sprawdz dane\n6) Reset kont", "Dalej", "Wyjdz");				
			}
		}
		return _TRUE;
	}
	return _FALSE;
}
//===============================================================
//---------------------------------------------------------------
//===============================================================
/*
	1) Operacje na koncie gracza
*/
//===============================================================
//---------------------------------------------------------------
//===============================================================
HAPanelPlayerAccount(playerid, playername[] = "") {
	if(IsAdmin(playerid) >= ALVL_HEAD_ADMIN) {
		new string[350];
		SetHelpVarValue(playerid, 98, 0);
		DeleteSpaces(playername);
		setPlayerTabListInfo(playerid, TAB_LIST_HAPANEL_PLAYER_SEARCH);
		if(!isnull(playername)) {
			new f_index, l_index;
			new DBResult: result, Result:sql_result;
			f_index = strfind(playername, "*");
			l_index = strfind(playername, "*", true, f_index + 1);
			if(f_index != -1) {
				new length = strlen(playername);
				if((f_index == 0 or f_index == length - 1) and (l_index == -1 or l_index == length - 1)) {
					if(f_index != 0) {
						l_index = f_index;
						f_index = -1;
					}
				
					if(l_index != -1 and f_index != -1 and l_index - f_index == 1) {
						l_index = -1;
					}
				
					if(l_index != -1) strdel(playername, l_index, l_index + 1);
					if(f_index != -1) strdel(playername, f_index, f_index + 1);					
					
					new bool:validnick = true;					
					if(!isnull(playername)) {
						if(!isNumeric(playername)) {
							if((length = strlen(playername)) <= MAX_PLAYER_NAME) {
								for(new i; i < length; i ++) {
									switch(playername[i]) {
										case 'A'..'Z', 'a'..'z', '0'..'9', '(', ')', '[', ']', '.', '_', '$', '@', '=': continue;
										default: {
											validnick = false;
											break;
										}
									}
								}
							} else validnick = false;
						} else validnick = false;
					} 
	
					if(validnick == true) {			
					
						SetHelpVarValue(playerid, 0, f_index == -1 ? 0 : 1);
						SetHelpVarValue(playerid, 1, l_index == -1 ? 0 : 1);
						SetHelpStringValue(playerid, 0, playername);
						HAPlayerAccountList(playerid);
						
						return _TRUE;
					} else strins(string, "\t    Podany do wyszukania nick, zawiera niedozwolone symbole.", 0);
				} else strins(string, "      Symboli gwiazdki mozna uzywac wylacznie na poczatku lub na koncu nazwy.", 0);
			} else {
				if(IsValidNick(playername) == _TRUE) {
					ConvertNick(playername);
					format(string, sizeof(string),"SELECT `"TK_UID"`,`"TK_NICK"` FROM `"T_KONTA"` WHERE `"TK_NICK"`='%s' LIMIT 1", playername);
					result = sendQueryResult(string, sql_result);
					strdel(string, 0, 128);
					if(numRows(result, sql_result) > 0) {
						new p_name[MAX_PLAYER_NAME];
						new userid = strval(getFieldAssoc_8(TK_UID, result, sql_result));
						
						strins(p_name, getFieldAssoc_32(TK_NICK, result, sql_result), 0);
						freeResult(result, sql_result);
						
						SetHelpVarValue(playerid, 0, userid);
						DeconvertNick(p_name);
						SetHelpStringValue(playerid, 0, p_name);
						
						HAPanelPlayerAccountMenu(playerid);
						return _TRUE;
					} else strins(string, "\t\t       Nieznaleziono konta o podanej nazwie.", 0);					
				} else if(strlen(playername) <= 8 and strval(playername) > 0) {
					format(string, sizeof(string),"SELECT `"TK_NICK"` FROM `"T_KONTA"` WHERE `"TK_UID"`='%d' LIMIT 1", strval(playername));
					result = sendQueryResult(string, sql_result);
					strdel(string, 0, 128);
					if(numRows(result, sql_result) > 0) {
						new p_name[MAX_PLAYER_NAME];
						
						strins(p_name, getFieldAssoc_32(TK_NICK, result, sql_result), 0);
						freeResult(result, sql_result);
						
						SetHelpVarValue(playerid, 0, strval(playername));
						DeconvertNick(p_name);
						SetHelpStringValue(playerid, 0, p_name);

						HAPanelPlayerAccountMenu(playerid);
						return _TRUE;
					} else strins(string, "\t\t       Nieznaleziono konta o podanym User ID.", 0);
				} else strins(string, "\t\t\tPodana nazwa jest niepoprawna.", 0);
			}
		}
		format(string, sizeof(string),"      Wpisz zarejestrowany nick gracza, jego User ID, lub wybierz go z 'Tab Listy'\n  zeby przejsc do panelu zarzadzania kontem. Mozesz rowniez skorzystac z opcji\nwyrszukiwania gwiazdkami, w przypadku kiedy nie znasz dokladnego nicku gracza.\n\n"TEXT_DIALOG_ALERT"%s", string);
		ShowPlayerDialogEx(playerid, DIALOG_HA_ACCOUNT_SEARCH, DIALOG_STYLE_INPUT, "Operacje na koncie gracza", string, "Dalej", "Wroc");
		return _TRUE;
	}
	return _FALSE;
}
//===============================================================
HAPlayerAccountList(playerid, page = 0) {
	if(IsAdmin(playerid) >= ALVL_HEAD_ADMIN) {
		new string[800], nick[32];		
		new DBResult: result, Result:sql_result;
		new rows;	

		if(page < 0) page = 0;
		
		format(string, sizeof(string), "SELECT `"TK_NICK"`, `"TK_UID"` FROM `"T_KONTA"` WHERE `"TK_NICK"` LIKE '%s%s%s' LIMIT %d, 11", GetHelpVarValue(playerid, 0) == 0 ? ("") : ("%"), GetHelpStringValue(playerid, 0), GetHelpVarValue(playerid, 1) == 0 ? ("") : ("%"), page * 10);
		result = sendQueryResult(string, sql_result);
		//_______________________	
		strdel(string, 0, 256);
		rows = numRows(result, sql_result);
		if(numRows(result, sql_result) > 0) {
			new bool:isNextPage = rows == 11 ? true : false;
			new index;
			for(new limit = rows == 11 ? 10 : rows; index < limit; index ++) {
				strdel(nick, 0, MAX_PLAYER_NAME);
				strins(nick, getFieldAssoc_32(TK_NICK, result, sql_result), 0);
				DeconvertNick(nick);					
				format(string, sizeof(string), "%s\n%d) %s\t\t"TEXT_DIALOG_HEAD"[ UID: "TEXT_DIALOG_NORMAL"%d"TEXT_DIALOG_HEAD" ]", string, page * 10 + index + 1, CutName(nick), strval(getFieldAssoc_8(TK_UID, result, sql_result)));
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
			ShowPlayerDialogEx(playerid, DIALOG_HA_ACCOUNT_SEARCH_LIST, DIALOG_STYLE_LIST, "Operacje na koncie gracza - Wyszukaj", string, "Przejdz", "Wroc");
			return _TRUE;
		} else {
			ShowPlayerInfoDialog(playerid, BACK_HA_ACCOUNT_SEARCH, "Operacje na koncie gracza - Wyszukaj", "Nieznaleziono rezultatow dla podanych danych.");
		}
		//_______________________	
	}
	return _FALSE;
}
//---------------------------------------------------------------
HAPlayerAccountListResponse(playerid, listitem) {
	if(IsAdmin(playerid) >= ALVL_HEAD_ADMIN) {
		new DBResult: result, Result:sql_result;
		new rows;
		new string[256];				
		
		format(string, sizeof(string), "SELECT `"TK_UID"` FROM `"T_KONTA"` WHERE `"TK_NICK"` LIKE '%s%s%s' LIMIT %d, 11", GetHelpVarValue(playerid, 0) == 0 ? ("") : ("%"), GetHelpStringValue(playerid, 0), GetHelpVarValue(playerid, 1) == 0 ? ("") : ("%"), GetPlayerPage(playerid) * 10);

		result = sendQueryResult(string, sql_result);
		rows = numRows(result, sql_result);
		if(rows > 0) {
			
			new bool:pvpage = GetPlayerPage(playerid) > 0 ? true : false;
			new bool:nxpage = rows == 11 ? true : false;
		
			if(listitem == 0 and (pvpage == true or nxpage == true)) {
				freeResult(result, sql_result);
				if(pvpage == true) HAPlayerAccountList(playerid, GetPlayerPage(playerid) - 1);
				else {
					HAPlayerAccountList(playerid, GetPlayerPage(playerid) + 1);
				}
			} else if(listitem == 1 and (pvpage == true and nxpage == true)) {
				freeResult(result, sql_result);
				HAPlayerAccountList(playerid, GetPlayerPage(playerid) + 1);
			} else {
				new uniqueid, s_uniqueid[8];
				if(pvpage == true) listitem --;
				if(nxpage == true) listitem --;
			
			
				new index, dest[8];
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
				valstr(s_uniqueid, uniqueid);
				HAPanelPlayerAccount(playerid, s_uniqueid);		
				return _TRUE;			
			}		
		} else HARegisterBaseList(playerid, 0);
	} 
	return _FALSE;
}
//===============================================================
HAPanelPlayerAccountMenu(playerid, menuid = -1) {
	if(IsAdmin(playerid) >= ALVL_HEAD_ADMIN) {
		if(IsUserIDRegistered(GetHelpVarValue(playerid, 0)) == _TRUE) {
			new string[1024], DBResult: result, Result:sql_result, userid = GetHelpVarValue(playerid, 0);
			switch(menuid) {
				case 0: {
					new r_stamp, a_lvl, a_stamp, d_stamp, l_stamp, l_ip[16], l_nick[24], p_time, p_confidental, b_time;
					new t_stamp = timestamp();
					format(string, sizeof(string), "SELECT `"TK_REGISTER_STAMP"`, `"TK_ADMIN_LVL"`, `"TK_ADMIN_STAMP"`, `"TK_DELETE_STAMP"`, `"TK_LAST_LOGIN_STAMP"`, `"TK_LAST_LOGIN_IP"`, `"TK_LAST_NICK"`, `"TK_PLAY_TIME"`, `"TK_PROV_CONFIDENTAL"`, `"TK_BAN_TIME"` FROM `"T_KONTA"` WHERE `"TK_UID"`='%d' LIMIT 1", userid);
					result = sendQueryResult(string, sql_result);					
					r_stamp = strval(getFieldAssoc_16(TK_REGISTER_STAMP, result, sql_result));
					a_lvl = strval(getFieldAssoc_16(TK_ADMIN_LVL, result, sql_result));
					a_stamp = strval(getFieldAssoc_16(TK_ADMIN_STAMP, result, sql_result));
					d_stamp = strval(getFieldAssoc_16(TK_DELETE_STAMP, result, sql_result));
					l_stamp = strval(getFieldAssoc_16(TK_LAST_LOGIN_STAMP, result, sql_result));
					p_time = strval(getFieldAssoc_16(TK_PLAY_TIME, result, sql_result));
					p_confidental = strval(getFieldAssoc_16(TK_PROV_CONFIDENTAL, result, sql_result));
					b_time = strval(getFieldAssoc_16(TK_BAN_TIME, result, sql_result));
					strins(l_nick, getFieldAssoc_32(TK_LAST_NICK, result, sql_result), 0);
					strins(l_ip, getFieldAssoc_16(TK_LAST_LOGIN_IP, result, sql_result), 0);
					freeResult(result, sql_result);
					
					new year, month, day, hour, minute;
					new register_Y, register_M, register_D;
					new delete_Y, delete_M, delete_D;
					new login_Y, login_M, login_D, login_h, login_m;
					new admin_date[128];
					new ban_date[128];
					new pconf_date[128];
					new fullconf_date[128];
					
					dtimestamp(r_stamp, register_Y, register_M, register_D);
					dtimestamp(d_stamp, delete_Y, delete_M, delete_D);
					dtimestamp(l_stamp, login_Y, login_M, login_D, login_h, login_m);
					
					if(a_lvl > 0 and a_stamp > t_stamp) {
						dtimestamp(a_stamp, year, month, day, hour, minute);
						format(admin_date, sizeof(admin_date), "%s  "TEXT_DIALOG_HEAD"( "TEXT_DIALOG_NORMAL"%s  "TEXT_DIALOG_HEAD"[ "TEXT_DIALOG_NORMAL"%d:%02d "TEXT_DIALOG_HEAD"] )", GetAdminNameByLvL(a_lvl), strData(year, month, day, " / ", false, false, true, false), hour, minute);
					} else strins(admin_date, "Brak", 0);
					
					if(b_time > t_stamp) {
						dtimestamp(b_time, year, month, day, hour, minute);
						format(ban_date, sizeof(ban_date), "Tak  "TEXT_DIALOG_HEAD"( "TEXT_DIALOG_NORMAL"%s  "TEXT_DIALOG_HEAD"[ "TEXT_DIALOG_NORMAL"%d:%02d "TEXT_DIALOG_HEAD"] )", strData(year, month, day, " / ", false, false, true, false), hour, minute);
					} else strins(ban_date, "Nie", 0);					
					
					if(p_confidental > t_stamp) {
						dtimestamp(p_confidental, year, month, day, hour, minute);
						format(pconf_date, sizeof(pconf_date), "Tak  "TEXT_DIALOG_HEAD"( "TEXT_DIALOG_NORMAL"%s  "TEXT_DIALOG_HEAD"[ "TEXT_DIALOG_NORMAL"%d:%02d "TEXT_DIALOG_HEAD"] )", strData(year, month, day, " / ", false, false, true, false), hour, minute);
					} else strins(pconf_date, "Nie", 0);						
					
					if(p_time < ToSeconds(getSettingIntValueByIndex(s_LoginConfiID), _HOUR)) {
						format(fullconf_date, sizeof(fullconf_date), "Brakuje %s", convertSeconds(ToSeconds(getSettingIntValueByIndex(s_LoginConfiID), _HOUR) - p_time));
					} else strins(fullconf_date, "Tak", 0);
					
					format(string, sizeof(string), 
							TEXT_DIALOG_HEAD"Nick: "TEXT_DIALOG_NORMAL"%s   "TEXT_DIALOG_HEAD"(Poprzedni: "TEXT_DIALOG_NORMAL"%s"TEXT_DIALOG_HEAD" )\n\
							"TEXT_DIALOG_HEAD"User ID: "TEXT_DIALOG_NORMAL"%d\n\
							"TEXT_DIALOG_HEAD"Data rejestracji: "TEXT_DIALOG_NORMAL"%s\n\
							"TEXT_DIALOG_HEAD"Ostatnie logowanie: "TEXT_DIALOG_NORMAL"%s "TEXT_DIALOG_HEAD"[ "TEXT_DIALOG_NORMAL"%d:%02d "TEXT_DIALOG_HEAD"]  ( IP: "TEXT_DIALOG_NORMAL"%s "TEXT_DIALOG_HEAD")\n\
						",
						GetHelpStringValue(playerid, 0), l_nick, 
						userid, 
						strData(register_Y, register_M, register_D, " / ", false, false, true, false), 
						strData(login_Y, login_M, login_D, " / ", false, false, true, false), login_h, login_m, l_ip					
					);
					
					format(string, sizeof(string), "%s\
							"TEXT_DIALOG_HEAD"Data usuniecia konta: "TEXT_DIALOG_NORMAL"%s "TEXT_DIALOG_HEAD"("TEXT_DIALOG_ALERT"*"TEXT_DIALOG_HEAD")\n\
							"TEXT_DIALOG_HEAD"Prawa administratora: "TEXT_DIALOG_NORMAL"%s\n\
							"TEXT_DIALOG_HEAD"Czas gry: "TEXT_DIALOG_NORMAL"%s\n\
							"TEXT_DIALOG_HEAD"Zaufany (pelny): "TEXT_DIALOG_NORMAL"%s\n\
						", 
						string, 		
						strData(delete_Y, delete_M, delete_D, " / ", false, false, true, false),
						admin_date, 
						p_time > 0 ? convertSeconds(p_time) : ("Brak"),
						fullconf_date
					);			
					
					format(string, sizeof(string), "%s\
							"TEXT_DIALOG_HEAD"Zaufany (warunkowy): "TEXT_DIALOG_NORMAL"%s\n\
							"TEXT_DIALOG_HEAD"Zbanowany: "TEXT_DIALOG_NORMAL"%s\n\n\
							"TEXT_DIALOG_ALERT"* "TEXT_DIALOG_HEAD"Data usuniecia konta z systemu w przypadku braku aktywnosci.", 			
						string,
						pconf_date,
						ban_date
					);				
					ShowPlayerInfoDialog(playerid, BACK_HA_ACCOUNT_MENU, "Panel gracza - Informacje", string);					
				}
				case 1: {
					new vipTime, vipBonusPoints, vipPlayerPoints;
					format(string, sizeof(string), "SELECT `"TK_PREMIUM_DATE"`,`"TK_PREMIUM_PLAYER_POINT"`,`"TK_PREMIUM_BONUS_POINT"` FROM `"T_KONTA"` WHERE `"TK_UID"`='%d' LIMIT 1", userid);
					result = sendQueryResult(string, sql_result);
					vipTime = strval(getFieldAssoc_16(TK_PREMIUM_DATE, result, sql_result));
					vipBonusPoints = strval(getFieldAssoc_16(TK_PREMIUM_BONUS_POINT, result, sql_result));
					vipPlayerPoints = strval(getFieldAssoc_16(TK_PREMIUM_PLAYER_POINT, result, sql_result));
					freeResult(result, sql_result);
					strdel(string, 0, 128);
					
					if(vipTime > timestamp()) {
						new year, month, day, hour, minute;
						dtimestamp(vipTime, year, month, day, hour, minute);
						format(string, sizeof(string), C_LIGHTGREEN"Aktywne  "TEXT_DIALOG_HEAD"( "C_WHITE"%s  "TEXT_DIALOG_HEAD"[ "C_WHITE"%d:%02d "TEXT_DIALOG_HEAD"] )", strData(year, month, day, " / ", false, false, true, false), hour, minute);
					} else strins(string, C_WHITE"Brak", 0);		
				
					format(string, sizeof(string), "\n\
								"TEXT_DIALOG_HEAD"Aktywne przywileje VIP: %s\n\
								"TEXT_DIALOG_HEAD"Niewykorzystane wlasne punkty VIP: "C_WHITE"%d\n\
								"TEXT_DIALOG_HEAD"Niewykorzystane bonusowe punkty VIP: "C_WHITE"%d\n\
								"TEXT_DIALOG_HEAD"Razem niewykorzystanych punktow VIP: "C_WHITE"%d\n \
							", 
						string,
						vipPlayerPoints,
						vipBonusPoints,
						vipBonusPoints + vipPlayerPoints
					);
					ShowPlayerInfoDialog(playerid, BACK_HA_ACCOUNT_MENU, "Panel gracza - Informacje VIP", string);				
				}
				case 2: {
					new rows;
					format(string, sizeof(string), "SELECT * FROM `"T_NICK_CHANGE"` WHERE `"TNC_UID"`='%d' ORDER BY `"TNC_STAMP"` DESC LIMIT 9", userid);
					result = sendQueryResult(string, sql_result);
					if((rows = numRows(result, sql_result)) > 0) {
						new oldnick[32], newnick[32], year, month, day;
						strdel(string, 0, 128);						
						for(new i; i < rows; i ++) {
							strdel(newnick, 0, 24);
							strdel(oldnick, 0, 24);
							dtimestamp(strval(getFieldAssoc_16(TNC_STAMP, result, sql_result)), year, month, day);
							strins(newnick, getFieldAssoc_32(TNC_NEW_NICK, result, sql_result), 0);
							strins(oldnick, getFieldAssoc_32(TNC_OLD_NICK, result, sql_result), 0);
							DeconvertNick(newnick);
							DeconvertNick(oldnick);
							format(string, sizeof(string), "%s"TEXT_DIALOG_HEAD"( "TEXT_DIALOG_BODY"%s "TEXT_DIALOG_HEAD")  "TEXT_DIALOG_NORMAL"%s "TEXT_DIALOG_HEAD"-> "TEXT_DIALOG_NORMAL"%s\n", string, strData(year, month, day, " / ", false, false, true, false), oldnick, newnick);
							nextRow(result, sql_result);				
						}						
						
						freeResult(result, sql_result);
						ShowPlayerInfoDialog(playerid, BACK_HA_ACCOUNT_MENU, "Panel gracza - Zmiany nickow", string);
					} else ShowPlayerInfoDialog(playerid, BACK_HA_ACCOUNT_MENU, "Panel gracza - Zmiany nickow", "Nieznaleziono informacji na temat zmian nickow dla tego konta.");
				}
				case 3: HAPanelPlayerAccountNewNick(playerid);
				case 4: HAPanelPlayerPasswordChange(playerid);
				case 5: HAPanelAdminLvLChange(playerid);			
				case 6: HSPanelAdminPasswordChange(playerid);
				case 7: HSPanelProvConfidental(playerid);
				case 8: HSPanelPlayerBanAccount(playerid);
				case 9: HSPanelPlayerStatisticReset(playerid);
				case 10: HAPanelPlayerVIPPremiumMenu(playerid);
				case 11: HSPanelRCONAccount(playerid);
				case 12: HSPanelPlayerDeleteAccount(playerid);
				default: {
					if(IsAdmin(playerid) == ALVL_GAME_MASTER) {
						ShowPlayerDialogEx(playerid, DIALOG_HA_ACCOUNT_MENU, DIALOG_STYLE_LIST, GetHelpStringValue(playerid, 0), 
							"1) Informacje\n\
							2) Informacje VIP\n\
							3) Logi zmian nicku\n\
							4) Zmien nick\n\
							5) Zmien haslo\n\
							6) Ustaw prawa administratora\n\
							7) Reset hasla aLog\n\
							8) Warunkowy zaufany\n\
							9) Blokada konta\n\
							10) Reset statystyk\n\
							11) Obsluga punktow premium i konta VIP\n\
							12) Konto RCON\n\
							13) Usun konto", 
						"Dalej", "Wroc");
					} else {
						ShowPlayerDialogEx(playerid, DIALOG_HA_ACCOUNT_MENU, DIALOG_STYLE_LIST, GetHelpStringValue(playerid, 0), 
							"1) Informacje\n\
							2) Informacje VIP\n\
							3) Logi zmian nicku\n\
							4) Zmien nick\n\
							5) Zmien haslo\n\
							6) Ustaw prawa administratora\n\
							7) Reset hasla aLog\n\
							8) Warunkowy zaufany\n\
							9) Blokada konta\n\
							10) Reset statystyk", 
						"Dalej", "Wroc");					
					}
				}
			}
			return _TRUE;
		} else ShowPlayerInfoDialog(playerid, BACK_HA_ACCOUNT_SEARCH, "Operacje na koncie gracza", "Podane User ID jest niepoprawne.");
	}
	return _FALSE;
}
//===============================================================
HAPanelPlayerAccountNewNick(playerid, newnick[] = "") {
	if(IsAdmin(playerid) >= ALVL_HEAD_ADMIN) {
		new DBResult: result, Result:sql_result;
		new userid = GetHelpVarValue(playerid, 0);
		new string[256];	
		
		format(string, sizeof(string),"SELECT `"TK_NICK"`,`"TK_ADMIN_LVL"`,`"TK_ADMIN_STAMP"` FROM `"T_KONTA"` WHERE `"TK_UID"` = '%d' LIMIT 1", userid);
		result = sendQueryResult(string, sql_result);
		strdel(string, 0, 128);
		if(numRows(result, sql_result) > 0) {
			if(!((strval(getFieldAssoc_8(TK_ADMIN_LVL, result, sql_result)) >= ALVL_HEAD_ADMIN and strval(getFieldAssoc_16(TK_ADMIN_STAMP, result, sql_result)) >= timestamp())) or userid == getPlayerUserID(playerid) or IsAdmin(playerid) == ALVL_GAME_MASTER) {
				if(!isnull(newnick)) {
					if(IsValidNick(newnick) and isNumeric(newnick) == _FALSE and IsValidIP(newnick) == _FALSE  and IsValidHost(newnick) == _FALSE ) {
						new oldName[MAX_PLAYER_NAME];	
						strins(oldName, getFieldAssoc_32(TK_NICK, result, sql_result), 0);
						freeResult(result, sql_result);
						
						if(IsNickRegistered(newnick) == _FALSE) {
							if(GetBanUniqueID(B_NICK, newnick) == 0) {
								new bool:used = false;
								new onlineid = INVALID_PLAYER_ID;
								forplayers(i) {
									if(getPlayerUserID(i) == userid) onlineid = i;					
									if(strcmp(getPlayerName(i), newnick) == 0) {
										used = true;
										break;
									}
								}
								if(used == false) {
									new conNick[MAX_PLAYER_NAME];									
									strins(conNick, newnick, 0);
									DeconvertNick(oldName);
									ConvertNick(conNick);
									format(string, sizeof(string), "UPDATE `"T_KONTA"` SET `"TK_NICK"`='%s',`"TK_LAST_NICK_STAMP"`='%d', `"TK_LAST_NICK"`='%s' WHERE `"TK_UID"`='%d'", conNick, timestamp(), oldName, userid);
									sendQueryWithout(string);									
									UpdateBasesByUserNewNick(userid, newnick);
									format(string, sizeof(string), "Zmiana nicku %s -> %s", oldName, newnick);
									AddToPlayerLog(userid, string);			
									
									AddToNickChangeLog(userid, newnick, oldName);
									SetHelpStringValue(playerid, 0, newnick);
									if(onlineid != INVALID_PLAYER_ID) {
										format(string, sizeof(string),"[Zmiana nicku] Administrator '%s' (UID: %d) zmienil(a) nick graczu '%s' (UID: %d) na na '%s'.", getPlayerName(playerid), getPlayerUserID(playerid), oldName, getPlayerUserID(onlineid), newnick);
										AddToChatLog(string);
										SetPVarString(onlineid, PV_LOGIN_LAST_NICK, oldName);
										SetPVarInt(onlineid, PV_LOGIN_LAST_NICK_STAMP, timestamp());							
										setPlayerName(onlineid, newnick);										
									}
									format(string, sizeof(string),"Nick gracza zostal zmieniony z '"TEXT_DIALOG_NORMAL"%s"TEXT_DIALOG_HEAD"' na '"TEXT_DIALOG_NORMAL"%s"TEXT_DIALOG_HEAD"'.", oldName, newnick);
									ShowPlayerInfoDialog(playerid, BACK_HA_ACCOUNT_MENU, GetHelpStringValue(playerid, 0), string);
									return _TRUE;
								} else strins(string, "Podany nick, jest uzywany przez jednego z graczy bedacych na serwerze.", 0);
							} else strins(string, "\tWybrany nick znajduje sie na liscie zablokowanych nazw.", 0);
						} else strins(string, "\t       Podany nick jest juz zarejestrowany w systemie.", 0);
					} else strins(string, "      Niepoprawny format nicku, lub nick zawiera niedozwolone symbole.", 0);
				}			
				format(string, sizeof(string),"\tW tym panelu mozesz zmienic zarejestrowany nick gracza.\nPodaj nowy nick gracza i kliknij 'Zmien', zeby zmienic nick dla tego konta.\n\n"TEXT_DIALOG_ALERT"%s", string);
				ShowPlayerDialogEx(playerid, DIALOG_HA_ACCOUNT_NICK, DIALOG_STYLE_INPUT, GetHelpStringValue(playerid, 0), string, "Zmien", "Wroc");			
			} else ShowPlayerInfoDialog(playerid, BACK_HA_ACCOUNT_MENU, GetHelpStringValue(playerid, 0), "Przywileje administracyjne dla wybranego konta, pozwalaja mu\n      na samodzielna zmiane nicku w panelu administratora.");
			freeResult(result, sql_result);
			return _TRUE;
		} else ShowPlayerInfoDialog(playerid, BACK_HA_ACCOUNT_SEARCH, GetHelpStringValue(playerid, 0), "User ID dla tego konta przestalo istniec w systemie.\nByc moze konto zostalo usuniete.");
	}
	return _FALSE;
}
//---------------------------------------------------------------
HAPanelPlayerPasswordChange(playerid, newpassword[] = "") {
	if(IsAdmin(playerid) >= ALVL_HEAD_ADMIN) {
		new userid = GetHelpVarValue(playerid, 0);
		new string[256];
		if(IsUserIDRegistered(userid) == _TRUE) {
			if(!isnull(newpassword)) {
				if(IsValidPassword(newpassword) or (strlen(newpassword) == 1 and newpassword[0] == '0')) {
					new onlineid = INVALID_PLAYER_ID;
					new password[32];
					forplayers(i) {
						if(getPlayerUserID(i) == userid) {
							onlineid = i;				
							break;
						}
					}					
					
					if(newpassword[0] == '0' and strlen(newpassword) == 1) {
						valstr(password, randomly(100000, 999999));
					} else {
						strins(password, newpassword, 0);
					}					

					format(string, sizeof(string), "UPDATE `"T_KONTA"` SET `"TK_PASSWORD"`='%d',`"TK_RESET_PASSWORD"`='1' WHERE `"TK_UID"`='%d'", Hash(password), userid);
					sendQueryWithout(string);									
		
					format(string, sizeof(string), "Zmiana hasla (administracyjna). Nowe haslo: %s", password);
					AddToPlayerLog(userid, string);			
					
					

					if(onlineid != INVALID_PLAYER_ID) {
						format(string, sizeof(string)," (Admin System) Administrator '%s' (UID: %d) zmienil(a) Twoje haslo do konta na '"TEXT_DIALOG_NORMAL"%s"TEXT_DIALOG_HEAD"'.", getPlayerName(playerid), getPlayerUserID(playerid), password);
						SendClientMessage(onlineid, COLOR_DIALOG_HEAD, string);
						SetPVarInt(onlineid, PV_LOGIN_PASSWORD, Hash(password));							
					}
					
					format(string, sizeof(string)," (Zmiana Hasla) Haslo do konta gracza '%s' zostalo zmienione na '%s'.", GetHelpStringValue(playerid, 0), password);
					SendClientMessage(playerid, COLOR_DIALOG_HEAD, string);
					format(string, sizeof(string),"Haslo do konta gracza '"TEXT_DIALOG_NORMAL"%s"TEXT_DIALOG_HEAD"' zostalo zmienione na '"TEXT_DIALOG_NORMAL"%s"TEXT_DIALOG_HEAD"'.", GetHelpStringValue(playerid, 0), password);
					ShowPlayerInfoDialog(playerid, BACK_HA_ACCOUNT_MENU, GetHelpStringValue(playerid, 0), string);
					return _TRUE;
				} else strins(string, "Niepoprawny format hasla, lub haslo zawiera niedozwolone\n\t\t\t  symbole.", 0);
			}			
			format(string, sizeof(string),"      W tym panelu mozesz zmienic haslo do konta gracza.\nPodaj nowe haslo, lub wpisz '0' zeby wygenerowac losowe\n   haslo i kliknij 'Zmien', zeby zmienic haslo dla tego konta.\n\n"TEXT_DIALOG_ALERT"%s", string);
			ShowPlayerDialogEx(playerid, DIALOG_HA_ACCOUNT_PASSWORD, DIALOG_STYLE_INPUT, GetHelpStringValue(playerid, 0), string, "Zmien", "Wroc");			
			return _TRUE;
		} else ShowPlayerInfoDialog(playerid, BACK_HA_ACCOUNT_SEARCH, GetHelpStringValue(playerid, 0), "User ID dla tego konta przestalo istniec w systemie.\nByc moze konto zostalo usuniete.");
	}
	return _FALSE;
}
//---------------------------------------------------------------
HAPanelAdminLvLChange(playerid, listitem = -1) {
	if(IsAdmin(playerid) >= ALVL_HEAD_ADMIN) {
		new userid = GetHelpVarValue(playerid, 0);
		new string[160];
		if(listitem == -1) {
			new DBResult: result, Result:sql_result;
			format(string, sizeof(string),"SELECT `"TK_ADMIN_LVL"`,`"TK_ADMIN_STAMP"` FROM `"T_KONTA"` WHERE `"TK_UID"` = '%d' LIMIT 1", userid);
			result = sendQueryResult(string, sql_result);
			strdel(string, 0, 128);
			if(numRows(result, sql_result) > 0) {
				new aAdminLvL, aAdminDate;
				aAdminLvL 	= strval(getFieldAssoc_8(TK_ADMIN_LVL, result, sql_result));
				aAdminDate	= strval(getFieldAssoc_16(TK_ADMIN_STAMP, result, sql_result));			
				if(aAdminDate < timestamp()) {
					aAdminDate = 0;
					aAdminLvL = ALVL_NON;
				}
				
				if(!(aAdminLvL >= ALVL_HEAD_ADMIN) or IsAdmin(playerid) == ALVL_GAME_MASTER) {
					new activeDate[80];
					if(aAdminDate > 0) {
						new Y, M, D, h, m;
						dtimestamp(aAdminDate, Y, M, D, h, m);
						format(activeDate, sizeof(activeDate), TEXT_DIALOG_HEAD"( "C_WHITE"%s  "TEXT_DIALOG_HEAD"[ "C_WHITE"%d:%02d "TEXT_DIALOG_HEAD"] )", strData(Y, M, D, " / ", false, false, true, false), h, m);
					} else strins(activeDate, TEXT_DIALOG_HEAD"( "C_WHITE"Aktywny "TEXT_DIALOG_HEAD")", 0);
				
					if(IsAdmin(playerid) == ALVL_GAME_MASTER) {
						format(string, sizeof(string), "\
								1) Brak\t\t\t%s\n\
								2) Junior Admin\t\t%s\n\
								3) Admin\t\t%s\n\
								4) Head Admin\t\t%s\n\
								5) Game Master\t\t%s",
							aAdminLvL == ALVL_NON ? activeDate : (""),
							aAdminLvL == ALVL_JUNIOR_ADMIN ? activeDate : (""),
							aAdminLvL == ALVL_ADMIN ? activeDate : (""),
							aAdminLvL == ALVL_HEAD_ADMIN ? activeDate : (""),
							aAdminLvL == ALVL_GAME_MASTER ? activeDate : ("")
						);
					} else {
						format(string, sizeof(string), "\
								1) Brak\t\t\t%s\n\
								2) Junior Admin\t\t%s\n\
								3) Admin\t\t%s\n\
								4) Head Admin\t\t%s",
							aAdminLvL == ALVL_NON ? activeDate : (""),
							aAdminLvL == ALVL_JUNIOR_ADMIN ? activeDate : (""),
							aAdminLvL == ALVL_ADMIN ? activeDate : (""),
							aAdminLvL == ALVL_HEAD_ADMIN ? activeDate : ("")
						);				
					}					
					ShowPlayerDialogEx(playerid, DIALOG_HA_ACCOUNT_ALVL, DIALOG_STYLE_LIST, GetHelpStringValue(playerid, 0), string, "Zmien", "Wroc");			
				} else ShowPlayerInfoDialog(playerid, BACK_HA_ACCOUNT_MENU, GetHelpStringValue(playerid, 0), "Przywileje administracyjne dla wybranego konta, pozwalaja mu\nna samodzielna zmiane poziomu praw w panelu administratora.");
				freeResult(result, sql_result);
				return _TRUE;
			} else ShowPlayerInfoDialog(playerid, BACK_HA_ACCOUNT_SEARCH, GetHelpStringValue(playerid, 0), "User ID dla tego konta przestalo istniec w systemie.\nByc moze konto zostalo usuniete.");
		} else {
			if(listitem == 0) {
				format(string, sizeof(string), "UPDATE `"T_KONTA"` SET `"TK_ADMIN_LVL"`='0', `"TK_ADMIN_STAMP"`='0' WHERE `"TK_UID"`='%d'", userid);
				sendQueryWithout(string);
				format(string, sizeof(string), " (Admin System) Administrator "C_WHITE"%s "TEXT_DIALOG_HEAD"odebral(a) Ci prawa administratora.", getPlayerName(playerid));
				forplayers(i) {
					if(getPlayerUserID(i) == userid) {
						if(IsAdmin(i) != ALVL_NON) {
							SendClientMessage(i, COLOR_DIALOG_HEAD, string);
							SetPVarInt(i, PV_LOGIN_ADMIN_LVL, 0);
							SetPVarInt(i, PV_LOGIN_ADMIN_STAMP, 0);
						}
						break;
					}
				}
				format(string, sizeof(string), "Usuniecie praw administratora (Admin: %s  (UID: %d))", getPlayerName(playerid), getPlayerUserID(playerid));
				AddToPlayerLog(userid, string);							
				HAPanelAdminLvLChange(playerid);
			} else {
				SetHelpVarValue(playerid, 1, listitem);
				HSPanelAdminLvLChangeDate(playerid);
			}
			return _TRUE;
		}
	}
	return _FALSE;
}
//---------------------------------------------------------------
HSPanelAdminLvLChangeDate(playerid, data[] = "") {
	if(IsAdmin(playerid) >= ALVL_HEAD_ADMIN) {
		new userid = GetHelpVarValue(playerid, 0);
		if(IsUserIDRegistered(userid) == _TRUE) {
			new string[150];
			if(!isnull(data)) {
				new days;
				if(0 < strlen(data) < 9 and isNumeric(data) and (days = strval(data)) >= 1) {
					new time = timestamp() + ToSeconds(days, _DAY);
					format(string, sizeof(string), "UPDATE `"T_KONTA"` SET `"TK_ADMIN_LVL"`='%d', `"TK_ADMIN_STAMP"`='%d' WHERE `"TK_UID"`='%d'", GetHelpVarValue(playerid, 1), time, userid);
					sendQueryWithout(string);
					format(string, sizeof(string), " (Admin System) Administrator %s zmienil poziom Twoich praw administratora na '"C_WHITE"%s"TEXT_DIALOG_HEAD"' (Czas: %d dni).", getPlayerName(playerid), GetAdminNameByLvL(GetHelpVarValue(playerid, 1)), days);
					forplayers(i) {
						if(getPlayerUserID(i) == userid) {
							SendClientMessage(i, COLOR_DIALOG_HEAD, string);
							SetPVarInt(i, PV_LOGIN_ADMIN_LVL, (IsAdmin(i) > 0 ? GetHelpVarValue(playerid, 1) : -GetHelpVarValue(playerid, 1)));
							SetPVarInt(i, PV_LOGIN_ADMIN_STAMP, time);
							break;
						}
					}							
					format(string, sizeof(string), "Zmiana poziomu praw administratora na '%s'. Czas: %d dni. (Admin: %s  (UID: %d))", GetAdminNameByLvL(GetHelpVarValue(playerid, 1)), days, getPlayerName(playerid), getPlayerUserID(playerid));
					AddToPlayerLog(userid, string);									
					HAPanelAdminLvLChange(playerid);
					return _TRUE;
				} else strins(string, "\t Niepoprawny czas trwania przywilejow.", 0);
			}
			format(string, sizeof(string), "Podaj w dniach czas trwania przywilejow administratora.\n\n"TEXT_DIALOG_ALERT"%s", string);
			ShowPlayerDialogEx(playerid, DIALOG_HA_ACCOUNT_ALVL_DATA, DIALOG_STYLE_INPUT, GetHelpStringValue(playerid, 0), string, "Ustaw", "Wroc");			
		} else ShowPlayerInfoDialog(playerid, BACK_HA_ACCOUNT_SEARCH, GetHelpStringValue(playerid, 0), "User ID dla tego konta przestalo istniec w systemie.\nByc moze konto zostalo usuniete.");
		return _TRUE;
	}
	return _FALSE;
}
//---------------------------------------------------------------
HSPanelAdminPasswordChange(playerid, bool:confirm = false) {
	if(IsAdmin(playerid) >= ALVL_HEAD_ADMIN) {
		new userid = GetHelpVarValue(playerid, 0);
		if(IsUserIDRegistered(userid) == _TRUE) {
			if(confirm == false) {
				ShowPlayerDialogEx(playerid, DIALOG_HA_ACCOUNT_APWD_RESET, DIALOG_STYLE_MSGBOX, GetHelpStringValue(playerid, 0), "     Czy chcesz zresetowac haslo aLog, dla wybranego konta?\nGracz, przy pierwszej probie logowania na konto administratora\n\t\tbedzie mogl ustawic nowe haslo.", "Resetuj", "Wroc");		
			} else {
				new string[128];
				format(string, sizeof(string), "UPDATE `"T_KONTA"` SET `"TK_ADMIN_PASSWORD"`='0' WHERE `"TK_UID"`='%d'", userid);
				sendQueryWithout(string);
				format(string, sizeof(string), "Reset hasla administratora (Admin: %s  (UID: %d))", getPlayerName(playerid), getPlayerUserID(playerid));
				AddToPlayerLog(userid, string);						
				format(string, sizeof(string), " (Admin System) Administrator "C_WHITE"%s "TEXT_DIALOG_HEAD"zresetowal(a) Twoje haslo aLog.", getPlayerName(playerid));				
				forplayers(i) {
					if(getPlayerUserID(i) == userid) {
						SendClientMessage(i, COLOR_DIALOG_HEAD, string);
						SetPVarInt(i, PV_LOGIN_ADMIN_PASSWORD, 0);
						break;
					}
				}	
				ShowPlayerInfoDialog(playerid, BACK_HA_ACCOUNT_MENU, GetHelpStringValue(playerid, 0), "Zresetowano haslo administratora dla wybranego konta gracza.");
			}
		} else ShowPlayerInfoDialog(playerid, BACK_HA_ACCOUNT_SEARCH, GetHelpStringValue(playerid, 0), "User ID dla tego konta przestalo istniec w systemie.\nByc moze konto zostalo usuniete.");
		return _TRUE;
	}
	return _FALSE;
}
//---------------------------------------------------------------
HSPanelProvConfidental(playerid, data[] = "") {
	if(IsAdmin(playerid) >= ALVL_HEAD_ADMIN) {
		new userid = GetHelpVarValue(playerid, 0);
		new string[350], DBResult: result, Result:sql_result;
		format(string, sizeof(string), "SELECT `"TK_PROV_CONFIDENTAL"` FROM `"T_KONTA"` WHERE `"TK_UID"`='%d' LIMIT 1", userid);
		result = sendQueryResult(string, sql_result);
		strdel(string, 0, 128);
		if(numRows(result, sql_result) > 0) {
			new profConfi = strval(getFieldAssoc_16(TK_PROV_CONFIDENTAL, result, sql_result));
			freeResult(result, sql_result);
			if(!isnull(data)) {
				new days;
				if(0 < strlen(data) < 9 and isNumeric(data) and (days = strval(data)) >= 0) {
					new time = timestamp() + ToSeconds(days, _DAY);
					format(string, sizeof(string), "UPDATE `"T_KONTA"` SET `"TK_PROV_CONFIDENTAL"`='%d' WHERE `"TK_UID"`='%d'", time, userid);
					sendQueryWithout(string);						
					format(string, sizeof(string), "Zmiana czasu warunkowego zaufanego na %d dni. (Admin: %s  (UID: %d))", days, getPlayerName(playerid), getPlayerUserID(playerid));
					AddToPlayerLog(userid, string);									
					HSPanelProvConfidental(playerid);
					return _TRUE;
				} else strins(string, "\t\t Niepoprawny czas trwania przywilejow.", 0);				
			} 			
			if(profConfi > 0 and profConfi > timestamp()) {
				new year, month, day, hour, minute;
				dtimestamp(profConfi, year, month, day, hour, minute);
				format(string, sizeof(string), "Warunkowy zaufany pozwala graczu na ominiecie banow na jego host.\n   Podaj w dniach, czas trwania przywilejow warunkowego zaufanego.\n         Info: Wpisz '0' zeby usunac status warunkowego zafaunego.\n\n"TEXT_DIALOG_BODY"     Aktualny czas trwania przywilejow: "C_WHITE"%s  "TEXT_DIALOG_BODY"[ "C_WHITE"%d:%02d "TEXT_DIALOG_BODY"]\n\n"TEXT_DIALOG_ALERT"%s", strData(year, month, day, " / ", false, false, true, false), hour, minute, string);
			} else {			
				format(string, sizeof(string), "Warunkowy zaufany pozwala graczu na ominiecie banow na jego host.\n   Podaj w dniach, czas trwania przywilejow warunkowego zaufanego.\n         Info: Wpisz '0' zeby usunac status warunkowego zafaunego.\n\n"TEXT_DIALOG_BODY"        Aktualnie gracz nie posiada statusu warunkowego zaufanego\n\n"TEXT_DIALOG_ALERT"%s", string);
			}
			ShowPlayerDialogEx(playerid, DIALOG_HA_ACCOUNT_PROV_CONFI, DIALOG_STYLE_INPUT, GetHelpStringValue(playerid, 0), string, "Ustaw", "Wroc");		
		} else ShowPlayerInfoDialog(playerid, BACK_HA_ACCOUNT_SEARCH, GetHelpStringValue(playerid, 0), "User ID dla tego konta przestalo istniec w systemie.\nByc moze konto zostalo usuniete.");
		return _TRUE;
	}
	return _FALSE;
}
//---------------------------------------------------------------
HSPanelPlayerBanAccount(playerid, bool:nextstep = false) {
	if(IsAdmin(playerid) >= ALVL_HEAD_ADMIN) {
		new userid = GetHelpVarValue(playerid, 0);
		if(IsUserIDRegistered(userid) == _TRUE) {
			new string[512], DBResult: result, Result:sql_result, bantime;
			format(string, sizeof(string), "SELECT `"TK_ADMIN_LVL"`,`"TK_ADMIN_STAMP"`,`"TK_BAN_TIME"`,`"TK_BAN_ADMIN_ID"`,`"TK_BAN_REASON"` FROM `"T_KONTA"` WHERE `"TK_UID"`='%d' LIMIT 1", userid);
			result = sendQueryResult(string, sql_result);
			strdel(string, 0, 128);		
			bantime = strval(getFieldAssoc_16(TK_BAN_TIME, result, sql_result));
			if(nextstep == false) {
				if(bantime > timestamp()) {	
					new adminName[MAX_PLAYER_NAME], year, month, day, hour, minute;					
					
					strins(string, getFieldAssoc_128(TK_BAN_REASON, result, sql_result), 0);
					if(strlen(string) > 55) strins(string, "\n", 55);
					freeResult(result, sql_result);
					
					strins(adminName, GetNickByUserID(strval(getFieldAssoc_8(TK_BAN_ADMIN_ID, result, sql_result))), 0);	// Kasuje wyniki zapytan MySQL
					DeconvertNick(adminName);					
					
					dtimestamp(bantime, year, month, day, hour, minute);					
					format(string, sizeof(string), "\tWybrane konto jest zbanowane!\n\nAdmin: "C_WHITE"%s"TEXT_DIALOG_HEAD"\nData odbanowania: "C_WHITE"%s"TEXT_DIALOG_HEAD"  [ "C_WHITE"%d:%02d"TEXT_DIALOG_HEAD" ]\nPowod: "C_WHITE"%s\n\n"TEXT_DIALOG_HEAD"\tCzy chcesz odbanowac konto?",
						adminName, strData(year, month, day, " / ", false, false, true, false), hour, minute, string);
					ShowPlayerDialogEx(playerid, DIALOG_HA_ACCOUNT_BAN_INFO, DIALOG_STYLE_MSGBOX, GetHelpStringValue(playerid, 0), string, "Odbanuj", "Wroc");	
				} else {
					freeResult(result, sql_result);
					format(string, sizeof(string), "\tWybrane konto nie jest zbanowane.\n\nJesli chcesz je zablokowac, kliknij przycisk \""C_WHITE"Zbanuj"TEXT_DIALOG_HEAD"\".");
					ShowPlayerDialogEx(playerid, DIALOG_HA_ACCOUNT_BAN_INFO, DIALOG_STYLE_MSGBOX, GetHelpStringValue(playerid, 0), string, "Zbanuj", "Wroc");		
				}				
			} else {	
				new adminLvL, adminStamp;
				adminLvL = strval(getFieldAssoc_8(TK_ADMIN_LVL, result, sql_result));
				adminStamp = strval(getFieldAssoc_16(TK_ADMIN_STAMP, result, sql_result));				
				freeResult(result, sql_result);
				
				if(bantime > timestamp()) {	
					format(string, sizeof(string), "UPDATE `"T_KONTA"` SET `"TK_BAN_TIME"`='0', `"TK_BAN_ADMIN_ID"`='0', `"TK_BAN_REASON"`=' ' WHERE `"TK_UID"`='%d'", userid);
					sendQueryWithout(string);
					format(string, sizeof(string), "Usuniecie blokady konta (Admin: %s  (UID: %d))", getPlayerName(playerid), getPlayerUserID(playerid));
					AddToPlayerLog(userid, string);			
					HSPanelPlayerBanAccount(playerid);
				} else {
					if((adminLvL >= IsAdmin(playerid) and adminStamp > timestamp()) and IsAdmin(playerid) != ALVL_GAME_MASTER) 
						ShowPlayerInfoDialog(playerid, BACK_HA_ACCOUNT_MENU, GetHelpStringValue(playerid, 0), "Nie mozesz zbanowac konta Head Admina, lub Game Mastera.\nTaka mozliwosc maja jedynie administratorzy o poziomie Game Master.");
					else HSPanelPlayerBanTime(playerid);
				}
			}
		} else ShowPlayerInfoDialog(playerid, BACK_HA_ACCOUNT_SEARCH, GetHelpStringValue(playerid, 0), "User ID dla tego konta przestalo istniec w systemie.\nByc moze konto zostalo usuniete.");
		return _TRUE;
	}
	return _FALSE;
}
//---------------------------------------------------------------
HSPanelPlayerBanTime(playerid, data[] = "") {
	if(IsAdmin(playerid) >= ALVL_HEAD_ADMIN) {
		new userid = GetHelpVarValue(playerid, 0);
		if(IsUserIDRegistered(userid) == _TRUE) {
			new string[128];
			if(!isnull(data)) {
				new days;
				if(0 < strlen(data) < 9 and isNumeric(data) and (days = strval(data)) > 0) {
					SetHelpVarValue(playerid, 1, days);
					HSPanelPlayerBanReason(playerid);
					return _TRUE;
				} else strins(string, "        Niepoprawny czas trwania blokady.", 0);				
			} 					
			format(string, sizeof(string), "Podaj w dniach, czas trwania blokady konta.\n\n"TEXT_DIALOG_ALERT"%s", string);
			ShowPlayerDialogEx(playerid, DIALOG_HA_ACCOUNT_BAN_TIME, DIALOG_STYLE_INPUT, GetHelpStringValue(playerid, 0), string, "Dalej", "Wroc");
		} else ShowPlayerInfoDialog(playerid, BACK_HA_ACCOUNT_SEARCH, GetHelpStringValue(playerid, 0), "User ID dla tego konta przestalo istniec w systemie.\nByc moze konto zostalo usuniete.");
		return _TRUE;
	} 
	return _FALSE;
}
//---------------------------------------------------------------
HSPanelPlayerBanReason(playerid, reason[] = "") {
	if(IsAdmin(playerid) >= ALVL_HEAD_ADMIN) {
		new userid = GetHelpVarValue(playerid, 0);
		if(IsUserIDRegistered(userid) == _TRUE) {
			new string[190];
			if(!isnull(reason)) {
				new length;
				if(120 >= (length = strlen(reason)) >= 3) {
					new bool:symbols = false;
					for(new i = length - 1; i >= 0; i --) {
						if(!(
							'a' <= reason[i] <= 'z' or 'A' <= reason[i] <= 'Z' or 
							'0' <= reason[i] <= '9' or reason[i] == ' ' or reason[i] == '_' or 
							reason[i] == '.' or reason[i] == ',' or reason[i] == '(' or 
							reason[i] == ')' or reason[i] == ']' or reason[i] == '[' or 
							reason[i] == '#' or reason[i] == '!' or reason[i] == '?' or
							reason[i] == ':' or reason[i] == '+' or reason[i] == '-')
						) {
							symbols = true;
							break;
						}
					}
					if(symbols == false) {
						SetHelpStringValue(playerid, 1, reason);
						HSPanelPlayerBanConfirm(playerid);
						return _TRUE;
					} else strins(string, "    Powod blokady zawiera niedozwolone symbole.", 0);						
				} else strins(string, "    Powod blokady musi zawierac sie w przedziale\n\t\t  od 3 do 120 znakow.", 0);			
			} 
			format(string, sizeof(string), "       Podaj powod blokady konta gracza. Powod\nmusi zawierac sie w przedziale od 3 do 120 znakow.\n\n"TEXT_DIALOG_ALERT"%s", string);
			ShowPlayerDialogEx(playerid, DIALOG_HA_ACCOUNT_BAN_REASON, DIALOG_STYLE_INPUT, GetHelpStringValue(playerid, 0), string, "Dalej", "Wroc");
		} else ShowPlayerInfoDialog(playerid, BACK_HA_ACCOUNT_SEARCH, GetHelpStringValue(playerid, 0), "User ID dla tego konta przestalo istniec w systemie.\nByc moze konto zostalo usuniete.");
		return _TRUE;
	}
	return _FALSE;
}
//---------------------------------------------------------------
HSPanelPlayerBanConfirm(playerid, bool:confirm = false) {
	if(IsAdmin(playerid) >= ALVL_HEAD_ADMIN) {
		new userid = GetHelpVarValue(playerid, 0);
		if(IsUserIDRegistered(userid) == _TRUE) {
			new string[512];
			if(confirm == false) {
				new year, month, day, hour, minute;
				strins(string, GetHelpStringValue(playerid, 1), 0);
				if(strlen(string) > 55) strins(string, "\n", 55);
				dtimestamp(timestamp() + ToSeconds(GetHelpVarValue(playerid, 1), _DAY), year, month, day, hour, minute);
				format(string, sizeof(string), "Czy na pewno chcesz zbanowac konto '"C_WHITE"%s"TEXT_DIALOG_HEAD"' (UID: "C_WHITE"%d"TEXT_DIALOG_HEAD")?\n\nCzas trwania: "C_WHITE"%d dni\n"TEXT_DIALOG_HEAD"Data odbanowania: "C_WHITE"%s  "TEXT_DIALOG_HEAD"[ "C_WHITE"%d:%02d "TEXT_DIALOG_HEAD"]\nPowod: "C_WHITE"%s\n",
					GetHelpStringValue(playerid, 0), GetHelpVarValue(playerid, 0), GetHelpVarValue(playerid, 1), strData(year, month, day, " / ", false, false, true, false), hour, minute, string);
				ShowPlayerDialogEx(playerid, DIALOG_HA_ACCOUNT_BAN_CONFIRM, DIALOG_STYLE_MSGBOX, GetHelpStringValue(playerid, 0), string, "Zbanuj", "Wroc");
			} else {
				format(string, sizeof(string), "UPDATE `"T_KONTA"` SET `"TK_BAN_TIME"`='%d',`"TK_BAN_ADMIN_ID"`='%d',`"TK_BAN_REASON"`='%s' WHERE `"TK_UID"`='%d'", timestamp() + ToSeconds(GetHelpVarValue(playerid, 1), _DAY), getPlayerUserID(playerid), GetHelpStringValue(playerid, 1), userid);
				sendQueryWithout(string);			

				format(string, sizeof(string), "Blokada konta na czas %d dni z powodu: %s    ( Admin: %s (UID: %d) )", GetHelpVarValue(playerid, 1), GetHelpStringValue(playerid, 1), getPlayerName(playerid), getPlayerUserID(playerid));
				AddToPlayerLog(userid, string);	
				
				forplayers(i) {
					if(getPlayerUserID(i) == userid) {
						format(string, sizeof(string), " (Blokada Konta) Administrator "C_WHITE"%s"TEXT_DIALOG_ALERT" zbanowal gracza "C_WHITE"%s"TEXT_DIALOG_ALERT" (Czas: "C_WHITE"%d dni"TEXT_DIALOG_ALERT").", getPlayerName(playerid), getPlayerName(i), GetHelpVarValue(playerid, 1));
						SendClientMessageToAll(COLOR_DIALOG_ALERT, string);
						format(string, sizeof(string), "    Powod: "C_WHITE"%s", GetHelpStringValue(playerid, 1));
						SendClientMessageToAll(COLOR_DIALOG_ALERT, string);
						KickEx(i, 100);
						break;
					}
				}				
				HSPanelPlayerBanAccount(playerid);
			}
		} else ShowPlayerInfoDialog(playerid, BACK_HA_ACCOUNT_SEARCH, GetHelpStringValue(playerid, 0), "User ID dla tego konta przestalo istniec w systemie.\nByc moze konto zostalo usuniete.");
		return _TRUE;
	}
	return _FALSE;
}
//---------------------------------------------------------------
HSPanelPlayerStatisticReset(playerid, bool:confirm = false) {
	if(IsAdmin(playerid) >= ALVL_HEAD_ADMIN) {
		new userid = GetHelpVarValue(playerid, 0);
		if(IsUserIDRegistered(userid) == _TRUE) {
			if(confirm == false) {
				ShowPlayerYesNoDialog(playerid, D_YESNO_HA_PSTAT_RESET, GetHelpStringValue(playerid, 0), "  W tym menu mozesz zresetowac wszystkie statstyki gracza.\n  Obejmuja one ilosc fragow, smierci, dmg itp., nie obejmuja\nnatomiast zadnych informacji niezbednych do istnienia konta.\n\t       "TEXT_DIALOG_ALERT"Reset statystyk jest nieodrwacalny!\n\n"TEXT_DIALOG_HEAD"\tCzy chcesz zresetowac statystyki gracza?");
			} else {
				new string[128];
				
				CallLocalFunction("ResetAccountStatistics", "dd", userid, playerid);
				
				format(string, sizeof(string), "Statystyki gracza "C_WHITE"%s "TEXT_DIALOG_HEAD"zostaly usuniete.", GetHelpStringValue(playerid, 0));
				ShowPlayerInfoDialog(playerid, BACK_HA_ACCOUNT_MENU, GetHelpStringValue(playerid, 0), string);
				
				format(string, sizeof(string), "Administrator %s (UID: %d) zresetowal(a) statystyki konta", getPlayerName(playerid), getPlayerUserID(playerid));
				AddToPlayerLog(userid, string);									
			}
		} else ShowPlayerInfoDialog(playerid, BACK_HA_ACCOUNT_SEARCH, GetHelpStringValue(playerid, 0), "User ID dla tego konta przestalo istniec w systemie.\nByc moze konto zostalo usuniete.");
		return _TRUE;
	}
	return _FALSE;
}
//---------------------------------------------------------------
HAPanelPlayerVIPPremiumMenu(playerid, listitem = -1) {
	if(IsAdmin(playerid) == ALVL_GAME_MASTER) {
		new userid = GetHelpVarValue(playerid, 0);
		if(IsUserIDRegistered(userid) == _TRUE) {
			switch(listitem) {
				case 0, 1: {
					SetHelpVarValue(playerid, 1, listitem);
					HAPanelPlayerVIPPremiumPoints(playerid);
				}
				case 2: {
					HAPanelPlayerVIPAccount(playerid);
				}
				default: {
					ShowPlayerDialogEx(playerid, DIALOG_HA_ACCOUNT_VIPMENU, DIALOG_STYLE_LIST, GetHelpStringValue(playerid, 0), "1) Ustaw punkty premium (gracza)\n2) Ustaw punkty premium (bonusowe)\n3) Ustaw date konta VIP", "Dalej", "Wroc");
				}
			}
			return _TRUE;
		} else ShowPlayerInfoDialog(playerid, BACK_HA_ACCOUNT_SEARCH, GetHelpStringValue(playerid, 0), "User ID dla tego konta przestalo istniec w systemie.\nByc moze konto zostalo usuniete.");	
	}
	return _FALSE;
}
//---------------------------------------------------------------
HAPanelPlayerVIPPremiumPoints(playerid, s_points[] = "") {
	if(IsAdmin(playerid) == ALVL_GAME_MASTER) {
		new string[512], DBResult: result, Result:sql_result;
		new userid = GetHelpVarValue(playerid, 0);
		format(string, sizeof(string), "SELECT `"TK_PREMIUM_PLAYER_POINT"`, `"TK_PREMIUM_BONUS_POINT"` FROM `"T_KONTA"` WHERE `"TK_UID"`='%d' LIMIT 1", userid);
		result = sendQueryResult(string, sql_result);
		
		if(numRows(result, sql_result) == 1) {
			new pointsType = GetHelpVarValue(playerid, 1);
			new playerVipPoints = strval(getFieldAssoc_16(TK_PREMIUM_PLAYER_POINT, result, sql_result));
			new bonusVipPoints = strval(getFieldAssoc_16(TK_PREMIUM_BONUS_POINT, result, sql_result));
			freeResult(result, sql_result);
			strdel(string, 0, 128);
			
			if(!isnull(s_points) and strlen(s_points) <= 5) {
				new bool:error;				
				for(new i = strlen(s_points) - 1; i >= 0; i --) {
					if(!('0' <= s_points[i] <= '9')) {
						if((s_points[i] == '-' or s_points[i] == '+') and i == 0) continue;
						else {
							error = true;
							break;
						}
					}
				}			
		
				if((s_points[0] == '-' or s_points[0] == '+') and strlen(s_points) == 1) error = true;
				
				if(error == false) {	
					new test_value[8];
					strins(test_value, s_points, 0);
					if(test_value[0] == '+') strdel(test_value, 0, 1);							
					if(strlen(test_value) > 0 and -9999 <= strval(test_value) <= 9999) {
						new bool:error_Value;
						new value;
						if((value = strval(s_points)) < 0) {
							error_Value = (pointsType == 0 ? (playerVipPoints + value < 0 ? true : false) : (bonusVipPoints + value < 0 ? true : false));
						}
						if(error_Value == false) {
							SetHelpStringValue(playerid, 1, s_points);					
							HAPanelPlayerVIPPremiumConfirm(playerid);
							return _TRUE;
						} strins(string, C_ADMIN"\t  Nowa wartosc punktow, po odjeciu nie moze byc mniejsza od zera.", 0);
					} else strins(string, C_ADMIN"\t\t\t\t  Niepoprawna wartosc.", 0);
				} else strins(string, C_ADMIN"\t\t\t\t  Niepoprawna wartosc.", 0);
			}
			format(string, sizeof(string), 
					"W tym menu mozesz ustawic, dodac lub odjac punkty premium o charakterze "C_WHITE"%s"TEXT_DIALOG_HEAD".\
					\n\tZeby ustawic punkty, wystarczy wpisac wartosc z przedzialu 0 - 9999.\
					\n        Zeby dodac lub odjac punkty od aktualnej puli nalezy uzyc prefiksu '+' lub '-',\n\
					\t\ta nastepnie podac wartosc z przedzialu 0 - 9999.\
					\n             Aktualnie gracz posiada "C_WHITE"%d"TEXT_DIALOG_HEAD" punktow wlasnych i "C_WHITE"%d"TEXT_DIALOG_HEAD" punktow bonusowych.\n\n\
					%s", 
				pointsType == 0 ? ("wlasnym") : ("bonusowym"), 		
				playerVipPoints, bonusVipPoints,
				string
			);
			ShowPlayerDialogEx(playerid, DIALOG_HA_ACCOUNT_VIPPOINTS, DIALOG_STYLE_INPUT, GetHelpStringValue(playerid, 0), string, "Dalej", "Wroc");
			
			return _TRUE;
		} else ShowPlayerInfoDialog(playerid, BACK_HA_ACCOUNT_SEARCH, GetHelpStringValue(playerid, 0), "User ID dla tego konta przestalo istniec w systemie.\nByc moze konto zostalo usuniete.");
	}
	return _FALSE;
}
//---------------------------------------------------------------
HAPanelPlayerVIPPremiumConfirm(playerid, bool:confirm = false) {
	if(IsAdmin(playerid) == ALVL_GAME_MASTER) {
		new string[512], DBResult: result, Result:sql_result;
		new userid = GetHelpVarValue(playerid, 0);
		format(string, sizeof(string), "SELECT `"TK_PREMIUM_PLAYER_POINT"`, `"TK_PREMIUM_BONUS_POINT"` FROM `"T_KONTA"` WHERE `"TK_UID"`='%d' LIMIT 1", userid);
		result = sendQueryResult(string, sql_result);
		
		if(numRows(result, sql_result) == 1) {
			new s_newValue[8], p_Name[MAX_PLAYER_NAME];
			new type, value;
			new pointsType = GetHelpVarValue(playerid, 1);
			new playerVipPoints = strval(getFieldAssoc_16(TK_PREMIUM_PLAYER_POINT, result, sql_result));
			new bonusVipPoints = strval(getFieldAssoc_16(TK_PREMIUM_BONUS_POINT, result, sql_result));
			new afterPlayerVipPoints = playerVipPoints;
			new afterPlayerBonusVipPoints = bonusVipPoints;
			strins(p_Name, GetHelpStringValue(playerid, 0), 0);
			freeResult(result, sql_result);
			strins(s_newValue, GetHelpStringValue(playerid, 1), 0);
			switch((type = s_newValue[0] == '+' ? 1 : s_newValue[0] == '-' ? -1 : 0)) {
				case 1: {
					strdel(s_newValue, 0, 1);
					if(pointsType == 0) afterPlayerVipPoints += (value = strval(s_newValue));
					else afterPlayerBonusVipPoints += (value = strval(s_newValue));
				}
				case -1: {
					strdel(s_newValue, 0, 1);
					if(pointsType == 0) afterPlayerVipPoints -= (value = strval(s_newValue));
					else afterPlayerBonusVipPoints -= (value = strval(s_newValue));
				}
				case 0: {
					if(pointsType == 0) afterPlayerVipPoints = (value = strval(s_newValue));
					else afterPlayerBonusVipPoints = (value = strval(s_newValue));					
				}
			}
			if(confirm == true) {
				switch(type) {
					case 1: format(string, sizeof(string), " (Punkty Premium) Administrator '%s' dodal(a) %d %s punktow premium do Twojego konta (Stara wartosc: %d | Nowa wartosc: %d).", getPlayerName(playerid), value, pointsType == 0 ? ("wlasnych") : ("bonusowych"), pointsType == 0 ? playerVipPoints : bonusVipPoints, pointsType == 0 ? afterPlayerVipPoints : afterPlayerBonusVipPoints);
					case -1: format(string, sizeof(string), " (Punkty Premium) Administrator '%s' odjal(ela) %d %s punktow premium od Twojego konta (Stara wartosc: %d | Nowa wartosc: %d).", getPlayerName(playerid), value, pointsType == 0 ? ("wlasnych") : ("bonusowych"), pointsType == 0 ? playerVipPoints : bonusVipPoints, pointsType == 0 ? afterPlayerVipPoints : afterPlayerBonusVipPoints);
					case 0: format(string, sizeof(string), " (Punkty Premium) Administrator '%s' ustawil(a) stan Twoich %s punktow premium na %d (Stara wartosc: %d).", getPlayerName(playerid), pointsType == 0 ? ("wlasnych") : ("bonusowych"), value, pointsType == 0 ? playerVipPoints : bonusVipPoints);
				}
				forplayers(i) {
					if(getPlayerUserID(i) == userid) {
						SetPlayerVIPSelfPoints(i, afterPlayerVipPoints);
						SetPlayerBonusPoints(i, afterPlayerBonusVipPoints);
						SendClientMessage(i, COLOR_GOLD, string);
						break;
					}
				}

				switch(type) {
					case 1: {
						format(string, sizeof(string), "Administrator '%s' dodal(a) %d %s punktow premium do konta '%s' (UID: %d) (Stara wartosc: %d | Nowa wartosc: %d).", getPlayerName(playerid), value, pointsType == 0 ? ("wlasnych") : ("bonusowych"), p_Name, userid, pointsType == 0 ? playerVipPoints : bonusVipPoints, pointsType == 0 ? afterPlayerVipPoints : afterPlayerBonusVipPoints);
					}
					case -1: {
						format(string, sizeof(string), "Administrator '%s' odjal(ela) %d %s punktow premium od konta '%s' (UID: %d) (Stara wartosc: %d | Nowa wartosc: %d).", getPlayerName(playerid), value, pointsType == 0 ? ("wlasnych") : ("bonusowych"), p_Name, userid, pointsType == 0 ? playerVipPoints : bonusVipPoints, pointsType == 0 ? afterPlayerVipPoints : afterPlayerBonusVipPoints);
					}
					case 0: {
						format(string, sizeof(string), "Administrator '%s' ustawil(a) stan %s punktow premium konta '%s' (UID: %d) na %d (Stara wartosc: %d).", getPlayerName(playerid), pointsType == 0 ? ("wlasnych") : ("bonusowych"), p_Name, userid, value, pointsType == 0 ? playerVipPoints : bonusVipPoints);
					}
				}				
				AddToPlayerLog(userid, string);
				AddToVIPLog(string);	
				
				format(string, sizeof(string), "UPDATE `"T_KONTA"` SET `"TK_PREMIUM_PLAYER_POINT"`='%d', `"TK_PREMIUM_BONUS_POINT"`='%d' WHERE `"TK_UID"`='%d'", afterPlayerVipPoints, afterPlayerBonusVipPoints, userid);
				sendQueryWithout(string);
				
				format(string, sizeof(string), "\
						Wartosc %s punktow premium gracza zostala zmieniona.\n\n\
						Stara wartosc: "C_WHITE"%d"TEXT_DIALOG_HEAD" punktow wlasnych i "C_WHITE"%d"TEXT_DIALOG_HEAD" punktow bonusowych.\n\
						Nowa wartosc: "C_WHITE"%d"TEXT_DIALOG_HEAD" punktow wlasnych i "C_WHITE"%d"TEXT_DIALOG_HEAD" punktow bonusowych.\n ",
					pointsType == 0 ? ("wlasnych") : ("bonusowych"),
					playerVipPoints, bonusVipPoints,
					afterPlayerVipPoints, afterPlayerBonusVipPoints
				);
				ShowPlayerInfoDialog(playerid, BACK_HA_ACCOUNT_VIPMENU, p_Name, string);					
			} else {
				format(string, sizeof(string),"\
						Czy na pewno chcesz "C_WHITE"%s %d %s "TEXT_DIALOG_HEAD"punktow premium graczu "C_WHITE"%s"TEXT_DIALOG_HEAD"?\
						\n    Aktualnie posiada on "C_WHITE"%d"TEXT_DIALOG_HEAD" punktow wlasnych i "C_WHITE"%d"TEXT_DIALOG_HEAD" punktow bonusowych,\
						\npo zmianie bedzie posiadal "C_WHITE"%d"TEXT_DIALOG_HEAD" punktow wlasnych i "C_WHITE"%d"TEXT_DIALOG_HEAD" punktow bonusowych.\n\n\
						\tCzy potwierdzasz chec dokonania zmian na koncie gracza?\
					",
					type == 0 ? ("ustawic") : type == 1 ? ("dodac") : ("odjac"), 
					value, 
					pointsType == 0 ? ("wlasnych") : ("bonusowych"), 
					p_Name,
					playerVipPoints, bonusVipPoints,
					afterPlayerVipPoints, afterPlayerBonusVipPoints
				);
				ShowPlayerYesNoDialog(playerid, D_YESNO_HA_PANEL_VIP_POINTS, p_Name, string);				
			}
			return _TRUE;
		} else ShowPlayerInfoDialog(playerid, BACK_HA_ACCOUNT_SEARCH, GetHelpStringValue(playerid, 0), "User ID dla tego konta przestalo istniec w systemie.\nByc moze konto zostalo usuniete.");		
	}
	return _FALSE;
}
//---------------------------------------------------------------
HAPanelPlayerVIPAccount(playerid, time[] = "") {
	if(IsAdmin(playerid) == ALVL_GAME_MASTER) {
		new string[512], DBResult: result, Result:sql_result;
		new userid = GetHelpVarValue(playerid, 0);
		format(string, sizeof(string), "SELECT `"TK_PREMIUM_DATE"` FROM `"T_KONTA"` WHERE `"TK_UID"`='%d' LIMIT 1", userid);
		result = sendQueryResult(string, sql_result);
		
		if(numRows(result, sql_result) == 1) {
			new vipActive[128];
			new playerVipTime = strval(getFieldAssoc_16(TK_PREMIUM_DATE, result, sql_result));
			freeResult(result, sql_result);
			strdel(string, 0, 128);
			if(playerVipTime <= timestamp()) playerVipTime = 0;
			
			
			if(!isnull(time) and strlen(time) <= 4) {
				new bool:error;				
				for(new i = strlen(time) - 1; i >= 0; i --) {
					if(!('0' <= time[i] <= '9')) {
						if((time[i] == '-' or time[i] == '+') and i == 0) continue;
						else {
							error = true;
							break;
						}
					}
				}	
				if((time[0] == '-' or time[0] == '+') and strlen(time) == 1) error = true;
				
				if(error == false) {	
					new test_value[8];
					strins(test_value, time, 0);
					if(test_value[0] == '+') strdel(test_value, 0, 1);							
					if(strlen(test_value) > 0 and -365 <= strval(test_value) <= 365) {
						if(strval(test_value) < 0) {
							if((playerVipTime - ToSeconds(strval(test_value[1]), _DAY)) < timestamp()) {
								time[0] = '0';
								time[1] = EOS;
							}
						}
						SetHelpStringValue(playerid, 1, time);					
						HAPanelPlayerVIPTimeConfirm(playerid);
						return _TRUE;
					} else strins(string, C_ADMIN"\t\t\t\tNiepoprawna wartosc.", 0);
				} else strins(string, C_ADMIN"\t\t\t\tNiepoprawna wartosc.", 0);
			}
			
			if(playerVipTime > 0) {
				new year, month, day, hour, minute;
				dtimestamp(playerVipTime, year, month, day, hour, minute);
				format(vipActive, sizeof(vipActive), C_LIGHTGREEN"Aktywne "TEXT_DIALOG_HEAD"( "C_WHITE"%s  "TEXT_DIALOG_HEAD"[ "C_WHITE"%d:%02d "TEXT_DIALOG_HEAD"] )", strData(year, month, day, " / ", false, false, true, false), hour, minute);
			} else strins(vipActive, C_ADMIN"Nieaktywne", 0);
			format(string, sizeof(string), 
					"    W tym menu mozesz ustawic, dodac lub odjac czas trwania konta VIP dla gracza.\
					\n  Zeby ustawic czas trwania w dniach, wystarczy wpisac wartosc z przedzialu 0 - 365.\
					\nZeby przedluzyc lub skrocic czas trwania aktywnych przywilejow nalezy uzyc prefiksu\
					\n\t         '+' lub '-', a nastepnie podac wartosc z przedzialu 0 - 365.\
					\n\tAktualny stan konta VIP gracza to: %s\n\n\
					%s", 
				vipActive,
				string
			);
			ShowPlayerDialogEx(playerid, DIALOG_HA_ACCOUNT_VIPTIME, DIALOG_STYLE_INPUT, GetHelpStringValue(playerid, 0), string, "Dalej", "Wroc");
			
			return _TRUE;
		} else ShowPlayerInfoDialog(playerid, BACK_HA_ACCOUNT_SEARCH, GetHelpStringValue(playerid, 0), "User ID dla tego konta przestalo istniec w systemie.\nByc moze konto zostalo usuniete.");
	}
	return _FALSE;
}
//---------------------------------------------------------------
HAPanelPlayerVIPTimeConfirm(playerid, bool:confirm = false) {
	if(IsAdmin(playerid) == ALVL_GAME_MASTER) {
		new string[512], DBResult: result, Result:sql_result;
		new userid = GetHelpVarValue(playerid, 0);
		format(string, sizeof(string), "SELECT `"TK_PREMIUM_DATE"` FROM `"T_KONTA"` WHERE `"TK_UID"`='%d' LIMIT 1", userid);
		result = sendQueryResult(string, sql_result);
		
		if(numRows(result, sql_result) == 1) {
			new s_newValue[8], p_Name[MAX_PLAYER_NAME];
			new value, type;
			new vipTime = strval(getFieldAssoc_16(TK_PREMIUM_DATE, result, sql_result));
			new afterPlayerVipTime = vipTime < timestamp() ? timestamp() : vipTime;
			new s_OldTime[16], s_NewTime[16];
			strins(p_Name, GetHelpStringValue(playerid, 0), 0);
			freeResult(result, sql_result);
			
			strins(s_newValue, GetHelpStringValue(playerid, 1), 0);
			switch((type = s_newValue[0] == '+' ? 1 : s_newValue[0] == '-' ? -1 : 0)) {
				case 1: {
					strdel(s_newValue, 0, 1);
					afterPlayerVipTime += ((value = strval(s_newValue)) * SECONDS_DAY);
				}
				case -1: {
					strdel(s_newValue, 0, 1);
					afterPlayerVipTime -= ((value = strval(s_newValue)) * SECONDS_DAY);
				}
				case 0: {
					afterPlayerVipTime = timestamp() + ((value = strval(s_newValue)) * SECONDS_DAY);				
				}
			}
			
			strins(s_OldTime, convertSeconds(vipTime - timestamp()), 0);
			if(strlen(s_OldTime) == 0) strins(s_OldTime, "Brak", 0);
			strins(s_NewTime, convertSeconds(afterPlayerVipTime - timestamp()), 0);
			if(strlen(s_NewTime) == 0) strins(s_NewTime, "Brak", 0);
			
			if(confirm == true) {
				switch(type) {
					case 1: format(string, sizeof(string), " (Punkty Premium) Administrator '%s' dodal(a) %d dni do Twojego konta VIP (Stara wartosc: %s | Nowa wartosc: %s).", getPlayerName(playerid), value, s_OldTime, s_NewTime);
					case -1: format(string, sizeof(string), " (Punkty Premium) Administrator '%s' odjal(ela) %d dni od Twoje konta premium (Stara wartosc: %s | Nowa wartosc: %s).", getPlayerName(playerid), value, s_OldTime, s_NewTime );
					case 0: format(string, sizeof(string), " (Punkty Premium) Administrator '%s' ustawil(a) stan Twojego konta premium na %d dni (Stara wartosc: %s).", getPlayerName(playerid), value, s_OldTime);
				}
				forplayers(i) {
					if(getPlayerUserID(i) == userid) {
						SetPlayerVIPTime(i, afterPlayerVipTime);
						SendClientMessage(i, COLOR_GOLD, string);
						break;
					}
				}

				switch(type) {
					case 1: {
						format(string, sizeof(string), "Administrator '%s' dodal(a) %d dni konta premium dla gracza '%s' (UID: %d) (Stara wartosc: %s | Nowa wartosc: %s).", getPlayerName(playerid), value, p_Name, userid, s_OldTime, s_NewTime);
					}
					case -1: {
						format(string, sizeof(string), "Administrator '%s' odjal(ela) %d dni konta premium dla gracza '%s' (UID: %d) (Stara wartosc: %s | Nowa wartosc: %s).", getPlayerName(playerid), value, p_Name, userid, s_OldTime, s_NewTime);
					}
					case 0: {
						format(string, sizeof(string), "Administrator '%s' ustawil(a) stan trwania konta premium gracza '%s' (UID: %d) na %d dni (Stara wartosc: %s).", getPlayerName(playerid), p_Name, userid, value, s_OldTime);
					}
				}				
				AddToPlayerLog(userid, string);
				AddToVIPLog(string);	
				
				format(string, sizeof(string), "UPDATE `"T_KONTA"` SET `"TK_PREMIUM_DATE"`='%d'WHERE `"TK_UID"`='%d'", afterPlayerVipTime, userid);
				sendQueryWithout(string);
				
				format(string, sizeof(string), "\
						Czas trwania konta premium gracza zostala zmieniona.\n\n\
						Stara wartosc: "C_WHITE"%s"TEXT_DIALOG_HEAD".\n\
						Nowa wartosc: "C_WHITE"%s"TEXT_DIALOG_HEAD"\n ",
					s_OldTime, 
					s_NewTime
				);
				ShowPlayerInfoDialog(playerid, BACK_HA_ACCOUNT_VIPMENU, p_Name, string);					
			} else {
				format(string, sizeof(string),"\
						Czy na pewno chcesz "C_WHITE"%s %d dni "TEXT_DIALOG_HEAD"konta VIP graczu "C_WHITE"%s"TEXT_DIALOG_HEAD"?\
						\nAktualny czas trwania przywilejow VIP to: "C_WHITE"%s"TEXT_DIALOG_HEAD", po zmianie: "C_WHITE"%s"TEXT_DIALOG_HEAD".\n\
						\nCzy potwierdzasz chec dokonania zmian na koncie gracza?\
					",
					type == 0 ? ("ustawic") : type == 1 ? ("dodac") : ("odjac"), 
					value, 
					p_Name,
					s_OldTime, 
					s_NewTime					
				);
				ShowPlayerYesNoDialog(playerid, D_YESNO_HA_PANEL_VIP_TIME, p_Name, string);				
			}
			return _TRUE;
		} else ShowPlayerInfoDialog(playerid, BACK_HA_ACCOUNT_SEARCH, GetHelpStringValue(playerid, 0), "User ID dla tego konta przestalo istniec w systemie.\nByc moze konto zostalo usuniete.");		
	}
	return _FALSE;
}
//---------------------------------------------------------------
HSPanelRCONAccount(playerid, bool:confirm = false) {
	if(IsAdmin(playerid) == ALVL_GAME_MASTER) {
		new DBResult: result, Result:sql_result;
		new userid = GetHelpVarValue(playerid, 0);
		new string[330];
		
		format(string, sizeof(string), "SELECT `"TK_RCON_ADMIN"` FROM `"T_KONTA"` WHERE `"TK_UID"`='%d' LIMIT 1", userid);
		result = sendQueryResult(string, sql_result);			
		
		if(numRows(result, sql_result) > 0) {	
			new rcon_priv = strval(getFieldAssoc_8(TK_RCON_ADMIN, result, sql_result));
			freeResult(result, sql_result);
			
			if(confirm == false) {		
				format(string, sizeof(string), 
					"   W tym menu, mozesz zmienic status konta RCON dla tego gracza.\nWlaczenie przywilejow RCON, przy wlaczonym systemie 'Kont RCON'\n  spowoduje, ze ten gracz bedzie mogl logowac sie na konto RCON.\n\n\t         Aktualny stan przywilejow RCON: %s\n\n"TEXT_DIALOG_HEAD"        Czy chcesz zmienic stan przywilejow RCON dla tego konta?", 
					rcon_priv == 0 ? (C_ADMIN"Wylaczone") : (C_LIGHTGREEN"Wlaczone")
				);
				ShowPlayerYesNoDialog(playerid, D_YESNO_HA_RCONACCOUNT, GetHelpStringValue(playerid, 0), string);
			} else {
				format(string, sizeof(string), "Administrator %s (UID: %d) zmienil stan przywilejow RCON na: %s", getPlayerName(playerid), getPlayerUserID(playerid), rcon_priv == 0 ? ("Wlaczone") : ("Wylaczone"));
				AddToPlayerLog(userid, string);					
				format(string, sizeof(string), "UPDATE `"T_KONTA"` SET `"TK_RCON_ADMIN"`='%d' WHERE `"TK_UID"`='%d'", rcon_priv == 0 ? 1 : 0, userid);
				sendQueryWithout(string);
				format(string, sizeof(string), "Stan konta RCON dla gracza '%s' zostal zmieniony na: %s", GetHelpStringValue(playerid, 0), rcon_priv == 0 ? (C_LIGHTGREEN"Wlaczone") : (C_ADMIN"Wylaczone"));
				ShowPlayerInfoDialog(playerid, BACK_HA_ACCOUNT_MENU, GetHelpStringValue(playerid, 0), string);
				
				format(string, sizeof(string), " (Konto RCON) Stan Twojego konta RCON zostal zmieniony na '%s"TEXT_DIALOG_HEAD"'.", rcon_priv == 0 ? (C_LIGHTGREEN"Wlaczone") : (C_ADMIN"Wylaczone"));
				forplayers(i) {
					if(userid == getPlayerUserID(i)) {
						SetPVarInt(i, PV_LOGIN_RCON_ADMIN, rcon_priv == 0 ? 1 : 0);
						SendClientMessage(playerid, COLOR_DIALOG_HEAD, string);
						break;
					}
				}								
			}
		} else ShowPlayerInfoDialog(playerid, BACK_HA_ACCOUNT_SEARCH, GetHelpStringValue(playerid, 0), "User ID dla tego konta przestalo istniec w systemie.\nByc moze konto zostalo usuniete.");
		return _TRUE;
	}
	return _FALSE;
}
//---------------------------------------------------------------
HSPanelPlayerDeleteAccount(playerid, bool:confirm = false) {
	if(IsAdmin(playerid) == ALVL_GAME_MASTER) {
		new userid = GetHelpVarValue(playerid, 0);
		if(IsUserIDRegistered(userid) == _TRUE) {
			if(confirm == false) {
				ShowPlayerYesNoDialog(playerid, D_YESNO_HA_ACCDELETE, GetHelpStringValue(playerid, 0), "W tym menu mozesz zresetowac usunac z serwera konto gracza.\n     Spowoduje to calkowite wymazanie danych dot. tego konta\n\t\t        z bazy danych serwera.\n\n\t    "TEXT_DIALOG_ALERT"USUNIECIE KONTA JEST NIEODWRACALNE!\n\n"TEXT_DIALOG_HEAD"\t\tCzy chcesz "TEXT_DIALOG_ALERT"usunac "TEXT_DIALOG_HEAD"konto gracza?");
			} else {
				new string[128];
				
				DeletePlayerAccount(userid, playerid);
				
				format(string, sizeof(string), "Konto gracza "C_WHITE"%s "TEXT_DIALOG_HEAD"zostalo usuniete.", GetHelpStringValue(playerid, 0));
				ShowPlayerInfoDialog(playerid, BACK_HA_ACCOUNT_SEARCH, GetHelpStringValue(playerid, 0), string);							
			}
		} else ShowPlayerInfoDialog(playerid, BACK_HA_ACCOUNT_SEARCH, GetHelpStringValue(playerid, 0), "User ID dla tego konta przestalo istniec w systemie.\nByc moze konto zostalo usuniete.");
		return _TRUE;
	}
	return _FALSE;
}

//===============================================================
//---------------------------------------------------------------
//===============================================================
/*
	2) Baza rejestrowanych kont
*/
//===============================================================
//---------------------------------------------------------------
//===============================================================
HAPanelRegisterBase(playerid, listitem = -1) {
	if(IsAdmin(playerid) >= ALVL_HEAD_ADMIN) {
		switch(listitem) {
			case 0: HAPanelRegisterBaseSearch(playerid);
			case 1: {
				SetHelpVarValue(playerid, 99, 0);
				HARegisterBaseList(playerid);
			}
			default: ShowPlayerDialogEx(playerid, DIALOG_HA_REGISTER_BASE_MENU, DIALOG_STYLE_LIST, "Baza rejestrowanych kont", "1) Wyszukaj dane dot. rejestracji konta\n2) Lista kont", "Dalej", "Wroc");
		}
		return _TRUE;
	}
	return _FALSE;
}
//===============================================================
HAPanelRegisterBaseSearch(playerid, data[] = "") {
	if(IsAdmin(playerid) >= ALVL_HEAD_ADMIN) {
		new string[256];
		if(!isnull(data)) {			
			new type, date_from, date_to, bool:search_front, bool:search_end, bool:sorttype_desc, errorid;
			if(SearchDataSplit(data, type, date_from, date_to, search_front, search_end, sorttype_desc, errorid) == _TRUE) {
				switch(type) {
					case DATA_TYPE_NON: 	strins(string, "Niepoprawny typ danych do wyszukania.", 0);
					case DATA_TYPE_ADMINID, DATA_TYPE_ADMIN_NICK: 	strins(string, "Ten typ wyszukiwania nie jest obslugiwany w tym menu.", 0);
					default: {
						if(type == DATA_TYPE_ONLINE) {
							SetHelpVarValue(playerid, 21, DATA_TYPE_NICK);
							SetHelpStringValue(playerid, 20, getPlayerName(strval(data)));
							SetHelpVarValue(playerid, 25, false);
							SetHelpVarValue(playerid, 24, false);
						} else if(type == DATA_TYPE_HOST) {
							SetHelpVarValue(playerid, 21, DATA_TYPE_IP);
							format(string, sizeof(string),"%s.", data);
							SetHelpStringValue(playerid, 20, string);
							SetHelpVarValue(playerid, 25, true);
							SetHelpVarValue(playerid, 24, false);
						} else {
							SetHelpVarValue(playerid, 21, type);
							SetHelpStringValue(playerid, 20, data);
							SetHelpVarValue(playerid, 25, _:search_end);
							SetHelpVarValue(playerid, 24, _:search_front);
						}	
					
						SetHelpVarValue(playerid, 99, 1);						
						SetHelpVarValue(playerid, 22, date_from);
						SetHelpVarValue(playerid, 23, date_to);						
						SetHelpVarValue(playerid, 26, _:sorttype_desc);
						HARegisterBaseList(playerid);
						return _TRUE;
					}
				}
			} else {
				switch(errorid) {
					case DATA_ERROR_HELP: {
						ShowPlayerSearchInfo(playerid, SI_REGISTER_BASE);
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
		format(string, sizeof(string), "     Podaj interesujacy Cie typ danych pod katem, ktorych\nma zostac przeszukana baza danych 'Rejestrowanych Kont'.\n     Info: Jesli nie wiesz jak poslugiwac sie wyszukiwarka,\n\t\twpisz polecenie '<INFO>'.\n\n"TEXT_DIALOG_ALERT"%s", string);
		ShowPlayerDialogEx(playerid, DIALOG_HA_REGISTER_BASE_SEARCH, DIALOG_STYLE_INPUT, "Baza rejestrowanych kont - Wyszukiwarka", string, "Wyszukaj", "Wroc");
		
		return _TRUE;
	}	
	return _FALSE;
}
//---------------------------------------------------------------
RegisterBaseMakeQuery(playerid, page) {
	new string[256];
	switch(GetHelpVarValue(playerid, 21)) {
		case DATA_TYPE_NICK: {
			strins(string, GetHelpStringValue(playerid, 20), 0);
			ConvertNick(string);
			format(string, sizeof(string), "SELECT `"TK_UID"`, `"TK_NICK"`, `"TK_REGISTER_IP"` FROM `"T_KONTA"` WHERE `"TK_NICK"` LIKE '%s%s%s' AND `"TK_REGISTER_STAMP"` >= '%d' AND `"TK_REGISTER_STAMP"` <= '%d' ORDER BY `"TK_REGISTER_STAMP"` %s LIMIT %d, 11", 
				GetHelpVarValue(playerid, 24) == 1 ? ("%") : (""), string, GetHelpVarValue(playerid, 25) == 1 ? ("%") : (""), 
				GetHelpVarValue(playerid, 22), GetHelpVarValue(playerid, 23),						
				GetHelpVarValue(playerid, 26) == 0 ? ("ASC") : ("DESC"), 
				page * 10);
		}
		case DATA_TYPE_USERID: {
			format(string, sizeof(string), "SELECT `"TK_UID"`, `"TK_NICK"`, `"TK_REGISTER_IP"` FROM `"T_KONTA"` WHERE `"TK_UID"` = '%s' AND `"TK_REGISTER_STAMP"` >= '%d' AND `"TK_REGISTER_STAMP"` <= '%d' ORDER BY `"TK_REGISTER_STAMP"` %s LIMIT %d, 11", 
				GetHelpStringValue(playerid, 20),
				GetHelpVarValue(playerid, 22), GetHelpVarValue(playerid, 23),		
				GetHelpVarValue(playerid, 26) == 0 ? ("ASC") : ("DESC"),
				page * 10);					
		}
		case DATA_TYPE_IP: {
			format(string, sizeof(string), "SELECT `"TK_UID"`, `"TK_NICK"`, `"TK_REGISTER_IP "` FROM `"T_KONTA"` WHERE `"TK_REGISTER_IP"` LIKE '%s%s%s' AND `"TK_REGISTER_STAMP"` >= '%d' AND `"TK_REGISTER_STAMP"` <= '%d' ORDER BY `"TK_REGISTER_STAMP"` %s LIMIT %d, 11", 
				GetHelpVarValue(playerid, 24) == 1 ? ("%") : (""), GetHelpStringValue(playerid, 20), GetHelpVarValue(playerid, 25) == 1 ? ("%") : (""), 
				GetHelpVarValue(playerid, 22), GetHelpVarValue(playerid, 23),		
				GetHelpVarValue(playerid, 26) == 0 ? ("ASC") : ("DESC"),
				page * 10);				
		}		
	}
	return string;
}
//===============================================================
HARegisterBaseList(playerid, page = 0) {
	if(IsAdmin(playerid) >= ALVL_HEAD_ADMIN) {
		new string[800];
		new DBResult: result, Result:sql_result;
		new rows;

		if(page < 0) page = 0;
		
		if(GetHelpVarValue(playerid, 99) == 0) {		
			format(string, sizeof(string), "SELECT `"TK_NICK"`, `"TK_REGISTER_IP"` FROM `"T_KONTA"` ORDER BY `"TK_REGISTER_STAMP"` DESC LIMIT %d, 11", page * 10);
		} else {
			strins(string, RegisterBaseMakeQuery(playerid, page), 0);
		}
		
		result = sendQueryResult(string, sql_result);
		//_______________________	
		strdel(string, 0, 256);
		rows = numRows(result, sql_result);
		if(numRows(result, sql_result) > 0) {
			new bool:isNextPage = rows == 11 ? true : false;
			
			new read[64], index = 0;
			for(new limit = rows == 11 ? 10 : rows; index < limit; index ++) {
				strdel(read, 0, 32);				
				strins(read, getFieldAssoc_32(TK_NICK, result, sql_result), 0);				
				DeconvertNick(read);
				format(string, sizeof(string), "%s\n%d) %s\t\t"TEXT_DIALOG_HEAD"[ "TEXT_DIALOG_NORMAL"%s"TEXT_DIALOG_HEAD" ]", string, page * 10 + index + 1, CutName(read), CutName(getFieldAssoc_16(TK_REGISTER_IP, result, sql_result)));
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
			ShowPlayerDialogEx(playerid, DIALOG_HA_REGISTER_BASE_LIST, DIALOG_STYLE_LIST, "Baza rejestrowanych kont - Lista", string, "Sprawdz", "Wroc");
			return _TRUE;
		} else {
			if(GetHelpVarValue(playerid, 99) == 0) {
				ShowPlayerInfoDialog(playerid, BACK_HA_REGISTER_MENU, "Baza rejestrowanych kont - Lista", "Brak danych do sprawdzenia w bazie. Sprobuj pozniej.");
			} else {
				ShowPlayerInfoDialog(playerid, BACK_HA_REGISTER_SEARCH, "Baza rejestrowanych kont - Wyszukiwarka", "Nieznaleziono rezultatow dla podanych danych.");	
			}
		}
		//_______________________	
	}
	return _FALSE;
}
//---------------------------------------------------------------
HARegisterListResponse(playerid, listitem) {
	if(IsAdmin(playerid) >= ALVL_HEAD_ADMIN) {
		new DBResult: result, Result:sql_result;
		new rows;
		new string[256];				
		
		if(GetHelpVarValue(playerid, 99) == 0) {		
			format(string, sizeof(string), "SELECT `"TK_UID"` FROM `"T_KONTA"` ORDER BY `"TK_REGISTER_STAMP"` DESC LIMIT %d, 11", GetPlayerPage(playerid) * 10);
		} else {
			strins(string, RegisterBaseMakeQuery(playerid, GetPlayerPage(playerid)), 0);
		}
		result = sendQueryResult(string, sql_result);
		rows = numRows(result, sql_result);
		if(rows > 0) {
			new bool:pvpage = GetPlayerPage(playerid) > 0 ? true : false;
			new bool:nxpage = rows == 11 ? true : false;
		
			if(listitem == 0 and (pvpage == true or nxpage == true)) {
				freeResult(result, sql_result);
				if(pvpage == true) HARegisterBaseList(playerid, GetPlayerPage(playerid) - 1);
				else {
					HARegisterBaseList(playerid, GetPlayerPage(playerid) + 1);
				}
			} else if(listitem == 1 and (pvpage == true and nxpage == true)) {
				freeResult(result, sql_result);
				HARegisterBaseList(playerid, GetPlayerPage(playerid) + 1);
			} else {
				new uniqueid;
				if(pvpage == true) listitem --;
				if(nxpage == true) listitem --;			

				new index, dest[64];
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

				format(string, sizeof(string), "SELECT `"TK_NICK"`,`"TK_REGISTER_STAMP"`,`"TK_REGISTER_IP"`,`"TK_REGISTER_GPCI"` FROM `"T_KONTA"` WHERE `"TK_UID"`='%d' LIMIT 1", uniqueid);
				result = sendQueryResult(string, sql_result);
				
				if(numRows(result, sql_result) > 0) {		
					new nick[24], r_stamp, r_ip[16], r_gpci[64];
					new year, month, day, hour, minute;				
					
					r_stamp = strval(getFieldAssoc_32(TK_REGISTER_STAMP, result, sql_result));
					strins(r_gpci, getFieldAssoc_64(TK_REGISTER_GPCI, result, sql_result), 0);		
					if(strlen(r_gpci) > 30) strins(r_gpci, "\n", 30);
					strins(r_ip, getFieldAssoc_64(TK_REGISTER_IP, result, sql_result), 0);	
					
					strins(nick, getFieldAssoc_32(TK_NICK, result, sql_result), 0);
					DeconvertNick(nick);				
					
					freeResult(result, sql_result);					
					
					if(strlen(r_ip) < 5) {
						strdel(r_ip, 0, 5);
						strins(r_ip, "Admin Register", 0);
					}
					if(strlen(r_gpci) < 5) {
						strdel(r_gpci, 0, 5);
						strins(r_gpci, "Admin Register", 0);
					}					
					
					dtimestamp(r_stamp, year, month, day, hour, minute);

					format(string, sizeof(string), "\
							Nick: "TEXT_DIALOG_NORMAL"%s"TEXT_DIALOG_HEAD" (User ID: "TEXT_DIALOG_NORMAL"%d"TEXT_DIALOG_HEAD")\n\
							Data rejestracji: "TEXT_DIALOG_NORMAL"%s"TEXT_DIALOG_HEAD"  [ "TEXT_DIALOG_NORMAL"%d:%02d"TEXT_DIALOG_HEAD" ]\n\
							IP: "TEXT_DIALOG_NORMAL"%s"TEXT_DIALOG_HEAD"\n\
							GPCI: "TEXT_DIALOG_NORMAL"%s"TEXT_DIALOG_HEAD"\n\
						",						
						nick, uniqueid,
						strData(year, month, day, " / ", false, false, true, false), hour, minute,
						r_ip,
						r_gpci
					);

					ShowPlayerInfoDialog(playerid, BACK_HA_REGISTER_LIST, "Baza rejestrowanych kont - Informacje", string);				
					return _TRUE;			
				} else {
					if(GetHelpVarValue(playerid, 99) == 0) {	
						ShowPlayerInfoDialog(playerid, BACK_HA_REGISTER_LIST, "Baza rejestrowanych kont - Informacje", "Wystapil blad :( Daj znac komus kto moze to naprawic.");	
					} else {
						ShowPlayerInfoDialog(playerid, BACK_HA_REGISTER_SEARCH, "Baza rejestrowanych kont - Informacje", "Wystapil blad :( Daj znac komus kto moze to naprawic.");	
					}
				}
			}		
		} else HARegisterBaseList(playerid, 0);
	} 
	return _FALSE;
}

//===============================================================
//---------------------------------------------------------------
//===============================================================
/*
	3) Obsluga banow stalych
*/
//===============================================================
//---------------------------------------------------------------
//===============================================================
HAPanelStaticBan(playerid, listitem = -1) {
	if(IsAdmin(playerid) >= ALVL_HEAD_ADMIN) {
		switch(listitem) {
			case 0:	HAPanelStaticBanSearch(playerid);
			case 1: {
				SetHelpVarValue(playerid, 99, 0);
				HAStaticBanList(playerid);
			}
			case 2: HAPanelStaticBanAddType(playerid);
			case 3: HAPanelSAMPBanRemove(playerid);
			default: {
				if(IsAdmin(playerid) == ALVL_GAME_MASTER) {
					ShowPlayerDialogEx(playerid, DIALOG_HA_STATIC_BAN_MENU, DIALOG_STYLE_LIST, "Obsluga banow stalych", "1) Szukaj bana\n2) Lista banow\n3) Dodaj nowa blokade\n4) Usun blokade z pliku 'samp.ban'", "Dalej", "Wroc");
				} else {
					ShowPlayerDialogEx(playerid, DIALOG_HA_STATIC_BAN_MENU, DIALOG_STYLE_LIST, "Obsluga banow stalych", "1) Szukaj bana\n2) Lista banow\n3) Dodaj nowa blokade", "Dalej", "Wroc");
				}
			}
		}
		return _TRUE;
	}
	return _FALSE;
}
//===============================================================
HAPanelSAMPBanRemove(playerid, ipvalue[] = "") {
	if(IsAdmin(playerid) >= ALVL_GAME_MASTER) {
		new string[256];
		if(!isnull(ipvalue)) {
			new dots[4], bool:errorInIP, dotindex;
			for(new i = strlen(ipvalue) - 1; i >= 0; i --) {
				if(!('9' >= ipvalue[i] >= '0')) {
					if(ipvalue[i] == '.') {
						dots[dotindex ++] = i;
						if(dotindex == 4) {
							errorInIP = true;
							break;
						}	
					} else if(ipvalue[i] != '*') {
						errorInIP = true;
						break;
					}
				}
			}
			if((dotindex != 3) or (dots[2] == 0 or dots[0] == strlen(ipvalue) - 1) or (dots[0] - 1 == dots[1] or dots[1] - 1 == dots[2]) or (dots[2] > 3 or strlen(ipvalue) - dots[0] > 4 or dots[0] - dots[1] > 4 or dots[1] - dots[2] > 4)) errorInIP = true;

			if(errorInIP == false) {
				format(string, sizeof(string), "unbanip %s", ipvalue);
				SendRconCommand(string);
				SendRconCommand("reloadbans");
				format(string, sizeof(string), C_LIGHTGREEN"   Usunieto IP %s z pliku 'samp.ban' (przeladowano liste).", ipvalue);				
			} else strins(string, C_ADMIN"\t\t     Niepoprawny format IP lub hostu.", 0);
		}
		format(string, sizeof(string), "Podaj IP lub host (np. '83.1.*.*'), ktory chcesz usunac z pliku 'samp.ban'.\n\n%s", string);
		ShowPlayerDialogEx(playerid, DIALOG_HA_SAMPBAN_REMOVE, DIALOG_STYLE_INPUT, "Obsluga banow stalych - Blokada 'samp.ban'", string, "Odbanuj", "Wroc");
		return _TRUE;
	}
	return _FALSE;
}
//---------------------------------------------------------------
HAPanelStaticBanAddType(playerid, listitem = -1) {
	if(IsAdmin(playerid) >= ALVL_HEAD_ADMIN) {
		switch(listitem) {
			case 0: SetHelpVarValue(playerid, 0, B_IP);
			case 1: SetHelpVarValue(playerid, 0, B_HOST);
			case 2: SetHelpVarValue(playerid, 0, B_NICK);
			default: return ShowPlayerDialogEx(playerid, DIALOG_HA_STATIC_BAN_ADD_TYPE, DIALOG_STYLE_LIST, "Nowa blokada - Podaj typ blokady", "1) IP\n2) Host\n3) Nick", "Dalej", "Wroc");
		}
		if(0 <= listitem <= 2) {
			HAPanelStaticBanAddValue(playerid);
		}
		return _TRUE;
	}
	return _FALSE;
}
//---------------------------------------------------------------
HAPanelStaticBanAddValue(playerid, value[] = "") {
	if(IsAdmin(playerid) >= ALVL_HEAD_ADMIN) {
		new string[256];
		if(!isnull(value) and 64 >= strlen(value)) {
			new bool:match = false;
			switch(GetHelpVarValue(playerid, 0)) {
				case B_IP:		if(IsValidIP(value) == _TRUE) match = true;
				case B_HOST:	if(IsValidHost(value) == _TRUE) match = true;
				case B_NICK:	if(IsValidNick(value) == _TRUE) match = true;
			}
			if(match == true) {
				new DBResult: result, Result:sql_result;
				format(string, sizeof(string), "SELECT `"TB_UNIQUE_ID"` FROM `"T_BAN"` WHERE `"TB_UNBANTIME"` > '%d' AND `"TB_VALUE"`='%s' AND `"TB_TYPE"`='%d' LIMIT 1", timestamp(), value, GetHelpVarValue(playerid, 0));
				result = sendQueryResult(string, sql_result);
				strdel(string, 0, 128);
				if(numRows(result, sql_result) == 0) {
					new bool:isregistered = false;
					if(GetHelpVarValue(playerid, 0) == B_NICK) {
						if(IsNickRegistered(value) != _FALSE) isregistered = true;
					}
					if(isregistered == false) {
						SetHelpStringValue(playerid, 0, value);
						HAPanelStaticBanAddTime(playerid);
						return _TRUE;						
					} else strins(string, "\t   Nie mozesz zbanowac zarejestrowanego nicku.\nDo banowania zarejestrowanych nickow, sluzy blokada kont graczy.", 0);
				} else {
					freeResult(result, sql_result);
					strins(string, "\tPodana wartosc znajduje sie juz na ban liscie.", 0);
				}			
			} else strins(string, "\t      Podana wartosc nie jest zgodna z typem.", 0);
		}
		format(string, sizeof(string), "Podaj wartosc, ktora ma zostac zbanowana. Pamietaj, ze wartosc\n\tmusi byc zgodna z wybranym typem bana ('"TEXT_DIALOG_NORMAL"%s"TEXT_DIALOG_HEAD"').\n\n"TEXT_DIALOG_ALERT"%s", GetBanPartNameFromType(GetHelpVarValue(playerid, 0)), string);
		ShowPlayerDialogEx(playerid, DIALOG_HA_STATIC_BAN_ADD_VALUE, DIALOG_STYLE_INPUT, "Nowa blokada - Podaj wartosc blokady", string, "Dalej", "Wroc");
		return _TRUE;
	}
	return _FALSE;
}
//---------------------------------------------------------------
HAPanelStaticBanAddTime(playerid, time[] = "") {
	if(IsAdmin(playerid) >= ALVL_HEAD_ADMIN) {
		new string[140];
		if(!isnull(time)) {
			if(strlen(time) <= 3 and 365 >= strval(time) > 0) {
				SetHelpVarValue(playerid, 1, strval(time));
				HAPanelStaticBanAddReason(playerid);
				return _TRUE;
			} else strins(string, "Czas trwania blokady musi zawierac sie w przedziale od\n\t\t\t1 do 365 dni.", 0);
		}
		format(string, sizeof(string), "Podaj czas trwania blokady w dniach (od 1 do 365 dni).\n\n"TEXT_DIALOG_ALERT"%s", string);
		ShowPlayerDialogEx(playerid, DIALOG_HA_STATIC_BAN_ADD_TIME, DIALOG_STYLE_INPUT, "Nowa blokada - Czas trwania blokady", string, "Dalej", "Wroc");
		return _TRUE;
	}
	return _FALSE;
}
//---------------------------------------------------------------
HAPanelStaticBanAddReason(playerid, reason[] = "") {
	if(IsAdmin(playerid) >= ALVL_HEAD_ADMIN) {
		new string[256];
		if(!isnull(reason)) {
			if(120 >= strlen(reason) >= 3) {
				new bool:symbols = false;
				for(new i = strlen(reason) - 1; i >= 0; i --) {
					if(!(
						'a' <= reason[i] <= 'z' or 'A' <= reason[i] <= 'Z' or 
						'0' <= reason[i] <= '9' or reason[i] == ' ' or reason[i] == '_' or 
						reason[i] == '.' or reason[i] == ',' or reason[i] == '(' or 
						reason[i] == ')' or reason[i] == ']' or reason[i] == '[' or 
						reason[i] == '#' or reason[i] == '!' or reason[i] == '?' or
						reason[i] == ':' or reason[i] == '+' or reason[i] == '-')
					) {
						symbols = true;
						break;
					}
				}
				if(symbols == false) {
					SetHelpStringValue(playerid, 1, reason);
					HAPanelStaticBanAddConfirm(playerid);
					return _TRUE;
				} else strins(string, "\tPowod blokady zawiera niedozwolone znaki.", 0);					
			} else strins(string, "       Powod blokady musi zawierac sie w przedziale od\n\t\t          3 do 120 znakow.", 0);
		}
		format(string, sizeof(string),"Podaj powod blokady. Powod musi skladac sie z liter lub\ncyfr i musi zawierac sie w przedziale od 3 do 120 znakow.\n\n"TEXT_DIALOG_ALERT"%s", string);
		ShowPlayerDialogEx(playerid, DIALOG_HA_STATIC_BAN_ADD_REASON, DIALOG_STYLE_INPUT, "Nowa blokada - Powod blokady", string, "Dalej", "Wroc");
		return _TRUE;
	}
	return _FALSE;
}
//---------------------------------------------------------------
HAPanelStaticBanAddConfirm(playerid, bool:confirm = false) {
	if(IsAdmin(playerid) >= ALVL_HEAD_ADMIN) {
		new string[300];
		new bantime = ToSeconds(GetHelpVarValue(playerid, 1), _DAY);
		if(confirm == false) {
			new year, month, day, hour, minute;
			strins(string, GetHelpStringValue(playerid, 1), 0);
			if(strlen(string) > 55) strins(string, "\n", 55);
			dtimestamp(timestamp() + bantime, year, month, day, hour, minute);
			format(string, sizeof(string), "\
					Czy na pewno chcesz dodac blokade o nastepujacych parametrach:\n\n\
					Typ: "TEXT_DIALOG_NORMAL"%s"TEXT_DIALOG_HEAD"\n\
					Wartosc: "TEXT_DIALOG_NORMAL"%s"TEXT_DIALOG_HEAD"\n\
					Czas trwania: "TEXT_DIALOG_NORMAL"%s"TEXT_DIALOG_HEAD"\n\
					Data odbanowania: "TEXT_DIALOG_NORMAL"%s  "TEXT_DIALOG_HEAD"[ "TEXT_DIALOG_NORMAL"%d:%02d "TEXT_DIALOG_HEAD"]\n\n\
					Powod: "TEXT_DIALOG_NORMAL"%s",
				GetBanPartNameFromType(GetHelpVarValue(playerid, 0)),
				GetHelpStringValue(playerid, 0),
				convertSeconds(bantime),
				strData(year, month, day, " / ", false, false, true, false), hour, minute,
				string
			);				
			ShowPlayerYesNoDialog(playerid, D_YESNO_HA_SBAN_CONFIRM, "Nowa blokada - Potwierdzenie", string);
		} else {
			AddBan(GetHelpVarValue(playerid, 0), GetHelpStringValue(playerid, 0), bantime, getPlayerUserID(playerid), GetHelpStringValue(playerid, 1));
			format(string, sizeof(string),"Dodano blokade na '"TEXT_DIALOG_NORMAL"%s"TEXT_DIALOG_HEAD"' o wartosci '"TEXT_DIALOG_NORMAL"%s"TEXT_DIALOG_HEAD"'.", GetBanPartNameFromType(GetHelpVarValue(playerid, 0)), GetHelpStringValue(playerid, 0));
			ShowPlayerInfoDialog(playerid, BACK_HA_BAN_MENU, "Nowa blokada - Potwierdzenie", string);					
		}
		return _TRUE;
	}
	return _FALSE;
}
//===============================================================
HAPanelStaticBanSearch(playerid, data[] = "") {
	if(IsAdmin(playerid) >= ALVL_HEAD_ADMIN) {
		new string[256];
		if(!isnull(data)) {			
			new type, date_from, date_to, bool:search_front, bool:search_end, bool:sorttype_desc, errorid;
			if(SearchDataSplit(data, type, date_from, date_to, search_front, search_end, sorttype_desc, errorid) == _TRUE) {
				switch(type) {
					case DATA_TYPE_NON: 	strins(string, "Niepoprawny typ danych do wyszukania.", 0);
					case DATA_TYPE_ONLINE, DATA_TYPE_USERID: 	strins(string, "Ten typ wyszukiwania nie jest obslugiwany w tym menu.", 0);
					default: {
						SetHelpVarValue(playerid, 99, 1);
						SetHelpVarValue(playerid, 21, type);
						SetHelpVarValue(playerid, 22, date_from);
						SetHelpVarValue(playerid, 23, date_to);
						SetHelpVarValue(playerid, 24, _:search_front);
						SetHelpVarValue(playerid, 25, _:search_end);
						SetHelpVarValue(playerid, 26, _:sorttype_desc);
						SetHelpStringValue(playerid, 20, data);
						HAStaticBanList(playerid);
						return _TRUE;
					}
				}
			} else {
				switch(errorid) {
					case DATA_ERROR_HELP: {
						ShowPlayerSearchInfo(playerid, SI_STATIC_BAN);
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
		format(string, sizeof(string), "Podaj interesujacy Cie typ danych pod katem, ktorych\nma zostac przeszukana baza danych 'Banow Stalych'.\n  Info: Jesli nie wiesz jak poslugiwac sie wyszukiwarka,\n\t\twpisz polecenie '<INFO>'.\n\n"TEXT_DIALOG_ALERT"%s", string);
		ShowPlayerDialogEx(playerid, DIALOG_HA_STATIC_BAN_SEARCH, DIALOG_STYLE_INPUT, "Bany czasowe - Wyszukiwarka", string, "Wyszukaj", "Wroc");
		
		return _TRUE;
	}	
	return _FALSE;
}
//---------------------------------------------------------------
StaticBanMakeQuery(playerid, page) {
	new string[256];
	switch(GetHelpVarValue(playerid, 21)) {
		case DATA_TYPE_NICK: {
			strins(string, GetHelpStringValue(playerid, 20), 0);
			ConvertNick(string);
			format(string, sizeof(string), "SELECT `"TB_UNIQUE_ID"`, `"TB_VALUE "`, `"TB_TYPE"` FROM `"T_BAN"` WHERE `"TB_UNBANTIME"` > '%d' AND `"TB_VALUE"` LIKE '%s%s%s' AND `"TB_TYPE"`='"#B_NICK"' AND `"TB_DATE_STAMP"` >= '%d' AND `"TB_DATE_STAMP"` <= '%d' ORDER BY `"TB_DATE_STAMP"` %s LIMIT %d, 11", 
				timestamp(), 
				GetHelpVarValue(playerid, 24) == 1 ? ("%") : (""), string, GetHelpVarValue(playerid, 25) == 1 ? ("%") : (""), 				
				GetHelpVarValue(playerid, 22), GetHelpVarValue(playerid, 23),						
				GetHelpVarValue(playerid, 26) == 0 ? ("ASC") : ("DESC"), 
				page * 10);
		}
		case DATA_TYPE_IP: {
			format(string, sizeof(string), "SELECT `"TB_UNIQUE_ID"`, `"TB_VALUE "`, `"TB_TYPE"` FROM `"T_BAN"` WHERE `"TB_UNBANTIME"` > '%d' AND `"TB_VALUE"` LIKE '%s%s%s' AND `"TB_TYPE"`='"#B_IP"' AND `"TB_DATE_STAMP"` >= '%d' AND `"TB_DATE_STAMP"` <= '%d' ORDER BY `"TB_DATE_STAMP"` %s LIMIT %d, 11", 
				timestamp(), 
				GetHelpVarValue(playerid, 24) == 1 ? ("%") : (""), GetHelpStringValue(playerid, 20), GetHelpVarValue(playerid, 25) == 1 ? ("%") : (""), 
				GetHelpVarValue(playerid, 22), GetHelpVarValue(playerid, 23),		
				GetHelpVarValue(playerid, 26) == 0 ? ("ASC") : ("DESC"),
				page * 10);				
		}		
		case DATA_TYPE_HOST: {
			format(string, sizeof(string), "SELECT `"TB_UNIQUE_ID"`, `"TB_VALUE "`, `"TB_TYPE"` FROM `"T_BAN"` WHERE `"TB_UNBANTIME"` > '%d' AND `"TB_VALUE"` LIKE '%s%s%s' AND `"TB_TYPE"`='"#B_HOST"' AND `"TB_DATE_STAMP"` >= '%d' AND `"TB_DATE_STAMP"` <= '%d' ORDER BY `"TB_DATE_STAMP"` %s LIMIT %d, 11", 
				timestamp(), 
				GetHelpVarValue(playerid, 24) == 1 ? ("%") : (""), GetHelpStringValue(playerid, 20), GetHelpVarValue(playerid, 25) == 1 ? ("%") : (""), 
				GetHelpVarValue(playerid, 22), GetHelpVarValue(playerid, 23),		
				GetHelpVarValue(playerid, 26) == 0 ? ("ASC") : ("DESC"),
				page * 10);				
		}
		case DATA_TYPE_ADMINID: {
			format(string, sizeof(string), "SELECT `"TB_UNIQUE_ID"`, `"TB_VALUE "`, `"TB_TYPE"` FROM `"T_BAN"` WHERE `"TB_UNBANTIME"` > '%d' AND `"TB_ADMINID"` = '%s' AND `"TB_DATE_STAMP"` >= '%d' AND `"TB_DATE_STAMP"` <= '%d' ORDER BY `"TB_DATE_STAMP"` %s LIMIT %d, 11", 
				timestamp(), 
				GetHelpStringValue(playerid, 20),
				GetHelpVarValue(playerid, 22), GetHelpVarValue(playerid, 23),		
				GetHelpVarValue(playerid, 26) == 0 ? ("ASC") : ("DESC"),
				page * 10);					
		}
		case DATA_TYPE_ADMIN_NICK: {
			strins(string, GetHelpStringValue(playerid, 20), 0);
			ConvertNick(string);
			format(string, sizeof(string), "SELECT `"TB_UNIQUE_ID"`, `"TB_VALUE "`, `"TB_TYPE"` FROM `"T_BAN"` WHERE `"TB_UNBANTIME"` > '%d' AND `"TB_ADMIN_NAME"` LIKE '%s%s%s' AND `"TB_DATE_STAMP"` >= '%d' AND `"TB_DATE_STAMP"` <= '%d' ORDER BY `"TB_DATE_STAMP"` %s LIMIT %d, 11", 
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
HAStaticBanList(playerid, page = 0) {
	if(IsAdmin(playerid) >= ALVL_HEAD_ADMIN) {
		new string[800];		
		new DBResult: result, Result:sql_result;
		new rows;	

		if(page < 0) page = 0;
		
		if(GetHelpVarValue(playerid, 99) == 0) {		
			format(string, sizeof(string), "SELECT `"TB_VALUE "`, `"TB_TYPE"` FROM `"T_BAN"` WHERE `"TB_UNBANTIME"` > '%d' ORDER BY `"TB_DATE_STAMP"` DESC LIMIT %d, 11", timestamp(), page * 10);
		} else {
			strins(string, StaticBanMakeQuery(playerid, page), 0);
		}
		result = sendQueryResult(string, sql_result);
		//_______________________	
		strdel(string, 0, 256);
		rows = numRows(result, sql_result);
		if(numRows(result, sql_result) > 0) {
			new bool:isNextPage = rows == 11 ? true : false;			
			
			new value[64];
			for(new i, limit = rows == 11 ? 10 : rows; i < limit; i ++) {
				strdel(value, 0, 64);				
				strins(value, getFieldAssoc_64(TB_VALUE, result, sql_result), 0);				
				DeconvertNick(value);
				format(string, sizeof(string), "%s\n%d) %s\t\t"TEXT_DIALOG_HEAD"[ "TEXT_DIALOG_NORMAL"%s"TEXT_DIALOG_HEAD" ]", string, page * 10 + i + 1, CutName(value), GetBanPartNameFromType(strval(getFieldAssoc_16(TB_TYPE, result, sql_result))));
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
			ShowPlayerDialogEx(playerid, DIALOG_HA_STATIC_BAN_LIST, DIALOG_STYLE_LIST, "Obsluga banow stalych - Lista", string, "Sprawdz", "Wroc");
			return _TRUE;
		} else {
			if(GetHelpVarValue(playerid, 99) == 0) {
				ShowPlayerInfoDialog(playerid, BACK_HA_BAN_MENU, "Obsluga banow stalych - Lista", "Brak danych do sprawdzenia w bazie. Sprobuj pozniej.");
			} else {
				ShowPlayerInfoDialog(playerid, BACK_HA_BAN_SEARCH, "Obsluga banow stalych - Wyszukiwarka", "Nieznaleziono rezultatow dla podanych danych.");	
			}
		}
		//_______________________	
	}
	return _FALSE;
}
//---------------------------------------------------------------
HAStaticBanListResponse(playerid, listitem) {
	if(IsAdmin(playerid) >= ALVL_HEAD_ADMIN) {
		new DBResult: result, Result:sql_result;
		new rows;
		new string[256];				
		
		if(GetHelpVarValue(playerid, 99) == 0) {		
			format(string, sizeof(string), "SELECT `"TB_UNIQUE_ID"` FROM `"T_BAN"` WHERE `"TB_UNBANTIME"` > '%d' ORDER BY `"TB_DATE_STAMP"` DESC LIMIT %d, 11", timestamp(), GetPlayerPage(playerid) * 10);
		} else {
			strins(string, StaticBanMakeQuery(playerid, GetPlayerPage(playerid)), 0);
		}
		result = sendQueryResult(string, sql_result);
		rows = numRows(result, sql_result);
		if(rows > 0) {
			
			new bool:pvpage = GetPlayerPage(playerid) > 0 ? true : false;
			new bool:nxpage = rows == 11 ? true : false;
		
			if(listitem == 0 and (pvpage == true or nxpage == true)) {
				freeResult(result, sql_result);
				if(pvpage == true) HAStaticBanList(playerid, GetPlayerPage(playerid) - 1);
				else {
					HAStaticBanList(playerid, GetPlayerPage(playerid) + 1);
				}
			} else if(listitem == 1 and (pvpage == true and nxpage == true)) {
				freeResult(result, sql_result);
				HAStaticBanList(playerid, GetPlayerPage(playerid) + 1);
			} else {
				new uniqueid;
				if(pvpage == true) listitem --;
				if(nxpage == true) listitem --;
							
				new index;
				new dest[8];
				strdel(string, 0, 256);
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

				format(string, sizeof(string), "SELECT * FROM `"T_BAN"` WHERE `"TB_UNIQUE_ID"`='%d' LIMIT 1", uniqueid);
				result = sendQueryResult(string, sql_result);
				if(numRows(result, sql_result) > 0) {			
					new value[64], type = strval(getFieldAssoc_16(TB_TYPE, result, sql_result)),
						adminname[MAX_PLAYER_NAME], adminid = strval(getFieldAssoc_16(TB_ADMINID, result, sql_result)),
						unbantime = strval(getFieldAssoc_16(TB_UNBANTIME, result, sql_result));
					new year, month, day, hour, minute;				

					SetHelpVarValue(playerid, 0, uniqueid);
					SetHelpVarValue(playerid, 1, listitem);
					
					strins(value, getFieldAssoc_64(TB_VALUE, result, sql_result), 0);
					strins(adminname, getFieldAssoc_32(TB_ADMIN_NAME, result, sql_result), 0);
					DeconvertNick(adminname);	
					
					strdel(string, 0, 256);
					strins(string, getFieldAssoc_128(TB_REASON, result, sql_result), 0);
					if(strlen(string) > 54) strins(string, "\n", 54);
					if(strlen(value) > 32) strins(value, "\n", 32);
					if(type == B_NICK) DeconvertNick(value);						
					
					freeResult(result, sql_result);					
					
					dtimestamp(unbantime, year, month, day, hour, minute);

					format(string, sizeof(string), "\
							Typ bana: "TEXT_DIALOG_NORMAL"%s"TEXT_DIALOG_HEAD"\n\
							Wartosc: "TEXT_DIALOG_NORMAL"%s"TEXT_DIALOG_HEAD"\n\
							Administrator: "TEXT_DIALOG_NORMAL"%s "TEXT_DIALOG_HEAD"(UID: "TEXT_DIALOG_NORMAL"%d"TEXT_DIALOG_HEAD")\n\
							Data odbanowania: "TEXT_DIALOG_NORMAL"%s  "TEXT_DIALOG_HEAD"[ "TEXT_DIALOG_NORMAL"%d:%02d "TEXT_DIALOG_HEAD"]\n\n\
							Powod: "TEXT_DIALOG_NORMAL"%s\n",						
						GetBanPartNameFromType(type),
						value,
						adminname, adminid,
						strData(year, month, day, " / ", false, false, true, false), hour, minute,
						string
					);

					ShowPlayerDialogEx(playerid, DIALOG_HA_BAN_UNBAN, DIALOG_STYLE_MSGBOX, "Obsluga banow stalych - Informacje", string, "Odbanuj", "Wroc");	
				
					return _TRUE;			
				} else {
					if(GetHelpVarValue(playerid, 99) == 0) {	
						ShowPlayerInfoDialog(playerid, BACK_HA_BAN_LIST, "Obsluga banow stalych - Informacje", "Wystapil blad :( Daj znac komus kto moze to naprawic.");	
					} else {
						ShowPlayerInfoDialog(playerid, BACK_HA_BAN_SEARCH, "Obsluga banow stalych - Informacje", "Wystapil blad :( Daj znac komus kto moze to naprawic.");	
					}
				}
			}		
		} else HAStaticBanList(playerid, 0);
	} 
	return _FALSE;
}
//---------------------------------------------------------------
HAStaticBanUnban(playerid, bool:confirm = false) {
	if(IsAdmin(playerid) >= ALVL_HEAD_ADMIN) {
		if(confirm == false) {
			ShowPlayerCaptcha(playerid, D_CAPTCHA_HA_UNBAN_STATIC);
		} else {
			new string[180], DBResult: result, Result:sql_result;
			format(string, sizeof(string), "SELECT `"TB_VALUE "`, `"TB_TYPE"` FROM `"T_BAN"` WHERE `"TB_UNIQUE_ID"`='%d' LIMIT 1", GetHelpVarValue(playerid, 0));
			result = sendQueryResult(string, sql_result);
			if(numRows(result, sql_result) > 0) {
				new value[64], type;
				type = strval(getFieldAssoc_16(TB_TYPE, result, sql_result));
				strins(value, getFieldAssoc_64(TB_VALUE, result, sql_result), 0);
				freeResult(result, sql_result);
				RemoveBan(GetHelpVarValue(playerid, 0), getPlayerUserID(playerid));
				if(type == B_NICK) DeconvertNick(value);
				
				format(string, sizeof(string), "Ban na '"TEXT_DIALOG_NORMAL"%s"TEXT_DIALOG_HEAD"' o wartosci '"TEXT_DIALOG_NORMAL"%s"TEXT_DIALOG_HEAD"' zostal usuniety.", GetBanPartNameFromType(type), value);
				ShowPlayerInfoDialog(playerid, BACK_HA_BAN_LIST, "Obsluga banow stalych - Unban", string);
			} else ShowPlayerInfoDialog(playerid, BACK_HA_BAN_LIST, "Obsluga banow stalych - Unban", "Nieodnaleziono bana o podanym 'Unique ID'. Byc moze, blokada zostala usunieta.");	
		}
		return _TRUE;
	}
	return _FALSE;
}

//===============================================================
//---------------------------------------------------------------
//===============================================================
/*
	4) Zarejestruj nowe konto
*/
//===============================================================
//---------------------------------------------------------------
//===============================================================
HAPanelAccRegisterNick(playerid, accname[] = "") {
	if(IsAdmin(playerid) >= ALVL_HEAD_ADMIN) {
		new string[200];
		if(!isnull(accname)) {
			if(IsValidNick(accname) == _TRUE and strval(accname) == 0 and IsValidIP(accname) == _FALSE and IsValidHost(accname) == _FALSE) {
				if(GetBanUniqueID(B_NICK, accname) == 0) {
					if(CheckSimilarRegisterNick(accname) == _FALSE) {
						SetHelpStringValue(playerid, 0, accname);
						HAPanelAccRegisterPassword(playerid);
						return _TRUE;
					} else strins(string, " Na serwerze znajduje sie nick z taka sama kombinacja\n\t\t\tznakow.", 0);
				} else strins(string, "\t   Ten nick znajduje sie na banliscie.", 0);
			} else strins(string, "\t\tNiepoprawny nick gracza", 0);
		}
		format(string, sizeof(string), "W tym menu mozesz zarejestrowac nowe konto gracza.\n\t      Podaj nick rejestrowanego konta.\n\n"TEXT_DIALOG_ALERT"%s", string);
		ShowPlayerDialogEx(playerid, DIALOG_HA_REGISTER, DIALOG_STYLE_INPUT, "Rejestracja nowego konta - Nick", string, "Dalej", "Wroc");
		return _TRUE;
	}
	return _FALSE;
}
//---------------------------------------------------------------
HAPanelAccRegisterPassword(playerid, password[] = "") {
	if(IsAdmin(playerid) >= ALVL_HEAD_ADMIN) {
		new string[280], s_pwd[32], bool:pwd_set;
		if(!isnull(password)) {
			if(strlen(password) == 1 and password[0] == '0') {
				valstr(s_pwd, randomly(100000, 999999));
				pwd_set = true;
			} else {
				if(IsValidPassword(password)) {
					strins(s_pwd, password, 0);
					pwd_set = true;
				} else strins(string, "Niepoprawne haslo - Haslo musi skladac sie z conajmniej 3 liter i 3 cyfr.", 0);
			}
		}
		if(pwd_set == false) {
			format(string, sizeof(string), "Podaj haslo do rejestrowanego konta. Gracz, po pierwszym logowaniu\n   bedzie musial je zmienic. Jesli chcesz wygenerowac losowe haslo,\n\t\t           w ponizsze pole wpisz '"TEXT_DIALOG_NORMAL"0"TEXT_DIALOG_HEAD"'.\n\n"TEXT_DIALOG_ALERT"%s", string);
			ShowPlayerDialogEx(playerid, DIALOG_HA_REGISTER_PASSWORD, DIALOG_STYLE_INPUT, "Rejestracja nowego konta - Haslo", string, "Dalej", "Wroc");		
		} else {
			SetHelpStringValue(playerid, 1, s_pwd);
			format(string, sizeof(string), "Czy chcesz zarejestrowac nowe konto z podanymi parametrami:\n\n\t\t\tNick: "TEXT_DIALOG_NORMAL"%s\n"TEXT_DIALOG_HEAD"\t\t\tHaslo: "TEXT_DIALOG_NORMAL"%s\n", GetHelpStringValue(playerid, 0), s_pwd);
			ShowPlayerYesNoDialog(playerid, D_YESNO_HA_REGISTER, "Rejestracja nowego konta - Potwierdzenie", string);
		}
		return _TRUE;
	}	
	return _FALSE;
}
//---------------------------------------------------------------
HAPanelRegisterNewAccount(playerid, nick[], password[]) {
	if(IsAdmin(playerid) >= ALVL_HEAD_ADMIN) {
		if(CheckSimilarRegisterNick(nick) == _FALSE) {
			new userid = AddNewAccount(nick, password, true, "0", "0");
			if(userid > 0) {
				new string[200];
				format(string, sizeof(string), "(Rejestracja konta) Haslo do konta '%s' (User ID: %d) to '%s'.", nick, userid, password);
				SendClientMessage(playerid, COLOR_DIALOG_BODY, string);
				format(string, sizeof(string),"(Rejestracja nowego konta) Administrator %s (User ID: %d) zarejestrowal(a) konto o nazwie '%s' (User ID: %d | Haslo: %s)", getPlayerName(playerid), getPlayerUserID(playerid), nick, userid, password);
				AddToAdminLog(string);
				format(string, sizeof(string),"Zarejestrowano nowe konto o nazwie '"TEXT_DIALOG_NORMAL"%s"TEXT_DIALOG_HEAD"' (User ID: "TEXT_DIALOG_NORMAL"%d"TEXT_DIALOG_HEAD").\n\t       Tymczasowe haslo do konta: "TEXT_DIALOG_NORMAL"%s", nick, userid, password);
				ShowPlayerInfoDialog(playerid, BACK_ACC_REGISTER, "Rejestracja nowego konta", string);
				return _TRUE;				
			} else ShowPlayerInfoDialog(playerid, BACK_ACC_REGISTER, "Rejestracja nowego konta - Blad", "Wystapil blad podczas rejestracji konta. Sprobuj ponownie pozniej.");
		} else ShowPlayerInfoDialog(playerid, BACK_ACC_REGISTER, "Rejestracja nowego konta - Blad", "Konto o takiej samej kombinacji znakow zostalo wczesniej zarejestrowane w systemie.");
		return _TRUE;
	}
	return _FALSE;
}
//===============================================================
//---------------------------------------------------------------
//===============================================================
/*
	5) Sprawdz dane
*/
//===============================================================
//---------------------------------------------------------------
//===============================================================
CMD:check(playerid) {
	if(IsAdmin(playerid) != 0) {
		if(IsAdmin(playerid) < 0) SendClientMessage(playerid, COLOR_DIALOG_BODY, " (Check) Komenda dostepna po zalogowaniu sie na konto administratora.");	
		else {
			SetHelpVarValue(playerid, 50, 1);
			ShowPlayerNameCheckMenu(playerid);
		}
	}
	return _TRUE;
}
//===============================================================
HACheckDataMenu(playerid, listitem = -1) {
	if(IsAdmin(playerid) >= ALVL_HEAD_ADMIN) {
		new Result:sql_result;
		new DBResult:result = sendQueryResult("SELECT `"TPI_UNIQUE_ID"` FROM `"T_PLAYER_INFO"` LIMIT 1", sql_result);
		if(numRows(result, sql_result) > 0) {
			freeResult(result, sql_result);
			switch(listitem) {
				case 0: HACheckDataSearch(playerid);
				case 1: {
					SetHelpVarValue(playerid, 99, 0);
					HACheckDataList(playerid);
				}
				default: ShowPlayerDialogEx(playerid, DIALOG_HA_DATA_MENU, DIALOG_STYLE_LIST, "Sprawdz dane", "1) Wyszukaj dane\n2) Lista", "Dalej", "Wroc");
			}
		} else ShowPlayerInfoDialog(playerid, BACK_HAPANEL, "Sprawdz dane", "Brak danych do sprawdzenia w bazie. Sprobuj pozniej.");
		return _TRUE;
	}
	return _FALSE;
}
//===============================================================
HACheckDataSearch(playerid, search[] = "") {
	if(IsAdmin(playerid) >= ALVL_HEAD_ADMIN) {
		new string[300];
		if(!isnull(search)) {			
			new type, date_from, date_to, bool:search_front, bool:search_end, bool:sorttype_desc, errorid;
			if(SearchDataSplit(search, type, date_from, date_to, search_front, search_end, sorttype_desc, errorid) == _TRUE) {
				switch(type) {				
					case DATA_TYPE_NON: 	strins(string, "  Niepoprawny typ danych do wyszukania.", 0);
					case DATA_TYPE_ADMINID, DATA_TYPE_ADMIN_NICK: 	strins(string, "  Ten typ wyszukiwania nie jest obslugiwany w tym menu.", 0);
					default: {
						if(type == DATA_TYPE_ONLINE) {
							SetHelpVarValue(playerid, 21, DATA_TYPE_NICK);
							SetHelpStringValue(playerid, 20, getPlayerName(strval(search)));
							SetHelpVarValue(playerid, 25, false);
							SetHelpVarValue(playerid, 24, false);
						} else if(type == DATA_TYPE_HOST) {
							SetHelpVarValue(playerid, 21, DATA_TYPE_IP);
							format(string, sizeof(string),"%s.", search);
							SetHelpStringValue(playerid, 20, string);
							SetHelpVarValue(playerid, 25, true);
							SetHelpVarValue(playerid, 24, false);
						} else {
							SetHelpVarValue(playerid, 21, type);
							SetHelpStringValue(playerid, 20, search);
							SetHelpVarValue(playerid, 25, _:search_end);
							SetHelpVarValue(playerid, 24, _:search_front);
						}		
						
						SetHelpVarValue(playerid, 99, 1);						
						SetHelpVarValue(playerid, 22, date_from);
						SetHelpVarValue(playerid, 23, date_to);						
						SetHelpVarValue(playerid, 26, _:sorttype_desc);
						
						HACheckDataList(playerid);
						return _TRUE;
					}
				}
			} else {
				switch(errorid) {
					case DATA_ERROR_HELP: {
						ShowPlayerSearchInfo(playerid, SI_DATA_CHECK);
						return _TRUE;
					}
					case DATA_ERROR_INVALID_LENGTH:		strins(string, "\t      Niepoprawne dane do wyszukania.", 0);
					case DATA_ERROR_INVALID_TYPE:		strins(string, "\t  Niepoprawny typ danych do wyszukania.", 0);
					case DATA_ERROR_INVALID_SPECIAL:	strins(string, "            Niepoprawne znaki w danych do wyszukania.", 0);
					case DATA_ERROR_DATE_FROM:			strins(string, "  Niepoprawna najwczesniejsza data danych do wyszukania.", 0);
					case DATA_ERROR_DATE_TO:			strins(string, "  Niepoprawna najpozniejsza data danych do wyszukania.", 0);
					case DATA_ERROR_NO_TYPE:			strins(string, "             Niezdefiniowany typ danych do wyszukania.", 0);
					case DATA_ERROR_NO_DATA:			strins(string, "  Brak danych do wyszukania.", 0);
					case DATA_ERROR_NO_MATCH_DATA_TYPE:	strins(string, "     Niepoprawne typ z formatem danych do wyszukania.", 0);
					case DATA_ERROR_INVALID_SORT_TYPE:	strins(string, "\t        Niepoprawny rodzaj sortowania.", 0);
				}
			}
		}		
		format(string, sizeof(string), "      Podaj interesujacy Cie typ danych pod katem, ktorych\nma zostac przeszukana baza danych 'Informacji o graczach'.\n    Info: Jesli nie wiesz jak poslugiwac sie wyszukiwarka,\n\t\twpisz polecenie '<INFO>'.\n\n"TEXT_DIALOG_ALERT"%s", string);
		ShowPlayerDialogEx(playerid, DIALOG_HA_DATA_CHECK_SEARCH_MENU, DIALOG_STYLE_INPUT, "Bany czasowe - Wyszukiwarka", string, "Wyszukaj", "Wroc");
			
		return _TRUE;
	}
	return _FALSE;
}
//---------------------------------------------------------------
DataCheckMakeQuery(playerid, page) {
	new string[256];
	switch(GetHelpVarValue(playerid, 21)) {
		case DATA_TYPE_NICK: {
			strins(string, GetHelpStringValue(playerid, 20), 0);
			ConvertNick(string);
			format(string, sizeof(string), "SELECT `"TPI_UNIQUE_ID"`, `"TPI_NICK"`, `"TPI_IP"` FROM `"T_PLAYER_INFO"` WHERE `"TPI_NICK"` LIKE '%s%s%s' AND `"TPI_STAMP"` >= '%d' AND `"TPI_STAMP"` <= '%d' ORDER BY `"TPI_STAMP"` %s LIMIT %d, 11", 
				GetHelpVarValue(playerid, 24) == 1 ? ("%") : (""), string, GetHelpVarValue(playerid, 25) == 1 ? ("%") : (""), 
				GetHelpVarValue(playerid, 22), GetHelpVarValue(playerid, 23),						
				GetHelpVarValue(playerid, 26) == 0 ? ("ASC") : ("DESC"), 
				page * 10);
		}
		case DATA_TYPE_USERID: {
			format(string, sizeof(string), "SELECT `"TPI_UNIQUE_ID"`, `"TPI_NICK"`, `"TPI_IP"` FROM `"T_PLAYER_INFO"` WHERE `"TPI_UID"` = '%s' AND `"TPI_STAMP"` >= '%d' AND `"TPI_STAMP"` <= '%d' ORDER BY `"TPI_STAMP"` %s LIMIT %d, 11", 
				GetHelpStringValue(playerid, 20),
				GetHelpVarValue(playerid, 22), GetHelpVarValue(playerid, 23),		
				GetHelpVarValue(playerid, 26) == 0 ? ("ASC") : ("DESC"),
				page * 10);					
		}
		case DATA_TYPE_IP: {
			format(string, sizeof(string), "SELECT `"TPI_UNIQUE_ID"`, `"TPI_NICK"`, `"TPI_IP "` FROM `"T_PLAYER_INFO"` WHERE `"TPI_IP"` LIKE '%s%s%s' AND `"TPI_STAMP"` >= '%d' AND `"TPI_STAMP"` <= '%d' ORDER BY `"TPI_STAMP"` %s LIMIT %d, 11", 
				GetHelpVarValue(playerid, 24) == 1 ? ("%") : (""), GetHelpStringValue(playerid, 20), GetHelpVarValue(playerid, 25) == 1 ? ("%") : (""), 
				GetHelpVarValue(playerid, 22), GetHelpVarValue(playerid, 23),		
				GetHelpVarValue(playerid, 26) == 0 ? ("ASC") : ("DESC"),
				page * 10);				
		}		
	}
	return string;
}
//===============================================================
HACheckDataList(playerid, page = 0) {
	if(IsAdmin(playerid) >= ALVL_HEAD_ADMIN) {
		new string[800];		
		new DBResult: result, Result:sql_result;
		new rows;	

		if(page < 0) page = 0;
		
		if(GetHelpVarValue(playerid, 99) == 0) {		
			format(string, sizeof(string), "SELECT `"TPI_NICK "`, `"TPI_IP"` FROM `"T_PLAYER_INFO"` ORDER BY `"TPI_STAMP"` DESC LIMIT %d, 11", page * 10);
		} else {
			strins(string, DataCheckMakeQuery(playerid, page), 0);
		}
		result = sendQueryResult(string, sql_result);
		//_______________________	
		strdel(string, 0, 256);
		rows = numRows(result, sql_result);
		if(numRows(result, sql_result) > 0) {
			new bool:isNextPage = rows == 11 ? true : false;
			
			new index = 0, nick[32];
			for(new limit = rows == 11 ? 10 : rows; index < limit; index ++) {
				strdel(nick, 0, MAX_PLAYER_NAME);				
				strins(nick, getFieldAssoc_32(TPI_NICK, result, sql_result), 0);				
				DeconvertNick(nick);
				format(string, sizeof(string), "%s\n%d) %s\t\t"TEXT_DIALOG_HEAD"[ "TEXT_DIALOG_NORMAL"%s"TEXT_DIALOG_HEAD" ]", string, page * 10 + index + 1, CutName(nick), getFieldAssoc_16(TPI_IP, result, sql_result));
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
			ShowPlayerDialogEx(playerid, DIALOG_HA_DATA_CHECK, DIALOG_STYLE_LIST, "Sprawdz dane - Lista", string, "Sprawdz", "Wroc");
			return _TRUE;
		} else {
			if(GetHelpVarValue(playerid, 99) == 0) {
				ShowPlayerInfoDialog(playerid, BACK_HAPANEL, "Sprawdz dane - Lista", "Brak danych do sprawdzenia w bazie. Sprobuj pozniej.");
			} else {
				ShowPlayerInfoDialog(playerid, BACK_HA_DATA_SEARCH, "Sprawdz dane - Wyszukiwarka", "Nieznaleziono rezultatow dla podanych danych.");	
			}
		}
		//_______________________	
	}
	return _FALSE;
}
//---------------------------------------------------------------
HACheckDataListResponse(playerid, listitem) {
	if(IsAdmin(playerid) >= ALVL_HEAD_ADMIN) {
		new DBResult: result, Result:sql_result;
		new rows;
		new string[256];				
		
		if(GetHelpVarValue(playerid, 99) == 0) {		
			format(string, sizeof(string), "SELECT `"TPI_UNIQUE_ID"` FROM `"T_PLAYER_INFO"` ORDER BY `"TPI_STAMP"` DESC LIMIT %d, 11", GetPlayerPage(playerid) * 10);
		} else {
			strins(string, DataCheckMakeQuery(playerid, GetPlayerPage(playerid)), 0);
		}
		result = sendQueryResult(string, sql_result);
		rows = numRows(result, sql_result);
		if(rows > 0) {
			
			new bool:pvpage = GetPlayerPage(playerid) > 0 ? true : false;
			new bool:nxpage = rows == 11 ? true : false;
		
			if(listitem == 0 and (pvpage == true or nxpage == true)) {
				freeResult(result, sql_result);
				if(pvpage == true) HACheckDataList(playerid, GetPlayerPage(playerid) - 1);
				else {
					HACheckDataList(playerid, GetPlayerPage(playerid) + 1);
				}
			} else if(listitem == 1 and (pvpage == true and nxpage == true)) {
				freeResult(result, sql_result);
				HACheckDataList(playerid, GetPlayerPage(playerid) + 1);
			} else {
				new uniqueid;
				if(pvpage == true) listitem --;
				if(nxpage == true) listitem --;
			
			
				new index, dest[64];
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

				format(string, sizeof(string), "SELECT * FROM `"T_PLAYER_INFO"` WHERE `"TPI_UNIQUE_ID"`='%d' LIMIT 1", uniqueid);
				result = sendQueryResult(string, sql_result);
				if(numRows(result, sql_result) > 0) {						
					new p_name[MAX_PLAYER_NAME],
						userid = strval(getFieldAssoc_16(TPI_UID, result, sql_result)),
						t_stamp = strval(getFieldAssoc_16(TPI_STAMP, result, sql_result)),
						ip[16];		
					new year, month, day, hour, minute;				

					strins(ip, getFieldAssoc_16(TPI_IP, result, sql_result), 0);
					strins(p_name, getFieldAssoc_32(TPI_NICK, result, sql_result), 0);
					DeconvertNick(p_name);						
					
					freeResult(result, sql_result);
					
					dtimestamp(t_stamp, year, month, day, hour, minute);

					format(string, sizeof(string), "\
						Nick: "TEXT_DIALOG_NORMAL"%s  "TEXT_DIALOG_HEAD"(UID: "TEXT_DIALOG_NORMAL"%d"TEXT_DIALOG_HEAD")\n\
						IP: "TEXT_DIALOG_NORMAL"%s"TEXT_DIALOG_HEAD"\n\
						Data wejscia na serwer: "TEXT_DIALOG_NORMAL"%s  "TEXT_DIALOG_HEAD"[ "TEXT_DIALOG_NORMAL"%d:%02d "TEXT_DIALOG_HEAD"]",
					p_name, userid,
					ip,
					strData(year, month, day, " / ", false, false, true, false), hour, minute);
					ShowPlayerInfoDialog(playerid, BACK_HA_DATA_CHECK_LIST, "Sprawdz dane - Informacje", string);	
				
					return _TRUE;			
				} else {
					if(GetHelpVarValue(playerid, 99) == 0) {	
						ShowPlayerInfoDialog(playerid, BACK_HA_DATA_CHECK_LIST, "Sprawdz dane - Informacje", "Wystapil blad :( Daj znac komus kto moze to naprawic.");	
					} else {
						ShowPlayerInfoDialog(playerid, BACK_HA_DATA_SEARCH, "Sprawdz dane - Informacje", "Wystapil blad :( Daj znac komus kto moze to naprawic.");	
					}
				}
			}		
		} else HACheckDataList(playerid, 0);
	} 
	return _FALSE;
}
//===============================================================
//---------------------------------------------------------------
//===============================================================
/*
	6) Reset kont
*/
//===============================================================
//---------------------------------------------------------------
//===============================================================
HAStatisticsReset(playerid, listitem = -1) {
	if(IsAdmin(playerid) >= ALVL_HEAD_ADMIN) {
		switch(listitem) {
			case 0: HAAccountReset(playerid);
			case 1: HADailyStatsReset(playerid);
			default: {
				ShowPlayerDialogEx(playerid, DIALOG_ADMIN_RESET_STATS, DIALOG_STYLE_LIST, "Reset staytystyk", "1) Statystyki stale\n2) Statystyki dzienne", "Dalej", "Wroc");
			}
		}
		return 1;
	}
	return 0;
}
//---------------------------------------------------------------
HADailyStatsReset(playerid, bool:confirm = false) {
	if(IsAdmin(playerid) >= ALVL_HEAD_ADMIN) {
		if(confirm == false) {
			new string[350] = "* Brak *";
			if(fexist(DAILY_STATS_RESET_FILE)) {
				new File:f_open = fopen(DAILY_STATS_RESET_FILE, io_read);
				new t_stamp = 0;
				while(fread(f_open, string, sizeof(string))) {
					DeleteNewLine(string);
					if(strlen(string) > 11) {	
						if(strcmp(string, "last_reset=", false, 11) == 0) {
							t_stamp = strval(string[11]);
							break;
						}
					}
				}
				fclose(f_open);
				if(0 < t_stamp < timestamp()) {
					new year, month, day, hour, minute;
					dtimestamp(t_stamp, year, month, day, hour, minute);
					format(string, sizeof(string), "%s  "TEXT_DIALOG_HEAD"[ "TEXT_DIALOG_NORMAL"%d:%02d "TEXT_DIALOG_HEAD"]", strData(year, month, day, " / ", false, false, true, false), hour, minute);
				}
			}
			format(string, sizeof(string), "Reset statystyk dziennych usuwa wylacznie dane dot. okresu od ostatniego\nresetu kont lub statystyk dziennych. Nie sa usuwane, zadne trwale statystyki.\n\n\tOstatni reset statystyk dziennych: "TEXT_DIALOG_NORMAL"%s\n\n"TEXT_DIALOG_HEAD"\t         Czy chcesz teraz wykonac reset statystyk dziennych?", string);
			ShowPlayerYesNoDialog(playerid, D_YESNO_HA_DAILYRESET, "Reset statystyk dziennych", string);
		} else {
			CallLocalFunction("DailyPlayerStatsReset", "d", true);
			ShowPlayerInfoDialog(playerid, BACK_HAPANEL, "Reset statystyk dziennych", "Wykonano reset statystyk dziennych.");
		}
		return _TRUE;
	}
	return _FALSE;
}
//---------------------------------------------------------------
HAAccountReset(playerid, bool:confirm = false) {
	if(IsAdmin(playerid) >= ALVL_HEAD_ADMIN) {
		if(confirm == false) {
			new string[300] = "* Brak *";
			if(fexist(ACC_RESET_FILE)) {
				new File:f_open = fopen(ACC_RESET_FILE, io_read);
				new t_stamp = 0;
				while(fread(f_open, string, sizeof(string))) {
					DeleteNewLine(string);
					if(strlen(string) > 10) {	
						if(strcmp(string, "acc_reset=", false, 10) == 0) {
							t_stamp = strval(string[10]);
							break;
						}
					}
				}
				fclose(f_open);
				if(0 < t_stamp < timestamp()) {
					new year, month, day, hour, minute;
					dtimestamp(t_stamp, year, month, day, hour, minute);
					format(string, sizeof(string), "%s  "TEXT_DIALOG_HEAD"[ "TEXT_DIALOG_NORMAL"%d:%02d "TEXT_DIALOG_HEAD"]", strData(year, month, day, " / ", false, false, true, false), hour, minute);
				}
			}
			format(string, sizeof(string), "Podczas resetu kont, usuwane sa wszystkie statstyki graczy dot. zabojstw,\n        smierci, respektu, dmg i liczby zabojstw na poszczegolne bronie.\n\n\t\tOstatni reset kont: "TEXT_DIALOG_NORMAL"%s\n\n"TEXT_DIALOG_HEAD"\t\t  Czy chcesz teraz wykonac reset kont?", string);
			ShowPlayerYesNoDialog(playerid, D_YESNO_HA_ACCRESET, "Reset kont", string);
		} else {
			CallLocalFunction("AccountReset", "s", getPlayerName(playerid));
			ShowPlayerInfoDialog(playerid, BACK_HAPANEL, "Reset kont", "Wykonano reset statystyk kont graczy.");
		}
		return _TRUE;
	}
	return _FALSE;
}
//===============================================================
//---------------------------------------------------------------
//===============================================================
/*
	7) Obsluga baz danych
*/
//===============================================================
//---------------------------------------------------------------
//===============================================================
HABaseMenu(playerid, settingid = -1) {
	if(IsAdmin(playerid) == ALVL_GAME_MASTER) {
		switch(settingid) {
			case 0: HABaseCyclicOperations(playerid);
			case 1: HSBaseDeleteBasesList(playerid);
			default: ShowPlayerDialogEx(playerid, DIALOG_HA_BASE, DIALOG_STYLE_LIST, "Obsluga baz danych", "1) Wykonaj operacje cykliczne\n2) Usun dane z bazy", "Dalej", "Wroc");
		}
		return _TRUE;
	}
	return _FALSE;
}
//---------------------------------------------------------------
HABaseCyclicOperations(playerid, bool:confirm = false) {
	if(IsAdmin(playerid) == ALVL_GAME_MASTER) {
		new string[256];
		if(confirm == false) {
			new year, month, day, hour, minute;
			new date = 0;
			if(fexist(RESET_FILE)) {
				new File:f_open = fopen(RESET_FILE, io_read);
				while(fread(f_open, string, 32)) {
					DeleteNewLine(string);
					if(strlen(string) > 11) {
						if(strcmp(string, "last_reset=", false, 11) == 0) {
							date = strval(string[11]);
							break;
						}
					}
				}
				fclose(f_open);
				strdel(string, 0, 32);
			}
			if(date == 0) strins(string, "* Brak *", 0);
			else {
				dtimestamp(date, year, month, day, hour, minute);
				format(string, sizeof(string), TEXT_DIALOG_NORMAL"%s  [%d:%02d]", strData(year, month, day, " / ", false, false, true, false), hour, minute);
			}
			strins(string, "        Czy chcesz teraz wykonac operacje cykliczne, polegajace na usunieciu\nprzestarzalych danych oraz wykonaniu resetu kont, o ile zachodzi taka potrzeba?\n\n\tOstatnie operacje cykliczne byly wykonane ", 0);
			ShowPlayerYesNoDialog(playerid, D_YESNO_HA_CYCLICOPERATIONS, "Obsluga baz danych - Wykonaj operacje cykliczne", string);
		} else {
			format(string, sizeof(string), "Administrator %s (UID: %d) wydal polecenie wykonania operacji cyklicznych.", getPlayerName(playerid), getPlayerUserID(playerid));
			AddToResetInfoLog(string);
			asHourTimer(1);
			ShowPlayerInfoDialog(playerid, BACK_HAPANEL_BASE, "Obsluga baz danych - Wykonaj operacje cykliczne", "Wydano polecenie wykonania operacji cyklicznych.");
		}
		return _TRUE;
	}
	return _FALSE;
}
//---------------------------------------------------------------
HSBaseDeleteBasesList(playerid, listitem = -1) {
	if(IsAdmin(playerid) == ALVL_GAME_MASTER) {
		SetPlayerPage(playerid, listitem);
		switch(listitem) {
			case 0: ShowPlayerYesNoDialog(playerid, D_YESNO_HA_DELETEBASE, "Obsluga baz danych - Usun dane z bazy", "Czy chcesz "TEXT_DIALOG_ALERT"CALKOWICIE"TEXT_DIALOG_HEAD" usunac wpisy z bazy danych dot. zmian nickow?\n\n\t\t"TEXT_DIALOG_ALERT"Dane te beda niemozliwe do odzyskania!");
			case 1: ShowPlayerYesNoDialog(playerid, D_YESNO_HA_DELETEBASE, "Obsluga baz danych - Usun dane z bazy", "Czy chcesz "TEXT_DIALOG_ALERT"CALKOWICIE"TEXT_DIALOG_HEAD" usunac wpisy z bazy danych dot. graczy wchodzacych na serwer?\n\n\t\t\t  "TEXT_DIALOG_ALERT"Dane te beda niemozliwe do odzyskania!");
			case 2: ShowPlayerYesNoDialog(playerid, D_YESNO_HA_DELETEBASE, "Obsluga baz danych - Usun dane z bazy", "Czy chcesz "TEXT_DIALOG_ALERT"CALKOWICIE"TEXT_DIALOG_HEAD" usunac wpisy z bazy danych dot. banow stalych?\n\n\t\t  "TEXT_DIALOG_ALERT"Dane te beda niemozliwe do odzyskania!");
			case 3: ShowPlayerYesNoDialog(playerid, D_YESNO_HA_DELETEBASE, "Obsluga baz danych - Usun dane z bazy", "Czy chcesz "TEXT_DIALOG_ALERT"CALKOWICIE"TEXT_DIALOG_HEAD" usunac wpisy z bazy danych dot. banow czasowych?\n\n\t\t     "TEXT_DIALOG_ALERT"Dane te beda niemozliwe do odzyskania!");
			case 4: ShowPlayerYesNoDialog(playerid, D_YESNO_HA_DELETEBASE, "Obsluga baz danych - Usun dane z bazy", "Czy chcesz "TEXT_DIALOG_ALERT"CALKOWICIE"TEXT_DIALOG_HEAD" usunac wpisy z bazy danych dot. kont graczy?\n\n\t\t"TEXT_DIALOG_ALERT"Dane te beda niemozliwe do odzyskania!");
			default: ShowPlayerDialogEx(playerid, DIALOG_HA_BASE_DELETE, DIALOG_STYLE_LIST, "Obsluga baz danych - Usun dane z bazy", "1) Zmiany nickow\n2) Informacje o graczach\n3) Bany stale\n4) Bany czasowe\n5) Konta graczy", "Dalej", "Wroc");
		}
	}
	return _FALSE;
}
//---------------------------------------------------------------
HABaseDeleteBase(playerid, base) {
	if(IsAdmin(playerid) == ALVL_GAME_MASTER) {
		new string[128], s_base[40];
		switch(base) {
			case 0: { 
				sendQueryWithout("DELETE FROM `"T_NICK_CHANGE"`");
				strins(s_base, "zmian nickow", 0);
			}
			case 1: {
				sendQueryWithout("DELETE FROM `"T_PLAYER_INFO"`");
				strins(s_base, "informacji o graczach", 0);
			}
			case 2: {
				sendQueryWithout("DELETE FROM `"T_BAN"`");
				strins(s_base, "banow stalych", 0);
			}
			case 3: {
				sendQueryWithout("DELETE FROM `"T_TIME_BAN"`");
				strins(s_base, "banow czasowych", 0);
			}
			case 4: {
				sendQueryWithout("DELETE FROM `"T_KONTA"`");
				format(string, sizeof(string), "Administrator %s (User ID: %d) usunal(ela) wszystkie konta graczy.", getPlayerName(playerid), getPlayerUserID(playerid));
				AddToAdminLog(string);
				format(string, sizeof(string), " (Usuwanie baz danych) Administrator "TEXT_DIALOG_NORMAL"%s"TEXT_DIALOG_HEAD" (User ID: "TEXT_DIALOG_NORMAL"%d"TEXT_DIALOG_HEAD") usunal(ela) wszystkie konta graczy.", getPlayerName(playerid), getPlayerUserID(playerid));
				SendClientMessageToAll(COLOR_DIALOG_HEAD, string);
				forplayers(i) KickEx(i, 100);				
				return _TRUE;
			}			
		}
		format(string, sizeof(string), "Administrator %s (User ID: %d) usunal(ela) wszystkie dane z bazy %s.", getPlayerName(playerid), getPlayerUserID(playerid), s_base);
		AddToAdminLog(string);
		format(string, sizeof(string), "Usunieto wszystkie dane z bazy "TEXT_DIALOG_NORMAL"%s"TEXT_DIALOG_HEAD".", s_base);
		ShowPlayerInfoDialog(playerid, BACK_HAPANEL_BASEDELETE, "Obsluga baz danych - Usun dane z bazy", string);
		return _TRUE;
	}
	return _FALSE;
}
//===============================================================
//---------------------------------------------------------------
//===============================================================
/*
	8) Ustawienia serwera
*/
//===============================================================
//---------------------------------------------------------------
//===============================================================
forward HAServerSettings(playerid, settingid);
public HAServerSettings(playerid, settingid) {
	if(IsAdmin(playerid) >= ALVL_GAME_MASTER) {
		if(0 <= settingid <= 9) ShowPlayerSettingsMenu(playerid, settingid, -1);
		else if(GetPlayerPage(playerid) == 97) ShowPlayerSettingsMenu(playerid, 1, -1);
		else if(98 <= GetPlayerPage(playerid) <= 99) ShowPlayerSettingsMenu(playerid, 4, -1);
		else if(92 <= GetPlayerPage(playerid) <= 96 or 88 <= GetPlayerPage(playerid) <= 90) ShowPlayerSettingsMenu(playerid, 7, -1);
		else if(91 == GetPlayerPage(playerid)) ShowPlayerSettingsMenu(playerid, 96, -1);
		else {
			ShowPlayerDialogEx(playerid, DIALOG_HA_SETTINGS, DIALOG_STYLE_LIST, "Ustawienia serwera","\
				1) Ustawienia logow\n\
				2) Ustawienia rejestracji i logowania\n\
				3) Ustawienia obslugi kont\n\
				4) Ustawienia administracyjne\n\
				5) Ustawienia powiadomien i chatu\n\
				6) Ograniczenia graczy\n\
				7) Ustawienia VIP\n\
				8) Ustawienia antycheatu\n\
				9) Zewn. skrypty\n\
				10) Ustawienia GameModa\
			", "Dalej", "Wroc");
		}
		return _TRUE;
	}
	return _FALSE;
}
//---------------------------------------------------------------
forward ShowPlayerSettingsMenu(playerid, menuid, listitem);
public ShowPlayerSettingsMenu(playerid, menuid, listitem) {
	if(IsAdmin(playerid) >= ALVL_GAME_MASTER) {
		new string[800];
		SetPlayerPage(playerid, menuid);
		if(listitem == -1) {
			new head[64];
			switch(menuid) {
				case 0: {
					strins(head, "Ustawienia serwera - Ustawienia logow", 0);
					format(string, sizeof(string), "\
							1) Logi SA-MP\t\t\t\t\t\t[ %s"TEXT_DIALOG_BODY" ]\n\
							2) Logi chatu\t\t\t\t\t\t[ %s"TEXT_DIALOG_BODY" ]\n\
							3) Logi kont graczy\t\t\t\t\t[ %s"TEXT_DIALOG_BODY" ]\n\
							4) Logi zmian nicku\t\t\t\t\t[ %s"TEXT_DIALOG_BODY" ]\n\
						",
						getSettingIntValueByIndex(s_SAMPChatID) == 1 ? (C_LIGHTGREEN"Tak") : (C_ADMIN"Nie"),
						getSettingIntValueByIndex(s_LogChatID) == 1 ? (C_LIGHTGREEN"Tak") : (C_ADMIN"Nie"),
						getSettingIntValueByIndex(s_LogPlayersID) == 1 ? (C_LIGHTGREEN"Tak") : (C_ADMIN"Nie"),
						getSettingIntValueByIndex(s_LogNickChangeID) == 1 ? (C_LIGHTGREEN"Tak") : (C_ADMIN"Nie")
					);
					format(string, sizeof(string), "%s\
							5) Logi o graczach wchodzacych na serwer\t\t[ %s"TEXT_DIALOG_BODY" ]\n\
							6) Logi o usuwanych kontach\t\t\t\t[ %s"TEXT_DIALOG_BODY" ]\n\
							7) Logi banow\t\t\t\t\t\t[ %s"TEXT_DIALOG_BODY" ]\n\
							8) Logi kont VIP\t\t\t\t\t\t[ %s"TEXT_DIALOG_BODY" ]\n\
							9) Info. o podejrzeniu multikont\t\t\t\t[ %s"TEXT_DIALOG_BODY" ]\n\							
						", 
						string,						
						getSettingIntValueByIndex(s_LogPlayerInfoID) == 1 ? (C_LIGHTGREEN"Tak") : (C_ADMIN"Nie"),
						getSettingIntValueByIndex(s_LogDeletingInfoID) == 1 ? (C_LIGHTGREEN"Tak") : (C_ADMIN"Nie"),
						getSettingIntValueByIndex(s_LogBanInfoID) == 1 ? (C_LIGHTGREEN"Tak") : (C_ADMIN"Nie"),
						getSettingIntValueByIndex(s_LogVIPInfoID) == 1 ? (C_LIGHTGREEN"Tak") : (C_ADMIN"Nie"),
						getSettingIntValueByIndex(s_LogMultiAccountInfoID) == 1 ? (C_LIGHTGREEN"Tak") : (C_ADMIN"Nie")						
					);
						
					format(string, sizeof(string), "%s\
							10) Info. o operacjach cyklicznych\t\t\t[ %s "TEXT_DIALOG_BODY"]\n\
							11) Info. o nieaktywnym administratorze\t\t\t[ "TEXT_DIALOG_NORMAL"%d dni "TEXT_DIALOG_BODY"]\n\
							12) Kopiuj logi usuwanych kont\t\t\t\t[ %s "TEXT_DIALOG_BODY"]\n\
							13) Czas przechowywania informacji o graczach\t\t[ "TEXT_DIALOG_NORMAL"%d dni"TEXT_DIALOG_BODY" ]\n\
							14) Czas przechowywania informacji o zmianie nicku\t[ "TEXT_DIALOG_NORMAL"%d dni"TEXT_DIALOG_BODY" ]\
						",
						string,		
						getSettingIntValueByIndex(s_LogResetInfoID) == 1 ? (C_LIGHTGREEN"Tak") : (C_ADMIN"Nie"),
						getSettingIntValueByIndex(s_NonActiveAdminInfoID),
						getSettingIntValueByIndex(s_CopyDeletingID) == 1 ? (C_LIGHTGREEN"Tak") : (C_ADMIN"Nie"),
						getSettingIntValueByIndex(s_PlayerInfoMaxTimeID),
						getSettingIntValueByIndex(s_NickChangeMaxTimeID)						
					);
				}
				case 1: {
					strins(head, "Ustawienia serwera - Ustawienia rejestracji i logowania", 0);
					format(string, sizeof(string),"\
							1) Rejestracja na serwerze\t\t\t\t\t[ "C_WHITE"%s "TEXT_DIALOG_BODY"]\n\
							2) Ochrona 'Captha' dla niezarejestrowanych\t\t\t[ %s "TEXT_DIALOG_BODY"]\n\
							3) Czas na wpisanie 'Capthy' dla niezarejestrowanych\t\t[ "TEXT_DIALOG_NORMAL"%d sek. "TEXT_DIALOG_BODY"]\n\
							4) Minimalny czas rejestracji (IP)\t\t\t\t[ "TEXT_DIALOG_NORMAL"%d min. "TEXT_DIALOG_BODY"]\n\
							5) Warunkowy zaufany po rejestracji\t\t\t\t[ "TEXT_DIALOG_NORMAL"%d godz. "TEXT_DIALOG_BODY"]\n\
						",
						getSettingIntValueByIndex(s_RegisterObligatoryID) == 0 ? ("Dobrowolna") : getSettingIntValueByIndex(s_RegisterObligatoryID) == 1 ? ("Obowiazkowa") : ("Wylaczona"),
						getSettingIntValueByIndex(s_StartingCaptchaID) == 1 ? (C_LIGHTGREEN"Tak") : (C_ADMIN"Nie"),
						getSettingIntValueByIndex(s_StartingCaptchaTimeID),						
						getSettingIntValueByIndex(s_RegisterMinTimeID),
						getSettingIntValueByIndex(s_ProvConfiRegisterID)
					);					
					
					format(string, sizeof(string),"%s\
							6) Czas na zalogowanie\t\t\t\t\t\t[ "TEXT_DIALOG_NORMAL"%d sek. "TEXT_DIALOG_BODY"]\n\
							7) Maksymalna ilosc blednych logowan\t\t\t\t[ "TEXT_DIALOG_NORMAL"%d "TEXT_DIALOG_BODY"]\n\
							8) Maksymalna ilosc blednych logowan 'aLog'\t\t\t[ "TEXT_DIALOG_NORMAL"%d "TEXT_DIALOG_BODY"]\n\
							9) Maksymalny czas na auto-zalogowanie\t\t\t[ "TEXT_DIALOG_NORMAL"%d min. "TEXT_DIALOG_BODY"]\
						",
						string,
						getSettingIntValueByIndex(s_LoginTimeID),
						getSettingIntValueByIndex(s_LoginFailID),
						getSettingIntValueByIndex(s_ALogLoginFailsID),
						getSettingIntValueByIndex(s_ReconnectMaxTimeID)
					);
				}
				case 2: {
					strins(head, "Ustawienia serwera - Ustawienia obslugi kont", 0);
					format(string, sizeof(string), "\
							1) Minimalny czas zmiany nicku\t\t\t\t[ "TEXT_DIALOG_NORMAL"%d dni"TEXT_DIALOG_BODY" ]\n\
							2) Maksymalny czas nieaktywnosci gracza\t\t[ "TEXT_DIALOG_NORMAL"%d dni"TEXT_DIALOG_BODY" ]\n\
							3) Minimalny czas gry do uzyskania 'Zaufanego'\t\t[ "TEXT_DIALOG_NORMAL"%d godz."TEXT_DIALOG_BODY" ]\
						",
						getSettingIntValueByIndex(s_NickChangeTimeID),	
						getSettingIntValueByIndex(s_LoginDeletingDaysID),	
						getSettingIntValueByIndex(s_LoginConfiID)
					);						
				}
				case 3: {
					new special_month[32], days, month;
					getdate(month, month);
					if(getSettingIntValueByIndex(s_AutoAccResetDay) > (days = GetDaysInMonth(month))) {
						format(special_month, sizeof(special_month), " ( "C_LIGHTGREEN"%d"TEXT_DIALOG_BODY" ) ", days);
					}
					
					strins(head, "Ustawienia serwera - Ustawienia administracyjne", 0);
					format(string, sizeof(string), "\
							1) Zdalna konsola SA-MP\t\t\t\t[ %s "TEXT_DIALOG_BODY"]\n\
							2) Uzywany typ bazy danych\t\t\t\t[ "TEXT_DIALOG_NORMAL"%s"TEXT_DIALOG_BODY" ]\n\
							3) Maksymalny czas nieaktywnosci administratora\t[ "TEXT_DIALOG_NORMAL"%d dni"TEXT_DIALOG_BODY" ]\n\
						",
						getSettingIntValueByIndex(s_SAMPRemoteID) == 1 ? (C_LIGHTGREEN"Tak") : (C_ADMIN"Nie"),
						getSettingIntValueByIndex(s_MySQLID) == 1 ? ChangeBaseType == true ? (C_ORANGE"MySQL -> SQL") : (C_LIGHTGREEN"MySQL") : ChangeBaseType == true ? (C_ORANGE"SQL - > MySQL") : (C_LIGHTGREEN"SQL"),
						getSettingIntValueByIndex(s_NADelAdminRightsID)
					);
					format(string, sizeof(string),"%s\
							4) Maksymany czas kicka dla Junior Admina\t\t[ "TEXT_DIALOG_NORMAL"%d min."TEXT_DIALOG_BODY" ]\n\
							5) Maksymany czas trwania bana czasowego\t\t[ "TEXT_DIALOG_NORMAL"%d godz."TEXT_DIALOG_BODY" ]\n\
							6) Automatyczne operacje cykliczne\t\t\t[ %s "TEXT_DIALOG_BODY"]\n\
							7) Godzina wykonywania operacji cyklicznych\t\t[ "TEXT_DIALOG_NORMAL"%d"TEXT_DIALOG_BODY" ]\n\
							8) Automatyczny reset kont\t\t\t\t[ %s "TEXT_DIALOG_BODY"]\n\
						",
						string,						
						getSettingIntValueByIndex(s_BanTimeJAdminID),
						getSettingIntValueByIndex(s_BanTimeAdminID),
						getSettingIntValueByIndex(s_AutomaticCyclicOps) == 1 ? (C_LIGHTGREEN"Tak") : (C_ADMIN"Nie"),
						getSettingIntValueByIndex(s_ResetTimeID),
						getSettingIntValueByIndex(s_AutomaticAccReset) == 1 ? (C_LIGHTGREEN"Tak") : (C_ADMIN"Nie")						
					);						

					format(string, sizeof(string), "%s\
							9) Dzien wykonywania resetu kont\t\t\t[ "TEXT_DIALOG_NORMAL"%d"TEXT_DIALOG_BODY" %s]\n\
							10) Konta RCON\t\t\t\t\t[ %s "TEXT_DIALOG_BODY"]\n\
							11) Maks. blednych logowan RCON\t\t\t[ "TEXT_DIALOG_NORMAL"%d"TEXT_DIALOG_BODY" ]\n\
							12) Maks. czas uciszenia (komenda)\t\t\t[ "TEXT_DIALOG_NORMAL"%d min."TEXT_DIALOG_BODY" ]\n\
							13) Auto. reset stat. dziennych\t\t\t\t[ %s "TEXT_DIALOG_BODY"]\
						",	
						string,
						getSettingIntValueByIndex(s_AutoAccResetDay), special_month,
						getSettingIntValueByIndex(s_RCONAccountsID) == 1 ? (C_LIGHTGREEN"Tak") : (C_ADMIN"Nie"),
						getSettingIntValueByIndex(s_RCONFailLoginID),
						getSettingIntValueByIndex(s_MuteMaxTimeID),
						getSettingIntValueByIndex(s_AutoDailyStatsReset) == 1 ? (C_LIGHTGREEN"Tak") : (C_ADMIN"Nie")						
					);
				}
				case 4: {
					strins(head, "Ustawienia serwera - Ustawienia powiadomien i chatu", 0);
					format(string, sizeof(string), "\
							1) Con-Dis Info\t\t\t\t\t[ %s"TEXT_DIALOG_BODY" ]\n\
							2) Typ cenzury\t\t\t\t\t[ "C_WHITE"%s"TEXT_DIALOG_BODY" ]\n\
							3) 'Mute' za przeklinanie\t\t\t[ %s "TEXT_DIALOG_BODY"]\n\
							4) Czas uciszenia za przeklinanie\t\t[ "C_WHITE"%d min. "TEXT_DIALOG_BODY"]\n\
					", 
						getSettingIntValueByIndex(s_ConDisInfoID) == 1 ? (C_LIGHTGREEN"Tak") : (C_ADMIN"Nie"),
						getSettingIntValueByIndex(s_CensureStatusID) == 0 ? ("Brak") : getSettingIntValueByIndex(s_CensureStatusID) == 2 ? ("Gwiazdkowanie") : ("Calkowita"),
						getSettingIntValueByIndex(s_CensureMuteStatusID) == 1 ? (C_LIGHTGREEN"Tak") : (C_ADMIN"Nie"),
						getSettingIntValueByIndex(s_CensureMuteTimeID)
					);					
					
					format(string, sizeof(string),"%s\
							5) Limit ostrzezen za przeklinanie\t\t[ "C_WHITE"%d"TEXT_DIALOG_BODY" ]\n\
							6) Anty Spam\t\t\t\t\t[ %s"TEXT_DIALOG_BODY" ]\n\
							7) Czas min. odstepu wiadomosci (spam)\t[ "C_WHITE"%d sek."TEXT_DIALOG_BODY" ]\n\
							8) Anty Flood\t\t\t\t\t[ %s"TEXT_DIALOG_BODY" ]\n\
							9) Czas min. odstepu wiadomosci (flood)\t[ "C_WHITE"%d sek."TEXT_DIALOG_BODY" ]\n\
							10) Prywatne wiadomosci\t\t\t[ %s"TEXT_DIALOG_BODY" ]\n\
							11) Priv. Min. Admin Spec LvL\t\t\t[ "C_WHITE"%s"TEXT_DIALOG_BODY" ]\
					",
						string,
						getSettingIntValueByIndex(s_CensureMaxWarningsID),
						getSettingIntValueByIndex(s_AntySpamStatusID) == 1 ? (C_LIGHTGREEN"Tak") : (C_ADMIN"Nie"),
						getSettingIntValueByIndex(s_AntySpamMinTimeID),
						getSettingIntValueByIndex(s_AntyFloodStatusID) == 1 ? (C_LIGHTGREEN"Tak") : (C_ADMIN"Nie"),
						getSettingIntValueByIndex(s_AntyFloodMinTimeID),
						getSettingIntValueByIndex(s_PrivMessagesID) == 1 ? (C_LIGHTGREEN"Tak") : (C_ADMIN"Nie"),
						GetAdminNameByLvL(getSettingIntValueByIndex(s_PrivMessagesSpecID))
					);	
				}			
				case 5: {
					strins(head, "Ustawienia serwera - Ograniczenia graczy", 0);
					format(string, sizeof(string), "\
							1) Maksymalny ping\t\t\t\t\t[ "C_WHITE"%d"TEXT_DIALOG_BODY" ]\n\
							2) Maksymalny ping (Ostrzezenia)\t\t\t[ "C_WHITE"%d"TEXT_DIALOG_BODY" ]\n\
							3) Minimalne FPS'y\t\t\t\t\t[ "C_WHITE"%d"TEXT_DIALOG_BODY" ]\n\
							4) Minimalne FPS'y (Ostrzezenia)\t\t\t[ "C_WHITE"%d"TEXT_DIALOG_BODY" ]\n\
							5) Maks. utrata pakietow\t\t\t\t[ "C_WHITE"%d proc."TEXT_DIALOG_BODY" ]\n\
						",
						getSettingIntValueByIndex(s_MaxPingID),
						getSettingIntValueByIndex(s_MaxPingWarningsID),
						getSettingIntValueByIndex(s_MinFPSID),
						getSettingIntValueByIndex(s_MinFPSWarningsID),
						getSettingIntValueByIndex(s_MaxPLossID)
					);
					format(string, sizeof(string), "%s\
							6) Maks. utrata pakietow (Ostrzezenia)\t\t\t[ "C_WHITE"%d"TEXT_DIALOG_BODY" ]\n\
							7) Czestotliwosc testow (Ping / FPS / P-Loss)\t\t[ "C_WHITE"%d sek."TEXT_DIALOG_BODY" ]\n\
							8) Ograniczenia administracji\t\t\t\t[ %s"TEXT_DIALOG_BODY" ]\n\
							9) Ograniczenia VIP'ow\t\t\t\t\t[ %s"TEXT_DIALOG_BODY" ]\n\
					", 
						string,
						getSettingIntValueByIndex(s_MaxPLossWarningsID),
						getSettingIntValueByIndex(s_CheckDataFrequencyID),
						getSettingIntValueByIndex(s_AdminLimitsID) == 1 ? (C_LIGHTGREEN"Tak") : (C_ADMIN"Nie"),
						getSettingIntValueByIndex(s_VIPLimitsID) == 1 ? (C_LIGHTGREEN"Tak") : (C_ADMIN"Nie")
					);		
					format(string, sizeof(string), "%s\
							10) Kryt. utrata pakietow\t\t\t\t[ "C_WHITE"%d"TEXT_DIALOG_BODY" ]\n\
							11) Kryt. wartosc pingu\t\t\t\t\t[ "C_WHITE"%d"TEXT_DIALOG_BODY" ]\
					", 
						string,
						getSettingIntValueByIndex(s_MaxPLossCriticalLimitID),
						getSettingIntValueByIndex(s_MaxPingCriticalLimitID)
					);							
				}
				case 6: { 
					strins(head, "Ustawienia serwera - Ustawienia VIP", 0);
					format(string, sizeof(string), "\
							1) Konto VIP po rejestracji\t\t\t[ "C_WHITE"%d dni"TEXT_DIALOG_BODY" ]\n\
							2) Punkty VIP po rejestracji\t\t\t[ "C_WHITE"%d pkt."TEXT_DIALOG_BODY" ]\n\
							3) Ilosc punktow za 3 dni konta VIP\t\t[ "C_WHITE"%d pkt."TEXT_DIALOG_BODY" ]\n\
							4) Ilosc punktow za 7 dni konta VIP\t\t[ "C_WHITE"%d pkt."TEXT_DIALOG_BODY" ]\n\
							5) Ilosc punktow za 30 dni konta VIP\t\t[ "C_WHITE"%d pkt."TEXT_DIALOG_BODY" ]\n\
							6) Omijanie banow czasowych dla VIP\t\t[ %s"TEXT_DIALOG_BODY" ]\
						",
						getSettingIntValueByIndex(s_VIPRegisterTimeID),
						getSettingIntValueByIndex(s_VIPRegisterPointsID),
						getSettingIntValueByIndex(s_VIP3DaysCostID),
						getSettingIntValueByIndex(s_VIP7DaysCostID),
						getSettingIntValueByIndex(s_VIP30DaysCostID),
						getSettingIntValueByIndex(s_VIPTimeBanID) == 1 ? (C_LIGHTGREEN"Tak") : (C_ADMIN"Nie")
					);			
				}
				case 7: {
					strins(head, "Ustawienia serwera - Anty Cheat", 0);
					format(string, sizeof(string), "\
							1) Gra z tego samego IP\t\t\t\t[ %s"TEXT_DIALOG_BODY" ]\n\
							2) Rejoin spam bot\t\t\t\t\t[ %s"TEXT_DIALOG_BODY" ]\n\
							3) Chat spam bot\t\t\t\t\t[ %s"TEXT_DIALOG_BODY" ]\n\
							4) CMD spam bot\t\t\t\t\t[ %s"TEXT_DIALOG_BODY" ]\n\
							5) Fake-Kill spam bot\t\t\t\t\t[ %s"TEXT_DIALOG_BODY" ]\n\
							6) SA-MP pieniadze\t\t\t\t\t[ %s"TEXT_DIALOG_BODY" ]\n\
							7) Anty Jetpack\t\t\t\t\t\t[ %s"TEXT_DIALOG_BODY" ]\n\
							8) Niedostepne bronie\t\t\t\t\t[ %s"TEXT_DIALOG_BODY" ]\n\
						",
						getSettingIntValueByIndex(s_ACConnectionSpamBotStatusID) == 1 ? (C_LIGHTGREEN"Tak") : (C_ADMIN"Nie"),
						getSettingIntValueByIndex(s_ACAntyReJoinSpamStatusID) == 1 ? (C_LIGHTGREEN"Tak") : (C_ADMIN"Nie"),
						getSettingIntValueByIndex(s_ACAntySpamBotStatusID) == 1 ? (C_LIGHTGREEN"Tak") : (C_ADMIN"Nie"),
						getSettingIntValueByIndex(s_ACAntyCMDSpamBotStatusID) == 1 ? (C_LIGHTGREEN"Tak") : (C_ADMIN"Nie"),
						getSettingIntValueByIndex(s_ACAntyFakeKillSpamBotStatusID) == 1 ? (C_LIGHTGREEN"Tak") : (C_ADMIN"Nie"),
						getSettingIntValueByIndex(s_ACAntyMoneyHackStatusID) == 1 ? (C_LIGHTGREEN"Tak") : (C_ADMIN"Nie"),				
						getSettingIntValueByIndex(s_ACAntyJetpackStatusID) == 1 ? (C_LIGHTGREEN"Tak") : (C_ADMIN"Nie"),		
						getSettingIntValueByIndex(s_ACAntyWeaponStatusID) == 1 ? (C_LIGHTGREEN"Tak") : (C_ADMIN"Nie")
					);
					format(string, sizeof(string),"%s\
							9) Anty godmode\t\t\t\t\t[ %s"TEXT_DIALOG_BODY" ]\
						",
						string,
						getSettingIntValueByIndex(s_ACAntyGodmodeStatusID) == 1 ? (C_LIGHTGREEN"Tak") : (C_ADMIN"Nie"));
				}
				case 8: {
					strins(head, "Ustawienia serwera - Zewnetrzne skrypty", 0);
					format(string, sizeof(string), "\
						1) AxL Anty Glitch (min. ver. "C_WHITE"1.2.1"TEXT_DIALOG_BODY")\t\t[ %s"TEXT_DIALOG_BODY" ]\n\
						2) AxL Anty Macro (min. ver. "C_WHITE"1.0.4"TEXT_DIALOG_BODY")\t\t[ %s"TEXT_DIALOG_BODY" ]\n\
						3) AxL Anty Crasher (min. ver. "C_WHITE"1.0.1"TEXT_DIALOG_BODY")\t\t[ %s"TEXT_DIALOG_BODY" ]\
					", 
						CallRemoteFunction("AAGStatus", "") == 0 ? (C_WHITE"NoN") : CallRemoteFunction("AAGStatus", "") == 1 ? (C_LIGHTGREEN"ON") : (C_ADMIN"OFF"),
						CallRemoteFunction("AMacroStatus", "") == 0 ? (C_WHITE"NoN") : CallRemoteFunction("AMacroStatus", "") == 1 ? (C_LIGHTGREEN"ON") : (C_ADMIN"OFF"),
						CallRemoteFunction("ACrasherStatus", "") == 0 ? (C_WHITE"NoN") : CallRemoteFunction("ACrasherStatus", "") == 1 ? (C_LIGHTGREEN"ON") : (C_ADMIN"OFF")
					);
				}				
				case 9: {
					if(CallRemoteFunction("ShowPlayerGamePanelMenu", "ddd", playerid, -1, 0) == 0) {
						return ShowPlayerInfoDialog(playerid, BACK_SETTING_MENU, "Ustawienia serwera - Ustawienia Gamemoda", "Brak odpowiedzi ze strony aktualnie uruchomionego GameModa.\n   Wyglada na to, ze GameMod nie obsluguje systemu ustawien.");
					} else return 1;
				}						
				case 88: {
					strins(head, "Anty Cheat - Godmode", 0);
					format(string, sizeof(string), "\
						1) Stan zabezpieczenia\t\t\t\t\t[ %s"TEXT_DIALOG_BODY" ]\n\
						2) Maks. liczba ostrzezen\t\t\t\t[ "C_WHITE"%d"TEXT_DIALOG_BODY" ]\n\
						3) Czestotliwosc testu\t\t\t\t\t[ "C_WHITE"%d j."TEXT_DIALOG_BODY" ]\
					", 				
						getSettingIntValueByIndex(s_ACAntyGodmodeStatusID) == 1 ? (C_LIGHTGREEN"Aktywne") : (C_ADMIN"Nieaktywne"),
						getSettingIntValueByIndex(s_ACAntyGodmodeMaxWarnsID),
						getSettingIntValueByIndex(s_ACAntyGodmodeTicksID)
					);					
				}				
				case 89: {
					strins(head, "Anty Cheat - Rejoin spam bot", 0);
					format(string, sizeof(string), "\
						1) Stan zabezpieczenia\t\t\t\t\t[ %s"TEXT_DIALOG_BODY" ]\n\
						2) Min. liczba polaczen\t\t\t\t\t[ "C_WHITE"%d"TEXT_DIALOG_BODY" ]\
					", 				
						getSettingIntValueByIndex(s_ACAntyReJoinSpamStatusID) == 1 ? (C_LIGHTGREEN"Aktywne") : (C_ADMIN"Nieaktywne"),
						getSettingIntValueByIndex(s_ACAntyReJoinSpamTryID)
					);					
				}
				case 90: {
					strins(head, "Anty Cheat - Niedostepne bronie", 0);
					
					new counter;
					for(new i; i < sizeof(ac_Weapons); i ++) {
						if(ac_Weapons[i] == NOT_ALLOWED_WEAPON) {
							if(!(19 <= i <= 21)) {
								counter ++;
							}		
						}
					}						
					
					format(string, sizeof(string), "\
						1) Stan zabezpieczenia\t\t\t\t\t[ %s"TEXT_DIALOG_BODY" ]\n\
						2) Lista zablokowanych broni\t\t\t\t[ "C_WHITE"%d "TEXT_DIALOG_BODY"]\n\
						3) Przeladuj liste zablokowanych broni\
					", 				
						getSettingIntValueByIndex(s_ACAntyWeaponStatusID) == 1 ? (C_LIGHTGREEN"Aktywne") : (C_ADMIN"Nieaktywne"),
						counter
					);						
				}				
				case 91: {
					strins(head, "Anty Cheat - SA-MP pieniadze (Akcja)", 0);
					format(string, sizeof(string), "\
						1) Reset pieniedzy\t\t\t\t\t[ %s"TEXT_DIALOG_BODY" ]\n\
						2) Kick\t\t\t\t\t\t\t[ %s"TEXT_DIALOG_BODY" ]\
					", 				
						getSettingIntValueByIndex(s_ACAntyMoneyHackActionID) == 0 ? (C_LIGHTGREEN"Tak") : (C_ADMIN"Nie"),
						getSettingIntValueByIndex(s_ACAntyMoneyHackActionID) == 1 ? (C_LIGHTGREEN"Tak") : (C_ADMIN"Nie")
					);						
				}
				case 92: {
					strins(head, "Anty Cheat - Gra z tego samego IP", 0);
					format(string, sizeof(string), "\
						1) Stan zabezpieczenia\t\t\t\t\t[ %s"TEXT_DIALOG_BODY" ]\n\
						2) Min. czas miedzy polaczeniami\t\t\t[ "C_WHITE"%d"TEXT_DIALOG_BODY" ]\
					", 				
						getSettingIntValueByIndex(s_ACConnectionSpamBotStatusID) == 1 ? (C_LIGHTGREEN"Aktywne") : (C_ADMIN"Nieaktywne"),
						getSettingIntValueByIndex(s_ACConnectionSpamBotTimeID)
					);						
				}
				case 93: {
					strins(head, "Anty Cheat - Chat spam bot", 0);
					format(string, sizeof(string), "\
						1) Stan zabezpieczenia\t\t\t\t\t[ %s"TEXT_DIALOG_BODY" ]\n\
						2) Min. wiadmosci na sekunde\t\t\t\t[ "C_WHITE"%d"TEXT_DIALOG_BODY" ]\
					", 				
						getSettingIntValueByIndex(s_ACAntySpamBotStatusID) == 1 ? (C_LIGHTGREEN"Aktywne") : (C_ADMIN"Nieaktywne"),
						getSettingIntValueByIndex(s_ACAntySpamBotMsgPerSecID)
					);							
				}
				case 94: {
					strins(head, "Anty Cheat - CMD spam bot", 0);
					format(string, sizeof(string), "\
						1) Stan zabezpieczenia\t\t\t\t\t[ %s"TEXT_DIALOG_BODY" ]\n\
						2) Min. komend na sekunde\t\t\t\t[ "C_WHITE"%d"TEXT_DIALOG_BODY" ]\
					", 				
						getSettingIntValueByIndex(s_ACAntyCMDSpamBotStatusID) == 1 ? (C_LIGHTGREEN"Aktywne") : (C_ADMIN"Nieaktywne"),
						getSettingIntValueByIndex(s_ACAntyCMDSpamBotMsgPerSecID)
					);						
				}
				case 95: {
					strins(head, "Anty Cheat - Fake-Kill spam bot", 0);
					format(string, sizeof(string), "\
						1) Stan zabezpieczenia\t\t\t\t\t[ %s"TEXT_DIALOG_BODY" ]\n\
						2) Min. smierci na sekunde\t\t\t\t[ "C_WHITE"%d"TEXT_DIALOG_BODY" ]\
					", 				
						getSettingIntValueByIndex(s_ACAntyFakeKillSpamBotStatusID) == 1 ? (C_LIGHTGREEN"Aktywne") : (C_ADMIN"Nieaktywne"),
						getSettingIntValueByIndex(s_ACAntyFakeKillsPerSecStatusID)
					);							
				}
				case 96: {
					strins(head, "Anty Cheat - SA-MP pieniadze", 0);
					format(string, sizeof(string), "\
						1) Stan zabezpieczenia\t\t\t\t\t[ %s"TEXT_DIALOG_BODY" ]\n\
						2) Podejmowana akcja\t\t\t\t\t[ "C_WHITE"%s"TEXT_DIALOG_BODY" ]\
					", 				
						getSettingIntValueByIndex(s_ACAntyMoneyHackStatusID) == 1 ? (C_LIGHTGREEN"Aktywne") : (C_ADMIN"Nieaktywne"),
						getSettingIntValueByIndex(s_ACAntyMoneyHackActionID) == 0 ? ("Reset") : ("Kick")
					);						
				}
				case 97: {
					strins(head, "Ustawienia rejestracji - Rejestracja na serwerze", 0);	// lolo2
					format(string, sizeof(string), "\
						1) Dobrowolna\t\t\t\t\t[ %s"TEXT_DIALOG_BODY" ]\n\
						2) Obowiazkowa\t\t\t\t[ %s"TEXT_DIALOG_BODY" ]\n\
						3) Wylaczona\t\t\t\t\t[ %s"TEXT_DIALOG_BODY" ]\
					", 
						getSettingIntValueByIndex(s_RegisterObligatoryID) == 0 ? (C_LIGHTGREEN"Tak") : (C_ADMIN"Nie"),
						getSettingIntValueByIndex(s_RegisterObligatoryID) == 1 ? (C_LIGHTGREEN"Tak") : (C_ADMIN"Nie"),
						getSettingIntValueByIndex(s_RegisterObligatoryID) == 2 ? (C_LIGHTGREEN"Tak") : (C_ADMIN"Nie")
					);					
				}
				case 98: {
					strins(head, "Ustawienia powiadomien i chatu - Priv. Min. Admin LvL", 0);
					format(string, sizeof(string), "\
						1) Brak\t\t\t\t\t[ %s"TEXT_DIALOG_BODY" ]\n\
						2) Junior Admin\t\t\t\t[ %s"TEXT_DIALOG_BODY" ]\n\
						3) Admin\t\t\t\t[ %s"TEXT_DIALOG_BODY" ]\n\
						4) Head Admin\t\t\t\t[ %s"TEXT_DIALOG_BODY" ]\n\
						5) Game Master\t\t\t\t[ %s"TEXT_DIALOG_BODY" ]\
					", 
						getSettingIntValueByIndex(s_PrivMessagesSpecID) == 0 ? (C_LIGHTGREEN"Tak") : (C_ADMIN"Nie"),
						getSettingIntValueByIndex(s_PrivMessagesSpecID) == 1 ? (C_LIGHTGREEN"Tak") : (C_ADMIN"Nie"),
						getSettingIntValueByIndex(s_PrivMessagesSpecID) == 2 ? (C_LIGHTGREEN"Tak") : (C_ADMIN"Nie"),
						getSettingIntValueByIndex(s_PrivMessagesSpecID) == 3 ? (C_LIGHTGREEN"Tak") : (C_ADMIN"Nie"),
						getSettingIntValueByIndex(s_PrivMessagesSpecID) == 4 ? (C_LIGHTGREEN"Tak") : (C_ADMIN"Nie")
					);								
				}
				case 99: {
					strins(head, "Ustawienia powiadomien i chatu - Typ cenzury", 0);
					format(string, sizeof(string), "\
						1) Brak\t\t\t\t\t[ %s"TEXT_DIALOG_BODY" ]\n\
						2) Blokowanie wiadomosci\t\t[ %s"TEXT_DIALOG_BODY" ]\n\
						3) Gwiazdkowanie\t\t\t[ %s"TEXT_DIALOG_BODY" ]\
					", 
						getSettingIntValueByIndex(s_CensureStatusID) == 0 ? (C_LIGHTGREEN"Tak") : (C_ADMIN"Nie"),
						getSettingIntValueByIndex(s_CensureStatusID) == 1 ? (C_LIGHTGREEN"Tak") : (C_ADMIN"Nie"),
						getSettingIntValueByIndex(s_CensureStatusID) == 2 ? (C_LIGHTGREEN"Tak") : (C_ADMIN"Nie")
					);					
				}
				default: HAServerSettings(playerid, -1);
			}
			ShowPlayerDialogEx(playerid, DIALOG_HE_SET_MENU, DIALOG_STYLE_LIST, head, string, "Dalej", "Wroc");
		} else {
			switch(menuid) {
				case 0: {
					switch(listitem) {
						case 0:	ShowPlayerYesNoDialog(playerid, D_YESNO_SET_SAMPLOG, "Ustawienia logow - Logi SA-MP", 
							"Logi SA-MP sa standardowymi logami zapisywanymi w pliku 'server_log.txt'.\n Zaleca sie ich wylaczenie w przypadku korzystania z systemu logow chatu.\n\n\t\t         Czy chcesz wlaczyc logi SA-MP?");
						case 1: ShowPlayerYesNoDialog(playerid, D_YESNO_SET_CHATLOG, "Ustawienia logow - Logi chatu", 
							"System logow chatu pozwala na zapisywanie wiadomosci do plikow nazywanych\ndata dokonania wpisu, co umozliwia szybkie znalezienie interesujacych danych.\n          W przypadku wlaczenia systemu, zaleca sie wylaczenie logow SA-MP.\n\n\t\t    Czy chcesz wlaczyc system logow chatu?");
						case 2: ShowPlayerYesNoDialog(playerid, D_YESNO_SET_PLAYERLOG, "Ustawienia logow - Logi kont graczy", 
							"System logow kont graczy pozwala na zapisywanie wszelkich zmian\n\tna koncie gracza do pliku nazwanego jego User ID.\n\n\t    Czy wlaczyc chcesz system logow kont graczy?");
						case 3: ShowPlayerYesNoDialog(playerid, D_YESNO_SET_NICKLOG, "Ustawienia logow - Logi zmian nicku", 
							" Kazda zmiana nicku dla konta gracza, moze byc odnotowana dzieki wlaczeniu tego systemu.\nPozwoli to na latwiejsze wyszukanie pierwotnego nicku gracza jesli zajdzie taka koniecznosc.\n\n\t\t\tCzy wlaczyc chcesz system logow zmian nicku?");
						case 4: ShowPlayerYesNoDialog(playerid, D_YESNO_SET_CONNLOG, "Ustawienia logow - Logi o polaczeniach graczy", 
							"Dane dot. kazdego gracza wchodzacego na serwer, czyli jego nick, User ID, IP, GPCI moga byc zapisywane w systemie.\n\t\tPozwoli to w razie koniecznosci na wyszukanie interesujacych administratora danych.\n\n\t\t\tCzy wlaczyc chcesz system logow o graczach wchodzacych na serwer?");
						case 5: ShowPlayerYesNoDialog(playerid, D_YESNO_SET_ACCDELLOG, "Ustawienia logow - Logi o usuwanych kontach", 
							"Kazde usuniecie konta gracza moze zostac odnotowane w odpowiednim pliku logow.\n\tPozwoli to na sprawdzenie jakie konta, za co i kiedy zostaly usuniete.\n\n\t\tCzy wlaczyc chcesz system logow o usuwanych kontach?");
						case 6: ShowPlayerYesNoDialog(playerid, D_YESNO_SET_BANLOG, "Ustawienia logow - Logi banow", 
							"Istnieje mozliwosc, zeby kazdy ban, zarowno czasowy jak i staly byl\n\t         odnotowany w oddzielnym pliku logow.\n\n\t\tCzy chcesz skorzystac z tej opcji?");
						case 7: ShowPlayerYesNoDialog(playerid, D_YESNO_SET_VIPLOG, "Ustawienia logow - Logi kont VIP", 
							"Istnieje mozliwosc, zeby kazdy operacja na statusie kont VIP byla\n       odnotowywana w odnotowany w oddzielnym pliku logow.\n\n\t\tCzy chcesz skorzystac z tej opcji?");
						case 8: ShowPlayerYesNoDialog(playerid, D_YESNO_SET_MULTIACCLOG, "Ustawienia logow - Info. o podejrzeniu multikont", 
							"\t  Przy kazdej rejestracji konta przez gracza, system sprawdza czy\n  w ciagu ostanich godzin nie bylo rejestrowane konto z tego samego komputera.\nW przypadku wykrycia zbieznosci (IP, Host, GPCI) istnieje mozliwosc odnotowania\n\t\t            tego faktu w oddzielnym pliku logow.\n\n\t\t             Czy chcesz wlaczyc logi multikont?");
						case 9: ShowPlayerYesNoDialog(playerid, D_YESNO_SET_RESETLOG, "Ustawienia logow - Info o operacjach cyklicznych", 
							"Kazda wykonana operacja cykliczna moze byc odnotowana w oddzielnym pliku logow.\n\n\t      Czy chcesz wlaczyc informowanie o operacjach cyklicznych?");
						case 10: ShowPlayerValueDialogBack(playerid, D_VALUE_SET_NACTIVE_ADMIN_INFO); //s_NonActiveAdminInfoID
						case 11: ShowPlayerYesNoDialog(playerid, D_YESNO_SET_COPYDELACC, "Ustawienia logow - Kopiuj logi usuwanych kont", 
							"           Podczas usuwania konta, usuwany jest rowniez plik jego logow.\nIstnieje jednak mozliwosc przeniesienia tego pliku do oddzielnego folderu.\n\n        Czy chcesz skorzystac z opcji kopiowania logow usuwanych kont?");
						case 12: ShowPlayerValueDialogBack(playerid, D_VALUE_SET_PLAYER_INFO);	//s_PlayerInfoMaxTimeID
						case 13: ShowPlayerValueDialogBack(playerid, D_VALUE_SET_NICK_CHANGE_INFO); //s_NickChangeMaxTimeID		
						default: ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);
					}
				}
				case 1: {
					switch(listitem) {
						case 0: ShowPlayerSettingsMenu(playerid, 97, -1);
						case 1: ShowPlayerYesNoDialog(playerid, D_YESNO_SET_CAPTCHAPROT, "Ustawienia logowania - Ochrona 'Captcha'", 
							"  Mozesz wlaczyc ochrone 'Captcha' dla wchodzacych na serwer graczy,\nnieposiadajacych zarejestrowanego w systemie konta. Pozwoli to przede\n  wszystkim na ochrone przed botami, jednak w przypadku kiedy serwer\n            nie jest 'pod atakiem' nie ma potrzeby aktywowania tej opcji.\n\n\t\tCzy chcesz wlaczyc ochrone 'Captcha'?");
						case 2: ShowPlayerValueDialogBack(playerid, D_VALUE_SET_STARTING_CAPTCHA_TIME); //s_StartingCaptchaTimeID
						case 3: ShowPlayerValueDialogBack(playerid, D_VALUE_SET_REGISTER_MIN_TIME); //s_RegisterMinTimeID
						case 4: ShowPlayerValueDialogBack(playerid, D_VALUE_SET_REGISTER_CONFI); //s_ProvConfiRegisterID
						case 5: ShowPlayerValueDialogBack(playerid, D_VALUE_SET_LOGIN_TIME); //s_LoginTimeID
						case 6: ShowPlayerValueDialogBack(playerid, D_VALUE_SET_LOGIN_FAIL); //s_LoginFailID
						case 7: ShowPlayerValueDialogBack(playerid, D_VALUE_SET_ALOG_LOGIN_FAIL); //s_ALogLoginFailsID
						case 8: ShowPlayerValueDialogBack(playerid, D_VALUE_SET_RECONNECT_MAX_TIME); //s_ReconnectMaxTimeID
						default: ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);
					}				
				}
				case 2: {
					switch(listitem) {
						case 0: ShowPlayerValueDialogBack(playerid, D_VALUE_SET_NICK_CHANGE_TIME); //s_NickChangeTimeID
						case 1: ShowPlayerValueDialogBack(playerid, D_VALUE_SET_ACC_DELETING_TIME); //s_LoginDeletingDaysID
						case 2: ShowPlayerValueDialogBack(playerid, D_VALUE_SET_CONFI_TIME); //s_LoginConfiID	
						default: ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);
					}
				}
				case 3: {
					switch(listitem) {
						case 0: ShowPlayerYesNoDialog(playerid, D_YESNO_SET_REMOTECON, "Ustawienia administracyjne - Zdalna konsola SA-MP", 
							"Zdalna konsola SA-MP umozliwia wykonywanie polecen RCON bez wchodzenie na serwer.\n      Jednak stanowi potencjalny slaby punkt i cel atakow 'Neo-Kidow', dlatego jesli nie\n\t\t\t   ma potrzeby, powinna byc wylaczona.\n\n\t\t            Czy chcesz wlaczyc zdalna konsole SA-MP?");
						case 1: ShowPlayerYesNoDialog(playerid, D_YESNO_SET_BASE, "Ustawienia administracyjne - Uzywany typ bazy danych", 
							"System obsluguje dwa rodzaje baz danych - SQL (obslugiwana przez server SA-MP) oraz MySQL (zewn. lub dostarczana przez hosting).\n   W przypadku bazy MySQL wymagane jest wczesniejsze zdefiniowanie danych do polaczenia. W przypadku braku poprawnych danych,\n           baza zamieniana jest automatycznie na baze SQL. Zmiana bazy wymaga restartu Admin Systemu, a najlepiej calego serwera.\n\n\t\t\t\t\t\t     Czy chcesz wlaczyc baze MySQL?");
						case 2: ShowPlayerValueDialogBack(playerid, D_VALUE_SET_NACTIVE_ADMIN_DELETE); //s_NADelAdminRightsID
						case 3: ShowPlayerValueDialogBack(playerid, D_VALUE_SET_JADMIN_BLOCK_TIME); //s_BanTimeJAdminID
						case 4: ShowPlayerValueDialogBack(playerid, D_VALUE_SET_ADMIN_BLOCK_TIME); //s_BanTimeAdminID
						case 5: ShowPlayerYesNoDialog(playerid, D_YESNO_SET_AUTOCYCLIC, "Ustawienia administracyjne - Auto. operacje cykliczne", 
							"Operacje cykliczne polegaja na usunieciu zbednych danych z baz danych oraz wykonaniu resetu kont,\n   o ile zachodzi taka potrzeba. Istnieje mozliwosc zautomatyzowania tego procesu i daje ja to menu.\n\n\t\t            Czy chcesz wlaczyc automatyczne operacje cykliczne?");
						case 6: ShowPlayerValueDialogBack(playerid, D_VALUE_SET_RESET_HOUR); //s_ResetTimeID
						case 7: ShowPlayerYesNoDialog(playerid, D_YESNO_SET_AUTOACCRES, "Ustawienia administracyjne - Auto. reset kont", 
							"Okreslone w systemie wpisy z kont graczy moga byc resetowane. System daje mozliwosc zautomatyzowania\n\ttego procesu i wykonywanie resetu kont, okreslonego dnia w raz z operacjami cyklicznymi.\n\n\t\t\t            Czy chcesz wlaczyc automatyczny reset kont?");
						case 8: ShowPlayerValueDialogBack(playerid, D_VALUE_SET_AUTOACCRES_DAY); //s_ResetTimeID
						case 9: ShowPlayerYesNoDialog(playerid, D_YESNO_SET_RCON_ACCOUNT, "Ustawienia administracyjne - Konta RCON", 
							"System umozliwia okreslenie graczy (kont graczy), ktorzy moga zalogowac sie na konto\n   RCON. W przypadku wlaczenia tej opcji, system podczas logowania gracza na konto\n      RCON bedzie sprawdzal czy ma on przypisana do konta opcje logowania RCON.\n  W przypadku kiedy na konto RCON zaloguje sie gracz bez przywilejow, lub bez konta\n\t\t\t    zostanie on wyrzucony z serwera.\n\n\t\t         Czy chcesz aktywowac opcje Kont RCON?");
						case 10: ShowPlayerValueDialogBack(playerid, D_VALUE_SET_RCON_FAIL); 
						case 11: ShowPlayerValueDialogBack(playerid, D_VALUE_SET_MUTE_TIME); 
						case 12: ShowPlayerYesNoDialog(playerid, D_YESNO_AUTO_DAILY_RESET, "Ustawienia administracyjne - Auto. reset stat. dzien.", 
							"Automatyczny reset stat. dziennych kasuje statystyki dot. zabojstw, smierci itp. zdobytych\n       przez gracza od ost. resetu tych statystyk. Automatyczny reset bedzie sie odbywal\n\t\t\t    w raz z dniowymi operacjami cyklicznymi.\n\n\t\tCzy chcesz wlaczyc automatyczny reset statystyk dziennych?");
						
						
						default: ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);
					}				
				}
				case 4: {
					switch(listitem) {
						case 0: ShowPlayerYesNoDialog(playerid, D_YESNO_SET_CON_DIS, "Ustawienia powiadomien i chatu - Con-Dis Info", "Ustawienie to reguluje, czy podczas polaczenia lub rozlaczenia gracza\n    z serwerem, ma byc wysylane powiadomienie na chacie do graczy.\n\n\t   Czy chcesz aktywowac opcje powiadomien Con-Dis?");		
						case 1: ShowPlayerSettingsMenu(playerid, 99, -1);
						case 2: ShowPlayerYesNoDialog(playerid, D_YESNO_SET_CENSURE_MUTE, "Ustawienia powiadomien i chatu - 'Mute' za przeklinanie", 
							"Ustawienie okresla, czy przy wlaczonej cenzurze, gracz ma dostawac ostrzezenia za przeklinanie.\n        W przypadku przekroczenia limitu ostrzezen, zostaje on uciszony na chacie. Ostrzezenia\n\t\t\tusuwane sa po uplynieciu pewnego okresu czasu.\n\n\t\t       Czy chcesz aktywowac opcje uciszania za przeklinanie?");
						case 3: ShowPlayerValueDialogBack(playerid, D_BALUE_SET_MUTE_CENSURE_TIME);	
						case 4: ShowPlayerValueDialogBack(playerid, D_BALUE_SET_MUTE_MAX_WARNINGS);	
						case 5: ShowPlayerYesNoDialog(playerid, D_YESNO_SET_ANTYSPAM, "Ustawienia powiadomien i chatu - Anty spam", 
							"Ustawienie okresla, czy chat ma byc chroniony przed nadmiernym\n            wysylaniem wiadomosci przez tego samego gracza.\n\n\t      Czy chcesz aktywowac opcje anty spamu?");
						case 6: ShowPlayerValueDialogBack(playerid, D_BALUE_SET_ANTYSPAM_MIN_SEC);	
						case 7: ShowPlayerYesNoDialog(playerid, D_YESNO_SET_ANTYFLOOD, "Ustawienia powiadomien i chatu - Anty flood", 
							"Ustawienie okresla, czy chat ma byc chroniony przed wysylaniem\n            takich samych wiadomosci przez tego samego gracza.\n\n\t      Czy chcesz aktywowac opcje anty flooda?");		
						case 8: ShowPlayerValueDialogBack(playerid, D_BALUE_SET_ANTYFLOOD_MIN_SEC);	
						case 9: ShowPlayerYesNoDialog(playerid, D_YESNO_SET_PRIVMESSAGES, "Ustawienia powiadomien i chatu - Prywatne wiadomosci", 
							"   Ustawienie okresla, czy gracze maja miec mozliwosc wysylania prywatnych wiadomosci.\nZaleca sie wylaczenie tej opcji, jesli prywatne wiadomosci sa obslugiwane przez gamemod.\n\n\t\t  Czy chcesz aktywowac opcje prywatnych wiadomosci?");	
						case 10: ShowPlayerSettingsMenu(playerid, 98, -1);
						default: ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);
					}
				}
				case 5: {
					switch(listitem) {
						case 0: ShowPlayerValueDialogBack(playerid, D_VALUE_SET_MAX_PING);	
						case 1: ShowPlayerValueDialogBack(playerid, D_VALUE_SET_MAX_PING_WARNINGS);	
						case 2: ShowPlayerValueDialogBack(playerid, D_VALUE_SET_MIN_FPS);	
						case 3: ShowPlayerValueDialogBack(playerid, D_VALUE_SET_MIN_FPS_WARNINGS);	
						case 4: ShowPlayerValueDialogBack(playerid, D_VALUE_SET_MAX_PLOSS);
						case 5: ShowPlayerValueDialogBack(playerid, D_VALUE_SET_MAX_PLOSS_WARNINGS);	
						case 6: ShowPlayerValueDialogBack(playerid, D_VALUE_SET_PINGGPSPLOSS_FREQUENCY);
						case 7: ShowPlayerYesNoDialog(playerid, D_YESNO_SET_ADMINLIMITS, "Ograniczenia graczy - Ograniczenia administracji", 
							" Ze wzgledu na funkcje jaka pelnia administratorzy na serwerze istnieje mozliwosc\nwylaczenia dla nich sprwadzania 'Ograniczen graczy'. W tym menu mozesz okreslic\n\t  czy chcesz zeby administracja podlegala ograniczeniom czy nie.\n\n\t\tCzy chcesz wlaczyc ograniczenia dla administracji?");
						case 8: ShowPlayerYesNoDialog(playerid, D_YESNO_SET_VIPLIMITS, "Ograniczenia graczy - Ograniczenia VIP'ow", 
							"Gracze z aktywnym statusem VIP na serwerze, ze wzgledu na uprzywilejowana\n       pozycje, moga zostac wylaczeni spod sprawdzania 'Ograniczen graczy'.\n\n\t\tCzy chcesz wlaczyc ograniczenia dla VIP'ow?");
						case 9:	ShowPlayerValueDialogBack(playerid, D_VALUE_SET_CRITICAL_PLOSS);	
						case 10:ShowPlayerValueDialogBack(playerid, D_VALUE_SET_CRITICAL_PING);						
						default: ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);
					}
				}
				case 6: { 
					switch(listitem) {
						case 0: ShowPlayerValueDialogBack(playerid, D_VALUE_SET_VIP_REG_TIME);
						case 1: ShowPlayerValueDialogBack(playerid, D_VALUE_SET_VIP_REG_POINTS);
						case 2: ShowPlayerValueDialogBack(playerid, D_VALUE_SET_VIP_3);
						case 3: ShowPlayerValueDialogBack(playerid, D_VALUE_SET_VIP_7);
						case 4: ShowPlayerValueDialogBack(playerid, D_VALUE_SET_VIP_30);
						case 5: ShowPlayerYesNoDialog(playerid, D_YESNO_SET_VIPTIMEBAN, "Ograniczenia graczy - Omijanie banow czasowych dla VIP", 
							"Gracze ze stantusem VIP moga miec mozliwosc omijania banow czasowych\n nalozonych na ich host, ale nie konto, podobnie jak administracja serwera.\n\n\tCzy chcesz wlaczyc omijanie banow czasowych dla VIP'ow?");
					}			
				}		
				case 7: {
					switch(listitem) {
						case 0: ShowPlayerSettingsMenu(playerid, 92, -1);
						case 1: ShowPlayerSettingsMenu(playerid, 89, -1);
						case 2: ShowPlayerSettingsMenu(playerid, 93, -1);
						case 3: ShowPlayerSettingsMenu(playerid, 94, -1);
						case 4: ShowPlayerSettingsMenu(playerid, 95, -1);
						case 5: ShowPlayerSettingsMenu(playerid, 96, -1);
						case 6: ShowPlayerYesNoDialog(playerid, D_YESNO_AC_JETPACK, "Anty Cheat - Anty Jetpack", "Czy chcesz wlaczyc Anty Jet Pack (brak mozliwosci uzywania jetpacka)?");
						case 7: ShowPlayerSettingsMenu(playerid, 90, -1);
						case 8: ShowPlayerSettingsMenu(playerid, 88, -1);
						default: ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);  
					}		
				}				
				case 8: {
					switch(listitem) {
						case 0: {
							if(CallRemoteFunction("AAGStatus", "") == 0) {
								ShowPlayerInfoDialog(playerid, BACK_SETTING_SCRIPT_MENU, "Zewnetrzne skrypty - AxL Anty Glitch (min. ver. 1.2.1)", 
									"Brak odpowiedzi ze strony skryptu. Mozliwe, ze skrypt jest wylaczony\n\tlub jego wersja nie zawiera mozliwosci zewn. obslugi.");
							} else {
								CallRemoteFunction("AAGStatusChange", "");
								ShowPlayerSettingsMenu(playerid, 4, -1);
							}
						}
						case 1: {
							if(CallRemoteFunction("AMacroStatus", "") == 0) {
								ShowPlayerInfoDialog(playerid, BACK_SETTING_SCRIPT_MENU, "Zewnetrzne skrypty - AxL Anty Macro (min. ver. 1.0.4)", 
									"Brak odpowiedzi ze strony skryptu. Mozliwe, ze skrypt jest wylaczony\n\tlub jego wersja nie zawiera mozliwosci zewn. obslugi.");
							} else {
								CallRemoteFunction("AMacroStatusChange", "");
								ShowPlayerSettingsMenu(playerid, 4, -1);
							}
						}
						case 2: {
							if(CallRemoteFunction("ACrasherStatus", "") == 0) {
								ShowPlayerInfoDialog(playerid, BACK_SETTING_SCRIPT_MENU, "Zewnetrzne skrypty - AxL Anty Crasher (min. ver. 1.0.1)", 
									"Brak odpowiedzi ze strony skryptu. Mozliwe, ze skrypt jest wylaczony\n\tlub jego wersja nie zawiera mozliwosci zewn. obslugi.");
							} else {
								CallRemoteFunction("ACrasherStatusChange", "");
								ShowPlayerSettingsMenu(playerid, 4, -1);
							}						
						}
						default: ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);
					}
				}	
				case 88: {
					switch(listitem) {
						case 0: ShowPlayerYesNoDialog(playerid, D_YESNO_AC_GODMODE, "Anty Cheat - Godmode", "Czy chcesz wlaczyc system pomiaru HP (Godmode)?");
						case 1: ShowPlayerValueDialogBack(playerid, D_VALUE_SET_AC_GODMODE_WARNINGS);
						case 2: ShowPlayerValueDialogBack(playerid, D_VALUE_SET_AC_GODMODE_TICKS);
						default: ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);						
					}					
				}
				case 89: {
					switch(listitem) {
						case 0: ShowPlayerYesNoDialog(playerid, D_YESNO_AC_REJOIN, "Anty Cheat - Rejoin spam bot", "Czy chcesz wlaczyc system sprawdzania Rejoin spambot'a?");
						case 1: ShowPlayerValueDialogBack(playerid, D_VALUE_SET_AC_REJOIN);
						default: ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);
					}
				}
				case 90: {
					switch(listitem) {
						case 0: ShowPlayerYesNoDialog(playerid, D_YESNO_AC_WEAPONS, "Anty Cheat - Niedostepne bronie", "W przypadku wspolpracy systemu z gamemodem dot. nieuzywanych broni\n        zaleca sie wlaczenie tej opcji w celu wyeliminowania mozliwosci\n     uzywania broni, ktore nie sa dostepne w obrebie calego gamemodu.\n\n\t      Czy chcesz wlaczyc system niedostepnych broni?");
						case 1: {
							new Y, M, D, Hour, Minute;
							new counter;
							for(new i, wName[32]; i < sizeof(ac_Weapons); i ++) {
								if(ac_Weapons[i] == NOT_ALLOWED_WEAPON) {
									if(!(19 <= i <= 21)) {										
										GetWeaponName(i, wName, sizeof(wName));
										format(string, sizeof(string),"%s\n%d) %s (ID: %d)", string, ++ counter, wName, i);
									}		
								}
							}
							if(counter == 0) strins(string, "\nBrak permanentnie zablokowanych broni.", 0);							
							dtimestamp(ac_WeaponTimeStamp, Y, M, D, Hour, Minute);
							format(string, sizeof(string), "Lista niedostepnych broni: %s  [ %d:%02d ]\n%s", strData(Y, M, D, " / ", false, false, true, false), Hour, Minute, string);
							ShowPlayerInfoDialog(playerid, BACK_AC_WEAPONS_INFO, "Anty Cheat - Niedostepne bronie", string);
						}
						case 2: {
							if(LoadWeaponACSettings(TEMP_WEAPONS_FILE) == 0) ShowPlayerInfoDialog(playerid, BACK_AC_WEAPONS_INFO, "Anty Cheat - Niedostepne bronie", "Niewykryto koniecznych elementow w kodzie aktualnie wlaczonego gamemoda.");
							else ShowPlayerInfoDialog(playerid, BACK_AC_WEAPONS_INFO, "Anty Cheat - Niedostepne bronie", "Lista zabronionych przez gamemod broni zostala przeladowana.");
						}
						default: ShowPlayerSettingsMenu(playerid, 90, -1);
					}
				}
				
				case 91: {		// Menu ustawien do Anty Cheata - SA-MP pieniadze (podejmowana akcja)
					if(0 <= listitem <= 1) setSettingIntValueByIndex(s_ACAntyMoneyHackActionID, listitem);
					ShowPlayerSettingsMenu(playerid, 96, -1);
				}
				case 92: {
					switch(listitem) {
						case 0: ShowPlayerYesNoDialog(playerid, D_YESNO_AC_SAMEIP, "Anty Cheat - Gra z tego samego IP", "Czy chcesz wlaczyc system sprawdzania gry z tego samego IP?");
						case 1: ShowPlayerValueDialogBack(playerid, D_VALUE_SET_AC_SAMEIP);
						default: ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);
					}
				}
				case 93: {
					switch(listitem) {
						case 0: ShowPlayerYesNoDialog(playerid, D_YESNO_AC_CHATSPAMBOT, "Anty Cheat - Chat spam bot", "Czy chcesz wlaczyc system anty chat spam bot'a?");
						case 1: ShowPlayerValueDialogBack(playerid, D_VALUE_SET_AC_CHATSPAMBOT);
						default: ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);
					}
				}
				case 94: {
					switch(listitem) {
						case 0: ShowPlayerYesNoDialog(playerid, D_YESNO_AC_CMDSPAMBOT, "Anty Cheat - CMD spam bot", "Czy chcesz wlaczyc system anty CMD spam bot'a (spamowanie komenda)?");
						case 1: ShowPlayerValueDialogBack(playerid, D_VALUE_SET_AC_CMDSPAMBOT);
						default: ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);
					}
				}					
				case 95: {
					switch(listitem) {
						case 0: ShowPlayerYesNoDialog(playerid, D_YESNO_AC_FAKEKILLSPAMBOT, "Anty Cheat - Fake-Kill spam bot", "Czy chcesz wlaczyc system anty Fake-Kill spam bot'a?");
						case 1: ShowPlayerValueDialogBack(playerid, D_VALUE_SET_AC_FAKEKILLSPAMBOT);
						default: ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);
					}
				}					
				case 96: {
					switch(listitem) {
						case 0: ShowPlayerYesNoDialog(playerid, D_YESNO_AC_SAMPMONEY, "Anty Cheat - SA-MP pieniadze", "W przypadku kiedy gamemod nie korzysta z SA-MP'owego obiegu pieniedzy,\ni calkowicie niemozliwe jest ich zdobycie zaleca sie wlaczenie tego systemu.\n\n\t          Czy chcesz wlaczyc system anty SA-MP pieniedzy?");
						case 1: ShowPlayerSettingsMenu(playerid, 91, -1);
						default: ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);
					}
				}								
				case 97: {
					setSettingIntValueByIndex(s_RegisterObligatoryID, listitem);
					ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);
				}
				case 98: {
					setSettingIntValueByIndex(s_PrivMessagesSpecID, listitem);
					ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);	
				}
				case 99: {
					CallRemoteFunction("OnChatCensureSettingUpdate", "d", listitem);
					setSettingIntValueByIndex(s_CensureStatusID, listitem);
					ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);					
				}
				default: ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);
			}
		}
		return _TRUE;
	}
	return _FALSE;
}
//===============================================================
//---------------------------------------------------------------
//===============================================================
/*
	9) Operacje na kontach VIP
*/
//===============================================================
//---------------------------------------------------------------
//===============================================================
HAVipMenu(playerid, listitem = -1) {
	if(IsAdmin(playerid) >= ALVL_GAME_MASTER) {
		switch(listitem) {
			case 0: {
				SetHelpVarValue(playerid, 99, 0);
				HAVipPlayersList(playerid);			
			}
			case 1: HAPanelVipPlayersSearch(playerid);
			case 2, 3: {
				SetHelpVarValue(playerid, 1, listitem-2);
				HAPanelVipPoints(playerid);			
			}
			case 4: HAPanelVipTime(playerid);
			default: ShowPlayerDialogEx(playerid, DIALOG_HA_VIPMENU, DIALOG_STYLE_LIST, "Operacje na kontach VIP", "1) Lista graczy z kontem VIP\n2) Wyszukaj gracza\n3) Dodaj / odbierz punkty premium gracza wszystkim graczom (gracza)\n4) Dodaj / odbierz punkty premium gracza wszystkim graczom (bonusowe)\n5) Przedluz / skroc czas trwania konta VIP wszystkim graczom", "Dalej", "Wroc");
		}
		return _TRUE;
	}
	return _FALSE;
}
//---------------------------------------------------------------
HAPanelVipPlayersSearch(playerid, data[] = "") {
	if(IsAdmin(playerid) >= ALVL_HEAD_ADMIN) {
		new string[300];
		if(!isnull(data)) {			
			new type, date_from, date_to, bool:search_front, bool:search_end, bool:sorttype_desc, errorid;
			if(SearchDataSplit(data, type, date_from, date_to, search_front, search_end, sorttype_desc, errorid) == _TRUE) {
				switch(type) {
					case DATA_TYPE_NON: 	strins(string, "Niepoprawny typ danych do wyszukania.", 0);
					case DATA_TYPE_NICK, DATA_TYPE_ONLINE, DATA_TYPE_HOST, DATA_TYPE_USERID, DATA_TYPE_ADMINID, DATA_TYPE_ADMIN_NICK, DATA_TYPE_IP: 	strins(string, "Ten typ wyszukiwania nie jest obslugiwany w tym menu.", 0);
					default: {
						if(type == DATA_TYPE_VIPPOINTS or type == DATA_TYPE_VIPBONUS) {
							SetHelpVarValue(playerid, 22, timestamp());
							SetHelpVarValue(playerid, 23, timestamp() + SECONDS_YEAR * 10);								
						} else {
							SetHelpVarValue(playerid, 22, date_from < timestamp() ? timestamp() : date_from);
							SetHelpVarValue(playerid, 23, date_to <= timestamp() ? timestamp() + SECONDS_YEAR * 10 : date_to);						
						}
						SetHelpVarValue(playerid, 21, type);
						SetHelpStringValue(playerid, 20, data);
						SetHelpVarValue(playerid, 25, _:search_end);
						SetHelpVarValue(playerid, 24, _:search_front);					
						SetHelpVarValue(playerid, 99, 1);								
						SetHelpVarValue(playerid, 26, _:sorttype_desc);
						HAVipPlayersList(playerid);
						return _TRUE;
					}
				}
			} else {
				switch(errorid) {
					case DATA_ERROR_HELP: {
						ShowPlayerSearchInfo(playerid, SI_VIP_SEARCH);
						return _TRUE;
					}
					case DATA_ERROR_INVALID_LENGTH:		strins(string, "\t           Niepoprawne dane do wyszukania.", 0);	// OK
					case DATA_ERROR_INVALID_TYPE:		strins(string, "\tNiepoprawny typ danych do wyszukania.", 0);
					case DATA_ERROR_INVALID_SPECIAL:	strins(string, "          Niepoprawne znaki w danych do wyszukania.", 0);
					case DATA_ERROR_DATE_FROM:			strins(string, "    Niepoprawna najwczesniejsza data danych do wyszukania.", 0); // OK
					case DATA_ERROR_DATE_TO:			strins(string, "     Niepoprawna najpozniejsza data danych do wyszukania.", 0); // OK
					case DATA_ERROR_NO_TYPE:			strins(string, "\t   Niezdefiniowany typ danych do wyszukania.", 0);	// OK
					case DATA_ERROR_NO_DATA:			strins(string, "    Brak danych do wyszukania.", 0);
					case DATA_ERROR_NO_MATCH_DATA_TYPE:	strins(string, "          Niepoprawne typ z formatem danych do wyszukania.", 0);	//OK
					case DATA_ERROR_INVALID_SORT_TYPE:	strins(string, "\t      Niepoprawny rodzaj sortowania.", 0);
				}
			}
		}		
		format(string, sizeof(string), "Podaj interesujacy Cie typ danych pod katem, ktorych ma zostac\n   przeszukana baza danych graczy z punktami lub kontem VIP.\n          Info: Jesli nie wiesz jak poslugiwac sie wyszukiwarka,\n\t\t    wpisz polecenie '<INFO>'.\n\n"TEXT_DIALOG_ALERT"%s", string);
		ShowPlayerDialogEx(playerid, DIALOG_HA_VIPACCOUNTS_SEARCH, DIALOG_STYLE_INPUT, "Operacje na kontach VIP - Wyszukiwarka", string, "Wyszukaj", "Wroc");
		
		return _TRUE;
	}	
	return _FALSE;
}
//---------------------------------------------------------------
VipPlayersMakeQuery(playerid, page) {
	new string[256];
	switch(GetHelpVarValue(playerid, 21)) {
		case DATA_TYPE_VIP: {
			strins(string, GetHelpStringValue(playerid, 20), 0);
			ConvertNick(string);
			format(string, sizeof(string), "SELECT `"TK_UID"`, `"TK_NICK"`, `"TK_PREMIUM_DATE"` FROM `"T_KONTA"` WHERE `"TK_NICK"` LIKE '%s%s%s' AND `"TK_PREMIUM_DATE"` >= '%d' AND `"TK_PREMIUM_DATE"` <= '%d' ORDER BY `"TK_PREMIUM_DATE"` %s LIMIT %d, 11", 
				GetHelpVarValue(playerid, 24) == 1 ? ("%") : (""), string, GetHelpVarValue(playerid, 25) == 1 ? ("%") : (""), 
				GetHelpVarValue(playerid, 22), GetHelpVarValue(playerid, 23),						
				GetHelpVarValue(playerid, 26) == 0 ? ("ASC") : ("DESC"), 
				page * 10);
		}
		case DATA_TYPE_VIPPOINTS: {
			format(string, sizeof(string), "SELECT `"TK_UID"`, `"TK_NICK"`, `"TK_PREMIUM_PLAYER_POINT"` FROM `"T_KONTA"` WHERE `"TK_UID"` = '%s' AND `"TK_PREMIUM_PLAYER_POINT"` >= '0' ORDER BY `"TK_PREMIUM_PLAYER_POINT"` %s LIMIT %d, 11", 
				GetHelpStringValue(playerid, 20),	
				GetHelpVarValue(playerid, 26) == 0 ? ("ASC") : ("DESC"),
				page * 10);					
		}
		case DATA_TYPE_VIPBONUS: {
			format(string, sizeof(string), "SELECT `"TK_UID"`, `"TK_NICK"`, `"TK_PREMIUM_BONUS_POINT"` FROM `"T_KONTA"` WHERE `"TK_UID"` = '%s' AND `"TK_PREMIUM_BONUS_POINT"` >= '0' ORDER BY `"TK_PREMIUM_BONUS_POINT"` %s LIMIT %d, 11", 
				GetHelpStringValue(playerid, 20),	
				GetHelpVarValue(playerid, 26) == 0 ? ("ASC") : ("DESC"),
				page * 10);					
		}	
	}
	return string;
}
//---------------------------------------------------------------
HAVipPlayersList(playerid, page = 0) {
	if(IsAdmin(playerid) >= ALVL_HEAD_ADMIN) {
		new string[800];
		new DBResult: result, Result:sql_result;
		new rows;

		if(page < 0) page = 0;
		
		if(GetHelpVarValue(playerid, 99) == 0) {		
			format(string, sizeof(string), "SELECT `"TK_NICK"`, `"TK_PREMIUM_DATE"` FROM `"T_KONTA"` WHERE `"TK_PREMIUM_DATE"`>'%d' ORDER BY `"TK_PREMIUM_DATE"` DESC LIMIT %d, 11", timestamp(), page * 10);
		} else {
			strins(string, VipPlayersMakeQuery(playerid, page), 0);
		}
		
		result = sendQueryResult(string, sql_result);
		//_______________________	
		strdel(string, 0, 256);
		rows = numRows(result, sql_result);
		if(numRows(result, sql_result) > 0) {
			new bool:isNextPage = rows == 11 ? true : false;
			
			new read[64], index = 0;
			for(new limit = rows == 11 ? 10 : rows, year, month, day, hour, minute; index < limit; index ++) {
				strdel(read, 0, 32);				
				strins(read, getFieldAssoc_32(TK_NICK, result, sql_result), 0);				
				DeconvertNick(read);
				if(GetHelpVarValue(playerid, 99) == 0 or GetHelpVarValue(playerid, 21) == DATA_TYPE_VIP) {
					dtimestamp(strval(getFieldAssoc_16(TK_PREMIUM_DATE, result, sql_result)), year, month, day, hour, minute);
					format(string, sizeof(string), "%s\n%d) %s\t\t"TEXT_DIALOG_HEAD"[ "TEXT_DIALOG_NORMAL"%s"TEXT_DIALOG_HEAD" ]", string, page * 10 + index + 1, CutName(read), strData(year, month, day, " / ", false, false, true, true), hour, minute);				
				} else {
					format(string, sizeof(string), "%s\n%d) %s\t\t"TEXT_DIALOG_HEAD"[ "TEXT_DIALOG_NORMAL"%d pkt."TEXT_DIALOG_HEAD" ]", string, page * 10 + index + 1, CutName(read), GetHelpVarValue(playerid, 21) == DATA_TYPE_VIPPOINTS ? strval(getFieldAssoc_16(TK_PREMIUM_PLAYER_POINT, result, sql_result)) : strval(getFieldAssoc_16(TK_PREMIUM_BONUS_POINT, result, sql_result)));	
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
			ShowPlayerDialogEx(playerid, DIALOG_HA_VIPACCOUNTS_LIST, DIALOG_STYLE_LIST, "Operacje na kontach VIP - Lista", string, "Sprawdz", "Wroc");
			return _TRUE;
		} else {
			if(GetHelpVarValue(playerid, 99) == 0) {
				ShowPlayerInfoDialog(playerid, BACK_VIPMENU_MENU, "Operacje na kontach VIP - Lista", "Brak danych do sprawdzenia w bazie. Sprobuj pozniej.");
			} else {
				ShowPlayerInfoDialog(playerid, BACK_VIPMENU_SEARCH, "Operacje na kontach VIP - Lista", "Nieznaleziono rezultatow dla podanych danych.");	
			}
		}
		//_______________________	
	}
	return _FALSE;
}
//---------------------------------------------------------------
HAVIPListResponse(playerid, listitem) {
	if(IsAdmin(playerid) >= ALVL_HEAD_ADMIN) {
		new DBResult: result, Result:sql_result;
		new rows;
		new string[256];				
		
		if(GetHelpVarValue(playerid, 99) == 0) {		
			format(string, sizeof(string), "SELECT `"TK_UID"`,`"TK_NICK"` FROM `"T_KONTA"` WHERE `"TK_PREMIUM_DATE"`>'%d' ORDER BY `"TK_PREMIUM_DATE"` DESC LIMIT %d, 11", timestamp(), GetPlayerPage(playerid) * 10);
		} else {
			strins(string, VipPlayersMakeQuery(playerid, GetPlayerPage(playerid)), 0);
		}
		result = sendQueryResult(string, sql_result);
		rows = numRows(result, sql_result);
		if(rows > 0) {
			new bool:pvpage = GetPlayerPage(playerid) > 0 ? true : false;
			new bool:nxpage = rows == 11 ? true : false;
		
			if(listitem == 0 and (pvpage == true or nxpage == true)) {
				freeResult(result, sql_result);
				if(pvpage == true) HAVipPlayersList(playerid, GetPlayerPage(playerid) - 1);
				else {
					HAVipPlayersList(playerid, GetPlayerPage(playerid) + 1);
				}
			} else if(listitem == 1 and (pvpage == true and nxpage == true)) {
				freeResult(result, sql_result);
				HAVipPlayersList(playerid, GetPlayerPage(playerid) + 1);
			} else {
				new uniqueid;
				if(pvpage == true) listitem --;
				if(nxpage == true) listitem --;			

				new index, dest[64];
				new nick[MAX_PLAYER_NAME];
				for(index = 0; index < rows; index ++) {
					if(index == listitem) {
						if(UseMySQL() == 1) {
							sql_get_field(sql_result, 0, dest, sizeof(dest));
							sql_get_field(sql_result, 1, nick, sizeof(nick));
						} else {
							db_get_field(result, 0, dest, sizeof(dest));
							db_get_field(result, 1, nick, sizeof(nick));
						}
						uniqueid = strval(dest);
						break;
					}		
					nextRow(result, sql_result);		
				}				

				freeResult(result, sql_result);

				SetHelpVarValue(playerid, 98, 1);
				SetHelpVarValue(playerid, 0, uniqueid);
				DeconvertNick(nick);
				SetHelpStringValue(playerid, 0, nick);				
				HAPanelPlayerAccountMenu(playerid);
				return _TRUE;
			}		
		} else HARegisterBaseList(playerid, 0);
	} 
	return _FALSE;
}
//---------------------------------------------------------------
HAPanelVipPoints(playerid, s_points[] = "") {
	if(IsAdmin(playerid) == ALVL_GAME_MASTER) {
		new string[300];
		new pointsType = GetHelpVarValue(playerid, 1);
		new length;
		if(!isnull(s_points) and (length = strlen(s_points)) <= 5) {	
			if(s_points[0] == '-' or s_points[0] == '+' and length > 1) { 
				new bool:error;				
				for(new i = 1; i < length; i ++) {
					if(!('0' <= s_points[i] <= '9')) {
						error = true;
						break;
					}
				}	
				if(error == false) {
					new value;
					if(9999 >= (value = strval(s_points[1])) > 0) {
						SetHelpVarValue(playerid, 2, value);
						SetHelpVarValue(playerid, 3, (s_points[0] == '+' ? 1 : -1));
						HAPanelVIPMenuPremiumConfirm(playerid);			
						return _TRUE;
					} else strins(string, C_ADMIN"\t\t\t\t         Niepoprawna wartosc.", 0);					
				} else strins(string, C_ADMIN"\t\t\t\t         Niepoprawna wartosc.", 0);		
			} else strins(string, "\t\t\t\tMusisz uzyc prefiksow '-' lub '+'.", 0);
		}
		format(string, sizeof(string), 
				"W tym menu mozesz dodac lub odjac punkty premium o charakterze "C_WHITE"%s"TEXT_DIALOG_HEAD" wszystkim graczom.\
				\nZeby dodac lub odjac punkty od aktualnej puli nalezy uzyc prefiksu '+' lub '-', a nastepnie podac\n\
				\t\t\t\t   wartosc z przedzialu 0 - 9999.\n\n\
				"C_ADMIN"%s", 
			pointsType == 0 ? ("wlasnym") : ("bonusowym"), 		
			string
		);
		ShowPlayerDialogEx(playerid, DIALOG_HA_VIPMENU_POINTS, DIALOG_STYLE_INPUT, pointsType == 0 ? ("Operacje na kontach VIP - Punkty premium (gracza)") : ("Operacje na kontach VIP - Punkty premium (bonusowe)"), string, "Dalej", "Wroc");			
		return _TRUE;
	}
	return _FALSE;
}
//---------------------------------------------------------------
HAPanelVIPMenuPremiumConfirm(playerid, bool:confirm = false) {
	if(IsAdmin(playerid) == ALVL_GAME_MASTER) {
		new string[512];
		new pointsType = GetHelpVarValue(playerid, 1);
		new pointsValue = GetHelpVarValue(playerid, 2);
		new pointsSymbol = GetHelpVarValue(playerid, 3);

		if(confirm == true) {
			switch(pointsSymbol) {
				case 1: {
					format(string, sizeof(string), " (Punkty Premium) Administrator '%s' dodal wszystkim graczom %d punktow premium o charakterze %s.", getPlayerName(playerid), pointsValue, pointsType == 0 ? ("gracza") : ("bonusowym"));
					SendClientMessageToAll(COLOR_GOLD, string);
					if(pointsType == 0) {
						format(string, sizeof(string), "UPDATE `"T_KONTA"` SET `"TK_PREMIUM_PLAYER_POINT"`="TK_PREMIUM_PLAYER_POINT"+%d WHERE `"TK_PREMIUM_PLAYER_POINT"`>='0'", pointsValue);
						sendQueryWithout(string);
					} else {
						format(string, sizeof(string), "UPDATE `"T_KONTA"` SET `"TK_PREMIUM_BONUS_POINT"`="TK_PREMIUM_BONUS_POINT"+%d WHERE `"TK_PREMIUM_BONUS_POINT"`>='0'", pointsValue);
						sendQueryWithout(string);					
					}			
					format(string, sizeof(string), " Administrator %s (UID: %d) dodal(a) wszystkim graczom %d punktow premium o charakterze %s.", getPlayerName(playerid), getPlayerUserID(playerid), pointsValue, pointsType == 0 ? ("gracza") : ("bonusowym"));
				}
				case -1: {
					format(string, sizeof(string), " (Punkty Premium) Administrator '%s' odjal wszystkim graczom %d punktow premium o charakterze %s.", getPlayerName(playerid), pointsValue, pointsType == 0 ? ("gracza") : ("bonusowym"));
					SendClientMessageToAll(COLOR_GOLD, string);
					
					if(pointsType == 0) {
						format(string, sizeof(string), "UPDATE `"T_KONTA"` SET `"TK_PREMIUM_PLAYER_POINT"`="TK_PREMIUM_PLAYER_POINT"-%d WHERE `"TK_PREMIUM_PLAYER_POINT"` > '0'", pointsValue);
						sendQueryWithout(string);
						sendQueryWithout("UPDATE `"T_KONTA"` SET `"TK_PREMIUM_PLAYER_POINT"`='0' WHERE `"TK_PREMIUM_PLAYER_POINT"` < '0'");	
					} else {
						format(string, sizeof(string), "UPDATE `"T_KONTA"` SET `"TK_PREMIUM_BONUS_POINT"`="TK_PREMIUM_BONUS_POINT"-%d WHERE `"TK_PREMIUM_BONUS_POINT"` > '0'", pointsValue);
						sendQueryWithout(string);
						sendQueryWithout("UPDATE `"T_KONTA"` SET `"TK_PREMIUM_BONUS_POINT"`='0' WHERE `"TK_PREMIUM_BONUS_POINT"` < '0'");						
					}
					format(string, sizeof(string), " Administrator %s (UID: %d) odjal(ela) wszystkim graczom %d punktow premium o charakterze %s.", getPlayerName(playerid), getPlayerUserID(playerid), pointsValue, pointsType == 0 ? ("gracza") : ("bonusowym"));
				}
				default: return 0;
			}		
			AddToVIPLog(string);	
		
			if(pointsType == 0) {
				forplayers(i) {
					if(getPlayerLoginStatus(i) != LOGIN_STATUS_NOTREGISTERED and getPlayerLoginStatus(i) != LOGIN_STATUS_NON) {
						if(pointsSymbol == 1) AddPlayerSelfPoints(i, pointsValue);
						else {
							TakePlayerSelfPoints(i, pointsValue);
							if(GetPlayerVIPSelfPoints(i) < 0) SetPlayerVIPSelfPoints(i, 0);
						}
					}
				}
			} else {		
				forplayers(i) {
					if(getPlayerLoginStatus(i) != LOGIN_STATUS_NOTREGISTERED and getPlayerLoginStatus(i) != LOGIN_STATUS_NON) {
						if(pointsSymbol == 1) AddPlayerBonusPoints(i, pointsValue);
						else {
							TakePlayerBonusPoints(i, pointsValue);
							if(GetPlayerVIPBonusPoints(i) < 0) SetPlayerBonusPoints(i, 0);
						}
					}
				}
			}	
			
			format(string, sizeof(string), "\
					%s "C_WHITE"%d "TEXT_DIALOG_HEAD"punktow premium o charakterze "C_WHITE"%s"TEXT_DIALOG_HEAD" %s kazdego konta.\
				",
				pointsSymbol == -1 ? ("Odebrales(as)") : ("Dodales(as)"), pointsValue, pointsType == 0 ? ("gracza") : ("bonusowym"), pointsSymbol == -1 ? ("od") : ("do")
			);
			ShowPlayerInfoDialog(playerid, BACK_VIPMENU_MENU, pointsType == 0 ? ("Operacje na kontach VIP - Punkty premium (gracza)") : ("Operacje na kontach VIP - Punkty premium (bonusowe)"), string);					
		} else {
			format(string, sizeof(string),"\
					Czy na pewno chcesz "C_WHITE"%s %d %s "TEXT_DIALOG_HEAD"punktow premium wszystkim graczom??\
				",
				pointsSymbol == 1 ? ("dodac") : ("odjac"), 
				pointsValue, 
				pointsType == 0 ? ("wlasnych") : ("bonusowych")
			);
			ShowPlayerYesNoDialog(playerid, D_YESNO_HA_VIPMENU_POINTS, pointsType == 0 ? ("Operacje na kontach VIP - Punkty premium (gracza)") : ("Operacje na kontach VIP - Punkty premium (bonusowe)"), string);				
		}
		return _TRUE;

	}
	return _FALSE;
}
//---------------------------------------------------------------
HAPanelVipTime(playerid, s_time[] = "") {
	if(IsAdmin(playerid) == ALVL_GAME_MASTER) {
		new string[300];
		new length;
		if(!isnull(s_time) and (length = strlen(s_time)) <= 5) {	
			if(s_time[0] == '-' or s_time[0] == '+' and length > 1) { 
				new bool:error;				
				for(new i = 1; i < length; i ++) {
					if(!('0' <= s_time[i] <= '9')) {
						error = true;
						break;
					}
				}	
				if(error == false) {
					new value;
					if(365 >= (value = strval(s_time[1])) > 0) {
						SetHelpVarValue(playerid, 1, value);
						SetHelpVarValue(playerid, 2, (s_time[0] == '+' ? 1 : -1));
						HAPanelVIPMenuTimeConfirm(playerid);			
						return _TRUE;
					} else strins(string, C_ADMIN"\t\t\t\t  Niepoprawna wartosc.", 0);					
				} else strins(string, C_ADMIN"\t\t\t\t  Niepoprawna wartosc.", 0);		
			} else strins(string, "\t\t\t      Musisz uzyc prefiksow '-' lub '+'.", 0);
		}
		format(string, sizeof(string), 
				" W tym menu mozesz przedluzyc lub skrocic czas trwania konta VIP wszystkim graczom.\
				\nZeby dodac lub odjac czas trwania przywilejow (w dniach) nalezy uzyc prefiksu '+' lub '-',\n\
				\t\t       a nastepnie podac wartosc z przedzialu 0 - 365.\n\n\
				"C_ADMIN"%s", 	
			string
		);
		ShowPlayerDialogEx(playerid, DIALOG_HA_VIPMENU_TIME, DIALOG_STYLE_INPUT, "Operacje na kontach VIP - Czas trwania konta VIP", string, "Dalej", "Wroc");			
		return _TRUE;
	}
	return _FALSE;
}
//---------------------------------------------------------------
HAPanelVIPMenuTimeConfirm(playerid, bool:confirm = false) {
	if(IsAdmin(playerid) == ALVL_GAME_MASTER) {
		new string[512];
		new pointsValue = GetHelpVarValue(playerid, 1);
		new pointsSymbol = GetHelpVarValue(playerid, 2);

		if(confirm == true) {
			new secondsTime = ToSeconds(pointsValue, _DAY);
			switch(pointsSymbol) {
				case 1: {
					format(string, sizeof(string), " (Konto VIP) Administrator '%s' dodal wszystkim graczom %d dni konta premium.", getPlayerName(playerid), pointsValue);
					SendClientMessageToAll(COLOR_GOLD, string);
					format(string, sizeof(string), "UPDATE `"T_KONTA"` SET `"TK_PREMIUM_DATE"`="TK_PREMIUM_DATE"+%d WHERE `"TK_PREMIUM_DATE"`>'%d'", secondsTime, timestamp());
					sendQueryWithout(string);						
					format(string, sizeof(string), "UPDATE `"T_KONTA"` SET `"TK_PREMIUM_DATE"`='%d' WHERE `"TK_PREMIUM_DATE"`<='%d'", timestamp() + secondsTime, timestamp());
					sendQueryWithout(string);	
					format(string, sizeof(string), " Administrator %s (UID: %d) dodal(a) %d dni konta premium.", getPlayerName(playerid), getPlayerUserID(playerid), pointsValue);
				}
				case -1: {
					format(string, sizeof(string), " (Konto VIP) Administrator '%s' odjal(ela) wszystkim graczom %d dni konta premium.", getPlayerName(playerid), pointsValue);
					SendClientMessageToAll(COLOR_GOLD, string);
					format(string, sizeof(string), "UPDATE `"T_KONTA"` SET `"TK_PREMIUM_DATE"`="TK_PREMIUM_DATE"-%d", secondsTime);
					sendQueryWithout(string);						
					format(string, sizeof(string), "UPDATE `"T_KONTA"` SET `"TK_PREMIUM_DATE"`='0' WHERE `"TK_PREMIUM_DATE"`<'%d'", timestamp());
					sendQueryWithout(string);	
					format(string, sizeof(string), " Administrator %s (UID: %d) odjal(ela) %d dni konta premium.", getPlayerName(playerid), getPlayerUserID(playerid), pointsValue);				
				}
				default: return 0;
			}		
			AddToVIPLog(string);	
		
			if(pointsSymbol == -1) {
				forplayers(i) {
					if(getPlayerLoginStatus(i) != LOGIN_STATUS_NOTREGISTERED and getPlayerLoginStatus(i) != LOGIN_STATUS_NON) {
						TakePlayerVIPTime(i, secondsTime);
						if(GetPlayerVIPTime(i) <= timestamp()) SetPlayerVIPTime(i, 0);
					}
				}
			} else {		
				forplayers(i) {
					if(getPlayerLoginStatus(i) != LOGIN_STATUS_NOTREGISTERED and getPlayerLoginStatus(i) != LOGIN_STATUS_NON) {
						if(GetPlayerVIPTime(i) < timestamp()) SetPlayerVIPTime(i, timestamp() + secondsTime);
						else AddPlayerVIPTime(i, secondsTime);						
					}
				}
			}	
			
			format(string, sizeof(string), "\
					%s "C_WHITE"%d "TEXT_DIALOG_HEAD"dni konta VIP kazdemu zarejestrowanemu graczowi.\
				",
				pointsSymbol == -1 ? ("Odebrales(as)") : ("Dodales(as)"), pointsValue
			);
			ShowPlayerInfoDialog(playerid, BACK_VIPMENU_MENU, "Operacje na kontach VIP - Czas trwania konta VIP", string);					
		} else {
			format(string, sizeof(string),"\
					Czy na pewno chcesz "C_WHITE"%s %d "TEXT_DIALOG_HEAD"dni konta premium wszystkim graczom??\
				",
				pointsSymbol == 1 ? ("dodac") : ("odjac"), 
				pointsValue
			);
			ShowPlayerYesNoDialog(playerid, D_YESNO_HA_VIPMENU_TIME, "Operacje na kontach VIP - Czas trwania konta VIP", string);				
		}
		return _TRUE;

	}
	return _FALSE;
}




