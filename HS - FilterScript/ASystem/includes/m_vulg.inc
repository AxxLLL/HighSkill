/*
	--- System cenzury wulgaryzmow ---
	Autor: Rafał (AxL_) Żółtański
	Data ostatniej modyfikacji: 28 czerwca 2013 (23:30)

*/
//===========================================================
//-----------------------------------------------------------
//===========================================================
#define MAX_WARNINGS_TO_MUTE	5
#define	VULG_MUTE_TIME			3

#define MAX_VULGS			200
#define MAX_SIMILAR_VULGS	25

#define	REMOVE_WARNING_TIME	30

#define	ANTY_SPAM_TIME	3
#define	ANTY_FLOOD_TIME	10
//-----------------------------------------------------------
#define C_OFF			0
#define C_TERMINATE 	1
#define	C_CENSURE		2
//-----------------------------------------------------------
#if USE_MVECTOR == 0
	enum E_VULG {PACK_WORD[8], CHECK_WORD}
	new g_Vulgs[MAX_VULGS][E_VULG];
	new g_SimilarVulgs[MAX_SIMILAR_VULGS][8];
	new g_CountVulgs = 0;
	new g_CountSimilarVulgs = 0;
	
#else 
	new vector:v_Vulgs;
	new vector:v_SimilarVulgs;
	//------------------------------------
	forward remoteVulgList();
	public remoteVulgList() return v_Vulgs;
	forward remoteSimilarVulgList();
	public remoteSimilarVulgList() return v_SimilarVulgs;
