/*
	--- System logow ---
	Autor: Rafał (AxL_) Żółtański
	Data ostatniej modyfikacji: 24 czerwca 2013 (21:25)
	
	UWAGA! 
	System uzywa include 'a_func'!
	
	Funkcje:
		native addToSpecyficLog(fileName[], filePatch[], logMessage[]);
		native addToNormalLog(filePatch[], logMessage[]);
		native addToDailyLog(filePatch[], logMessage[]);
	
		--------------------
*/
//===========================================================
//-----------------------------------------------------------
//===========================================================
//#include <a_func>
#if defined _c_logs_included
  #endinput
#endif

#define _c_logs_included
#pragma library c_logs

#if !defined _FALSE
	#define _FALSE 0
#endif
#if !defined _TRUE
	#define _TRUE 1
#endif
#if !defined and
	#define and &&
#endif
#if !defined or
	#define or ||
#endif
//-----------------------------------------------------------
forward OnFunctionGetError(funcname[], errormsg[]);
//===========================================================
//-----------------------------------------------------------
//===========================================================
stock addToSpecyficLog(fileName[], filePatch[], logMessage[]) {
	if(!isnull(fileName) and !isnull(filePatch) and !isnull(logMessage)) {
		new string[128];
		format(string, sizeof(string), "%s/%s.txt", filePatch, fileName);
		addToNormalLog(string, logMessage);
		return _TRUE;
	}
	return _FALSE;
}
//-----------------------------------------------------------
stock addToNormalLog(filePatch[], logMessage[]) {
	if(!isnull(filePatch) and !isnull(logMessage)) {
	
		if(!fexist(filePatch)) {
			if(CheckFolderPatch(filePatch) == _TRUE) {
				fclose(fopen(filePatch, io_write));
			} else {
				new e_string[128];
				format(e_string, sizeof(e_string), "Nieodnaleziono pliku o sciezce '%s'.", filePatch);
				CallLocalFunction("OnFunctionGetError", "ss", "addToNormalLog", e_string);
				return _FALSE;
			}
		}
		
		if(fexist(filePatch)) {
			new string[64];	
			new File:f_open = fopen(filePatch, io_append);
			new year, month, day, hour, minute, second;
					
			getdate(year, month, day);
			gettime(hour, minute, second);						
			format(string, sizeof(string), "\r\n[ %d/%02d/%02d | %d:%02d:%02d ] ", year, month, day, hour, minute, second);
			fwrite(f_open, string);
			fwrite(f_open, logMessage);
			fclose(f_open);
			return _TRUE;
		}
	}
	return _FALSE;
}
//-----------------------------------------------------------
stock addToDailyLog(filePatch[], logMessage[]) {
	if(!isnull(filePatch) and !isnull(logMessage)) {

		if(fexist(filePatch)) {			
			new string[64];	
			new File:f_open;	
			new year, month, day, hour, minute, second;
				
			//----------------------------
			getdate(year, month, day);
			gettime(hour, minute, second);							
			//----------------------------
			format(string, sizeof(string),"%s/%d-%02d-%02d.txt", filePatch, year, month, day);
			f_open = fopen(string, io_append);
			//----------------------------
			format(string, sizeof(string), "\r\n[ %d:%02d:%02d ] ", hour, minute, second);
			fwrite(f_open, string);
			fwrite(f_open, logMessage);
			fclose(f_open);
			return _TRUE;
		} else {
			new e_string[128];
			format(e_string, sizeof(e_string), "Nieodnaleziono folderu o sciezce '%s'.", filePatch);
			CallLocalFunction("OnFunctionGetError", "ss", "addToDailyLog", e_string);
		}		
	}
	return _FALSE;
}
