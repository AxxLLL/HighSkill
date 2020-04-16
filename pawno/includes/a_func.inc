/*
	Usefull functions 
	Data: 30/06/2013
	
	Functions:
		native MACRO:isnull(string[]);
		native CheckString(string[]);
		native isNumeric(string[]);
		native GetOddValueByIndex(index);
		native DeleteNewLine(string[]);
		native DeleteSpecialChars(string[]);
		native DeleteSpaces(word[]);
		native DeleteFirstSpaces(word[]);
		native DeleteDoubleSpaces(message[]);
		native UpperWord(word[]);
		native LowerWord(word[]);
		native CreateFile(patch[]);
		native CheckFolderPatch(patch[]);
		native IsValidNick(nick[]);
		native Float:CircleVariation(Float:from, max);
		native ClearDeathList();
		native ClearPlayerChat(playerid);
		native ClearAllPlayersChat();			
		native GetChatLoggingStatus();
		native SetChatLoggingStatus(bool:status);
		native GetRemoteConsoleStatus();
		native SetRemoteConsoleStatus(bool:status);	
		native SetServerPassword(password[]);
		native GetServerPassword();
		native RemoveServerPassword();
		native KickEx(playerid);
		native IsValidIP(ip[]);
		native IsValidHost(host[]);
		native GetHostFromIP(ip[]);
		native DeleteSQLInjectionChars(string[]);
		native Hash(string[]);
		native randomly(min = cellmin, max = cellmax);
		native IsSimilarNick(nick[], ignore_playerid = -1);
		native ConvertNick(nick[]);
		native DeconvertNick(nick[]);
		native strtok(const string[], &index, seperator=' ');
		native Float:angleToPoint(Float:fromx, Float:fromy, Float:tox, Float:toy);
		native SearchDataSplit(data[], &type, &date_from, &date_to, &bool:search_front, &bool:search_end, &errorid = 0);
*/
//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
#if defined _a_func_included
  #endinput
#endif

#define _a_func_included
#pragma library a_func
//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
native gpci(playerid, const s_gpci[], len);
forward OnFunctionGetError(funcname[], errormsg[]);
//------------------------------------------------------------------------------
#define AND &&
#define OR 	||
#define and AND
#define or OR

#define _TRUE	1
#define _FALSE	0
//----------------------------------------------------
#if !defined isnull
	#define isnull(%1) ((!(%1[0])) || (((%1[0]) == '\1') && (!(%1[1]))))
