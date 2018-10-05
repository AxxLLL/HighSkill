/*
________________________________________________________________


________________________________________________________________
*/
//===============================================================
//---------------------------------------------------------------
//===============================================================
new g_LoginTimer[MAX_PLAYERS];									// Timer resetowany po: zalogowaniu sie, wyjsciu z serwera, ponownym pierwszym wywolaniu okna logowania.
//---------------------------------------------------------------
forward OnPlayerLoginStatusChange(playerid, newstatus, oldstatus);
//===============================================================
//---------------------------------------------------------------
//===============================================================
#define GetPlayerLoginStatus(%1) getPlayerLoginStatus(%1)
getPlayerLoginStatus(playerid) return GetPVarInt(playerid, PV_LOGIN_STATUS);
//---------------------------------------------------------------
#define SetPlayerLoginStatus(%1,%2) setPlayerLoginStatus(%1, %2)
setPlayerLoginStatus(playerid, status) {
	if(LOGIN_STATUS_NON <= status <= LOGIN_STATUS_LOGGED) {
		new oldstatus;
		if(status != (oldstatus = GetPVarInt(playerid, PV_LOGIN_STATUS))) {
			SetPVarInt(playerid, PV_LOGIN_STATUS, status);
			CallLocalFunction("OnPlayerLoginStatusChange", "ddd", playerid, status, oldstatus);
			SetTimerEx("CallLoginStatusCange", 2000, 0, "ddd", playerid, status, oldstatus);
			return _TRUE;
		}
	}
	return _FALSE;
}
//---------------------------------------------------------------
forward CallLoginStatusCange(playerid, status, oldstatus);
public CallLoginStatusCange(playerid, status, oldstatus) CallRemoteFunction("AS_OnPlayerLoginStatusChange", "ddd", playerid, status, oldstatus);
//===============================================================
//---------------------------------------------------------------
//===============================================================
#define GetPlayerUserID(%1)	getPlayerUserID(%1)
getPlayerUserID(playerid) return GetPVarInt(playerid, PV_LOGIN_USERID);
//---------------------------------------------------------------
#define SetPlayerUserID(%1,%2) setPlayerUserID(%1, %2)
setPlayerUserID(playerid, userid) {
	if(IsPlayerConnected(playerid) and (IsValidUID(userid) or userid == 0)) {
		SetPVarInt(playerid, PV_LOGIN_USERID, userid);
		return _TRUE;
	}
	return _FALSE;
}
//---------------------------------------------------------------
isPlayerConfidental(playerid) {
	if(IsValidUID(getPlayerUserID(playerid)) == _TRUE) {
		return GetPVarInt(playerid, PV_LOGIN_PLAY_TIME) > ToSeconds(getSettingIntValueByIndex(s_LoginConfiID), _HOUR) ? _TRUE: _FALSE;
	}
	return _FALSE;
}
//---------------------------------------------------------------
isPlayerProvConfidental(playerid) {
	if(IsValidUID(getPlayerUserID(playerid)) == _TRUE) {
		return GetPVarInt(playerid, PV_LOGIN_PROV_CONFIDENTAL) > timestamp() ? _TRUE: _FALSE;
	}
	return _FALSE;
}
//===============================================================
ConnectLoadPlayerData(playerid, nick[]) {
	new string[128], DBResult: result, Result:sql_result;
	new conNick[MAX_PLAYER_NAME];
	strins(conNick, nick, 0);
	ConvertNick(conNick);
	format(string, sizeof(string),	"SELECT * FROM `"T_KONTA"` WHERE `"TK_NICK"`='%s' LIMIT 1", conNick);	
	result = sendQueryResult(string, sql_result);

	if(numRows(result, sql_result) > 0) {
		setPlayerUserID(playerid, strval(getFieldAssoc_16(TK_UID, result, sql_result)));
		SetPVarInt(playerid, PV_LOGIN_PASSWORD, 			strval(getFieldAssoc_32(TK_PASSWORD, result, sql_result)));
		SetPVarInt(playerid, PV_LOGIN_RESET_PASSWORD, 		strval(getFieldAssoc_32(TK_RESET_PASSWORD, result, sql_result)));
		SetPVarInt(playerid, PV_LOGIN_REGISTER_STAMP, 		strval(getFieldAssoc_32(TK_REGISTER_STAMP, result, sql_result)));
		SetPVarString(playerid, PV_LOGIN_REGISTER_IP, 		getFieldAssoc_16(TK_REGISTER_IP, result, sql_result));
		SetPVarInt(playerid, PV_LOGIN_RCON_ADMIN,			strval(getFieldAssoc_8(TK_RCON_ADMIN, result, sql_result)));
		
		SetPVarInt(playerid, PV_LOGIN_ADMIN_LVL, 			strval(getFieldAssoc_16(TK_ADMIN_LVL, result, sql_result)));
		SetPVarInt(playerid, PV_LOGIN_ADMIN_PASSWORD,		strval(getFieldAssoc_32(TK_ADMIN_PASSWORD, result, sql_result)));
		SetPVarInt(playerid, PV_LOGIN_ADMIN_STAMP, 			strval(getFieldAssoc_32(TK_ADMIN_STAMP, result, sql_result)));
		SetPVarInt(playerid, PV_LOGIN_DELETE_STAMP, 		strval(getFieldAssoc_32(TK_DELETE_STAMP, result, sql_result)));
		SetPVarInt(playerid, PV_LOGIN_LAST_LOGIN_STAMP,		strval(getFieldAssoc_32(TK_LAST_LOGIN_STAMP, result, sql_result)));
		SetPVarString(playerid, PV_LOGIN_LAST_LOGIN_IP, 	getFieldAssoc_32(TK_LAST_LOGIN_IP, result, sql_result));
		SetPVarString(playerid, PV_LOGIN_LAST_LOGIN_GPCI, 	getFieldAssoc_64(TK_LAST_LOGIN_GPCI, result, sql_result));
		
		strdel(conNick, 0, 24);
		strins(conNick, getFieldAssoc_32(TK_LAST_NICK, result, sql_result), 0);
		DeconvertNick(conNick);
		SetPVarString(playerid, PV_LOGIN_LAST_NICK, 		conNick);		
		
		SetPVarInt(playerid, PV_LOGIN_LAST_NICK_STAMP, 		strval(getFieldAssoc_32(TK_LAST_NICK_STAMP, result, sql_result)));
		SetPVarInt(playerid, PV_LOGIN_PLAY_TIME, 			strval(getFieldAssoc_32(TK_PLAY_TIME, result, sql_result)));	
		SetPVarInt(playerid, PV_LOGIN_PROV_CONFIDENTAL, 	strval(getFieldAssoc_32(TK_PROV_CONFIDENTAL, result, sql_result)));
		SetPVarInt(playerid, PV_LOGIN_BAN_TIME,				strval(getFieldAssoc_32(TK_BAN_TIME, result, sql_result)));
		SetPVarInt(playerid, PV_LOGIN_BAN_ADMIN_ID,			strval(getFieldAssoc_32(TK_BAN_ADMIN_ID, result, sql_result)));
		SetPVarString(playerid, PV_LOGIN_BAN_REASON,		getFieldAssoc_128(TK_BAN_REASON, result, sql_result));
		SetPVarInt(playerid, PV_LOGIN_LAST_DISCONNECT,		strval(getFieldAssoc_16(TK_LAST_DISCONNECT, result, sql_result)));
		
		//_____________________________________
		new s_reconnect, s_censure, s_priv, s_privSound;
		strdel(string, 0, sizeof(string));
		strins(string, getFieldAssoc_128(TK_SETTINGS, result, sql_result), 0);
		sscanf(string, "p<|>dddd", s_reconnect, s_censure, s_priv, s_privSound);
		SetPVarInt(playerid, PV_SET_RECONNECT, s_reconnect);
		setPlayerCensureStatus(playerid, s_censure == 0 ? false : true);
		SetPlayerPMessagesStatus(playerid, s_priv == 0 ? false : true);
		SetPlayerPMSoundID(playerid, s_privSound);		
		
		//_____________________________________
		SetPVarInt(playerid, PV_LOGIN_VIP_TIME, 			strval(getFieldAssoc_16(TK_PREMIUM_DATE, result, sql_result)));
		SetPVarInt(playerid, PV_LOGIN_VIP_POINTS, 			strval(getFieldAssoc_16(TK_PREMIUM_PLAYER_POINT, result, sql_result)));
		SetPVarInt(playerid, PV_LOGIN_VIP_BONUS_POINTS,		strval(getFieldAssoc_16(TK_PREMIUM_BONUS_POINT, result, sql_result)));
		//_____________________________________
		freeResult(result, sql_result);
		//_____________________________________
		CallLocalFunction("LoadPlayerAccountData", "dd", playerid, getPlayerUserID(playerid));
		return getPlayerUserID(playerid);
	}
	return _FALSE;
}
//---------------------------------------------------------------
ResetPlayerLoginTimer(playerid) {
	if(g_LoginTimer[playerid] != 0) {
		KillTimer(g_LoginTimer[playerid]);
		g_LoginTimer[playerid] = 0;
	}
}
//---------------------------------------------------------------
PlayerLoginAtAccount(playerid, password[] = "", bool:firstshow = false) {
	if(getPlayerLoginStatus(playerid) == LOGIN_STATUS_NOTLOGGED) {
		new string[512];
		new s_gpci[64], p_ip[16];
		new t_stamp = timestamp();
		new bool:autologin;
		//----------------------
		gpci(playerid, s_gpci, 64);
		GetPlayerIp(playerid, p_ip, 16);
		if(firstshow == true) {
			ResetPlayerLoginTimer(playerid);
			g_LoginTimer[playerid] = SetTimerEx("LoginTimeEnd", getSettingIntValueByIndex(s_LoginTimeID) * 1000, 0, "d", playerid);
		}
		//---------------------- 
		if(getSettingIntValueByIndex(s_ReconnectMaxTimeID) > 0) {
			if(GetPVarInt(playerid, PV_SET_RECONNECT) != 0 and (GetPVarInt(playerid, PV_LOGIN_LAST_DISCONNECT) > t_stamp - ToSeconds(getSettingIntValueByIndex(s_ReconnectMaxTimeID), _MINUTE))) {
				new old_ip[16], old_gpci[64];
				GetPVarString(playerid, PV_LOGIN_LAST_LOGIN_IP, old_ip, 16);
				GetPVarString(playerid, PV_LOGIN_LAST_LOGIN_GPCI, old_gpci, 64);		
				if(strlen(old_ip) > 5 and strlen(old_gpci) > 5 and strcmp(old_ip, p_ip) == 0 and strcmp(old_gpci, s_gpci) == 0) {
					autologin = true;
				} 
			}
		}		
		
		if(!isnull(password) or autologin == true) {
			if(((IsValidPassword(password) == _TRUE or (strlen(password) == 6 and 999999 >= strval(password) >= 100000 and GetPVarInt(playerid, PV_LOGIN_RESET_PASSWORD) == 1)) and GetPVarInt(playerid, PV_LOGIN_PASSWORD) == Hash(password)) or (autologin == true and GetPVarInt(playerid, PV_LOGIN_RESET_PASSWORD) == 0)) {	
				//__________________
				ResetPlayerLoginTimer(playerid);
				DeletePVar(playerid, PV_LOGIN_FAIL);
				DeletePVar(playerid, PV_LOGIN_BAN_TIME);
				DeletePVar(playerid, PV_LOGIN_BAN_ADMIN_ID);
				DeletePVar(playerid, PV_LOGIN_BAN_REASON);
				//__________________
				
				format(string, sizeof(string),"\
						UPDATE `"T_KONTA"` SET \
						`"TK_DELETE_STAMP"`='%d',\
						`"TK_LAST_LOGIN_STAMP"`='%d',\
						`"TK_LAST_LOGIN_GPCI"`='%s',\
						`"TK_LAST_LOGIN_IP"`='%s' WHERE `"TK_UID"`='%d'\
					",
					t_stamp + (ToSeconds(getSettingIntValueByIndex(s_LoginDeletingDaysID), _DAY)),
					t_stamp,
					s_gpci,
					p_ip,
					getPlayerUserID(playerid)
				);
				sendQueryWithout(string);
				SetPVarInt(playerid, PV_LOGIN_DELETE_STAMP, t_stamp + (ToSeconds(getSettingIntValueByIndex(s_LoginDeletingDaysID), _DAY)));
				//__________________
				if(IsAdmin(playerid) > 0) {
					if(GetPVarInt(playerid, PV_LOGIN_ADMIN_STAMP) > t_stamp) {						
						SetPVarInt(playerid, PV_LOGIN_ADMIN_LVL, -IsAdmin(playerid));
					} else {
						SetPVarInt(playerid, PV_LOGIN_ADMIN_LVL, 0);
						SetPVarInt(playerid, PV_LOGIN_ADMIN_STAMP, 0);
						format(string, sizeof(string),"UPDATE `"T_KONTA"` SET `"TK_ADMIN_LVL"`='0', `"TK_ADMIN_STAMP"`='0' WHERE `"TK_UID"`='%d'", getPlayerUserID(playerid));
						sendQueryWithout(string);					
					}					
				}
				setPlayerLoginStatus(playerid, LOGIN_STATUS_LOGGED);	
				//__________________
				format(string, sizeof(string), "Logowanie na konto (IP: %s)", p_ip);
				AddToPlayerLog(getPlayerUserID(playerid), string);
				format(string, sizeof(string),"[Logowanie] Gracz '%s' zalogowal(a) sie na konto (UID: %d | IP: %s)", getPlayerName(playerid), getPlayerUserID(playerid), p_ip);
				AddToChatLog(string);	
				
				SendClientMessage(playerid, 0xFFFFFFFF, " ");
				
				format(string, sizeof(string)," (Logowanie) Zostales(as) %s zalogowany(a) na konto "TEXT_DIALOG_NORMAL"%s{0DBF27}.", autologin == true ? ("automatycznie") : ("poprawnie"), getPlayerName(playerid));
				SendClientMessage(playerid,0x0DBF27FF, string);
				SendClientMessage(playerid,0x0DB527FF,"     Wszystkie statystyki zostaly przywrocone.");
				SendClientMessage(playerid,0x0DA127FF,"     Wpisz komende: \""TEXT_DIALOG_NORMAL"/konto{0DA127}\" zeby przejsc do panelu konta.");
				SendClientMessage(playerid,0x0D9727FF,"     Zyczymy przyjemnej gry - Administracja serwera");				
				
				if(IsAdmin(playerid) < 0) {
					SendClientMessage(playerid, 0xFFFFFFFF, " ");
					SendClientMessage(playerid, 0x0DBF27FF, "     To konto posiada przywileje konta administratora.");
					SendClientMessage(playerid, 0x0DBF27FF, "     Wpisz komende: \""TEXT_DIALOG_NORMAL"/alog{0DBF27}\" zeby sie zalogowac.");
				}

				if(IsVIP(playerid) == _TRUE) {
					new year, month, day, hour, minute;
					dtimestamp(GetPlayerVIPTime(playerid), year, month, day, hour, minute);
					format(string, sizeof(string), " (VIP) To konto posiada aktywne do "C_WHITE"%s  "C_GOLD"[ "C_WHITE"%d:%02d "C_GOLD"] przywileje VIP.", strData(year, month, day, " / ", false, false, true, false), hour, minute);
					SendClientMessage(playerid, COLOR_GOLD, string);
				} else {
					SendClientMessage(playerid, COLOR_GOLD, " (VIP) Nie posiadasz konta VIP? Zapraszamy na forum serwera, zeby zobaczyc przywileje wynikajace z posiadania konta VIP!");
				}
				
				SendClientMessage(playerid, 0xFFFFFFFF, " ");					
				//__________________
				if(GetPVarInt(playerid, PV_LOGIN_RESET_PASSWORD) != 0) {
					PlayerAccountPasswordChange(playerid);
				}	
				//__________________
				GetPVarString(playerid, PV_LOGIN_REGISTER_IP, string, 32);
				if(strlen(string) < 3) {
					format(string, sizeof(string), "UPDATE `"T_KONTA"` SET `"TK_REGISTER_IP"`='%s', `"TK_REGISTER_GPCI"`='%s' WHERE `"TK_UID"`='%d'", p_ip, s_gpci, getPlayerUserID(playerid));
					sendQueryWithout(string);
				}				
				return _TRUE;
			} else {
				SetPVarInt(playerid, PV_LOGIN_FAIL, GetPVarInt(playerid, PV_LOGIN_FAIL) + 1);
				format(string, sizeof(string), "Nieudana proba logowania na konto gracza '%s' (IP: %s | Haslo: %s | %d/%d)", getPlayerName(playerid), p_ip, password, GetPVarInt(playerid, PV_LOGIN_FAIL), getSettingIntValueByIndex(s_LoginFailID));
				AddToPlayerLog(getPlayerUserID(playerid), string);
				format(string, sizeof(string),"[Logowanie] Gracz '%s' wpisal niepoprawne haslo podczas logowania sie na konto (UID: %d | IP: %s | %d/%d)", getPlayerName(playerid), getPlayerUserID(playerid), p_ip, GetPVarInt(playerid, PV_LOGIN_FAIL), getSettingIntValueByIndex(s_LoginFailID));
				AddToChatLog(string);			
				strdel(string, 0, sizeof(string));
				strins(string, "\t\t         Niepoprawne haslo dostepu.", 0);	
				if(GetPVarInt(playerid, PV_LOGIN_FAIL) >= getSettingIntValueByIndex(s_LoginFailID)) {
					BlockPlayer(playerid, 3, "Przekroczono limit prob logowania sie na konto.", -1, false);
					return _FALSE;
				}
			}
		}
		format(string, sizeof(string), "\
			\t\t       {F37572}Witaj na serwerze "TEXT_DIALOG_NORMAL"%s{F37572}.\n\n\
			"TEXT_DIALOG_HEAD"   Uzywany przez Ciebie nick jest zarejestrowany na naszym serwerze.\
			\n Jesli jest to Twoje konto, prosimy podac haslo dostepu. W przeciwnym\
			\n      razie prosimy o zmiane nicku na niezarejestrowany. W przypadku\
			\n\tjakichkolwiek problemow prosimy o kontakt z administracja\n\n\
			"TEXT_DIALOG_ALERT"%s", 
		getPlayerName(playerid), string);		
		return ShowPlayerDialogEx(playerid, DIALOG_LOGIN, DIALOG_STYLE_PASSWORD, "Logowanie", string, "Zaloguj", "Wyjdz");		
	}
	return _FALSE;
}
//---------------------------------------------------------------
forward LoginTimeEnd(playerid);
public LoginTimeEnd(playerid) {
	BlockPlayer(playerid, 0, "Uplynal czas wyznaczony na zalogowanie sie na konto.", -1, false);
	return _TRUE;
}


