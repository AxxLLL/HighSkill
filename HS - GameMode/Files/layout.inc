#define DIALOG_HEAD_FULL_COLOR		0x078FE0FF
#define DIALOG_HEAD_COLOR			"{078FE0}"
#define DIALOG_KICK_FULL_COLOR		0xFF0000FF
#define DIALOG_KICK_COLOR			"{FF0000}"
#define	DIALOG_TEXT_FULL_COLOR		0x68BEFDFF
#define	DIALOG_TEXT_COLOR			"{68BEFD}"
#define	DIALOG_NORMAL_FULL_COLOR	0xFFFFFFFF
#define	DIALOG_NORMAL_COLOR			"{FFFFFF}"
#define DIALOG_COUNT_FULL_COLOR		0xDDF4FFFF
#define DIALOG_COUNT_COLOR			"{DDF4FF}"

#define DIALOG_TEAM_CHANGE_COLOR		"{3EA5F9}"
#define DIALOG_TEAM_CHANGE_FULL_COLOR	0x3EA5F9FF

#define D_CC	DIALOG_COUNT_COLOR


#define COLOR_NORMAL				COLOR_WHITE
#define TEXT_NORMAL					C_WHITE
#define COLOR_TEAM_CHANGE			0x3EA5F9FF
#define TEXT_TEAM_CHANGE			"{3EA5F9}"
#define COLOR_WARNING				0xCEF1FFFF
#define TEXT_WARNING				"{CEF1FF}"
#define COLOR_SPARING_INFO			0x47B9F5FF
#define TEXT_SPARING_INFO			"{47B9F5}"
#define COLOR_SPARING_WARNING		0x9FDCFDFF
#define TEXT_SPARING_WARNING		"{9FDCFD}"
#define COLOR_CMD_INFO				0x2EB3FAFF
#define TEXT_CMD_INFO				"{2EB3FA}"
#define COLOR_RESPECT_INFO			0x5BA3F2FF
#define TEXT_RESPECT_INFO			"{5BA3F2}"
#define COLOR_CAR_INFO				0x5BA3F2FF
#define TEXT_CAR_INFO				"{5BA3F2}"
#define COLOR_RSP_INFO				0x5BA3F2FF
#define TEXT_RSP_INFO				"{5BA3F2}"
#define COLOR_PADD					0x2CB3FCFF
#define TEXT_PADD					"{2CB3FC}"
#define COLOR_PREM					0x0B8BF4FF
#define TEXT_PREM					"{0B8BF4}"
#define COLOR_DM_INFO				0x5BA3F2FF
#define TEXT_DM_INFO				"{5BA3F2}"
#define COLOR_START_INFO			0x2CB3FCFF
#define TEXT_START_INFO				"{2CB3FC}"
#define COLOR_VOTE_INFO				0x62ADE6FF
#define TEXT_VOTE_INFO				"{62ADE6}"
#define COLOR_PM_RECEIVED			0xFCE123FF
#define TEXT_PM_RECEIVED			"{FCE123}"
#define COLOR_PM_SEND				0xFEDD5AFF
#define TEXT_PM_SEND				"{FEDD5A}"
#define COLOR_PM_SPEC				0xFAA301FF
#define TEXT_PM_SPEC				"{FAA301}"
#define COLOR_GUN_INFO				0x078FE0FF
#define TEXT_GUN_INFO				"{078FE0}"

//===========================================================================================================
//-----------------------------------------------------------------------------------------------------------
//===========================================================================================================
#define HITBY_Y		338.0	
#define HITBY_X		441.0
#define HIT_X		201.0

