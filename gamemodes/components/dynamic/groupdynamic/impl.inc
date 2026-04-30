#if defined _inc_impl
	#undef _inc_impl
#endif

forward Group_Load();
public Group_Load(){
    static rows, str[32];
	
    cache_get_row_count(rows);

    for(new i=0; i<rows; i++){

        GroupData[i][groupExists] = true;
        cache_get_value_name_int(i, "groupID", GroupData[i][groupID]);
        cache_get_value_name(i, "groupName", GroupData[i][groupName], 64);
        cache_get_value_name_int(i, "groupType", GroupData[i][groupType]);
        cache_get_value_name_int(i, "groupColor", GroupData[i][groupColor]);
        cache_get_value_name_int(i, "groupRanks", GroupData[i][groupRanks]);

        cache_get_value_name_float(i, "groupLockerPosX", GroupData[i][groupLockerPos][0]);
        cache_get_value_name_float(i, "groupLockerPosY", GroupData[i][groupLockerPos][1]);
        cache_get_value_name_float(i, "groupLockerPosZ", GroupData[i][groupLockerPos][2]);
		cache_get_value_name_int(i, "groupLockerInt", GroupData[i][groupLockerInt]);
		cache_get_value_name_int(i, "groupLockerWorld", GroupData[i][groupLockerWorld]);

		cache_get_value_name_float(i, "groupLocker2PosX", GroupData[i][groupLocker2Pos][0]);
        cache_get_value_name_float(i, "groupLocker2PosY", GroupData[i][groupLocker2Pos][1]);
        cache_get_value_name_float(i, "groupLocker2PosZ", GroupData[i][groupLocker2Pos][2]);
		cache_get_value_name_int(i, "groupLocker2Int", GroupData[i][groupLocker2Int]);
		cache_get_value_name_int(i, "groupLocker2World", GroupData[i][groupLocker2World]);

		cache_get_value_name_float(i, "groupLocker3PosX", GroupData[i][groupLocker3Pos][0]);
        cache_get_value_name_float(i, "groupLocker3PosY", GroupData[i][groupLocker3Pos][1]);
        cache_get_value_name_float(i, "groupLocker3PosZ", GroupData[i][groupLocker3Pos][2]);
		cache_get_value_name_int(i, "groupLocker3Int", GroupData[i][groupLocker3Int]);
		cache_get_value_name_int(i, "groupLocker3World", GroupData[i][groupLocker3World]);

		cache_get_value_name_int(i, "groupMoney", GroupData[i][groupMoney]);
		cache_get_value_name_int(i, "groupHoldZonePoint", GroupData[i][groupHoldZonePoint]);
		
		cache_get_value_name_int(i, "groupSkills1", GroupData[i][groupSkills][0]);
		cache_get_value_name_int(i, "groupSkills2", GroupData[i][groupSkills][1]);
		cache_get_value_name_int(i, "groupSkills3", GroupData[i][groupSkills][2]);
		cache_get_value_name_int(i, "groupSkills4", GroupData[i][groupSkills][3]);
		cache_get_value_name_int(i, "groupSkills5", GroupData[i][groupSkills][4]);

		cache_get_value_name_int(i, "groupWood", GroupData[i][groupWood]);
		cache_get_value_name_int(i, "groupPowder", GroupData[i][groupPowder]);
		cache_get_value_name_int(i, "groupOre", GroupData[i][groupOre]);
		cache_get_value_name_int(i, "groupRedMoney", GroupData[i][groupRedMoney]);
		cache_get_value_name_int(i, "groupKill", GroupData[i][groupKill]);

		for (new j = 0; j < 10; j ++) {
			format(str, sizeof(str), "groupWeapon%d", j + 1);
			cache_get_value_name_int(i, str, GroupData[i][groupWeapons][j]);
			format(str, sizeof(str), "groupAmmo%d", j + 1);
			cache_get_value_name_int(i, str, GroupData[i][groupAmmo][j]);

			if(j < 8){
				format(str, sizeof(str), "groupSkin%d", j + 1);
            	cache_get_value_name_int(i, str, GroupData[i][groupSkin][j]);
			}
		}

		for(new k=0; k<16; k++){
			format(str, sizeof(str), "groupRank%d", k + 1);
			cache_get_value_name(i, str, GroupRanks[i][k], 32);
		}

        Group_Count++;
        Group_Refresh(i);
    }
    printf("(( [MYSQL]: Load %d Group Successfully ))", Group_Count);
    return 1;
}

Group_Save(groupid)
{
	new
	    query[2048];

	format(query, sizeof(query), "UPDATE `groups` SET `groupName` = '%s', `groupColor` = '%d', `groupType` = '%d', `groupRanks` = '%d', `groupLockerPosX` = '%.4f', `groupLockerPosY` = '%.4f', `groupLockerPosZ` = '%.4f', `groupLockerInt` = '%d', `groupLockerWorld` = '%d'",
		SQL_ReturnEscaped(GroupData[groupid][groupName]),
		GroupData[groupid][groupColor],
		GroupData[groupid][groupType],
		GroupData[groupid][groupRanks],
		GroupData[groupid][groupLockerPos][0],
		GroupData[groupid][groupLockerPos][1],
		GroupData[groupid][groupLockerPos][2],
		GroupData[groupid][groupLockerInt],
		GroupData[groupid][groupLockerWorld]
	);
	for (new i = 0; i < 10; i ++)
	{
	    if (i < 8)
	    {
			format(query, sizeof(query), "%s, `groupSkin%d` = '%d', `groupWeapon%d` = '%d', `groupAmmo%d` = '%d'", query, i + 1, GroupData[groupid][groupSkin][i], i + 1, GroupData[groupid][groupWeapons][i], i + 1, GroupData[groupid][groupAmmo][i]);
		}
		else format(query, sizeof(query), "%s, `groupWeapon%d` = '%d', `groupAmmo%d` = '%d'", query, i + 1, GroupData[groupid][groupWeapons][i], i + 1, GroupData[groupid][groupAmmo][i]);
	}
	format(query, sizeof(query), "%s, `groupMoney` = '%d', `groupHoldZonePoint` = '%d', `groupSkills1` = '%d', `groupSkills2` = '%d', `groupSkills3` = '%d', `groupSkills4` = '%d', `groupSkills5` = '%d', `groupWood` = '%d', `groupPowder` = '%d', `groupOre` = '%d', `groupRedMoney` = '%d', `groupKill` = '%d'",
		query,
		GroupData[groupid][groupMoney],
		GroupData[groupid][groupHoldZonePoint],
		GroupData[groupid][groupSkills][0],
		GroupData[groupid][groupSkills][1],
		GroupData[groupid][groupSkills][2],
		GroupData[groupid][groupSkills][3],
		GroupData[groupid][groupSkills][4],
		GroupData[groupid][groupWood],
		GroupData[groupid][groupPowder],
		GroupData[groupid][groupOre],
		GroupData[groupid][groupRedMoney],
		GroupData[groupid][groupKill]
	);

	format(query, sizeof(query), "%s, `groupLocker2PosX` = '%.4f', `groupLocker2PosY` = '%.4f', `groupLocker2PosZ` = '%.4f', `groupLocker2Int` = '%d', `groupLocker2World` = '%d', `groupLocker3PosX` = '%.4f', `groupLocker3PosY` = '%.4f', `groupLocker3PosZ` = '%.4f', `groupLocker3Int` = '%d', `groupLocker3World` = '%d' WHERE `groupID` = '%d'",
		query,
		GroupData[groupid][groupLocker2Pos][0],
		GroupData[groupid][groupLocker2Pos][1],
		GroupData[groupid][groupLocker2Pos][2],
		GroupData[groupid][groupLocker2Int],
		GroupData[groupid][groupLocker2World],
		GroupData[groupid][groupLocker3Pos][0],
		GroupData[groupid][groupLocker3Pos][1],
		GroupData[groupid][groupLocker3Pos][2],
		GroupData[groupid][groupLocker3Int],
		GroupData[groupid][groupLocker3World],
		GroupData[groupid][groupID]
	);
	return mysql_tquery(dbCon, query);
}

