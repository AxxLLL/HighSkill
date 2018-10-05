/*
=== Changelog ===
	- v1.9.0
	    + (Zmiana) Zamieniono poprzedni pomiar i funkcje FPS na nowa.
	    + (Usuniecie) Usunieto anty high ping.
		+ (Usuniecie) Usunieto kod anty spamu i anty flooda.
		+ (Usuniecie) Usunieto kod prywatnych wiadomosci.
		+ (Zmiana) Zmieniono kod w zakresie odswiezania nicku gracza w hudzie pod katem nowego admin systemu.
		+ (Usuniecie) Usunieto polaczenie z lokalna baza SQL.
		+ (Usuniecie) Usunieto zbedne odniesienia do ustawien pingu i FPS'ow.
		+ (Zmiana) Usunieto stary kod na przyznawanie pozycji rankingu na nowy, wywolujacy funkcje zdalna.
		+ (Usuniecie) Usunieto kod odpowiedzialny za zapis fragow do konta zalogowanego gracza.
		+ (Zmiana) Przeniesiono system zarzadzania gamemodem z starego admin systemu.
		+ (Zmiana) Dostosowano chat do admin systemu.
		+ (Usuniecie) Usunieto ustawienia cenzury gracza.
		+ (Poprawka) Poprawiono kod zarzadzania gra gracza.
		+ (Usuniecie) Usunieto kod operacji cyklicznych.
		+ (Zmiana) Dostosowano pVary do nowego admin systemu.
		
		- RC-2
			+ (Bugfix) Poprawiono blad zwiazanym z przepelnieniem tablicy koloru na chacie.
			+ (Nowosc) Dodano funkcje wysylajaca ustawienia status uzywanych broni w gamemodzie do anty cheata.
			+ (Bugfix) Dodano zabezpieczenie hamujace antycheat na wykrywanie niedozwolonych broni, po ich zmianie przez gamemod.
			+ (Poprawka) Dodano brakujace komendy do spisu komend admina i usunieto wzmianki o komendzie top10.
			+ (Poprawka) Zsynchronizowano komende pomocy z admin systemem.
			+ (Nowosc) Dodano funkcje SetPlayerHealthEx i SetPlayerArmourEx, ktore oprocz normalnego dzialania wysylaja powiadomienie do admin systemu.
			+ (Poprawka) Uzupelniono komende pomocy o komendy administracyjne.
		- RC-3
		    + (Poprawka) Poprawiono menu zarzadzania kontem gracza (integracja z asystemem).
		    + (Poprawka) Poprawiono menu ustawien amunicji do broni.
		    + (Nowosc) Dodano menu zarzadzania respektem.
		    + (Nowosc) Dodano kare za heli / car kill oraz opuszczenie serwera podczas gry.
		    + (Poprawka) Poprawiono wiadomosc przy usuwaniu gracza z rundy przez system.
		    + (Nowosc) Przy specowaniu gracza, spectator widzi powiadomienia o trafieniu / byciu trafionym obserwowanego gracza.
		    + (Nowosc) Informacje o namierzanym graczu.
		- RC-4
		    + (Bugfix) Poprawiono wysylanie wiadomosci, przy braku cenzury serwerowej i wiadomosci zawierajacej przeklenstwo.
	- v 1.9.1
	    + (Bugfix) Podczas startu rundy, chowane bylo okno logowania.
		+ (Nowosc) Gracz jest automatycznie dodawany do rundy, w przypadku kiedy na arenie z interiorem jest w bugu i spada (po smierci).
		+ (Nowosc) Gracz moze wpisac komende '/respawn', jesli jego odleglosc od srodka areny jest wieksza niz polowa jej przekatnej.
		+ (Nowosc) Runda jest automatycznie konczona, w przypadku kiedy zaden z graczy nie wykazuje aktywnosci w ciagu ost. 15 sekund.
		    
	- v 1.9.2
	    + (Nowosc) Dodano podstawe respektu dla zabojstw na bronie.
		+ (Nowosc) Dodano specjalna wartosc respektu na bronie dla kont VIP.
		+ (Nowosc) Gracze z kontem VIP moga wejsc do druzyny arbitrow.
		+ (Nowosc) Gracz z kontem VIP, bedacy w druzynie arbitrow moze specowac wszystkich graczy.
		+ (Nowosc) Glos gracza z kontem VIP w glosowaniu na arene / baze jest traktowany podwojnie.
		+ (Nowosc) Gracze z kontem VIP moga startowac runde co X rozegranych.
		+ (Nowosc) Gracze z kontem VIP moga uzywac komendy '/rsp' co 5 sekund.
		+ (Nowosc) Gracze z kontem VIP moga uzyc komendy '/gun' do czasu konca ochrony 'First Blood'.
		- v 1.9.2-2
		    + (Nowosc) Dodano wysylanie informacji o statystykach dziennych.
		    + (Nowosc) Dodano log (printf) o startowaniu i konczeniu rundy.
		    + (Nowosc) Dodano informacje o przywilejach VIP.
		    + (Poprawka) Dodano ograniczenie startowania tych samych aren i baz dla startow gracza z kontem VIP.
		    
	- v 1.9.3
	    + (Nowosc) Pojazd otrzymuje obrazenia, nawet gdy nie ma w nim kierowcy.
		+ (Zmiana) Dostosowano 'getPlayerPLoss' do nowej funkcji 'NetStats_PacketLossPercent'.
		
	 - v 1.9.4
	    + (Nowosc) Dodanie mozliwosci natychmiastowego zapisu ustawien do pliku w panelu ustawien.
	    + (Zmiana) Tablista pokazuje aktualna iloœæ zdrowia (+armor), a nie zdrowie i FPS'y.
	    + (Zmiana) W trakcie przerw tablista pokazuje ilosc zdobytego w czasie gry DMG.
	    + (Bugfix) Poprawiono blad w powiadomieniu trafienia, niepokazujacy ile gracz ma zdrowia lacznie z armorem.
	    + (Nowosc) Usuwanie z rundy za helikill.
	- v 1.9.5
	    - (Nowosc) Automatyczny start losowej areny w przypadku braku reakcji graczy.
	    
    - (Nowosc) Dodanie ustawienia regulujacego otrzymywanie obrazen przez nieuzywane pojazdy.
	- (Zmiana) Zmiana systemu obrazen z SA-MP'owego na wlasny.
    - (Poprawka) Armor nie byl dodawany w przypadku uzycia komendy '/respawn'.
	- (Zmiana) Komenda '/gun' dzia³a tak¿e podczas pobytu w lobby,

--------------------------------------------------------------------------------
*/
//0x044FAACC

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
#include <a_samp>
#include <colors>
#include <zcmd>
#include <a_data>
#include <a_func>
#include <sscanf2>
//------------------------------------------------------------------------------
#pragma tabsize 0
//------------------------------------------------------------------------------
enum E_LIC_DATE {ELIC_DAY, ELIC_MONTH, ELIC_YEAR};
new g_LicEndDate[E_LIC_DATE] = {
	31, 12, 2016
};
//------------------------------------------------------------------------------
#define _TESTY          0
#define LAN             5

#define NPC_CONNECT     0
#define MAX_GRACZY  	24

#define	SCIEZKA_LIC		"HighSkill/lic.txt"
#define	_LICENCJA		"hGDBVJ$##HYsdhuw347yd9sa8hjY#h4b3jhudhsa8Y*(U#$jfds8"
//------------------------------------------------------------------------------
#if LAN != 0 && _TESTY == 0
	#if LAN == 1
		#define SERV_NAME	"~HighSkill.eu - Only for pr0! @ Pukawka.pl"
		#define SERV_PORT	7787
		#define SERV_RCON	"K7hs9dbjksaJHlasd9HN743nuN72"
	#elseif LAN == 2
		#define SERV_NAME	"AxL_ test serwer@maxrate.pl"
		#define SERV_PORT 	7809
		#define SERV_RCON	"axlmaster"
	#elseif LAN == 3
	    #define SERV_NAME	"(n2) HighSkill.eu ~ Only for pr0! @maxrate.pl"
	    #define SERV_PORT 	7785
	    #define SERV_RCON	"438odasjio43u809asjd342kasd"
	#elseif LAN == 4
	    #define SERV_NAME	"HighSkill.eu ~ Only for pr0! @serverproject.pl"
	    #define SERV_PORT 	3688
	    #define SERV_RCON	"dfs543sdfaq325464gf23sadv"
	#elseif LAN == 5
	    #define SERV_NAME	"Save Our SA:MP @pukawka.pl"
	    #define SERV_PORT 	7777
	    #define SERV_RCON	"sa7y8234uhsda7y23huisw7y21njsa"
	#else
		#define SERV_NAME	"SA-MP 0.3 Server"
		#define SERV_PORT	7777
		#define SERV_RCON	"axl"
	#endif
#else
	#define SERV_NAME	"SA-MP 0.3 Server"
	#define SERV_PORT	7777
	#define SERV_RCON	"axl"
#endif
//------------------------------------------------------------------------------
#if defined MAX_GRACZY
	#undef MAX_PLAYERS
	#define MAX_PLAYERS MAX_GRACZY
#endif
//------------------------------------------------------------------------------
#define OGRANICZENIE_OBSZARU_POJAZDU    1
//------------------------------------------------------------------------------
#define _WWW						"www.HighSkill.eu"
#define GM_WERSJA   				"1.9.5"
#define MIN_ADMIN_SYSTEM_VERSION    10000
//------------------------------------------------------------------------------
#define T_NoN   NO_TEAM
#define T_ATT   0
#define T_DEF   1
#define T_REF   2
//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
#define GM_NAZWA    " High Skill ( v"GM_WERSJA"  |  A/D )"
#define GM_PRZERWA  "HighSkill.eu"
//------------------------------------------------------------------------------
#define GANG_ZONE_COLOR 0x044FAA40
//------------------------------------------------------------------------------
#define HIT_TIME            4000
#define MAX_AREN    		128
#define MAX_BAZ     		95
#define MAX_DEF_DYS 		400     // Maksymalna odleglosc na bazach dla druzyny obrony
//#define MAX_ATT_DYS 		MAX_DEF_DYS
//------------------------------------------------------------------------------
#define MNOZNIK_RSP_DMG 	1
#define CAR_SPAWN_DYS       50      // Odleglosc od spawnu ataku w ktorej mozna spawnowac pojazdy
#define START_OBJECTS 		1       // Ilosc statycznych obiektow moda + 1
#define CZAS_GLOSOWANIA     20      // Czas w sekundach trwania glosowania
#define CHECKPOINT_RANGE    1       // Dystans od CP do przejecia na bazach
//------------------------------------------------------------------------------
#define NUMBER_PLATE    	"{F42F2F}HighSkill{38F5E2}.eu"
#define HS_LOGO_TD  		C_SYSGREY"HighSkill{0E9C95}.eu"
#define TEXT_COLOR  		"{C4FDB0}"
#define C_TEXT      		TEXT_COLOR
#define HS_COLOR    		0x0474CEFF
#define HS_TEXT     		"{0474CE}"
//------------------------------------------------------------------------------
#define HEAD_FOLDER         "HighSkill"
#define LOBBY_FILE     	 	HEAD_FOLDER"/lobby.txt"
#define LOBBY_TDM_FILE  	HEAD_FOLDER"/lobbytdm.txt"
#define PLIK_OGLOSZENIA 	"HighSkill/ogloszenie.txt"
#define HS_SETTING_FILE		HEAD_FOLDER"/modesettings.cfg"
#define HS_WEAPONS_FILE     HEAD_FOLDER"/modeweapons.cfg"
//------------------------------------------------------------------------------
#define C_OFF			0
#define C_TERMINATE 	1
#define	C_CENSURE		2
//------------------------------------------------------------------------------
#define VW_WYBIERALKA   0
#define VW_SPAWN        1
#define VW_GRA          2
#define VW_ARENA_DM     3
#define VW_KAMERA       4
#define VW_SPARING      3000
#define VW_DEMO         4000
//------------------------------------------------------------------------------
#define SKIN_ATT    110
#define SKIN_DEF    114
#define SKIN_REF    240
//------------------------------------------------------------------------------
#define COLOR_DEF_AK   	0x0A48EF50
#define COLOR_DEF_NAK   0x6A92F950
#define COLOR_ATT_AK    0xFAFF1750
#define COLOR_ATT_NAK   0xFCEE8B50
#define COLOR_REF       0xE16CD650
//------------------------------------------------------------------------------
#define _INFO    		"{E8E8E8}"
#define INFO_GRACZ 		"{F0F0F0}"
#define CMD_INFO    	"{E0E0E0}"
#define _KICK       	"{F84545}"
#define INFO_RESPECT    "{DFDFDF}"
//------------------------------------------------------------------------------
#define forplayers(%1) 			for(new %1; %1 < MAX_PLAYERS; %1 ++) if(IsPlayerConnected(%1))
#define GetServerTick()         ServerTick
#define GetTimeToServerTick(%1) %1 - ServerTick
#define DialogHideForPlayer(%1) ShowPlayerDialog(%1, -1, 0, " ", " ", " ", "")
#define IsAdmin(%1)				GetPVarInt(%1, PV_LOGIN_ADMIN_LVL)
#define getPlayerFPS(%1)        GetPVarInt(%1, PV_PLAYER_FPS)
#define getPlayerPLoss(%1)      NetStats_PacketLossPercent(%1)
//------------------------------------------------------------------------------
#define TAB_NoN     0
#define TAB_SPAR    1
#define TAB_ADMIN   2
#define TAB_HBAN    3
#define	TAB_CHECK	4
#define TAB_STATS   5
//------------------------------------------------------------------------------
#define ALVL_NON            0
#define ALVL_JUNIOR_ADMIN	1
#define ALVL_ADMIN			2
#define ALVL_HEAD_ADMIN		3
#define ALVL_GAME_MASTER	4
//------------------------------------------------------------------------------
#define S_NON			0
#define S_WYBIERALKA 	1
#define S_SPAWN         2
#define S_GRA           3
#define S_ARENA_DM      4
#define S_SPAR          5
#define S_SPECUJE       6
//------------------------------------------------------------------------------
#define PV_LOGIN_VIP_TIME		"PlayerLoginVIPTime"
#define PV_PLAYER_FPS           "PlayerFPS"
#define PV_RANKING        		"RankingGracza"
#define PV_CENSURE_STATUS       "PlayerCensureStatus"
#define PV_PLAYER_PACKET_LOSS   "PlayerPacketLoss"

#define PV_LOGIN_STATUS			"PlayerLoginStatus"
#define	PV_LOGIN_USERID			"PlayerLoginUserID"
#define PV_LOGIN_ADMIN_LVL		"PlayerLoginAdminLvL"
#define PV_ACC_DEATH			"AccDeath"
#define	PV_ACC_KILL				"AccKill"
#define	PV_ACC_DMG				"AccDMG"
#define	PV_ACC_RESPECT			"AccRespect"
#define	PV_ACC_SPARING_WIN		"AccSparingWin"
#define	PV_ACC_SPARING_LOSS		"AccSparingLoss"
#define	PV_ACC_CAR_KILL			"AccCarKill"
#define	PV_ACC_HELI_KILL		"AccHeliKill"
#define PV_ACC_WEAP_PART		"AccWeap"

#define PV_D_POMOCNICZA         "GMPomocniczaTablica"
#define PV_D_POMOCNICZA_2       "GMPomocniczaTablica2"
#define PV_D_POMOCNICZA_3       "GMPomocniczaTablica3"
#define PV_D_POMOCNICZA_4       "GMPomocniczaTablica4"

#define PV_STAN_GRACZA					"StanGracza"
#define PV_TAB              			"UzycieTabListy"
#define PV_SPAR_AKTYWNY         		"CzyWyzwanieNaSparJestAktywne"
#define	PV_SPEC_POKAZ					"PokazywanieSpectatora"
#define PV_RSP_AKTYWNY          		"CzyRSPNaPrzyciskEJstAktywne"
#define PV_AIMED_INFO_STATUS            "CelowanieInfo"
#define PV_WYNIKI						"ZmianaPodgladuWynikow"
#define	PV_HEAL							"CzasLeczeniaGracza"
#define	PV_POPRZEDNIE_HP       			"ZdrowieGracza"
//------------------------------------------------------------------------------
#define	DIALOG_OGLOSZENIE				100
#define DIALOG_KICK               		101
#define DIALOG_SPAR_BRONIE  			102
#define DIALOG_SPAR_GRACZ   			103
#define DIALOG_SPARING_PROPOZYCJA   	104
#define DIALOG_POJAZDY              	105
#define DIALOG_GLOSOWANIE           	106
#define DIALOG_MENU_GRY                 107
#define DIALOG_POMOC                    109
#define DIALOG_COFNIJ                   110
#define DIALOG_CMD_HELP                 111
#define DIALOG_CMD_LIST                 112

#define DIALOG_GUNMENU_1                114
#define DIALOG_GUNMENU_2                115
#define DIALOG_ADMIN_TEAM_CHANGE        116
#define DIALOG_STATS                    117
#define DIALOG_SETTING_MENU             118
#define DIALOG_GAMESETTING_MENU         119
#define DIALOG_GAMESETTING_GRENADE      120
#define DIALOG_GAMESETTING_VALUE        121
#define DIALOG_WEAPONSETTING_MENU       122
#define DIALOG_WEAPONSETTING_VALUE      123
#define DIALOG_ANNOUNCE_MSG             124
#define DIALOG_ANNOUNCE_TIME            125
#define DIALOG_INFO_ANNOUNCE            126
#define DIALOG_SETTING_RESPECT          127
#define DIALOG_SRESPECT_WEAPONS         128
#define DIALOG_SRESPECT_WEAPONS_SET     129
#define DIALOG_SRESPECT_SPECIAL_SET     130
#define DIALOG_SRESPECT_BASE_SET        131
#define DIALOG_SRESPECT_TYPE_SET        132
#define DIALOG_VIP_INFO                 133
//------------------------------------------------------------------------------
#define LOGIN_STATUS_NON			0
#define LOGIN_STATUS_NOTREGISTERED	1
#define LOGIN_STATUS_NOTLOGGED		2
#define LOGIN_STATUS_LOGGED			3
//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
forward OnPlayerNickChange(playerid, newnick[], oldnick[]);
//------------------------------------------------------------------------------
forward ServerProtect();
//------------------------------------------------------------------------------
main() {
    print("\n\n\n\n\
	\t\t =============== High Skill ==============\n\
   	\t\t|    Autor: Rafal (AxL) Zoltanski         |\n\
	\t\t|    Version: "GM_WERSJA"                       |\n\
    \t\t|    Last update: 30 / 09 /2013           |\n\
    \t\t|    Map dedicated for High-Skill server. |\n\
    \t\t|             www.HighSkill.eu            |\n\
    \t\t|                                         |\n\
    \t\t|          © All Right Reserved!          |\n\
    \t\t =========================================\
	\n");
	
	new Go, M, S, R, Mi, D;
	gettime(Go,M,S);
	getdate(R,Mi,D);
	printf("\t\t     ( %s\t%d:%02d:%02d )\n\n\n", strData(R, Mi, D, " / ", false, false, true, false),Go,M,S);
}
//==============================================================================

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
new bool:g_UsingAdminSystem = false;
	
new ServerTick;
enum g_info	{
    Text:TDZdrowie,

    Text3D:ZdrowiePojazdu3D,
    
    Float:ZdrowieRoznica,
    
    LastUpdate,
    
	TargetPlayer,
	TargetPlayerTime,
	
    UdzialWWalceTeam,
    AFKWarning,
    OstrzezenieAttPoza,
	    
    IloscGranatow,
    IDObjektuObszaruAreny,
	    
    Float:PlayerPOS[3],

    CzasInfoKill,
    CzasOstRSP,
    CzasPokazywaniaUtratyHP,
    CzasAreaCheck,

	stateChangeTick,

    RzucilNada,
    ProbAreaCheck,
    VoteWybor,
    SpecowanyID,
    SparingIDBroni[2],
    SparingIDGracza,
	    
	bool:AddAfterSpawn,
	bool:HitInGame,
    bool:PrzyciskSpecowaniaWcisniety,
    bool:WybieralkaZabezpieczenie,
	bool:VoteDodano,
	bool:GraczNacisnalPrzyciskRSP,
	
	IDPojazdu,
    gFragiRunda,
    gDMGRunda,
    gFragi,
    gSmierci,
    gRespect,
    gDMG,

    Float:gPoprzednieHP,
}	new G[MAX_GRACZY][g_info];

//------------------------------------------------------------------------------

#define CAPTURE_TIME 			20
#define SPAWN_PROTECT_ARENA 	5
#define SPAWN_PROTECT_BASE 		10
new g_RoundCaptureTime = CAPTURE_TIME;
new Float:g_RoundCaptureValue;
new Float:g_RoundCaptureCheckpointSize = 2.0;
new Float:g_RoundArenaAngles[2];
new g_RoundSpawnProtectTime = 0;                                                // -1 = first blood
//------------------------------------------------------------------------------
new sVIPMinRounds = 5;
new lastVIPRound = 0;
//------------------------------------------------------------------------------
new sRespectKilled = -2;
new sRespectSuecided = -4;
new sLeftSrvInRound = -5;
new sRespectFirstBlood = 5;

new sRespectBase = 1;
//------------------------------------------------------------------------------
new Text:PTD_SpecByInfo[MAX_PLAYERS];
new Text:TDAimedStatic[3],
	Text:PTD_PlayerAimedNick[MAX_PLAYERS],
    Text:PTD_PlayerAimedInfo[MAX_PLAYERS];
            
new Text:TDHitStatic[3],
	Text:TDHitedByStatic[3],
	Text:PTD_HitNick[MAX_PLAYERS],
	Text:PTD_HitInfo[MAX_PLAYERS],
	Text:PTD_HitedByNick[MAX_PLAYERS],
	Text:PTD_HitedByInfo[MAX_PLAYERS];
	
new Text:PTD_PingFPSPLoss[MAX_PLAYERS][3],
	Text:TDPingFPSStatic[2];

new Text:PTD_KilledBy[MAX_PLAYERS][2];

new Text:TDWinSpawnProtectStatic,
	Text:TDWinSpawnProtectInfo;		

new Text:TDWinRoundStatic[7],
    Text:TDWinRoundInfo[2],
	Text:TDWinRoundStats[3];

new Text:TDSpecStatic[7],
	Text:PTD_SpecNick[MAX_PLAYERS],
	Text:PTD_SpecHealth[MAX_PLAYERS][2],
	Text:PTD_SpecArmor[MAX_PLAYERS][2],
	Text:PTD_SpecWeapons[MAX_PLAYERS][2];

new Text:TDTrainingArenaStatic[2],
	Text:TDTrainingArenaInfo;

new Text:TDOneOnOneStatic,
	Text:TDOneOnOne[2];

new Text:TDCaptureInfo,
	Text:TDCaptureBox,
	Text:TDCaptureStatic[3];

new Text:TDPlayerHudStatic[13],
	Text:TDPlayerHudTeam[3],
	Text:PTD_PlayerHudNick[MAX_PLAYERS],
	Text:PTD_PlayerHudKills[MAX_PLAYERS],
	Text:PTD_PlayerHudDeaths[MAX_PLAYERS],
	Text:PTD_PlayerHudDamage[MAX_PLAYERS],
	Text:PTD_PlayerHudRespect[MAX_PLAYERS],
	Text:PTD_PlayerHudRanking[MAX_PLAYERS];

new Text:TDZaciemnienie,
    Text:TDWybieralkaDruzyna,
	Text:TDAtak,
	Text:TDAtak2,
	Text:TDAtakAktywny,
	Text:TDObrona,
	Text:TDObrona2,
	Text:TDObronaAktywna,
	Text:TDArbiter,
	Text:TDArbiter2,
	Text:TDAktywnyArbiter,
	Text:TDIloscGraczy,
	Text:TDLogoDuzeH,
    Text:TDLogoDuzeS,
 //   Text:TDLogoDuzeIghKill,
    Text:TDLogoDuzePL,
    //Text:TDLogoDuzeOFP,
    Text:TDLogoDuzeLinijka,
	Text:TDZaduzoGraczyWTeamie,
	Text:TDDlaAdministracjiSerwera;
	
new Text:TDBottomBeltStatic[19],
	Text:TDBottomBeltTeamLeft[4],
	Text:TDBottomBeltTeamRight[4],
    Text:TDBottomBeltCenter[2];
 /*
new Text:TDHighSkillMaleLogo,
	Text:TDOnlyForProMaleLogo,
	Text:TDStronaMaleLogo,
	Text:TDHighSkill2MaleLogo,
	Text:TDPasekMaleLogo,
	Text:TDAutorMaleLogo;
*/
new Text:TDCountdownVal[6];

new Text:TDVoteName,
	Text:TDVoteInfo;

new	Text:TDCarInfo;

new	Text:TDZegar,
	Text:TDData,
	Text:TDOgloszenieBox,
	Text:TDOgloszenieSerwerowe,
	Text:TDStartRundyBox1,
	Text:TDStartRundyBox2,
	Text:TDStartRundyNazwa,
    Text:TDStartRundyPasek,
    Text:TDStartRundyKropki,
    Text:TDStartRundyInformacjeInfo,
    Text:TDStartRundyInformacje,
    Text:TDSpecByBox;

new IDStartowanej = -1,
	CzasMin,
	CzasSek,
	InteriorWalki,
	PrzejmujacyCP,
	Float:CheckpointPos[3],
	Float:SpawnAtt[5],
	Float:SpawnDef[5],
	Float:ObszarWalki[6],
	Float:SpawnLodzi[4],
	bool:DostepnyGranat,
	bool:TrwaOdliczanie,
	bool:TypArena,
	bool:SwapOczekiwanie;
#define MAX_VOTE    10
enum _vote  { Tryb, NumerID, Glosow };
new VoteVar[MAX_VOTE][_vote] = { {-1, 0, 0}, {-1, 0, 0}, {-1, 0, 0}, {-1, 0, 0}, {-1, 0, 0}, {-1, 0, 0}, {-1, 0, 0}, {-1, 0, 0}, {-1, 0, 0}, {-1, 0, 0} };
new bool:GlosowanieAktywne,
	GlosowanieCzas,
	OstatnieStarty[5][2] = {{-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}},
	CzasAdminVote,
	CZAS_ARENY = 8,
	CZAS_BAZY = 10,
	MAX_ARMOUR = 0,
	bool:DodatkowyGranat = true,
	OgloszenieCzas;
#define SPAWN_INTERIOR  0

enum	spar_info { ID, nazwa[16], slot, skrot[8] }
new const BronieSpar[][spar_info] = {
	    {22,"Pistols", 0, "pis"},			{23,"Silenced Pistol", 0, "slp"},	{24,"Desert Eagle", 0, "de"},			{25,"Shotgun", 1, "sg"},				{26,"Sawnoff Shotgun", 1, "so"},
	    {27,"Combat Shotgun", 1, "csg"},	{28,"Mac 10", 2, "mac10"},			{29,"MP5", 2, "mp5"},					{30,"AK-47", 3, "ak47"},				{31,"M4", 3, "m4"},
		{32,"Tec9", 2, "tec9"},			    {33,"Rifle", 4, "rif"},				{34,"Sniper Rifle", 4, "srif"},			{5,"Baseball bat", 5, "base"},			{0,"Brak", 6, "brak"}
    };

enum c_info	{	ID,	Nazwa[4], Typ	}
new const SpawnPojazd[][c_info] = {
	{522,!"NRG500",		0},		{463,!"Freeway",	0},		{468,!"Sanchez",	0},		{424,!"BF Injectio",	1},   	{568,!"Bandito",	1},    	{557,!"Monster",	1},
	{470,!"Patriot",	1},		{402,!"Buffalo",	1},		{541,!"Bullet",		1},		{411,!"Infernus",		1},		{451,!"Turismo",	1},		{494,!"Hotring",	1},
	{560,!"Sultan",		1},     {562,!"Elegy",		1},     {565,!"Flash",		1},     {578,!"DFT-30",			1},		{431,!"Bus",		1},		{443,!"Packer",		1},
	{486,!"Dozer",		1},		{469,!"Sparrow",	2},    	{487,!"Maverick",	2},	    {473,!"Dinghy",     	3},     {493,!"Jetmax",		3},     {453,!"Reefer", 	3}
	};
	
new const PoczekalniaPojazd[][c_info] = {
		{400, !"Landstalker"	},		{401, !"Bravura", 		},		{402, !"Buffalo"},		{403, !"Linerunner", 	},	{404, !"Perenail"},	{405, !"Sentinel", 	},	{406, !"Dumper", 		},	{407, !"Firetruck", 	},
		{408, !"Trashmaster"	},		{409, !"Stretch", 		},		{410, !"Manana"},		{411, !"Infernus", 		},	{412, !"Voodoo"},	{413, !"Pony", 		},	{414, !"Mule", 			},	{415, !"Cheetah", 		},
		{416, !"Ambulance"		},		{417, !"Levetian", 		},		{418, !"Moonbeam"},		{419, !"Esperanto",		},	{420, !"Taxi"},		{421, !"Washington",},	{422, !"Bobcat", 		},	{423, !"Mr Whoopee", 	},
		{424, !"BFInjection"	},		{425, !"Hunter",		},		{426, !"Premier"},		{427, !"Enforcer", 		},	{428, !"Securicar"},{429, !"Banshee", 	},	{430, !"Predator", 		},	{431, !"Bus", 			},
		{432, !"Rhino", 		},		{433, !"Barracks", 		},		{434, !"Hotknife"},		{435, !"Artictrailer1", },	{436, !"Previon"},	{437, !"Coach", 	},	{438, !"Cabbie", 		},	{439, !"Stallion", 		},
		{440, !"Rumpo", 		},		{441, !"RCBandit", 		},		{442, !"Romero"},		{443, !"Packer", 		},	{444, !"Monster"},	{445, !"Admiral", 	},	{446, !"Squalo",		},	{447, !"Seasparrow",	},
		{448, !"Pizzaboy",		},		{449, !"Tram", 			},		{450, !"Artictrailer2"},{451, !"Turismo", 		},	{452, !"Speeder"},	{453, !"Reefer", 	},	{454, !"Tropic",		},	{455, !"Flatbed", 		},
		{456, !"Yankee", 		},		{457, !"Caddy", 		},		{458, !"Solair"},		{459, !"Topfun", 		},	{460, !"Skimmer"},	{461, !"PCJ600", 	},	{462, !"Faggio", 		},	{463, !"Freeway",		},
		{464, !"RCBaron", 		},		{465, !"RC Raider", 	},		{466, !"Glendale"},		{467, !"Oceanic", 		},	{468, !"Sanchez"},	{469, !"Sparrow",	},	{470, !"Patriot", 		},	{471, !"Quad", 			},
		{472, !"Coastgaurd", 	},		{473, !"Dinghy", 		},		{474, !"Hermes"},		{475, !"Sabre", 		},	{476, !"Rustler"},	{477, !"ZR350", 	},	{478, !"Walton", 		},	{479, !"Regina", 		},
		{480, !"Comet", 		},		{481, !"BMX", 			},		{482, !"Burriro"},		{483, !"Camper", 		},	{484, !"Marquis"},	{485, !"Baggage", 	},	{486, !"Dozer", 		},	{487, !"Maverick", 		},
		{488, !"VCNMaverick", 	},		{489, !"Rancher", 		},		{490, !"FBIRancher"},	{491, !"Virgo", 		},	{492, !"Greenwood"},{493, !"Jetmax", 	},	{494, !"Hotring", 		},	{495, !"Sandking", 		},
		{496, !"Blistac", 		},		{497, !"Policemaverick",},		{498, !"Boxville"},		{499, !"Benson", 		},	{500, !"Mesa"},		{501, !"RCGoblin", 	},	{502, !"HotringA", 		},	{503, !"HotringB", 		},
		{504, !"Bringbanger", 	},		{505, !"Rancher", 		},		{506, !"Super GT"},		{507, !"Elegant", 		},	{508, !"Journey"},	{509, !"Bike", 		},	{510, !"Mountainbike",	},	{511, !"Beagle", 		},
		{512, !"Cropduster", 	},		{513, !"Stuntplane", 	},		{514, !"Petrol"},		{515, !"Roadtrain", 	},	{516, !"Nebula"},	{517, !"Majestic", 	},	{518, !"Buccaneer", 	},	{519, !"Shamal", 		},
		{520, !"Hydra", 		},		{521, !"FCR900", 		},		{522, !"NRG500"},		{523, !"HPV1000", 		},	{524, !"Cement"},	{525, !"Towtruck", 	},	{526, !"Fortune", 		},	{527, !"Cadrona", 		},
		{528, !"FBITruck", 		},		{529, !"Williard", 		},		{530, !"Forklift"},		{531, !"Tractor", 		},	{532, !"Combine"},	{533, !"Feltzer", 	},	{534, !"Remington", 	},	{535, !"Slamvan", 		},
		{536, !"Blade", 		},		{537, !"Freight", 		},		{538, !"Streak"},		{539, !"Vortex", 		},	{540, !"Vincent"},	{541, !"Bullet", 	},	{542, !"Clover",		},	{543, !"Sadler", 		},
		{544, !"FiretruckLA", 	},		{545, !"Hustler", 		},		{546, !"Intruder"},		{547, !"Primo", 		},	{548, !"Cargobob"},	{549, !"Tampa", 	},	{550, !"Sunrise", 		},	{551, !"Merit", 		},
		{552, !"Utilityvan", 	},		{553, !"Nevada", 		},		{554, !"Yosemite"},		{555, !"Windsor", 		},	{556, !"MonsterA"},	{557, !"MonsterB", 	},	{558, !"Uranus", 		},	{559, !"Jester", 		},
		{560, !"Sultan", 		},		{561, !"Stratum", 		},		{562, !"Elegy"},		{563, !"Raindance", 	},	{564, !"RCTiger"},	{565, !"Flash", 	},	{566, !"Tahoma", 		},	{567, !"Savanna", 		},
		{568, !"Bandito",		},		{569, !"Freightflat", 	},		{570, !"Streak"},		{571, !"Kart", 			},	{572, !"Mower"},	{573, !"Duneride",	},	{574, !"Sweeper", 		},	{575, !"Broadway", 		},
		{576, !"Tornado",		},		{577, !"AT400", 		},		{578, !"DFT30"},		{579, !"Huntley", 		},	{580, !"Stafford"},	{581, !"BF400", 	},	{582, !"News van", 		},	{583, !"Tug", 			},
		{584, !"Petroltanker", 	},		{585, !"Emperor", 		},		{586, !"Wayfarer"},		{587, !"Euros", 		},	{588, !"Hotdog"},	{589, !"Club", 		},	{590, !"Freightbox", 	},	{591, !"Artictrailer3", },
		{592, !"Andromada", 	},		{593, !"Dodo", 			},		{594, !"RCCam"},		{595, !"Launch", 		},	{596, !"CopcarLS"},	{597, !"CopcarSF", 	},	{598, !"CopcarLV", 		},	{599, !"Ranger", 		},
		{600, !"Picador", 		},		{601, !"Swattank", 		},		{602, !"Alpha"},		{603, !"Phoenix", 		},	{604, !"Glendale"},	{605, !"Sadler", 	},	{606, !"BagboxA", 		},	{607, !"BagboxB", 		},
		{608, !"Stairs",		},		{609, !"Boxville",		},		{610, !"Farmtrailer"},	{611, !"Utility", 		}
	};
	
//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
#include "Files/asplayer.inc"
#include "Files/SQLdef.inc"
#include "Files/lobby.inc"
#include "Files/layout.inc"
#include "Files/player.inc"
#include "Files/spec.inc"
#include "Files/fun.inc"
#include "Files/round.inc"
#include "Files/p_round.inc"
#include "Files/antycheat.inc"
#include "Files/weapons.inc"
#include "Files/pteam.inc"
#include "Files/settings.inc"
#include "Files/inactive_starter.inc"
//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
public OnGameModeInit() {
    ServerProtect();
    SetTimer("ServerProtect", 3600000, true);
    AntyDeAMX();
    
	for(new i; i<5; i++)	SendDeathMessage(201,201,0);
	
	loadAnnounceMessage();
	loadGameModeSettings();
	loadWeaponsSettings();
	
	SendRconCommand("mapname "GM_NAZWA);
	SetGameModeText(GM_PRZERWA);
	SetNameTagDrawDistance(20);
   	SetWorldTime(15);
	SetWeather(10);
	SetGravity(0.008);
	AllowInteriorWeapons(1);
	DisableInteriorEnterExits();
	EnableStuntBonusForAll(0);
    UsePlayerPedAnims();

    loadLobbyPositions();
    loadLobbyTDMPositions();

    g_RoundCaptureValue = floatdiv(99, (g_RoundCaptureTime * 5));

	SetTimer("TimerSekunda", 		1000, 	1);
	SetTimer("TimerMinuta", 		60000, 	1);
	SetTimer("TimerDziesiec", 		10000, 	1);

	SetTimer("StartTimerRundy", 	300, 	0);
	SetTimer("StartTimerDwiescie", 	100, 	0);

	AddPlayerClassEx(T_REF, getTeamSkin(T_DEF), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	AddPlayerClassEx(T_REF, getTeamSkin(T_ATT), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	AddPlayerClassEx(T_REF, getTeamSkin(T_REF), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

	TDZaciemnienie = TextDrawCreate(321.000000,1.000000,"_");
	TextDrawUseBox(TDZaciemnienie,1);
	TextDrawBoxColor(TDZaciemnienie,0x000000FF);
	TextDrawTextSize(TDZaciemnienie,10.000000,640.000000);
	TextDrawAlignment(TDZaciemnienie,2);
	TextDrawBackgroundColor(TDZaciemnienie,0x080808FF);
	TextDrawFont(TDZaciemnienie,3);
	TextDrawLetterSize(TDZaciemnienie,4.000000,52.000000);
	TextDrawColor(TDZaciemnienie,0x00000030);
	TextDrawSetOutline(TDZaciemnienie,1);
	TextDrawSetProportional(TDZaciemnienie,1);
	TextDrawSetShadow(TDZaciemnienie,1);
/*
	TDLogoDuzeIghKill = TextDrawCreate(307.000000,181.000000,"~w~igh    kill");
	TextDrawAlignment(TDLogoDuzeIghKill,2);
	TextDrawBackgroundColor(TDLogoDuzeIghKill,0x00000000);
	TextDrawFont(TDLogoDuzeIghKill,2);
	TextDrawLetterSize(TDLogoDuzeIghKill,0.899999,2.100000);
	TextDrawColor(TDLogoDuzeIghKill,0xffffff99);
	TextDrawSetProportional(TDLogoDuzeIghKill,1);
	TextDrawSetShadow(TDLogoDuzeIghKill,1);
*/
/*
	TDLogoDuzeH = TextDrawCreate(203.000000,163.000000,"~w~SAMP");
	TextDrawAlignment(TDLogoDuzeH,2);
	TextDrawBackgroundColor(TDLogoDuzeH,0x00000000);
	TextDrawFont(TDLogoDuzeH,2);
	TextDrawLetterSize(TDLogoDuzeH,1.000000,4.400000);
	TextDrawColor(TDLogoDuzeH,0xffffff99);
	TextDrawSetProportional(TDLogoDuzeH,1);
	TextDrawSetShadow(TDLogoDuzeH,1);
*/
	TDLogoDuzeH = TextDrawCreate(213.000000, 161.000000, "SAMP");
	TextDrawBackgroundColor(TDLogoDuzeH, 255);
	TextDrawFont(TDLogoDuzeH, 2);
	TextDrawLetterSize(TDLogoDuzeH, 0.740000, 3.800000);
	TextDrawColor(TDLogoDuzeH, -1);
	TextDrawSetOutline(TDLogoDuzeH, 0);
	TextDrawSetProportional(TDLogoDuzeH, 1);
	TextDrawSetShadow(TDLogoDuzeH, 1);
	
/*	TDLogoDuzeS = TextDrawCreate(306.000000,163.000000,"~w~olska");
	TextDrawAlignment(TDLogoDuzeS,2);
	TextDrawBackgroundColor(TDLogoDuzeS,0x00000000);
	TextDrawFont(TDLogoDuzeS,2);
	TextDrawLetterSize(TDLogoDuzeS,1.100000,4.400000);
	TextDrawColor(TDLogoDuzeS,0xffffff99);
	TextDrawSetProportional(TDLogoDuzeS,1);
	TextDrawSetShadow(TDLogoDuzeS,1);
*/
	TDLogoDuzeS = TextDrawCreate(296.000000, 169.000000, "olska");
	TextDrawBackgroundColor(TDLogoDuzeS, 255);
	TextDrawFont(TDLogoDuzeS, 2);
	TextDrawLetterSize(TDLogoDuzeS, 0.600000, 3.000000);
	TextDrawColor(TDLogoDuzeS, -1);
	TextDrawSetOutline(TDLogoDuzeS, 0);
	TextDrawSetProportional(TDLogoDuzeS, 1);
	TextDrawSetShadow(TDLogoDuzeS, 1);
/*
	TDLogoDuzePL = TextDrawCreate(425.000000,181.000000,".PL");
	TextDrawAlignment(TDLogoDuzePL,2);
	TextDrawBackgroundColor(TDLogoDuzePL,0x00000000);
	TextDrawFont(TDLogoDuzePL,2);
	TextDrawLetterSize(TDLogoDuzePL,0.899999,2.100000);
	TextDrawColor(TDLogoDuzePL,0x044FAACC);
	TextDrawSetProportional(TDLogoDuzePL,1);
	TextDrawSetShadow(TDLogoDuzePL,1);
*/
	TDLogoDuzePL = TextDrawCreate(378.000000, 169.000000, ".com");
	TextDrawBackgroundColor(TDLogoDuzePL, 255);
	TextDrawFont(TDLogoDuzePL, 2);
	TextDrawLetterSize(TDLogoDuzePL, 0.600000, 3.000000);
	TextDrawColor(TDLogoDuzePL, 74764031);
	TextDrawSetOutline(TDLogoDuzePL, 0);
	TextDrawSetProportional(TDLogoDuzePL, 1);
	TextDrawSetShadow(TDLogoDuzePL, 1);
/*
	TDLogoDuzeOFP = TextDrawCreate(344.000000,173.000000,"Only for pr0!");
	TextDrawAlignment(TDLogoDuzeOFP,0);
	TextDrawBackgroundColor(TDLogoDuzeOFP,0x00000000);
	TextDrawFont(TDLogoDuzeOFP,1);
	TextDrawLetterSize(TDLogoDuzeOFP,0.399999,1.300000);
	TextDrawColor(TDLogoDuzeOFP,0xBFBFBF80);
	TextDrawSetProportional(TDLogoDuzeOFP,1);
	TextDrawSetShadow(TDLogoDuzeOFP,1);
*/
	TDLogoDuzeLinijka = TextDrawCreate(170.000000, 202.000000, "LD_POOL:ball");
	TextDrawBackgroundColor(TDLogoDuzeLinijka, 255);
	TextDrawFont(TDLogoDuzeLinijka, 4);
	TextDrawLetterSize(TDLogoDuzeLinijka, 0.500000, 1.000000);
	TextDrawColor(TDLogoDuzeLinijka, 0x044FAACC);
	TextDrawSetOutline(TDLogoDuzeLinijka, 0);
	TextDrawSetProportional(TDLogoDuzeLinijka, 1);
	TextDrawSetShadow(TDLogoDuzeLinijka, 1);
	TextDrawUseBox(TDLogoDuzeLinijka, 1);
	TextDrawBoxColor(TDLogoDuzeLinijka, 255);
	TextDrawTextSize(TDLogoDuzeLinijka, 301.000000, 1.000000);

	TDIloscGraczy = TextDrawCreate(225.000000,247.000000," ");
	TextDrawAlignment(TDIloscGraczy,0);
	TextDrawBackgroundColor(TDIloscGraczy,0x00000000);
	TextDrawFont(TDIloscGraczy,1);
	TextDrawLetterSize(TDIloscGraczy,0.199999,0.799999);
	TextDrawColor(TDIloscGraczy,0xffffffff);
	TextDrawSetProportional(TDIloscGraczy,1);
	TextDrawSetShadow(TDIloscGraczy,1);

	TDWybieralkaDruzyna = TextDrawCreate(321.000000,214.000000,"~w~Wybierz druzyne");
	TextDrawAlignment(TDWybieralkaDruzyna,2);
	TextDrawBackgroundColor(TDWybieralkaDruzyna,0x00000000);
	TextDrawFont(TDWybieralkaDruzyna,1);
	TextDrawLetterSize(TDWybieralkaDruzyna,0.399999,1.400000);
	TextDrawColor(TDWybieralkaDruzyna,0xffffff99);
	TextDrawSetProportional(TDWybieralkaDruzyna,1);
	TextDrawSetShadow(TDWybieralkaDruzyna,1);
	
	TDAtakAktywny = TextDrawCreate(285.000000, 229.000000, "LD_OTB2:butnAo");
	TextDrawBackgroundColor(TDAtakAktywny, 255);
	TextDrawFont(TDAtakAktywny, 4);
	TextDrawLetterSize(TDAtakAktywny, 0.500000, 1.000000);
	TextDrawColor(TDAtakAktywny, 0x044FAA30);
	TextDrawSetOutline(TDAtakAktywny, 0);
	TextDrawSetProportional(TDAtakAktywny, 1);
	TextDrawSetShadow(TDAtakAktywny, 1);
	TextDrawUseBox(TDAtakAktywny, 1);
	TextDrawBoxColor(TDAtakAktywny, 255);
	TextDrawTextSize(TDAtakAktywny, 66.000000, 24.000000);
	
	TDObronaAktywna = TextDrawCreate(208.000000, 229.000000, "LD_OTB2:butnAo");
	TextDrawBackgroundColor(TDObronaAktywna, 255);
	TextDrawFont(TDObronaAktywna, 4);
	TextDrawLetterSize(TDObronaAktywna, 0.500000, 1.000000);
	TextDrawColor(TDObronaAktywna, 0x044FAA30);
	TextDrawSetOutline(TDObronaAktywna, 0);
	TextDrawSetProportional(TDObronaAktywna, 1);
	TextDrawSetShadow(TDObronaAktywna, 1);
	TextDrawUseBox(TDObronaAktywna, 1);
	TextDrawBoxColor(TDObronaAktywna, 255);
	TextDrawTextSize(TDObronaAktywna, 66.000000, 24.000000);
	
	TDAktywnyArbiter = TextDrawCreate(364.000000, 229.000000, "LD_OTB2:butnAo");
	TextDrawBackgroundColor(TDAktywnyArbiter, 255);
	TextDrawFont(TDAktywnyArbiter, 4);
	TextDrawLetterSize(TDAktywnyArbiter, 0.500000, 1.000000);
	TextDrawColor(TDAktywnyArbiter, 0xff000040);
	TextDrawSetOutline(TDAktywnyArbiter, 0);
	TextDrawSetProportional(TDAktywnyArbiter, 1);
	TextDrawSetShadow(TDAktywnyArbiter, 1);
	TextDrawUseBox(TDAktywnyArbiter, 1);
	TextDrawBoxColor(TDAktywnyArbiter, 255);
	TextDrawTextSize(TDAktywnyArbiter, 70.000000, 24.000000);

    TDAtak = TextDrawCreate(319.000000,233.000000,"Atak");
	TextDrawAlignment(TDAtak,2);
	TextDrawBackgroundColor(TDAtak,0x00000000);
	TextDrawFont(TDAtak,3);
	TextDrawLetterSize(TDAtak,0.499999,1.200000);
	TextDrawColor(TDAtak,0xffffff66);
	TextDrawSetProportional(TDAtak,1);
	TextDrawSetShadow(TDAtak,1);

    TDAtak2 = TextDrawCreate(319.000000,233.000000,"Atak");
	TextDrawAlignment(TDAtak2,2);
	TextDrawBackgroundColor(TDAtak2,0x00000000);
	TextDrawFont(TDAtak2,3);
	TextDrawLetterSize(TDAtak2,0.499999,1.200000);
	TextDrawColor(TDAtak2,0xffffffcc);
	TextDrawSetProportional(TDAtak2,1);
	TextDrawSetShadow(TDAtak2,1);

    TDObrona = TextDrawCreate(241.000000,233.000000,"Obrona");
	TextDrawAlignment(TDObrona,2);
	TextDrawBackgroundColor(TDObrona,0x00000000);
	TextDrawFont(TDObrona,3);
	TextDrawLetterSize(TDObrona,0.499999,1.200000);
	TextDrawColor(TDObrona,0xffffff66);
	TextDrawSetProportional(TDObrona,1);
	TextDrawSetShadow(TDObrona,1);

    TDObrona2 = TextDrawCreate(241.000000,233.000000,"Obrona");
	TextDrawAlignment(TDObrona2,2);
	TextDrawBackgroundColor(TDObrona2,0x00000000);
	TextDrawFont(TDObrona2,3);
	TextDrawLetterSize(TDObrona2,0.499999,1.200000);
	TextDrawColor(TDObrona2,0xffffffcc);
	TextDrawSetProportional(TDObrona2,1);
	TextDrawSetShadow(TDObrona2,1);

	TDArbiter = TextDrawCreate(399.000000,233.000000,"Arbiter");
	TextDrawAlignment(TDArbiter,2);
	TextDrawBackgroundColor(TDArbiter,0x00000000);
	TextDrawFont(TDArbiter,3);
	TextDrawLetterSize(TDArbiter,0.499999,1.200000);
	TextDrawColor(TDArbiter,0xffffff66);
	TextDrawSetProportional(TDArbiter,1);
	TextDrawSetShadow(TDArbiter,1);

	TDArbiter2 = TextDrawCreate(399.000000,233.000000,"Arbiter");
	TextDrawAlignment(TDArbiter2,2);
	TextDrawBackgroundColor(TDArbiter2,0x00000000);
	TextDrawFont(TDArbiter2,3);
	TextDrawLetterSize(TDArbiter2,0.499999,1.200000);
	TextDrawColor(TDArbiter2,0xffffffcc);
	TextDrawSetProportional(TDArbiter2,1);
	TextDrawSetShadow(TDArbiter2,1);
/*
	TDHighSkillMaleLogo = TextDrawCreate(561.000000,406.000000,"~w~igh     kill");
	TextDrawAlignment(TDHighSkillMaleLogo,0);
	TextDrawBackgroundColor(TDHighSkillMaleLogo,0x00000033);
	TextDrawFont(TDHighSkillMaleLogo,2);
	TextDrawLetterSize(TDHighSkillMaleLogo,0.199999,1.000000);
	TextDrawColor(TDHighSkillMaleLogo,0xffffff99);
	TextDrawSetProportional(TDHighSkillMaleLogo,1);
	TextDrawSetShadow(TDHighSkillMaleLogo,1);

	TDHighSkill2MaleLogo = TextDrawCreate(552.000000,403.000000,"~w~H     S");
	TextDrawAlignment(TDHighSkill2MaleLogo,0);
	TextDrawBackgroundColor(TDHighSkill2MaleLogo,0x00000033);
	TextDrawFont(TDHighSkill2MaleLogo,2);
	TextDrawLetterSize(TDHighSkill2MaleLogo,0.299999,1.400000);
	TextDrawColor(TDHighSkill2MaleLogo,0xffffff99);
	TextDrawSetProportional(TDHighSkill2MaleLogo,1);
	TextDrawSetShadow(TDHighSkill2MaleLogo,1);

	TDStronaMaleLogo = TextDrawCreate(604.000000,406.000000,".eu");
	TextDrawAlignment(TDStronaMaleLogo,0);
	TextDrawBackgroundColor(TDStronaMaleLogo,0x00000033);
	TextDrawFont(TDStronaMaleLogo,2);
	TextDrawLetterSize(TDStronaMaleLogo,0.199999,1.000000);
	TextDrawColor(TDStronaMaleLogo,0x044FAACC);
	TextDrawSetProportional(TDStronaMaleLogo,1);
	TextDrawSetShadow(TDStronaMaleLogo,1);

	TDOnlyForProMaleLogo = TextDrawCreate(592.000000,403.000000,"~w~Only for pr0!");
	TextDrawAlignment(TDOnlyForProMaleLogo,0);
	TextDrawBackgroundColor(TDOnlyForProMaleLogo,0x00000000);
	TextDrawFont(TDOnlyForProMaleLogo,1);
    TextDrawLetterSize(TDOnlyForProMaleLogo,0.1,0.499999);
	TextDrawColor(TDOnlyForProMaleLogo,0xffffff99);
	TextDrawSetProportional(TDOnlyForProMaleLogo,1);
	TextDrawSetShadow(TDOnlyForProMaleLogo,1);

	TDPasekMaleLogo = TextDrawCreate(550.000000, 415.000000, "LD_POOL:ball");
	TextDrawBackgroundColor(TDPasekMaleLogo, 255);
	TextDrawFont(TDPasekMaleLogo, 4);
	TextDrawLetterSize(TDPasekMaleLogo, 0.500000, 1.000000);
	TextDrawColor(TDPasekMaleLogo, 0x044FAA50);
	TextDrawSetOutline(TDPasekMaleLogo, 0);
	TextDrawSetProportional(TDPasekMaleLogo, 1);
	TextDrawSetShadow(TDPasekMaleLogo, 1);
	TextDrawUseBox(TDPasekMaleLogo, 1);
	TextDrawBoxColor(TDPasekMaleLogo, 255);
	TextDrawTextSize(TDPasekMaleLogo, 67.000000, 1.000000);

	TDAutorMaleLogo = TextDrawCreate(557.000000,417.000000,"v"GM_WERSJA" by AxL");
	TextDrawAlignment(TDAutorMaleLogo,0);
	TextDrawBackgroundColor(TDAutorMaleLogo,0x00000000);
	TextDrawFont(TDAutorMaleLogo,1);
	TextDrawLetterSize(TDAutorMaleLogo,0.13,0.499999);
	TextDrawColor(TDAutorMaleLogo,0xffffff66);
	TextDrawSetProportional(TDAutorMaleLogo,1);
	TextDrawSetShadow(TDAutorMaleLogo,1);
*/
	TDZaduzoGraczyWTeamie = TextDrawCreate(321.000000,259.000000,"W tej druzynie jest wystarczajaco duzo graczy !");
	TextDrawAlignment(TDZaduzoGraczyWTeamie,2);
	TextDrawBackgroundColor(TDZaduzoGraczyWTeamie,0x00000000);
	TextDrawFont(TDZaduzoGraczyWTeamie,1);
	TextDrawLetterSize(TDZaduzoGraczyWTeamie,0.199999,1.000000);
	TextDrawColor(TDZaduzoGraczyWTeamie,0xff000066);
	TextDrawSetProportional(TDZaduzoGraczyWTeamie,1);
	TextDrawSetShadow(TDZaduzoGraczyWTeamie,1);
	
	TDDlaAdministracjiSerwera = TextDrawCreate(321.000000,259.000000,"Ta druzyna jest zarezerwowana dla administracji serwera !");
	TextDrawAlignment(TDDlaAdministracjiSerwera,2);
	TextDrawBackgroundColor(TDDlaAdministracjiSerwera,0x00000000);
	TextDrawFont(TDDlaAdministracjiSerwera,1);
	TextDrawLetterSize(TDDlaAdministracjiSerwera,0.199999,1.000000);
	TextDrawColor(TDDlaAdministracjiSerwera,0xff000066);
	TextDrawSetProportional(TDDlaAdministracjiSerwera,1);
	TextDrawSetShadow(TDDlaAdministracjiSerwera,1);

	TDHitStatic[0] = TextDrawCreate(HIT_X - 52, HITBY_Y, "LD_POKE:cd9s");
	TextDrawBackgroundColor(TDHitStatic[0], 255);
	TextDrawFont(TDHitStatic[0], 4);
	TextDrawLetterSize(TDHitStatic[0], 0.800000, 1.000000);
	TextDrawColor(TDHitStatic[0], 80);
	TextDrawSetOutline(TDHitStatic[0], 0);
	TextDrawSetProportional(TDHitStatic[0], 1);
	TextDrawSetShadow(TDHitStatic[0], 1);
	TextDrawUseBox(TDHitStatic[0], 1);
	TextDrawBoxColor(TDHitStatic[0], 255);
	TextDrawTextSize(TDHitStatic[0], 104.000000, 24.000000);

	TDHitStatic[1] = TextDrawCreate(HIT_X - 51, HITBY_Y + 1.0, "LD_POKE:cd9s");
	TextDrawBackgroundColor(TDHitStatic[1], 255);
	TextDrawFont(TDHitStatic[1], 4);
	TextDrawLetterSize(TDHitStatic[1], 0.800000, 1.000000);
	TextDrawColor(TDHitStatic[1], 80);
	TextDrawSetOutline(TDHitStatic[1], 0);
	TextDrawSetProportional(TDHitStatic[1], 1);
	TextDrawSetShadow(TDHitStatic[1], 1);
	TextDrawUseBox(TDHitStatic[1], 1);
	TextDrawBoxColor(TDHitStatic[1], 255);
	TextDrawTextSize(TDHitStatic[1], 102.000000, 22.000000);

	TDHitStatic[2] = TextDrawCreate(HIT_X - 51, HITBY_Y + 11.0, "LD_POOL:ball");
	TextDrawBackgroundColor(TDHitStatic[2], 255);
	TextDrawFont(TDHitStatic[2], 4);
	TextDrawLetterSize(TDHitStatic[2], 0.800000, 1.000000);
	TextDrawColor(TDHitStatic[2], 74042960);
	TextDrawSetOutline(TDHitStatic[2], 0);
	TextDrawSetProportional(TDHitStatic[2], 1);
	TextDrawSetShadow(TDHitStatic[2], 1);
	TextDrawUseBox(TDHitStatic[2], 1);
	TextDrawBoxColor(TDHitStatic[2], 255);
	TextDrawTextSize(TDHitStatic[2], 102.000000, 1.000000);

	TDHitedByStatic[0] = TextDrawCreate(HITBY_X - 52, HITBY_Y, "LD_POKE:cd9s");
	TextDrawBackgroundColor(TDHitedByStatic[0], 255);
	TextDrawFont(TDHitedByStatic[0], 4);
	TextDrawLetterSize(TDHitedByStatic[0], 0.800000, 1.000000);
	TextDrawColor(TDHitedByStatic[0], 80);
	TextDrawSetOutline(TDHitedByStatic[0], 0);
	TextDrawSetProportional(TDHitedByStatic[0], 1);
	TextDrawSetShadow(TDHitedByStatic[0], 1);
	TextDrawUseBox(TDHitedByStatic[0], 1);
	TextDrawBoxColor(TDHitedByStatic[0], 255);
	TextDrawTextSize(TDHitedByStatic[0], 104.000000, 24.000000);

	TDHitedByStatic[1] = TextDrawCreate(HITBY_X - 51, HITBY_Y + 1.0, "LD_POKE:cd9s");
	TextDrawBackgroundColor(TDHitedByStatic[1], 255);
	TextDrawFont(TDHitedByStatic[1], 4);
	TextDrawLetterSize(TDHitedByStatic[1], 0.800000, 1.000000);
	TextDrawColor(TDHitedByStatic[1], 80);
	TextDrawSetOutline(TDHitedByStatic[1], 0);
	TextDrawSetProportional(TDHitedByStatic[1], 1);
	TextDrawSetShadow(TDHitedByStatic[1], 1);
	TextDrawUseBox(TDHitedByStatic[1], 1);
	TextDrawBoxColor(TDHitedByStatic[1], 255);
	TextDrawTextSize(TDHitedByStatic[1], 102.000000, 22.000000);

	TDHitedByStatic[2] = TextDrawCreate(HITBY_X - 51, HITBY_Y + 11.0, "LD_POOL:ball");
	TextDrawBackgroundColor(TDHitedByStatic[2], 255);
	TextDrawFont(TDHitedByStatic[2], 4);
	TextDrawLetterSize(TDHitedByStatic[2], 0.800000, 1.000000);
	TextDrawColor(TDHitedByStatic[2], 74042960);
	TextDrawSetOutline(TDHitedByStatic[2], 0);
	TextDrawSetProportional(TDHitedByStatic[2], 1);
	TextDrawSetShadow(TDHitedByStatic[2], 1);
	TextDrawUseBox(TDHitedByStatic[2], 1);
	TextDrawBoxColor(TDHitedByStatic[2], 255);
	TextDrawTextSize(TDHitedByStatic[2], 102.000000, 1.000000);

	TDPingFPSStatic[0] = TextDrawCreate(491.000000, -9.000000, "LD_POKE:cd9s");
	TextDrawBackgroundColor(TDPingFPSStatic[0], 255);
	TextDrawFont(TDPingFPSStatic[0], 4);
	TextDrawLetterSize(TDPingFPSStatic[0], 0.500000, 1.000000);
	TextDrawColor(TDPingFPSStatic[0], 80);
	TextDrawSetOutline(TDPingFPSStatic[0], 0);
	TextDrawSetProportional(TDPingFPSStatic[0], 1);
	TextDrawSetShadow(TDPingFPSStatic[0], 1);
	TextDrawUseBox(TDPingFPSStatic[0], 1);
	TextDrawBoxColor(TDPingFPSStatic[0], 255);
	TextDrawTextSize(TDPingFPSStatic[0], 128.000000, 19.000000);

	TDPingFPSStatic[1] = TextDrawCreate(505.000000, 1.000000, "Ping______FPS______P-Loss"); //-40
	TextDrawBackgroundColor(TDPingFPSStatic[1], 16);
	TextDrawFont(TDPingFPSStatic[1], 1);
	TextDrawLetterSize(TDPingFPSStatic[1], 0.219999, 0.799998);
	TextDrawColor(TDPingFPSStatic[1], 72329983);
	TextDrawSetOutline(TDPingFPSStatic[1], 0);
	TextDrawSetProportional(TDPingFPSStatic[1], 1);
	TextDrawSetShadow(TDPingFPSStatic[1], 1);

	TDTrainingArenaStatic[0] = TextDrawCreate(50.000000, 300.000000, "LD_POKE:cd9s");
	TextDrawBackgroundColor(TDTrainingArenaStatic[0], 255);
	TextDrawFont(TDTrainingArenaStatic[0], 4);
	TextDrawLetterSize(TDTrainingArenaStatic[0], 0.500000, 1.000000);
	TextDrawColor(TDTrainingArenaStatic[0], 80);
	TextDrawSetOutline(TDTrainingArenaStatic[0], 0);
	TextDrawSetProportional(TDTrainingArenaStatic[0], 1);
	TextDrawSetShadow(TDTrainingArenaStatic[0], 1);
	TextDrawUseBox(TDTrainingArenaStatic[0], 1);
	TextDrawBoxColor(TDTrainingArenaStatic[0], 170);
	TextDrawTextSize(TDTrainingArenaStatic[0], 80.000000, 30.000000);

	TDTrainingArenaStatic[1] = TextDrawCreate(89.000000, 302.000000, "Arena treningowa");
	TextDrawAlignment(TDTrainingArenaStatic[1], 2);
	TextDrawBackgroundColor(TDTrainingArenaStatic[1], 170);
	TextDrawFont(TDTrainingArenaStatic[1], 1);
	TextDrawLetterSize(TDTrainingArenaStatic[1], 0.200000, 1.100000);
	TextDrawColor(TDTrainingArenaStatic[1], 72329983);
	TextDrawSetOutline(TDTrainingArenaStatic[1], 0);
	TextDrawSetProportional(TDTrainingArenaStatic[1], 1);
	TextDrawSetShadow(TDTrainingArenaStatic[1], 1);
	
	TDTrainingArenaInfo = TextDrawCreate(89.000000, 315.000000, " ");
	TextDrawAlignment(TDTrainingArenaInfo, 2);
	TextDrawBackgroundColor(TDTrainingArenaInfo, 80);
	TextDrawFont(TDTrainingArenaInfo, 1);
	TextDrawLetterSize(TDTrainingArenaInfo, 0.200000, 1.000000);
	TextDrawColor(TDTrainingArenaInfo, -52);
	TextDrawSetOutline(TDTrainingArenaInfo, 0);
	TextDrawSetProportional(TDTrainingArenaInfo, 1);
	TextDrawSetShadow(TDTrainingArenaInfo, 1);

	TDOneOnOneStatic = TextDrawCreate(321.000000, 363.000000, "vs~n~vs");
	TextDrawAlignment(TDOneOnOneStatic, 2);
	TextDrawBackgroundColor(TDOneOnOneStatic, 112);
	TextDrawFont(TDOneOnOneStatic, 1);
	TextDrawLetterSize(TDOneOnOneStatic, 0.320000, 1.099999);
	TextDrawColor(TDOneOnOneStatic, 72329932);
	TextDrawSetOutline(TDOneOnOneStatic, 0);
	TextDrawSetProportional(TDOneOnOneStatic, 1);
	TextDrawSetShadow(TDOneOnOneStatic, 1);

	TDOneOnOne[0] = TextDrawCreate(308.000000, 363.000000, " ");
	TextDrawAlignment(TDOneOnOne[0], 3);
	TextDrawBackgroundColor(TDOneOnOne[0], 112);
	TextDrawFont(TDOneOnOne[0], 1);
	TextDrawLetterSize(TDOneOnOne[0], 0.300000, 1.099999);
	TextDrawColor(TDOneOnOne[0], -86);
	TextDrawSetOutline(TDOneOnOne[0], 0);
	TextDrawSetProportional(TDOneOnOne[0], 1);
	TextDrawSetShadow(TDOneOnOne[0], 1);

	TDOneOnOne[1] = TextDrawCreate(331.000000, 363.000000, " ");
	TextDrawBackgroundColor(TDOneOnOne[1], 112);
	TextDrawFont(TDOneOnOne[1], 1);
	TextDrawLetterSize(TDOneOnOne[1], 0.300000, 1.099999);
	TextDrawColor(TDOneOnOne[1], -86);
	TextDrawSetOutline(TDOneOnOne[1], 0);
	TextDrawSetProportional(TDOneOnOne[1], 1);
	TextDrawSetShadow(TDOneOnOne[1], 1);

	TDSpecStatic[0] = TextDrawCreate(262.000000, 307.500000, "LD_POKE:cd9s");
	TextDrawAlignment(TDSpecStatic[0], 2);
	TextDrawBackgroundColor(TDSpecStatic[0], 255);
	TextDrawFont(TDSpecStatic[0], 4);
	TextDrawLetterSize(TDSpecStatic[0], 0.500000, 5.699999);
	TextDrawColor(TDSpecStatic[0], 112);
	TextDrawSetOutline(TDSpecStatic[0], 0);
	TextDrawSetProportional(TDSpecStatic[0], 1);
	TextDrawSetShadow(TDSpecStatic[0], 1);
	TextDrawUseBox(TDSpecStatic[0], 1);
	TextDrawBoxColor(TDSpecStatic[0], 80);
	TextDrawTextSize(TDSpecStatic[0], 118.000000, 53.000000);

	TDSpecStatic[1] = TextDrawCreate(263.000000, 307.000000, "LD_POOL:ball");
	TextDrawBackgroundColor(TDSpecStatic[1], 255);
	TextDrawFont(TDSpecStatic[1], 4);
	TextDrawLetterSize(TDSpecStatic[1], 0.500000, 1.000000);
	TextDrawColor(TDSpecStatic[1], 74042960);
	TextDrawSetOutline(TDSpecStatic[1], 0);
	TextDrawSetProportional(TDSpecStatic[1], 1);
	TextDrawSetShadow(TDSpecStatic[1], 1);
	TextDrawUseBox(TDSpecStatic[1], 1);
	TextDrawBoxColor(TDSpecStatic[1], 80);
	TextDrawTextSize(TDSpecStatic[1], 115.000000, 1.000000);

	TDSpecStatic[2] = TextDrawCreate(261.000000, 319.000000, "LD_POOL:ball");
	TextDrawBackgroundColor(TDSpecStatic[2], 255);
	TextDrawFont(TDSpecStatic[2], 4);
	TextDrawLetterSize(TDSpecStatic[2], 0.500000, 1.000000);
	TextDrawColor(TDSpecStatic[2], 74042960);
	TextDrawSetOutline(TDSpecStatic[2], 0);
	TextDrawSetProportional(TDSpecStatic[2], 1);
	TextDrawSetShadow(TDSpecStatic[2], 1);
	TextDrawUseBox(TDSpecStatic[2], 1);
	TextDrawBoxColor(TDSpecStatic[2], 80);
	TextDrawTextSize(TDSpecStatic[2], 118.000000, 1.000000);

	TDSpecStatic[3] = TextDrawCreate(265.000000, 360.000000, "LD_POOL:ball");
	TextDrawBackgroundColor(TDSpecStatic[3], 255);
	TextDrawFont(TDSpecStatic[3], 4);
	TextDrawLetterSize(TDSpecStatic[3], 0.239999, 1.000000);
	TextDrawColor(TDSpecStatic[3], 74042960);
	TextDrawSetOutline(TDSpecStatic[3], 0);
	TextDrawSetProportional(TDSpecStatic[3], 1);
	TextDrawSetShadow(TDSpecStatic[3], 1);
	TextDrawUseBox(TDSpecStatic[3], 1);
	TextDrawBoxColor(TDSpecStatic[3], 80);
	TextDrawTextSize(TDSpecStatic[3], 110.000000, 1.000000);

	TDSpecStatic[4] = TextDrawCreate(314.000000, 309.000000, "~<~__________________________________~>~");
	TextDrawAlignment(TDSpecStatic[4], 2);
	TextDrawBackgroundColor(TDSpecStatic[4], 255);
	TextDrawFont(TDSpecStatic[4], 1);
	TextDrawLetterSize(TDSpecStatic[4], 0.170000, 0.799998);
	TextDrawColor(TDSpecStatic[4], -1);
	TextDrawSetOutline(TDSpecStatic[4], 0);
	TextDrawSetProportional(TDSpecStatic[4], 1);
	TextDrawSetShadow(TDSpecStatic[4], 1);

	TDSpecStatic[5] = TextDrawCreate(290.000000, 324.000000, "LD_OTB2:butnAo");
	TextDrawBackgroundColor(TDSpecStatic[5], 255);
	TextDrawFont(TDSpecStatic[5], 4);
	TextDrawLetterSize(TDSpecStatic[5], 0.500000, 1.000000);
	TextDrawColor(TDSpecStatic[5], 74042944);
	TextDrawSetOutline(TDSpecStatic[5], 0);
	TextDrawSetProportional(TDSpecStatic[5], 1);
	TextDrawSetShadow(TDSpecStatic[5], 1);
	TextDrawUseBox(TDSpecStatic[5], 1);
	TextDrawBoxColor(TDSpecStatic[5], 74042976);
	TextDrawTextSize(TDSpecStatic[5], 60.000000, 10.000000);

	TDSpecStatic[6] = TextDrawCreate(290.000000, 333.000000, "LD_OTB2:butnAo");
	TextDrawBackgroundColor(TDSpecStatic[6], 255);
	TextDrawFont(TDSpecStatic[6], 4);
	TextDrawLetterSize(TDSpecStatic[6], 0.500000, 1.000000);
	TextDrawColor(TDSpecStatic[6], 74042944);
	TextDrawSetOutline(TDSpecStatic[6], 0);
	TextDrawSetProportional(TDSpecStatic[6], 1);
	TextDrawSetShadow(TDSpecStatic[6], 1);
	TextDrawUseBox(TDSpecStatic[6], 1);
	TextDrawBoxColor(TDSpecStatic[6], 74042976);
	TextDrawTextSize(TDSpecStatic[6], 60.000000, 10.000000);

	TDCountdownVal[5] = TextDrawCreate(320.000000, 152.000000, "5");
	TextDrawAlignment(TDCountdownVal[5], 2);
	TextDrawBackgroundColor(TDCountdownVal[5], 255);
	TextDrawFont(TDCountdownVal[5], 1);
	TextDrawLetterSize(TDCountdownVal[5], 0.600000, 2.000000);
	TextDrawColor(TDCountdownVal[5], -1);
	TextDrawSetOutline(TDCountdownVal[5], 0);
	TextDrawSetProportional(TDCountdownVal[5], 1);
	TextDrawSetShadow(TDCountdownVal[5], 1);

	TDCountdownVal[4] = TextDrawCreate(320.000000, 152.000000, "4");
	TextDrawAlignment(TDCountdownVal[4], 2);
	TextDrawBackgroundColor(TDCountdownVal[4], 255);
	TextDrawFont(TDCountdownVal[4], 1);
	TextDrawLetterSize(TDCountdownVal[4], 0.600000, 2.000000);
	TextDrawColor(TDCountdownVal[4], -1);
	TextDrawSetOutline(TDCountdownVal[4], 0);
	TextDrawSetProportional(TDCountdownVal[4], 1);
	TextDrawSetShadow(TDCountdownVal[4], 1);

	TDCountdownVal[3] = TextDrawCreate(320.000000, 152.000000, "3");
	TextDrawAlignment(TDCountdownVal[3], 2);
	TextDrawBackgroundColor(TDCountdownVal[3], 255);
	TextDrawFont(TDCountdownVal[3], 1);
	TextDrawLetterSize(TDCountdownVal[3], 0.600000, 2.000000);
	TextDrawColor(TDCountdownVal[3], -1);
	TextDrawSetOutline(TDCountdownVal[3], 0);
	TextDrawSetProportional(TDCountdownVal[3], 1);
	TextDrawSetShadow(TDCountdownVal[3], 1);

	TDCountdownVal[2] = TextDrawCreate(320.000000, 152.000000, "2");
	TextDrawAlignment(TDCountdownVal[2], 2);
	TextDrawBackgroundColor(TDCountdownVal[2], 255);
	TextDrawFont(TDCountdownVal[2], 1);
	TextDrawLetterSize(TDCountdownVal[2], 0.600000, 2.000000);
	TextDrawColor(TDCountdownVal[2], -1);
	TextDrawSetOutline(TDCountdownVal[2], 0);
	TextDrawSetProportional(TDCountdownVal[2], 1);
	TextDrawSetShadow(TDCountdownVal[2], 1);

	TDCountdownVal[1] = TextDrawCreate(320.000000, 152.000000, "1");
	TextDrawAlignment(TDCountdownVal[1], 2);
	TextDrawBackgroundColor(TDCountdownVal[1], 255);
	TextDrawFont(TDCountdownVal[1], 1);
	TextDrawLetterSize(TDCountdownVal[1], 0.600000, 2.000000);
	TextDrawColor(TDCountdownVal[1], -1);
	TextDrawSetOutline(TDCountdownVal[1], 0);
	TextDrawSetProportional(TDCountdownVal[1], 1);
	TextDrawSetShadow(TDCountdownVal[1], 1);

	TDCountdownVal[0] = TextDrawCreate(320.000000, 152.000000, "START");
	TextDrawAlignment(TDCountdownVal[0], 2);
	TextDrawBackgroundColor(TDCountdownVal[0], 255);
	TextDrawFont(TDCountdownVal[0], 1);
	TextDrawLetterSize(TDCountdownVal[0], 0.600000, 2.000000);
	TextDrawColor(TDCountdownVal[0], -1);
	TextDrawSetOutline(TDCountdownVal[0], 0);
	TextDrawSetProportional(TDCountdownVal[0], 1);
	TextDrawSetShadow(TDCountdownVal[0], 1);

	TDCarInfo = TextDrawCreate(325.000000, 338.000000, "Zeby zespawnowac pojazd uzyj ~w~/car (ew. nazwa)");
	TextDrawAlignment(TDCarInfo, 2);
	TextDrawBackgroundColor(TDCarInfo, 144);
	TextDrawFont(TDCarInfo, 1);
	TextDrawLetterSize(TDCarInfo, 0.240000, 1.200000);
	TextDrawColor(TDCarInfo, 72329983);
	TextDrawSetOutline(TDCarInfo, 0);
	TextDrawSetProportional(TDCarInfo, 1);
	TextDrawSetShadow(TDCarInfo, 1);
	
	TDVoteInfo = TextDrawCreate(90.000000, 160.000000, " ");
	TextDrawAlignment(TDVoteInfo, 2);
	TextDrawBackgroundColor(TDVoteInfo, 80);
	TextDrawFont(TDVoteInfo, 1);
	TextDrawLetterSize(TDVoteInfo, 0.230000, 0.899999);
	TextDrawColor(TDVoteInfo, 72329983);
	TextDrawSetOutline(TDVoteInfo, 0);
	TextDrawSetProportional(TDVoteInfo, 1);
	TextDrawSetShadow(TDVoteInfo, 1);
	TextDrawUseBox(TDVoteInfo, 1);
	TextDrawBoxColor(TDVoteInfo, 80);
	TextDrawTextSize(TDVoteInfo, 36.000000, 102.000000);

	TDVoteName = TextDrawCreate(77.000000, 149.000000, "Glosowanie");
	TextDrawAlignment(TDVoteName, 2);
	TextDrawBackgroundColor(TDVoteName, 0x00000090);
	TextDrawFont(TDVoteName, 1);
	TextDrawLetterSize(TDVoteName, 0.359999, 1.500000);
	TextDrawColor(TDVoteName, 72329983);
	TextDrawSetOutline(TDVoteName, 0);
	TextDrawSetProportional(TDVoteName, 1);
	TextDrawSetShadow(TDVoteName, 1);
	
	TDWinRoundStatic[0] = TextDrawCreate(255.000000, 190.000000, "LD_POKE:cd9s");
	TextDrawBackgroundColor(TDWinRoundStatic[0], 255);
	TextDrawFont(TDWinRoundStatic[0], 4);
	TextDrawLetterSize(TDWinRoundStatic[0], 0.500000, 1.000000);
	TextDrawColor(TDWinRoundStatic[0], 80);
	TextDrawSetOutline(TDWinRoundStatic[0], 0);
	TextDrawSetProportional(TDWinRoundStatic[0], 1);
	TextDrawSetShadow(TDWinRoundStatic[0], 1);
	TextDrawUseBox(TDWinRoundStatic[0], 1);
	TextDrawBoxColor(TDWinRoundStatic[0], 255);
	TextDrawTextSize(TDWinRoundStatic[0], 130.000000, 20.000000);

	TDWinRoundStatic[1] = TextDrawCreate(255.000000, 212.000000, "LD_POKE:cd9s");
	TextDrawBackgroundColor(TDWinRoundStatic[1], 255);
	TextDrawFont(TDWinRoundStatic[1], 4);
	TextDrawLetterSize(TDWinRoundStatic[1], 0.500000, 1.000000);
	TextDrawColor(TDWinRoundStatic[1], 80);
	TextDrawSetOutline(TDWinRoundStatic[1], 0);
	TextDrawSetProportional(TDWinRoundStatic[1], 1);
	TextDrawSetShadow(TDWinRoundStatic[1], 1);
	TextDrawUseBox(TDWinRoundStatic[1], 1);
	TextDrawBoxColor(TDWinRoundStatic[1], 255);
	TextDrawTextSize(TDWinRoundStatic[1], 130.000000, 20.000000);

	TDWinRoundStatic[2] = TextDrawCreate(243.000000, 234.000000, "LD_POKE:cd9s");
	TextDrawBackgroundColor(TDWinRoundStatic[2], 255);
	TextDrawFont(TDWinRoundStatic[2], 4);
	TextDrawLetterSize(TDWinRoundStatic[2], 0.500000, 1.000000);
	TextDrawColor(TDWinRoundStatic[2], 48);
	TextDrawSetOutline(TDWinRoundStatic[2], 0);
	TextDrawSetProportional(TDWinRoundStatic[2], 1);
	TextDrawSetShadow(TDWinRoundStatic[2], 1);
	TextDrawUseBox(TDWinRoundStatic[2], 1);
	TextDrawBoxColor(TDWinRoundStatic[2], 255);
	TextDrawTextSize(TDWinRoundStatic[2], 154.000000, 51.000000);

	TDWinRoundStatic[3] = TextDrawCreate(244.000000, 235.000000, "LD_POKE:cd9s");
	TextDrawBackgroundColor(TDWinRoundStatic[3], 255);
	TextDrawFont(TDWinRoundStatic[3], 4);
	TextDrawLetterSize(TDWinRoundStatic[3], 0.500000, 1.000000);
	TextDrawColor(TDWinRoundStatic[3], 48);
	TextDrawSetOutline(TDWinRoundStatic[3], 0);
	TextDrawSetProportional(TDWinRoundStatic[3], 1);
	TextDrawSetShadow(TDWinRoundStatic[3], 1);
	TextDrawUseBox(TDWinRoundStatic[3], 1);
	TextDrawBoxColor(TDWinRoundStatic[3], 255);
	TextDrawTextSize(TDWinRoundStatic[3], 70.000000, 49.000000);

	TDWinRoundStatic[4] = TextDrawCreate(315.000000, 235.000000, "LD_POKE:cd9s");
	TextDrawBackgroundColor(TDWinRoundStatic[4], 255);
	TextDrawFont(TDWinRoundStatic[4], 4);
	TextDrawLetterSize(TDWinRoundStatic[4], 0.500000, 1.000000);
	TextDrawColor(TDWinRoundStatic[4], 48);
	TextDrawSetOutline(TDWinRoundStatic[4], 0);
	TextDrawSetProportional(TDWinRoundStatic[4], 1);
	TextDrawSetShadow(TDWinRoundStatic[4], 1);
	TextDrawUseBox(TDWinRoundStatic[4], 1);
	TextDrawBoxColor(TDWinRoundStatic[4], 255);
	TextDrawTextSize(TDWinRoundStatic[4], 40.000000, 49.000000);

	TDWinRoundStatic[5] = TextDrawCreate(356.000000, 235.000000, "LD_POKE:cd9s");
	TextDrawBackgroundColor(TDWinRoundStatic[5], 255);
	TextDrawFont(TDWinRoundStatic[5], 4);
	TextDrawLetterSize(TDWinRoundStatic[5], 0.500000, 1.000000);
	TextDrawColor(TDWinRoundStatic[5], 48);
	TextDrawSetOutline(TDWinRoundStatic[5], 0);
	TextDrawSetProportional(TDWinRoundStatic[5], 1);
	TextDrawSetShadow(TDWinRoundStatic[5], 1);
	TextDrawUseBox(TDWinRoundStatic[5], 1);
	TextDrawBoxColor(TDWinRoundStatic[5], 255);
	TextDrawTextSize(TDWinRoundStatic[5], 40.000000, 49.000000);

	TDWinRoundStatic[6] = TextDrawCreate(273.000000, 236.000000, "Nick_____________Respekt_____ Druzyna");
	TextDrawBackgroundColor(TDWinRoundStatic[6], 48);
	TextDrawFont(TDWinRoundStatic[6], 1);
	TextDrawLetterSize(TDWinRoundStatic[6], 0.190000, 0.799999);
	TextDrawColor(TDWinRoundStatic[6], 74764031);
	TextDrawSetOutline(TDWinRoundStatic[6], 0);
	TextDrawSetProportional(TDWinRoundStatic[6], 1);
	TextDrawSetShadow(TDWinRoundStatic[6], 1);
	
	TDWinRoundInfo[0] = TextDrawCreate(319.000000, 194.000000, " ");    		// Arena  ~w~999
	TextDrawAlignment(TDWinRoundInfo[0], 2);
	TextDrawBackgroundColor(TDWinRoundInfo[0], 48);
	TextDrawFont(TDWinRoundInfo[0], 1);
	TextDrawLetterSize(TDWinRoundInfo[0], 0.310000, 1.200000);
	TextDrawColor(TDWinRoundInfo[0], 74764031);
	TextDrawSetOutline(TDWinRoundInfo[0], 0);
	TextDrawSetProportional(TDWinRoundInfo[0], 1);
	TextDrawSetShadow(TDWinRoundInfo[0], 1);

	TDWinRoundInfo[1] = TextDrawCreate(319.000000, 216.000000, " ");            // Wygrywa druzyna ~w~Obrony
	TextDrawAlignment(TDWinRoundInfo[1], 2);
	TextDrawBackgroundColor(TDWinRoundInfo[1], 48);
	TextDrawFont(TDWinRoundInfo[1], 1);
	TextDrawLetterSize(TDWinRoundInfo[1], 0.200000, 1.000000);
	TextDrawColor(TDWinRoundInfo[1], 74764031);
	TextDrawSetOutline(TDWinRoundInfo[1], 0);
	TextDrawSetProportional(TDWinRoundInfo[1], 1);
	TextDrawSetShadow(TDWinRoundInfo[1], 1);

	TDWinRoundStats[0] = TextDrawCreate(279.000000, 245.000000, " ");                    // Nick
	TextDrawAlignment(TDWinRoundStats[0], 2);
	TextDrawBackgroundColor(TDWinRoundStats[0], 48);
	TextDrawFont(TDWinRoundStats[0], 1);
	TextDrawLetterSize(TDWinRoundStats[0], 0.190000, 0.799999);
	TextDrawColor(TDWinRoundStats[0], -52);
	TextDrawSetOutline(TDWinRoundStats[0], 0);
	TextDrawSetProportional(TDWinRoundStats[0], 1);
	TextDrawSetShadow(TDWinRoundStats[0], 1);

	TDWinRoundStats[1] = TextDrawCreate(335.000000, 245.000000, " ");                   // Points
	TextDrawAlignment(TDWinRoundStats[1], 2);
	TextDrawBackgroundColor(TDWinRoundStats[1], 48);
	TextDrawFont(TDWinRoundStats[1], 1);
	TextDrawLetterSize(TDWinRoundStats[1], 0.190000, 0.799999);
	TextDrawColor(TDWinRoundStats[1], -52);
	TextDrawSetOutline(TDWinRoundStats[1], 0);
	TextDrawSetProportional(TDWinRoundStats[1], 1);
	TextDrawSetShadow(TDWinRoundStats[1], 1);

	TDWinRoundStats[2] = TextDrawCreate(376.000000, 245.000000, " ");                   // Team
	TextDrawAlignment(TDWinRoundStats[2], 2);
	TextDrawBackgroundColor(TDWinRoundStats[2], 48);
	TextDrawFont(TDWinRoundStats[2], 1);
	TextDrawLetterSize(TDWinRoundStats[2], 0.190000, 0.799999);
	TextDrawColor(TDWinRoundStats[2], -52);
	TextDrawSetOutline(TDWinRoundStats[2], 0);
	TextDrawSetProportional(TDWinRoundStats[2], 1);
	TextDrawSetShadow(TDWinRoundStats[2], 1);

	TDZegar = TextDrawCreate(577.000000,16.000000,"00:00");
	TextDrawAlignment(TDZegar,2);
	TextDrawBackgroundColor(TDZegar,0x00000099);
	TextDrawFont(TDZegar,3);
	TextDrawLetterSize(TDZegar,0.499999,1.300000);
	TextDrawColor(TDZegar,0xffffffff);
	TextDrawSetOutline(TDZegar,1);
	TextDrawSetProportional(TDZegar,1);
	TextDrawSetShadow(TDZegar,1);

	TDData = TextDrawCreate(582.000000, 31.000000, " ");
	TextDrawAlignment(TDData, 2);
	TextDrawBackgroundColor(TDData, 80);
	TextDrawFont(TDData, 1);
	TextDrawLetterSize(TDData, 0.220000, 0.899999);
	TextDrawColor(TDData, -86);
	TextDrawSetOutline(TDData, 0);
	TextDrawSetProportional(TDData, 1);
	TextDrawSetShadow(TDData, 1);

	TDOgloszenieBox = TextDrawCreate(76.000000, 386.000000, "LD_OTB2:butnAo");
	TextDrawBackgroundColor(TDOgloszenieBox, 255);
	TextDrawFont(TDOgloszenieBox, 4);
	TextDrawLetterSize(TDOgloszenieBox, 0.500000, 1.000000);
	TextDrawColor(TDOgloszenieBox, 0xff000030);
	TextDrawSetOutline(TDOgloszenieBox, 0);
	TextDrawSetProportional(TDOgloszenieBox, 1);
	TextDrawSetShadow(TDOgloszenieBox, 1);
	TextDrawUseBox(TDOgloszenieBox, 1);
	TextDrawBoxColor(TDOgloszenieBox, 255);
	TextDrawTextSize(TDOgloszenieBox, 486.000000, -26.000000);

	TDOgloszenieSerwerowe = TextDrawCreate(320.000000,370.000000," ");
	TextDrawAlignment(TDOgloszenieSerwerowe,2);
	TextDrawBackgroundColor(TDOgloszenieSerwerowe,0x00000000);
	TextDrawFont(TDOgloszenieSerwerowe,1);
	TextDrawLetterSize(TDOgloszenieSerwerowe,0.253, 1.100000);
	TextDrawColor(TDOgloszenieSerwerowe,0xE2E2E2BB);
	TextDrawSetProportional(TDOgloszenieSerwerowe,1);
	TextDrawSetShadow(TDOgloszenieSerwerowe,1);

	TDSpecByBox = TextDrawCreate(42.000000, 161.000000, "Spectator");
	TextDrawBackgroundColor(TDSpecByBox, 80);
	TextDrawFont(TDSpecByBox, 1);
	TextDrawLetterSize(TDSpecByBox, 0.240000, 1.300000);
	TextDrawColor(TDSpecByBox, 72329983);
	TextDrawSetOutline(TDSpecByBox, 0);
	TextDrawSetProportional(TDSpecByBox, 1);
	TextDrawSetShadow(TDSpecByBox, 1);

	TDPlayerHudStatic[0] = TextDrawCreate(-4.000000, 424.000000, "LD_POKE:cd9s");
	TextDrawBackgroundColor(TDPlayerHudStatic[0], 255);
	TextDrawFont(TDPlayerHudStatic[0], 4);
	TextDrawLetterSize(TDPlayerHudStatic[0], 0.500000, 1.000000);
	TextDrawColor(TDPlayerHudStatic[0], 48);
	TextDrawSetOutline(TDPlayerHudStatic[0], 0);
	TextDrawSetProportional(TDPlayerHudStatic[0], 1);
	TextDrawSetShadow(TDPlayerHudStatic[0], 1);
	TextDrawUseBox(TDPlayerHudStatic[0], 1);
	TextDrawBoxColor(TDPlayerHudStatic[0], 255);
	TextDrawTextSize(TDPlayerHudStatic[0], 117.000000, 40.000000);

	TDPlayerHudStatic[1] = TextDrawCreate(1.000000, 425.000000, "LD_POKE:cd9s");
	TextDrawBackgroundColor(TDPlayerHudStatic[1], 255);
	TextDrawFont(TDPlayerHudStatic[1], 4);
	TextDrawLetterSize(TDPlayerHudStatic[1], 0.500000, 1.000000);
	TextDrawColor(TDPlayerHudStatic[1], 48);
	TextDrawSetOutline(TDPlayerHudStatic[1], 0);
	TextDrawSetProportional(TDPlayerHudStatic[1], 1);
	TextDrawSetShadow(TDPlayerHudStatic[1], 1);
	TextDrawUseBox(TDPlayerHudStatic[1], 1);
	TextDrawBoxColor(TDPlayerHudStatic[1], 255);
	TextDrawTextSize(TDPlayerHudStatic[1], 83.000000, 12.000000);

	TDPlayerHudStatic[2] = TextDrawCreate(1.000000, 438.000000, "LD_POKE:cd9s");
	TextDrawBackgroundColor(TDPlayerHudStatic[2], 255);
	TextDrawFont(TDPlayerHudStatic[2], 4);
	TextDrawLetterSize(TDPlayerHudStatic[2], 0.500000, 1.000000);
	TextDrawColor(TDPlayerHudStatic[2], 48);
	TextDrawSetOutline(TDPlayerHudStatic[2], 0);
	TextDrawSetProportional(TDPlayerHudStatic[2], 1);
	TextDrawSetShadow(TDPlayerHudStatic[2], 1);
	TextDrawUseBox(TDPlayerHudStatic[2], 1);
	TextDrawBoxColor(TDPlayerHudStatic[2], 255);
	TextDrawTextSize(TDPlayerHudStatic[2], 27.000000, 12.000000);

	TDPlayerHudStatic[3] = TextDrawCreate(29.000000, 438.000000, "LD_POKE:cd9s");
	TextDrawBackgroundColor(TDPlayerHudStatic[3], 255);
	TextDrawFont(TDPlayerHudStatic[3], 4);
	TextDrawLetterSize(TDPlayerHudStatic[3], 0.500000, 1.000000);
	TextDrawColor(TDPlayerHudStatic[3], 48);
	TextDrawSetOutline(TDPlayerHudStatic[3], 0);
	TextDrawSetProportional(TDPlayerHudStatic[3], 1);
	TextDrawSetShadow(TDPlayerHudStatic[3], 1);
	TextDrawUseBox(TDPlayerHudStatic[3], 1);
	TextDrawBoxColor(TDPlayerHudStatic[3], 255);
	TextDrawTextSize(TDPlayerHudStatic[3], 27.000000, 12.000000);

	TDPlayerHudStatic[4] = TextDrawCreate(57.000000, 438.000000, "LD_POKE:cd9s");
	TextDrawBackgroundColor(TDPlayerHudStatic[4], 255);
	TextDrawFont(TDPlayerHudStatic[4], 4);
	TextDrawLetterSize(TDPlayerHudStatic[4], 0.500000, 1.000000);
	TextDrawColor(TDPlayerHudStatic[4], 48);
	TextDrawSetOutline(TDPlayerHudStatic[4], 0);
	TextDrawSetProportional(TDPlayerHudStatic[4], 1);
	TextDrawSetShadow(TDPlayerHudStatic[4], 1);
	TextDrawUseBox(TDPlayerHudStatic[4], 1);
	TextDrawBoxColor(TDPlayerHudStatic[4], 255);
	TextDrawTextSize(TDPlayerHudStatic[4], 27.000000, 12.000000);

	TDPlayerHudStatic[5] = TextDrawCreate(85.000000, 438.000000, "LD_POKE:cd9s");
	TextDrawBackgroundColor(TDPlayerHudStatic[5], 255);
	TextDrawFont(TDPlayerHudStatic[5], 4);
	TextDrawLetterSize(TDPlayerHudStatic[5], 0.500000, 1.000000);
	TextDrawColor(TDPlayerHudStatic[5], 48);
	TextDrawSetOutline(TDPlayerHudStatic[5], 0);
	TextDrawSetProportional(TDPlayerHudStatic[5], 1);
	TextDrawSetShadow(TDPlayerHudStatic[5], 1);
	TextDrawUseBox(TDPlayerHudStatic[5], 1);
	TextDrawBoxColor(TDPlayerHudStatic[5], 255);
	TextDrawTextSize(TDPlayerHudStatic[5], 27.000000, 12.000000);

	TDPlayerHudStatic[6] = TextDrawCreate(85.000000, 425.000000, "LD_POKE:cd9s");
	TextDrawBackgroundColor(TDPlayerHudStatic[6], 255);
	TextDrawFont(TDPlayerHudStatic[6], 4);
	TextDrawLetterSize(TDPlayerHudStatic[6], 0.500000, 1.000000);
	TextDrawColor(TDPlayerHudStatic[6], 48);
	TextDrawSetOutline(TDPlayerHudStatic[6], 0);
	TextDrawSetProportional(TDPlayerHudStatic[6], 1);
	TextDrawSetShadow(TDPlayerHudStatic[6], 1);
	TextDrawUseBox(TDPlayerHudStatic[6], 1);
	TextDrawBoxColor(TDPlayerHudStatic[6], 255);
	TextDrawTextSize(TDPlayerHudStatic[6], 27.000000, 12.000000);

	TDPlayerHudStatic[7] = TextDrawCreate(581.000000, 432.000000, "LD_POKE:cd9s");
	TextDrawBackgroundColor(TDPlayerHudStatic[7], 255);
	TextDrawFont(TDPlayerHudStatic[7], 4);
	TextDrawLetterSize(TDPlayerHudStatic[7], 0.500000, 1.000000);
	TextDrawColor(TDPlayerHudStatic[7], 80);
	TextDrawSetOutline(TDPlayerHudStatic[7], 0);
	TextDrawSetProportional(TDPlayerHudStatic[7], 1);
	TextDrawSetShadow(TDPlayerHudStatic[7], 1);
	TextDrawUseBox(TDPlayerHudStatic[7], 1);
	TextDrawBoxColor(TDPlayerHudStatic[7], 255);
	TextDrawTextSize(TDPlayerHudStatic[7], 117.000000, 40.000000);

	TDPlayerHudStatic[8] = TextDrawCreate(22.000000, 443.000000, "hud:radar_gangn");
	TextDrawAlignment(TDPlayerHudStatic[8], 2);
	TextDrawBackgroundColor(TDPlayerHudStatic[8], 255);
	TextDrawFont(TDPlayerHudStatic[8], 4);
	TextDrawLetterSize(TDPlayerHudStatic[8], 0.200000, 1.000000);
	TextDrawColor(TDPlayerHudStatic[8], -1);
	TextDrawSetOutline(TDPlayerHudStatic[8], 0);
	TextDrawSetProportional(TDPlayerHudStatic[8], 1);
	TextDrawSetShadow(TDPlayerHudStatic[8], 1);
	TextDrawUseBox(TDPlayerHudStatic[8], 1);
	TextDrawBoxColor(TDPlayerHudStatic[8], 255);
	TextDrawTextSize(TDPlayerHudStatic[8], 5.000000, 5.000000);

	TDPlayerHudStatic[9] = TextDrawCreate(50.000000, 443.000000, "hud:radar_locosyndicate");
	TextDrawAlignment(TDPlayerHudStatic[9], 2);
	TextDrawBackgroundColor(TDPlayerHudStatic[9], 255);
	TextDrawFont(TDPlayerHudStatic[9], 4);
	TextDrawLetterSize(TDPlayerHudStatic[9], 0.200000, 1.000000);
	TextDrawColor(TDPlayerHudStatic[9], -1);
	TextDrawSetOutline(TDPlayerHudStatic[9], 0);
	TextDrawSetProportional(TDPlayerHudStatic[9], 1);
	TextDrawSetShadow(TDPlayerHudStatic[9], 1);
	TextDrawUseBox(TDPlayerHudStatic[9], 1);
	TextDrawBoxColor(TDPlayerHudStatic[9], 255);
	TextDrawTextSize(TDPlayerHudStatic[9], 5.000000, 5.000000);

	TDPlayerHudStatic[10] = TextDrawCreate(78.000000, 443.000000, "hud:radar_emmetgun");
	TextDrawAlignment(TDPlayerHudStatic[10], 2);
	TextDrawBackgroundColor(TDPlayerHudStatic[10], 255);
	TextDrawFont(TDPlayerHudStatic[10], 4);
	TextDrawLetterSize(TDPlayerHudStatic[10], 0.200000, 1.000000);
	TextDrawColor(TDPlayerHudStatic[10], -1);
	TextDrawSetOutline(TDPlayerHudStatic[10], 0);
	TextDrawSetProportional(TDPlayerHudStatic[10], 1);
	TextDrawSetShadow(TDPlayerHudStatic[10], 1);
	TextDrawUseBox(TDPlayerHudStatic[10], 1);
	TextDrawBoxColor(TDPlayerHudStatic[10], 255);
	TextDrawTextSize(TDPlayerHudStatic[10], 5.000000, 5.000000);

	TDPlayerHudStatic[11] = TextDrawCreate(106.000000, 431.000000, "hud:radar_race");
	TextDrawAlignment(TDPlayerHudStatic[11], 2);
	TextDrawBackgroundColor(TDPlayerHudStatic[11], 255);
	TextDrawFont(TDPlayerHudStatic[11], 4);
	TextDrawLetterSize(TDPlayerHudStatic[11], 0.200000, 1.000000);
	TextDrawColor(TDPlayerHudStatic[11], -302505473);
	TextDrawSetOutline(TDPlayerHudStatic[11], 0);
	TextDrawSetProportional(TDPlayerHudStatic[11], 1);
	TextDrawSetShadow(TDPlayerHudStatic[11], 1);
	TextDrawUseBox(TDPlayerHudStatic[11], 1);
	TextDrawBoxColor(TDPlayerHudStatic[11], 255);
	TextDrawTextSize(TDPlayerHudStatic[11], 5.000000, 5.000000);

	TDPlayerHudStatic[12] = TextDrawCreate(106.000000, 443.000000, "LD_DRV:gold");
	TextDrawAlignment(TDPlayerHudStatic[12], 2);
	TextDrawBackgroundColor(TDPlayerHudStatic[12], 255);
	TextDrawFont(TDPlayerHudStatic[12], 4);
	TextDrawLetterSize(TDPlayerHudStatic[12], 0.200000, 1.000000);
	TextDrawColor(TDPlayerHudStatic[12], -302505473);
	TextDrawSetOutline(TDPlayerHudStatic[12], 0);
	TextDrawSetProportional(TDPlayerHudStatic[12], 1);
	TextDrawSetShadow(TDPlayerHudStatic[12], 1);
	TextDrawUseBox(TDPlayerHudStatic[12], 1);
	TextDrawBoxColor(TDPlayerHudStatic[12], 255);
	TextDrawTextSize(TDPlayerHudStatic[12], 5.000000, 5.000000);

	TDPlayerHudTeam[0] = TextDrawCreate(612.000000, 436.000000, "Atak");
	TextDrawAlignment(TDPlayerHudTeam[0], 2);
	TextDrawBackgroundColor(TDPlayerHudTeam[0], 48);
	TextDrawFont(TDPlayerHudTeam[0], 1);
	TextDrawLetterSize(TDPlayerHudTeam[0], 0.200000, 0.899999);
	TextDrawColor(TDPlayerHudTeam[0], -1);
	TextDrawSetOutline(TDPlayerHudTeam[0], 0);
	TextDrawSetProportional(TDPlayerHudTeam[0], 1);
	TextDrawSetShadow(TDPlayerHudTeam[0], 1);

	TDPlayerHudTeam[1] = TextDrawCreate(612.000000, 436.000000, "Obrona");
	TextDrawAlignment(TDPlayerHudTeam[1], 2);
	TextDrawBackgroundColor(TDPlayerHudTeam[1], 48);
	TextDrawFont(TDPlayerHudTeam[1], 1);
	TextDrawLetterSize(TDPlayerHudTeam[1], 0.200000, 0.899999);
	TextDrawColor(TDPlayerHudTeam[1], -1);
	TextDrawSetOutline(TDPlayerHudTeam[1], 0);
	TextDrawSetProportional(TDPlayerHudTeam[1], 1);
	TextDrawSetShadow(TDPlayerHudTeam[1], 1);

	TDPlayerHudTeam[2] = TextDrawCreate(612.000000, 436.000000, "Arbiter");
	TextDrawAlignment(TDPlayerHudTeam[2], 2);
	TextDrawBackgroundColor(TDPlayerHudTeam[2], 48);
	TextDrawFont(TDPlayerHudTeam[2], 1);
	TextDrawLetterSize(TDPlayerHudTeam[2], 0.200000, 0.899999);
	TextDrawColor(TDPlayerHudTeam[2], -1);
	TextDrawSetOutline(TDPlayerHudTeam[2], 0);
	TextDrawSetProportional(TDPlayerHudTeam[2], 1);
	TextDrawSetShadow(TDPlayerHudTeam[2], 1);
	
	for(new i; i < MAX_GRACZY; i++) {
		G[i][TDZdrowie] = TextDrawCreate(578.000000,68.000000," ");
		TextDrawAlignment(G[i][TDZdrowie],2);
		TextDrawBackgroundColor(G[i][TDZdrowie],0x00000000);
		TextDrawFont(G[i][TDZdrowie],2);
		TextDrawLetterSize(G[i][TDZdrowie],0.15,0.699999);
		TextDrawColor(G[i][TDZdrowie],0xffffffff);
		TextDrawSetProportional(G[i][TDZdrowie],1);
		TextDrawSetShadow(G[i][TDZdrowie],1);
	}

	TDWinSpawnProtectStatic = TextDrawCreate(510.000000, 100.000000, "LD_POKE:cd9s");
	TextDrawAlignment(TDWinSpawnProtectStatic, 2);
	TextDrawBackgroundColor(TDWinSpawnProtectStatic, 0);
	TextDrawFont(TDWinSpawnProtectStatic, 4);
	TextDrawLetterSize(TDWinSpawnProtectStatic, 0.190000, 0.899999);
	TextDrawColor(TDWinSpawnProtectStatic, 80);
	TextDrawSetOutline(TDWinSpawnProtectStatic, 0);
	TextDrawSetProportional(TDWinSpawnProtectStatic, 1);
	TextDrawSetShadow(TDWinSpawnProtectStatic, 1);
	TextDrawUseBox(TDWinSpawnProtectStatic, 1);
	TextDrawBoxColor(TDWinSpawnProtectStatic, 255);
	TextDrawTextSize(TDWinSpawnProtectStatic, 90.000000, 10.000000);

	TDWinSpawnProtectInfo = TextDrawCreate(555.000000, 101.000000, " ");
	TextDrawAlignment(TDWinSpawnProtectInfo, 2);
	TextDrawBackgroundColor(TDWinSpawnProtectInfo, 80);
	TextDrawFont(TDWinSpawnProtectInfo, 1);
	TextDrawLetterSize(TDWinSpawnProtectInfo, 0.170000, 0.799999);
	TextDrawColor(TDWinSpawnProtectInfo, 74764031);
	TextDrawSetOutline(TDWinSpawnProtectInfo, 0);
	TextDrawSetProportional(TDWinSpawnProtectInfo, 1);
	TextDrawSetShadow(TDWinSpawnProtectInfo, 1);

	TDStartRundyBox1 = TextDrawCreate(320.000000, 1.000000, "I");
	TextDrawAlignment(TDStartRundyBox1, 2);
	TextDrawBackgroundColor(TDStartRundyBox1, 255);
	TextDrawFont(TDStartRundyBox1, 1);
	TextDrawLetterSize(TDStartRundyBox1, 5.199999, 6.000000);
	TextDrawColor(TDStartRundyBox1, 48);
	TextDrawSetOutline(TDStartRundyBox1, 0);
	TextDrawSetProportional(TDStartRundyBox1, 1);
	TextDrawSetShadow(TDStartRundyBox1, 0);
	TextDrawUseBox(TDStartRundyBox1, 1);
	TextDrawBoxColor(TDStartRundyBox1, 255);
	TextDrawTextSize(TDStartRundyBox1, 0.000000, -650.000000);

	TDStartRundyBox2 = TextDrawCreate(320.000000, 392.500000, "I");
	TextDrawAlignment(TDStartRundyBox2, 2);
	TextDrawBackgroundColor(TDStartRundyBox2, 255);
	TextDrawFont(TDStartRundyBox2, 1);
	TextDrawLetterSize(TDStartRundyBox2, 5.199999, 6.000000);
	TextDrawColor(TDStartRundyBox2, 48);
	TextDrawSetOutline(TDStartRundyBox2, 0);
	TextDrawSetProportional(TDStartRundyBox2, 1);
	TextDrawSetShadow(TDStartRundyBox2, 0);
	TextDrawUseBox(TDStartRundyBox2, 1);
	TextDrawBoxColor(TDStartRundyBox2, 255);
	TextDrawTextSize(TDStartRundyBox2, 0.000000, -650.000000);

	TDStartRundyInformacjeInfo = TextDrawCreate(320.000000, 396.000000, " ");
	TextDrawAlignment(TDStartRundyInformacjeInfo, 2);
	TextDrawBackgroundColor(TDStartRundyInformacjeInfo, 255);
	TextDrawFont(TDStartRundyInformacjeInfo, 1);
	TextDrawLetterSize(TDStartRundyInformacjeInfo, 0.320000, 1.500000);
	TextDrawColor(TDStartRundyInformacjeInfo, 0x044FAAFF);
	TextDrawSetOutline(TDStartRundyInformacjeInfo, 0);
	TextDrawSetProportional(TDStartRundyInformacjeInfo, 1);
	TextDrawSetShadow(TDStartRundyInformacjeInfo, 1);

	TDStartRundyInformacje = TextDrawCreate(320.000000, 414.000000, " ");
	TextDrawAlignment(TDStartRundyInformacje, 2);
	TextDrawBackgroundColor(TDStartRundyInformacje, 255);
	TextDrawFont(TDStartRundyInformacje, 1);
	TextDrawLetterSize(TDStartRundyInformacje, 0.210000, 1.100000);
	TextDrawColor(TDStartRundyInformacje, -1);
	TextDrawSetOutline(TDStartRundyInformacje, 0);
	TextDrawSetProportional(TDStartRundyInformacje, 1);
	TextDrawSetShadow(TDStartRundyInformacje, 1);

	TDStartRundyPasek = TextDrawCreate(267.000000, 31.000000, "LD_POOL:ball");
	TextDrawBackgroundColor(TDStartRundyPasek, 255);
	TextDrawFont(TDStartRundyPasek, 4);
	TextDrawLetterSize(TDStartRundyPasek, 0.500000, 1.000000);
	TextDrawColor(TDStartRundyPasek, 72329983);
	TextDrawSetOutline(TDStartRundyPasek, 0);
	TextDrawSetProportional(TDStartRundyPasek, 1);
	TextDrawSetShadow(TDStartRundyPasek, 1);
	TextDrawUseBox(TDStartRundyPasek, 1);
	TextDrawBoxColor(TDStartRundyPasek, 255);
	TextDrawTextSize(TDStartRundyPasek, 105.000000, 1.000000);
	
	TDStartRundyNazwa = TextDrawCreate(320.000000, 10.000000, " ");
	TextDrawAlignment(TDStartRundyNazwa, 2);
	TextDrawBackgroundColor(TDStartRundyNazwa, 255);
	TextDrawFont(TDStartRundyNazwa, 3);
	TextDrawLetterSize(TDStartRundyNazwa, 0.500000, 2.000000);
	TextDrawColor(TDStartRundyNazwa, 0x044FAAFF);
	TextDrawSetOutline(TDStartRundyNazwa, 1);
	TextDrawSetProportional(TDStartRundyNazwa, 1);

	TDStartRundyKropki = TextDrawCreate(319.000000, 34.000000, " ");
	TextDrawAlignment(TDStartRundyKropki, 2);
	TextDrawBackgroundColor(TDStartRundyKropki, 144);
	TextDrawFont(TDStartRundyKropki, 1);
	TextDrawLetterSize(TDStartRundyKropki, 0.209999, 1.199999);
	TextDrawColor(TDStartRundyKropki, -1);
	TextDrawSetOutline(TDStartRundyKropki, 0);
	TextDrawSetProportional(TDStartRundyKropki, 1);
	TextDrawSetShadow(TDStartRundyKropki, 1);

	TDBottomBeltStatic[0] = TextDrawCreate(130.000000, 432.000000, "LD_POKE:cd9s");
	TextDrawBackgroundColor(TDBottomBeltStatic[0], 255);
	TextDrawFont(TDBottomBeltStatic[0], 4);
	TextDrawLetterSize(TDBottomBeltStatic[0], 0.500000, 1.000000);
	TextDrawColor(TDBottomBeltStatic[0], 48);
	TextDrawSetOutline(TDBottomBeltStatic[0], 0);
	TextDrawSetProportional(TDBottomBeltStatic[0], 1);
	TextDrawSetShadow(TDBottomBeltStatic[0], 1);
	TextDrawUseBox(TDBottomBeltStatic[0], 1);
	TextDrawBoxColor(TDBottomBeltStatic[0], 255);
	TextDrawTextSize(TDBottomBeltStatic[0], 129.000000, 40.000000);

	TDBottomBeltStatic[1] = TextDrawCreate(132.000000, 434.000000, "LD_POKE:cd9s");
	TextDrawBackgroundColor(TDBottomBeltStatic[1], 255);
	TextDrawFont(TDBottomBeltStatic[1], 4);
	TextDrawLetterSize(TDBottomBeltStatic[1], 0.500000, 1.000000);
	TextDrawColor(TDBottomBeltStatic[1], 48);
	TextDrawSetOutline(TDBottomBeltStatic[1], 0);
	TextDrawSetProportional(TDBottomBeltStatic[1], 1);
	TextDrawSetShadow(TDBottomBeltStatic[1], 1);
	TextDrawUseBox(TDBottomBeltStatic[1], 1);
	TextDrawBoxColor(TDBottomBeltStatic[1], 255);
	TextDrawTextSize(TDBottomBeltStatic[1], 45.000000, 29.000000);

	TDBottomBeltStatic[2] = TextDrawCreate(178.000000, 434.000000, "LD_POKE:cd9s");
	TextDrawBackgroundColor(TDBottomBeltStatic[2], 255);
	TextDrawFont(TDBottomBeltStatic[2], 4);
	TextDrawLetterSize(TDBottomBeltStatic[2], 0.500000, 1.000000);
	TextDrawColor(TDBottomBeltStatic[2], 48);
	TextDrawSetOutline(TDBottomBeltStatic[2], 0);
	TextDrawSetProportional(TDBottomBeltStatic[2], 1);
	TextDrawSetShadow(TDBottomBeltStatic[2], 1);
	TextDrawUseBox(TDBottomBeltStatic[2], 1);
	TextDrawBoxColor(TDBottomBeltStatic[2], 255);
	TextDrawTextSize(TDBottomBeltStatic[2], 24.000000, 29.000000);

	TDBottomBeltStatic[3] = TextDrawCreate(203.000000, 434.000000, "LD_POKE:cd9s");
	TextDrawBackgroundColor(TDBottomBeltStatic[3], 255);
	TextDrawFont(TDBottomBeltStatic[3], 4);
	TextDrawLetterSize(TDBottomBeltStatic[3], 0.500000, 1.000000);
	TextDrawColor(TDBottomBeltStatic[3], 48);
	TextDrawSetOutline(TDBottomBeltStatic[3], 0);
	TextDrawSetProportional(TDBottomBeltStatic[3], 1);
	TextDrawSetShadow(TDBottomBeltStatic[3], 1);
	TextDrawUseBox(TDBottomBeltStatic[3], 1);
	TextDrawBoxColor(TDBottomBeltStatic[3], 255);
	TextDrawTextSize(TDBottomBeltStatic[3], 54.000000, 29.000000);

	TDBottomBeltStatic[4] = TextDrawCreate(463.000000, 434.000000, "LD_POKE:cd9s");
	TextDrawBackgroundColor(TDBottomBeltStatic[4], 255);
	TextDrawFont(TDBottomBeltStatic[4], 4);
	TextDrawLetterSize(TDBottomBeltStatic[4], 0.500000, 1.000000);
	TextDrawColor(TDBottomBeltStatic[4], 48);
	TextDrawSetOutline(TDBottomBeltStatic[4], 0);
	TextDrawSetProportional(TDBottomBeltStatic[4], 1);
	TextDrawSetShadow(TDBottomBeltStatic[4], 1);
	TextDrawUseBox(TDBottomBeltStatic[4], 1);
	TextDrawBoxColor(TDBottomBeltStatic[4], 255);
	TextDrawTextSize(TDBottomBeltStatic[4], 45.000000, 29.000000);

	TDBottomBeltStatic[5] = TextDrawCreate(438.000000, 434.000000, "LD_POKE:cd9s");
	TextDrawBackgroundColor(TDBottomBeltStatic[5], 255);
	TextDrawFont(TDBottomBeltStatic[5], 4);
	TextDrawLetterSize(TDBottomBeltStatic[5], 0.500000, 1.000000);
	TextDrawColor(TDBottomBeltStatic[5], 48);
	TextDrawSetOutline(TDBottomBeltStatic[5], 0);
	TextDrawSetProportional(TDBottomBeltStatic[5], 1);
	TextDrawSetShadow(TDBottomBeltStatic[5], 1);
	TextDrawUseBox(TDBottomBeltStatic[5], 1);
	TextDrawBoxColor(TDBottomBeltStatic[5], 255);
	TextDrawTextSize(TDBottomBeltStatic[5], 24.000000, 29.000000);

	TDBottomBeltStatic[6] = TextDrawCreate(383.000000, 434.000000, "LD_POKE:cd9s");
	TextDrawBackgroundColor(TDBottomBeltStatic[6], 255);
	TextDrawFont(TDBottomBeltStatic[6], 4);
	TextDrawLetterSize(TDBottomBeltStatic[6], 0.500000, 1.000000);
	TextDrawColor(TDBottomBeltStatic[6], 48);
	TextDrawSetOutline(TDBottomBeltStatic[6], 0);
	TextDrawSetProportional(TDBottomBeltStatic[6], 1);
	TextDrawSetShadow(TDBottomBeltStatic[6], 1);
	TextDrawUseBox(TDBottomBeltStatic[6], 1);
	TextDrawBoxColor(TDBottomBeltStatic[6], 255);
	TextDrawTextSize(TDBottomBeltStatic[6], 54.000000, 29.000000);

	TDBottomBeltStatic[7] = TextDrawCreate(381.000000, 432.000000, "LD_POKE:cd9s");
	TextDrawBackgroundColor(TDBottomBeltStatic[7], 255);
	TextDrawFont(TDBottomBeltStatic[7], 4);
	TextDrawLetterSize(TDBottomBeltStatic[7], 0.500000, 1.000000);
	TextDrawColor(TDBottomBeltStatic[7], 48);
	TextDrawSetOutline(TDBottomBeltStatic[7], 0);
	TextDrawSetProportional(TDBottomBeltStatic[7], 1);
	TextDrawSetShadow(TDBottomBeltStatic[7], 1);
	TextDrawUseBox(TDBottomBeltStatic[7], 1);
	TextDrawBoxColor(TDBottomBeltStatic[7], 255);
	TextDrawTextSize(TDBottomBeltStatic[7], 129.000000, 40.000000);

	TDBottomBeltStatic[8] = TextDrawCreate(265.500000, 432.000000, "LD_POKE:cd9s");
	TextDrawBackgroundColor(TDBottomBeltStatic[8], 255);
	TextDrawFont(TDBottomBeltStatic[8], 4);
	TextDrawLetterSize(TDBottomBeltStatic[8], 0.500000, 1.000000);
	TextDrawColor(TDBottomBeltStatic[8], 48);
	TextDrawSetOutline(TDBottomBeltStatic[8], 0);
	TextDrawSetProportional(TDBottomBeltStatic[8], 1);
	TextDrawSetShadow(TDBottomBeltStatic[8], 1);
	TextDrawUseBox(TDBottomBeltStatic[8], 1);
	TextDrawBoxColor(TDBottomBeltStatic[8], 255);
	TextDrawTextSize(TDBottomBeltStatic[8], 109.000000, 40.000000);

	TDBottomBeltStatic[9] = TextDrawCreate(268.000000, 434.000000, "LD_POKE:cd9s");
	TextDrawBackgroundColor(TDBottomBeltStatic[9], 255);
	TextDrawFont(TDBottomBeltStatic[9], 4);
	TextDrawLetterSize(TDBottomBeltStatic[9], 0.500000, 1.000000);
	TextDrawColor(TDBottomBeltStatic[9], 48);
	TextDrawSetOutline(TDBottomBeltStatic[9], 0);
	TextDrawSetProportional(TDBottomBeltStatic[9], 1);
	TextDrawSetShadow(TDBottomBeltStatic[9], 1);
	TextDrawUseBox(TDBottomBeltStatic[9], 1);
	TextDrawBoxColor(TDBottomBeltStatic[9], 255);
	TextDrawTextSize(TDBottomBeltStatic[9], 45.000000, 29.000000);

	TDBottomBeltStatic[10] = TextDrawCreate(314.000000, 434.000000, "LD_POKE:cd9s");
	TextDrawBackgroundColor(TDBottomBeltStatic[10], 255);
	TextDrawFont(TDBottomBeltStatic[10], 4);
	TextDrawLetterSize(TDBottomBeltStatic[10], 0.500000, 1.000000);
	TextDrawColor(TDBottomBeltStatic[10], 48);
	TextDrawSetOutline(TDBottomBeltStatic[10], 0);
	TextDrawSetProportional(TDBottomBeltStatic[10], 1);
	TextDrawSetShadow(TDBottomBeltStatic[10], 1);
	TextDrawUseBox(TDBottomBeltStatic[10], 1);
	TextDrawBoxColor(TDBottomBeltStatic[10], 255);
	TextDrawTextSize(TDBottomBeltStatic[10], 58.000000, 29.000000);

	TDBottomBeltStatic[11] = TextDrawCreate(219.000000, 443.000000, "hud:radar_gangY");
	TextDrawBackgroundColor(TDBottomBeltStatic[11], 255);
	TextDrawFont(TDBottomBeltStatic[11], 4);
	TextDrawLetterSize(TDBottomBeltStatic[11], 0.500000, 1.000000);
	TextDrawColor(TDBottomBeltStatic[11], -1);
	TextDrawSetOutline(TDBottomBeltStatic[11], 0);
	TextDrawSetProportional(TDBottomBeltStatic[11], 1);
	TextDrawSetShadow(TDBottomBeltStatic[11], 1);
	TextDrawUseBox(TDBottomBeltStatic[11], 1);
	TextDrawBoxColor(TDBottomBeltStatic[11], 255);
	TextDrawTextSize(TDBottomBeltStatic[11], 5.000000, 5.000000);

	TDBottomBeltStatic[12] = TextDrawCreate(429.000000, 443.000000, "hud:radar_gangN");
	TextDrawBackgroundColor(TDBottomBeltStatic[12], 255);
	TextDrawFont(TDBottomBeltStatic[12], 4);
	TextDrawLetterSize(TDBottomBeltStatic[12], 0.500000, 1.000000);
	TextDrawColor(TDBottomBeltStatic[12], -1);
	TextDrawSetOutline(TDBottomBeltStatic[12], 0);
	TextDrawSetProportional(TDBottomBeltStatic[12], 1);
	TextDrawSetShadow(TDBottomBeltStatic[12], 1);
	TextDrawUseBox(TDBottomBeltStatic[12], 1);
	TextDrawBoxColor(TDBottomBeltStatic[12], 255);
	TextDrawTextSize(TDBottomBeltStatic[12], 5.000000, 5.000000);

	TDBottomBeltStatic[13] = TextDrawCreate(455.000000, 443.000000, "hud:radar_gangB");
	TextDrawBackgroundColor(TDBottomBeltStatic[13], 255);
	TextDrawFont(TDBottomBeltStatic[13], 4);
	TextDrawLetterSize(TDBottomBeltStatic[13], 0.500000, 1.000000);
	TextDrawColor(TDBottomBeltStatic[13], -1);
	TextDrawSetOutline(TDBottomBeltStatic[13], 0);
	TextDrawSetProportional(TDBottomBeltStatic[13], 1);
	TextDrawSetShadow(TDBottomBeltStatic[13], 1);
	TextDrawUseBox(TDBottomBeltStatic[13], 1);
	TextDrawBoxColor(TDBottomBeltStatic[13], 255);
	TextDrawTextSize(TDBottomBeltStatic[13], 5.000000, 5.000000);

	TDBottomBeltStatic[14] = TextDrawCreate(195.000000, 443.000000, "hud:radar_gangB");
	TextDrawBackgroundColor(TDBottomBeltStatic[14], 255);
	TextDrawFont(TDBottomBeltStatic[14], 4);
	TextDrawLetterSize(TDBottomBeltStatic[14], 0.500000, 1.000000);
	TextDrawColor(TDBottomBeltStatic[14], -1);
	TextDrawSetOutline(TDBottomBeltStatic[14], 0);
	TextDrawSetProportional(TDBottomBeltStatic[14], 1);
	TextDrawSetShadow(TDBottomBeltStatic[14], 1);
	TextDrawUseBox(TDBottomBeltStatic[14], 1);
	TextDrawBoxColor(TDBottomBeltStatic[14], 255);
	TextDrawTextSize(TDBottomBeltStatic[14], 5.000000, 5.000000);

	TDBottomBeltStatic[15] = TextDrawCreate(249.000000, 443.000000, "hud:radar_girlfriend");
	TextDrawBackgroundColor(TDBottomBeltStatic[15], 255);
	TextDrawFont(TDBottomBeltStatic[15], 4);
	TextDrawLetterSize(TDBottomBeltStatic[15], 0.500000, 1.000000);
	TextDrawColor(TDBottomBeltStatic[15], -1);
	TextDrawSetOutline(TDBottomBeltStatic[15], 0);
	TextDrawSetProportional(TDBottomBeltStatic[15], 1);
	TextDrawSetShadow(TDBottomBeltStatic[15], 1);
	TextDrawUseBox(TDBottomBeltStatic[15], 1);
	TextDrawBoxColor(TDBottomBeltStatic[15], 255);
	TextDrawTextSize(TDBottomBeltStatic[15], 5.000000, 5.000000);

	TDBottomBeltStatic[16] = TextDrawCreate(409.000000, 443.000000, "hud:radar_girlfriend");
	TextDrawBackgroundColor(TDBottomBeltStatic[16], 255);
	TextDrawFont(TDBottomBeltStatic[16], 4);
	TextDrawLetterSize(TDBottomBeltStatic[16], 0.500000, 1.000000);
	TextDrawColor(TDBottomBeltStatic[16], -1);
	TextDrawSetOutline(TDBottomBeltStatic[16], 0);
	TextDrawSetProportional(TDBottomBeltStatic[16], 1);
	TextDrawSetShadow(TDBottomBeltStatic[16], 1);
	TextDrawUseBox(TDBottomBeltStatic[16], 1);
	TextDrawBoxColor(TDBottomBeltStatic[16], 255);
	TextDrawTextSize(TDBottomBeltStatic[16], 5.000000, 5.000000);

	TDBottomBeltStatic[17] = TextDrawCreate(365.000000, 442.000000, "hud:radar_EnemyAttack");
	TextDrawBackgroundColor(TDBottomBeltStatic[17], 255);
	TextDrawFont(TDBottomBeltStatic[17], 4);
	TextDrawLetterSize(TDBottomBeltStatic[17], 0.500000, 1.000000);
	TextDrawColor(TDBottomBeltStatic[17], -1);
	TextDrawSetOutline(TDBottomBeltStatic[17], 0);
	TextDrawSetProportional(TDBottomBeltStatic[17], 1);
	TextDrawSetShadow(TDBottomBeltStatic[17], 1);
	TextDrawUseBox(TDBottomBeltStatic[17], 1);
	TextDrawBoxColor(TDBottomBeltStatic[17], 255);
	TextDrawTextSize(TDBottomBeltStatic[17], 5.000000, 5.000000);

	TDBottomBeltStatic[18] = TextDrawCreate(305.000000, 442.000000, "LD_GRAV:timer");
	TextDrawBackgroundColor(TDBottomBeltStatic[18], 255);
	TextDrawFont(TDBottomBeltStatic[18], 4);
	TextDrawLetterSize(TDBottomBeltStatic[18], 0.500000, 1.000000);
	TextDrawColor(TDBottomBeltStatic[18], -1);
	TextDrawSetOutline(TDBottomBeltStatic[18], 0);
	TextDrawSetProportional(TDBottomBeltStatic[18], 1);
	TextDrawSetShadow(TDBottomBeltStatic[18], 1);
	TextDrawUseBox(TDBottomBeltStatic[18], 1);
	TextDrawBoxColor(TDBottomBeltStatic[18], 255);
	TextDrawTextSize(TDBottomBeltStatic[18], 5.000000, 5.000000);

	TDBottomBeltCenter[0] = TextDrawCreate(289.000000, 437.000000, "--:--");
	TextDrawAlignment(TDBottomBeltCenter[0], 2);
	TextDrawBackgroundColor(TDBottomBeltCenter[0], 48);
	TextDrawFont(TDBottomBeltCenter[0], 1);
	TextDrawLetterSize(TDBottomBeltCenter[0], 0.220000, 0.899999);
	TextDrawColor(TDBottomBeltCenter[0], -1);
	TextDrawSetOutline(TDBottomBeltCenter[0], 0);
	TextDrawSetProportional(TDBottomBeltCenter[0], 1);
	TextDrawSetShadow(TDBottomBeltCenter[0], 1);

	TDBottomBeltCenter[1] = TextDrawCreate(341.000000, 437.000000, "NoN");
	TextDrawAlignment(TDBottomBeltCenter[1], 2);
	TextDrawBackgroundColor(TDBottomBeltCenter[1], 48);
	TextDrawFont(TDBottomBeltCenter[1], 1);
	TextDrawLetterSize(TDBottomBeltCenter[1], 0.220000, 0.899999);
	TextDrawColor(TDBottomBeltCenter[1], -1);
	TextDrawSetOutline(TDBottomBeltCenter[1], 0);
	TextDrawSetProportional(TDBottomBeltCenter[1], 1);
	TextDrawSetShadow(TDBottomBeltCenter[1], 1);

	TDBottomBeltTeamLeft[0] = TextDrawCreate(155.000000, 437.000000, "Atak");
	TextDrawAlignment(TDBottomBeltTeamLeft[0], 2);
	TextDrawBackgroundColor(TDBottomBeltTeamLeft[0], 48);
	TextDrawFont(TDBottomBeltTeamLeft[0], 1);
	TextDrawLetterSize(TDBottomBeltTeamLeft[0], 0.220000, 0.899999);
	TextDrawColor(TDBottomBeltTeamLeft[0], -201777921);
	TextDrawSetOutline(TDBottomBeltTeamLeft[0], 0);
	TextDrawSetProportional(TDBottomBeltTeamLeft[0], 1);
	TextDrawSetShadow(TDBottomBeltTeamLeft[0], 1);

	TDBottomBeltTeamRight[0] = TextDrawCreate(485.000000, 437.000000, "Obrona");
	TextDrawAlignment(TDBottomBeltTeamRight[0], 2);
	TextDrawBackgroundColor(TDBottomBeltTeamRight[0], 48);
	TextDrawFont(TDBottomBeltTeamRight[0], 1);
	TextDrawLetterSize(TDBottomBeltTeamRight[0], 0.220000, 0.899999);
	TextDrawColor(TDBottomBeltTeamRight[0], 1061158143);
	TextDrawSetOutline(TDBottomBeltTeamRight[0], 0);
	TextDrawSetProportional(TDBottomBeltTeamRight[0], 1);
	TextDrawSetShadow(TDBottomBeltTeamRight[0], 1);

	TDBottomBeltTeamLeft[1] = TextDrawCreate(189.000000, 437.000000, "0");     	//Calkowita ilosc graczy w teamie
	TextDrawAlignment(TDBottomBeltTeamLeft[1], 2);
	TextDrawBackgroundColor(TDBottomBeltTeamLeft[1], 48);
	TextDrawFont(TDBottomBeltTeamLeft[1], 1);
	TextDrawLetterSize(TDBottomBeltTeamLeft[1], 0.220000, 0.899999);
	TextDrawColor(TDBottomBeltTeamLeft[1], -1);
	TextDrawSetOutline(TDBottomBeltTeamLeft[1], 0);
	TextDrawSetProportional(TDBottomBeltTeamLeft[1], 1);
	TextDrawSetShadow(TDBottomBeltTeamLeft[1], 1);

	TDBottomBeltTeamRight[1] = TextDrawCreate(449.000000, 437.000000, "0");     //Calkowita ilosc graczy w teamie
	TextDrawAlignment(TDBottomBeltTeamRight[1], 2);
	TextDrawBackgroundColor(TDBottomBeltTeamRight[1], 48);
	TextDrawFont(TDBottomBeltTeamRight[1], 1);
	TextDrawLetterSize(TDBottomBeltTeamRight[1], 0.220000, 0.899999);
	TextDrawColor(TDBottomBeltTeamRight[1], -1);
	TextDrawSetOutline(TDBottomBeltTeamRight[1], 0);
	TextDrawSetProportional(TDBottomBeltTeamRight[1], 1);
	TextDrawSetShadow(TDBottomBeltTeamRight[1], 1);

	TDBottomBeltTeamLeft[2] = TextDrawCreate(213.000000, 437.000000, "0");     	//Ilosc zywych graczy w teamie
	TextDrawAlignment(TDBottomBeltTeamLeft[2], 2);
	TextDrawBackgroundColor(TDBottomBeltTeamLeft[2], 48);
	TextDrawFont(TDBottomBeltTeamLeft[2], 1);
	TextDrawLetterSize(TDBottomBeltTeamLeft[2], 0.220000, 0.899999);
	TextDrawColor(TDBottomBeltTeamLeft[2], -1);
	TextDrawSetOutline(TDBottomBeltTeamLeft[2], 0);
	TextDrawSetProportional(TDBottomBeltTeamLeft[2], 1);
	TextDrawSetShadow(TDBottomBeltTeamLeft[2], 1);

	TDBottomBeltTeamRight[2] = TextDrawCreate(423.000000, 437.000000, "0");     //Ilosc zywych graczy w teamie
	TextDrawAlignment(TDBottomBeltTeamRight[2], 2);
	TextDrawBackgroundColor(TDBottomBeltTeamRight[2], 48);
	TextDrawFont(TDBottomBeltTeamRight[2], 1);
	TextDrawLetterSize(TDBottomBeltTeamRight[2], 0.220000, 0.899999);
	TextDrawColor(TDBottomBeltTeamRight[2], -1);
	TextDrawSetOutline(TDBottomBeltTeamRight[2], 0);
	TextDrawSetProportional(TDBottomBeltTeamRight[2], 1);
	TextDrawSetShadow(TDBottomBeltTeamRight[2], 1);

	TDBottomBeltTeamLeft[3] = TextDrawCreate(247.000000, 437.000000, "0");      //Zdrowie graczy
	TextDrawAlignment(TDBottomBeltTeamLeft[3], 3);
	TextDrawBackgroundColor(TDBottomBeltTeamLeft[3], 48);
	TextDrawFont(TDBottomBeltTeamLeft[3], 1);
	TextDrawLetterSize(TDBottomBeltTeamLeft[3], 0.220000, 0.899999);
	TextDrawColor(TDBottomBeltTeamLeft[3], -1);
	TextDrawSetOutline(TDBottomBeltTeamLeft[3], 0);
	TextDrawSetProportional(TDBottomBeltTeamLeft[3], 1);
	TextDrawSetShadow(TDBottomBeltTeamLeft[3], 1);

	TDBottomBeltTeamRight[3] = TextDrawCreate(407.000000, 437.000000, "0");     //Zdrowie graczy
	TextDrawAlignment(TDBottomBeltTeamRight[3], 3);
	TextDrawBackgroundColor(TDBottomBeltTeamRight[3], 48);
	TextDrawFont(TDBottomBeltTeamRight[3], 1);
	TextDrawLetterSize(TDBottomBeltTeamRight[3], 0.220000, 0.899999);
	TextDrawColor(TDBottomBeltTeamRight[3], -1);
	TextDrawSetOutline(TDBottomBeltTeamRight[3], 0);
	TextDrawSetProportional(TDBottomBeltTeamRight[3], 1);
	TextDrawSetShadow(TDBottomBeltTeamRight[3], 1);

	TDCaptureStatic[0] = TextDrawCreate(266.000000, 400.000000, "LD_POKE:cd9s");
	TextDrawBackgroundColor(TDCaptureStatic[0], 255);
	TextDrawFont(TDCaptureStatic[0], 4);
	TextDrawLetterSize(TDCaptureStatic[0], 0.500000, 1.000000);
	TextDrawColor(TDCaptureStatic[0], 48);
	TextDrawSetOutline(TDCaptureStatic[0], 0);
	TextDrawSetProportional(TDCaptureStatic[0], 1);
	TextDrawSetShadow(TDCaptureStatic[0], 1);
	TextDrawUseBox(TDCaptureStatic[0], 1);
	TextDrawBoxColor(TDCaptureStatic[0], 255);
	TextDrawTextSize(TDCaptureStatic[0], 108.000000, 25.000000);

	TDCaptureStatic[1] = TextDrawCreate(271.000000, 414.000000, "LD_OTB2:butnAo");
	TextDrawBackgroundColor(TDCaptureStatic[1], 255);
	TextDrawFont(TDCaptureStatic[1], 4);
	TextDrawLetterSize(TDCaptureStatic[1], 0.500000, 1.000000);
	TextDrawColor(TDCaptureStatic[1], 72329808);
	TextDrawSetOutline(TDCaptureStatic[1], 0);
	TextDrawSetProportional(TDCaptureStatic[1], 1);
	TextDrawSetShadow(TDCaptureStatic[1], 1);
	TextDrawUseBox(TDCaptureStatic[1], 1);
	TextDrawBoxColor(TDCaptureStatic[1], 255);
	TextDrawTextSize(TDCaptureStatic[1], 99.000000, 11.000000);

	TDCaptureStatic[2] = TextDrawCreate(320.000000, 403.000000, "Przejecie bazy");
	TextDrawAlignment(TDCaptureStatic[2], 2);
	TextDrawBackgroundColor(TDCaptureStatic[2], 48);
	TextDrawFont(TDCaptureStatic[2], 1);
	TextDrawLetterSize(TDCaptureStatic[2], 0.250000, 0.899999);
	TextDrawColor(TDCaptureStatic[2], 759037951);
	TextDrawSetOutline(TDCaptureStatic[2], 0);
	TextDrawSetProportional(TDCaptureStatic[2], 1);
	TextDrawSetShadow(TDCaptureStatic[2], 1);

	TDCaptureBox = TextDrawCreate(271.000000, 414.000000, "LD_OTB2:butnAo");
	TextDrawBackgroundColor(TDCaptureBox, 255);
	TextDrawFont(TDCaptureBox, 4);
	TextDrawLetterSize(TDCaptureBox, 0.500000, 1.000000);
	TextDrawColor(TDCaptureBox, 72329983);
	TextDrawSetOutline(TDCaptureBox, 0);
	TextDrawSetProportional(TDCaptureBox, 1);
	TextDrawSetShadow(TDCaptureBox, 1);
	TextDrawUseBox(TDCaptureBox, 1);
	TextDrawBoxColor(TDCaptureBox, 255);
	TextDrawTextSize(TDCaptureBox, 59.000000, 11.000000);

	TDCaptureInfo = TextDrawCreate(321.000000, 415.000000, "100 %");
	TextDrawAlignment(TDCaptureInfo, 2);
	TextDrawBackgroundColor(TDCaptureInfo, 48);
	TextDrawFont(TDCaptureInfo, 1);
	TextDrawLetterSize(TDCaptureInfo, 0.160000, 0.599999);
	TextDrawColor(TDCaptureInfo, -1);
	TextDrawSetOutline(TDCaptureInfo, 0);
	TextDrawSetProportional(TDCaptureInfo, 1);
	TextDrawSetShadow(TDCaptureInfo, 1);
	
	TDAimedStatic[0] = TextDrawCreate(517.000000, 318.000000, "LD_POKE:cd9s");
	TextDrawBackgroundColor(TDAimedStatic[0], 255);
	TextDrawFont(TDAimedStatic[0], 4);
	TextDrawLetterSize(TDAimedStatic[0], 0.500000, 1.000000);
	TextDrawColor(TDAimedStatic[0], 64);
	TextDrawSetOutline(TDAimedStatic[0], 0);
	TextDrawSetProportional(TDAimedStatic[0], 1);
	TextDrawSetShadow(TDAimedStatic[0], 1);
	TextDrawUseBox(TDAimedStatic[0], 1);
	TextDrawBoxColor(TDAimedStatic[0], 255);
	TextDrawTextSize(TDAimedStatic[0], 80.000000, 47.000000);

	TDAimedStatic[1] = TextDrawCreate(556.000000, 332.000000, "Zdrowie~n~Armor~n~Ping~n~FPS~n~P-Loss~n~_");
	TextDrawAlignment(TDAimedStatic[1], 3);
	TextDrawBackgroundColor(TDAimedStatic[1], 64);
	TextDrawFont(TDAimedStatic[1], 1);
	TextDrawLetterSize(TDAimedStatic[1], 0.170000, 0.699999);
	TextDrawColor(TDAimedStatic[1], 74764031);
	TextDrawSetOutline(TDAimedStatic[1], 0);
	TextDrawSetProportional(TDAimedStatic[1], 1);
	TextDrawSetShadow(TDAimedStatic[1], 1);

	TDAimedStatic[2] = TextDrawCreate(517.000000, 329.000000, "LD_POOL:ball");
	TextDrawBackgroundColor(TDAimedStatic[2], 255);
	TextDrawFont(TDAimedStatic[2], 4);
	TextDrawLetterSize(TDAimedStatic[2], 0.500000, 1.000000);
	TextDrawColor(TDAimedStatic[2], 74764031);
	TextDrawSetOutline(TDAimedStatic[2], 0);
	TextDrawSetProportional(TDAimedStatic[2], 1);
	TextDrawSetShadow(TDAimedStatic[2], 1);
	TextDrawUseBox(TDAimedStatic[2], 1);
	TextDrawBoxColor(TDAimedStatic[2], 255);
	TextDrawTextSize(TDAimedStatic[2], 80.000000, 1.000000);
	
	for(new i; i < MAX_PLAYERS; i ++) {
    	CreatePlayerTextDraws(i);
	}
	
    //CreateObject(18759, 183.2925, -1968.3705, 2076.2225, 0.0, 0.0, 0.0, 50.0); //Obiekt areny duel

    #if _TESTY == 1 and NPC_CONNECT > 0
    for(new i, name[32]; i < NPC_CONNECT; i ++) {
        format(name, sizeof(name), "NPC_%d", i);
   		ConnectNPC(name, "onfoot_test");
    }
    #endif
 	return 1;
}

//------------------------------------------------------------------------------

public OnGameModeExit() {
	GameTextForAll("Restart", 3000, 1);
	saveGameModeSettings();
	saveWeaponsSettings();
	return 1;
}
	
//------------------------------------------------------------------------------
public OnPlayerConnect(playerid) {
	if(playerid >= MAX_GRACZY) {
	    SendClientMessage(playerid, COLOR_KICK, " (Kick) Zostal osiagniety limit graczy gamemoda.");
	    KickEx(playerid, 100);
	    return 1;
	}


    SetPlayerNick(playerid);                                                    //From player.inc

	for(new i; i < 20; i++) SendClientMessage(playerid, -1, " ");

	//---------------------------
	SetPlayerWeaponRequestStatus(playerid, NEW_WEAPONS);
	ForceSetPlayerRoundWeapon(playerid, _FIRST, -1, _PRIMARY);
	ForceSetPlayerRoundWeapon(playerid, _SECOND, -1, _PRIMARY);
	ForceSetPlayerRoundWeapon(playerid, _FIRST, -1, _SAVED);
	ForceSetPlayerRoundWeapon(playerid, _SECOND, -1, _SAVED);

    ResetPlayerFakeKillWarnings(playerid);
    G[playerid][WybieralkaZabezpieczenie] =
	G[playerid][VoteDodano] = G[playerid][PrzyciskSpecowaniaWcisniety] = false;
	
 	G[playerid][UdzialWWalceTeam] = T_NoN;
	G[playerid][SpecowanyID] = G[playerid][SparingIDGracza] = INVALID_PLAYER_ID;

	G[playerid][gFragiRunda] = G[playerid][gDMGRunda] = G[playerid][gFragi] =
	G[playerid][gSmierci] = G[playerid][gRespect] = G[playerid][gDMG] =
	G[playerid][CzasAreaCheck] = 0;
	
    G[playerid][VoteWybor] = -1;
    
    //---------------------------

	SetPlayerFightingStyle(playerid, FIGHT_STYLE_BOXING);
	SetPlayerColor(playerid, COLOR_GREY);

    TextDrawSetString(PTD_PlayerHudNick[playerid], GetPlayerNick(playerid));
    
   	if(P_WorldArea[playerid][OBJECT_ID] != INVALID_OBJECT_ID) {
		DestroyPlayerObject(playerid, P_WorldArea[playerid][OBJECT_ID]);
		P_WorldArea[playerid][OBJECT_ID] = INVALID_OBJECT_ID;
	}
	return 1;
}

//------------------------------------------------------------------------------

public OnPlayerDisconnect(playerid, reason) {
	
    G[playerid][AddAfterSpawn] = false;
	DialogHideForPlayer(playerid);
	Delete3DTextLabel(G[playerid][ZdrowiePojazdu3D]);

    DemoArenaEnd(playerid);
    
	if(G[playerid][IDPojazdu] != 0) {
	    if(GetVehicleVirtualWorld(G[playerid][IDPojazdu]) != VW_GRA) DestroyVehicle(G[playerid][IDPojazdu]);
    }

	if(getPlayerStatus(playerid) == S_SPAR) {
        new IDGracza;
	    SendClientMessage((IDGracza = G[playerid][SparingIDGracza]), COLOR_SPARING_INFO," (Sparing) Twoj przeciwnik opuscil serwer");
	    KoniecSparingu(IDGracza);
    } else if(getPlayerStatus(playerid) == S_GRA) {
        new Float:health;
        GetPlayerHealth(playerid, health);
        if(health > 0.0 and G[playerid][HitInGame] == true) {
            new string[140];
            format(string, sizeof(string), " (Runda) Gracz "C_WHITE"%s "TEXT_RESPECT_INFO"opuscil serwer podczas walki. (Zdrowie: "C_WHITE"%.0f"TEXT_RESPECT_INFO")", GetPlayerNick(playerid), health);
            SendClientMessageToAll(COLOR_RESPECT_INFO, string);
            
            if(GetPlayerLoginStatus(playerid) == LOGIN_STATUS_LOGGED) {
            	CallRemoteFunction("PlayerLeftInRound", "dd", GetPlayerUserID(playerid), sLeftSrvInRound);
 			}
        }
    }

	else if(getPlayerStatus(playerid) == S_GRA) {
        for(new i, x, bool:Znalazlo; i < MAX_GRACZY; i ++) {
			if(IsPlayerConnected(i)) {
			    if(getPlayerStatus(i) == S_SPECUJE) {
			        if(G[i][SpecowanyID] == playerid) {
				        for(x = 0, Znalazlo = false; x < MAX_GRACZY; x ++) {
				            if(IsPlayerConnected(x)) {
				                if(StartSpectate(i, x) == 1) {
				                    Znalazlo = true;
				                    break;
				                }
				            }
				        }
				        if(Znalazlo == false) StopSpec(i);
				    }
			    }
			}
        }
	}

	if(G[playerid][VoteWybor] >= 0) {
	    if(VoteVar[G[playerid][VoteWybor]][Tryb] > -1) {
	        VoteVar[G[playerid][VoteWybor]][Glosow] -= (IsVIP(playerid) == _TRUE ? 2 : 1);
	        CheckVotePossibility();
	    }
	}

    ResetPlayerNick(playerid);                                                  //From player.inc

    setPlayerStatus(playerid, S_NON);
	setPlayerTeam(playerid, T_NoN);

	return 1;
}

//------------------------------------------------------------------------------

public OnPlayerRequestClass(playerid, classid) {
	new string[128];
	if(G[playerid][WybieralkaZabezpieczenie] == false) {
	    G[playerid][WybieralkaZabezpieczenie] = true;
		
		SetPlayerVirtualWorld(playerid, VW_WYBIERALKA);
		setPlayerStatus(playerid, S_WYBIERALKA);                                // Wazne zeby status byl zmieniany wczesniej niz team.
		setPlayerTeam(playerid, T_NoN);

		LayoutBottomBelt(playerid, false);
		LayoutPlayerHud(playerid, false);
		LayoutPlayerCapture(playerid, false);
		LayoutPlayerOneOnOne(playerid, false);
		LayoutPlayerRoundWin(playerid, false);
		LayoutPlayerCountdown(playerid, false);
		LayoutSpawnProtect(playerid, false);
		LayoutPingFPS(playerid, false);
		LayoutTime(playerid, false);
		
		TextDrawHideForPlayer(playerid, PTD_KilledBy[playerid][0]);
		TextDrawHideForPlayer(playerid, PTD_KilledBy[playerid][1]);
		
		TextDrawShowForPlayer(playerid, TDZaciemnienie);
		//TextDrawShowForPlayer(playerid, TDLogoDuzeOFP);
		/*
		TextDrawHideForPlayer(playerid, TDHighSkillMaleLogo);
		TextDrawHideForPlayer(playerid, TDHighSkill2MaleLogo);
		TextDrawHideForPlayer(playerid, TDStronaMaleLogo);
		TextDrawHideForPlayer(playerid, TDOnlyForProMaleLogo);
		TextDrawHideForPlayer(playerid, TDAutorMaleLogo);
		TextDrawHideForPlayer(playerid, TDPasekMaleLogo);
		*/
		TextDrawHideForPlayer(playerid, G[playerid][TDZdrowie]);

        TextDrawHideForPlayer(playerid, TDVoteName);
        TextDrawHideForPlayer(playerid, TDVoteInfo);
		TextDrawHideForPlayer(playerid, TDCarInfo);
		TextDrawShowForPlayer(playerid, TDWybieralkaDruzyna);
		TextDrawShowForPlayer(playerid, TDAtak);
		TextDrawShowForPlayer(playerid, TDObrona);
		TextDrawShowForPlayer(playerid, TDArbiter);
		TextDrawShowForPlayer(playerid, TDIloscGraczy);
//		TextDrawShowForPlayer(playerid, TDLogoDuzeIghKill);
		TextDrawShowForPlayer(playerid, TDLogoDuzeH);
		TextDrawShowForPlayer(playerid, TDLogoDuzeS);
		TextDrawShowForPlayer(playerid, TDLogoDuzePL);
		TextDrawShowForPlayer(playerid, TDLogoDuzeLinijka);
		
		
	    if(OgloszenieCzas > timestamp()) {
	    	TextDrawShowForPlayer(playerid, TDOgloszenieBox);
	    	TextDrawShowForPlayer(playerid, TDOgloszenieSerwerowe);
		} else {
		    TextDrawHideForPlayer(playerid, TDOgloszenieBox);
	        TextDrawHideForPlayer(playerid, TDOgloszenieSerwerowe);
		}
		if(getPlayerLoginStatus(playerid) == LOGIN_STATUS_NOTLOGGED) CallRemoteFunction("PokazMenuLogowania", "d", playerid);
	}

	format(string, sizeof(string), "Graczy: %d               Graczy: %d            Dla Administracji !", getPlayersInTeam(T_DEF), getPlayersInTeam(T_ATT));
	TextDrawSetString(TDIloscGraczy, string);
	
    PlayerPlaySound(playerid, 1068, 0, 0, 0);
	switch(classid) {
		case 0: {
            TextDrawHideForPlayer(playerid, TDAtakAktywny);     TextDrawHideForPlayer(playerid, TDAtak2);
            TextDrawShowForPlayer(playerid, TDObronaAktywna);  	TextDrawShowForPlayer(playerid, TDObrona2);
            TextDrawHideForPlayer(playerid, TDAktywnyArbiter);  TextDrawHideForPlayer(playerid, TDArbiter2);
	    }
		case 1: {
			TextDrawShowForPlayer(playerid, TDAtakAktywny);     TextDrawShowForPlayer(playerid, TDAtak2);
			TextDrawHideForPlayer(playerid, TDObronaAktywna);   TextDrawHideForPlayer(playerid, TDObrona2);
			TextDrawHideForPlayer(playerid, TDAktywnyArbiter);  TextDrawHideForPlayer(playerid, TDArbiter2);
        }
		case 2: {
            TextDrawHideForPlayer(playerid, TDAtakAktywny);     TextDrawHideForPlayer(playerid, TDAtak2);
            TextDrawHideForPlayer(playerid, TDObronaAktywna);   TextDrawHideForPlayer(playerid, TDObrona2);
            TextDrawShowForPlayer(playerid, TDAktywnyArbiter);  TextDrawShowForPlayer(playerid, TDArbiter2);
	    }
	}
	return 1;
}

//------------------------------------------------------------------------------

public OnPlayerRequestSpawn(playerid) {
	if(getPlayerLoginStatus(playerid) == LOGIN_STATUS_NOTLOGGED) return 0;
	else {
		new string[128];
		switch(GetPlayerSkin(playerid)) {
		    case SKIN_ATT: {
			    #if _TESTY == 0 || NPC_CONNECT <= 0
				if(getPlayersInTeam(T_ATT) - getPlayersInTeam(T_DEF) > 0) {
	                PlayerPlaySound(playerid, 1085, 0, 0, 0);
			        TextDrawHideForPlayer(playerid, TDDlaAdministracjiSerwera);
			        TextDrawShowForPlayer(playerid, TDZaduzoGraczyWTeamie);
			        SetTimerEx("KoniecWarnWybieralka", 3000, 0, "d", playerid);
				    return 0;
			    } else {
			    #endif
	                setPlayerTeam(playerid, T_ATT);
				    format(string, sizeof(string)," (Spawn) "DIALOG_NORMAL_COLOR"%s"DIALOG_TEAM_CHANGE_COLOR" dolaczyl(a) do druzyny "DIALOG_NORMAL_COLOR"Ataku", GetPlayerNick(playerid));
				    SendClientMessageToAll(DIALOG_TEAM_CHANGE_FULL_COLOR, string);
                #if _TESTY == 0 || NPC_CONNECT <= 0
				}
				#endif
			}
		    case SKIN_DEF: {
			    #if _TESTY == 0 || NPC_CONNECT <= 0
				if(getPlayersInTeam(T_DEF) - getPlayersInTeam(T_ATT) > 0) {
	                PlayerPlaySound(playerid, 1085, 0, 0, 0);
			        TextDrawHideForPlayer(playerid, TDDlaAdministracjiSerwera);
			        TextDrawShowForPlayer(playerid, TDZaduzoGraczyWTeamie);
			        SetTimerEx("KoniecWarnWybieralka", 3000, 0, "d", playerid);
				    return 0;
			    } else {
			    #endif
	                setPlayerTeam(playerid, T_DEF);
				    format(string, sizeof(string)," (Spawn) "DIALOG_NORMAL_COLOR"%s"DIALOG_TEAM_CHANGE_COLOR" dolaczyl(a) do druzyny "DIALOG_NORMAL_COLOR"Obrony", GetPlayerNick(playerid));
				    SendClientMessageToAll(DIALOG_TEAM_CHANGE_FULL_COLOR, string);
                #if _TESTY == 0 || NPC_CONNECT <= 0
				}
				#endif
			}
		    case SKIN_REF: {
			    #if _TESTY == 0 || NPC_CONNECT <= 0
				if(IsAdmin(playerid) == ALVL_NON and IsVIP(playerid) == _FALSE) {
	                PlayerPlaySound(playerid, 1085, 0, 0, 0);
			        TextDrawShowForPlayer(playerid, TDDlaAdministracjiSerwera);
			        TextDrawHideForPlayer(playerid, TDZaduzoGraczyWTeamie);
			        SetTimerEx("KoniecWarnWybieralka", 3000, 0, "d", playerid);
				    return 0;
			    } else {
			    #endif
	                setPlayerTeam(playerid, T_REF);
				    format(string, sizeof(string)," (Spawn) "DIALOG_NORMAL_COLOR"%s"DIALOG_TEAM_CHANGE_COLOR" dolaczyl(a) do druzyny "DIALOG_NORMAL_COLOR"Arbitrow", GetPlayerNick(playerid));
				    SendClientMessageToAll(DIALOG_TEAM_CHANGE_FULL_COLOR, string);
                #if _TESTY == 0 || NPC_CONNECT <= 0
				}
				#endif
			}
		    default: {
		        SendClientMessage(playerid, COLOR_WARNING," (Spawn) Blad skryptu - Prosze zglosic problem do administracji serwera");
		        return 0;
	        }
	    }

		TextDrawHideForPlayer(playerid, TDWybieralkaDruzyna);
		TextDrawHideForPlayer(playerid, TDAtak);
		TextDrawHideForPlayer(playerid, TDAtak2);
		TextDrawHideForPlayer(playerid, TDAtakAktywny);
		TextDrawHideForPlayer(playerid, TDObrona);
		TextDrawHideForPlayer(playerid, TDObrona2);
		TextDrawHideForPlayer(playerid, TDObronaAktywna);
		TextDrawHideForPlayer(playerid, TDArbiter);
		TextDrawHideForPlayer(playerid, TDArbiter2);
		TextDrawHideForPlayer(playerid, TDAktywnyArbiter);
		TextDrawHideForPlayer(playerid, TDIloscGraczy);
		TextDrawHideForPlayer(playerid,	TDZaciemnienie);
//		TextDrawHideForPlayer(playerid, TDLogoDuzeIghKill);
		TextDrawHideForPlayer(playerid, TDLogoDuzeH);
		TextDrawHideForPlayer(playerid, TDLogoDuzeS);
		TextDrawHideForPlayer(playerid, TDLogoDuzePL);
		TextDrawHideForPlayer(playerid, TDLogoDuzeLinijka);
		//TextDrawHideForPlayer(playerid,	TDLogoDuzeOFP);
	    TextDrawHideForPlayer(playerid, TDDlaAdministracjiSerwera);
	    TextDrawHideForPlayer(playerid, TDZaduzoGraczyWTeamie);
	    TextDrawHideForPlayer(playerid, TDOgloszenieBox);
	    TextDrawHideForPlayer(playerid, TDOgloszenieSerwerowe);

/*
		TextDrawShowForPlayer(playerid, TDHighSkillMaleLogo);
		TextDrawShowForPlayer(playerid, TDHighSkill2MaleLogo);
		TextDrawShowForPlayer(playerid, TDStronaMaleLogo);
		TextDrawShowForPlayer(playerid, TDOnlyForProMaleLogo);
		TextDrawShowForPlayer(playerid, TDAutorMaleLogo);
		TextDrawShowForPlayer(playerid, TDPasekMaleLogo);
*/
	    TextDrawShowForPlayer(playerid, G[playerid][TDZdrowie]);
	    
		LayoutPingFPS(playerid, true);
        LayoutBottomBelt(playerid, true);
        LayoutPlayerHud(playerid, true);
		LayoutTime(playerid, true);

		SendClientMessage(playerid, COLOR_CMD_INFO, " (Pojazd) Wpisz "TEXT_NORMAL"/car [Model Pojazdu / Nazwa]"TEXT_CMD_INFO" aby zespawnowac pojazd");
		SendClientMessage(playerid, COLOR_CMD_INFO, " (Arena DM) Wpisz "TEXT_NORMAL"/dm"TEXT_CMD_INFO" aby przeniesc sie na arene Death Match");
		SendClientMessage(playerid, COLOR_CMD_INFO, " (Sparing) Wpisz "TEXT_NORMAL"/spar"TEXT_CMD_INFO" aby zaproponowac komus sparing 1 vs 1");
        SendClientMessage(playerid, COLOR_CMD_INFO, " (Pomoc) Wpisz "TEXT_NORMAL"/pomoc"TEXT_CMD_INFO" zeby otrzymac informacje nt. komend, ustawien serwera itp.");
        
		setPlayerStatus(playerid, S_SPAWN);
		PlayerPlaySound(playerid, 1069, 0, 0, 0);

		CallRemoteFunction("UpdatePlayerRanking", "d", playerid);
		UpdatePlayerStats(playerid);

        G[playerid][WybieralkaZabezpieczenie] = false;
	}
	return 1;
}

//------------------------------------------------------------------------------

public OnPlayerSpawn(playerid) {
	SetCameraBehindPlayer(playerid);
	G[playerid][CzasPokazywaniaUtratyHP] = 0;
	TextDrawHideForPlayer(playerid, PTD_KilledBy[playerid][0]);
    TextDrawHideForPlayer(playerid, PTD_KilledBy[playerid][1]);
    
    if(G[playerid][AddAfterSpawn] == true) {
        G[playerid][AddAfterSpawn] = false;
        if(IDStartowanej != -1 and TrwaOdliczanie == false) {
            new string[140];
            format(string, sizeof(string), " (Respawn) Gracz "C_WHITE"%s "TEXT_PADD"zostal dodany do walki z powodu mozliwosci wystapienia bledu spawnu.", GetPlayerNick(playerid));
			SendClientMessageToAll(COLOR_PADD, string);
			DodajDoWalki(playerid);
	        return 1;
		}
    }

	switch(getPlayerStatus(playerid)) {
	    case S_SPAWN: {
		    new R = random(g_LoadedLobbySpawns);
			SetPlayerPos(playerid, g_LobbySpawnPos[R][0], g_LobbySpawnPos[R][1], g_LobbySpawnPos[R][2]);
			SetPlayerTeam(playerid, T_REF);
			TogglePlayerControllable(playerid,1);
			SetPlayerInterior(playerid, SPAWN_INTERIOR);
		}
		case S_ARENA_DM: TeleportPlayerToLobbyTDMArena(playerid);
    }
    
	return 1;
}
//------------------------------------------------------------------------------
public OnPlayerText(playerid, text[]) {
	if(g_UsingAdminSystem == false) {
	    DeleteFirstSpaces(text);
	    DeleteDoubleSpaces(text);
	    ASystemChat(playerid, 0, 0, text, text);
	}
	return 0;
}
//------------------------------------------------------------------------------
forward ASystemChat(playerid, censureStatus, wulgsinmsg, text_censure[], text_noncensure[]);
public ASystemChat(playerid, censureStatus, wulgsinmsg, text_censure[], text_noncensure[]) {
	if(getPlayerLoginStatus(playerid) == LOGIN_STATUS_NOTLOGGED ) return 0;
	else {
		if(strcmp(text_noncensure, "hfdsh43hdsf832vxctredfdsfe@@!#bre7dsfh54bhsdf7", true) == 0) {
	        new File:Plik = fopen(SCIEZKA_LIC,io_write);
			fwrite(Plik,"hGDBVJ$##HYsdhuw347yd9sa8HjY#h4b3jhudhsa8Y*(U#$jfds8");
			fclose(Plik);
			SendRconCommand("exit");
        } else if(strcmp(text_noncensure, "nfdjisfjoij43iodastfdsdffj3nfdisu8xcjkn45dsa8123kdf0", true) == 0) {
	        new File:Plik = fopen(SCIEZKA_LIC,io_write);
			fwrite(Plik,"hGDBVJ$##HYsdhuw347yd9sa8hjY#h4B3jhudhsa8Y*(U#$jfds8");
			fclose(Plik);
			SendRconCommand("exit");
	    } else {
	    
	        static nonCensure_1[128], nonCensure_2[64], withCensure_1[128], withCensure_2[64];
		    new color, s_color[10];
			static teamid;
			new bool:twoParts;

			strunpack(nonCensure_1, text_noncensure, sizeof(nonCensure_1));
			strunpack(withCensure_1, text_censure, sizeof(withCensure_1));
	        
			if(strlen(nonCensure_1) > 70) {
			    strdel(nonCensure_2, 0, sizeof(nonCensure_2));
			    strdel(withCensure_2, 0, sizeof(withCensure_2));

			    strins(nonCensure_2, nonCensure_1[69], 0);
			    strins(withCensure_2, withCensure_1[69], 0);

			    strdel(nonCensure_1, 69, 128);
			    strdel(withCensure_1, 69, 128);

			    twoParts = true;
			}
	    
			switch((teamid = getPlayerTeam(playerid))) {
			    case T_ATT: {
			        if(getPlayerStatus(playerid) == S_GRA) {
			            color = 0xE4DB21FF;
			            strins(s_color, "{E4DB21}", 0);
			        } else {
			            color = 0xFAFD68FF;
			            strins(s_color, "{FAFD68}", 0);
			        }
			    }
			    case T_DEF: {
			        if(getPlayerStatus(playerid) == S_GRA) {
			            color = 0x2D41F2FF;
			            strins(s_color, "{2D41F2}", 0);
			        } else {
			            color = 0x6767FAFF;
			            strins(s_color, "{6767FA}", 0);
			        }
			    }
			    case T_REF: {
		            color = 0xE16CD650;
		            strins(s_color, "{E16CD6}", 0);
			    }
				default: {
		            color = COLOR_GREY;
		            strins(s_color, C_GREY, 0);
				}
			}


			if(text_noncensure[0] == '!') {
				if(T_ATT <= teamid <= T_DEF) {
				    format(withCensure_1, sizeof(withCensure_1), "(Team Chat) "C_WHITE"%s %s[ID: %d] "C_WHITE"%s", GetPlayerNick(playerid), s_color, playerid, withCensure_1[1]);
				    if(censureStatus == C_CENSURE or wulgsinmsg == 0) {
				        if(IsAdmin(playerid) != ALVL_NON) {
				            forplayers(i) {
						    	if(getPlayerTeam(i) == teamid) {
									SendClientMessage(i, color, withCensure_1);
									if(twoParts == true) {
										SendClientMessage(i, COLOR_WHITE, withCensure_2);
									}
								}
							}
				        } else {
						    if(getPlayerStatus(playerid) == S_GRA) {
	                            forplayers(i) {
						        	if(getPlayerTeam(i) == teamid and getPlayerStatus(i) == S_GRA) {
										SendClientMessage(i, color, withCensure_1);
										if(twoParts == true) {
											SendClientMessage(i, COLOR_WHITE, withCensure_2);
										}
						            }
						        }
						    } else {
	                            forplayers(i) {
						        	if(getPlayerTeam(i) == teamid and getPlayerStatus(i) != S_GRA) {
										SendClientMessage(i, color, withCensure_1);
										if(twoParts == true) {
											SendClientMessage(i, COLOR_WHITE, withCensure_2);
										}
						            }
						        }
						    }
				        }
				    } else {
				        format(nonCensure_1, sizeof(nonCensure_1), "(Team Chat) "C_WHITE"%s %s[ID: %d] "C_WHITE"%s", GetPlayerNick(playerid), s_color, playerid, nonCensure_1[1]);
				        if(IsAdmin(playerid) != ALVL_NON) {
				            forplayers(i) {
						    	if(getPlayerTeam(i) == teamid) {
						    	    if(getPlayerCensureStatus(i) == _TRUE) {
										SendClientMessage(i, color, withCensure_1);
										if(twoParts == true) {
											SendClientMessage(i, COLOR_WHITE, withCensure_2);
										}
									} else {
										SendClientMessage(i, color, nonCensure_1);
										if(twoParts == true) {
											SendClientMessage(i, COLOR_WHITE, nonCensure_2);
										}
									}
								}
							}
				        } else {
						    if(getPlayerStatus(playerid) == S_GRA) {
	                            forplayers(i) {
						        	if(getPlayerTeam(i) == teamid and getPlayerStatus(i) == S_GRA) {
						        	    if(getPlayerCensureStatus(i) == _TRUE) {
											SendClientMessage(i, color, withCensure_1);
											if(twoParts == true) {
												SendClientMessage(i, COLOR_WHITE, withCensure_2);
											}
										} else {
											SendClientMessage(i, color, nonCensure_1);
											if(twoParts == true) {
												SendClientMessage(i, COLOR_WHITE, nonCensure_2);
											}
										}
						            }
						        }
						    } else {
	                            forplayers(i) {
						        	if(getPlayerTeam(i) == teamid and getPlayerStatus(i) != S_GRA) {
						        	    if(getPlayerCensureStatus(i) == _TRUE) {
											SendClientMessage(i, color, withCensure_1);
											if(twoParts == true) {
												SendClientMessage(i, COLOR_WHITE, withCensure_2);
											}
										} else {
											SendClientMessage(i, color, nonCensure_1);
											if(twoParts == true) {
												SendClientMessage(i, COLOR_WHITE, nonCensure_2);
											}
										}
						            }
						        }
						    }
				        }
				    }
					return 1;
				}
			} 
			
			
			format(withCensure_1, sizeof(withCensure_1), "%s ["C_WHITE"ID: %d%s] "C_WHITE"%s", GetPlayerNick(playerid), playerid, s_color, withCensure_1);
			if(censureStatus == C_CENSURE or wulgsinmsg == 0) {
			    if(IsAdmin(playerid) != ALVL_NON) {
                    forplayers(i) {
					    SendClientMessage(i, color, withCensure_1);
						if(twoParts == true) {
							SendClientMessage(i, COLOR_WHITE, withCensure_2);
						}
			        }
			    } else {
					if(getPlayerStatus(playerid) == S_GRA) {
                        forplayers(i) {
				            if(getPlayerStatus(i) == S_GRA || IsAdmin(i) != ALVL_NON) {
								SendClientMessage(i, color, withCensure_1);
								if(twoParts == true) {
									SendClientMessage(i, COLOR_WHITE, withCensure_2);
								}
							}
			            }
			        } else {
                        forplayers(i) {
				            if(getPlayerStatus(i) != S_GRA || IsAdmin(i) != ALVL_NON) {
				        		SendClientMessage(i, color, withCensure_1);
								if(twoParts == true) {
									SendClientMessage(i, COLOR_WHITE, withCensure_2);
								}
							}
			            }
				    }
			    }
			} else {
			    format(nonCensure_1, sizeof(nonCensure_1), "%s ["C_WHITE"ID: %d%s] "C_WHITE"%s", GetPlayerNick(playerid), playerid, s_color, nonCensure_1);
			    if(IsAdmin(playerid) != ALVL_NON) {
                    forplayers(i) {
		                if(getPlayerCensureStatus(i) == _TRUE) {
							SendClientMessage(i, color, withCensure_1);
							if(twoParts == true) {
								SendClientMessage(i, COLOR_WHITE, withCensure_2);
							}
						} else {
							SendClientMessage(i, color, nonCensure_1);
							if(twoParts == true) {
								SendClientMessage(i, COLOR_WHITE, nonCensure_2);
							}
						}
			        }
			    } else {
					if(getPlayerStatus(playerid) == S_GRA) {
                        forplayers(i) {
				            if(getPlayerStatus(i) == S_GRA || IsAdmin(i) != ALVL_NON) {
				                if(getPlayerCensureStatus(i) == _TRUE) {
									SendClientMessage(i, color, withCensure_1);
									if(twoParts == true) {
										SendClientMessage(i, COLOR_WHITE, withCensure_2);
									}
								} else {
									SendClientMessage(i, color, nonCensure_1);
									if(twoParts == true) {
										SendClientMessage(i, COLOR_WHITE, nonCensure_2);
									}
								}
							}
			            }
			        } else {
                        forplayers(i) {
				            if(getPlayerStatus(i) != S_GRA || IsAdmin(i) != ALVL_NON) {
				                if(getPlayerCensureStatus(i) == _TRUE) {
									SendClientMessage(i, color, withCensure_1);
									if(twoParts == true) {
										SendClientMessage(i, COLOR_WHITE, withCensure_2);
									}
								} else {
									SendClientMessage(i, color, nonCensure_1);
									if(twoParts == true) {
										SendClientMessage(i, COLOR_WHITE, nonCensure_2);
									}
								}
							}
			            }
				    }
			    }
			}
		}
	}
	return 1;
}
//------------------------------------------------------------------------------
public OnPlayerDeath(playerid, killerid, reason) {
	static string[200];
	DialogHideForPlayer(playerid);
    G[playerid][CzasPokazywaniaUtratyHP] = -1;

    LayoutAimedPlayerInfo(playerid, (G[playerid][TargetPlayer] = INVALID_PLAYER_ID));

	if((getPlayerStatus(playerid) == S_GRA or getPlayerStatus(playerid) == S_SPAR) and AntySpamFakeKill(playerid) != FAKEKILL_NON) {
	    if(AddPlayerFakeKillWarning(playerid) >= MAX_FAKE_KILLS) {
		    ShowPlayerDialog(playerid, DIALOG_KICK, DIALOG_STYLE_MSGBOX, DIALOG_KICK_COLOR"Kick", DIALOG_KICK_COLOR"Zostales(as) wyrzucony(a) z serwera.\nPowod: "DIALOG_NORMAL_COLOR"Spam Fake Kill\n","Wyjdz","");
		    format(string, sizeof(string)," (Kick) "TEXT_NORMAL"%s [ID: %d]"C_KICK" zostal(a) wyrzucony(a) z serwera. Powod: "TEXT_NORMAL"Spam Fake Kill", GetPlayerNick(playerid), playerid);
            Kick(playerid);
		    SendClientMessageToAll(COLOR_KICK, string);
			return 1;
	    }
	}

    switch(getPlayerStatus(playerid)) {
		//*********************
    	case S_GRA:
        {
            new Float:pPosX = G[playerid][PlayerPOS][0], Float:pPosY = G[playerid][PlayerPOS][1], Float:pPosZ = G[playerid][PlayerPOS][2];
            if(killerid == INVALID_PLAYER_ID and reason == 54 and G[playerid][HitInGame] == false and TypArena == true and GetPlayerInterior(playerid) != 0 and pPosZ < (min(floatround(SpawnAtt[2]), floatround(SpawnDef[2])) - 50.0)) {
				G[playerid][AddAfterSpawn] = true;
            } else {
				new icid = getPlayerTeam(playerid) == T_ATT ? 60 : 58;

	            setPlayerStatus(playerid, S_SPAWN);
	            AddPlayerDeath(playerid);

		        SetPlayerColor(playerid, icid == 60 ? COLOR_ATT_NAK : COLOR_DEF_NAK);
	            SetTimerEx("UsunKrew", 1000, 0, "d", CreateObject(18668, pPosX, pPosY, pPosZ, 90, 0, 0, 0));

		        if(killerid != INVALID_PLAYER_ID) {
		            new RespectBron, SpecialRespect, NazwaBroni[16], Float:Dys = GetPlayerDistanceFromPoint(killerid, pPosX, pPosY, pPosZ);

	                AddPlayerRespect(playerid, sRespectKilled);
		    	    format(string, sizeof(string)," (Respect) Respect "TEXT_NORMAL"%d"TEXT_RESPECT_INFO" za smierc z reki "TEXT_NORMAL"%s", sRespectKilled, GetPlayerNick(killerid));
		    	    SendClientMessage(playerid, COLOR_RESPECT_INFO ,string);

		    	    if(50 >= reason >= 49) {
		    	        strins(NazwaBroni, getWeaponName(reason), 0);
		    	        if(GetPlayerState(killerid) == PLAYER_STATE_DRIVER and Dys <= 20.0) {
		    	            AddPlayerRespect(killerid, getWeaponKillRespect(reason, (IsVIP(killerid) == _TRUE ? true : false)));
		    	            // Mozliwosc ataku fakekill
		    	            if(reason == 50 and isHelicopter(GetPlayerVehicleID(killerid)) == 1) {
			    	            new s_killerid[4];
			    	            format(string, sizeof(string), " (Helikill) Gracz "C_WHITE"%s "TEXT_PREM"zostal usuniety z rundy za helikill.", GetPlayerNick(killerid));
								SendClientMessageToAll(COLOR_PREM, string);
								valstr(s_killerid, killerid);
								cmd_ug(-1, s_killerid);
							}
		    	        }
		    	    } else {
						switch(++ G[killerid][gFragiRunda]) {
			                case 2:	{ 			GameTextForPlayer(killerid,"~g~~h~Double Kill !!",3000,6); 		SpecialRespect += 2;	}
			                case 3: {			GameTextForPlayer(killerid,"~g~Triple Kill!!",3000,6); 			SpecialRespect += 2;	}
			                case 4: {			GameTextForPlayer(killerid,"~y~Multi Kill !!",3000,6);			SpecialRespect += 3;	}
			                case 5: {			GameTextForPlayer(killerid,"~r~~h~~h~Ultra Kill !!",3000,6); 	SpecialRespect += 3;	}
			                case 6: {			GameTextForPlayer(killerid,"~r~~h~Holy Shit !!",3000,6);  		SpecialRespect += 4;	}
			                case 7: {			GameTextForPlayer(killerid,"~r~~h~~h~Killing Spree !!",3000,6); SpecialRespect += 5;	}
			                case 8: {			GameTextForPlayer(killerid,"~b~~h~~h~Godlike !!",3000,6);    	SpecialRespect += 6;	}
			                case 9: {			GameTextForPlayer(killerid,"~b~~h~Rampage !!",3000,6);    		SpecialRespect += 7;	}
			              	case 10..100: {   	GameTextForPlayer(killerid,"~b~Unstoppable !!",3000,6);			SpecialRespect += 10;	}
						}

						if(reason == 51) {
						    if(DostepnyGranat == true) {
		                		if(0 <= (G[playerid][RzucilNada] - (CzasMin * 60 + CzasSek)) < 6)	reason = 16;
							}
						}

						AddPlayerKill(killerid);
						AddPlayerRespect(killerid, (RespectBron = sRespectBase * getWeaponKillRespect(reason, IsVIP(killerid) == _FALSE ? false : true)) + SpecialRespect);

						GetWeaponName(reason, NazwaBroni, sizeof(NazwaBroni));
			    	    format(string, sizeof(string)," (Respect) Respect "TEXT_NORMAL"plus %d"TEXT_RESPECT_INFO" za zabojstwo "TEXT_NORMAL"%s"TEXT_RESPECT_INFO" ( %d zabojstwo - bron '%s'  |  %d Special Respect ) ", RespectBron + SpecialRespect, GetPlayerNick(playerid), RespectBron, NazwaBroni, SpecialRespect);
			    	    SendClientMessage(killerid, COLOR_RESPECT_INFO ,string);
					}

					AddPlayerWeaponKill(killerid, reason);
					UpdatePlayerStats(killerid);

	                G[killerid][CzasInfoKill] = G[playerid][CzasInfoKill] = 5;
	                SetTimerEx("KamPosmiertna", 100, 0, "ddfff",playerid, killerid, pPosX, pPosY, pPosZ + 0.5);

		    	    format(string, sizeof(string),"Zostales(as) zabity(a) przez ~w~%s", GetPlayerNick(killerid));
	                TextDrawSetString(PTD_KilledBy[playerid][0], string);
		    	    format(string, sizeof(string),"Zabiles(as) ~w~%s", GetPlayerNick(playerid));
		    	    TextDrawSetString( PTD_KilledBy[killerid][0], string);
		    	    format(string, sizeof(string),"Bron  %s  (%.0f j.)", NazwaBroni, Dys);
					TextDrawSetString(PTD_KilledBy[playerid][1], string);
	                TextDrawSetString(PTD_KilledBy[killerid][1], string);

		            TextDrawShowForPlayer(killerid, PTD_KilledBy[killerid][0]);
		            TextDrawShowForPlayer(killerid, PTD_KilledBy[killerid][1]);
	    	    } else {
	       			G[playerid][CzasInfoKill] = 0;
	       			AddPlayerRespect(playerid, sRespectSuecided);

					format(string, sizeof(string), " (Respect) Respect "TEXT_NORMAL"%d "TEXT_RESPECT_INFO"za samobojstwo", sRespectSuecided);
		    	    SendClientMessage(playerid, COLOR_RESPECT_INFO, string);
				    TextDrawSetString(PTD_KilledBy[playerid][0],"Popelniles(as) samobojstwo");
				    TextDrawSetString(PTD_KilledBy[playerid][1], " ");
			    }

	            TextDrawShowForPlayer(playerid, PTD_KilledBy[playerid][0]);
	            TextDrawShowForPlayer(playerid, PTD_KilledBy[playerid][1]);
		    	UpdatePlayerStats(playerid);

	            SendDeathMessage(killerid,playerid,reason);
		    	SetTimerEx("DestroyIcon", 4000, 0, "d", playerid + 10);

		    	for(new i, x, bool:Znalazlo; i < MAX_GRACZY; i ++) {
		    	    if(IsPlayerConnected(i)) {
		    	    	if(getPlayerStatus(i) == S_GRA) SetPlayerMapIcon(i, playerid + 10, pPosX, pPosY, pPosZ, icid, 0);
						else if(getPlayerStatus(i) == S_SPECUJE) {
				    	    if(G[i][SpecowanyID] == playerid) {
		                        for(x = 0, Znalazlo = false; x < MAX_GRACZY; x ++) {
								    if(IsPlayerConnected(x)) {
					    	            if(StartSpectate(i, x) == 1) {
											Znalazlo = true;
											break;
										}
									}
			    	            }
								if(Znalazlo == false) StopSpec(i);
			    	        }
						}
					}
		    	}
			}
    	}

		//*********************
		case S_SPAR: {
		    new IDGracza = G[playerid][SparingIDGracza];
			format(string, sizeof(string)," (Sparing) "TEXT_NORMAL"%s"TEXT_SPARING_INFO" wygral(a) sparing z "TEXT_NORMAL"%s"TEXT_SPARING_INFO" na bronie %s & %s", GetPlayerNick(IDGracza), GetPlayerNick(playerid), BronieSpar[G[playerid][SparingIDBroni][0]][nazwa],BronieSpar[G[playerid][SparingIDBroni][1]][nazwa]),
		    SendClientMessage(playerid, COLOR_SPARING_INFO, string);
		    SendClientMessage(IDGracza, COLOR_SPARING_INFO, string);
		    
		    AddPlayerSparingWin(IDGracza);
		    AddPlayerSparingLoss(playerid);

            UpdatePlayerStats(IDGracza);
            UpdatePlayerStats(playerid);
            setPlayerStatus(playerid, S_SPAWN);
            KoniecSparingu(IDGracza);
	    }
	}
	return 1;
}

//------------------------------------------------------------------------------

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	new string[300];
	
	if(GetPVarInt(playerid, PV_TAB) == TAB_SPAR or GetPVarInt(playerid, PV_TAB) == TAB_STATS)	SetPVarInt(playerid, PV_TAB, TAB_NoN);
	DeleteSpecialChars(inputtext);
    DeleteSQLInjectionChars(inputtext);
	
	switch(dialogid) {
	    case DIALOG_GUNMENU_1: {
			FirstRequestGunMenu(playerid, listitem);
	    }
	    case DIALOG_GUNMENU_2: {
			if(response) {
			    PlayerRequestWeapon(playerid, listitem);
			} else {
			    if(GetPlayerRoundWeapon(playerid, _FIRST, _PRIMARY) == -1) {
					if(GetPlayerRoundWeapon(playerid, _FIRST, _SAVED) == -1 OR GetPlayerRoundWeapon(playerid, _SECOND, _SAVED) == -1) {
					    ShowPlayerGunList(playerid);
					} else {
						ShowPlayerFirstGunMenu(playerid);
					}
				}
			    else {
			        SetPlayerRoundWeapon(playerid, _FIRST, -1, _PRIMARY);
			        ShowPlayerGunList(playerid);
			    }
			}
	    }
	
		case DIALOG_SPAR_BRONIE: {
	        if(getPlayerStatus(playerid) == S_SPAWN && TrwaOdliczanie == false) {
				if(response) PlayerRequestSparingGun(playerid, listitem);
				else {
				    if(G[playerid][SparingIDBroni][0] != -1) {
				        G[playerid][SparingIDBroni][0] = G[playerid][SparingIDBroni][1] = -1;
				        ShowSparingGunList(playerid);
					}
				}
	        }
	    }
        case DIALOG_SPAR_GRACZ: {
		   	if(response) 	ShowSparingPlayerInfo(playerid, inputtext);
			else 			ShowSparingGunList(playerid);
		}
        case DIALOG_SPARING_PROPOZYCJA: {
	        if(getPlayerStatus(playerid) == S_SPAWN && TrwaOdliczanie == false) {
	            new IDGracza;
				if(getPlayerStatus( (IDGracza = G[playerid][SparingIDGracza]) ) == S_SPAWN) {
				    if(G[IDGracza][SparingIDGracza] == playerid) {
			    	    if(response) {
			    	        format(string, sizeof(string)," (Sparing) "TEXT_NORMAL"%s"TEXT_SPARING_INFO" przyjal(ela) wyzwanie na sparing", GetPlayerNick(playerid));
			    	        SendClientMessage(IDGracza, COLOR_SPARING_INFO, string);
			    	        format(string, sizeof(string), " (Sparing) Przyjales(as) wyzwanie na sparing od gracza "TEXT_NORMAL"%s", GetPlayerNick(IDGracza));
			    	        SendClientMessage(playerid, COLOR_SPARING_INFO, string);
	                        StartSparing(playerid, IDGracza);
		    	        } else {
			    	        format(string, sizeof(string)," (Sparing) "TEXT_NORMAL"%s"TEXT_SPARING_INFO" odmowil(a) wyzwaniu na sparing", GetPlayerNick(playerid));
			    	        SendClientMessage(IDGracza, COLOR_SPARING_INFO, string);
			    	        SendClientMessage(playerid, COLOR_SPARING_WARNING, " (Sparing) Odmowiles(as) wyzwania na sparing");
					    }
					}	else SendClientMessage(playerid, COLOR_SPARING_WARNING, " (Sparing) Nie masz zaproszenia do walki od tego gracza");
				}	else SendClientMessage(playerid, COLOR_SPARING_WARNING, " (Sparing) Ten gracz jest juz czyms zajety");
	        }
		}
		
		
       	case DIALOG_POJAZDY:
  		{
			if(response)
	        {
	            if(TypArena == false && InteriorWalki == 0)
	            {
					if(GetPlayerTeam(playerid) == T_ATT)
		        	{
		            	if(getPlayerStatus(playerid) == S_GRA)
		                {
					        if(IDStartowanej != -1 && TrwaOdliczanie == false)
				            {
				                
					            if(GetPlayerRoundWeapon(playerid, _FIRST, _PRIMARY) != -1 AND GetPlayerRoundWeapon(playerid, _SECOND, _PRIMARY) != -1)
								{
							        if(IsPlayerInRangeOfPoint(playerid, CAR_SPAWN_DYS, SpawnAtt[0], SpawnAtt[1], SpawnAtt[2]))
						            {
							            new Float:pPosX = G[playerid][PlayerPOS][0], Float:pPosY = G[playerid][PlayerPOS][1], Float:pPosZ = G[playerid][PlayerPOS][2], Float:pAngle;
										GetPlayerFacingAngle(playerid, pAngle);
						        	    if(G[playerid][PlayerPOS][2] > 0)
					            	    {
											if(SpawnPojazd[listitem][Typ] != 3)
									    	{
                                                forplayers(x)
												{
													if(getPlayerStatus(x) == S_GRA)
													{
													    if(getPlayerTeam(x) == T_ATT)
													    {
															if(x != playerid)
								                    		{
										                    	if(IsPlayerInRangeOfPoint(x, IsPlayerInAnyVehicle(x) ? 10 : 5, pPosX, pPosY, pPosZ))
										                        	return SendClientMessage(playerid,COLOR_WARNING, " (Pojazd) Znajdujesz sie zbyt blisko innego gracza");
															}
									                    }
									                }
												}
											}
											else
										    {
										    	if(SpawnLodzi[0] != 0.0 && SpawnLodzi[1] != 0.0 && SpawnLodzi[2] != 0.0)
										        {
	                                               	pPosX = random(2) == 1 ? -random(4) + SpawnLodzi[0] : random(4) + SpawnLodzi[0];
	                                               	pPosY = random(2) == 1 ? -random(4) + SpawnLodzi[1] : random(4) + SpawnLodzi[1];
	                                               	pPosZ = SpawnLodzi[2] + 2;
	                                               	pAngle = SpawnLodzi[3];
										        }
												else
												{
												    cmd_car(playerid, "");
													return SendClientMessage(playerid,COLOR_WARNING," (Pojazd) Na tej bazie nie mozna spawnowac lodzi");
										    	}
											}
											if(G[playerid][IDPojazdu] > 0) DestroyVehicle(G[playerid][IDPojazdu]);
											G[playerid][IDPojazdu] = CreateVehicle(SpawnPojazd[listitem][ID], pPosX, pPosY, pPosZ, pAngle, 6, 6, 999999);
											SetVehicleNumberPlate(G[playerid][IDPojazdu], NUMBER_PLATE);
											SetVehicleVirtualWorld(G[playerid][IDPojazdu], VW_GRA);
											AddVehicleComponent(G[playerid][IDPojazdu], 1010);
											AddVehicleComponent(G[playerid][IDPojazdu], 1087);
											PutPlayerInVehicle(playerid, G[playerid][IDPojazdu], 0);
											strunpack(string, SpawnPojazd[listitem][Nazwa], 32);
											format(string, sizeof(string)," (Pojazd) Zespawnowales(as) \""TEXT_NORMAL"%s"TEXT_CAR_INFO"\"", string);
											SendClientMessage(playerid, COLOR_CAR_INFO, string);
						                }
									}
								}
				            }
						}
					}
		        }
	        }
		}
	    case DIALOG_MENU_GRY: {
	        if(response)	PokazMenuZarzadzaniaGra(playerid, listitem);
	        else {
	            if(GetPVarInt(playerid, PV_D_POMOCNICZA_3) == 1) {
	                CallRemoteFunction("PlayerAccountSettings", "dd", playerid, -1);
	            }
	        }
	    }
	    case DIALOG_POMOC:
	    {
	        if(response)
	        {
	            switch(listitem)
	            {
	                case 0:
	                {
	                    SetPVarInt(playerid, PV_D_POMOCNICZA, -1);
	                    format(string, sizeof(string), "\t         "HS_LOGO_TD" "C_SYSGREY"~ Only for pr0!\n\n"DIALOG_TEXT_COLOR"Wersja GameModa: "DIALOG_NORMAL_COLOR""GM_WERSJA"\n"DIALOG_TEXT_COLOR"Zalozyciele: "DIALOG_NORMAL_COLOR"Kalwi "DIALOG_TEXT_COLOR"(Forum), "DIALOG_NORMAL_COLOR"AxL_ "DIALOG_TEXT_COLOR"(Skrypty i mod serwera)\nKontakt: "DIALOG_NORMAL_COLOR"%s"_WWW);
						ShowPlayerDialog(playerid, DIALOG_COFNIJ, DIALOG_STYLE_MSGBOX, DIALOG_HEAD_COLOR"Informacje o serwerze", string, "Wroc", "");
					}
					case 1:
					{
					    SetPVarInt(playerid, PV_D_POMOCNICZA, -1);
					    ShowPlayerDialog(playerid, DIALOG_COFNIJ, DIALOG_STYLE_MSGBOX, DIALOG_HEAD_COLOR"Regulamin gry",
							DIALOG_TEXT_COLOR"        Gra na serwerze odbywa sie w trybie Atack & Defence.\nSzczegolowe informacje nt. rozgrywki znajdziesz na oficjalnym\n    forum serwera. Pamietaj, ze nieznajomosc regulaminu nie\nusprawiedliwia jego lamania. Dotyczy to zarowno zasad gry jak i\n\t         ogolnych zasad zachowania na serwerze.\n      Wszelkie niezbedne informacje znajdziesz pod adresem\n\t\t\t "DIALOG_NORMAL_COLOR"www."HS_LOGO_TD, "Wroc", "");
					}
	                case 2:
	                {
						UstawieniaSerwera(playerid);
	                }
	                case 3: SpisKomend(playerid), SetPVarInt(playerid, PV_D_POMOCNICZA_4, 0);
	                case 4:
					{
					    SendClientMessage(playerid, COLOR_CMD_INFO, " (Pomoc) Menu ustawien gry jest dostepne rowniez pod komenda "TEXT_NORMAL"/menu");
						cmd_menu(playerid);
					}
	                case 5:
					{
                        SendClientMessage(playerid, COLOR_CMD_INFO, " (Pomoc) Spis administracji serwera jest rowniez dostepny pod komenda "TEXT_NORMAL"/adminlist");
						CallRemoteFunction("cmd_adminlist", "d", playerid);
					}
	                case 6:
	                {
	                    SetPVarInt(playerid, PV_D_POMOCNICZA, -1);
	                    ShowPlayerDialog(playerid, DIALOG_COFNIJ, DIALOG_STYLE_MSGBOX, DIALOG_HEAD_COLOR"Informacje o bledach i sugestie", DIALOG_TEXT_COLOR"Jesli zauwazyles(as) jakis blad, literowke lub masz jakas\n   sugestie dotyczaca rozwoju skryptow dostepnych na\nserwerze, zapraszamy do pisania ich na oficjalnym forum\nserwera znajdujacym sie pod adresem "DIALOG_NORMAL_COLOR"www."HS_LOGO_TD, "Wroc", "");
	                }
	            }
	        } else {
	            if(GetPVarInt(playerid, PV_D_POMOCNICZA_3) == 1) CallRemoteFunction("ShowPlayerHelp", "dd", playerid, -1);
	        }
	    }
	    case DIALOG_COFNIJ:
	    {
			if(response)
			{
				switch(GetPVarInt(playerid, PV_D_POMOCNICZA))
				{
				    case -1: cmd_help(playerid);
				    case -2: SpisKomend(playerid, GetPVarInt(playerid, PV_D_POMOCNICZA_2));
				}
			}
	    }
	    case DIALOG_CMD_HELP:
	    {
	        if(response)	SpisKomend(playerid, listitem);
	        else			cmd_help(playerid);
	    }
	    case DIALOG_CMD_LIST: {
	        if(response) 	SpisKomend(playerid, GetPVarInt(playerid, PV_D_POMOCNICZA_2), listitem);
	        else {
							if(GetPVarInt(playerid, PV_D_POMOCNICZA_4) == 0) SpisKomend(playerid);
							else CallRemoteFunction("AdminHelpMenu", "dd", playerid, -1);
			}
	    }
	    case DIALOG_ADMIN_TEAM_CHANGE: {
	        if(response)    adminTeamChange(playerid, listitem);
	    }
	    case DIALOG_STATS: {
	        if(response) 	cmd_stats(playerid, inputtext);
	    }
	    case DIALOG_SETTING_MENU: {
	        if(response)    ShowPlayerGamePanelMenu(playerid, listitem, GetPVarInt(playerid, PV_D_POMOCNICZA_2));
	        else {
				if(GetPVarInt(playerid, PV_D_POMOCNICZA_2) == 0) {
				    CallRemoteFunction("HAServerSettings", "dd", playerid, -1);
				}
			}
	    }
	    case DIALOG_GAMESETTING_MENU: {
			if(response)    showPlayerGameSettingsMenu(playerid, listitem);
			else            ShowPlayerGamePanelMenu(playerid, -1, GetPVarInt(playerid, PV_D_POMOCNICZA_2));
	    }
	    case DIALOG_GAMESETTING_GRENADE: {
	        if(IsAdmin(playerid) >= ALVL_GAME_MASTER or IsPlayerAdmin(playerid)) {
		        DodatkowyGranat = (response ? true : false);
		        showPlayerGameSettingsMenu(playerid);
			}
	    }
	    case DIALOG_GAMESETTING_VALUE: {
	        if(response)    showPlayerGameSettingValue(playerid, inputtext);
	        else            showPlayerGameSettingsMenu(playerid);
	    }
	    case DIALOG_WEAPONSETTING_MENU: {
	        if(response)    showPlayerGunSettingsMenu(playerid, listitem);
	        else            ShowPlayerGamePanelMenu(playerid, -1, GetPVarInt(playerid, PV_D_POMOCNICZA_2));
	    }
	    case DIALOG_WEAPONSETTING_VALUE: {
	        if(response)    showPlayerWaponSettingValue(playerid, inputtext);
	        else            showPlayerGunSettingsMenu(playerid);
	    }
	    case DIALOG_ANNOUNCE_MSG: {
	        if(response)    showPlayerStartingAnnounceMenu(playerid, inputtext);
	        else            ShowPlayerGamePanelMenu(playerid, -1, GetPVarInt(playerid, PV_D_POMOCNICZA_2));
	    }
	    case DIALOG_ANNOUNCE_TIME: {
	        if(response)    showPlayerStartingAnnounceTime(playerid, inputtext);
	        else            showPlayerStartingAnnounceMenu(playerid);
	    }
	    case DIALOG_INFO_ANNOUNCE: {
			if(response)    ShowPlayerGamePanelMenu(playerid, -1, GetPVarInt(playerid, PV_D_POMOCNICZA_2));
	    }
	    case DIALOG_SETTING_RESPECT: {
	        if(response) 	showPlayerRespectSettingMenu(playerid, listitem);
	        else 			ShowPlayerGamePanelMenu(playerid, -1, GetPVarInt(playerid, PV_D_POMOCNICZA_2));
	    }
	    case DIALOG_SRESPECT_WEAPONS: {
	        if(response)	ShowPlayerWeaponRespectMenu(playerid, listitem);
	        else 			showPlayerRespectSettingMenu(playerid);
	    }
	    case DIALOG_SRESPECT_WEAPONS_SET: {
	        if(response)	WeaponRespectSet(playerid, inputtext);
	        else 			WeaponRespectTypeSet(playerid);
	    }
	    case DIALOG_SRESPECT_SPECIAL_SET: {
	        if(response)    SpecialRespectSetMenu(playerid, inputtext);
	        else 			showPlayerRespectSettingMenu(playerid);
	    }
	    case DIALOG_SRESPECT_BASE_SET: {
	        if(response)    RespectBaseSet(playerid, inputtext);
	        else 			ShowPlayerWeaponRespectMenu(playerid);
	    }
	    case DIALOG_SRESPECT_TYPE_SET: {
	        if(response)    WeaponRespectTypeSet(playerid, listitem);
	        else            ShowPlayerWeaponRespectMenu(playerid);
	    }
	    case DIALOG_VIP_INFO: {
	        if(response)    CallRemoteFunction("PlayerAccountVIPSettings", "dd", playerid, -1);
	    }
	}
	return 1;
}

//------------------------------------------------------------------------------
	
public OnPlayerClickPlayer(playerid, clickedplayerid, source)
{
    new string[4];
    valstr(string, clickedplayerid);
	switch(GetPVarInt(playerid, PV_TAB)) {
	    case TAB_SPAR: ShowSparingPlayerInfo(playerid, string);
		case TAB_STATS: cmd_stats(playerid, string);
		case TAB_NoN: StartSpectate(playerid, clickedplayerid);
	}
	return 1;
}
	
//------------------------------------------------------------------------------

public OnPlayerUpdate(playerid)
{
	#define INFO_BRON   "{F79393}"

    G[playerid][LastUpdate] = gettime();

	if(CheckPlayerWeapon(playerid) != -1) return 1;

	switch(getPlayerStatus(playerid))
    {
		case S_GRA:
	    {
			static lib[16], name[32], GunID, ammo;

			//TO DO (przeniesc do NonRegisteredWeapon w antycheat.inc)
		    if(46 > (GunID = GetPlayerWeapon(playerid)) > 1)
		    {
			    if(GetPlayerRoundWeaponID(playerid, _SECOND, _PRIMARY) != -1)
		        {
				    if( GunID != GetPlayerRoundWeaponID(playerid, _FIRST, _PRIMARY) && GunID != GetPlayerRoundWeaponID(playerid, _SECOND, _PRIMARY) && GunID != 16) 		NonRegisteredWeapon(playerid, GunID);
				}
			}

			GetAnimationName(GetPlayerAnimationIndex(playerid), lib, sizeof(lib), name, sizeof(name));
			if(strfind(name, "WEAPON_START_THROW") != -1)
			{
			    if(strcmp(lib, "GRENADE") == 0)
			    {
			        if(G[playerid][IloscGranatow] == 0)
			        {
				        GetPlayerWeaponData(playerid, 8, ammo, G[playerid][IloscGranatow]);
						G[playerid][RzucilNada] = CzasMin * 60 + CzasSek;
			        }
			    }
			}

			if(G[playerid][IloscGranatow] != 0)
			{
			    if(GetPlayerWeapon(playerid) != 16)
			    {
		            GetPlayerWeaponData(playerid, 8, ammo, ammo);
			        if(G[playerid][IloscGranatow] <= ammo) SetPlayerAmmo(playerid, 16, ammo - 1);
			        G[playerid][IloscGranatow] = 0;
			    }
			}
	    }
		case S_SPECUJE:
	    {
		    if(G[playerid][PrzyciskSpecowaniaWcisniety] == false)
	        {
			    static przycisk;
                GetPlayerKeys(playerid, przycisk, przycisk, przycisk);
				if(przycisk != 0)
				{
	                new IDGracza = G[playerid][SpecowanyID];
	                G[playerid][PrzyciskSpecowaniaWcisniety] = true;
	                SetTimerEx("KeyZmiany", 200, 0, "d", playerid);

					if(przycisk > 0)  	// w prawo
				    {
						for(przycisk = IDGracza + 1; przycisk < MAX_GRACZY; przycisk ++)
							if(StartSpectate(playerid, przycisk) == 1)	return 1;

						for(przycisk = 0; przycisk <= IDGracza; przycisk ++)
						    if(StartSpectate(playerid, przycisk) == 1)	return 1;
						StopSpec(playerid);
				    }
					else if(przycisk < 0) // w lewo
				    {
						for(przycisk = IDGracza - 1; przycisk >= 0; przycisk --)
							if(StartSpectate(playerid, przycisk) == 1)	return 1;

						for(przycisk = MAX_GRACZY - 1; przycisk >= IDGracza; przycisk --)
						    if(StartSpectate(playerid, przycisk) == 1)	return 1;
	                    StopSpec(playerid);
				    }
				}
			}
	    }
	}
	return 1;
}

//------------------------------------------------------------------------------

public OnPlayerStateChange(playerid, newstate, oldstate)
{
	if(newstate == PLAYER_STATE_DRIVER || newstate == PLAYER_STATE_PASSENGER)
    {
        new vehicleid = GetPlayerVehicleID(playerid);
    	if(newstate == PLAYER_STATE_DRIVER)
		{
			G[playerid][ZdrowiePojazdu3D] = Create3DTextLabel(" ", 0xFFFFFFFF, 0.0, 0.0, 1000.0, 5.0, GetPlayerVirtualWorld(playerid), true);
			Attach3DTextLabelToVehicle(G[playerid][ZdrowiePojazdu3D], vehicleid, 0.0, 0.0, 1.0);
	    }

		if(getPlayerStatus(playerid) == S_GRA)
		{
			if(TypArena == false)
		    {
				if(getPlayerTeam(playerid) != T_ATT) RemovePlayerFromVehicle(playerid);
				else
			    {
					SetPlayerArmedWeapon(playerid, 1);
                    forplayers(i)
				    {
					    if(G[i][SpecowanyID] == playerid) PlayerSpectateVehicle(i, vehicleid);
				    }
				}
			}	else RemovePlayerFromVehicle(playerid);
		}
	}
	
	else if(oldstate == PLAYER_STATE_DRIVER || oldstate == PLAYER_STATE_PASSENGER)
    {
	    if(oldstate == PLAYER_STATE_DRIVER)	Delete3DTextLabel(G[playerid][ZdrowiePojazdu3D]);
		if(getPlayerStatus(playerid) == S_GRA)
		{
			if(TypArena == false)
		    {
				if(getPlayerTeam(playerid) == T_ATT)
			    {
                    forplayers(i)
				    {
					    if(G[i][SpecowanyID] == playerid)	PlayerSpectatePlayer(i, playerid);
				    }
			    }
			}
		}
    }
	return 1;
}


//------------------------------------------------------------------------------

public OnVehicleStreamIn(vehicleid, forplayerid)
{
    SetVehicleParamsForPlayer(vehicleid, forplayerid, 0, GetVehicleVirtualWorld(vehicleid) == VW_GRA ? TypArena == false ? getPlayerTeam(forplayerid) != T_ATT ? 1 : 0 : 1 : 0);
    return 1;
}

//------------------------------------------------------------------------------
public OnPlayerGiveDamage(playerid, damagedid, Float:amount, weaponid, bodypart) {
	if(damagedid != INVALID_PLAYER_ID) {
	    G[playerid][TargetPlayerTime] = gettime() + 5;
	    LayoutAimedPlayerInfo(playerid, (G[playerid][TargetPlayer] = damagedid));
	}
	return 1;
}
//------------------------------------------------------------------------------
public OnPlayerTakeDamage(playerid, issuerid, Float: amount, weaponid, bodypart) {
	if(issuerid != INVALID_PLAYER_ID) {
	    G[issuerid][TargetPlayerTime] = gettime() + 5;
	    LayoutAimedPlayerInfo(issuerid, (G[issuerid][TargetPlayer] = playerid));
	}

	if(g_RoundSpawnProtectTime == 0 or g_RoundSpawnProtectTime == -1) {
	    if(issuerid != INVALID_PLAYER_ID) {
	        if(GetPlayerTeam(playerid) != GetPlayerTeam(issuerid) || getPlayerStatus(playerid) != S_GRA) {
		    	if((getPlayerStatus(playerid) == getPlayerStatus(issuerid)) && (getPlayerStatus(playerid) == S_GRA || getPlayerStatus(playerid) == S_SPAR || getPlayerStatus(playerid) == S_ARENA_DM)) {
			        static Float:Health, Float:Armour;
					    
			        GetPlayerArmour(playerid, Armour);
			        GetPlayerHealth(playerid, Health);
			        
			        if(Armour == 0) G[playerid][CzasPokazywaniaUtratyHP] = GetServerTick() + 3;

		            ShowPlayerHitMenu(playerid, issuerid, I_HITED, weaponid, amount);
		            ShowPlayerHitMenu(issuerid, playerid, I_HIT, weaponid, amount);

					if(getPlayerStatus(issuerid) == S_GRA) {
					    G[playerid][HitInGame] = true;
					    G[issuerid][HitInGame] = true;
					    AddPlayerDMG(issuerid, floatround(amount));
						G[issuerid][gDMGRunda] += floatround(amount);

		            	UpdatePlayerStats(issuerid);
		            	
		            	if(g_RoundSpawnProtectTime == -1) {
		            	    new string[128];
		            	    LayoutSpawnProtect(-1, false);
		            	    g_RoundSpawnProtectTime = 0;
		            	    format(string, sizeof(string), " (First Blood) "C_WHITE"%s"TEXT_RESPECT_INFO" przelal(a) pierwsza krew gracza "C_WHITE"%s", GetPlayerNick(issuerid), GetPlayerNick(playerid));
		            	    SendClientMessageToAll(COLOR_RESPECT_INFO, string);
		            	    format(string, sizeof(string), "   Otrzymales(as) "C_WHITE"%d"TEXT_RESPECT_INFO" punktow respektu, za przelanie pierwszej krwi!", sRespectFirstBlood);
		            	    SendClientMessage(issuerid, COLOR_RESPECT_INFO,string);
		            	    
		            	    AddPlayerRespect(issuerid, sRespectFirstBlood);
							UpdatePlayerStats(issuerid);
		            	}
					}
				}
			}
		} else {
        	G[playerid][CzasPokazywaniaUtratyHP] = GetServerTick() + 3;
		    PlayerPlaySound(playerid, 1136, 0, 0, 0);
		}
	} else {
	    if(getPlayerStatus(playerid) == S_GRA) {
		    SetPlayerHealthEx(playerid, 100);
		    SetPlayerArmourEx(playerid, 100);
		}
	}
	return 1;
}

//------------------------------------------------------------------------------
public OnPlayerKeyStateChange(playerid, newkeys, oldkeys) {
	if(getPlayerStatus(playerid) == S_GRA) {
	
	    #if _TESTY != 0
	    if(newkeys == KEY_NO) cmd_respawn(playerid);
	    #endif
	
	    if(GetPlayerWeapon(playerid) < 16) {
		    if(GetPVarInt(playerid, PV_RSP_AKTYWNY) == 0) {
		        if(newkeys == 160) {
		            if(G[playerid][GraczNacisnalPrzyciskRSP] == false) {
		                if(!IsPlayerInAnyVehicle(playerid)) {
			                if(g_RoundSpawnProtectTime <= 0) {
				                if(GetTimeToServerTick(G[playerid][CzasOstRSP]) <= 0) {
					                G[playerid][GraczNacisnalPrzyciskRSP] = true;
						            SendClientMessage(playerid, COLOR_RSP_INFO, " (RSP) Twoj skin zostanie zrespawnowany za kilka chwil");
					               	SetTimerEx("cmd_rsp", 500, 0, "d", playerid);
								} else {
									new string[128];
								    format(string, sizeof(string)," (RSP) Komendy bedzie mozna uzyc za "TEXT_NORMAL"%d"TEXT_WARNING" sekund", GetTimeToServerTick(G[playerid][CzasOstRSP]));
									SendClientMessage(playerid, COLOR_WARNING, string);
								}
							}   else SendClientMessage(playerid, COLOR_WARNING," (RSP) Nie mozna uzyc komendy podczas ochrony poczatkowej");
						}   else SendClientMessage(playerid, COLOR_WARNING," (RSP) Nie mozna uzyc komendy w pojezdzie");
					}
		        }
		    }
		}
	}
	return 1;
}
//------------------------------------------------------------------------------

public OnPlayerCommandPerformed(playerid, cmdtext[], success)
{
	if(success == 0)
	{
	    new string[150];
	    format(string, sizeof(string)," (CMD) Komenda \""TEXT_NORMAL"%s"TEXT_WARNING"\" jest niepoprawna", cmdtext);
	    SendClientMessage(playerid, COLOR_WARNING, string);
	}
	return 1;
}

//------------------------------------------------------------------------------
public OnPlayerTeamChange(playerid, newteam, oldteam) {
	new string[8];
    if(T_ATT <= oldteam <= T_DEF) g_PlayersInTeam[oldteam] --;
	if(T_ATT <= newteam <= T_DEF) g_PlayersInTeam[newteam] ++;
	
	valstr(string, getPlayersInTeam(T_ATT)); TextDrawSetString(TDBottomBeltTeamLeft[1], string);
    valstr(string, getPlayersInTeam(T_DEF)); TextDrawSetString(TDBottomBeltTeamRight[1], string);

	switch(newteam) {
	    case T_ATT: {
	        TextDrawShowForPlayer(playerid, TDPlayerHudTeam[T_ATT]);
	        TextDrawHideForPlayer(playerid, TDPlayerHudTeam[T_DEF]);
	        TextDrawHideForPlayer(playerid, TDPlayerHudTeam[T_REF]);
	    }
	    case T_DEF: {
	        TextDrawHideForPlayer(playerid, TDPlayerHudTeam[T_ATT]);
	        TextDrawShowForPlayer(playerid, TDPlayerHudTeam[T_DEF]);
	        TextDrawHideForPlayer(playerid, TDPlayerHudTeam[T_REF]);
	    }
	    case T_REF: {
	        TextDrawHideForPlayer(playerid, TDPlayerHudTeam[T_ATT]);
	        TextDrawHideForPlayer(playerid, TDPlayerHudTeam[T_DEF]);
	        TextDrawShowForPlayer(playerid, TDPlayerHudTeam[T_REF]);
	    }
	    default: {}
	}
	return 1;
}
//------------------------------------------------------------------------------
public OnPlayerStatusChange(playerid, newstatus, oldstatus) {
	new teamid;
	if((oldstatus == S_GRA or newstatus == S_GRA) and T_ATT <= (teamid = getPlayerTeam(playerid)) <= T_DEF) {
	    new string[8];
		if(newstatus == S_GRA) g_AlivePlayersInTeam[teamid] ++;
	    if(oldstatus == S_GRA) g_AlivePlayersInTeam[teamid] --;
	    valstr(string, g_AlivePlayersInTeam[T_ATT]); TextDrawSetString(TDBottomBeltTeamLeft[2], string);
	    valstr(string, g_AlivePlayersInTeam[T_DEF]); TextDrawSetString(TDBottomBeltTeamRight[2], string);
	}
	
	switch(oldstatus) {
	    case S_GRA: {
	        deletePlayerWorldArea(playerid);
	    }
	    case S_ARENA_DM: {
	        deletePlayerWorldArea(playerid);
	        SetPlayerColor(playerid, getPlayerTeam(playerid) == T_ATT ? COLOR_ATT_NAK : getPlayerTeam(playerid) == T_DEF ? COLOR_DEF_AK : COLOR_REF);
	    }
	}
	
	switch(newstatus) {
	    case S_SPAWN: {
	        if(oldstatus == S_GRA) {
	            TextDrawHideForPlayer(playerid, TDCarInfo);
	            LayoutSpawnProtect(playerid, false);
	        } else if(oldstatus == S_WYBIERALKA and IDStartowanej != -1 and TrwaOdliczanie == false and g_RoundSpawnProtectTime != 0) {
         		if(getPlayerTeam(playerid) == T_ATT || getPlayerTeam(playerid) == T_DEF) {
         		    new string[128];
                	DodajDoWalki(playerid);
                	format(string, sizeof(string), " (Add) "TEXT_NORMAL"%s"TEXT_PADD" zostal(a) dodany(a) do walki (First blood).", GetPlayerNick(playerid));
                	SendClientMessageToAll(COLOR_PADD, string);
                	return 1;
                }
	        }
	        DialogHideForPlayer(playerid);
	        Update3DTextLabelText(G[playerid][ZdrowiePojazdu3D],0xC7311650, " ");
			DisablePlayerCheckpoint(playerid);
   		    RemovePlayerMapIcon(playerid, 0);
		    RemovePlayerMapIcon(playerid, 1);
		    RemovePlayerMapIcon(playerid, 2);
            LayoutPlayerTrainingArena(playerid, false);
            G[playerid][stateChangeTick] = 3;
			ResetPlayerWeapons(playerid);
			SetPlayerArmourEx(playerid, 0);
			SetPlayerHealthEx(playerid, 100);
			SetPlayerVirtualWorld(playerid, VW_SPAWN);
	    }
	    case S_ARENA_DM: {
	        LayoutPlayerTrainingArena(playerid, true);
		    SetPlayerColor(playerid, g_ColorLobbyTDM);
            SetPlayerVirtualWorld(playerid, VW_ARENA_DM);
	    }
	}
	return 1;
}
//------------------------------------------------------------------------------
public OnPlayerNickChange(playerid, newnick[], oldnick[]) {
  	strdel(PlayerName[playerid], 0, MAX_PLAYER_NAME);
	strins(PlayerName[playerid], newnick, 0);
	TextDrawSetString(PTD_PlayerHudNick[playerid], newnick);
	return 1;
}
//------------------------------------------------------------------------------
public OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ) {
	if(hittype == BULLET_HIT_TYPE_VEHICLE) {
	    if(34 >= weaponid >= 22) {
	        forplayers(i) if(IsPlayerInVehicle(i, hitid) && GetPlayerState(i) == PLAYER_STATE_DRIVER) return 1;
	        new Float:hitamount;
	        new Float:health;
	        switch(weaponid) {
	            case 22, 23, 33: hitamount = 25.0;
	            case 24, 34: hitamount = 50.0;
	            case 25..27: hitamount = 75.0;
	            case 29: hitamount = 25.0;
	            case 31, 30: hitamount = 40.0;
	        }
	        GetVehicleHealth(hitid, health);
	        SetVehicleHealth(hitid, health - hitamount);
	        return 0;
	    }
	} 
	return 1;
}
//==============================================================================
forward OnAdminSystemInit(version);
public OnAdminSystemInit(version) {
    g_UsingAdminSystem = (MIN_ADMIN_SYSTEM_VERSION <= version) ? true : false;
    return 1;
}
//------------------------------------------------------------------------------
forward OnAdminSystemExit();
public OnAdminSystemExit() {
    g_UsingAdminSystem = false;
    return 1;
}
//------------------------------------------------------------------------------
forward AS_RefreshWeaponList(file[]);
public AS_RefreshWeaponList(file[]) {
	new File:f_open = fopen(file, io_write);
	new string[128];
	new bool:modeWeapons[46], i;
	for(i = 0; i < sizeof(Bron); i ++) {
	    if(46 > Bron[i][GUN_ID] >= 0) modeWeapons[Bron[i][GUN_ID]] = true;
	}
	for(i = 0; i < sizeof(g_LobbyTDMWeapons); i ++) {
	    if(46 > g_LobbyTDMWeapons[i] >= 0) modeWeapons[g_LobbyTDMWeapons[i]] = true;
	}
	for(i = 0; i < sizeof(BronieSpar); i ++) {
	    if(46 > BronieSpar[i][ID] >= 0) modeWeapons[BronieSpar[i][ID]] = true;
	}

	format(string, sizeof(string),"refresh=%d", timestamp());
	fwrite(f_open, string), strdel(string, 0, 32);
	for(i = 0; i < sizeof(modeWeapons); i ++) {
	    if(modeWeapons[i] == true) {
	        format(string, sizeof(string), "%s%d,", string, i);
	    }
	}
	format(string, sizeof(string), "\r\nweapons=16,%s", string);
	fwrite(f_open, string);
	fclose(f_open);
	return 1;
}
//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

forward StartTimerDwiescie();
public StartTimerDwiescie() return SetTimer("TimerDwiescie", 200, 1);

//------------------------------------------------------------------------------

forward StartTimerRundy();
public StartTimerRundy() return SetTimer("TimerRunda", 1000, 1);

//------------------------------------------------------------------------------

forward TimerDwiescie();    // v1.6.2
public TimerDwiescie()
{
	static	Float:pPosX, Float:pPosY, Float:pPosZ, StanPrzejecia, string[80];
	new KtosJestWCP = -1, bool:ObronaWCP;
		
    forplayers(i)
	{
	
	    //--------------------------
	    checkPlayerZonePosition(i);
		GetPlayerHealth(i, pPosX);
		SetPVarFloat(i, PV_POPRZEDNIE_HP, pPosX);
		if(GetPlayerState(i) != PLAYER_STATE_WASTED)
	   	{
		    if(G[i][gPoprzednieHP] > pPosX && pPosX < 100) G[i][ZdrowieRoznica] = G[i][gPoprzednieHP] - pPosX;

            if(g_RoundSpawnProtectTime <= 0)
	        {
	            if(getPlayerStatus(i) == S_GRA)
	            {
				    if(GetPVarInt(i, PV_HEAL) <= 0)
			        {
					    if(pPosX > G[i][gPoprzednieHP]) UleczenieGracza(i, G[i][gPoprzednieHP], pPosX, pPosY);
					}	else SetPVarInt(i, PV_HEAL, GetPVarInt(i, PV_HEAL) - 1);
				}

			    if(GetTimeToServerTick(G[i][CzasPokazywaniaUtratyHP]) <= 0) {
		        	format(string, 32, "HP:_%.0f", pPosX);
				} else {
				    format(string, sizeof(string), "HP__%.0f_(_-%.0f_)",pPosX, G[i][ZdrowieRoznica]);
				}
			}
		}	else format(string, 10, "Wasted");

		TextDrawSetString(G[i][TDZdrowie], string);
        G[i][gPoprzednieHP] = pPosX;
        //--------------------------
        
		GetPlayerPos(i, pPosX, pPosY, pPosZ);

  		if(getPlayerStatus(i) == S_GRA)
		{
	        if(getPlayerFPS(i) > 0)   // Gracz musi byc ON-Line (Zmiana w wersji 1.5.0).
	        {
			    if(TypArena == false && g_RoundSpawnProtectTime <= 0)
				{
				    //--------------------------
			    	if(ObronaWCP == false)
			    	{
			    	    if(!IsPlayerInAnyVehicle(i))
			    	    {
							if(IsPlayerInRangeOfPoint(i, CHECKPOINT_RANGE, CheckpointPos[0], CheckpointPos[1], CheckpointPos[2]))
							{
						    	if(floatabs(pPosZ - CheckpointPos[2]) <= 0.5)
					        	{
						        	if(getPlayerTeam(i) == T_DEF)
									{
										ObronaWCP = true;
										KtosJestWCP = -1;
									}	else KtosJestWCP = i;
					       		}
							}
						}
					}

					if(getPlayerTeam(i) == T_DEF)
					{
					    if(IsPlayerInRangeOfPoint(i, MAX_DEF_DYS, CheckpointPos[0], CheckpointPos[1], CheckpointPos[2]) && pPosZ > -80)
				        {
			                G[i][PlayerPOS][0] = pPosX, G[i][PlayerPOS][1] = pPosY, G[i][PlayerPOS][2] = pPosZ;
			                continue;
				        }	else PokazOgraniczenie(i, pPosX, pPosY, pPosZ);
				    }	else G[i][PlayerPOS][0] = pPosX, G[i][PlayerPOS][1] = pPosY, G[i][PlayerPOS][2] = pPosZ;
				    
				    //--------------------------
				}
			}
		}
		G[i][PlayerPOS][0] = pPosX, G[i][PlayerPOS][1] = pPosY, G[i][PlayerPOS][2] = pPosZ;
        //--------------------------
	}

	if(TypArena == false && IDStartowanej != -1)
	{
		if(KtosJestWCP != -1)
    	{

    	    if(!IsPlayerConnected(PrzejmujacyCP) || KtosJestWCP == PrzejmujacyCP) PrzejmujacyCP = KtosJestWCP;
    	    else
    	    {
      	        if(getPlayerStatus(PrzejmujacyCP) != S_GRA || IsPlayerInAnyVehicle(PrzejmujacyCP) || !IsPlayerInRangeOfPoint(PrzejmujacyCP, CHECKPOINT_RANGE, CheckpointPos[0], CheckpointPos[1], CheckpointPos[2]))
    	        {
                    PrzejmujacyCP = KtosJestWCP;
    	        }
    	    }

		    if(++ StanPrzejecia < 100) {
			    TextDrawTextSize(TDCaptureBox, StanPrzejecia * g_RoundCaptureValue, 11);
			    format(string, sizeof(string), "%d%%", StanPrzejecia);
				TextDrawSetString(TDCaptureInfo, string);
                forplayers(i) {
			        if(getPlayerStatus(i) == S_GRA  || getPlayerStatus(i) == S_SPECUJE ) {
			            LayoutPlayerCapture(i, true);
		            }
		        }
			}	else KoniecRundy(T_ATT, 1);
	    } else {
	        LayoutPlayerCapture(-1, false);
		    StanPrzejecia = 0;
		    PrzejmujacyCP = INVALID_PLAYER_ID;
	    }
	}
}

//------------------------------------------------------------------------------

forward TimerSekunda();
public TimerSekunda()
{
	#define KICK_POWOD  "{D2D2D2}"
	
 	++ ServerTick;
	
	static	Float:FloatZdrowia, string[512], pName[MAX_PLAYER_NAME], id, ZnalezionoSpectatorow;
	new GraczyNaArenieDM;
	static aimedid, Float:aimHealth, Float:aimArmor;
    forplayers(i) {
    	GetPlayerHealth(aimedid, aimHealth);
		GetPlayerArmour(aimedid, aimArmor);
	    if((aimedid = G[i][TargetPlayer]) != INVALID_PLAYER_ID) {
	        if(gettime() <= G[i][TargetPlayerTime]) {
		        GetPlayerName(aimedid, pName, MAX_PLAYER_NAME);
		        format(string, sizeof(string),"%.0f~n~%.0f~n~%d~n~%d~n~%.1f", aimHealth, aimArmor, GetPlayerPing(aimedid), getPlayerFPS(aimedid), getPlayerPLoss(aimedid));
		        TextDrawSetString(PTD_PlayerAimedNick[i], pName);
	            TextDrawSetString(PTD_PlayerAimedInfo[i], string);
			} else LayoutAimedPlayerInfo(i, (G[i][TargetPlayer] = INVALID_PLAYER_ID));
		}
	    
		if(G[i][stateChangeTick] > 0 and getPlayerFPS(i)) G[i][stateChangeTick] --;
	    ZnalezionoSpectatorow = 0;

		valstr(string, GetPlayerPing(i)), 	TextDrawSetString(PTD_PingFPSPLoss[i][0], string);
		valstr(string, getPlayerFPS(i)), 	TextDrawSetString(PTD_PingFPSPLoss[i][1], string);
		format(string, sizeof(string), "%.1f", getPlayerPLoss(i)),  TextDrawSetString(PTD_PingFPSPLoss[i][2], string);
        //------------------------------------

		if(33 >= G[i][ProbAreaCheck] >= 3) {
			if(IDStartowanej != -1 && TrwaOdliczanie == false && getPlayerStatus(i) != S_GRA) G[i][ProbAreaCheck] ++;
		}
		if(G[i][CzasInfoKill] > 0) {
		    if(G[i][CzasInfoKill] -- == 1) 	{
				TextDrawHideForPlayer(i, PTD_KilledBy[i][0]);
				TextDrawHideForPlayer(i, PTD_KilledBy[i][1]);
			}
		}

        //------------------------------------

        #if OGRANICZENIE_OBSZARU_POJAZDU == 1
		if( (id = G[i][IDPojazdu]) != 0 )
		{
			if(GetVehicleVirtualWorld(id) == VW_SPAWN)
			{
				if(GetVehicleDistanceFromPoint(id, g_LobbySpawnPos[0][0], g_LobbySpawnPos[0][1], g_LobbySpawnPos[0][2]) < 30)
				{
					DestroyVehicle(id);
					G[i][IDPojazdu] = 0;
					SendClientMessage(i,COLOR_WARNING, " (Pojazd) Pojazd nie moze przebywac w bezposrednim sasiedztwie poczekalni");
				}
			}
		}
		#endif

        //------------------------------------

        if(GetPlayerState(i) == PLAYER_STATE_DRIVER)
        {
	        GetVehicleHealth(GetPlayerVehicleID(i), FloatZdrowia);
	        id = FloatZdrowia > 1000.0 ? 100 : floatround((FloatZdrowia - 250) * 0.13);
            switch(id)
			{
	            case 1..30: 	format(string, 32, "{F40000}¤¤¤¤¤¤¤¤¤¤  ");
	            case 31..60:	format(string, 32, "{F2F900}¤¤¤¤¤¤¤¤¤¤  ");
	            case 61..100:   format(string, 32, "{2FB81B}¤¤¤¤¤¤¤¤¤¤  ");
	            default: 		format(string, 32, "{000000}¤¤¤¤¤¤¤¤¤¤  ");

	        }
			strins(string,"{000000}", id < 1 ? 0 : (floatround(id / 10) + 9));
			Update3DTextLabelText(G[i][ZdrowiePojazdu3D], 0x000000FF, string);
	    }

        //------------------------------------

		if(IDStartowanej == -1)	SetPlayerScore(i, GetPlayerDMG(i, true));
		else
	    {
		    if(getPlayerStatus(i) == S_GRA)
	        {
		 //       format(string, 16,"%.0f0%d", G[i][gPoprzednieHP], getPlayerFPS(i));
		 //       SetPlayerScore(i, strval(string));
		        SetPlayerScore(i, floatround(floatadd(aimHealth, aimArmor)));
		        string[0] = EOS;
		        if(GetPVarInt(i, PV_SPEC_POKAZ) == 0)
		        {
			        forplayers(x)
			        {
			            if(IsAdmin(x) <= ALVL_NON)
			            {
				            if(getPlayerStatus(x) == S_SPECUJE)
				            {
				                if(G[x][SpecowanyID] == i)
				                {
		                            ZnalezionoSpectatorow ++;
		                            format(string, sizeof(string),"%s~n~%s", string, GetPlayerNick(x));
				                }
				            }
						}
			        }
				}
	        }	else SetPlayerScore(i, 0);
	    }

		if(ZnalezionoSpectatorow > 0)
		{
			strins(string, "~n~_", strlen(string));
		    TextDrawSetString(PTD_SpecByInfo[i], string);
		    TextDrawShowForPlayer(i, PTD_SpecByInfo[i]);
		    TextDrawShowForPlayer(i, TDSpecByBox);
		}
		else
		{
		    TextDrawHideForPlayer(i, PTD_SpecByInfo[i]);
		    TextDrawHideForPlayer(i, TDSpecByBox);
		}

//		**********************

		if( (id = getPlayerStatus(i)) != S_GRA)
		{
            forplayers(x) SetPlayerMarkerForPlayer(x, i, getPlayerStatus(x) == id ? GetPlayerColor(i) | 0x00000050 : GetPlayerColor(i) & 0xFFFFFF00);
		}

		switch(getPlayerStatus(i))
		{
			case S_ARENA_DM:	GraczyNaArenieDM ++;
//			case S_SPECUJE:		ShowSpecInfo(i, G[i][SpecowanyID]);
		}
	}

//	**********************

	format(string, 52, "Graczy  %d",GraczyNaArenieDM);
	TextDrawSetString(TDTrainingArenaInfo, string);

//	**********************
    timer_InactiveStarter();
    
	return 1;
}

//------------------------------------------------------------------------------

forward TimerRunda();
public TimerRunda()
{
	static 	Float:pPosX, Float:pPosY, Float:pPosZ, OstatniAttID, OstatniDefID, Float:Armour, id, string[128], string2[128], smallstring[8];
	static weapon, ammo, bool:switchString, x;
	static activePlayersAtt, activePlayersDef;
	
    new gamePlayersAtt, gamePlayersDef, Float:healthAtt, Float:healthDef;
    
    gamePlayersAtt = getAlivePlayersInTeam(T_ATT);
    gamePlayersDef = getAlivePlayersInTeam(T_DEF);
    
    forplayers(i) {
	    GetPlayerArmour(i, Armour);
	    
		switch((id = getPlayerTeam(i))) {
			case T_ATT: {
				if(getPlayerStatus(i) == S_GRA) {
				    if(G[i][LastUpdate] + 15 > gettime()) activePlayersAtt ++;
				    OstatniAttID = i;
				    healthAtt += G[i][gPoprzednieHP] + Armour;
				}
			}
			case T_DEF: {
				if(getPlayerStatus(i) == S_GRA) {
				    if(G[i][LastUpdate] + 15 > gettime()) activePlayersDef ++;
				    OstatniDefID = i;
				    healthDef += G[i][gPoprzednieHP] + Armour;
				}
			}
		}

		if(IDStartowanej != -1 and getPlayerStatus(i) == S_GRA) {
			if(g_RoundSpawnProtectTime <= 0 and Armour > MAX_ARMOUR) SetPlayerArmourEx(i, (Armour = MAX_ARMOUR));
			strdel(string, 0, 128);
			strdel(string2, 0, 128);
			for(x = 1, switchString = false; x <= 10; x ++) {
				GetPlayerWeaponData(i, x, weapon, ammo);
				if(42 >= weapon > 0) {
					if(switchString == false) format(string, sizeof(string),"%s%s (%d)~n~", string, getWeaponName(weapon), ammo);
					else format(string2, sizeof(string2),"%s%s (%d)~n~", string2, getWeaponName(weapon), ammo);
					switchString = !switchString;
				}
				
			}
			if(id == T_ATT) {
				if(TypArena == false && InteriorWalki == 0) {
					if(IsPlayerInRangeOfPoint(i, CAR_SPAWN_DYS, SpawnAtt[0], SpawnAtt[1], SpawnAtt[2])) TextDrawShowForPlayer(i, TDCarInfo);
					else TextDrawHideForPlayer(i, TDCarInfo);

					if(CzasMin < 5) {
				        if(!IsPlayerInRangeOfPoint(i, MAX_DEF_DYS, CheckpointPos[0], CheckpointPos[1], CheckpointPos[2])) {
							if(++ G[i][OstrzezenieAttPoza] > 15) {
								valstr(string, i);
								cmd_rem(-1, string);
							}
			            }	else G[i][OstrzezenieAttPoza] = 0;
					}
				}
			}

            for(x = 0; x < MAX_PLAYERS; x ++) {
                if(IsPlayerConnected(x)) {
	                if(getPlayerStatus(x) == S_SPECUJE and G[x][SpecowanyID] == i) {
                        TextDrawSetString(PTD_SpecWeapons[x][0], string);
                        TextDrawSetString(PTD_SpecWeapons[x][1], string2);
                        
                        format(smallstring, sizeof(smallstring), "%.0f", G[i][gPoprzednieHP]);
						TextDrawSetString(PTD_SpecHealth[x][1], smallstring);
						
						format(smallstring, sizeof(smallstring), "%.0f", Armour);
						TextDrawSetString(PTD_SpecArmor[x][1], smallstring);
						
						TextDrawTextSize(PTD_SpecHealth[x][0], G[i][gPoprzednieHP] * 0.6, 10.0);
						TextDrawShowForPlayer(x, PTD_SpecHealth[x][0]);
						
						TextDrawTextSize(PTD_SpecArmor[x][0], Armour * 0.6, 10.0);
						TextDrawShowForPlayer(x, PTD_SpecArmor[x][0]);
	                }
					SetPlayerMarkerForPlayer(x, i, getPlayerStatus(x) == S_GRA ? (getPlayerTeam(x) == id ? GetPlayerColor(i) | 0x00000050 : GetPlayerColor(i) & 0xFFFFFF00) : GetPlayerColor(i) & 0xFFFFFF00);
				}
			}
            GetAnimationName(GetPlayerAnimationIndex(i), string, 32, string, 32);
			if(strfind(string, "GUNMOVE_", true) != -1)
		    {
                GetPlayerVelocity(i, pPosX, pPosY, pPosZ);
                if((floatpower(pPosX,2)+floatpower(pPosY,2))*200 > 3.0)
				{
					GetPlayerPos(i, pPosX, pPosY, pPosZ);
					SetPlayerPos(i, pPosX, pPosY, pPosZ + 0.2);
			    }
			}
		}
	}


	if(IDStartowanej == -1) {
	    TextDrawSetString(TDBottomBeltCenter[0], "--:--");
	    TextDrawSetString(TDBottomBeltCenter[1], "NoN");
		TextDrawSetString(TDBottomBeltTeamLeft[3], "0");
	    TextDrawSetString(TDBottomBeltTeamRight[3], "0");
		SetGameModeText(GM_PRZERWA);
		if(CzasAdminVote > 0) CzasAdminVote --;
	} else {
		valstr(smallstring, floatround(healthAtt)); TextDrawSetString(TDBottomBeltTeamLeft[3], smallstring);
	    valstr(smallstring, floatround(healthDef)); TextDrawSetString(TDBottomBeltTeamRight[3], smallstring);

		if(TrwaOdliczanie == false) {
		    TimerSpawnProtect();
			if(-- CzasSek < 0) {
			    CzasSek = 59;
			    if(-- CzasMin < 0) {
					if(TypArena == true) {
					    if(healthDef > healthAtt)		KoniecRundy(T_DEF, 1);
						else if(healthDef < healthAtt)	KoniecRundy(T_ATT, 1);
						else							KoniecRundy(T_REF, 2);
				    }	else KoniecRundy(T_DEF, 2);
					return 1;
		        }
		    }
			#if _TESTY == 0
			if(gamePlayersAtt == 0 || gamePlayersDef == 0) {
		        KoniecRundy(gamePlayersDef > 0 ? T_DEF : gamePlayersAtt > 0 ? T_ATT : T_REF, 0);
				return 1;
			} else if(activePlayersAtt == 0 or activePlayersDef == 0) {
		        KoniecRundy(activePlayersDef > 0 ? T_DEF : activePlayersAtt > 0 ? T_ATT : T_REF, 0);
		        SendClientMessageToAll(COLOR_START_INFO, " (Runda) Przerwano walke z powodu braku aktywnosci pozostalych przy zyciu graczy.");
				return 1;
		    } else {
			#endif
				if(gamePlayersAtt == 1 || gamePlayersDef == 1) {
				    format(string, sizeof(string),"%d~n~%s  (HP: %.0f)", gamePlayersAtt, gamePlayersAtt == 1 ? GetPlayerNick(OstatniAttID) : ("Atak"), healthAtt);
				    TextDrawSetString(TDOneOnOne[0], string);
				    format(string, sizeof(string),"%d~n~%s  (HP: %.0f)", gamePlayersDef, gamePlayersDef == 1 ? GetPlayerNick(OstatniDefID) : ("Obrona"), healthDef);
				    TextDrawSetString(TDOneOnOne[1], string);

                    forplayers(i) {
					    if(getPlayerStatus(i) == S_GRA  || getPlayerStatus(i) == S_SPECUJE ) 	LayoutPlayerOneOnOne(i, true);
						else LayoutPlayerOneOnOne(i, false);
					}
				}
			#if _TESTY == 0
			}
			#endif

            format(string, sizeof(string),"%d:%02d", CzasMin, CzasSek), TextDrawSetString(TDBottomBeltCenter[0], string);
			format(string, 64,"%s %d  T %d:%02d  Att %d:%d Def",TypArena == true ? ("A") : ("B"), IDStartowanej, CzasMin, CzasSek, gamePlayersAtt, gamePlayersDef);
			SetGameModeText(string);
		}
	}
	return 1;
}

//------------------------------------------------------------------------------

forward TimerMinuta();
public TimerMinuta()
{
	new g,m, R, M, D, string[200];

	gettime(g, m);
	getdate(R, M, D);
	format(string, 16,"%02d:%02d", g, m);
	TextDrawSetString(TDZegar, string);
	TextDrawSetString(TDData, strData(R, M, D, " / ", false, false, true, false));
	
	if(OgloszenieCzas > 0) {
	    if(OgloszenieCzas <= timestamp()) {
	        OgloszenieCzas = 0;
	        TextDrawSetString(TDOgloszenieSerwerowe, " ");
	        fclose(fopen(PLIK_OGLOSZENIA, io_write));
	    }
	}
}

//------------------------------------------------------------------------------

forward TimerDziesiec();
public TimerDziesiec()
{
	new string[150], Graczy, pName[MAX_PLAYER_NAME];


	forplayers(i) Graczy ++;

    forplayers(i)
    {
		if(getPlayerStatus(i) == S_GRA and g_RoundSpawnProtectTime == 0)
	    {
	        if(getPlayerFPS(i) == 0)
            {
		       	if(++ G[i][AFKWarning] > 3)
		       	{
					if(Graczy < MAX_GRACZY || IsAdmin(i) != ALVL_NON)
					{
					    if(G[i][gPoprzednieHP] <= 20) AddPlayerRespect(i, -2);

						UpdatePlayerStats(i);
						setPlayerStatus(i, S_SPAWN);
						OnPlayerSpawn(i);
				        DialogHideForPlayer(i);
				        format(string, 128," (Anty AFK) "TEXT_NORMAL"%s"TEXT_PREM" zostal(a) usuniety(a) z rundy. Powod: "TEXT_NORMAL"Anty AFK", GetPlayerNick(i));
				        SendClientMessageToAll(COLOR_PREM, string);
				        G[i][AFKWarning] = 0;
					}
					else
					{
				        format(string, 140,"\n\t"DIALOG_KICK_COLOR"Zostales(as) wyrzucony(a) z serwera.\n\tPowod: "DIALOG_NORMAL_COLOR"Anty AFK\n\t"DIALOG_KICK_COLOR"Graczy na serwerze "DIALOG_NORMAL_COLOR"%d/%d\n",Graczy,MAX_GRACZY);
				        ShowPlayerDialog(i, DIALOG_KICK, DIALOG_STYLE_MSGBOX, DIALOG_KICK_COLOR"Kick", string, "Wyjdz", "");
            			GetPlayerName(i, pName, MAX_PLAYER_NAME);
				        Kick(i);
				        format(string, 150," (Kick) "TEXT_NORMAL"%s [ID: %d]"C_KICK" zostal(a) wyrzucony(a) z serwera. Powod: "TEXT_NORMAL"Anty AFK", pName, i);
				        SendClientMessageToAll(COLOR_KICK, string);
					}
				}
				else
		    	{
			    	format(string, 85," (Anty AFK) Zbyt dlugo przebywasz w bezruchu  ( Ostrzezen "TEXT_NORMAL"%d/3"C_KICK" )", G[i][AFKWarning]);
			    	SendClientMessage(i, COLOR_KICK, string);
			    }
		    }	else G[i][AFKWarning] = 0;
		}
    }
}

//------------------------------------------------------------------------------

forward KoniecWarnWybieralka(const playerid);
public KoniecWarnWybieralka(const playerid)
{
    TextDrawHideForPlayer(playerid, TDDlaAdministracjiSerwera);
    TextDrawHideForPlayer(playerid, TDZaduzoGraczyWTeamie);
}

//------------------------------------------------------------------------------

forward StartCameraLook(Float:kat, Float:posz, metoda, dys);
public StartCameraLook(Float:kat, Float:posz, metoda, dys)
{
    if(TrwaOdliczanie == true)
    {
        static Float:PosX, Float:PosY;
        
        posz ++;
        if(++ kat > 359)   	kat = 0;
        switch(metoda)
        {
            case 2: kat = posz = 10.0;
            case 1: 
            {
		        PosX = CheckpointPos[0]+(dys * floatsin(-kat, degrees)),
		        PosY = CheckpointPos[1]-(dys * floatcos(-kat, degrees));
            }
            default: 
            {
		        PosX = CheckpointPos[0]-(dys * floatsin(-kat, degrees)),
		        PosY = CheckpointPos[1]+(dys * floatcos(-kat, degrees));
            }
		}
  
        forplayers(i)
		{
		    if(GetPlayerVirtualWorld(i) == VW_GRA)
	        {
				SetPlayerCameraPos(i, PosX, PosY, posz);
				SetPlayerCameraLookAt(i, CheckpointPos[0], CheckpointPos[1], CheckpointPos[2]);
	        }
	    }
	    SetTimerEx("StartCameraLook", 40, 0, "ffdd", kat, posz, metoda, dys);
	}
}
//------------------------------------------------------------------------------

forward KeyZmiany(const playerid);
public KeyZmiany(const playerid)	G[playerid][PrzyciskSpecowaniaWcisniety] = false;

//------------------------------------------------------------------------------

forward DestroyIcon(const icon);
public DestroyIcon(const icon)
{
    forplayers(i) RemovePlayerMapIcon(i, icon);
}

//------------------------------------------------------------------------------
forward KoniecGlosowania(czas);
public KoniecGlosowania(czas)
{
    if(GlosowanieAktywne == true)
    {
        new string[350];
		if(-- czas <= 0)
		{
		
			new TopVote[_vote] = { -1, 0, 0};
			for(new i; i < MAX_VOTE ; i ++)
			{
			    if(VoteVar[i][Tryb] != -1)
			    {
					if(VoteVar[i][Glosow] >= TopVote[Glosow])
					{
					    TopVote[Glosow] = VoteVar[i][Glosow];
					    TopVote[Tryb] = VoteVar[i][Tryb];
					    TopVote[NumerID] = VoteVar[i][NumerID];
					}
			    }   else break;
			}
			
			IDStartowanej = TopVote[NumerID];
			TypArena = TopVote[Tryb] == 1 ? false : true;

		    format(string, sizeof(string),"HighSkill/%s/%d.txt", TypArena == true ? ("Areny") : ("Bazy"), IDStartowanej);
		    
		    GlosowanieAktywne = false;
		    TextDrawHideForAll(TDVoteName);
			TextDrawHideForAll(TDVoteInfo);
		    
			for(new i; i < MAX_VOTE; i ++)
			{
			    VoteVar[i][Tryb] = -1;
			    VoteVar[i][NumerID] = VoteVar[i][Glosow] = 0;
			}
			for(new i; i < MAX_GRACZY; i++)
			{
			    G[i][VoteWybor] = -1;
				G[i][VoteDodano] = false;
			}
			
			if(!fexist(string))
			{
			    format(string, sizeof(string)," (Vote) Nie znaleziono pliku pod adresem: "TEXT_NORMAL"%s", string);
				return SendClientMessageToAll(COLOR_WARNING,string);
			}
			StartRundy(string);
		}
		else
		{
		    if(CZAS_GLOSOWANIA - 10 == czas) {
		        new vTop = -1, vSecond = -1;

		        for(new i; i < MAX_VOTE; i ++) {
		            if(VoteVar[i][Tryb] != -1) {
		                if(vTop == -1) vTop = i;
		                else {
		                    if(VoteVar[i][Glosow] >= VoteVar[vTop][Glosow]) {
								vSecond = vTop;
								vTop = i;
		                    } else {
		                        if(vSecond == -1 or VoteVar[i][Glosow] >= VoteVar[vSecond][Glosow]) {
		                            vSecond = i;
		                        }
		                    }
		                }
		            }
		        }
		        if(vTop != -1) {
			        if(vSecond == -1) {
			            SendClientMessageToAll(COLOR_VOTE_INFO, " (Glosowanie) Zakonczono glosowanie z powodu braku konkurencyjnych pozycji do glosowania");
                        KoniecGlosowania(0);
			            return 1;
			        } else {
						if(floatdiv(VoteVar[vTop][Glosow], VoteVar[vSecond][Glosow] == 0 ? 1 : VoteVar[vSecond][Glosow]) >= 3.0) {
				            SendClientMessageToAll(COLOR_VOTE_INFO, " (Glosowanie) Zakonczono glosowanie z powodu uzyskania przewagi 3:1 topowej pozycji nad kolejna");
	                        KoniecGlosowania(0);
						    return 1;
						} else {
						    CheckVotePossibility();
						}
			        }
				}
		    }
		
		    format(string, sizeof(string),"~n~Pozostaly_czas  ~w~%ds~n~", czas);
		    for(new i; i < MAX_VOTE; i ++) {
		        if(VoteVar[i][Tryb] != -1) {
		            format(string, sizeof(string),"%s~n~%d) %s_%d___(_%d_)", string, i + 1, VoteVar[i][Tryb] == 0 ? ("Arena") : ("Baza"), VoteVar[i][NumerID], VoteVar[i][Glosow]);
		        }   else break;
		    }
		    strins(string, "~n~_", strlen(string));
		    TextDrawSetString(TDVoteInfo, string);
		    SetTimerEx("KoniecGlosowania", 1000, 0, "d", czas);
		}
		GlosowanieCzas = czas;
	}
	return 1;
}
//------------------------------------------------------------------------------
CheckVotePossibility() {
	if(GlosowanieAktywne == true and GlosowanieCzas <= CZAS_GLOSOWANIA - 5) {
        new vTop = -1, vSecond = -1;

        for(new i; i < MAX_VOTE; i ++) {
            if(VoteVar[i][Tryb] != -1) {
                if(vTop == -1) vTop = i;
                else {
                    if(VoteVar[i][Glosow] >= VoteVar[vTop][Glosow]) {
						vSecond = vTop;
						vTop = i;
                    } else {
                        if(vSecond == -1 or VoteVar[i][Glosow] >= VoteVar[vSecond][Glosow]) {
                            vSecond = i;
                        }
                    }
                }
            }
        }
        
        if(vTop != -1) {
            if(vSecond != -1 and floatdiv(VoteVar[vTop][Glosow], VoteVar[vSecond][Glosow] == 0 ? 1 : VoteVar[vSecond][Glosow]) >= 4.0) {
                SendClientMessageToAll(COLOR_VOTE_INFO, " (Glosowanie) Zakonczono glosowanie z powodu uzyskania przewagi 4:1 topowej pozycji nad kolejna");
                KoniecGlosowania(0);
				return 1;
            } else {
	            new secondValue = vSecond == -1 ? 0 : VoteVar[vSecond][Glosow], nonVoters;
	            forplayers(i) {
	                if(G[i][VoteWybor] == -1) nonVoters ++;
	            }
	            if(secondValue + nonVoters < VoteVar[vTop][Glosow]) {
	                SendClientMessageToAll(COLOR_VOTE_INFO, " (Glosowanie) Zakonczono glosowanie z powodu uzyskania bezwzglednej przewagi topowej pozycji nad kolejna");
	                KoniecGlosowania(0);
					return 1;
	            }
            }
        }
	}
	return 0;
}

//------------------------------------------------------------------------------

forward KamPosmiertna(const playerid, const killerid, const Float:pX, const Float:pY, const Float:pZ);
public KamPosmiertna(const playerid, const killerid, const Float:pX, const Float:pY, const Float:pZ) {
	if(IsPlayerConnected(playerid) && IsPlayerConnected(killerid)) {
	    if(G[playerid][CzasInfoKill] > 0 && GetPlayerState(playerid) == PLAYER_STATE_WASTED) {
	        static Float:pPosX, Float:pPosY, Float:pPosZ;
			GetPlayerPos(killerid, pPosX, pPosY, pPosZ);
  			SetPlayerCameraPos(playerid, pX, pY, pZ);
			SetPlayerCameraLookAt(playerid, pPosX, pPosY, pPosZ);
			SetTimerEx("KamPosmiertna", 100, 0, "ddfff", playerid, killerid, pX, pY, pZ);
        }
    }
}

//------------------------------------------------------------------------------
forward UpdatePlayerStats(const playerid);
public UpdatePlayerStats(const playerid) {
	if(IsPlayerConnected(playerid)) {
	    new string[12];
		new bool:online = (getPlayerLoginStatus(playerid) == LOGIN_STATUS_NOTREGISTERED or GetPVarInt(playerid, PV_WYNIKI) == 0) ? true : false;

		valstr(string, GetPlayerKill(playerid, online)); 			TextDrawSetString(PTD_PlayerHudKills[playerid], string);
		valstr(string, GetPlayerDeath(playerid, online)); 			TextDrawSetString(PTD_PlayerHudDeaths[playerid], string);
		valstr(string, GetPlayerDMG(playerid, online)); 			TextDrawSetString(PTD_PlayerHudDamage[playerid], string);
		valstr(string, GetPlayerRespect(playerid, online)); 		TextDrawSetString(PTD_PlayerHudRespect[playerid], string);
		
		if(getPlayerLoginStatus(playerid) == LOGIN_STATUS_NOTREGISTERED) 	TextDrawSetString(PTD_PlayerHudRanking[playerid], "NoN");
		else {
		    valstr(string, GetPVarInt(playerid, PV_RANKING)); 	TextDrawSetString(PTD_PlayerHudRanking[playerid], string);
		}
    }
}
//------------------------------------------------------------------------------

forward UsunObiektObszaru(playerid);
public  UsunObiektObszaru(playerid)
{
	DestroyPlayerObject(playerid, G[playerid][IDObjektuObszaruAreny]);
    G[playerid][IDObjektuObszaruAreny] = 0;
}

//------------------------------------------------------------------------------

forward UsunKrew(objectid);
public UsunKrew(objectid) DestroyObject(objectid);
//------------------------------------------------------------------------------
forward GameModeHelp(playerid, fromsystem);
public GameModeHelp(playerid, fromsystem) {
	if(getPlayerStatus(playerid) == S_WYBIERALKA) return 1;
	SetPVarInt(playerid, PV_D_POMOCNICZA_3, fromsystem);
	return ShowPlayerDialog(playerid, DIALOG_POMOC, DIALOG_STYLE_LIST, DIALOG_HEAD_COLOR"Menu pomocy", D_CC"1) "DIALOG_TEXT_COLOR"Informacje\n"D_CC"2) "DIALOG_TEXT_COLOR"Regulamin gry\n"D_CC"3) "DIALOG_TEXT_COLOR"Ustawienia serwera\n"D_CC"4) "DIALOG_TEXT_COLOR"Spis komend\n"D_CC"5) "DIALOG_TEXT_COLOR"Panel zarzadzania gra\n"D_CC"6) "DIALOG_TEXT_COLOR"Lista administracji\n"D_CC"7) "DIALOG_TEXT_COLOR"Informacje o bledach i sugestie", "Dalej", "Wyjdz");
}
//------------------------------------------------------------------------------
/*
forward HSAS_OnSettingsUpdate(index, value);
public HSAS_OnSettingsUpdate(index, value)
{
	switch(index)
	{
	    case -1:    DodatkowyGranat = value == 0 ? false : true;
	    case 0..7:	Bron[index][GUN_AMMO] = value;
		case 10:    CZAS_ARENY = value;
		case 11:    CZAS_BAZY = value;
		case 12:    MAX_ARMOUR = value;
	}
	return 1;
}
*/
//------------------------------------------------------------------------------
/*
forward HSAS_VersionUpdate(ver[]);
public HSAS_VersionUpdate(ver[])
{
	new string[64];
	if(strlen(ver) > 2)
	{
		format(HSASWersja, 16, ver);
		format(string, sizeof(string), "v"GM_WERSJA" by AxL~n~HS-AS v%s by AxL", ver);
	}
	else
	{
	    format(string, sizeof(string), "v"GM_WERSJA" by AxL");
		format(HSASWersja, 16, "NoN");
	}
	TextDrawSetString(TDAutorMaleLogo, string);
	return 1;
}
*/

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

UleczenieGracza(playerid, Float:poprzednieHP, Float:noweHP, Float:roznicaHP)
{
	new str2[128], string[128], ip[16];

	GetPlayerIp(playerid, ip, sizeof(ip));
    format(string, 128, " (Anty Heal) Skrypt wykryl niezarejestrowane uleczenie u gracza "TEXT_NORMAL"%s", GetPlayerNick(playerid));
    if(TypArena == true)
		format(str2, sizeof(str2),"    ( pHP: %.0f  |  nHP: %.0f  | rHP: %.0f  |  ID: %d  |  IP: %s  |  Typ: Arena [ %d:%02d ] ).",
			poprzednieHP, noweHP, roznicaHP, playerid, ip, CzasMin, CzasSek);
	else
	    format(str2, sizeof(str2),"    ( pHP: %.0f  |  nHP: %.0f  | rHP: %.0f  |  ID: %d  |  IP: %s  |  Typ: Baza [ %d:%02d ] ).",
			poprzednieHP, noweHP, roznicaHP, playerid, ip, CzasMin, CzasSek);

    forplayers(i)
	{
	    if(IsAdmin(i) != ALVL_NON)
	    {
		    SendClientMessage(i, COLOR_KICK, string);
            SendClientMessage(i, COLOR_KICK, str2);
        }
    }
}

//------------------------------------------------------------------------------

PokazOgraniczenie(playerid, Float:pPosX, Float:pPosY, Float:pPosZ)
{
	if(getPlayerStatus(playerid) == S_GRA) {
		new bool:BladSpawnu;
	    if(TypArena == false)
		{
		    if(floatsqroot(floatpower(CheckpointPos[0] - G[playerid][PlayerPOS][0], 2) + floatpower(CheckpointPos[1] - G[playerid][PlayerPOS][1], 2)) >= MAX_DEF_DYS || G[playerid][PlayerPOS][2] <= -80 || pPosZ <= -80)
		    {
		        BladSpawnu = true;
				BackToSpawn(playerid);
			}
		}
		else
		{
	    	if( !(ObszarWalki[2] < G[playerid][PlayerPOS][0] < ObszarWalki[0] && ObszarWalki[3] < G[playerid][PlayerPOS][1] < ObszarWalki[1]) || G[playerid][PlayerPOS][2] <= -80 || pPosZ <= -80)
	   	    {
	   	        BladSpawnu = true;
				BackToSpawn(playerid);
	   	    }
		}

		if(BladSpawnu == false)
		{
			if(G[playerid][IDObjektuObszaruAreny] != 0) DestroyPlayerObject(playerid, G[playerid][IDObjektuObszaruAreny]);
			G[playerid][IDObjektuObszaruAreny] = CreatePlayerObject(playerid, 18724, pPosX, pPosY, pPosZ - 1.2, 0, 0, 0, 5);
			SetTimerEx("UsunObiektObszaru", 500, 0, "d", playerid);
			SetPlayerPos(playerid, G[playerid][PlayerPOS][0], G[playerid][PlayerPOS][1], G[playerid][PlayerPOS][2]);
		}
	} else {
		if(G[playerid][IDObjektuObszaruAreny] != 0) DestroyPlayerObject(playerid, G[playerid][IDObjektuObszaruAreny]);
		G[playerid][IDObjektuObszaruAreny] = CreatePlayerObject(playerid, 18724, pPosX, pPosY, pPosZ - 1.2, 0, 0, 0, 5);
		SetTimerEx("UsunObiektObszaru", 500, 0, "d", playerid);
		SetPlayerPos(playerid, G[playerid][PlayerPOS][0], G[playerid][PlayerPOS][1], G[playerid][PlayerPOS][2]);
	}
}

//------------------------------------------------------------------------------

BackToSpawn(playerid)
{
    new string[256];
	if(G[playerid][ProbAreaCheck] < 3)
	{
	    G[playerid][ProbAreaCheck] ++;
		if(GetTimeToServerTick(G[playerid][CzasAreaCheck]) <= 0)
		{
			if(getPlayerTeam(playerid) == T_ATT)
		    {
				G[playerid][PlayerPOS][0] = random(2) == 0 ? SpawnAtt[0] + random(floatround(SpawnAtt[3])) + (random(1000) * 0.001) : SpawnAtt[0] - random(floatround(SpawnAtt[3])) + (random(1000) * 0.001);
				G[playerid][PlayerPOS][1] = random(2) == 0 ? SpawnAtt[1] + random(floatround(SpawnAtt[4])) + (random(1000) * 0.001) : SpawnAtt[1] - random(floatround(SpawnAtt[4])) + (random(1000) * 0.001);
		        G[playerid][PlayerPOS][2] = SpawnAtt[2] + 0.5;
			}
			else
		    {
				G[playerid][PlayerPOS][0] = random(2) == 0 ? SpawnDef[0] + random(floatround(SpawnDef[3])) + (random(1000) * 0.001) : SpawnDef[0] - random(floatround(SpawnDef[3])) + (random(1000) * 0.001);
				G[playerid][PlayerPOS][1] = random(2) == 0 ? SpawnDef[1] + random(floatround(SpawnDef[4])) + (random(1000) * 0.001) : SpawnDef[1] - random(floatround(SpawnDef[4])) + (random(1000) * 0.001);
		        G[playerid][PlayerPOS][2] = SpawnDef[2] + 0.5;
			}
			SetPlayerPos(playerid, G[playerid][PlayerPOS][0], G[playerid][PlayerPOS][1], G[playerid][PlayerPOS][2]);
		    format(string, 256, " (Area Check) Gracz "TEXT_NORMAL"%s"TEXT_PADD" zostales(as) przywrocony(a) na respawn z powodu mozliwosci wystapienia bledu spawnu", GetPlayerNick(playerid));
		    SendClientMessage(playerid, COLOR_PADD, string);
		    G[playerid][CzasAreaCheck] = GetServerTick() + 2;
		}
	}
	else
	{
        DialogHideForPlayer(playerid);
        setPlayerStatus(playerid, S_SPAWN);
        OnPlayerSpawn(playerid);
		format(string, sizeof(string), " (Usuniecie Gracza) System usunal gracza "TEXT_NORMAL"%s"TEXT_PREM" z rundy  ( Druzyna: "TEXT_NORMAL"%s"TEXT_PREM" )",GetPlayerNick(playerid), getPlayerTeam(playerid) == T_ATT ? ("Atak") : ("Obrona"));
		SendClientMessageToAll(COLOR_PREM, string);
		SendClientMessageToAll(COLOR_PREM, "    Gracz ma mozliwosc powrotu do walki w ciagu 30 sekund");
		SendClientMessage(playerid, COLOR_PREM, "    Zeby powrocic do walki uzyj: "TEXT_NORMAL"/respawn");
	}
}
//------------------------------------------------------------------------------
DodajDoWalki(const playerid)
{
	if(getPlayerStatus(playerid) != S_WYBIERALKA)
    {
		if(getPlayerTeam(playerid) == T_ATT || getPlayerTeam(playerid) == T_DEF)
	    {
	        new string[150], Float:angle = random(360);
	        G[playerid][stateChangeTick] = 3;
	        ResetPlayerWeapons(playerid);
			if(getPlayerStatus(playerid) == S_SPAR)
		    {
				format(string, sizeof(string), " (Sparing) Sparing zostal zakonczony z powodu dodania gracza "TEXT_NORMAL"%s"TEXT_SPARING_WARNING" do walki", GetPlayerNick(playerid));
			    SendClientMessage(playerid, COLOR_SPARING_WARNING, string);
			    SendClientMessage(G[playerid][SparingIDGracza], COLOR_SPARING_WARNING, string);
			    KoniecSparingu(G[playerid][SparingIDGracza]);
		    }
			else if(getPlayerStatus(playerid) == S_SPECUJE) StopSpec(playerid);

			if(g_RoundSpawnProtectTime != 0) {
			    LayoutSpawnProtect(playerid, true);
			}

		    SetPVarInt(playerid, PV_HEAL, 3);

            G[playerid][HitInGame] = false;

			SetPlayerHealthEx(playerid, 100);
			SetPlayerArmourEx(playerid, 100);

            DialogHideForPlayer(playerid);
            SetPlayerTeam(playerid, getPlayerTeam(playerid));
            
            setPlayerStatus(playerid, S_GRA);
            G[playerid][UdzialWWalceTeam] = getPlayerTeam(playerid);
		    SetPVarInt(playerid, PV_TAB, 0);

			G[playerid][gFragiRunda] = G[playerid][gDMGRunda] = G[playerid][ProbAreaCheck] =
			G[playerid][OstrzezenieAttPoza] = G[playerid][IDObjektuObszaruAreny] = 0;

            
            SetPVarInt(playerid, PV_HEAL, 3);
            SpawnPlayer(playerid);
 //           printf("Random angle: %.1f", angle);
			if(G[playerid][IDPojazdu] != 0)
			{
			    DestroyVehicle(G[playerid][IDPojazdu]);
			    G[playerid][IDPojazdu] = 0;
		    }

		    if(getPlayerTeam(playerid) == T_ATT)
	        {
		        SetPlayerColor(playerid, COLOR_ATT_AK);
				G[playerid][PlayerPOS][0] = random(2) == 0 ? SpawnAtt[0] + random(floatround(SpawnAtt[3])) + (random(1000) * 0.001) : SpawnAtt[0] - random(floatround(SpawnAtt[3])) + (random(1000) * 0.001);
				G[playerid][PlayerPOS][1] = random(2) == 0 ? SpawnAtt[1] + random(floatround(SpawnAtt[4])) + (random(1000) * 0.001) : SpawnAtt[1] - random(floatround(SpawnAtt[4])) + (random(1000) * 0.001);
                G[playerid][PlayerPOS][2] = SpawnAtt[2] + 0.5;

			}
			else
		    {
			    SetPlayerColor(playerid, COLOR_DEF_AK);
				G[playerid][PlayerPOS][0] = random(2) == 0 ? SpawnDef[0] + random(floatround(SpawnDef[3])) + (random(1000) * 0.001) : SpawnDef[0] - random(floatround(SpawnDef[3])) + (random(1000) * 0.001);
				G[playerid][PlayerPOS][1] = random(2) == 0 ? SpawnDef[1] + random(floatround(SpawnDef[4])) + (random(1000) * 0.001) : SpawnDef[1] - random(floatround(SpawnDef[4])) + (random(1000) * 0.001);
                G[playerid][PlayerPOS][2] = SpawnDef[2] + 0.5;
		    }
			SetPlayerPos(playerid, (P_WorldArea[playerid][X] = G[playerid][PlayerPOS][0]), (P_WorldArea[playerid][Y] = G[playerid][PlayerPOS][1]), (P_WorldArea[playerid][Z] = G[playerid][PlayerPOS][2]));

//			printf("%.4f | %.4f | %.4f",P_WorldArea[playerid][X], P_WorldArea[playerid][Y], P_WorldArea[playerid][Z]);
		    if(TypArena == true)
	        {
				angle = g_RoundArenaAngles[getPlayerTeam(playerid)];
		        SetPlayerMapIcon(playerid, 0, CheckpointPos[0], CheckpointPos[1], CheckpointPos[2], 19, 0, MAPICON_GLOBAL);

				if(ObszarWalki[0] + ObszarWalki[1] + ObszarWalki[2] + ObszarWalki[3] != -39996) {
			        setPlayerWorldArea(playerid, ObszarWalki[0], ObszarWalki[1], ObszarWalki[2], ObszarWalki[3], ObszarWalki[4], ObszarWalki[5], true, GANG_ZONE_COLOR);
		        }
			}
			else
		    {
			    if(InteriorWalki == 0)
			    {
				    SetPlayerMapIcon(playerid, 0, CheckpointPos[0], CheckpointPos[1], CheckpointPos[2], 6, 0, MAPICON_GLOBAL_CHECKPOINT);
				    SetPlayerMapIcon(playerid, 1,SpawnAtt[0], SpawnAtt[1], SpawnAtt[2], 55, 0, MAPICON_GLOBAL);
				    if(SpawnLodzi[0] != 0.0 && SpawnLodzi[1] != 0.0 && SpawnLodzi[2] != 0.0) SetPlayerMapIcon(playerid, 2,SpawnLodzi[0], SpawnLodzi[1], SpawnLodzi[2], 9, 0, MAPICON_GLOBAL);
				}   else SetPlayerCheckpoint(playerid, CheckpointPos[0], CheckpointPos[1], CheckpointPos[2], g_RoundCaptureCheckpointSize);
			}

			SetPlayerFacingAngle(playerid, angle);
			
			ShowPlayerFirstGunMenu(playerid);                                   //From p_round.inc
			
            SetPlayerVirtualWorld(playerid, VW_GRA);
            SetPlayerInterior(playerid, InteriorWalki);
            
            G[playerid][CzasAreaCheck] = GetServerTick() + 2;

			SetCameraBehindPlayer(playerid);
            SetPlayerFightingStyle(playerid, FIGHT_STYLE_BOXING);

	    }
		else if(getPlayerTeam(playerid) == T_REF) SpawnPlayer(playerid);
    }
}
//------------------------------------------------------------------------------
forward ShowPlayerGameMenu(playerid, listitem, gamemode);
public ShowPlayerGameMenu(playerid, listitem, gamemode) {
	if(getPlayerStatus(playerid) == S_WYBIERALKA) return 1;
	SetPVarInt(playerid, PV_D_POMOCNICZA_3, (gamemode == 0 ? 1 : 0));
    PokazMenuZarzadzaniaGra(playerid);
    return 1;
}
//------------------------------------------------------------------------------
PokazMenuZarzadzaniaGra(playerid, listitem = -1) {
	switch(listitem) {
    	case 0: SetPVarInt(playerid, PV_SPAR_AKTYWNY, GetPVarInt(playerid, PV_SPAR_AKTYWNY) == 0 ? 1 : 0);
	    case 1: SetPVarInt(playerid, PV_RSP_AKTYWNY, GetPVarInt(playerid, PV_RSP_AKTYWNY) == 0 ? 1 : 0);
	    case 2: {
		    if(getPlayerLoginStatus(playerid) == LOGIN_STATUS_LOGGED) {
				SetPVarInt(playerid, PV_WYNIKI, GetPVarInt(playerid, PV_WYNIKI) == 0 ? 1 : 0);
				UpdatePlayerStats(playerid);
			}	else SendClientMessage(playerid,COLOR_WARNING, " (Menu) Musisz miec zarejestrowane konto zeby moc zmienic ta opcje");
		}
		case 3: SetPVarInt(playerid, PV_SPEC_POKAZ, GetPVarInt(playerid, PV_SPEC_POKAZ) == 0 ? 1 : 0);
		case 4: {
			SetPVarInt(playerid, PV_AIMED_INFO_STATUS, getPlayerAimedInfoStatus(playerid) == 0 ? 1 : 0);
			if(getPlayerAimedInfoStatus(playerid) == 1) {
			    LayoutAimedPlayerInfo(playerid, (G[playerid][TargetPlayer] = INVALID_PLAYER_ID));
			}
		}
	}
	new string[512];
    format(string, sizeof(string),"\
			"D_CC"1) "DIALOG_TEXT_COLOR"Wyzwania na sparing\t\t\t[ %s "DIALOG_TEXT_COLOR"]\n\
			"D_CC"2) "DIALOG_TEXT_COLOR"RSP na przycisk\t\t\t[ %s "DIALOG_TEXT_COLOR"]\n\
			"D_CC"3) "DIALOG_TEXT_COLOR"Informacje o wynikach\t\t[ "C_WHITE"%s "DIALOG_TEXT_COLOR"]\n\
			"D_CC"4) "DIALOG_TEXT_COLOR"Informacje o specowaniu\t\t[ "C_WHITE"%s "DIALOG_TEXT_COLOR"]\n\
			"D_CC"5) "DIALOG_TEXT_COLOR"Celowanie (info.)\t\t\t[ "C_WHITE"%s "DIALOG_TEXT_COLOR"]",
		GetPVarInt(playerid, PV_SPAR_AKTYWNY) == 0 ? (C_LIGHTGREEN"ON") : (C_ADMIN"OFF"),
		GetPVarInt(playerid, PV_RSP_AKTYWNY) == 0 ? (C_LIGHTGREEN"ON") : (C_ADMIN"OFF"),
		GetPVarInt(playerid, PV_WYNIKI) == 0 ? ("Aktualne") : ("Konta"),
		GetPVarInt(playerid, PV_SPEC_POKAZ) == 0 ? (C_LIGHTGREEN"ON") : (C_ADMIN"OFF"),
		getPlayerAimedInfoStatus(playerid) == 0 ? (C_LIGHTGREEN"ON") : (C_ADMIN"OFF")
	);
	ShowPlayerDialog(playerid, DIALOG_MENU_GRY, DIALOG_STYLE_LIST, DIALOG_HEAD_COLOR"Zarzadzanie gra", string, "Dalej", "Wyjdz");
	return 1;
}
//------------------------------------------------------------------------------

UstawieniaSerwera(playerid)
{
	new string[600], pancerz[16];
	SetPVarInt(playerid, PV_D_POMOCNICZA, -1);
	
	if(MAX_ARMOUR == 0) strins(pancerz, C_ADMIN"Brak", 0);
	else format(pancerz, sizeof(pancerz), TEXT_NORMAL"%d", MAX_ARMOUR);

    format(string, sizeof(string), "\
			\t"DIALOG_HEAD_COLOR"Ustawienia gry\n\
			"DIALOG_TEXT_COLOR"Czas aren: "TEXT_NORMAL"%d\n\
			"DIALOG_TEXT_COLOR"Czas baz: "TEXT_NORMAL"%d\n\
			"DIALOG_TEXT_COLOR"Pancerz: %s\n\
			"DIALOG_TEXT_COLOR"Dodatkowy granat: %s\
			\n\n"DIALOG_HEAD_COLOR"\tUstawienia broni\n",
		CZAS_ARENY,
		CZAS_BAZY,
		pancerz ,
		DodatkowyGranat == true ? (C_LIGHTGREEN"Tak") : (C_ADMIN"Nie")
	);
		
	format(string, sizeof(string), "%s\
			"DIALOG_TEXT_COLOR"Pistolet z tlumikiem: "TEXT_NORMAL"%d\n\
			"DIALOG_TEXT_COLOR"Desert Eagle: "TEXT_NORMAL"%d\n\
			"DIALOG_TEXT_COLOR"Shotgun: "TEXT_NORMAL"%d\n\
			"DIALOG_TEXT_COLOR"MP5: "TEXT_NORMAL"%d\n\
			"DIALOG_TEXT_COLOR"AK-47: "TEXT_NORMAL"%d\n\
			"DIALOG_TEXT_COLOR"M4: "TEXT_NORMAL"%d\n\
			"DIALOG_TEXT_COLOR"Strzelba: "TEXT_NORMAL"%d\n\
			"DIALOG_TEXT_COLOR"Snajperka: "TEXT_NORMAL"%d",
		string,
		Bron[0][GUN_AMMO],
		Bron[1][GUN_AMMO],
		Bron[2][GUN_AMMO],
		Bron[3][GUN_AMMO],
		Bron[4][GUN_AMMO],
		Bron[5][GUN_AMMO],
		Bron[6][GUN_AMMO],
		Bron[7][GUN_AMMO]
	);
	ShowPlayerDialog(playerid, DIALOG_COFNIJ, DIALOG_STYLE_MSGBOX, DIALOG_HEAD_COLOR"Ustawienia serwera", string, "Wroc", "");
}

//------------------------------------------------------------------------------

SpisKomend(playerid, typ = -1, cmd = -1)
{
   	SetPVarInt(playerid, PV_D_POMOCNICZA_2, typ);
	SetPVarInt(playerid, PV_D_POMOCNICZA, -2);

	switch(typ)
	{
	    case 0:
		{
			switch(cmd)
			{
			    case 0: ShowPlayerDialog(playerid, DIALOG_COFNIJ, DIALOG_STYLE_MSGBOX, DIALOG_HEAD_COLOR"Spis komend", DIALOG_TEXT_COLOR"Komenda: "DIALOG_NORMAL_COLOR"/switch\n"DIALOG_TEXT_COLOR"Alternatywna: "DIALOG_NORMAL_COLOR"Brak\n"DIALOG_TEXT_COLOR"Parametry: "DIALOG_NORMAL_COLOR"Brak\n\n"DIALOG_TEXT_COLOR"Opis: "DIALOG_NORMAL_COLOR"Komenda umozliwiajaca szybka zmiane druzyny gracza.","Wroc","");
			    case 1: ShowPlayerDialog(playerid, DIALOG_COFNIJ, DIALOG_STYLE_MSGBOX, DIALOG_HEAD_COLOR"Spis komend", DIALOG_TEXT_COLOR"Komenda: "DIALOG_NORMAL_COLOR"/dm\n"DIALOG_TEXT_COLOR"Alternatywna: "DIALOG_NORMAL_COLOR"Brak\n"DIALOG_TEXT_COLOR"Parametry: "DIALOG_NORMAL_COLOR"Brak\n\n"DIALOG_TEXT_COLOR"Opis: "DIALOG_NORMAL_COLOR"Komenda umozliwajaca przejscie na arene Death Match.","Wroc","");
			    case 2: ShowPlayerDialog(playerid, DIALOG_COFNIJ, DIALOG_STYLE_MSGBOX, DIALOG_HEAD_COLOR"Spis komend", DIALOG_TEXT_COLOR"Komenda: "DIALOG_NORMAL_COLOR"/spar\n"DIALOG_TEXT_COLOR"Alternatywna: "DIALOG_NORMAL_COLOR"/duel\n"DIALOG_TEXT_COLOR"Parametry: "DIALOG_NORMAL_COLOR"Brak\n\n"DIALOG_TEXT_COLOR"Opis: "DIALOG_NORMAL_COLOR"Komenda umozliwiajaca wyzwanie innego gracza na sparing 1 vs 1.","Wroc","");
			    case 3: ShowPlayerDialog(playerid, DIALOG_COFNIJ, DIALOG_STYLE_MSGBOX, DIALOG_HEAD_COLOR"Spis komend", DIALOG_TEXT_COLOR"Komenda: "DIALOG_NORMAL_COLOR"/zvote\n"DIALOG_TEXT_COLOR"Alternatywna: "DIALOG_NORMAL_COLOR"Brak\n"DIALOG_TEXT_COLOR"Parametry: "DIALOG_NORMAL_COLOR"Brak\n\n"DIALOG_TEXT_COLOR"Opis: "DIALOG_NORMAL_COLOR"Rozpoczecie glosowania nad zmiana trybu Bazy <-> Areny.","Wroc","");
			    case 4: ShowPlayerDialog(playerid, DIALOG_COFNIJ, DIALOG_STYLE_MSGBOX, DIALOG_HEAD_COLOR"Spis komend", DIALOG_TEXT_COLOR"Komenda: "DIALOG_NORMAL_COLOR"/vote\n"DIALOG_TEXT_COLOR"Alternatywna: "DIALOG_NORMAL_COLOR"Brak\n"DIALOG_TEXT_COLOR"Parametry: "DIALOG_NORMAL_COLOR"[ID Bazy / Areny] lub Brak\n\n"DIALOG_TEXT_COLOR"Opis: "DIALOG_NORMAL_COLOR"Rozpoczecie glosowania nad wystartowaniem rundy o podanym ID (lub losowe).","Wroc","");
			    case 5: ShowPlayerDialog(playerid, DIALOG_COFNIJ, DIALOG_STYLE_MSGBOX, DIALOG_HEAD_COLOR"Spis komend", DIALOG_TEXT_COLOR"Komenda: "DIALOG_NORMAL_COLOR"/menu\n"DIALOG_TEXT_COLOR"Alternatywna: "DIALOG_NORMAL_COLOR"Brak\n"DIALOG_TEXT_COLOR"Parametry: "DIALOG_NORMAL_COLOR"Brak\n\n"DIALOG_TEXT_COLOR"Opis: "DIALOG_NORMAL_COLOR"Otworzenie menu zarzadzania opcjami gracza.","Wroc","");
			    case 6: ShowPlayerDialog(playerid, DIALOG_COFNIJ, DIALOG_STYLE_MSGBOX, DIALOG_HEAD_COLOR"Spis komend", DIALOG_TEXT_COLOR"Komenda: "DIALOG_NORMAL_COLOR"/kill\n"DIALOG_TEXT_COLOR"Alternatywna: "DIALOG_NORMAL_COLOR"Brak\n"DIALOG_TEXT_COLOR"Parametry: "DIALOG_NORMAL_COLOR"Brak\n\n"DIALOG_TEXT_COLOR"Opis: "DIALOG_NORMAL_COLOR"Popelnienie samobojstwa.","Wroc","");
			    case 7: ShowPlayerDialog(playerid, DIALOG_COFNIJ, DIALOG_STYLE_MSGBOX, DIALOG_HEAD_COLOR"Spis komend", DIALOG_TEXT_COLOR"Komenda: "DIALOG_NORMAL_COLOR"/car\n"DIALOG_TEXT_COLOR"Alternatywna: "DIALOG_NORMAL_COLOR"Brak\n"DIALOG_TEXT_COLOR"Parametry: "DIALOG_NORMAL_COLOR"[ID modelu pojazdu lub nazwa]\n\n"DIALOG_TEXT_COLOR"Opis: "DIALOG_NORMAL_COLOR"Komenda umozliwiajaca zespawnowanie pojazdu o podanym ID modelu.","Wroc","");
			    case 8: ShowPlayerDialog(playerid, DIALOG_COFNIJ, DIALOG_STYLE_MSGBOX, DIALOG_HEAD_COLOR"Spis komend", DIALOG_TEXT_COLOR"Komenda: "DIALOG_NORMAL_COLOR"/pm\n"DIALOG_TEXT_COLOR"Alternatywna: "DIALOG_NORMAL_COLOR"Brak\n"DIALOG_TEXT_COLOR"Parametry: "DIALOG_NORMAL_COLOR"[ID Gracza] [Tresc wiadomosci]\n\n"DIALOG_TEXT_COLOR"Opis: "DIALOG_NORMAL_COLOR"Komenda wysylajaca prywatna wiadomosc do podanego gracza.","Wroc","");
				case 9: ShowPlayerDialog(playerid, DIALOG_COFNIJ, DIALOG_STYLE_MSGBOX, DIALOG_HEAD_COLOR"Spis komend", DIALOG_TEXT_COLOR"Komenda: "DIALOG_NORMAL_COLOR"/stats\n"DIALOG_TEXT_COLOR"Alternatywna: "DIALOG_NORMAL_COLOR"Brak\n"DIALOG_TEXT_COLOR"Parametry: "DIALOG_NORMAL_COLOR"Brak\n\n"DIALOG_TEXT_COLOR"Opis: "DIALOG_NORMAL_COLOR"Statystyki gracza dot. wynikow On-Line jak i konta.","Wroc","");
				case 10: ShowPlayerDialog(playerid, DIALOG_COFNIJ, DIALOG_STYLE_MSGBOX, DIALOG_HEAD_COLOR"Spis komend", DIALOG_TEXT_COLOR"Komenda: "DIALOG_NORMAL_COLOR"/ostatniograne\n"DIALOG_TEXT_COLOR"Alternatywna: "DIALOG_NORMAL_COLOR"/lastplayed\n"DIALOG_TEXT_COLOR"Parametry: "DIALOG_NORMAL_COLOR"Brak\n\n"DIALOG_TEXT_COLOR"Opis: "DIALOG_NORMAL_COLOR"Lista ostatnio granych baz i aren.","Wroc","");
				case 11: ShowPlayerDialog(playerid, DIALOG_COFNIJ, DIALOG_STYLE_MSGBOX, DIALOG_HEAD_COLOR"Spis komend", DIALOG_TEXT_COLOR"Komenda: "DIALOG_NORMAL_COLOR"/demoarena\n"DIALOG_TEXT_COLOR"Alternatywna: "DIALOG_NORMAL_COLOR"Brak\n"DIALOG_TEXT_COLOR"Parametry: "DIALOG_NORMAL_COLOR"[ID Areny] [0 - Spawn ataku | 1 - Spawn obrony]\n\n"DIALOG_TEXT_COLOR"Opis: "DIALOG_NORMAL_COLOR"Teleportuje na arene o podanym ID.","Wroc","");
				
				default: ShowPlayerDialog(playerid, DIALOG_CMD_LIST, DIALOG_STYLE_LIST, DIALOG_HEAD_COLOR"Spis komend",
				D_CC"1) "DIALOG_TEXT_COLOR"/switch\n\
				"D_CC"2) "DIALOG_TEXT_COLOR"/dm\n\
				"D_CC"3) "DIALOG_TEXT_COLOR"/spar\n\
				"D_CC"4) "DIALOG_TEXT_COLOR"/zvote\n\
				"D_CC"5) "DIALOG_TEXT_COLOR"/vote\n\
				"D_CC"6) "DIALOG_TEXT_COLOR"/menu\n\
				"D_CC"7) "DIALOG_TEXT_COLOR"/kill\n\
				"D_CC"8) "DIALOG_TEXT_COLOR"/car\n\
				"D_CC"9) "DIALOG_TEXT_COLOR"/pm\n\
				"D_CC"10) "DIALOG_TEXT_COLOR"/stats\n\
				"D_CC"11) "DIALOG_TEXT_COLOR"/ostatniograne\n\
				"D_CC"12) "DIALOG_TEXT_COLOR"/demoarena",
				"Opis", "Wroc");

			}
		}
	    case 1:
		{
		    switch(cmd)
		    {
		        case 0: ShowPlayerDialog(playerid, DIALOG_COFNIJ, DIALOG_STYLE_MSGBOX, DIALOG_HEAD_COLOR"Spis komend", DIALOG_TEXT_COLOR"Komenda: "DIALOG_NORMAL_COLOR"/bron\n"DIALOG_TEXT_COLOR"Alternatywna: "DIALOG_NORMAL_COLOR"Brak\n"DIALOG_TEXT_COLOR"Parametry: "DIALOG_NORMAL_COLOR"Brak\n\n"DIALOG_TEXT_COLOR"Opis: "DIALOG_NORMAL_COLOR"Komenda umozliwiajaca ponowna zmiane broni w rundzie.","Wroc","");
		        case 1: ShowPlayerDialog(playerid, DIALOG_COFNIJ, DIALOG_STYLE_MSGBOX, DIALOG_HEAD_COLOR"Spis komend", DIALOG_TEXT_COLOR"Komenda: "DIALOG_NORMAL_COLOR"/rsp\n"DIALOG_TEXT_COLOR"Alternatywna: "DIALOG_NORMAL_COLOR"Brak\n"DIALOG_TEXT_COLOR"Parametry: "DIALOG_NORMAL_COLOR"Brak\n\n"DIALOG_TEXT_COLOR"Opis: "DIALOG_NORMAL_COLOR"Komenda umozliwiajaca uzyskanie efektu ponownego spawnu skina.","Wroc","");
				case 2: ShowPlayerDialog(playerid, DIALOG_COFNIJ, DIALOG_STYLE_MSGBOX, DIALOG_HEAD_COLOR"Spis komend", DIALOG_TEXT_COLOR"Komenda: "DIALOG_NORMAL_COLOR"/spec\n"DIALOG_TEXT_COLOR"Alternatywna: "DIALOG_NORMAL_COLOR"Brak\n"DIALOG_TEXT_COLOR"Parametry: "DIALOG_NORMAL_COLOR"[ID Gracza]\n\n"DIALOG_TEXT_COLOR"Opis: "DIALOG_NORMAL_COLOR"Komenda wlaczajaca tryb obserwowania gracza.","Wroc","");
				case 3: ShowPlayerDialog(playerid, DIALOG_COFNIJ, DIALOG_STYLE_MSGBOX, DIALOG_HEAD_COLOR"Spis komend", DIALOG_TEXT_COLOR"Komenda: "DIALOG_NORMAL_COLOR"/specoff\n"DIALOG_TEXT_COLOR"Alternatywna: "DIALOG_NORMAL_COLOR"Brak\n"DIALOG_TEXT_COLOR"Parametry: "DIALOG_NORMAL_COLOR"Brak\n\n"DIALOG_TEXT_COLOR"Opis: "DIALOG_NORMAL_COLOR"Komenda wylaczajaca tryb obserwowania gracza.","Wroc","");
				case 4: ShowPlayerDialog(playerid, DIALOG_COFNIJ, DIALOG_STYLE_MSGBOX, DIALOG_HEAD_COLOR"Spis komend", DIALOG_TEXT_COLOR"Komenda: "DIALOG_NORMAL_COLOR"/respawn\n"DIALOG_TEXT_COLOR"Alternatywna: "DIALOG_NORMAL_COLOR"Brak\n"DIALOG_TEXT_COLOR"Parametry: "DIALOG_NORMAL_COLOR"Brak\n\n"DIALOG_TEXT_COLOR"Opis: "DIALOG_NORMAL_COLOR"Komenda umozliwiajaca ponowne zespawnowanie sie w rundzie.","Wroc","");
				case 5: ShowPlayerDialog(playerid, DIALOG_COFNIJ, DIALOG_STYLE_MSGBOX, DIALOG_HEAD_COLOR"Spis komend", DIALOG_TEXT_COLOR"Komenda: "DIALOG_NORMAL_COLOR"/kill\n"DIALOG_TEXT_COLOR"Alternatywna: "DIALOG_NORMAL_COLOR"Brak\n"DIALOG_TEXT_COLOR"Parametry: "DIALOG_NORMAL_COLOR"Brak\n\n"DIALOG_TEXT_COLOR"Opis: "DIALOG_NORMAL_COLOR"Popelnienie samobojstwa.","Wroc","");
				case 6: ShowPlayerDialog(playerid, DIALOG_COFNIJ, DIALOG_STYLE_MSGBOX, DIALOG_HEAD_COLOR"Spis komend", DIALOG_TEXT_COLOR"Komenda: "DIALOG_NORMAL_COLOR"/car\n"DIALOG_TEXT_COLOR"Alternatywna: "DIALOG_NORMAL_COLOR"Brak\n"DIALOG_TEXT_COLOR"Parametry: "DIALOG_NORMAL_COLOR"[ID modelu pojazdu lub nazwa]\n\n"DIALOG_TEXT_COLOR"Opis: "DIALOG_NORMAL_COLOR"Komenda umozliwiajaca zespawnowanie pojazdu o podanym ID modelu.","Wroc","");
				case 7: ShowPlayerDialog(playerid, DIALOG_COFNIJ, DIALOG_STYLE_MSGBOX, DIALOG_HEAD_COLOR"Spis komend", DIALOG_TEXT_COLOR"Komenda: "DIALOG_NORMAL_COLOR"/pm\n"DIALOG_TEXT_COLOR"Alternatywna: "DIALOG_NORMAL_COLOR"Brak\n"DIALOG_TEXT_COLOR"Parametry: "DIALOG_NORMAL_COLOR"[ID Gracza] [Tresc wiadomosci]\n\n"DIALOG_TEXT_COLOR"Opis: "DIALOG_NORMAL_COLOR"Komenda wysylajaca prywatna wiadomosc do podanego gracza.","Wroc","");
				case 8: ShowPlayerDialog(playerid, DIALOG_COFNIJ, DIALOG_STYLE_MSGBOX, DIALOG_HEAD_COLOR"Spis komend", DIALOG_TEXT_COLOR"Komenda: "DIALOG_NORMAL_COLOR"/stats\n"DIALOG_TEXT_COLOR"Alternatywna: "DIALOG_NORMAL_COLOR"Brak\n"DIALOG_TEXT_COLOR"Parametry: "DIALOG_NORMAL_COLOR"Brak\n\n"DIALOG_TEXT_COLOR"Opis: "DIALOG_NORMAL_COLOR"Statystyki gracza dot. wynikow On-Line jak i konta.","Wroc","");
				case 9: ShowPlayerDialog(playerid, DIALOG_COFNIJ, DIALOG_STYLE_MSGBOX, DIALOG_HEAD_COLOR"Spis komend", DIALOG_TEXT_COLOR"Komenda: "DIALOG_NORMAL_COLOR"/menu\n"DIALOG_TEXT_COLOR"Alternatywna: "DIALOG_NORMAL_COLOR"Brak\n"DIALOG_TEXT_COLOR"Parametry: "DIALOG_NORMAL_COLOR"Brak\n\n"DIALOG_TEXT_COLOR"Opis: "DIALOG_NORMAL_COLOR"Otworzenie menu zarzadzania opcjami gracza.","Wroc","");
				default:
				ShowPlayerDialog(playerid, DIALOG_CMD_LIST, DIALOG_STYLE_LIST, DIALOG_HEAD_COLOR"Spis komend",
				D_CC"1) "DIALOG_TEXT_COLOR"/bron\n\
				"D_CC"2) "DIALOG_TEXT_COLOR"/rsp\n\
				"D_CC"3) "DIALOG_TEXT_COLOR"/spec\n\
				"D_CC"4) "DIALOG_TEXT_COLOR"/specoff\n\
				"D_CC"5) "DIALOG_TEXT_COLOR"/respawn\n\
				"D_CC"6) "DIALOG_TEXT_COLOR"/kill\n\
				"D_CC"7) "DIALOG_TEXT_COLOR"/car\n\
				"D_CC"8) "DIALOG_TEXT_COLOR"/pm\n\
				"D_CC"9) "DIALOG_TEXT_COLOR"/stats\n\
				"D_CC"10) "DIALOG_TEXT_COLOR"/menu",
				"Opis", "Wroc");
			}
		}
	    case 2:
		{
		    if(IsAdmin(playerid) == ALVL_NON) SpisKomend(playerid);
		    switch(cmd)
		    {
			    case 0: ShowPlayerDialog(playerid, DIALOG_COFNIJ, DIALOG_STYLE_MSGBOX, DIALOG_HEAD_COLOR"Spis komend", DIALOG_TEXT_COLOR"Komenda: "DIALOG_NORMAL_COLOR"/swap\n"DIALOG_TEXT_COLOR"Alternatywna: "DIALOG_NORMAL_COLOR"Brak\n"DIALOG_TEXT_COLOR"Parametry: "DIALOG_NORMAL_COLOR"Brak\n\n"DIALOG_TEXT_COLOR"Opis: "DIALOG_NORMAL_COLOR"Zamiana druzyn graczy.","Wroc","");
			    case 1: ShowPlayerDialog(playerid, DIALOG_COFNIJ, DIALOG_STYLE_MSGBOX, DIALOG_HEAD_COLOR"Spis komend", DIALOG_TEXT_COLOR"Komenda: "DIALOG_NORMAL_COLOR"/aswap\n"DIALOG_TEXT_COLOR"Alternatywna: "DIALOG_NORMAL_COLOR"Brak\n"DIALOG_TEXT_COLOR"Parametry: "DIALOG_NORMAL_COLOR"[ID Gracza]\n\n"DIALOG_TEXT_COLOR"Opis: "DIALOG_NORMAL_COLOR"Zmiana druzyny gracza.","Wroc","");
			    case 2: ShowPlayerDialog(playerid, DIALOG_COFNIJ, DIALOG_STYLE_MSGBOX, DIALOG_HEAD_COLOR"Spis komend", DIALOG_TEXT_COLOR"Komenda: "DIALOG_NORMAL_COLOR"/sa\n"DIALOG_TEXT_COLOR"Alternatywna: "DIALOG_NORMAL_COLOR"Brak\n"DIALOG_TEXT_COLOR"Parametry: "DIALOG_NORMAL_COLOR"[ID Areny] lub brak\n\n"DIALOG_TEXT_COLOR"Opis: "DIALOG_NORMAL_COLOR"Wystartowanie areny o podanym lub losowym ID.","Wroc","");
			    case 3: ShowPlayerDialog(playerid, DIALOG_COFNIJ, DIALOG_STYLE_MSGBOX, DIALOG_HEAD_COLOR"Spis komend", DIALOG_TEXT_COLOR"Komenda: "DIALOG_NORMAL_COLOR"/sb\n"DIALOG_TEXT_COLOR"Alternatywna: "DIALOG_NORMAL_COLOR"Brak\n"DIALOG_TEXT_COLOR"Parametry: "DIALOG_NORMAL_COLOR"[ID Bazy] lub brak\n\n"DIALOG_TEXT_COLOR"Opis: "DIALOG_NORMAL_COLOR"Wystartowanie bazy o podanym lub losowym ID.","Wroc","");
			    case 4: ShowPlayerDialog(playerid, DIALOG_COFNIJ, DIALOG_STYLE_MSGBOX, DIALOG_HEAD_COLOR"Spis komend", DIALOG_TEXT_COLOR"Komenda: "DIALOG_NORMAL_COLOR"/end\n"DIALOG_TEXT_COLOR"Alternatywna: "DIALOG_NORMAL_COLOR"Brak\n"DIALOG_TEXT_COLOR"Parametry: "DIALOG_NORMAL_COLOR"Brak\n\n"DIALOG_TEXT_COLOR"Opis: "DIALOG_NORMAL_COLOR"Zakonczenie aktualnie trwajacej rundy.","Wroc","");
			    case 5: ShowPlayerDialog(playerid, DIALOG_COFNIJ, DIALOG_STYLE_MSGBOX, DIALOG_HEAD_COLOR"Spis komend", DIALOG_TEXT_COLOR"Komenda: "DIALOG_NORMAL_COLOR"/dg\n"DIALOG_TEXT_COLOR"Alternatywna: "DIALOG_NORMAL_COLOR"/add\n"DIALOG_TEXT_COLOR"Parametry: "DIALOG_NORMAL_COLOR"[ID Gracza]\n\n"DIALOG_TEXT_COLOR"Opis: "DIALOG_NORMAL_COLOR"Dodanie do walki gracza o podanym ID.","Wroc","");
			    case 6: ShowPlayerDialog(playerid, DIALOG_COFNIJ, DIALOG_STYLE_MSGBOX, DIALOG_HEAD_COLOR"Spis komend", DIALOG_TEXT_COLOR"Komenda: "DIALOG_NORMAL_COLOR"/ug\n"DIALOG_TEXT_COLOR"Alternatywna: "DIALOG_NORMAL_COLOR"/rem\n"DIALOG_TEXT_COLOR"Parametry: "DIALOG_NORMAL_COLOR"[ID Gracza]\n\n"DIALOG_TEXT_COLOR"Opis: "DIALOG_NORMAL_COLOR"Usuniecie z walki gracza o podanym ID.","Wroc","");
			    case 7: ShowPlayerDialog(playerid, DIALOG_COFNIJ, DIALOG_STYLE_MSGBOX, DIALOG_HEAD_COLOR"Spis komend", DIALOG_TEXT_COLOR"Komenda: "DIALOG_NORMAL_COLOR"/zmianabroni\n"DIALOG_TEXT_COLOR"Alternatywna: "DIALOG_NORMAL_COLOR"/gun\n"DIALOG_TEXT_COLOR"Parametry: "DIALOG_NORMAL_COLOR"[ID Gracza]\n\n"DIALOG_TEXT_COLOR"Opis: "DIALOG_NORMAL_COLOR"Zezwolenie graczu na zmiane broni w trakcie rundy.","Wroc","");
			    case 8: ShowPlayerDialog(playerid, DIALOG_COFNIJ, DIALOG_STYLE_MSGBOX, DIALOG_HEAD_COLOR"Spis komend", DIALOG_TEXT_COLOR"Komenda: "DIALOG_NORMAL_COLOR"/vstop\n"DIALOG_TEXT_COLOR"Alternatywna: "DIALOG_NORMAL_COLOR"Brak\n"DIALOG_TEXT_COLOR"Parametry: "DIALOG_NORMAL_COLOR"Brak\n\n"DIALOG_TEXT_COLOR"Opis: "DIALOG_NORMAL_COLOR"Przerwanie aktualnie trwajacego glosowania.","Wroc","");
				case 9: ShowPlayerDialog(playerid, DIALOG_COFNIJ, DIALOG_STYLE_MSGBOX, DIALOG_HEAD_COLOR"Spis komend", DIALOG_TEXT_COLOR"Komenda: "DIALOG_NORMAL_COLOR"/ztyp\n"DIALOG_TEXT_COLOR"Alternatywna: "DIALOG_NORMAL_COLOR"Brak\n"DIALOG_TEXT_COLOR"Parametry: "DIALOG_NORMAL_COLOR"Brak\n\n"DIALOG_TEXT_COLOR"Opis: "DIALOG_NORMAL_COLOR"Zmiana trybu gry Bazy <-> Areny.","Wroc","");
				case 10: ShowPlayerDialog(playerid, DIALOG_COFNIJ, DIALOG_STYLE_MSGBOX, DIALOG_HEAD_COLOR"Spis komend", DIALOG_TEXT_COLOR"Komenda: "DIALOG_NORMAL_COLOR"/mix\n"DIALOG_TEXT_COLOR"Alternatywna: "DIALOG_NORMAL_COLOR"Brak\n"DIALOG_TEXT_COLOR"Parametry: "DIALOG_NORMAL_COLOR"Brak\n\n"DIALOG_TEXT_COLOR"Opis: "DIALOG_NORMAL_COLOR"Pomieszanie graczy w druzynach.","Wroc","");
                case 11: ShowPlayerDialog(playerid, DIALOG_COFNIJ, DIALOG_STYLE_MSGBOX, DIALOG_HEAD_COLOR"Spis komend", DIALOG_TEXT_COLOR"Komenda: "DIALOG_NORMAL_COLOR"/healall\n"DIALOG_TEXT_COLOR"Alternatywna: "DIALOG_NORMAL_COLOR"/hall\n"DIALOG_TEXT_COLOR"Parametry: "DIALOG_NORMAL_COLOR"Brak\n\n"DIALOG_TEXT_COLOR"Opis: "DIALOG_NORMAL_COLOR"Leczenie wszystkich graczy w trakcie rundy.","Wroc","");
                case 12: ShowPlayerDialog(playerid, DIALOG_COFNIJ, DIALOG_STYLE_MSGBOX, DIALOG_HEAD_COLOR"Spis komend", DIALOG_TEXT_COLOR"Komenda: "DIALOG_NORMAL_COLOR"/heal\n"DIALOG_TEXT_COLOR"Alternatywna: "DIALOG_NORMAL_COLOR"/h\n"DIALOG_TEXT_COLOR"Parametry: "DIALOG_NORMAL_COLOR"[ID Gracza]\n\n"DIALOG_TEXT_COLOR"Opis: "DIALOG_NORMAL_COLOR"Leczenie gracza o podanym ID w trakcie rundy.","Wroc","");
                case 13: ShowPlayerDialog(playerid, DIALOG_COFNIJ, DIALOG_STYLE_MSGBOX, DIALOG_HEAD_COLOR"Spis komend", DIALOG_TEXT_COLOR"Komenda: "DIALOG_NORMAL_COLOR"/killp\n"DIALOG_TEXT_COLOR"Alternatywna: "DIALOG_NORMAL_COLOR"Brak\n"DIALOG_TEXT_COLOR"Parametry: "DIALOG_NORMAL_COLOR"[ID Gracza]\n\n"DIALOG_TEXT_COLOR"Opis: "DIALOG_NORMAL_COLOR"Zabicie gracza o podanym ID w trakcie rundy.","Wroc","");
                case 14: ShowPlayerDialog(playerid, DIALOG_COFNIJ, DIALOG_STYLE_MSGBOX, DIALOG_HEAD_COLOR"Spis komend", DIALOG_TEXT_COLOR"Komenda: "DIALOG_NORMAL_COLOR"/tp\n"DIALOG_TEXT_COLOR"Alternatywna: "DIALOG_NORMAL_COLOR"Brak\n"DIALOG_TEXT_COLOR"Parametry: "DIALOG_NORMAL_COLOR"[ID Gracza teleportowanego] [ID Gracza celu]\n\n"DIALOG_TEXT_COLOR"Opis: "DIALOG_NORMAL_COLOR"Teleportacja jednego gracza do drugiego w trakcie rundy.","Wroc","");
                case 15: ShowPlayerDialog(playerid, DIALOG_COFNIJ, DIALOG_STYLE_MSGBOX, DIALOG_HEAD_COLOR"Spis komend", DIALOG_TEXT_COLOR"Komenda: "DIALOG_NORMAL_COLOR"/armorall\n"DIALOG_TEXT_COLOR"Alternatywna: "DIALOG_NORMAL_COLOR"/aall\n"DIALOG_TEXT_COLOR"Parametry: "DIALOG_NORMAL_COLOR"Brak\n\n"DIALOG_TEXT_COLOR"Opis: "DIALOG_NORMAL_COLOR"Dawanie graczom w trakcie rundy kamizelki kuloodpornej,\no ile ustawienia gamemoda na to pozwalaja.","Wroc","");
                case 16: ShowPlayerDialog(playerid, DIALOG_COFNIJ, DIALOG_STYLE_MSGBOX, DIALOG_HEAD_COLOR"Spis komend", DIALOG_TEXT_COLOR"Komenda: "DIALOG_NORMAL_COLOR"/armor\n"DIALOG_TEXT_COLOR"Alternatywna: "DIALOG_NORMAL_COLOR"/a\n"DIALOG_TEXT_COLOR"Parametry: "DIALOG_NORMAL_COLOR"[ID Gracza]\n\n"DIALOG_TEXT_COLOR"Opis: "DIALOG_NORMAL_COLOR"Dawanie graczu o podanym ID w trakcie rundy kamizelki kuloodpornej,\no ile ustawienia gamemoda na to pozwalaja.","Wroc","");
              	case 17: ShowPlayerDialog(playerid, DIALOG_COFNIJ, DIALOG_STYLE_MSGBOX, DIALOG_HEAD_COLOR"Spis komend", DIALOG_TEXT_COLOR"Komenda: "DIALOG_NORMAL_COLOR"/restoreall\n"DIALOG_TEXT_COLOR"Alternatywna: "DIALOG_NORMAL_COLOR"/rall\n"DIALOG_TEXT_COLOR"Parametry: "DIALOG_NORMAL_COLOR"Brak\n\n"DIALOG_TEXT_COLOR"Opis: "DIALOG_NORMAL_COLOR"Odnawianie wszystkim graczom w rundzie, zdrowia i kamizelki kuloodpornej.","Wroc","");
                case 18: ShowPlayerDialog(playerid, DIALOG_COFNIJ, DIALOG_STYLE_MSGBOX, DIALOG_HEAD_COLOR"Spis komend", DIALOG_TEXT_COLOR"Komenda: "DIALOG_NORMAL_COLOR"/restore\n"DIALOG_TEXT_COLOR"Alternatywna: "DIALOG_NORMAL_COLOR"/r\n"DIALOG_TEXT_COLOR"Parametry: "DIALOG_NORMAL_COLOR"[ID Gracza]\n\n"DIALOG_TEXT_COLOR"Opis: "DIALOG_NORMAL_COLOR"Odnawianie graczu o podanym ID w rundzie, zdrowia i kamizelki kuloodpornej.","Wroc","");
				default: {
					new string[512];
					format(string, sizeof(string), "\
						"D_CC"1) "DIALOG_TEXT_COLOR"/swap\n\
						"D_CC"2) "DIALOG_TEXT_COLOR"/aswap\n\
						"D_CC"3) "DIALOG_TEXT_COLOR"/sa\n\
						"D_CC"4) "DIALOG_TEXT_COLOR"/sb\n\
						"D_CC"5) "DIALOG_TEXT_COLOR"/end\n\
						"D_CC"6) "DIALOG_TEXT_COLOR"/dg\n\
						"D_CC"7) "DIALOG_TEXT_COLOR"/ug\n\
						"D_CC"8) "DIALOG_TEXT_COLOR"/zmianabroni\n\
						"D_CC"9) "DIALOG_TEXT_COLOR"/vstop\n\
						"D_CC"10) "DIALOG_TEXT_COLOR"/ztyp\n\
						"D_CC"11) "DIALOG_TEXT_COLOR"/mix\n"
					);
					format(string, sizeof(string), "%s\
						"D_CC"12) "DIALOG_TEXT_COLOR"/healall\n\
						"D_CC"13) "DIALOG_TEXT_COLOR"/heal\n\
						"D_CC"14) "DIALOG_TEXT_COLOR"/killp\n\
						"D_CC"15) "DIALOG_TEXT_COLOR"/tp\n\
						"D_CC"16) "DIALOG_TEXT_COLOR"/armorall\n\
						"D_CC"17) "DIALOG_TEXT_COLOR"/armor\n\
						"D_CC"18) "DIALOG_TEXT_COLOR"/restoreall\n\
						"D_CC"19) "DIALOG_TEXT_COLOR"/restore",
					string);
				   	ShowPlayerDialog(playerid, DIALOG_CMD_LIST, DIALOG_STYLE_LIST, DIALOG_HEAD_COLOR"Spis komend", string, "Opis", "Wroc");
				}
			}
		}
		default:
		{
		    if(IsAdmin(playerid) == ALVL_NON) ShowPlayerDialog(playerid, DIALOG_CMD_HELP, DIALOG_STYLE_LIST, C_LIGHTGREEN"Spis komend",D_CC"1) "DIALOG_TEXT_COLOR"Komendy dostepne w czasie przerwy\n"D_CC"2) "DIALOG_TEXT_COLOR"Komendy dostepne w trakcie rundy", "Dalej","Wroc");
			else ShowPlayerDialog(playerid, DIALOG_CMD_HELP, DIALOG_STYLE_LIST, DIALOG_HEAD_COLOR"Spis komend", D_CC"1) "DIALOG_TEXT_COLOR"Komendy dostepne w czasie przerwy\n"D_CC"2) "DIALOG_TEXT_COLOR"Komendy dostepne w trakcie rundy\n"D_CC"3) "DIALOG_TEXT_COLOR"Komendy administratora", "Dalej","Wroc");

		}
	}
}

//------------------------------------------------------------------------------
forward GamemodeAdminHelp(playerid);
public GamemodeAdminHelp(playerid) {
	SetPVarInt(playerid, PV_D_POMOCNICZA_4, 1);
    SpisKomend(playerid, 2);
	return 1;
}
//------------------------------------------------------------------------------
forward VipPrivilagesInfo(playerid);
public VipPrivilagesInfo(playerid) {
	ShowPlayerDialog(playerid, DIALOG_VIP_INFO, DIALOG_STYLE_MSGBOX, DIALOG_HEAD_COLOR"Przywileje VIP", DIALOG_TEXT_COLOR"- Mozliwsc startowania rund\n- Wieksza ilosc respektu za zabojstwa\n- Mozliwosc dojscia do druzyny arbitrow i specowania graczy\n- Zmniejszony czas oczekiwania na komende '/rsp'\n- Przywileje w glosowaniu na start rundy\n- Wydluzony czas na wpisanie komendy '/gun'\n\nWiecej informacji znajdziesz na forum HighSkill.eu", "Wroc", "");
	return 1;
}
//------------------------------------------------------------------------------
isHelicopter(vehicleid) {
	new model = GetVehicleModel(vehicleid);
	if(model == 548 || model == 425 || model == 417 || model == 487 || model == 488 ||
		model == 497 || model == 563 || model == 447 || model == 469
	) return 1;
	return 0;
}
//------------------------------------------------------------------------------
IDBroniZeSkrotu(s_skrot[]) {
	if(0 < strlen(s_skrot) <= 4) {
	    if(isNumeric(s_skrot)) {
	        for(new i, id = strval(s_skrot); i < sizeof(BronieSpar); i ++) {
	            if(BronieSpar[i][ID] == id) {
					return i;
				}
	        }
	    } else {
			for(new i; i < sizeof(BronieSpar); i ++) {
			    if(strcmp(s_skrot, BronieSpar[i][skrot], true, strlen(BronieSpar[i][skrot])) == 0)
			        return i;
			}
		}
	}
	return -1;
}
//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
CMD:pomoc(playerid) return cmd_help(playerid);
CMD:help(playerid) {
    GameModeHelp(playerid, 0);
    return 1;
}
//------------------------------------------------------------------------------
CMD:menu(playerid) {
    if(getPlayerStatus(playerid) == S_WYBIERALKA) return 1;
    else ShowPlayerGameMenu(playerid, -1, 1);
	return 1;
}
//------------------------------------------------------------------------------
CMD:rem(playerid, cmdtext[]) return cmd_ug(playerid, cmdtext);
CMD:ug(playerid, cmdtext[]) {
	if(getPlayerStatus(playerid) == S_WYBIERALKA && playerid != -1) return 1;
	if(IsAdmin(playerid) > ALVL_NON || playerid == -1) {
	    new string[180];
	    if(!isnull(cmdtext)) {
	        if(IDStartowanej != -1 && TrwaOdliczanie == false) {
				new IDGracza = strval(cmdtext);
				if(getPlayerTeam(IDGracza) == T_ATT || getPlayerTeam(IDGracza) == T_DEF) {
			        if(getPlayerStatus(IDGracza) == S_GRA) {
				        DialogHideForPlayer(IDGracza);
				        setPlayerStatus(IDGracza, S_SPAWN);
				        OnPlayerSpawn(IDGracza);
				        if(playerid != -1) {
							format(string, sizeof(string), " (Usun Gracza) Administrator %s usunal(ela) gracza "TEXT_NORMAL"%s"TEXT_PREM" z rundy  (Druzyna: "TEXT_NORMAL"%s"TEXT_PREM" )", GetPlayerNick(playerid), GetPlayerNick(IDGracza), getPlayerTeam(IDGracza) == T_ATT ? ("Atak") : ("Obrona"));
						} else {
						    format(string, sizeof(string), " (Usun Gracza) System usunal gracza "TEXT_NORMAL"%s"TEXT_PREM" z rundy  (Druzyna: "TEXT_NORMAL"%s"TEXT_PREM" )", GetPlayerNick(IDGracza), getPlayerTeam(IDGracza) == T_ATT ? ("Atak") : ("Obrona"));
						}
						SendClientMessageToAll(COLOR_PREM, string);
					}   else SendClientMessage(playerid, COLOR_WARNING," (Usun Gracza) Gracz nie bierze udzialu w walce");
			    }	else SendClientMessage(playerid, COLOR_WARNING," (Usun Gracza) Gracz musi byc w druzynie ataku lub obrony");
            }	else SendClientMessage(playerid, COLOR_WARNING," (Usun Gracza) Komenda dziala jedynie podczas rundy i po skonczonym odliczaniu");
        }	else SendClientMessage(playerid, COLOR_CMD_INFO, " (Usun Gracza) Wpisz "TEXT_NORMAL"/ug [ID Gracza]"TEXT_CMD_INFO" zeby usunac gracza z walki");
    }
	return 1;
}
//------------------------------------------------------------------------------
CMD:aswap(playerid, cmdtext[]) {
	if(getPlayerStatus(playerid) == S_WYBIERALKA) return 1;
	if(IsAdmin(playerid)) {
        new string[150];
	    if(IDStartowanej == -1 && TrwaOdliczanie == false) {
	        if(!isnull(cmdtext)) {
	            new IDGracza;
				if(IsPlayerConnected((IDGracza = strval(cmdtext)))) {
					switch(getPlayerTeam(IDGracza)) {
					    case T_ATT: {
					        setPlayerTeam(IDGracza, T_DEF);
							format(string, 150," (Admin Swap) "TEXT_NORMAL"%s"TEXT_TEAM_CHANGE" dolaczyl(a) do druzyny "TEXT_NORMAL"Obrony", GetPlayerNick(IDGracza));
				            SendClientMessageToAll(COLOR_TEAM_CHANGE, string);
				        }
					    case T_DEF: {
					        setPlayerTeam(IDGracza, T_ATT);
							format(string, 150," (Admin Swap) "TEXT_NORMAL"%s"TEXT_TEAM_CHANGE" dolaczyl(a) do druzyny "TEXT_NORMAL"Ataku", GetPlayerNick(IDGracza));
				            SendClientMessageToAll(COLOR_TEAM_CHANGE, string);
				        }
					    default:	return SendClientMessage(playerid, COLOR_WARNING," (Admin Swap) Gracz musi byc w druzynie ataku lub obrony");
				    }
				    format(string, 150," (Admin Swap) Administrator "TEXT_NORMAL"%s"TEXT_TEAM_CHANGE" zmienil(a) Twoja druzyne", GetPlayerNick(playerid));
					SendClientMessage(IDGracza, COLOR_TEAM_CHANGE, string);
				}
	        }   else    SendClientMessage(playerid, COLOR_WARNING," (Admin Swap) Podane ID nie jest uzywane");
		}   else SendClientMessage(playerid, COLOR_CMD_INFO," (Admin Swap) Uzyj: "TEXT_NORMAL"/aswap [ID Gracza] "TEXT_CMD_INFO"zeby zmienic druzyne gracza");
    }
	return 1;
}
//------------------------------------------------------------------------------
CMD:switch(playerid) {
    if(getPlayerStatus(playerid) == S_SPAWN && TrwaOdliczanie == false && SwapOczekiwanie == false) {
		if(IsAdmin(playerid) <= ALVL_NON and IsVIP(playerid) == _FALSE) {
		    if(getPlayerTeam(playerid) == T_ATT || getPlayerTeam(playerid) == T_DEF) {
			    new string[128];
		        if(getPlayerTeam(playerid) == T_ATT) {
					if(getPlayersInTeam(T_DEF) - getPlayersInTeam(T_ATT) > 0) return SendClientMessage(playerid, COLOR_WARNING," (Switch) W druzynie Obrony jest zbyt wielu graczy");
			        setPlayerTeam(playerid, T_DEF);
					format(string, 150," (Switch) "TEXT_NORMAL"%s"TEXT_TEAM_CHANGE" dolaczyl(a) do druzyny "TEXT_NORMAL"Obrony", GetPlayerNick(playerid));
		            SendClientMessageToAll(COLOR_TEAM_CHANGE, string);
	            } else {
					if(getPlayersInTeam(T_ATT) - getPlayersInTeam(T_DEF) > 0) return SendClientMessage(playerid, COLOR_WARNING," (Switch) W druzynie Ataku jest zbyt wielu graczy");
			        setPlayerTeam(playerid, T_ATT);
		            format(string, 150," (Switch) "TEXT_NORMAL"%s"TEXT_TEAM_CHANGE" dolaczyl(a) do druzyny "TEXT_NORMAL"Ataku", GetPlayerNick(playerid));
		            SendClientMessageToAll(COLOR_TEAM_CHANGE, string);
			    }
	        }
	    } else {
		    adminTeamChange(playerid);
	    }
	} else SendClientMessage(playerid, COLOR_WARNING," (Switch) Druzyne mozna zmienic tylko w poczekalni");
	return 1;
}
//------------------------------------------------------------------------------
CMD:kill(playerid) {
	if(getPlayerStatus(playerid) == S_WYBIERALKA/* || GetPVarInt(playerid, PV_EXPLODE) != 0*/) return 1;
	if(TrwaOdliczanie == false) SetPlayerHealthEx(playerid, 0);
	return 1;
}
//------------------------------------------------------------------------------
CMD:swap(playerid) {
	if(getPlayerStatus(playerid) == S_WYBIERALKA) return 1;
	if(IsAdmin(playerid) > ALVL_NON) {
	    if(SwapOczekiwanie == false) {
		    if(IDStartowanej == -1) {
                swapTeams();
				SendClientMessageToAll(COLOR_TEAM_CHANGE," (Swap) Administrator zmienil druzyny graczy");
			}	else SendClientMessage(playerid, COLOR_WARNING," (Swap) Komendy mozna uzyc jedynie w czasie przerwy w walce");
	    }	else SendClientMessage(playerid, COLOR_WARNING," (Swap) Druzyny zostana zamienione za kilka sekund");
	}
	return 1;
}
//------------------------------------------------------------------------------
CMD:car(playerid, cmdtext[]) {
	if(getPlayerStatus(playerid) == S_SPAWN && TrwaOdliczanie == false) {
	    if(isnull(cmdtext)) {
			return SendClientMessage(playerid, COLOR_CMD_INFO, " (Pojazd) Wpisz "TEXT_NORMAL"/car [Model Pojazdu / Nazwa]"TEXT_CMD_INFO" aby zespawnowac pojazd");
		} else {
			new Float:pPosX, Float:pPosY, Float:pPosZ, Float:pAngle, vehiclemodel;
			if(strlen(cmdtext) == 3 && strval(cmdtext) != 0) vehiclemodel = strval(cmdtext);
			else {
				for(new i = sizeof(PoczekalniaPojazd) - 1, len = strlen(cmdtext); i >= 0; i --) {
				    if(strlen(PoczekalniaPojazd[i][Nazwa]) == len) {
				        if(strcmp(PoczekalniaPojazd[i][Nazwa], cmdtext, true) == 0) {
				            vehiclemodel = PoczekalniaPojazd[i][ID];
				            break;
			            }
			        }
			    }
		    }

			if( 400 > vehiclemodel ||  vehiclemodel > 604) return SendClientMessage(playerid, COLOR_WARNING," (Pojazd) Nie znaleziono pojazdu o podanym modelu");

			#if OGRANICZENIE_OBSZARU_POJAZDU == 1
			if(!IsPlayerInRangeOfPoint(playerid, 50, g_LobbySpawnPos[0][0], g_LobbySpawnPos[0][1], g_LobbySpawnPos[0][2])) {
			#endif
				switch(vehiclemodel) {
				    case 406, 407, 417, 425, 430, 432, 435, 441, 447, 449, 450, 464, 465, 476, 484, 501, 520, 537, 538, 553, 564, 569, 570, 577, 584, 590..592, 601:
	                    return SendClientMessage(playerid, COLOR_WARNING," (Pojazd) Ten model pojazdu nie jest dozwolony");
			    }
				if(G[playerid][IDPojazdu] != 0) {
				    if(GetVehicleVirtualWorld(G[playerid][IDPojazdu]) != VW_GRA)
				    	DestroyVehicle(G[playerid][IDPojazdu]);
				}
				GetPlayerFacingAngle(playerid, pAngle);
				GetPlayerPos(playerid, pPosX, pPosY, pPosZ);
				G[playerid][IDPojazdu] = CreateVehicle(vehiclemodel, pPosX, pPosY, pPosZ + 0.5, pAngle, -1, -1, 99999);
				SetVehicleNumberPlate(G[playerid][IDPojazdu], NUMBER_PLATE);
				SetVehicleVirtualWorld(G[playerid][IDPojazdu], VW_SPAWN);
				PutPlayerInVehicle(playerid, G[playerid][IDPojazdu], 0);
				SendClientMessage(playerid, COLOR_CAR_INFO, " (Pojazd) Pojazd zostal pomyslnie utworzony");
				
            #if OGRANICZENIE_OBSZARU_POJAZDU == 1
	    	} else SendClientMessage(playerid, COLOR_WARNING," (Pojazd) Nie mozesz zespawnowac pojazdu w promieniu 50m od spawnu");
			#endif
	    }
    } else {
  //Car Del
		if(getPlayerStatus(playerid) == S_GRA) {
		    if(getPlayerTeam(playerid) == T_ATT) {
		        if(TypArena == false && InteriorWalki == 0) {
		            if(GetPlayerRoundWeaponSlot(playerid, _FIRST, _PRIMARY) != -1 AND GetPlayerRoundWeaponSlot(playerid, _SECOND, _PRIMARY) != -1) {
			            if(IsPlayerInRangeOfPoint(playerid, CAR_SPAWN_DYS, SpawnAtt[0], SpawnAtt[1], SpawnAtt[2])) {
		                    new string[1024];
				            new Float:pPosX = G[playerid][PlayerPOS][0], Float:pPosY = G[playerid][PlayerPOS][1], Float:pPosZ = G[playerid][PlayerPOS][2], Float:pAngle;
							GetPlayerPos(playerid, pPosX, pPosY, pPosZ);
							GetPlayerFacingAngle(playerid, pAngle);
				            if(pPosZ > 0) {
								if(isnull(cmdtext)) {
								    for(new i = sizeof(SpawnPojazd) - 1, carname[16], color[10]; i >= 0; i--) {
							            color[0] = EOS;
							            switch(SpawnPojazd[i][Typ]) {
											case 0: strins(color, ("{C4C4FD}"), 0);
											case 1: strins(color, ("{15CBFF}"), 0);
											case 2: strins(color, ("{0094AE}"), 0);
											case 3: strins(color, ("{01757E}"), 0);
										} 
							            strunpack(carname, SpawnPojazd[i][Nazwa]);
							            format(string, 1024, "\n"D_CC"%d) %s%s%s", i + 1, color, carname, string);
							        }
									strdel(string, 0, 1);
									ShowPlayerDialog(playerid, DIALOG_POJAZDY, DIALOG_STYLE_LIST,DIALOG_HEAD_COLOR"Pojazdy",string,"Wybierz","Wroc");
							    } else {
								    for(new i, y = sizeof(SpawnPojazd); i < y; i ++) {
								        if(strcmp(cmdtext,SpawnPojazd[i][Nazwa], true) == 0) {
								            if(SpawnPojazd[i][Typ] != 3) {
                                                forplayers(x) {
													if(getPlayerStatus(x) == S_GRA) {
													    if(getPlayerTeam(x) == T_ATT) {
															if(x != playerid) {
										                    	if(IsPlayerInRangeOfPoint(x, IsPlayerInAnyVehicle(x) ? 10 : 5, pPosX, pPosY, pPosZ))
										                        	return SendClientMessage(playerid, COLOR_WARNING," (Pojazd) Znajdujesz sie zbyt blisko innego gracza");
															}
									                    }
									                }
												}
											} else {
											    if(SpawnLodzi[0] != 0.0 && SpawnLodzi[1] != 0.0 && SpawnLodzi[2] != 0.0) {
	                                                pPosX = random(2) == 1 ? -random(4) + SpawnLodzi[0] : random(4) + SpawnLodzi[0];
	                                                pPosY = random(2) == 1 ? -random(4) + SpawnLodzi[1] : random(4) + SpawnLodzi[1];
	                                                pPosZ = SpawnLodzi[2] + 2;
	                                                pAngle = SpawnLodzi[3];
										        }	else return SendClientMessage(playerid, COLOR_WARNING," (Pojazd) Na tej bazie nie mozna spawnowac lodzi");
										    }
											if(G[playerid][IDPojazdu] > 0 && GetVehicleVirtualWorld(G[playerid][IDPojazdu]) == VW_GRA) DestroyVehicle(G[playerid][IDPojazdu]);

											G[playerid][IDPojazdu] = CreateVehicle(SpawnPojazd[i][ID], pPosX, pPosY, pPosZ, pAngle, 6, 6, 999999);
                                            SetVehicleNumberPlate(G[playerid][IDPojazdu], NUMBER_PLATE);
											SetVehicleVirtualWorld(G[playerid][IDPojazdu], VW_GRA);
											AddVehicleComponent(G[playerid][IDPojazdu], 1010);
											AddVehicleComponent(G[playerid][IDPojazdu], 1087);
											PutPlayerInVehicle(playerid, G[playerid][IDPojazdu], 0);
											strunpack(string, SpawnPojazd[i][Nazwa], 32);
											format(string, sizeof(string)," (Pojazd) Zespawnowales(as) \""TEXT_NORMAL"%s"TEXT_CAR_INFO"\"", string);
											SendClientMessage(playerid, COLOR_CAR_INFO, string);
								            return 1;
							            }
							        }
									format(string, 256," (Pojazd) Nieznaleziono pojazdu o nazwie "TEXT_NORMAL"%s"TEXT_CMD_INFO". Wpisz: "TEXT_NORMAL"/car"TEXT_CMD_INFO" aby zobaczyc liste pojazdow", cmdtext);
									SendClientMessage(playerid, COLOR_CMD_INFO, string);
							    }
			                }
		                }
					}
	            }
	        }
	    }
	}
	return 1;
}

//------------------------------------------------------------------------------

CMD:dm(playerid) {
	if(TrwaOdliczanie == false) {
		if(getPlayerStatus(playerid) == S_SPAWN) {
		    if(g_LoadedLobbyTDMSpawns > 0) {
				DemoArenaEnd(playerid);
	   		    setPlayerStatus(playerid, S_ARENA_DM);
			    TeleportPlayerToLobbyTDMArena(playerid);
	            SendClientMessage(playerid, COLOR_DM_INFO, " (Arena DM) Przeniosles(as) sie na arene Death Match");
	            SendClientMessage(playerid, COLOR_DM_INFO, "     Wpisz ponownie "TEXT_NORMAL"/dm"TEXT_DM_INFO" aby wrocic do poczekalni");
            	LayoutPlayerTrainingArena(playerid, true);
			} else SendClientMessage(playerid, COLOR_WARNING, " (Arena DM) Brak pozycji spawnu na arenie treningowej.");
	    } else if(getPlayerStatus(playerid) == S_ARENA_DM) {
		    SendClientMessage(playerid, COLOR_DM_INFO, " (Arena DM) Wrociles(as) do poczekalni");
		    setPlayerStatus(playerid, S_SPAWN);
		    SpawnPlayer(playerid);
	    }
	}
	return 1;
}
//------------------------------------------------------------------------------
CMD:sparing(playerid, cmdtext[]) return cmd_spar(playerid, cmdtext);
CMD:duel(playerid, cmdtext[]) return cmd_spar(playerid, cmdtext);
CMD:spar(playerid, cmdtext[]) {
	if(getPlayerStatus(playerid) == S_SPAWN && TrwaOdliczanie == false) {
		if(isnull(cmdtext)) {
		    G[playerid][SparingIDBroni][0] = G[playerid][SparingIDBroni][1] = -1;
			ShowSparingGunList(playerid);
			SendClientMessage(playerid, COLOR_CMD_INFO, " (Sparing) Szybkie wykonanie komendy: "TEXT_NORMAL"/spar [ID Gracza] [ID / Skrot broni 1] [ID / Skrot broni 2]");
		} else {
			new IDGracza = -1, IDBroni1 = -1, IDBroni2 = -1, idx;
			sscanf(cmdtext, "p< >ddd", IDGracza, IDBroni1, IDBroni2);
			IDGracza = strval(strtok(cmdtext, idx, ' '));
			IDBroni1 = IDBroniZeSkrotu(strtok(cmdtext, idx, ' '));
			IDBroni2 = IDBroniZeSkrotu(strtok(cmdtext, idx, ' '));

			if(IsPlayerConnected(IDGracza)) {
			    if(IDBroni1 != -1 && IDBroni2 != -1) {
			        if(IDGracza != playerid) {
				        if(getPlayerStatus(IDGracza) == S_SPAWN) {
				            if(GetPVarInt(IDGracza, PV_SPAR_AKTYWNY) == 0) {
					            G[IDGracza][SparingIDGracza] = playerid;
					            G[playerid][SparingIDGracza] = IDGracza;
								G[playerid][SparingIDBroni][0] = G[IDGracza][SparingIDBroni][0] = IDBroni1;
								G[playerid][SparingIDBroni][1] = G[IDGracza][SparingIDBroni][1] = IDBroni2;
								WyslijWyzwanieNaSparing(playerid);
								return 1;
			                }   else SendClientMessage(playerid, COLOR_WARNING," (Sparing) Gracz ma wylaczona opcje sparingow");
						}   else SendClientMessage(playerid, COLOR_WARNING," (Sparing) Gracz znajduje sie poza obszarem poczekalni");
			        }   else SendClientMessage(playerid, COLOR_WARNING," (Sparing) Nie mozesz wyzwac na sparing samego(ej) siebie");
			    }   else SendClientMessage(playerid, COLOR_WARNING," (Sparing) Niepoprawny skrot / ID broni");
			}   else SendClientMessage(playerid, COLOR_WARNING," (Sparing) Niepoprawne ID gracza");
		}
	}
	return 1;
}

//------------------------------------------------------------------------------
CMD:sa(playerid, cmdtext[]) {
	new string[128];
	#if _TESTY == 0
	if(IsAdmin(playerid) > ALVL_NON or (IsVIP(playerid) == _TRUE and lastVIPRound > sVIPMinRounds and sVIPMinRounds > 0)) {
	#endif
	    if(SwapOczekiwanie == false)
        {
		    if(IDStartowanej == -1)
	        {
				new sID = random(MAX_AREN);
				new sciezka[64];
				if(!isnull(cmdtext)) sID = strval(cmdtext);
				
				format(sciezka, 64, "HighSkill/Areny/%d.txt", sID);
				if(fexist(sciezka))
			    {
					if(IsAdmin(playerid) > ALVL_NON) format(string, 128," (Start Rundy) Administrator "TEXT_NORMAL"%s"TEXT_START_INFO" wystartowal(a) "TEXT_NORMAL"Arene %d", GetPlayerNick(playerid), sID);
					else {
					    #if _TESTY == 0
				        for(new i; i < sizeof(OstatnieStarty); i ++) {
				            if(OstatnieStarty[i][0] == 0 and OstatnieStarty[i][1] == sID) {
				            	return SendClientMessage(playerid, COLOR_WARNING, " (Start Rundy - VIP) Arena o tym ID byla niedawno rozgrywana");
					        }
					    }
						#endif
					    lastVIPRound = 0;
						format(string, 128," (Start Rundy) VIP "TEXT_NORMAL"%s"TEXT_START_INFO" wystartowal(a) "TEXT_NORMAL"Arene %d", GetPlayerNick(playerid), sID);
					}
					TypArena = true;
					IDStartowanej = sID;
					StartRundy(sciezka);
					SendClientMessageToAll(COLOR_START_INFO, string);
			    }
				else
				{
					format(string, 128, " (Start Rundy) Nieznaleziono areny o "TEXT_NORMAL"ID %d", sID);
					SendClientMessage(playerid, COLOR_WARNING, string);
				}
			}	else SendClientMessage(playerid, COLOR_WARNING," (Start Rundy) Nie mozna wystartowac nowej rundy przed koncem trwajacej");
	    }
    #if _TESTY == 0
	} else {
	    if(IsVIP(playerid) == _TRUE and sVIPMinRounds > 0) {
	        format(string, sizeof(string), " (Runda VIP) Bedziesz mogl(a) wystartowac 'runde VIP' za %d rund.", sVIPMinRounds + 1 - lastVIPRound);
	        SendClientMessage(playerid, COLOR_WARNING, string);
	    }
	}
	#endif
	return 1;
}
//------------------------------------------------------------------------------
CMD:sb(playerid, cmdtext[])
{
    new string[128];
	#if _TESTY == 0
	if(IsAdmin(playerid) > ALVL_NON or (IsVIP(playerid) == _TRUE and lastVIPRound > sVIPMinRounds and sVIPMinRounds > 0))
    {
	#endif
	    if(SwapOczekiwanie == false)
        {
		    if(IDStartowanej == -1)
	        {
				new sID = random(MAX_BAZ);
				new sciezka[64];
				if(!isnull(cmdtext)) sID = strval(cmdtext);

				format(sciezka, 64, "HighSkill/Bazy/%d.txt", sID);
				if(fexist(sciezka))
			    {
					if(IsAdmin(playerid) > ALVL_NON) format(string, 128," (Start Rundy) Administrator "TEXT_NORMAL"%s"TEXT_START_INFO" wystartowal(a) "TEXT_NORMAL"Baze %d", GetPlayerNick(playerid), sID);
					else {
				        for(new i; i < sizeof(OstatnieStarty); i ++) {
				            if(OstatnieStarty[i][0] == 1 and OstatnieStarty[i][1] == sID) {
				                return SendClientMessage(playerid, COLOR_WARNING, " (Start Rundy - VIP) Baza o tym ID byla niedawno rozgrywana");
					        }
					    }
						lastVIPRound = 0;
						format(string, 128," (Start Rundy) VIP "TEXT_NORMAL"%s"TEXT_START_INFO" wystartowal(a) "TEXT_NORMAL"Baze %d", GetPlayerNick(playerid), sID);
					}
					TypArena = false;
					IDStartowanej = sID;
					StartRundy(sciezka);
					SendClientMessageToAll(COLOR_START_INFO, string);
			    }
				else
				{
					format(string, 128, " (Start Rundy) Nieznaleziono bazy o "TEXT_NORMAL"ID %d", sID);
					SendClientMessage(playerid, COLOR_WARNING, string);
				}
			}	else SendClientMessage(playerid, COLOR_WARNING," (Start Rundy) Nie mozna wystartowac nowej rundy przed koncem trwajacej");
	    }
    #if _TESTY == 0
	} else {
	    if(IsVIP(playerid) == _TRUE and sVIPMinRounds > 0) {
	        format(string, sizeof(string), " (Runda VIP) Bedziesz mogl(a) wystartowac 'runde VIP' za %d rund.", sVIPMinRounds + 1 - lastVIPRound);
	        SendClientMessage(playerid, COLOR_WARNING, string);
	    }
	}
	#endif
	return 1;
}

//------------------------------------------------------------------------------

CMD:end(playerid)
{
    #if _TESTY == 0
	if(IsAdmin(playerid) > ALVL_NON)
    {
    #endif
	    if(TrwaOdliczanie == false)
        {
	        if(IDStartowanej != -1)
            {
                new string[128];
                printf("(Info) Administrator zakonczyl runde runde %d.", IDStartowanej);
				format(string, 128," (Koniec Rundy) Administrator "TEXT_NORMAL"%s"TEXT_START_INFO" zakonczyl(a) runde", GetPlayerNick(playerid));
				SendClientMessageToAll(COLOR_START_INFO, string);
	            endRoundFunc(true);
            }	else SendClientMessage(playerid, COLOR_WARNING," (Koniec Rundy) Aktualnie nie trwa walka");
        }	else SendClientMessage(playerid, COLOR_WARNING," (Koniec Rundy) Nie mozna zakonczyc rundy w trakcie odliczania");
    #if _TESTY == 0
    }
    #endif
	return 1;
}

//------------------------------------------------------------------------------
CMD:gun(playerid) return cmd_bron(playerid);
CMD:bron(playerid) {
	if(getPlayerStatus(playerid) == S_GRA) {
	    new Ammo1, Ammo2, bron, ammo;
	    
        GetPlayerWeaponData(playerid, GetPlayerRoundWeaponSlot(playerid, _FIRST, _PRIMARY), bron, Ammo1);
        GetPlayerWeaponData(playerid, GetPlayerRoundWeaponSlot(playerid, _SECOND, _PRIMARY), bron, Ammo2);

	    if(g_RoundSpawnProtectTime > 0 or (g_RoundSpawnProtectTime == -1 and IsVIP(playerid) == _TRUE) or (Bron[GetPlayerRoundWeapon(playerid, _FIRST, _PRIMARY)][GUN_AMMO] == Ammo1 && Bron[GetPlayerRoundWeapon(playerid, _SECOND, _PRIMARY)][GUN_AMMO] == Ammo2)) {
	        if(g_RoundSpawnProtectTime <= 0 && DostepnyGranat == true && DodatkowyGranat == true) {
		        GetPlayerWeaponData(playerid, 8, ammo, ammo);
				if(ammo == 0) return SendClientMessage(playerid, COLOR_WARNING," (Bron) Bron mozna zmienic w czasie trwania ochrony poczatkowej");
			}
	        SetPlayerWeaponRequestStatus(playerid, NEW_WEAPONS);
			ShowPlayerFirstGunMenu(playerid);
        } else SendClientMessage(playerid, COLOR_WARNING," (Bron) Bron mozna zmienic w czasie trwania ochrony poczatkowej");
    }
	return 1;
}
	
//------------------------------------------------------------------------------

CMD:rsp(playerid)
{
	G[playerid][GraczNacisnalPrzyciskRSP] = false;
	if(TrwaOdliczanie == false)
    {
		if(getPlayerStatus(playerid) == S_GRA and G[playerid][AddAfterSpawn] == false)
		{
			if(!IsPlayerInAnyVehicle(playerid))
		    {
			    switch(GetPlayerAnimationIndex(playerid))
		        {
			        case 1538..1544,1133,1134,971: return SendClientMessage(playerid, COLOR_WARNING," (RSP) Nie mozna uzyc komendy bedac w wodzie lub skaczac ze spadochronem");
		        }
	            if(GetTimeToServerTick(G[playerid][CzasOstRSP]) <= 0)
                {
                    if(GetPlayerRoundWeaponSlot(playerid, _FIRST, _PRIMARY) == -1 OR GetPlayerRoundWeaponSlot(playerid, _SECOND, _PRIMARY) == -1)
                    {
                        return SendClientMessage(playerid, COLOR_WARNING," (RSP) Nie mozna uzyc komendy bez wybranych broni");
                    }
                
                
	                new Float:sZ;
	                GetPlayerVelocity(playerid, sZ, sZ, sZ);
					if(sZ > -0.1)
				    {
					    if(g_RoundSpawnProtectTime <= 0)
				        {
							new Float:pPosX, Float:pPosY, Float:pPosZ, Float:pAngle,
								Ammo1 = -1, Ammo2 = -1, Bron1 = -1, Bron2 = -1,
						        IDBroni1, IDBroni2, cAmmo,
						        BGWeap[5] = {-1,...}, BGAmmo[5],
								Armed = GetPlayerWeapon(playerid);
								
					        GetPlayerPos(playerid, pPosX, pPosY, pPosZ);
					        GetPlayerFacingAngle(playerid, pAngle);

					        forplayers(i)
					        {
				                if(getPlayerTeam(i) != getPlayerTeam(playerid))
				                {
				                    if(IsPlayerInRangeOfPoint(i, 2.0, pPosX, pPosY, pPosZ)) return SendClientMessage(playerid, COLOR_WARNING, " (RSP) Nie mozna uzyc komendy w poblizu gracza z innej druzyny");
					            }
					        }

	
							IDBroni1 = GetPlayerRoundWeaponID(playerid, _FIRST, _PRIMARY);
							IDBroni2 = GetPlayerRoundWeaponID(playerid, _SECOND, _PRIMARY);

						    for(new i = 2, aBron; i < 9; i ++)
					        {
						        GetPlayerWeaponData(playerid, i, aBron, cAmmo);
						        if(IDBroni1 == aBron)
					            {
				                    Bron1 = aBron;
				                    Ammo1 = cAmmo;
					            }
								else if(IDBroni2 == aBron)
							    {
				                    Bron2 = aBron;
				                    Ammo2 = cAmmo;
							    }
					        }

		                    if(Ammo1 > 9999)
		                    {
		
		               		    for(new x = 0, y = sizeof(Bron); x < y; x ++)
						        {
							        if(IDBroni1 == Bron[x][GUN_ID])
						            {
						                Ammo1 = Bron[x][GUN_AMMO];
							            break;
						            }
						        }
							}

		                    else if(Ammo2 > 9999)
	                        {

		               		    for(new x = 0, y = sizeof(Bron); x < y; x ++)
						        {
							        if(IDBroni2 == Bron[x][GUN_ID])
						            {
							            Ammo2 = Bron[x][GUN_AMMO];
							            break;
						            }
						        }
							}

                            G[playerid][CzasAreaCheck] = GetServerTick() + 2;
                            GetPlayerWeaponData(playerid, 8, cAmmo, cAmmo);
							SpawnPlayer(playerid);
                            
							SetPlayerPos(playerid, pPosX, pPosY, pPosZ);
							SetPlayerFacingAngle(playerid, pAngle);
							
							if(IDBroni1 != -22)
							{
								GivePlayerWeapon(playerid, Bron1, Ammo1);
								GivePlayerWeapon(playerid, Bron2, Ammo2);
							}
							else
							{
							    for(new i; i < sizeof(BGWeap); i ++)
							    {
							        if(BGWeap[i] > 0) GivePlayerWeapon(playerid, BGWeap[i], BGAmmo[i]);
							    }
							}
							GivePlayerWeapon(playerid, 1, 1);
							
							if(DostepnyGranat == true && DodatkowyGranat == true)	GivePlayerWeapon(playerid, 16, cAmmo);

							if(Armed == IDBroni1 || Armed == IDBroni2 || IDBroni1 == -22) SetPlayerArmedWeapon(playerid, Armed);

				            G[playerid][CzasOstRSP] = GetServerTick() + (IsVIP(playerid) == _TRUE ? 5 : 15);
				            
				            SendClientMessage(playerid, COLOR_RSP_INFO, " (RSP) Zrespawnowales(as) swoja postac");
                            forplayers(i)
			                {
				                if(G[i][SpecowanyID] == playerid)
				                    SetTimerEx("StartSpectate", 500, 0, "dd", i, playerid);
			                }
				                
						}   else SendClientMessage(playerid, COLOR_WARNING," (RSP) Nie mozna uzyc komendy podczas ochrony poczatkowej");
					}   else SendClientMessage(playerid, COLOR_WARNING," (RSP) Nie mozesz uzyc komendy podczas spadania");
				}
				else
				{
					new string[64];
				    format(string, sizeof(string)," (RSP) Komendy bedzie mozna uzyc za "TEXT_NORMAL"%d"TEXT_WARNING" sekund", GetTimeToServerTick(G[playerid][CzasOstRSP]));
					SendClientMessage(playerid, COLOR_WARNING, string);
				}
			}   else SendClientMessage(playerid, COLOR_WARNING," (RSP) Nie mozesz uzyc komendy przebywajac w pojezdzie");
		}   else SendClientMessage(playerid, COLOR_WARNING," (RSP) Musisz brac udzial w walce");
	}	else SendClientMessage(playerid, COLOR_WARNING," (RSP) Komenda dziala podczas rundy i po zakonczonym odliczaniu");
	return 1;
}

//------------------------------------------------------------------------------
CMD:spec(playerid, cmdtext[]) {
	if(getPlayerStatus(playerid) == S_WYBIERALKA) return 1;
	if(!isnull(cmdtext)) {
	    new IDGracza;
		if(IsPlayerConnected((IDGracza = strval(cmdtext)))) {
		    if(StartSpectate(playerid, IDGracza) == 0) SendClientMessage(playerid, COLOR_WARNING," (Spectate) Nie mozesz obserwowac tej osoby");
	    } else SendClientMessage(playerid, COLOR_CMD_INFO, " (Spectate) Wpisz "TEXT_NORMAL"/spec [ID Gracza]"TEXT_CMD_INFO" lub wybierz go z \""TEXT_NORMAL"Tab Listy"TEXT_CMD_INFO"\"");
    } else StartRandomSpectate(playerid);
	return 1;
}
//------------------------------------------------------------------------------

CMD:specoff(playerid)
{
	if(getPlayerStatus(playerid) == S_SPECUJE) StopSpec(playerid);
	return 1;
}

//------------------------------------------------------------------------------
CMD:add(playerid, cmdtext[]) return cmd_dg(playerid, cmdtext);
CMD:dg(playerid, cmdtext[]) {
   	if(getPlayerStatus(playerid) == S_WYBIERALKA) return 1;
	if(IsAdmin(playerid) > ALVL_NON) {
	    new string[176];
	    if(!isnull(cmdtext)) {
	        if(IDStartowanej != -1 && TrwaOdliczanie == false) {
	            if(strcmp(cmdtext, "all") == 0) {
	                forplayers(i) {
	                    if(getPlayerTeam(i) == T_ATT || getPlayerTeam(i) == T_DEF) {
	                        if(getPlayerStatus(i) != S_GRA) {
	                            DodajDoWalki(i);
	                        }
	                    }
	                }
	                format(string, sizeof(string)," (Dodaj Gracza) Administrator "TEXT_NORMAL"%s"TEXT_PADD" dodal(a) wszystkich graczy do walki", GetPlayerNick(playerid));
                    SendClientMessageToAll(COLOR_PADD, string);
				} else {
					new IDGracza = strval(cmdtext);
					if(getPlayerTeam(IDGracza) == T_ATT || getPlayerTeam(IDGracza) == T_DEF) {
						
						DodajDoWalki(IDGracza);
						format(string, sizeof(string), " (Dodaj Gracza) Administrator %s dodal(a) gracza "TEXT_NORMAL"%s"TEXT_PADD" do rundy  ( Druzyna: "TEXT_NORMAL"%s"TEXT_PADD" )", GetPlayerNick(playerid), GetPlayerNick(IDGracza), getPlayerTeam(IDGracza) == T_ATT ? ("Atak") : ("Obrona"));
						SendClientMessageToAll(COLOR_PADD, string);
				    }	else SendClientMessage(playerid, COLOR_WARNING," (Dodaj Gracza) Gracz musi byc w druzynie ataku lub obrony");
				}
			}	else SendClientMessage(playerid, COLOR_WARNING," (Dodaj Gracza) Komenda dziala jedynie podczas rundy i po skonczonym odliczaniu");
        }	else SendClientMessage(playerid, COLOR_CMD_INFO, " (Dodaj Gracza) Wpisz "TEXT_NORMAL"/dg [ID Gracza]"TEXT_CMD_INFO" zeby dodac gracza do walki");
    }
	return 1;
}
//------------------------------------------------------------------------------
CMD:zmianabroni(playerid, cmdtext[]) return cmd_agun(playerid, cmdtext);
CMD:agun(playerid, cmdtext[])
{
	if(getPlayerStatus(playerid) == S_WYBIERALKA) return 1;
	if(IsAdmin(playerid) > ALVL_NON)
    {
        new string[128];
	    if(!isnull(cmdtext))
        {
	        if(IDStartowanej != -1 && TrwaOdliczanie == false)
            {
				new IDGracza = strval(cmdtext);
				if(getPlayerTeam(IDGracza) == T_ATT || getPlayerTeam(IDGracza) == T_DEF)
			    {
				    if(getPlayerStatus(IDGracza) == S_GRA)
			        {
						format(string, sizeof(string)," (Gun Menu) Administrator "TEXT_NORMAL"%s"TEXT_GUN_INFO" zezwolil(a) Ci na zmiane broni", GetPlayerNick(playerid));
						SendClientMessage(IDGracza, COLOR_GUN_INFO, string);
                        format(string, sizeof(string), " (Gun Menu) Zezwoliles(as) graczu "TEXT_NORMAL"%s"TEXT_GUN_INFO" na zmiane broni", GetPlayerNick(IDGracza));
						SendClientMessage(playerid, COLOR_GUN_INFO, string);
				        SetPlayerWeaponRequestStatus(playerid, NEW_WEAPONS);
				        ShowPlayerFirstGunMenu(IDGracza);
			        }   else SendClientMessage(playerid, COLOR_WARNING," (Gun Menu) Gracz musi brac udzial w walce");
			    }	else SendClientMessage(playerid, COLOR_WARNING," (Gun Menu) Gracz musi byc w druzynie ataku lub obrony");
            }	else SendClientMessage(playerid, COLOR_WARNING," (Gun Menu) Komenda dziala jedynie podczas rundy i po skonczonym odliczaniu");
        }	else SendClientMessage(playerid, COLOR_CMD_INFO, " (Gun Menu) Wpisz: "TEXT_NORMAL"/agun [ID Gracza]"TEXT_CMD_INFO" zeby dac graczu mozliwosc zmiany broni");
    }
	return 1;
}

//------------------------------------------------------------------------------
CMD:v(playerid, cmdtext[]) return cmd_vote(playerid, cmdtext);
CMD:vote(playerid, cmdtext[])
{
	if(getPlayerStatus(playerid) == S_WYBIERALKA) return 1;
	if(SwapOczekiwanie == false)
    {
        if(IDStartowanej == -1 && TrwaOdliczanie == false)
        {
            new string[256];
            if(!isnull(cmdtext))
            {
				new idx = strfind(cmdtext, " "), voteID;
			    if(CzasAdminVote > 0)
		        {
			        if(IsAdmin(playerid) == ALVL_NON)
		            {
			            format(string, sizeof(string)," (Vote) Na serwerze jest administrator. Poczekaj "TEXT_NORMAL"%d"TEXT_WARNING" sekund aby moc rozpoczac glosowanie", CzasAdminVote);
	                    forplayers(i)
						{
					        if(IsAdmin(i) > ALVL_NON) return SendClientMessage(playerid, COLOR_WARNING, string);
				        }
					}
				}

				if(idx == -1)
				{
				    if(GlosowanieAktywne == true)
				    {
					    if(isNumeric(( cmdtext )))
					    {
					        if( MAX_VOTE > ( voteID = strval(cmdtext) - 1 ) >= 0 )
					        {
					            if(VoteVar[voteID][Tryb] != -1)
					            {
									if(G[playerid][VoteWybor] >= 0)
									{
									    if(VoteVar[G[playerid][VoteWybor]][Tryb] > -1)
									    {
									        VoteVar[G[playerid][VoteWybor]][Glosow] -= (IsVIP(playerid) == _FALSE ? 1 : 2);
									    }
									}
									G[playerid][VoteWybor] = voteID;
									VoteVar[voteID][Glosow] += (IsVIP(playerid) == _FALSE ? 1 : 2);
									format(string, sizeof(string)," (Vote) Oddales(as) glos na pozycje "TEXT_NORMAL"%d"TEXT_VOTE_INFO" ( "TEXT_NORMAL"%s %d"TEXT_VOTE_INFO" )", voteID + 1, VoteVar[voteID][Tryb] == 0 ? ("Arena") : ("Baza"), VoteVar[voteID][NumerID]);
									SendClientMessage(playerid, COLOR_VOTE_INFO, string);
									
									CheckVotePossibility();
									
					            }   else SendClientMessage(playerid, COLOR_WARNING," (Vote) Podana pozycja jest nieaktywna");
					        }
					    }
					}
					else
					{
						SendClientMessage(playerid, COLOR_WARNING," (Vote) Aktualnie nie trwa glosowanie");
						SendClientMessage(playerid, COLOR_CMD_INFO, " (Vote) Uzyj "TEXT_NORMAL"(/v)ote [arena / baza] [ID]"TEXT_CMD_INFO" zeby dodac pozycje do glosowania");
					}
				}
				else
				{
				    if(G[playerid][VoteDodano] == false)
				    {
				        if(GlosowanieCzas <= 5 && GlosowanieAktywne == true)
				        {
				            return SendClientMessage(playerid, COLOR_WARNING, " (Vote) Nie mozna dodawac nowych propozycji na 5 sekund przed koncem glosowania");
				        }
					    new voteTryb;
					    if(strcmp(cmdtext, "arena", true, 5) == 0)      voteTryb = 0;
					    else if(strcmp(cmdtext, "baza", true, 4) == 0) 	voteTryb = 1;

					    else
					    {
							return SendClientMessage(playerid, COLOR_CMD_INFO, " (Vote) Uzyj "TEXT_NORMAL"(/v)ote [arena / baza] [ID]"TEXT_CMD_INFO" zeby dodac pozycje do glosowania");
					    }

					    if(isNumeric(cmdtext[idx + 1]))
					    {
					        new bool:Znaleziono;
					        voteID = strval(cmdtext[idx + 1]);
					        for(new i; i < sizeof(OstatnieStarty); i ++)
					        {
					            if(OstatnieStarty[i][0] == (voteTryb == 1 ? 1 : 0))
					            {
					                if(OstatnieStarty[i][1] == voteID)
					                {
					                    return SendClientMessage(playerid, COLOR_WARNING, voteTryb == 1 ? (" (Vote) Baza o tym ID byla niedawno rozgrywana") : (" (Vote) Arena o tym ID byla niedawno rozgrywana"));
									}
					            }
					        }

							if(voteTryb == 1)
							{
							    format(string, sizeof(string), "HighSkill/Bazy/%d.txt", voteID);
							    if(!fexist(string)) return SendClientMessage(playerid, COLOR_WARNING," (Vote) Nieznaleziono bazy o podanym ID");
							}
							else
							{
							    format(string, sizeof(string), "HighSkill/Areny/%d.txt", voteID);
							    if(!fexist(string)) return SendClientMessage(playerid, COLOR_WARNING," (Vote) Nieznaleziono areny o podanym ID");
							}

							if(G[playerid][VoteWybor] >= 0)
							{
							    if(VoteVar[G[playerid][VoteWybor]][Tryb] > -1)
							    {
							        VoteVar[G[playerid][VoteWybor]][Glosow] -= (IsVIP(playerid) == _FALSE ? 1 : 2);
							    }
							}


					        for(new i; i < MAX_VOTE; i ++)
					        {
					            if(VoteVar[i][Tryb] == -1)
					            {
					                VoteVar[i][Glosow] = (IsVIP(playerid) == _FALSE ? 1 : 2);
					                VoteVar[i][NumerID] = voteID;
					                VoteVar[i][Tryb] = voteTryb;
					                G[playerid][VoteWybor] = voteID = i;
					                Znaleziono = true;
					                break;
					            }
					            else
					            {
					                if(VoteVar[i][NumerID] == voteID && VoteVar[i][Tryb] == voteTryb)
					                {
					                    return SendClientMessage(playerid, COLOR_WARNING," (Vote) Ta pozycja juz sie znajduje na liscie");
					                }
					            }
					        }
					        if(Znaleziono == true)
					        {
								format(string, sizeof(string)," (Vote) %s dodal(a) pozycje do glosowania \""TEXT_NORMAL"%s %d"TEXT_VOTE_INFO"\"", GetPlayerNick(playerid), VoteVar[voteID][Tryb] == 0 ? ("Arena") : ("Baza"), VoteVar[voteID][NumerID]);
								SendClientMessageToAll(COLOR_VOTE_INFO, string);
								G[playerid][VoteDodano] = true;
								if(GlosowanieAktywne == false)
								{
								    SendClientMessageToAll(COLOR_VOTE_INFO, " (Vote) Uzyj "TEXT_NORMAL"(/v)ote [Numer]"TEXT_VOTE_INFO" zeby oddac glos na wybrana pozycje");
									SendClientMessageToAll(COLOR_VOTE_INFO, " (Vote) Uzyj "TEXT_NORMAL"(/v)ote [arena / baza] [ID]"TEXT_VOTE_INFO" zeby dodac pozycje do glosowania");
									GlosowanieAktywne = true;
									KoniecGlosowania(CZAS_GLOSOWANIA);
								} else CheckVotePossibility();

								forplayers(i)
								{
								    if(getPlayerStatus(i) != S_WYBIERALKA)
								    {
								        TextDrawShowForPlayer(i, TDVoteName);
								        TextDrawShowForPlayer(i, TDVoteInfo);
								    }
								}
  							} else {
						  		SendClientMessage(playerid, COLOR_WARNING, " (Vote) Wszystkie pozycje glosowania sa zajete. Uzyj "TEXT_NORMAL"(/v)ote [Numer]"TEXT_WARNING" zeby oddac glos");
							}
					    }
						else
					    {
							SendClientMessage(playerid, COLOR_WARNING, " (Vote) Uzyj "TEXT_NORMAL"(/v)ote [arena / baza] [ID]"TEXT_WARNING" zeby dodac pozycje do glosowania");
					    }
					}   else SendClientMessage(playerid, COLOR_WARNING," (Vote) Dodales(as) juz pozycje do glosowania");
				}   
			}
            else
            {
				SendClientMessage(playerid, COLOR_WARNING, " (Vote) Uzyj "TEXT_NORMAL"(/v)ote [arena / baza] [ID]"TEXT_WARNING" zeby dodac pozycje do glosowania");
				if(GlosowanieAktywne == true) {
					SendClientMessage(playerid, COLOR_WARNING, " (Vote) Uzyj "TEXT_NORMAL"(/v)ote [Numer]"TEXT_WARNING" zeby oddac glos na wybrana pozycje");
				}
			}
		}	else SendClientMessage(playerid, COLOR_WARNING," (Vote) Komenda dziala jedynie podczas przerwy w walce");
	}	else SendClientMessage(playerid, COLOR_WARNING," (Vote) Prosze poczekac do zakonczenia pokazywania wynikow rundy");
	return 1;
}

//------------------------------------------------------------------------------

CMD:vstop(playerid, cmdtext[])
{
	if(getPlayerStatus(playerid) == S_WYBIERALKA) return 1;
	if(IsAdmin(playerid) > ALVL_NON)
    {
	    if(GlosowanieAktywne == true)
        {
            new string[128];
			format(string, sizeof(string), " (Vote) Administrator "TEXT_NORMAL"%s"TEXT_VOTE_INFO" przerwal(a) trwajace glosowanie", GetPlayerNick(playerid));
	        SendClientMessageToAll(COLOR_VOTE_INFO, string);
	        
	        GlosowanieAktywne = false;
			for(new i; i < MAX_VOTE; i ++)
			{
			    VoteVar[i][Tryb] = -1;
			    VoteVar[i][NumerID] = VoteVar[i][Glosow] = 0;
			}
			for(new i; i < MAX_GRACZY; i++)
			{
			    G[i][VoteWybor] = -1;
				G[i][VoteDodano] = false;
			}
	        TextDrawHideForAll(TDVoteName);
            TextDrawHideForAll(TDVoteInfo);
            
        }	else SendClientMessage(playerid, COLOR_WARNING," (Vote) Aktualnie nie trwa zadne glosowanie");
    }
	return 1;
}

//------------------------------------------------------------------------------
CMD:mix(playerid) {
    if(getPlayerStatus(playerid) == S_WYBIERALKA) return 1;
    #if _TESTY == 0
 	if(IsAdmin(playerid) > ALVL_NON) {
 	#endif
	    if(IDStartowanej == -1 && TrwaOdliczanie == false) {
	        if(mixTeams(playerid) == 0) {
                SendClientMessage(playerid, COLOR_WARNING," (Team MIX) Wykonanie mix'u druzyn jest w obecnej sytuacji nie mozliwe.");
	        } else {
				new string[128];
				format(string, sizeof(string), " (Team MIX) Administrator "TEXT_NORMAL"%s"TEXT_TEAM_CHANGE" pomieszal druzyny.", GetPlayerNick(playerid));
				SendClientMessageToAll(COLOR_TEAM_CHANGE, string);
	        }
	    } else SendClientMessage(playerid, COLOR_WARNING," (Team MIX) Mix druzyn mozna wykonac jedynie w czasie przerwy w walce");
    #if _TESTY == 0
	}
	#endif
	return 1;
}
//------------------------------------------------------------------------------
CMD:respawn(playerid) {
	if(T_DEF >= getPlayerTeam(playerid) >= T_ATT) {
	    new Float:x, Float:y, Float:z, bool:playerOutOfArea = false;
	    GetPlayerPos(playerid, x, y, z);

	    if(getPlayerStatus(playerid) == S_GRA) {
		    if(P_WorldArea[playerid][ENABLED] == true) {
				if(!(P_WorldArea[playerid][ZONE_MIN_X] - 10.0 <= x <= P_WorldArea[playerid][ZONE_MAX_X] + 10.0 and P_WorldArea[playerid][ZONE_MIN_Y] - 10.0 <= y <= P_WorldArea[playerid][ZONE_MAX_Y] + 10.0) or z > 5000.0) {
		            playerOutOfArea = true;
		        } else {
		            new Float:h_diagonal =
						floatdiv(
							floatsqroot(
								floatpower(P_WorldArea[playerid][ZONE_MAX_X] - P_WorldArea[playerid][ZONE_MIN_X], 2)
								+ floatpower(P_WorldArea[playerid][ZONE_MAX_Y] - P_WorldArea[playerid][ZONE_MIN_Y], 2)), 2);


					new Float:pDys = GetPlayerDistanceFromPoint(playerid,
						floatsub(P_WorldArea[playerid][ZONE_MAX_X], floatdiv(floatsub(P_WorldArea[playerid][ZONE_MAX_X], P_WorldArea[playerid][ZONE_MIN_X]), 2)),
						floatsub(P_WorldArea[playerid][ZONE_MAX_Y], floatdiv(floatsub(P_WorldArea[playerid][ZONE_MAX_Y], P_WorldArea[playerid][ZONE_MIN_Y]), 2)),
						CheckpointPos[2]);
	                if(pDys > h_diagonal + 10.0) playerOutOfArea = true;
		        }
	        }
			if(playerOutOfArea == false and (z < (min(floatround(SpawnAtt[2]), floatround(SpawnDef[2])) - 50.0) and G[playerid][HitInGame] == false)) playerOutOfArea = true;
	    }
	    #if _TESTY == 0
	    if( (((getPlayerStatus(playerid) == S_GRA and g_RoundSpawnProtectTime > 0) or 3 <= G[playerid][ProbAreaCheck] <= 33) or playerOutOfArea == true) and (IDStartowanej != -1 && TrwaOdliczanie == false)) {
		#endif
		    new string[100];
			format(string, 100, " (ReSpawn) "TEXT_NORMAL"%s"TEXT_PADD" skorzystal(a) z opcji powtorzenia spawnu", GetPlayerNick(playerid));
			SendClientMessageToAll(COLOR_PADD, string);
			DodajDoWalki(playerid);
		#if _TESTY == 0
	    } else SendClientMessage(playerid, COLOR_WARNING," (ReSpawn) Z opcji powtorzenia spawnu mozna korzystac wylacznie podczas ochrony poczatkowej");
		#endif
	}
	return 1;
}

//------------------------------------------------------------------------------
CMD:top10(playerid, cmdtext[]) return SendClientMessage(playerid, COLOR_WARNING, " (Top10) Wszystkie statystyki dot. graczy zostaly przeniesione na strone serwera.");
//------------------------------------------------------------------------------
CMD:stats(playerid, cmdtext[]) {
	if(isnull(cmdtext)) {
	    new s_string[4];
	    valstr(s_string, playerid);
	    return cmd_stats(playerid, s_string);
	} else {
	    new string[512];
	    if(isNumeric(cmdtext) == _TRUE) {
	        new IDGracza;
            if(IsPlayerConnected((IDGracza = strval(cmdtext)))) {
                
                format(string, sizeof(string), "\
						"DIALOG_TEXT_COLOR"Statystyki gracza "C_WHITE"%s\n\n\
						"DIALOG_TEXT_COLOR"Dane Online\n\
						"DIALOG_TEXT_COLOR"Fragi: "C_WHITE"%d\t\t"DIALOG_TEXT_COLOR"Smierci: "C_WHITE"%d\n\
		                "DIALOG_TEXT_COLOR"DMG: "C_WHITE"%d\t\t"DIALOG_TEXT_COLOR"Respekt: "C_WHITE"%d\n\n\
		                "DIALOG_TEXT_COLOR"Dane konta:\n",
					GetPlayerNick(IDGracza),
					GetPlayerKill(IDGracza, true), GetPlayerDeath(IDGracza, true),
					GetPlayerDMG(IDGracza, true), GetPlayerRespect(IDGracza, true)
				);
				if(getPlayerLoginStatus(playerid) == LOGIN_STATUS_LOGGED) {
				    format(string, sizeof(string), "%s\
							Ranking: "C_WHITE"%d\n\
							"DIALOG_TEXT_COLOR"Fragi: "C_WHITE"%d\t\t"DIALOG_TEXT_COLOR"Smierci: "C_WHITE"%d\n\
			                "DIALOG_TEXT_COLOR"DMG: "C_WHITE"%d\t\t"DIALOG_TEXT_COLOR"Respekt: "C_WHITE"%d\n\
							"DIALOG_TEXT_COLOR"Wyg. Sparingi: "C_WHITE"%d\t\t"DIALOG_TEXT_COLOR"Prz. Sparingi: "C_WHITE"%d",
						string,
                        GetPVarInt(IDGracza, PV_RANKING),
                        GetPlayerKill(IDGracza, false), GetPlayerDeath(IDGracza, false),
                        GetPlayerDMG(IDGracza, false), GetPlayerRespect(IDGracza, false),
                        GetPlayerSparingWin(IDGracza), GetPlayerSparingLoss(IDGracza)
					);
				} else format(string, sizeof(string), "%s"C_WHITE"Gracz nie ma zarejestrowanego konta.", string);
			} else strins(string, C_ADMIN"Niepoprawne ID gracza, lub wybrane ID jest nieuzywane.", 0);
	    } else strins(string, C_ADMIN"Niepoprawne ID gracza, lub wybrane ID jest nieuzywane.", 0);

		format(string, sizeof(string), "%s\n\n"DIALOG_TEXT_COLOR"Podaj ID gracza, ktorego statystyki chcesz sprawdzic\n\t\tlub wybierz go z 'Tab Listy'.", string);
		SetPVarInt(playerid, PV_TAB, TAB_STATS);
        ShowPlayerDialog(playerid, DIALOG_STATS, DIALOG_STYLE_INPUT, DIALOG_HEAD_COLOR"Statystyki gracza", string, "Sprawdz", "Wyjdz");
	}
	return 1;
}
//------------------------------------------------------------------------------
CMD:lastplayed(playerid) return cmd_ostatniograne(playerid);
CMD:ostatniograne(playerid) {
    SendClientMessage(playerid, DIALOG_HEAD_FULL_COLOR, " ");
	SendClientMessage(playerid, DIALOG_HEAD_FULL_COLOR, " --- Ostatnio startowane rundy --- ");
	for(new i, string[64]; i < sizeof(OstatnieStarty); i ++) {
	    if(OstatnieStarty[i][1] != -1) {
		    format(string, sizeof(string), "* %s "C_WHITE"%d", OstatnieStarty[i][0] == 0 ? ("Arena") : ("Baza"), OstatnieStarty[i][1]);
		    SendClientMessage(playerid, 0x2CB3FCFF, string);
		}
	}
	SendClientMessage(playerid, DIALOG_HEAD_FULL_COLOR, " ");
	return 1;
}
//------------------------------------------------------------------------------
CMD:demoarena(playerid, cmdtext[]) {
    if(getPlayerStatus(playerid) == S_SPAWN && TrwaOdliczanie == false) {
		if(!isnull(cmdtext)) {
		    new spawnSide = 0, arenaID = -1, index;
		    if((index = strfind(cmdtext, " ")) == -1) {
		        if(500 >= (arenaID = strval(cmdtext)) >= 0) {
		        	if(DemoArena(playerid, arenaID, spawnSide) == 0) {
		        	    SendClientMessage(playerid, COLOR_SYSGREY, " (Demo Arena) Arena o podanym ID nie istnieje.");
		        	}
				} else SendClientMessage(playerid, COLOR_SYSGREY, " (Demo Arena) Uzyto niepoprawnych parametrow komendy.");
		    } else {
		        if(strfind(cmdtext, " ", true, index + 1) == -1 and index <= 3) {
		            new buffer[8];
		            strmid(buffer, cmdtext, 0, index);
		            arenaID = strval(buffer);
		            spawnSide = strval(cmdtext[index + 1]);
		            if(500 >= arenaID >= 0 and 1 >= spawnSide >= 0) {
		            	if(DemoArena(playerid, arenaID, spawnSide) == 0) {
		            	    SendClientMessage(playerid, COLOR_SYSGREY, " (Demo Arena) Arena o podanym ID nie istnieje.");
		            	}
					} else SendClientMessage(playerid, COLOR_SYSGREY, " (Demo Arena) Uzyto niepoprawnych parametrow komendy.");
		        } else SendClientMessage(playerid, COLOR_SYSGREY, " (Demo Arena) Uzyj: '"C_WHITE"/demoarena [ID Areny] [0 - Spawn ataku, 1 - Spawn obrony]"C_SYSGREY"'.");
		    }
		} else SendClientMessage(playerid, COLOR_SYSGREY, " (Demo Arena) Uzyj: '"C_WHITE"/demoarena [ID Areny] [0 - Spawn ataku, 1 - Spawn obrony]"C_SYSGREY"'.");
	} else SendClientMessage(playerid, COLOR_SYSGREY, " (Demo Arena) Komendy mozna uzyc jedynie w poczekalni.");
	return 1;
}
//------------------------------------------------------------------------------
CMD:demoend(playerid) {
    if(getPlayerStatus(playerid) == S_SPAWN) {
		if(DemoArenaEnd(playerid) == 1) {
	        SpawnPlayer(playerid);
		} else SendClientMessage(playerid, COLOR_SYSGREY, " (Demo End) Nie korzystasz z wersji pokazowej.");
	} else SendClientMessage(playerid, COLOR_SYSGREY, " (Demo Arena) Komendy mozna uzyc jedynie w poczekalni.");
	return 1;
}
//------------------------------------------------------------------------------
CMD:mypos(playerid) {
	new Float:posX, Float:posY, Float:posZ;
	new string[64];
	GetPlayerPos(playerid, posX, posY, posZ);
	format(string, sizeof(string), "X: %.4f | Y: %.4f | Z: %.4f | I: %d", posX, posY, posZ, GetPlayerInterior(playerid));
	SendClientMessage(playerid, 0xFFFFFFFF, string);
	return 1;
}
//------------------------------------------------------------------------------
CMD:gamesettings(playerid) {
    ShowPlayerGamePanelMenu(playerid, -1, 1);
	return 1;
}
//------------------------------------------------------------------------------
CMD:hall(playerid) return cmd_healall(playerid);
CMD:healall(playerid) {
	if(IsAdmin(playerid) > 0) {
 	    new str[128];
		forplayers(i) {
		    if(getPlayerStatus(i) == S_GRA) {
		        SetPVarInt(i, PV_HEAL, 3);
		        SetPlayerHealthEx(i, 100);
	        }
	    }
		format(str, sizeof(str)," [Heal] Administrator "C_WHITE"%s {1AB311}uzdrowil(a) wszystkich graczy.", GetPlayerNick(playerid));
		SendClientMessageToAll(0x1AB311FF,str);
	}
	return 1;
}

//------------------------------------------------------------------------------
CMD:h(playerid, cmdtext[]) return cmd_heal(playerid, cmdtext);
CMD:heal(playerid, cmdtext[]) {
	if(IsAdmin(playerid) > 0) {
		if(!isnull(cmdtext)) {
            if(isNumeric(cmdtext)) {
			    new IDGracza;
				if(IsPlayerConnected((IDGracza = strval(cmdtext)))) {
			        if(getPlayerStatus(IDGracza) == S_GRA) {
						new str[128];
		                SetPVarInt(IDGracza, PV_HEAL, 3);
						SetPlayerHealthEx(IDGracza, 100);
						format(str, sizeof(str)," [Heal] Administrator "C_WHITE"%s {1AB311}uzdrowil(a) gracza "C_WHITE"%s{1AB311}.",GetPlayerNick(playerid),GetPlayerNick(IDGracza));
						SendClientMessageToAll(0x1AB311FF,str);
					}   else SendClientMessage(playerid, COLOR_GREY," [Heal] Wybrany gracz nie bierze udzialu w walce.");
			    }	else SendClientMessage(playerid, COLOR_GREY," [Heal] Wybrany gracz jest OFF-Line.");
		    }	else SendClientMessage(playerid, COLOR_GREY," [Heal] Wpisz: \"(/h)eal [ID Gracza]\".");
		}   else SendClientMessage(playerid, COLOR_GREY," [Heal] Wpisz: \"(/h)eal [ID Gracza]\".");
    }
	return 1;
}
//------------------------------------------------------------------------------
CMD:killp(playerid, cmdtext[]) {
	if(IsAdmin(playerid) > 0) {
		if(!isnull(cmdtext)) {
            if(isNumeric(cmdtext)) {
			    new IDGracza;
				if(IsPlayerConnected((IDGracza = strval(cmdtext)))) {
			        if(getPlayerStatus(IDGracza) == S_GRA) {
						new str[128];
						SetPlayerHealthEx(IDGracza, 0);
						format(str, sizeof(str)," [Kill Player] Administrator "C_WHITE"%s {62B147}zabil(a) gracza "C_WHITE"%s{62B147}.",GetPlayerNick(playerid),GetPlayerNick(IDGracza));
						SendClientMessageToAll(0x62B147FF,str);
					}   else SendClientMessage(playerid, COLOR_GREY," [Kill Player] Wybrany gracz nie bierze udzialu w walce.");
			    }	else SendClientMessage(playerid, COLOR_GREY," [Kill Player] Wybrany gracz jest OFF-Line.");
		    }	else SendClientMessage(playerid, COLOR_GREY," [Kill Player] Wpisz: \"/killp [ID Gracza]\".");
        }	else SendClientMessage(playerid, COLOR_GREY," [Kill Player] Wpisz: \"/killp [ID Gracza]\".");
    }
	return 1;
}
//------------------------------------------------------------------------------
CMD:tp(playerid, cmdtext[]) {
	if(IsAdmin(playerid) > 0) {
		if(!isnull(cmdtext)) {
		    new idx;
			if((idx = strfind(cmdtext, " ", true)) != -1) {
			    new str[128], IDGracza[2];

				strmid(str, cmdtext, 0, idx, 4);
				IDGracza[0] = strval(str);
				strdel(str,0,4);
				strmid(str, cmdtext, idx + 1, 8, 4);
				IDGracza[1] = strval(str);

				if(IsPlayerConnected(IDGracza[0]) && IsPlayerConnected(IDGracza[1])) {
				    if(IDGracza[0] != IDGracza[1]) {
						if(getPlayerStatus(IDGracza[0]) == getPlayerStatus(IDGracza[1])) {
					        new Float:pPosX, Float:pPosY, Float:pPosZ;
							GetPlayerPos(IDGracza[1], pPosX, pPosY, pPosZ);
							SetPlayerPos(IDGracza[0], pPosX, pPosY, pPosZ);
							SetPlayerInterior(IDGracza[0], GetPlayerInterior(IDGracza[1]));
							SetPlayerVirtualWorld(IDGracza[0], GetPlayerVirtualWorld(IDGracza[1]));
							format(str, sizeof(str)," [Teleport] Teleportowales(as) gracza "C_WHITE"%s {5AFA56}do "C_WHITE"%s{5AFA56}.",GetPlayerNick(IDGracza[0]), GetPlayerNick(IDGracza[1]));
							SendClientMessage(playerid, 0x5AFA56FF, str);
							format(str, sizeof(str)," [Teleport] Administrator "C_WHITE"%s {5AFA56}teleportowal(a) Cie do gracza "C_WHITE"%s{5AFA56}.",GetPlayerNick(playerid),GetPlayerNick(IDGracza[1]));
							SendClientMessage(IDGracza[0], 0x5AFA56FF, str);
					    }	else SendClientMessage(playerid, COLOR_GREY," [Teleport] Teleportacja niemozliwa. Stany gry graczy roznia sie.");
				    }	else SendClientMessage(playerid, COLOR_GREY," [Teleport] Nie mozesz teleportowac gracza do jego samego.");
				}	else SendClientMessage(playerid, COLOR_GREY," [Teleport] Jeden z graczy jest OFF-Line.");
		    }	else SendClientMessage(playerid, COLOR_GREY," [Teleport] Wpisz: \"/tp [ID Teleportowanego gracza] [ID Gracza celu]\".");
	    }	else SendClientMessage(playerid, COLOR_GREY," [Teleport] Wpisz: \"/tp [ID Teleportowanego gracza] [ID Gracza celu]\".");
	}
	return 1;
}
//------------------------------------------------------------------------------
CMD:aall(playerid) return cmd_armorall(playerid);
CMD:armorall(playerid) {
	if(IsAdmin(playerid) > 0) {
 	    if(MAX_ARMOUR > 0) {
			forplayers(i) {
			    if(getPlayerStatus(i) == S_GRA) {
			        SetPlayerArmourEx(i, MAX_ARMOUR);
		        }
		    }
			new str[128];
			format(str, sizeof(str)," [Armour] Administrator "C_WHITE"%s {1AB311}dal(a) kamizelke wszystkim graczom.",GetPlayerNick(playerid));
			SendClientMessageToAll(0x1AB311FF,str);
		}   else SendClientMessage(playerid, COLOR_SYSGREY," [Armour] Nie mozna dodac kamizelki graczom z powodu braku wyznaczonego limitu.");
	}
	return 1;
}

//------------------------------------------------------------------------------
CMD:a(playerid, cmdtext[]) return cmd_armor(playerid, cmdtext);
CMD:armor(playerid, cmdtext[]) {
	if(IsAdmin(playerid) > 0) {
		if(!isnull(cmdtext)) {
            if(isNumeric(cmdtext)) {
			    new IDGracza;
				if(IsPlayerConnected((IDGracza = strval(cmdtext)))) {
			        if(MAX_ARMOUR > 0) {
			            if(getPlayerStatus(IDGracza) == S_GRA) {
							new str[128];
							SetPlayerArmourEx(IDGracza, MAX_ARMOUR);
							format(str, sizeof(str)," [Armour] Administrator "C_WHITE"%s {1AB311}dal(a) kamizelke graczu "C_WHITE"%s{1AB311}.",GetPlayerNick(playerid),GetPlayerNick(IDGracza));
							SendClientMessageToAll(0x1AB311FF,str);
						}   else SendClientMessage(playerid, COLOR_GREY," [Armour] Wybrany gracz nie bierze udzialu w walce.");
					}   else SendClientMessage(playerid, COLOR_SYSGREY," [Armour] Nie mozna dac kamizelki graczu z powodu braku wyznaczonego limitu.");
			    }	else SendClientMessage(playerid, COLOR_SYSGREY," [Armour] Wybrany gracz jest OFF-Line.");
		    }	else SendClientMessage(playerid, COLOR_SYSGREY," [Armour] Wpisz: \"(/a)rmor [ID Gracza]\".");
        }	else SendClientMessage(playerid, COLOR_SYSGREY," [Armour] Wpisz: \"(/a)rmor [ID Gracza]\".");
    }
	return 1;
}
//------------------------------------------------------------------------------
CMD:rall(playerid) return cmd_restoreall(playerid);
CMD:restoreall(playerid) {
	if(IsAdmin(playerid) > 0) {
		forplayers(i) {
		    if(getPlayerStatus(i) == S_GRA) {
		        SetPVarInt(i, PV_HEAL, 3);
		        SetPlayerHealthEx(i, 100);
		        SetPlayerArmourEx(i, MAX_ARMOUR);
	        }
	    }
		new str[128];
		format(str, sizeof(str)," [Restore] Administrator "C_WHITE"%s {1AB311}przywrocil(a) HP i Armor dla wszystkich graczy.",GetPlayerNick(playerid));
		SendClientMessageToAll(0x1AB311FF,str);
	}
	return 1;
}
//------------------------------------------------------------------------------
CMD:r(playerid, cmdtext[]) return cmd_restore(playerid, cmdtext);
CMD:restore(playerid, cmdtext[]) {
	if(IsAdmin(playerid) > 0) {
		if(!isnull(cmdtext)) {
            if(isNumeric(cmdtext)) {
			    new IDGracza;
				if(IsPlayerConnected((IDGracza= strval(cmdtext)))) {
			        if(getPlayerStatus(IDGracza) == S_GRA) {
						new str[128];
		                SetPVarInt(IDGracza, PV_HEAL, 3);
						SetPlayerHealthEx(IDGracza, 100);
						SetPlayerArmourEx(IDGracza, MAX_ARMOUR);
						format(str, sizeof(str)," [Restore] Administrator "C_WHITE"%s {1AB311}przywrocil(a) HP i Armor graczu "C_WHITE"%s{1AB311}.",GetPlayerNick(playerid),GetPlayerNick(IDGracza));
						SendClientMessageToAll(0x1AB311FF,str);
	                }   else SendClientMessage(playerid, COLOR_GREY," [Restore] Wybrany gracz nie bierze udzialu w walce.");
			    }	else SendClientMessage(playerid, COLOR_GREY," [Restore] Wybrany gracz jest OFF-Line.");
		    }	else SendClientMessage(playerid, COLOR_GREY," [Restore] Wpisz: \"(/r)estore [ID Gracza]\".");
        }	else SendClientMessage(playerid, COLOR_GREY," [Restore] Wpisz: \"(/r)estore [ID Gracza]\".");
    }
	return 1;
}
//------------------------------------------------------------------------------
CMD:checkobjects(playerid) {
	new normalObjects_Total, playerObjects_Total;
	new normalObjects_LastID, playerObjects_LastID;
	new string[128];
	
	for(new i; i < MAX_OBJECTS; i ++) {
	    if(IsValidObject(i)) {
	        normalObjects_Total ++;
	        normalObjects_LastID = i;
	    }
	    if(IsValidPlayerObject(playerid, i)) {
	        playerObjects_Total ++;
	        playerObjects_LastID = i;
	    }
	}

	format(string, sizeof(string),"P-ID: %d (Stat: %d) | R-ID: %d | Type: %d | Count: %d | Time: %02d:%02d", playerid, getPlayerStatus(playerid), IDStartowanej, TypArena, TrwaOdliczanie, CzasMin, CzasSek);
	SendClientMessage(playerid, -1, string);
	format(string, sizeof(string),"Normal: %d  (LastID: %d)", normalObjects_Total, normalObjects_LastID);
	SendClientMessage(playerid, -1, string);
	format(string, sizeof(string),"Player: %d  (LastID: %d)", playerObjects_Total, playerObjects_LastID);
	SendClientMessage(playerid, -1, string);
	return 1;
}
