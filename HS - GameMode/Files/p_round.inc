enum GUN_REQUEST {_NON, NEW_WEAPONS, PREVIOUS_WEAPONS}
enum WEAPON_IDX {_FIRST, _SECOND}
enum WEAPON_TYPE {_PRIMARY, _SAVED}

enum GUN_INFO	{	GUN_ID,	GUN_NAME[8], GUN_AMMO, GUN_SLOT, GUN_TABS[8]	}
new Bron[][GUN_INFO]   =   {
		{23, !"Pistolet z tlumikiem", 350, 2},
		{24, !"Desert Eagle", 200, 2, "\t"},
		{25, !"Shotgun", 150, 3, "\t"},
		{29, !"MP5", 500, 4, "\t\t"},
		{30, !"AK-47", 400, 5, "\t"},
		{31, !"M4", 300, 5, "\t\t"},
		{33, !"Karabin", 250, 6, "\t"},
		{34, !"Karabin Sniperski", 100, 6}
	    };


new PlayerPreviousWeaponsIndex[MAX_GRACZY][WEAPON_IDX];
new PlayerWeaponsIndex[MAX_GRACZY][WEAPON_IDX];				// Zapisywany jest index broni, nie ID!!!
new GUN_REQUEST:PlayerWeaponRequest[MAX_GRACZY];
//=================================================================================
//---------------------------------------------------------------------------------
//=================================================================================
ForceSetPlayerRoundWeapon(playerid, WEAPON_IDX:index, value, WEAPON_TYPE:saved) {
	if(saved == _PRIMARY) PlayerWeaponsIndex[playerid][index] = value;
	else PlayerPreviousWeaponsIndex[playerid][index] = value;
	return 1;
}
//---------------------------------------------------------------------------------
SetPlayerRoundWeapon(playerid, WEAPON_IDX:index, value, WEAPON_TYPE:saved) {
	if(getPlayerStatus(playerid) == S_GRA) {
		if(saved == _PRIMARY) PlayerWeaponsIndex[playerid][index] = value;
		else PlayerPreviousWeaponsIndex[playerid][index] = value;
		return 1;
	}
	return 0;
}
//---------------------------------------------------------------------------------
GetPlayerRoundWeapon(playerid, WEAPON_IDX:index, WEAPON_TYPE:saved) {
	if(getPlayerStatus(playerid) == S_GRA) {
		return saved == _PRIMARY ? PlayerWeaponsIndex[playerid][index] : PlayerPreviousWeaponsIndex[playerid][index];
	}
	return -2;
}
//---------------------------------------------------------------------------------
GetPlayerRoundWeaponSlot(playerid, WEAPON_IDX:index, WEAPON_TYPE:saved) {
	if(getPlayerStatus(playerid) == S_GRA) {
		new weapon_idx = (saved == _PRIMARY ? PlayerWeaponsIndex[playerid][index] : PlayerPreviousWeaponsIndex[playerid][index]);
		if(0 <= weapon_idx < sizeof(Bron)) {
			return Bron[weapon_idx][GUN_SLOT];
		}
	}
	return -1;
}
//---------------------------------------------------------------------------------
GetPlayerRoundWeaponID(playerid, WEAPON_IDX:index, WEAPON_TYPE:saved) {
	if(getPlayerStatus(playerid) == S_GRA) {
		new weapon_idx = (saved == _PRIMARY ? PlayerWeaponsIndex[playerid][index] : PlayerPreviousWeaponsIndex[playerid][index]);
		if(0 <= weapon_idx < sizeof(Bron)) {
			return Bron[weapon_idx][GUN_ID];
		}
	}
	return -1;
}
//---------------------------------------------------------------------------------
GUN_REQUEST:GetPlayerWeaponRequestStatus(playerid) {
	if(getPlayerStatus(playerid) == S_GRA) {
		return PlayerWeaponRequest[playerid];
	}
	return _NON;
}
//---------------------------------------------------------------------------------
SetPlayerWeaponRequestStatus(playerid, GUN_REQUEST:status) {
	PlayerWeaponRequest[playerid] = status;
	return 1;
}
//---------------------------------------------------------------------------------
ResetPlayerActualRoundWeapons(playerid) {
	if(getPlayerStatus(playerid) == S_GRA) {
		ResetPlayerWeapons(playerid);
		SetPlayerRoundWeapon(playerid, _FIRST, -1, _PRIMARY);
		SetPlayerRoundWeapon(playerid, _SECOND, -1, _PRIMARY);
		return 1;
	}
	return 0;
}
//=================================================================================
//---------------------------------------------------------------------------------
//=================================================================================
ShowPlayerFirstGunMenu(playerid) {
	new GUN_REQUEST:requestType;
	if((requestType = GetPlayerWeaponRequestStatus(playerid)) != _NON) {
		new bool:previous = (GetPlayerRoundWeapon(playerid, _FIRST, _SAVED) == -1 OR GetPlayerRoundWeapon(playerid, _SECOND, _SAVED) == -1 ? false : true);
		ResetPlayerActualRoundWeapons(playerid);
		if(requestType != PREVIOUS_WEAPONS OR previous == false) {
			if(previous == false) {
				return ShowPlayerGunList(playerid);
			}
			new str[150];
			format(str, sizeof(str), D_CC"1) "DIALOG_TEXT_COLOR "Wybierz nowe bronie\n"D_CC"2) %sWybierz poprzedni zestaw\n"D_CC"3) %sWybierz poprzednie i nie pytaj wiecej",
				previous == true ? (DIALOG_TEXT_COLOR) : (C_KICK),
				previous == true ? (DIALOG_TEXT_COLOR) : (C_KICK));	
			SetPlayerWeaponRequestStatus(playerid, NEW_WEAPONS);
			ShowPlayerDialog(playerid, DIALOG_GUNMENU_1, DIALOG_STYLE_LIST, DIALOG_HEAD_COLOR "Wybor broni", str, "Dalej", "");
		} else {
			SetPlayerRoundWeapon(playerid, _FIRST, GetPlayerRoundWeapon(playerid, _FIRST, _SAVED), _PRIMARY);
			SetPlayerRoundWeapon(playerid, _SECOND, GetPlayerRoundWeapon(playerid, _SECOND, _SAVED), _PRIMARY);
			EndSelectPlayerRoundWeapons(playerid, GetPlayerRoundWeapon(playerid, _FIRST, _PRIMARY), GetPlayerRoundWeapon(playerid, _SECOND, _PRIMARY));
		}
		return 1;
	}
	return 0;
}
//---------------------------------------------------------------------------------
FirstRequestGunMenu(playerid, listitem) {
	if(getPlayerStatus(playerid) == S_GRA) {
			if(listitem == 0) {
				ShowPlayerGunList(playerid);				
			} else {
				if(GetPlayerRoundWeapon(playerid, _FIRST, _SAVED) != -1 AND GetPlayerRoundWeapon(playerid, _SECOND, _SAVED) != -1) {
					if(listitem == 2) {
						SetPlayerWeaponRequestStatus(playerid, PREVIOUS_WEAPONS);
					}
					SetPlayerRoundWeapon(playerid, _FIRST, GetPlayerRoundWeapon(playerid, _FIRST, _SAVED), _PRIMARY);
					SetPlayerRoundWeapon(playerid, _SECOND, GetPlayerRoundWeapon(playerid, _SECOND, _SAVED), _PRIMARY);
					EndSelectPlayerRoundWeapons(playerid, GetPlayerRoundWeapon(playerid, _FIRST, _PRIMARY), GetPlayerRoundWeapon(playerid, _SECOND, _PRIMARY));
				} else ShowPlayerFirstGunMenu(playerid);
			}
		return 1;
	}
	return 0;
}
//---------------------------------------------------------------------------------
ShowPlayerGunList(playerid) {
	if(getPlayerStatus(playerid) == S_GRA) {
		if(GetPlayerRoundWeapon(playerid, _FIRST, _PRIMARY) == -1 OR GetPlayerRoundWeapon(playerid, _SECOND, _PRIMARY) == -1) {
			new str[512], player_weapons[64], gunName[32], first_weapon = GetPlayerRoundWeapon(playerid, _FIRST, _PRIMARY);
			for(new i, bool:allowed; i < sizeof(Bron); i ++) {
				allowed = true;
				strunpack(gunName, Bron[i][GUN_NAME]);
				if(first_weapon != -1) {
					allowed = (GetPlayerRoundWeaponSlot(playerid, _FIRST, _PRIMARY) == Bron[i][GUN_SLOT] ? false : true);
				}			
				format(str, sizeof(str),"%s\n"D_CC"%d) %s%s"DIALOG_TEXT_COLOR"\t\t\t%sAmmo: "TEXT_NORMAL"%d",
					str,
					i + 1,
					allowed == false ? (C_KICK) : (DIALOG_HEAD_COLOR), gunName,
					Bron[i][GUN_TABS],
					Bron[i][GUN_AMMO]);		
			}
			if(first_weapon == -1) {
				format(player_weapons, sizeof(player_weapons), DIALOG_HEAD_COLOR "Wybierz pierwsza bron");
				ShowPlayerDialog(playerid, DIALOG_GUNMENU_2, DIALOG_STYLE_LIST, player_weapons, str, "Dalej", (GetPlayerRoundWeapon(playerid, _FIRST, _SAVED) == -1 OR GetPlayerRoundWeapon(playerid, _SECOND, _SAVED) == -1 ? ("") : ("Wroc")));
			} else {
				strunpack(gunName, Bron[first_weapon][GUN_NAME]);
				format(player_weapons, sizeof(player_weapons), DIALOG_HEAD_COLOR "Wybierz druga bron  (Pierwsza: %s)", gunName);
				ShowPlayerDialog(playerid, DIALOG_GUNMENU_2, DIALOG_STYLE_LIST, player_weapons, str, "Dalej", "Wroc");
			}
			
			return 1;
		}
	}
	return 0;
}
//---------------------------------------------------------------------------------
PlayerRequestWeapon(playerid, weapon_idx) {
	if(getPlayerStatus(playerid) == S_GRA) {	
		if(GetPlayerRoundWeapon(playerid, _FIRST, _PRIMARY) != -1) {
			if(GetPlayerRoundWeaponSlot(playerid, _FIRST, _PRIMARY) != Bron[weapon_idx][GUN_SLOT]) {
				SetPlayerRoundWeapon(playerid, _SECOND, weapon_idx, _PRIMARY);
				EndSelectPlayerRoundWeapons(playerid, GetPlayerRoundWeapon(playerid, _FIRST, _PRIMARY), GetPlayerRoundWeapon(playerid, _SECOND, _PRIMARY));				
				return 1;
			}
		} else SetPlayerRoundWeapon(playerid, _FIRST, weapon_idx, _PRIMARY);	
		
		ShowPlayerGunList(playerid);
		return 1;
	}
	return 0;
}
//---------------------------------------------------------------------------------
EndSelectPlayerRoundWeapons(playerid, weapon_idx_first, weapon_idx_second) {
	if(getPlayerStatus(playerid) == S_GRA) {	
		if(weapon_idx_first != -1 AND weapon_idx_second != -1) {
			if(g_RoundSpawnProtectTime <= 0) {  
				GivePlayerRoundWeapons(playerid);
			} else {
			    new GunName[2][32], str[150];
			    GetWeaponName(Bron[weapon_idx_first][GUN_ID], GunName[0], 32);
			    GetWeaponName(Bron[weapon_idx_second][GUN_ID], GunName[1], 32);
				SetPlayerRoundWeapon(playerid, _FIRST, weapon_idx_first, _SAVED);
				SetPlayerRoundWeapon(playerid, _SECOND, weapon_idx_second, _SAVED);				
				
			    format(str, sizeof(str)," (Bron) Wybrany zestaw "TEXT_NORMAL"%s"TEXT_GUN_INFO" i "TEXT_NORMAL"%s"TEXT_GUN_INFO" otrzymasz po zakonczeniu ochrony poczatkowej", GunName[0], GunName[1]);
	    		SendClientMessage(playerid, COLOR_GUN_INFO, str);			
			}
			return 1;
		} else ShowPlayerFirstGunMenu(playerid);
	}
	return 0;
}
//---------------------------------------------------------------------------------
GivePlayerRoundWeapons(playerid) {
	if(getPlayerStatus(playerid) == S_GRA) {
		new w_idx[WEAPON_IDX];
		if((w_idx[_FIRST] = GetPlayerRoundWeapon(playerid, _FIRST, _PRIMARY)) != -1 AND (w_idx[_SECOND] = GetPlayerRoundWeapon(playerid, _SECOND, _PRIMARY)) != -1) {
			new w_id[WEAPON_IDX];
			new str[132], w_name[WEAPON_IDX][32];
			
			w_id[_FIRST] = Bron[w_idx[_FIRST]][GUN_ID];
			w_id[_SECOND] = Bron[w_idx[_SECOND]][GUN_ID];
			
			strunpack(w_name[_FIRST], Bron[w_idx[_FIRST]][GUN_NAME]);
			strunpack(w_name[_SECOND], Bron[w_idx[_SECOND]][GUN_NAME]);
			
			format(str, sizeof(str)," (Bron) Otrzymales(as) wybrany zestaw broni: "TEXT_NORMAL"%s"TEXT_GUN_INFO" i "TEXT_NORMAL"%s", w_name[_FIRST], w_name[_SECOND]);
			SendClientMessage(playerid, COLOR_GUN_INFO, str);
			
			ResetPlayerWeapons(playerid);
			G[playerid][stateChangeTick] = 3;
			GivePlayerWeapon(playerid, 1, 1);
			GivePlayerWeapon(playerid, w_id[_FIRST], Bron[w_idx[_FIRST]][GUN_AMMO]); 
			GivePlayerWeapon(playerid, w_id[_SECOND], Bron[w_idx[_SECOND]][GUN_AMMO]); 			
			if(DostepnyGranat == true && DodatkowyGranat == true) GivePlayerWeapon(playerid, 16, 1);
			return 1;
		}
	}
	return 0;
}
