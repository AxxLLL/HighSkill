//=================================================================================
//---------------------------------------------------------------------------------
//=================================================================================
forward OnPlayerTeamChange(playerid, newteam, oldteam);
//=================================================================================
new g_PlayersInTeam[2];
new g_PlayerTeam[MAX_PLAYERS] = {T_NoN, T_NoN, ...};
new g_AlivePlayersInTeam[2];
new g_TeamSkins[3] = {SKIN_ATT, SKIN_DEF, SKIN_REF};
new g_TeamColors[3][2] = {{COLOR_ATT_AK, COLOR_ATT_NAK}, {COLOR_DEF_AK, COLOR_DEF_NAK}, {COLOR_REF, COLOR_REF}};
new g_MixCounter;
new g_RoundMixCounter = 3; // Ilosc rund, jaka ma zostac rozegrana do automatycznego mix'a.
//=================================================================================
getAlivePlayersInTeam(teamid) return T_ATT <= teamid <= T_DEF ? g_AlivePlayersInTeam[teamid] : 0;
getPlayersInTeam(teamid) return T_ATT <= teamid <= T_DEF ? g_PlayersInTeam[teamid] : 0;
//---------------------------------------------------------------------------------
getTeamSkin(teamid) return g_TeamSkins[teamid];
//---------------------------------------------------------------------------------
getPlayerTeam(playerid) return g_PlayerTeam[playerid];
setPlayerTeam(playerid, newteam) {
	if(T_ATT <= newteam <= T_REF or newteam == T_NoN) {
		new oldteam = g_PlayerTeam[playerid];
		if(oldteam != newteam) {
		    g_PlayerTeam[playerid] = newteam;
			if(newteam != T_NoN) {
				SetPlayerColor(playerid, g_TeamColors[newteam][1]);
				SetSpawnInfo(playerid, T_REF, g_TeamSkins[newteam], 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
				if(!IsPlayerInAnyVehicle(playerid) and getPlayerStatus(playerid) == S_SPAWN) {
					SpawnPlayer(playerid);
				}
			} else SetPlayerColor(playerid, COLOR_GREY);
		    OnPlayerTeamChange(playerid, newteam, oldteam);
		    return 1;
		}
	}
	return 0;
}
//---------------------------------------------------------------------------------
swapTeams() {
	for(new i, pTeam; i < MAX_PLAYERS; i ++) {
		if(IsPlayerConnected(i) and T_ATT <= (pTeam = getPlayerTeam(i)) <= T_DEF) {
			setPlayerTeam(i, pTeam == T_ATT ? T_DEF : T_ATT);
		}
	}
}
//---------------------------------------------------------------------------------
mixTeams(playerid = INVALID_PLAYER_ID) {
	if(playerid != INVALID_PLAYER_ID or ++ g_MixCounter >= g_RoundMixCounter) {
		new possiblePlayers[MAX_PLAYERS], playerCounter;
		g_MixCounter = 0;
		forplayers(i) {
			if(T_ATT <= getPlayerTeam(i) <= T_DEF) {
				possiblePlayers[playerCounter ++] = i;
			}
		}
		if(playerCounter > 0) {
			new teamID = T_DEF;
			new rand;
			while(playerCounter > 0) {
				teamID = (teamID == T_ATT ? T_DEF : T_ATT);
				setPlayerTeam(possiblePlayers[(rand = random(playerCounter --))], teamID);	
				if(rand < playerCounter) possiblePlayers[rand] = possiblePlayers[playerCounter];		
			}
			return 1;
		}	
	}
	return 0;
}
//---------------------------------------------------------------------------------
teamBalance() {
	new x;
	x = getPlayersInTeam(T_ATT) - getPlayersInTeam(T_DEF);
	if( x < -1 || x > 1) {
		if(x > 0) {
            x = floatround(x / 2);
			forplayers(i) {
				if(getPlayerTeam(i) == T_ATT) {
					setPlayerTeam(i, T_DEF);
                    TextDrawHideForPlayer(i, TDPlayerHudTeam[T_ATT]);
                    TextDrawShowForPlayer(i, TDPlayerHudTeam[T_DEF]);
                    SendClientMessage(i, COLOR_TEAM_CHANGE, " (Auto Balans) Zostales(as) przeniesiony(a) do druzyny "TEXT_NORMAL"Obrony");					
					if(--x == 0) break;
				}
			}
		} else {
            x = floatround(floatabs(x) / 2);
			forplayers(i) {
				if(getPlayerTeam(i) == T_DEF) {
					setPlayerTeam(i, T_ATT);
                    TextDrawShowForPlayer(i, TDPlayerHudTeam[T_ATT]);
                    TextDrawHideForPlayer(i, TDPlayerHudTeam[T_DEF]);
                    SendClientMessage(i, COLOR_TEAM_CHANGE, " (Auto Balans) Zostales(as) przeniesiony(a) do druzyny "TEXT_NORMAL"Ataku");					
					if(--x == 0) break;
				}
			}
		}		
        return 1;
	}
	return 0;
}
//---------------------------------------------------------------------------------
adminTeamChange(playerid, listitem = -1) {
	if(IsAdmin(playerid) != ALVL_NON or IsVIP(playerid) == _TRUE) {
		if(listitem == -1) {
			ShowPlayerDialog(playerid, DIALOG_ADMIN_TEAM_CHANGE, DIALOG_STYLE_LIST, DIALOG_HEAD_COLOR "Switch", DIALOG_COUNT_COLOR "1) "DIALOG_TEXT_COLOR "Atak\n"DIALOG_COUNT_COLOR "2) "DIALOG_TEXT_COLOR "Obrona\n"DIALOG_COUNT_COLOR "3) "DIALOG_TEXT_COLOR "Arbiter", "Wybierz", "Wyjdz");
		} else {
			if(getPlayerStatus(playerid) == S_SPAWN) {
				new string[150];
				switch(listitem) {
					case 0: {
						if(getPlayerTeam(playerid) == T_ATT) return 1;
						if(getPlayersInTeam(T_ATT) - getPlayersInTeam(T_DEF) > 0) return SendClientMessage(playerid, COLOR_WARNING," (Switch) W druzynie Ataku jest zbyt wielu graczy");
						else {
							setPlayerTeam(playerid, T_ATT);
							format(string, sizeof(string)," (Switch) "TEXT_NORMAL"%s"TEXT_TEAM_CHANGE" dolaczyl(a) do druzyny "TEXT_NORMAL"Ataku", GetPlayerNick(playerid));
							SendClientMessageToAll(COLOR_TEAM_CHANGE, string);
						}	
					}
					case 1: {
						if(getPlayerTeam(playerid) == T_DEF) return 1;
						else if(getPlayersInTeam(T_DEF) - getPlayersInTeam(T_ATT) > 0) return SendClientMessage(playerid, COLOR_WARNING," (Switch) W druzynie Obrony jest zbyt wielu graczy");
						else {
							setPlayerTeam(playerid, T_DEF);
							format(string, sizeof(string)," (Switch) "TEXT_NORMAL"%s"TEXT_TEAM_CHANGE" dolaczyl(a) do druzyny "TEXT_NORMAL"Obrony", GetPlayerNick(playerid));
							SendClientMessageToAll(COLOR_TEAM_CHANGE, string);
						}					
					}
					case 2: {
						if(getPlayerTeam(playerid) == T_REF) return 1;
						setPlayerTeam(playerid, T_REF);
						format(string, sizeof(string)," (Switch) "TEXT_NORMAL"%s"TEXT_TEAM_CHANGE" dolaczyl(a) do druzyny "TEXT_NORMAL"Arbitrow", GetPlayerNick(playerid));
						SendClientMessageToAll(COLOR_TEAM_CHANGE, string);					
					}
				}
				return 1;
			}
		}
	}
	return 0;
}
//=================================================================================
//---------------------------------------------------------------------------------
//=================================================================================
forward OnPlayerStatusChange(playerid, newstatus, oldstatus);
//=================================================================================
getPlayerStatus(playerid) return GetPVarInt(playerid, PV_STAN_GRACZA);
setPlayerStatus(playerid, newstatus) {
	if(S_NON <= newstatus <= S_SPECUJE) {
		new oldstatus = GetPVarInt(playerid, PV_STAN_GRACZA);
		if(oldstatus != newstatus) {
			SetPVarInt(playerid, PV_STAN_GRACZA, newstatus);
			OnPlayerStatusChange(playerid, newstatus, oldstatus);
			return 1;
		}
	}
	return 0;
}