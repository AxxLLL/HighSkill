/*
	___________________________________________
	Wykorzystanie specjalnej funkcji 'ShowPlayerDialogEx' do wywołania okna dialogowego, oprócz kolorowania tekstu pełni również rolę Anty Cheata na programy wywołujące okna dialogowe.
	Korzystając z tego skryptu należy wykorzystywać tylko i wyłącznie tą formę otwierania okien dialogowych, gdyż w przeciwnym razie nie będą one działały poprawnie z powodu blokowania przez skrypt.
	___________________________________________
	
	
	___________________________________________
	ShowPlayerDialogEx(playerid, dialogid, style, head[], text[], btn1[], btn2[]) - Funkcja wyświetlająca okno dialogowe dla gracza. Treść okna dialogowego jest automatycznie kolorowana
			zgodnie z stylem serwera. Numeracja wierszy w stylu listowym również jest kolorowana automatycznie.
			Zwracane wartości: 1 - Wyświetlono dialog, 0 - Niewyświetlono dialogu, -1 - Gracz Offline
	___________________________________________
	GetPlayerDialogID(playerid) - Funkcja zwracająca ID ostatnio otwartego okna dialogowego dla gracza.
			Zwracane wartości: ID ostatnio aktywnego okna dialogowego, -1 - Gdy gracz jest Offline.
	___________________________________________
	HidePlayerDialog(playerid) - Funkcja ukrywająca aktywne okno dialogowe dla gracza.
			Zwracane wartości: Brak.
	___________________________________________
	IsValidPlayerDialogID(playerid, dialogid) - Funkcja sprawdzająca czy aktywne okno dialogowe zostało rzeczywiście otwarte przez skrypt. Ma to na celu zabezpieczenie serwera przed
			możliwością otwierania okien dialogowych przez zewnętrzne programy.
			Zwracane wartości: 1 - Okno poprawne, 0 - Okno niepoprawne.
	___________________________________________
	ShowPlayerInfoDialog(playerid, backid, head[], info[]) - Funkcja wyświetlająca specjalne okno dialogowe informacji, które umożliwia szybki powrót do menu, z którego zostało wywołane.
			Zwracane wartości: Brak.
	___________________________________________
	GetPlayerBackDialogID(playerid) - Funkcja zwracająca ID menu do którego ma wrócić funkcja po wyłączeniu okna dialogowego informacji.
			Zwracane wartości: ID menu, do którego ma wrócić funkcja.
	___________________________________________
	BackPlayerDialog(playerid, backid) - Funkcja odpowiadająca za powrót do poprzedniego menu, po wyłączeniu okna dialogowego informacji.
			Zwracane wartości: 1 - Powrócono do menu, 0 - Niepowrócono do menu.
	___________________________________________
	ShowPlayerCaptcha(playerid, backid, captcha_time = 0) - Funkcja pokazujaca graczu okno "Captcha". Kodem jest liczba z przedzialu od 10.000 do 99.999. Jako parametry nalezy podac ID gracza (playerid), 
			ID Back Menu, czyli menu do ktorego, ma wrocic gracz po poprawnym wpisaniu kodu 'Captcha' oraz czas, jaki ma gracz na wpisanie kodu. Czas rowny 0 oznacza brak limitu czasowego.
			Zwracane wartości: 1.		
	___________________________________________
	GetPlayerCaptchaBackID(playerid) - Funkcja zwracajaca wartosc ID Back Menu gracza.
			Zwracane wartości: ID Back Menu gracza.
	___________________________________________
	PlayerConfirmCaptcha(playerid, captcha[]) - Funkcja wykonywana po wpisaniu dowolnego kodu w okno 'Captcha'. W przypadku poprawnego kodu, wywolywany jest Callback 'OnPlayerConfirmCaptcha(playerid, 1)', w przypadku zlego kodu
			ponownie wyswietlane jest okno 'Captcha' lub, w przypadku przekroczenia 5 nieudanych prob wpisania kodu, wywolywany jest Callback 'OnPlayerConfirmCaptcha(playerid, 0)'.
			Zwracane wartości: 1 - Poprawny kod 'Captcha', 0 - Niepoprawny kod 'Captcha'.		
	___________________________________________
	KillCaptchaTimer(playerid) - Funkcja "zabijająca" timer 'Captchy'. Nalezy jej uzyc przy wychodzeniu gracza z serwera.
			Zwracane wartości: 1.
	___________________________________________
	ShowPlayerYesNoDialog(playerid, backid, head[], info[]) - Funkcja pokazująca graczu menu wyboru "Tak / Nie". Parametr backid oznacza identyfikator opcji, dla ktorej zostalo wywolane menu. 
			Parametr 'head' oznacza naglowek okna dialogowego, a 'info' jego tresc.
			Zwracane wartości: 1.
	___________________________________________
	DialogYesNoResponse(playerid, response)	- Funkcja obsługująca menu wyboru "Tak / Nie". W niej należy tworzyć odpowiedni kod postępowania po zatwierdzeniu lub braku zatwierdzenia opcji.
			Zwracane wartości: 1 - Znaleziono opcję, 0 - Nieznaleziono opcji.
	___________________________________________
*/
//==============================================================
//--------------------------------------------------------------
//==============================================================
#define COLOR_DIALOG_HEAD		0x078FE0FF						// Definicja koloru naglowka okien dialogowych w formacje 0xRRGGBBPP  (P - Przezroczystosc [bez znaczenia w przypadku okien dialogowych, no ale...]).
#define TEXT_DIALOG_HEAD		"{078FE0}"						// Definicja koloru naglowka okien dialogowych w formacje {RRGGBB} do wykorzystania wewnatrz tekstu.

#define COLOR_DIALOG_BODY		0x68BEFDFF						// Definicja koloru ciala okien dialogowych w formacje 0xRRGGBBPP  (P - Przezroczystosc).
#define TEXT_DIALOG_BODY		"{68BEFD}"						// Definicja koloru ciala okien dialogowych w formacje {RRGGBB} do wykorzystania wewnatrz tekstu.

#define COLOR_DIALOG_ALERT		0xFF0000FF						// Definicja koloru ostrzezen okien dialogowych w formacje 0xRRGGBBPP  (P - Przezroczystosc).
#define TEXT_DIALOG_ALERT		"{FF0000}"						// Definicja koloru ostrzezen okien dialogowych w formacje {RRGGBB} do wykorzystania wewnatrz tekstu.

#define COLOR_DIALOG_COUNT		0xDDF4FFFF						// Definicja koloru listingu okien dialogowych w formacje 0xRRGGBBPP  (P - Przezroczystosc).
#define TEXT_DIALOG_COUNT		"{DDF4FF}"						// Definicja koloru listingu okien dialogowych w formacje {RRGGBB} do wykorzystania wewnatrz tekstu.

#define COLOR_DIALOG_NORMAL		0xFFFFFFFF						// Definicja koloru normalnego okien dialogowych w formacje 0xRRGGBBPP  (P - Przezroczystosc). Kolor najczesciej uzywany do wyroznienia wyrazu w tekscie.
#define TEXT_DIALOG_NORMAL		"{FFFFFF}"						// Definicja koloru normalnego okien dialogowych w formacje {RRGGBB} do wykorzystania wewnatrz tekstu.

#define COLOR_SERVER_NAME		C_SYSGREY"HighSkill{0E9C95}.eu"	// Definicja nazwy serwera, ktora moze zostac uzywana w roznych miejscach okien dialogowych (w zaleznosci od specyfikacji moda).

//==============================================================
#define DIALOG_INFO							9000
#define DIALOG_CAPTCHA_CODE					9001
#define	DIALOG_YESNO						9002
#define	DIALOG_SEARCH_INFO					9003
#define	DIALOG_VALUE						9004

#define	DIALOG_LOGIN						10000
#define	DIALOG_REGISTER						10001
#define	DIALOG_PLAYER_ACCOUNT				10002
#define DIALOG_PLAYER_NICK					10003
#define	DIALOG_PLAYER_PASSWORD				10004
#define	DIALOG_PLAYER_ALOG_PASSWORD			10005
#define	DIALOG_PLAYER_SETTINGS				10006
#define	DIALOG_ALOG							10007
#define	DIALOG_ALOG_TYPE					10008
#define	DIALOG_ADMIN_LIST					10009
#define	DIALOG_ADMIN_LIST_LIST				10010
#define	DIALOG_ADMIN_LIST_INFO				10011
#define	DIALOG_ADMIN_PANEL					10012
#define	DIALOG_LDL							10013
#define	DIALOG_LDL_INFO						10014
#define	DIALOG_LDL_BAN_TIME					10015
#define	DIALOG_LDL_BAN_REASON				10016
#define	DIALOG_LDL_BAN_CONFIRM				10017
#define	DIALOG_TBAN_MENU					10018
#define	DIALOG_TBAN_SEARCH_MENU				10019
#define DIALOG_ADMIN_TBAN_LIST				10020
#define DIALOG_ADMIN_UNBAN_TIME_LIST		10021
#define	DIALOG_ADMIN_UNBAN_TIME_LIST_2		10022
#define	DIALOG_ADMIN_LIST_SEARCH			10023
#define	DIALOG_HA_PANEL						10024
#define	DIALOG_HA_SETTINGS					10025
#define	DIALOG_HE_SET_MENU					10026
#define	DIALOG_HA_BASE						10027
#define	DIALOG_HA_BASE_DELETE				10028
#define	DIALOG_HA_REGISTER					10029
#define	DIALOG_HA_REGISTER_PASSWORD			10030
#define	DIALOG_HA_DATA_MENU					10031
#define	DIALOG_HA_DATA_CHECK				10032
#define	DIALOG_HA_DATA_CHECK_SEARCH_MENU	10033
#define	DIALOG_HA_STATIC_BAN_MENU			10034
#define DIALOG_HA_STATIC_BAN_LIST			10035
#define	DIALOG_HA_STATIC_BAN_SEARCH			10036
#define	DIALOG_HA_STATIC_BAN_ADD_TYPE		10037
#define	DIALOG_HA_STATIC_BAN_ADD_VALUE		10038
#define	DIALOG_HA_STATIC_BAN_ADD_TIME		10039
#define	DIALOG_HA_STATIC_BAN_ADD_REASON		10040
#define	DIALOG_HA_BAN_UNBAN					10041
#define	DIALOG_HA_REGISTER_BASE_MENU		10042
#define	DIALOG_HA_REGISTER_BASE_LIST		10043
#define	DIALOG_HA_REGISTER_BASE_SEARCH		10044
#define	DIALOG_HA_ACCOUNT_SEARCH			10045
#define	DIALOG_HA_ACCOUNT_MENU				10046
#define	DIALOG_HA_ACCOUNT_SEARCH_LIST		10047
#define	DIALOG_HA_ACCOUNT_NICK				10048
#define	DIALOG_HA_ACCOUNT_PASSWORD			10049
#define	DIALOG_HA_ACCOUNT_ALVL				10050
#define	DIALOG_HA_ACCOUNT_ALVL_DATA			10051
#define	DIALOG_HA_ACCOUNT_APWD_RESET		10052
#define	DIALOG_HA_ACCOUNT_PROV_CONFI		10053
#define	DIALOG_HA_ACCOUNT_BAN_INFO			10054
#define	DIALOG_HA_ACCOUNT_BAN_TIME			10055
#define	DIALOG_HA_ACCOUNT_BAN_REASON		10056
#define	DIALOG_HA_ACCOUNT_BAN_CONFIRM		10057
#define	DIALOG_PLAYER_PRIV_SETTINGS			10058
#define	DIALOG_PLAYER_PRIV_PLAYERS_SETTINGS	10059
#define	DIALOG_PLAYER_PRIV_SOUND			10060
#define	DIALOG_PLAYER_VIP_MENU				10061
#define	DIALOG_PLAYER_VIP_ACTIVATE			10062
#define	DIALOG_HA_ACCOUNT_VIPMENU			10063
#define	DIALOG_HA_ACCOUNT_VIPPOINTS			10064
#define	DIALOG_HA_ACCOUNT_VIPTIME			10065
#define	DIALOG_HA_VIPMENU					10066
#define	DIALOG_HA_VIPACCOUNTS_SEARCH		10067
#define	DIALOG_HA_VIPACCOUNTS_LIST			10068
#define	DIALOG_HA_VIPMENU_POINTS			10069
#define	DIALOG_HA_VIPMENU_TIME				10070
#define	DIALOG_PLAYER_VIP_SENDPOINTS		10071
#define	DIALOG_PLAYER_VIP_SENDUSER			10072
#define	DIALOG_ADMIN_HELP					10073
#define	DIALOG_ADMIN_HELP_CMDS				10074
#define DIALOG_ADMIN_ONLINE_CHECK			10075
#define	DIALOG_HELP_MENU					10078
#define DIALOG_HELP_CMD_MENU				10079
#define	DIALOG_HA_SAMPBAN_REMOVE			10080
#define	DIALOG_ADMIN_RESET_STATS			10081
#define DIALOG_NAME_CHECK_TYPE				10082
#define	DIALOG_NAME_CHECK_PLAYER			10083

