/*
	Anty Cheat
*/
//===============================================================
//---------------------------------------------------------------
//===============================================================
/*
	1) Blokada mozliwosci gry dwoch lub wiecej graczy o tym samym IP (w przypadku polaczenia w krotkim czasie)
*/
//===============================================================
#define	MAX_REJOIN_INFOS	20
enum E_REJOIN {RE_IP[8], RE_TIMES, RE_LAST_ONE}
new reJoinSpamInfos[MAX_REJOIN_INFOS][E_REJOIN];
//===============================================================
ac_OnPlayerConnect(playerid) {
	new pIP[16];
	GetPlayerIp(playerid, pIP, sizeof(pIP));
	if(ac_ReJoinSpam(pIP) == 1) {
		if(getSettingIntValueByIndex(s_ACConnectionSpamBotStatusID) == 1) {
			for(new i, cIP[16]; i < MAX_PLAYERS; i ++) {
				if(IsPlayerConnected(i) and i != playerid and !IsPlayerNPC(i)) {
					if(getPlayerConnectTime(i) <= getSettingIntValueByIndex(s_ACConnectionSpamBotTimeID)) {
						GetPlayerIp(i, cIP, sizeof(cIP));
						if(strcmp(pIP, cIP) == 0) {
							return 0;
						}
					}
				}
			}
		}
	} else {
		new string[150];
		GetPlayerName(playerid, string, 24);
		format(string, sizeof(string), "IP %s zostalo dodane do pliku 'samp.ban' z powodu zagrozenia ataku 'rejoin-spambot' (Gracz: %s | ID: %d)", pIP, string, playerid);
		AddToBanLog(string);
		AddToAntyCheatLog(string);
		BanEx(playerid, "ReJoin spam bot");
		return -1;
	}
	return 1;
}
//---------------------------------------------------------------
ac_ReJoinSpam(ip[]) {
	if(getSettingIntValueByIndex(s_ACAntyReJoinSpamStatusID) == 1) {
		new foundedIndex = -1, bool:founded, zeroIndex = -1;
		for(new i; i < MAX_REJOIN_INFOS; i ++) {
			if(reJoinSpamInfos[i][RE_LAST_ONE] != 0) {
				if(strcmp(ip, reJoinSpamInfos[i][RE_IP]) == 0) {
					if(timestamp() - reJoinSpamInfos[i][RE_LAST_ONE] < 5) {
						if(++ reJoinSpamInfos[i][RE_TIMES] >= getSettingIntValueByIndex(s_ACAntyReJoinSpamTryID)) {
							return 0;
						}										
					} else reJoinSpamInfos[i][RE_TIMES] = 0;
					founded = true;
					reJoinSpamInfos[i][RE_LAST_ONE] = timestamp();
					break;
				}
				if(zeroIndex == -1 and (foundedIndex == -1 or foundedIndex > reJoinSpamInfos[i][RE_LAST_ONE])) {
					foundedIndex = i;
				}				
			} else zeroIndex = i; 
		}	
		if(founded == false) {
			zeroIndex = (zeroIndex == -1 ? foundedIndex : zeroIndex);
			reJoinSpamInfos[zeroIndex][RE_TIMES] = 0;
			reJoinSpamInfos[zeroIndex][RE_LAST_ONE] = timestamp();
			strpack(reJoinSpamInfos[zeroIndex][RE_IP], ip, 8);	
		}	
	}
	return 1;
}
//===============================================================
//---------------------------------------------------------------
//===============================================================
/*
	2) Blokada mozliwosci uzycia calkowicie niedozwolonych broni
*/
//===============================================================
#define TEMP_WEAPONS_FILE	"tweaponshs.txt"

