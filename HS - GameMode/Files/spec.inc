//===========================================================================================================
//-----------------------------------------------------------------------------------------------------------
//===========================================================================================================
StartRandomSpectate(playerid) {
	if(IDStartowanej != -1 AND TrwaOdliczanie == false) {
		new specPlayers[MAX_GRACZY] = {-1, -1, ...}, fouded;
		for(new i, mainTeam = getPlayerTeam(playerid), bool:isAdmin = (IsAdmin(playerid) != 0 or mainTeam == T_REF ? true : false); i < MAX_GRACZY; i ++) {
			if(IsPlayerConnected(i)) {
				if(i != playerid) {
					if(mainTeam == getPlayerTeam(i) OR isAdmin == true) {
						if(getPlayerStatus(i) == S_GRA) {
							specPlayers[fouded ++] = i;
						}
					}
				}
			}
		}
		if(fouded > 0) {
			return StartSpectate(playerid, specPlayers[random(fouded)]);
		}
	}
	return 0;
}
//-----------------------------------------------------------------------------------------------------------
forward StartSpectate(playerid, specid);
public StartSpectate(playerid, specid) {
   	if(getPlayerStatus(playerid) == S_SPAWN OR getPlayerStatus(playerid) == S_SPECUJE) {
	
		DemoArenaEnd(playerid);		
	
		if(getPlayerStatus(specid) == S_GRA) {
			if(IDStartowanej != -1 AND TrwaOdliczanie == false) {
	    		if(playerid != specid) {
		        	if(getPlayerTeam(playerid) == getPlayerTeam(specid) OR getPlayerTeam(playerid) == T_REF OR IsAdmin(playerid) != 0) {
			            SetPlayerVirtualWorld(playerid, VW_GRA);
			            TogglePlayerSpectating(playerid, 1);
			            SetPlayerInterior(playerid,GetPlayerInterior(specid));
			            G[playerid][SpecowanyID] = specid;
			        	setPlayerStatus(playerid, S_SPECUJE);
						
						if(IsPlayerInAnyVehicle(specid))	PlayerSpectateVehicle(playerid, GetPlayerVehicleID(specid));
						else								PlayerSpectatePlayer(playerid, specid);						

						TextDrawSetString(PTD_SpecNick[playerid], GetPlayerNick(specid));					

					    TextDrawHideForPlayer(playerid, G[playerid][TDZdrowie]);
						LayoutSpecPlayer(playerid, true);
			        	return 1;
		        	}
	        	}
	        }
		}
    }
	return 0;
}
//-----------------------------------------------------------------------------------------------------------
StopSpec(const playerid) {
    LayoutSpecPlayer(playerid, false);
	TogglePlayerSpectating(playerid, 0);
	G[playerid][SpecowanyID] = INVALID_PLAYER_ID;
   	setPlayerStatus(playerid, S_SPAWN);
   	SpawnPlayer(playerid);
}