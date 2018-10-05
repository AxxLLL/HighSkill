//===========================================================================================================
//-----------------------------------------------------------------------------------------------------------
//===========================================================================================================
forward ShowPlayerGamePanelMenu(playerid, listitem, gamemode);
public ShowPlayerGamePanelMenu(playerid, listitem, gamemode) {
	if(IsAdmin(playerid) >= ALVL_GAME_MASTER or IsPlayerAdmin(playerid)) {
	    SetPVarInt(playerid, PV_D_POMOCNICZA_2, gamemode);
	    switch(listitem) {
	        case 0: showPlayerGameSettingsMenu(playerid);
	        case 1: showPlayerGunSettingsMenu(playerid);
			case 2: showPlayerRespectSettingMenu(playerid);
	        case 3: showPlayerStartingAnnounceMenu(playerid);
			case 4: {
				saveGameModeSettings();
				saveWeaponsSettings();
				SendClientMessage(playerid, -1, " (Ustawienia) Zapisano ustawienia do pliku.");
				ShowPlayerGamePanelMenu(playerid, -1, gamemode);
			}
			default: ShowPlayerDialog(playerid, DIALOG_SETTING_MENU, DIALOG_STYLE_LIST, DIALOG_HEAD_COLOR "Ustawienia gamemoda", "\
					"D_CC"1) "DIALOG_TEXT_COLOR "Ustawienia gry\n\
					"D_CC"2) "DIALOG_TEXT_COLOR "Ustawienia broni\n\
					"D_CC"3) "DIALOG_TEXT_COLOR "Ustawienia respektu\n\
					"D_CC"4) "DIALOG_TEXT_COLOR "Ogloszenie startowe\n\
					"D_CC"5) "DIALOG_TEXT_COLOR "Zapisz wszystkie ustawienia do pliku\
				", "Dalej", gamemode == 1 ? ("Wyjdz") : ("Wroc"));
	    }
	}
	return 1;
}
//-----------------------------------------------------------------------------------------------------------
showPlayerGameSettingsMenu(playerid, listitem = -1) {
	if(IsAdmin(playerid) >= ALVL_GAME_MASTER or IsPlayerAdmin(playerid)) {	
		SetPVarInt(playerid, PV_D_POMOCNICZA, listitem);
		switch(listitem) {
			case 0..2, 4: showPlayerGameSettingValue(playerid);
			case 3: ShowPlayerDialog(playerid, DIALOG_GAMESETTING_GRENADE, DIALOG_STYLE_MSGBOX, DIALOG_HEAD_COLOR "Ustawienia gry - Dodatkowy granat", DIALOG_TEXT_COLOR " Ustawienie to decyduje, czy gracze maja otrzymywac granat na\narenach, ktorych ustawienia pozwalaja na uzycie tego typu broni.\n       Czy chcesz, zeby gracze otrzymywali dodatkowy granat?", "Tak", "Nie");
			default: {
				new string[320];
				format(string, sizeof(string), "\
						"D_CC"1) "DIALOG_TEXT_COLOR "Czas trwania baz\t\t\t[ "C_WHITE"%d "DIALOG_TEXT_COLOR "]\n\
						"D_CC"2) "DIALOG_TEXT_COLOR "Czas trwania aren\t\t\t[ "C_WHITE"%d "DIALOG_TEXT_COLOR "]\n\
						"D_CC"3) "DIALOG_TEXT_COLOR "Kamizelka podczas rund\t\t[ "C_WHITE"%d "DIALOG_TEXT_COLOR "]\n\
						"D_CC"4) "DIALOG_TEXT_COLOR "Dodatkowy granat\t\t\t[ %s "DIALOG_TEXT_COLOR "]\n\
						"D_CC"5) "DIALOG_TEXT_COLOR "Runda VIP\t\t\t\t[ "C_WHITE"%d"DIALOG_TEXT_COLOR" ]",
					CZAS_BAZY,
					CZAS_ARENY, 
					MAX_ARMOUR,
					DodatkowyGranat == true ? (C_LIGHTGREEN"Tak") : (C_ADMIN"Nie"),
					sVIPMinRounds
				);
				ShowPlayerDialog(playerid, DIALOG_GAMESETTING_MENU, DIALOG_STYLE_LIST, DIALOG_HEAD_COLOR "Ustawienia gamemoda - Ustawienia gry", string, "Dalej", "Wroc");
			}
		}	
		return 1;
	}
	return 0;
}
//-----------------------------------------------------------------------------------------------------------
showPlayerGameSettingValue(playerid, newvalue[] = "") {
	if(IsAdmin(playerid) >= ALVL_GAME_MASTER or IsPlayerAdmin(playerid)) {	
		new head[64], string[340];
		if(!isnull(newvalue)) {
			new value;
			if(1 <= strlen(newvalue) <= 3 and isNumeric(newvalue) and (value = strval(newvalue)) >= 0) {
				switch(GetPVarInt(playerid, PV_D_POMOCNICZA)) {
					case 0: {
						if(5 <= value < 100) {
							CZAS_BAZY = value;
							showPlayerGameSettingsMenu(playerid);
							return 1;
						} else strins(string, "\t\t       Niepoprawna wartosc.", 0);
					}
					case 1: {
						if(5 <= value < 100) {
							CZAS_ARENY = value;
							showPlayerGameSettingsMenu(playerid);
							return 1;							
						} else strins(string, "\t\t       Niepoprawna wartosc.", 0);
					}					
					case 2: {
						if(value <= 100) {
							MAX_ARMOUR = value;
							showPlayerGameSettingsMenu(playerid);
							return 1;						
						} else strins(string, "\t\t        Niepoprawna wartosc.", 0);
					}
					case 4: {
						if(0 <= value <= 100) {
							sVIPMinRounds = value;
							showPlayerGameSettingsMenu(playerid);
							return 1;						
						} else strins(string, "\t\t\t    Niepoprawna wartosc.", 0);					
					}
					default: strins(string, "Nieobslugiwane ustawienie.", 0);
				}
			} else strins(string, "\t\t\t    Niepoprawna wartosc.", 0);
		}
		
		switch(GetPVarInt(playerid, PV_D_POMOCNICZA)) {
			case 0: strins(head, DIALOG_HEAD_COLOR "Ustawienia gry - Czas trwania baz", 0), format(string, sizeof(string), DIALOG_TEXT_COLOR "\t   Podaj nowy czas trwania baz (w minutach).\nCzas trwania musi zawierac sie w przedziale od 5 do 99 minut.\n\n"C_ADMIN"%s", string);
			case 1: strins(head, DIALOG_HEAD_COLOR "Ustawienia gry - Czas trwania aren", 0), format(string, sizeof(string), DIALOG_TEXT_COLOR "\t   Podaj nowy czas trwania aren (w minutach).\nCzas trwania musi zawierac sie w przedziale od 5 do 99 minut.\n\n"C_ADMIN"%s", string);
			case 2: strins(head, DIALOG_HEAD_COLOR "Ustawienia gry - Kamizelka podczas rund", 0), format(string, sizeof(string), DIALOG_TEXT_COLOR "Podaj wartosc armora jaka maja otrzymywac gracze po starcie rundy.\n     Wartosc musi zawierac sie w przedziale od 0 do 100 jednostek.\n\n"C_ADMIN"%s", string);
			case 4: strins(head, DIALOG_HEAD_COLOR "Ustawienia gry - Runda VIP", 0), format(string, sizeof(string), DIALOG_TEXT_COLOR "          W tym menu mozesz ustalic co ile rozegranych rund, gracz z\n      aktywnym kontem VIP moze wystartowac swoja runde. Ustawienie\nwartosci '0' spowoduje brak mozliwosci wystartowania rundy przez VIP'a.\n             Wartosc musi zawierac sie w przedziale od 0 do 100 rund.\n\n"C_ADMIN"%s", string);
			default: showPlayerGameSettingsMenu(playerid);
		}
		
		ShowPlayerDialog(playerid, DIALOG_GAMESETTING_VALUE, DIALOG_STYLE_INPUT, head, string, "Ustaw", "Wroc");
		return 1;
	}
	return 0;
}
//-----------------------------------------------------------------------------------------------------------
showPlayerGunSettingsMenu(playerid, listitem = -1) {
	if(IsAdmin(playerid) >= ALVL_GAME_MASTER or IsPlayerAdmin(playerid)) {	
		if(listitem == -1) {
			new string[512];
			format(string, sizeof(string), "\
						"D_CC"1) "DIALOG_TEXT_COLOR "Pistolet z tlumikiem\t\t\t\t\t\t[ "C_WHITE"%d "DIALOG_TEXT_COLOR "]\n\
						"D_CC"2) "DIALOG_TEXT_COLOR "Desert Eagle\t\t\t\t\t\t\t[ "C_WHITE"%d "DIALOG_TEXT_COLOR "]\n\
						"D_CC"3) "DIALOG_TEXT_COLOR "Shotgun\t\t\t\t\t\t\t[ "C_WHITE"%d "DIALOG_TEXT_COLOR "]\n\
						"D_CC"4) "DIALOG_TEXT_COLOR "MP5\t\t\t\t\t\t\t\t[ "C_WHITE"%d "DIALOG_TEXT_COLOR "]\n\
					",
				Bron[0][GUN_AMMO],
				Bron[1][GUN_AMMO],
				Bron[2][GUN_AMMO],
				Bron[3][GUN_AMMO]				
			);	
			format(string, sizeof(string), "%s\
						"D_CC"5) "DIALOG_TEXT_COLOR "AK-47\t\t\t\t\t\t\t[ "C_WHITE"%d "DIALOG_TEXT_COLOR "]\n\
						"D_CC"6) "DIALOG_TEXT_COLOR "M4\t\t\t\t\t\t\t\t[ "C_WHITE"%d "DIALOG_TEXT_COLOR "]\n\
						"D_CC"7) "DIALOG_TEXT_COLOR "Strzelba\t\t\t\t\t\t\t[ "C_WHITE"%d "DIALOG_TEXT_COLOR "]\n\
						"D_CC"8) "DIALOG_TEXT_COLOR "Snajperka\t\t\t\t\t\t\t[ "C_WHITE"%d "DIALOG_TEXT_COLOR "]\
					",
				string,
				Bron[4][GUN_AMMO],
				Bron[5][GUN_AMMO],
				Bron[6][GUN_AMMO],
				Bron[7][GUN_AMMO]
			);
			ShowPlayerDialog(playerid, DIALOG_WEAPONSETTING_MENU, DIALOG_STYLE_LIST, DIALOG_HEAD_COLOR "Ustawienia gamemoda - Ustawienia broni", string, "Dalej", "Wroc");
		} else {
			SetPVarInt(playerid, PV_D_POMOCNICZA, listitem);
			showPlayerWaponSettingValue(playerid);
		}
		return 1;
	}
	return 0;
}
//-----------------------------------------------------------------------------------------------------------
showPlayerWaponSettingValue(playerid, newammo[] = "") {
	if(IsAdmin(playerid) >= ALVL_GAME_MASTER or IsPlayerAdmin(playerid)) {	
		new weaponlist;
		if(0 <= (weaponlist = GetPVarInt(playerid, PV_D_POMOCNICZA)) <= 7) {
			new head[64], string[180];
			if(!isnull(newammo)) {
				new value;
				if(1 <= strlen(newammo) <= 4 and isNumeric(newammo) and 9999 >= (value = strval(newammo)) >= 0) {
					Bron[weaponlist][GUN_AMMO] = value;
					showPlayerGunSettingsMenu(playerid);
					return 1;
				} else strins(string, "\t\t    Niepoprawna wartosc.", 0); 
			}
			strunpack(head, Bron[weaponlist][GUN_NAME], 64);			
			format(string, sizeof(string), DIALOG_TEXT_COLOR "Podaj nowa ilosc amunicji dla broni "C_WHITE"%s"DIALOG_TEXT_COLOR ".\nIlosc amunicji musi zawierac sie w przedziale od 0 do 9999.\n\n"C_ADMIN"%s", head, string);
			strins(head, DIALOG_HEAD_COLOR "Ustawienia broni - ", 0);
			ShowPlayerDialog(playerid, DIALOG_WEAPONSETTING_VALUE, DIALOG_STYLE_INPUT, head, string, "Ustaw", "Wroc");			
		} else showPlayerGunSettingsMenu(playerid);
		return 1;
	}
	return 0;
}
//-----------------------------------------------------------------------------------------------------------
showPlayerStartingAnnounceMenu(playerid, announce[] = "") {
	if(IsAdmin(playerid) >= ALVL_GAME_MASTER or IsPlayerAdmin(playerid)) {	
		new string[256];
		if(!isnull(announce)) {
			if(strlen(announce) == 1 and announce[0] == '-') {
				fclose(fopen(PLIK_OGLOSZENIA, io_write));				
				OgloszenieCzas = 0;
				TextDrawSetString(TDOgloszenieSerwerowe, " ");				
			} else {
				new bool:valid = true;
				for(new i = strlen(announce) - 1; i >= 0; i --) {
					if(!('a' <= announce[i] <= 'z' or 'A' <= announce[i] <= 'Z' or '0' <= announce[i] <= '9' or  announce[i] == '.' or announce[i] == ',' or announce[i] == ' ' or announce[i] == ':' or announce[i] == '=' or announce[i] == '\'' or announce[i] == '-' or announce[i] == '_' or announce[i] == '(' or announce[i] == ')' or announce[i] == '[' or announce[i] == ']' or announce[i] == '<' or announce[i] == '>' or announce[i] == '\"' or announce[i] == '!' or announce[i] == '?' or announce[i] == '@')) {
						valid = false;
						break;
					}
				}
				if(valid == true) {
					SetPVarString(playerid, PV_D_POMOCNICZA, announce);
					showPlayerStartingAnnounceTime(playerid);
					return 1;
				} else strins(string, "Niepoprawny symbol w tresci ogloszenia.", 0);
			}
		}
		format(string, sizeof(string), DIALOG_TEXT_COLOR "Podaj tresc ogloszenia startowego, widocznego podczas wybierania druzyny.\nOgloszenie moze skladac sie z liter, cyfr oraz symboli \""C_WHITE". , : = ' - _ ( ) [ ] < >"DIALOG_TEXT_COLOR "\".\nUzyj symbolu myslnika ("C_WHITE"-"DIALOG_TEXT_COLOR ") zeby usunac aktualne ogloszenie.\n"C_ADMIN"%s", string);
		ShowPlayerDialog(playerid, DIALOG_ANNOUNCE_MSG, DIALOG_STYLE_INPUT, DIALOG_HEAD_COLOR "Ustawienia gamemoda - Ogloszenie startowe (Tresc)", string, "Dalej", "Wroc");	
		return 1;
	}
	return 0;
}
//-----------------------------------------------------------------------------------------------------------
showPlayerStartingAnnounceTime(playerid, showtime[] = "") {
	if(IsAdmin(playerid) >= ALVL_GAME_MASTER or IsPlayerAdmin(playerid)) {	
		new string[200];
		if(!isnull(showtime)) {
			new time;
			if(isNumeric(showtime) and 1 <= (time = strval(showtime)) <= 365) {
				new File:f_open = fopen(PLIK_OGLOSZENIA, io_write);
				GetPVarString(playerid, PV_D_POMOCNICZA, string, 128);
				OgloszenieCzas = timestamp() + ToSeconds(time, _DAY);
				TextDrawSetString(TDOgloszenieSerwerowe, string);	
				ShowPlayerDialog(playerid, DIALOG_INFO_ANNOUNCE, DIALOG_STYLE_MSGBOX, DIALOG_HEAD_COLOR "Ustawienia gamemoda - Ogloszenie startowe", "Nowe ogloszenie zostalo ustawione.", "Wroc", "");				
				format(string, sizeof(string),"time=%d\r\nann=%s", OgloszenieCzas, string);
				fwrite(f_open, string);
				fclose(f_open);
				return 1;
			} else strins(string, "Niepoprawny czas trwania ogloszenia.", 0); 
		}
		format(string, sizeof(string), DIALOG_TEXT_COLOR"Podaj czas trwania ogloszenia.\nCzas trwania musi zawierac sie w przedziale od 1 do 365 dni.\n\n"C_ADMIN"%s", string);
		ShowPlayerDialog(playerid, DIALOG_ANNOUNCE_TIME, DIALOG_STYLE_INPUT, DIALOG_HEAD_COLOR "Ustawienia gamemoda - Ogloszenie startowe (Czas)", string, "Ustaw", "Wroc");		
		return 1;
	}	
	return 0;
}
//-----------------------------------------------------------------------------------------------------------
#define MAX_SPECIAL_RESPECT_REASONS 6
showPlayerRespectSettingMenu(playerid, listitem = -1) {
	if(IsAdmin(playerid) >= ALVL_GAME_MASTER or IsPlayerAdmin(playerid)) {	
		switch(listitem) {
			case 0: ShowPlayerWeaponRespectMenu(playerid);
			case 1..MAX_SPECIAL_RESPECT_REASONS: {
				SetPVarInt(playerid, PV_D_POMOCNICZA_3, listitem - 1);
				SpecialRespectSetMenu(playerid);
			}
			default: {
				new string[512];
				format(string, sizeof(string), 
						 D_CC"1) "DIALOG_TEXT_COLOR"Zabojstwa na bronie\n\
						"D_CC"2) "DIALOG_TEXT_COLOR"Heli-kill\t\t\t\t\t\t\t[ "C_WHITE"%d "DIALOG_TEXT_COLOR"]\n\
						"D_CC"3) "DIALOG_TEXT_COLOR"Car-kill\t\t\t\t\t\t\t[ "C_WHITE"%d "DIALOG_TEXT_COLOR"]\n\
						"D_CC"4) "DIALOG_TEXT_COLOR"Zabicie przez gracza\t\t\t\t\t\t[ "C_WHITE"%d "DIALOG_TEXT_COLOR"]\n\
						"D_CC"5) "DIALOG_TEXT_COLOR"Samobojstwo\t\t\t\t\t\t\t[ "C_WHITE"%d "DIALOG_TEXT_COLOR"]\n\
					",
					getWeaponKillRespect(50),
					getWeaponKillRespect(49),
					sRespectKilled,
					sRespectSuecided					
				);
				
				format(string, sizeof(string),"%s\
						"D_CC"6) "DIALOG_TEXT_COLOR"Ucieczka z serwera\t\t\t\t\t\t[ "C_WHITE"%d "DIALOG_TEXT_COLOR"]\n\
						"D_CC"7) "DIALOG_TEXT_COLOR"First Blood\t\t\t\t\t\t\t[ "C_WHITE"%d "DIALOG_TEXT_COLOR"]\n\
					", string,
					sLeftSrvInRound,
					sRespectFirstBlood
				);
				ShowPlayerDialog(playerid, DIALOG_SETTING_RESPECT, DIALOG_STYLE_LIST, DIALOG_HEAD_COLOR"Ustawienia gamemoda - Ustawienia respektu", string, "Dalej", "Wroc");
			}
		}
		return 1;
	}	
	return 0;
}
//-----------------------------------------------------------------------------------------------------------
#define MAX_RESPECT_WEAPONS	9
ShowPlayerWeaponRespectMenu(playerid, listitem = -1) {
	if(IsAdmin(playerid) >= ALVL_GAME_MASTER or IsPlayerAdmin(playerid)) {	
		switch(listitem) {
			case 0: RespectBaseSet(playerid);
			case 1..10: {
				SetPVarInt(playerid, PV_D_POMOCNICZA_3, listitem - 1);
				WeaponRespectTypeSet(playerid);		
			}
			default: {
				new string[700];
				format(string, sizeof(string), "\
							"D_CC"1) "DIALOG_TEXT_COLOR"Podstawa respektu\t\t\t\t\t\t[ "C_WHITE"%d"DIALOG_TEXT_COLOR" ]\n\
							"D_CC"2) "DIALOG_TEXT_COLOR"Pistolet z tlumikiem\t\t\t\t\t\t[ "C_WHITE"%d | %d"DIALOG_TEXT_COLOR" ]\n\
							"D_CC"3) "DIALOG_TEXT_COLOR"Desert Eagle\t\t\t\t\t\t\t[ "C_WHITE"%d | %d"DIALOG_TEXT_COLOR" ]\n\
							"D_CC"4) "DIALOG_TEXT_COLOR"Shotgun\t\t\t\t\t\t\t[ "C_WHITE"%d | %d"DIALOG_TEXT_COLOR" ]\n\
						",
					sRespectBase,
					getWeaponKillRespect(Bron[0][GUN_ID], false), getWeaponKillRespect(Bron[0][GUN_ID], true),
					getWeaponKillRespect(Bron[1][GUN_ID], false), getWeaponKillRespect(Bron[1][GUN_ID], true),
					getWeaponKillRespect(Bron[2][GUN_ID], false), getWeaponKillRespect(Bron[2][GUN_ID], true)												
				);	
				
				format(string, sizeof(string), "%s\
							"D_CC"5) "DIALOG_TEXT_COLOR"MP5\t\t\t\t\t\t\t\t[ "C_WHITE"%d | %d"DIALOG_TEXT_COLOR" ]\n\
							"D_CC"6) "DIALOG_TEXT_COLOR "AK-47\t\t\t\t\t\t\t[ "C_WHITE"%d | %d"DIALOG_TEXT_COLOR" ]\n\
							"D_CC"7) "DIALOG_TEXT_COLOR "M4\t\t\t\t\t\t\t\t[ "C_WHITE"%d | %d"DIALOG_TEXT_COLOR" ]\n\
							"D_CC"8) "DIALOG_TEXT_COLOR "Strzelba\t\t\t\t\t\t\t[ "C_WHITE"%d | %d"DIALOG_TEXT_COLOR" ]\n\
						",
					string,	
					getWeaponKillRespect(Bron[3][GUN_ID], false), getWeaponKillRespect(Bron[3][GUN_ID], true),
					getWeaponKillRespect(Bron[4][GUN_ID], false), getWeaponKillRespect(Bron[4][GUN_ID], true),
					getWeaponKillRespect(Bron[5][GUN_ID], false), getWeaponKillRespect(Bron[5][GUN_ID], true),
					getWeaponKillRespect(Bron[6][GUN_ID], false), getWeaponKillRespect(Bron[6][GUN_ID], true)
				);
				
				format(string, sizeof(string), "%s\
							"D_CC"9) "DIALOG_TEXT_COLOR "Snajperka\t\t\t\t\t\t\t[ "C_WHITE"%d | %d"DIALOG_TEXT_COLOR" ]\n\
							"D_CC"10) "DIALOG_TEXT_COLOR "Granat\t\t\t\t\t\t\t[ "C_WHITE"%d | %d"DIALOG_TEXT_COLOR" ]\n\
							"D_CC"11) "DIALOG_TEXT_COLOR "Kastet\t\t\t\t\t\t\t[ "C_WHITE"%d | %d"DIALOG_TEXT_COLOR" ]\
						",
					string,	
					getWeaponKillRespect(Bron[7][GUN_ID], false), getWeaponKillRespect(Bron[7][GUN_ID], true),
					getWeaponKillRespect(16, false), getWeaponKillRespect(16, true),
					getWeaponKillRespect(1, false), getWeaponKillRespect(1, true)
				);						
				
				ShowPlayerDialog(playerid, DIALOG_SRESPECT_WEAPONS, DIALOG_STYLE_LIST, DIALOG_HEAD_COLOR"Ustawienia respektu - Zabojstwa na bronie", string, "Zmien", "Wroc");			
			}
		}
		return 1;
	}
	return 0;
}
//-----------------------------------------------------------------------------------------------------------
WeaponRespectTypeSet(playerid, listitem = -1) {
	if(IsAdmin(playerid) >= ALVL_GAME_MASTER or IsPlayerAdmin(playerid)) {
		if(1 >= listitem >= 0) {
			SetPVarInt(playerid, PV_D_POMOCNICZA_4, listitem);
			WeaponRespectSet(playerid);
		} else {
			new string[128];
			new weaponid = GetPVarInt(playerid, PV_D_POMOCNICZA_3);
			if(sizeof(Bron) > weaponid >= 0) weaponid = Bron[weaponid][GUN_ID];
			else {
				switch(weaponid) {
					case 8: weaponid = 16;
					case 9: weaponid = 1;
					default: {
						return 1;
					}				
				}
			}	
			 
			format(string, sizeof(string), 
					D_CC"1) "DIALOG_TEXT_COLOR"Normalny\t\t\t\t\t\t\t[ "C_WHITE"%d"DIALOG_TEXT_COLOR" ]\n\
					"D_CC"2) "DIALOG_TEXT_COLOR"VIP\t\t\t\t\t\t\t\t[ "C_WHITE"%d"DIALOG_TEXT_COLOR" ]\
				",
				getWeaponKillRespect(weaponid, false),
				getWeaponKillRespect(weaponid, true)
			);
			ShowPlayerDialog(playerid, DIALOG_SRESPECT_TYPE_SET, DIALOG_STYLE_LIST, "Ustawienia respektu - Typ respektu", string, "Dalej", "Wroc");
		}
		return 1;
	}
	return 0;
}
//-----------------------------------------------------------------------------------------------------------
WeaponRespectSet(playerid, newvalue[] = "") {
	new weaponid;
	if((IsAdmin(playerid) >= ALVL_GAME_MASTER or IsPlayerAdmin(playerid)) and MAX_RESPECT_WEAPONS >= (weaponid = GetPVarInt(playerid, PV_D_POMOCNICZA_3)) >= 0) {	
		new string[256];
		
		if(sizeof(Bron) > weaponid >= 0) weaponid = Bron[weaponid][GUN_ID];
		else {
			switch(weaponid) {
				case 8: weaponid = 16;
				case 9: weaponid = 1;
				default: {
					return 1;
				}				
			}
		}		
		
		if(!isnull(newvalue)) {
			new value;
			if(isNumeric(newvalue) and 10 >= (value = strval(newvalue)) >= 0) {
				setWeaponKillRespect(weaponid, value, (GetPVarInt(playerid, PV_D_POMOCNICZA_4) == 0 ? false : true));
				WeaponRespectTypeSet(playerid);
				return 1;
			} else strins(string, "\tWartosc respektu musi zawierac sie w przedziale od 0 do 10.", 0);
		}
		format(string, sizeof(string), DIALOG_TEXT_COLOR"Podaj nowa wartosc respektu dla broni '"C_WHITE"%s"DIALOG_TEXT_COLOR"', z przedzialu od 0 do 10.\n\n"C_ADMIN"%s", getWeaponName(weaponid), string);
		ShowPlayerDialog(playerid, DIALOG_SRESPECT_WEAPONS_SET, DIALOG_STYLE_INPUT, DIALOG_HEAD_COLOR"Ustawienia respektu - Zabojstwa na bronie", string, "Zmien", "Wroc");
		
		return 1;
	}
	return 0;
}
#undef MAX_RESPECT_WEAPONS
//-----------------------------------------------------------------------------------------------------------
RespectBaseSet(playerid, newvalue[] = "") { 
	if(IsAdmin(playerid) >= ALVL_GAME_MASTER or IsPlayerAdmin(playerid)) {	
		new string[256];		
		if(!isnull(newvalue)) {
			new value;
			if(isNumeric(newvalue) and 5 >= (value = strval(newvalue)) >= 1) {
				sRespectBase = value;
				ShowPlayerWeaponRespectMenu(playerid);
				return 1;
			} else strins(string, "      Wartosc podstawy respektu musi zawierac sie w przedziale od 1 do 5.", 0);
		}
		format(string, sizeof(string), DIALOG_TEXT_COLOR"           Podaj nowa wartosc podstawy respektu, z przedzialu od 1 do 5.\nPodstawa respektu oznacza mnoznik, podstawowej wartosci respektu broni.\n"C_ADMIN"%s", string);
		ShowPlayerDialog(playerid, DIALOG_SRESPECT_BASE_SET, DIALOG_STYLE_INPUT, DIALOG_HEAD_COLOR"Ustawienia respektu - Podstawa respektu", string, "Zmien", "Wroc");
		return 1;
	}
	return 0;
}
//-----------------------------------------------------------------------------------------------------------
SpecialRespectSetMenu(playerid, newvalue[] = "") { 
	new reasonid;
	if((IsAdmin(playerid) >= ALVL_GAME_MASTER or IsPlayerAdmin(playerid)) and MAX_SPECIAL_RESPECT_REASONS > (reasonid = GetPVarInt(playerid, PV_D_POMOCNICZA_3)) >= 0) {	
		new string[256], reason[32], head[64];
		
		switch(reasonid) {
			case 0: strins(reason, "Heli-Kill", 0);
			case 1: strins(reason, "Car-Kill", 0);
			case 2: strins(reason, "Zabicie przez gracza", 0);
			case 3: strins(reason, "Samobojstwo", 0);
			case 4: strins(reason, "Ucieczka z serwera", 0);
			case 5: strins(reason, "First blood", 0);
			default: {
				return 1;
			}
		}
		
		if(!isnull(newvalue)) {
			new value;
			if(isNumeric(newvalue) and 9999 >= (value = strval(newvalue)) >= -9999) {
				switch(reasonid) {
					case 0: setWeaponKillRespect(50, value);
					case 1: setWeaponKillRespect(49, value);
					case 2: sRespectKilled = value;
					case 3: sRespectSuecided = value;
					case 4: sLeftSrvInRound = value;
					case 5: sRespectFirstBlood = value;
					default: return 1;
				}				
				showPlayerRespectSettingMenu(playerid);
				return 1;
			} else strins(string, "\tWartosc respektu musi zawierac sie w przedziale od -9999 do 9999.", 0);
		}
		format(string, sizeof(string), DIALOG_TEXT_COLOR"Podaj nowa wartosc respektu dla '"C_WHITE"%s"DIALOG_TEXT_COLOR"', z przedzialu od -9999 do 9999.\n\n"C_ADMIN"%s", reason, string);
		
		format(head, sizeof(head), DIALOG_HEAD_COLOR"Ustawienia respektu - %s", reason);
		ShowPlayerDialog(playerid, DIALOG_SRESPECT_SPECIAL_SET, DIALOG_STYLE_INPUT, head, string, "Zmien", "Wroc");
		
		return 1;
	}
	return 0;
}

