/*
	___________________________________________
	___________________________________________
	
	
	___________________________________________
	getPlayerName(playerid)
	___________________________________________
	setPlayerName(playerid, name[])
	___________________________________________
	getPlayerIp(playerid)
	___________________________________________
	savePlayerIp(playerid)
	___________________________________________
	getSavedPlayerIp(playerid)
	___________________________________________
	savePlayerConnectTime(playerid)
	___________________________________________
	getPlayerConnectTime(playerid)
	___________________________________________
	SetPlayerPage(playerid, page)
	___________________________________________
	GetPlayerPage(playerid)
	___________________________________________
	SetHelpVarValue(playerid, varid, value)
	___________________________________________
	GetHelpVarValue(playerid, varid)
	___________________________________________
	DeleteHelpVarValue(playerid, varid)
	___________________________________________
	SetHelpStringValue(playerid, varid, string[])
	___________________________________________
	GetHelpStringValue(playerid, varid)
	___________________________________________
	DeleteHelpStringValue(playerid, varid)
	___________________________________________
*/
//===============================================================
//---------------------------------------------------------------
//===============================================================
forward OnPlayerNickChange(playerid, newnick[], oldnick[]);
//-----------------------------------------------------------
new g_PlayerConnectTime[MAX_PLAYERS];
new g_PlayerSavedIP[MAX_PLAYERS][6];
//===============================================================
//---------------------------------------------------------------
//===============================================================
getPlayerName(playerid) {
	static nick[MAX_PLAYER_NAME];
	GetPlayerName(playerid, nick, MAX_PLAYER_NAME);
	return nick;
}
//-----------------------------------------------------------
setPlayerName(playerid, name[]) {
	if(IsPlayerConnected(playerid)) {
		if(IsValidNick(name)) {
			if(strcmp(getPlayerName(playerid), name) != 0) {		
				new oldName[MAX_PLAYER_NAME];
				forplayers(i) {
					if(strcmp(name, getPlayerName(i)) == 0) return _FALSE;
				}			
				GetPlayerName(playerid, oldName, MAX_PLAYER_NAME);				
				CallRemoteFunction("OnPlayerNickChange", "dss", playerid, name, oldName);
				SetPlayerName(playerid, name);
				return _TRUE;
			}
		}		
	}
	return _FALSE;
}
//-----------------------------------------------------------
getPlayerIp(playerid) {
	new ip[16];
	GetPlayerIp(playerid, ip, sizeof(ip));
	return ip;
}
//-----------------------------------------------------------
savePlayerIp(playerid) {
	strpack(g_PlayerSavedIP[playerid], getPlayerIp(playerid), 5);
	return _TRUE;
}
//-----------------------------------------------------------
getSavedPlayerIp(playerid) {
	new ip[16];
	strunpack(ip, g_PlayerSavedIP[playerid], 16);
	return ip;
}
//===========================================================
setPlayerTabListInfo(playerid, tablistid) {
	SetPVarInt(playerid, PV_TAB_LIST_INFO, tablistid);
	return 1;
}
//-----------------------------------------------------------
getPlayerTabListInfo(playerid) {
	return GetPVarInt(playerid, PV_TAB_LIST_INFO);
}
//===========================================================
savePlayerConnectTime(playerid) {
	if(IsPlayerConnected(playerid)) {
		g_PlayerConnectTime[playerid] = timestamp();
		return _TRUE;
	}
	return _FALSE;
}
//-----------------------------------------------------------
getPlayerConnectTime(playerid) {
	if(IsPlayerConnected(playerid)) {
		return timestamp() - g_PlayerConnectTime[playerid];
	}
	return _FALSE;
}
//===========================================================
SetPlayerPage(playerid, page) {
	if(page >= 0) {
		SetPVarInt(playerid, PV_PLAYER_PAGE, page);
		return _TRUE;
	}
	return _FALSE;
}
//-----------------------------------------------------------
GetPlayerPage(playerid) {
	return GetPVarInt(playerid, PV_PLAYER_PAGE);
}
//===========================================================
#define SetPlayerHelpVar(%1,%2,%3) SetHelpVarValue(%1, %2, %3)
SetHelpVarValue(playerid, varid, value) {
	if(0 <= varid < 100) {
		new var_string[16];
		format(var_string, sizeof(var_string), "PV_HELP_%d", varid);
		SetPVarInt(playerid, var_string, value);
		return _TRUE;
	}
	return _FALSE;
}
//-----------------------------------------------------------
#define GetHelpVar(%1,%2) GetHelpVarValue(%1, %2)
GetHelpVarValue(playerid, varid) {
	if(0 <= varid < 100) {
		new var_string[16];
		format(var_string, sizeof(var_string), "PV_HELP_%d", varid);
		return GetPVarInt(playerid, var_string);
	}
	return _FALSE;
}
//-----------------------------------------------------------
stock DeleteHelpVarValue(playerid, varid) {
	if(0 <= varid < 100) {
		new var_string[16];
		format(var_string, sizeof(var_string), "PV_HELP_%d", varid);
		return DeletePVar(playerid, var_string);
	}
	return _FALSE;
}
//-----------------------------------------------------------
SetHelpStringValue(playerid, varid, string[]) {
	if(0 <= varid < 100) {
		new var_string[16];
		format(var_string, sizeof(var_string), "PVS_HELP_%d", varid);
		SetPVarString(playerid, var_string, string);
		return _TRUE;
	}
	return _FALSE;	
}
//-----------------------------------------------------------
GetHelpStringValue(playerid, varid) {
	new string[128];
	if(0 <= varid < 100) {
		new var_string[16];		
		format(var_string, sizeof(var_string), "PVS_HELP_%d", varid);
		GetPVarString(playerid, var_string, string, sizeof(string));
	}
	return string;	
}
//-----------------------------------------------------------
stock DeleteHelpStringValue(playerid, varid) {
	if(0 <= varid < 100) {
		new var_string[16];
		format(var_string, sizeof(var_string), "PVS_HELP_%d", varid);
		return DeletePVar(playerid, var_string);
	}
	return _FALSE;
}
//===========================================================
#define GetPlayerRconLoginStatus(%1) GetPVarInt(%1, PV_RCON_LOGIN)
#define SetPlayerRconLoginStatus(%1,%2) SetPVarInt(%1, PV_RCON_LOGIN, %2)
#define GetPlayerRconFailLogins(%1) GetPVarInt(%1, PV_RCON_FAIL_LOGIN)
#define AddPlayerRconFailLogin(%1) SetPVarInt(%1, PV_RCON_FAIL_LOGIN, GetPVarInt(%1, PV_RCON_FAIL_LOGIN) + 1)
#define ResetPlayerRconFailLogin(%1) DeletePVar(%1, PV_RCON_FAIL_LOGIN)

