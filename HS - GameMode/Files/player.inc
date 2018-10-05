new PlayerName[MAX_GRACZY][MAX_PLAYER_NAME];

//===========================================================================================================
//-----------------------------------------------------------------------------------------------------------
//===========================================================================================================
#define GetPlayerVIPTime(%1)			GetPVarInt(%1, PV_LOGIN_VIP_TIME)
IsVIP(playerid) return GetPlayerVIPTime(playerid) > timestamp() ? _TRUE : _FALSE;
//===========================================================================================================
getPlayerCensureStatus(playerid)				return GetPVarInt(playerid, PV_CENSURE_STATUS);
//-----------------------------------------------------------------------------------------------------------
GetPlayerNick(playerid) {
	new p_name[MAX_PLAYER_NAME];
	if(IsPlayerConnected(playerid)) {
		strins(p_name, PlayerName[playerid], 0);
	}
	return p_name;
}
//-----------------------------------------------------------------------------------------------------------
SetPlayerNick(playerid) {
	if(IsPlayerConnected(playerid)) {
		GetPlayerName(playerid, PlayerName[playerid], MAX_PLAYER_NAME);
		CallLocalFunction("OnPlayerNickChange", "dss", playerid, PlayerName[playerid], "-");
		return 1;
	}
	return 0;
}
//-----------------------------------------------------------------------------------------------------------
ResetPlayerNick(playerid) {
	if(0 <= playerid < MAX_GRACZY) {
		strdel(PlayerName[playerid], 0, MAX_PLAYER_NAME);
		return 1;
	}
	return 0;
}
//===========================================================================================================
//-----------------------------------------------------------------------------------------------------------
//===========================================================================================================
enum WorLD_AREA {bool:ENABLED, GANGZONE, OBJECT_ID, PROTECT_TIME, Float:X, Float:Y, Float:Z, Float:ZONE_MIN_X, Float:ZONE_MAX_X, Float:ZONE_MIN_Y, Float:ZONE_MAX_Y, Float:ZONE_MIN_Z, Float:ZONE_MAX_Z}
new Float:P_WorldArea[MAX_PLAYERS][WorLD_AREA];
//------------------------------------------------------------------------------
setPlayerWorldArea(playerid, Float:min_x, Float:max_x, Float:min_y, Float:max_y, Float:min_z, Float:max_z, bool:gangzone = false, gangzone_color = 0x0474CE50, gangzone_flash = -1) {
	if(min_x < max_x and min_y < max_y and min_z < max_z) {
		if(P_WorldArea[playerid][ENABLED] == true) {
			if(P_WorldArea[playerid][GANGZONE] != INVALID_GANG_ZONE) {
				GangZoneDestroy(P_WorldArea[playerid][GANGZONE]);
				P_WorldArea[playerid][GANGZONE] = INVALID_GANG_ZONE;
			}
		}
		if(P_WorldArea[playerid][OBJECT_ID] != INVALID_OBJECT_ID) {
			DestroyPlayerObject(playerid, P_WorldArea[playerid][OBJECT_ID]);
			P_WorldArea[playerid][OBJECT_ID] = INVALID_OBJECT_ID;
		}
		P_WorldArea[playerid][ZONE_MIN_X] = min_x, P_WorldArea[playerid][ZONE_MAX_X] = max_x;
		P_WorldArea[playerid][ZONE_MIN_Y] = min_y, P_WorldArea[playerid][ZONE_MAX_Y] = max_y;
		P_WorldArea[playerid][ZONE_MIN_Z] = min_z, P_WorldArea[playerid][ZONE_MAX_Z] = max_z;
		if(gangzone == true) {
			if((P_WorldArea[playerid][GANGZONE] = GangZoneCreate(min_x, min_y, max_x, max_y)) != INVALID_GANG_ZONE) {
				GangZoneShowForPlayer(playerid, P_WorldArea[playerid][GANGZONE], gangzone_color);
				if(gangzone_flash != -1) {
					GangZoneFlashForPlayer(playerid, P_WorldArea[playerid][GANGZONE], gangzone_flash);
				}
			}
		}
		P_WorldArea[playerid][PROTECT_TIME] = gettime() + 2;
		P_WorldArea[playerid][ENABLED] = true;
		return 1;		
	}
	return 0;
}
//------------------------------------------------------------------------------
deletePlayerWorldArea(playerid) {
	if(P_WorldArea[playerid][ENABLED] == true) {
		if(P_WorldArea[playerid][GANGZONE] != INVALID_GANG_ZONE) {
			GangZoneDestroy(P_WorldArea[playerid][GANGZONE]);
			P_WorldArea[playerid][GANGZONE] = INVALID_GANG_ZONE;
		}		
		if(P_WorldArea[playerid][OBJECT_ID] != INVALID_OBJECT_ID) {
			DestroyPlayerObject(playerid, P_WorldArea[playerid][OBJECT_ID]);
			P_WorldArea[playerid][OBJECT_ID] = INVALID_OBJECT_ID;
		}
		P_WorldArea[playerid][ZONE_MIN_X] = -9999.0, P_WorldArea[playerid][ZONE_MAX_X] = 9999.0;
		P_WorldArea[playerid][ZONE_MIN_Y] = -9999.0, P_WorldArea[playerid][ZONE_MAX_Y] = 9999.0;
		P_WorldArea[playerid][ZONE_MIN_Z] = -9999.0, P_WorldArea[playerid][ZONE_MAX_Z] = 9999.0;	
		P_WorldArea[playerid][PROTECT_TIME] = 0;
		P_WorldArea[playerid][ENABLED] = false;
		return 1;
	}
	return 0;
}
//------------------------------------------------------------------------------
checkPlayerZonePosition(playerid) {	
	if(P_WorldArea[playerid][OBJECT_ID] != INVALID_OBJECT_ID) {
		DestroyPlayerObject(playerid, P_WorldArea[playerid][OBJECT_ID]);
		P_WorldArea[playerid][OBJECT_ID] = INVALID_OBJECT_ID;
	}		
	
	if(getPlayerFPS(playerid) != 0) {
		static Float:x, Float:y, Float:z;
		GetPlayerPos(playerid, x, y, z);	
		if(P_WorldArea[playerid][ENABLED] == true) {
			if(gettime() > P_WorldArea[playerid][PROTECT_TIME] ) {
				if(!(P_WorldArea[playerid][ZONE_MIN_X] <= x <= P_WorldArea[playerid][ZONE_MAX_X] and P_WorldArea[playerid][ZONE_MIN_Y] <= y <= P_WorldArea[playerid][ZONE_MAX_Y] and P_WorldArea[playerid][ZONE_MIN_Z] <= z <= P_WorldArea[playerid][ZONE_MAX_Z])) {
					if(P_WorldArea[playerid][ZONE_MIN_X] <= P_WorldArea[playerid][X] <= P_WorldArea[playerid][ZONE_MAX_X] and P_WorldArea[playerid][ZONE_MIN_Y] <= P_WorldArea[playerid][Y] <= P_WorldArea[playerid][ZONE_MAX_Y] and P_WorldArea[playerid][ZONE_MIN_Z] <= P_WorldArea[playerid][Z] <= P_WorldArea[playerid][ZONE_MAX_Z]) {
						if(z <= P_WorldArea[playerid][ZONE_MIN_Z] and getPlayerStatus(playerid) == S_GRA) {
							BackToSpawn(playerid);
						} else {
							if(z >= 5000 and getPlayerStatus(playerid) == S_GRA) {
								P_WorldArea[playerid][PROTECT_TIME] = gettime() + 2;
								backToSpawnByTeam(playerid);
							} else {
								SetPlayerPos(playerid, P_WorldArea[playerid][X], P_WorldArea[playerid][Y], P_WorldArea[playerid][Z]);				
								P_WorldArea[playerid][OBJECT_ID] = CreatePlayerObject(playerid, 18724, x, y, z - 1.2, 0, 0, 0, 5);
							}
						}
					} else {
						P_WorldArea[playerid][PROTECT_TIME] = gettime() + 2;
						backToSpawnByTeam(playerid);															
					}
					return 1;
				} else {
					if(z >= 5000 and getPlayerStatus(playerid) == S_GRA) {
						P_WorldArea[playerid][PROTECT_TIME] = gettime() + 2;
						backToSpawnByTeam(playerid);
						return 1;
					}
				}
				P_WorldArea[playerid][X] = x;
				P_WorldArea[playerid][Y] = y;
				P_WorldArea[playerid][Z] = z;					
			}
		}		
	} else P_WorldArea[playerid][PROTECT_TIME] = gettime() + 2;
	return 1;
}
//------------------------------------------------------------------------------
backToSpawnByTeam(playerid) {
	if(getPlayerTeam(playerid) == T_ATT) {
		SetPlayerPos(playerid, SpawnAtt[0], SpawnAtt[1], SpawnAtt[2] + 0.5);
		SetPlayerFacingAngle(playerid, g_RoundArenaAngles[T_ATT]);	
	} else if(getPlayerTeam(playerid) == T_DEF) {
		SetPlayerPos(playerid, SpawnDef[0], SpawnDef[1], SpawnDef[2] + 0.5);
		SetPlayerFacingAngle(playerid, g_RoundArenaAngles[T_DEF]);	
	} else {
		SetPlayerPos(playerid, 0.0, 0.0, 2.0);
	}
}
//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
enum INFO_HIT {I_HIT, I_HITED};
new g_PlayerHitTimer[MAX_PLAYERS][INFO_HIT];
//------------------------------------------------------------------------------
ShowPlayerHitMenu(playerid, secondid, INFO_HIT:type, weaponid, Float:amount) {
	if(g_PlayerHitTimer[playerid][type] != 0) KillTimer(g_PlayerHitTimer[playerid][type]);

	new weaponName[16], pName[MAX_PLAYER_NAME];
	new string[64], Float:Health, Float:Armour;
	GetWeaponName(weaponid, weaponName, sizeof(weaponName));
	GetPlayerName(secondid, pName, sizeof(pName));
	
	switch(type) {
		case I_HITED: {
			GetPlayerHealth(playerid, Health);	
			GetPlayerArmour(playerid, Armour);	
			format(string, sizeof(string),"%s__-%.1f_HP__[_%.0f_HP_]", weaponName, amount, Health + Armour);		
			PlayerPlaySound(playerid, 1136, 0.0, 0.0, 0.0);
			forplayers(i) {
				if(i == playerid or G[i][SpecowanyID] == playerid) {
					TextDrawSetString(PTD_HitedByNick[i], pName);	
					TextDrawSetString(PTD_HitedByInfo[i], string);
					LayoutHitBy(i, true);
					g_PlayerHitTimer[i][type] = SetTimerEx("HidePlayerHitMenu", HIT_TIME, 0, "dd", i, _:type);
				}
			}			
		}
		case I_HIT: {
			GetPlayerHealth(secondid, Health);
			GetPlayerArmour(secondid, Armour);
			format(string, sizeof(string),"%s__-%.1f_HP__[_%.0f_HP_]", weaponName, amount, Health + Armour);
			PlayerPlaySound(playerid, 17802, 0.0, 0.0, 0.0);
			forplayers(i) {
				if(i == playerid or G[i][SpecowanyID] == playerid) {
					TextDrawSetString(PTD_HitNick[i], pName);
					TextDrawSetString(PTD_HitInfo[i], string);
					LayoutHitEnemy(i, true);
					g_PlayerHitTimer[i][type] = SetTimerEx("HidePlayerHitMenu", HIT_TIME, 0, "dd", i, _:type);
				}
			}				
		}
	}		
	
	return 1;
}
//------------------------------------------------------------------------------
forward HidePlayerHitMenu(playerid, INFO_HIT:type);
public HidePlayerHitMenu(playerid, INFO_HIT:type) {
	if(g_PlayerHitTimer[playerid][type] != 0) {
		if(type == I_HIT) LayoutHitEnemy(playerid, false);
		else LayoutHitBy(playerid, false);
		
		KillTimer(g_PlayerHitTimer[playerid][type]);
		g_PlayerHitTimer[playerid][type] = 0;
		return _TRUE;
	}
	return _FALSE;
}