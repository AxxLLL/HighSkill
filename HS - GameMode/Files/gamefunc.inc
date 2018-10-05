//===========================================================================================================
//-----------------------------------------------------------------------------------------------------------
//===========================================================================================================

/*
	Fazy glosowania:
		1) Pierwsze piec sekund, bez sprawdzania przewagi. Po uplywie czasu, sprawdzane sa oddane glosy i w przypadku uzyskania przewagi, startowana jest arena. 
			Przewage mozna uzyskac przez:
				1) Oddana zostala tylko jedna propozycja glosowania.
				2) Jedna z propozycji uzyskala przewage 1:3 w stosunku do pozostalych.
		2) Kolejne piec sekund to czas swobodnego glosowania i dodawania pozycji. Po kazdym glosie sprawdzana jest przewaga 'topowej' pozycji, nad druga i jesli wynosi min. 3:1, pozycja jest startowana.
		3) Ostatnie piec sekund to czas swobodnego glosowania.
*/

CheckVotePossibility() {
	if(GlosowanieAktywne == true) {
		new nVoters, vTop = -1, vSecond = -1;

		for(new i; i < MAX_VOTE; i ++) {
			if(VoteVar[i][Tryb] != -1) {
				if(vTop == -1) vTop = i;
				else {
					if(VoteVar[i][Glosow] >= VoteVar[vTop][Glosow]) {
						vSecond = vTop;
						vTop = i;
					} else {
						if(vSecond == -1 or VoteVar[i][Glosow] >= VoteVar[vSecond][Glosow]) {
							vSecond = i;
						}
					}
				}
			}
		}
		
		if(vTop != -1) {
		
			forplayers(i) {
				if(G[i][VoteWybor] == -1) {
					nVoters ++;
				}
			}
			
			if(
		}
	}
	return 0;
}
//-----------------------------------------------------------------------------------------------------------
StartRandomSpectate(playerid) {
	if(IDStartowanej != -1 AND TrwaOdliczanie == false) {
		new specPlayers[MAX_GRACZY] = {-1, -1, ...}, fouded;
		for(new i, mainTeam = GetMainTeam(playerid), bool:isAdmin = (IsAdmin(playerid) != 0 ? true : false); i < MAX_GRACZY; i ++) {
			if(IsPlayerConnected(i)) {
				if(i != playerid) {
					if(mainTeam == GetMainTeam(i) OR isAdmin == true) {
						if(GetPlayerStan(i) == S_GRA) {
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
   	if(GetPlayerStan(playerid) == S_SPAWN OR GetPlayerStan(playerid) == S_SPECUJE) {
		if(GetPlayerStan(specid) == S_GRA) {
			if(IDStartowanej != -1 AND TrwaOdliczanie == false) {
	    		if(playerid != specid) {
		        	if(GetMainTeam(playerid) == GetMainTeam(specid) OR GetMainTeam(playerid) == T_REF OR IsAdmin(playerid) != 0) {
	            	    new str[32];
			            SetPlayerVirtualWorld(playerid, VW_GRA);
			            TogglePlayerSpectating(playerid, 1);
			            SetPlayerInterior(playerid,GetPlayerInterior(specid));
			            G[playerid][SpecowanyID] = specid;
			        	SetPlayerStan(playerid, S_SPECUJE);
						
						if(IsPlayerInAnyVehicle(specid))	PlayerSpectateVehicle(playerid, GetPlayerVehicleID(specid));
						else								PlayerSpectatePlayer(playerid, specid);
						
						format(str, sizeof(str),"~<~ %s ~>~",GetPlayerNick(specid));
						TextDrawSetString(G[playerid][TDSpecNick],str);
						if(GetMainTeam(specid) == T_ATT) {
						    TextDrawHideForPlayer(playerid, GetPVarInt(playerid, PV_BOX) == 0 ? TDSpecStatyBox[1] : TDSpecStatyBoxAlternatywny[1]);
                            TextDrawShowForPlayer(playerid, GetPVarInt(playerid, PV_BOX) == 0 ? TDSpecStatyBox[0] : TDSpecStatyBoxAlternatywny[0]);
                            TextDrawColor(G[playerid][TDSpecNick], 0xffff00cc);
						} else {
						    TextDrawHideForPlayer(playerid, GetPVarInt(playerid, PV_BOX) == 0 ? TDSpecStatyBox[0] : TDSpecStatyBoxAlternatywny[0]);
                            TextDrawShowForPlayer(playerid, GetPVarInt(playerid, PV_BOX) == 0 ? TDSpecStatyBox[1] : TDSpecStatyBoxAlternatywny[1]);
                            TextDrawColor(G[playerid][TDSpecNick], 0x0000ffcc);
						}
					    TextDrawHideForPlayer(playerid, G[playerid][TDZdrowie]);
						TextDrawShowForPlayer(playerid, TDSpecBox);
						TextDrawShowForPlayer(playerid, TDSpecNapis);
						TextDrawShowForPlayer(playerid, G[playerid][TDSpecNick]);
						TextDrawShowForPlayer(playerid, G[playerid][TDSpecStaty]);
			        	return 1;
		        	}
	        	}
	        }
		}
    }
	return 0;
}