stock Group_SaveRanks(groupid)
{
	new
	    query[1024];

	format(query, sizeof(query), "UPDATE `groups` SET `groupRank1` = '%s', `groupRank2` = '%s', `groupRank3` = '%s', `groupRank4` = '%s', `groupRank5` = '%s', `groupRank6` = '%s', `groupRank7` = '%s', `groupRank8` = '%s', `groupRank9` = '%s'",
	    GroupRanks[groupid][0],
	    GroupRanks[groupid][1],
	    GroupRanks[groupid][2],
	    GroupRanks[groupid][3],
	    GroupRanks[groupid][4],
	    GroupRanks[groupid][5],
		GroupRanks[groupid][6],
		GroupRanks[groupid][7],
		GroupRanks[groupid][8]
	);
	format(query, sizeof(query), "%s, `groupRank10` = '%s', `groupRank11` = '%s', `groupRank12` = '%s', `groupRank13` = '%s', `groupRank14` = '%s', `groupRank15` = '%s', `groupRank16` = '%s' WHERE `groupID` = '%d'",
		query,
		GroupRanks[groupid][9],
		GroupRanks[groupid][10],
		GroupRanks[groupid][11],
		GroupRanks[groupid][12],
		GroupRanks[groupid][13],
		GroupRanks[groupid][14],
		GroupRanks[groupid][15],
		GroupData[groupid][groupID]
	);
	return mysql_tquery(dbCon, query);
}

Group_Refresh(groupid){
    if(groupid != -1 && GroupData[groupid][groupExists]){
        new string[128];

        if(GroupData[groupid][groupLockerPos][0] != 0.0 && GroupData[groupid][groupLockerPos][1] != 0.0 && GroupData[groupid][groupLockerPos][2] != 0){
            if(IsValidDynamicPickup(GroupData[groupid][groupLockerPickup][0]))
                DestroyDynamicPickup(GroupData[groupid][groupLockerPickup][0]);

            if(IsValidDynamic3DTextLabel(GroupData[groupid][groupLockerText3D][0]))
                DestroyDynamic3DTextLabel(GroupData[groupid][groupLockerText3D][0]);

			if(GroupData[groupid][groupType] == GROUP_GANG){
				GroupData[groupid][groupLockerPickup][0] = CreateDynamicPickup(1314, 23, GroupData[groupid][groupLockerPos][0], GroupData[groupid][groupLockerPos][1], GroupData[groupid][groupLockerPos][2], GroupData[groupid][groupLockerWorld], GroupData[groupid][groupLockerInt]);
				format(string, sizeof(string), "{%06x}[%s]\nกดปุ่ม 'Y' เพื่อใช้งานคลังแก๊ง", GetGroupColor(groupid) >>> 8, GroupData[groupid][groupName]);
				GroupData[groupid][groupLockerText3D][0] = CreateDynamic3DTextLabel(string, -1, GroupData[groupid][groupLockerPos][0], GroupData[groupid][groupLockerPos][1], GroupData[groupid][groupLockerPos][2], 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, GroupData[groupid][groupLockerWorld], GroupData[groupid][groupLockerInt]);
			}
			else{
				GroupData[groupid][groupLockerPickup][0] = CreateDynamicPickup(1210, 23, GroupData[groupid][groupLockerPos][0], GroupData[groupid][groupLockerPos][1], GroupData[groupid][groupLockerPos][2], GroupData[groupid][groupLockerWorld], GroupData[groupid][groupLockerInt]);
				format(string, sizeof(string), "{%06x}[%s]\nกดปุ่ม 'Y' เพื่อเปิด Locker", GetGroupColor(groupid) >>> 8, GroupData[groupid][groupName]);
				GroupData[groupid][groupLockerText3D][0] = CreateDynamic3DTextLabel(string, -1, GroupData[groupid][groupLockerPos][0], GroupData[groupid][groupLockerPos][1], GroupData[groupid][groupLockerPos][2], 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, GroupData[groupid][groupLockerWorld], GroupData[groupid][groupLockerInt]);
			}
        }

		if(GroupData[groupid][groupLocker2Pos][0] != 0.0 && GroupData[groupid][groupLocker2Pos][1] != 0.0 && GroupData[groupid][groupLocker2Pos][2] != 0){
            if(IsValidDynamicPickup(GroupData[groupid][groupLockerPickup][1]))
                DestroyDynamicPickup(GroupData[groupid][groupLockerPickup][1]);

            if(IsValidDynamic3DTextLabel(GroupData[groupid][groupLockerText3D][1]))
                DestroyDynamic3DTextLabel(GroupData[groupid][groupLockerText3D][1]);

			if(GroupData[groupid][groupType] == GROUP_GANG){
				GroupData[groupid][groupLockerPickup][1] = CreateDynamicPickup(1314, 23, GroupData[groupid][groupLocker2Pos][0], GroupData[groupid][groupLocker2Pos][1], GroupData[groupid][groupLocker2Pos][2], GroupData[groupid][groupLocker2World], GroupData[groupid][groupLocker2Int]);
				format(string, sizeof(string), "{%06x}[%s]\nกดปุ่ม 'Y' เพื่อใช้งานคลังแก๊ง", GetGroupColor(groupid) >>> 8, GroupData[groupid][groupName]);
				GroupData[groupid][groupLockerText3D][1] = CreateDynamic3DTextLabel(string, -1, GroupData[groupid][groupLocker2Pos][0], GroupData[groupid][groupLocker2Pos][1], GroupData[groupid][groupLocker2Pos][2], 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, GroupData[groupid][groupLocker2World], GroupData[groupid][groupLocker2Int]);
			}
			else{
				GroupData[groupid][groupLockerPickup][1] = CreateDynamicPickup(1210, 23, GroupData[groupid][groupLocker2Pos][0], GroupData[groupid][groupLocker2Pos][1], GroupData[groupid][groupLocker2Pos][2], GroupData[groupid][groupLocker2World], GroupData[groupid][groupLocker2Int]);
				format(string, sizeof(string), "{%06x}[%s]\nกดปุ่ม 'Y' เพื่อเปิด Locker", GetGroupColor(groupid) >>> 8, GroupData[groupid][groupName]);
				GroupData[groupid][groupLockerText3D][1] = CreateDynamic3DTextLabel(string, -1, GroupData[groupid][groupLocker2Pos][0], GroupData[groupid][groupLocker2Pos][1], GroupData[groupid][groupLocker2Pos][2], 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, GroupData[groupid][groupLocker2World], GroupData[groupid][groupLocker2Int]);
			}
        }

		if(GroupData[groupid][groupLocker3Pos][0] != 0.0 && GroupData[groupid][groupLocker3Pos][1] != 0.0 && GroupData[groupid][groupLocker3Pos][2] != 0){
            if(IsValidDynamicPickup(GroupData[groupid][groupLockerPickup][2]))
                DestroyDynamicPickup(GroupData[groupid][groupLockerPickup][2]);

            if(IsValidDynamic3DTextLabel(GroupData[groupid][groupLockerText3D][2]))
                DestroyDynamic3DTextLabel(GroupData[groupid][groupLockerText3D][2]);

			if(GroupData[groupid][groupType] == GROUP_GANG){
				GroupData[groupid][groupLockerPickup][2] = CreateDynamicPickup(1314, 23, GroupData[groupid][groupLocker3Pos][0], GroupData[groupid][groupLocker3Pos][1], GroupData[groupid][groupLocker3Pos][2], GroupData[groupid][groupLocker3World], GroupData[groupid][groupLocker3Int]);
				format(string, sizeof(string), "{%06x}[%s]\nกดปุ่ม 'Y' เพื่อใช้งานคลังแก๊ง", GetGroupColor(groupid) >>> 8, GroupData[groupid][groupName]);
				GroupData[groupid][groupLockerText3D][2] = CreateDynamic3DTextLabel(string, -1, GroupData[groupid][groupLocker3Pos][0], GroupData[groupid][groupLocker3Pos][1], GroupData[groupid][groupLocker3Pos][2], 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, GroupData[groupid][groupLocker3World], GroupData[groupid][groupLocker3Int]);
			}
			else{
				GroupData[groupid][groupLockerPickup][2] = CreateDynamicPickup(1210, 23, GroupData[groupid][groupLocker3Pos][0], GroupData[groupid][groupLocker3Pos][1], GroupData[groupid][groupLocker3Pos][2], GroupData[groupid][groupLocker3World], GroupData[groupid][groupLocker3Int]);
				format(string, sizeof(string), "{%06x}[%s]\nกดปุ่ม 'Y' เพื่อเปิด Locker", GetGroupColor(groupid) >>> 8, GroupData[groupid][groupName]);
				GroupData[groupid][groupLockerText3D][2] = CreateDynamic3DTextLabel(string, -1, GroupData[groupid][groupLocker3Pos][0], GroupData[groupid][groupLocker3Pos][1], GroupData[groupid][groupLocker3Pos][2], 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, GroupData[groupid][groupLocker3World], GroupData[groupid][groupLocker3Int]);
			}
        }
    }
    return 1;
}

