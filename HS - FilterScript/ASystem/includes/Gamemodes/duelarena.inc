/*

*/
//===========================================================
//-----------------------------------------------------------
//===========================================================
#define PV_PLAYER_STATS_SETTING		"PVPlayerStatsSetting"
#define PV_PLAYER_CHAT_STATUS		"PVPlayerChatStatus"
#define PV_SPARING_INVITE_SETTING   "PlayerSparingInviteSetting"
#define	PV_PLAYER_FIGHT_STYLE		"PlayerFightStyle"
//------------------------------------------------------------------------------
#define	ONLINE_DATA		0
#define	ACCOUNT_DATA	1
getPlayerStatsSetting(playerid) return GetPVarInt(playerid, PV_PLAYER_STATS_SETTING);
setPlayerStatsSetting(playerid, status) return SetPVarInt(playerid, PV_PLAYER_STATS_SETTING, status == 1 ? ACCOUNT_DATA : ONLINE_DATA);
//------------------------------------------------------------------------------
#define CHAT_STATUS_LOCAL	0
#define CHAT_STATUS_GLOBAL	1
setPlayerChatStatus(playerid, status) SetPVarInt(playerid, PV_PLAYER_CHAT_STATUS, status == 0 ? CHAT_STATUS_LOCAL : CHAT_STATUS_GLOBAL);
getPlayerChatStatus(playerid) return GetPVarInt(playerid, PV_PLAYER_CHAT_STATUS);
//------------------------------------------------------------------------------
getPlayerSparingInviteStatus(playerid) return GetPVarInt(playerid, PV_SPARING_INVITE_SETTING);
setPlayerSparingInviteStatus(playerid, bool:enable) SetPVarInt(playerid, PV_SPARING_INVITE_SETTING, _:enable);
//------------------------------------------------------------------------------
#define PV_ALLOWSPEC_STATUS 		"PVPlayerAllowSpecStatus"
setPlayerAllowSpecStatus(playerid, bool:allow) SetPVarInt(playerid, PV_ALLOWSPEC_STATUS, allow == true ? 0 : 1);
getPlayerAllowSpecStatus(playerid) return GetPVarInt(playerid, PV_ALLOWSPEC_STATUS) == 0 ? 1 : 0;
//------------------------------------------------------------------------------
setPlayerFightStyle(playerid, style) {
	if(4 <= style <= 7) {
		SetPVarInt(playerid, PV_PLAYER_FIGHT_STYLE, style);
		SetPlayerFightingStyle(playerid, style);
		return 1;
	}
	return 0;
}
getPlayerFightStyle(playerid) return GetPVarInt(playerid, PV_PLAYER_FIGHT_STYLE);
//------------------------------------------------------------------------------
GameModeSaveSettingsList(playerid) {
	new string[64];
	format(string, sizeof(string), "|%d,%d,%d,%d,%d", getPlayerStatsSetting(playerid), getPlayerChatStatus(playerid), getPlayerSparingInviteStatus(playerid), getPlayerFightStyle(playerid), getPlayerAllowSpecStatus(playerid));
	return string;
}
//------------------------------------------------------------------------------
GameModeLoadSettingsList(playerid, response[]) {
	if(strlen(response) > 1) {
		new s_Stats, s_Chat, s_Invite, s_FightStyle, s_SpecAllow;
		sscanf(response, "p<,>ddddd", s_Stats, s_Chat, s_Invite, s_FightStyle, s_SpecAllow);
		setPlayerStatsSetting(playerid, s_Stats);
		setPlayerChatStatus(playerid, s_Chat);
		setPlayerSparingInviteStatus(playerid, s_Invite == 1 ? true : false);
		setPlayerFightStyle(playerid, s_FightStyle);
		setPlayerAllowSpecStatus(playerid, s_SpecAllow == 0 ? true : false);
		return 1;
	}
	return 0;
}
