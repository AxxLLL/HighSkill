/*

*/
//===============================================================
//---------------------------------------------------------------
//===============================================================
#define	MIN_PASSWORD_LEN	6
#define	MAX_PASSWORD_LEN	16

//===============================================================
#define IsValidUserID(%1) IsValidUID(%1)
IsValidUID(uid) {
	return uid >= 1 ? _TRUE : _FALSE;
}
//---------------------------------------------------------------
IsValidPassword(password[]) {
	new length;
	if(MAX_PASSWORD_LEN >= (length = strlen(password)) >= MIN_PASSWORD_LEN) {
		new special_chars, normal_chars;
		for(-- length; length >= 0; length --) {
			switch(password[length]) {
				case 'a'..'z', 'A'..'Z': normal_chars ++;
				case '0'..'9', '!', '@', '#', '$': special_chars ++;
				default: return _FALSE;
			}
			if(normal_chars >= 3 and special_chars >= 3) return _TRUE;
		}
	}
	return _FALSE;
}
//---------------------------------------------------------------
IsNickRegistered(nick[]) {
	new userID = 0;
	new conNick[MAX_PLAYER_NAME];
	strins(conNick, nick, 0);
	if(ConvertNick(conNick) == _TRUE) {
		new string[128], DBResult: result, Result:sql_result;
		format(string, sizeof(string), "SELECT `"TK_UID"` FROM `"T_KONTA"` WHERE `"TK_NICK"` = '%s' LIMIT 1", conNick);
		result = sendQueryResult(string, sql_result);
		if(numRows(result, sql_result) > 0) {
			userID = strval(getFieldAssoc_16(TK_UID, result, sql_result));
			freeResult(result, sql_result);	
		}
	}
	return IsValidUID(userID) == _FALSE ? 0 : userID;
}
//---------------------------------------------------------------
IsUserIDRegistered(userid) {
	new DBResult: result, Result:sql_result, string[128];
	format(string, sizeof(string), "SELECT `"TK_UID"` FROM `"T_KONTA"` WHERE `"TK_UID"`='%d' LIMIT 1", userid);
	result = sendQueryResult(string, sql_result);
	if(numRows(result, sql_result) > 0) {
		freeResult(result, sql_result);
		return _TRUE;
	}
	return _FALSE;
}
//---------------------------------------------------------------
GetNickByUserID(userid) {
	new nick[MAX_PLAYER_NAME] = "*System*";
	if(IsValidUID(userid)) {
		new string[64];
		new DBResult: result, Result:sql_result;
		format(string, sizeof(string), "SELECT `"TK_NICK"` FROM `"T_KONTA"` WHERE `"TK_UID"`='%d' LIMIT 1", userid);
		result = sendQueryResult(string, sql_result);
		if(numRows(result, sql_result) > 0) {
			strdel(nick, 0, MAX_PLAYER_NAME);
			strins(nick, getFieldAssoc_32(TK_NICK, result, sql_result), 0);
			DeconvertNick(nick);
			freeResult(result, sql_result);
		}
	}
	return nick;
}
//---------------------------------------------------------------
AddNewAccount(nick[], password[], bool:forcepassword, registerip[], registergpci[]) {
	if(IsValidNick(nick) and (IsValidPassword(password) or forcepassword == true)) {
		if(IsNickRegistered(nick) == _FALSE) {
			new string[512], t_stamp = timestamp();
			new conNick[MAX_PLAYER_NAME];
			new DBResult: result, Result:sql_result;
			new user_id;
			strins(conNick, nick, 0);
			ConvertNick(conNick);
			format(string, sizeof(string),"INSERT INTO `"T_KONTA"` \
					(`"TK_NICK"`,\
					`"TK_PASSWORD"`,\
					`"TK_RESET_PASSWORD"`,\
					`"TK_REGISTER_STAMP"`,\
					`"TK_REGISTER_IP"`,\
					`"TK_REGISTER_GPCI"`,\
					`"TK_DELETE_STAMP"`,\
					`"TK_PROV_CONFIDENTAL"`,\
					`"TK_PREMIUM_DATE"`,\
					`"TK_PREMIUM_BONUS_POINT"`\
					) "
			);
			format(string, sizeof(string), "%s\
				VALUES \
					('%s', '%d', '%d', '%d', '%s', '%s', '%d', '%d', '%d', '%d');", 
				string,
				conNick, 
				Hash(password), 
				forcepassword == true ? 1 : 0,
				t_stamp, 
				registerip,
				registergpci,
				t_stamp + (ToSeconds(getSettingIntValueByIndex(s_LoginDeletingDaysID), _DAY)), 
				t_stamp + (ToSeconds(getSettingIntValueByIndex(s_ProvConfiRegisterID), _HOUR)),
				t_stamp + (ToSeconds(getSettingIntValueByIndex(s_VIPRegisterTimeID), _DAY)),
				getSettingIntValueByIndex(s_VIPRegisterPointsID)
			);
			sendQueryWithout(string);
			
			format(string, sizeof(string),"SELECT `"TK_UID"` FROM `"T_KONTA"` WHERE `"TK_NICK"`='%s' LIMIT 1", conNick);
			result = sendQueryResult(string, sql_result);			
			user_id = strval(getFieldAssoc_8(TK_UID, result, sql_result));				
			freeResult(result, sql_result);
			AddToPlayerLog(user_id, "Zarejestrowano konto");
			format(string, sizeof(string),"[Rejestracja] Zarejestrowano nowe konto '%s'. User ID: %d", nick, user_id);
			AddToChatLog(string);
			
			CallLocalFunction("OnNewAccountRegistered", "d", user_id);
			
			if(getSettingIntValueByIndex(s_VIPRegisterTimeID) > 0) {
				format(string, sizeof(string), "Gracz otrzymal gratisowe konto VIP po rejestracji na serwerze na okres %d dni.", getSettingIntValueByIndex(s_VIPRegisterTimeID));
				AddToPlayerLog(user_id, string);
				format(string, sizeof(string), "Gracz %s (UID: %d) otrzymal gratisowe konto VIP na okres %d dni za rejestracje na serwerze.", nick, user_id, getSettingIntValueByIndex(s_VIPRegisterTimeID));
				AddToVIPLog(string);
			}
			if(getSettingIntValueByIndex(s_VIPRegisterPointsID) > 0) {
				format(string, sizeof(string), "Gracz otrzymal gratisowe punkty premium w ilosci %d za rejestracje na serwerze.", getSettingIntValueByIndex(s_VIPRegisterPointsID));
				AddToPlayerLog(user_id, string);
				format(string, sizeof(string), "Gracz %s (UID: %d) otrzymal gratisowe punkty premium w ilosci %d za rejestracje na serwerze.", nick, user_id, getSettingIntValueByIndex(s_VIPRegisterPointsID));
				AddToVIPLog(string);
			}						
			return user_id;
		} else return -1;
	}
	return 0;
}
//===============================================================
//---------------------------------------------------------------
//===============================================================
CheckDataToRegister(s_ip[], s_gpci[]) {
	if(IsValidIP(s_ip) == _TRUE and IsValidGPCI(s_gpci) == _TRUE) {
		new string[150], s_stamp = timestamp() - ToSeconds(getSettingIntValueByIndex(s_RegisterMinTimeID), _MINUTE);
		new DBResult: result, Result:sql_result, numrows;
		//-------------------------------
		format(string, sizeof(string), "SELECT `"TK_UID"` FROM `"T_KONTA "` WHERE `"TK_REGISTER_IP"`='%s' AND `"TK_REGISTER_STAMP"` >= '%d' LIMIT 1", s_ip, s_stamp);
		result = sendQueryResult(string, sql_result);
		numrows = numRows(result, sql_result);
		freeResult(result, sql_result);
		if(numrows > 0) return 1;
		else {
			format(string, sizeof(string), "SELECT `"TK_UID"` FROM `"T_KONTA "` WHERE (`"TK_REGISTER_IP"` LIKE '%s.%%' AND `"TK_REGISTER_GPCI"`='%s') AND `"TK_REGISTER_STAMP"` >= '%d' LIMIT 1", GetHostFromIP(s_ip), s_gpci, s_stamp);
			result = sendQueryResult(string, sql_result);
			numrows = numRows(result, sql_result);
			freeResult(result, sql_result);
			if(numrows > 0) return 2;		
			
			format(string, sizeof(string), "SELECT `"TK_UID"` FROM `"T_KONTA "` WHERE (`"TK_REGISTER_IP"` LIKE '%s.%%' OR `"TK_REGISTER_GPCI"`='%s') AND `"TK_REGISTER_STAMP"` >= '%d' LIMIT 1", GetHostFromIP(s_ip), s_gpci, s_stamp);
			result = sendQueryResult(string, sql_result);
			numrows = numRows(result, sql_result);
			freeResult(result, sql_result);
			if(numrows > 0) return 3;				
			
			s_stamp = timestamp() - 43200; // ost. 12 godzin
			format(string, sizeof(string), "SELECT `"TK_UID"` FROM `"T_KONTA "` WHERE `"TK_REGISTER_IP"` = '%s' AND `"TK_REGISTER_STAMP"` >= '%d' LIMIT 1", s_ip, s_stamp);
			result = sendQueryResult(string, sql_result);
			numrows = numRows(result, sql_result);
			freeResult(result, sql_result);		
			if(numrows > 0) return 4;		
		}
		//-------------------------------
	}
	return 0;
}
//---------------------------------------------------------------
CheckSimilarRegisterNick(nick[]) {
	new conNick[MAX_PLAYER_NAME];
	strins(conNick, nick, 0);
	if(ConvertNick(conNick) == _TRUE) {
		new string[128];
		new DBResult: result, Result:sql_result;
		format(string, sizeof(string), "SELECT `"TK_UID"` FROM `"T_KONTA"` WHERE `"TK_NICK"` LIKE '%s' LIMIT 1", conNick);
		result = sendQueryResult(string, sql_result);			
		if(numRows(result, sql_result) > 0) {
			freeResult(result, sql_result);	
			return _TRUE;
		}
	}
	return _FALSE;
}
//===============================================================
//---------------------------------------------------------------
//===============================================================
CMD:register(playerid) return cmd_zarejestruj(playerid);
CMD:zarejestruj(playerid) {
	PlayerRegisterAccount(playerid);
	return _TRUE;
}
//---------------------------------------------------------------
PlayerRegisterAccount(playerid, password[] = "") {
	if(getPlayerLoginStatus(playerid) == LOGIN_STATUS_NOTREGISTERED) {
		if(getSettingIntValueByIndex(s_RegisterObligatoryID) != 2) {
			new string[800];
			new p_name[MAX_PLAYER_NAME];
			GetPlayerName(playerid, p_name, sizeof(p_name));		
			if(!isnull(password)) {
				if(GetBanUniqueID(B_NICK, p_name) == 0) {
					new s_gpci[64], testing, p_ip[16];
					GetPlayerIp(playerid, p_ip, sizeof(p_ip));
					gpci(playerid, s_gpci, 64);
					if((testing = CheckDataToRegister(p_ip, s_gpci)) != 1) { 
						if(CheckSimilarRegisterNick(p_name) == _FALSE) {
							if(testing != 0){
								format(string, sizeof(string), "Istnieje prawdopodobienswo proby rejestracji multikonta przez gracza '%s' (IP: %s | GPCI: %s | KOD: %d)", p_name, p_ip, s_gpci, testing);
								AddToMultiAccountInfoLog(string);
								strdel(string, 0, 800);
							}						
					
							new userID;
							switch((userID = AddNewAccount(p_name, password, false, p_ip, s_gpci))) {
								case -1: 	strins(string, "\n\n"TEXT_DIALOG_ALERT"Konto o takiej nazwie jest juz zarejestrowane w systemie.", 0);
								case 0: 	strins(string, "\n\n"TEXT_DIALOG_ALERT"   Haslo musi zawierac sie w przedziale od "#MIN_PASSWORD_LEN" do "#MAX_PASSWORD_LEN" symboli\n     i musi zawierac co najmniej 3 litery i 3 znaki specjalne.", 0);
								default: {	
									if(setPlayerUserID(playerid, userID) == _TRUE) {
										new t_stamp = timestamp();
										
										SetPVarInt(playerid, 	PV_LOGIN_LAST_LOGIN_STAMP, 	t_stamp);
										SetPVarString(playerid, PV_LOGIN_LAST_LOGIN_GPCI, 	s_gpci);
										SetPVarString(playerid, PV_LOGIN_LAST_LOGIN_IP, 	p_ip);
										SetPVarInt(playerid, 	PV_LOGIN_REGISTER_STAMP, 	t_stamp);
										SetPVarInt(playerid, 	PV_LOGIN_DELETE_STAMP, 		t_stamp + (ToSeconds(getSettingIntValueByIndex(s_LoginDeletingDaysID), _DAY)));						
										SetPVarInt(playerid, 	PV_LOGIN_PASSWORD,			Hash(password));
										
										
										format(string, sizeof(string), "  {F37572}Gratulacje, Twoj nick zostal poprawnie zarejestrowany na serwerze!\n\n\
											"TEXT_DIALOG_HEAD"  Od teraz przy kazdym wejsciu bedziesz proszony(a) o podanie hasla\n\
											\t\t\t      dostepu do konta.\n");
										format(string, sizeof(string), "%s\n\
											"TEXT_DIALOG_ALERT"\t\t\t___Dane do logowania___\n\
											"TEXT_DIALOG_HEAD"\t\t\t      Nick: "TEXT_DIALOG_NORMAL"%s\n\
											"TEXT_DIALOG_HEAD"\t\t\t      Haslo: "TEXT_DIALOG_NORMAL"%s\n\n\
											"TEXT_DIALOG_HEAD"\t     Wpisz komende \""TEXT_DIALOG_NORMAL"/konto"TEXT_DIALOG_HEAD"\" zeby zobaczyc opcje konta.\n\n\
											Zyczymy przyjemnej gry na naszym serwerze - Administracja serwera", 
										string, p_name, password);		
								
										setPlayerLoginStatus(playerid, LOGIN_STATUS_LOGGED);
										ShowPlayerInfoDialog(playerid, -1, "Rejestracja konta", string);	
										
										if(getSettingIntValueByIndex(s_VIPRegisterTimeID) > 0) {									
											SetPlayerVIPTime(playerid, timestamp() + ToSeconds(getSettingIntValueByIndex(s_VIPRegisterTimeID), _DAY));
											format(string, sizeof(string), " (Konto VIP) Otrzymales(as) bonusowe "C_WHITE"%d dni "C_GOLD"konta VIP.", getSettingIntValueByIndex(s_VIPRegisterTimeID));
											SendClientMessage(playerid, COLOR_GOLD, string);
										}
										if(getSettingIntValueByIndex(s_VIPRegisterPointsID) > 0) {
											AddPlayerBonusPoints(playerid, getSettingIntValueByIndex(s_VIPRegisterPointsID));
											format(string, sizeof(string), " (Konto VIP) Otrzymales(as) "C_WHITE"%d "C_GOLD"bonusowych punktow premium.", getSettingIntValueByIndex(s_VIPRegisterPointsID));
											SendClientMessage(playerid, COLOR_GOLD, string);
										}									
										return _TRUE;
									} else {
										SendClientMessage(playerid, 0xFF0000FF, "(Register-Error [001]) Wystapil blad podczas rejestracji. Prosimy zglosic jak najszybciej problem do administracji serwera (C-RS-001).");
										SendClientMessage(playerid, 0xFF0000FF, "  Info: Rejestracja konta nie powiodla sie, sprobuj ponownie pozniej.");
										format(string, sizeof(string),"[C-RS-001] Wystapil problem podczas rejestracji nicku '%s'. Zwrocone User ID: %d.", p_name, userID);
										OnFunctionGetError("RegisterSystem", string);
									}
								}	
							}	
						} else strins(string, "\n\n"TEXT_DIALOG_ALERT"Na serwerze jest zarejestrowany nick z taka sama kombinacja znakow jak Twoj.", 0); 
					} else strins(string, "\n\n"TEXT_DIALOG_ALERT"Z tego IP zarejestrowano w niedawnym czasie konto, sprobuj pozniej.", 0);
				} else strins(string, "\n\n"TEXT_DIALOG_ALERT"Twoj nick zostal zbanowany w systemie, nie mozesz go teraz zarejestrowac.", 0);
			}
			
			format(string, sizeof(string), "\nPodaj haslo dzieki ktoremu bedziesz mogl(a) logowac sie na\nswoje konto. Haslo powinno skladac sie z od %d do %d znakow\noraz musi zawierac co najmniej 3 litery i 3 znak i specjalne\n\t\t(cyfry lub symbole '!', '@', '#', '$').%s", MIN_PASSWORD_LEN, MAX_PASSWORD_LEN, string);
			format(string, sizeof(string),"\t\t{F37572}Witaj na serwerze "TEXT_DIALOG_NORMAL"%s{F37572}.\n\n"TEXT_DIALOG_HEAD"Rejestrujac nowe konto otrzymasz szereg przywilejow dzieki\nktorym bedziesz mogl(a) korzystac z wiekszej ilosci funkcji.\n\t\t        ktore oferuje serwer.\nPamietaj, ze rejestracja konta jest rownoznaczna z akceptacja\nregulaminu serwera, wraz z pozniejszymi zmianami! Regulamin\n\t       mozesz znalezc na stronie WWW serwera.\n%s",	p_name, string);
			if(getSettingIntValueByIndex(s_RegisterObligatoryID) == 1) {
				format(string, sizeof(string),TEXT_DIALOG_ALERT"       Rejestracja konta jest konieczna do gry na serwerze!\n\n%s", string);		
			}
			ShowPlayerDialogEx(playerid, DIALOG_REGISTER, DIALOG_STYLE_INPUT, "Rejestracja konta", string, "Zarejestruj", "Wyjdz");
		} else SendClientMessage(playerid, COLOR_DIALOG_BODY, " (Rejestracja) Rejestracja kont na serwerze zostala wylaczona.");
		return _TRUE;			
	}
	return _FALSE;
}