#endif
//----------------------------------------------------
enum E_STATUS {_OFF, _ON}
//----------------------------------------------------
#define _LETTERS 1
#define _NUMBERS 2
#define _SPACES	 4
#define _SYMBOLS 8
stock CheckString(string[]) {
	if(!isnull(string)) {
		new bool:letters, bool:numbers, bool:symbols, bool:spaces;
		for(new i = strlen(string) - 1; i >= 0; i --) {
			if(letters == true AND numbers == true AND symbols == true AND spaces == true) break;
			if(letters == false AND ('A' <= string[i] <= 'Z' OR 'a' <= string[i] <= 'z')) letters = true;
			else if(numbers == false AND '0' <= string[i] <= '9') numbers = true;
			else if(spaces == false AND (string[i] == ' ' or string[i] == '_')) spaces = true;
			else if(symbols == false AND ('!' <= string[i] <= '/' OR ':' <= string[i] <= '@' OR '[' <= string[i] <= '^')) symbols = true;
		}
		return ((letters == true ? _LETTERS : 0) + (numbers == true ? _NUMBERS : 0) + (symbols == true ? _SYMBOLS : 0) + (spaces == true ? _SPACES : 0));		
	}
	return -1;
}
//----------------------------------------------------
stock isNumeric(string[]) {
	if(!isnull(string)) {
		for(new i, len = strlen(string); i < len; i ++) {
			if(!('0' <= string[i] <= '9')) {
				if(string[i] == '-' and i == 0) continue;
				return 0;
			}
		}
		return 1;
	}
	return 0;
}
//----------------------------------------------------
stock GetOddValueByIndex(index) {
		return index >= 0 ? index * 2 + 1 : 0;
}
//----------------------------------------------------
stock DeleteNewLine(string[]) {
	new idx;
	if((idx = strfind(string, "\r")) != -1) string[idx] = EOS;
	if((idx = strfind(string, "\n")) != -1) string[idx] = EOS;
}
//----------------------------------------------------
stock DeleteSpecialChars(string[]) {
	if(!isnull(string)) {
		new index, index2, lenght, bool:color;
		while((index = strfind(string, "\r")) != -1) strdel(string, index, index + 1);
		while((index = strfind(string, "\n")) != -1) strdel(string, index, index + 1);
		while((index = strfind(string, "\t")) != -1) strdel(string, index, index + 1);
		while((index = strfind(string, "%")) != -1)  string[index] = '#';
		while((index = strfind(string, "'")) != -1)  string[index] = '#';
		//-----------------------------------------
		index2 = 0;
		lenght = strlen(string);
		while((index = strfind(string, "{", true, index2)) != -1) {
			if(lenght - 1 >= index + 7) {
				index2 = index + 1;
				if(string[index + 7] == '}') {
					color = true;
					for(new i = index + 1, limit = index + 7; i < limit; i ++) {
						if(!('0' <= string[i] <= '9' OR 'A' <= string[i] <= 'F')) {
							color = false;
							break;
						}
					}
					if(color == true) {
						strdel(string, index, index + 8);
						index2 --;
					}
				}
			} else break;
		}
		return _TRUE;
	}
	return _FALSE;
}
//----------------------------------------------------
stock DeleteSpaces(word[]) {
	if(!isnull(word)) {
		new index;
		while((index = strfind(word, " ")) != -1) {
			strdel(word, index, index + 1);
		}
	}	
}
//----------------------------------------------------
stock DeleteFirstSpaces(word[]) {
	if(!isnull(word)) {
		for(new i, len = strlen(word); i < len; ) {
			if(word[i] == ' ') {
				strdel(word, i, i + 1);
				len --;
				continue;
			} else break;
			i ++;
		}
	}	
}
//----------------------------------------------------
stock DeleteDoubleSpaces(message[]) {
	if(!isnull(message)) {
		for(new i, length = strlen(message), bool:founded = false; i < length; ) {
			if(founded == false) {
				if(message[i] == ' ') founded = true;
			} else {
				if(message[i] == ' ') {
					strdel(message, i, i + 1);
					-- length;
					continue;
				} else founded = false;
			}
			i ++;
		}
		return _TRUE;
	}
	return _FALSE;
}
//----------------------------------------------------
stock UpperWord(word[]) {
	if(!isnull(word)) {
		for(new i = strlen(word) - 1; i >= 0; i --) word[i] = toupper(word[i]);
	}
}
//----------------------------------------------------
stock LowerWord(word[]) {
	if(!isnull(word)) {
		for(new i = strlen(word) - 1; i >= 0; i --) word[i] = tolower(word[i]);
	}
}
//----------------------------------------------------
stock CreateFile(patch[]) {
	if(!isnull(patch)) {
		if(!fexist(patch)) {
			if(strfind(patch, "/") != -1) {
				new pos = -1;
				new length = strlen(patch);
				for(new i = length; i >= 0; i --) {
					if(patch[i] == '/') {
						pos = i;
						break;
					}
				}
				if(pos + 1 < length) {
					patch[pos] = EOS;
					if(fexist(patch)) {
						patch[pos] = '/';
						fclose(fopen(patch, io_write));
						return _TRUE;
					} else patch[pos] = '/';
				}
			} else {
				fclose(fopen(patch, io_write));
				return _TRUE;
			}
		}
	}
	return _FALSE;
}
//----------------------------------------------------
stock CheckFolderPatch(patch[]) {
	//printf("CheckFolderPatch: %s", patch);
	new lenght;
	if(!isnull(patch) and 0 < (lenght = strlen(patch)) < 64) {
		new index;
		if((index = strfind(patch, "/")) != -1) {
			if(index > 0) {
				new modify_patch[64];
				strins(modify_patch, patch, 0);
				for(lenght -= 1; lenght >= 0; lenght --) {
					if(modify_patch[lenght] == '/') {
						modify_patch[lenght] = EOS;
						break;
					}
				}
				if(fexist(modify_patch)) return _TRUE;			
			}
		} else return _TRUE;
	}
	return _FALSE;
}
//----------------------------------------------------
stock IsValidNick(nick[]) {
	if(!isnull(nick)) {
		if(!isNumeric(nick)) {
			new Len;
			if(3 <= (Len = strlen(nick)) <= MAX_PLAYER_NAME) {
				for(new i; i < Len; i ++) {
					switch(nick[i]) {
						case 'A'..'Z', 'a'..'z', '0'..'9', '(', ')', '[', ']', '.', '_', '$', '@', '=': continue;
						default: return _FALSE;
					}
				}
				return _TRUE;
			}
		}
	}
	return _FALSE;
}
//----------------------------------------------------
stock Float:CircleVariation(Float:from, max) {
	new Float:f_max = floatdiv(random(10000), 10000);
	f_max += float(random((max < 0 ? -max : max)));
	return (random(2) == 0 ? (from + f_max) : (from - f_max));
}
//----------------------------------------------------------------------------------------
stock ClearDeathList() {
	for(new i; i < 5; i ++) SendDeathMessage(201, 201, 0);
}
//----------------------------------------------------------------------------------------
stock ClearPlayerChat(playerid) {
	for(new i; i < 30; i ++) {
		SendClientMessage(playerid, -1, " ");
	}
	return 1;
}
//----------------------------------------------------------------------------------------
stock ClearAllPlayersChat() {
	for(new i; i < 30; i ++) {
		SendClientMessageToAll(-1, " ");
	}
	return 1;
}
//----------------------------------------------------------------------------------------
stock GetChatLoggingStatus() {
    return GetServerVarAsBool("chatlogging");
}
//----------------------------------------------------------------------------------------
stock SetChatLoggingStatus(bool:status) {
    if(status == false) SendRconCommand("chatlogging 0");
    else SendRconCommand("chatlogging 1");
    return 1;
}
//----------------------------------------------------------------------------------------
stock GetRemoteConsoleStatus() {
    return GetServerVarAsBool("rcon");
}
//----------------------------------------------------------------------------------------
stock SetRemoteConsoleStatus(bool:status) {
    if(status == false) SendRconCommand("rcon 0");
    else SendRconCommand("rcon 1");
    return 1;
}
//----------------------------------------------------------------------------------------
stock SetServerPassword(password[]) {
	if(!isnull(password) and 16 >= strlen(password) > 0) {
		new string[32];
		for(new i = strlen(password) - 1; i >= 0; i --) {
			if(!('0' <= password[i] <= '9' or 'A' <= password[i] <= 'Z' or 'a' <= password[i] <= 'z')) return 0;
		}
		format(string, sizeof(string), "password %s", password);
		SendRconCommand(string);
		return 1;
	}
	return 0;
}
//----------------------------------------------------------------------------------------
stock GetServerPassword() {
	new password[32];
	GetServerVarAsString("password", password, sizeof(password));
	return password;
}
//----------------------------------------------------------------------------------------
stock RemoveServerPassword() {
	SendRconCommand("password 0");
	return 1;
}
//----------------------------------------------------------------------------------------
stock KickEx(playerid, mstime = 300) {
	if(IsPlayerConnected(playerid)) {
		SetTimerEx("kickExTimer", mstime, 0, "d", playerid);
		return _TRUE;
	}
	return _FALSE;
}
forward kickExTimer(playerid);
public kickExTimer(playerid) {
	Kick(playerid);
}
//----------------------------------------------------------------------------------------
stock IsValidIP(ip[]) {
	new length;
	if(7 <= (length = strlen(ip)) < 16) {
		new dots[3], find;
		while((dots[find] = strfind(ip, ".", true, (find == 0 ? 0 : (dots[find - 1] + 1)))) != -1) {
			if(++ find == 3) {
				if(strfind(ip, ".", true, dots[find - 1] + 1) != -1) return _FALSE;
				break;
			}
		}
		if(find == 3) {
			if(dots[0] != 0 and dots[2] + 1 != length) {
				if((5 > (dots[1] - dots[0]) > 1) and (5 > (dots[2] - dots[1]) > 1)) {
					for(new i = length - 1; i >= 0; i --) {
						if(!('0' <= ip[i] <= '9' or ip[i] == '.')) return _FALSE;
					}				
				
					new s_val[4][4];
					strmid(s_val[0], ip, 0, dots[0]);
					strmid(s_val[1], ip, dots[0] + 1, dots[1]);
					strmid(s_val[2], ip, dots[1] + 1, dots[2]);
					strmid(s_val[3], ip, dots[2] + 1, length);
					
					if((255 >= strval(s_val[0]) > 0) and (255 >= strval(s_val[1]) >= 0) and (255 >= strval(s_val[2]) >= 0) and (255 >= strval(s_val[3]) >= 0)) {
						return _TRUE;
					}					
				}
			}
		}		
	}
	return _FALSE;
}
//----------------------------------------------------------------------------------------
stock IsValidHost(host[]) {
	new length;
	if(3 <= (length = strlen(host)) <= 7) {
		new dot;
		if((dot = strfind(host, ".")) != -1) {
			if((strfind(host, ".", true, dot + 1) == -1) and dot != 0 and dot + 1 != length) {
				for(new i = length - 1; i >= 0; i --) {
					if(!('0' <= host[i] <= '9' or host[i] == '.')) return _FALSE;
				}				
				
				new s_val[2][4];
				strmid(s_val[0], host, 0, dot);
				strmid(s_val[1], host, dot + 1, length);
				
				if((255 >= strval(s_val[0]) > 0) and (255 >= strval(s_val[1]) >= 0)) {
					return _TRUE;
				}					
				
			}
		}		
	}
	return _FALSE;
}
//----------------------------------------------------------------------------------------
stock GetHostFromIP(ip[]) {
	new host[8];
	if(IsValidIP(ip) == _TRUE) {
		strmid(host, ip, 0, strfind(ip, ".", true, strfind(ip, ".") + 1));
	}
	return host;
}
//----------------------------------------------------------------------------------------
stock IsValidGPCI(s_gpci[]) {
	new length;
	if(64 > (length = strlen(s_gpci)) > 32) {
		for(new i = length - 1; i >= 0; i --) {
			if(!('A' <= s_gpci[i] <= 'Z' or '0' <= s_gpci[i] <= '9')) return _FALSE;
		}
		return _TRUE;
	}
	return _FALSE;
}
//----------------------------------------------------------------------------------------
stock DeleteSQLInjectionChars(string[]) {
	if(!isnull(string)) {
		new index;
		while((index = strfind(string, "'")) != -1) strdel(string, index, index + 1);
		while((index = strfind(string, "%")) != -1) string[index] = '*';
		while((index = strfind(string, "\\")) != -1) strdel(string, index, index + 1);
		while((index = strfind(string, "--")) != -1) strdel(string, index, index + 2);
		return _TRUE;
	}
	return _FALSE;
}
//----------------------------------------------------------------------------------------
stock Hash(string[]) {
	new hash_num;
	if(!isnull(string)) {
		new length;
		if((length = strlen(string)) > 0) {
			for(new i, middle_pos = string[floatround(floatdiv(length, 2), floatround_floor)]; i < length; i ++) {
				hash_num += (middle_pos * string[i]) * (length + i);
			}
		}
	}
	return hash_num;
}
//----------------------------------------------------------------------------------------
stock randomly(min = cellmin, max = cellmax) {
	if(min < max) {
		return min + random(max - min);
	}
	return _FALSE;
}
//----------------------------------------------------------------------------------------
stock IsSimilarNick(nick[], ignore_playerid = -1) {
	new similar_nick[MAX_PLAYER_NAME];
	if(IsValidNick(nick)) {
		for(new i, p_name[MAX_PLAYER_NAME], x; i < MAX_PLAYERS; i ++) {
		    if(i != ignore_playerid AND IsPlayerConnected(i)) {
				GetPlayerName(i, p_name, sizeof(p_name));
				if((x = strlen(p_name)) == strlen(nick)) {
					if(strcmp(p_name, nick, true) == 0) {
						strins(similar_nick, p_name, 0);
						break;
					} else {
						for(-- x; x >= 0; x --) {
						    if(p_name[x] == 'l') p_name[x] = 'i';
						}
						if(strcmp(p_name, nick, true) == 0) {
							strins(similar_nick, p_name, 0);
							break;
						}
						
						GetPlayerName(i, p_name, sizeof(p_name));
						for(x = strlen(nick) - 1; x >= 0; x --) {
						    if(p_name[x] == '0') p_name[x] = 'o';
						}
						if(strcmp(p_name, nick, true) == 0) {
							strins(similar_nick, p_name, 0);
							break;
						}

						GetPlayerName(i, p_name, sizeof(p_name));
						for(-- x; x >= 0; x --) {
						    if(p_name[x] == 'l') p_name[x] = 'i';
						    else if(p_name[x] == '0') p_name[x] = 'o';
						}
						if(strcmp(p_name, nick, true) == 0) {
							strins(similar_nick, p_name, 0);
							break;
						}					
					}
				}
		    }
		}
	}
	return similar_nick;
}
//----------------------------------------------------------------------------------------
stock ConvertNick(nick[]) {
	if(IsValidNick(nick)) {
		for(new i = strlen(nick) - 1; i >= 0; i --) {
			if(nick[i] == '_') nick[i] = '#';
		}
		return _TRUE;
	}
	return _FALSE;
}
//----------------------------------------------------------------------------------------
stock DeconvertNick(nick[]) {
	if(24 >= strlen(nick) >= 3) {
		for(new i = strlen(nick) - 1; i >= 0; i --) {
			if(nick[i] == '#') nick[i] = '_';
		}
		if(IsValidNick(nick) == _TRUE) {
			return _TRUE;
		}
	}
	return _FALSE;
}
//----------------------------------------------------------------------------------------
stock CutName(nick[], maxlen = 10) {
	new cutNick[64];
	strins(cutNick, nick, 0);
	if(strlen(cutNick) > maxlen) {
		strins(cutNick, "...", maxlen - 1);
		cutNick[maxlen + 2] = EOS;
	}
	return cutNick;
}
//----------------------------------------------------------------------------------------
stock strtok(const string[], &index, seperator=' ') {
	new length = strlen(string), offset = index, result[128];
	while ((index < length) && (string[index] != seperator) && ((index - offset) < (sizeof(result) - 1))) {
		result[index - offset] = string[index];
		index++;
	}

	result[index - offset] = EOS;
	if ((index < length) && (string[index] == seperator)) index++;
	return result;
}
//----------------------------------------------------------------------------------------
forward Float:angleToPoint(Float:fromx, Float:fromy, Float:tox, Float:toy);
stock Float:angleToPoint(Float:fromx, Float:fromy, Float:tox, Float:toy) {
	new Float:angle;
	new Float:ba, Float:bb, Float:bc;
		
	if(tox == fromx) fromx += 1.0;
	if(toy == fromy) fromy += 1.0;
	
	//printf("Starting 'from' values: %.4f | %.4f\nStarting 'to' values: %.4f | %.4f", fromx, fromy, tox, toy);				
	ba = floatsqroot(floatadd(floatpower(floatsub(fromx, tox), 2), floatpower(floatsub(fromy, toy), 2)));  // Bok miedzy skinem, a punktem celem.
	bb = floatsqroot(floatpower(floatsub(tox, fromx), 2)); // Bok miedzy graczem a punktem X.
	bc = floatsqroot(floatpower(floatsub(toy, fromy), 2));  // Bok miedzy punktem celem, a punktem X.
    //printf("ba: %.4f | bb: %.4f | bc: %.4f", ba, bb, bc);

	if(fromx >= tox) {
	    if(fromy >= toy) {
	        angle = floatadd(asin(floatdiv(bc, ba)), 90.0);
	    } else angle = asin(floatdiv(bb, ba));
	} else {
	    if(fromy >= toy) {
	        angle = floatsub(asin(floatdiv(bb, ba)), 180.0);
	    } else {
	        angle = floatsub(asin(floatdiv(bc, ba)), 90.0);
	    }
	}
	//printf("Angle: %.4f", angle);
	return angle;
}
//===============================================================
#define DATA_TYPE_NON			0
#define	DATA_TYPE_NICK			1
#define	DATA_TYPE_ONLINE		2
#define DATA_TYPE_HOST			3
#define	DATA_TYPE_USERID		4
#define	DATA_TYPE_ADMINID		5
#define	DATA_TYPE_ADMIN_NICK	6
#define	DATA_TYPE_IP			7
#define DATA_TYPE_VIP			8
#define DATA_TYPE_VIPPOINTS		9
#define DATA_TYPE_VIPBONUS		10

