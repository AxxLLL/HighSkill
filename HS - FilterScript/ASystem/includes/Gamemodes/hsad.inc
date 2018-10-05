/*

*/
//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
#define PV_RANKING        				"RankingGracza"
//------------------------------------------------------------------------------
#define PV_SPAR_AKTYWNY         		"CzyWyzwanieNaSparJestAktywne"
#define	PV_SPEC_POKAZ					"PokazywanieSpectatora"
#define PV_RSP_AKTYWNY          		"CzyRSPNaPrzyciskEJstAktywne"
#define PV_WYNIKI						"ZmianaPodgladuWynikow"
#define PV_AIMED_INFO_STATUS            "CelowanieInfo"
//------------------------------------------------------------------------------
#define getPlayerSparingStatus(%1)		GetPVarInt(%1, PV_SPAR_AKTYWNY)
#define getPlayerRSPStatus(%1)			GetPVarInt(%1, PV_RSP_AKTYWNY)
#define getPlayerStatsStatus(%1)		GetPVarInt(%1, PV_WYNIKI)
#define getPlayerSpecStatus(%1)			GetPVarInt(%1, PV_SPEC_POKAZ)
#define getPlayerAimedInfoStatus(%1) 	GetPVarInt(%1, PV_AIMED_INFO_STATUS)
//==============================================================================
#define setPlayerSparingStatus(%1,%2) 	SetPVarInt(%1, PV_SPAR_AKTYWNY, %2 == 1 ? 1 : 0)
#define setPlayerRSPStatus(%1,%2)		SetPVarInt(%1, PV_RSP_AKTYWNY, %2 == 1 ? 1 : 0)
#define setPlayerStatsStatus(%1,%2) 	SetPVarInt(%1, PV_WYNIKI, %2 == 1 ? 1 : 0)
#define setPlayerSpecStatus(%1,%2) 		SetPVarInt(%1, PV_SPEC_POKAZ, %2 == 1 ? 1 : 0)
#define setPlayerAimedInfoStatus(%1,%2) SetPVarInt(%1, PV_AIMED_INFO_STATUS, %2 == 1 ? 1 : 0)
//==============================================================================
#define T_ACCOUNT_DATA          BASE_PREFIX"accdata"
//{	notepad ++ - ukrycie
#define TAD_UID                 "a"
#define TAD_SETTINGS            "b"
#define TAD_KILLS				"c"
#define TAD_DEATHS				"d"
#define TAD_DMG					"e"
#define TAD_RESPECT				"f"
#define TAD_SPARING_WIN			"g"
#define TAD_SPARING_LOSS		"h"
#define TAD_CAR_KILL			"i"
#define TAD_HELI_KILL			"j"
#define TAD_TODAY_KILLS			"k"
#define TAD_TODAY_DEATHS		"l"
#define TAD_TODAY_RESPECT		"m"
#define TAD_TODAY_DMG			"n"
#define TAD_YESTERDAY_RANKPOS	"o"
#define TAD_WEAPONS_0			"a0"
#define TAD_WEAPONS_1			"a1"
#define TAD_WEAPONS_2			"a2"
#define TAD_WEAPONS_3			"a3"
#define TAD_WEAPONS_4			"a4"
#define TAD_WEAPONS_5			"a5"
#define TAD_WEAPONS_6			"a6"
#define TAD_WEAPONS_7			"a7"
#define TAD_WEAPONS_8			"a8"
#define TAD_WEAPONS_9			"a9"
#define TAD_WEAPONS_10			"a10"
#define TAD_WEAPONS_11			"a11"
#define TAD_WEAPONS_12			"a12"
#define TAD_WEAPONS_13			"a13"
#define TAD_WEAPONS_14			"a14"
#define TAD_WEAPONS_15			"a15"
#define TAD_WEAPONS_16			"a16"
#define TAD_WEAPONS_17			"a17"
#define TAD_WEAPONS_18			"a18"
#define TAD_WEAPONS_19			"a19"
#define TAD_WEAPONS_20			"a20"
#define TAD_WEAPONS_21			"a21"
#define TAD_WEAPONS_22			"a22"
#define TAD_WEAPONS_23			"a23"
#define TAD_WEAPONS_24			"a24"
#define TAD_WEAPONS_25			"a25"
#define TAD_WEAPONS_26			"a26"
#define TAD_WEAPONS_27			"a27"
#define TAD_WEAPONS_28			"a28"
#define TAD_WEAPONS_29			"a29"
#define TAD_WEAPONS_30			"a30"
#define TAD_WEAPONS_31			"a31"
#define TAD_WEAPONS_32			"a32"
#define TAD_WEAPONS_33			"a33"
#define TAD_WEAPONS_34			"a34"
#define TAD_WEAPONS_35			"a35"
#define TAD_WEAPONS_36			"a36"
#define TAD_WEAPONS_37			"a37"
#define TAD_WEAPONS_38			"a38"
#define TAD_WEAPONS_39			"a39"
#define TAD_WEAPONS_40			"a40"
#define TAD_WEAPONS_41			"a41"
#define TAD_WEAPONS_42			"a42"
//}
//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
forward UpdatePlayerRanking(playerid);
public UpdatePlayerRanking(playerid) {
	new Result:sql_result;
	new DBResult:result = sendQueryResult("SELECT `"TAD_UID"` FROM `"T_ACCOUNT_DATA"` ORDER BY `"TAD_RESPECT"` DESC", sql_result),
		rows = numRows(result, sql_result);
	if(rows > 0) {
		if(playerid == INVALID_PLAYER_ID) {
			new playersList[MAX_PLAYERS], playersCounter;
			for(new i; i < MAX_PLAYERS; i ++) {
				if(IsPlayerConnected(i) and getPlayerLoginStatus(i) == LOGIN_STATUS_LOGGED) {
					playersList[playersCounter ++] = i;
				}
			}
			if(playersCounter > 0) {			
				for(new i, x, userid; i < rows and playersCounter > 0; i ++) {
					for(x = 0, userid = strval(getFieldAssoc_8(TAD_UID, result, sql_result)); x < playersCounter; x ++) {
						if(userid == getPlayerUserID(playersList[x])) {
							SetPVarInt(playersList[x], PV_RANKING, i + 1);
							playersCounter --;
							break;
						}
					}	
					if(UseMySQL() == 1) sql_next_row(sql_result);
					else db_next_row(result);
				}
			}
		} else {
			if(IsPlayerConnected(playerid) and getPlayerLoginStatus(playerid) == LOGIN_STATUS_LOGGED) {
				new pUserID = getPlayerUserID(playerid);
				for(new i; i < rows; i ++) {
					if(strval(getFieldAssoc_8(TAD_UID, result, sql_result)) == pUserID) {
						SetPVarInt(playerid, PV_RANKING, i + 1);
						freeResult(result, sql_result);
						return 1;
					}								
					if(UseMySQL() == 1) sql_next_row(sql_result);
					else db_next_row(result);
				}			
			}
		}
		freeResult(result, sql_result);
		return 1;
	}
	return -1;
}
//------------------------------------------------------------------------------
forward PlayerLeftInRound(userid, addrespect);
public PlayerLeftInRound(userid, addrespect) {
	if(IsValidUserID(userid) and -9999 <= addrespect <= 9999) {
		new string[128];
		format(string, sizeof(string), "UPDATE `"T_ACCOUNT_DATA"` SET `"TAD_RESPECT"`="TAD_RESPECT"+%d, `"TAD_DEATHS"`="TAD_DEATHS"+1 WHERE `"TAD_UID"` = '%d'", addrespect, userid);		
		sendQueryWithout(string);
	}
	return 1;
}
//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
#define setPlayerDailyKills(%1,%2) dailyKills[%1] = %2
#define setPlayerDailyDeaths(%1,%2) dailyDeaths[%1] = %2
#define setPlayerDailyDamage(%1,%2) dailyDamage[%1] = %2
#define setPlayerDailyRespect(%1,%2) dailyRespect[%1] = %2
//------------------------------------------------------------------------------
#define getPlayerDailyKills(%1) dailyKills[%1]
#define getPlayerDailyDeaths(%1) dailyDeaths[%1]
#define getPlayerDailyDamage(%1) dailyDamage[%1]
#define getPlayerDailyRespect(%1) dailyRespect[%1]
//==============================================================================
new dailyKills[MAX_PLAYERS], dailyDeaths[MAX_PLAYERS], dailyDamage[MAX_PLAYERS], dailyRespect[MAX_PLAYERS];
//==============================================================================
forward UpdatePlayerDailyStatInfo(playerid, kills, deaths, damage, respect);
public UpdatePlayerDailyStatInfo(playerid, kills, deaths, damage, respect) {
	setPlayerDailyKills(playerid, kills);
	setPlayerDailyDeaths(playerid, deaths);
	setPlayerDailyDamage(playerid, damage);
	setPlayerDailyRespect(playerid, respect);
	return 1;
}
//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
public LoadPlayerAccountData(playerid, userid) {
	new string[128], DBResult: result, Result:sql_result;
	format(string, sizeof(string),	"SELECT * FROM `"T_ACCOUNT_DATA"` WHERE `"TAD_UID"`='%d' LIMIT 1", userid);	
	result = sendQueryResult(string, sql_result);
	if(numRows(result, sql_result) > 0) {
		new s_Sparing, s_RSP, s_Stats, s_Spec, s_AimInfo;
		strdel(string, 0, sizeof(string));
		strins(string, getFieldAssoc_128(TAD_SETTINGS, result, sql_result), 0);
		sscanf(string, "p<|>ddddd", s_Sparing, s_RSP, s_Stats, s_Spec, s_AimInfo);
		setPlayerSparingStatus(playerid, s_Sparing);
		setPlayerRSPStatus(playerid, s_RSP);
		setPlayerStatsStatus(playerid, s_Stats);
		setPlayerSpecStatus(playerid, s_Spec);
		setPlayerAimedInfoStatus(playerid, s_AimInfo);			

		//_____________________________________
		SetPlayerDeath(playerid, strval(getFieldAssoc_16(TAD_DEATHS, result, sql_result)));
		SetPlayerKill(playerid, strval(getFieldAssoc_16(TAD_KILLS, result, sql_result)));		
		SetPlayerDMG(playerid, strval(getFieldAssoc_16(TAD_DMG, result, sql_result)));
		SetPlayerRespect(playerid, strval(getFieldAssoc_16(TAD_RESPECT, result, sql_result)));
		SetPlayerSparingWin(playerid, strval(getFieldAssoc_16(TAD_SPARING_WIN, result, sql_result)));
		SetPlayerSparingLoss(playerid, strval(getFieldAssoc_16(TAD_SPARING_LOSS, result, sql_result)));
		SetPlayerCarKill(playerid, strval(getFieldAssoc_16(TAD_CAR_KILL, result, sql_result)));
		SetPlayerHeliKill(playerid, strval(getFieldAssoc_16(TAD_HELI_KILL, result, sql_result)));
		
		for(new i; i <= 42; i ++) {
			format(string, 4, "a%d", i);
			SetPlayerWeaponKill(playerid, i, strval(getFieldAssoc_16(string, result, sql_result)));
		}		

		freeResult(result, sql_result);
		return 1;
	}
	return 0;
}
//------------------------------------------------------------------------------
public OnNewAccountRegistered(userid) {
	new string[64];
	format(string, sizeof(string), "INSERT INTO `"T_ACCOUNT_DATA"` (`"TAD_UID"`) VALUES ('%d');", userid);
	sendQueryWithout(string);
}
//------------------------------------------------------------------------------
public GameModeOnPlayerConnect(playerid) {
    setPlayerDailyKills(playerid, 0);
    setPlayerDailyDeaths(playerid, 0);
    setPlayerDailyDamage(playerid, 0);
    setPlayerDailyRespect(playerid, 0);
}
//------------------------------------------------------------------------------
public AccountOnPlayerDisconnect(playerid, userid) {
	new string[1024];
	if(getPlayerLoginStatus(playerid) == LOGIN_STATUS_LOGGED) {
           format(string, sizeof(string),"UPDATE `"T_ACCOUNT_DATA"` SET \
				`"TAD_SETTINGS"`='%d|%d|%d|%d|%d',\
				`"TAD_KILLS"`='%d',\
				`"TAD_DEATHS"`='%d',\
				`"TAD_DMG"`='%d',\
				`"TAD_RESPECT"`='%d',\
				`"TAD_SPARING_WIN"`='%d',\
				`"TAD_SPARING_LOSS"`='%d',\
				`"TAD_CAR_KILL"`='%d',\
				`"TAD_HELI_KILL"`='%d',\
				`"TAD_TODAY_KILLS"`= "TAD_TODAY_KILLS"+%d,\
				`"TAD_TODAY_DEATHS"`="TAD_TODAY_DEATHS"+%d,\
				`"TAD_TODAY_RESPECT"`="TAD_TODAY_RESPECT"+%d,\
				`"TAD_TODAY_DMG"`="TAD_TODAY_DMG"+%d\
			",				
			getPlayerSparingStatus(playerid), getPlayerRSPStatus(playerid), getPlayerStatsStatus(playerid), getPlayerSpecStatus(playerid), getPlayerAimedInfoStatus(playerid),
			GetPlayerKill(playerid),
			GetPlayerDeath(playerid),
			GetPlayerDMG(playerid),
			GetPlayerRespect(playerid),
			GetPlayerSparingWin(playerid),
			GetPlayerSparingLoss(playerid),
			GetPlayerCarKill(playerid),
	        GetPlayerHeliKill(playerid),
			getPlayerDailyKills(playerid),
            getPlayerDailyDeaths(playerid),
            getPlayerDailyRespect(playerid),
            getPlayerDailyDamage(playerid)
		);
					
		for(new i; i <= 42; i ++) {
		    format(string, sizeof(string),"%s,`a%d`='%d'", string, i, GetPlayerWeaponKill(playerid, i));
		}
			
		format(string, sizeof(string), "%s WHERE `"TAD_UID"`='%d'", string, userid);
        sendQueryWithout(string);
    }
}
//------------------------------------------------------------------------------
public ResetAccountStatistics(userid, adminid) {
	new string[256];
    format(string, sizeof(string),"UPDATE `"T_ACCOUNT_DATA"` SET \
			`"TAD_KILLS"`='0',\
			`"TAD_DEATHS"`='0',\
			`"TAD_DMG"`='0',\
			`"TAD_RESPECT"`='0'\
	");
	for(new i; i <= 42; i ++) {
	    format(string, sizeof(string),"%s,`a%d`='0'", string, i);
	}
	format(string, sizeof(string), "%s WHERE `"TAD_UID"`='%d'", string, userid);
    sendQueryWithout(string);	

	format(string, sizeof(string), " (Reset Statystyk) Statystyki Twojego konta zostaly usuniete przez administratora "C_WHITE"%s"TEXT_DIALOG_HEAD".", ((IsPlayerConnected(adminid) and IsAdmin(adminid) > 0) ? getPlayerName(adminid) : ("*System*")));
	new x;
	forplayers(i) {
		if(getPlayerUserID(i) == userid) {
			SetPlayerDeath(i, 0);
			SetPlayerKill(i, 0);
			SetPlayerDMG(i, 0);
			SetPlayerRespect(i, 0);
			SetPlayerSparingWin(i, 0);
			SetPlayerSparingLoss(i, 0);
			SetPlayerCarKill(i, 0);
			SetPlayerHeliKill(i, 0);
			for(x = 0; x <= 42; x ++) {
				SetPlayerWeaponKill(i, x, 0);
			}
			SendClientMessage(i, COLOR_DIALOG_HEAD, string);
			break;
		}
	}	
	return _TRUE;
}

