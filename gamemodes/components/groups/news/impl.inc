#if defined _inc_impl
	#undef _inc_impl
#endif

CMD:news(playerid, params[]){
    if(!LoggedIn[playerid]) return 1;
    if(PlayerData[playerid][pGroup] == -1) return 1;
    if(GetGroupType(playerid) != GROUP_NEWS) return ErrorMsg(playerid, "คำสั่งนี้สำหรับนักข่าวเท่านั้น!");

    if (isnull(params)) return SystemMsg(playerid, "/news [messages]");
    if (strlen(params) > 64){
        foreach (new i : Player) if(LoggedIn[i]){
            SendClientMessageEx(i, 0xFF8A9EAA, "(( [NEWS] นักข่าว %s: %.64s ))", ReturnRoleplayName(playerid), params);
            SendClientMessageEx(i, 0xFF8A9EAA, "...%s ))", params[64]);
		}
	}
	else{
        foreach (new i : Player) if(LoggedIn[i]){
		    SendClientMessageEx(i, 0xFF8A9EAA, "(( [NEWS] นักข่าว %s: %s ))", ReturnRoleplayName(playerid), params);
		}
	}
    return 1;
}