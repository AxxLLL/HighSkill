/*


*/
//===============================================================
//---------------------------------------------------------------
//===============================================================
BlockPlayer(playerid, min_time, reason[], adminid = -1, bool:showforplayers = true) {
	DeleteDoubleSpaces(reason);
	if(IsPlayerConnected(playerid) and min_time >= 0 and strlen(reason) >= 3) {
		//________________________
		new type[8], 
			string[512], 
			s_time[16] = "Brak", 
			s_unban[64] = "Brak", 
			admin_nick[MAX_PLAYER_NAME], 
			year, month, day, hour, minute;
			
		new const sec_time = min_time * 60;
		//________________________		
		if(sec_time > 0) {
			strdel(s_time, 0, 16);
			strins(s_time, convertSeconds(sec_time), 0);	
		
			dtimestamp(timestamp() + sec_time, year, month, day, hour, minute);
			format(s_unban, sizeof(s_unban), "%s  [%d:%02d]", strData(year, month, day, " / ", false, false, true, false), hour, minute);					

			AddToTimeBan(GetHostFromIP(getPlayerIp(playerid)), sec_time, getPlayerUserID(playerid), getPlayerName(playerid), adminid == -1 ? 0 : getPlayerUserID(adminid), reason); 
		}
		//________________________			
		strins(type, min_time < 60 ? ("Kick") : ("Ban"), 0);		
		
		strins(string, reason, 0);
		if(strlen(string) >= 55) strins(string, "\n", 54);
		strins(admin_nick, adminid == -1 ? ("*System*") : getPlayerName(adminid), 0);
		//________________________				
		format(string, sizeof(string),"\
				"TEXT_DIALOG_HEAD"\tZostales(as) wyrzucony(a) z serwera.\n\n\
				"TEXT_DIALOG_HEAD"Typ: "TEXT_DIALOG_NORMAL"%s\n\
				"TEXT_DIALOG_HEAD"Czas trwania: "TEXT_DIALOG_NORMAL"%s\n\
				"TEXT_DIALOG_HEAD"Data odblokowania: "TEXT_DIALOG_NORMAL"%s\n\
				"TEXT_DIALOG_HEAD"Administrator: "TEXT_DIALOG_NORMAL"%s\n\n\
				"TEXT_DIALOG_HEAD"Powod: "TEXT_DIALOG_NORMAL"%s\n\
			", 
			type,
			s_time,
			s_unban,
			admin_nick,
			string
		);
		ShowPlayerInfoDialog(playerid, -1, "Blokada czasowa", string);		
		//________________________				
		
		if(showforplayers == true) {		
			new s_reason[140];
			
			format(string, sizeof(string), "(%s) Gracz "C_WHITE"%s{FF0000} zostal(a) wyrzucony z serwera przez administratora "C_WHITE"%s{FF0000}. Czas: "C_WHITE"%s", type, getPlayerName(playerid), admin_nick, s_time);
			format(s_reason, sizeof(s_reason), "  Powod: "C_WHITE"%s", reason);
			
			forplayers(i) {
				if(i != playerid) {
					SendClientMessage(i, 0xFF0000FF, string);
					SendClientMessage(i, 0xFF0000FF, s_reason);
				}
			}
		}
		KickEx(playerid, 100);
		return _TRUE;
	}
	return _FALSE;
}
//===============================================================
//---------------------------------------------------------------
//===============================================================
stock UnblockPlayerAccount(userid, adminid = 0) {
	if(IsValidUID(userid)) {
		new DBResult: result, Result:sql_result;
		new string[140];
		format(string, sizeof(string), "SELECT `"TK_NICK"` FROM `"T_KONTA"` WHERE `"TK_UID"`='%d' AND `"TK_BAN_TIME"`!=0 LIMIT 1", userid);
		result = sendQueryResult(string, sql_result);
		if(numRows(result, sql_result) > 0) {
			new p_name[MAX_PLAYER_NAME];
			new admin_name[MAX_PLAYER_NAME];
			
			strins(p_name, getFieldAssoc_32(TK_NICK, result, sql_result), 0);
			DeconvertNick(p_name);
			freeResult(result, sql_result);			
			
			strins(admin_name, GetNickByUserID(adminid), 0);
				
			format(string, sizeof(string), "UPDATE `"T_KONTA"` SET `"TK_BAN_TIME"`='0', `"TK_BAN_ADMIN_ID"`='0', `"TK_BAN_REASON"`='-' WHERE `"TK_UID"`='%d'", userid);
			sendQueryWithout(string);
			format(string, sizeof(string), "Konto zostalo odblokowane przez administratora '%s' (UID: %d)", admin_name, adminid); 
			AddToPlayerLog(userid, string);		
			format(string, sizeof(string), "Gracz '%s' (UID: %d) zostal odbanowany przez administratora '%s' (UID: %d)", p_name, userid, admin_name, adminid);
			AddToBanLog(string);						
				
			format(string, sizeof(string), "SELECT `"TTB_UNIQUE_ID"` FROM `"T_TIME_BAN"` WHERE `"TTB_UID"`='%d' LIMIT 1", userid);
			result = sendQueryResult(string, sql_result);
			if(numRows(result, sql_result) > 0) {
				new unique_id = strval(getFieldAssoc_32(TTB_UNIQUE_ID, result, sql_result));
				freeResult(result, sql_result);
				format(string, sizeof(string), "DELETE FROM `"T_TIME_BAN"` WHERE `"TTB_UNIQUE_ID"`='%d'", unique_id);
				sendQueryWithout(string);
				format(string, sizeof(string), "Ban czasowy na host (UniqeID: %d) powiazany z kontem '%s' (UID: %d) zostal usuniety przez administratora %s (UID: %d).", 
					unique_id, p_name, userid, admin_name, adminid);
				AddToBanLog(string);					
			}
			return _TRUE;			
		}
	}
	return _FALSE;
}
//---------------------------------------------------------------
/*
BlockPlayerAccount(userid, adminid, bantime, reason[], bool:tobanlog = false) {
	DeleteDoubleSpaces(reason);
	DeleteSQLInjectionChars(reason);
	DeleteSpecialChars(reason);
	
	if(strlen(reason) >= 3 and IsValidUID(userid) and (IsValidUID(adminid) or adminid == 0) and bantime > 0) {			
		new string[256],
			s_data[32],
			year, month, day, hour, minute,
			admin_nick[MAX_PLAYER_NAME];
		new const unbantime = timestamp() + bantime;
			
		format(string, sizeof(string), "UPDATE `"T_KONTA"` SET `"TK_BAN_TIME"`='%d', `"TK_BAN_ADMIN_ID"`='%d', `"TK_BAN_REASON"`='%s' WHERE `"TK_UID"`='%d'", unbantime, adminid, reason, userid);
		sendQueryWithout(string);	
				
		strins(admin_nick, GetNickByUserID(adminid), 0);
		dtimestamp(unbantime, year, month, day, hour, minute);	
		strins(s_data, strData(year, month, day, " / ", false, false, true, false), 0);		
		
		format(string, sizeof(string), "Konto zostalo zablokowane do %s [ %d:%02d ] przez administratora '%s' (UID: %d) z powodu: %s", 
			s_data, hour, minute, admin_nick, adminid, reason);
		AddToPlayerLog(userid, string);	

		if(tobanlog == true) {
			format(string, sizeof(string), "Gracz '%s' (UID: %d) zostal zbanowany przez administratora '%s' (UID: %d) do %s  [ %d:%02d ]. Powod: %s", 
				GetNickByUserID(userid), userid, admin_nick, adminid, s_data, hour, minute, reason);
			AddToBanLog(string);	
		}
		return _TRUE;
	}
	return _FALSE;
}
*/
//===============================================================
//---------------------------------------------------------------
//===============================================================
IsHostInTimeBan(host[], time = -1, &bantime = 0) {
	if(IsValidHost(host) == _TRUE) {
		if(time == -1) time = timestamp();
		new string[128];
		new DBResult: result, Result:sql_result;
		format(string, sizeof(string), "SELECT `"TTB_UNIQUE_ID"`,`"TTB_UNBANTIME"` FROM `"T_TIME_BAN"` WHERE `"TTB_HOST"`='%s' AND `"TTB_UNBANTIME"`>='%d' LIMIT 1", host, time);
		result = sendQueryResult(string, sql_result);
		if(numRows(result, sql_result) > 0) {
			new uniqueid = strval(getFieldAssoc_16(TTB_UNIQUE_ID, result, sql_result));
			bantime = strval(getFieldAssoc_16(TTB_UNBANTIME, result, sql_result));
			freeResult(result, sql_result);
			return uniqueid;
		}		
	}
	return _FALSE;
}
//---------------------------------------------------------------
/*
stock DeleteTimeBanByPlayer(playername[], userid, adminid = 0) {
	if(IsValidNick(playername) and userid >= 0) {
		new string[256],
			DBResult: result, Result:sql_result;
			conNick[MAX_PLAYER_NAME];
			
		strins(conNick, playername, 0);
		ConvertNick(conNick);
		
		format(string, sizeof(string), "SELECT `"TTB_UNIQUE_ID"`,`"TTB_UNBANTIME"` FROM `"T_TIME_BAN"` WHERE `"TTB_PLAYER_NAME"`='%s' AND `"TTB_UID"`='%d' AND `"TTB_UNBANTIME"`>='%d' LIMIT 1", conNick, userid, timestamp());
		result = sendQueryResult(string, sql_result);
		if(numRows(result, sql_result) > 0) {
			new uniqueid = strval(getFieldAssoc_16(TTB_UNIQUE_ID, result, sql_result));
			new unbantime = strval(getFieldAssoc_16(TTB_UNBANTIME, result, sql_result));
			new admin_name[MAX_PLAYER_NAME];
			freeResult(result, sql_result);
			
			strins(admin_name, GetNickByUserID(adminid), 0);
		
			format(string, sizeof(string), "DELETE FROM `"T_TIME_BAN"` WHERE `"TTB_UNIQUE_ID"` = '%d'", uniqueid);
			sendQueryWithout(string);

			format(string, sizeof(string), "Administrator %s (UID: %d) usunal(ela) ban czasowy dla gracza %s (UID: %d)", 
				admin_name, adminid, playername, userid);
			AddToBanLog(string);			
			
			if(IsValidUID(userid) == _TRUE) {
				format(string, sizeof(string), "UPDATE `"T_KONTA"` SET `"TK_BAN_TIME"`='0', `"TK_BAN_ADMIN_ID"`='0', `"TK_BAN_REASON"`='-' WHERE `"TK_UID"`='%d' AND `"TK_BAN_TIME"`='%d'", userid, unbantime);
				sendQueryWithout(string);
				format(string, sizeof(string), "Konto zostalo odblokowane przez administratora '%s' (UID: %d)", admin_name, adminid); 
				AddToPlayerLog(userid, string);		
			}
			
			return _TRUE;
		}
	}
	return _FALSE;
}
*/
//---------------------------------------------------------------
stock DeleteTimeBanByIndex(uniqueid, adminid = 0) {
	new string[256],
		DBResult: result, Result:sql_result;
	format(string, sizeof(string), "SELECT `"TTB_UID"`, `"TTB_PLAYER_NAME"`, `"TTB_UNBANTIME"` FROM `"T_TIME_BAN"` WHERE `"TTB_UNBANTIME"`>='%d' AND `"TTB_UNIQUE_ID"` = '%d' LIMIT 1", timestamp(), uniqueid);
	result = sendQueryResult(string, sql_result);	
	if(numRows(result, sql_result) > 0) {
		new conNick[MAX_PLAYER_NAME],			
			userid = strval(getFieldAssoc_16(TTB_UID, result, sql_result)),
			unbantime = strval(getFieldAssoc_16(TTB_UNBANTIME, result, sql_result)),
			admin_name[MAX_PLAYER_NAME];
			
		strins(conNick, getFieldAssoc_32(TTB_PLAYER_NAME, result, sql_result), 0);
		strins(admin_name, GetNickByUserID(adminid), 0);
		DeconvertNick(conNick);
		
		freeResult(result, sql_result);	
		
		format(string, sizeof(string), "DELETE FROM `"T_TIME_BAN"` WHERE `"TTB_UNIQUE_ID"` = '%d'", uniqueid);
		sendQueryWithout(string);

		format(string, sizeof(string), "Administrator %s (UID: %d) usunal(ela) ban czasowy dla gracza %s (UID: %d)", 
			admin_name, adminid, conNick, userid);
		AddToBanLog(string);			
			
		if(IsValidUID(userid) == _TRUE) {
			format(string, sizeof(string), "UPDATE `"T_KONTA"` SET `"TK_BAN_TIME"`='0', `"TK_BAN_ADMIN_ID"`='0', `"TK_BAN_REASON"`='-' WHERE `"TK_UID"`='%d' AND `"TK_BAN_TIME"`='%d'", userid, unbantime);
			sendQueryWithout(string);
			format(string, sizeof(string), "Konto zostalo odblokowane przez administratora '%s' (UID: %d)", admin_name, adminid); 
			AddToPlayerLog(userid, string);		
		}			
		return _TRUE;
	}
	return _FALSE;
}
//---------------------------------------------------------------
AddToTimeBan(host[], bantime, userid, username[], adminid, reason[]) {
	DeleteDoubleSpaces(reason);
	DeleteSQLInjectionChars(reason);
	DeleteSpecialChars(reason);
	if(IsValidHost(host) == _TRUE and strlen(reason) >= 3 and userid >= 0 and adminid >= 0 and bantime > 0 and IsValidNick(username)) {		
		new string[350],
			conNick[MAX_PLAYER_NAME],
			admin_nick[MAX_PLAYER_NAME],
			year, month, day, hour, minute;
		new s_data[32];
		new is_unbantime, uniqueid;
		new const unbantime = timestamp() + bantime;
		strins(admin_nick, GetNickByUserID(adminid), 0);
		strins(conNick, username, 0);
		strins(s_data, strData(year, month, day, " / ", false, false, true, false), 0);
		ConvertNick(conNick);
		ConvertNick(admin_nick);
		dtimestamp(unbantime, year, month, day, hour, minute);		
		
		if((uniqueid = IsHostInTimeBan(host, -1, is_unbantime)) == _FALSE) {
			format(string, sizeof(string), "INSERT INTO `"T_TIME_BAN"` (`"TTB_HOST"`,`"TTB_UID"`,`"TTB_PLAYER_NAME"`,`"TTB_ADMINID"`,`"TTB_ADMIN_NAME"`,`"TTB_UNBANTIME"`,`"TTB_REASON"`,`"TTB_DATE_STAMP"`) VALUES ('%s','%d','%s','%d','%s','%d','%s','%d');",
				host, userid, conNick, adminid, admin_nick, unbantime, reason, timestamp());
			sendQueryWithout(string);		
			DeconvertNick(admin_nick);
			format(string, sizeof(string), "Gracz '%s' (UID: %d) zostal czasowo zbanowany przez administratora '%s' (UID: %d) do %s  [ %d:%02d ]. Powod: %s", 
				username, userid, admin_nick, adminid, s_data, hour, minute, reason);
			AddToBanLog(string);		
		} else {
			if(is_unbantime < unbantime) {				
				format(string, sizeof(string), "UPDATE `"T_TIME_BAN"` SET `"TTB_UID"`='%d',`"TTB_PLAYER_NAME"`='%s',`"TTB_ADMINID"`='%d',`"TTB_ADMIN_NAME"`='%s', `"TTB_UNBANTIME"`='%d',`"TTB_REASON"`='%s',`"TTB_DATE_STAMP"`='%d' WHERE `"TTB_UNIQUE_ID"`='%d'",
					userid, conNick, adminid, admin_nick, unbantime, reason, timestamp(), uniqueid);
				sendQueryWithout(string);
				DeconvertNick(admin_nick);
				format(string, sizeof(string), "Gracz '%s' (UID: %d) zostal czasowo zbanowany przez administratora '%s' (UID: %d) do %s  [ %d:%02d ]. Powod: %s", 
					username, userid, admin_nick, adminid, s_data, hour, minute, reason);
				AddToBanLog(string);					
			}
		}
		
		if(IsValidUserID(userid) == _TRUE) {
			new DBResult: result, Result:sql_result;
			format(string, sizeof(string), "SELECT `"TK_BAN_TIME"` FROM `"T_KONTA"` WHERE `"TK_UID"` = '%d' LIMIT 1", userid);
			result = sendQueryResult(string, sql_result);
			if(numRows(result, sql_result) > 0) {
				new timeban = strval(getFieldAssoc_16(TK_BAN_TIME, result, sql_result));
				freeResult(result, sql_result);
				if(timeban < unbantime) {				
					format(string, sizeof(string), "UPDATE `"T_KONTA"` SET `"TK_BAN_TIME"`='%d', `"TK_BAN_ADMIN_ID"`='%d', `"TK_BAN_REASON"`='%s' WHERE `"TK_UID"`='%d'", unbantime, adminid, reason, userid);
					sendQueryWithout(string);
					DeconvertNick(admin_nick);
					format(string, sizeof(string), "Konto zostalo zablokowane do %s [ %d:%02d ] przez administratora '%s' (UID: %d) z powodu: %s", 
						s_data, hour, minute, admin_nick, adminid, reason);
					AddToPlayerLog(userid, string);			
				}
			}
		}		
		return _TRUE;
	}
	return _FALSE;
}
//===============================================================
//---------------------------------------------------------------
//===============================================================
CMD:ban(playerid, cmdtext[]) return cmd_b(playerid, cmdtext);
CMD:b(playerid, cmdtext[]) {
	if(IsAdmin(playerid) > ALVL_NON) {
		if(IsAdmin(playerid) > ALVL_JUNIOR_ADMIN) {
			new string[128];
			new maxBanTime = getSettingIntValueByIndex(s_BanTimeAdminID);
		    if(!isnull(cmdtext)) {
		        new idx = strfind(cmdtext, " ", true), idx2 = strfind(cmdtext, " ", true, idx + 1);
				if(idx == -1 || idx2 == -1) {
					format(string, sizeof(string), " (Ban) Uzyj: \"(/b)an [ID Gracza] [Czas w godzinach ( 1 - %d )] [Powod (min. 3 znaki)]\".", maxBanTime);					
					return SendClientMessage(playerid, COLOR_DIALOG_BODY, string);					
				} else {
				    new IDGracza = INVALID_PLAYER_ID, Czas;
				    strmid(string, cmdtext, 0, idx);
					
					if(IsValidNick(string)) {
						forplayers(i) {
							if(strcmp(getPlayerName(i), string) == 0) {
								IDGracza = i;
								break;
							}
						}
					}
					
					if(IDGracza == INVALID_PLAYER_ID and strlen(string) <= 3) {
						IDGracza = strval(string);
						if(!(MAX_PLAYERS >= IDGracza >= 0) or !IsPlayerConnected(IDGracza)) IDGracza = INVALID_PLAYER_ID;
					}					
					
					if( IDGracza != INVALID_PLAYER_ID) {
						if(IsAdmin(IDGracza) < IsAdmin(playerid)) {
							strmid(string, cmdtext, idx + 1, idx2);
							if(0 < strlen(string) <= 2) {
								if( 1 <= ( Czas = strval(string) ) <= maxBanTime ) {
									if(strlen(cmdtext[idx2 + 1]) >= 3) {
										BlockPlayer(IDGracza, Czas * 60, cmdtext[idx2 + 1], playerid, true);
									}	else SendClientMessage(playerid, COLOR_DIALOG_BODY," (Ban) Powod bana musi skladac sie z co najmniej 3 znakow.");
									return _TRUE;
								}
							}
							SendClientMessage(playerid, COLOR_DIALOG_BODY, " (Ban) Niepoprawny czas trwania blokady.");
						} else SendClientMessage(playerid, COLOR_DIALOG_BODY," (Ban) Nie mozesz wyrzucic admina z taka sama lub wyzsza ranga.");
					}	else SendClientMessage(playerid, COLOR_DIALOG_BODY, " (Ban) Niepoprawne ID gracza.");
				}
			} else {
				format(string, sizeof(string), " (Ban) Uzyj: \"(/b)an [ID Gracza] [Czas w godzinach ( 1 - %d )] [Powod (min. 3 znaki)]\".", maxBanTime);					
				SendClientMessage(playerid, COLOR_DIALOG_BODY, string);		
			}
		} else SendClientMessage(playerid, COLOR_DIALOG_BODY, " (Ban) Komenda nie jest dostepna dla administratora z poziomem 'Junior Admin'.");
	}
	return _TRUE;
}
//---------------------------------------------------------------
CMD:kick(playerid, cmdtext[]) return cmd_k(playerid, cmdtext);
CMD:k(playerid, cmdtext[]) {
	if(IsAdmin(playerid) > ALVL_NON) {
		new string[128];
		new maxBanTime = (IsAdmin(playerid) == ALVL_JUNIOR_ADMIN ? getSettingIntValueByIndex(s_BanTimeJAdminID) : 60);
	    if(!isnull(cmdtext)) {
	        new idx = strfind(cmdtext, " ", true), idx2 = strfind(cmdtext, " ", true, idx + 1);
			if(idx == -1 || idx2 == -1) {
				format(string, sizeof(string), " (Kick) Uzyj: \"(/k)ick [ID Gracza] [Czas w minutach ( 0 - %d )] [Powod (min. 3 znaki)]\".", maxBanTime);					
				return SendClientMessage(playerid, COLOR_DIALOG_BODY, string);					
			} else {
			    new IDGracza = INVALID_PLAYER_ID, Czas;
			    strmid(string, cmdtext, 0, idx);
				
				if(IsValidNick(string)) {
					forplayers(i) {
						if(strcmp(getPlayerName(i), string) == 0) {
							IDGracza = i;
							break;
						}
					}
				}
					
				if(IDGracza == INVALID_PLAYER_ID and strlen(string) <= 3) {
					IDGracza = strval(string);
					if(!(MAX_PLAYERS >= IDGracza >= 0) or !IsPlayerConnected(IDGracza)) IDGracza = INVALID_PLAYER_ID;
				}					
					
				if( IDGracza != INVALID_PLAYER_ID) {
					if(IsAdmin(IDGracza) < IsAdmin(playerid)) {
						strmid(string, cmdtext, idx + 1, idx2);
						if(0 < strlen(string) <= 2) {
							if( 0 <= ( Czas = strval(string) ) <= maxBanTime ) {
								if(strlen(cmdtext[idx2 + 1]) >= 3) {
									BlockPlayer(IDGracza, Czas, cmdtext[idx2 + 1], playerid, true);
								}	else SendClientMessage(playerid, COLOR_DIALOG_BODY," (Kick) Powod bana musi skladac sie z co najmniej 3 znakow.");
								return _TRUE;
							}
						}
						SendClientMessage(playerid, COLOR_DIALOG_BODY, " (Kick) Niepoprawny czas trwania blokady.");
					} else SendClientMessage(playerid, COLOR_DIALOG_BODY," (Kick) Nie mozesz wyrzucic admina z taka sama lub wyzsza ranga.");
				}	else SendClientMessage(playerid, COLOR_DIALOG_BODY, " (Kick) Niepoprawne ID gracza.");
			}
		} else {
			format(string, sizeof(string), " (Kick) Uzyj: \"(/k)ick [ID Gracza] [Czas w minutach ( 0 - %d )] [Powod (min. 3 znaki)]\".", maxBanTime);					
			SendClientMessage(playerid, COLOR_DIALOG_BODY, string);		
		}
	}
	return _TRUE;
}