public AccountReset(adminname[]) {
	new string[512];
	new File:f_open;
	new year, month, day, hour, minute, second;
	getdate(year, month, day);
	gettime(hour, minute, second);
	
	if(CheckFolderPatch(L_TOP10)) {
		new DBResult: result, Result:sql_result;	
		new rows;
		format(string, sizeof(string), "SELECT `"TAD_UID"`,`"TAD_KILLS"`,`"TAD_DEATHS"`,`"TAD_DMG"`,`"TAD_RESPECT"`");
		for(new i; i <= 42; i ++) {
			format(string, sizeof(string),"%s,`a%d`", string, i);
		}		
		format(string, sizeof(string), "%s FROM `"T_ACCOUNT_DATA"` ORDER BY `"TAD_RESPECT"` DESC LIMIT 10", string);
		result = sendQueryResult(string, sql_result);
		if((rows = numRows(result, sql_result)) > 0) {
			format(string, 256, L_TOP10"%d-%d-%d-%d.txt", year, month, day, timestamp());
			f_open = fopen(string, io_write);
			
			for(new i; i < rows; i ++) {
				format(string, sizeof(string), "\r\n%d)%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d",
						i + 1, 
						strval(getFieldAssoc_16(TAD_UID, result, sql_result)),
						strval(getFieldAssoc_16(TAD_KILLS, result, sql_result)), 
						strval(getFieldAssoc_16(TAD_DEATHS, result, sql_result)), 
						strval(getFieldAssoc_16(TAD_DMG, result, sql_result)), 
						strval(getFieldAssoc_16(TAD_RESPECT, result, sql_result)), 
						strval(getFieldAssoc_16(TAD_WEAPONS_0, result, sql_result)),
						strval(getFieldAssoc_16(TAD_WEAPONS_1, result, sql_result)),
						strval(getFieldAssoc_16(TAD_WEAPONS_2, result, sql_result)),
						strval(getFieldAssoc_16(TAD_WEAPONS_3, result, sql_result)),
						strval(getFieldAssoc_16(TAD_WEAPONS_4, result, sql_result)),
						strval(getFieldAssoc_16(TAD_WEAPONS_5, result, sql_result)),
						strval(getFieldAssoc_16(TAD_WEAPONS_6, result, sql_result)),
						strval(getFieldAssoc_16(TAD_WEAPONS_7, result, sql_result)),
						strval(getFieldAssoc_16(TAD_WEAPONS_8, result, sql_result)),
						strval(getFieldAssoc_16(TAD_WEAPONS_9, result, sql_result)),
						strval(getFieldAssoc_16(TAD_WEAPONS_10, result, sql_result)),
						strval(getFieldAssoc_16(TAD_WEAPONS_11, result, sql_result)),
						strval(getFieldAssoc_16(TAD_WEAPONS_12, result, sql_result)),
						strval(getFieldAssoc_16(TAD_WEAPONS_13, result, sql_result)),
						strval(getFieldAssoc_16(TAD_WEAPONS_14, result, sql_result)),
						strval(getFieldAssoc_16(TAD_WEAPONS_15, result, sql_result)),
						strval(getFieldAssoc_16(TAD_WEAPONS_16, result, sql_result)),
						strval(getFieldAssoc_16(TAD_WEAPONS_17, result, sql_result)),
						strval(getFieldAssoc_16(TAD_WEAPONS_18, result, sql_result)),
						strval(getFieldAssoc_16(TAD_WEAPONS_19, result, sql_result)),
						strval(getFieldAssoc_16(TAD_WEAPONS_20, result, sql_result)),
						strval(getFieldAssoc_16(TAD_WEAPONS_21, result, sql_result)),
						strval(getFieldAssoc_16(TAD_WEAPONS_22, result, sql_result)),
						strval(getFieldAssoc_16(TAD_WEAPONS_23, result, sql_result)),
						strval(getFieldAssoc_16(TAD_WEAPONS_24, result, sql_result)),
						strval(getFieldAssoc_16(TAD_WEAPONS_25, result, sql_result)),
						strval(getFieldAssoc_16(TAD_WEAPONS_26, result, sql_result)),
						strval(getFieldAssoc_16(TAD_WEAPONS_27, result, sql_result)),
						strval(getFieldAssoc_16(TAD_WEAPONS_28, result, sql_result)),
						strval(getFieldAssoc_16(TAD_WEAPONS_29, result, sql_result)),
						strval(getFieldAssoc_16(TAD_WEAPONS_30, result, sql_result)),
						strval(getFieldAssoc_16(TAD_WEAPONS_31, result, sql_result)),
						strval(getFieldAssoc_16(TAD_WEAPONS_32, result, sql_result)),
						strval(getFieldAssoc_16(TAD_WEAPONS_33, result, sql_result)),
						strval(getFieldAssoc_16(TAD_WEAPONS_34, result, sql_result)),
						strval(getFieldAssoc_16(TAD_WEAPONS_35, result, sql_result)),
						strval(getFieldAssoc_16(TAD_WEAPONS_36, result, sql_result)),
						strval(getFieldAssoc_16(TAD_WEAPONS_37, result, sql_result)),
						strval(getFieldAssoc_16(TAD_WEAPONS_38, result, sql_result)),
						strval(getFieldAssoc_16(TAD_WEAPONS_39, result, sql_result)),
						strval(getFieldAssoc_16(TAD_WEAPONS_40, result, sql_result)),
						strval(getFieldAssoc_16(TAD_WEAPONS_41, result, sql_result)),
						strval(getFieldAssoc_16(TAD_WEAPONS_42, result, sql_result))
				);
				fwrite(f_open, string);
				nextRow(result, sql_result);
			}
			fclose(f_open);
			freeResult(result, sql_result);			
		}		
	} else AddToErrorLog("Top 10: Nieznaleziono folderu Top 10.");
	
	
    format(string, sizeof(string),"UPDATE `"T_ACCOUNT_DATA"` SET \
			`"TAD_KILLS"`='0',\
			`"TAD_DEATHS"`='0',\
			`"TAD_DMG"`='0',\
			`"TAD_RESPECT"`='0'\
	");
	for(new i; i <= 42; i ++) {
	    format(string, sizeof(string),"%s,`a%d`='0'", string, i);
	}
    sendQueryWithout(string);	
	
	new x;
	forplayers(i) {
		if(getPlayerUserID(i) != 0) {
			SetPlayerDeath(i, 0);
			SetPlayerKill(i, 0);
			SetPlayerDMG(i, 0);
			SetPlayerRespect(i, 0);
			SetPlayerSparingWin(i, 0);
			SetPlayerSparingLoss(i, 0);
			SetPlayerCarKill(i, 0);
			SetPlayerHeliKill(i, 0);
			for(x = 0; x <= 42; x ++) {
				SetPlayerWeaponKill(i, x, 0);
			}
			AddToPlayerLog(getPlayerUserID(i), "Wykonano reset statystyk (Reset kont)");
		}
	}
	
	format(string, sizeof(string), "Administrator '%s' wykonal reset kont.", adminname);
	AddToChatLog(string);
	
	f_open = fopen(ACC_RESET_FILE, io_append);
	format(string, 256, "acc_reset=%d\r\n(ACC-RESET - IN DATE: %s  [ %d:%02d:%02d ] | ADM: %s)", timestamp(), strData(year, month, day, " / ", false, false, true, false), hour, minute, second, adminname);
    fwrite(f_open, string);
	fclose(f_open);	
	
	SendClientMessageToAll(0x1189E1FF, " (Serwer) Wykonano reset kont!");
	return _TRUE;
}
//------------------------------------------------------------------------------
public DailyPlayerStatsReset(bool:force) {
	new bool:makeReset;
	new File:f_open, string[128];
	new year, month, day, hour, minute, second, t_stamp = timestamp();
	gettime(hour, minute, second);
	getdate(year, month, day);
	
	if((makeReset = force) == false) {
		if(!fexist(DAILY_STATS_RESET_FILE)) {
			makeReset = true;
		} else {	
			f_open = fopen(DAILY_STATS_RESET_FILE, io_read);
			new l_stamp;
			while(fread(f_open, string, sizeof(string))) {
				DeleteNewLine(string);
				if(strlen(string) > 11) {
					if(strcmp(string, "last_reset=", false, 11) == 0) {
					    l_stamp = strval(string[11]);
					    break;
					}				
				}
			}
			fclose(f_open);
			if(l_stamp <= 0 or t_stamp - l_stamp < 0 or t_stamp - l_stamp >= 82800) {
				makeReset = true;
			}  	
		}
	}
	
	if(makeReset == true) {
		new DBResult:result, Result:sql_result, rows;
		f_open = fopen(DAILY_STATS_RESET_FILE, io_write);
		format(string, sizeof(string),"last_reset=%d\r\n(INFO - IN DATE: %s  [ %d:%02d:%02d ])", t_stamp, strData(year, month, day, " / ", false, false, true, false), hour, minute, second);
		fwrite(f_open, string);
		fclose(f_open);	
		
		result = sendQueryResult("SELECT `"TAD_UID"` FROM `"T_ACCOUNT_DATA"` ORDER BY `"TAD_RESPECT"` DESC", sql_result);
		if((rows = numRows(result, sql_result)) > 0) {
			for(new i; i < rows; i ++) {
				format(string, sizeof(string),"UPDATE `"T_ACCOUNT_DATA"` SET `"TAD_YESTERDAY_RANKPOS"`='%d',`"TAD_TODAY_KILLS"`='0',`"TAD_TODAY_DEATHS"`='0',`"TAD_TODAY_RESPECT"`='0',`"TAD_TODAY_DMG"`='0' WHERE `"TAD_UID"`='%d'", i + 1, strval(getFieldAssoc_8(TAD_UID, result, sql_result)));
				sendQueryWithout(string);
				nextRow(result, sql_result);
			}
		}
		freeResult(result, sql_result);
	}
}
//------------------------------------------------------------------------------
public DeleteAccountData(userid) {
	new string[128];
	format(string, sizeof(string), "DELETE FROM `"T_ACCOUNT_DATA"` WHERE `"TAD_UID"`='%d'", userid);
	sendQueryWithout(string);
}
//------------------------------------------------------------------------------
public CreateAccountDataTable() {
	new string[2048];
    format(string, sizeof(string), "CREATE TABLE IF NOT EXISTS `"T_ACCOUNT_DATA"` (\
					`"TAD_UID"` INT PRIMARY KEY,\
					`"TAD_SETTINGS"` VARCHAR(64) DEFAULT '0',\
			");
	format(string, sizeof(string),"%s\
					`"TAD_TODAY_KILLS"` INT DEFAULT '0',\
					`"TAD_TODAY_DEATHS"` INT DEFAULT '0',\
					`"TAD_TODAY_RESPECT"` INT DEFAULT '0',\
					`"TAD_TODAY_DMG"` INT DEFAULT '0',\
					`"TAD_YESTERDAY_RANKPOS"` INT DEFAULT '0',\
				", string);
	format(string, sizeof(string),"%s\
					`"TAD_KILLS"` INT DEFAULT '0',\
					`"TAD_DEATHS"` INT DEFAULT '0',\
					`"TAD_DMG"` INT DEFAULT '0',\
					`"TAD_RESPECT"` INT DEFAULT '0',\
					`"TAD_SPARING_WIN"` INT DEFAULT '0',\
					`"TAD_SPARING_LOSS"` INT DEFAULT '0',\
					`"TAD_CAR_KILL"` INT DEFAULT '0',\
					`"TAD_HELI_KILL"` INT DEFAULT '0',\
				", string);
	format(string, sizeof(string), "%s\
					`"TAD_WEAPONS_0"` INT DEFAULT '0',\
					`"TAD_WEAPONS_1"` INT DEFAULT '0',\
					`"TAD_WEAPONS_2"` INT DEFAULT '0',\
					`"TAD_WEAPONS_3"` INT DEFAULT '0',\
					`"TAD_WEAPONS_4"` INT DEFAULT '0',\
					`"TAD_WEAPONS_5"` INT DEFAULT '0',\
					`"TAD_WEAPONS_6"` INT DEFAULT '0',\
					`"TAD_WEAPONS_7"` INT DEFAULT '0',\
					`"TAD_WEAPONS_8"` INT DEFAULT '0',\
					`"TAD_WEAPONS_9"` INT DEFAULT '0',\
					`"TAD_WEAPONS_10"` INT DEFAULT '0',\
					`"TAD_WEAPONS_11"` INT DEFAULT '0',\
					`"TAD_WEAPONS_12"` INT DEFAULT '0',\
				", string);
	format(string, sizeof(string), "%s\
					`"TAD_WEAPONS_13"` INT DEFAULT '0',\
					`"TAD_WEAPONS_14"` INT DEFAULT '0',\
					`"TAD_WEAPONS_15"` INT DEFAULT '0',\
					`"TAD_WEAPONS_16"` INT DEFAULT '0',\
					`"TAD_WEAPONS_17"` INT DEFAULT '0',\
					`"TAD_WEAPONS_18"` INT DEFAULT '0',\
					`"TAD_WEAPONS_19"` INT DEFAULT '0',\
					`"TAD_WEAPONS_20"` INT DEFAULT '0',\
					`"TAD_WEAPONS_21"` INT DEFAULT '0',\
					`"TAD_WEAPONS_22"` INT DEFAULT '0',\
					`"TAD_WEAPONS_23"` INT DEFAULT '0',\
					`"TAD_WEAPONS_24"` INT DEFAULT '0',\
				", string);
	format(string, sizeof(string), "%s\
					`"TAD_WEAPONS_25"` INT DEFAULT '0',\
					`"TAD_WEAPONS_26"` INT DEFAULT '0',\
					`"TAD_WEAPONS_27"` INT DEFAULT '0',\
					`"TAD_WEAPONS_28"` INT DEFAULT '0',\
					`"TAD_WEAPONS_29"` INT DEFAULT '0',\
					`"TAD_WEAPONS_30"` INT DEFAULT '0',\
					`"TAD_WEAPONS_31"` INT DEFAULT '0',\
					`"TAD_WEAPONS_32"` INT DEFAULT '0',\
					`"TAD_WEAPONS_33"` INT DEFAULT '0',\
					`"TAD_WEAPONS_34"` INT DEFAULT '0',\
					`"TAD_WEAPONS_35"` INT DEFAULT '0',\
					`"TAD_WEAPONS_36"` INT DEFAULT '0',\
				", string);
	format(string, sizeof(string), "%s\
					`"TAD_WEAPONS_37"` INT DEFAULT '0',\
					`"TAD_WEAPONS_38"` INT DEFAULT '0',\
					`"TAD_WEAPONS_39"` INT DEFAULT '0',\
					`"TAD_WEAPONS_40"` INT DEFAULT '0',\
					`"TAD_WEAPONS_41"` INT DEFAULT '0',\
					`"TAD_WEAPONS_42"` INT DEFAULT '0'\
				);", string);
				
	sendQueryWithout(string);
	return 1;
}