//===============================================================
//---------------------------------------------------------------
//===============================================================
#define PV_ACC_DEATH			"AccDeath"
#define	PV_ACC_KILL				"AccKill"
#define	PV_ACC_DMG				"AccDMG"
#define	PV_ACC_RESPECT			"AccRespect"
#define	PV_ACC_SPARING_WIN		"AccSparingWin"
#define	PV_ACC_SPARING_LOSS		"AccSparingLoss"
#define	PV_ACC_CAR_KILL			"AccCarKill"
#define	PV_ACC_HELI_KILL		"AccHeliKill"
#define PV_ACC_WEAP_PART		"AccWeap"
//---------------------------------------------------------------
stock AddPlayerDeath(playerid, add = 1) 			SetPVarInt(playerid, PV_ACC_DEATH, GetPVarInt(playerid, PV_ACC_DEATH) + add);
stock AddPlayerKill(playerid, add = 1) 				SetPVarInt(playerid, PV_ACC_KILL, GetPVarInt(playerid, PV_ACC_KILL) + add);
stock AddPlayerDMG(playerid, add = 1) 				SetPVarInt(playerid, PV_ACC_DMG, GetPVarInt(playerid, PV_ACC_DMG) + add);
stock AddPlayerRespect(playerid, add = 1) 			SetPVarInt(playerid, PV_ACC_RESPECT, GetPVarInt(playerid, PV_ACC_RESPECT) + add);
stock AddPlayerSparingWin(playerid, add = 1)		SetPVarInt(playerid, PV_ACC_SPARING_WIN, GetPVarInt(playerid, PV_ACC_SPARING_WIN) + add);
stock AddPlayerSparingLoss(playerid, add = 1) 		SetPVarInt(playerid, PV_ACC_SPARING_LOSS, GetPVarInt(playerid, PV_ACC_SPARING_LOSS) + add);
stock AddPlayerCarKill(playerid, add = 1)			SetPVarInt(playerid, PV_ACC_CAR_KILL, GetPVarInt(playerid, PV_ACC_CAR_KILL) + add);
stock AddPlayerHeliKill(playerid, add = 1) 			SetPVarInt(playerid, PV_ACC_HELI_KILL, GetPVarInt(playerid, PV_ACC_HELI_KILL) + add);
stock AddPlayerWeaponKill(playerid, weaponid, add = 1) {
	if(42 >= weaponid >= 0) {
		new string[16];
		format(string, sizeof(string), PV_ACC_WEAP_PART"_%d", weaponid);
		SetPVarInt(playerid, string, GetPVarInt(playerid, string) + add);
		return _TRUE;
	}
	return _FALSE;
}
//---------------------------------------------------------------
stock GetPlayerDeath(playerid) 			return GetPVarInt(playerid, PV_ACC_DEATH);
stock GetPlayerKill(playerid) 			return GetPVarInt(playerid, PV_ACC_KILL);
stock GetPlayerDMG(playerid) 			return GetPVarInt(playerid, PV_ACC_DMG);
stock GetPlayerRespect(playerid) 		return GetPVarInt(playerid, PV_ACC_RESPECT);
stock GetPlayerSparingWin(playerid) 	return GetPVarInt(playerid, PV_ACC_SPARING_WIN);
stock GetPlayerSparingLoss(playerid) 	return GetPVarInt(playerid, PV_ACC_SPARING_LOSS);
stock GetPlayerCarKill(playerid)		return GetPVarInt(playerid, PV_ACC_CAR_KILL);
stock GetPlayerHeliKill(playerid)		return GetPVarInt(playerid, PV_ACC_HELI_KILL);
stock GetPlayerWeaponKill(playerid, weaponid) {
	if(42 >= weaponid >= 0) {
		new string[16];
		format(string, sizeof(string), PV_ACC_WEAP_PART"_%d", weaponid);
		return GetPVarInt(playerid, string);
	}
	return _FALSE;
}
//---------------------------------------------------------------
stock SetPlayerDeath(playerid, set) 		SetPVarInt(playerid, PV_ACC_DEATH, set);
stock SetPlayerKill(playerid, set)			SetPVarInt(playerid, PV_ACC_KILL, set);
stock SetPlayerDMG(playerid, set) 			SetPVarInt(playerid, PV_ACC_DMG, set);
stock SetPlayerRespect(playerid, set) 		SetPVarInt(playerid, PV_ACC_RESPECT, set);
stock SetPlayerSparingWin(playerid, set) 	SetPVarInt(playerid, PV_ACC_SPARING_WIN, set);
stock SetPlayerSparingLoss(playerid, set) 	SetPVarInt(playerid, PV_ACC_SPARING_LOSS, set);
stock SetPlayerCarKill(playerid, set)		SetPVarInt(playerid, PV_ACC_CAR_KILL, set);
stock SetPlayerHeliKill(playerid, set)		SetPVarInt(playerid, PV_ACC_HELI_KILL, set);
stock SetPlayerWeaponKill(playerid, weaponid, set) {
	if(42 >= weaponid >= 0) {
		new string[16];
		format(string, sizeof(string), PV_ACC_WEAP_PART"_%d", weaponid);
		SetPVarInt(playerid, string, set);
		return _TRUE;
	}
	return _FALSE;
}
//===============================================================
//---------------------------------------------------------------
//===============================================================
new p_FPSWarnings[MAX_PLAYERS];
new p_PingWarnings[MAX_PLAYERS];
new p_PLossWarnings[MAX_PLAYERS];
//===============================================================
//---------------------------------------------------------------
//===============================================================
#define TakePlayerVIPTime(%1,%2)		SetPVarInt(%1, PV_LOGIN_VIP_TIME, GetPVarInt(%1, PV_LOGIN_VIP_TIME) - %2)
#define	AddPlayerVIPTime(%1,%2)			SetPVarInt(%1, PV_LOGIN_VIP_TIME, GetPVarInt(%1, PV_LOGIN_VIP_TIME) + %2)
#define SetPlayerVIPTime(%1,%2)			SetPVarInt(%1, PV_LOGIN_VIP_TIME, %2)
#define GetPlayerVIPTime(%1)			GetPVarInt(%1, PV_LOGIN_VIP_TIME)
#define AddPlayerSelfPoints(%1,%2)		SetPVarInt(%1, PV_LOGIN_VIP_POINTS, GetPVarInt(%1, PV_LOGIN_VIP_POINTS) + %2)
#define TakePlayerSelfPoints(%1,%2)		SetPVarInt(%1, PV_LOGIN_VIP_POINTS, GetPVarInt(%1, PV_LOGIN_VIP_POINTS) - %2)
#define GetPlayerVIPSelfPoints(%1)		GetPVarInt(%1, PV_LOGIN_VIP_POINTS)
#define SetPlayerVIPSelfPoints(%1,%2)	SetPVarInt(%1, PV_LOGIN_VIP_POINTS, %2)
#define TakePlayerBonusPoints(%1,%2)	SetPVarInt(%1, PV_LOGIN_VIP_BONUS_POINTS, GetPVarInt(%1, PV_LOGIN_VIP_BONUS_POINTS) - %2)
#define AddPlayerBonusPoints(%1,%2)		SetPVarInt(%1, PV_LOGIN_VIP_BONUS_POINTS, GetPVarInt(%1, PV_LOGIN_VIP_BONUS_POINTS) + %2)
#define SetPlayerBonusPoints(%1,%2)		SetPVarInt(%1, PV_LOGIN_VIP_BONUS_POINTS, %2)
#define GetPlayerVIPBonusPoints(%1)		GetPVarInt(%1, PV_LOGIN_VIP_BONUS_POINTS)
#define GetPlayerVIPPoints(%1)			GetPVarInt(%1, PV_LOGIN_VIP_POINTS) + GetPVarInt(%1, PV_LOGIN_VIP_BONUS_POINTS)