CreatePlayerTextDraws(playerid) {
	PTD_PlayerHudNick[playerid] = TextDrawCreate( 42.000000, 426.000000, " ");
	TextDrawAlignment(PTD_PlayerHudNick[playerid], 2);
	TextDrawBackgroundColor(PTD_PlayerHudNick[playerid], 48);
	TextDrawFont(PTD_PlayerHudNick[playerid], 1);
	TextDrawLetterSize(PTD_PlayerHudNick[playerid], 0.200000, 0.899999);
	TextDrawColor(PTD_PlayerHudNick[playerid], -1);
	TextDrawSetOutline(PTD_PlayerHudNick[playerid], 0);
	TextDrawSetProportional(PTD_PlayerHudNick[playerid], 1);
	TextDrawSetShadow(PTD_PlayerHudNick[playerid], 1);

	PTD_PlayerHudKills[playerid] = TextDrawCreate( 13.000000, 440.000000, "0");
	TextDrawAlignment(PTD_PlayerHudKills[playerid], 2);
	TextDrawBackgroundColor(PTD_PlayerHudKills[playerid], 48);
	TextDrawFont(PTD_PlayerHudKills[playerid], 1);
	TextDrawLetterSize(PTD_PlayerHudKills[playerid], 0.170000, 0.699999);
	TextDrawColor(PTD_PlayerHudKills[playerid], -1);
	TextDrawSetOutline(PTD_PlayerHudKills[playerid], 0);
	TextDrawSetProportional(PTD_PlayerHudKills[playerid], 1);
	TextDrawSetShadow(PTD_PlayerHudKills[playerid], 1);

	PTD_PlayerHudDeaths[playerid] = TextDrawCreate( 40.000000, 440.000000, "0");
	TextDrawAlignment(PTD_PlayerHudDeaths[playerid], 2);
	TextDrawBackgroundColor(PTD_PlayerHudDeaths[playerid], 48);
	TextDrawFont(PTD_PlayerHudDeaths[playerid], 1);
	TextDrawLetterSize(PTD_PlayerHudDeaths[playerid], 0.170000, 0.699999);
	TextDrawColor(PTD_PlayerHudDeaths[playerid], -1);
	TextDrawSetOutline(PTD_PlayerHudDeaths[playerid], 0);
	TextDrawSetProportional(PTD_PlayerHudDeaths[playerid], 1);
	TextDrawSetShadow(PTD_PlayerHudDeaths[playerid], 1);

	PTD_PlayerHudDamage[playerid] = TextDrawCreate( 68.000000, 440.000000, "0");
	TextDrawAlignment(PTD_PlayerHudDamage[playerid], 2);
	TextDrawBackgroundColor(PTD_PlayerHudDamage[playerid], 48);
	TextDrawFont(PTD_PlayerHudDamage[playerid], 1);
	TextDrawLetterSize(PTD_PlayerHudDamage[playerid], 0.170000, 0.699999);
	TextDrawColor(PTD_PlayerHudDamage[playerid], -1);
	TextDrawSetOutline(PTD_PlayerHudDamage[playerid], 0);
	TextDrawSetProportional(PTD_PlayerHudDamage[playerid], 1);
	TextDrawSetShadow(PTD_PlayerHudDamage[playerid], 1);

	PTD_PlayerHudRespect[playerid] = TextDrawCreate( 97.000000, 440.000000, "0");
	TextDrawAlignment(PTD_PlayerHudRespect[playerid], 2);
	TextDrawBackgroundColor(PTD_PlayerHudRespect[playerid], 48);
	TextDrawFont(PTD_PlayerHudRespect[playerid], 1);
	TextDrawLetterSize(PTD_PlayerHudRespect[playerid], 0.170000, 0.699999);
	TextDrawColor(PTD_PlayerHudRespect[playerid], -1);
	TextDrawSetOutline(PTD_PlayerHudRespect[playerid], 0);
	TextDrawSetProportional(PTD_PlayerHudRespect[playerid], 1);
	TextDrawSetShadow(PTD_PlayerHudRespect[playerid], 1);

	PTD_PlayerHudRanking[playerid] = TextDrawCreate( 97.000000, 426.000000, "0");
	TextDrawAlignment(PTD_PlayerHudRanking[playerid], 2);
	TextDrawBackgroundColor(PTD_PlayerHudRanking[playerid], 48);
	TextDrawFont(PTD_PlayerHudRanking[playerid], 1);
	TextDrawLetterSize(PTD_PlayerHudRanking[playerid], 0.200000, 0.899999);
	TextDrawColor(PTD_PlayerHudRanking[playerid], -1);
	TextDrawSetOutline(PTD_PlayerHudRanking[playerid], 0);
	TextDrawSetProportional(PTD_PlayerHudRanking[playerid], 1);
	TextDrawSetShadow(PTD_PlayerHudRanking[playerid], 1);
	
	PTD_SpecNick[playerid] = TextDrawCreate( 320.000000, 309.000000, " ");
	TextDrawAlignment(PTD_SpecNick[playerid], 2);
	TextDrawBackgroundColor(PTD_SpecNick[playerid], 255);
	TextDrawFont(PTD_SpecNick[playerid], 1);
	TextDrawLetterSize(PTD_SpecNick[playerid], 0.170000, 0.899999);
	TextDrawColor(PTD_SpecNick[playerid], 74043135);
	TextDrawSetOutline(PTD_SpecNick[playerid], 0);
	TextDrawSetProportional(PTD_SpecNick[playerid], 1);
	TextDrawSetShadow(PTD_SpecNick[playerid], 1);

	PTD_SpecHealth[playerid][0] = TextDrawCreate( 290.000000, 324.000000, "LD_OTB2:butnAo");
	TextDrawBackgroundColor(PTD_SpecHealth[playerid][0], 255);
	TextDrawFont(PTD_SpecHealth[playerid][0], 4);
	TextDrawLetterSize(PTD_SpecHealth[playerid][0], 0.500000, 1.000000);
	TextDrawColor(PTD_SpecHealth[playerid][0], 0x044FAAFF);
	TextDrawSetOutline(PTD_SpecHealth[playerid][0], 0);
	TextDrawSetProportional(PTD_SpecHealth[playerid][0], 1);
	TextDrawSetShadow(PTD_SpecHealth[playerid][0], 1);
	TextDrawUseBox(PTD_SpecHealth[playerid][0], 1);
	TextDrawBoxColor(PTD_SpecHealth[playerid][0], 74042976);
	TextDrawTextSize(PTD_SpecHealth[playerid][0], 0.000000, 10.000000);

	PTD_SpecHealth[playerid][1] = TextDrawCreate( 320.000000, 325.000000, " ");
	TextDrawAlignment(PTD_SpecHealth[playerid][1], 2);
	TextDrawBackgroundColor(PTD_SpecHealth[playerid][1], 48);
	TextDrawFont(PTD_SpecHealth[playerid][1], 1);
	TextDrawLetterSize(PTD_SpecHealth[playerid][1], 0.129998, 0.599999);
	TextDrawColor(PTD_SpecHealth[playerid][1], -86);
	TextDrawSetOutline(PTD_SpecHealth[playerid][1], 0);
	TextDrawSetProportional(PTD_SpecHealth[playerid][1], 1);
	TextDrawSetShadow(PTD_SpecHealth[playerid][1], 1);

	PTD_SpecArmor[playerid][0] = TextDrawCreate( 290.000000, 333.000000, "LD_OTB2:butnAo");
	TextDrawBackgroundColor(PTD_SpecArmor[playerid][0], 255);
	TextDrawFont(PTD_SpecArmor[playerid][0], 4);
	TextDrawLetterSize(PTD_SpecArmor[playerid][0], 0.500000, 1.000000);
	TextDrawColor(PTD_SpecArmor[playerid][0], 0x044FAAFF);
	TextDrawSetOutline(PTD_SpecArmor[playerid][0], 0);
	TextDrawSetProportional(PTD_SpecArmor[playerid][0], 1);
	TextDrawSetShadow(PTD_SpecArmor[playerid][0], 1);
	TextDrawUseBox(PTD_SpecArmor[playerid][0], 1);
	TextDrawBoxColor(PTD_SpecArmor[playerid][0], 74042976);
	TextDrawTextSize(PTD_SpecArmor[playerid][0], 0.000000, 10.000000);

	PTD_SpecArmor[playerid][1] = TextDrawCreate( 320.000000, 334.000000, " ");
	TextDrawAlignment(PTD_SpecArmor[playerid][1], 2);
	TextDrawBackgroundColor(PTD_SpecArmor[playerid][1], 48);
	TextDrawFont(PTD_SpecArmor[playerid][1], 1);
	TextDrawLetterSize(PTD_SpecArmor[playerid][1], 0.129998, 0.599999);
	TextDrawColor(PTD_SpecArmor[playerid][1], -86);
	TextDrawSetOutline(PTD_SpecArmor[playerid][1], 0);
	TextDrawSetProportional(PTD_SpecArmor[playerid][1], 1);
	TextDrawSetShadow(PTD_SpecArmor[playerid][1], 1);

	PTD_SpecWeapons[playerid][0] = TextDrawCreate( 322.000000, 342.000000, " ");
	TextDrawBackgroundColor(PTD_SpecWeapons[playerid][0], 48);
	TextDrawFont(PTD_SpecWeapons[playerid][0], 1);
	TextDrawLetterSize(PTD_SpecWeapons[playerid][0], 0.129998, 0.599999);
	TextDrawColor(PTD_SpecWeapons[playerid][0], -86);
	TextDrawSetOutline(PTD_SpecWeapons[playerid][0], 0);
	TextDrawSetProportional(PTD_SpecWeapons[playerid][0], 1);
	TextDrawSetShadow(PTD_SpecWeapons[playerid][0], 1);

	PTD_SpecWeapons[playerid][1] = TextDrawCreate( 318.000000, 342.000000, " ");
	TextDrawAlignment(PTD_SpecWeapons[playerid][1], 3);
	TextDrawBackgroundColor(PTD_SpecWeapons[playerid][1], 48);
	TextDrawFont(PTD_SpecWeapons[playerid][1], 1);
	TextDrawLetterSize(PTD_SpecWeapons[playerid][1], 0.129998, 0.599999);
	TextDrawColor(PTD_SpecWeapons[playerid][1], -86);
	TextDrawSetOutline(PTD_SpecWeapons[playerid][1], 0);
	TextDrawSetProportional(PTD_SpecWeapons[playerid][1], 1);
	TextDrawSetShadow(PTD_SpecWeapons[playerid][1], 1);	
	
	PTD_KilledBy[playerid][0] = TextDrawCreate( 325.000000, 338.000000, " ");
	TextDrawAlignment(PTD_KilledBy[playerid][0], 2);
	TextDrawBackgroundColor(PTD_KilledBy[playerid][0], 144);
	TextDrawFont(PTD_KilledBy[playerid][0], 1);
	TextDrawLetterSize(PTD_KilledBy[playerid][0], 0.240000, 1.200000);
	TextDrawColor(PTD_KilledBy[playerid][0], 72329932);
	TextDrawSetOutline(PTD_KilledBy[playerid][0], 0);
	TextDrawSetProportional(PTD_KilledBy[playerid][0], 1);
	TextDrawSetShadow(PTD_KilledBy[playerid][0], 1);
	
	PTD_KilledBy[playerid][1] = TextDrawCreate( 325.000000, 349.000000, " ");
	TextDrawAlignment(PTD_KilledBy[playerid][1], 2);
	TextDrawBackgroundColor(PTD_KilledBy[playerid][1], 144);
	TextDrawFont(PTD_KilledBy[playerid][1], 1);
	TextDrawLetterSize(PTD_KilledBy[playerid][1], 0.240000, 1.200000);
	TextDrawColor(PTD_KilledBy[playerid][1], 72329932);
	TextDrawSetOutline(PTD_KilledBy[playerid][1], 0);
	TextDrawSetProportional(PTD_KilledBy[playerid][1], 1);
	TextDrawSetShadow(PTD_KilledBy[playerid][1], 1);	

	PTD_PingFPSPLoss[playerid][0] = TextDrawCreate( 529.000000, 1.000000, " ");
	TextDrawAlignment(PTD_PingFPSPLoss[playerid][0], 2);
	TextDrawBackgroundColor(PTD_PingFPSPLoss[playerid][0], 48);
	TextDrawFont(PTD_PingFPSPLoss[playerid][0], 1);
	TextDrawLetterSize(PTD_PingFPSPLoss[playerid][0], 0.189999, 0.799998);
	TextDrawColor(PTD_PingFPSPLoss[playerid][0], -1);
	TextDrawSetOutline(PTD_PingFPSPLoss[playerid][0], 0);
	TextDrawSetProportional(PTD_PingFPSPLoss[playerid][0], 1);
	TextDrawSetShadow(PTD_PingFPSPLoss[playerid][0], 1);

	PTD_PingFPSPLoss[playerid][1] = TextDrawCreate( 561.000000, 1.000000, " ");
	TextDrawAlignment(PTD_PingFPSPLoss[playerid][1], 2);
	TextDrawBackgroundColor(PTD_PingFPSPLoss[playerid][1], 48);
	TextDrawFont(PTD_PingFPSPLoss[playerid][1], 1);
	TextDrawLetterSize(PTD_PingFPSPLoss[playerid][1], 0.189999, 0.799998);
	TextDrawColor(PTD_PingFPSPLoss[playerid][1], -1);
	TextDrawSetOutline(PTD_PingFPSPLoss[playerid][1], 0);
	TextDrawSetProportional(PTD_PingFPSPLoss[playerid][1], 1);
	TextDrawSetShadow(PTD_PingFPSPLoss[playerid][1], 1);	

	PTD_PingFPSPLoss[playerid][2] = TextDrawCreate( 605.000000, 1.000000, " ");
	TextDrawAlignment(PTD_PingFPSPLoss[playerid][2], 2);
	TextDrawBackgroundColor(PTD_PingFPSPLoss[playerid][2], 48);
	TextDrawFont(PTD_PingFPSPLoss[playerid][2], 1);
	TextDrawLetterSize(PTD_PingFPSPLoss[playerid][2], 0.189999, 0.799998);
	TextDrawColor(PTD_PingFPSPLoss[playerid][2], -1);
	TextDrawSetOutline(PTD_PingFPSPLoss[playerid][2], 0);
	TextDrawSetProportional(PTD_PingFPSPLoss[playerid][2], 1);
	TextDrawSetShadow(PTD_PingFPSPLoss[playerid][2], 1);	
	
	PTD_HitNick[playerid] = TextDrawCreate( HIT_X, HITBY_Y + 2.0, " ");
	TextDrawAlignment(PTD_HitNick[playerid], 2);
	TextDrawBackgroundColor(PTD_HitNick[playerid], 0x00000050);
	TextDrawFont(PTD_HitNick[playerid], 1);
	TextDrawLetterSize(PTD_HitNick[playerid], 0.190000, 0.899999);
	TextDrawColor(PTD_HitNick[playerid], 0x00FF00AA);
	TextDrawSetOutline(PTD_HitNick[playerid], 0);
	TextDrawSetProportional(PTD_HitNick[playerid], 1);
	TextDrawSetShadow(PTD_HitNick[playerid], 1);
	
	PTD_HitInfo[playerid] = TextDrawCreate( HIT_X + 1, HITBY_Y + 13.0, " "); 
	TextDrawAlignment(PTD_HitInfo[playerid], 2);
	TextDrawBackgroundColor(PTD_HitInfo[playerid], 80);
	TextDrawFont(PTD_HitInfo[playerid], 1);
	TextDrawLetterSize(PTD_HitInfo[playerid], 0.139999, 0.699999);
	TextDrawColor(PTD_HitInfo[playerid], 74043050);
	TextDrawSetOutline(PTD_HitInfo[playerid], 0);
	TextDrawSetProportional(PTD_HitInfo[playerid], 1);
	TextDrawSetShadow(PTD_HitInfo[playerid], 1);	

	PTD_HitedByNick[playerid] = TextDrawCreate( HITBY_X, HITBY_Y + 2.0, " ");
	TextDrawAlignment(PTD_HitedByNick[playerid], 2);
	TextDrawBackgroundColor(PTD_HitedByNick[playerid], 0x00000050);
	TextDrawFont(PTD_HitedByNick[playerid], 1);
	TextDrawLetterSize(PTD_HitedByNick[playerid], 0.190000, 0.899999);
	TextDrawColor(PTD_HitedByNick[playerid], 0xFF0000AA);//74043135
	TextDrawSetOutline(PTD_HitedByNick[playerid], 0);
	TextDrawSetProportional(PTD_HitedByNick[playerid], 1);
	TextDrawSetShadow(PTD_HitedByNick[playerid], 1);

	PTD_HitedByInfo[playerid] = TextDrawCreate( HITBY_X + 1, HITBY_Y + 13.0, " ");
	TextDrawAlignment(PTD_HitedByInfo[playerid], 2);
	TextDrawBackgroundColor(PTD_HitedByInfo[playerid], 80);
	TextDrawFont(PTD_HitedByInfo[playerid], 1);
	TextDrawLetterSize(PTD_HitedByInfo[playerid], 0.139999, 0.699999);
	TextDrawColor(PTD_HitedByInfo[playerid], 74043050);
	TextDrawSetOutline(PTD_HitedByInfo[playerid], 0);
	TextDrawSetProportional(PTD_HitedByInfo[playerid], 1);
	TextDrawSetShadow(PTD_HitedByInfo[playerid], 1);	
		
	PTD_SpecByInfo[playerid] = TextDrawCreate( 87.000000, 170.000000, " ");
	TextDrawAlignment(PTD_SpecByInfo[playerid], 2);
	TextDrawBackgroundColor(PTD_SpecByInfo[playerid], 48);
	TextDrawFont(PTD_SpecByInfo[playerid], 1);
	TextDrawLetterSize(PTD_SpecByInfo[playerid], 0.200000, 0.799999);
	TextDrawColor(PTD_SpecByInfo[playerid], -52);
	TextDrawSetOutline(PTD_SpecByInfo[playerid], 0);
	TextDrawSetProportional(PTD_SpecByInfo[playerid], 1);
	TextDrawSetShadow(PTD_SpecByInfo[playerid], 1);
	TextDrawUseBox(PTD_SpecByInfo[playerid], 1);
	TextDrawBoxColor(PTD_SpecByInfo[playerid], 80);
	TextDrawTextSize(PTD_SpecByInfo[playerid], 0.000000, 98.000000);	
	
	PTD_PlayerAimedNick[playerid] = TextDrawCreate(557.000000, 321.000000, " ");
	TextDrawAlignment(PTD_PlayerAimedNick[playerid], 2);
	TextDrawBackgroundColor(PTD_PlayerAimedNick[playerid], 64);
	TextDrawFont(PTD_PlayerAimedNick[playerid], 1);
	TextDrawLetterSize(PTD_PlayerAimedNick[playerid], 0.200000, 0.799999);
	TextDrawColor(PTD_PlayerAimedNick[playerid], -1);
	TextDrawSetOutline(PTD_PlayerAimedNick[playerid], 0);
	TextDrawSetProportional(PTD_PlayerAimedNick[playerid], 1);
	TextDrawSetShadow(PTD_PlayerAimedNick[playerid], 1);

	PTD_PlayerAimedInfo[playerid] = TextDrawCreate(565.000000, 332.000000, " ");
	TextDrawBackgroundColor(PTD_PlayerAimedInfo[playerid], 64);
	TextDrawFont(PTD_PlayerAimedInfo[playerid], 1);
	TextDrawLetterSize(PTD_PlayerAimedInfo[playerid], 0.170000, 0.699999);
	TextDrawColor(PTD_PlayerAimedInfo[playerid], -1);
	TextDrawSetOutline(PTD_PlayerAimedInfo[playerid], 0);
	TextDrawSetProportional(PTD_PlayerAimedInfo[playerid], 1);
	TextDrawSetShadow(PTD_PlayerAimedInfo[playerid], 1);	
}
//-----------------------------------------------------------------------------------------------------------
LayoutBottomBelt(playerid, bool:show) {
	new x;
	if(playerid != -1) {
		if(show == true) {
			for(x = 0; x < sizeof(TDBottomBeltStatic); x ++)	TextDrawShowForPlayer(playerid, TDBottomBeltStatic[x]);
			for(x = 0; x < sizeof(TDBottomBeltTeamLeft); x ++)	TextDrawShowForPlayer(playerid, TDBottomBeltTeamLeft[x]), TextDrawShowForPlayer(playerid, TDBottomBeltTeamRight[x]);
			for(x = 0; x < sizeof(TDBottomBeltCenter); x ++)	TextDrawShowForPlayer(playerid, TDBottomBeltCenter[x]);
		} else {
			for(x = 0; x < sizeof(TDBottomBeltStatic); x ++)	TextDrawHideForPlayer(playerid, TDBottomBeltStatic[x]);
			for(x = 0; x < sizeof(TDBottomBeltTeamLeft); x ++)	TextDrawHideForPlayer(playerid, TDBottomBeltTeamLeft[x]), TextDrawHideForPlayer(playerid, TDBottomBeltTeamRight[x]);
			for(x = 0; x < sizeof(TDBottomBeltCenter); x ++)	TextDrawHideForPlayer(playerid, TDBottomBeltCenter[x]);	
		}
	} else {
		if(show == true) {
			for(x = 0; x < sizeof(TDBottomBeltStatic); x ++)	TextDrawShowForAll(TDBottomBeltStatic[x]);
			for(x = 0; x < sizeof(TDBottomBeltTeamLeft); x ++)	TextDrawShowForAll(TDBottomBeltTeamLeft[x]), TextDrawShowForAll(TDBottomBeltTeamRight[x]);
			for(x = 0; x < sizeof(TDBottomBeltCenter); x ++)	TextDrawShowForAll(TDBottomBeltCenter[x]);
		} else {
			for(x = 0; x < sizeof(TDBottomBeltStatic); x ++)	TextDrawHideForAll(TDBottomBeltStatic[x]);
			for(x = 0; x < sizeof(TDBottomBeltTeamLeft); x ++)	TextDrawHideForAll(TDBottomBeltTeamLeft[x]), TextDrawHideForAll(TDBottomBeltTeamRight[x]);
			for(x = 0; x < sizeof(TDBottomBeltCenter); x ++)	TextDrawHideForAll(TDBottomBeltCenter[x]);	
		}	
	}
}
//-----------------------------------------------------------------------------------------------------------
LayoutPlayerHud(playerid, bool:show) {
	new x;
	if(show == true) {
		for(x = 0; x < sizeof(TDPlayerHudStatic); x ++)	TextDrawShowForPlayer(playerid, TDPlayerHudStatic[x]);	
		TextDrawShowForPlayer(playerid, PTD_PlayerHudNick[playerid]);
		TextDrawShowForPlayer(playerid, PTD_PlayerHudKills[playerid]);
		TextDrawShowForPlayer(playerid, PTD_PlayerHudDeaths[playerid]);
		TextDrawShowForPlayer(playerid, PTD_PlayerHudDamage[playerid]);
		TextDrawShowForPlayer(playerid, PTD_PlayerHudRespect[playerid]);
		TextDrawShowForPlayer(playerid, PTD_PlayerHudRanking[playerid]);
	} else {
		for(x = 0; x < sizeof(TDPlayerHudStatic); x ++)	TextDrawHideForPlayer(playerid, TDPlayerHudStatic[x]);	
		for(x = 0; x < sizeof(TDPlayerHudTeam); x ++)	TextDrawHideForPlayer(playerid, TDPlayerHudTeam[x]);	
		TextDrawHideForPlayer(playerid, PTD_PlayerHudNick[playerid]);
		TextDrawHideForPlayer(playerid, PTD_PlayerHudKills[playerid]);
		TextDrawHideForPlayer(playerid, PTD_PlayerHudDeaths[playerid]);
		TextDrawHideForPlayer(playerid, PTD_PlayerHudDamage[playerid]);
		TextDrawHideForPlayer(playerid, PTD_PlayerHudRespect[playerid]);
		TextDrawHideForPlayer(playerid, PTD_PlayerHudRanking[playerid]);
	}
}
//-----------------------------------------------------------------------------------------------------------
LayoutPlayerCapture(playerid, bool:show) {
	new x;
	if(playerid != -1) {
		if(show == true) {
			for(x = 0; x < sizeof(TDCaptureStatic); x ++)	TextDrawShowForPlayer(playerid, TDCaptureStatic[x]);
			TextDrawShowForPlayer(playerid, TDCaptureInfo);
			TextDrawShowForPlayer(playerid, TDCaptureBox);
		} else {
			for(x = 0; x < sizeof(TDCaptureStatic); x ++)	TextDrawHideForPlayer(playerid, TDCaptureStatic[x]);
			TextDrawHideForPlayer(playerid, TDCaptureInfo);
			TextDrawHideForPlayer(playerid, TDCaptureBox);
		}
	} else {
		if(show == true) {
			for(x = 0; x < sizeof(TDCaptureStatic); x ++)	TextDrawShowForAll(TDCaptureStatic[x]);
			TextDrawShowForAll(TDCaptureInfo);
			TextDrawShowForAll(TDCaptureBox);
		} else {
			for(x = 0; x < sizeof(TDCaptureStatic); x ++)	TextDrawHideForAll(TDCaptureStatic[x]);
			TextDrawHideForAll(TDCaptureInfo);
			TextDrawHideForAll(TDCaptureBox);
		}	
	}
}
//-----------------------------------------------------------------------------------------------------------
LayoutPlayerOneOnOne(playerid, bool:show) {
	if(playerid != -1) {
		if(show == true) {
			TextDrawShowForPlayer(playerid, TDOneOnOneStatic);
			TextDrawShowForPlayer(playerid, TDOneOnOne[0]);
			TextDrawShowForPlayer(playerid, TDOneOnOne[1]);
		} else {
			TextDrawHideForPlayer(playerid, TDOneOnOneStatic);
			TextDrawHideForPlayer(playerid, TDOneOnOne[0]);
			TextDrawHideForPlayer(playerid, TDOneOnOne[1]);
		}
	} else {
		if(show == true) {
			TextDrawShowForAll(TDOneOnOneStatic);
			TextDrawShowForAll(TDOneOnOne[0]);
			TextDrawShowForAll(TDOneOnOne[1]);
		} else {
			TextDrawHideForAll(TDOneOnOneStatic);
			TextDrawHideForAll(TDOneOnOne[0]);
			TextDrawHideForAll(TDOneOnOne[1]);
		}	
	}
}
//-----------------------------------------------------------------------------------------------------------
LayoutPlayerTrainingArena(playerid, bool:show) {
	new x;
	if(playerid != -1) {
		if(show == true) {
			for(x = 0; x < sizeof(TDTrainingArenaStatic); x ++)	TextDrawShowForPlayer(playerid, TDTrainingArenaStatic[x]);	
			TextDrawShowForPlayer(playerid, TDTrainingArenaInfo);	
		} else {
			for(x = 0; x < sizeof(TDTrainingArenaStatic); x ++)	TextDrawHideForPlayer(playerid, TDTrainingArenaStatic[x]);	
			TextDrawHideForPlayer(playerid, TDTrainingArenaInfo);	
		}
	} else {
		if(show == true) {
			for(x = 0; x < sizeof(TDTrainingArenaStatic); x ++)	TextDrawShowForAll(TDTrainingArenaStatic[x]);	
			TextDrawShowForAll(TDTrainingArenaInfo);	
		} else {
			for(x = 0; x < sizeof(TDTrainingArenaStatic); x ++)	TextDrawHideForAll(TDTrainingArenaStatic[x]);	
			TextDrawHideForAll(TDTrainingArenaInfo);	
		}	
	}
}
//-----------------------------------------------------------------------------------------------------------
LayoutSpecPlayer(playerid, bool:show) {
	new x;
	if(show == true) {
		for(x = 0; x < sizeof(TDSpecStatic); x ++)	TextDrawShowForPlayer(playerid, TDSpecStatic[x]);	
		TextDrawShowForPlayer(playerid, PTD_SpecNick[playerid]);
		TextDrawShowForPlayer(playerid, PTD_SpecHealth[playerid][0]),	TextDrawShowForPlayer(playerid, PTD_SpecHealth[playerid][1]);	
		TextDrawShowForPlayer(playerid, PTD_SpecArmor[playerid][0]),	TextDrawShowForPlayer(playerid, PTD_SpecArmor[playerid][1]);	
		TextDrawShowForPlayer(playerid, PTD_SpecWeapons[playerid][0]),	TextDrawShowForPlayer(playerid, PTD_SpecWeapons[playerid][1]);	
	} else {
		for(x = 0; x < sizeof(TDSpecStatic); x ++)	TextDrawHideForPlayer(playerid, TDSpecStatic[x]);	
		TextDrawHideForPlayer(playerid, PTD_SpecNick[playerid]);
		TextDrawHideForPlayer(playerid, PTD_SpecHealth[playerid][0]),	TextDrawHideForPlayer(playerid, PTD_SpecHealth[playerid][1]);	
		TextDrawHideForPlayer(playerid, PTD_SpecArmor[playerid][0]),	TextDrawHideForPlayer(playerid, PTD_SpecArmor[playerid][1]);	
		TextDrawHideForPlayer(playerid, PTD_SpecWeapons[playerid][0]),	TextDrawHideForPlayer(playerid, PTD_SpecWeapons[playerid][1]);	
	}		
}
//-----------------------------------------------------------------------------------------------------------
LayoutPlayerCountdown(playerid, bool:show, step = -1) {
	new x;
	if(playerid != -1) {
		if(show == true) {
			if(5 >= step >= 0) {
				for(x = 0; x < sizeof(TDCountdownVal); x ++)	TextDrawHideForPlayer(playerid, TDCountdownVal[x]);	
				TextDrawShowForPlayer(playerid, TDCountdownVal[step]);
			}
		} else {
			for(x = 0; x < sizeof(TDCountdownVal); x ++)	TextDrawHideForPlayer(playerid, TDCountdownVal[x]);		
		}
	} else {
		if(show == true) {
			if(5 >= step >= 0) {
				for(x = 0; x < sizeof(TDCountdownVal); x ++)	TextDrawHideForAll(TDCountdownVal[x]);	
				TextDrawShowForAll(TDCountdownVal[step]);			
			}
		} else {
			for(x = 0; x < sizeof(TDCountdownVal); x ++)	TextDrawHideForAll(TDCountdownVal[x]);	
		}	
	}
}

