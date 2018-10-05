//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
forward StartOdliczaniaSparing(const czas, const gracz1, const gracz2);
public StartOdliczaniaSparing(const czas, const gracz1, const gracz2) {
	if(TrwaOdliczanie == false) {
		if(getPlayerStatus(gracz1) != S_SPAR || getPlayerStatus(gracz2) != S_SPAR) {
		    KoniecSparingu(gracz1);
		    KoniecSparingu(gracz2);
		    return 1;
	    } else {
			LayoutPlayerCountdown(gracz1, true, czas);
			LayoutPlayerCountdown(gracz2, true, czas);
			if(czas > 0) {				
				PlayerPlaySound(gracz1, 1056, 0, 0, 0);	PlayerPlaySound(gracz2, 1056, 0, 0, 0);
			} else {
				if(czas == 0) {
					PlayerPlaySound(gracz1, 1057, 0, 0, 0);	PlayerPlaySound(gracz2, 1057, 0, 0, 0);		
					TogglePlayerControllable(gracz1,1);		TogglePlayerControllable(gracz2,1);
					G[gracz1][stateChangeTick] = G[gracz2][stateChangeTick] = 3;
					GivePlayerWeapon(gracz1, BronieSpar[G[gracz1][SparingIDBroni][0]][ID], 500);
					GivePlayerWeapon(gracz2, BronieSpar[G[gracz1][SparingIDBroni][0]][ID], 500);
					GivePlayerWeapon(gracz1, BronieSpar[G[gracz1][SparingIDBroni][1]][ID], 500);
					GivePlayerWeapon(gracz2, BronieSpar[G[gracz1][SparingIDBroni][1]][ID], 500);
				} else {
					LayoutPlayerCountdown(gracz1, false);
					LayoutPlayerCountdown(gracz2, false);				
				}
			}   
			SetTimerEx("StartOdliczaniaSparing",1000,0,"ddd",czas - 1, gracz1, gracz2);
	    }
	}
	return 1;
}
//------------------------------------------------------------------------------
PlayerRequestSparingGun(playerid, listitem) {
	if(getPlayerStatus(playerid) == S_SPAWN AND TrwaOdliczanie == false) {
		if(G[playerid][SparingIDBroni][0] < 0) {
			G[playerid][SparingIDBroni][0] = listitem;
			ShowSparingGunList(playerid);
		} else {
			if(BronieSpar[listitem][slot] == BronieSpar[G[playerid][SparingIDBroni][0]][slot]) {
				ShowSparingGunList(playerid);
			} else {
				G[playerid][SparingIDBroni][1] = listitem;
				ShowSparingPlayerInfo(playerid);
			}
		}
		return 1;
	}
	return 0;
}
//------------------------------------------------------------------------------
ShowSparingGunList(playerid) {
	if(getPlayerStatus(playerid) == S_SPAWN AND TrwaOdliczanie == false) {
		new str[512];
		new gunid = G[playerid][SparingIDBroni][0];
		for(new i = sizeof(BronieSpar) - 1; i >= 0; i --) format(str, 512, "\n"D_CC"%d) %s%s%s", i + 1, gunid >= 0 ? BronieSpar[i][slot] == BronieSpar[gunid][slot] ? (DIALOG_KICK_COLOR) : (DIALOG_TEXT_COLOR) : (DIALOG_TEXT_COLOR), BronieSpar[i][nazwa], str);
		strdel(str, 0, 1);
		ShowPlayerDialog(playerid, DIALOG_SPAR_BRONIE, DIALOG_STYLE_LIST, gunid != -1 ? (DIALOG_HEAD_COLOR "Sparing - Druga bron") : (DIALOG_HEAD_COLOR "Sparing - Pierwsza bron"), str, "Dalej", gunid != -1 ? ("Wroc") : ("Wyjdz"));
	}
}
//------------------------------------------------------------------------------
ShowSparingPlayerInfo(playerid, gracz[] = "") {
	if(getPlayerStatus(playerid) == S_SPAWN && TrwaOdliczanie == false) {
		new gunName[128], str[256], gun1 = G[playerid][SparingIDBroni][0], gun2 = G[playerid][SparingIDBroni][1];
		SetPVarInt(playerid, PV_TAB, TAB_SPAR);
		format(gunName, sizeof(gunName), DIALOG_HEAD_COLOR "Sparing   %s -> %s",BronieSpar[gun1][nazwa],BronieSpar[gun2][nazwa]);
		
		if(24 > strlen(gracz) > 0) {
			new IDGracza = -1;
			if(isNumeric(gracz)) {
				if( !IsPlayerConnected( ( IDGracza = strval(gracz) ) ) ) format(str, sizeof(str),"    Podane ID gracza ( "DIALOG_NORMAL_COLOR "%d "DIALOG_KICK_COLOR ") jest niepoprawne, lub gracz jest OFF-Line.", IDGracza), IDGracza = -1;
			} else {
				format(str, sizeof(str),"\t\tNie znaleziono gracza o nicku "DIALOG_NORMAL_COLOR "%s"DIALOG_KICK_COLOR ".", gracz);
				forplayers(i) {
					if(strcmp(GetPlayerNick(i), gracz, false) == 0) {
						IDGracza = i;
						break;
					}
				}
			}
			if(IDGracza != -1) {
				if(IDGracza != playerid) {
					if(getPlayerStatus(IDGracza) == S_SPAWN) {
						if(GetPVarInt(IDGracza, PV_SPAR_AKTYWNY) == 0) {
							G[playerid][SparingIDGracza] = IDGracza;
							WyslijWyzwanieNaSparing(playerid);
							return 1;
						}   else format(str, sizeof(str),"\t         Gracz "DIALOG_NORMAL_COLOR "%s "DIALOG_KICK_COLOR "ma wylaczona opcje sparingow.", GetPlayerNick(IDGracza));
					}   else format(str, sizeof(str),"\tGracz "DIALOG_NORMAL_COLOR "%s "DIALOG_KICK_COLOR " znajduje sie poza obszarem poczekalni.", GetPlayerNick(IDGracza));
				}   else format(str, sizeof(str),"\tNie mozesz wyzwac na sparing samego(ej) siebie.");
			}
		}
		format(str, sizeof(str), DIALOG_TEXT_COLOR "Wybierz przeciwnika poprzez wpisanie jego ID/Nick'u w ponizsze pole,\n\t\t    lub przez wybranie go z \"Tab Listy\".\n"DIALOG_KICK_COLOR "%s", str);
		ShowPlayerDialog(playerid, DIALOG_SPAR_GRACZ, DIALOG_STYLE_INPUT, gunName, str,"Wybierz","Wroc");
		return 1;
	}
	return 0;
}
//------------------------------------------------------------------------------
WyslijWyzwanieNaSparing(playerid) {
	new IDGracza;
    if(IsPlayerConnected((IDGracza = G[playerid][SparingIDGracza]))) {
        if(getPlayerStatus(IDGracza) == S_SPAWN) {
	        if(GetPVarInt(IDGracza, PV_SPAR_AKTYWNY) == 0) {
	            new str[256];
	            G[IDGracza][SparingIDGracza] = playerid;
				G[IDGracza][SparingIDBroni][0] = G[playerid][SparingIDBroni][0];
				G[IDGracza][SparingIDBroni][1] = G[playerid][SparingIDBroni][1];
				format(str, sizeof(str), DIALOG_TEXT_COLOR "Zaproponowales(as) graczu "DIALOG_NORMAL_COLOR "%s "DIALOG_TEXT_COLOR "sparing na bronie "DIALOG_NORMAL_COLOR "%s "DIALOG_TEXT_COLOR "i "DIALOG_NORMAL_COLOR "%s.\n\t\t\t"DIALOG_TEXT_COLOR "    Oczekuj na odpowiedz...",GetPlayerNick(IDGracza), BronieSpar[G[playerid][SparingIDBroni][0]][nazwa], BronieSpar[G[playerid][SparingIDBroni][1]][nazwa]);
				ShowPlayerDialog(playerid, DIALOG_KICK, DIALOG_STYLE_MSGBOX, DIALOG_HEAD_COLOR "Sparing",str,"Wyjdz","");
				format(str, sizeof(str), DIALOG_TEXT_COLOR "Gracz "DIALOG_NORMAL_COLOR "%s "DIALOG_TEXT_COLOR "zaproponowal(a) Ci sparing na bronie "DIALOG_NORMAL_COLOR "%s "DIALOG_TEXT_COLOR "i "DIALOG_NORMAL_COLOR "%s"DIALOG_TEXT_COLOR ".\n\t\t\t"DIALOG_TEXT_COLOR "Czy przyjmujesz wyzwanie?\n",GetPlayerNick(playerid), BronieSpar[G[playerid][SparingIDBroni][0]][nazwa], BronieSpar[G[playerid][SparingIDBroni][1]][nazwa]);
				ShowPlayerDialog(IDGracza, DIALOG_SPARING_PROPOZYCJA, DIALOG_STYLE_MSGBOX, DIALOG_HEAD_COLOR "Sparing",str,"Tak","Nie");
				return 1;
			}
		}
	}
    ShowSparingPlayerInfo(playerid);
    return 0;
}
//------------------------------------------------------------------------------
StartSparing(const gracz1, const gracz2) {
	if(TrwaOdliczanie == false) {
		DemoArenaEnd(gracz1);								DemoArenaEnd(gracz2);
        setPlayerStatus(gracz1, S_SPAR);						setPlayerStatus(gracz2, S_SPAR);
	    ResetPlayerWeapons(gracz1); 						ResetPlayerWeapons(gracz2);
	    SetPlayerVirtualWorld(gracz1, gracz1 + VW_SPARING);   	SetPlayerVirtualWorld(gracz2, gracz1 + VW_SPARING);
	    SetPlayerHealthEx(gracz1, 100);               		SetPlayerHealthEx(gracz2, 100);
	    TogglePlayerControllable(gracz1, false);   			TogglePlayerControllable(gracz2, false);
	    SetPlayerArmourEx(gracz1, 0);                 		SetPlayerArmourEx(gracz2, 0);
		
	    SetPlayerInterior(gracz1, 0);               		SetPlayerInterior(gracz2, 0);
	    SetCameraBehindPlayer(gracz1);              		SetCameraBehindPlayer(gracz2);
	    //SetPlayerInterior(gracz1, 1);                       SetPlayerInterior(gracz2, 1);
	    SetPlayerTeam(gracz1, NO_TEAM);                 	SetPlayerTeam(gracz2, NO_TEAM);
	    DialogHideForPlayer(gracz1);                        DialogHideForPlayer(gracz2);

        G[gracz2][SparingIDBroni][0] = G[gracz1][SparingIDBroni][0];
        G[gracz2][SparingIDBroni][1] = G[gracz1][SparingIDBroni][1];
/*
		SetPlayerPos(gracz1, 169.5472, -1981.8058, 2077.2224);
		SetPlayerPos(gracz2, 201.2994, -1950.2238, 2077.2224);
		SetPlayerFacingAngle(gracz1, 313.6261);				
		SetPlayerFacingAngle(gracz2, 131.2643);		
*/
		SetPlayerPos(gracz1, 1887.4681,-2493.7642,13.5391);
		SetPlayerPos(gracz2, 1837.9824,-2493.6970,13.5547); 
		SetPlayerFacingAngle(gracz1, 89.0698);				
		SetPlayerFacingAngle(gracz2, 267.6479);
		
	    StartOdliczaniaSparing(5, gracz1, gracz2);
    }
}
//------------------------------------------------------------------------------
KoniecSparingu(const playerid) {
	if(!IsPlayerConnected(playerid)) return 1;
	else {
	    new R = random(sizeof(g_LoadedLobbySpawns));
		setPlayerStatus(playerid, S_SPAWN);
		switch(getPlayerTeam(playerid)) {
		    case T_ATT: SetPlayerColor(playerid, COLOR_ATT_NAK);
		    case T_DEF: SetPlayerColor(playerid, COLOR_DEF_NAK);
		    case T_REF: SetPlayerColor(playerid, COLOR_REF);
	    }
	    SetPlayerInterior(playerid, 0);
		ResetPlayerWeapons(playerid);
		SetPlayerArmourEx(playerid, 0);
		SetPlayerHealthEx(playerid, 100);
		SetPlayerInterior(playerid, SPAWN_INTERIOR);
		SetPlayerVirtualWorld(playerid, VW_SPAWN);
		SetPlayerPos(playerid, g_LobbySpawnPos[R][0], g_LobbySpawnPos[R][1], g_LobbySpawnPos[R][2]);
		SetPlayerTeam(playerid, T_REF);
	    LayoutPlayerCountdown(playerid, false);
	    TogglePlayerControllable(playerid,1);
  	}
	return 1;
}
//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
new bool:playerUseDemo[MAX_PLAYERS],
	Float:playerDemoZoneArea[MAX_PLAYERS][6];
