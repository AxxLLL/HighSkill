/*


*/
//===============================================================
//---------------------------------------------------------------
//===============================================================
stock CheckBanValueByType(value[], bantype) {
	if(B_IP <= bantype <= B_GPCI and strlen(value) >= 3) {
		switch(bantype) {
			case B_IP:		if(IsValidIP(value) == _FALSE) 		return _FALSE;	
			case B_HOST: 	if(IsValidHost(value) == _FALSE) 	return _FALSE;
			case B_NICK: 	if(IsValidNick(value) == _FALSE) 	return _FALSE;
			case B_GPCI: 	if(IsValidGPCI(value) == _FALSE) 	return _FALSE;
			default: 		return _FALSE;
		}
		return _TRUE;		
	}
	return _FALSE;
}
//---------------------------------------------------------------
stock GetBanUniqueID(bantype, value[], unbantime = -1) {
	if(unbantime < 0) unbantime = timestamp();

	if(CheckBanValueByType(value, bantype) == _TRUE) {
		new string[160];
		new conValue[64];
		new DBResult: result, Result:sql_result;
		
		strins(conValue, value, 0);
		if(bantype == B_NICK) ConvertNick(conValue);
		
		format(string, sizeof(string), "SELECT `"TB_UNIQUE_ID"` FROM `"T_BAN"` WHERE `"TB_TYPE"`='%d' AND `"TB_VALUE"`='%s' AND `"TB_UNBANTIME"`>'%d' LIMIT 1", bantype, conValue, unbantime);
		result = sendQueryResult(string, sql_result);
		if(numRows(result, sql_result) > 0) {
			new unique_id = strval(getFieldAssoc_16(TB_UNIQUE_ID, result, sql_result));
			freeResult(result, sql_result);
			return unique_id;
		}
	}
	return _FALSE;
}
//---------------------------------------------------------------
stock GetBanPartNameFromType(bantype) {
	new s_part[6] = "NoN";
	if(B_IP <= bantype <= B_GPCI) {
		strdel(s_part, 0, 6);
		switch(bantype) {
			case B_IP:		strins(s_part, "IP", 0);
			case B_HOST: 	strins(s_part, "Host", 0);
			case B_NICK: 	strins(s_part, "Nick", 0);
			case B_GPCI: 	strins(s_part, "GPCI", 0);
		}
	}
	return s_part;
}
//---------------------------------------------------------------
stock RemoveBan(unique_id, adminid = 0) {
	new string[200];
	new DBResult: result, Result:sql_result;
	format(string, sizeof(string), "SELECT `"TB_VALUE"`, `"TB_TYPE"` FROM `"T_BAN"` WHERE `"TB_UNIQUE_ID"`='%d' LIMIT 1", unique_id);
	result = sendQueryResult(string, sql_result);
	if(numRows(result, sql_result) > 0) {
		//______________________
		new value[64], 
			admin_name[MAX_PLAYER_NAME],
			ban_type 	= strval(getFieldAssoc_8(TB_TYPE, result, sql_result));
		strins(value, getFieldAssoc_64(TB_VALUE, result, sql_result), 0);
		freeResult(result, sql_result);		
		strins(admin_name, GetNickByUserID(adminid), 0);	// Kasuje poprzednie wyniki bazy danych MySQL
		DeconvertNick(admin_name);
		if(ban_type == B_NICK) DeconvertNick(value);
		//______________________		
		format(string, sizeof(string), "DELETE FROM `"T_BAN"` WHERE `"TB_UNIQUE_ID"`='%d'", unique_id);
		sendQueryWithout(string);
		//______________________________________
		format(string, sizeof(string), "Ban na '%s' o wartosci '%s' (UniqeID: %d) zostal usuniety przez administratora %s (UID: %d).", 
			GetBanPartNameFromType(ban_type), value, unique_id, admin_name, adminid);
		AddToBanLog(string);			
		return _TRUE;
	}	
	return _FALSE;
}
//---------------------------------------------------------------
stock AddBan(bantype, value[], bantime, adminid, reason[]) {
	DeleteDoubleSpaces(reason);
	DeleteSQLInjectionChars(reason);
	DeleteSpecialChars(reason);	
	if(CheckBanValueByType(value, bantype) == _TRUE and bantime > 0 and (IsValidUID(adminid) or adminid == 0)) {
		new conValue[64];
		//_________________________________________	
		strins(conValue, value, 0);
		if(bantype == B_NICK) ConvertNick(conValue);	
		//_________________________________________
		if(GetBanUniqueID(bantype, conValue) == _FALSE) {
			new string[512],
				t_stamp = timestamp(),
				unban_time = t_stamp + bantime,
				year, month, day, hour, minute;	
			new admin_name[MAX_PLAYER_NAME];
			
			strins(admin_name, GetNickByUserID(adminid), 0);
			ConvertNick(admin_name);
			format(string, sizeof(string), "INSERT INTO `"T_BAN"` (`"TB_VALUE"`,`"TB_TYPE"`,`"TB_ADMINID"`,`"TB_ADMIN_NAME"`,`"TB_UNBANTIME"`,`"TB_REASON"`,`"TB_DATE_STAMP"`) VALUES ('%s', '%d', '%d', '%s', '%d', '%s', '%d');",
				conValue, bantype, adminid, admin_name, unban_time, reason, t_stamp
			);				
			sendQueryWithout(string);
			
			DeconvertNick(admin_name);
			format(string, sizeof(string), "Nowy ban na %s (Value: %s | UniqeID: %d) zostal nalozony do %s [ %d:%02d ] przez administratora '%s' (UID: %d). Powod: %s", 
				GetBanPartNameFromType(bantype), 
				value, 
				GetBanUniqueID(bantype, conValue), 
				strData(year, month, day, " / ", false, false, true, false), hour, minute, 
				admin_name, adminid, 
				reason
			);
			AddToBanLog(string);					
			return _TRUE;	
		}	
	}
	return _FALSE;
}
//---------------------------------------------------------------

