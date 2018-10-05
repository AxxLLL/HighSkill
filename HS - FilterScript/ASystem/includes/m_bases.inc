/*
	___________________________________________
	Funkcje tworzace bazy danych Admin Systemu. 
	Wszystkie bazy uzywaja opcji AutoIncrement, oraz sa dostosowane zarowno do zapisu w bazie SQL, jak i w MySQL.
	___________________________________________
	
	
	___________________________________________
	CreateNickChangeBase ("b") - Baza przechowujaca informacje o zmianach nicku na koncie gracza.
		- CreateNickChangeBase()
			- T_NICK_CHANGE
				+ TCN_UNIQUE_ID	
				+ TNC_UID
				+ TNC_STAMP
				+ TNC_OLD_NICK
				+ TNC_NEW_NICK
	___________________________________________
	CreatePlayerInfoBase ("c") - Baza przechowujaca informacje o graczu wchodzacym na serwer.
		- CreatePlayerInfoBase()
			- T_PLAYER_INFO
				+ TPI_UNIQUE_ID
				+ TPI_UID
				+ TPI_STAMP
				+ TPI_NICK
				+ TPI_IP
				+ TPI_GPCI
	___________________________________________			
	CreateBanTable ("e") - Baza przechowujaca informacje o banach stalych (tj. na nick, ip, host, gpci).
		- CreateBanTable()
			- T_BAN
				+ TB_UNIQUE_ID
				+ TB_VALUE
				+ TB_TYPE
				+ TB_ADMINID
				+ TB_ADMIN_NAME
				+ TB_UNBANTIME
				+ TB_REASON
				+ TB_DATE_STAMP
	___________________________________________	
	CreateTimeBanTable ("f") - Baza przechowujaca informacje o banach czasowch.
		- CreateTimeBanTable()
			- T_TIME_BAN
				+ TTB_UNIQUE_ID
				+ TTB_HOST
				+ TTB_UID
				+ TTB_PLAYER_NAME
				+ TTB_ADMINID
				+ TTB_ADMIN_NAME
				+ TTB_UNBANTIME
				+ TTB_REASON
				+ TTB_DATE_STAMP
	___________________________________________	
	CreatePlayersBase ("a") - Baza przechowujaca dane kont graczy.
		- CreatePlayersBase()
			- T_KONTA
				+ TK_UID
				+ TK_NICK
				+ TK_PASSWORD
				+ TK_RESET_PASSWORD
				+ TK_REGISTER_STAMP
				+ TK_ADMIN_LVL
				+ TK_ADMIN_PASSWORD
				+ TK_ADMIN_STAMP
				+ TK_DELETE_STAMP
				+ TK_LAST_LOGIN_STAMP
				+ TK_LAST_LOGIN_IP
				+ TK_LAST_LOGIN_GPCI
				+ TK_LAST_NICK
				+ TK_LAST_NICK_STAMP
				+ TK_PLAY_TIME
				+ TK_PROV_CONFIDENTAL
				+ TK_BAN_TIME			
				+ TK_BAN_ADMIN_ID
				+ TK_BAN_REASON
				+ TK_LAST_DISCONNECT
				+ TK_SETTINGS
	___________________________________________
*/
//===============================================================
//---------------------------------------------------------------
//===============================================================
#define	T_NICK_CHANGE	"b"

#define TCN_UNIQUE_ID	"ba"
#define	TNC_UID			"bb"
#define	TNC_STAMP		"bc"
#define	TNC_OLD_NICK	"bd"
#define	TNC_NEW_NICK	"be"
//---------------------------------------------------------------
CreateNickChangeBase() {
	new string[256];
	if(UseMySQL() == _FALSE) {
		format(string, sizeof(string), "CREATE TABLE IF NOT EXISTS `"T_NICK_CHANGE"` (`"TCN_UNIQUE_ID"` INTEGER PRIMARY KEY AUTOINCREMENT,");
	} else {
		format(string, sizeof(string), "CREATE TABLE IF NOT EXISTS `"T_NICK_CHANGE"` (`"TCN_UNIQUE_ID"` INTEGER PRIMARY KEY NOT NULL AUTO_INCREMENT,");
	}
	
	format(string, sizeof(string),"%s\
					`"TNC_UID"` INT,\
					`"TNC_STAMP"` INT,\
					`"TNC_OLD_NICK"` VARCHAR(24),\
					`"TNC_NEW_NICK"` VARCHAR(24)\
				);", string);

	sendQueryWithout(string);	
	return _TRUE;
}
//===============================================================
//---------------------------------------------------------------
//===============================================================
#define	T_PLAYER_INFO	"c"