#define ALLOWED_WEAPON			0
#define NOT_ALLOWED_WEAPON		1
//---------------------------------------------------------------
new ac_Weapons[46] = {ALLOWED_WEAPON, ALLOWED_WEAPON, ALLOWED_WEAPON, ...};
new bool:ac_WeaponsLoadedList = false;
new ac_WeaponTimeStamp;
//===============================================================
forward startingModeWeaponACSettings();
public startingModeWeaponACSettings() {
	LoadWeaponACSettings(TEMP_WEAPONS_FILE);
	return 1;
}
//---------------------------------------------------------------
forward LoadWeaponACSettings(file[]);
public LoadWeaponACSettings(file[]) {
	if(CallRemoteFunction("AS_RefreshWeaponList", "s", file) == 1) {
		if(fexist(file)) {
			new File:f_open = fopen(file, io_read);
			new string[128], index;
			new D, M, R, g, m, s;
			new bool:validData, weaponIndex;
			for(new i; i < sizeof(ac_Weapons); i ++) ac_Weapons[i] = ALLOWED_WEAPON;
			while(fread(f_open, string, sizeof(string))) {
				if((index = strfind(string, "\r")) != -1) string[index] = EOS;
				if((index = strfind(string, "\n")) != -1) string[index] = EOS;
				DeleteSpaces(string);
				if(strlen(string) > ((index = strfind(string, "=")) + 1) > 0) {
					if(strcmp(string, "refresh=", true, 8) == 0 and validData == false) {
						if(timestamp() - strval(string[8]) <= 5) {
							fseek(f_open, 0, seek_start);
							validData = true;
						}
					} else if(strcmp(string, "weapons=", true, 8) == 0 and validData == true) {
						strdel(string, 0, 8);
						index = 0;
						do {
							if(46 > (weaponIndex = strval(string[index == 0 ? 0 : index + 1])) > 1) {
								ac_Weapons[weaponIndex] = -1;
							}
						} while((index = strfind(string, ",", true, ++ index)) != -1 and index + 1 < strlen(string));
					}
				}
			}
			fclose(f_open);
			fremove(file);
			
			ac_WeaponsLoadedList = true;
			
			f_open = fopen(NOT_ALLOWED_WEAPONS, io_write);
			getdate(D, M, R);
			gettime(g, m, s);
			format(string, sizeof(string),"Lista niedozwolonych broni (aktualizacja: %d / %d / %d  [%d:%02d:%02d])", D, M, R, g, m, s);
			fwrite(f_open, string);
			ac_WeaponTimeStamp = timestamp();
			for(new i = 2, wName[32]; i < sizeof(ac_Weapons); i ++) {
				if(ac_Weapons[i] == -1) {
					ac_Weapons[i] = ALLOWED_WEAPON;
				} else {
					ac_Weapons[i] = NOT_ALLOWED_WEAPON;
					if(!(19 <= i <= 21)) {
						GetWeaponName(i, wName, sizeof(wName));
						format(string, sizeof(string),"\r\n%s (ID: %d)", wName, i);
						fwrite(f_open, string);
					}					
				}
			}			
			fclose(f_open);
			return 1;
		}
	}
	return 0;
}
//---------------------------------------------------------------
ac_CheckPlayerWeapon(playerid) {
	static weaponid;
	return (ac_WeaponsLoadedList == true and getSettingIntValueByIndex(s_ACAntyWeaponStatusID) == 1 and 46 > (weaponid = GetPlayerWeapon(playerid)) > 1 and !(19 <= weaponid <= 21) and ac_Weapons[weaponid] == NOT_ALLOWED_WEAPON) ? weaponid : 0;
}

//===============================================================
//---------------------------------------------------------------
//===============================================================
/*
	3) Anty spam bot
*/
//===============================================================
AntySpamBot(playerid, bool:reset = false) {
	static lastMSGTime[MAX_PLAYERS], messageCounter[MAX_PLAYERS];
	if(reset == true) {
		lastMSGTime[playerid] = messageCounter[playerid] = 0;
	} else {
		if(getSettingIntValueByIndex(s_ACAntySpamBotStatusID) == 1) {
			if(timestamp() != lastMSGTime[playerid]) {
				new messages = messageCounter[playerid];
				lastMSGTime[playerid] = timestamp();
				messageCounter[playerid] = 0;			
				if(messages >= getSettingIntValueByIndex(s_ACAntySpamBotMsgPerSecID)) {
					return messages;
				}
			} else messageCounter[playerid] ++;
		}
	}
	return 0;
}
//---------------------------------------------------------------
AntyCMDMSGSpamBot(playerid, bool:reset = false) {
	static lastMSGTime[MAX_PLAYERS], messageCounter[MAX_PLAYERS];
	if(reset == true) {
		lastMSGTime[playerid] = messageCounter[playerid] = 0;
	} else {
		if(getSettingIntValueByIndex(s_ACAntyCMDSpamBotStatusID) == 1) {
			if(timestamp() != lastMSGTime[playerid]) {
				new messages = messageCounter[playerid];
				lastMSGTime[playerid] = timestamp();
				messageCounter[playerid] = 0;			
				if(messages >= getSettingIntValueByIndex(s_ACAntyCMDSpamBotMsgPerSecID)) {			
					return messages;
				}
			} else messageCounter[playerid] ++;
		}
	}
	return 0;
}
//===============================================================
//---------------------------------------------------------------
//===============================================================
/*
	3) Anty jetpack
*/
//===============================================================
ac_AntyJetpack(playerid) return (getSettingIntValueByIndex(s_ACAntyJetpackStatusID) == 1 and GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_USEJETPACK) ? 0 : 1;
//===============================================================
//---------------------------------------------------------------
//===============================================================
/*
	4) Anty moneyhack
*/
//===============================================================
ac_AntyMoneyHack(playerid) return (getSettingIntValueByIndex(s_ACAntyMoneyHackStatusID) == 1 and GetPlayerMoney(playerid) != 0) ? 0 : 1;
//===============================================================
//---------------------------------------------------------------
//===============================================================
/*
	5) Anty fakekill
*/
//===============================================================
AntyFakeKillSpamBot(playerid, bool:reset = false) {
	static lastKillTime[MAX_PLAYERS], killCounter[MAX_PLAYERS];
	if(reset == true) {
		lastKillTime[playerid] = killCounter[playerid] = 0;
	} else {
		if(getSettingIntValueByIndex(s_ACAntyFakeKillSpamBotStatusID) == 1) {			
			if(timestamp() != lastKillTime[playerid]) {
				new messages = killCounter[playerid];
				lastKillTime[playerid] = timestamp();
				killCounter[playerid] = 0;				
				if(messages >= getSettingIntValueByIndex(s_ACAntyFakeKillsPerSecStatusID)) {			
					return messages;
				}
			} else killCounter[playerid] ++;
		}
	}
	return 0;
}
//===============================================================
//---------------------------------------------------------------
//===============================================================
/*
	5) Anty godmode
*/
//===============================================================
#define MAX_GODMODE_WARNINGS    	5
#define WAITING_FOR_UPDATES     	60  // ok. 2-3 sek. na HS'ie w trakcie walki.
//------------------------------------------------------------------------------
new Float:playerHealth[MAX_PLAYERS];
new playerTick[MAX_PLAYERS];
new playerGodModeWarnings[MAX_PLAYERS];
new playerTakeDamageInterior[MAX_PLAYERS];
new playerTakeDamageVW[MAX_PLAYERS];