#define	BACK_PLAYER_ACC_MENU		1
#define BACK_ALOG_MENU				2
#define BACK_PLAYER_ACC_SETTINGS	3
#define BACK_ADMIN_LIST				4
#define BACK_LDL					5
#define BACK_LDL_INFO				6
#define BACK_NADMIN_PANEL			7
#define	BACK_TIME_BAN_LIST			8
#define BACK_TIME_BAN_MENU			9
#define	BACK_TIME_SEARCH_MENU		10
#define	BACK_SEARCH_LIST			11
#define	BACK_HAPANEL_BASE			12
#define	BACK_HAPANEL_BASEDELETE		13
#define	BACK_HAPANEL				14
#define BACK_SETTING_MENU			15
#define	BACK_SETTING_SERVER_MENU	16
#define BACK_ACC_REGISTER			17
#define BACK_ADMIN_DATA				18
#define	BACK_HA_DATA_CHECK_LIST		19
#define BACK_HA_DATA_SEARCH			20
#define	BACK_HA_BAN_MENU			21
#define	BACK_HA_BAN_SEARCH			22
#define	BACK_HA_BAN_LIST			23
#define	BACK_HA_REGISTER_MENU		24
#define	BACK_HA_REGISTER_LIST		25
#define	BACK_HA_REGISTER_SEARCH		26
#define	BACK_HA_ACCOUNT_SEARCH		27
#define	BACK_HA_ACCOUNT_MENU		28
#define	BACK_SETTING_SCRIPT_MENU	29
#define BACK_SETTINGS_PMFP_SETTINGS	30
#define	BACK_PLAYER_ACC_VIP_MENU	31
#define	BACK_HA_ACCOUNT_VIPMENU		32
#define BACK_VIPMENU_MENU			33
#define	BACK_VIPMENU_SEARCH			34
#define	BACK_ADMIN_HELP_MENU		35
#define	BACK_ADMIN_HELP_CMDS_MENU	36
#define	BACK_ADMIN_INFO_MENU		37
#define	BACK_HELP_MENU				39
#define	BACK_HELP_CMD_MENU			40
#define	BACK_AC_WEAPONS_INFO		41
//==============================================================
//--------------------------------------------------------------
//==============================================================
#define PV_PLAYER_DIALOGID	"PlayerDialogID"
ShowPlayerDialogEx(playerid, dialogid, style, head[], text[], btn1[], btn2[]) {
	if(IsPlayerConnected(playerid)) {
		new s_head[64], s_text[1024], index, index2;
		strins(s_head, head, 0);
		strins(s_head, TEXT_DIALOG_HEAD, 0);
		strins(s_text, text, 0);
		switch(style) {
			case DIALOG_STYLE_LIST: {
				while((index = strfind(s_text, "\n", false, index2)) != -1) {
					if(index > 950) break;
					strins(s_text, TEXT_DIALOG_COUNT, (index2 = index + 1));	
				}
				
				index2 = 0;
				while((index = strfind(s_text, ")", false, index2)) != -1) {
					if(index > 950) break;
					strins(s_text, TEXT_DIALOG_BODY, (index2 = index + 1));	
				}
			
			}
			default: strins(s_text, TEXT_DIALOG_HEAD, 0);
		}
		SetPVarInt(playerid, PV_PLAYER_DIALOGID, dialogid);
		return ShowPlayerDialog(playerid, dialogid, style, s_head, s_text, btn1, btn2);
	}
	return -1;
}
//--------------------------------------------------------------
GetPlayerDialogID(playerid) return IsPlayerConnected(playerid) ? GetPVarInt(playerid, PV_PLAYER_DIALOGID) : -1;
//--------------------------------------------------------------
HidePlayerDialog(playerid) {
	SetPVarInt(playerid, PV_PLAYER_DIALOGID, -1);
	ShowPlayerDialog(playerid, -1, DIALOG_STYLE_MSGBOX, " ", " ", " ", "");
}
//--------------------------------------------------------------
IsValidPlayerDialogID(playerid, dialogid) {
	return dialogid == GetPlayerDialogID(playerid) ? 1 : 0;
}
//==============================================================
#define PV_PLAYER_BACK_DIALOGID	"PlayerBackDialogID"
ShowPlayerInfoDialog(playerid, backid, head[], info[]) {
	SetPVarInt(playerid, PV_PLAYER_BACK_DIALOGID, backid);
	ShowPlayerDialogEx(playerid, DIALOG_INFO, DIALOG_STYLE_MSGBOX, head, info, "Wroc", "");
	return 1;
}
//--------------------------------------------------------------
GetPlayerBackDialogID(playerid) return GetPVarInt(playerid, PV_PLAYER_BACK_DIALOGID);
//--------------------------------------------------------------
BackPlayerDialog(playerid, backid) {
	switch(backid) {
		case BACK_PLAYER_ACC_MENU: 			ShowPlayerAccountMenu(playerid);
		case BACK_ALOG_MENU: 				aLogLogin(playerid);
		case BACK_PLAYER_ACC_SETTINGS:	 	PlayerAccountSettings(playerid, -1);
		case BACK_ADMIN_LIST: 				ShowPlayerAdminList(playerid);
		case BACK_LDL: 						LastDisconnectList(playerid, GetPlayerPage(playerid));
		case BACK_LDL_INFO:					LastDisconnectList(playerid, GetPlayerPage(playerid), GetHelpVarValue(playerid, 0));
		case BACK_NADMIN_PANEL: 			ShowNormalAdminPanel(playerid);
		case BACK_TIME_BAN_LIST: 			ShowPlayerTimeBanList(playerid, GetPlayerPage(playerid));
		case BACK_TIME_BAN_MENU:			PlayerTBanMenuResponse(playerid);
		case BACK_TIME_SEARCH_MENU: 		PlayerTBanSearch(playerid);
		case BACK_SEARCH_LIST:				AdminListSearch(playerid);
		case BACK_HAPANEL_BASE:				HABaseMenu(playerid);
		case BACK_HAPANEL_BASEDELETE:		HSBaseDeleteBasesList(playerid);
		case BACK_HAPANEL:					HAPanelStart(playerid);
		case BACK_SETTING_MENU:				HAServerSettings(playerid, -1);
		case BACK_SETTING_SERVER_MENU:		ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);
		case BACK_ACC_REGISTER:				HAPanelAccRegisterNick(playerid);
		case BACK_ADMIN_DATA:				HACheckDataMenu(playerid);
		case BACK_HA_DATA_CHECK_LIST:		HACheckDataList(playerid, GetPlayerPage(playerid));
		case BACK_HA_DATA_SEARCH: 			HACheckDataSearch(playerid);
		case BACK_HA_BAN_MENU:				HAPanelStaticBan(playerid);
		case BACK_HA_BAN_SEARCH:			HAPanelStaticBanSearch(playerid);
		case BACK_HA_BAN_LIST:				HAStaticBanList(playerid, GetPlayerPage(playerid));
		case BACK_HA_REGISTER_MENU:			HAPanelRegisterBase(playerid);
		case BACK_HA_REGISTER_LIST:			HARegisterBaseList(playerid, GetPlayerPage(playerid));
		case BACK_HA_REGISTER_SEARCH:		HAPanelRegisterBaseSearch(playerid);
		case BACK_HA_ACCOUNT_SEARCH: {
											if(GetHelpVarValue(playerid, 98) == 0) HAPanelPlayerAccount(playerid);
											else HAVipPlayersList(playerid);
		}
		case BACK_HA_ACCOUNT_MENU:			HAPanelPlayerAccountMenu(playerid);
		case BACK_SETTING_SCRIPT_MENU:		ShowPlayerSettingsMenu(playerid, 8, -1);
		case BACK_SETTINGS_PMFP_SETTINGS:	PlayerPMFPSettings(playerid);
		case BACK_PLAYER_ACC_VIP_MENU:		PlayerAccountVIPSettings(playerid, -1);
		case BACK_HA_ACCOUNT_VIPMENU:		HAPanelPlayerVIPPremiumMenu(playerid);
		case BACK_VIPMENU_MENU:				HAVipMenu(playerid);
		case BACK_VIPMENU_SEARCH:			HAPanelVipPlayersSearch(playerid);
		case BACK_ADMIN_HELP_MENU:			AdminHelpMenu(playerid, -1);
		case BACK_ADMIN_HELP_CMDS_MENU:		AdminSystemCommandsHelp(playerid);
		case BACK_ADMIN_INFO_MENU:			ShowPlayerInfoMenu(playerid);
		case BACK_HELP_MENU:				ShowPlayerHelp(playerid, -1);
		case BACK_HELP_CMD_MENU:			ShowPlayerSystemCommands(playerid);
		case BACK_AC_WEAPONS_INFO:			ShowPlayerSettingsMenu(playerid, 90, -1);
		default: return 0;		
	}
	return 1;
}
//==============================================================
#define D_CAPTCHA_HA_CYCLICOPERATIONS	1
#define	D_CAPTCHA_HA_DELETEBASE			2
#define D_CAPTCHA_HA_ACCRESET			3
#define D_CAPTCHA_HA_UNBAN_STATIC		4
#define D_CAPTCHA_HA_PANEL_RESET_ALOG	5
#define	D_CAPTCHA_HA_PSTAT_RESET		6
#define	D_CAPTCHA_VIP_CONFIRM			7
#define	D_CAPTCHA_HA_ACCDELETE			24
#define	D_CAPTCHA_PREMIUM_SEND			8
#define D_CAPTCHA_HA_DAILYRESET			9
//--------------------------------------------------------------
#define MAX_INVALID_CAPTCHA		5
#define PV_CAPTCHA_BACK		"PVCaptchaBack"
//--------------------------------------------------------------
new PlayerCaptchaCode[MAX_PLAYERS];
new PlayerCaptchaError[MAX_PLAYERS];
new PlayerCaptchaTimer[MAX_PLAYERS];
//--------------------------------------------------------------
forward OnPlayerConfirmCaptcha(playerid, success, bool:dresponse);
//--------------------------------------------------------------
SetPlayerCapthaCode(playerid) {
	PlayerCaptchaCode[playerid] = randomly(10000, 99999);
	return _TRUE;
}
//--------------------------------------------------------------
ShowPlayerCaptcha(playerid, backid, captcha_time = 0) {
	new string[256];
	SetPlayerCapthaCode(playerid);
	SetPlayerCaptchaBackID(playerid, backid);
	
	format(string, sizeof(string), "System wymaga zebys potwierdzil swoj wybor lub udowodnil,\n        ze nie jestes botem. Przepisz prosze ponizsze cyfry\n\t          w wolne pole i kliknij 'Potwierdz'.\n\n\t\t\tCaptcha: "TEXT_DIALOG_ALERT"%d\n ", PlayerCaptchaCode[playerid]);
	
	if(captcha_time > 0) {
		KillCaptchaTimer(playerid);
		PlayerCaptchaTimer[playerid] = SetTimerEx("CaptchaEndTime", captcha_time * 1000, 0, "d", playerid);
	}
	
	ShowPlayerDialogEx(playerid, DIALOG_CAPTCHA_CODE, DIALOG_STYLE_INPUT, "Captcha", string, "Potwierdz", "Anuluj");
	return _TRUE;
}
//--------------------------------------------------------------
SetPlayerCaptchaBackID(playerid, backid) SetPVarInt(playerid, PV_CAPTCHA_BACK, backid);
GetPlayerCaptchaBackID(playerid) return GetPVarInt(playerid, PV_CAPTCHA_BACK);
//--------------------------------------------------------------
PlayerConfirmCaptcha(playerid, captcha[]) {
	if(strlen(captcha) == 5 and isNumeric(captcha) and PlayerCaptchaCode[playerid] == strval(captcha)) {
		PlayerCaptchaError[playerid] = 0;
		KillCaptchaTimer(playerid);
		OnPlayerConfirmCaptcha(playerid, 1, true);		
		return _TRUE;
	} else {
		if(++ PlayerCaptchaError[playerid] >= MAX_INVALID_CAPTCHA) {
			KillCaptchaTimer(playerid);
			PlayerCaptchaError[playerid] = 0;
			OnPlayerConfirmCaptcha(playerid, 0, true);
		} else ShowPlayerCaptcha(playerid, GetPlayerCaptchaBackID(playerid));
	}
	return _FALSE;
}
//--------------------------------------------------------------
KillCaptchaTimer(playerid) {
	KillTimer(PlayerCaptchaTimer[playerid]);
	PlayerCaptchaTimer[playerid] = 0;
	return _TRUE;
}
//--------------------------------------------------------------
forward CaptchaEndTime(playerid);
public CaptchaEndTime(playerid) {
	OnPlayerConfirmCaptcha(playerid, 0, false);
	return _TRUE;
}
//==============================================================
#define PV_YESNO_DIALOG_BACK	"PlayerDialogYesNoBack"
//--------------------------------------------------------------
#define	D_YESNO_AUTOLOG				1
#define D_YESNO_SET_SAMPLOG			2
#define D_YESNO_SET_CHATLOG			3
#define D_YESNO_SET_PLAYERLOG		4
#define	D_YESNO_SET_NICKLOG			5
#define	D_YESNO_SET_CONNLOG			6
#define	D_YESNO_SET_ACCDELLOG		7
#define	D_YESNO_SET_BANLOG			8
#define	D_YESNO_SET_MULTIACCLOG		9
#define	D_YESNO_SET_RESETLOG		10
#define	D_YESNO_SET_COPYDELACC		11
#define	D_YESNO_SET_REGOBLIG		12
#define D_YESNO_SET_CAPTCHAPROT		13
#define	D_YESNO_SET_REMOTECON		14
#define	D_YESNO_SET_BASE			15
#define	D_YESNO_SET_AUTOCYCLIC		16
#define	D_YESNO_SET_AUTOACCRES		17
#define D_YESNO_HA_CYCLICOPERATIONS	18
#define	D_YESNO_HA_DELETEBASE		19
#define	D_YESNO_HA_ACCRESET			20
#define D_YESNO_HA_REGISTER			21
#define D_YESNO_HA_SBAN_CONFIRM		22
#define	D_YESNO_HA_PSTAT_RESET		23
#define	D_YESNO_HA_ACCDELETE		24
#define	D_YESNO_SET_RCON_ACCOUNT	25
#define	D_YESNO_HA_RCONACCOUNT		26
#define	D_YESNO_SET_CON_DIS			27
#define	D_YESNO_SET_CENSURE_MUTE	28
#define	D_YESNO_SET_ANTYSPAM		29
#define	D_YESNO_SET_ANTYFLOOD		30
#define	D_YESNO_PLAYERCENSURE		31
#define	D_YESNO_PLAYERGLOBPRIV		32
#define	D_YESNO_PLAYERSPECPRIV		33
#define	D_YESNO_SET_PRIVMESSAGES	34
#define	D_YESNO_SET_ADMINLIMITS		35
#define	D_YESNO_SET_VIPLIMITS		36
#define	D_YESNO_SET_VIPLOG			37
#define	D_YESNO_SET_VIPTIMEBAN		38
#define	D_YESNO_HA_PANEL_VIP_POINTS	39
#define	D_YESNO_HA_PANEL_VIP_TIME	40
#define	D_YESNO_HA_VIPMENU_POINTS	41
#define	D_YESNO_HA_VIPMENU_TIME		42
#define	D_YESNO_PREMIUM_SEND		43
#define D_YESNO_AC_WEAPONS			45
#define	D_YESNO_AC_JETPACK			46
#define D_YESNO_AC_REJOIN			47
#define D_YESNO_AC_SAMEIP			48
#define D_YESNO_AC_CHATSPAMBOT		49
#define D_YESNO_AC_CMDSPAMBOT		50
#define D_YESNO_AC_FAKEKILLSPAMBOT	51
#define D_YESNO_AC_SAMPMONEY		52
#define D_YESNO_AC_GODMODE			53
#define D_YESNO_HA_DAILYRESET		54
#define	D_YESNO_AUTO_DAILY_RESET	55
//==============================================================
ShowPlayerYesNoDialog(playerid, backid, head[], info[]) {
	SetPVarInt(playerid, PV_YESNO_DIALOG_BACK, backid);
	ShowPlayerDialogEx(playerid, DIALOG_YESNO, DIALOG_STYLE_MSGBOX, head, info, "Tak", "Nie");	
	return _TRUE;
}
//--------------------------------------------------------------
DialogYesNoResponse(playerid, response) {
	switch(GetPVarInt(playerid, PV_YESNO_DIALOG_BACK)) {
		case D_YESNO_AUTOLOG: {
			SetPVarInt(playerid, PV_SET_RECONNECT, response);
			PlayerAccountSettings(playerid, -1);
		}	
		case D_YESNO_SET_SAMPLOG: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			if(response) {
				SetChatLoggingStatus(true);
				setSettingIntValueByIndex(s_SAMPChatID, 1);
			} else {
				SetChatLoggingStatus(false);
				setSettingIntValueByIndex(s_SAMPChatID, 0);			
			}
			ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);
		}
		case D_YESNO_SET_CHATLOG: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			setSettingIntValueByIndex(s_LogChatID, response ? 1 : 0);	
			ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);
		}
		case D_YESNO_SET_PLAYERLOG: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			setSettingIntValueByIndex(s_LogPlayersID, response ? 1 : 0);	
			ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);		
		}
		case D_YESNO_SET_NICKLOG: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			setSettingIntValueByIndex(s_LogNickChangeID, response ? 1 : 0);	
			ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);				
		}
		case D_YESNO_SET_CONNLOG: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			setSettingIntValueByIndex(s_LogPlayerInfoID, response ? 1 : 0);	
			ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);		
		}
		case D_YESNO_SET_ACCDELLOG: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			setSettingIntValueByIndex(s_LogDeletingInfoID, response ? 1 : 0);	
			ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);			
		}		
		case D_YESNO_SET_BANLOG: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			setSettingIntValueByIndex(s_LogBanInfoID, response ? 1 : 0);	
			ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);			
		}
		case D_YESNO_SET_VIPLOG: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			setSettingIntValueByIndex(s_LogVIPInfoID, response ? 1 : 0);	
			ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);			
		}	
		case D_YESNO_SET_MULTIACCLOG: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			setSettingIntValueByIndex(s_LogMultiAccountInfoID, response ? 1 : 0);	
			ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);			
		}
		case D_YESNO_SET_RESETLOG: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			setSettingIntValueByIndex(s_LogResetInfoID, response ? 1 : 0);	
			ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);			
		}
		case D_YESNO_SET_COPYDELACC: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			setSettingIntValueByIndex(s_CopyDeletingID, response ? 1 : 0);	
			ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);			
		}		
		case D_YESNO_SET_REGOBLIG: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			setSettingIntValueByIndex(s_RegisterObligatoryID, response ? 1 : 0);
			ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);		
		}
		case D_YESNO_SET_CAPTCHAPROT: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			setSettingIntValueByIndex(s_StartingCaptchaID, response ? 1 : 0);
			ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);		
		}
		case D_YESNO_SET_REMOTECON: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			if(response) {
				SetRemoteConsoleStatus(true);
				setSettingIntValueByIndex(s_SAMPRemoteID, 1);
			} else {
				SetRemoteConsoleStatus(false);
				setSettingIntValueByIndex(s_SAMPRemoteID, 0);			
			}
			ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);			
		}	
		case D_YESNO_SET_BASE: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			// response == 1 - baza mysql on | response == 0 - baza mysql off
			ChangeBaseType = (response != getSettingIntValueByIndex(s_MySQLID) ? true : false);
			if(ChangeBaseType == true) ShowPlayerInfoDialog(playerid, BACK_SETTING_SERVER_MENU, "Ustawienia serwera - Ustawienia administracyjne", "\t         Uzywany typ bazy danych zostanie zmieniony po restarcie systemu.\nZaleca sie, oprocz wykonania restartu admin systemu, wykonanie rowniez restartu gamemoda.\n");
			else ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);
		}
		case D_YESNO_SET_AUTOCYCLIC: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			setSettingIntValueByIndex(s_AutomaticCyclicOps, response ? 1 : 0);	
			ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);	
		}
		case D_YESNO_SET_AUTOACCRES: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;			
			setSettingIntValueByIndex(s_AutomaticAccReset, response ? 1 : 0);	
			ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);			
		}
		case D_YESNO_SET_RCON_ACCOUNT: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;	
			setSettingIntValueByIndex(s_RCONAccountsID, response ? 1 : 0);	
			ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);	
		}
		case D_YESNO_SET_CON_DIS: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			setSettingIntValueByIndex(s_ConDisInfoID, response ? 1 : 0);	
			ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);		
		}			
		case D_YESNO_SET_CENSURE_MUTE: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			setSettingIntValueByIndex(s_CensureMuteStatusID, response ? 1 : 0);	
			ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);			
		}
		case D_YESNO_SET_ANTYSPAM: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			setSettingIntValueByIndex(s_AntySpamStatusID, response ? 1 : 0);	
			ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);			
		}
		case D_YESNO_SET_ANTYFLOOD: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			setSettingIntValueByIndex(s_AntyFloodStatusID, response ? 1 : 0);	
			ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);			
		}		
		case D_YESNO_HA_CYCLICOPERATIONS: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			if(response) ShowPlayerCaptcha(playerid, D_CAPTCHA_HA_CYCLICOPERATIONS);
			else HABaseMenu(playerid);
		}
		case D_YESNO_HA_DELETEBASE: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			if(response) ShowPlayerCaptcha(playerid, D_CAPTCHA_HA_DELETEBASE);
			else HSBaseDeleteBasesList(playerid);		
		}
		case D_YESNO_HA_ACCRESET: {
			if(IsAdmin(playerid) < ALVL_HEAD_ADMIN) return _FALSE;
			if(response) ShowPlayerCaptcha(playerid, D_CAPTCHA_HA_ACCRESET);
			else HAStatisticsReset(playerid);				
		}
		case D_YESNO_HA_DAILYRESET: {
			if(IsAdmin(playerid) < ALVL_HEAD_ADMIN) return _FALSE;
			if(response) ShowPlayerCaptcha(playerid, D_CAPTCHA_HA_DAILYRESET);
			else HAStatisticsReset(playerid);				
		}
		case D_YESNO_HA_REGISTER: {
			if(IsAdmin(playerid) < ALVL_HEAD_ADMIN) return _FALSE;
			if(response) HAPanelRegisterNewAccount(playerid, GetHelpStringValue(playerid, 0), GetHelpStringValue(playerid, 1));
			else HAPanelAccRegisterNick(playerid);		
		}
		case D_YESNO_HA_SBAN_CONFIRM: {
			if(IsAdmin(playerid) < ALVL_HEAD_ADMIN) return _FALSE;
			if(response) HAPanelStaticBanAddConfirm(playerid, true);
			else HAPanelStaticBan(playerid);					
		}
		case D_YESNO_HA_PSTAT_RESET: {
			if(IsAdmin(playerid) < ALVL_HEAD_ADMIN) return _FALSE;
			if(response) ShowPlayerCaptcha(playerid, D_CAPTCHA_HA_PSTAT_RESET);
			else HAPanelPlayerAccountMenu(playerid);				
		}
		case D_YESNO_HA_ACCDELETE: {
			if(IsAdmin(playerid) < ALVL_GAME_MASTER) return _FALSE;
			if(response) ShowPlayerCaptcha(playerid, D_CAPTCHA_HA_ACCDELETE);
			else HAPanelPlayerAccountMenu(playerid);		
		}
		case D_YESNO_HA_RCONACCOUNT: {
			if(IsAdmin(playerid) < ALVL_GAME_MASTER) return _FALSE;
			if(response) HSPanelRCONAccount(playerid, true);
			else HAPanelPlayerAccountMenu(playerid);			
		}
		case D_YESNO_PLAYERCENSURE: {
			if(response) setPlayerCensureStatus(playerid, true);
			else setPlayerCensureStatus(playerid, false);
			PlayerAccountSettings(playerid, -1);
		}
		case D_YESNO_PLAYERGLOBPRIV: {
			if(response) SetPlayerPMessagesStatus(playerid, true);
			else SetPlayerPMessagesStatus(playerid, false);
			PlayerPrivMessagesSettings(playerid);			
		}
		case D_YESNO_PLAYERSPECPRIV: {
			if(response) SetPlayerPMessagesSpec(playerid, true);
			else SetPlayerPMessagesSpec(playerid, false);
			PlayerPrivMessagesSettings(playerid);				
		}
		case D_YESNO_SET_PRIVMESSAGES: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			setSettingIntValueByIndex(s_PrivMessagesID, response ? 1 : 0);	
			ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);			
		}
		case D_YESNO_SET_ADMINLIMITS: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			setSettingIntValueByIndex(s_AdminLimitsID, response ? 1 : 0);	
			ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);				
		}
		case D_YESNO_SET_VIPLIMITS: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			setSettingIntValueByIndex(s_VIPLimitsID, response ? 1 : 0);	
			ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);				
		}
		case D_YESNO_SET_VIPTIMEBAN: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			setSettingIntValueByIndex(s_VIPTimeBanID, response ? 1 : 0);	
			ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);					
		}
		case D_YESNO_HA_PANEL_VIP_POINTS: {
			if(response) HAPanelPlayerVIPPremiumConfirm(playerid, true);					
			else HAPanelPlayerVIPPremiumPoints(playerid);
		}
		case D_YESNO_HA_PANEL_VIP_TIME: {
			if(response) HAPanelPlayerVIPTimeConfirm(playerid, true);					
			else HAPanelPlayerVIPAccount(playerid);		
		}
		case D_YESNO_HA_VIPMENU_POINTS: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			if(response) HAPanelVIPMenuPremiumConfirm(playerid, true);
			else HAPanelVipPoints(playerid);				
		}
		case D_YESNO_HA_VIPMENU_TIME: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			if(response) HAPanelVIPMenuTimeConfirm(playerid, true);
			else HAPanelVipTime(playerid);			
		}
		case D_YESNO_PREMIUM_SEND: {
			if(response) ShowPlayerCaptcha(playerid, D_CAPTCHA_PREMIUM_SEND);
			else SendPremiumPointsPlayer(playerid);					
		}
		case D_YESNO_AC_WEAPONS: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			setSettingIntValueByIndex(s_ACAntyWeaponStatusID, response ? 1 : 0);
			ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);			
		}		
		case D_YESNO_AC_JETPACK: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			setSettingIntValueByIndex(s_ACAntyJetpackStatusID, response ? 1 : 0);
			ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);			
		}		
		case D_YESNO_AC_REJOIN: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			setSettingIntValueByIndex(s_ACAntyReJoinSpamStatusID, response ? 1 : 0);
			ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);			
		}
		case D_YESNO_AC_SAMEIP: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			setSettingIntValueByIndex(s_ACConnectionSpamBotStatusID, response ? 1 : 0);
			ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);				
		}
		case D_YESNO_AC_CHATSPAMBOT: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			setSettingIntValueByIndex(s_ACAntySpamBotStatusID, response ? 1 : 0);
			ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);				
		}
		case D_YESNO_AC_CMDSPAMBOT: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			setSettingIntValueByIndex(s_ACAntyCMDSpamBotStatusID, response ? 1 : 0);
			ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);				
		}
		case D_YESNO_AC_FAKEKILLSPAMBOT: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			setSettingIntValueByIndex(s_ACAntyFakeKillSpamBotStatusID, response ? 1 : 0);
			ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);				
		}
		case D_YESNO_AC_SAMPMONEY: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			setSettingIntValueByIndex(s_ACAntyMoneyHackStatusID, response ? 1 : 0);
			ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);				
		}	
		case D_YESNO_AC_GODMODE: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			setSettingIntValueByIndex(s_ACAntyGodmodeStatusID, response ? 1 : 0);
			ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);				
		}
		case D_YESNO_AUTO_DAILY_RESET: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			setSettingIntValueByIndex(s_AutoDailyStatsReset, response ? 1 : 0);
			ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);					
		}
		
		default: return _FALSE;
	}
	return _TRUE;
}
//==============================================================
#define PV_VALUE_DIALOG_BACK	"PVValueDialogBack"
//--------------------------------------------------------------
#define D_VALUE_SET_NACTIVE_ADMIN_INFO		0
#define D_VALUE_SET_PLAYER_INFO				1
#define D_VALUE_SET_NICK_CHANGE_INFO		2
#define D_VALUE_SET_STARTING_CAPTCHA_TIME	3
#define D_VALUE_SET_REGISTER_MIN_TIME		4
#define D_VALUE_SET_REGISTER_CONFI			5
#define D_VALUE_SET_LOGIN_TIME				6
#define D_VALUE_SET_LOGIN_FAIL				7
#define D_VALUE_SET_ALOG_LOGIN_FAIL			8
#define D_VALUE_SET_RECONNECT_MAX_TIME		9	
#define D_VALUE_SET_NICK_CHANGE_TIME		10	
#define D_VALUE_SET_ACC_DELETING_TIME		11
#define D_VALUE_SET_CONFI_TIME				12
#define D_VALUE_SET_RESET_HOUR				13
#define D_VALUE_SET_NACTIVE_ADMIN_DELETE	14
#define D_VALUE_SET_JADMIN_BLOCK_TIME		15
#define D_VALUE_SET_ADMIN_BLOCK_TIME		16
#define	D_VALUE_SET_AUTOACCRES_DAY			17
#define	D_VALUE_SET_RCON_FAIL				18
#define	D_BALUE_SET_MUTE_CENSURE_TIME		19
#define	D_BALUE_SET_MUTE_MAX_WARNINGS		20
#define D_BALUE_SET_ANTYSPAM_MIN_SEC		21
#define	D_BALUE_SET_ANTYFLOOD_MIN_SEC		22
#define	D_VALUE_SET_MAX_PING				23
#define	D_VALUE_SET_MIN_FPS					24
#define	D_VALUE_SET_MAX_PLOSS				25
#define	D_VALUE_SET_MAX_PING_WARNINGS		26
#define	D_VALUE_SET_MIN_FPS_WARNINGS		27
#define	D_VALUE_SET_MAX_PLOSS_WARNINGS		28
#define	D_VALUE_SET_VIP_REG_TIME			29
#define	D_VALUE_SET_VIP_REG_POINTS			30
#define	D_VALUE_SET_VIP_3					31
#define	D_VALUE_SET_VIP_7					32
#define	D_VALUE_SET_VIP_30					33
#define	D_VALUE_SET_MUTE_TIME				35
#define D_VALUE_SET_AC_SAMEIP				36
#define D_VALUE_SET_AC_CHATSPAMBOT			37
#define D_VALUE_SET_AC_CMDSPAMBOT			38
#define D_VALUE_SET_AC_FAKEKILLSPAMBOT		39
#define D_VALUE_SET_AC_REJOIN				40
#define D_VALUE_SET_AC_GODMODE_WARNINGS		41
#define D_VALUE_SET_AC_GODMODE_TICKS		42
#define	D_VALUE_SET_PINGGPSPLOSS_FREQUENCY	43
#define	D_VALUE_SET_CRITICAL_PLOSS			44
#define	D_VALUE_SET_CRITICAL_PING			45
//==============================================================
ShowPlayerValueDialogBack(playerid, backid, s_value[] = "", bool:response_false = false) {
	new head[64], string[600];
	new value, bool:set_value;
	if(11 > strlen(s_value) > 0 and isNumeric(s_value) == _TRUE) {
		value = strval(s_value);
		set_value = true;
	}
	SetPVarInt(playerid, PV_VALUE_DIALOG_BACK, backid);
	switch(backid) {
		case D_VALUE_SET_NACTIVE_ADMIN_INFO: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			else if(response_false == true) return ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);	
			else if(set_value == true) {
				if(getSettingIntMinValueByIndex(s_NonActiveAdminInfoID) <= value <= getSettingIntMaxValueByIndex(s_NonActiveAdminInfoID)) {
					setSettingIntValueByIndex(s_NonActiveAdminInfoID, value);
					strins(string, C_LIGHTGREEN"\t\t           Nowa wartosc zostala poprawnie ustawiona.", 0);
				} else strins(string, TEXT_DIALOG_ALERT"\t        Podana wartosc nie miesci sie w dopuszczalnym przedziale.", 0);
			}	
			strins(head, "Ustawienia logow - Info. o nieaktywnym administratorze", 0);
			format(string, sizeof(string), "W tym menu mozesz ustalic czas, po ktorym w menu listy administratorow (CMD: /alist)\n   pojawi sie informacja o nieaktywnym administratorze. Czas jest podawany w dniach\n\t\t     i musi zawierac sie w przedziale od %d do %d dni.\n\n%s", getSettingIntMinValueByIndex(s_NonActiveAdminInfoID), getSettingIntMaxValueByIndex(s_NonActiveAdminInfoID), string);
		}
		case D_VALUE_SET_PLAYER_INFO: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			else if(response_false == true) return ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);	
			else if(set_value == true) {
				if(getSettingIntMinValueByIndex(s_PlayerInfoMaxTimeID) <= value <= getSettingIntMaxValueByIndex(s_PlayerInfoMaxTimeID)) {
					setSettingIntValueByIndex(s_PlayerInfoMaxTimeID, value);
					strins(string, C_LIGHTGREEN"\t\t        Nowa wartosc zostala poprawnie ustawiona.", 0);
				} else strins(string, TEXT_DIALOG_ALERT"\t        Podana wartosc nie miesci sie w dopuszczalnym przedziale.", 0);			
			}		
			strins(head, "Ustawienia logow - Przechowywanie info. o graczach", 0);
			format(string, sizeof(string), "jak dlugo maja byc przechowywane informacje o graczach. Czas jest podawany w dniach\n\t\t      i musi zawierac sie w przedziale od %d do %d dni.\nInformacja: Dane sa usuwane tylko z bazy danych, nie z pliku tekstowego wiec w razie\n\t\t\t       potrzeby mozna je tam znalezc.\n\n%s", getSettingIntMinValueByIndex(s_PlayerInfoMaxTimeID), getSettingIntMaxValueByIndex(s_PlayerInfoMaxTimeID), string);
			format(string, sizeof(string), "Informacje o kazdym graczu wchodzacym na serwer sa przechowywane w bazie danych.\n Jednak po pewnym czasie dane staja sie przestarzale, lub nieuzywane przez co nie ma\npotrzeby ich dalszego przechowywania w bazie danych. Ta opcja pozwala na okreslenie\n%s", string);
			
		}
		case D_VALUE_SET_NICK_CHANGE_INFO: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			else if(response_false == true) return ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);	
			else if(set_value == true) {
				if(getSettingIntMinValueByIndex(s_NickChangeMaxTimeID) <= value <= getSettingIntMaxValueByIndex(s_NickChangeMaxTimeID)) {
					setSettingIntValueByIndex(s_NickChangeMaxTimeID, value);
					strins(string, C_LIGHTGREEN"\t\t        Nowa wartosc zostala poprawnie ustawiona.", 0);
				} else strins(string, TEXT_DIALOG_ALERT"\t        Podana wartosc nie miesci sie w dopuszczalnym przedziale.", 0);			
			}	
			strins(head, "Ustawienia logow - Przechowywanie info. o zmianie nicku", 0);
			format(string, sizeof(string),"Ta opcja umozliwia\n    okreslenie, jak dlugo maja byc przechowywane informacje o zmianach nicku konta\n gracza. Czas jest podawany w dniach i musi zawierac sie w przedziale od %d do %d dni.\n\tInformacja: Dane usuwane sa wylacznie z bazy danych, nie z pliku logow.\n\n%s", getSettingIntMinValueByIndex(s_NickChangeMaxTimeID), getSettingIntMaxValueByIndex(s_NickChangeMaxTimeID), string);
			format(string, sizeof(string), "    Informacje o zmianach nicku na koncie gracza sa przechowywane w bazie danych.\n    Po pewnym czasie jednak, dane te staja sie przestarzale i nieuzywane co pozwala\nna ich usuniecie i oczyszczenie bazy danych z zbednych informacji.%s", string);
		}
		case D_VALUE_SET_STARTING_CAPTCHA_TIME: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			else if(response_false == true) return ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);	
			else if(set_value == true) {
				if(getSettingIntMinValueByIndex(s_StartingCaptchaTimeID) <= value <= getSettingIntMaxValueByIndex(s_StartingCaptchaTimeID)) {
					setSettingIntValueByIndex(s_StartingCaptchaTimeID, value);
					strins(string, C_LIGHTGREEN"\t\t        Nowa wartosc zostala poprawnie ustawiona.", 0);
				} else strins(string, TEXT_DIALOG_ALERT"\t        Podana wartosc nie miesci sie w dopuszczalnym przedziale.", 0);			
			}
			strins(head, "Ustawienia logowania - Czas potwierdzenia Captha", 0);
			format(string, sizeof(string), "          W tym menu mozesz ustalic, jak duzo czasu beda mieli gracze na wpisanie\n     kodu 'Captcha' przy wejsciu na sewer w przypadku wlaczenia 'Ochrony Captcha'\nCzas jest podawany w sekundach i musi zawierac sie w przedziale od %d do %d sekund.\n\n%s", getSettingIntMinValueByIndex(s_StartingCaptchaTimeID), getSettingIntMaxValueByIndex(s_StartingCaptchaTimeID), string);
		}
		case D_VALUE_SET_REGISTER_MIN_TIME: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			else if(response_false == true) return ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);	
			else if(set_value == true) {
				if(getSettingIntMinValueByIndex(s_RegisterMinTimeID) <= value <= getSettingIntMaxValueByIndex(s_RegisterMinTimeID)) {
					setSettingIntValueByIndex(s_RegisterMinTimeID, value);
					strins(string, C_LIGHTGREEN"\t\t        Nowa wartosc zostala poprawnie ustawiona.", 0);
				} else strins(string, TEXT_DIALOG_ALERT"\t        Podana wartosc nie miesci sie w dopuszczalnym przedziale.", 0);			
			}
			strins(head, "Ustawienia rejestracji - Min. czas rejestracji", 0);
			format(string, sizeof(string), "    System zabezpiecza mozliwosc rejestracji wiecej niz jednego konta z jednego IP.\nZa pomoca tego menu mozesz ustalic jak dlugo ma trwac ochrona przed multikontami.\n   Czas jest podawany w minutach i musi zawierac sie w przedziale od %d do %d minut.\n\n%s", getSettingIntMinValueByIndex(s_RegisterMinTimeID), getSettingIntMaxValueByIndex(s_RegisterMinTimeID), string);
		}
		case D_VALUE_SET_REGISTER_CONFI: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			else if(response_false == true) return ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);	
			else if(set_value == true) {
				if(getSettingIntMinValueByIndex(s_ProvConfiRegisterID) <= value <= getSettingIntMaxValueByIndex(s_ProvConfiRegisterID)) {
					setSettingIntValueByIndex(s_ProvConfiRegisterID, value);
					strins(string, C_LIGHTGREEN"\t\t\t       Nowa wartosc zostala poprawnie ustawiona.", 0);
				} else strins(string, TEXT_DIALOG_ALERT"\t\t        Podana wartosc nie miesci sie w dopuszczalnym przedziale.", 0);			
			}			
			strins(head, "Ustawienia rejestracji - Warunkowy zaufany", 0);
			format(string, sizeof(string), "Za pomoca tego menu mozesz ustalic jak dlugo ma trwac 'Warunkowy status zaufanego' po rejestracji\n       konta. Czas jest podawany w godzinach i musi zawierac sie w przedziale od %d do %d godzin.\n\n%s", getSettingIntMinValueByIndex(s_ProvConfiRegisterID), getSettingIntMaxValueByIndex(s_ProvConfiRegisterID), string);
		}
		case D_VALUE_SET_LOGIN_TIME: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			else if(response_false == true) return ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);	
			else if(set_value == true) {
				if(getSettingIntMinValueByIndex(s_LoginTimeID) <= value <= getSettingIntMaxValueByIndex(s_LoginTimeID)) {
					setSettingIntValueByIndex(s_LoginTimeID, value);
					strins(string, C_LIGHTGREEN"\t\t\t        Nowa wartosc zostala poprawnie ustawiona.", 0);
				} else strins(string, TEXT_DIALOG_ALERT"\t\t        Podana wartosc nie miesci sie w dopuszczalnym przedziale.", 0);			
			}				
			strins(head, "Ustawienia logowania - Czas na zalogowanie sie", 0);
			format(string, sizeof(string), "Za pomoca tego menu mozesz ustalic jak duzo czasu ma miec gracz na zalogowanie sie na swoje konto.\n\tCzas jest podawany w sekundach i musi zawierac sie w przedziale od %d do %d sekund.\n\n%s", getSettingIntMinValueByIndex(s_LoginTimeID), getSettingIntMaxValueByIndex(s_LoginTimeID), string);
		}
		case D_VALUE_SET_LOGIN_FAIL: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			else if(response_false == true) return ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);	
			else if(set_value == true) {
				if(getSettingIntMinValueByIndex(s_LoginFailID) <= value <= getSettingIntMaxValueByIndex(s_LoginFailID)) {
					setSettingIntValueByIndex(s_LoginFailID, value);
					strins(string, C_LIGHTGREEN"\t          Nowa wartosc zostala poprawnie ustawiona.", 0);
				} else strins(string, TEXT_DIALOG_ALERT"          Podana wartosc nie miesci sie w dopuszczalnym przedziale.", 0);			
			}
			strins(head, "Ustawienia logowania - Ilosc blednych logowan", 0);
			format(string, sizeof(string), "Za pomoca tego menu mozesz ustalic jak duzo blednych prob logowania\n       na konto, moze wykonac gracz zanim zostanie usuniety z serwera.\n\t  Ilosc prob musi zawierac sie w przedziale od %d do %d.\n\n%s", getSettingIntMinValueByIndex(s_LoginFailID), getSettingIntMaxValueByIndex(s_LoginFailID), string);
		}
		case D_VALUE_SET_ALOG_LOGIN_FAIL: {//
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			else if(response_false == true) return ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);	
			else if(set_value == true) {
				if(getSettingIntMinValueByIndex(s_ALogLoginFailsID) <= value <= getSettingIntMaxValueByIndex(s_ALogLoginFailsID)) {
					setSettingIntValueByIndex(s_ALogLoginFailsID, value);
					strins(string, C_LIGHTGREEN"\t           Nowa wartosc zostala poprawnie ustawiona.", 0);
				} else strins(string, TEXT_DIALOG_ALERT"\tPodana wartosc nie miesci sie w dopuszczalnym przedziale.", 0);			
			}
			strins(head, "Ustawienia logowania - Ilosc blednych logowan aLog", 0);
			format(string, sizeof(string), "W tym menu mozesz ustalic jak duzo nieudanych prob logowania na konto\n    aLog moze dokonac administrator, zanim zostanie usuniety z serwera.\n\t     Ilosc prob musi zawierac sie w przedziale od %d do %d.\n\n%s", getSettingIntMinValueByIndex(s_ALogLoginFailsID), getSettingIntMaxValueByIndex(s_ALogLoginFailsID), string);
		}
		case D_VALUE_SET_RECONNECT_MAX_TIME: {//s_ReconnectMaxTimeID
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			else if(response_false == true) return ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);	
			else if(set_value == true) {
				if(getSettingIntMinValueByIndex(s_ReconnectMaxTimeID) <= value <= getSettingIntMaxValueByIndex(s_ReconnectMaxTimeID)) {
					setSettingIntValueByIndex(s_ReconnectMaxTimeID, value);
					strins(string, C_LIGHTGREEN"\t           Nowa wartosc zostala poprawnie ustawiona.", 0);
				} else strins(string, TEXT_DIALOG_ALERT"\t  Podana wartosc nie miesci sie w dopuszczalnym przedziale.", 0);			
			}	
			strins(head, "Ustawienia logowania - Max. czas na autologowanie", 0);
			format(string, sizeof(string), 
				"   System umozliwia dokonanie autologowania na konto gracza, jesli jego\n dane (IP, GPCI) nie ulegly zmianie. Jednak, ze wzgledow bezpieczenstwa\nmozliwosc autologowania zostala ograniczona do kilku minut. W tym menu\n   mozesz ustalic jak dlugo ma trwac mozliwosc autologowania. Czas jest\n  podawany w minutach i musi zawierac sie w przedziale od %d do %d minut.\n\n%s",  
				getSettingIntMinValueByIndex(s_ReconnectMaxTimeID), getSettingIntMaxValueByIndex(s_ReconnectMaxTimeID), string);
		}
		case D_VALUE_SET_NICK_CHANGE_TIME: {//s_NickChangeTimeID
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			else if(response_false == true) return ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);	
			else if(set_value == true) {
				if(getSettingIntMinValueByIndex(s_NickChangeTimeID) <= value <= getSettingIntMaxValueByIndex(s_NickChangeTimeID)) {
					setSettingIntValueByIndex(s_NickChangeTimeID, value);
					strins(string, C_LIGHTGREEN"\t\t        Nowa wartosc zostala poprawnie ustawiona.", 0);
				} else strins(string, TEXT_DIALOG_ALERT"\t        Podana wartosc nie miesci sie w dopuszczalnym przedziale.", 0);			
			}	
			strins(head, "Ustawienia obslugi kont - Zmiana nicku", 0);
			format(string, sizeof(string), "W tym menu mozesz ustalic co ile czasu gracz moze zmienic swoj zarejestrowany nick.\n      Czas jest podawany w dniach i musi zawierac sie w przedziale od %d do %d dni.\n\n%s", getSettingIntMinValueByIndex(s_NickChangeTimeID), getSettingIntMaxValueByIndex(s_NickChangeTimeID), string);
		}
		case D_VALUE_SET_ACC_DELETING_TIME: {//s_LoginDeletingDaysID
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			else if(response_false == true) return ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);	
			else if(set_value == true) {
				if(getSettingIntMinValueByIndex(s_LoginDeletingDaysID) <= value <= getSettingIntMaxValueByIndex(s_LoginDeletingDaysID)) {
					setSettingIntValueByIndex(s_LoginDeletingDaysID, value);
					strins(string, C_LIGHTGREEN"\t\t\t\t    Nowa wartosc zostala poprawnie ustawiona.", 0);
				} else strins(string, TEXT_DIALOG_ALERT"\t\t\t      Podana wartosc nie miesci sie w dopuszczalnym przedziale.", 0);			
			}
			strins(head, "Ustawienia obslugi kont - Usuwanie nieaktywnych kont", 0);	
			format(string, sizeof(string), "Nieuzywane konta graczy, sa usuwane z systemu. W tym menu mozesz okreslic ile dni musi uplynac od ostatniego\n    logowania na konto gracza do momentu jego usuniecia. Czas musi zawierac sie w przedziale od %d do %d dni.\n\n%s", getSettingIntMinValueByIndex(s_LoginDeletingDaysID), getSettingIntMaxValueByIndex(s_LoginDeletingDaysID), string);
		}
		case D_VALUE_SET_CONFI_TIME: {//s_LoginConfiID
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			else if(response_false == true) return ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);	
			else if(set_value == true) {
				if(getSettingIntMinValueByIndex(s_LoginConfiID) <= value <= getSettingIntMaxValueByIndex(s_LoginConfiID)) {
					setSettingIntValueByIndex(s_LoginConfiID, value);
					strins(string, C_LIGHTGREEN"\t\t        Nowa wartosc zostala poprawnie ustawiona.", 0);
				} else strins(string, TEXT_DIALOG_ALERT"\t        Podana wartosc nie miesci sie w dopuszczalnym przedziale.", 0);			
			}
			strins(head, "Ustawienia obslugi kont - Czas gry do pelnego zaufanego", 0);
			format(string, sizeof(string), "W tym menu mozesz ustalic ile godzin gracz musi spedzic na serwerze zeby otrzymac\n       status 'Zaufanego'. Czas musi zawierac sie w przedziale od %d do %d godzin.\n\n%s", getSettingIntMinValueByIndex(s_LoginConfiID), getSettingIntMaxValueByIndex(s_LoginConfiID), string);
		}
		case D_VALUE_SET_RESET_HOUR: {//s_ResetTimeID
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			else if(response_false == true) return ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);	
			else if(set_value == true) {
				if(getSettingIntMinValueByIndex(s_ResetTimeID) <= value <= getSettingIntMaxValueByIndex(s_ResetTimeID)) {
					setSettingIntValueByIndex(s_ResetTimeID, value);
					strins(string, C_LIGHTGREEN"\t\t        Nowa wartosc zostala poprawnie ustawiona.", 0);
				} else strins(string, TEXT_DIALOG_ALERT"\t        Podana wartosc nie miesci sie w dopuszczalnym przedziale.", 0);			
			}
			strins(head, "Ustawienia administracyjne - Operacje cykliczne", 0);
			format(string, sizeof(string), "W tym menu mozesz ustalic, o ktorej godzinie maja byc wykonane operacje cykliczne,\nczyli czyszczenie baz ze zbednych danych oraz w razie potrzeby wykonywany ma byc\n\t    reset kont. Godzina musi zawierac sie w przedziale od %d do %d.\n\n%s", getSettingIntMinValueByIndex(s_ResetTimeID), getSettingIntMaxValueByIndex(s_ResetTimeID), string);
		}
		case D_VALUE_SET_NACTIVE_ADMIN_DELETE: {//s_NADelAdminRightsID
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			else if(response_false == true) return ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);	
			else if(set_value == true) {
				if(getSettingIntMinValueByIndex(s_NADelAdminRightsID) <= value <= getSettingIntMaxValueByIndex(s_NADelAdminRightsID)) {
					setSettingIntValueByIndex(s_NADelAdminRightsID, value);
					strins(string, C_LIGHTGREEN"\t\t\t           Nowa wartosc zostala poprawnie ustawiona.", 0);
				} else strins(string, TEXT_DIALOG_ALERT"\t\t            Podana wartosc nie miesci sie w dopuszczalnym przedziale.", 0);			
			}
			strins(head, "Ustawienia administracyjne - Nieaktywni administratorzy", 0);
			format(string, sizeof(string), "  W tym menu mozesz ustalic po jakim czasie nieaktywnosci, maja byc zabierane przywileje administratora.\nOpcja automatycznego odbierania przywilejow administratora nie dotyczy rang Head Admin i Game Master.\n\t\t\t    Czas musi zawierac sie w przedziale od %d do %d dni.\n\n%s", getSettingIntMinValueByIndex(s_NADelAdminRightsID), getSettingIntMaxValueByIndex(s_NADelAdminRightsID), string);
		}
		case D_VALUE_SET_JADMIN_BLOCK_TIME: {//s_BanTimeJAdminID
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			else if(response_false == true) return ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);	
			else if(set_value == true) {
				if(getSettingIntMinValueByIndex(s_BanTimeJAdminID) <= value <= getSettingIntMaxValueByIndex(s_BanTimeJAdminID)) {
					setSettingIntValueByIndex(s_BanTimeJAdminID, value);
					strins(string, C_LIGHTGREEN"\t\t               Nowa wartosc zostala poprawnie ustawiona.", 0);
				} else strins(string, TEXT_DIALOG_ALERT"\t               Podana wartosc nie miesci sie w dopuszczalnym przedziale.", 0);			
			}
			strins(head, "Ustawienia administracyjne - JAdmin kick", 0);
			format(string, sizeof(string), "W tym menu mozesz ustalic na jak maksymalnie dlugo, moze wyrzucac z serwera administrator\n\tz ranga Junior Admina. Czas musi zawierac sie w przedziale od %d do %d minut.\n\n%s", getSettingIntMinValueByIndex(s_BanTimeJAdminID), getSettingIntMaxValueByIndex(s_BanTimeJAdminID), string);
		}
		case D_VALUE_SET_ADMIN_BLOCK_TIME: {//s_BanTimeAdminID
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			else if(response_false == true) return ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);	
			else if(set_value == true) {
				if(getSettingIntMinValueByIndex(s_BanTimeAdminID) <= value <= getSettingIntMaxValueByIndex(s_BanTimeAdminID)) {
					setSettingIntValueByIndex(s_BanTimeAdminID, value);
					strins(string, C_LIGHTGREEN"\t\tNowa wartosc zostala poprawnie ustawiona.", 0);
				} else strins(string, TEXT_DIALOG_ALERT"             Podana wartosc nie miesci sie w dopuszczalnym przedziale.", 0);			
			}
			strins(head, "Ustawienia administracyjne - Admin ban", 0);
			format(string, sizeof(string), "W tym menu mozesz ustalic jak maksymalnie dlugo moze trwac ban czasowy.\n\t   Czas musi zawierac sie w przedziale od %d do %d godzin.\n\n%s", getSettingIntMinValueByIndex(s_BanTimeAdminID), getSettingIntMaxValueByIndex(s_BanTimeAdminID), string);
		}
		case D_VALUE_SET_MUTE_TIME: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			else if(response_false == true) return ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);	
			else if(set_value == true) {
				if(getSettingIntMinValueByIndex(s_MuteMaxTimeID) <= value <= getSettingIntMaxValueByIndex(s_MuteMaxTimeID)) {
					setSettingIntValueByIndex(s_MuteMaxTimeID, value);
					strins(string, C_LIGHTGREEN"\t\t\t   Nowa wartosc zostala poprawnie ustawiona.", 0);
				} else strins(string, TEXT_DIALOG_ALERT"\t\t     Podana wartosc nie miesci sie w dopuszczalnym przedziale.", 0);			
			}
			strins(head, "Ustawienia administracyjne - Maks. czas uciszenia (cmd)", 0);
			format(string, sizeof(string), "W tym menu mozesz ustalic jak maksymalnie dlugo moze trwac uciszenie gracza komenda '/mute'.\n\t\t         Czas musi zawierac sie w przedziale od %d do %d minut.\n\n%s", getSettingIntMinValueByIndex(s_MuteMaxTimeID), getSettingIntMaxValueByIndex(s_MuteMaxTimeID), string);
		}
		case D_VALUE_SET_AUTOACCRES_DAY: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			else if(response_false == true) return ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);	
			else if(set_value == true) {
				if(getSettingIntMinValueByIndex(s_AutoAccResetDay) <= value <= getSettingIntMaxValueByIndex(s_AutoAccResetDay)) {
					new month, days;
					getdate(month, month);
					setSettingIntValueByIndex(s_AutoAccResetDay, value);
					if(value > (days = GetDaysInMonth(month))) {
						format(string, sizeof(string), C_LIGHTGREEN"\t\t\t    Nowa wartosc zostala poprawnie ustawiona.\n\n"TEXT_DIALOG_BODY"\t      Informacja: W tym miesiacu reset kont zostanie wykonany %d dnia miesiaca.", days);
					} else strins(string, C_LIGHTGREEN"\t\t\t    Nowa wartosc zostala poprawnie ustawiona.", 0);
				} else strins(string, TEXT_DIALOG_ALERT"\t\t     Podana wartosc nie miesci sie w dopuszczalnym przedziale.", 0);			
			}
			strins(head, "Ustawienia administracyjne - Dzien auto. resetu kont", 0);
			format(string, sizeof(string), "  W tym menu mozesz ustalic, ktorego dnia miesiaca ma byc wykonywany automatyczny reset kont.\nW przypadku kiedy miesiac zawiera mniej dni niz ustawiona data, reset kont odbywa sie ostatniego\n\t\tdnia miesiaca. Dzien musi zawierac sie w przedziale od %d do %d.\n\n%s", getSettingIntMinValueByIndex(s_AutoAccResetDay), getSettingIntMaxValueByIndex(s_AutoAccResetDay), string);		
		}
		case D_VALUE_SET_RCON_FAIL: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			else if(response_false == true) return ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);	
			else if(set_value == true) {
				if(getSettingIntMinValueByIndex(s_RCONFailLoginID) <= value <= getSettingIntMaxValueByIndex(s_RCONFailLoginID)) {
					setSettingIntValueByIndex(s_RCONFailLoginID, value);
					strins(string, C_LIGHTGREEN"\t          Nowa wartosc zostala poprawnie ustawiona.", 0);
				} else strins(string, TEXT_DIALOG_ALERT"          Podana wartosc nie miesci sie w dopuszczalnym przedziale.", 0);			
			}
			strins(head, "Ustawienia administracyjne - Maks. blednych logowan RCON", 0);
			format(string, sizeof(string), "W tym menu mozesz ustalic ile maksymalnie blednych logowan RCON\n          moze dokonac gracz, zanim zostanie wyrzucony z serwera.\n\t   Ilosc prob musi zawierac sie w przedziale od %d do %d.\n\n%s", getSettingIntMinValueByIndex(s_RCONFailLoginID), getSettingIntMaxValueByIndex(s_RCONFailLoginID), string);
		}
		case D_BALUE_SET_MUTE_CENSURE_TIME: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			else if(response_false == true) return ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);	
			else if(set_value == true) {
				if(getSettingIntMinValueByIndex(s_CensureMuteTimeID) <= value <= getSettingIntMaxValueByIndex(s_CensureMuteTimeID)) {
					setSettingIntValueByIndex(s_CensureMuteTimeID, value);
					strins(string, C_LIGHTGREEN"\t       Nowa wartosc zostala poprawnie ustawiona.", 0);
				} else strins(string, TEXT_DIALOG_ALERT"         Podana wartosc nie miesci sie w dopuszczalnym przedziale.", 0);			
			}
			strins(head, "Ustawienia powiadomien i chatu - Czas uciszenia za przek.", 0);
			format(string, sizeof(string), "  W tym menu mozesz ustalic, jak dlugo ma trwac uciszenie dla gracza\n\t   za przekroczenie limitu ostrzezen za przeklinanie.\n\tCzas musi zawierac sie w przedziale od %d do %d minut.\n\n%s", getSettingIntMinValueByIndex(s_CensureMuteTimeID), getSettingIntMaxValueByIndex(s_CensureMuteTimeID), string);		
		}
		case D_BALUE_SET_MUTE_MAX_WARNINGS: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			else if(response_false == true) return ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);	
			else if(set_value == true) {
				if(getSettingIntMinValueByIndex(s_CensureMaxWarningsID) <= value <= getSettingIntMaxValueByIndex(s_CensureMaxWarningsID)) {
					setSettingIntValueByIndex(s_CensureMaxWarningsID, value);
					strins(string, C_LIGHTGREEN"\t           Nowa wartosc zostala poprawnie ustawiona.", 0);
				} else strins(string, TEXT_DIALOG_ALERT"             Podana wartosc nie miesci sie w dopuszczalnym przedziale.", 0);			
			}
			strins(head, "Ustawienia powiadomien i chatu - Limit ostr. za przek.", 0);
			format(string, sizeof(string), "  W tym menu mozesz ustalic ile maksymalnie ostrzezen ma dostac gracz,\n\t\tzanim zostanie uciszony za przeklinanie.\n\tLimit musi zawierac sie w przedziale od %d do %d ostrzezen.\n\n%s", getSettingIntMinValueByIndex(s_CensureMaxWarningsID), getSettingIntMaxValueByIndex(s_CensureMaxWarningsID), string);		
		}		
		case D_BALUE_SET_ANTYSPAM_MIN_SEC: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			else if(response_false == true) return ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);	
			else if(set_value == true) {
				if(getSettingIntMinValueByIndex(s_AntySpamMinTimeID) <= value <= getSettingIntMaxValueByIndex(s_AntySpamMinTimeID)) {
					setSettingIntValueByIndex(s_AntySpamMinTimeID, value);
					strins(string, C_LIGHTGREEN"\t    Nowa wartosc zostala poprawnie ustawiona.", 0);
				} else strins(string, TEXT_DIALOG_ALERT"    Podana wartosc nie miesci sie w dopuszczalnym przedziale.", 0);			
			}
			strins(head, "Ustawienia powiadomien i chatu - Czas min. spam", 0);
			format(string, sizeof(string), "  W tym menu mozesz ustalic ile minimalnie sekund musi uplynac\n        miedzy dwoma wyslanymi przez gracza wiadomosciami.\n        Limit musi zawierac sie w przedziale od %d do %d sekund.\n\n%s", getSettingIntMinValueByIndex(s_AntySpamMinTimeID), getSettingIntMaxValueByIndex(s_AntySpamMinTimeID), string);		
		}			
		case D_BALUE_SET_ANTYFLOOD_MIN_SEC: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			else if(response_false == true) return ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);	
			else if(set_value == true) {
				if(getSettingIntMinValueByIndex(s_AntyFloodMinTimeID) <= value <= getSettingIntMaxValueByIndex(s_AntyFloodMinTimeID)) {
					setSettingIntValueByIndex(s_AntyFloodMinTimeID, value);
					strins(string, C_LIGHTGREEN"\t       Nowa wartosc zostala poprawnie ustawiona.", 0);
				} else strins(string, TEXT_DIALOG_ALERT"         Podana wartosc nie miesci sie w dopuszczalnym przedziale.", 0);			
			}
			strins(head, "Ustawienia powiadomien i chatu - Czas min. flood", 0);
			format(string, sizeof(string), "      W tym menu mozesz ustalic ile minimalnie sekund musi uplynac\nmiedzy dwoma takimi samymi wiadomosciami wyslanymi przez gracza.\n             Limit musi zawierac sie w przedziale od %d do %d sekund.\n\n%s", getSettingIntMinValueByIndex(s_AntyFloodMinTimeID), getSettingIntMaxValueByIndex(s_AntyFloodMinTimeID), string);		
		}		

		case D_VALUE_SET_MAX_PING: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			else if(response_false == true) return ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);	
			else if(set_value == true) {
				if(getSettingIntMinValueByIndex(s_MaxPingID) <= value <= getSettingIntMaxValueByIndex(s_MaxPingID)) {
					setSettingIntValueByIndex(s_MaxPingID, value);
					strins(string, C_LIGHTGREEN"\tNowa wartosc zostala poprawnie ustawiona.", 0);
				} else strins(string, TEXT_DIALOG_ALERT"  Podana wartosc nie miesci sie w dopuszczalnym przedziale.", 0);			
			}
			strins(head, "Ograniczenia graczy - Maksymalny ping", 0);
			format(string, sizeof(string), "W tym menu mozesz ustalic jaki maksymalnie ping moze miec\n\t        gracz, zanim dostanie ostrzezenie.\nLimit musi zawierac sie w przedziale od %d do %d jednostek.\n\n%s", getSettingIntMinValueByIndex(s_MaxPingID), getSettingIntMaxValueByIndex(s_MaxPingID), string);		
		}	

		case D_VALUE_SET_MIN_FPS: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			else if(response_false == true) return ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);	
			else if(set_value == true) {
				if(getSettingIntMinValueByIndex(s_MinFPSID) <= value <= getSettingIntMaxValueByIndex(s_MinFPSID)) {
					setSettingIntValueByIndex(s_MinFPSID, value);
					strins(string, C_LIGHTGREEN"          Nowa wartosc zostala poprawnie ustawiona.", 0);
				} else strins(string, TEXT_DIALOG_ALERT"Podana wartosc nie miesci sie w dopuszczalnym przedziale.", 0);			
			}
			strins(head, "Ograniczenia graczy - Minimalne FPS'y", 0);
			format(string, sizeof(string), "    W tym menu mozesz ustalic ile minimalnie FPS'ow musi\n\t   miec gracz zeby nie dostal ostrzezenia.\n  Limit musi zawierac sie w przedziale od %d do %d FPS'ow.\n\n%s", getSettingIntMinValueByIndex(s_MinFPSID), getSettingIntMaxValueByIndex(s_MinFPSID), string);		
		}	
		
		case D_VALUE_SET_MAX_PLOSS: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			else if(response_false == true) return ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);	
			else if(set_value == true) {
				if(getSettingIntMinValueByIndex(s_MaxPLossID) <= value <= getSettingIntMaxValueByIndex(s_MaxPLossID)) {
					setSettingIntValueByIndex(s_MaxPLossID, value);
					strins(string, C_LIGHTGREEN"\t\t\t      Nowa wartosc zostala poprawnie ustawiona.", 0);
				} else strins(string, TEXT_DIALOG_ALERT"\t\t         Podana wartosc nie miesci sie w dopuszczalnym przedziale.", 0);			
			}
			strins(head, "Ograniczenia graczy - Maks. utrata pakietow", 0);
			format(string, sizeof(string), 
					"W tym menu mozesz ustalic ile maksymalnie pakietow moze stracic gracz zanim otrzyma ostrzezenie.\n\t\t         Limit musi zawierac sie w przedziale od %d do %d procent.\n\n%s",
				getSettingIntMinValueByIndex(s_MaxPLossID), getSettingIntMaxValueByIndex(s_MaxPLossID), string);		
		}	
		case D_VALUE_SET_MAX_PING_WARNINGS: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			else if(response_false == true) return ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);	
			else if(set_value == true) {
				if(getSettingIntMinValueByIndex(s_MaxPingWarningsID) <= value <= getSettingIntMaxValueByIndex(s_MaxPingWarningsID)) {
					setSettingIntValueByIndex(s_MaxPingWarningsID, value);
					strins(string, C_LIGHTGREEN"\t\t Nowa wartosc zostala poprawnie ustawiona.", 0);
				} else strins(string, TEXT_DIALOG_ALERT"\t  Podana wartosc nie miesci sie w dopuszczalnym przedziale.", 0);			
			}
			strins(head, "Ograniczenia graczy - Maksymalny ping (Ostrzezenia)", 0);
			format(string, sizeof(string), 
					"W tym menu mozesz ustalic ile maksymalnie ostrzezen ma dostac gracz, zanim\n  zostanie wyrzucony z serwera za przekroczenie limitu maksymalnego pingu.\n\t   Limit musi zawierac sie w przedziale od %d do %d ostrzezen.\n\n%s",
				getSettingIntMinValueByIndex(s_MaxPingWarningsID), getSettingIntMaxValueByIndex(s_MaxPingWarningsID), string
			);		
		}			
		case D_VALUE_SET_MIN_FPS_WARNINGS: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			else if(response_false == true) return ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);	
			else if(set_value == true) {
				if(getSettingIntMinValueByIndex(s_MinFPSWarningsID) <= value <= getSettingIntMaxValueByIndex(s_MinFPSWarningsID)) {
					setSettingIntValueByIndex(s_MinFPSWarningsID, value);
					strins(string, C_LIGHTGREEN"\t\t Nowa wartosc zostala poprawnie ustawiona.", 0);
				} else strins(string, TEXT_DIALOG_ALERT"\t  Podana wartosc nie miesci sie w dopuszczalnym przedziale.", 0);			
			}
			strins(head, "Ograniczenia graczy - Maksymalny ping (Ostrzezenia)", 0);
			format(string, sizeof(string), 
					"W tym menu mozesz ustalic ile maksymalnie ostrzezen ma dostac gracz, zanim\n  zostanie wyrzucony z serwera za przekroczenie limitu minimalnych FPS'ow.\n\t   Limit musi zawierac sie w przedziale od %d do %d ostrzezen.\n\n%s",
				getSettingIntMinValueByIndex(s_MinFPSWarningsID), getSettingIntMaxValueByIndex(s_MinFPSWarningsID), string
			);		
		}		
		case D_VALUE_SET_MAX_PLOSS_WARNINGS: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			else if(response_false == true) return ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);	
			else if(set_value == true) {
				if(getSettingIntMinValueByIndex(s_MaxPLossWarningsID) <= value <= getSettingIntMaxValueByIndex(s_MaxPLossWarningsID)) {
					setSettingIntValueByIndex(s_MaxPLossWarningsID, value);
					strins(string, C_LIGHTGREEN"\t\t         Nowa wartosc zostala poprawnie ustawiona.", 0);
				} else strins(string, TEXT_DIALOG_ALERT"\t             Podana wartosc nie miesci sie w dopuszczalnym przedziale.", 0);			
			}
			strins(head, "Ograniczenia graczy - Maksymalny ping (Ostrzezenia)", 0);
			format(string, sizeof(string), 
					"W tym menu mozesz ustalic ile maksymalnie ostrzezen ma dostac gracz, zanim zostanie\n      wyrzucony z serwera za przekroczenie limitu maksymalnych traconych pakietow.\n\t\tLimit musi zawierac sie w przedziale od %d do %d ostrzezen.\n\n%s",
				getSettingIntMinValueByIndex(s_MaxPLossWarningsID), getSettingIntMaxValueByIndex(s_MaxPLossWarningsID), string
			);		
		}		
		case D_VALUE_SET_PINGGPSPLOSS_FREQUENCY: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			else if(response_false == true) return ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);	
			else if(set_value == true) {
				if(getSettingIntMinValueByIndex(s_CheckDataFrequencyID) <= value <= getSettingIntMaxValueByIndex(s_CheckDataFrequencyID)) {
					setSettingIntValueByIndex(s_CheckDataFrequencyID, value);
					strins(string, C_LIGHTGREEN"\t\t        Nowa wartosc zostala poprawnie ustawiona.", 0);
				} else strins(string, TEXT_DIALOG_ALERT"\t         Podana wartosc nie miesci sie w dopuszczalnym przedziale.", 0);			
			}
			strins(head, "Ograniczenia graczy - Czestotliwosc testow", 0);
			format(string, sizeof(string), "W tym menu mozesz ustawic czestotliwosc testu pingu, FPS'ow i traconych pakietow.\n\t   Czestotliwosc musi zawierac sie w przedziale od %d do %d sekund.\n\n%s", getSettingIntMinValueByIndex(s_CheckDataFrequencyID), getSettingIntMaxValueByIndex(s_CheckDataFrequencyID), string);		
		}		
		case D_VALUE_SET_VIP_REG_TIME: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			else if(response_false == true) return ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);	
			else if(set_value == true) {
				if(getSettingIntMinValueByIndex(s_VIPRegisterTimeID) <= value <= getSettingIntMaxValueByIndex(s_VIPRegisterTimeID)) {
					setSettingIntValueByIndex(s_VIPRegisterTimeID, value);
					strins(string, C_LIGHTGREEN"\t\t\tNowa wartosc zostala poprawnie ustawiona.", 0);
				} else strins(string, TEXT_DIALOG_ALERT"\t\t  Podana wartosc nie miesci sie w dopuszczalnym przedziale.", 0);			
			}
			strins(head, "Ustawienia VIP - Konto VIP po rejestracji", 0);
			format(string, sizeof(string), 
					"W tym menu mozesz ustalic ile dni bonusowego konta VIP ma dostac gracz po rejestracji konta.\n\t\t       Limit musi zawierac sie w przedziale od %d do %d dni.\n\n%s",
				getSettingIntMinValueByIndex(s_VIPRegisterTimeID), getSettingIntMaxValueByIndex(s_VIPRegisterTimeID), string
			);		
		}	
		case D_VALUE_SET_VIP_REG_POINTS: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			else if(response_false == true) return ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);	
			else if(set_value == true) {
				if(getSettingIntMinValueByIndex(s_VIPRegisterPointsID) <= value <= getSettingIntMaxValueByIndex(s_VIPRegisterPointsID)) {
					setSettingIntValueByIndex(s_VIPRegisterPointsID, value);
					strins(string, C_LIGHTGREEN"\t\t\t    Nowa wartosc zostala poprawnie ustawiona.", 0);
				} else strins(string, TEXT_DIALOG_ALERT"\t\t      Podana wartosc nie miesci sie w dopuszczalnym przedziale.", 0);			
			}
			strins(head, "Ustawienia VIP - Punkty VIP po rejestracji", 0);
			format(string, sizeof(string), 
					"W tym menu mozesz ustalic ile dni bonusowych punktow premium ma dostac gracz po rejestracji konta.\n\t\t      Limit musi zawierac sie w przedziale od %d do %d punktow.\n\n%s",
				getSettingIntMinValueByIndex(s_VIPRegisterPointsID), getSettingIntMaxValueByIndex(s_VIPRegisterPointsID), string
			);		
		}
		case D_VALUE_SET_VIP_3: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			else if(response_false == true) return ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);	
			else if(set_value == true) {
				if(getSettingIntMinValueByIndex(s_VIP3DaysCostID) <= value <= getSettingIntMaxValueByIndex(s_VIP3DaysCostID)) {
					setSettingIntValueByIndex(s_VIP3DaysCostID, value);
					strins(string, C_LIGHTGREEN"\t\t         Nowa wartosc zostala poprawnie ustawiona.", 0);
				} else strins(string, TEXT_DIALOG_ALERT"\t             Podana wartosc nie miesci sie w dopuszczalnym przedziale.", 0);			
			}
			strins(head, "Ustawienia VIP - Ilosc punktow za 3 dni konta VIP", 0);
			format(string, sizeof(string), 
					"W tym menu mozesz ustalic ile punktow premium ma kosztowac 3 dni przywilejow VIP'a.\n W przypadku ustawienia wartosci '0', opcja 3 dniowego konta VIP nie bedzie dostepna.\n\t\tLimit musi zawierac sie w przedziale od %d do %d punktow.\n\n%s",
				getSettingIntMinValueByIndex(s_VIP3DaysCostID), getSettingIntMaxValueByIndex(s_VIP3DaysCostID), string
			);		
		}
		case D_VALUE_SET_VIP_7: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			else if(response_false == true) return ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);	
			else if(set_value == true) {
				if(getSettingIntMinValueByIndex(s_VIP7DaysCostID) <= value <= getSettingIntMaxValueByIndex(s_VIP7DaysCostID)) {
					setSettingIntValueByIndex(s_VIP7DaysCostID, value);
					strins(string, C_LIGHTGREEN"\t\t         Nowa wartosc zostala poprawnie ustawiona.", 0);
				} else strins(string, TEXT_DIALOG_ALERT"\t             Podana wartosc nie miesci sie w dopuszczalnym przedziale.", 0);			
			}
			strins(head, "Ustawienia VIP - Ilosc punktow za 7 dni konta VIP", 0);
			format(string, sizeof(string), 
					"W tym menu mozesz ustalic ile punktow premium ma kosztowac 7 dni przywilejow VIP'a.\n W przypadku ustawienia wartosci '0', opcja 7 dniowego konta VIP nie bedzie dostepna.\n\t\tLimit musi zawierac sie w przedziale od %d do %d punktow.\n\n%s",
				getSettingIntMinValueByIndex(s_VIP7DaysCostID), getSettingIntMaxValueByIndex(s_VIP7DaysCostID), string
			);		
		}
		case D_VALUE_SET_VIP_30: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			else if(response_false == true) return ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);	
			else if(set_value == true) {
				if(getSettingIntMinValueByIndex(s_VIP30DaysCostID) <= value <= getSettingIntMaxValueByIndex(s_VIP30DaysCostID)) {
					setSettingIntValueByIndex(s_VIP30DaysCostID, value);
					strins(string, C_LIGHTGREEN"\t\t         Nowa wartosc zostala poprawnie ustawiona.", 0);
				} else strins(string, TEXT_DIALOG_ALERT"\t             Podana wartosc nie miesci sie w dopuszczalnym przedziale.", 0);			
			}
			strins(head, "Ustawienia VIP - Ilosc punktow za 30 dni konta VIP", 0);
			format(string, sizeof(string), 
					"W tym menu mozesz ustalic ile punktow premium ma kosztowac 30 dni przywilejow VIP'a.\n W przypadku ustawienia wartosci '0', opcja 30 dniowego konta VIP nie bedzie dostepna.\n\t\tLimit musi zawierac sie w przedziale od %d do %d punktow.\n\n%s",
				getSettingIntMinValueByIndex(s_VIP30DaysCostID), getSettingIntMaxValueByIndex(s_VIP30DaysCostID), string
			);		
		}
		case D_VALUE_SET_AC_SAMEIP: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			else if(response_false == true) return ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);	
			else if(set_value == true) {
				if(getSettingIntMinValueByIndex(s_ACConnectionSpamBotTimeID) <= value <= getSettingIntMaxValueByIndex(s_ACConnectionSpamBotTimeID)) {
					setSettingIntValueByIndex(s_ACConnectionSpamBotTimeID, value);
					strins(string, C_LIGHTGREEN"\t  Nowa wartosc zostala poprawnie ustawiona.", 0);
				} else strins(string, TEXT_DIALOG_ALERT"  Podana wartosc nie miesci sie w dopuszczalnym przedziale.", 0);			
			}
			strins(head, "Anty Cheat - Gra z tego samego IP", 0);
			format(string, sizeof(string), "     W tym menu mozesz ustalic jaki okres czasu musi uplynac,\nzeby na serwer mogl wejsc gracz o tym samym IP, ktore posiada\n\t     inny gracz aktualnie bedacy na serwerze.\n    Limit musi zawierac sie w przedziale od %d do %d sekund.\n\n%s", getSettingIntMinValueByIndex(s_ACConnectionSpamBotTimeID), getSettingIntMaxValueByIndex(s_ACConnectionSpamBotTimeID), string);		
		}		
		case D_VALUE_SET_AC_CHATSPAMBOT: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			else if(response_false == true) return ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);	
			else if(set_value == true) {
				if(getSettingIntMinValueByIndex(s_ACAntySpamBotMsgPerSecID) <= value <= getSettingIntMaxValueByIndex(s_ACAntySpamBotMsgPerSecID)) {
					setSettingIntValueByIndex(s_ACAntySpamBotMsgPerSecID, value);
					strins(string, C_LIGHTGREEN"\t             Nowa wartosc zostala poprawnie ustawiona.", 0);
				} else strins(string, TEXT_DIALOG_ALERT"\tPodana wartosc nie miesci sie w dopuszczalnym przedziale.", 0);			
			}
			strins(head, "Anty Cheat - Chat spam bot", 0);
			format(string, sizeof(string), "   W tym menu mozesz ustalic ile minimalnie wiadomosci na sekunde musi\nwyslac gracz, zeby jego aktywnosc uznac za podejrzenie uzycia spam bota.\n\tLimit musi zawierac sie w przedziale od %d do %d wiadomosci.\n\n%s", getSettingIntMinValueByIndex(s_ACAntySpamBotMsgPerSecID), getSettingIntMaxValueByIndex(s_ACAntySpamBotMsgPerSecID), string);		
		}
		case D_VALUE_SET_AC_CMDSPAMBOT: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			else if(response_false == true) return ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);	
			else if(set_value == true) {
				if(getSettingIntMinValueByIndex(s_ACAntyCMDSpamBotMsgPerSecID) <= value <= getSettingIntMaxValueByIndex(s_ACAntyCMDSpamBotMsgPerSecID)) {
					setSettingIntValueByIndex(s_ACAntyCMDSpamBotMsgPerSecID, value);
					strins(string, C_LIGHTGREEN"\t            Nowa wartosc zostala poprawnie ustawiona.", 0);
				} else strins(string, TEXT_DIALOG_ALERT"             Podana wartosc nie miesci sie w dopuszczalnym przedziale.", 0);			
			}
			strins(head, "Anty Cheat - CMD spam bot", 0);
			format(string, sizeof(string), "      W tym menu mozesz ustalic ile minimalnie komend na sekunde musi\nwyslac gracz, zeby jego aktywnosc uznac za podejrzenie uzycia CMD bota.\n\t  Limit musi zawierac sie w przedziale od %d do %d komend.\n\n%s", getSettingIntMinValueByIndex(s_ACAntyCMDSpamBotMsgPerSecID), getSettingIntMaxValueByIndex(s_ACAntyCMDSpamBotMsgPerSecID), string);		
		}
		case D_VALUE_SET_AC_FAKEKILLSPAMBOT: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			else if(response_false == true) return ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);	
			else if(set_value == true) {
				if(getSettingIntMinValueByIndex(s_ACAntyFakeKillsPerSecStatusID) <= value <= getSettingIntMaxValueByIndex(s_ACAntyFakeKillsPerSecStatusID)) {
					setSettingIntValueByIndex(s_ACAntyFakeKillsPerSecStatusID, value);
					strins(string, C_LIGHTGREEN"\t          Nowa wartosc zostala poprawnie ustawiona.", 0);
				} else strins(string, TEXT_DIALOG_ALERT"          Podana wartosc nie miesci sie w dopuszczalnym przedziale.", 0);			
			}
			strins(head, "Anty Cheat - Fake-Kill spam bot", 0);
			format(string, sizeof(string), "     W tym menu mozesz ustalic ile minimalnie smierci na sekunde musi\nmiec gracz, zeby jego aktywnosc uznac za podejrzenie uzycia spam bota.\n\tLimit musi zawierac sie w przedziale od %d do %d smierci.\n\n%s", getSettingIntMinValueByIndex(s_ACAntyFakeKillsPerSecStatusID), getSettingIntMaxValueByIndex(s_ACAntyFakeKillsPerSecStatusID), string);		
		}		
		case D_VALUE_SET_AC_REJOIN: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			else if(response_false == true) return ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);	
			else if(set_value == true) {
				if(getSettingIntMinValueByIndex(s_ACAntyReJoinSpamTryID) <= value <= getSettingIntMaxValueByIndex(s_ACAntyReJoinSpamTryID)) {
					setSettingIntValueByIndex(s_ACAntyReJoinSpamTryID, value);
					strins(string, C_LIGHTGREEN"\t\t\tNowa wartosc zostala poprawnie ustawiona.", 0);
				} else strins(string, TEXT_DIALOG_ALERT"\t\tPodana wartosc nie miesci sie w dopuszczalnym przedziale.", 0);			
			}
			strins(head, "Anty Cheat - Rejoin spam bot", 0);
			format(string, sizeof(string), "    W tym menu mozesz ustalic ile minimalnie polaczen w ciagu sekundy z tego samego IP,\nmusi zostac wykonanych, zeby czynnosc zostala uznana za probe ataku Rejoin spambotem\n\t\t Limit musi zawierac sie w przedziale od %d do %d polaczen.\n\n%s", getSettingIntMinValueByIndex(s_ACAntyReJoinSpamTryID), getSettingIntMaxValueByIndex(s_ACAntyReJoinSpamTryID), string);		
		}	
		case D_VALUE_SET_AC_GODMODE_WARNINGS: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			else if(response_false == true) return ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);	
			else if(set_value == true) {
				if(getSettingIntMinValueByIndex(s_ACAntyGodmodeMaxWarnsID) <= value <= getSettingIntMaxValueByIndex(s_ACAntyGodmodeMaxWarnsID)) {
					setSettingIntValueByIndex(s_ACAntyGodmodeMaxWarnsID, value);
					strins(string, C_LIGHTGREEN"\t   Nowa wartosc zostala poprawnie ustawiona.", 0);
				} else strins(string, TEXT_DIALOG_ALERT"    Podana wartosc nie miesci sie w dopuszczalnym przedziale.", 0);			
			}
			strins(head, "Anty Cheat - Godmode", 0);
			format(string, sizeof(string), " W tym menu mozesz ustalic ile ostrzezen musi dostac gracz, za\nniepoprawny pomiar HP zanim zostanie podjeta akcja. Zaleca sie\n\t      ustawienie nie mniejsze niz 5 ostrzezen!\n     Limit musi zawierac sie w przedziale od %d do %d ostrzezen.\n\n%s", getSettingIntMinValueByIndex(s_ACAntyGodmodeMaxWarnsID), getSettingIntMaxValueByIndex(s_ACAntyGodmodeMaxWarnsID), string);		
		}
		case D_VALUE_SET_AC_GODMODE_TICKS: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			else if(response_false == true) return ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);	
			else if(set_value == true) {
				if(getSettingIntMinValueByIndex(s_ACAntyGodmodeTicksID) <= value <= getSettingIntMaxValueByIndex(s_ACAntyGodmodeTicksID)) {
					setSettingIntValueByIndex(s_ACAntyGodmodeTicksID, value);
					strins(string, C_LIGHTGREEN"\t\tNowa wartosc zostala poprawnie ustawiona.", 0);
				} else strins(string, TEXT_DIALOG_ALERT"\t Podana wartosc nie miesci sie w dopuszczalnym przedziale.", 0);			
			}
			strins(head, "Anty Cheat - Godmode", 0);
			format(string, sizeof(string), "W tym menu mozesz ustawic czestotliwosc testu HP. Zaleca sie ustawienie\nwartosci nie mniejszej niz 50 odswiezen. Im mniejsza wartosc, tym wieksze\n             ryzyko niepoprawnego testu! 50 jednostek rowna sie ok. 2 sek.\n\tLimit musi zawierac sie w przedziale od %d do %d odswiezen.\n\n%s", getSettingIntMinValueByIndex(s_ACAntyGodmodeTicksID), getSettingIntMaxValueByIndex(s_ACAntyGodmodeTicksID), string);		
		}		
		case D_VALUE_SET_CRITICAL_PLOSS: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			else if(response_false == true) return ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);	
			else if(set_value == true) {
				if(getSettingIntMinValueByIndex(s_MaxPLossCriticalLimitID) <= value <= getSettingIntMaxValueByIndex(s_MaxPLossCriticalLimitID)) {
					setSettingIntValueByIndex(s_MaxPLossCriticalLimitID, value);
					strins(string, C_LIGHTGREEN"\t\t        Nowa wartosc zostala poprawnie ustawiona.", 0);
				} else strins(string, TEXT_DIALOG_ALERT"\t       Podana wartosc nie miesci sie w dopuszczalnym przedziale.", 0);			
			}
			strins(head, "Ograniczenia graczy - Kryt. utrata pakietow", 0);
			format(string, sizeof(string), "W tym menu mozesz ustawic maksymalna dopuszczalna wartosc traconych pakietow.\n\tGracz, ktory ja przekroczy, bedzie natychmiast wyrzucany z serwera.\n\t       Wartosc musi zawierac sie w przedziale od %d do %d procent.\n\n%s", getSettingIntMinValueByIndex(s_MaxPLossCriticalLimitID), getSettingIntMaxValueByIndex(s_MaxPLossCriticalLimitID), string);		
		}			
		case D_VALUE_SET_CRITICAL_PING: {
			if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
			else if(response_false == true) return ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), -1);	
			else if(set_value == true) {
				if(getSettingIntMinValueByIndex(s_MaxPingCriticalLimitID) <= value <= getSettingIntMaxValueByIndex(s_MaxPingCriticalLimitID)) {
					setSettingIntValueByIndex(s_MaxPingCriticalLimitID, value);
					strins(string, C_LIGHTGREEN"\t        Nowa wartosc zostala poprawnie ustawiona.", 0);
				} else strins(string, TEXT_DIALOG_ALERT"          Podana wartosc nie miesci sie w dopuszczalnym przedziale.", 0);			
			}
			strins(head, "Ograniczenia graczy - Kryt. wartosc pingu", 0);
			format(string, sizeof(string), "W tym menu mozesz ustawic maksymalna dopuszczalna wartosc pingu.\n  Gracz, ktory ja przekroczy, bedzie natychmiast wyrzucany z serwera.\n\tWartosc musi zawierac sie w przedziale od %d do %d.\n\n%s", getSettingIntMinValueByIndex(s_MaxPingCriticalLimitID), getSettingIntMaxValueByIndex(s_MaxPingCriticalLimitID), string);		
		}			
	}
	ShowPlayerDialogEx(playerid, DIALOG_VALUE, DIALOG_STYLE_INPUT, head, string, "Ustaw", "Wroc");
	return _TRUE;
}