IsVIP(playerid) return GetPlayerVIPTime(playerid) > timestamp() ? _TRUE : _FALSE;                                                    
//===============================================================
//---------------------------------------------------------------
//===============================================================
#define PV_PRIV_MESSAGES_STATUS	"PlayerPrivMessagesStatus"
//---------------------------------------------------------------
GetPlayerPMessagesStatus(playerid) return GetPVarInt(playerid, PV_PRIV_MESSAGES_STATUS) == 0 ? 1 : 0;
SetPlayerPMessagesStatus(playerid, bool:status) {
	SetPVarInt(playerid, PV_PRIV_MESSAGES_STATUS, status == true ? 0 : 1);
}
//---------------------------------------------------------------
GetPlayerPMessagesSpec(playerid) return -getSettingIntValueByIndex(s_PrivMessagesSpecID) < IsAdmin(playerid) < getSettingIntValueByIndex(s_PrivMessagesSpecID) ? 0 : GetPVarInt(playerid, PV_PRIV_MESSAGES_SPEC);
SetPlayerPMessagesSpec(playerid, bool:status) {
	SetPVarInt(playerid, PV_PRIV_MESSAGES_SPEC, _:status);
}
//---------------------------------------------------------------
GetPlayerPMFromPlayerStatus(playerid, fromid) {
	new lStr[8];
    format(lStr, 8, "PM_%d", fromid);
    return GetPVarType(playerid, lStr) == 0 ? _ACTIVE : _NONACTIVE;
}