//-----------------------------------------------------------------------------------------------------------
LayoutPlayerRoundWin(playerid,  bool:show) {
	new x;
	if(playerid != -1) {
		if(show == true) {
			for(x = 0; x < sizeof(TDWinRoundStatic); x ++)	TextDrawShowForPlayer(playerid, TDWinRoundStatic[x]);	
			for(x = 0; x < sizeof(TDWinRoundInfo); x ++)	TextDrawShowForPlayer(playerid, TDWinRoundInfo[x]);	
			for(x = 0; x < sizeof(TDWinRoundStats); x ++)	TextDrawShowForPlayer(playerid, TDWinRoundStats[x]);	
		} else {
			for(x = 0; x < sizeof(TDWinRoundStatic); x ++)	TextDrawHideForPlayer(playerid, TDWinRoundStatic[x]);	
			for(x = 0; x < sizeof(TDWinRoundInfo); x ++)	TextDrawHideForPlayer(playerid, TDWinRoundInfo[x]);	
			for(x = 0; x < sizeof(TDWinRoundStats); x ++)	TextDrawHideForPlayer(playerid, TDWinRoundStats[x]);		
		}
	} else {
		if(show == true) {
			for(x = 0; x < sizeof(TDWinRoundStatic); x ++)	TextDrawShowForAll(TDWinRoundStatic[x]);	
			for(x = 0; x < sizeof(TDWinRoundInfo); x ++)	TextDrawShowForAll(TDWinRoundInfo[x]);	
			for(x = 0; x < sizeof(TDWinRoundStats); x ++)	TextDrawShowForAll(TDWinRoundStats[x]);		
		} else {
			for(x = 0; x < sizeof(TDWinRoundStatic); x ++)	TextDrawHideForAll(TDWinRoundStatic[x]);	
			for(x = 0; x < sizeof(TDWinRoundInfo); x ++)	TextDrawHideForAll(TDWinRoundInfo[x]);	
			for(x = 0; x < sizeof(TDWinRoundStats); x ++)	TextDrawHideForAll(TDWinRoundStats[x]);		
		}	
	}
}
//-----------------------------------------------------------------------------------------------------------
LayoutSpawnProtect(playerid,  bool:show) {
	if(playerid != -1) {
		if(show == true) {
			TextDrawShowForPlayer(playerid, TDWinSpawnProtectStatic);
			TextDrawShowForPlayer(playerid, TDWinSpawnProtectInfo);
		} else {
			TextDrawHideForPlayer(playerid, TDWinSpawnProtectStatic);
			TextDrawHideForPlayer(playerid, TDWinSpawnProtectInfo);	
		}
	} else {
		if(show == true) {
			TextDrawShowForAll(TDWinSpawnProtectStatic);
			TextDrawShowForAll(TDWinSpawnProtectInfo);
		} else {
			TextDrawHideForAll(TDWinSpawnProtectStatic);
			TextDrawHideForAll(TDWinSpawnProtectInfo);	
		}	
	}
}
//-----------------------------------------------------------------------------------------------------------
LayoutPingFPS(playerid, bool:show) {
	if(show == true) {
		TextDrawShowForPlayer(playerid, TDPingFPSStatic[0]);
		TextDrawShowForPlayer(playerid, TDPingFPSStatic[1]);
		TextDrawShowForPlayer(playerid, PTD_PingFPSPLoss[playerid][0]);
		TextDrawShowForPlayer(playerid, PTD_PingFPSPLoss[playerid][1]);
		TextDrawShowForPlayer(playerid, PTD_PingFPSPLoss[playerid][2]);
	} else {
		TextDrawHideForPlayer(playerid, TDPingFPSStatic[0]);
		TextDrawHideForPlayer(playerid, TDPingFPSStatic[1]);
		TextDrawHideForPlayer(playerid, PTD_PingFPSPLoss[playerid][0]);
		TextDrawHideForPlayer(playerid, PTD_PingFPSPLoss[playerid][1]);
		TextDrawHideForPlayer(playerid, PTD_PingFPSPLoss[playerid][2]);
	}
}
//-----------------------------------------------------------------------------------------------------------
LayoutTime(playerid, bool:show) {
	if(show == true) {
		TextDrawShowForPlayer(playerid, TDZegar);
		TextDrawShowForPlayer(playerid, TDData);
	} else {
		TextDrawHideForPlayer(playerid, TDZegar);
		TextDrawHideForPlayer(playerid, TDData);
	}
}
//-----------------------------------------------------------------------------------------------------------
/*
LayoutSmallLogo(playerid, bool:show) {
	if(show == true) {
		TextDrawShowForPlayer(playerid, TDHighSkillMaleLogo);
		TextDrawShowForPlayer(playerid, TDHighSkill2MaleLogo);
		TextDrawShowForPlayer(playerid, TDStronaMaleLogo);
		TextDrawShowForPlayer(playerid, TDOnlyForProMaleLogo);
		TextDrawShowForPlayer(playerid, TDAutorMaleLogo);
		TextDrawShowForPlayer(playerid, TDPasekMaleLogo);
	} else {
		TextDrawHideForPlayer(playerid, TDHighSkillMaleLogo);
		TextDrawHideForPlayer(playerid, TDHighSkill2MaleLogo);
		TextDrawHideForPlayer(playerid, TDStronaMaleLogo);
		TextDrawHideForPlayer(playerid, TDOnlyForProMaleLogo);
		TextDrawHideForPlayer(playerid, TDAutorMaleLogo);
		TextDrawHideForPlayer(playerid, TDPasekMaleLogo);
	}
}
*/
//-----------------------------------------------------------------------------------------------------------
LayoutHitEnemy(playerid, bool:show) {	
	new x;
	if(show == true) {
		for(x = 0; x < sizeof(TDHitedByStatic); x ++) TextDrawShowForPlayer(playerid, TDHitStatic[x]);
		TextDrawShowForPlayer(playerid, PTD_HitNick[playerid]);
		TextDrawShowForPlayer(playerid, PTD_HitInfo[playerid]);
	} else {
		for(x = 0; x < sizeof(TDHitedByStatic); x ++) TextDrawHideForPlayer(playerid, TDHitStatic[x]);
		TextDrawHideForPlayer(playerid, PTD_HitNick[playerid]);
		TextDrawHideForPlayer(playerid, PTD_HitInfo[playerid]);
	}
}
//-----------------------------------------------------------------------------------------------------------
LayoutHitBy(playerid, bool:show) {	
	new x;
	if(show == true) {
		for(x = 0; x < sizeof(TDHitedByStatic); x ++) TextDrawShowForPlayer(playerid, TDHitedByStatic[x]);
		TextDrawShowForPlayer(playerid, PTD_HitedByNick[playerid]);
		TextDrawShowForPlayer(playerid, PTD_HitedByInfo[playerid]);
	} else {
		for(x = 0; x < sizeof(TDHitedByStatic); x ++) TextDrawHideForPlayer(playerid, TDHitedByStatic[x]);
		TextDrawHideForPlayer(playerid, PTD_HitedByNick[playerid]);
		TextDrawHideForPlayer(playerid, PTD_HitedByInfo[playerid]);
	}
}
//-----------------------------------------------------------------------------------------------------------
LayoutAimedPlayerInfo(playerid, targetid) {
	if(getPlayerAimedInfoStatus(playerid) == 0) {
		static x;
		if(targetid != INVALID_PLAYER_ID) {
			static pName[MAX_PLAYER_NAME], string[32], Float:aimHealth, Float:aimArmor;
			GetPlayerName(targetid, pName, MAX_PLAYER_NAME);
			GetPlayerHealth(targetid, aimHealth);
			GetPlayerArmour(targetid, aimArmor);
			format(string, sizeof(string),"%.0f~n~%.0f~n~%d~n~%d~n~%.1f", aimHealth, aimArmor, GetPlayerPing(targetid), getPlayerFPS(targetid), getPlayerPLoss(targetid));
			TextDrawSetString(PTD_PlayerAimedNick[playerid], pName);
			TextDrawSetString(PTD_PlayerAimedInfo[playerid], string);
				
			for(x = 0; x < sizeof(TDAimedStatic); x ++) TextDrawShowForPlayer(playerid, TDAimedStatic[x]);
			TextDrawShowForPlayer(playerid, PTD_PlayerAimedNick[playerid]);
			TextDrawShowForPlayer(playerid, PTD_PlayerAimedInfo[playerid]);
		} else {
			for(x = 0; x < sizeof(TDAimedStatic); x ++) TextDrawHideForPlayer(playerid, TDAimedStatic[x]);
			TextDrawHideForPlayer(playerid, PTD_PlayerAimedNick[playerid]);
			TextDrawHideForPlayer(playerid, PTD_PlayerAimedInfo[playerid]);	
		}
	}
}



