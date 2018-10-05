//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
#define MAX_LOBBY_SPAWN 20
new g_LobbyInterior = 0;
new g_LoadedLobbySpawns = MAX_LOBBY_SPAWN;
new Float:g_LobbySpawnPos[MAX_LOBBY_SPAWN][3] = {
	{-303.1419,1327.4504,54.4486},	{-287.0430,1327.8767,54.5321},	{-288.7126,1318.0247,54.3058},
	{-303.2817,1316.9030,54.1113},	{-314.1280,1314.2343,53.7398},	{-300.0637,1305.0854,53.7875},
	{-292.8141,1294.3276,53.6667},	{-303.7168,1294.2936,53.4136},	{-327.2828,1292.2070,53.6643},
	{-317.9008,1293.0813,53.6643},	{-311.4513,1306.8601,57.3733},	{-311.3127,1297.9427,57.8726},
	{-317.6140,1297.6582,57.9098},	{-319.0826,1304.8599,57.6025},	{-330.0067,1304.0254,57.6025},
	{-335.4880,1297.9418,57.8727},	{-335.4837,1307.1418,57.3885},	{-325.7553,1320.0907,53.0051},
	{-321.1763,1335.1846,54.2835},	{-300.2766,1336.8976,54.7674}
};
//------------------------------------------------------------------------------
#define MAX_LOBBY_TDM_SPAWN 10
new g_ColorLobbyTDM = 0xF9BE44FF;
new g_LobbyTDMInterior = 10;
new bool:g_LobbyTDMArmour = false;
new g_LoadedLobbyTDMSpawns = MAX_LOBBY_TDM_SPAWN;
new g_LobbyTDMWeapons[11] = {24, 25, 29, 31, 34, -1, -1, -1, -1, -1, -1};
new Float:g_LobbyTDMZone[4] = {-99999.0, -99999.0, -99999.0, -99999.0};
new Float:g_LobbyTDMSpawnPos[MAX_LOBBY_TDM_SPAWN][3] = {
	{-1113.1446 , 1027.0458 , 1343.5024},	{-1113.1411 , 1034.6298 , 1342.8479},	{-1113.1367 , 1043.8854 , 1342.6998},
	{-1113.1324 , 1053.2231 , 1342.5924},	{-1113.1282 , 1061.9482 , 1342.7778},	{-987.6328 , 1094.0135 , 1342.9873},
	{-988.0238 , 1089.5164 , 1342.9669},	{-988.3283 , 1084.3800 , 1342.8874},	{-988.8311 , 1077.5029 , 1342.9631},
	{-988.8150 , 1069.8974 , 1342.9117}
};
//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
TeleportPlayerToLobbyTDMArena(playerid) {
	new rand = random(g_LoadedLobbyTDMSpawns);
    SetPlayerVirtualWorld(playerid, VW_ARENA_DM);
    SetPlayerInterior(playerid, g_LobbyTDMInterior);
    SetPlayerPos(playerid, CircleVariation(g_LobbyTDMSpawnPos[rand][0], 2), CircleVariation(g_LobbyTDMSpawnPos[rand][1], 2), g_LobbyTDMSpawnPos[rand][2]);
    SetPlayerTeam(playerid, T_NoN);
    ResetPlayerWeapons(playerid);
    SetPlayerHealthEx(playerid, 100.0);
    SetPlayerArmourEx(playerid, g_LobbyTDMArmour == true ? 100.0 : 0.0);
    if(g_LobbyTDMZone[3] != -99999.0 and g_LobbyTDMInterior == 0) {
        setPlayerWorldArea(playerid, g_LobbyTDMZone[0], g_LobbyTDMZone[1], g_LobbyTDMZone[2], g_LobbyTDMZone[3], -5000.0, 5000.0, true, GANG_ZONE_COLOR);
    }
	G[playerid][stateChangeTick] = 3;
    for(new i; i < sizeof(g_LobbyTDMWeapons); i ++) {
    	if(g_LobbyTDMWeapons[i] != -1) {
			GivePlayerWeapon(playerid, g_LobbyTDMWeapons[i], 9999);
		} else break;
	}
}
//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
loadLobbyPositions(separator[] = ",") {
	if(fexist(HEAD_FOLDER)) {
	    new File:f_open;
	    new read[128];
	    if(!fexist(LOBBY_FILE)) {
            f_open = fopen(LOBBY_FILE, io_write);
            format(read, sizeof(read), "\r\ninterior: %d", g_LobbyInterior);
            fwrite(f_open, read);
            for(new i; i < g_LoadedLobbySpawns; i ++) {
                format(read, sizeof(read), "\r\nposition: %.4f, %.4f, %.4f", g_LobbySpawnPos[i][0], g_LobbySpawnPos[i][1], g_LobbySpawnPos[i][2]);
				fwrite(f_open, read);
            }
            print(" (Lobby Positions) Utworzono plik konfiguracyjny 'Lobby Positions' o sciezce '"LOBBY_FILE"'.");
	    } else {
			new buffer[16], readline;
			new totallength;
			new loadedInterior = 0, loadedSpawns, Float:loadedSpawnPositions[MAX_LOBBY_SPAWN][3];
			new first_index, second_index;
			
			f_open = fopen(LOBBY_FILE, io_read);
			
			while(fread(f_open, read, sizeof(read))) {
			    DeleteNewLine(read);
			    DeleteSpaces(read);
				if((totallength = strlen(read)) > 3) {
				    if(strcmp(read, "interior", true, 8) == 0 and 11 >= totallength > 9) {
				        strdel(read, 0, 9);
				        if(!isNumeric(read) or (loadedInterior = strval(read)) < 0) {
				            loadedInterior = -1;
				            printf(" (Lobby Positions) Niepoprawny interior w pliku konfiguracyjnym. (Read-Line: %d)", readline);
				        }
				    } else if(strcmp(read, "position", true, 8) == 0 and totallength > 9) {
				        if(loadedSpawns == MAX_LOBBY_SPAWN) printf(" (Lobby Positions) Osiagnieto maksymalna ilosc "#MAX_LOBBY_SPAWN" spawnow. (Read-Line: %d)", readline);
				        else {
					        strdel(read, 0, 9);
					        totallength -= 9;
					        loadedSpawnPositions[loadedSpawns][2] = -99999.0;
					        if((first_index = strfind(read, separator, true, 0)) != -1) {
					            strmid(buffer, read, 0, first_index);
					            loadedSpawnPositions[loadedSpawns][0] = floatstr(buffer);
					            if((second_index = strfind(read, separator, true, first_index + 1)) != -1) {
						            strmid(buffer, read, first_index + 1, second_index);
						            loadedSpawnPositions[loadedSpawns][1] = floatstr(buffer);
						            if(totallength > second_index + 1) {
						                loadedSpawnPositions[loadedSpawns][2] = floatstr(read[second_index + 1]);
						            }
					            }
					        }
					        if(loadedSpawnPositions[loadedSpawns][2] != -99999.0) loadedSpawns ++;
					        else printf(" (Lobby Positions) Niepoprawna pozycja spawnu poczkalni w pliku konfiguracyjnym. (Read-Line: %d)", readline);
					    }
					}
				}
				readline ++;
			}

			if(loadedSpawns > 0 and loadedInterior != -1) {
			    g_LoadedLobbySpawns = loadedSpawns;
			    g_LobbyInterior = loadedInterior;
			    for(new i; i < MAX_LOBBY_SPAWN; i ++) {
			        if(i < loadedSpawns) {
			        	g_LobbySpawnPos[i][0] = loadedSpawnPositions[i][0];
			        	g_LobbySpawnPos[i][1] = loadedSpawnPositions[i][1];
			        	g_LobbySpawnPos[i][2] = loadedSpawnPositions[i][2];
					} else {
			        	g_LobbySpawnPos[i][0] = g_LobbySpawnPos[i][1] = g_LobbySpawnPos[i][2] = 0.0;
					}
			    }
			}
		}
		fclose(f_open);
		return 1;
	} else print(" (Lobby Positions) Brak folderu glownego '"HEAD_FOLDER "'.");
	return 0;
}
//------------------------------------------------------------------------------
loadLobbyTDMPositions(separator[] = ",") {
	if(fexist(HEAD_FOLDER)) {
	    new File:f_open;
	    new read[128];
	    if(!fexist(LOBBY_TDM_FILE)) {
            f_open = fopen(LOBBY_TDM_FILE, io_write);
            format(read, sizeof(read), "\r\ninterior: %d\r\narmour: %d", g_LobbyTDMInterior, _:g_LobbyTDMArmour);
            fwrite(f_open, read);
            for(new i; i < g_LoadedLobbyTDMSpawns; i ++) {
                format(read, sizeof(read), "\r\nposition: %.4f, %.4f, %.4f", g_LobbyTDMSpawnPos[i][0], g_LobbyTDMSpawnPos[i][1], g_LobbyTDMSpawnPos[i][2]);
				fwrite(f_open, read);
            }
            for(new i; i < sizeof(g_LobbyTDMWeapons); i ++) {
                if(g_LobbyTDMWeapons[i] != -1) {
	                format(read, sizeof(read), "\r\nweapon: %d", g_LobbyTDMWeapons[i]);
					fwrite(f_open, read);
				}
            }
            if(g_LobbyTDMZone[3] != -99999.0) {
                format(read, sizeof(read), "\r\nzone: %.4f, %.4f, %.4f, %.4f", g_LobbyTDMZone[0], g_LobbyTDMZone[1], g_LobbyTDMZone[2], g_LobbyTDMZone[3]);
				fwrite(f_open, read);
			}
            print(" (Lobby TDM Positions) Utworzono plik konfiguracyjny 'Lobby TDM Positions' o sciezce '"LOBBY_TDM_FILE"'.");
	    } else {
			new buffer[16], readline;
			new totallength;
			new loadedInterior = 0, loadedSpawns, Float:loadedSpawnPositions[MAX_LOBBY_TDM_SPAWN][3], loadedWeapon, Float:loadedLobbyTDMZone[4] = {-99999.0, -99999.0, ...};
			new first_index, second_index;

			f_open = fopen(LOBBY_TDM_FILE, io_read);

			while(fread(f_open, read, sizeof(read))) {
			    DeleteNewLine(read);
			    DeleteSpaces(read);
				if((totallength = strlen(read)) > 3) {
				    if(strcmp(read, "interior", true, 8) == 0 and 11 >= totallength > 9) {
				        strdel(read, 0, 9);
				        if(!isNumeric(read) or (loadedInterior = strval(read)) < 0) {
				            loadedInterior = -1;
				            printf(" (Lobby TDM Positions) Niepoprawny interior w pliku konfiguracyjnym. (Read-Line: %d)", readline);
				        }
				    } else if(strcmp(read, "weapon", true, 6) == 0 and 9 >= totallength > 7) {
				        strdel(read, 0, 7);
				        if(!isNumeric(read) or !(18 >= (loadedWeapon = strval(read)) >= 0 or 39 >= loadedWeapon >= 22 or 42 >= loadedWeapon >= 41)) {
				            printf(" (Lobby TDM Positions) Niepoprawne ID broni w pliku konfiguracyjnym. (Read-Line: %d)", readline);
				        } else {
				            g_LobbyTDMWeapons[getWeaponSlot(loadedWeapon)] = loadedWeapon;
				        }
				    } else if(strcmp(read, "armour", true, 6) == 0 and totallength > 7) {
				        strdel(read, 0, 7);
				        if(!isNumeric(read)) {
				            printf(" (Lobby TDM Positions) Niepoprawne stan 'Armour' w pliku konfiguracyjnym. (Read-Line: %d)", readline);
				        } else {
				            g_LobbyTDMArmour = strval(read) == 1 ? true : false;
				        }
					} else if(strcmp(read, "position", true, 8) == 0 and totallength > 9) {
				        if(loadedSpawns == MAX_LOBBY_TDM_SPAWN) printf(" (Lobby TDM Positions) Osiagnieto maksymalna ilosc "#MAX_LOBBY_TDM_SPAWN" spawnow. (Read-Line: %d)", readline);
				        else {
					        strdel(read, 0, 9);
					        totallength -= 9;
					        loadedSpawnPositions[loadedSpawns][2] = -99999.0;
					        if((first_index = strfind(read, separator, true, 0)) != -1) {
					            strmid(buffer, read, 0, first_index);
					            loadedSpawnPositions[loadedSpawns][0] = floatstr(buffer);
					            if((second_index = strfind(read, separator, true, first_index + 1)) != -1) {
						            strmid(buffer, read, first_index + 1, second_index);
						            loadedSpawnPositions[loadedSpawns][1] = floatstr(buffer);
						            if(totallength > second_index + 1) {
						                loadedSpawnPositions[loadedSpawns][2] = floatstr(read[second_index + 1]);
						            }
					            }
					        }
					        if(loadedSpawnPositions[loadedSpawns][2] != -99999.0) loadedSpawns ++;
					        else printf(" (Lobby TDM Positions) Niepoprawna pozycja spawnu areny treningowej w pliku konfiguracyjnym. (Read-Line: %d)", readline);
					    }
					} else if(strcmp(read, "zone", true, 4) == 0 and totallength > 5) {
				        strdel(read, 0, 5);
				        totallength -= 5;
				        loadedLobbyTDMZone[3] = -99999.0;
				        if((first_index = strfind(read, separator, true, 0)) != -1) {
				            strmid(buffer, read, 0, first_index);
				            loadedLobbyTDMZone[0] = floatstr(buffer);
				            if((second_index = strfind(read, separator, true, first_index + 1)) != -1) {
					            strmid(buffer, read, first_index + 1, second_index);
					            loadedLobbyTDMZone[1] = floatstr(buffer);
					            if((first_index = strfind(read, separator, true, second_index + 1)) != -1) {
						            strmid(buffer, read, second_index + 1, first_index);
						            loadedLobbyTDMZone[2] = floatstr(buffer);
						            if(totallength > first_index + 1) {
						                loadedLobbyTDMZone[3] = floatstr(read[first_index + 1]);
						            }
								}
				            }
				        }
				        if(loadedLobbyTDMZone[3] == -99999.0 or loadedLobbyTDMZone[0] > loadedLobbyTDMZone[1] or loadedLobbyTDMZone[2] > loadedLobbyTDMZone[3]) {
				            loadedLobbyTDMZone[3] = -99999.0;
            				printf(" (Lobby TDM Positions) Niepoprawna pozycja obszaru walki w pliku konfiguracyjnym. (Read-Line: %d)", readline);
						}
					}
					
					
					
					
				}
				readline ++;
			}

			if(loadedSpawns > 0 and loadedInterior != -1) {
			    g_LoadedLobbyTDMSpawns = loadedSpawns;
			    g_LobbyTDMInterior = loadedInterior;
			    for(new i; i < MAX_LOBBY_TDM_SPAWN; i ++) {
			        if(i < loadedSpawns) {
			        	g_LobbyTDMSpawnPos[i][0] = loadedSpawnPositions[i][0];
			        	g_LobbyTDMSpawnPos[i][1] = loadedSpawnPositions[i][1];
			        	g_LobbyTDMSpawnPos[i][2] = loadedSpawnPositions[i][2];
					} else {
			        	g_LobbyTDMSpawnPos[i][0] = g_LobbyTDMSpawnPos[i][1] = g_LobbyTDMSpawnPos[i][2] = 0.0;
					}
			    }
			    if(loadedLobbyTDMZone[3] != -99999.0) {
			        g_LobbyTDMZone[0] = loadedLobbyTDMZone[0];
			        g_LobbyTDMZone[1] = loadedLobbyTDMZone[1];
			        g_LobbyTDMZone[2] = loadedLobbyTDMZone[2];
			        g_LobbyTDMZone[3] = loadedLobbyTDMZone[3];
			    }
			}
		}
		fclose(f_open);
		return 1;
	} else print(" (Lobby TDM Positions) Brak folderu glownego '"HEAD_FOLDER "'.");
	return 0;
}
//------------------------------------------------------------------------------