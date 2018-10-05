//=================================================================================
//---------------------------------------------------------------------------------
//=================================================================================

AntyDeAMX() {
        new amx[][] ={"Unarmed (Fist)","Brass K"};
        new d;
        #emit load.pri d
        #emit stor.pri d
        #pragma unused amx
}
//---------------------------------------------------------------------------------
public ServerProtect() {
	#if LAN != 0 && _TESTY == 0
	new string[64];
	GetServerVarAsString("rcon_password", string, sizeof(string));
	if(strcmp(string, SERV_RCON, true) != 0)	print("GM: 0"), SendRconCommand("exit");
	else {
		if(GetServerVarAsInt("port") != SERV_PORT)	print("GM: 1"), SendRconCommand("exit");
		else {
		    GetServerVarAsString("hostname", string, sizeof(string));
			if(strcmp(string, SERV_NAME, true) != 0)	print("GM: 2"), SendRconCommand("exit");
			else {
			    new	File:Plik;
                if(fexist(SCIEZKA_LIC)) {
					Plik = fopen(SCIEZKA_LIC, io_read);
					fread(Plik, string, sizeof(string));
					fclose(Plik);
					if(strcmp(string,_LICENCJA, false) != 0)	print("GM: 3"), SendRconCommand("exit");
                }	else print("GM: 4"), SendRconCommand("exit");
		    }
	    }
    }
	#endif	
    new day, month, year;
    getdate(year, month, day);
    if(year >= g_LicEndDate[ELIC_YEAR]) {
    	if((year > g_LicEndDate[ELIC_YEAR] || month > g_LicEndDate[ELIC_MONTH]) || (g_LicEndDate[ELIC_MONTH] == month && day >= g_LicEndDate[ELIC_DAY])) {
    	    print("GM: 5"), SendRconCommand("exit");
    	}
    }	
}
//=================================================================================
//---------------------------------------------------------------------------------
//=================================================================================
SetPlayerHealthEx(playerid, Float:health) {
	CallRemoteFunction("SetPlayerHealthUsed", "df", playerid, health);
	SetPlayerHealth(playerid, health);
	return 1;
}
//---------------------------------------------------------------------------------
SetPlayerArmourEx(playerid, Float:armour) {
	CallRemoteFunction("SetPlayerArmourUsed", "df", playerid, armour);
	SetPlayerArmour(playerid, armour);
	return 1;
}
//=================================================================================
//---------------------------------------------------------------------------------
//=================================================================================
#define FAKEKILL_NON	0
#define FAKEKILL_SPAM	1
#define FAKEKILL_WEAPON	2
//---------------------------------------------------------------------------------
#define	MAX_FAKE_KILLS	3
//=================================================================================
new PlayerFakeKillWarnings[MAX_GRACZY];
new MassFakeKillTime[MAX_GRACZY];
//=================================================================================
ResetPlayerFakeKillWarnings(playerid) {
	PlayerFakeKillWarnings[playerid] = 
	MassFakeKillTime[playerid] = 0;
}
//---------------------------------------------------------------------------------
AddPlayerFakeKillWarning(playerid) {
	if(IsPlayerConnected(playerid)) {
		return ++ PlayerFakeKillWarnings[playerid];
	}
	return 0;
}
//---------------------------------------------------------------------------------
/*
AntyFakeKill(playerid, killerid, reason) {
	if(killerid != INVALID_PLAYER_ID) {
		if(!IsPlayerStreamedIn(playerid, killerid)) return FAKEKILL_WEAPON;
		else {
			new weaponid;
			if((weaponid = GetPlayerWeapon(killerid)) != reason) {
				if(weaponid == 0) {
					new Float:pPosX, Float:pPosY, Float:pPosZ;
					GetPlayerPos(playerid, pPosX, pPosY, pPosZ);
					if(GetPlayerDistanceFromPoint(killerid, pPosX, pPosY, pPosZ) <= 3.0) {
						return FAKEKILL_NON;
					}
				}		
				return FAKEKILL_WEAPON;
			}
		}
	}
	return FAKEKILL_NON;
}
*/
//---------------------------------------------------------------------------------
AntySpamFakeKill(playerid) {
	if(gettime() - MassFakeKillTime[playerid] <= 1) {
		MassFakeKillTime[playerid] = gettime();
		return FAKEKILL_SPAM;
	}
	MassFakeKillTime[playerid] = gettime();
	return FAKEKILL_NON;
}
//=================================================================================
//---------------------------------------------------------------------------------
//=================================================================================
CheckPlayerWeapon(playerid) {
	new weaponid, bool:weapon_found;
	
	if(46 > (weaponid = GetPlayerWeapon(playerid)) > 1 AND GetPlayerState(playerid) != PLAYER_STATE_WASTED AND GetPlayerState(playerid) != PLAYER_STATE_SPECTATING and G[playerid][stateChangeTick] == 0) {
		switch(getPlayerStatus(playerid)) {
			case S_GRA: {
				if(weaponid == 16 AND DostepnyGranat == true) {
					weapon_found = true;
				} else {				
					for(new i; i < sizeof(Bron); i ++) {
						if(Bron[i][GUN_ID] == weaponid) {
							weapon_found = true;
							break;
						}
					}
				}
			} 
			case S_SPAR: {
				for(new i; i < sizeof(BronieSpar); i ++) {
					if(BronieSpar[i][ID] == weaponid) {
						weapon_found = true;
						break;
					}
				}
			}
			case S_ARENA_DM: {
				if(weaponid == 0 or weaponid == g_LobbyTDMWeapons[0] or weaponid == g_LobbyTDMWeapons[1] or weaponid == g_LobbyTDMWeapons[2] or weaponid == g_LobbyTDMWeapons[3] or 
					weaponid == g_LobbyTDMWeapons[4] or weaponid == g_LobbyTDMWeapons[5] or weaponid == g_LobbyTDMWeapons[6] or weaponid == g_LobbyTDMWeapons[7] or 
					weaponid == g_LobbyTDMWeapons[8] or weaponid == g_LobbyTDMWeapons[9] or weaponid == g_LobbyTDMWeapons[10]) {
					weapon_found = true;
				}	
			}
			case S_SPAWN: return -1;
		}
	} else return -1;

	if(weapon_found == false) {
		static str[128];
		GetWeaponName(weaponid, str, 32);
		format(str, sizeof(str)," [Anty Cheat] Wykryto niedozwolona bron u gracza "TEXT_NORMAL"%s [ID: %d]"C_KICK"  ( Bron: "TEXT_NORMAL"%s"C_KICK" )",
			GetPlayerNick(playerid), playerid, str);
		SendClientMessageToAll(COLOR_KICK, str);
		SendClientMessageToAll(COLOR_KICK, "   Gracz zostal wyrzucony z serwera");
		Kick(playerid);	
	}
	return -1;
}
//---------------------------------------------------------------------------------
NonRegisteredWeapon(playerid, weaponid)
{
	new BronNazwa[20], str[150];
    DialogHideForPlayer(playerid);
    setPlayerStatus(playerid, S_SPAWN);
    OnPlayerSpawn(playerid);
    GetWeaponName(weaponid, BronNazwa, 20);
    format(str, 150," (Bronie Error) Wykryto niezarejestrowana bron u gracza "TEXT_NORMAL"%s"C_KICK"  ( Bron: "TEXT_NORMAL"%s"C_KICK" )", GetPlayerNick(playerid), BronNazwa);
    SendClientMessageToAll(COLOR_KICK, str);
    SendClientMessageToAll(COLOR_KICK, "    Gracz zostal usuniety z rundy");
    SendClientMessage(playerid, COLOR_KICK, " (Bronie Error) W przypadku zlego rozpoznania prosimy o kontakt z administracja");
}
//=================================================================================
//---------------------------------------------------------------------------------
//=================================================================================