//------------------------------------------------------------------------------
DemoArena(playerid, arenaid, side) {
    if(getPlayerStatus(playerid) == S_SPAWN) {
        if(500 >= arenaid >= 0 and 1 >= side >= 0) {
			new string[128];
			format(string, 64, "HighSkill/Areny/%d.txt", arenaid);
	        if(fexist(string)) {
	            new File:f_open = fopen(string, io_read);
	            new Float:spawnPos[5], Float:home[3], interior, Float:zone[6] = {-9999.0, -9999.0, ...};
				new modelid, Float:oPosX, Float:oPosY, Float:oPosZ, Float:oRotX, Float:oRotY, Float:oRotZ;
				new len;
				
				DemoArenaEnd(playerid);
				
				while(fread(f_open, string, sizeof(string))) {
				    if(strlen(string) > 4) {
						DeleteSpecialChars(string);
						DeleteSpaces(string);

				        if(strcmp(string, "home", true, 4) == 0) {
							sscanf(string[5], "p<,>fff", home[0], home[1], home[2]);
			            } else if((strcmp(string, "Att", true, 3) == 0 || strcmp(string, "T1_0", true, 4) == 0) && side == 0) {
					        len = strcmp(string, "T1_0", true, 4) == 0 ? 5 : 4;
							sscanf(string[len], "p<,>fffff", spawnPos[0], spawnPos[1], spawnPos[2], spawnPos[3], spawnPos[4]);
					    } else if((strcmp(string, "Def", true, 3) == 0 || strcmp(string, "T2_0", true, 4) == 0) && side == 1) {
					        len = strcmp(string, "T2_0", true, 4) == 0 ? 5 : 4;
						    sscanf(string[len], "p<,>fffff", spawnPos[0], spawnPos[1], spawnPos[2], spawnPos[3], spawnPos[4]);
					    } else if(strcmp(string, "Obszar", true, 6) == 0) {
							sscanf(string[7], "p<,>ffffff", zone[1], zone[3], zone[0], zone[2], zone[4], zone[5]);							
							if(zone[4] == 0 or zone[4] >= zone[5]) zone[4] = -9999.0;
							if(zone[5] == 0 or zone[5] <= zone[4]) zone[5] = 9999.0;
					    } else if(strcmp(string, "Object", true, 6) == 0) {
							sscanf(string[7], "p<,>dffffff", modelid, oPosX, oPosY, oPosZ, oRotX, oRotY, oRotZ);
						    CreatePlayerObject(playerid, modelid, oPosX, oPosY, oPosZ, oRotX, oRotY, oRotZ);
						}
						else if(strcmp(string, "Interior", true, 8) == 0) interior = strval(string[9]);	
			        }
				}
	            
	            fclose(f_open);
	            
	            playerUseDemo[playerid] = true;
	            SetPlayerPos(playerid, spawnPos[0], spawnPos[1], spawnPos[2]);
	            SetPlayerInterior(playerid, interior);
	            SetPlayerVirtualWorld(playerid, VW_DEMO + playerid);
	            SetPlayerCheckpoint(playerid, home[0], home[1], home[2], g_RoundCaptureCheckpointSize);
	            
	            if(zone[0] + zone[1] + zone[2] + zone[3] != -39996) {
	                /*
	                    Wazne, zeby przypisanie obszaru nastapilo po ustawieniu pozycji gracza.
	                */
				    playerDemoZoneArea[playerid][0] = zone[0];
				    playerDemoZoneArea[playerid][1] = zone[1];
				    playerDemoZoneArea[playerid][2] = zone[2];
				    playerDemoZoneArea[playerid][3] = zone[3];
				    playerDemoZoneArea[playerid][4] = zone[4];
					playerDemoZoneArea[playerid][5] = zone[5];
					
					setPlayerWorldArea(playerid, playerDemoZoneArea[playerid][0], playerDemoZoneArea[playerid][1], playerDemoZoneArea[playerid][2], playerDemoZoneArea[playerid][3], playerDemoZoneArea[playerid][4], playerDemoZoneArea[playerid][5], true, GANG_ZONE_COLOR);
	            }

	            format(string, sizeof(string), " (Demo Arena) Uruchomiles(as) wersje pokazowa areny o ID: "C_WHITE"%d "C_LIGHTGREEN"(Spawn: "C_WHITE"%s"C_LIGHTGREEN").", arenaid, side == 0 ? ("Atak") : ("Obrona"));
	            SendClientMessage(playerid, COLOR_LIGHTGREEN, string);
	            SendClientMessage(playerid, COLOR_LIGHTGREEN, " (Demo Arena) Zeby wjsc z areny pokazowej wpisz '"C_WHITE"/demoend"C_LIGHTGREEN"'.");
	            return 1;
	        }
        }
    }
    return 0;
}
//------------------------------------------------------------------------------

DemoArenaEnd(playerid) {
	if(playerUseDemo[playerid] == true) {
        for(new i; i < MAX_OBJECTS; i ++) {
            if(IsValidPlayerObject(playerid, i)) {
       			DestroyPlayerObject(playerid, i);
			} else break;
        }
		deletePlayerWorldArea(playerid);
        DisablePlayerCheckpoint(playerid);
	    return 1;
	}
	return 0;
}
//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