GetGroupColor(groupid)
{
	if (groupid == -1) {
		return 0xFFFFFF77;
	}
	else {
		return GroupData[groupid][groupColor];
	}
}

ResetGroup(playerid)
{
    PlayerData[playerid][pGroup] = -1;
    PlayerData[playerid][pGroupID] = -1;
    PlayerData[playerid][pGroupRank] = 0;
}

Group_GetName(playerid){
    new groupid = PlayerData[playerid][pGroup],
    name[32] = "ประชาชน";

    if(groupid == -1) return name;

    format(name, 32, GroupData[groupid][groupName]);
    return name;
}

Group_GetRank(playerid){
    new groupid = PlayerData[playerid][pGroup],
    name[32] = "ไม่มีตำแหน่ง";

    if(groupid == -1)
        return name;

    format(name, 32, GroupRanks[groupid][PlayerData[playerid][pGroupRank] - 1]);
    return name;
}

Group_Create(const name[], type){
    for(new i=0; i<MAX_GROUPS; i++) if(!GroupData[i][groupExists]){
        format(GroupData[i][groupName], 64, name);

        GroupData[i][groupExists] = true;
        GroupData[i][groupColor] = 0xFFFFFF00;
        GroupData[i][groupType] = type;
        GroupData[i][groupRanks] = 16;

        GroupData[i][groupLockerPos][0] = 0.0;
        GroupData[i][groupLockerPos][1] = 0.0;
        GroupData[i][groupLockerPos][2] = 0.0;
        GroupData[i][groupLockerInt] = 0;
        GroupData[i][groupLockerWorld] = 0;

		GroupData[i][groupLocker2Pos][0] = 0.0;
        GroupData[i][groupLocker2Pos][1] = 0.0;
        GroupData[i][groupLocker2Pos][2] = 0.0;
        GroupData[i][groupLocker2Int] = 0;
        GroupData[i][groupLocker2World] = 0;

		GroupData[i][groupLocker3Pos][0] = 0.0;
        GroupData[i][groupLocker3Pos][1] = 0.0;
        GroupData[i][groupLocker3Pos][2] = 0.0;
        GroupData[i][groupLocker3Int] = 0;
        GroupData[i][groupLocker3World] = 0;

		GroupData[i][groupHoldZonePoint] = 0;

        for(new j=0; j<8; j++)
            GroupData[i][groupSkin][j] = 0;
		for (new j = 0; j < 10; j ++) {
            GroupData[i][groupWeapons][j] = 0;
            GroupData[i][groupAmmo][j] = 0;
	    }
        for(new j=0; j<16; j++)
            format(GroupRanks[i][j], 32, "Rank %d", j+1);

        mysql_tquery(dbCon, "INSERT INTO `groups` (`groupType`) VALUES(0)", "OnGroupCreated", "d", i);
        return i;
    }
    return -1;
}

forward OnGroupCreated(groupid);
public OnGroupCreated(groupid){
    if(groupid == -1 || !GroupData[groupid][groupExists])
        return 0;

    GroupData[groupid][groupID] = cache_insert_id();

    Group_Save(groupid);
    Group_SaveRanks(groupid);
    return 1;
}

Group_Delete(groupid){
    if(groupid != -1 && GroupData[groupid][groupExists]){
        new string[64];

        format(string, sizeof(string), "DELETE FROM `groups` WHERE `groupID` = '%d' LIMIT 1", GroupData[groupid][groupID]);
		mysql_tquery(dbCon, string);

		format(string, sizeof(string), "UPDATE `characters` SET `Group` = '-1' WHERE `Group` = '%d'", GroupData[groupid][groupID]);
		mysql_tquery(dbCon, string);

        foreach(new i : Player){
            if(!LoggedIn[i]) continue;
			if(PlayerData[i][pGroup] == groupid){
				PlayerData[i][pGroup] = -1;
				PlayerData[i][pGroupID] = -1;
				PlayerData[i][pGroupRank] = 0;
			}
			if(PlayerData[i][pGroupEdit] == groupid){
				PlayerData[i][pGroupEdit] = -1;
			}
        }

        if (IsValidDynamicPickup(GroupData[groupid][groupLockerPickup][0]))
  			DestroyDynamicPickup(GroupData[groupid][groupLockerPickup][0]);

		if (IsValidDynamic3DTextLabel(GroupData[groupid][groupLockerText3D][0]))
  			DestroyDynamic3DTextLabel(GroupData[groupid][groupLockerText3D][0]);

		if (IsValidDynamicPickup(GroupData[groupid][groupLockerPickup][1]))
  			DestroyDynamicPickup(GroupData[groupid][groupLockerPickup][1]);

		if (IsValidDynamic3DTextLabel(GroupData[groupid][groupLockerText3D][1]))
  			DestroyDynamic3DTextLabel(GroupData[groupid][groupLockerText3D][1]);

		if (IsValidDynamicPickup(GroupData[groupid][groupLockerPickup][2]))
  			DestroyDynamicPickup(GroupData[groupid][groupLockerPickup][2]);

		if (IsValidDynamic3DTextLabel(GroupData[groupid][groupLockerText3D][2]))
  			DestroyDynamic3DTextLabel(GroupData[groupid][groupLockerText3D][2]);

        GroupData[groupid][groupExists] = false;
	    GroupData[groupid][groupType] = 0;
	    GroupData[groupid][groupID] = 0;
    }
    return 1;
}

ViewGroups(playerid){
    new string[2048], menu[20], count;

	format(string, sizeof(string), "%s{B4B5B7}หน้า 1{FFFFFF}\n", string);

	SetPVarInt(playerid, "page", 1);

	for (new i = 0; i != MAX_GROUPS; i ++) if (GroupData[i][groupExists]) {
		if(count == 20)
		{
			format(string, sizeof(string), "%s{B4B5B7}หน้า 2{FFFFFF}\n", string);
			break;
		}
		format(menu, 20, "menu%d", ++count);
		SetPVarInt(playerid, menu, i);
		format(string, sizeof(string), "%s{FFFFFF}({FFBF00}%i{FFFFFF}) | %s\n", string, i, GroupData[i][groupName]);
	}
	if(!count) Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "รายชื่อกลุ่ม", "ไม่พบข้อมูลของ Group นี้", "โอเค", "");
	else Dialog_ShowEasy(playerid, GroupList, DIALOG_STYLE_LIST, "รายชื่อกลุ่ม", string, "แก้ไข", "ปิด");
	return 1;
}

