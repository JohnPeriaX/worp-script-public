#if defined _inc_impl
	#undef _inc_impl
#endif

forward OnPlayerChangeWeapon(playerid, newWeapon, oldWeapon);
public OnPlayerChangeWeapon(playerid, newWeapon, oldWeapon)
{
	if(IsPlayerAttachedObjectSlotUsed(playerid, 0) && taser[playerid])
		SetPlayerArmedWeapon(playerid, 0);

	return 1;
}

forward EndTaserEffect(playerid);
public EndTaserEffect(playerid)
{
    TogglePlayerControllable(playerid, 1);
	IsPlayerTaser[playerid] = 0;
	TaserTime[playerid] = 0;
	ClearAnimations(playerid);
	SetPlayerDrunkLevel(playerid, 0);
	return 1;
}

forward GiveTaserAgain(playerid);
public GiveTaserAgain(playerid)
{
	RemovePlayerAttachedObject(playerid, 0);
	GivePlayerWeapon(playerid, TASER_WEAPON, 1);
    GiveTaserAgainTimer[playerid] = 0;
    GiveTaserAgainTimerEx[playerid] = 0;
    TaserTimeAG[playerid] = 0;
    TaserShoot[playerid] = 0;
    ApplyAnimation(playerid, "COLT45", "colt45_reload", 4.0, 0, 0, 0, 0, 0);
	return 1;
}

CMD:taser(playerid, params[])
{
    if(!LoggedIn[playerid]) return 0;
	if(GetGroupType(playerid) != GROUP_POLICE && GetGroupType(playerid) != GROUP_GOV && GetGroupType(playerid) != GROUP_NATIONAL)
		return SendClientMessage(playerid, COLOR_RED, "[!] {FFFFFF}คุณไม่ใช่เจ้าหน้าที่ตำรวจ/รัฐบาล");

    if (!BitFlag_Get(g_PlayerFlags[playerid], PLAYER_ONDUTY))
        return ErrorMsg(playerid, "คุณจำเป็นต้อง ON-DUTY ก่อน");

    if(PlayerEnterWarFlag[playerid]) return 1;

    new weapons, ammo, string[128];
    if(taser[playerid]) // Duty แล้ว , กำลังจะเก็บปืน
    {
        taser[playerid] = false;

        if(GiveTaserAgainTimer[playerid])
            KillTimer(GiveTaserAgainTimer[playerid]);

        if(IsPlayerAttachedObjectSlotUsed(playerid, 0))
        {
            RemovePlayerAttachedObject(playerid, 0);
        }
        GetPlayerWeaponData(playerid, 2, weapons, ammo);
        GivePlayerWeapon(playerid, weapons, -ammo);

        GivePlayerWeapon(playerid, PoliceLastWeapon[playerid], PoliceLastAmmo[playerid]);
        SetPlayerArmedWeapon(playerid, 0);
        ClearAnimations(playerid);

        OnPlayerChangeWeapon(playerid, GetPlayerWeapon(playerid), lastWeapon[playerid]);

        format(string,sizeof(string), "%s ได้เก็บ Taser", ReturnRoleplayName(playerid));
        SendNearbyMessage(playerid, 6.0, COLOR_RP, string);
    }
    else // ยังไม่ได้ duty , ยังไม่มีปืน
    {
        taser[playerid] = true;
        GetPlayerWeaponData(playerid, 2, PoliceLastWeapon[playerid], PoliceLastAmmo[playerid]);

        GetPlayerWeaponData(playerid, 2, weapons, ammo);
        GivePlayerWeapon(playerid, weapons, -ammo);

        GivePlayerWeapon(playerid, TASER_WEAPON, 1);

		lastWeapon[playerid] = GetPlayerWeapon(playerid);

        format(string,sizeof(string), "%s ได้หยิบ Taser ออกมาจากซองปืน", ReturnRoleplayName(playerid));
        SendNearbyMessage(playerid, 6.0, COLOR_RP, string);
    }
    return 1;
}