//------------------------------------------------------------------------------
SetPlayerPMFromPlayerStatus(playerid, fromid, status = _ACTIVE) {
	if(IsPlayerConnected(playerid)) {
  	  	if(playerid != fromid) {
		    new lStr[8];
	        format(lStr, 8, "PM_%d", fromid);
	        if(status == _ACTIVE) {
				if(GetPVarType(playerid, lStr) == 0) return -2;
				DeletePVar(playerid, lStr);
				return IsPlayerConnected(fromid) ? 1 : 0;
	        } else {
	            if(!IsPlayerConnected(fromid)) return 0;
                if(GetPVarType(playerid, lStr) != 0) return -2;
                SetPVarInt(playerid, lStr, 1);
                return 1;
	        }
	    }
	    return -1;
	}
	return 0;
}
//------------------------------------------------------------------------------
#define	PV_PRIVMESSAGE_SOUNDID	"PrivMessageSoundID"
GetPlayerPMSoundID(playerid) {
	return GetPVarInt(playerid, PV_PRIVMESSAGE_SOUNDID) >= sizeof(privMessagesSounds) ? 0 : GetPVarInt(playerid, PV_PRIVMESSAGE_SOUNDID);
}
//------------------------------------------------------------------------------
SetPlayerPMSoundID(playerid, soundid) {
	if(sizeof(privMessagesSounds) > soundid >= 0) {
		SetPVarInt(playerid, PV_PRIVMESSAGE_SOUNDID, soundid);
		return _TRUE;
	}
	return _FALSE;
}
//------------------------------------------------------------------------------
#define PV_LAST_PMESSAGE_SENDERID	"LastPrivMessageSenderID"
CMD:priv(playerid, cmdtext[]) return cmd_pm(playerid, cmdtext);
CMD:pw(playerid, cmdtext[]) return cmd_pm(playerid, cmdtext);
CMD:pm(playerid, cmdtext[]) {
	if(getSettingIntValueByIndex(s_PrivMessagesID) == 0) return 0;
	if(getPlayerLoginStatus(playerid) == LOGIN_STATUS_NOTLOGGED or getPlayerLoginStatus(playerid) == LOGIN_STATUS_NON) return _TRUE;
	if(!isnull(cmdtext)) {
		new toPlayerID, message[128];
	    if(sscanf(cmdtext, "p< >ds[128]", toPlayerID, message)) SendClientMessage(playerid, COLOR_DIALOG_BODY," (Prywatne Wiadomosci) Uzyj: '"C_WHITE"/pm [ID Gracza] [Tresc]"TEXT_DIALOG_BODY"' zeby wyslac prywatna wiadomosc.");
		else {
			if(IsPlayerConnected(toPlayerID)) {
				if(playerid != toPlayerID) {
					new string[200];
					if(checkPlayerBySpam(playerid) == _TRUE) {
						format(string, sizeof(string)," (Anty Spam) Musisz poczekac %d sekund przed wyslaniem kolejnej wiadomosci.", getPlayerAntySpamMessageTime(playerid) - timestamp());
						SendClientMessage(playerid, 0xFF0000FF, string);						
					} else {
						if(IsAdmin(playerid) > 0 or (GetPlayerPMessagesStatus(playerid) == _TRUE and GetPlayerPMFromPlayerStatus(playerid, toPlayerID) == _ACTIVE)) {
							if((GetPlayerPMessagesStatus(toPlayerID) == _TRUE and GetPlayerPMFromPlayerStatus(toPlayerID, playerid) == _ACTIVE) or IsAdmin(playerid) > 0) {
								DeleteFirstSpaces(message);
								DeleteDoubleSpaces(message);								
								if(strlen(message) > 0) {
									new Text1[40], Text2[128];
									new bool:TwoParts;	
														
									strmid(Text1, message, 0, 40);
			                        if(strlen(Text1) > 35) {
			                            strdel(Text1, 35, 55);
			                            strins(Text2, message[35], 0);
			                            strins(Text1, " ...", 35);
			                            strins(Text2, "       ... ", 0);
			                            TwoParts = true;
			                        }								
									
			                        format(string, 200, "   (Nowa wiadomosc)  "C_WHITE"%s [ID: %d] {F2B526}: %s", getPlayerName(playerid), playerid, Text1);
									SendClientMessage(toPlayerID, COLOR_PM_REVEIVED, " ");		
									SendClientMessage(toPlayerID, 0xF2B526FF, string);			
									if(TwoParts == true) SendClientMessage(toPlayerID, 0xF2B526FF, Text2);	
									if(GetPVarType(toPlayerID, PV_LAST_PMESSAGE_SENDERID) == 0) {
										SendClientMessage(toPlayerID, COLOR_PM_REVEIVED, " (Info) Uzyj '"C_WHITE"/rpm [Wiadomosc]"TEXT_PM_REVEIVED"' zeby odpowiadac na prywatna wiadomosc.");
									}									
									SetPVarInt(toPlayerID, PV_LAST_PMESSAGE_SENDERID, playerid);									
									PlayerPlaySound(toPlayerID, privMessagesSounds[GetPlayerPMSoundID(toPlayerID)][SOUND_ID], 0.0, 0.0, 0.0);
									SendClientMessage(toPlayerID, COLOR_DIALOG_HEAD, " ");	
									
									format(string, 200, " (Wyslano wiadomosc) "C_WHITE"%s [ID: %d] {FEDD6B}: %s", getPlayerName(toPlayerID), toPlayerID, Text1);
									SendClientMessage(playerid, 0xFEDD6BFF, string);
									if(TwoParts == true) SendClientMessage(playerid, 0xFEDD6BFF, Text2);
									
									if(getSettingIntValueByIndex(s_PrivMessagesSpecID) != 0) {
										format(string, 200, " ( PM aSpec ) %s [ID: %d] --> %s [ID: %d] "TEXT_PM_SPEC": %s", getPlayerName(playerid), playerid, getPlayerName(toPlayerID), toPlayerID, Text1);

										forplayers(i) {
											if(GetPlayerPMessagesSpec(i) != _FALSE and i != toPlayerID && i != playerid) {
												SendClientMessage(i, COLOR_PM_SPEC, string);
												if(TwoParts == true) SendClientMessage(i, COLOR_PM_SPEC, Text2);
											}
										}								 	
									}
									format(string, sizeof(string), " [PM] %s (ID: %d) --> %s (ID: %d): %s", getPlayerName(playerid), playerid, getPlayerName(toPlayerID), toPlayerID, message);
									AddToChatLog(string);	
									
								} else SendClientMessage(playerid, COLOR_DIALOG_BODY," (Prywatne Wiadomosci) Nie mozesz wyslac pustej wiadomosci.");							
							} else SendClientMessage(playerid, COLOR_DIALOG_BODY," (Prywatne Wiadomosci) Wybrany gracz ma wylaczone prywatne wiadomosci.");
						} else SendClientMessage(playerid, COLOR_DIALOG_BODY," (Prywatne Wiadomosci) Masz wylaczone globalne prywatne wiadomosci lub wylaczyles(as) je dla wybranego gracza.");
					}
				} else SendClientMessage(playerid, COLOR_DIALOG_BODY," (Prywatne Wiadomosci) Nie mozesz wysylac wiadomosci do samego(ej) siebie.");
			} else SendClientMessage(playerid, COLOR_DIALOG_BODY," (Prywatne Wiadomosci) Podane ID gracza nie jest uzywane.");
		} 
	} else SendClientMessage(playerid, COLOR_DIALOG_BODY," (Prywatne Wiadomosci) Uzyj: '"C_WHITE"/pm [ID Gracza] [Tresc]"TEXT_DIALOG_BODY"' zeby wyslac prywatna wiadomosc.");
	return _TRUE;
}
//------------------------------------------------------------------------------
CMD:rpm(playerid, cmdtext[]) {
	if(getSettingIntValueByIndex(s_PrivMessagesID) == 0) return 0;
	if(GetPVarType(playerid, PV_LAST_PMESSAGE_SENDERID) == 1) {
		new toPlayerID;
		if(IsPlayerConnected((toPlayerID = GetPVarInt(playerid, PV_LAST_PMESSAGE_SENDERID))) != -1) {
			if(!isnull(cmdtext)) {
				new string[135];
				format(string, sizeof(string), "%d %s", toPlayerID, cmdtext);
				cmd_pm(playerid, string);
			} else SendClientMessage(playerid, COLOR_DIALOG_BODY," (Odp. na wiadomosc) Uzyj: '"C_WHITE"/rpm [Wiadomosc]"TEXT_DIALOG_BODY"' zeby odpowiedziec na ostatnia prywatna wiadomosc.");
		} else SendClientMessage(playerid, COLOR_DIALOG_BODY," (Odp. na wiadomosc) Gracz, od ktorego ostatnio otrzymales(as) wiadomosc, jest Off-Line.");
	} else SendClientMessage(playerid, COLOR_DIALOG_BODY," (Odp. na wiadomosc) Ostatnio nie dostales(as) prywatnej wiadomosci.");
	return _TRUE;
}
//===============================================================
//---------------------------------------------------------------
//===============================================================
CMD:help(playerid) return cmd_pomoc(playerid);
CMD:pomoc(playerid) {
	ShowPlayerHelp(playerid, -1);
	return _TRUE;
}
//---------------------------------------------------------------
forward ShowPlayerHelp(playerid, listitem);
public ShowPlayerHelp(playerid, listitem) {
	switch(listitem) {
		case 0: {
			new string[600];
			new DBResult: result, Result:sql_result;
			new accounts;
			result = sendQueryResult("SELECT `"TK_UID"` FROM `"T_KONTA"`", sql_result);
			accounts = numRows(result, sql_result);
			freeResult(result, sql_result);
			
			format(string, sizeof(string), "\
					Nazwa systemu: "C_WHITE"Admin System\n\
					"TEXT_DIALOG_HEAD"Wersja systemu: "C_WHITE""_VERSION"\n\
					"TEXT_DIALOG_HEAD"Data ost. aktualizacji: "C_WHITE""_TIME"\n\
					"TEXT_DIALOG_HEAD"Autor: "C_WHITE"AxL_\n\n\
					"TEXT_DIALOG_HEAD"Zarejestrowanych kont: "C_WHITE"%d\n\
					"TEXT_DIALOG_HEAD"Typ rejestracji: "C_WHITE"%s\n\
					"TEXT_DIALOG_HEAD"Maks. czas nieaktywnego konta: "C_WHITE"%d dni\n\
					",
				accounts,
				getSettingIntValueByIndex(s_RegisterObligatoryID) == 0 ? ("Dobrowolna") : getSettingIntValueByIndex(s_RegisterObligatoryID) == 1 ? ("Obowiazkowa") : ("Wylaczona"),
				getSettingIntValueByIndex(s_LoginDeletingDaysID)
			);
			
			format(string, sizeof(string), "%s\
					"TEXT_DIALOG_HEAD"Automatyczne operacje cykliczne: "C_WHITE"%s\n\
					"TEXT_DIALOG_HEAD"Automatyczny reset kont: "C_WHITE"%s\n\n\
					"TEXT_DIALOG_HEAD"Maksymalny dopuszczalny ping: "C_WHITE"%d\n\
					"TEXT_DIALOG_HEAD"Minimalne dopuszczalne FPS'y: "C_WHITE"%d\n\
					"TEXT_DIALOG_HEAD"Maksymalne tracone pakiety: "C_WHITE"%d proc.\n \
					", string,
				getSettingIntValueByIndex(s_AutomaticCyclicOps) == 1 ? ("Tak") : ("Nie"),
				getSettingIntValueByIndex(s_AutomaticAccReset) == 1 ? ("Tak") : ("Nie"),
				getSettingIntValueByIndex(s_MaxPingID),
				getSettingIntValueByIndex(s_MinFPSID),
				getSettingIntValueByIndex(s_MaxPLossID)			
			);
			ShowPlayerInfoDialog(playerid, BACK_HELP_MENU, "Pomoc - Informacje o systemie", string);
		}
		case 1: ShowPlayerSystemCommands(playerid);
		case 2: {
			if(CallRemoteFunction("GameModeHelp", "dd", playerid, 1) == 0) ShowPlayerInfoDialog(playerid, BACK_HELP_MENU, "Pomoc - Informacje GameModu", "Gamemod nie dostarcza zadnych informacji.");	
		}
		default: ShowPlayerDialogEx(playerid, DIALOG_HELP_MENU, DIALOG_STYLE_LIST, "Pomoc", "1) Informacje o systemie\n2) Komendy systemu\n3) Informacje GameModu", "Dalej", "Wyjdz");
	}
	return _TRUE;
}
//---------------------------------------------------------------
ShowPlayerSystemCommands(playerid, listitem = -1) {
	switch(listitem) {
		case 0: ShowPlayerInfoDialog(playerid, BACK_HELP_CMD_MENU, "Komendy systemu - Zarejestruj", "Komenda: "C_WHITE"/zarejestruj\n"TEXT_DIALOG_HEAD"Parametry: "C_WHITE"Brak\n"TEXT_DIALOG_HEAD"Opis: "TEXT_DIALOG_BODY"Komenda sluzaca do rejestracji Twojego nicku na serwerze.\nZapisywane beda Twoje statystyki i ustawienia.");
		case 1: ShowPlayerInfoDialog(playerid, BACK_HELP_CMD_MENU, "Komendy systemu - Konto", "Komenda: "C_WHITE"/konto\n"TEXT_DIALOG_HEAD"Parametry: "C_WHITE"Brak\n"TEXT_DIALOG_HEAD"Opis: "TEXT_DIALOG_BODY"Komenda pozwalajaca na zarzadzanie zarejestrowanym kontem gracza.");
		case 2: ShowPlayerInfoDialog(playerid, BACK_HELP_CMD_MENU, "Komendy systemu - Priv", "Komenda: "C_WHITE"/pm  /pw  /priv\n"TEXT_DIALOG_HEAD"Parametry: "C_WHITE"ID Gracza i wiadomosc\n"TEXT_DIALOG_HEAD"Opis: "TEXT_DIALOG_BODY"Komenda sluzaca do wysylania prywatnej wiadomosci do wybranego gracza.\nPrywatne wiadomosci moga byc obserwowane przez administracje z ranga HA i wyzsza.");
		case 3: ShowPlayerInfoDialog(playerid, BACK_HELP_CMD_MENU, "Komendy systemu - Resp", "Komenda: "C_WHITE"/rpm\n"TEXT_DIALOG_HEAD"Parametry: "C_WHITE"Wiadomosc\n"TEXT_DIALOG_HEAD"Opis: "TEXT_DIALOG_BODY"Komenda sluzaca do szybkiej odpowiedzi na ostatnia prywatna wiadomosc.");
		case 4: ShowPlayerInfoDialog(playerid, BACK_HELP_CMD_MENU, "Komendy systemu - Admins", "Komenda: "C_WHITE"/admins\n"TEXT_DIALOG_HEAD"Parametry: "C_WHITE"Brak\n"TEXT_DIALOG_HEAD"Opis: "TEXT_DIALOG_BODY"Komenda pokazujaca liste administratorow OnLine. Administratorzy z ranga\nHead Admin i wyzsza, maja mozliwosc ukrycia swojej obecnosci na serwerze.");
		case 5: ShowPlayerInfoDialog(playerid, BACK_HELP_CMD_MENU, "Komendy systemu - Admin List", "Komenda: "C_WHITE"/alist\n"TEXT_DIALOG_HEAD"Parametry: "C_WHITE"Brak\n"TEXT_DIALOG_HEAD"Opis: "TEXT_DIALOG_BODY"Komenda pokazujaca liste wszystkich administratorow serwera.");
		case 6: ShowPlayerInfoDialog(playerid, BACK_HELP_CMD_MENU, "Komendy systemu - Prefiks '@'", "Komenda: "C_WHITE"Prefiks '@'\n"TEXT_DIALOG_HEAD"Parametry: "C_WHITE"Wiadomosc\n"TEXT_DIALOG_HEAD"Opis: "TEXT_DIALOG_BODY"Komenda sluzaca do wyslania wiadomosci do administracji serwera (OnLine).\nUzycie: '"C_WHITE"@ test wiadomosci"TEXT_DIALOG_BODY"'.");
		default: ShowPlayerDialogEx(playerid, DIALOG_HELP_CMD_MENU, DIALOG_STYLE_LIST, "Pomoc - Komendy systemu", "1) Zarejestruj\n2) Konto\n3) Priv\n4) Re\n5) Admins\n6) Admin List\n7) Prefiks '@'", "Dalej", "Wroc");
	}
	return _TRUE;
}
//===============================================================
//---------------------------------------------------------------
//===============================================================
CMD:ignore(playerid, cmdtext[]) {
	new IDGracza;
	if(isnull(cmdtext) || strlen(cmdtext) > 3 || !('9' >= cmdtext[0] >= '0') || !(MAX_PLAYERS >= (IDGracza = strval(cmdtext)) >= 0)) return SendClientMessage(playerid, COLOR_SYSGREY, " (Blokada PM) Uzyj: '/ignore [ID Gracza]' zeby zablokowac lub odblokowac prywatne wiadomosci od wybranego gracza.");
	else {
		if(IsPlayerConnected(IDGracza)) {
			if(IDGracza != playerid) {
				new string[128];
				if(GetPlayerPMFromPlayerStatus(playerid, IDGracza) == _ACTIVE) {
					SetPlayerPMFromPlayerStatus(playerid, IDGracza, _NONACTIVE);
					format(string, sizeof(string)," (Blokada PM) Zablokowales(as) prywatne wiadomosci od gracza '"C_WHITE"%s"TEXT_DIALOG_HEAD"'.", getPlayerName(IDGracza));
				} else {
					SetPlayerPMFromPlayerStatus(playerid, IDGracza, _ACTIVE);
					format(string, sizeof(string)," (Blokada PM) Odblokowales(as) prywatne wiadomosci od gracza '"C_WHITE"%s"TEXT_DIALOG_HEAD"'.", getPlayerName(IDGracza));				
				}
				SendClientMessage(playerid, COLOR_DIALOG_HEAD, string);				
			} else SendClientMessage(playerid, COLOR_SYSGREY, " (Blokada PM) Nie mozesz zablokowac samego(ej) siebie.");
		} else SendClientMessage(playerid, COLOR_SYSGREY, " (Blokada PM) Niepoprawne ID gracza lub ID nie jest uzywane.");
	}
	return 1;
}