/*
new TO_DELETE_StartingTime[MAX_PLAYERS];
new TO_DELETE_LastShooterID[MAX_PLAYERS];
new TO_DELETE_ShooterTeamID[MAX_PLAYERS];
new TO_DELETE_TakeDamageVW[MAX_PLAYERS];
*/
//------------------------------------------------------------------------------
ac_AntyGodmode(playerid) {
	if(getSettingIntValueByIndex(s_ACAntyGodmodeStatusID) == 1) {
		if(playerTick[playerid] > 0) {
			if(GetPlayerState(playerid) == PLAYER_STATE_SPECTATING or playerTakeDamageInterior[playerid] != GetPlayerInterior(playerid) or playerTakeDamageVW[playerid] != GetPlayerVirtualWorld(playerid)) playerTick[playerid] = 0;
			else {
				if(-- playerTick[playerid] == 0) {
					static Float:health;
					GetPlayerHealth(playerid, health);
					if(health > playerHealth[playerid]) {
						if(++ playerGodModeWarnings[playerid] >= getSettingIntValueByIndex(s_ACAntyGodmodeMaxWarnsID)) {
							playerGodModeWarnings[playerid] = 0;
							if(isPlayerConfidental(playerid) == _TRUE) {
								static string[128];
								format(string, sizeof(string), "Limit ostrzezen pomiaru HP (Godmode - AC) zostal osiagniety przez gracza %s (UID: %d)", getPlayerName(playerid), getPlayerUserID(playerid));
								AddToAntyCheatLog(string);
							} else return 0;
						}		            
					} else {
						if(playerGodModeWarnings[playerid] > 0) {
							playerGodModeWarnings[playerid] --;
						}
					}
				}
			}
		}	
	}
	return 1;
}
//---------------------------------------------------------------
ac_GodmodeStartTest(playerid, issuerid, Float: amount) {
	if(issuerid != INVALID_PLAYER_ID and playerid != issuerid and (GetPlayerTeam(playerid) != GetPlayerTeam(issuerid) or GetPlayerTeam(playerid) == NO_TEAM) and playerTick[playerid] == 0 and GetPlayerState(playerid) != PLAYER_STATE_WASTED) {
		GetPlayerHealth(playerid, playerHealth[playerid]);
	    playerHealth[playerid] = floatround((playerHealth[playerid] - amount), floatround_ceil);
    	playerTick[playerid] = getSettingIntValueByIndex(s_ACAntyGodmodeTicksID);
    	playerTakeDamageInterior[playerid] = GetPlayerInterior(playerid);
    	playerTakeDamageVW[playerid] = GetPlayerVirtualWorld(playerid);
		/*
    	TO_DELETE_StartingTime[playerid] = gettime();
    	TO_DELETE_LastShooterID[playerid] = issuerid;
    	TO_DELETE_ShooterTeamID[playerid] = GetPlayerTeam(issuerid);
    	TO_DELETE_TakeDamageVW[playerid] = GetPlayerVirtualWorld(playerid);
		*/
	}
}
//---------------------------------------------------------------
ac_ResetGodmoveVariables(playerid) {
    playerTick[playerid] = 0;
    playerHealth[playerid] = 100.0;
    playerGodModeWarnings[playerid] = 0;
}