#define	TPI_UNIQUE_ID	"ca"
#define	TPI_UID			"cb"
#define	TPI_STAMP		"cc"
#define	TPI_NICK		"cd"
#define	TPI_IP			"ce"
#define	TPI_GPCI		"cf"
//---------------------------------------------------------------
CreatePlayerInfoBase() {
	new string[256];
	if(UseMySQL() == _FALSE) {
		format(string, sizeof(string), "CREATE TABLE IF NOT EXISTS `"T_PLAYER_INFO"` (`"TPI_UNIQUE_ID"` INTEGER PRIMARY KEY AUTOINCREMENT,");
	} else {
		format(string, sizeof(string), "CREATE TABLE IF NOT EXISTS `"T_PLAYER_INFO"` (`"TPI_UNIQUE_ID"` INTEGER PRIMARY KEY NOT NULL AUTO_INCREMENT,");
	}
	
	format(string, sizeof(string),"%s\
					`"TPI_UID"` INT,\
					`"TPI_STAMP"` INT,\
					`"TPI_NICK"` VARCHAR(24),\
					`"TPI_IP"` VARCHAR(16),\
					`"TPI_GPCI"` VARCHAR(64)\
				);", string);
				
	sendQueryWithout(string);	
	return _TRUE;
}
//===============================================================
//---------------------------------------------------------------
//===============================================================
#define T_BAN			"e"

#define TB_UNIQUE_ID	"ea"
#define TB_VALUE		"eb"
#define	TB_TYPE			"ec"
#define TB_ADMINID		"ed"
#define TB_ADMIN_NAME	"ee"
#define TB_UNBANTIME	"ef"
#define TB_REASON		"eg"
#define TB_DATE_STAMP	"eh"
//---------------------------------------------------------------
CreateBanTable() {
	new string[256];
	if(UseMySQL() == _FALSE) {
		format(string, sizeof(string), "CREATE TABLE IF NOT EXISTS `"T_BAN"` (`"TB_UNIQUE_ID"` INTEGER PRIMARY KEY AUTOINCREMENT,");
	} else {
		format(string, sizeof(string), "CREATE TABLE IF NOT EXISTS `"T_BAN"` (`"TB_UNIQUE_ID"` INTEGER PRIMARY KEY NOT NULL AUTO_INCREMENT,");
	}	

	format(string, sizeof(string),"%s\
					`"TB_VALUE"` VARCHAR(64),\
					`"TB_TYPE"` INT,\
					`"TB_ADMINID"` INT,\
					`"TB_ADMIN_NAME"` VARCHAR(24),\
					`"TB_UNBANTIME"` INT,\
					`"TB_REASON"` VARCHAR(128),\
					`"TB_DATE_STAMP"` INT\
					);\
				", string);

	sendQueryWithout(string);
	return _TRUE;
}
//===============================================================
//---------------------------------------------------------------
//===============================================================
#define T_TIME_BAN		"f"

#define TTB_UNIQUE_ID	"fa"
#define TTB_HOST		"fb"
#define TTB_UID			"fc"
#define TTB_PLAYER_NAME	"fd"
#define TTB_ADMINID		"fe"
#define TTB_ADMIN_NAME	"ff"
#define TTB_UNBANTIME	"fg"
#define TTB_REASON		"fh"
#define TTB_DATE_STAMP	"fi"
//---------------------------------------------------------------
CreateTimeBanTable() {
	new string[256];
	if(UseMySQL() == _FALSE) {
		format(string, sizeof(string), "CREATE TABLE IF NOT EXISTS `"T_TIME_BAN"` (`"TTB_UNIQUE_ID"` INTEGER PRIMARY KEY AUTOINCREMENT,");
	} else {
		format(string, sizeof(string), "CREATE TABLE IF NOT EXISTS `"T_TIME_BAN"` (`"TTB_UNIQUE_ID"` INTEGER PRIMARY KEY NOT NULL AUTO_INCREMENT,");
	}
	format(string, sizeof(string),"%s\
					`"TTB_HOST"` VARCHAR(8),\
					`"TTB_UID"` INT,\
					`"TTB_PLAYER_NAME"` VARCHAR(24),\
					`"TTB_ADMINID"` INT,\
					`"TTB_ADMIN_NAME"` VARCHAR(24),\
					`"TTB_UNBANTIME"` INT,\
					`"TTB_REASON"` VARCHAR(128),\
					`"TTB_DATE_STAMP"` INT\
					);\
				", string);
	sendQueryWithout(string);
	return _TRUE;
}
//===============================================================
//---------------------------------------------------------------
//===============================================================
#define T_KONTA					"a"

