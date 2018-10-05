#define GetPlayerUserID(%1)	getPlayerUserID(%1)
stock getPlayerUserID(playerid) return GetPVarInt(playerid, PV_LOGIN_USERID);
//---------------------------------------------------------------
#define GetPlayerLoginStatus(%1) getPlayerLoginStatus(%1)
getPlayerLoginStatus(playerid) return GetPVarInt(playerid, PV_LOGIN_STATUS);
//---------------------------------------------------------------
#define getPlayerAimedInfoStatus(%1) GetPVarInt(%1, PV_AIMED_INFO_STATUS)
//---------------------------------------------------------------
stock AddPlayerDeath(playerid, add = 1) 			SetPVarInt(playerid, PV_ACC_DEATH, GetPVarInt(playerid, PV_ACC_DEATH) + add), 	G[playerid][gSmierci] += add;
stock AddPlayerKill(playerid, add = 1) 				SetPVarInt(playerid, PV_ACC_KILL, GetPVarInt(playerid, PV_ACC_KILL) + add), 		G[playerid][gFragi] += add;
stock AddPlayerDMG(playerid, add = 1) 				SetPVarInt(playerid, PV_ACC_DMG, GetPVarInt(playerid, PV_ACC_DMG) + add), 			G[playerid][gDMG] += add;
stock AddPlayerRespect(playerid, add = 1) 			SetPVarInt(playerid, PV_ACC_RESPECT, GetPVarInt(playerid, PV_ACC_RESPECT) + add), 	G[playerid][gRespect] += add;
stock AddPlayerSparingWin(playerid, add = 1)		SetPVarInt(playerid, PV_ACC_SPARING_WIN, GetPVarInt(playerid, PV_ACC_SPARING_WIN) + add);
stock AddPlayerSparingLoss(playerid, add = 1) 		SetPVarInt(playerid, PV_ACC_SPARING_LOSS, GetPVarInt(playerid, PV_ACC_SPARING_LOSS) + add);


//stock AddPlayerCarKill(playerid, add = 1)			SetPVarInt(playerid, PV_ACC_CAR_KILL, GetPVarInt(playerid, PV_ACC_CAR_KILL) + add);
//stock AddPlayerHeliKill(playerid, add = 1) 			SetPVarInt(playerid, PV_ACC_HELI_KILL, GetPVarInt(playerid, PV_ACC_HELI_KILL) + add);
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
stock GetPlayerDeath(playerid, bool:online) 		return online == true ? G[playerid][gSmierci] : GetPVarInt(playerid, PV_ACC_DEATH);
stock GetPlayerKill(playerid, bool:online) 			return online == true ? G[playerid][gFragi] : 	GetPVarInt(playerid, PV_ACC_KILL);
stock GetPlayerDMG(playerid, bool:online) 			return online == true ? G[playerid][gDMG] : 	GetPVarInt(playerid, PV_ACC_DMG);
stock GetPlayerRespect(playerid, bool:online) 		return online == true ? G[playerid][gRespect] : GetPVarInt(playerid, PV_ACC_RESPECT);
stock GetPlayerSparingWin(playerid) 	return GetPVarInt(playerid, PV_ACC_SPARING_WIN);
stock GetPlayerSparingLoss(playerid) 	return GetPVarInt(playerid, PV_ACC_SPARING_LOSS);
//stock GetPlayerCarKill(playerid)		return GetPVarInt(playerid, PV_ACC_CAR_KILL);
//stock GetPlayerHeliKill(playerid)		return GetPVarInt(playerid, PV_ACC_HELI_KILL);
stock GetPlayerWeaponKill(playerid, weaponid) {
	if(42 >= weaponid >= 0) {
		new string[16];
		format(string, sizeof(string), PV_ACC_WEAP_PART"_%d", weaponid);
		return GetPVarInt(playerid, string);		
	}
	return _FALSE;
}
//---------------------------------------------------------------
stock SetPlayerDeath(playerid, set) 		SetPVarInt(playerid, PV_ACC_DEATH, set), 	G[playerid][gSmierci] = set;
stock SetPlayerKill(playerid, set)			SetPVarInt(playerid, PV_ACC_KILL, set), 	G[playerid][gFragi] = set;
stock SetPlayerDMG(playerid, set) 			SetPVarInt(playerid, PV_ACC_DMG, set), 		G[playerid][gDMG] = set;
stock SetPlayerRespect(playerid, set) 		SetPVarInt(playerid, PV_ACC_RESPECT, set), 	G[playerid][gRespect] = set;
stock SetPlayerSparingWin(playerid, set) 	SetPVarInt(playerid, PV_ACC_SPARING_WIN, set);
stock SetPlayerSparingLoss(playerid, set) 	SetPVarInt(playerid, PV_ACC_SPARING_LOSS, set);
/*
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
*/