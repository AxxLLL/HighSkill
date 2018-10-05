//===========================================================================================================
//-----------------------------------------------------------------------------------------------------------
//===========================================================================================================
new g_Inactive_ArenaID = -1;
new g_Inactive_Time = 0;
//===========================================================================================================
startInactiveStarter() {
	if(GlosowanieAktywne == false && IDStartowanej == -1 && g_Inactive_ArenaID == -1) {
		new string[64], attempts;
		while((++ attempts) != 5) {
			format(string, sizeof(string), "HighSkill/Areny/%d.txt", (g_Inactive_ArenaID = random(MAX_AREN)));
			if(fexist(string)) break;
		}
		
		if(attempts < 5) {
			g_Inactive_Time = 10;
			for(new i; i < MAX_PLAYERS; i ++) {
				if(IsPlayerConnected(i) && IsAdmin(i) > ALVL_NON) {
					g_Inactive_Time = 15;
					break;
				}
			}
			
			format(string, sizeof(string), " (Starter) Losowa arena wystartuje za %d sekund", g_Inactive_Time);
			SendClientMessageToAll(COLOR_START_INFO, string);	
			CallLocalFunction("OnInactiveStarterStatusChange", "d", 1);
			return 1;
		}
		g_Inactive_ArenaID = -1;		
	}
	return 0;
}
//-----------------------------------------------------------------------------------------------------------
stopInactiveStarter() {
	if(g_Inactive_ArenaID != -1) {
		g_Inactive_ArenaID = -1;
		g_Inactive_Time = 0;
		CallLocalFunction("OnInactiveStarterStatusChange", "d", 0);
		return 1;
	}
	return 0;
}
//===========================================================================================================
timer_InactiveStarter() {
	new playerCounter;
	for(new i; i < MAX_PLAYERS; i++) {
		if(IsPlayerConnected(i) && (getPlayerTeam(i) == T_ATT || getPlayerTeam(i) == T_DEF)) playerCounter ++;
	}	
	
	if(g_Inactive_Time > 0) {
		if(GlosowanieAktywne == true || IDStartowanej != -1 || getPlayersInTeam(T_ATT) == 0 || getPlayersInTeam(T_DEF) == 0 || playerCounter < 4) { 
			stopInactiveStarter();
		} else {
			if((-- g_Inactive_Time) == 0) {
				new string[64];
				TypArena = true;
				format(string, sizeof(string), "HighSkill/Areny/%d.txt", (IDStartowanej = g_Inactive_ArenaID));
				StartRundy(string);
				SendClientMessageToAll(COLOR_START_INFO, " (Starter) Losowa arena zostala rozpoczeta");			
				stopInactiveStarter();
			}
		} 
	} else {
		if(GlosowanieAktywne == false && IDStartowanej == -1 && (getPlayersInTeam(T_ATT) > 0 && getPlayersInTeam(T_DEF) > 0) && playerCounter >= 4 && !SwapOczekiwanie) {
			startInactiveStarter();
		}
	}
}