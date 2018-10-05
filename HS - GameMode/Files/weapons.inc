//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
enum E_WEAPON_STATUS {W_OFF, W_ON, W_ALLOWED, W_NON}
enum E_WEAPONS_INFO {WEAPON_ID, WEAPON_SLOT, E_WEAPON_STATUS:WEAPON_STATUS, WEAPON_NAME[8], WEAPON_TABS[6], WEAPON_AMMO, WEAPON_RESPECT, WEAPON_VIP_RESPECT}
new g_Weapons[][E_WEAPONS_INFO] = {
	{0, 	0, 		W_ALLOWED, 	!"Piesc", 					"",			0, 4, 4},		{1, 	0, 		W_ALLOWED, 	!"Kastet", 					"",			0, 0, 0},		{2, 	1, 		W_OFF, 		!"Kij golfowy", 			"\t\t",		0, 0, 0},
	{3, 	1, 		W_ON, 		!"Palka policyjna", 		"\t",		0, 4, 4},		{4, 	1, 		W_ON, 		!"Noz", 					"\t\t\t",	0, 0, 0},		{5, 	1, 		W_OFF, 		!"Kij Baseballowy", 		"\t",		0, 0, 0},
	{6, 	1, 		W_ON, 		!"Szpadel", 				"\t\t",		0, 0, 0},		{7, 	1, 		W_ON,	 	!"Kij bilardowy", 			"\t\t",		0, 0, 0},		{8, 	1, 		W_OFF,	 	!"Katana", 					"\t\t",		0, 0, 0},
	{9, 	1, 		W_ON,	 	!"Pila mechaniczna",		"\t",		0, 0, 0},		{10, 	10,		W_ON,	 	!"Dildo 1", 				"\t\t",		0, 0, 0},		{11, 	10, 	W_OFF,	 	!"Dildo 2", 				"\t\t",		0, 0, 0},
	{12, 	10, 	W_ON,	 	!"Dildo 3", 				"\t\t",		0, 0, 0},		{13, 	10, 	W_ON,	 	!"Dildo 4", 				"\t\t",		0, 0, 0},		{14, 	10, 	W_OFF,	 	!"Kwiaty", 					"\t\t",		0, 0, 0},
	{15, 	10, 	W_ON,	 	!"Laska", 					"\t\t",		0, 0, 0},		{16, 	8, 		W_ON,	 	!"Granat", 					"\t\t",		0, 1, 1},		{17, 	8, 		W_OFF, 		!"Gaz lzawiacy", 			"\t",		0, 0, 0},
	{18, 	8, 		W_ON,	 	!"Koktail Molotova", 		"\t",		0, 0, 0},		{19, 	-1, 	W_NON,	 	!"NaN", 					"",			0, 0, 0},		{20, 	-1, 	W_NON, 		!"NaN", 					"",			0, 0, 0},
	{21, 	-1, 	W_NON, 		!"NaN", 					"",			0, 0, 0},		{22, 	2, 		W_ON, 		!"Pistolet 9mm", 			"\t",		0, 0, 0},		{23, 	2, 		W_ON, 		!"Pistolet 9mm (+tlumik)", 	"",			0, 2, 2},
	{24, 	2, 		W_ON, 		!"Desert Eagle", 			"\t",		0, 2, 2},		{25, 	3, 		W_ON, 		!"Shotgun", 				"\t\t",		0, 2, 2},		{26, 	3, 		W_OFF, 		!"Sawnoff Shotgun", 		"\t",		0, 0, 0},
	{27, 	3, 		W_ON, 		!"Combat Shotgun", 			"\t",		0, 1, 1},		{28, 	4, 		W_ON, 		!"Micro SMG (Uzi)", 		"\t",		0, 0, 0},		{29, 	4, 		W_ON,	 	!"MP5", 					"\t\t",		0, 1, 1},
	{30, 	5, 		W_ON, 		!"AK-47", 					"\t\t",		0, 1, 1},		{31, 	5, 		W_ON, 		!"M4", 						"\t\t\t",	0, 1, 1},		{32,	4, 		W_OFF, 		!"Tec-9", 					"\t\t",		0, 0, 0},
	{33, 	6, 		W_ON, 		!"Strzelba", 				"\t\t",		0, 3, 3},		{34, 	6,		W_ON,	 	!"Karabin Snajperski", 		"\t",		0, 2, 2},		{35, 	7, 		W_OFF,	 	!"RPG", 					"\t\t",		0, 0, 0},
	{35, 	7, 		W_ON,		!"HS Rocket", 				"\t\t",		0, 0, 0},		{37, 	7, 		W_ON, 		!"Miotacz ognia", 			"\t",		0, 0, 0},		{38, 	7, 		W_OFF,	 	!"Minigun", 				"\t\t",		0, 0, 0},
	{39, 	8, 		W_OFF,	 	!"Satchel", 				"\t\t",		0, 0, 0},		{40, 	12, 	W_ALLOWED, 	!"Detonator", 				"\t\t",		0, 0, 0},		{41, 	9, 		W_OFF, 		!"Puszka spray'u", 			"\t",		0, 0, 0},
	{42, 	9, 		W_OFF,		!"Gasnica", 				"\t\t",		0, 0, 0},		{43, 	9, 		W_OFF, 		!"Aparat", 					"",			0, 0, 0},		{44, 	11, 	W_OFF, 		!"Noktowizor",				"",			0, 0, 0},
	{45, 	11, 	W_OFF, 		!"Termowizor",				"",			0, 0, 0},		{46, 	11, 	W_ALLOWED, 	!"Spadochron",				"",			0, 0, 0},		{47, 	-1, 	W_ALLOWED, 	!"Fake Pistol",				"",			0, 0, 0},
	{48, 	-1, 	W_NON, 		!"NaN",						"",			0, 0, 0},		{49, 	-1, 	W_ALLOWED, 	!"Car Kill",				"",			0, 0, 0},		{50, 	-1, 	W_ALLOWED, 	!"Heli Kill",				"",			0, 0, 0},
	{51, 	-1, 	W_ALLOWED, 	!"Eksplozja",				"",			0, 0, 0},		{52, 	-1,		W_NON, 		!"NaN",						"",			0, 0, 0},		{53, 	-1, 	W_ALLOWED, 	!"Utoniecie",				"",			0, 0, 0},
	{54, 	-1, 	W_ALLOWED, 	!"Upadek",					"",			0, 0, 0}
};
new g_MaxWeaponsInGame = 5;
//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
getWeaponKillRespect(weaponid, bool:vip = false) return 0 <= weaponid <= 54 ? g_Weapons[weaponid][vip == false ? WEAPON_RESPECT : WEAPON_VIP_RESPECT] : 0;
setWeaponKillRespect(weaponid, respect, bool:vip = false) {
	if(sizeof(g_Weapons) > weaponid >= 0) {
		g_Weapons[weaponid][vip == false ? WEAPON_RESPECT : WEAPON_VIP_RESPECT] = respect;
		return 1;
	}
	return 0;
}
//------------------------------------------------------------------------------
getWeaponAmmo(weaponid) return 0 <= weaponid <= 42 ? g_Weapons[weaponid][WEAPON_AMMO] : 0;
//------------------------------------------------------------------------------
getWeaponSlot(weaponid) return 0 <= weaponid <= 54 ? g_Weapons[weaponid][WEAPON_SLOT] : -1;
//------------------------------------------------------------------------------
getMaxWeaponsBySlots() {
	new bool:slotUsed[12], i;
	new counter;
	for(i = 0; i < 45; i ++) {
	    if(g_Weapons[i][WEAPON_STATUS] == W_ON) {
	        slotUsed[g_Weapons[i][WEAPON_SLOT]] = true;
	    }
	}
	for(i = 0; i < sizeof(slotUsed); i ++) {
	    if(slotUsed[i] == true) counter ++;
	}
	return counter;
}
//------------------------------------------------------------------------------
getWeaponName(weaponid) {
	new weaponName[32] = "NaN";
	if(0 <= weaponid <= 54) strunpack(weaponName, g_Weapons[weaponid][WEAPON_NAME], 32);
	return weaponName;
}
//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
#define MAX_WEAPONS_ON_PAGE 15
/*
ShowPlayerGunMenu(playerid, listitem = -1) {
    if(getPlayerStatus(playerid) == STATUS_LOBBY or getPlayerStatus(playerid) == STATUS_GAME) {
        new string[1024];
        new step = GetPVarInt(playerid, PV_HELP_1);
        new maxSteps;
		new x, weaponid;
        if(step == 0) {
            if(getPlayerStatus(playerid) == STATUS_GAME) {
				ResetPlayerWeapons(playerid);
				resetPlayerGameWeapons(playerid);
			} else resetPlayerRequestWeapons(playerid);
		}
		if(step < (maxSteps = min(g_MaxWeaponsInGame, getMaxWeaponsBySlots()))) {
			new bool:playerUsedSlots[11] = {false, false, ...};
			new chosedWeapons;
			new possibleWeapons;
			new possibleWeaponsMenu[42] = {-1, -1, ...};
			new page = GetPlayerPage(playerid);
			for(new i, playerWeaponID; i < MAX_WEAPONS_SLOTS; i ++) {
				if((playerWeaponID = getPlayerRequestWeapon(playerid, i)) == -1) break;
				else {
					++ chosedWeapons;
					playerUsedSlots[getWeaponSlot(playerWeaponID)] = true;
				}
			}
			for(new i; i < 42; i ++) {
				if(g_Weapons[i][WEAPON_STATUS] == W_ON and playerUsedSlots[getWeaponSlot(i)] == false and g_Weapons[i][WEAPON_AMMO] > 0) {
					possibleWeaponsMenu[possibleWeapons ++] = i;
				}
			}
		    if(possibleWeapons > 0) {
			    new maxpages = floatround(possibleWeapons / MAX_WEAPONS_ON_PAGE, floatround_floor);
				if(listitem == -1) {
					new counter, head[64];
					new weapon_idx = page * MAX_WEAPONS_ON_PAGE;

					if(maxpages > page) strins(string, "\n\t\t\t"TEXT_DIALOG_HEAD">>> Nastepna strona >>>", 0);
					if(page > 0) strins(string, "\n\t\t\t"TEXT_DIALOG_HEAD"<<< Poprzednia strona <<<", 0);
					while(counter < MAX_WEAPONS_ON_PAGE and weapon_idx < possibleWeapons) {
						format(string, sizeof(string), "%s\n"TEXT_DIALOG_COUNT"%d) "TEXT_DIALOG_BODY"%s", string, weapon_idx + 1, getWeaponName(possibleWeaponsMenu[weapon_idx]));
						weapon_idx ++;
						counter ++;
					}
					strdel(string, 0, 1);

					format(head, sizeof(head), TEXT_DIALOG_HEAD"Wybor broni (%d / %d)", step + 1, maxSteps);
					ShowPlayerDialog(playerid, DIALOG_GAME_WEAPONS, DIALOG_STYLE_LIST, head, string, "Dalej", "Wroc");
				} else {
					if(listitem == 0 and (page > 0 or maxpages > page)) {
						if(maxpages > page) {
							SetPlayerPage(playerid, page + 1);
						} else {
							SetPlayerPage(playerid, page - 1);
						}
						ShowPlayerGunMenu(playerid);
					} else if(listitem == 1 and page > 0 and maxpages > page) {
						SetPlayerPage(playerid, page - 1);
						ShowPlayerGunMenu(playerid);
					} else {
						if(maxpages > page) listitem --;
						if(page > 0) listitem --;
						listitem += page * MAX_WEAPONS_ON_PAGE;

						if(g_Weapons[possibleWeaponsMenu[listitem]][WEAPON_STATUS] == W_ON) {
							setPlayerRequestWeapon(playerid, step, possibleWeaponsMenu[listitem]);
							SetPVarInt(playerid, PV_HELP_1, step + 1);
							SetPlayerPage(playerid, 0);
						    ShowPlayerGunMenu(playerid);
						} else ShowPlayerGunMenu(playerid);
					}
				}
			} else {
			    if(step != 0) {
					format(string, sizeof(string), " (Bron) Wybrales(as) nastepujace bronie: "C_WHITE);
					for(x = 0; x < MAX_WEAPONS_SLOTS; x ++) {
					    if((weaponid = getPlayerRequestWeapon(playerid, x)) == -1) setPlayerGameWeapon(playerid, x, weaponid);
					    else {						
							setPlayerGameWeapon(playerid, x, weaponid);
					        format(string, sizeof(string), "%s%s, ", string, getWeaponName(weaponid));
					    }
					}
					string[strlen(string) - 2] = EOS;
					SendClientMessage(playerid, COLOR_GUN_INFO, string);
					if(getPlayerStatus(playerid) == STATUS_LOBBY) SendClientMessage(playerid, COLOR_GUN_INFO, "   Wybrane bronie, zostana Ci wreczone przy starcie rundy.");
					else {
					    if(g_RoundSpawnProtectTime > 0) {
					        SendClientMessage(playerid, COLOR_GUN_INFO, "   Wybrane bronie, zostana Ci wreczone po zakonczeniu ochrony 'Spawn Protect'.");
					    } else {
						    ResetPlayerWeapons(playerid);
						    for(x = 0; x < MAX_WEAPONS_SLOTS; x ++) {
								if((weaponid = getPlayerGameWeapon(playerid, x)) == -1) break;
								else GivePlayerWeapon(playerid, weaponid, g_Weapons[weaponid][WEAPON_AMMO]);
							}
						}
					}
				}
			}
		} else {
		    if(step != 0) {
				format(string, sizeof(string), " (Bron) Wybrales(as) nastepujace bronie: "C_WHITE);
				for(x = 0; x < MAX_WEAPONS_SLOTS; x ++) {
				    if((weaponid = getPlayerRequestWeapon(playerid, x)) == -1) setPlayerGameWeapon(playerid, x, weaponid);
				    else {						
						setPlayerGameWeapon(playerid, x, weaponid);
				        format(string, sizeof(string), "%s%s, ", string, getWeaponName(weaponid));
				    }
				}
				string[strlen(string) - 2] = EOS;
				SendClientMessage(playerid, COLOR_GUN_INFO, string);
				if(getPlayerStatus(playerid) == STATUS_LOBBY) SendClientMessage(playerid, COLOR_GUN_INFO, "   Wybrane bronie, zostana Ci wreczone przy starcie rundy.");
				else {
				    if(g_RoundSpawnProtectTime > 0) {
				        SendClientMessage(playerid, COLOR_GUN_INFO, "   Wybrane bronie, zostana Ci wreczone po zakonczeniu ochrony 'Spawn Protect'.");
				    } else {
					    ResetPlayerWeapons(playerid);
					    for(x = 0; x < MAX_WEAPONS_SLOTS; x ++) {
							if((weaponid = getPlayerGameWeapon(playerid, x)) == -1) break;
							else GivePlayerWeapon(playerid, weaponid, g_Weapons[weaponid][WEAPON_AMMO]);
						}
					}
				}
			}
		}
    }
	return 1;
}
*/