Dialog:GroupList(playerid, response, listitem, inputtext[])
{
	if(response) {

		new menu[20];
		if(listitem != 0 && listitem != 21) {
			new str_biz[8];
			format(str_biz, 20, "menu%d", listitem);

			PlayerData[playerid][pGroupEdit] = GetPVarInt(playerid, str_biz);
			ShowPlayerEditGroup(playerid);
			return true;
		}

		new currentPage = GetPVarInt(playerid, "page");
		if(listitem==0) {
			if(currentPage>1) currentPage--;
		}
		else if(listitem == 21) currentPage++;

		new string[2048], count;
		format(string, sizeof(string), "%s{B4B5B7}หน้า %d{FFFFFF}\n", string, (currentPage==1) ? 1 : currentPage-1);

		SetPVarInt(playerid, "page", currentPage);

		new skipitem = (currentPage-1) * 20;

		for (new i = 0; i != MAX_GROUPS; i ++) if (GroupData[i][groupExists]) {

			if(skipitem)
			{
				skipitem--;
				continue;
			}
			if(count == 20)
			{
				format(string, sizeof(string), "%s{B4B5B7}หน้า %d{FFFFFF}\n", string, (currentPage==1) ? 1 : currentPage+1);
				break;
			}
			format(menu, 20, "menu%d", ++count);
			SetPVarInt(playerid, menu, i);
			format(string, sizeof(string), "%s{FFFFFF}({FFBF00}%i{FFFFFF}) | %s\n", string, i, GroupData[i][groupName]);

		}

		Dialog_ShowEasy(playerid, GroupList, DIALOG_STYLE_LIST, "รายชื่อกลุ่ม", string, "แก้ไข", "ปิด");
	}
	return 1;
}

SetGroup(playerid, id)
{
	if (id != -1 && GroupData[id][groupExists])
	{
		PlayerData[playerid][pGroup] = id;
		PlayerData[playerid][pGroupID] = GroupData[id][groupID];
	}
	return 1;
}

GetGroupName(groupid)
{
    new
		name[32] = "None";

 	if (groupid == -1)
	    return name;

    format(name, 32, GroupData[groupid][groupName]);
	return name;
}

stock RemoveAlpha(color) {
    return (color & ~0xFF);
}

stock IsNearGroupLocker(playerid)
{
	new groupid = PlayerData[playerid][pGroup];

	if (groupid == -1)
	    return -1;

	if (IsPlayerInRangeOfPoint(playerid, 3.0, GroupData[groupid][groupLockerPos][0], GroupData[groupid][groupLockerPos][1], GroupData[groupid][groupLockerPos][2]) && GetPlayerInterior(playerid) == GroupData[groupid][groupLockerInt] && GetPlayerVirtualWorld(playerid) == GroupData[groupid][groupLockerWorld])
	    return groupid;

	if (IsPlayerInRangeOfPoint(playerid, 3.0, GroupData[groupid][groupLocker2Pos][0], GroupData[groupid][groupLocker2Pos][1], GroupData[groupid][groupLocker2Pos][2]) && GetPlayerInterior(playerid) == GroupData[groupid][groupLocker2Int] && GetPlayerVirtualWorld(playerid) == GroupData[groupid][groupLocker2World])
	    return groupid;

	if (IsPlayerInRangeOfPoint(playerid, 3.0, GroupData[groupid][groupLocker3Pos][0], GroupData[groupid][groupLocker3Pos][1], GroupData[groupid][groupLocker3Pos][2]) && GetPlayerInterior(playerid) == GroupData[groupid][groupLocker3Int] && GetPlayerVirtualWorld(playerid) == GroupData[groupid][groupLocker3World])
	    return groupid;

	return -1;
}

SetGroupColor(playerid)
{
	new groupid = PlayerData[playerid][pGroup];

	if (groupid != -1)
		return SetPlayerColor(playerid, RemoveAlpha(GroupData[groupid][groupColor]));

	return 0;
}

stock GetGroupTypeName(type)
{
	new string[32] = "ไม่ทราบ";

	switch(type)
	{
		case 1: format(string, 32, "ตำรวจ");
		case 2: format(string, 32, "หมอ/แพทย์");
		case 3: format(string, 32, "หน่วยรัฐบาล");
		case 4: format(string, 32, "ช่างยนต์");
		case 5: format(string, 32, "แก็งค์");
		case 6: format(string, 32, "หน่วยข่าวกรอง");
		case 7: format(string, 32, "นักข่าว");
	}
	return string;
}

stock ShowPlayerEditGroup(playerid)
{
	if(PlayerData[playerid][pGroupEdit] != -1 && GroupData[PlayerData[playerid][pGroupEdit]][groupExists])
	{
		new caption[128], dialog_str[1024], id = PlayerData[playerid][pGroupEdit];
		format(caption, sizeof(caption), "แก้ไขกลุ่ม: %s(%d)", GroupData[id][groupName], id);
        format(dialog_str, sizeof dialog_str, "ชื่อ\t%s\n", GroupData[id][groupName]);
        format(dialog_str, sizeof dialog_str, "%sสี\t{%06x}%06x\n", dialog_str, GroupData[id][groupColor] >>> 8, GroupData[id][groupColor]);
        format(dialog_str, sizeof dialog_str, "%sประเภท\t%s\n", dialog_str, GetGroupTypeName(GroupData[id][groupType]));
        format(dialog_str, sizeof dialog_str, "%sยศ\t%d/%d\n", dialog_str, GroupData[id][groupRanks], 16);
		format(dialog_str, sizeof dialog_str, "%sสกิน\n", dialog_str);
        format(dialog_str, sizeof dialog_str, "%sตั้งจุด Locker ที่ 1\t\n", dialog_str);
		format(dialog_str, sizeof dialog_str, "%sตั้งจุด Locker ที่ 2\t\n", dialog_str);
		format(dialog_str, sizeof dialog_str, "%sตั้งจุด Locker ที่ 3\t\n", dialog_str);
		Dialog_ShowEasy(playerid, GroupEdit, DIALOG_STYLE_TABLIST, caption, dialog_str, "เลือก", "กลับ");
	}
	return 1;
}

stock GetGroupType(playerid){
	if(!LoggedIn[playerid]) return 0;

	if (PlayerData[playerid][pGroup] == -1)
	    return 0;

	return (GroupData[PlayerData[playerid][pGroup]][groupType]);
}

stock GetGroupByID(sqlid)
{
	for (new i = 0; i != MAX_GROUPS; i ++) if (GroupData[i][groupExists] && GroupData[i][groupID] == sqlid)
	    return i;

	return -1;
}

