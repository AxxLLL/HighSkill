/*

*/
//===============================================================
//---------------------------------------------------------------
//===============================================================
UpdateBasesByUserNewNick(userid, nick[]) {
	new conNick[MAX_PLAYER_NAME];
	new string[128];
	strins(conNick, nick, 0);
	ConvertNick(conNick);

	format(string, sizeof(string), "UPDATE `"T_BAN"` SET `"TB_ADMIN_NAME"`='%s' WHERE `"TB_ADMINID"`='%d'", conNick, userid);
	sendQueryWithout(string);
									
	format(string, sizeof(string), "UPDATE `"T_TIME_BAN"` SET `"TTB_PLAYER_NAME"`='%s' WHERE `"TTB_UID"`='%d'", conNick, userid);
	sendQueryWithout(string);			

	format(string, sizeof(string), "UPDATE `"T_TIME_BAN"` SET `"TTB_ADMIN_NAME"`='%s' WHERE `"TTB_ADMINID"`='%d'", conNick, userid);
	sendQueryWithout(string);		
	return _TRUE;
}
//---------------------------------------------------------------

//---------------------------------------------------------------
DeletePlayerAccount(userid, adminid = INVALID_PLAYER_ID) {
	new pName[MAX_PLAYER_NAME];
	strins(pName, GetNickByUserID(userid), 0);
	if(IsValidNick(pName) == _TRUE) {
		new string[128];
		new year, month, day, hour, minute;
		
		gettime(hour, minute);
		getdate(year, month, day);
		
		format(string, sizeof(string), "DELETE FROM `"T_KONTA"` WHERE `"TK_UID"`='%d'", userid);
		sendQueryWithout(string);
		CallLocalFunction("DeleteAccountData", "d", userid);
		
		format(string, 128, L_PLAYER "/%d.txt", userid);
	    if(fexist(string)) {
			if(CheckFolderPatch(L_DEL_PLAYER) == _TRUE and getSettingIntValueByIndex(s_CopyDeletingID) == 1) {
                new File:f_del = fopen(string, io_read);
                format(string, 128, L_DEL_PLAYER "%s(%d).txt", pName, userid);
                new File:f_new = fopen(string, io_write);
                while(fread(f_del, string, sizeof(string))) {
					DeleteNewLine(string);
                    if(strlen(string) > 5) {
						fwrite(f_new, "\r\n");
                        fwrite(f_new, string);
                    }
                }
                format(string, sizeof(string), "\r\n( %s  [ %d:%02d ])  KONTO USUNIETE PRZEZ ADMINISTRATORA: %s  (UID: %d)", strData(year, month, day, " / ", false, false, true, false), hour, minute, ((IsPlayerConnected(adminid) and IsAdmin(adminid) > 0) ? getPlayerName(adminid) : ("*System*")), ((IsPlayerConnected(adminid) and IsAdmin(adminid) > 0) ? getPlayerUserID(adminid) : 0));
                fwrite(f_new, string);
                fclose(f_del);
                fclose(f_new);
			}
			format(string, 128, L_PLAYER "/%d.txt", userid);
            fremove(string);
        }
        format(string, sizeof(string),"%s  (UID: %d)", pName, userid);
        AddToDeletingInfoLog(string);

		format(string, sizeof(string), " (Admin System) Administrator "C_WHITE"%s "TEXT_DIALOG_ALERT"usunal(ela) Twoje konto z serwera.", ((IsPlayerConnected(adminid) and IsAdmin(adminid) > 0) ? getPlayerName(adminid) : ("*System*")));
		forplayers(i) {
			if(getPlayerUserID(i) == userid) {
				SendClientMessage(i, COLOR_DIALOG_ALERT, string);
				KickEx(i, 100);
				break;
			}
		}
		return _TRUE;
	}
	return _FALSE;
}

