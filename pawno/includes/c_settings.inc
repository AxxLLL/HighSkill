/*
	//------------------------------------------------
	System ustawien
	Autor: Rafał (AxL_) Żółtański
	Wersja 1.0.0
	Data: 29 czerwca 2013
	//------------------------------------------------
	
	
	//------------------------------------------------
	native CheckFolderPatch(patch[]);
	
	native isValidSettingIntName(name[], &index = -1);
	native getIntSettingsAmount();
	native registerIntSetting(name[], patch[], value, min_value = cellmin + 1, max_value = cellmax - 1, call_func[] = "");
	native deleteIntSetting(name[]);
	native setSettingIntValue(name[], value);
	native getSettingIntValue(name[]);
	native getSettingIntMinValue(name[]);
	native getSettingIntMaxValue(name[]);
	native getSettingIntPatch(name[]);
	native getSettingIntIndex(name[]);
	native getSettingIntNameByIndex(index);
	native setSettingIntValueByIndex(index, value);
	native getSettingIntValueByIndex(index);
	native getSettingIntMinValueByIndex(index);
	native getSettingIntMaxValueByIndex(index);
	native getSettingIntPatchByIndex(index);
	
	native isValidSettingFloatName(name[], &index = -1)
	native getFloatSettingsAmount();
	native registerFloatSetting(name[], patch[], Float:value, Float:min_value = cellmin + 1, Float:max_value = cellmax - 1, call_func[] = "");
	native deleteFloatSetting(name[]);
	native setSettingFloatValue(name[], Float:value);
	native Float:getSettingFloatValue(name[]);
	native Float:getSettingFloatMinValue(name[]);
	native Float:getSettingFloatMaxValue(name[]);
	native getSettingFloatPatch(name[]);
	native getSettingFloatIndex(name[]);
	native getSettingFloatNameByIndex(index);
	native setSettingFloatValueByIndex(index, Float:value);
	native Float:getSettingFloatValueByIndex(index);
	native Float:getSettingFloatMinValueByIndex(index);
	native Float:getSettingFloatMaxValueByIndex(index);
	native getSettingFloatPatchByIndex(index);	
	
	native loadSettingsFromFile();
	native saveSettingsToFile();
	//------------------------------------------------
*/
//===========================================================
//-----------------------------------------------------------
//===========================================================
#if defined _c_settings_included
  #endinput
#endif

#define _c_settings_included
#pragma library c_settings
//===========================================================
//-----------------------------------------------------------
//===========================================================
#if !defined AND
	#define AND &&
#endif
#if !defined OR
	#define OR 	||
#endif
#if !defined and
	#define and AND
#endif
#if !defined or
	#define or OR
#endif
#if !defined _TRUE
	#define _TRUE 1
#endif
#if !defined _FALSE
	#define _FALSE 0