#define TK_UID					"aa"
#define TK_NICK					"ab"
#define TK_PASSWORD				"ac"
#define TK_RESET_PASSWORD		"ad"
#define	TK_REGISTER_STAMP		"ae"
#define TK_REGISTER_IP			"aai"
#define TK_REGISTER_GPCI		"aaj"
#define TK_RCON_ADMIN			"aak"
#define TK_ADMIN_LVL 			"af"
#define TK_ADMIN_PASSWORD		"ag"
#define TK_ADMIN_STAMP			"ah"
#define TK_DELETE_STAMP			"ai"
#define TK_LAST_LOGIN_STAMP		"aj"
#define TK_LAST_LOGIN_IP		"ak"
#define TK_LAST_LOGIN_GPCI		"al"
#define	TK_LAST_NICK			"am"
#define TK_LAST_NICK_STAMP		"an"
#define TK_PLAY_TIME			"ao"
#define	TK_PROV_CONFIDENTAL		"ap"
#define TK_BAN_TIME				"ar"
#define TK_BAN_ADMIN_ID			"aq"
#define TK_BAN_REASON			"at"
#define TK_LAST_DISCONNECT		"au"
#define TK_SETTINGS				"aw"
#define TK_PREMIUM_DATE			"ax"
#define TK_PREMIUM_PLAYER_POINT	"ay"
#define TK_PREMIUM_BONUS_POINT	"az"
//---------------------------------------------------------------
CreatePlayersBase() {
	new string[2048];
	if(UseMySQL() == _FALSE) {
		format(string, sizeof(string), "CREATE TABLE IF NOT EXISTS `"T_KONTA"` (`"TK_UID"` INTEGER PRIMARY KEY AUTOINCREMENT,");
	} else {
		format(string, sizeof(string), "CREATE TABLE IF NOT EXISTS `"T_KONTA"` (`"TK_UID"` INTEGER PRIMARY KEY NOT NULL AUTO_INCREMENT,");
	}	

	format(string, sizeof(string), "%s\
					`"TK_NICK"` VARCHAR(24), \
					`"TK_PASSWORD"` INT, \
					`"TK_RESET_PASSWORD"` INT DEFAULT '0',\
					`"TK_REGISTER_STAMP"` INT DEFAULT '0',\
					`"TK_REGISTER_IP"` VARCHAR(16) DEFAULT ' ',\
					`"TK_REGISTER_GPCI"` VARCHAR(64) DEFAULT ' ',\
					`"TK_RCON_ADMIN"` INT DEFAULT '0',\
					`"TK_ADMIN_LVL"` INT DEFAULT '0', \
					`"TK_ADMIN_PASSWORD"` INT DEFAULT '0',\
					`"TK_ADMIN_STAMP"` INT DEFAULT '0',\
					`"TK_DELETE_STAMP"` INT,\
				", string);
	format(string, sizeof(string), "%s\
					`"TK_LAST_LOGIN_STAMP"` INT DEFAULT '0',\
					`"TK_LAST_LOGIN_IP"` VARCHAR(16) DEFAULT ' ',\
					`"TK_LAST_LOGIN_GPCI"` VARCHAR(64) DEFAULT ' ',\
					`"TK_LAST_NICK"` VARCHAR(24) DEFAULT '0',\
					`"TK_LAST_NICK_STAMP"` INT DEFAULT '0',\
					`"TK_PLAY_TIME"` INT DEFAULT '0',\
					`"TK_PROV_CONFIDENTAL"` INT DEFAULT '0',\
					`"TK_BAN_TIME"` INT DEFAULT '0',\
					`"TK_BAN_ADMIN_ID"` INT DEFAULT '0',\
					`"TK_BAN_REASON"` VARCHAR(128) DEFAULT ' ',\
				", string);
	format(string, sizeof(string), "%s\
					`"TK_LAST_DISCONNECT"` INT DEFAULT '0',\
					`"TK_SETTINGS"` VARCHAR(16) DEFAULT '0',\
					`"TK_PREMIUM_DATE"` INT DEFAULT '0',\
					`"TK_PREMIUM_PLAYER_POINT"` INT DEFAULT '0',\
					`"TK_PREMIUM_BONUS_POINT"` INT DEFAULT '0'\
					);\
				", string);
	sendQueryWithout(string);
	return _TRUE;
}