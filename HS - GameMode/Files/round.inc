//===========================================================================================================
//-----------------------------------------------------------------------------------------------------------
//===========================================================================================================
StartRundy(const sciezka[]) {
	
	new i, string[128], Autor[24] = "Standard", ArmorInfo[8] = "Brak",
	    modelid, Float:oPosX, Float:oPosY, Float:oPosZ, Float:oRotX, Float:oRotY, Float:oRotZ,
	    File:Plik = fopen(sciezka, io_read),
	    Metoda, KamDys = 100, len;

	//--------------------
	
	for(i = 0; i < 5; i ++) SendDeathMessage(201, 201, 0);
	restoreDefaultRoundSettings();
	
	#if _TESTY == 0
	if(getPlayersInTeam(T_ATT) == 0 || getPlayersInTeam(T_DEF) == 0) {
	    IDStartowanej = -1;
	    SendClientMessageToAll(COLOR_WARNING, " (Start Rundy) Runda nie moze zostac rozpoczeta z powodu braku minimalnej ilosci graczy w druzynach");
	    return 0;
    }
	#endif

	if(!fexist(sciezka)) {
		IDStartowanej = -1;
	    format(string, sizeof(string)," (Start Rundy) Nie znaleziono pliku pod adresem: "TEXT_NORMAL"%s", sciezka);
		return SendClientMessageToAll( COLOR_WARNING,string);
	}	
	//--------------------	

	for(i = sizeof(OstatnieStarty) - 1; i >= 1; i --) {
	    OstatnieStarty[i][0] = OstatnieStarty[i - 1][0];
	    OstatnieStarty[i][1] = OstatnieStarty[i - 1][1];
	}	
    OstatnieStarty[0][0] = TypArena == true ? 0 : 1;
    OstatnieStarty[0][1] = IDStartowanej;
    
    SetGameModeText("Trwa odliczanie do startu...");
        
		
	//-------------------------
    
	while(fread(Plik, string, 128)) {
	    if(strlen(string) > 4) {
			DeleteSpecialChars(string);
			DeleteSpaces(string);

	        if(strcmp(string, "home", true, 4) == 0) {
				sscanf(string[5], "p<,>fff", CheckpointPos[0], CheckpointPos[1], CheckpointPos[2]);
            } else if(strcmp(string, "autor", true, 5) == 0) {
                if(IsValidNick(string[6]) == _TRUE) {
                    Autor[0] = EOS;
					strins(Autor, string[6], 0);
				} 
            } else if(strcmp(string, "Att", true, 3) == 0 || strcmp(string, "T1_0", true, 4) == 0) {
		        len = strcmp(string, "T1_0", true, 4) == 0 ? 5 : 4;
				sscanf(string[len], "p<,>fffff", SpawnAtt[0], SpawnAtt[1], SpawnAtt[2], SpawnAtt[3], SpawnAtt[4]);
		    } else if(strcmp(string, "Def", true, 3) == 0 || strcmp(string, "T2_0", true, 4) == 0) {
		        len = strcmp(string, "T2_0", true, 4) == 0 ? 5 : 4;
				sscanf(string[len], "p<,>fffff", SpawnDef[0], SpawnDef[1], SpawnDef[2], SpawnDef[3], SpawnDef[4]);
		    } else if(strcmp(string, "Obszar", true, 6) == 0) {
				sscanf(string[7], "p<,>ffffff", ObszarWalki[1], ObszarWalki[3], ObszarWalki[0], ObszarWalki[2], ObszarWalki[4], ObszarWalki[5]);				
				if(ObszarWalki[4] == 0 or ObszarWalki[4] >= ObszarWalki[5]) ObszarWalki[4] = -9999.0;
				if(ObszarWalki[5] == 0 or ObszarWalki[5] <= ObszarWalki[4]) ObszarWalki[5] = 9999.0;
		    } else if(strcmp(string, "Object", true, 6) == 0) {
				sscanf(string[7], "p<,>dffffff", modelid, oPosX, oPosY, oPosZ, oRotX, oRotY, oRotZ);
			    CreateObject(modelid, oPosX, oPosY, oPosZ, oRotX, oRotY, oRotZ);
			} else if(strcmp(string, "Lodz", true, 4) == 0) {
				sscanf(string[5], "p<,>ffff", SpawnLodzi[0], SpawnLodzi[1], SpawnLodzi[2], SpawnLodzi[3]);
		    }
			else if(strcmp(string, "Interior", true, 8) == 0) InteriorWalki = strval(string[9]);
		    else if(strcmp(string, "Granat", true, 6) == 0) DostepnyGranat = strval(string[7]) == 1 ? true : false;			
        }
    }
	fclose(Plik);

	if(SpawnAtt[3] == 0) SpawnAtt[3] = 5;
	if(SpawnAtt[4] == 0) SpawnAtt[4] = 5;
	if(SpawnDef[3] == 0) SpawnDef[3] = 5;
	if(SpawnDef[4] == 0) SpawnDef[4] = 5;
	
	//-------------------------
	
	g_RoundArenaAngles[0] = angleToPoint(SpawnAtt[0], SpawnAtt[1], CheckpointPos[0], CheckpointPos[1]);
	g_RoundArenaAngles[1] = angleToPoint(SpawnDef[0], SpawnDef[1], CheckpointPos[0], CheckpointPos[1]);
    	
		
	
    //-------------------------
    
	LayoutPlayerTrainingArena(-1, false);
	LayoutPlayerOneOnOne(-1, false);
	LayoutPlayerRoundWin(-1, false);
	LayoutPlayerCountdown(-1, false);

	TextDrawHideForAll(TDCarInfo);
	TextDrawHideForAll(TDVoteName);
	TextDrawHideForAll(TDVoteInfo);
	//-------------------------
	
	if(TypArena == true) {
		printf("(Info) Rozpoczeto runde %d (Arena).", IDStartowanej);
		CzasMin = CZAS_ARENY;
		g_RoundSpawnProtectTime = SPAWN_PROTECT_ARENA;
		format(string, sizeof(string), "Arena %d", IDStartowanej);
		TextDrawSetString(TDBottomBeltCenter[1], string);
		format(string, sizeof(string),"Arena ~w~%d", IDStartowanej);
		TextDrawSetString(TDStartRundyNazwa, string);
		TextDrawSetString(TDStartRundyInformacjeInfo, "- Informacje o arenie -");
	} else {
		printf("(Info) Rozpoczeto runde %d (Baza).", IDStartowanej);
		CzasMin = CZAS_BAZY;
		g_RoundSpawnProtectTime = SPAWN_PROTECT_BASE;
		format(string, sizeof(string), "Baza %d", IDStartowanej);
		TextDrawSetString(TDBottomBeltCenter[1], string);		
		format(string, sizeof(string),"Baza ~w~%d", IDStartowanej);
		TextDrawSetString(TDStartRundyNazwa, string);
		TextDrawSetString(TDStartRundyInformacjeInfo, "- Informacje o bazie -");
	}
	
	TextDrawSetString(TDStartRundyKropki, ".... wystartuje za kilka sekund ....");
	
	if(MAX_ARMOUR > 0)  valstr(ArmorInfo, MAX_ARMOUR);
	format(string, sizeof(string),"Autor: %s~n~Armor: %s  |  Dodatkowy granat: %s", Autor, ArmorInfo, DodatkowyGranat == true && DostepnyGranat == true ? ("Tak") : ("Nie"));
	TextDrawSetString(TDStartRundyInformacje, string);
	
	//-------------------------
	

	for(i = 0; i < MAX_PLAYERS; i ++) {
		if(IsPlayerConnected(i)) {
			LayoutBottomBelt(i, false);
			LayoutPlayerHud(i, false);
			LayoutPingFPS(i, false);
			LayoutTime(i, false);
		//	LayoutSmallLogo(i, false);
			
			DemoArenaEnd(i);
			G[i][IDPojazdu] = 0;
			G[i][UdzialWWalceTeam] = T_NoN;
			
			SetPVarInt(i, PV_TAB, 0);
			
			if(getPlayerStatus(i) != S_WYBIERALKA and getPlayerStatus(i) != S_NON) {
				TextDrawShowForPlayer(i, TDStartRundyBox1);
				TextDrawShowForPlayer(i, TDStartRundyBox2);
				TextDrawShowForPlayer(i, TDStartRundyNazwa);
				TextDrawShowForPlayer(i, TDStartRundyPasek);
				TextDrawShowForPlayer(i, TDStartRundyKropki);
				TextDrawShowForPlayer(i, TDStartRundyInformacjeInfo);
				TextDrawShowForPlayer(i, TDStartRundyInformacje);
				TextDrawHideForPlayer(i, G[i][TDZdrowie]);

				TogglePlayerSpectating(i, true);
				DisablePlayerCheckpoint(i);
				DialogHideForPlayer(i);
				setPlayerStatus(i, S_SPAWN);
				ResetPlayerWeapons(i);
				SetPVarInt(i, PV_HEAL, 3);
				SetPlayerHealthEx(i, 100);
				SetPlayerArmourEx(i, 0);
				TogglePlayerControllable(i, false);
				SetPlayerPos(i, CheckpointPos[0], CheckpointPos[1], CheckpointPos[2] - 5);
				SetPlayerVirtualWorld(i, VW_GRA);
				SetPlayerInterior(i, InteriorWalki);
				if(TypArena == false) {
					CreateObject(2993,CheckpointPos[0], CheckpointPos[1], CheckpointPos[2] - 1,0,0,0);
					if(InteriorWalki == 0) {
						SetPlayerMapIcon(i, 0, CheckpointPos[0], CheckpointPos[1], CheckpointPos[2], 6, 0, MAPICON_GLOBAL_CHECKPOINT);
						SetPlayerMapIcon(i, 1, SpawnAtt[0], SpawnAtt[1], SpawnAtt[2], 55, 0, MAPICON_GLOBAL);
						if(SpawnLodzi[0] != 0.0 && SpawnLodzi[1] != 0.0 && SpawnLodzi[2] != 0.0) SetPlayerMapIcon(i, 2, SpawnLodzi[0], SpawnLodzi[1], SpawnLodzi[2], 9, 0, MAPICON_GLOBAL);
					}   else SetPlayerCheckpoint(i, CheckpointPos[0], CheckpointPos[1], CheckpointPos[2], g_RoundCaptureCheckpointSize);
				}	else SetPlayerMapIcon(i, 0, CheckpointPos[0], CheckpointPos[1], CheckpointPos[2], 62, 0, MAPICON_GLOBAL);
			}
		}
  	}
	    
	//-------------------------
		
	if(teamBalance() == 1)  SendClientMessageToAll(COLOR_TEAM_CHANGE," (Auto Balans) Druzyny zostaly zbalansowane");
	else SendClientMessageToAll(COLOR_TEAM_CHANGE," (Auto Balans) Balans druzyn nie jest konieczny");
		
	//-------------------------
	    
	TrwaOdliczanie = true;
	StartCameraLook(0, CheckpointPos[2] + 2, Metoda, KamDys);
	RoundCountdown(5);
	
	return 1;
}
//-----------------------------------------------------------------------------------------------------------
KoniecRundy(const winTeam, const reason)
{
	new string[150], playerGetRespect, topRespectCount[5], topRespectID[5] = {INVALID_PLAYER_ID, INVALID_PLAYER_ID, ...}, topRespectTeam[5] = {T_NoN, T_NoN, ...};
	new bool:WygranaDruzyny;
	new IDRundy = IDStartowanej;
	new x, y;

    TextDrawSetString(TDWinRoundStats[0], " ");
    TextDrawSetString(TDWinRoundStats[1], " ");
    TextDrawSetString(TDWinRoundStats[2], " ");

	format(string, sizeof(string), "%s  ~w~%d", TypArena == true ? ("Arena") : ("Baza"), IDRundy);
    TextDrawSetString(TDWinRoundInfo[0], string);
	
	printf("(Info) Poprawnie zakonczono runde.");
	
	switch(winTeam) {
		case T_ATT: TextDrawSetString(TDWinRoundInfo[1], "Wygrywa druzyna ~w~'Atak'");
		case T_DEF: TextDrawSetString(TDWinRoundInfo[1], "Wygrywa druzyna ~w~'Obrona'");
		case T_REF: TextDrawSetString(TDWinRoundInfo[1], "Remis");
    }
	
	lastVIPRound ++;

    forplayers(i) {
		
        if(T_ATT <= G[i][UdzialWWalceTeam] <= T_DEF) {
            WygranaDruzyny = false;
            playerGetRespect = floatround(floatdiv(G[i][gDMGRunda], 20), floatround_floor) * MNOZNIK_RSP_DMG;

	        if(G[i][UdzialWWalceTeam] == winTeam) {
	        	playerGetRespect += 3;
	        	WygranaDruzyny = true;
			}
			if(playerGetRespect > 0) {
				AddPlayerRespect(i, playerGetRespect);

                format(string, sizeof(string), " (Respect) Otrzymales "TEXT_NORMAL"%d"TEXT_RESPECT_INFO" punktow respectu za udzial w walce  [  DMG: %d  ( Resp: %d ) | Zwyciestwo druzyny: %d  ]", playerGetRespect, G[i][gDMGRunda], WygranaDruzyny == true ? playerGetRespect - 3 : playerGetRespect, WygranaDruzyny == true ? 3 : 0);
	        	SendClientMessage(i,COLOR_RESPECT_INFO, string);
	        	UpdatePlayerStats(i);

				if(playerGetRespect >= topRespectCount[sizeof(topRespectCount) - 1]) {
				    for(x = 0; x < sizeof(topRespectCount); x ++) {
						if(topRespectCount[x] <= playerGetRespect) {
						    for(y = sizeof(topRespectCount) - 1; y > x; y --) {
                                topRespectID[y] = topRespectID[y - 1];
                                topRespectCount[y] = topRespectCount[y - 1];
                                topRespectTeam[y] = topRespectTeam[y - 1];
						    }
					        topRespectID[x] = i;
					        topRespectCount[x] = playerGetRespect;
					        topRespectTeam[x] = G[i][UdzialWWalceTeam];
					        break;
						}
				    }
				}
			}
		}

		switch(getPlayerStatus(i)) {
		    case S_GRA: {
				DialogHideForPlayer(i);
		        setPlayerStatus(i, S_SPAWN);
		        OnPlayerSpawn(i);
		    }
		    case S_SPECUJE: StopSpec(i);
		    case S_SPAWN: {/* Nie usuwac. Odpowiedzialne za pokazywanie tabeli wynikow dla osob bedacych przed zakonczeniem na spawnie */}
		    default: continue;
		}
        PlayerPlaySound(i, 1185, 0, 0, 0);
        LayoutPlayerRoundWin(i, true);
		CallRemoteFunction("UpdatePlayerDailyStatInfo", "ddddd", i, G[i][gFragi], G[i][gSmierci], G[i][gDMG], G[i][gRespect]);
    }

	if(TypArena == false and reason == 1) {
		AddPlayerRespect(PrzejmujacyCP, 3);
		UpdatePlayerStats(PrzejmujacyCP);
		SendClientMessage(PrzejmujacyCP, COLOR_RESPECT_INFO, " (Baza) Otrzymales(as) dodatkowe "TEXT_NORMAL"3"TEXT_RESPECT_INFO" punkty respektu za przejecie checkpointu");
    }
	
	strdel(string, 0, 150);
	for(x = 0; x < sizeof(topRespectCount); x ++) {
	    if(topRespectID[x] == INVALID_PLAYER_ID) break;
	    else {
	        format(string, sizeof(string), "%s%s~n~", string, GetPlayerNick(topRespectID[x]));
	    }
	}
	
	TextDrawSetString(TDWinRoundStats[0], string);
	strdel(string, 0, 150);
	for(x = 0; x < sizeof(topRespectCount); x ++) {
	    if(topRespectID[x] == INVALID_PLAYER_ID) break;
	    else {
	        format(string, sizeof(string), "%s%d~n~", string, topRespectCount[x]);
	    }
	}
	
	TextDrawSetString(TDWinRoundStats[1], string);
	strdel(string, 0, 150);
	for(x = 0; x < sizeof(topRespectCount); x ++) {
	    if(topRespectID[x] == INVALID_PLAYER_ID) break;
	    else {
	        format(string, sizeof(string), "%s%s~n~", string, topRespectTeam[x] == T_ATT ? ("Atak") : topRespectTeam[x] == T_DEF ? ("Obrona") : ("NoN"));
	    }
	}
	TextDrawSetString(TDWinRoundStats[2], string);
	
	endRoundFunc(false);
	SwapOczekiwanie = true;
    SetGameModeText("Koniec rundy");
	SetTimer("KoniecTablicyWynikow", 8000, 0);
	

	return 1;
}
//-----------------------------------------------------------------------------------------------------------
TimerSpawnProtect() {
	if(g_RoundSpawnProtectTime > 0) {
        if( -- g_RoundSpawnProtectTime == 0) {
        	g_RoundSpawnProtectTime = -1;
            TextDrawSetString(TDWinSpawnProtectInfo, "Spawn protect  ~w~First Blood");
			forplayers(i) {
			    if(getPlayerStatus(i) == S_GRA) {
			        SetPlayerArmourEx(i, MAX_ARMOUR);
			        SetPlayerHealthEx(i, 100.0);
			        SetPVarInt(i, PV_HEAL, 3);
			        GivePlayerRoundWeapons(i);
			    }
			}
        } else {
	       	new string[32];
			format(string, sizeof(string), "Spawn Protect  ~w~%d", g_RoundSpawnProtectTime);
			TextDrawSetString(TDWinSpawnProtectInfo, string);
			return 1;
		}
	}
	return 0;
}
//-----------------------------------------------------------------------------------------------------------
endRoundFunc(bool:f_players = true) {
    IDStartowanej = -1;
    g_RoundSpawnProtectTime = 0;
					
	LayoutSpawnProtect(-1, false);
	LayoutPlayerOneOnOne(-1, false);
	LayoutPlayerCapture(-1, false);
    TextDrawHideForAll(TDCarInfo);
			
	if(f_players == true) {
		new ZdobytyRespect, string[144];
		forplayers(i) {
			switch(getPlayerStatus(i)) {
				case S_GRA: {
					setPlayerStatus(i, S_SPAWN);
					OnPlayerSpawn(i);
				}
				case S_SPECUJE: StopSpec(i);
			}
			if(T_ATT <= G[i][UdzialWWalceTeam] <= T_DEF) {	            	
				if((ZdobytyRespect = floatround(floatdiv(G[i][gDMGRunda], 20), floatround_floor) * MNOZNIK_RSP_DMG) > 0) {
					AddPlayerRespect(i, ZdobytyRespect);
					format(string, sizeof(string), " (Respect) Otrzymales "TEXT_NORMAL"%d"TEXT_RESPECT_INFO" punktow respectu za udzial w walce. [  DMG: %d  ( Resp: %d )  ]", ZdobytyRespect, G[i][gDMGRunda], ZdobytyRespect);
					SendClientMessage(i,COLOR_RESPECT_INFO, string);
					UpdatePlayerStats(i);
				}
			}
		}
	}
	
    CallRemoteFunction("UpdatePlayerRanking", "d", INVALID_PLAYER_ID);
	restoreDefaultRoundSettings();

}
//-----------------------------------------------------------------------------------------------------------
restoreDefaultRoundSettings() {
	new i;
	//-----------------------------------------
	GlosowanieAktywne = false;
	for(i = 0; i < MAX_VOTE; i ++) {
	    VoteVar[i][Tryb] = -1;
	    VoteVar[i][NumerID] = VoteVar[i][Glosow] = 0;
	}
	for(i = 0; i < MAX_PLAYERS; i ++) {
	    G[i][VoteDodano] = false;
	    G[i][VoteWybor] = -1;
	}
	//-----------------------------------------
	DostepnyGranat = true;
	PrzejmujacyCP = INVALID_PLAYER_ID;
	CzasAdminVote = CzasSek = InteriorWalki = 0;
    SpawnLodzi[0] = SpawnLodzi[1] = SpawnLodzi[2] = SpawnLodzi[3] = 0.0;
    ObszarWalki[0] = ObszarWalki[1] = ObszarWalki[2] = ObszarWalki[3] = -9999;
	ObszarWalki[4] = -9999;
	ObszarWalki[5] = 9999;

	//-----------------------------------------
    for(i = START_OBJECTS; i < MAX_OBJECTS; i ++) {
        DestroyObject(i);
        DestroyVehicle(i - START_OBJECTS);
    }	
	//-----------------------------------------
}
//-----------------------------------------------------------------------------------------------------------
forward RoundCountdown(const czas);
public RoundCountdown(const czas) {
	if(TrwaOdliczanie == true) {
		if(czas >= 0) {
		    switch(czas) {
                case 5: TextDrawSetString(TDStartRundyKropki, ".... wystartuje za kilka sekund ....");
		        case 4: TextDrawSetString(TDStartRundyKropki, "... wystartuje za kilka sekund ...");
		        case 3: TextDrawSetString(TDStartRundyKropki, ".. wystartuje za kilka sekund ..");
		        case 2: TextDrawSetString(TDStartRundyKropki, ". wystartuje za kilka sekund .");
		        default: TextDrawSetString(TDStartRundyKropki, "_wystartuje za kilka sekund_");
		    }

		    if(czas != 0) {
                forplayers(i) {
			        if(GetPlayerVirtualWorld(i) == VW_GRA) PlayerPlaySound(i, 1058, 0, 0, 0);
		        }
			} else {
		 		TextDrawHideForAll(TDStartRundyBox1);
				TextDrawHideForAll(TDStartRundyBox2);
				TextDrawHideForAll(TDStartRundyNazwa);
				TextDrawHideForAll(TDStartRundyPasek);
				TextDrawHideForAll(TDStartRundyKropki);
				TextDrawHideForAll(TDStartRundyInformacjeInfo);
				TextDrawHideForAll(TDStartRundyInformacje);
				
			    TrwaOdliczanie = false;
                forplayers(i) {
			        if(GetPlayerVirtualWorld(i) == VW_GRA)	PlayerPlaySound(i, 1057, 0, 0, 0);
					if(getPlayerStatus(i) != S_WYBIERALKA) {
						LayoutBottomBelt(i, true);
						LayoutPlayerHud(i, true);
						LayoutPingFPS(i, true);
						LayoutTime(i, true);
			//			LayoutSmallLogo(i, true);
						switch(getPlayerTeam(i)) {
							case T_ATT: TextDrawShowForPlayer(i, TDPlayerHudTeam[0]);
							case T_DEF: TextDrawShowForPlayer(i, TDPlayerHudTeam[1]);
							case T_REF: TextDrawShowForPlayer(i, TDPlayerHudTeam[2]);
						}
					}
			        TogglePlayerSpectating(i, false);
                    DodajDoWalki(i);
					TextDrawShowForPlayer(i, G[i][TDZdrowie]);
		        }
		    }
			SetTimerEx("RoundCountdown",600,0,"d", czas - 1);
		}
    }
}
	
//-----------------------------------------------------------------------------------------------------------

forward KoniecTablicyWynikow();
public KoniecTablicyWynikow() {
    SwapOczekiwanie = false;
    LayoutPlayerRoundWin(-1, false);
    if(mixTeams() == 0) {
        swapTeams();
        SendClientMessageToAll(COLOR_TEAM_CHANGE," (Auto Swap) Druzyny zostaly automatycznie zamienione");
    } else SendClientMessageToAll(COLOR_TEAM_CHANGE," (Auto Mix) Druzyny zostaly automatycznie pomieszane");

    forplayers(i) {
	    if(IsAdmin(i) > ALVL_NON) CzasAdminVote = 10;
	    if(getPlayerStatus(i) != S_WYBIERALKA) PlayerPlaySound(i, 1186, 0, 0, 0);
    }
}