#endif
//----------------------------------------------------
#define isnull(%1) ((!(%1[0])) || (((%1[0]) == '\1') && (!(%1[1]))))
//----------------------------------------------------
#if !defined _a_func_included
stock CheckFolderPatch(patch[]) {
	new lenght;
	if(!isnull(patch) and 0 < (lenght = strlen(patch)) < 64) {
		new index;
		if((index = strfind(patch, "/")) != -1) {
			if(index + 1 < lenght and index > 0) {
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
#endif
//----------------------------------------------------
forward OnFunctionGetError(funcname[], errormsg[]);
//===========================================================
//-----------------------------------------------------------
//===========================================================
#define TMP_FILE	"setBuffer.txt"

#if !defined MAX_FLOAT_SETTINGS 
	#define MAX_FLOAT_SETTINGS	10
#elseif MAX_FLOAT_SETTINGS < 0
	#undef MAX_FLOAT_SETTINGS
	#define MAX_FLOAT_SETTINGS 0
#endif

#if !defined MAX_INT_SETTINGS
	#define MAX_INT_SETTINGS	10
#elseif MAX_INT_SETTINGS < 0
	#undef MAX_INT_SETTINGS
	#define MAX_INT_SETTINGS 0
#endif

//===========================================================
//-----------------------------------------------------------
//===========================================================
#if MAX_INT_SETTINGS > 0
enum E_SETTINGS_INT {SI_NAME[8], SI_PATCH[16], SI_VALUE, SI_MIN_VALUE, SI_MAX_VALUE, SI_FUNCTION[9]}
new g_IntSettings[MAX_INT_SETTINGS][E_SETTINGS_INT];
new g_CurrentIntSettings = 0;
//===========================================================
stock isValidSettingIntName(name[], &index = -1) {
	if(!isnull(name) and getIntSettingsAmount() > 0) {
		for(new i = getIntSettingsAmount() - 1; i >= 0; i --) {
			if(strcmp(name, g_IntSettings[i][SI_NAME]) == 0) {
				index = i;
				return _TRUE;
			}
		}		
	}
	return _FALSE;
}
//-----------------------------------------------------------
stock getIntSettingsAmount() return g_CurrentIntSettings;
//-----------------------------------------------------------
stock registerIntSetting(name[], patch[], value, min_value = cellmin + 1, max_value = cellmax - 1, call_func[] = "") {
	new string[128];
	if(getIntSettingsAmount() < MAX_INT_SETTINGS) {
		if(!isnull(name) and !isnull(patch)) {
			if(30 >= strlen(name) > 0 and 62 >= strlen(patch) > 0) {
				if(min_value < max_value and min_value <= value <= max_value) {
					new bool:founded;
					for(new i = getIntSettingsAmount() - 1; i >= 0; i --) {
						if(strcmp(name, g_IntSettings[i][SI_NAME]) == 0) {
							founded = true;
							break;
						}
					}
					if(founded == false) {
						new index = getIntSettingsAmount();
						strpack(g_IntSettings[index][SI_NAME], name, 8);
						strpack(g_IntSettings[index][SI_PATCH], patch, 16);
						g_IntSettings[index][SI_VALUE] = value;
						g_IntSettings[index][SI_MIN_VALUE] = min_value;
						g_IntSettings[index][SI_MAX_VALUE] = max_value;
						if(funcidx(call_func) != -1) {
							strpack(g_IntSettings[index][SI_FUNCTION], call_func, 8);							
						}						
						g_CurrentIntSettings ++;
						return index;
					} else {
						format(string, sizeof(string), "Wykryto probe zarejestrowania ustawien o istniejacej juz nazwie '%s'.", name);
					}
				} else {
					format(string, sizeof(string), "Niepoprawna wartosc startowa dla ustawien '%s'. Wartosc %d nie miesci sie w przedziale %d - %d.", name, value, min_value, max_value);
				}
			} else {
				if(30 >= strlen(name) > 0) 	format(string, sizeof(string), "Dlugosc nazwy ustawien musi miescic sie w przedziale od 0 do 30 znakow. Aktualna dlugosc to %d znaki (%s).", strlen(name), name);
				if(62 >= strlen(patch) > 0) format(string, sizeof(string), "Dlugosc sciezki pliku musi miescic sie w przedziale od 0 do 62 znakow. Aktualna dlugosc to %d znaki (%s).", strlen(patch), patch);
			}	
		} else {
			if(isnull(name)) format(string, sizeof(string), "Brak nazwy ustawien do zapisu.");
			if(isnull(patch)) format(string, sizeof(string), "Brak nazwy sciezki pliku do zapisu.");
		}
	} else {
		format(string, sizeof(string), "Limit ustawien zostal osiagniety. Proba dodania ustawienia '%s' nie powiodla sie (Limit: %d).", name, MAX_INT_SETTINGS);
	}
	CallLocalFunction("OnFunctionGetError", "ss", "registerIntSetting", string);  
	return -1;
}
//-----------------------------------------------------------
stock deleteIntSetting(name[]) {
	new string[128];
	if(!isnull(name) and 30 >= strlen(name) > 0 and getIntSettingsAmount() > 0) {
		new index = -1;
		for(new i = getIntSettingsAmount() - 1; i >= 0; i --) {
			if(strcmp(name, g_IntSettings[i][SI_NAME]) == 0) {
				strdel(g_IntSettings[i][SI_NAME], 0, 8);
				strdel(g_IntSettings[i][SI_PATCH], 0, 16);
				g_IntSettings[i][SI_VALUE] = 0;
				g_IntSettings[i][SI_MIN_VALUE] = g_IntSettings[i][SI_MAX_VALUE] = 0;
				index = i;			
				break;
			}
		}
		if(index != -1) {
			for(new i = index; i < g_CurrentIntSettings - 1; i ++) {
				strpack(g_IntSettings[i][SI_NAME], 		g_IntSettings[i + 1][SI_NAME], 8);
				strpack(g_IntSettings[i][SI_PATCH], 	g_IntSettings[i + 1][SI_PATCH], 16);
				g_IntSettings[i][SI_VALUE] =		 	g_IntSettings[i + 1][SI_VALUE];
				g_IntSettings[i][SI_MIN_VALUE] = 		g_IntSettings[i + 1][SI_MIN_VALUE];
				g_IntSettings[i][SI_MAX_VALUE] = 		g_IntSettings[i + 1][SI_MAX_VALUE];		
			}			
			g_CurrentIntSettings --;
			return _TRUE;
		} else format(string, sizeof(string), "Nieodnaleziono ustawienia o nazwie '%s'.", name);
	} else format(string, sizeof(string), "Niepoprawna nazwa ustawien ('%s') lub brak zapisanych ustawien (%d).", name, getIntSettingsAmount());
	CallLocalFunction("OnFunctionGetError", "ss", "deleteIntSetting", string);  
	return _FALSE;
}
//-----------------------------------------------------------
stock setSettingIntValue(name[], value) {
	if(!isnull(name) and 30 >= strlen(name) > 0 and getIntSettingsAmount() > 0) {
		for(new i = getIntSettingsAmount() - 1, call_func[36]; i >= 0; i --) {
			if(strcmp(name, g_IntSettings[i][SI_NAME]) == 0) {
				if(g_IntSettings[i][SI_MIN_VALUE] <= value <= g_IntSettings[i][SI_MAX_VALUE]) {
					g_IntSettings[i][SI_VALUE] = value;
					if(!isnull(g_IntSettings[i][SI_FUNCTION])) {
						strunpack(call_func, g_IntSettings[i][SI_FUNCTION], 32);
						CallLocalFunction(call_func, "d", value);
					}
					return _TRUE;
				}
				return _FALSE;
			}
		}
		new string[64];
		format(string, sizeof(string), "Niewykryto ustawienia o nazwie '%s'.", name);
		CallLocalFunction("OnFunctionGetError", "ss", "setSettingIntValue", string);  
	}
	return _FALSE;
}
//-----------------------------------------------------------
stock getSettingIntValue(name[]) {
	if(!isnull(name) and 30 >= strlen(name) > 0 and getIntSettingsAmount() > 0) {
		for(new i = getIntSettingsAmount() - 1; i >= 0; i --) {
			if(strcmp(name, g_IntSettings[i][SI_NAME]) == 0) {
				return g_IntSettings[i][SI_VALUE];
			}
		}
		new string[64];
		format(string, sizeof(string), "Niewykryto ustawienia o nazwie '%s'.", name);
		CallLocalFunction("OnFunctionGetError", "ss", "getSettingIntValue", string);  
	}
	return _FALSE;
}
//-----------------------------------------------------------
stock getSettingIntMinValue(name[]) {
	if(!isnull(name) and 30 >= strlen(name) > 0 and getIntSettingsAmount() > 0) {
		for(new i = getIntSettingsAmount() - 1; i >= 0; i --) {
			if(strcmp(name, g_IntSettings[i][SI_NAME]) == 0) {
				return g_IntSettings[i][SI_MIN_VALUE];
			}
		}
		new string[64];
		format(string, sizeof(string), "Niewykryto ustawienia o nazwie '%s'.", name);
		CallLocalFunction("OnFunctionGetError", "ss", "getSettingIntMinValue", string);  
	}
	return _FALSE;
}
//-----------------------------------------------------------
stock getSettingIntMaxValue(name[]) {
	if(!isnull(name) and 30 >= strlen(name) > 0 and getIntSettingsAmount() > 0) {
		for(new i = getIntSettingsAmount() - 1; i >= 0; i --) {
			if(strcmp(name, g_IntSettings[i][SI_NAME]) == 0) {
				return g_IntSettings[i][SI_MAX_VALUE];
			}
		}
		new string[64];
		format(string, sizeof(string), "Niewykryto ustawienia o nazwie '%s'.", name);
		CallLocalFunction("OnFunctionGetError", "ss", "getSettingIntMaxValue", string);   
	}
	return _FALSE;
}
//-----------------------------------------------------------
stock getSettingIntPatch(name[]) {
	new patch[64];
	if(!isnull(name) and 30 >= strlen(name) > 0 and getIntSettingsAmount() > 0) {
		new bool:founded;
		for(new i = getIntSettingsAmount() - 1; i >= 0; i --) {
			if(strcmp(name, g_IntSettings[i][SI_NAME]) == 0) {
				founded = true;
				strunpack(patch, g_IntSettings[index][SI_PATCH], 64);
				break;
			}
		}
		if(founded == false) {
			new string[64];
			format(string, sizeof(string), "Niewykryto ustawienia o nazwie '%s'.", name);
			CallLocalFunction("OnFunctionGetError", "ss", "getSettingIntPatch", string);  
		}
	}
	return patch;
}
//-----------------------------------------------------------
stock getSettingIntIndex(name[]) {
	if(!isnull(name) and 30 >= strlen(name) > 0 and getIntSettingsAmount() > 0) {
		for(new i = getIntSettingsAmount() - 1; i >= 0; i --) {
			if(strcmp(name, g_IntSettings[i][SI_NAME]) == 0) {
				return i;
			}
		}
		new string[64];
		format(string, sizeof(string), "Niewykryto ustawienia o nazwie '%s'.", name);
		CallLocalFunction("OnFunctionGetError", "ss", "getSettingIntIndex", string);    
	}	
	return -1;
}
//-----------------------------------------------------------
stock getSettingIntNameByIndex(index) {
	new setting_name[32];
	if(0 <= index < getIntSettingsAmount()) {
		strunpack(setting_name, g_IntSettings[index][SI_NAME], 32);
	} else {
		new string[64];
		format(string, sizeof(string), "Indeks wykracza poza zakres tabeli (0 <= %d < %d).", index, getIntSettingsAmount());
		CallLocalFunction("OnFunctionGetError", "ss", "getSettingIntNameByIndex", string);  
	}
	return setting_name;
}
//-----------------------------------------------------------
stock setSettingIntValueByIndex(index, value) {
	if(0 <= index < getIntSettingsAmount()) {
		if(g_IntSettings[index][SI_MIN_VALUE] <= value <= g_IntSettings[index][SI_MAX_VALUE]) {
			g_IntSettings[index][SI_VALUE] = value;
			if(!isnull(g_IntSettings[index][SI_FUNCTION])) {
				new call_func[36];
				strunpack(call_func, g_IntSettings[index][SI_FUNCTION], 32);
				CallLocalFunction(call_func, "d", value);
			}			
			return _TRUE;
		}
	} else {
		new string[64];
		format(string, sizeof(string), "Indeks wykracza poza zakres tabeli (0 <= %d < %d).", index, getIntSettingsAmount());
		CallLocalFunction("OnFunctionGetError", "ss", "setSettingIntValueByIndex", string); 
	}
	return _FALSE;
}
//-----------------------------------------------------------
stock getSettingIntValueByIndex(index) {
	if(0 <= index < getIntSettingsAmount()) {
		return g_IntSettings[index][SI_VALUE];
	} else {
		new string[64];
		format(string, sizeof(string), "Indeks wykracza poza zakres tabeli (0 <= %d < %d).", index, getIntSettingsAmount());
		CallLocalFunction("OnFunctionGetError", "ss", "getSettingIntValueByIndex", string); 
	}
	return _FALSE;
}
//-----------------------------------------------------------
stock getSettingIntMinValueByIndex(index) {
	if(0 <= index < getIntSettingsAmount()) {
		return g_IntSettings[index][SI_MIN_VALUE];
	} else {
		new string[64];
		format(string, sizeof(string), "Indeks wykracza poza zakres tabeli (0 <= %d < %d).", index, getIntSettingsAmount());
		CallLocalFunction("OnFunctionGetError", "ss", "getSettingIntMinValueByIndex", string); 
	}
	return _FALSE;
}
//-----------------------------------------------------------
stock getSettingIntMaxValueByIndex(index) {
	if(0 <= index < getIntSettingsAmount()) {
		return g_IntSettings[index][SI_MAX_VALUE];
	} else {
		new string[64];
		format(string, sizeof(string), "Indeks wykracza poza zakres tabeli (0 <= %d < %d).", index, getIntSettingsAmount());
		CallLocalFunction("OnFunctionGetError", "ss", "getSettingIntMaxValueByIndex", string); 
	}
	return _FALSE;
}
//-----------------------------------------------------------
stock getSettingIntPatchByIndex(index) {
	new patch[64];
	if(0 <= index < getIntSettingsAmount()) {
		strunpack(patch, g_IntSettings[index][SI_PATCH], 64);
	} else {
		new string[64];
		format(string, sizeof(string), "Indeks wykracza poza zakres tabeli (0 <= %d < %d).", index, getIntSettingsAmount());
		CallLocalFunction("OnFunctionGetError", "ss", "getSettingIntPatchByIndex", string); 
	}
	return patch;
}
#else
	stock getIntSettingsAmount() {
		return _FALSE;
	}
	stock registerIntSetting(name[], patch[], value, min_value = cellmin + 1, max_value = cellmax - 1) {
		#pragma unused name, patch, value, min_value, max_value
		new string[90];
		format(string, sizeof(string), "Niepoprawnie zdefiniowany rozmiar tablic skryptu (MAX_INT_SETTINGS: %d (<= 0))", MAX_INT_SETTINGS);
		CallLocalFunction("OnFunctionGetError", "ss", "registerIntSetting", string);  
		return _FALSE;
	}
	stock deleteIntSetting(name[]) {
		#pragma unused name
		new string[90];
		format(string, sizeof(string), "Niepoprawnie zdefiniowany rozmiar tablic skryptu (MAX_INT_SETTINGS: %d (<= 0))", MAX_INT_SETTINGS);
		CallLocalFunction("OnFunctionGetError", "ss", "deleteIntSetting", string);  
		return _FALSE;
	}
	stock setSettingIntValue(name[], value) {
		#pragma unused name, value
		new string[90];
		format(string, sizeof(string), "Niepoprawnie zdefiniowany rozmiar tablic skryptu (MAX_INT_SETTINGS: %d (<= 0))", MAX_INT_SETTINGS);
		CallLocalFunction("OnFunctionGetError", "ss", "setSettingIntValue", string);  
		return _FALSE;
	}
	stock getSettingIntValue(name[]) {
		#pragma unused name
		new string[90];
		format(string, sizeof(string), "Niepoprawnie zdefiniowany rozmiar tablic skryptu (MAX_INT_SETTINGS: %d (<= 0))", MAX_INT_SETTINGS);
		CallLocalFunction("OnFunctionGetError", "ss", "getSettingIntValue", string);   
		return _FALSE;
	}
	stock getSettingIntMinValue(name[]) {
		#pragma unused name
		new string[90];
		format(string, sizeof(string), "Niepoprawnie zdefiniowany rozmiar tablic skryptu (MAX_INT_SETTINGS: %d (<= 0))", MAX_INT_SETTINGS);
		CallLocalFunction("OnFunctionGetError", "ss", "getSettingIntMinValue", string);  
		return _FALSE;
	}
	stock getSettingIntMaxValue(name[]) {
		#pragma unused name
		new string[90];
		format(string, sizeof(string), "Niepoprawnie zdefiniowany rozmiar tablic skryptu (MAX_INT_SETTINGS: %d (<= 0))", MAX_INT_SETTINGS);
		CallLocalFunction("OnFunctionGetError", "ss", "getSettingIntMaxValue", string);  
		return _FALSE;
	}
	stock getSettingIntPatch(name[]) {
		#pragma unused name
		new string[90];
		format(string, sizeof(string), "Niepoprawnie zdefiniowany rozmiar tablic skryptu (MAX_INT_SETTINGS: %d (<= 0))", MAX_INT_SETTINGS);
		CallLocalFunction("OnFunctionGetError", "ss", "getSettingIntPatch", string);  
		return _FALSE;
	}
	stock getSettingIntIndex(name[]) {
		#pragma unused name
		new string[90];
		format(string, sizeof(string), "Niepoprawnie zdefiniowany rozmiar tablic skryptu (MAX_INT_SETTINGS: %d (<= 0))", MAX_INT_SETTINGS);
		CallLocalFunction("OnFunctionGetError", "ss", "getSettingIntIndex", string);  
		return _FALSE;
	}
	stock getSettingIntNameByIndex(index) {
		#pragma unused index
		new string[90];
		format(string, sizeof(string), "Niepoprawnie zdefiniowany rozmiar tablic skryptu (MAX_INT_SETTINGS: %d (<= 0))", MAX_INT_SETTINGS);
		CallLocalFunction("OnFunctionGetError", "ss", "getSettingIntNameByIndex", string);  
		return _FALSE;
	}	
	stock setSettingIntValueByIndex(index, value) {
		#pragma unused index, value
		new string[90];
		format(string, sizeof(string), "Niepoprawnie zdefiniowany rozmiar tablic skryptu (MAX_INT_SETTINGS: %d (<= 0))", MAX_INT_SETTINGS);
		CallLocalFunction("OnFunctionGetError", "ss", "setSettingIntValueByIndex", string);  
		return _FALSE;
	}	
	stock getSettingIntValueByIndex(index) {
		#pragma unused index
		new string[90];
		format(string, sizeof(string), "Niepoprawnie zdefiniowany rozmiar tablic skryptu (MAX_INT_SETTINGS: %d (<= 0))", MAX_INT_SETTINGS);
		CallLocalFunction("OnFunctionGetError", "ss", "getSettingIntValueByIndex", string);  
		return _FALSE;
	}	
	stock getSettingIntMinValueByIndex(index) {
		#pragma unused index
		new string[90];
		format(string, sizeof(string), "Niepoprawnie zdefiniowany rozmiar tablic skryptu (MAX_INT_SETTINGS: %d (<= 0))", MAX_INT_SETTINGS);
		CallLocalFunction("OnFunctionGetError", "ss", "getSettingIntMinValueByIndex", string);  
		return _FALSE;
	}	
	stock getSettingIntMaxValueByIndex(index) {
		#pragma unused index
		new string[90];
		format(string, sizeof(string), "Niepoprawnie zdefiniowany rozmiar tablic skryptu (MAX_INT_SETTINGS: %d (<= 0))", MAX_INT_SETTINGS);
		CallLocalFunction("OnFunctionGetError", "ss", "getSettingIntMaxValueByIndex", string);  
		return _FALSE;
	}	
	stock getSettingIntPatchByIndex(index) {
		#pragma unused index
		new string[90];
		format(string, sizeof(string), "Niepoprawnie zdefiniowany rozmiar tablic skryptu (MAX_INT_SETTINGS: %d (<= 0))", MAX_INT_SETTINGS);
		CallLocalFunction("OnFunctionGetError", "ss", "getSettingIntPatchByIndex", string);  
		return _FALSE;
	}	
#endif
//===========================================================
//-----------------------------------------------------------
//===========================================================
#if MAX_FLOAT_SETTINGS > 0
enum E_SETTINGS_FLOAT {SF_NAME[8], SF_PATCH[16], Float:SF_VALUE, Float:SF_MIN_VALUE, Float:SF_MAX_VALUE, SF_FUNCTION[9]}
new g_FloatSettings[MAX_FLOAT_SETTINGS][E_SETTINGS_FLOAT];
new g_CurrentFloatSettings = 0;
//===========================================================
stock isValidSettingFloatName(name[], &index = -1) {
	if(!isnull(name) and getFloatSettingsAmount() > 0) {
		for(new i = getFloatSettingsAmount() - 1; i >= 0; i --) {
			if(strcmp(name, g_FloatSettings[i][SF_NAME]) == 0) {
				index = i;
				return _TRUE;
			}
		}		
	}
	return _FALSE;
}
//-----------------------------------------------------------
stock getFloatSettingsAmount() return g_CurrentFloatSettings;
//-----------------------------------------------------------
stock registerFloatSetting(name[], patch[], Float:value, Float:min_value = -2147482647.0, Float:max_value = 2147482646.0, call_func[] = "") {
	new string[128];
	if(getFloatSettingsAmount() < MAX_FLOAT_SETTINGS) {
		if(!isnull(name) and !isnull(patch)) {
			if(30 >= strlen(name) > 0 and 62 >= strlen(patch) > 0) {
				if(min_value < max_value and min_value <= value <= max_value) {
					new bool:founded;
					for(new i = getFloatSettingsAmount() - 1; i >= 0; i --) {
						if(strcmp(name, g_FloatSettings[i][SF_NAME]) == 0) {
							founded = true;
							break;
						}
					}
					if(founded == false) {
						new index = getFloatSettingsAmount();
						strpack(g_FloatSettings[index][SF_NAME], name, 8);
						strpack(g_FloatSettings[index][SF_PATCH], patch, 16);
						g_FloatSettings[index][SF_VALUE] = value;
						g_FloatSettings[index][SF_MIN_VALUE] = min_value;
						g_FloatSettings[index][SF_MAX_VALUE] = max_value;						
						if(funcidx(call_func) != -1) {
							strpack(g_FloatSettings[index][SF_FUNCTION], call_func, 8);							
						}								
						g_CurrentFloatSettings ++;
						return index;
					} else format(string, sizeof(string), "Wykryto probe zarejestrowania ustawien o istniejacej juz nazwie '%s'.", name);
				} else format(string, sizeof(string), "Niepoprawna wartosc startowa dla ustawien '%s'. Wartosc %d nie miesci sie w przedziale %d - %d.", name, value, min_value, max_value);
			} else {
				if(30 >= strlen(name) > 0) 	format(string, sizeof(string), "Dlugosc nazwy ustawien musi miescic sie w przedziale od 0 do 30 znakow. Aktualna dlugosc to %d znaki (%s).", strlen(name), name);
				if(62 >= strlen(patch) > 0) format(string, sizeof(string), "Dlugosc sciezki pliku musi miescic sie w przedziale od 0 do 62 znakow. Aktualna dlugosc to %d znaki (%s).", strlen(patch), patch); 
			}	
		} else {
			if(isnull(name)) format(string, sizeof(string), "Brak nazwy ustawien do zapisu.");
			if(isnull(patch)) format(string, sizeof(string), "Brak nazwy sciezki pliku do zapisu.");
			
		}
	} else format(string, sizeof(string), "Limit ustawien zostal osiagniety. Proba dodania ustawienia '%s' nie powiodla sie (Limit: %d).", name, MAX_FLOAT_SETTINGS);
	CallLocalFunction("OnFunctionGetError", "ss", "registerFloatSetting", string);  
	return -1;
}
//-----------------------------------------------------------
stock deleteFloatSetting(name[]) {
	new string[128];
	if(!isnull(name) and 30 >= strlen(name) > 0 and getFloatSettingsAmount() > 0) {
		new index = -1;
		for(new i = getFloatSettingsAmount() - 1; i >= 0; i --) {
			if(strcmp(name, g_FloatSettings[i][SF_NAME]) == 0) {
				strdel(g_FloatSettings[i][SF_NAME], 0, 8);
				strdel(g_FloatSettings[i][SF_PATCH], 0, 16);
				g_FloatSettings[i][SF_VALUE] = 0;
				g_FloatSettings[i][SF_MIN_VALUE] = g_FloatSettings[i][SF_MAX_VALUE] = 0;
				index = i;			
				break;
			}
		}
		if(index != -1) {
			for(new i = index; i < g_CurrentFloatSettings - 1; i ++) {
				strpack(g_FloatSettings[i][SF_NAME], 	g_FloatSettings[i + 1][SF_NAME], 8);
				strpack(g_FloatSettings[i][SF_PATCH], 	g_FloatSettings[i + 1][SF_PATCH], 16);
				g_FloatSettings[i][SF_VALUE] =		 	g_FloatSettings[i + 1][SF_VALUE];
				g_FloatSettings[i][SF_MIN_VALUE] = 		g_FloatSettings[i + 1][SF_MIN_VALUE];
				g_FloatSettings[i][SF_MAX_VALUE] = 		g_FloatSettings[i + 1][SF_MAX_VALUE];		
			}			
			g_CurrentFloatSettings --;
			return _TRUE;
		} else format(string, sizeof(string), "Nieodnaleziono ustawienia o nazwie '%s'.", name);
	} else format(string, sizeof(string), "Niepoprawna nazwa ustawien ('%s') lub brak zapisanych ustawien (%d).", name, getFloatSettingsAmount());
	CallLocalFunction("OnFunctionGetError", "ss", "deleteFloatSetting", string);  
	return _FALSE;
}
//-----------------------------------------------------------
stock setSettingFloatValue(name[], Float:value) {
	if(!isnull(name) and 30 >= strlen(name) > 0 and getFloatSettingsAmount() > 0) {
		for(new i = getFloatSettingsAmount() - 1, call_func[36]; i >= 0; i --) {
			if(strcmp(name, g_FloatSettings[i][SF_NAME]) == 0) {
				if(g_FloatSettings[i][SF_MIN_VALUE] <= value <= g_FloatSettings[i][SF_MAX_VALUE]) {
					g_FloatSettings[i][SF_VALUE] = value;
					if(!isnull(g_FloatSettings[i][SF_FUNCTION])) {
						strunpack(call_func, g_FloatSettings[i][SF_FUNCTION], 32);
						CallLocalFunction(call_func, "d", value);
					}					
					return _TRUE;
				}
				return _FALSE;
			}
		}
		new string[64];
		format(string, sizeof(string), "Niewykryto ustawienia o nazwie '%s'.", name);
		CallLocalFunction("OnFunctionGetError", "ss", "setSettingFloatValue", string);  
	}
	return _FALSE;
}
//-----------------------------------------------------------
stock Float:getSettingFloatValue(name[]) {
	if(!isnull(name) and 30 >= strlen(name) > 0 and getFloatSettingsAmount() > 0) {
		for(new i = getFloatSettingsAmount() - 1; i >= 0; i --) {
			if(strcmp(name, g_FloatSettings[i][SF_NAME]) == 0) {
				return g_FloatSettings[i][SF_VALUE];
			}
		}
		new string[64];
		format(string, sizeof(string), "Niewykryto ustawienia o nazwie '%s'.", name);
		CallLocalFunction("OnFunctionGetError", "ss", "getSettingFloatValue", string);  
	}
	return 0.0;
}
//-----------------------------------------------------------
stock Float:getSettingFloatMinValue(name[]) {
	if(!isnull(name) and 30 >= strlen(name) > 0 and getFloatSettingsAmount() > 0) {
		for(new i = getFloatSettingsAmount() - 1; i >= 0; i --) {
			if(strcmp(name, g_FloatSettings[i][SF_NAME]) == 0) {
				return g_FloatSettings[i][SF_MIN_VALUE];
			}
		}
		new string[64];
		format(string, sizeof(string), "Niewykryto ustawienia o nazwie '%s'.", name);
		CallLocalFunction("OnFunctionGetError", "ss", "getSettingFloatMinValue", string);  
	}
	return 0.0;
}
//-----------------------------------------------------------
stock Float:getSettingFloatMaxValue(name[]) {
	if(!isnull(name) and 30 >= strlen(name) > 0 and getFloatSettingsAmount() > 0) {
		for(new i = getFloatSettingsAmount() - 1; i >= 0; i --) {
			if(strcmp(name, g_FloatSettings[i][SF_NAME]) == 0) {
				return g_FloatSettings[i][SF_MAX_VALUE];
			}
		}
		new string[64];
		format(string, sizeof(string), "Niewykryto ustawienia o nazwie '%s'.", name);
		CallLocalFunction("OnFunctionGetError", "ss", "getSettingFloatMaxValue", string);  
	}
	return 0.0;
}
//-----------------------------------------------------------
stock getSettingFloatPatch(name[]) {
	new patch[64];
	if(!isnull(name) and 30 >= strlen(name) > 0 and getFloatSettingsAmount() > 0) {
		new bool:founded;
		for(new i = getFloatSettingsAmount() - 1; i >= 0; i --) {
			if(strcmp(name, g_FloatSettings[i][SF_NAME]) == 0) {
				strunpack(patch, g_FloatSettings[index][SF_PATCH], 64);
				founded = true;
				break;
			}
		}
		if(founded == false) {
			new string[64];
			format(string, sizeof(string), "Niewykryto ustawienia o nazwie '%s'.", name);
			CallLocalFunction("OnFunctionGetError", "ss", "getSettingFloatPatch", string);  
		}
	}
	return patch;
}
//-----------------------------------------------------------
stock getSettingFloatIndex(name[]) {
	if(!isnull(name) and 30 >= strlen(name) > 0 and getFloatSettingsAmount() > 0) {
		for(new i = getFloatSettingsAmount() - 1; i >= 0; i --) {
			if(strcmp(name, g_FloatSettings[i][SF_NAME]) == 0) {
				return i;
			}
		}
		new string[64];
		format(string, sizeof(string), "Niewykryto ustawienia o nazwie '%s'.", name);
		CallLocalFunction("OnFunctionGetError", "ss", "getSettingFloatIndex", string);   
	}	
	return -1;
}
//-----------------------------------------------------------
stock getSettingFloatNameByIndex(index) {
	new setting_name[32];
	if(0 <= index < getFloatSettingsAmount()) {
		strunpack(setting_name, g_FloatSettings[index][SF_NAME], 32);
	} else {
		new string[64];
		format(string, sizeof(string), "Indeks wykracza poza zakres tabeli (0 <= %d < %d).", index, getFloatSettingsAmount());
		CallLocalFunction("OnFunctionGetError", "ss", "getSettingFloatNameByIndex", string);  
	}
	return setting_name;
}
//-----------------------------------------------------------
stock setSettingFloatValueByIndex(index, Float:value) {
	if(0 <= index < getFloatSettingsAmount()) {
		if(g_FloatSettings[index][SF_MIN_VALUE] <= value <= g_FloatSettings[index][SF_MAX_VALUE]) {
			g_FloatSettings[index][SF_VALUE] = value;
			if(!isnull(g_FloatSettings[index][SF_FUNCTION])) {
				new call_func[36];
				strunpack(call_func, g_FloatSettings[index][SF_FUNCTION], 32);
				CallLocalFunction(call_func, "d", value);
			}			
			return _TRUE;
		}
	} else {
		new string[64];
		format(string, sizeof(string), "Indeks wykracza poza zakres tabeli (0 <= %d < %d).", index, getFloatSettingsAmount());
		CallLocalFunction("OnFunctionGetError", "ss", "setSettingFloatValueByIndex", string);  
	}
	return _FALSE;
}
//-----------------------------------------------------------
stock Float:getSettingFloatValueByIndex(index) {
	if(0 <= index < getFloatSettingsAmount()) {
		return g_FloatSettings[index][SF_VALUE];
	} else {
		new string[64];
		format(string, sizeof(string), "Indeks wykracza poza zakres tabeli (0 <= %d < %d).", index, getFloatSettingsAmount());
		CallLocalFunction("OnFunctionGetError", "ss", "getSettingFloatValueByIndex", string);  
	}
	return 0.0;
}
//-----------------------------------------------------------
stock Float:getSettingFloatMinValueByIndex(index) {
	if(0 <= index < getFloatSettingsAmount()) {
		return g_FloatSettings[index][SF_MIN_VALUE];
	} else {
		new string[64];
		format(string, sizeof(string), "Indeks wykracza poza zakres tabeli (0 <= %d < %d).", index, getFloatSettingsAmount());
		CallLocalFunction("OnFunctionGetError", "ss", "getSettingFloatMinValueByIndex", string);  
	}
	return 0.0;
}
//-----------------------------------------------------------
stock Float:getSettingFloatMaxValueByIndex(index) {
	if(0 <= index < getFloatSettingsAmount()) {
		return g_FloatSettings[index][SF_MAX_VALUE];
	} else {
		new string[64];
		format(string, sizeof(string), "Indeks wykracza poza zakres tabeli (0 <= %d < %d).", index, getFloatSettingsAmount());
		CallLocalFunction("OnFunctionGetError", "ss", "getSettingFloatMaxValueByIndex", string);  
	}
	return 0.0;
}
//-----------------------------------------------------------
stock getSettingFloatPatchByIndex(index) {
	new patch[64];
	if(0 <= index < getFloatSettingsAmount()) {
		strunpack(patch, g_FloatSettings[index][SF_PATCH], 64);
	} else {
		new string[64];
		format(string, sizeof(string), "Indeks wykracza poza zakres tabeli (0 <= %d < %d).", index, getFloatSettingsAmount());
		CallLocalFunction("OnFunctionGetError", "ss", "getSettingFloatPatchByIndex", string);  
	}
	return patch;
}
#else
	stock getFloatSettingsAmount() {
		return _FALSE;
	}
	stock registerFloatSetting(name[], patch[], Float:value, Float:min_value = -1.0, Float:max_value = 1.0) {
		#pragma unused name, patch, value, min_value, max_value
		new string[90];
		format(string, sizeof(string), "Niepoprawnie zdefiniowany rozmiar tablic skryptu (MAX_FLOAT_SETTINGS: %d (<= 0))", MAX_FLOAT_SETTINGS);
		CallLocalFunction("OnFunctionGetError", "ss", "registerFloatSettings", string);   
		return _FALSE;
	}
	stock deleteFloatSetting(name[]) {
		#pragma unused name
		new string[90];
		format(string, sizeof(string), "Niepoprawnie zdefiniowany rozmiar tablic skryptu (MAX_FLOAT_SETTINGS: %d (<= 0))", MAX_FLOAT_SETTINGS);
		CallLocalFunction("OnFunctionGetError", "ss", "deleteFloatSetting", string);   
		return _FALSE;
	}
	stock setSettingFloatValue(name[], Float:value) {
		#pragma unused name, value
		new string[90];
		format(string, sizeof(string), "Niepoprawnie zdefiniowany rozmiar tablic skryptu (MAX_FLOAT_SETTINGS: %d (<= 0))", MAX_FLOAT_SETTINGS);
		CallLocalFunction("OnFunctionGetError", "ss", "setSettingFloatValue", string);   
		return _FALSE;
	}
	stock Float:getSettingFloatValue(name[]) {
		#pragma unused name
		new string[90];
		format(string, sizeof(string), "Niepoprawnie zdefiniowany rozmiar tablic skryptu (MAX_FLOAT_SETTINGS: %d (<= 0))", MAX_FLOAT_SETTINGS);
		CallLocalFunction("OnFunctionGetError", "ss", "getSettingFloatValue", string);   
		return 0.0;
	}
	stock Float:getSettingFloatMinValue(name[]) {
		#pragma unused name
		new string[90];
		format(string, sizeof(string), "Niepoprawnie zdefiniowany rozmiar tablic skryptu (MAX_FLOAT_SETTINGS: %d (<= 0))", MAX_FLOAT_SETTINGS);
		CallLocalFunction("OnFunctionGetError", "ss", "getSettingFloatMinValue", string);    
		return 0.0;
	}
	stock Float:getSettingFloatMaxValue(name[]) {
		#pragma unused name
		new string[90];
		format(string, sizeof(string), "Niepoprawnie zdefiniowany rozmiar tablic skryptu (MAX_FLOAT_SETTINGS: %d (<= 0))", MAX_FLOAT_SETTINGS);
		CallLocalFunction("OnFunctionGetError", "ss", "getSettingFloatMaxValue", string);   
		return 0.0;
	}
	stock getSettingFloatPatch(name[]) {
		#pragma unused name
		new string[90];
		format(string, sizeof(string), "Niepoprawnie zdefiniowany rozmiar tablic skryptu (MAX_FLOAT_SETTINGS: %d (<= 0))", MAX_FLOAT_SETTINGS);
		CallLocalFunction("OnFunctionGetError", "ss", "getSettingFloatPatch", string);    
		return _FALSE;
	}
	stock getSettingFloatIndex(name[]) {
		#pragma unused name
		new string[90];
		format(string, sizeof(string), "Niepoprawnie zdefiniowany rozmiar tablic skryptu (MAX_FLOAT_SETTINGS: %d (<= 0))", MAX_FLOAT_SETTINGS);
		CallLocalFunction("OnFunctionGetError", "ss", "getSettingFloatIndex", string);   
		return _FALSE;
	}
	stock getSettingFloatNameByIndex(index) {
		#pragma unused index
		new string[90];
		format(string, sizeof(string), "Niepoprawnie zdefiniowany rozmiar tablic skryptu (MAX_FLOAT_SETTINGS: %d (<= 0))", MAX_FLOAT_SETTINGS);
		CallLocalFunction("OnFunctionGetError", "ss", "getSettingFloatNameByIndex", string);   
		return _FALSE;
	}	
	stock setSettingFloatValueByIndex(index, Float:value) {
		#pragma unused index, value
		new string[90];
		format(string, sizeof(string), "Niepoprawnie zdefiniowany rozmiar tablic skryptu (MAX_FLOAT_SETTINGS: %d (<= 0))", MAX_FLOAT_SETTINGS);
		CallLocalFunction("OnFunctionGetError", "ss", "setSettingFloatValueByIndex", string);    
		return _FALSE;
	}	
	stock Float:getSettingFloatValueByIndex(index) {
		#pragma unused index
		new string[90];
		format(string, sizeof(string), "Niepoprawnie zdefiniowany rozmiar tablic skryptu (MAX_FLOAT_SETTINGS: %d (<= 0))", MAX_FLOAT_SETTINGS);
		CallLocalFunction("OnFunctionGetError", "ss", "getSettingFloatValueByIndex", string);     
		return 0.0;
	}	
	stock Float:getSettingFloatMinValueByIndex(index) {
		#pragma unused index
		new string[90];
		format(string, sizeof(string), "Niepoprawnie zdefiniowany rozmiar tablic skryptu (MAX_FLOAT_SETTINGS: %d (<= 0))", MAX_FLOAT_SETTINGS);
		CallLocalFunction("OnFunctionGetError", "ss", "getSettingFloatMinValueByIndex", string);   
		return 0.0;
	}	
	stock Float:getSettingFloatMaxValueByIndex(index) {
		#pragma unused index
		new string[90];
		format(string, sizeof(string), "Niepoprawnie zdefiniowany rozmiar tablic skryptu (MAX_FLOAT_SETTINGS: %d (<= 0))", MAX_FLOAT_SETTINGS);
		CallLocalFunction("OnFunctionGetError", "ss", "getSettingFloatMaxValueByIndex", string);    
		return 0.0;
	}	
	stock Float:getSettingFloatPatchByIndex(index) {
		#pragma unused index
		new string[90];
		format(string, sizeof(string), "Niepoprawnie zdefiniowany rozmiar tablic skryptu (MAX_FLOAT_SETTINGS: %d (<= 0))", MAX_FLOAT_SETTINGS);
		CallLocalFunction("OnFunctionGetError", "ss", "getSettingFloatPatchByIndex", string);   
		return 0.0;
	}	
#endif
//===========================================================
//-----------------------------------------------------------
//===========================================================
stock loadSettingsFromFile() { 
	if(getIntSettingsAmount() > 0 or getFloatSettingsAmount() > 0) {
		new c_patch[64], File:f_open, read[64], length, index, name[32], value[16], string[128];
		//------------------------------
		#if MAX_INT_SETTINGS > 0
		if(getIntSettingsAmount() > 0) {
			new bool:int_Settings[MAX_INT_SETTINGS];
			for(new i = getIntSettingsAmount() - 1, x; i >= 0; i --) {
				if(int_Settings[i] == false) {
					int_Settings[i] = true;
					strunpack(c_patch, g_IntSettings[i][SI_PATCH], 64);
					if(!isnull(c_patch)) {
						//------------------------------
						for(x = getIntSettingsAmount() - 1; x >= 0; x --) {
							if(int_Settings[x] == false) {
								if(!isnull(g_IntSettings[x][SI_PATCH])) {
									if(strcmp(g_IntSettings[x][SI_PATCH], g_IntSettings[i][SI_PATCH]) == 0) {
										int_Settings[x] = true;
									}
								}
							}
						}
						//------------------------------
						if(CheckFolderPatch(c_patch) == _TRUE and fexist(c_patch)) {
							f_open = fopen(c_patch, io_read);
							while(fread(f_open, read, sizeof(read))) {
								if((index = strfind(read, "\r")) != -1) read[index] = EOS;
								if((index = strfind(read, "\n")) != -1) read[index] = EOS;	
								if(!isnull(read) and (length = strlen(read)) > 2) {
									//----------------------
									for(x = length - 1, index = -1; x >= 0; x --) {
										if(read[x] == '=') {
											index = x;
											break;
										}
									}
									//----------------------
									if(index > 0 and index + 1 < length and index < 30 and length - index < 14) {
										strmid(name, read, 0, index, 32);
										strmid(value, read, index + 1, length, 16);
										if(!isnull(name) and !isnull(value)) {
											for(x = getIntSettingsAmount() - 1; x >= 0; x --) {
												if(strcmp(g_IntSettings[x][SI_NAME], name) == 0) {
													if(strcmp(g_IntSettings[x][SI_PATCH], g_IntSettings[i][SI_PATCH]) == 0) {
														setSettingIntValueByIndex(x, strval(value));
													}
													break;
												}
											}							
										}
									}		
									//----------------------
								}
							}
							fclose(f_open);
						} else {
							format(string, sizeof(string), "Niepoprawna sciezka odczytu ustawien (%s).", c_patch);
							CallLocalFunction("OnFunctionGetError", "ss", "loadSettingsFromFile", string);  
						}
						//------------------------------
					}
				}
			}			
		}
		#endif
		//------------------------------
		#if MAX_FLOAT_SETTINGS > 0
		if(getFloatSettingsAmount() > 0) {
			new bool:float_Settings[MAX_FLOAT_SETTINGS];
			for(new i = getFloatSettingsAmount() - 1, x; i >= 0; i --) {
				if(float_Settings[i] == false) {
					float_Settings[i] = true;
					strunpack(c_patch, g_FloatSettings[i][SF_PATCH], 64);
					if(!isnull(c_patch)) {
						//------------------------------
						for(x = getFloatSettingsAmount() - 1; x >= 0; x --) {
							if(float_Settings[x] == false) {
								if(!isnull(g_FloatSettings[x][SF_PATCH])) {
									if(strcmp(g_FloatSettings[x][SF_PATCH], g_FloatSettings[i][SF_PATCH]) == 0) {
										float_Settings[x] = true;
									}
								}
							}
						}
						//------------------------------
						if(CheckFolderPatch(c_patch) == _TRUE and fexist(c_patch)) {
							f_open = fopen(c_patch, io_read);
							while(fread(f_open, read, sizeof(read))) {
								if((index = strfind(read, "\r")) != -1) read[index] = EOS;
								if((index = strfind(read, "\n")) != -1) read[index] = EOS;	
								if(!isnull(read) and (length = strlen(read)) > 2) {
									//----------------------
									for(x = length - 1, index = -1; x >= 0; x --) {
										if(read[x] == '=') {
											index = x;
											break;
										}
									}
									//----------------------
									if(index > 0 and index + 1 < length and index < 30 and length - index < 14) {
										strmid(name, read, 0, index, 32);
										strmid(value, read, index + 1, length, 16);
										if(!isnull(name) and !isnull(value)) {
											for(x = getFloatSettingsAmount() - 1; x >= 0; x --) {
												if(strcmp(g_FloatSettings[x][SF_NAME], name) == 0) {
													if(strcmp(g_FloatSettings[x][SF_PATCH], g_FloatSettings[i][SF_PATCH]) == 0) {
														setSettingFloatValueByIndex(x, floatstr(value));
													}
													break;
												}
											}							
										}
									}		
									//----------------------
								}
							}
							fclose(f_open);
						} else {
							format(string, sizeof(string), "Niepoprawna sciezka odczytu ustawien (%s).", c_patch);
							CallLocalFunction("OnFunctionGetError", "ss", "loadSettingsFromFile", string);  
						}
						//------------------------------
					}
				}
			}			
		}
		#endif	
		//------------------------------
		return _TRUE;
	}
	return _FALSE;
}
//-----------------------------------------------------------
stock saveSettingsToFile() { 
	if(getIntSettingsAmount() > 0 or getFloatSettingsAmount() > 0) {
		new c_patch[64], File:f_open, File:f_buffer, read[128], index, bool:write, length;
		#if MAX_INT_SETTINGS > 0
		if(getIntSettingsAmount() > 0) {
			new bool:int_Settings[MAX_INT_SETTINGS];
			for(new i = getIntSettingsAmount() - 1, x; i >= 0; i --) {
				if(int_Settings[i] == false) {
					int_Settings[i] = true;
					strunpack(c_patch, g_IntSettings[i][SI_PATCH], 64);
					if(!isnull(c_patch)) {
						//------------------------------
						for(x = getIntSettingsAmount() - 1; x >= 0; x --) {
							if(int_Settings[x] == false) {
								if(!isnull(g_IntSettings[x][SI_PATCH])) {
									if(strcmp(g_IntSettings[x][SI_PATCH], g_IntSettings[i][SI_PATCH]) == 0) {
										int_Settings[x] = true;
									}
								}
							}
						}
						//------------------------------
						if(CheckFolderPatch(c_patch) == _TRUE) {
							//------------------------------
							if(fexist(c_patch)) {
								f_buffer = fopen(TMP_FILE, io_write);
								f_open = fopen(c_patch, io_read);
								while(fread(f_open, read, sizeof(read))) {
									write = true;
									if((index = strfind(read, "\r")) != -1) read[index] = EOS;
									if((index = strfind(read, "\n")) != -1) read[index] = EOS;	
									if(!isnull(read) and (length = strlen(read)) > 2) {
										//----------------------
										for(x = length - 1, index = -1; x >= 0; x --) {
											if(read[x] == '=') {
												index = x;
												break;
											}
										}
										//----------------------
										if(index > 0 and index + 1 < length and index < 30 and length - index < 14) {
											for(x = getIntSettingsAmount() - 1; x >= 0; x --) {
												if(strcmp(g_IntSettings[x][SI_NAME], read, false, index) == 0) {
													if(strcmp(g_IntSettings[x][SI_PATCH], g_IntSettings[i][SI_PATCH]) == 0) {
														write = false;
														break;
													}
												}
											}
										}
										if(write == true) {
											fwrite(f_buffer, read);
											fwrite(f_buffer, "\r\n");
										}											
									}																
								}								
								fclose(f_open);
								fclose(f_buffer);
								
								f_buffer = fopen(TMP_FILE, io_read);
								f_open = fopen(c_patch, io_write);

								while(fread(f_buffer, read, sizeof(read))) {
									fwrite(f_open, read);
								}
								
								fclose(f_open);
								fclose(f_buffer);								
								fremove(TMP_FILE);
							}
							//------------------------------
							f_open = fopen(c_patch, io_append);
							for(x = getIntSettingsAmount() - 1; x >= 0; x --) {
								if(strcmp(g_IntSettings[x][SI_PATCH], g_IntSettings[i][SI_PATCH]) == 0) {
									strunpack(read, g_IntSettings[x][SI_NAME], 32);
									if(!isnull(read)) {
										format(read, sizeof(read),"\r\n%s=%d", read, g_IntSettings[x][SI_VALUE]);
										fwrite(f_open, read);
									}
								}
							}							
							fclose(f_open);
							//------------------------------
						} else {
							format(read, sizeof(read), "Niepoprawna sciezka odczytu ustawien (%s).", c_patch);
							CallLocalFunction("OnFunctionGetError", "ss", "saveSettingsToFile", read);  
						}
					}
				}
			}
		}
		#endif
		
		#if MAX_FLOAT_SETTINGS > 0
		if(getFloatSettingsAmount() > 0) {
			new bool:float_Settings[MAX_INT_SETTINGS];
			for(new i = getFloatSettingsAmount() - 1, x; i >= 0; i --) {
				if(float_Settings[i] == false) {
					float_Settings[i] = true;
					strunpack(c_patch, g_FloatSettings[i][SF_PATCH], 64);
					if(!isnull(c_patch)) {
						//------------------------------
						for(x = getFloatSettingsAmount() - 1; x >= 0; x --) {
							if(float_Settings[x] == false) {
								if(!isnull(g_FloatSettings[x][SF_PATCH])) {
									if(strcmp(g_FloatSettings[x][SF_PATCH], g_FloatSettings[i][SF_PATCH]) == 0) {
										float_Settings[x] = true;
									}
								}
							}
						}
						//------------------------------
						if(CheckFolderPatch(c_patch) == _TRUE) {
							//------------------------------
							if(fexist(c_patch)) {
								f_buffer = fopen(TMP_FILE, io_write);
								f_open = fopen(c_patch, io_read);
								while(fread(f_open, read, sizeof(read))) {
									write = true;
									if((index = strfind(read, "\r")) != -1) read[index] = EOS;
									if((index = strfind(read, "\n")) != -1) read[index] = EOS;	
									if(!isnull(read) and (length = strlen(read)) > 2) {
										//----------------------
										for(x = length - 1, index = -1; x >= 0; x --) {
											if(read[x] == '=') {
												index = x;
												break;
											}
										}
										//----------------------
										if(index > 0 and index + 1 < length and index < 30 and length - index < 14) {
											for(x = getFloatSettingsAmount() - 1; x >= 0; x --) {
												if(strcmp(g_FloatSettings[x][SF_NAME], read, false, index) == 0) {
													if(strcmp(g_FloatSettings[x][SF_PATCH], g_FloatSettings[i][SF_PATCH]) == 0) {
														write = false;
														break;
													}
												}
											}
										}
										if(write == true) {
											fwrite(f_buffer, read);
											fwrite(f_buffer, "\r\n");
										}											
									}									
								
								}								
								fclose(f_open);
								fclose(f_buffer);
								
								f_buffer = fopen(TMP_FILE, io_read);
								f_open = fopen(c_patch, io_write);

								while(fread(f_buffer, read, sizeof(read))) {
									fwrite(f_open, read);
								}
								
								fclose(f_open);
								fclose(f_buffer);								
								fremove(TMP_FILE);
							}
							//------------------------------
							f_open = fopen(c_patch, io_append);
							for(x = getFloatSettingsAmount() - 1; x >= 0; x --) {
								if(strcmp(g_FloatSettings[x][SF_PATCH], g_FloatSettings[i][SF_PATCH]) == 0) {
									strunpack(read, g_FloatSettings[x][SF_NAME], 32);
									if(!isnull(read)) {
										format(read, sizeof(read),"\r\n%s=%.04f", read, g_FloatSettings[x][SF_VALUE]);
										fwrite(f_open, read);
									}
								}
							}							
							fclose(f_open);
							//------------------------------
						} else {
							format(read, sizeof(read), "Niepoprawna sciezka odczytu ustawien (%s).", c_patch);
							CallLocalFunction("OnFunctionGetError", "ss", "saveSettingsToFile", read);  
						}
					}
				}
			}
		}	
		#endif
		return _TRUE;
	}
	return _FALSE;
}



