Dialog:GroupEdit(playerid, response, listitem, inputtext[])
{
	if(response) {

		new string[128];

		switch(listitem)
		{
			case 0: // Name
			{
				format(string, sizeof(string), "ชื่อกลุ่ม: %s", GroupData[PlayerData[playerid][pGroupEdit]][groupName]);
				Dialog_ShowEasy(playerid, GroupEdit_Name, DIALOG_STYLE_INPUT, "ตั้งค่าชื่อ", string, "เปลี่ยน", "กลับ");
			}
			case 1: // Color
			{
				format(string, sizeof(string), "สีกลุ่ม: {%06x}%06x\n{FFFFFF}ใช้รูปแบบ RGBA เช่น 0xFFFFFFAA\n(AA คือความสว่างหากต้องการให้โซนมีสีจาง ๆ ใช้ 50 แทน AA)", GroupData[PlayerData[playerid][pGroupEdit]][groupColor] >>> 8, GroupData[PlayerData[playerid][pGroupEdit]][groupColor]);
				Dialog_ShowEasy(playerid, GroupEdit_Color, DIALOG_STYLE_INPUT, "ตั้งค่าสี", string, "เปลี่ยน", "กลับ");
			}
			case 2: // Type
			{
				format(string, sizeof(string), "กลุ่มประเภท: %s\n\nเลือกหมายเลข 1: ตำรวจ | 2: หมอ | 3: รัฐบาล | 4: ช่างยนต์ | 5: แก็งค์ | 6: หน่วยข่าวกรอง", GetGroupTypeName(GroupData[PlayerData[playerid][pGroupEdit]][groupType]));
				Dialog_ShowEasy(playerid, GroupEdit_Type, DIALOG_STYLE_INPUT, "Edit Type", string, "เปลี่ยน", "กลับ");
			}
			case 3: // แก้ไขยศ
			{
				ShowEditRank(playerid, PlayerData[playerid][pGroupEdit]);
			}
			case 4: // สกิน
			{
				ShowEditSkin(playerid, PlayerData[playerid][pGroupEdit]);
			}
			case 5: // จุดเกิด
			{
				Dialog_ShowEasy(playerid, GroupEdit_Locker1, DIALOG_STYLE_MSGBOX, "ตั้งจุด Locker ที่ 1", "คุณแน่ใจหรือว่าที่จะตั้งจุด Locker ที่ 1 ตรงนี้", "ยืนยัน", "กลับ");
			}
			case 6: // จุดเกิด
			{
				Dialog_ShowEasy(playerid, GroupEdit_Locker2, DIALOG_STYLE_MSGBOX, "ตั้งจุด Locker ที่ 2", "คุณแน่ใจหรือว่าที่จะตั้งจุด Locker ที่ 2 ตรงนี้", "ยืนยัน", "กลับ");
			}
			case 7: // จุดเกิด
			{
				Dialog_ShowEasy(playerid, GroupEdit_Locker3, DIALOG_STYLE_MSGBOX, "ตั้งจุด Locker ที่ 3", "คุณแน่ใจหรือว่าที่จะตั้งจุด Locker ที่ 3 ตรงนี้", "ยืนยัน", "กลับ");
			}
		}
	}
	else
	{
	    PlayerData[playerid][pGroupEdit] = -1;
	}
}

Dialog:GroupEdit_Name(playerid, response, listitem, inputtext[])
{
	if(response) {
		new string[128];

		if(isnull(inputtext) || strlen(inputtext) >= 32) {
			format(string, sizeof(string), "ความยาวของชื่อต้องมากกว่า 0 และไม่เกินที่ถูกกำหนดไว้/n/nชื่อกลุ่ม: %s", GroupData[PlayerData[playerid][pGroupEdit]][groupName]);
			Dialog_ShowEasy(playerid, GroupEdit_Name, DIALOG_STYLE_INPUT, "แก้ไขชื่อ", string, "เปลี่ยน", "กลับ");
			return true;
		}
		format(GroupData[PlayerData[playerid][pGroupEdit]][groupName], 32, inputtext);
		Group_Refresh(PlayerData[playerid][pGroupEdit]);
		Group_Save(PlayerData[playerid][pGroupEdit]);
		format(string, sizeof(string), "ผู้ดูแล %s ได้ปรับชื่อของกลุ่มไอดี: %d เป็น \"%s\"", ReturnRoleplayName(playerid), PlayerData[playerid][pGroupEdit], inputtext);
        SendAdminsMessage(1, COLOR_GRAY, string);
	}
	return ShowPlayerEditGroup(playerid);
}

Dialog:GroupEdit_Color(playerid, response, listitem, inputtext[])
{
	if(response) {

		new string[128], color;
		if (sscanf(inputtext, "x", color)) {
			format(string, sizeof(string), "รูปแบบของสีไม่ถูกต้อง\n\nGroup Color: {%06x}CODE\nRGBA 0xFFFFFFAA", GroupData[PlayerData[playerid][pGroupEdit]][groupColor] >>> 8);
			Dialog_ShowEasy(playerid, GroupEdit_Color, DIALOG_STYLE_INPUT, "แก้ไขสี", string, "เปลี่ยน", "กลับ");
			return true;
		}

	    GroupData[PlayerData[playerid][pGroupEdit]][groupColor] = color;
	    Group_Refresh(PlayerData[playerid][pGroupEdit]);

	    Group_Save(PlayerData[playerid][pGroupEdit]);

		format(string, sizeof(string), "ผู้ดูแล %s ได้ปร{%06x}ั{FF6347}บ สี ของฝ่ายหรือกลุ่มไอดี: %d", ReturnRoleplayName(playerid), color >>> 8, PlayerData[playerid][pGroupEdit]);
        SendAdminsMessage(1, COLOR_GRAY, string);

	}
	return ShowPlayerEditGroup(playerid);
}

Dialog:GroupEdit_Type(playerid, response, listitem, inputtext[])
{
	if(response) {
		new string[128], typeint = strval(inputtext);

		if(typeint < 1 && typeint > 6) {
			format(string, sizeof(string), "ประเภทที่ระบุไม่ถูกต้องอยู่ระหว่าง 1 ถึง 5/n/nGroup Type: %s\n\nเลือกหมายเลข 1: ตำรวจ | 2: หมอ | 3: รัฐบาล | 4: ช่างยนต์ | 5: แก็งค์ | 6: หน่วยข่าวกรอง", GetGroupTypeName(GroupData[PlayerData[playerid][pGroupEdit]][groupType]));
			Dialog_ShowEasy(playerid, GroupEdit_Type, DIALOG_STYLE_INPUT, "แก้ไขประเภท", string, "เปลี่ยน", "กลับ");
			return true;
		}
	    GroupData[PlayerData[playerid][pGroupEdit]][groupType] = typeint;

	    Group_Refresh(PlayerData[playerid][pGroupEdit]);

	    Group_Save(PlayerData[playerid][pGroupEdit]);

		format(string, sizeof(string), "ผู้ดูแล %s ได้รับประเภทของกลุ่ม: %d เป็น %d", ReturnRoleplayName(playerid), PlayerData[playerid][pGroupEdit], typeint);
        SendAdminsMessage(1, COLOR_GRAY, string);
	}
	return ShowPlayerEditGroup(playerid);
}

Dialog:GroupEdit_Locker1(playerid, response, listitem, inputtext[]){
    if(response){
        new string[128];
        new Float:x, Float:y, Float:z;
        GetPlayerPos(playerid, x, y, z);
        GroupData[PlayerData[playerid][pGroupEdit]][groupLockerPos][0] = x;
        GroupData[PlayerData[playerid][pGroupEdit]][groupLockerPos][1] = y;
        GroupData[PlayerData[playerid][pGroupEdit]][groupLockerPos][2] = z;
        GroupData[PlayerData[playerid][pGroupEdit]][groupLockerInt] = GetPlayerInterior(playerid);
        GroupData[PlayerData[playerid][pGroupEdit]][groupLockerWorld] = GetPlayerVirtualWorld(playerid);
        Group_Refresh(PlayerData[playerid][pGroupEdit]);
        Group_Save(PlayerData[playerid][pGroupEdit]);
        format(string, sizeof(string), "ผู้ดูแล %s ได้ปรับตำแหน่ง Locker ที่ 1 ของกลุ่มไอดี: %d มายังจุดของเขา", ReturnRoleplayName(playerid), PlayerData[playerid][pGroupEdit]);
        SendAdminsMessage(1, COLOR_GRAY, string);
    }
    return ShowPlayerEditGroup(playerid);
}