//===========================================================================================================
//-----------------------------------------------------------------------------------------------------------
//===========================================================================================================
saveGameModeSettings(file[] = HS_SETTING_FILE) {
	if(CheckFolderPatch(file)) {
		new string[256];
		if(fexist(file)) {
			new File:f_read = fopen(file, io_read);
			new File:f_temp = fopen("hstempset.txt", io_write);
			
			while(fread(f_read, string, sizeof(string))) {
				DeleteNewLine(string);
				if(strlen(string)) {
					if(!(strcmp(string, "vip_round", true, 9) == 0 or strcmp(string, "t_arena", true, 7) == 0 or strcmp(string, "t_base", true, 6) == 0 or strcmp(string, "armour", true, 6) == 0 or strcmp(string, "grenade", true, 7) == 0 or strcmp(string, "sresp_", true, 6) == 0)) {
						format(string, sizeof(string), "%s\r\n", string);
						fwrite(f_temp, string);
					}
				}
			}
			
			fclose(f_read);
			fclose(f_temp);
			
			f_read = fopen("hstempset.txt", io_read);
			f_temp = fopen(file, io_write);	
			while(fread(f_read, string, sizeof(string))) fwrite(f_temp, string);	
			fclose(f_read);
			fclose(f_temp);	
			fremove("hstempset.txt");			
		}
		new File:f_open = fopen(file, io_append);
		format(string, sizeof(string), "\r\nt_arena=%d\r\nt_base=%d\r\narmour=%d\r\ngrenade=%d\r\nvip_round=%d", CZAS_ARENY, CZAS_BAZY, MAX_ARMOUR, DodatkowyGranat, sVIPMinRounds), fwrite(f_open, string);
		format(string, sizeof(string), "\r\nsresp_killed=%d\r\nsresp_suec=%d\r\nsresp_roundleft=%d\r\nsresp_fblood=%d\t\nsresp_base=%d", sRespectKilled, sRespectSuecided, sLeftSrvInRound, sRespectFirstBlood, sRespectBase), fwrite(f_open, string);		
		fclose(f_open);
		return 1;
	}
	return 0;
}
//-----------------------------------------------------------------------------------------------------------
saveWeaponsSettings(file[] = HS_WEAPONS_FILE) {
	if(CheckFolderPatch(file)) {	
		new string[128];
		if(fexist(file)) {
			new File:f_read = fopen(file, io_read);
			new File:f_temp = fopen("hstempset.txt", io_write);
			
			while(fread(f_read, string, sizeof(string))) {
				DeleteNewLine(string);
				if(strlen(string)) {
					if(strcmp(string, "weapon_", true, 7) != 0) {
						format(string, sizeof(string), "%s\r\n", string);
						fwrite(f_temp, string);
					}
				}
			}
			
			fclose(f_read);
			fclose(f_temp);
			
			f_read = fopen("hstempset.txt", io_read);
			f_temp = fopen(file, io_write);	
			while(fread(f_read, string, sizeof(string))) fwrite(f_temp, string);	
			fclose(f_read);
			fclose(f_temp);	
			fremove("hstempset.txt");			
		}
		new File:f_open = fopen(file, io_append);
		for(new i; i <= sizeof(g_Weapons); i ++) {
			format(string, sizeof(string), "\r\nweapon_%d=%d|%d|%d", i, getWeaponAmmo(i), getWeaponKillRespect(i, false), getWeaponKillRespect(i, true));
			fwrite(f_open, string);
		}	
		fclose(f_open);
		return 1;
	}
	return 0;
}
//-----------------------------------------------------------------------------------------------------------
loadWeaponsSettings(file[] = HS_WEAPONS_FILE) {
	if(CheckFolderPatch(file)) {
		if(fexist(file)) {
			new File:f_open = fopen(file, io_read);
			new index;
			new string[32], weaponid, ammo, normalRespect, vipRespect;
			while(fread(f_open, string, sizeof(string))) {
				weaponid = ammo = normalRespect = vipRespect = -1;
				DeleteNewLine(string);
				DeleteSpaces(string);
				if(strlen(string) > 9 and (index = strfind(string, "=")) >= 8 and index != strlen(string) - 1) {				
					if(5 < (weaponid = strfind(string, "_")) < index - 1) weaponid = strval(string[weaponid + 1]);				
					if(0 <= weaponid < sizeof(g_Weapons)) {
						sscanf(string[index + 1], "p<|>ddd", ammo, normalRespect, vipRespect);
						if(9999 >= ammo >= 0) g_Weapons[weaponid][WEAPON_AMMO] = ammo;
						if(10 >= normalRespect >= 0) g_Weapons[weaponid][WEAPON_RESPECT] = normalRespect;
						if(10 >= vipRespect >= 0) g_Weapons[weaponid][WEAPON_VIP_RESPECT] = vipRespect;
					}					
				}				
			}
			fclose(f_open);
		}
		return 1;
	}
	return 0;
}
//-----------------------------------------------------------------------------------------------------------
loadGameModeSettings(file[] = HS_SETTING_FILE) {
	if(CheckFolderPatch(file)) {
		if(fexist(file)) {
			new File:f_open = fopen(file, io_read);
			new string[32], value;
			while(fread(f_open, string, sizeof(string))) {
				DeleteNewLine(string);
				DeleteSpaces(string);
				if(strlen(string) > 7) {
					if(strcmp(string, "t_arena", true, 7) == 0) {
						if(5 <= (value = strval(string[8])) <= 99) CZAS_ARENY = value;
					} else if(strcmp(string, "t_base", true, 6) == 0) {
						if(5 <= (value = strval(string[7])) <= 99) CZAS_BAZY = value;
					} else if(strcmp(string, "armour", true, 6) == 0) {
						if(0 <= (value = strval(string[7])) <= 100) MAX_ARMOUR = value;
					} else if(strcmp(string, "grenade", true, 7) == 0) {
						if(0 <= (value = strval(string[8])) <= 1) DodatkowyGranat = value == 0 ? false : true;
					} else if(strcmp(string, "vip_round", true, 9) == 0) {
						if(0 <= (value = strval(string[10])) <= 100) sVIPMinRounds = value;
					} else if(strcmp(string, "sresp_killed", true, 12) == 0) {
						if(-9999 <= (value = strval(string[13])) <= 9999) sRespectKilled = value;
					} else if(strcmp(string, "sresp_suec", true, 10) == 0) {
						if(-9999 <= (value = strval(string[11])) <= 9999) sRespectSuecided = value;
					} else if(strcmp(string, "sresp_roundleft", true, 15) == 0) {
						if(-9999 <= (value = strval(string[16])) <= 9999) sLeftSrvInRound = value;
					} else if(strcmp(string, "sresp_fblood", true, 12) == 0) {
						if(-9999 <= (value = strval(string[13])) <= 9999) sRespectFirstBlood = value;
					} else if(strcmp(string, "sresp_base", true, 10) == 0) {
						if(1 <= (value = strval(string[11])) <= 5) sRespectBase = value;
					}

					
				}
			}
			fclose(f_open);
		}
		return 1;
	}
	return 0;
}
//-----------------------------------------------------------------------------------------------------------
loadAnnounceMessage(file[] = PLIK_OGLOSZENIA) {
	if(CheckFolderPatch(file)) {
		if(fexist(file)) {
			new File:f_open = fopen(file, io_read);
			new string[140], announce[130];
			new bool:valid, i;
			while(fread(f_open, string, 128)) {
				DeleteNewLine(string);
				if(strlen(string) >= 5) {
					if(strcmp(string, "time", true, 4) == 0 and strlen(string) <= 12) {
						if((OgloszenieCzas = strval(string[5])) <= 0) {
							OgloszenieCzas = 0;
						}
					}
					else if(strcmp(string, "ann", true, 3) == 0) {
						valid = true;
						for(i = strlen(string) - 1; i >= 4; i --) {
							if(!('a' <= string[i] <= 'z' or 'A' <= string[i] <= 'Z' or '0' <= string[i] <= '9' or string[i] == '.' or string[i] == ',' or string[i] == ' ' or string[i] == ':' or string[i] == '=' or string[i] == '\'' or string[i] == '-' or string[i] == '_' or string[i] == '(' or string[i] == ')' or string[i] == '[' or string[i] == ']' or string[i] == '<' or string[i] == '>' or string[i] == '\"' or string[i] == '!' or string[i] == '?' or string[i] == '@')) {
								valid = false;
								break;
							}
						}
						if(valid == true) {
							strdel(announce, 0, 130);
							strins(announce, string[4], 0);
						}						
					}
				}
			}			
			if(OgloszenieCzas > timestamp() and strlen(announce)) {
				TextDrawSetString(TDOgloszenieSerwerowe, announce);
			} 		
			fclose(f_open);
		}
		return 1;
	}
	return 0;
}
//-----------------------------------------------------------------------------------------------------------