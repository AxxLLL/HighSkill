/*

*/
//===============================================================
//---------------------------------------------------------------
//===============================================================
#define	L_CHAT				GLOBAL_LOG_FOLDER"Chat"
#define	L_ERROR				GLOBAL_LOG_FOLDER"error.txt"
#define L_PLAYER			GLOBAL_LOG_FOLDER"Players"
#define L_DEL_PLAYER		L_PLAYER"/Deleted/"
#define L_NICK_CHANGE		GLOBAL_LOG_FOLDER"nicks.txt"
#define	L_PLAYER_INFO		GLOBAL_LOG_FOLDER"playerinfo.txt"
#define L_RESET_INFO		GLOBAL_LOG_FOLDER"resetlog.txt"
#define L_DELETE_INFO		GLOBAL_LOG_FOLDER"delreg.txt"
#define L_MULTIACCOUNT  	GLOBAL_LOG_FOLDER"multiaccount.txt"
#define L_BAN_INFO			GLOBAL_LOG_FOLDER"ban.txt"
#define L_ADMIN_INFO		GLOBAL_LOG_FOLDER"admin.txt"
#define	L_VIP_INFO			GLOBAL_LOG_FOLDER"vip.txt"
#define L_ANTYCHEAT_INFO	GLOBAL_LOG_FOLDER"antycheat.txt"
//===============================================================
//---------------------------------------------------------------
//===============================================================
AddToChatLog(message[]) {
	if(getSettingIntValueByIndex(s_LogChatID) == 1) {
		return addToDailyLog(L_CHAT, message);
	}
	return _FALSE;
}
//---------------------------------------------------------------
AddToErrorLog(message[]) {
	print(message);
	AddToChatLog(message);
	return addToNormalLog(L_ERROR, message);
}
//---------------------------------------------------------------
AddToAntyCheatLog(message[]) {
	print(message);
	AddToChatLog(message);
	return addToNormalLog(L_ANTYCHEAT_INFO, message);
}
//---------------------------------------------------------------
AddToPlayerLog(userid, message[]) {
	if(getSettingIntValueByIndex(s_LogPlayersID) == 1 and IsValidUID(userid) == _TRUE) {
		new patch[64];
		format(patch, sizeof(patch), L_PLAYER "/%d.txt", userid);	
		return addToNormalLog(patch, message);
	}
	return _FALSE;
}
//---------------------------------------------------------------
AddToDeletingInfoLog(message[]) {
	if(getSettingIntValueByIndex(s_LogDeletingInfoID) == 1) {
		return addToNormalLog(L_DELETE_INFO, message);
	}
	return _FALSE;
}
//---------------------------------------------------------------
AddToResetInfoLog(message[]) {
	if(getSettingIntValueByIndex(s_LogResetInfoID) == 1) {
		return addToNormalLog(L_RESET_INFO, message);
	}
	return _FALSE;
}
//---------------------------------------------------------------
AddToMultiAccountInfoLog(message[]) {
	if(getSettingIntValueByIndex(s_LogMultiAccountInfoID) == 1) {
		return addToNormalLog(L_MULTIACCOUNT, message);			
	}
	return _FALSE;
}
//---------------------------------------------------------------
AddToBanLog(message[]) {
	if(getSettingIntValueByIndex(s_LogBanInfoID) == 1) {
		AddToChatLog(message);
		return addToNormalLog(L_BAN_INFO, message);			
	}
	return _FALSE;
}
//---------------------------------------------------------------
AddToAdminLog(message[]) {
	AddToChatLog(message);
	return addToNormalLog(L_ADMIN_INFO, message);	
}
//---------------------------------------------------------------
AddToVIPLog(message[]) {
	if(getSettingIntValueByIndex(s_LogVIPInfoID) == 1) {
		return addToNormalLog(L_VIP_INFO, message);			
	}
	return _FALSE;
}
//===============================================================
//---------------------------------------------------------------
//===============================================================
AddToNickChangeLog(userID, newnick[], oldnick[]) {
	if(getSettingIntValueByIndex(s_LogNickChangeID) == 1) {
		new string[200];
		new conNick_new[MAX_PLAYER_NAME];
		new conNick_old[MAX_PLAYER_NAME];
		strins(conNick_new, newnick, 0);
		strins(conNick_old, oldnick, 0);
			
		ConvertNick(conNick_new);
		ConvertNick(conNick_old);
			
		format(string, sizeof(string), "INSERT INTO `"T_NICK_CHANGE"` (`"TNC_UID"`,`"TNC_STAMP"`,`"TNC_OLD_NICK"`,`"TNC_NEW_NICK"`) VALUES ('%d','%d','%s','%s');", userID, timestamp(), conNick_old, conNick_new);
		sendQueryWithout(string);		
		
		format(string, sizeof(string),"%s -> %s  [UID: %d]", oldnick, newnick, userID);
		AddToChatLog(string);
		addToNormalLog(L_NICK_CHANGE, string);
		return _TRUE;
	}
	return _FALSE;
}
//---------------------------------------------------------------
DeleteOldNickChangeLogs(older_than = -1) {
	new string[64];
	if(older_than == -1) older_than = timestamp() - ToSeconds(getSettingIntValueByIndex(s_NickChangeMaxTimeID), _DAY);
	format(string, sizeof(string), "DELETE FROM `"T_NICK_CHANGE"` WHERE `"TNC_STAMP"` <= '%d'", older_than);
	sendQueryWithout(string);
	return _TRUE;
}
//===============================================================
//---------------------------------------------------------------
//===============================================================
AddNewPlayerInfo(playerid) {
	if(IsPlayerConnected(playerid) and getSettingIntValueByIndex(s_LogPlayerInfoID) == 1) {
		new string[256], s_GPCI[64], s_IP[16], s_Nick[24], u_UID;
		new DBResult: result, Result:sql_result, rows;
		new conNick[MAX_PLAYER_NAME];
		new uniqueID;
		//______________________________
		u_UID = getPlayerUserID(playerid);		
		gpci(playerid, s_GPCI, sizeof(s_GPCI));
		GetPlayerIp(playerid, s_IP, sizeof(s_IP));
		
		GetPlayerName(playerid, s_Nick, sizeof(s_Nick));
		strins(conNick, s_Nick, 0);
		ConvertNick(conNick);
		//______________________________
		
		format(string, sizeof(string), 
			"SELECT `"TPI_UNIQUE_ID"` FROM `"T_PLAYER_INFO"` WHERE `"TPI_UID"`='%d' AND `"TPI_NICK"`='%s' AND `"TPI_IP"` LIKE '%s.%%' AND `"TPI_GPCI"`='%s' LIMIT 1",
			u_UID, conNick, GetHostFromIP(s_IP), s_GPCI);
			
		result = sendQueryResult(string, sql_result);
		if((rows = numRows(result, sql_result)) > 0) uniqueID = strval(getFieldAssoc_16(TPI_UNIQUE_ID, result, sql_result));
		freeResult(result, sql_result);
		
		if(rows == 0) {
			format(string, sizeof(string), "INSERT INTO `"T_PLAYER_INFO"` (`"TPI_UID"`,`"TPI_STAMP"`,`"TPI_NICK"`,`"TPI_IP"`,`"TPI_GPCI"`) VALUES('%d','%d','%s','%s','%s');",  u_UID, timestamp(), conNick, s_IP, s_GPCI);
			sendQueryWithout(string);
		} else {
			format(string, sizeof(string), "UPDATE `"T_PLAYER_INFO"` SET `"TPI_STAMP"`='%d' WHERE `"TPI_UNIQUE_ID"`='%d'", timestamp(), uniqueID);
			sendQueryWithout(string);		
		}
		format(string, sizeof(string), 
			"SELECT `"TPI_UNIQUE_ID"` FROM `"T_PLAYER_INFO"` WHERE `"TPI_UID"`='%d' AND `"TPI_NICK"`='%s' AND `"TPI_IP"`='%s' AND `"TPI_GPCI"`='%s' LIMIT 1",
		u_UID, conNick, s_IP, s_GPCI);		
		
		result = sendQueryResult(string, sql_result);
		if(numRows(result, sql_result) > 0) {
			format(string, sizeof(string), "Nick: %s ( User ID: %d | IP: %s | GPCI: %s )", s_Nick, u_UID, s_IP, s_GPCI);
			addToNormalLog(L_PLAYER_INFO, string);				
			freeResult(result, sql_result);
		}					
		return _TRUE;
	}
	return _FALSE;
}
//---------------------------------------------------------------
DeleteOldPlayerInfo(older_than = -1) {
	new string[64];
	if(older_than == -1) older_than = timestamp() - ToSeconds(getSettingIntValueByIndex(s_PlayerInfoMaxTimeID), _DAY);
	format(string, sizeof(string), "DELETE FROM `"T_PLAYER_INFO"` WHERE `"TPI_STAMP"` <= '%d'", older_than);
	sendQueryWithout(string);	
	return _TRUE;
}
//---------------------------------------------------------------
stock CheckPlayerInfoData(nick[], ip[], gpci[], byuserid = 0, intime = 0) {
	if((IsValidNick(nick) == _TRUE or IsValidUserID(byuserid) == _TRUE) and IsValidIP(ip) and IsValidGPCI(gpci) and intime >= 0) {
		new string[256];
		new DBResult: result, Result:sql_result;
		if(IsValidUserID(byuserid)) {
			format(string, sizeof(string), "SELECT `"TPI_UNIQUE_ID"` FROM `"T_PLAYER_INFO"` WHERE `"TPI_UID"`='%d' AND `"TPI_IP"`='%s' AND `"TPI_GPCI"`='%s' AND `"TPI_STAMP"`>='%d' LIMIT 1", byuserid, ip, gpci, intime);
		} else {	
			new conNick[MAX_PLAYER_NAME];
			strins(conNick, nick, 0);	
			ConvertNick(conNick);
			format(string, sizeof(string), "SELECT `"TPI_UNIQUE_ID"` FROM `"T_PLAYER_INFO"` WHERE `"TPI_NICK"`='%s' AND `"TPI_IP"`='%s' AND `"TPI_GPCI"`='%s' AND `"TPI_STAMP"`>='%d' LIMIT 1", conNick, ip, gpci, intime);
		}
		result = sendQueryResult(string, sql_query);
		if(numRows(result, sql_result) > 0) {
			new uniqueid = strval(getFieldAssoc_16(TPI_UNIQUE_ID, result, sql_result));
			freeResult(result, sql_result);
			return uniqueid;
		}
	}
	return _FALSE;
}
//===============================================================
//---------------------------------------------------------------
//===============================================================
/*
DeleteOldRegisterInfo(older_than = -1) {
	new string[64];
	if(older_than == -1) older_than = timestamp() - 43200;  // 12 godzin
	format(string, sizeof(string), "DELETE FROM `"T_REGISTER "` WHERE `"TR_STAMP"` <= '%d'", older_than);
	sendQueryWithout(string);
	return _TRUE;
}
*/
//===============================================================
//---------------------------------------------------------------
//===============================================================
DeleteUnusedAdminRights() {
	new string[128], t_stamp = timestamp();
	new numrows, old_time;
	new DBResult: result, Result:sql_result;
	//__________________________
	format(string, sizeof(string), "UPDATE `"T_KONTA"` SET `"TK_ADMIN_LVL"`='0' WHERE `"TK_ADMIN_STAMP"` < '%d' AND `"TK_ADMIN_STAMP"` != 0", t_stamp);
	sendQueryWithout(string);	
	//__________________________
    format(string, sizeof(string), "SELECT `"TK_UID"`,`"TK_NICK"`,`"TK_LAST_DISCONNECT"` FROM `"T_KONTA"` WHERE `"TK_LAST_DISCONNECT"` <= '%d' AND `"TK_ADMIN_LVL"` != '0' AND `"TK_ADMIN_LVL"` <= '2'", (old_time = t_stamp - ToSeconds(getSettingIntValueByIndex(s_NADelAdminRightsID), _DAY)));
    result = sendQueryResult(string, sql_result);
    if((numrows = numRows(result, sql_result)) > 0) {
		new userid, nick[32], last_disconnect, c_seconds[16];
		for(new i; i < numrows; i ++) {
			last_disconnect = strval(getFieldAssoc_16(TK_LAST_DISCONNECT, result, sql_result));
			userid = strval(getFieldAssoc_8(TK_UID, result, sql_result));
			strins(nick, getFieldAssoc_32(TK_NICK, result, sql_result), 0);
			DeconvertNick(nick);
					
			strdel(c_seconds, 0, 16);
			strins(c_seconds, convertSeconds(t_stamp - last_disconnect), 0);
				
			format(string, sizeof(string), "Usunieto prawa administratora graczu %s (UID: %d) z powodu nieaktywnosci (%s)", nick, userid, c_seconds);
			AddToAdminLog(string);
					
			format(string, sizeof(string), "Usunieto prawa administratora z powodu nieaktywnosci (%s)", c_seconds);
			AddToPlayerLog(userid, string);
					
			nextRow(result, sql_result);
		}		
		
     	freeResult(result, sql_result);
      	format(string, sizeof(string), "UPDATE `"T_KONTA"` SET `"TK_ADMIN_LVL"`='0' WHERE `"TK_LAST_DISCONNECT"` <= '%d' AND `"TK_ADMIN_LVL"` != '0' AND `"TK_ADMIN_LVL"` <= '2'", old_time);
		sendQueryWithout(string);
	}
	return _TRUE;
}
//===============================================================
//---------------------------------------------------------------
//===============================================================
DeleteOldBanInfo(old_time = -1) {
	new string[64];
	if(old_time == -1) old_time = timestamp();
	format(string, sizeof(string), "DELETE FROM `"T_BAN"` WHERE `"TB_UNBANTIME"` <= '%d'", old_time);
	sendQueryWithout(string);	
	return _TRUE;
}
//---------------------------------------------------------------
DeleteOldTimeBanInfo(old_time = -1) {
	new string[64];
	if(old_time == -1) old_time = timestamp();
	format(string, sizeof(string), "DELETE FROM `"T_TIME_BAN"` WHERE `"TTB_UNBANTIME"` <= '%d'", old_time);
	sendQueryWithout(string);	
	return _TRUE;
}
//===============================================================
//---------------------------------------------------------------
//===============================================================
DeleteUnusedPlayerAccounts() {
	new string[200];
	new t_stamp = timestamp();
	new DBResult: result, Result:sql_result, numrows;
	
	format(string, sizeof(string),"SELECT `"TK_UID"`, `"TK_NICK"` FROM `"T_KONTA"` WHERE `"TK_DELETE_STAMP"` < '%d' AND `"TK_ADMIN_LVL"`='0' AND `"TK_BAN_TIME"` < '%d' AND `"TK_PREMIUM_DATE"` < '%d'", t_stamp, t_stamp, t_stamp);
    result = sendQueryResult(string, sql_result);
    if((numrows = numRows(result, sql_result)) > 0) {
		new year, month, day, hour, minute, File:f_del, File:f_new, userid, nick[32];
		new bool:isFolder = ((CheckFolderPatch(L_DEL_PLAYER) == _TRUE and getSettingIntValueByIndex(s_CopyDeletingID) == 1) ? true : false);
		
		getdate(year, month, day);
		gettime(hour, minute);		
		
		for(new i; i < numrows; i ++) {		
			strdel(nick, 0, 32);
			strins(nick, getFieldAssoc_32(TK_NICK, result, sql_result), 0);
			DeconvertNick(nick);

			if(IsValidUID((userid = strval(getFieldAssoc_32(TK_UID, result, sql_result)))) == _TRUE) {
				CallLocalFunction("DeleteAccountData", "d", userid);
				format(string, 128, L_PLAYER "/%d.txt", userid);
				if(fexist(string)) {
					if(isFolder == true) {
						f_del = fopen(string, io_read);
						format(string, 128, L_DEL_PLAYER "%s(%d).txt", nick, userid);
						f_new = fopen(string, io_write);
						while(fread(f_del, string, sizeof(string))) {
							DeleteNewLine(string);
							if(strlen(string) > 5) {
								fwrite(f_new, "\r\n");
								fwrite(f_new, string);
							}
						}
						format(string, sizeof(string), "\r\n( %s  [ %02d:%02d ])  KONTO USUNIETO Z POWODU BRAKU AKTYWNOSCI", strData(year, month, day, " / ", false, false, true, false), hour, minute);
						fwrite(f_new, string);
						fclose(f_del);
						fclose(f_new);
					}
					format(string, 128, L_PLAYER "/%d.txt", userid);
					fremove(string);
				}
			}
			format(string, sizeof(string),"%s  (UID: %d)", nick, userid);
			AddToDeletingInfoLog(string);

			nextRow(result, sql_result);
		}		
		
		freeResult(result, sql_result);
		format(string, sizeof(string), "DELETE FROM `"T_KONTA"` WHERE `"TK_DELETE_STAMP"` < '%d' AND `"TK_BAN_TIME"` < '%d' AND `"TK_ADMIN_LVL"`='0' AND `"TK_PREMIUM_DATE"` < '%d'", t_stamp, t_stamp, t_stamp);
		sendQueryWithout(string);
    }
	return _TRUE;
}
//---------------------------------------------------------------
DeleteOldPlayersBans() {
	new string[64];
	format(string, sizeof(string), "UPDATE `"T_KONTA"` SET `"TK_BAN_TIME"`='0', `"TK_BAN_ADMIN_ID"`='0', `"TK_BAN_REASON"`='-' WHERE `"TK_BAN_TIME"` < '%d' AND `"TK_BAN_TIME"` != 0", timestamp());
	sendQueryWithout(string);
	return _TRUE;
}