Dialog:GroupEdit_Locker2(playerid, response, listitem, inputtext[]){
    if(response){
        new string[128];
        new Float:x, Float:y, Float:z;
        GetPlayerPos(playerid, x, y, z);
        GroupData[PlayerData[playerid][pGroupEdit]][groupLocker2Pos][0] = x;
        GroupData[PlayerData[playerid][pGroupEdit]][groupLocker2Pos][1] = y;
        GroupData[PlayerData[playerid][pGroupEdit]][groupLocker2Pos][2] = z;
        GroupData[PlayerData[playerid][pGroupEdit]][groupLocker2Int] = GetPlayerInterior(playerid);
        GroupData[PlayerData[playerid][pGroupEdit]][groupLocker2World] = GetPlayerVirtualWorld(playerid);
        Group_Refresh(PlayerData[playerid][pGroupEdit]);
        Group_Save(PlayerData[playerid][pGroupEdit]);
        format(string, sizeof(string), "ผู้ดูแล %s ได้ปรับตำแหน่ง Locker ที่ 2 ของกลุ่มไอดี: %d มายังจุดของเขา", ReturnRoleplayName(playerid), PlayerData[playerid][pGroupEdit]);
        SendAdminsMessage(1, COLOR_GRAY, string);
    }
    return ShowPlayerEditGroup(playerid);
}

Dialog:GroupEdit_Locker3(playerid, response, listitem, inputtext[]){
    if(response){
        new string[128];
        new Float:x, Float:y, Float:z;
        GetPlayerPos(playerid, x, y, z);
        GroupData[PlayerData[playerid][pGroupEdit]][groupLocker3Pos][0] = x;
        GroupData[PlayerData[playerid][pGroupEdit]][groupLocker3Pos][1] = y;
        GroupData[PlayerData[playerid][pGroupEdit]][groupLocker3Pos][2] = z;
        GroupData[PlayerData[playerid][pGroupEdit]][groupLocker3Int] = GetPlayerInterior(playerid);
        GroupData[PlayerData[playerid][pGroupEdit]][groupLocker3World] = GetPlayerVirtualWorld(playerid);
        Group_Refresh(PlayerData[playerid][pGroupEdit]);
        Group_Save(PlayerData[playerid][pGroupEdit]);
        format(string, sizeof(string), "ผู้ดูแล %s ได้ปรับตำแหน่ง Locker ที่ 3 ของกลุ่มไอดี: %d มายังจุดของเขา", ReturnRoleplayName(playerid), PlayerData[playerid][pGroupEdit]);
        SendAdminsMessage(1, COLOR_GRAY, string);
    }
    return ShowPlayerEditGroup(playerid);
}

CMD:groupcmds(playerid, params[]){
	if(!LoggedIn[playerid]) return 0;
    if(PlayerData[playerid][pAdmin] >= 1338){
        SendClientMessage(playerid, COLOR_DARKGREEN, "|-------------------------------------------------------------------------------------------|");
        SendClientMessage(playerid, COLOR_GRAY, "[GROUPCMDS]: /makegroup, /removegroup, /editgroup, /viewgroups");
        SendClientMessage(playerid, COLOR_DARKGREEN, "|-------------------------------------------------------------------------------------------|");
    }
    return 1;
}

CMD:viewgroups(playerid, params[]){
	if(!LoggedIn[playerid]) return 0;
    if(PlayerData[playerid][pAdmin] < 1338)
        return ErrorMsg(playerid, "8ุณไม่ได้รับอนุญาติ");

    ViewGroups(playerid);
    return 1;
}

CMD:makegroup(playerid, params[]){

	if(!LoggedIn[playerid]) return 0;
    new id = -1, type, name[32];

    if(PlayerData[playerid][pAdmin] >= 1338){
        if(sscanf(params, "ds[32]", type, name)){
            SystemMsg(playerid, "/makegroup [type] [name]");
            SendClientMessage(playerid, COLOR_YELLOW, "[Type]: 1: ตำรวจ | 2: หมอ | 3: รัฐบาล | 4: ช่างยนต์ | 5: แก็งค์ | 6: หน่วยข่าวกรอง | 7: นักข่าว");
            return 1;
        }

        if(type < 1 || type > 7)
            return ErrorMsg(playerid, "ประเภทที่ระบุไม่ถูกต้อง");

        id = Group_Create(name, type);

        if(id == -1)
            return ErrorMsg(playerid, "เซิฟเวอร์ได้สร้างกลุ่มเกินขีดจำกัดแล้ว");
 
        SendClientMessageEx(playerid, COLOR_WHITE, "- คุณได้ประสบความสำเร็จในการสร้างกลุ่มไอดี: %d", id);
    }
    return 1;
}

CMD:removegroup(playerid, params[]){
    
	if(!LoggedIn[playerid]) return 0;
    new id = -1;

    if(PlayerData[playerid][pAdmin] >= 1338){
        if(sscanf(params, "d", id))
            return SystemMsg(playerid, "/removegroup [groupid]");

        if ((id < 0 || id >= MAX_GROUPS) || !GroupData[id][groupExists])
	       return ErrorMsg(playerid, "คุณระบุไอดีกลุ่มไม่ถูกต้อง");

        Group_Delete(id);
        SendClientMessageEx(playerid, COLOR_WHITE, "- คุณได้ประสบความสำเร็จในการลบกลุ่มไอดี: %d", id);
    }
    return 1;
}

CMD:editgroup(playerid, params[]){
	if(!LoggedIn[playerid]) return 0;
    new id, type[24], string[128];
    if(PlayerData[playerid][pAdmin] >= 1338){
        if(sscanf(params, "ds[24]S()[128]", id, type, string)){
            SystemMsg(playerid, "/editgroup [id] [name]");
            SendClientMessage(playerid, COLOR_YELLOW, "[Name]: name, color, type, skin, ranks, maxranks, weaponlocker");
            return 1;
        }

        if ((id < 0 || id >= MAX_GROUPS) || !GroupData[id][groupExists])
	       return ErrorMsg(playerid, "คุณระบุไอดีกลุ่มไม่ถูกต้อง");

        if(!strcmp(type, "name", true)){
            new name[64];
            if(sscanf(string, "s[64]", name))
                return SystemMsg(playerid, "/editgroup [id] [name] [newname]");

            format(GroupData[id][groupName], 64, name);
            Group_Save(id);
            Group_Refresh(id);
            format(string, sizeof(string), "ผู้ดูแล %s ได้ปรับชื่อของกลุ่มไอดี: %d เป็น \"%s\"", ReturnRoleplayName(playerid), id, name);
		    SendAdminsMessage(1, COLOR_GRAY, string);
        }
        else if(!strcmp(type, "type", true)){
            new typeint;
            if(sscanf(string, "d", typeint)){
                SystemMsg(playerid, "/editgroup [id] [type] [group type]");
                SendClientMessage(playerid, COLOR_YELLOW, "[Type]: 1: ตำรวจ | 2: หมอ | 3: รัฐบาล | 4: ช่างยนต์ | 5: แก็งค์ | 6: หน่วยข่าวกรอง | 7: นักข่าว");
                return 1;
            }

            if(typeint < 1 || typeint > 7)
                return ErrorMsg(playerid, "ประเภทที่ระบุไม่ถูกต้อง");

            GroupData[id][groupType] = typeint;
            Group_Save(id);
            format(string, sizeof(string), "ผู้ดูแล %s ได้รับประเภทของกลุ่ม: %d เป็น %d", ReturnRoleplayName(playerid), id, typeint);
		    SendAdminsMessage(1, COLOR_GRAY, string);
        }
        else if(!strcmp(type, "color", true)){
            new color;
            if(sscanf(params, "d", color))
                return SystemMsg(playerid, "/editgroup [id] [color] [hex color]");

            GroupData[id][groupColor] = color;
            Group_Save(id);
            format(string, sizeof(string), "ผู้ดูแล %s ได้ปร{%06x}ั{FF6347}บ สี ของฝ่ายหรือกลุ่มไอดี: %d", ReturnRoleplayName(playerid), color >>> 8, id);
		    SendAdminsMessage(1, COLOR_GRAY, string);
        }
        else if(!strcmp(type, "skin", true)){
            ShowEditSkin(playerid, id);
        }
        else if(!strcmp(type, "ranks", true)){
            ShowEditRank(playerid, id);
        }
        else if(!strcmp(type, "maxranks", true)){
            new maxranks;
            if(sscanf(string, "d", maxranks))
                return SystemMsg(playerid, "/editgroup [id] [maxranks] [maxranks]");

            if(maxranks < 1 || maxranks > 16)
                return ErrorMsg(playerid, "ต้องกรอกระหว่าง 1-16");

            GroupData[id][groupRanks] = maxranks;
            Group_Save(id);
            format(string, sizeof(string), "ผู้ดูแล %s ได้รับยศสูงสุดของกลุ่ม: %d เป็น %d", ReturnRoleplayName(playerid), id, maxranks);
		    SendAdminsMessage(1, COLOR_GRAY, string);
        }
		else if (!strcmp(type, "weaponlocker", true))
		{
			PlayerData[playerid][pGroupEdit] = id;
			Dialog_ShowEasy(playerid, GroupLocker, DIALOG_STYLE_LIST, "Group Locker", "Locker Weapons", "Select", "Cancel");
		}
    }
    return 1;
}