#endif
//-----------------------------------------------------------
//new g_PlayerCensureStatus[MAX_PLAYERS];						// Status cenzury gracza.
new g_PlayerCensureMute[MAX_PLAYERS];							// Czas uciszenia gracza.
new g_PlayerCensureWarnings[MAX_PLAYERS];						// Liczba ostrzezen za przeklinanie.
new g_PlayerRemoveWarningTimer[MAX_PLAYERS];					// Timer usuwajacy ostrzezenia gracza.
new g_CensureRemoveWarningTime = REMOVE_WARNING_TIME;			// Czas automatycznego znoszenia ostrzezen za przeklenstwa (w sekundach).
//-----------------------------------------------------------
new g_PlayerAntySpamTime[MAX_PLAYERS];							// Tablica przechowujaca czas (timestamp) ostatniej wyslanej wiadomosci gracza.
new g_PlayerAntyFloodTime[MAX_PLAYERS];							// Tablica przechowujaca czas (timestamp) ostatniej wyslanej wiadomosci gracza.
new g_PlayerAntyFloodMessage[MAX_PLAYERS][34];					// Tablica przechowujaca ostatnia wiadomosc gracza (spakowana).
//-----------------------------------------------------------
forward OnPlayerGetMute(playerid, time, admin_name[], reason[]);
forward OnPlayerGetUnmute(playerid, admin_name[]);
//===========================================================
//-----------------------------------------------------------
//===========================================================
stock unloadCurrentVulgList() {
	if(getVulgCount() > 0 or getSimilarVulgCount() > 0) {
		#if USE_MVECTOR == 0
		for(-- g_CountVulgs; g_CountVulgs >= 0; g_CountVulgs --) {
			strdel(g_Vulgs[g_CountVulgs][PACK_WORD], 0, 8);
			g_Vulgs[g_CountVulgs][CHECK_WORD] = _FALSE;
		}	
		g_CountVulgs = 0;
		#else
		Clear(v_Vulgs);
		#endif
		
		
		#if USE_MVECTOR == 0
		for(-- g_CountSimilarVulgs; g_CountSimilarVulgs >= 0; g_CountSimilarVulgs --) {
			strdel(g_SimilarVulgs[g_CountSimilarVulgs], 0, 8);
		}	
		g_CountSimilarVulgs = 0;
		#else
		Clear(v_SimilarVulgs);
		#endif
				
		return _TRUE;
	}		
	return _FALSE;
}
//-----------------------------------------------------------
stock loadVulgList(patch[] = VULG_LIST_FILE) {
	if(CheckFolderPatch(patch) == _TRUE and fexist(patch)) {
		new File:f_open = fopen(patch, io_read);
		new string[32], index, status, buffer[4];
		unloadCurrentVulgList();
		while(fread(f_open, string, sizeof(string))) {
			DeleteNewLine(string);
			if(!isnull(string) and strlen(string) > 2) {
				if(strcmp(string, "v=", false, 2) == 0) {
					status = _FALSE;
					if((index = strfind(string, "|")) != -1) {
						if(index == 3) {
							strmid(buffer, string, 2, 3);
							status = (strval(buffer) == 0 ? _FALSE : _TRUE);
						}
						index ++;
					} else index = 2;
					
					strdel(string, 0, index);
					DeleteSpaces(string);
					
					if(!isnull(string) and (30 >= strlen(string) >= 3)) {	
						#if USE_MVECTOR == 0
						strpack(g_Vulgs[g_CountVulgs][PACK_WORD], string, 8);
						g_Vulgs[g_CountVulgs][CHECK_WORD] = status;
						++ g_CountVulgs;
						#else 
						#pragma unused status
						Push_BackString(v_Vulgs, true, string);
						#endif
						
					}						
					
				} else if(strcmp(string, "s=", false, 2) == 0) {
					strdel(string, 0, 2);
					DeleteSpaces(string);
					if(!isnull(string) and 30 >= strlen(string) >= 3) {
						#if USE_MVECTOR == 0
						strpack(g_SimilarVulgs[g_CountSimilarVulgs], string, 8);
						++ g_CountSimilarVulgs;
						#else
						Push_BackString(v_SimilarVulgs, true, string);
						#endif
						
					}						
				}
			}				
		}			
		fclose(f_open);		
		return _TRUE;
	} else {
		new string[128];
		format(string, sizeof(string), "Nieodnaleziono folderu lub pliku przeklenstw o sciezce '%s'.", patch);		
		OnFunctionGetError("loadVulgList", string);
	}
	return _FALSE;
}
//-----------------------------------------------------------
stock getVulgCount() {
	#if USE_MVECTOR == 0
		return g_CountVulgs;
	#else
		return Size(v_Vulgs);
	#endif
}
//-----------------------------------------------------------
stock getSimilarVulgCount() {
	#if USE_MVECTOR == 0
		return g_CountSimilarVulgs;
	#else
		return Size(v_SimilarVulgs);
	#endif	
}
//-----------------------------------------------------------
stock getVulgByIndex(index) {
	new word[32];
	if(getVulgCount() > 0 and getVulgCount() > index >= 0) {
		#if USE_MVECTOR == 0
		strunpack(word, g_Vulgs[index][PACK_WORD], 30);	
		#else
		AtString(v_Vulgs, index, false, word, sizeof(word));
		#endif
	}
	return word;
}
//-----------------------------------------------------------
stock checkMessageByVulg(message[], whatToDo, &wulg_index = -1) {
	new bool:founded;
	if(whatToDo != C_OFF) {	
		if(!isnull(message) and strlen(message) >= 3) {
			for(
				new i = getVulgCount() - 1, 
				index, index_sim, last_index = 0, vulgWord[32], similarWord[32],
				bool:non_vulg,
				x; 
					i >= 0; i --) {		
				#if USE_MVECTOR == 0	
				strunpack(vulgWord, g_Vulgs[i][PACK_WORD]);
				#else
				AtString(v_Vulgs, i, false, vulgWord, sizeof(vulgWord));
				#endif
				while((index = strfind(message, vulgWord, true, last_index)) != -1) {
					last_index = index + strlen(vulgWord);
					#if USE_MVECTOR == 0
					#pragma unused similarWord
					if(g_Vulgs[i][CHECK_WORD] == _FALSE) {
						if(whatToDo == C_TERMINATE) {
							wulg_index = i;
							return _TRUE;
						} else {
							founded = true;
							wulg_index = i;
							for(x = index; x < last_index; x ++) {
								message[x] = '*';
							}
						}
					} else {
						non_vulg = false;
						for(x = getSimilarVulgCount() - 1; x >= 0; x --) {
							if((index_sim = strfind(message, g_SimilarVulgs[x], true)) != -1) {
								if(index_sim <= index and last_index <= index_sim + strlen(g_SimilarVulgs[x])) {
									non_vulg = true;
									break;
								}
							}
						}
						if(non_vulg == false) {
							if(whatToDo == C_TERMINATE) {
								wulg_index = i;
								return _TRUE;
							}
							else {
								founded = true;
								wulg_index = i;
								for(x = index; x < last_index; x ++) {
									message[x] = '*';
								}
							}						
						}					
					}					
					#else
					if((x = getSimilarVulgCount() - 1) >= 0) {
						for(;x >= 0; x --) {
							AtString(v_SimilarVulgs, x, false, similarWord, sizeof(similarWord));
							if((index_sim = strfind(message, similarWord, true)) != -1) {
								if(index_sim <= index and last_index <= index_sim + strlen(similarWord)) {
									non_vulg = true;
									break;
								}
							}
						}
					}					
					if(non_vulg == false) {
						if(whatToDo == C_TERMINATE) {
							wulg_index = i;
							return _TRUE;					
						} else {
							founded = true;
							wulg_index = i;
							for(x = index; x < last_index; x ++) {
								message[x] = '*';
							}					
						}
					}
					#endif
				
				}
			}
		}	
	}
	return founded == true ? _TRUE : _FALSE;
}
//-----------------------------------------------------------
stock getMaxCensureWarnings(bool:real = false) {
	return getSettingIntValueByIndex(s_CensureMuteStatusID) == _TRUE or real == true ? getSettingIntValueByIndex(s_CensureMaxWarningsID) : 9999999;
}
//-----------------------------------------------------------
stock setCensureRemoveWarningTime(seconds_time = REMOVE_WARNING_TIME) {
	if(seconds_time > 0) {
		g_CensureRemoveWarningTime = seconds_time;
		return _TRUE;
	}
	return _FALSE;
}
//-----------------------------------------------------------
stock getCensureRemoveWarningTime(bool:in_msseconds = true) {
	return in_msseconds == false ? g_CensureRemoveWarningTime : g_CensureRemoveWarningTime * 1000;
}
//===========================================================
stock setPlayerCensureStatus(playerid, bool:status) {
	if(IsPlayerConnected(playerid)) {
		SetPVarInt(playerid, PV_CENSURE_STATUS, _:status);
		return _TRUE;
	}
	return _FALSE;
}
//-----------------------------------------------------------
stock getPlayerCensureStatus(playerid) {
	return GetPVarInt(playerid, PV_CENSURE_STATUS);
}
//-----------------------------------------------------------
stock addPlayerCensureWarning(playerid) {
	if(IsPlayerConnected(playerid)) {
		KillTimer(g_PlayerRemoveWarningTimer[playerid]);
		if(++ g_PlayerCensureWarnings[playerid] > getMaxCensureWarnings()) {
			g_PlayerCensureWarnings[playerid] = 0;
			mutePlayer(playerid, getSettingIntValueByIndex(s_CensureMuteTimeID), "*System*", "Uzywanie wulgarnych slow");
		} else g_PlayerRemoveWarningTimer[playerid] = SetTimerEx("removePlayerCensureWarning", getCensureRemoveWarningTime(), 0, "d", playerid);
		return _TRUE;
	}
	return _FALSE;
}
//-----------------------------------------------------------
forward removePlayerCensureWarning(playerid);
public removePlayerCensureWarning(playerid) {
	KillTimer(g_PlayerRemoveWarningTimer[playerid]);
	if(IsPlayerConnected(playerid)) {
		if(g_PlayerCensureWarnings[playerid] > 0) {
			if(-- g_PlayerCensureWarnings[playerid] > 0) {
				g_PlayerRemoveWarningTimer[playerid] = SetTimerEx("removePlayerCensureWarning", getCensureRemoveWarningTime(), 0, "d", playerid);
			}
			return _TRUE;
		}
	}
	return _FALSE;
}
//-----------------------------------------------------------
stock getPlayerCensureWarnings(playerid) {
	if(IsPlayerConnected(playerid)) {
		return g_PlayerCensureWarnings[playerid];
	}
	return 0;
}
//-----------------------------------------------------------
stock setPlayerCensureWarnings(playerid, warnings) {
	if(warnings >= 0) {
		g_PlayerCensureWarnings[playerid] = warnings;
		if(warnings == 0) KillTimer(g_PlayerRemoveWarningTimer[playerid]);
		else g_PlayerRemoveWarningTimer[playerid] = SetTimerEx("removePlayerCensureWarning", getCensureRemoveWarningTime(), 0, "d", playerid);

		return _TRUE;
	}
	return _FALSE;
}
//-----------------------------------------------------------
stock mutePlayer(playerid, minute_time, admin_name[] = "*System*", reason[] = "Brak") {
	if(IsPlayerConnected(playerid) and minute_time > 0) {
		new s_reason[256];
		if(strlen(reason) == 0 or isnull(reason)) strins(s_reason, "Brak", 0);
		else strins(s_reason, reason, 0);
		g_PlayerCensureMute[playerid] = timestamp() + ToSeconds(minute_time, _MINUTE);
		CallLocalFunction("OnPlayerGetMute", "ddss", playerid, minute_time, admin_name, s_reason);
		format(s_reason, sizeof(s_reason), " (Mute) Gracz %s zostal uciszony przez administratora %s (Czas: %d min. | Powod: %s)", getPlayerName(playerid), admin_name, minute_time, reason);		
		AddToChatLog(s_reason);
		return _TRUE;
	}
	return _FALSE;
}
//-----------------------------------------------------------
stock unmutePlayer(playerid, admin_name[] = "*System*") {
	if(IsPlayerConnected(playerid) && g_PlayerCensureMute[playerid] > 0) {
		if(gettime() < g_PlayerCensureMute[playerid]) {
			new string[150];
			CallLocalFunction("OnPlayerGetUnmute", "ds", playerid, admin_name);
			format(string, sizeof(string)," (Mute) Uciszenie dla gracza %s zostalo wylaczone, lub czas uciszenia dobiegl konca (Administrator: %s)", getPlayerName(playerid), admin_name);
			AddToChatLog(string);
		}
		g_PlayerCensureMute[playerid] = 0;
		return _TRUE;
	}
	return _FALSE;
}
//-----------------------------------------------------------
stock getPlayerMuteTime(playerid, bool:real = true) {
	if(IsPlayerConnected(playerid)) {
		if(real == true) return g_PlayerCensureMute[playerid];
		else return g_PlayerCensureMute[playerid] < timestamp() ? 0 : g_PlayerCensureMute[playerid] - timestamp();
	}
	return _FALSE;
}
//-----------------------------------------------------------
stock isPlayerMuted(playerid) {
	if(IsPlayerConnected(playerid)) {
		if(timestamp() < getPlayerMuteTime(playerid)) {
			return _TRUE;
		}
	}
	return _FALSE;
}
//-----------------------------------------------------------
stock setPlayerAntySpamMessageTime(playerid) {
	g_PlayerAntySpamTime[playerid] = timestamp() + getSettingIntValueByIndex(s_AntySpamMinTimeID);
	return _TRUE;
}
//-----------------------------------------------------------
stock getPlayerAntySpamMessageTime(playerid) {
	return g_PlayerAntySpamTime[playerid];
}
//-----------------------------------------------------------
stock setPlayerAntyFloodMessageTime(playerid) {
	g_PlayerAntyFloodTime[playerid] = timestamp() + getSettingIntValueByIndex(s_AntyFloodMinTimeID);
	return _TRUE;
}
//-----------------------------------------------------------
stock getPlayerAntyFloodMessageTime(playerid) {
	return g_PlayerAntyFloodTime[playerid];
}

//===========================================================
stock checkPlayerBySpam(playerid) {
	if(getSettingIntValueByIndex(s_AntySpamStatusID) == _FALSE) return _FALSE;
	if(timestamp() - getPlayerAntySpamMessageTime(playerid) >= 0) {
		setPlayerAntySpamMessageTime(playerid);
		return _FALSE;
	}
	return _TRUE;
}
//-----------------------------------------------------------
stock checkPlayerByFlood(playerid, message[]) {
	if(getSettingIntValueByIndex(s_AntyFloodStatusID) == _TRUE and !isnull(message)) {
		if(timestamp() - getPlayerAntyFloodMessageTime(playerid) >= 0 or isnull(g_PlayerAntyFloodMessage[playerid])) {
			strpack(g_PlayerAntyFloodMessage[playerid], message, 34);
			setPlayerAntyFloodMessageTime(playerid);
		} else {
			if(strcmp(message, g_PlayerAntyFloodMessage[playerid], true) == 0) return _TRUE;
			else {
				strpack(g_PlayerAntyFloodMessage[playerid], message, 34);
				setPlayerAntyFloodMessageTime(playerid);
			}
		}
	}
	return _FALSE;
}