#define	DATA_ERROR_HELP					-1
#define DATA_ERROR_INVALID_LENGTH		1
#define DATA_ERROR_INVALID_TYPE			2
#define	DATA_ERROR_INVALID_SPECIAL		3
#define	DATA_ERROR_DATE_FROM			4
#define	DATA_ERROR_DATE_TO				5
#define	DATA_ERROR_NO_TYPE				6
#define DATA_ERROR_NO_DATA				7
#define	DATA_ERROR_NO_MATCH_DATA_TYPE	8
#define	DATA_ERROR_INVALID_SORT_TYPE	9

stock SearchDataSplit(data[], &type, &date_from, &date_to, &bool:search_front, &bool:search_end, &bool:sorttype_desc, &errorid = 0) {	
	date_from = 0;
	date_to = timestamp();
	sorttype_desc = true;
	type = DATA_TYPE_NON;
		
	DeleteSpaces(data);
	if(100 >= strlen(data) > 2) {
		new string[128];
		new index_s, index_e;
		new index; 		

		//_________________
		if((index = strfind(data, ":")) != -1) {		
			if(index == 1) {
				switch(data[0]) {
					case 'N', 'n': type = DATA_TYPE_NICK;
					case 'O', 'o': type = DATA_TYPE_ONLINE;
					case 'H', 'h': type = DATA_TYPE_HOST;
					case 'V', 'v': type = DATA_TYPE_VIP;
					default: {
						errorid = DATA_ERROR_INVALID_TYPE;
						return _FALSE;
					}	
				}
			} else if(index == 2) {
				if(strcmp(data, "UI", true, 2) == 0) type = DATA_TYPE_USERID;
				else if(strcmp(data, "AI", true, 2) == 0) type = DATA_TYPE_ADMINID;
				else if(strcmp(data, "AN", true, 2) == 0) type = DATA_TYPE_ADMIN_NICK;
				else if(strcmp(data, "IP", true, 2) == 0) type = DATA_TYPE_IP;
				else if(strcmp(data, "VP", true, 2) == 0) type = DATA_TYPE_VIPPOINTS;
				else if(strcmp(data, "VB", true, 2) == 0) type = DATA_TYPE_VIPBONUS;
				else {
					errorid = DATA_ERROR_INVALID_TYPE;
					return _FALSE;
				}
			} else {
				errorid = DATA_ERROR_INVALID_TYPE;
				return _FALSE;			
			}
			strdel(data, 0, index + 1);
		}
		//_________________
		if(isnull(data)) {
			type = DATA_TYPE_NON;
			errorid = DATA_ERROR_INVALID_LENGTH;
			return _FALSE;
		}
		//_________________
		if((index_s = strfind(data, "<")) != -1) {
			if((index_e = strfind(data, ">", true, index_s)) != -1 and index_e - index_s > 3) {
				strmid(string, data, index_s + 1, index_e);
				strdel(data, index_s, index_e + 1);
				
				if((index_s = strfind(string, "(")) != -1 and (index_e = strfind(string, ")", false, index_s)) != -1 and index_e - index_s == 2) {
					if(string[index_s + 1] == 'D' or string[index_s + 1] == 'd') 		sorttype_desc = true;
					else if(string[index_s + 1] == 'U' or string[index_s + 1] == 'u') 	sorttype_desc = false;
					else {
						type = DATA_TYPE_NON;
						errorid = DATA_ERROR_INVALID_SORT_TYPE;
						return _FALSE;
					}
					strdel(string, index_s, index_e + 1);
				}
				if(!isnull(string)) {
					if(strcmp(string, "HELP", true) == 0 or strcmp(string, "POMOC", true) == 0 or strcmp(string, "INFO", true) == 0) {
						type = DATA_TYPE_NON;
						errorid = DATA_ERROR_HELP;
						return _FALSE;
					} else {
						new year, month, day;
						new hour, minute, second;
						gettime(hour, minute, second);
						if((index = strfind(string, "|")) != -1 and index != strlen(string) - 1) {
							if(index == 0) {
								if(DataSplit(string[1], year, month, day, "/") == 1) {
									date_to = timestamp(year, month, day, hour, minute, second);
									if(date_to > timestamp()) {
										date_to = timestamp();
										errorid = DATA_ERROR_DATE_TO;
										return _FALSE;
									}
								} else {
									type = DATA_TYPE_NON;
									errorid = DATA_ERROR_DATE_TO;
									return _FALSE;
								}						
							} else {
								if(DataSplit(string[index + 1], year, month, day, "/") == 1) {
									date_to = timestamp(year, month, day, hour, minute, second);
									string[index] = EOS;
									if(date_to > timestamp()) {
										date_to = timestamp();
										errorid = DATA_ERROR_DATE_TO;
										return _FALSE;
									}								
								} else {
									errorid = DATA_ERROR_DATE_TO;
									type = DATA_TYPE_NON;
									return _FALSE;
								}
								if(strlen(string) > 3) {
									if(DataSplit(string, year, month, day, "/") == 1) {
										date_from = timestamp(year, month, day, 0, 0, 0);
										if(date_from > timestamp()) {
											date_from = 0;
											type = DATA_TYPE_NON;
											errorid = DATA_ERROR_DATE_FROM;								
											return _FALSE;
										}									
									} else {
										errorid = DATA_ERROR_DATE_FROM;
										date_to = timestamp();
										type = DATA_TYPE_NON;
										return _FALSE;
									}				
									if(date_from >= date_to) {
										new h_date = date_to;
										date_to = date_from;
										date_from = h_date;
									}										
								} else {
									date_to = timestamp();
									errorid = DATA_ERROR_DATE_FROM;
									type = DATA_TYPE_NON;
									return _FALSE;
								}							
							}						
						} else {
							if(DataSplit(string, year, month, day, "/") == 1) {
								date_from = timestamp(year, month, day, 0, 0, 0);
								if(date_from > timestamp()) {
									date_from = 0;
									type = DATA_TYPE_NON;
									errorid = DATA_ERROR_DATE_FROM;								
									return _FALSE;
								}
							} else {
								type = DATA_TYPE_NON;
								errorid = DATA_ERROR_DATE_FROM;
								return _FALSE;
							}
						}
					}
				}
			} else {
				type = DATA_TYPE_NON;
				errorid = DATA_ERROR_INVALID_SPECIAL;
				return _FALSE;
			}
		}		
		//_________________
		if(type == DATA_TYPE_NON) {
			date_to = timestamp();
			date_from = 0;
			errorid = DATA_ERROR_NO_TYPE;
			return _FALSE;
		}
		
		
		if(isnull(data) or type == DATA_TYPE_NON) {
			type = DATA_TYPE_NON;
			date_to = timestamp();
			date_from = 0;			
			errorid = DATA_ERROR_INVALID_LENGTH;
			return _FALSE;
		}
		//_________________
		index_s = index_e = -1;		
		if(data[0] == '*') {
			index_s = 0;
			search_front = true;
			strdel(data, 0, 1);
		}
		if(data[strlen(data) - 1] == '*') {
			index_e = strlen(data) - 1;
			search_end = true;
			strdel(data, index_e, index_e + 1);
		}		
		if(index_e - index_s == 1) search_end = false;		
		//_________________
		if(isnull(data) and index_s == -1 and index_e == -1) {
			date_to = timestamp();
			date_from = 0;	
			type = DATA_TYPE_NON;
			errorid = DATA_ERROR_NO_DATA;			
			return _FALSE;
		}
		//_________________
		if(!isnull(data)) {
			new bool:match;
			switch(type) {

			
				case DATA_TYPE_NICK, DATA_TYPE_VIP: {
					if((IsValidNick(data) == _TRUE or search_end == true or search_front == true) and IsValidIP(data) == _FALSE and IsValidHost(data) == _FALSE) {
						match = true;
					}
				}			
				case DATA_TYPE_ONLINE: {
					if(strlen(data) <= 3 and isNumeric(data) and (MAX_PLAYERS >= strval(data) >= 0) and IsPlayerConnected(strval(data))) {
						match = true;
					}
				}	
				case DATA_TYPE_HOST: {
					if(IsValidHost(data) == _TRUE or search_end == true or search_front == true) {
						match = true;
					}
				}			
				case DATA_TYPE_USERID, DATA_TYPE_VIPPOINTS, DATA_TYPE_VIPBONUS: {
					if(strlen(data) <= 9 and isNumeric(data) and strval(data) > 0) {
						match = true;
					}
				}			
				case DATA_TYPE_ADMINID:	{
					if(strlen(data) <= 9 and isNumeric(data) and strval(data) > 0) {
						match = true;
					}
				}			
				case DATA_TYPE_ADMIN_NICK: {
					if((IsValidNick(data) == _TRUE or search_end == true or search_front == true) and IsValidIP(data) == _FALSE and IsValidHost(data) == _FALSE) {
						match = true;
					}			
				}			
				case DATA_TYPE_IP:{
					if(IsValidIP(data) == _TRUE or search_end == true or search_front == true) {
						match = true;
					}
				}				
				default: {
					date_to = timestamp();
					date_from = 0;	
					type = DATA_TYPE_NON;
					search_front = search_end = false;			
					errorid = DATA_ERROR_INVALID_TYPE;
					return _FALSE;						
				}
			}		
			if(match == false) {
				date_to = timestamp();
				date_from = 0;	
				type = DATA_TYPE_NON;
				search_front = search_end = false;			
				errorid = DATA_ERROR_NO_MATCH_DATA_TYPE;		
				return _FALSE;
			}	
		} 
		return _TRUE;
		//_________________
	} else errorid = DATA_ERROR_INVALID_LENGTH;
	return _FALSE;
}