//===============================================================
CMD:konto(playerid) {
	ShowPlayerAccountMenu(playerid);
	return 1;
}
//---------------------------------------------------------------
ShowPlayerAccountMenu(playerid) {
	if(getPlayerLoginStatus(playerid) == LOGIN_STATUS_LOGGED) {
		if(IsAdmin(playerid) <= 0) {
			ShowPlayerDialogEx(playerid, DIALOG_PLAYER_ACCOUNT, DIALOG_STYLE_LIST, "Panel gracza", "\
					1) Informacje\n\
					2) Konto VIP\n\
					3) Zmiana nicku\n\
					4) Zmiana hasla gracza\n\
					5) Ustawienia\
				", "Dalej", "Wyjdz");
		} else {
			if(IsAdmin(playerid) < 2) {
				ShowPlayerDialogEx(playerid, DIALOG_PLAYER_ACCOUNT, DIALOG_STYLE_LIST, "Panel gracza", "\
						1) Informacje\n\
						2) Konto VIP\n\
						3) Zmiana nicku\n\
						4) Zmiana hasla gracza\n\
						5) Ustawienia\n\
						6) Zmiana hasla administratora (aLog)\
					", "Dalej", "Wyjdz");	
			} else {
				ShowPlayerDialogEx(playerid, DIALOG_PLAYER_ACCOUNT, DIALOG_STYLE_LIST, "Panel gracza", "\
						1) Informacje\n\
						2) Konto VIP\n\
						3) Zmiana nicku\n\
						4) Zmiana hasla gracza\n\
						5) Ustawienia\n\
						6) Zmiana hasla administratora (aLog)\
					", "Dalej", "Wyjdz");			
			}
		}
		return _TRUE;
	} else if (getPlayerLoginStatus(playerid) == LOGIN_STATUS_NOTREGISTERED) {
		ShowPlayerDialogEx(playerid, DIALOG_PLAYER_ACCOUNT, DIALOG_STYLE_LIST, "Panel gracza", "\
				1) Zarejestruj konto\n\
				2) Ustawienia\
			", "Dalej", "Wyjdz");	
		return _TRUE;
	}
	return _FALSE;
}
//===============================================================
PlayerAccountMenu(playerid, listitem) {
	if(getPlayerLoginStatus(playerid) == LOGIN_STATUS_LOGGED) {
		switch(listitem) {
			case 0: {
				new string[1024], adminTime[64] = TEXT_DIALOG_HEAD"( "TEXT_DIALOG_NORMAL"Brak"TEXT_DIALOG_HEAD" )";
				new lastNick[24], lastIP[16], fullConfidental[32] = "Tak", provConfidental[80] = "Nie";
				new lastlogin_Y, lastlogin_M, lastlogin_D, lastlogin_h, laslogin_m,
					delete_Y, delete_M, delete_D,
					adminStamp, playTime,
					register_Y, register_M, register_D;
				
				dtimestamp(GetPVarInt(playerid, PV_LOGIN_REGISTER_STAMP), register_Y, register_M, register_D); 
				dtimestamp(GetPVarInt(playerid, PV_LOGIN_LAST_LOGIN_STAMP), lastlogin_Y, lastlogin_M, lastlogin_D, lastlogin_h, laslogin_m); 
				dtimestamp(GetPVarInt(playerid, PV_LOGIN_DELETE_STAMP), delete_Y, delete_M, delete_D);
				adminStamp = GetPVarInt(playerid, PV_LOGIN_ADMIN_STAMP);		
				playTime = GetPVarInt(playerid, PV_LOGIN_PLAY_TIME) + getPlayerConnectTime(playerid);

				GetPVarString(playerid, PV_LOGIN_LAST_NICK, 	lastNick, sizeof(lastNick));
				GetPVarString(playerid, PV_LOGIN_LAST_LOGIN_IP, lastIP, sizeof(lastIP));
				
				if(IsValidNick(lastNick) == _FALSE) {
					strdel(lastNick, 0, MAX_PLAYER_NAME);
					strins(lastNick, "-", 0);
				}
				
				if(adminStamp > timestamp()) {
					new admin_Y, admin_M, admin_D;
					dtimestamp(adminStamp, admin_Y, admin_M, admin_D);
					format(adminTime, sizeof(adminTime), TEXT_DIALOG_HEAD"( "TEXT_DIALOG_NORMAL"%s"TEXT_DIALOG_HEAD" )", strData(admin_Y, admin_M, admin_D, " / ", false, false, true, false));
				}
				
				if(isPlayerConfidental(playerid) == _FALSE) {
					format(fullConfidental, sizeof(fullConfidental), "Brakuje %s", convertSeconds(ToSeconds(getSettingIntValueByIndex(s_LoginConfiID), _HOUR) - playTime));
				}
				if(isPlayerProvConfidental(playerid) == _TRUE) {
					new prov_Y, prov_M, prov_D, prov_h, prov_m;
					dtimestamp(GetPVarInt(playerid, PV_LOGIN_PROV_CONFIDENTAL), prov_Y, prov_M, prov_D, prov_h, prov_m);
					format(provConfidental, sizeof(provConfidental), "Tak "TEXT_DIALOG_HEAD"( "TEXT_DIALOG_NORMAL"%s "TEXT_DIALOG_HEAD"[ "TEXT_DIALOG_NORMAL"%d:%02d "TEXT_DIALOG_HEAD"] )", strData(prov_Y, prov_M, prov_D, " / ", false, false, true, false), prov_h, prov_m);
				}
				
				
				format(string, sizeof(string), 
						TEXT_DIALOG_HEAD"Nick: "TEXT_DIALOG_NORMAL"%s   "TEXT_DIALOG_HEAD"(Poprzedni: "TEXT_DIALOG_NORMAL"%s"TEXT_DIALOG_HEAD" )\n\
						"TEXT_DIALOG_HEAD"User ID: "TEXT_DIALOG_NORMAL"%d\n\
						"TEXT_DIALOG_HEAD"Data rejestracji: "TEXT_DIALOG_NORMAL"%s\n\
						"TEXT_DIALOG_HEAD"Ostatnie logowanie: "TEXT_DIALOG_NORMAL"%s "TEXT_DIALOG_HEAD"[ "TEXT_DIALOG_NORMAL"%d:%02d "TEXT_DIALOG_HEAD"]  ( IP: "TEXT_DIALOG_NORMAL"%s "TEXT_DIALOG_HEAD")\n\
					",
					getPlayerName(playerid), lastNick, 
					getPlayerUserID(playerid), 
					strData(register_Y, register_M, register_D, " / ", false, false, true, false), 
					strData(lastlogin_Y, lastlogin_M, lastlogin_D, " / ", false, false, true, false), lastlogin_h, laslogin_m, lastIP					
				);
				
				format(string, sizeof(string), "%s\
						"TEXT_DIALOG_HEAD"Data usuniecia konta: "TEXT_DIALOG_NORMAL"%s "TEXT_DIALOG_HEAD"("TEXT_DIALOG_ALERT"*"TEXT_DIALOG_HEAD")\n\
						"TEXT_DIALOG_HEAD"Prawa administratora: "TEXT_DIALOG_NORMAL"%s  %s\n\
						"TEXT_DIALOG_HEAD"Czas gry: "TEXT_DIALOG_NORMAL"%s\n\
						"TEXT_DIALOG_HEAD"Zaufany (pelny): "TEXT_DIALOG_NORMAL"%s\n\
					", 
					string, 		
					strData(delete_Y, delete_M, delete_D, " / ", false, false, true, false),
					GetAdminNameByLvL(IsAdmin(playerid)), adminTime, 
					playTime > 0 ? convertSeconds(playTime) : ("Brak"),
					fullConfidental
				);			
				
				format(string, sizeof(string), "%s\
						"TEXT_DIALOG_HEAD"Zaufany (warunkowy): "TEXT_DIALOG_NORMAL"%s\n\n\
						"TEXT_DIALOG_ALERT"* "TEXT_DIALOG_HEAD"Data usuniecia konta z systemu w przypadku braku aktywnosci.", 			
					string,
					provConfidental
				);				
	
				ShowPlayerInfoDialog(playerid, BACK_PLAYER_ACC_MENU, "Panel gracza - Informacje", string);
			}
			case 1: PlayerAccountVIPSettings(playerid, -1);
			case 2: PlayerAccountNickChange(playerid);
			case 3: PlayerAccountPasswordChange(playerid);
			case 4: PlayerAccountSettings(playerid, -1);
			case 5: {
				DeletePVar(playerid, PV_ALOG_PASSWORD_CHANGE);
				PlayerAccountAlogPasswordChange(playerid);
			}
		}
		
		return _TRUE;
	} else if (getPlayerLoginStatus(playerid) == LOGIN_STATUS_NOTREGISTERED) {
		switch(listitem) {
			case 0: cmd_zarejestruj(playerid);
			case 1: PlayerAccountSettings(playerid, -1);
		}
		return _TRUE;
	}
	return _FALSE;
}
//---------------------------------------------------------------
PlayerAccountNickChange(playerid, nick[] = "") {
	if(getPlayerLoginStatus(playerid) == LOGIN_STATUS_LOGGED) {
		new string[300];	
		new sTime = timestamp(),
			changeTime = GetPVarInt(playerid, PV_LOGIN_LAST_NICK_STAMP) + ToSeconds(getSettingIntValueByIndex(s_NickChangeTimeID), _DAY);
		if(sTime > changeTime) {
			if(!isnull(nick)) {
				if(IsValidNick(nick) == _TRUE) {
					if(IsNickRegistered(nick) == 0) {
						new bool:usedOnLine;
						forplayers(i) {
							if(strcmp(getPlayerName(i), nick) == 0) {
								usedOnLine = true;
								break;
							}
						}
						if(usedOnLine == false) {
							if(CheckSimilarRegisterNick(nick) == 0) {
								if(GetBanUniqueID(B_NICK, nick) == 0) {
									new conNick[MAX_PLAYER_NAME];
									strins(conNick, nick, 0);
									ConvertNick(conNick);
									format(string, sizeof(string),"UPDATE `"T_KONTA"` SET `"TK_NICK"`='%s', `"TK_LAST_NICK_STAMP"`='%d', `"TK_LAST_NICK"`='%s' WHERE `"TK_UID"` = '%d'", conNick, sTime, getPlayerName(playerid), getPlayerUserID(playerid));
									sendQueryWithout(string);
									
									UpdateBasesByUserNewNick(getPlayerUserID(playerid), nick);
									AddToNickChangeLog(getPlayerUserID(playerid), nick, getPlayerName(playerid));
									
									format(string, sizeof(string), "Zmiana nicku %s -> %s", getPlayerName(playerid), nick);
									AddToPlayerLog(getPlayerUserID(playerid), string);							
									format(string, sizeof(string),"[Zmiana nicku] Gracz '%s' (UID: %d) zmienil(a) swoj nick na '%s'.", getPlayerName(playerid), getPlayerUserID(playerid), nick);
									AddToChatLog(string);	
									
									SetPVarString(playerid, PV_LOGIN_LAST_NICK, getPlayerName(playerid));
									SetPVarInt(playerid, PV_LOGIN_LAST_NICK_STAMP, sTime);							
									setPlayerName(playerid, nick);			
						
									format(string, sizeof(string), 
											"\t\t Twoj nick zostal zmieniony.\n\n\
											"TEXT_DIALOG_ALERT"\t\t    ___Dane do logowania___\n\
											"TEXT_DIALOG_HEAD"\t\t\t Nick: "TEXT_DIALOG_NORMAL"%s\n\n\
											"TEXT_DIALOG_HEAD"     Od tej chwili bedziesz musial(a) uzywac nowego nicku,\n\
											\t     chcac zalogowac sie na swoje konto.", 
										getPlayerName(playerid)
									);
									ShowPlayerInfoDialog(playerid, BACK_PLAYER_ACC_MENU, "Panel gracza - Zmiana nicku", string);
									return _TRUE;	
								} else format(string, sizeof(string), TEXT_DIALOG_ALERT"\n\tNick "TEXT_DIALOG_NORMAL"%s "TEXT_DIALOG_ALERT"znajduje sie na ban liscie.", nick);
							} else format(string, sizeof(string), TEXT_DIALOG_ALERT"\n\tNick "TEXT_DIALOG_NORMAL"%s "TEXT_DIALOG_ALERT"jest zbyt podobny do jednego z zarejestrowanych kont.", nick);	
						}	else format(string, sizeof(string), TEXT_DIALOG_ALERT"\n\tNick "TEXT_DIALOG_NORMAL"%s "TEXT_DIALOG_ALERT"jest uzywany przez ktoregos gracza.", nick);				
					}	else format(string, sizeof(string), TEXT_DIALOG_ALERT"\n\t\tNick "TEXT_DIALOG_NORMAL"%s"TEXT_DIALOG_ALERT" jest juz zarejestrowany.", nick);					
				}	else format(string, sizeof(string), TEXT_DIALOG_ALERT"\nNick zawiera niedozwolone znaki lub ma nieodpowiednia dlugosc.");
			}		
		} else {
			new Y, M, D, g, m;
			dtimestamp(changeTime, Y, M, D, g, m);
			format(string, sizeof(string), "         Nick mozna zmienic raz na %d dni.\nKolejny raz tej opcji bedziesz mogl(a) uzyc:\n\n\t"TEXT_DIALOG_NORMAL"%s "TEXT_DIALOG_BODY"[ "TEXT_DIALOG_NORMAL"%d:%02d "TEXT_DIALOG_BODY"]",
				getSettingIntValueByIndex(s_NickChangeTimeID),
				strData(Y, M, D, " / ", false, false, true, false), g, m
			);
			ShowPlayerInfoDialog(playerid, BACK_PLAYER_ACC_MENU, "Panel gracza - Zmiana nicku", string);
			return _TRUE;
		}		
		format(string, sizeof(string), TEXT_DIALOG_HEAD"    W tym panelu mozesz zmienic uzywany nick. Po zmianie\n   nicku przy kazdym wejsciu na serwer bedziesz musial(a)\nuzywac nowej nazwy. Zmiana nicku jest mozliwa raz na %d dni.\n%s", getSettingIntValueByIndex(s_NickChangeTimeID), string);
		ShowPlayerDialogEx(playerid, DIALOG_PLAYER_NICK, DIALOG_STYLE_INPUT, "Panel gracza - Zmiana nicku", string, "Zmien", "Wroc");
		return _TRUE;
	}
	return _FALSE;
}
//---------------------------------------------------------------
PlayerAccountPasswordChange(playerid, password[] = "") {
	if(getPlayerLoginStatus(playerid) == LOGIN_STATUS_LOGGED) {
		new string[300];
		if(!isnull(password)) {
			if(IsValidPassword(password) == _TRUE) {
				new hnum;
				if((hnum = Hash(password)) != GetPVarInt(playerid, PV_LOGIN_ADMIN_PASSWORD)) {
					format(string, sizeof(string),"UPDATE `"T_KONTA"` SET `"TK_PASSWORD"`='%d', `"TK_RESET_PASSWORD"`='0' WHERE `"TK_UID"`='%d'", hnum, getPlayerUserID(playerid));
					sendQueryWithout(string);		
					
					SetPVarInt(playerid, PV_LOGIN_PASSWORD, hnum);					

					format(string, sizeof(string), 
						"\t         Haslo do konta zostalo zmienione.\n\n\
						"TEXT_DIALOG_ALERT"\t\t ___Dane do logowania___\n\
						"TEXT_DIALOG_HEAD"\t\t       Haslo: "TEXT_DIALOG_NORMAL"%s\n\n\
						"TEXT_DIALOG_HEAD"     Od tej chwili bedziesz musial(a) uzywac nowego hasla,\n\
						\t     chcac zalogowac sie na swoje konto.", 
					password);
					
					if(GetPVarInt(playerid, PV_LOGIN_RESET_PASSWORD) == 0) {
						AddToPlayerLog(getPlayerUserID(playerid), "Gracz zmienil swoje haslo do konta.");
						ShowPlayerInfoDialog(playerid, BACK_PLAYER_ACC_MENU, "Panel gracza - Zmiana hasla", string);
					} else {
						SetPVarInt(playerid, PV_LOGIN_RESET_PASSWORD, 0);
						AddToPlayerLog(getPlayerUserID(playerid), "Gracz ustawil nowe haslo po zresetowaniu.");
						ShowPlayerInfoDialog(playerid, -1, "Reset hasla do konta", string);
					}					
					return _TRUE;											
				}	else strins(string, TEXT_DIALOG_ALERT"\n    Haslo do konta nie moze pokrywac sie z haslem aLog.", 0);
			}	else strins(string, TEXT_DIALOG_ALERT"\n\tHaslo nie spelnia wymogow bezpieczenstwa.", 0);
		}
		if(GetPVarInt(playerid, PV_LOGIN_RESET_PASSWORD) == 0) {
			format(string, sizeof(string), TEXT_DIALOG_HEAD"  W tym panelu mozesz zmienic haslo do swojego konta.\n           Haslo powinno skladac sie z od "#MIN_PASSWORD_LEN" do "#MAX_PASSWORD_LEN" znakow\noraz musi zawierac co najmniej 3 litery i 3 znak i specjalne\n\t         (cyfry lub symbole '!', '@', '#', '$').\n%s", string);
			ShowPlayerDialogEx(playerid, DIALOG_PLAYER_PASSWORD, DIALOG_STYLE_INPUT, "Panel gracza - Zmiana hasla", string, "Zmien", "Wroc");		
		} else {
			format(string, sizeof(string), "  Haslo do Twojego konta zostalo zresetowane przez administratora\n              Nowe haslo powinno skladac sie z od "#MIN_PASSWORD_LEN" do "#MAX_PASSWORD_LEN" znakow\n          oraz musi zawierac co najmniej 3 litery i 3 znak i specjalne\n\t                 (cyfry lub symbole '!', '@', '#', '$').\n%s", string);
			ShowPlayerDialogEx(playerid, DIALOG_PLAYER_PASSWORD, DIALOG_STYLE_INPUT, "Reset hasla do konta", string, "Zmien", "");		
		}
		return _TRUE;
	}
	return _FALSE;
}
//---------------------------------------------------------------
PlayerAccountAlogPasswordChange(playerid, alogpassword[] = "") {
	if(getPlayerLoginStatus(playerid) == LOGIN_STATUS_LOGGED and (IsAdmin(playerid) > 0 or GetPVarInt(playerid, PV_ALOG_PASSWORD_CHANGE) == 1)) {
		new string[350];
		if(!isnull(alogpassword)) {
			if(IsValidPassword(alogpassword) == _TRUE) {
				new hnum;
				if((hnum = Hash(alogpassword)) != GetPVarInt(playerid, PV_LOGIN_PASSWORD)) {
					format(string, sizeof(string),"UPDATE `"T_KONTA"` SET `"TK_ADMIN_PASSWORD"`='%d' WHERE `"TK_UID"`='%d'", hnum, getPlayerUserID(playerid));
					sendQueryWithout(string);	
					
					SetPVarInt(playerid, PV_LOGIN_ADMIN_PASSWORD, hnum);					

					format(string, sizeof(string), 
						"\tHaslo do konta administratora zostalo zmienione.\n\n\
						"TEXT_DIALOG_ALERT"\t\t ___Dane do logowania___\n\
						"TEXT_DIALOG_HEAD"\t\t       Haslo: "TEXT_DIALOG_NORMAL"%s\n\n\
						"TEXT_DIALOG_HEAD"     Od tej chwili bedziesz musial(a) uzywac nowego hasla,\n\
						\t chcac zalogowac sie na konto administratora.", 
					alogpassword);

					if(GetPVarInt(playerid, PV_ALOG_PASSWORD_CHANGE) == 1) {
						DeletePVar(playerid, PV_ALOG_PASSWORD_CHANGE);
						AddToPlayerLog(getPlayerUserID(playerid), "Gracz ustawil swoje haslo do konta administratora (Pierwsze logowanie aLog).");
						ShowPlayerInfoDialog(playerid, BACK_ALOG_MENU, "Pierwsze logowanie aLog", string);		
					} else {
						AddToPlayerLog(getPlayerUserID(playerid), "Gracz zmienil swoje haslo do konta administratora (aLog).");
						ShowPlayerInfoDialog(playerid, BACK_PLAYER_ACC_MENU, "Panel gracza - Zmiana hasla administratora", string);	
					}
					return _TRUE;											
				}	else strins(string, TEXT_DIALOG_ALERT"\n  Haslo do konta nie moze pokrywac sie z haslem do konta gracza.", 0);
			}	else strins(string, TEXT_DIALOG_ALERT"\n\tHaslo nie spelnia wymogow bezpieczenstwa.", 0);
		}
		format(string, sizeof(string), TEXT_DIALOG_HEAD"W tym panelu mozesz zmienic haslo do konta administratora.\n           Haslo powinno skladac sie z od "#MIN_PASSWORD_LEN" do "#MAX_PASSWORD_LEN" znakow\noraz musi zawierac co najmniej 3 litery i 3 znak i specjalne\n\t         (cyfry lub symbole '!', '@', '#', '$').\n%s", string);
		if(GetPVarInt(playerid, PV_ALOG_PASSWORD_CHANGE) == 1) {
			ShowPlayerDialogEx(playerid, DIALOG_PLAYER_ALOG_PASSWORD, DIALOG_STYLE_INPUT, "Pierwsze logowanie aLog", string, "Ustaw", "Wyjdz");		
		} else {
			ShowPlayerDialogEx(playerid, DIALOG_PLAYER_ALOG_PASSWORD, DIALOG_STYLE_INPUT, "Panel gracza - Zmiana hasla", string, "Zmien", "Wroc");		
		}		
		return _TRUE;
	}
	return _FALSE;
}
//---------------------------------------------------------------
forward PlayerAccountSettings(playerid, listitem);
public PlayerAccountSettings(playerid, listitem) {
	new string[350];
	if(getPlayerLoginStatus(playerid) == LOGIN_STATUS_LOGGED) {		
		switch(listitem) {
			case 0: {
				if(getSettingIntValueByIndex(s_ReconnectMaxTimeID) > 0) {
					format(string, sizeof(string), 
							"  W tym menu mozesz ustawic status autologowania na swoje konto.\n\
							Jesli w ciagu %d minut wejdziesz na serwer z niezmienionymi danymi\
							\n           zostaniesz automatycznie zalogowany(a) na swoje konto.\n\n\
							\t\tCzy chcesz skorzystac z tej opcji?", 
						getSettingIntValueByIndex(s_ReconnectMaxTimeID)
					);
					ShowPlayerYesNoDialog(playerid, D_YESNO_AUTOLOG, "Panel gracza - Auto logowanie (Ust.)", string);
				} else {
					ShowPlayerInfoDialog(playerid, BACK_PLAYER_ACC_SETTINGS, "Panel gracza - Auto logowanie (Ust.)", "Mozliwosc automatycznego logowania zostala wylaczona przez administracje.");
				}
				
			}
			case 1: {
				format(string, sizeof(string),
					"     W tym menu mozesz ustawic status cenzury wiadomosci, ktore otrzymujesz\n\
						od innych graczy. Ustawienia dot. cenzury ustawione przez gracza brane sa pod\n\
						\tuwage w przypadku kiedy nie jest wlaczona cenzura serwerowa.\n\n\
						\t\t     Status 'cenzury serwerowej': %s\n\n\
						\t\t           "TEXT_DIALOG_HEAD"Czy chcesz skorzystac z tej opcji?",
				getSettingIntValueByIndex(s_CensureStatusID) == 0 ? (C_LIGHTGREEN"Wylaczona") : (C_ADMIN"Wlaczona"));
						
				ShowPlayerYesNoDialog(playerid, D_YESNO_PLAYERCENSURE, "Panel gracza - Cenzurowanie wiadomosci (Ust.)", string);				
			}
			case 2: PlayerPrivMessagesSettings(playerid);
			case 3: {
				if(CallRemoteFunction("ShowPlayerGameMenu", "ddd", playerid, -1, 0) == _FALSE) {
					ShowPlayerInfoDialog(playerid, BACK_PLAYER_ACC_SETTINGS, "Ustawienia - Ustawienia gry", "Aktualny gamemod nie obsluguje ustawien gry, lub nie jest zsynchronizowany z admin systemem.");
				}
			}
			default: {
				format(string, sizeof(string), "1) Automatyczne logowanie\t\t[ %s "TEXT_DIALOG_BODY"]\n2) Cenzurowanie wiadomosci\t\t[ %s "TEXT_DIALOG_BODY"]\n3) Prywatne wiadomosci\t\t[ %s "TEXT_DIALOG_BODY"]\n4) Ustawienia gry",
					(GetPVarInt(playerid, PV_SET_RECONNECT) == 0 or getSettingIntValueByIndex(s_ReconnectMaxTimeID) == 0 ? (C_ADMIN"Nie") : (C_LIGHTGREEN"Tak")),
					(getPlayerCensureStatus(playerid) == 0 ? (C_ADMIN"Nie") : (C_LIGHTGREEN"Tak")),
					(GetPlayerPMessagesStatus(playerid) == 0 or getSettingIntValueByIndex(s_PrivMessagesID) == 0 ? (C_ADMIN"Nie") : (C_LIGHTGREEN"Tak"))
				);
				ShowPlayerDialogEx(playerid, DIALOG_PLAYER_SETTINGS, DIALOG_STYLE_LIST, "Panel gracza - Ustawienia", string, "Zmien", "Wroc");
			} 
		}
		return _TRUE;
	} else if (getPlayerLoginStatus(playerid) == LOGIN_STATUS_NOTREGISTERED) {
		switch(listitem) {
			case 0: {
				format(string, sizeof(string),
					"     W tym menu mozesz ustawic status cenzury wiadomosci, ktore otrzymujesz\n\
						od innych graczy. Ustawienia dot. cenzury ustawione przez gracza brane sa pod\n\
						\tuwage w przypadku kiedy nie jest wlaczona cenzura serwerowa.\n\n\
						\t\t     Status 'cenzury serwerowej': %s\n\n\
						\t\t           "TEXT_DIALOG_HEAD"Czy chcesz skorzystac z tej opcji?",
				getSettingIntValueByIndex(s_CensureStatusID) == 0 ? (C_LIGHTGREEN"Wylaczona") : (C_ADMIN"Wlaczona"));
				ShowPlayerYesNoDialog(playerid, D_YESNO_PLAYERCENSURE, "Panel gracza - Cenzurowanie wiadomosci (Ust.)", string);				
			}
			case 1: PlayerPrivMessagesSettings(playerid);
			case 2: {
				if(CallRemoteFunction("ShowPlayerGameMenu", "ddd", playerid, -1, 0) == _FALSE) {
					ShowPlayerInfoDialog(playerid, BACK_PLAYER_ACC_SETTINGS, "Ustawienia - Ustawienia gry", "Aktualny gamemod nie obsluguje ustawien gry, lub nie jest zsynchronizowany z admin systemem.");
				}
			}
			default: {
				format(string, sizeof(string), "1) Cenzurowanie wiadomosci\t\t[ %s "TEXT_DIALOG_BODY"]\n2) Prywatne wiadomosci\t\t[ %s "TEXT_DIALOG_BODY"]\n3) Ustawienia gry",
					(getPlayerCensureStatus(playerid) == 0 ? (C_ADMIN"Nie") : (C_LIGHTGREEN"Tak")),
					(GetPlayerPMessagesStatus(playerid) == 0 or getSettingIntValueByIndex(s_PrivMessagesID) == 0 ? (C_ADMIN"Nie") : (C_LIGHTGREEN"Tak"))
				);
				ShowPlayerDialogEx(playerid, DIALOG_PLAYER_SETTINGS, DIALOG_STYLE_LIST, "Panel gracza - Ustawienia", string, "Zmien", "Wroc");
			} 
		}
		return _TRUE;
	}
	return _FALSE;
}
//---------------------------------------------------------------
PlayerPrivMessagesSettings(playerid, listitem = -1) {
	if(getPlayerLoginStatus(playerid) == LOGIN_STATUS_LOGGED or getPlayerLoginStatus(playerid) == LOGIN_STATUS_NOTREGISTERED) {
		if(getSettingIntValueByIndex(s_PrivMessagesID) == 0) {
			ShowPlayerInfoDialog(playerid, BACK_PLAYER_ACC_SETTINGS, "Ustawienia - Prywatne wiadomosci", "Prywatne wiadomosci obslugiwane przez admin system sa wylaczone.");
		} else {	
			new string[300];
			switch(listitem) {
				case 0: {
					ShowPlayerYesNoDialog(playerid, D_YESNO_PLAYERGLOBPRIV, "Ustawienia - Prywatne wiadomosci (Glob.)", 
						"      W tym menu mozesz ustawic status globalnych prywatnych wiadomosci\
						\n od innych graczy. W przypadku wylaczenia wiadomosci, nie bedziesz mogl(a)\n\
						odbierac, ani wysylac PW do innych osob. Blokada nie dotyczy wiadomosci od\n\
						administracji. W przypadku kiedy posiadasz aktywne przywileje administratora\
						\n wylaczenie tej opcji spowoduje, ze nie bedziesz otrzymywac wiadomosci od\n\
						\t\tgraczy ale sam(a) bedziesz mogl(a) je wysylac.\n\n\
						\t\t           Czy chcesz skorzystac z tej opcji?");	
				}
				case 1: {
					SetPlayerPage(playerid, 0);
					PlayerPMFPSettings(playerid);
				}
				case 2: {
					ShowPlayerPrivMessagesSounds(playerid);
				}
				case 3: {
					if(!(-getSettingIntValueByIndex(s_PrivMessagesSpecID) < IsAdmin(playerid) < getSettingIntValueByIndex(s_PrivMessagesSpecID)) and getSettingIntValueByIndex(s_PrivMessagesSpecID) != 0) {
						ShowPlayerYesNoDialog(playerid, D_YESNO_PLAYERSPECPRIV, "Ustawienia - Prywatne wiadomosci (Admin Spec.)", 
							"W tym menu mozesz ustawic okreslic status podgladu prywatnych wiadomosci\
							\nwysylanych przez innych graczy na serwerze. Opcja jest dostepna jedynie dla\
							\n\t\tadministratorow z ranga Head Admin i wyzsza.\n\n\
							\t\t          Czy chcesz skorzystac z tej opcji?");						
					} else PlayerPrivMessagesSettings(playerid);
				}
				default: {
					if(-getSettingIntValueByIndex(s_PrivMessagesSpecID) < IsAdmin(playerid) < getSettingIntValueByIndex(s_PrivMessagesSpecID) or getSettingIntValueByIndex(s_PrivMessagesSpecID) == 0) {
						format(string, sizeof(string), 
								"1) Prywatne wiadomosci ("C_WHITE"Globalnie"TEXT_DIALOG_BODY")\t\t\t[ %s "TEXT_DIALOG_BODY"]\n\
								2) Prywatne wiadomosci ("C_WHITE"Od poszczegolnych graczy"TEXT_DIALOG_BODY")\n\
								3) Dzwiek odbioru wiadomosci \t\t\t\t[ "C_WHITE"%s "TEXT_DIALOG_BODY"]\
								",
							(GetPlayerPMessagesStatus(playerid) == 0 ? (C_ADMIN"Nie") : (C_LIGHTGREEN"Tak")),
							privMessagesSounds[GetPlayerPMSoundID(playerid)][SOUND_NAME]
						);		
					} else {
						format(string, sizeof(string), 
								"1) Prywatne wiadomosci ("C_WHITE"Globalnie"TEXT_DIALOG_BODY")\t\t\t[ %s "TEXT_DIALOG_BODY"]\n\
								2) Prywatne wiadomosci ("C_WHITE"Od poszczegolnych graczy"TEXT_DIALOG_BODY")\n\
								3) Dzwiek odbioru wiadomosci \t\t\t\t[ "C_WHITE"%s "TEXT_DIALOG_BODY"]\n\
								4) Podglad prywatnych wiadomosci\t\t\t[ %s "TEXT_DIALOG_BODY"]",
							(GetPlayerPMessagesStatus(playerid) == 0 ? (C_ADMIN"Nie") : (C_LIGHTGREEN"Tak")),
							privMessagesSounds[GetPlayerPMSoundID(playerid)][SOUND_NAME],
							(GetPlayerPMessagesSpec(playerid) == 0 ? (C_ADMIN"Nie") : (C_LIGHTGREEN"Tak"))
						);					
					}
					ShowPlayerDialogEx(playerid, DIALOG_PLAYER_PRIV_SETTINGS, DIALOG_STYLE_LIST, "Panel gracza - Ustawienia", string, "Zmien", "Wroc");
				}
			}
		}
		return _TRUE;
	}
	return _FALSE;
}
//---------------------------------------------------------------
PlayerPMFPSettings(playerid, listitem = -1) {
	if(getPlayerLoginStatus(playerid) == LOGIN_STATUS_LOGGED or getPlayerLoginStatus(playerid) == LOGIN_STATUS_NOTREGISTERED) {
		new page = GetPlayerPage(playerid);
		switch(listitem) {
			case 0: {
				ShowPlayerInfoDialog(playerid, BACK_SETTINGS_PMFP_SETTINGS, "Info - Prywatne wiadomosci (Gracz.)", 
					"W tym menu mozesz ustawic status prywatnych wiadomosci od poszczegolnych graczy na serwerze.\
					\n   Administratorow dotycza takie same reguly jak w przypadku globalnych prywatnych wiadomosci.");
			}
			case 1..12: {
				if(listitem == 1 and (page > 0 or page * 10 + 10 < MAX_PLAYERS)) {
					if(page * 10 + 10 < MAX_PLAYERS) {
						SetPlayerPage(playerid, page + 1);			
					} else {
						SetPlayerPage(playerid, page - 1);
					}
				} else if(listitem == 2 and page > 0 and page * 10 + 10 < MAX_PLAYERS) {
					SetPlayerPage(playerid, page - 1);								
				} else {
					new forplayer = -1 + page * 10 + listitem;
					if(page * 10 + 10 < MAX_PLAYERS) forplayer --;
					if(page > 0) forplayer --;
									
					SetPlayerPMFromPlayerStatus(playerid, forplayer, GetPlayerPMFromPlayerStatus(playerid, forplayer) == _NONACTIVE ? _ACTIVE : _NONACTIVE);
				}		
				PlayerPMFPSettings(playerid);	
			}
			default: {
				new string[1024];
			
				if(page > 0) strins(string, TEXT_DIALOG_HEAD"\t\t\t<<< Poprzednia strona <<<\n", 0);
				if(page * 10 + 10 < MAX_PLAYERS) strins(string, TEXT_DIALOG_HEAD"\t\t\t>>> Nastepna strona >>>\n", 0);
				strins(string, TEXT_DIALOG_HEAD"\t\t\t>>> Informacje <<<\n", 0);
				
				for(new i = page * 10, Limit = ((page * 10 + 10) > MAX_PLAYERS ? MAX_PLAYERS : (page * 10 + 10)); i < Limit; i ++) {
					if(IsPlayerConnected(i)) {
						if(i != playerid) {
							format(string, sizeof(string), "%s  "TEXT_DIALOG_BODY"PM.ID %d\t\t[ %s "TEXT_DIALOG_BODY"]\n", string, i, GetPlayerPMFromPlayerStatus(playerid, i) == _NONACTIVE ? (C_ADMIN"Nie") : (C_LIGHTGREEN"Tak"));
						}   else format(string, sizeof(string), "%s  "TEXT_DIALOG_BODY"PM.ID %d\t\t[ "C_WHITE"NoN "TEXT_DIALOG_BODY"]\n", string, i);
					} else {
						format(string, sizeof(string), "%s  "TEXT_DIALOG_BODY"PM.ID %d\t\t[ "C_WHITE"OFF Line "TEXT_DIALOG_BODY"]\n", string, i);
					}
				}	
				strdel(string, strlen(string) - 1, strlen(string));
				ShowPlayerDialogEx(playerid, DIALOG_PLAYER_PRIV_PLAYERS_SETTINGS, DIALOG_STYLE_LIST, "Ustawienia - Prywatne wiadomosci (Gracz.)", string, "Zmien", "Wroc");
			}
		}
		return _TRUE;
	}
	return _FALSE;
}
//---------------------------------------------------------------
ShowPlayerPrivMessagesSounds(playerid, listitem = -1) {
	if(getPlayerLoginStatus(playerid) == LOGIN_STATUS_LOGGED or getPlayerLoginStatus(playerid) == LOGIN_STATUS_NOTREGISTERED) {
		if(listitem != -1) {
			SetPlayerPMSoundID(playerid, listitem);
			PlayerPlaySound(playerid, privMessagesSounds[GetPlayerPMSoundID(playerid)][SOUND_ID], 0.0, 0.0, 0.0);
		}
		new string[256];
		for(new i, p_soundid = GetPlayerPMSoundID(playerid); i < sizeof(privMessagesSounds); i ++) {
			format(string, sizeof(string),"%s\n%d) %s\t\t%s[ %s "TEXT_DIALOG_BODY"]", string, i + 1, privMessagesSounds[i][SOUND_NAME], strlen(privMessagesSounds[i][SOUND_NAME]) <= 4 ? ("\t") : (""), i == p_soundid ? (C_LIGHTGREEN"Tak") : (C_ADMIN"Nie"));
		}
		strdel(string, 0, 1);
		ShowPlayerDialogEx(playerid, DIALOG_PLAYER_PRIV_SOUND, DIALOG_STYLE_LIST, "Prywatne wiadomosci - Dzwiek odbioru wiadomosci", string, "Ustaw", "Wroc");
		return _TRUE;
	}
	return _FALSE;
}
//---------------------------------------------------------------
forward PlayerAccountVIPSettings(playerid, listitem);
public PlayerAccountVIPSettings(playerid, listitem) {
	if(getPlayerLoginStatus(playerid) == LOGIN_STATUS_LOGGED) {
		switch(listitem) {
			case 0: {
				new string[512];
				if(GetPlayerVIPTime(playerid) > timestamp()) {
					new year, month, day, hour, minute;
					dtimestamp(GetPlayerVIPTime(playerid), year, month, day, hour, minute);
					format(string, sizeof(string), C_LIGHTGREEN"Aktywne  "TEXT_DIALOG_HEAD"( "C_WHITE"%s  "TEXT_DIALOG_HEAD"[ "C_WHITE"%d:%02d "TEXT_DIALOG_HEAD"] )", strData(year, month, day, " / ", false, false, true, false), hour, minute);
				} else strins(string, C_WHITE"Brak", 0);			
		
				
				format(string, sizeof(string), "\n\
							"TEXT_DIALOG_HEAD"Aktywne przywileje VIP: %s\n\
							"TEXT_DIALOG_HEAD"Niewykorzystane wlasne punkty VIP: "C_WHITE"%d\n\
							"TEXT_DIALOG_HEAD"Niewykorzystane bonusowe punkty VIP: "C_WHITE"%d\n\
							"TEXT_DIALOG_HEAD"Razem niewykorzystanych punktow VIP: "C_WHITE"%d\n \
						", 
					string,
					GetPlayerVIPSelfPoints(playerid),
					GetPlayerVIPBonusPoints(playerid),
					GetPlayerVIPPoints(playerid)
				);
				ShowPlayerInfoDialog(playerid, BACK_PLAYER_ACC_VIP_MENU, "Konto VIP - Informacje o stanie konta", string);					
			}
			case 1: {
				if(CallRemoteFunction("VipPrivilagesInfo", "d", playerid) == 0) ShowPlayerInfoDialog(playerid, BACK_PLAYER_ACC_VIP_MENU, "Konto VIP - Informacje o przywilejach", "Gamemod nie dostarcza informacji o przywilejach VIP.");		
			}
			case 2: {
				if(getSettingIntValueByIndex(s_VIP3DaysCostID) == 0) ShowPlayerInfoDialog(playerid, BACK_PLAYER_ACC_VIP_MENU, "Konto VIP - Aktywuj VIP na 3 dni", "Aktualnie system ma wylaczona opcje aktywacji konta VIP na 3 dni.");		
				else {
					SetHelpVarValue(playerid, 0, 3);
					ActivateVIPPrivilages(playerid);					
				}
			}
			case 3: {
				if(getSettingIntValueByIndex(s_VIP7DaysCostID) == 0) ShowPlayerInfoDialog(playerid, BACK_PLAYER_ACC_VIP_MENU, "Konto VIP - Aktywuj VIP na 7 dni", "Aktualnie system ma wylaczona opcje aktywacji konta VIP na 7 dni.");		
				else {
					SetHelpVarValue(playerid, 0, 7);
					ActivateVIPPrivilages(playerid);					
				}
			}	
			case 4: {
				if(getSettingIntValueByIndex(s_VIP30DaysCostID) == 0) ShowPlayerInfoDialog(playerid, BACK_PLAYER_ACC_VIP_MENU, "Konto VIP - Aktywuj VIP na 30 dni", "Aktualnie system ma wylaczona opcje aktywacji konta VIP na 30 dni.");		
				else {
					SetHelpVarValue(playerid, 0, 30);
					ActivateVIPPrivilages(playerid);					
				}
			}		
			case 5: {
				if(GetPlayerVIPSelfPoints(playerid) <= 0) {
					ShowPlayerInfoDialog(playerid, BACK_PLAYER_ACC_VIP_MENU, "Konto VIP - Przekaz punkty premium", "Nie posiadasz punktow premium o charakterze "C_WHITE"wlasnym"TEXT_DIALOG_HEAD", ktore moglbys(abys) przekazac innemu graczowi.");
				} else SendPremiumPointsValue(playerid);
			}
			default: {
				ShowPlayerDialogEx(playerid, DIALOG_PLAYER_VIP_MENU, DIALOG_STYLE_LIST, "Konto VIP", "\
						1) Informacje o stanie konta\n\
						2) Informacje o przywilejach\n\
						3) Aktywuj VIP na 3 dni\n\
						4) Aktywuj VIP na 7 dni\n\
						5) Aktywuj VIP na 30 dni\n\
						6) Przekaz punkty premium\
					",
				"Dalej", "Wroc");
			}
		}
		return _TRUE;
	}
	return _FALSE;
}
//---------------------------------------------------------------
ActivateVIPPrivilages(playerid, bool:confirm = false) {
	if(getPlayerLoginStatus(playerid) == LOGIN_STATUS_LOGGED) {	
		new vipCost, playerVipPoints = GetPlayerVIPPoints(playerid), playerVipBonusPoints = GetPlayerVIPBonusPoints(playerid),vipDays, head[40], year, month, day, hour, minute;
		new string[600];
		switch((vipDays = GetHelpVarValue(playerid, 0))) {
			case 3: {
				if((vipCost = getSettingIntValueByIndex(s_VIP3DaysCostID)) == 0) ShowPlayerInfoDialog(playerid, BACK_PLAYER_ACC_VIP_MENU, "Konto VIP - Aktywuj VIP na 3 dni", "Aktualnie system ma wylaczona opcje aktywacji konta VIP na 3 dni.");		
			}
			case 7: {
				if((vipCost = getSettingIntValueByIndex(s_VIP7DaysCostID)) == 0) ShowPlayerInfoDialog(playerid, BACK_PLAYER_ACC_VIP_MENU, "Konto VIP - Aktywuj VIP na 7 dni", "Aktualnie system ma wylaczona opcje aktywacji konta VIP na 7 dni.");		
			}
			case 30: {
				if((vipCost = getSettingIntValueByIndex(s_VIP30DaysCostID)) == 0) ShowPlayerInfoDialog(playerid, BACK_PLAYER_ACC_VIP_MENU, "Konto VIP - Aktywuj VIP na 30 dni", "Aktualnie system ma wylaczona opcje aktywacji konta VIP na 30 dni.");				
			}
			default: return PlayerAccountVIPSettings(playerid, -1);
		}
		
		
		new vipTime = ((GetPlayerVIPTime(playerid) > timestamp() ? GetPlayerVIPTime(playerid) : timestamp()) + ToSeconds(vipDays, _DAY));
		dtimestamp(vipTime, year, month, day, hour, minute);
		if(confirm == true) {
			if(playerVipPoints >= vipCost) {
				new takeBonusPoints;
				new takePlayerPoints;
				if(playerVipBonusPoints > 0) {
					if(playerVipBonusPoints >= vipCost) {
						takeBonusPoints = vipCost;
						takePlayerPoints = 0;
						format(string, sizeof(string), "UPDATE `"T_KONTA"` SET `"TK_PREMIUM_DATE"`='%d', `"TK_PREMIUM_BONUS_POINT"`="TK_PREMIUM_BONUS_POINT"-%d WHERE `"TK_UID"`='%d'", vipTime, vipCost, getPlayerUserID(playerid));
					} else {
						takeBonusPoints = playerVipBonusPoints;
						takePlayerPoints = vipCost - playerVipBonusPoints;
						format(string, sizeof(string), "UPDATE `"T_KONTA"` SET `"TK_PREMIUM_DATE"`='%d', `"TK_PREMIUM_BONUS_POINT"`='0', `"TK_PREMIUM_PLAYER_POINT"`="TK_PREMIUM_PLAYER_POINT"-%d WHERE `"TK_UID"`='%d'", vipTime, takePlayerPoints, getPlayerUserID(playerid));
					}				
				} else {
					takeBonusPoints = 0;
					takePlayerPoints = vipCost;
					format(string, sizeof(string), "UPDATE `"T_KONTA"` SET `"TK_PREMIUM_DATE"`='%d', `"TK_PREMIUM_PLAYER_POINT"`="TK_PREMIUM_PLAYER_POINT"-%d WHERE `"TK_UID"`='%d'", vipTime, vipCost, getPlayerUserID(playerid));					
				}
				sendQueryWithout(string);
				format(string, sizeof(string), "Gracz aktywowal konto VIP na okres %d dni za %d punktow premium w tym %d punktow wlasnych, %d punktow bonusowych.", vipDays, vipCost, takePlayerPoints, takeBonusPoints);
				AddToPlayerLog(getPlayerUserID(playerid), string);
				format(string, sizeof(string), "Gracz %s (UID: %d) aktywowal konto VIP na okres %d dni za %d punktow premium w tym %d punktow wlasnych, %d punktow bonusowych.", getPlayerName(playerid), getPlayerUserID(playerid), vipDays, vipCost, takePlayerPoints, takeBonusPoints);
				AddToVIPLog(string);
				format(string, sizeof(string), 
						"\t\t      Konto VIP na "C_WHITE"%d dni "TEXT_DIALOG_HEAD"zostalo aktywowane.\nOdebrano "C_WHITE"%d "TEXT_DIALOG_HEAD"punktow premium w tym "C_WHITE"%d "TEXT_DIALOG_HEAD"punktow bonusowych i "C_WHITE"%d "TEXT_DIALOG_HEAD"punktow gracza.\n\t      Konto VIP bedzie aktywne do "C_WHITE"%s  "TEXT_DIALOG_HEAD"[ "C_WHITE"%d:%02d"TEXT_DIALOG_HEAD" ]", 
					vipDays, vipCost, takeBonusPoints, takePlayerPoints, strData(year, month, day, " / ", false, false, true, false), hour, minute
				);
				format(head, sizeof(head), "Konto VIP - Aktywuj VIP na %d dni", vipDays);
				TakePlayerSelfPoints(playerid, takePlayerPoints);
				TakePlayerBonusPoints(playerid, takeBonusPoints);
				SetPlayerVIPTime(playerid, vipTime);
				
				ShowPlayerInfoDialog(playerid, BACK_PLAYER_ACC_VIP_MENU, head, string);		
				return _TRUE;
			} else strins(string, C_ADMIN"\t\t\tMasz za malo punktow premium do aktywacji konta VIP.", 0);
		}
		
		format(string, sizeof(string),"\
 				\t\tAktualnie posiadasz "C_WHITE"%d"TEXT_DIALOG_HEAD" punktow punktow premium, w tym "C_WHITE"%d"TEXT_DIALOG_HEAD" bonusowych.\n\n\
				\t\t\t\t    Czy chcesz aktywowac konto VIP?\n\n\
				%s",
			playerVipPoints, playerVipBonusPoints, string
		);
		
		format(string, sizeof(string), "\
				\t       Aktywacja konta VIP na serwerze na okres "C_WHITE"%d dni "TEXT_DIALOG_HEAD"kosztuje "C_WHITE"%d"TEXT_DIALOG_HEAD" punktow premium.\
				\nW przypadku kiedy posiadasz bonusowe punkty premium, beda one odbierane w pierwszej kolejnosci.\
				\nJesli teraz zdecydujesz sie aktywowac konto VIP, bedzie ono aktywne do "C_WHITE"%s  "TEXT_DIALOG_HEAD"[ "C_WHITE"%d:%02d "TEXT_DIALOG_HEAD"].\n\
				%s",
			vipDays, vipCost, strData(year, month, day, " / ", false, false, true, false), hour, minute, string
		);		
		
		format(head, sizeof(head), "Konto VIP - Aktywuj VIP na %d dni", vipDays);
		ShowPlayerDialogEx(playerid, DIALOG_PLAYER_VIP_ACTIVATE, DIALOG_STYLE_MSGBOX, head, string, "Aktywuj", "Wroc");		
		return _TRUE;
	}
	return _FALSE;
}
//---------------------------------------------------------------
SendPremiumPointsValue(playerid, s_value[] = "") {
	if(getPlayerLoginStatus(playerid) == LOGIN_STATUS_LOGGED) {	
		new maxValue = GetPlayerVIPSelfPoints(playerid) > 9999 ? 9999 : GetPlayerVIPSelfPoints(playerid);
		new string[256];
		if(!isnull(s_value) and strlen(s_value) <= 4) {
			new value;
			if(isNumeric(s_value) and 0 < (value = strval(s_value)) <= maxValue) {
				SetHelpVarValue(playerid, 0, value);
				SendPremiumPointsPlayer(playerid);
				return _TRUE;
			} else strins(string, "\t\t      Niepoprawna ilosc punktow do wyslania.", 0);
		}
		
		format(string, sizeof(string), "Podaj ilosc punktow premium (wlasnych), ktore chcesz przekazac innemu graczu.\n          W tym momencie mozesz wyslac maksymalnie "C_WHITE"%d "TEXT_DIALOG_HEAD"punktow premium.\n\n"C_ADMIN"%s", maxValue, string);
		ShowPlayerDialogEx(playerid, DIALOG_PLAYER_VIP_SENDPOINTS, DIALOG_STYLE_INPUT, "Konto VIP - Przekaz punkty premium", string, "Aktywuj", "Wroc");			
		return _TRUE;
	}
	return _FALSE;
}
//---------------------------------------------------------------
SendPremiumPointsPlayer(playerid, s_player[] = "") {
	if(getPlayerLoginStatus(playerid) == LOGIN_STATUS_LOGGED) {	
		new string[140];
		if(!isnull(s_player) and strlen(s_player) <= 6) {
			new userid;
			if(isNumeric(s_player) and 0 < (userid = strval(s_player)) <= 999999) {				
				if(getPlayerUserID(playerid) != userid) {
					if(IsUserIDRegistered(userid) == _TRUE) {
						SetHelpVarValue(playerid, 1, userid);
						SendPremiumPointsConfirm(playerid);
						return _TRUE;
					} else strins(string, "     Gracz o podanym User ID nie jest zarejestrowany.", 0);
				} else strins(string, "         Nie mozesz byc odbiorca punktow premium.", 0);
			} else strins(string, "\t      Niepoprawne User ID odbiorcy.", 0);
		}		
		format(string, sizeof(string), "Podaj indywidualne "C_WHITE"User ID "TEXT_DIALOG_HEAD"odbiorcy punktow premium.\n\n"C_ADMIN"%s", string);
		ShowPlayerDialogEx(playerid, DIALOG_PLAYER_VIP_SENDUSER, DIALOG_STYLE_INPUT, "Konto VIP - Przekaz punkty premium", string, "Aktywuj", "Wroc");	
		return _TRUE;
	}
	return _FALSE;
}
//---------------------------------------------------------------
SendPremiumPointsConfirm(playerid, bool:confirm = false) {

	if(getPlayerLoginStatus(playerid) == LOGIN_STATUS_LOGGED) {	
		new userid = GetHelpVarValue(playerid, 1);
		new premiumPoints = GetHelpVarValue(playerid, 0);
		new userName[MAX_PLAYER_NAME];
		new string[256];
		
		strins(userName, GetNickByUserID(userid), 0);
		if(strcmp(userName, "*System*", true) != 0) {
			if(premiumPoints <= GetPlayerVIPSelfPoints(playerid)) {
				if(confirm == true) {
					format(string, sizeof(string), "UPDATE `"T_KONTA"` SET `"TK_PREMIUM_PLAYER_POINT"`="TK_PREMIUM_PLAYER_POINT"-%d WHERE `"TK_UID"`='%d'", premiumPoints, getPlayerUserID(playerid));
					sendQueryWithout(string);
					format(string, sizeof(string), "UPDATE `"T_KONTA"` SET `"TK_PREMIUM_PLAYER_POINT"`="TK_PREMIUM_PLAYER_POINT"+%d WHERE `"TK_UID"`='%d'", premiumPoints, userid);
					sendQueryWithout(string);
					
					format(string, sizeof(string), " (Punkty Premium) Gracz %s wyslal Ci %d punktow premium.", getPlayerName(playerid), premiumPoints);
					forplayers(i) {
						if(getPlayerUserID(i) == userid) {
							SendClientMessage(i, COLOR_GOLD, string);
							AddPlayerSelfPoints(i, premiumPoints);
							break;
						}
					}
					format(string, sizeof(string), "Gracz %s (User ID: %d) wyslal %d punktow premium na konto gracza.", getPlayerName(playerid), getPlayerUserID(playerid), premiumPoints);
					AddToPlayerLog(userid, string);

					
					TakePlayerSelfPoints(playerid, premiumPoints);
					format(string, sizeof(string), "Gracz wyslal %d punktow premium na konto gracza %s (User ID: %d).", premiumPoints, userName, userid);
					AddToPlayerLog(getPlayerUserID(playerid), string);
					
					format(string, sizeof(string), "Gracz %s (UID: %d) wyslal %d punktow premium na konto gracza %s (UID: %d).", getPlayerName(playerid), getPlayerUserID(playerid), premiumPoints, userName, userid);
					AddToVIPLog(string);
					
					format(string, sizeof(string), "Przekazales "C_WHITE"%d "TEXT_DIALOG_HEAD"punktow premium graczu "C_WHITE"%s "TEXT_DIALOG_HEAD"(User ID: "C_WHITE"%d"TEXT_DIALOG_HEAD").", premiumPoints, userName, userid);
					ShowPlayerInfoDialog(playerid, BACK_PLAYER_ACC_VIP_MENU, "Konto VIP - Przekaz punkty premium", string);
				} else {				
					format(string, sizeof(string), "Czy na pewno chcesz przekazac "C_WHITE"%d "TEXT_DIALOG_HEAD"punktow premium graczu "C_WHITE"%s "TEXT_DIALOG_HEAD"(User ID: "C_WHITE"%d"TEXT_DIALOG_HEAD")?", premiumPoints, userName, userid);
					ShowPlayerYesNoDialog(playerid, D_YESNO_PREMIUM_SEND, "Konto VIP - Przekaz punkty premium", string);	
				}
			} else ShowPlayerInfoDialog(playerid, BACK_PLAYER_ACC_VIP_MENU, "Konto VIP - Przekaz punkty premium", "Ilosc Twoich punktow premium nie jest wystarczajaca do wykonania operacji przekazania.");
		} else ShowPlayerInfoDialog(playerid, BACK_PLAYER_ACC_VIP_MENU, "Konto VIP - Przekaz punkty premium", "Wybrane User ID gracza przestalo byc aktywne (byc moze konto zostalo usuniete).");
		return _TRUE;
	}
	return _FALSE;
}
//---------------------------------------------------------------
forward RemoteAddRemBonusPP(userid, value);
public RemoteAddRemBonusPP(userid, value) {
	if(99999999 >= userid > 0 and 9999 >= value >= -9999) {
		if(IsUserIDRegistered(userid) == _TRUE) {
			new string[128];
			format(string, sizeof(string), "UPDATE `"T_KONTA"` SET `"TK_PREMIUM_BONUS_POINT"`="TK_PREMIUM_BONUS_POINT"+%d WHERE `"TK_UID"`='%d'", value, userid);
			sendQueryWithout(string);
			format(string, sizeof(string), "Gracz otrzymal bonusowe punkty premium w ilosci %d (Remote Function).", value);
			AddToPlayerLog(userid, string);
			format(string, sizeof(string), "Gracz o UserID: %d otrzymal bonusowe punkty premium w ilosci %d (Remote Function).", userid, value);
			AddToVIPLog(string);			
			return _TRUE;
		}
	}
	return -1;
}