ShowEditSkin(playerid, id){
    new caption[128];
    new stringskin[500];

    format(caption, sizeof(caption), "สกินของ %s", GroupData[id][groupName]);
    for(new i=0; i<8; i++){
        format(stringskin, sizeof(stringskin), "%s [%d] สกิน: %d\n", stringskin, i+1, GroupData[id][groupSkin][i]);
    }
    PlayerData[playerid][pGroupEdit] = id;
    Dialog_ShowEasy(playerid, EditGroupSkin, DIALOG_STYLE_LIST, caption, stringskin, "แก้ไข", "ยกเลิก");
}

Dialog:EditGroupSkin(playerid, response, listitem, inputtext[])
{
    if(!response){
        PlayerData[playerid][pGroupEdit] = -1;
        PlayerData[playerid][pSelectedSlot] = -1;
        return 1;
    }
	if (response)
	{
	    if (!GroupData[PlayerData[playerid][pGroupEdit]][groupExists])
			return 0;

		PlayerData[playerid][pSelectedSlot] = listitem;
		Dialog_ShowEasy(playerid, SetChangeSkin, DIALOG_STYLE_INPUT, "จัดการสกิน", "สกิน: %d\n\nกรุณากรอกเลขไอดีสกินด้านล่าง:", "ตกลง", "ยกเลิก", GroupData[PlayerData[playerid][pGroupEdit]][groupSkin], PlayerData[playerid][pSelectedSlot] + 1);
	}
	return 1;
}

Dialog:SetChangeSkin(playerid, response, listitem, inputtext[])
{
	if (response)
	{
        new skin = strval(inputtext);
	    if (isnull(inputtext))
            return Dialog_ShowEasy(playerid, SetChangeSkin, DIALOG_STYLE_INPUT, "จัดการสกิน", "สกิน: %d\n\nกรุณากรอกเลขไอดีสกินด้านล่าง:", "ตกลง", "ยกเลิก", GroupData[PlayerData[playerid][pGroupEdit]][groupSkin], PlayerData[playerid][pSelectedSlot] + 1);

	    if (skin < 0 || skin > 311)
	        return Dialog_ShowEasy(playerid, SetRankName, DIALOG_STYLE_INPUT, "จัดการสกิน", "ข้อผิดพลาด: ต้องกรอกสกิน (0-311) เท่านั้น\n\nสกิน: %d\n\nกรุณากรอกเลขไอดีสกินด้านล่าง:", "ตกลง", "ยกเลิก", GroupData[PlayerData[playerid][pGroupEdit]][groupSkin], PlayerData[playerid][pSelectedSlot] + 1);

		GroupData[PlayerData[playerid][pGroupEdit]][groupSkin][PlayerData[playerid][pSelectedSlot]] = skin;
		Group_Save(PlayerData[playerid][pGroupEdit]);

		ShowEditSkin(playerid, PlayerData[playerid][pGroupEdit]);

        new query[128];

		format(query, sizeof(query), "คุณปรับสกินลำดับ %d เป็น \"%s\"", PlayerData[playerid][pSelectedSlot] + 1, inputtext);
		SendClientMessage(playerid, COLOR_GRAD1, query);
	}
	return 1;
}

ShowEditRank(playerid, id){
    new caption[128];
    new stringrank[500];

    format(caption, sizeof(caption), "ยศของ %s", GroupData[id][groupName]);
    for(new i=0; i<GroupData[id][groupRanks]; i++){
        format(stringrank, sizeof(stringrank), "%s [%d] %s\n", stringrank, i+1, GroupRanks[id][i]);
    }
    PlayerData[playerid][pGroupEdit] = id;
    Dialog_ShowEasy(playerid, EditGroupRank, DIALOG_STYLE_LIST, caption, stringrank, "แก้ไข", "ยกเลิก");
}

Dialog:EditGroupRank(playerid, response, listitem, inputtext[])
{
    if(!response){
        PlayerData[playerid][pGroupEdit] = -1;
        PlayerData[playerid][pSelectedSlot] = -1;
        return 1;
    }
	if (response)
	{
	    if (!GroupData[PlayerData[playerid][pGroupEdit]][groupExists])
			return 0;

		PlayerData[playerid][pSelectedSlot] = listitem;
		Dialog_ShowEasy(playerid, SetRankName, DIALOG_STYLE_INPUT, "เปลี่ยนชื่อยศ", "ยศ: %s (%d)\n\nกรุณาป้อนชื่อยศใหม่ด้านล่างนี้:", "ตกลง", "ยกเลิก", GroupRanks[PlayerData[playerid][pGroupEdit]][PlayerData[playerid][pSelectedSlot]], PlayerData[playerid][pSelectedSlot] + 1);
	}
	return 1;
}

Dialog:SetRankName(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    if (isnull(inputtext))
			return Dialog_ShowEasy(playerid, SetRankName, DIALOG_STYLE_INPUT, "เปลี่ยนชื่อยศ", "ยศ: %s (%d)\n\nกรุณาป้อนชื่อยศใหม่ด้านล่างนี้:", "ตกลง", "ยกเลิก", GroupRanks[PlayerData[playerid][pGroupEdit]][PlayerData[playerid][pSelectedSlot]], PlayerData[playerid][pSelectedSlot] + 1);

	    if (strlen(inputtext) > 32)
	        return Dialog_ShowEasy(playerid, SetRankName, DIALOG_STYLE_INPUT, "เปลี่ยนชื่อยศ", "ข้อผิดพลาด: ยศต้องไม่มากกว่า 32 ตัวอักษร\n\nยศ: %s (%d)\n\nกรุณาป้อนชื่อยศใหม่ด้านล่างนี้:", "ตกลง", "ยกเลิก", GroupRanks[PlayerData[playerid][pGroupEdit]][PlayerData[playerid][pSelectedSlot]], PlayerData[playerid][pSelectedSlot] + 1);

		format(GroupRanks[PlayerData[playerid][pGroupEdit]][PlayerData[playerid][pSelectedSlot]], 32, inputtext);

		new
		    query[128],
			set_rank[32],
			clean_rank[32];

        mysql_escape_string(inputtext,clean_rank);

        format(set_rank, 32, "groupRank%d", PlayerData[playerid][pSelectedSlot] + 1);
		format(query, sizeof(query), "UPDATE `groups` SET `%s` = '%s' WHERE `groupID` = '%d'",
		    set_rank,
		    clean_rank,
		    GroupData[PlayerData[playerid][pGroupEdit]][groupID]
		);
		mysql_tquery(dbCon, query);

		ShowEditRank(playerid, PlayerData[playerid][pGroupEdit]);

		format(query, sizeof(query), "คุณได้ปรับชื่อยศ %d เป็น \"%s\"", PlayerData[playerid][pSelectedSlot] + 1, inputtext);
		SendClientMessage(playerid, COLOR_GRAD1, query);
	}
	return 1;
}

CMD:makeleader(playerid, params[]){
	if(!LoggedIn[playerid]) return 0;
	if(PlayerData[playerid][pAdmin] >= 1337){
		new userid, id;
		if(sscanf(params, "ud", userid, id)) return SystemMsg(playerid, "/makeleader [playerid] [group id]");
		if ((id < -1 || id >= MAX_GROUPS) || (id != -1 && !GroupData[id][groupExists])) return ErrorMsg(playerid, "คุณระบุกลุ่มไม่ถูกต้อง");
		if(userid == INVALID_PLAYER_ID) return ErrorMsg(playerid, "ไอดีผู้เล่นนั้นไม่ถูกต้อง");
		if(userid != INVALID_PLAYER_ID){
			if(LoggedIn[userid]){
				if(id == -1){
					ResetGroup(userid);
					PlayerData[userid][pTimeQuitGang] = 1;
					SendClientMessageEx(playerid, -1, "คุณได้ลบ %s ออกจากผู้นำกลุ่มแล้ว", ReturnRoleplayName(userid));
					SendClientMessage(userid, -1, "ผู้ดูแล ได้ลบคุณออกจากกลุ่ม");
					SetPlayerNameTag(userid, userid);
				}
				else{
					SetGroup(userid, id);
					PlayerData[userid][pGroupRank] = GroupData[id][groupRanks];
					SendClientMessageEx(playerid, -1, "คุณได้แต่งตั้งให้ %s เป็นผู้นำกลุ่ม %s", ReturnRoleplayName(userid), GroupData[id][groupName]);
					SendClientMessageEx(userid, -1, "ผู้ดูแล ได้แต่งตั้งให้คุณเป็นผู้นำกลุ่ม %s", GroupData[id][groupName]);
					SetPlayerNameTag(userid, userid);
				}
			}
		}
	}
	return 1;
}

CMD:asetrank(playerid, params[]){
	if(!LoggedIn[playerid]) return 0;
	new
		userid,
		rank,
		groupid;

    if (PlayerData[playerid][pAdmin] < 1337)
	    return ErrorMsg(playerid, "คุณไม่ได้รับอนุญาตให้ใช้คำสั่งนี้");

	if (sscanf(params, "ud", userid, rank))
	    return SystemMsg(playerid, "/asetrank [playerid/name] [rank id]");

	if (userid == INVALID_PLAYER_ID)
	    return ErrorMsg(playerid, "ผู้เล่นที่ระบุไม่ถูกต้อง");

	if ((groupid = PlayerData[userid][pGroup]) == -1)
	    return ErrorMsg(playerid, "ผู้เล่นนั้นไม่ใช่สมาชิกของฝ่ายหรือกลุ่มใด ๆ");

    if (rank < 1 || rank > GroupData[groupid][groupRanks])
        return ErrorMsg(playerid, "ยศไม่ถูกต้อง ยศของฝ่ายหรือกลุ่มนี้อยู่ระหว่าง 1 ถึง %d", GroupData[groupid][groupRanks]);

	PlayerData[userid][pGroupRank] = rank;

	SendClientMessageEx(playerid, -1, "คุณได้ตั้งค่ายศกลุ่มของ %s เป็น %d", ReturnRoleplayName(userid), rank);
    SendClientMessageEx(userid, -1, "ผู้ดูแล ได้ตั้งค่ายศกลุ่มของคุณเป็น %d", rank);

    return 1;
}

CMD:members(playerid, params[]){
	if(!LoggedIn[playerid]) return 0;
	new groupid = PlayerData[playerid][pGroup];
 	if (groupid == -1) return ErrorMsg(playerid, "คุณต้องเป็นสมาชิกของฝ่ายหรือกลุ่ม");
	SendClientMessage(playerid, COLOR_ORANGE, "Online Members:");
	foreach (new i : Player) {
		if(!LoggedIn[i]) continue;
		if (PlayerData[i][pGroup] != groupid) continue;
		SendClientMessageEx(playerid, COLOR_WHITE, "[ID: %d] %s - %s (%d)", i, ReturnRoleplayName(i), Group_GetRank(i), PlayerData[i][pGroupRank]);
	}
	return 1;
}

ShowGroupSkin(playerid, id){
    new caption[128];
    new stringskin[500];

    format(caption, sizeof(caption), "สกินของ %s", GroupData[id][groupName]);
    for(new i=0; i<8; i++){
        format(stringskin, sizeof(stringskin), "%s [%d] สกิน: %d\n", stringskin, i+1, GroupData[id][groupSkin][i]);
    }
    Dialog_ShowEasy(playerid, ChangeGroupSkin, DIALOG_STYLE_LIST, caption, stringskin, "เลือก", "ยกเลิก");
}

Dialog:ChangeGroupSkin(playerid, response, listitem, inputtext[])
{
    if(!response){
        return 1;
    }
	if (response)
	{
		new groupid = PlayerData[playerid][pGroup];
	    if (!GroupData[groupid][groupExists])
			return 0;

		if(GroupData[groupid][groupSkin][listitem] == 0)
			return ErrorMsg(playerid, "ช่องสกินนี้ยังไม่ได้ตั้ง");

		SetPlayerSkin(playerid, GroupData[groupid][groupSkin][listitem]);

		if(GetGroupType(playerid) == GROUP_MECHANIC){
			SetPlayerAttachedObject(playerid,6,19921,1,0.216999,-0.160000,0.131999,-95.599914,-179.800003,-53.200107,1.000000,1.000000,1.000000);
		}

		SendClientMessage(playerid, COLOR_YELLOW, "- คุณได้เปลี่ยนชุดเรียบร้อยแล้ว");
	}
	return 1;
}

stock SendGroupMessageEx(type, color, const str[], {Float,_}:...)
{
	static
	    args,
	    start,
	    end,
	    string[144]
	;
	#emit LOAD.S.pri 8
	#emit STOR.pri args

	if (args > 12)
	{
		#emit ADDR.pri str
		#emit STOR.pri start

	    for (end = start + (args - 12); end > start; end -= 4)
		{
	        #emit LREF.pri end
	        #emit PUSH.pri
		}
		#emit PUSH.S str
		#emit PUSH.C 144
		#emit PUSH.C string
		#emit PUSH.C args

		#emit SYSREQ.C format
		#emit LCTRL 5
		#emit SCTRL 4

		foreach (new i : Player) if (PlayerData[i][pGroup] != -1 && GetGroupType(i) == type) {
			if(LoggedIn[i])
		    	SendClientMessage(i, color, string);
		}
		return 1;
	}
	foreach (new i : Player) if (PlayerData[i][pGroup] != -1 && GetGroupType(i) == type) {
		if(LoggedIn[i])
 			SendClientMessage(i, color, str);
	}
	return 1;
}