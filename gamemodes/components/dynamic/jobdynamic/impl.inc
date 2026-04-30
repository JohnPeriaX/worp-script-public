#if defined _inc_impl
	#undef _inc_impl
#endif

//Job

Job_GetPlateName(type){
	new
	    str[32];

	switch (type){
		case 1: str = "Farmer";
		case 2: str = "Building";
		case 3: str = "Fishing";
		case 4: str = "Gas Transport";
		case 5: str = "Cow Job";
		case 6: str = "Engineer";
		case 7: str = "Jelly Fish";
		case 8: str = "Weapon Dealer";
		case 9: str = "Trasher";
		case 10: str = "Rubber";
		case 11: str = "Clothing";
		case 12: str = "Seeker";
		case 13: str = "Gardener";
		case 14: str = "Oiller";
		case 15: str = "Sheller";
		case 16: str = "Oranger";
		case 17: str = "Shark Fish";
		case 18: str = "Pizza Job";
		case 19: str = "Oil Transport";
	    default: str = "Empty";
	}
	return str;
}

Job_GetName(type){
	new
	    str[32];

	switch (type){
		case 1: str = "ชาวนา";
		case 2: str = "ก่อสร้าง";
		case 3: str = "ชาวประมง";
		case 4: str = "ขนส่งแก๊ส";
		case 5: str = "ฆ่าวัว";
		case 6: str = "ช่างไฟ";
		case 7: str = "เก็บแมงกระพรุน";
		case 8: str = "พ่อค้าอาวุธ";
		case 9: str = "คนเก็บขยะ";
		case 10: str = "กรีดยาง";
		case 11: str = "ขนเสื้อผ้า";
		case 12: str = "หาสมบัติ";
		case 13: str = "คนดูแลสวน";
		case 14: str = "ขุดน้ำมัน";
		case 15: str = "เก็บหอย";
		case 16: str = "เก็บส้ม";
		case 17: str = "ตกปลาฉลาม";
		case 18: str = "ทำพิซซ่า";
		case 19: str = "ขนส่งน้ำมัน";
	    default: str = "ว่างงาน";
	}
	return str;
}

forward Job_Load();
public Job_Load()
{
	new
	    rows;

	cache_get_row_count(rows);

    for (new i = 0; i < rows; i ++) if (i < MAX_DYNAMIC_JOBS)
	{
	    JobData[i][jobExists] = true;

	    cache_get_value_name_int(i, "jobID", JobData[i][jobID]);
	    cache_get_value_name(i, "jobName", JobData[i][jobName], 32);
	    cache_get_value_name_int(i, "jobType", JobData[i][jobType]);
	    cache_get_value_name_float(i, "jobPosX", JobData[i][jobPos][0]);
	    cache_get_value_name_float(i, "jobPosY", JobData[i][jobPos][1]);
	    cache_get_value_name_float(i, "jobPosZ", JobData[i][jobPos][2]);
	    cache_get_value_name_int(i, "jobInterior", JobData[i][jobInterior]);
	    cache_get_value_name_int(i, "jobWorld", JobData[i][jobWorld]);
	    cache_get_value_name_float(i, "jobPointX", JobData[i][jobPoint][0]);
	    cache_get_value_name_float(i, "jobPointY", JobData[i][jobPoint][1]);
	    cache_get_value_name_float(i, "jobPointZ", JobData[i][jobPoint][2]);
		cache_get_value_name_float(i, "jobPoint2X", JobData[i][jobPoint2][0]);
	    cache_get_value_name_float(i, "jobPoint2Y", JobData[i][jobPoint2][1]);
	    cache_get_value_name_float(i, "jobPoint2Z", JobData[i][jobPoint2][2]);
	    cache_get_value_name_float(i, "jobDeliverX", JobData[i][jobDeliver][0]);
	    cache_get_value_name_float(i, "jobDeliverY", JobData[i][jobDeliver][1]);
	    cache_get_value_name_float(i, "jobDeliverZ", JobData[i][jobDeliver][2]);
	    cache_get_value_name_int(i, "jobPointInt", JobData[i][jobPointInt]);
	    cache_get_value_name_int(i, "jobPointWorld", JobData[i][jobPointWorld]);
		cache_get_value_name_int(i, "jobPoint2Int", JobData[i][jobPoint2Int]);
	    cache_get_value_name_int(i, "jobPoint2World", JobData[i][jobPoint2World]);
		cache_get_value_name_int(i, "jobDeliverInt", JobData[i][jobDeliverInt]);
	    cache_get_value_name_int(i, "jobDeliverWorld", JobData[i][jobDeliverWorld]);
		cache_get_value_name_int(i, "jobDeliverPrice", JobData[i][jobDeliverPrice]);
		cache_get_value_name_float(i, "jobActorAngle", JobData[i][jobActorAngle]);
		cache_get_value_name_int(i, "jobActorSkin", JobData[i][jobActorSkin]);
		cache_get_value_name_int(i, "jobLevel", JobData[i][jobLevel]);

        Total_Jobs_Created++;

 	    Job_Refresh(i);

	}
	printf("(( [MYSQL]: Load %d Job Successfully ))", Total_Jobs_Created);
	return 1;
}

Job_NearestPoint(playerid, Float:radius = 3.5)
{
    for (new i = 0; i != MAX_DYNAMIC_JOBS; i ++) if (JobData[i][jobExists] && IsPlayerInRangeOfPoint(playerid, radius, JobData[i][jobPoint][0], JobData[i][jobPoint][1], JobData[i][jobPoint][2])) {
		return i;
	}
	return -1;
}

Job_NearestPointFishShark(playerid, Float:radius = 60.0)
{
    for (new i = 0; i != MAX_DYNAMIC_JOBS; i ++) if (JobData[i][jobExists] && JobData[i][jobType] == SHARKJOB && IsPlayerInRangeOfPoint(playerid, radius, JobData[i][jobPoint][0], JobData[i][jobPoint][1], JobData[i][jobPoint][2])) {
		return i;
	}
	return -1;
}

Job_NearestPoint2Fish(playerid, Float:radius = 60.0)
{
    for (new i = 0; i != MAX_DYNAMIC_JOBS; i ++) if (JobData[i][jobExists] && JobData[i][jobType] == FISHJOB && IsPlayerInRangeOfPoint(playerid, radius, JobData[i][jobPoint2][0], JobData[i][jobPoint2][1], JobData[i][jobPoint2][2])) {
		return i;
	}
	return -1;
}

Job_NearestPoint2Farmer(playerid, Float:radius = 7.0)
{
    for (new i = 0; i != MAX_DYNAMIC_JOBS; i ++) if (JobData[i][jobExists] && JobData[i][jobType] == FARMERJOB && IsPlayerInRangeOfPoint(playerid, radius, JobData[i][jobPoint2][0], JobData[i][jobPoint2][1], JobData[i][jobPoint2][2])) {
		return i;
	}
	return -1;
}

Job_NearestPoint2(playerid, Float:radius = 3.5)
{
    for (new i = 0; i != MAX_DYNAMIC_JOBS; i ++) if (JobData[i][jobExists] && IsPlayerInRangeOfPoint(playerid, radius, JobData[i][jobPoint2][0], JobData[i][jobPoint2][1], JobData[i][jobPoint2][2])) {
		return i;
	}
	return -1;
}

GetClosestJob(playerid, type)
{
	new
	    Float:fDistance[2] = {99999.0, 0.0},
	    iIndex = -1
	;
	for (new i = 0; i < MAX_DYNAMIC_JOBS; i ++) if (JobData[i][jobExists] && JobData[i][jobType] == type && GetPlayerInterior(playerid) == JobData[i][jobInterior] && GetPlayerVirtualWorld(playerid) == JobData[i][jobWorld])
	{
		fDistance[1] = GetPlayerDistanceFromPoint(playerid, JobData[i][jobPos][0], JobData[i][jobPos][1], JobData[i][jobPos][2]);

		if (fDistance[1] < fDistance[0])
		{
		    fDistance[0] = fDistance[1];
		    iIndex = i;
		}
	}
	return iIndex;
}

GetClosestJobPoint(playerid, type)
{
	new
	    Float:fDistance[2] = {99999.0, 0.0},
	    iIndex = -1
	;
	for (new i = 0; i < MAX_DYNAMIC_JOBS; i ++) if (JobData[i][jobExists] && JobData[i][jobType] == type && GetPlayerInterior(playerid) == JobData[i][jobInterior] && GetPlayerVirtualWorld(playerid) == JobData[i][jobWorld])
	{
		fDistance[1] = GetPlayerDistanceFromPoint(playerid, JobData[i][jobPoint][0], JobData[i][jobPoint][1], JobData[i][jobPoint][2]);

		if (fDistance[1] < fDistance[0])
		{
		    fDistance[0] = fDistance[1];
		    iIndex = i;
		}
	}
	return iIndex;
}

GetClosestJobPoint2(playerid, type)
{
	new
	    Float:fDistance[2] = {99999.0, 0.0},
	    iIndex = -1
	;
	for (new i = 0; i < MAX_DYNAMIC_JOBS; i ++) if (JobData[i][jobExists] && JobData[i][jobType] == type && GetPlayerInterior(playerid) == JobData[i][jobInterior] && GetPlayerVirtualWorld(playerid) == JobData[i][jobWorld])
	{
		fDistance[1] = GetPlayerDistanceFromPoint(playerid, JobData[i][jobPoint2][0], JobData[i][jobPoint2][1], JobData[i][jobPoint2][2]);

		if (fDistance[1] < fDistance[0])
		{
		    fDistance[0] = fDistance[1];
		    iIndex = i;
		}
	}
	return iIndex;
}

GetClosestJobDeliver(playerid, type)
{
	new
	    Float:fDistance[2] = {99999.0, 0.0},
	    iIndex = -1
	;
	for (new i = 0; i < MAX_DYNAMIC_JOBS; i ++) if (JobData[i][jobExists] && JobData[i][jobType] == type && GetPlayerInterior(playerid) == JobData[i][jobInterior] && GetPlayerVirtualWorld(playerid) == JobData[i][jobWorld])
	{
		fDistance[1] = GetPlayerDistanceFromPoint(playerid, JobData[i][jobDeliver][0], JobData[i][jobDeliver][1], JobData[i][jobDeliver][2]);

		if (fDistance[1] < fDistance[0])
		{
		    fDistance[0] = fDistance[1];
		    iIndex = i;
		}
	}
	return iIndex;
}

Job_NearestDelivery(playerid, Float:radius = 4.0)
{
    for (new i = 0; i != MAX_DYNAMIC_JOBS; i ++) if (JobData[i][jobExists] && IsPlayerInRangeOfPoint(playerid, radius, JobData[i][jobDeliver][0], JobData[i][jobDeliver][1], JobData[i][jobDeliver][2])) {
		return i;
	}
	return -1;
}

Job_Nearest(playerid)
{
    for (new i = 0; i != MAX_DYNAMIC_JOBS; i ++) if (JobData[i][jobExists] && IsPlayerInRangeOfPoint(playerid, 2.5, JobData[i][jobPos][0], JobData[i][jobPos][1], JobData[i][jobPos][2]))
	{
		if (GetPlayerInterior(playerid) == JobData[i][jobInterior] && GetPlayerVirtualWorld(playerid) == JobData[i][jobWorld])
			return i;
	}
	return -1;
}

Job_Refresh(jobid){
	if (jobid != -1 && JobData[jobid][jobExists])
	{
	    for (new i = 0; i < 4; i ++) {
			if (IsValidDynamic3DTextLabel(JobData[jobid][jobText3D][i]) && JobData[jobid][jobText3D][i])
		    	DestroyDynamic3DTextLabel(JobData[jobid][jobText3D][i]);

			if (IsValidDynamicPickup(JobData[jobid][jobPickups][i]) && JobData[jobid][jobPickups][i])
		    	DestroyDynamicPickup(JobData[jobid][jobPickups][i]);
		}

		if(JobData[jobid][jobActorCheck] == 1)
			DestroyActor(JobData[jobid][jobDeliverActor]);

		new
		    string1[128];

		format(string1, sizeof(string1), "[%s]\nกดปุ่ม 'Y' เพื่อสมัครงานนี้\n{FF0000}(( [คำเตือน]: คุณจะเสียเงิน $500 ในการสมัครงานนี้ ))\n(( เลเวลที่ต้องการ: %d ))", Job_GetName(JobData[jobid][jobType]), JobData[jobid][jobLevel]);
		JobData[jobid][jobText3D][0] = CreateDynamic3DTextLabel(string1, 0xFF0000FF, JobData[jobid][jobPos][0], JobData[jobid][jobPos][1], JobData[jobid][jobPos][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, JobData[jobid][jobWorld], JobData[jobid][jobInterior]);
	    JobData[jobid][jobPickups][0] = CreateDynamicPickup(19132, 23, JobData[jobid][jobPos][0], JobData[jobid][jobPos][1], JobData[jobid][jobPos][2], JobData[jobid][jobWorld], JobData[jobid][jobInterior]);

		if (JobData[jobid][jobType] == 1)
		{
		    format(string1, sizeof(string1), "[%s]\nกด 'Y' เพื่อเริ่มทำงาน", Job_GetName(JobData[jobid][jobType]));
		    JobData[jobid][jobText3D][1] = CreateDynamic3DTextLabel(string1, 0xFF0000FF, JobData[jobid][jobPoint][0], JobData[jobid][jobPoint][1], JobData[jobid][jobPoint][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, JobData[jobid][jobPointWorld], JobData[jobid][jobPointInt]);
			JobData[jobid][jobPickups][1] = CreateDynamicPickup(1239, 23, JobData[jobid][jobPoint][0], JobData[jobid][jobPoint][1], JobData[jobid][jobPoint][2], JobData[jobid][jobPointWorld], JobData[jobid][jobPointInt]);
		
			format(string1, sizeof(string1), "[%s]\nกด 'Y' เพื่อแปรรูปข้าว", Job_GetName(JobData[jobid][jobType]));
			JobData[jobid][jobText3D][2] = CreateDynamic3DTextLabel(string1, 0xFF0000FF, JobData[jobid][jobPoint2][0], JobData[jobid][jobPoint2][1], JobData[jobid][jobPoint2][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, JobData[jobid][jobPoint2World], JobData[jobid][jobPoint2Int]);
			JobData[jobid][jobPickups][2] = CreateDynamicPickup(1239, 23, JobData[jobid][jobPoint2][0], JobData[jobid][jobPoint2][1], JobData[jobid][jobPoint2][2], JobData[jobid][jobPoint2World], JobData[jobid][jobPoint2Int]);

			format(string1, sizeof(string1), "[%s]\nกด 'Y' เพื่อขายข้าว", Job_GetName(JobData[jobid][jobType]));
			JobData[jobid][jobText3D][3] = CreateDynamic3DTextLabel(string1, 0xFF0000FF, JobData[jobid][jobDeliver][0], JobData[jobid][jobDeliver][1], JobData[jobid][jobDeliver][2]+1.2, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, JobData[jobid][jobDeliverWorld], JobData[jobid][jobDeliverInt]);
			JobData[jobid][jobDeliverActor] = CreateActor(JobData[jobid][jobActorSkin], JobData[jobid][jobDeliver][0], JobData[jobid][jobDeliver][1], JobData[jobid][jobDeliver][2], JobData[jobid][jobActorAngle]);
			JobData[jobid][jobActorCheck] = 1;
		}

		if (JobData[jobid][jobType] == 2)
		{
		    format(string1, sizeof(string1), "[%s]\nกด 'Y' เพื่อเปลี่ยนชุดทำงาน", Job_GetName(JobData[jobid][jobType]));
		    JobData[jobid][jobText3D][1] = CreateDynamic3DTextLabel(string1, 0xFF0000FF, JobData[jobid][jobPoint][0], JobData[jobid][jobPoint][1], JobData[jobid][jobPoint][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, JobData[jobid][jobPointWorld], JobData[jobid][jobPointInt]);
			JobData[jobid][jobPickups][1] = CreateDynamicPickup(1275, 23, JobData[jobid][jobPoint][0], JobData[jobid][jobPoint][1], JobData[jobid][jobPoint][2], JobData[jobid][jobPointWorld], JobData[jobid][jobPointInt]);
		
			format(string1, sizeof(string1), "[%s]\nกด 'Y' เพื่อแบกปูน", Job_GetName(JobData[jobid][jobType]));
			JobData[jobid][jobText3D][2] = CreateDynamic3DTextLabel(string1, 0xFF0000FF, JobData[jobid][jobPoint2][0], JobData[jobid][jobPoint2][1], JobData[jobid][jobPoint2][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, JobData[jobid][jobPoint2World], JobData[jobid][jobPoint2Int]);
			JobData[jobid][jobPickups][2] = CreateDynamicPickup(1239, 23, JobData[jobid][jobPoint2][0], JobData[jobid][jobPoint2][1], JobData[jobid][jobPoint2][2], JobData[jobid][jobPoint2World], JobData[jobid][jobPoint2Int]);

			format(string1, sizeof(string1), "[%s]\nจุดส่งปูน", Job_GetName(JobData[jobid][jobType]));
			JobData[jobid][jobText3D][3] = CreateDynamic3DTextLabel(string1, 0xFF0000FF, JobData[jobid][jobDeliver][0], JobData[jobid][jobDeliver][1], JobData[jobid][jobDeliver][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, JobData[jobid][jobDeliverWorld], JobData[jobid][jobDeliverInt]);
			JobData[jobid][jobPickups][3] = CreateDynamicPickup(1239, 23, JobData[jobid][jobDeliver][0], JobData[jobid][jobDeliver][1], JobData[jobid][jobDeliver][2], JobData[jobid][jobDeliverWorld], JobData[jobid][jobDeliverInt]);
		}

		if (JobData[jobid][jobType] == 3)
		{
		    /*format(string1, sizeof(string1), "[%s]\nกด 'Y' เพื่อเช่าเรือ", Job_GetName(JobData[jobid][jobType]));
		    JobData[jobid][jobText3D][1] = CreateDynamic3DTextLabel(string1, 0xFF0000FF, JobData[jobid][jobPoint][0], JobData[jobid][jobPoint][1], JobData[jobid][jobPoint][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, JobData[jobid][jobPointWorld], JobData[jobid][jobPointInt]);
			JobData[jobid][jobPickups][1] = CreateDynamicPickup(1239, 23, JobData[jobid][jobPoint][0], JobData[jobid][jobPoint][1], JobData[jobid][jobPoint][2], JobData[jobid][jobPointWorld], JobData[jobid][jobPointInt]);
		*/
			format(string1, sizeof(string1), "[%s]\nจุดตกปลา", Job_GetName(JobData[jobid][jobType]));
			JobData[jobid][jobText3D][2] = CreateDynamic3DTextLabel(string1, 0xFF0000FF, JobData[jobid][jobPoint2][0], JobData[jobid][jobPoint2][1], JobData[jobid][jobPoint2][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, JobData[jobid][jobPoint2World], JobData[jobid][jobPoint2Int]);
			JobData[jobid][jobPickups][2] = CreateDynamicPickup(1239, 23, JobData[jobid][jobPoint2][0], JobData[jobid][jobPoint2][1], JobData[jobid][jobPoint2][2], JobData[jobid][jobPoint2World], JobData[jobid][jobPoint2Int]);

			format(string1, sizeof(string1), "[%s]\nกด 'Y' เพื่อขายปลา", Job_GetName(JobData[jobid][jobType]));
			JobData[jobid][jobText3D][3] = CreateDynamic3DTextLabel(string1, 0xFF0000FF, JobData[jobid][jobDeliver][0], JobData[jobid][jobDeliver][1], JobData[jobid][jobDeliver][2]+1.2, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, JobData[jobid][jobDeliverWorld], JobData[jobid][jobDeliverInt]);
			JobData[jobid][jobDeliverActor] = CreateActor(JobData[jobid][jobActorSkin], JobData[jobid][jobDeliver][0], JobData[jobid][jobDeliver][1], JobData[jobid][jobDeliver][2], JobData[jobid][jobActorAngle]);
			JobData[jobid][jobActorCheck] = 1;
		}

		if (JobData[jobid][jobType] == 4)
		{
		    format(string1, sizeof(string1), "[%s]\nกด 'Y' เพื่อหยิบแก๊ส", Job_GetName(JobData[jobid][jobType]));
		    JobData[jobid][jobText3D][1] = CreateDynamic3DTextLabel(string1, 0xFF0000FF, JobData[jobid][jobPoint][0], JobData[jobid][jobPoint][1], JobData[jobid][jobPoint][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, JobData[jobid][jobPointWorld], JobData[jobid][jobPointInt]);
			JobData[jobid][jobPickups][1] = CreateDynamicPickup(1239, 23, JobData[jobid][jobPoint][0], JobData[jobid][jobPoint][1], JobData[jobid][jobPoint][2], JobData[jobid][jobPointWorld], JobData[jobid][jobPointInt]);
		
		/*	format(string1, sizeof(string1), "[%s]\nจุดตกปลา", Job_GetName(JobData[jobid][jobType]));
			JobData[jobid][jobText3D][2] = CreateDynamic3DTextLabel(string1, 0xFF0000FF, JobData[jobid][jobPoint2][0], JobData[jobid][jobPoint2][1], JobData[jobid][jobPoint2][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, JobData[jobid][jobPoint2World], JobData[jobid][jobPointInt]);
			JobData[jobid][jobPickups][2] = CreateDynamicPickup(1239, 23, JobData[jobid][jobPoint2][0], JobData[jobid][jobPoint2][1], JobData[jobid][jobPoint2][2], JobData[jobid][jobPoint2World], JobData[jobid][jobPointInt]);
*/
			format(string1, sizeof(string1), "[%s]\nกด 'Y' เพื่อส่งแก๊ส", Job_GetName(JobData[jobid][jobType]));
			JobData[jobid][jobText3D][3] = CreateDynamic3DTextLabel(string1, 0xFF0000FF, JobData[jobid][jobDeliver][0], JobData[jobid][jobDeliver][1], JobData[jobid][jobDeliver][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, JobData[jobid][jobDeliverWorld], JobData[jobid][jobDeliverInt]);
			JobData[jobid][jobPickups][3] = CreateDynamicPickup(1239, 23, JobData[jobid][jobDeliver][0], JobData[jobid][jobDeliver][1], JobData[jobid][jobDeliver][2], JobData[jobid][jobDeliverWorld], JobData[jobid][jobDeliverInt]);
		}

		if (JobData[jobid][jobType] == 5)
		{
		    format(string1, sizeof(string1), "[%s]\nกด 'Y' เพื่อเปลี่ยนชุดทำงาน", Job_GetName(JobData[jobid][jobType]));
		    JobData[jobid][jobText3D][1] = CreateDynamic3DTextLabel(string1, 0xFF0000FF, JobData[jobid][jobPoint][0], JobData[jobid][jobPoint][1], JobData[jobid][jobPoint][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, JobData[jobid][jobPointWorld], JobData[jobid][jobPointInt]);
			JobData[jobid][jobPickups][1] = CreateDynamicPickup(1275, 23, JobData[jobid][jobPoint][0], JobData[jobid][jobPoint][1], JobData[jobid][jobPoint][2], JobData[jobid][jobPointWorld], JobData[jobid][jobPointInt]);
		
			format(string1, sizeof(string1), "[%s]\nกด 'Y' เพื่อแปรรูปเนื้อ", Job_GetName(JobData[jobid][jobType]));
			JobData[jobid][jobText3D][2] = CreateDynamic3DTextLabel(string1, 0xFF0000FF, JobData[jobid][jobPoint2][0], JobData[jobid][jobPoint2][1], JobData[jobid][jobPoint2][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, JobData[jobid][jobPoint2World], JobData[jobid][jobPoint2Int]);
			JobData[jobid][jobPickups][2] = CreateDynamicPickup(1239, 23, JobData[jobid][jobPoint2][0], JobData[jobid][jobPoint2][1], JobData[jobid][jobPoint2][2], JobData[jobid][jobPoint2World], JobData[jobid][jobPoint2Int]);

			format(string1, sizeof(string1), "[%s]\nกด 'Y' เพื่อขายเนื้อแปรรูป", Job_GetName(JobData[jobid][jobType]));
			JobData[jobid][jobText3D][3] = CreateDynamic3DTextLabel(string1, 0xFF0000FF, JobData[jobid][jobDeliver][0], JobData[jobid][jobDeliver][1], JobData[jobid][jobDeliver][2]+1.2, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, JobData[jobid][jobDeliverWorld], JobData[jobid][jobDeliverInt]);
			JobData[jobid][jobDeliverActor] = CreateActor(JobData[jobid][jobActorSkin], JobData[jobid][jobDeliver][0], JobData[jobid][jobDeliver][1], JobData[jobid][jobDeliver][2], JobData[jobid][jobActorAngle]);
			JobData[jobid][jobActorCheck] = 1;
		}

		if (JobData[jobid][jobType] == 6)
		{
		    format(string1, sizeof(string1), "[%s]\nกด 'Y' เพื่อเปลี่ยนชุดทำงาน", Job_GetName(JobData[jobid][jobType]));
		    JobData[jobid][jobText3D][1] = CreateDynamic3DTextLabel(string1, 0xFF0000FF, JobData[jobid][jobPoint][0], JobData[jobid][jobPoint][1], JobData[jobid][jobPoint][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, JobData[jobid][jobPointWorld], JobData[jobid][jobPointInt]);
			JobData[jobid][jobPickups][1] = CreateDynamicPickup(1275, 23, JobData[jobid][jobPoint][0], JobData[jobid][jobPoint][1], JobData[jobid][jobPoint][2], JobData[jobid][jobPointWorld], JobData[jobid][jobPointInt]);
		
			/*format(string1, sizeof(string1), "[%s]\nกด 'Y' เพื่อแปรรูปเนื้อ", Job_GetName(JobData[jobid][jobType]));
			JobData[jobid][jobText3D][2] = CreateDynamic3DTextLabel(string1, 0xFF0000FF, JobData[jobid][jobPoint2][0], JobData[jobid][jobPoint2][1], JobData[jobid][jobPoint2][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, JobData[jobid][jobPoint2World], JobData[jobid][jobPointInt]);
			JobData[jobid][jobPickups][2] = CreateDynamicPickup(1239, 23, JobData[jobid][jobPoint2][0], JobData[jobid][jobPoint2][1], JobData[jobid][jobPoint2][2], JobData[jobid][jobPoint2World], JobData[jobid][jobPointInt]);

			format(string1, sizeof(string1), "[%s]\nกด 'Y' เพื่อขายเนื้อแปรรูป", Job_GetName(JobData[jobid][jobType]));
			JobData[jobid][jobText3D][3] = CreateDynamic3DTextLabel(string1, 0xFF0000FF, JobData[jobid][jobDeliver][0], JobData[jobid][jobDeliver][1], JobData[jobid][jobDeliver][2]+1.2, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, JobData[jobid][jobDeliverWorld], JobData[jobid][jobDeliverInt]);
			JobData[jobid][jobDeliverActor] = CreateActor(JobData[jobid][jobActorSkin], JobData[jobid][jobDeliver][0], JobData[jobid][jobDeliver][1], JobData[jobid][jobDeliver][2], JobData[jobid][jobActorAngle]);
			JobData[jobid][jobActorCheck] = 1;*/
		}

		if (JobData[jobid][jobType] == 7)
		{
		    format(string1, sizeof(string1), "[%s]\nกด 'Y' เพื่อขายแมงกระพรุน", Job_GetName(JobData[jobid][jobType]));
			JobData[jobid][jobText3D][3] = CreateDynamic3DTextLabel(string1, 0xFF0000FF, JobData[jobid][jobDeliver][0], JobData[jobid][jobDeliver][1], JobData[jobid][jobDeliver][2]+1.2, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, JobData[jobid][jobDeliverWorld], JobData[jobid][jobDeliverInt]);
			JobData[jobid][jobDeliverActor] = CreateActor(JobData[jobid][jobActorSkin], JobData[jobid][jobDeliver][0], JobData[jobid][jobDeliver][1], JobData[jobid][jobDeliver][2], JobData[jobid][jobActorAngle]);
			JobData[jobid][jobActorCheck] = 1;
		}

		if (JobData[jobid][jobType] == 8)
		{
		    format(string1, sizeof(string1), "[%s]\nกด 'Y' เพื่อรับดินปืน", Job_GetName(JobData[jobid][jobType]));
		    JobData[jobid][jobText3D][1] = CreateDynamic3DTextLabel(string1, 0xFF0000FF, JobData[jobid][jobPoint][0], JobData[jobid][jobPoint][1], JobData[jobid][jobPoint][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, JobData[jobid][jobPointWorld], JobData[jobid][jobPointInt]);
			JobData[jobid][jobPickups][1] = CreateDynamicPickup(2060, 23, JobData[jobid][jobPoint][0], JobData[jobid][jobPoint][1], JobData[jobid][jobPoint][2], JobData[jobid][jobPointWorld], JobData[jobid][jobPointInt]);
		
			format(string1, sizeof(string1), "[%s]\nกด 'Y' เพื่อคราฟอาวุธ", Job_GetName(JobData[jobid][jobType]));
			JobData[jobid][jobText3D][2] = CreateDynamic3DTextLabel(string1, 0xFF0000FF, JobData[jobid][jobPoint2][0], JobData[jobid][jobPoint2][1], JobData[jobid][jobPoint2][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, JobData[jobid][jobPoint2World], JobData[jobid][jobPoint2Int]);
			JobData[jobid][jobPickups][2] = CreateDynamicPickup(1239, 23, JobData[jobid][jobPoint2][0], JobData[jobid][jobPoint2][1], JobData[jobid][jobPoint2][2], JobData[jobid][jobPoint2World], JobData[jobid][jobPoint2Int]);

			format(string1, sizeof(string1), "[%s]\nจุดรับ 'ถุงดินปืน'", Job_GetName(JobData[jobid][jobType]));
			JobData[jobid][jobText3D][3] = CreateDynamic3DTextLabel(string1, 0xFF0000FF, JobData[jobid][jobDeliver][0], JobData[jobid][jobDeliver][1], JobData[jobid][jobDeliver][2]+1.2, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, JobData[jobid][jobDeliverWorld], JobData[jobid][jobDeliverInt]);
			JobData[jobid][jobDeliverActor] = CreateActor(JobData[jobid][jobActorSkin], JobData[jobid][jobDeliver][0], JobData[jobid][jobDeliver][1], JobData[jobid][jobDeliver][2], JobData[jobid][jobActorAngle]);
			JobData[jobid][jobActorCheck] = 1;
		}

		if (JobData[jobid][jobType] == 9)
		{
		    format(string1, sizeof(string1), "[%s]\nกด 'Y' เพื่อเปลี่ยนชุดทำงาน", Job_GetName(JobData[jobid][jobType]));
		    JobData[jobid][jobText3D][1] = CreateDynamic3DTextLabel(string1, 0xFF0000FF, JobData[jobid][jobPoint][0], JobData[jobid][jobPoint][1], JobData[jobid][jobPoint][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, JobData[jobid][jobPointWorld], JobData[jobid][jobPointInt]);
			JobData[jobid][jobPickups][1] = CreateDynamicPickup(1275, 23, JobData[jobid][jobPoint][0], JobData[jobid][jobPoint][1], JobData[jobid][jobPoint][2], JobData[jobid][jobPointWorld], JobData[jobid][jobPointInt]);
		
		/*	format(string1, sizeof(string1), "[%s]\nกด 'Y' เพื่อคราฟอาวุธ", Job_GetName(JobData[jobid][jobType]));
			JobData[jobid][jobText3D][2] = CreateDynamic3DTextLabel(string1, 0xFF0000FF, JobData[jobid][jobPoint2][0], JobData[jobid][jobPoint2][1], JobData[jobid][jobPoint2][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, JobData[jobid][jobPoint2World], JobData[jobid][jobPoint2Int]);
			JobData[jobid][jobPickups][2] = CreateDynamicPickup(1239, 23, JobData[jobid][jobPoint2][0], JobData[jobid][jobPoint2][1], JobData[jobid][jobPoint2][2], JobData[jobid][jobPoint2World], JobData[jobid][jobPoint2Int]);
*/
			format(string1, sizeof(string1), "[%s]\nจุดส่งขยะ", Job_GetName(JobData[jobid][jobType]));
			JobData[jobid][jobText3D][3] = CreateDynamic3DTextLabel(string1, 0xFF0000FF, JobData[jobid][jobDeliver][0], JobData[jobid][jobDeliver][1], JobData[jobid][jobDeliver][2]+0.5, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, JobData[jobid][jobDeliverWorld], JobData[jobid][jobDeliverInt]);
			/*JobData[jobid][jobDeliverActor] = CreateActor(JobData[jobid][jobActorSkin], JobData[jobid][jobDeliver][0], JobData[jobid][jobDeliver][1], JobData[jobid][jobDeliver][2], JobData[jobid][jobActorAngle]);
			JobData[jobid][jobActorCheck] = 1;*/
		}

		if (JobData[jobid][jobType] == 10)
		{
		    format(string1, sizeof(string1), "[%s]\nกด 'Y' เพื่อรับอุปกรณ์การทำงาน", Job_GetName(JobData[jobid][jobType]));
		    JobData[jobid][jobText3D][1] = CreateDynamic3DTextLabel(string1, 0xFF0000FF, JobData[jobid][jobPoint][0], JobData[jobid][jobPoint][1], JobData[jobid][jobPoint][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, JobData[jobid][jobPointWorld], JobData[jobid][jobPointInt]);
			JobData[jobid][jobPickups][1] = CreateDynamicPickup(1239, 23, JobData[jobid][jobPoint][0], JobData[jobid][jobPoint][1], JobData[jobid][jobPoint][2], JobData[jobid][jobPointWorld], JobData[jobid][jobPointInt]);
		
			format(string1, sizeof(string1), "[%s]\nกด 'Y' จุดแปรรูปน้ำยาง", Job_GetName(JobData[jobid][jobType]));
			JobData[jobid][jobText3D][2] = CreateDynamic3DTextLabel(string1, 0xFF0000FF, JobData[jobid][jobPoint2][0], JobData[jobid][jobPoint2][1], JobData[jobid][jobPoint2][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, JobData[jobid][jobPoint2World], JobData[jobid][jobPoint2Int]);
			JobData[jobid][jobPickups][2] = CreateDynamicPickup(1239, 23, JobData[jobid][jobPoint2][0], JobData[jobid][jobPoint2][1], JobData[jobid][jobPoint2][2], JobData[jobid][jobPoint2World], JobData[jobid][jobPoint2Int]);
			JobData[jobid][jobCPDynamic] = CreateDynamicCP(JobData[jobid][jobPoint2][0], JobData[jobid][jobPoint2][1], JobData[jobid][jobPoint2][2], 1.5, -1, -1, -1, 5.0, -1, 0);

			format(string1, sizeof(string1), "[%s]\nกด 'Y' เพื่อขายยางแผ่น", Job_GetName(JobData[jobid][jobType]));
			JobData[jobid][jobText3D][3] = CreateDynamic3DTextLabel(string1, 0xFF0000FF, JobData[jobid][jobDeliver][0], JobData[jobid][jobDeliver][1], JobData[jobid][jobDeliver][2]+1.2, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, JobData[jobid][jobDeliverWorld], JobData[jobid][jobDeliverInt]);
			JobData[jobid][jobDeliverActor] = CreateActor(JobData[jobid][jobActorSkin], JobData[jobid][jobDeliver][0], JobData[jobid][jobDeliver][1], JobData[jobid][jobDeliver][2], JobData[jobid][jobActorAngle]);
			JobData[jobid][jobActorCheck] = 1;
		}

		if (JobData[jobid][jobType] == 11)
		{
		    format(string1, sizeof(string1), "[%s]\nกด 'Y' เพื่อหยิบกล่องเสื้อผ้า", Job_GetName(JobData[jobid][jobType]));
		    JobData[jobid][jobText3D][1] = CreateDynamic3DTextLabel(string1, 0xFF0000FF, JobData[jobid][jobPoint][0], JobData[jobid][jobPoint][1], JobData[jobid][jobPoint][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, JobData[jobid][jobPointWorld], JobData[jobid][jobPointInt]);
			JobData[jobid][jobPickups][1] = CreateDynamicPickup(1239, 23, JobData[jobid][jobPoint][0], JobData[jobid][jobPoint][1], JobData[jobid][jobPoint][2], JobData[jobid][jobPointWorld], JobData[jobid][jobPointInt]);
		
			/*format(string1, sizeof(string1), "[%s]\nกด 'Y' จุดแปรรูปน้ำยาง", Job_GetName(JobData[jobid][jobType]));
			JobData[jobid][jobText3D][2] = CreateDynamic3DTextLabel(string1, 0xFF0000FF, JobData[jobid][jobPoint2][0], JobData[jobid][jobPoint2][1], JobData[jobid][jobPoint2][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, JobData[jobid][jobPoint2World], JobData[jobid][jobPoint2Int]);
			JobData[jobid][jobPickups][2] = CreateDynamicPickup(1239, 23, JobData[jobid][jobPoint2][0], JobData[jobid][jobPoint2][1], JobData[jobid][jobPoint2][2], JobData[jobid][jobPoint2World], JobData[jobid][jobPoint2Int]);
			JobData[jobid][jobCPDynamic] = CreateDynamicCP(JobData[jobid][jobPoint2][0], JobData[jobid][jobPoint2][1], JobData[jobid][jobPoint2][2], 1.5, -1, -1, -1, 5.0, -1, 0);

			format(string1, sizeof(string1), "[%s]\nกด 'Y' เพื่อส่งเสื้อผ้า", Job_GetName(JobData[jobid][jobType]));
			JobData[jobid][jobText3D][3] = CreateDynamic3DTextLabel(string1, 0xFF0000FF, JobData[jobid][jobDeliver][0], JobData[jobid][jobDeliver][1], JobData[jobid][jobDeliver][2]+1.2, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, JobData[jobid][jobDeliverWorld], JobData[jobid][jobDeliverInt]);
			JobData[jobid][jobDeliverActor] = CreateActor(JobData[jobid][jobActorSkin], JobData[jobid][jobDeliver][0], JobData[jobid][jobDeliver][1], JobData[jobid][jobDeliver][2], JobData[jobid][jobActorAngle]);
			JobData[jobid][jobActorCheck] = 1;*/
		}

		if (JobData[jobid][jobType] == 12)
		{
		    format(string1, sizeof(string1), "[%s]\nกด 'Y' เพื่อเปลี่ยนชุดและรับอุปกรณ์", Job_GetName(JobData[jobid][jobType]));
		    JobData[jobid][jobText3D][1] = CreateDynamic3DTextLabel(string1, 0xFF0000FF, JobData[jobid][jobPoint][0], JobData[jobid][jobPoint][1], JobData[jobid][jobPoint][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, JobData[jobid][jobPointWorld], JobData[jobid][jobPointInt]);
			JobData[jobid][jobPickups][1] = CreateDynamicPickup(1239, 23, JobData[jobid][jobPoint][0], JobData[jobid][jobPoint][1], JobData[jobid][jobPoint][2], JobData[jobid][jobPointWorld], JobData[jobid][jobPointInt]);
		
			format(string1, sizeof(string1), "[%s]\nกด 'Y' เพื่อล้างรังสีจากสมบัติ", Job_GetName(JobData[jobid][jobType]));
			JobData[jobid][jobText3D][2] = CreateDynamic3DTextLabel(string1, 0xFF0000FF, JobData[jobid][jobPoint2][0], JobData[jobid][jobPoint2][1], JobData[jobid][jobPoint2][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, JobData[jobid][jobPoint2World], JobData[jobid][jobPoint2Int]);
			JobData[jobid][jobPickups][2] = CreateDynamicPickup(1239, 23, JobData[jobid][jobPoint2][0], JobData[jobid][jobPoint2][1], JobData[jobid][jobPoint2][2], JobData[jobid][jobPoint2World], JobData[jobid][jobPoint2Int]);
			//JobData[jobid][jobCPDynamic] = CreateDynamicCP(JobData[jobid][jobPoint2][0], JobData[jobid][jobPoint2][1], JobData[jobid][jobPoint2][2], 1.5, -1, -1, -1, 5.0, -1, 0);

			format(string1, sizeof(string1), "[%s]\nกด 'Y' เพื่อขายสมบัติ", Job_GetName(JobData[jobid][jobType]));
			JobData[jobid][jobText3D][3] = CreateDynamic3DTextLabel(string1, 0xFF0000FF, JobData[jobid][jobDeliver][0], JobData[jobid][jobDeliver][1], JobData[jobid][jobDeliver][2]+1.2, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, JobData[jobid][jobDeliverWorld], JobData[jobid][jobDeliverInt]);
			JobData[jobid][jobDeliverActor] = CreateActor(JobData[jobid][jobActorSkin], JobData[jobid][jobDeliver][0], JobData[jobid][jobDeliver][1], JobData[jobid][jobDeliver][2], JobData[jobid][jobActorAngle]);
			JobData[jobid][jobActorCheck] = 1;
		}

		if (JobData[jobid][jobType] == 13)
		{
		    format(string1, sizeof(string1), "[%s]\nกด 'Y' เพื่อเปลี่ยนชุดและรับอุปกรณ์", Job_GetName(JobData[jobid][jobType]));
		    JobData[jobid][jobText3D][1] = CreateDynamic3DTextLabel(string1, 0xFF0000FF, JobData[jobid][jobPoint][0], JobData[jobid][jobPoint][1], JobData[jobid][jobPoint][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, JobData[jobid][jobPointWorld], JobData[jobid][jobPointInt]);
			JobData[jobid][jobPickups][1] = CreateDynamicPickup(1239, 23, JobData[jobid][jobPoint][0], JobData[jobid][jobPoint][1], JobData[jobid][jobPoint][2], JobData[jobid][jobPointWorld], JobData[jobid][jobPointInt]);
		
			format(string1, sizeof(string1), "[%s]\nกด 'Y' เพื่อส่งงานดูแลสวน", Job_GetName(JobData[jobid][jobType]));
			JobData[jobid][jobText3D][2] = CreateDynamic3DTextLabel(string1, 0xFF0000FF, JobData[jobid][jobPoint2][0], JobData[jobid][jobPoint2][1], JobData[jobid][jobPoint2][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, JobData[jobid][jobPoint2World], JobData[jobid][jobPoint2Int]);
			JobData[jobid][jobPickups][2] = CreateDynamicPickup(1239, 23, JobData[jobid][jobPoint2][0], JobData[jobid][jobPoint2][1], JobData[jobid][jobPoint2][2], JobData[jobid][jobPoint2World], JobData[jobid][jobPoint2Int]);

			/*format(string1, sizeof(string1), "[%s]\nกด 'Y' เพื่อขายสมบัติ", Job_GetName(JobData[jobid][jobType]));
			JobData[jobid][jobText3D][3] = CreateDynamic3DTextLabel(string1, 0xFF0000FF, JobData[jobid][jobDeliver][0], JobData[jobid][jobDeliver][1], JobData[jobid][jobDeliver][2]+1.2, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, JobData[jobid][jobDeliverWorld], JobData[jobid][jobDeliverInt]);
			JobData[jobid][jobDeliverActor] = CreateActor(JobData[jobid][jobActorSkin], JobData[jobid][jobDeliver][0], JobData[jobid][jobDeliver][1], JobData[jobid][jobDeliver][2], JobData[jobid][jobActorAngle]);
			JobData[jobid][jobActorCheck] = 1;*/
		}

		if (JobData[jobid][jobType] == 14)
		{
		    format(string1, sizeof(string1), "[%s]\nกด 'Y' เพื่อแปรรูปน้ำมัน", Job_GetName(JobData[jobid][jobType]));
		    JobData[jobid][jobText3D][1] = CreateDynamic3DTextLabel(string1, 0xFF0000FF, JobData[jobid][jobPoint][0], JobData[jobid][jobPoint][1], JobData[jobid][jobPoint][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, JobData[jobid][jobPointWorld], JobData[jobid][jobPointInt]);
			JobData[jobid][jobPickups][1] = CreateDynamicPickup(1239, 23, JobData[jobid][jobPoint][0], JobData[jobid][jobPoint][1], JobData[jobid][jobPoint][2], JobData[jobid][jobPointWorld], JobData[jobid][jobPointInt]);
		
			/*format(string1, sizeof(string1), "[%s]\nกด 'Y' เพื่อส่งงานดูแลสวน", Job_GetName(JobData[jobid][jobType]));
			JobData[jobid][jobText3D][2] = CreateDynamic3DTextLabel(string1, 0xFF0000FF, JobData[jobid][jobPoint2][0], JobData[jobid][jobPoint2][1], JobData[jobid][jobPoint2][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, JobData[jobid][jobPoint2World], JobData[jobid][jobPoint2Int]);
			JobData[jobid][jobPickups][2] = CreateDynamicPickup(1239, 23, JobData[jobid][jobPoint2][0], JobData[jobid][jobPoint2][1], JobData[jobid][jobPoint2][2], JobData[jobid][jobPoint2World], JobData[jobid][jobPoint2Int]);
			*/

			format(string1, sizeof(string1), "[%s]\nกด 'Y' เพื่อส่งน้ำมันเข้าคลัง", Job_GetName(JobData[jobid][jobType]));
			JobData[jobid][jobText3D][3] = CreateDynamic3DTextLabel(string1, 0xFF0000FF, JobData[jobid][jobDeliver][0], JobData[jobid][jobDeliver][1], JobData[jobid][jobDeliver][2]+1.2, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, JobData[jobid][jobDeliverWorld], JobData[jobid][jobDeliverInt]);
			JobData[jobid][jobDeliverActor] = CreateActor(JobData[jobid][jobActorSkin], JobData[jobid][jobDeliver][0], JobData[jobid][jobDeliver][1], JobData[jobid][jobDeliver][2], JobData[jobid][jobActorAngle]);
			JobData[jobid][jobActorCheck] = 1;
		}

		if (JobData[jobid][jobType] == 15)
		{
			format(string1, sizeof(string1), "[%s]\nกด 'Y' เพื่อขายหอยสด", Job_GetName(JobData[jobid][jobType]));
			JobData[jobid][jobText3D][3] = CreateDynamic3DTextLabel(string1, 0xFF0000FF, JobData[jobid][jobDeliver][0], JobData[jobid][jobDeliver][1], JobData[jobid][jobDeliver][2]+1.2, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, JobData[jobid][jobDeliverWorld], JobData[jobid][jobDeliverInt]);
			JobData[jobid][jobDeliverActor] = CreateActor(JobData[jobid][jobActorSkin], JobData[jobid][jobDeliver][0], JobData[jobid][jobDeliver][1], JobData[jobid][jobDeliver][2], JobData[jobid][jobActorAngle]);
			JobData[jobid][jobActorCheck] = 1;
		}

		if(JobData[jobid][jobType] == ORANGEJOB){

			format(string1, sizeof(string1), "[%s]\nกด 'ALT' เพื่อทำการชั่งน้ำหนักส้ม", Job_GetName(JobData[jobid][jobType]));
		    JobData[jobid][jobText3D][1] = CreateDynamic3DTextLabel(string1, 0xFF6203FF, JobData[jobid][jobPoint][0], JobData[jobid][jobPoint][1], JobData[jobid][jobPoint][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, JobData[jobid][jobPointWorld], JobData[jobid][jobPointInt]);
			JobData[jobid][jobPickups][1] = CreateDynamicPickup(19638, 23, JobData[jobid][jobPoint][0], JobData[jobid][jobPoint][1], JobData[jobid][jobPoint][2], JobData[jobid][jobPointWorld], JobData[jobid][jobPointInt]);

			format(string1, sizeof(string1), "[%s]\nกด 'Y' เพื่อขายส้ม", Job_GetName(JobData[jobid][jobType]));
			JobData[jobid][jobText3D][3] = CreateDynamic3DTextLabel(string1, 0xFF6203FF, JobData[jobid][jobDeliver][0], JobData[jobid][jobDeliver][1], JobData[jobid][jobDeliver][2]+1.2, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, JobData[jobid][jobDeliverWorld], JobData[jobid][jobDeliverInt]);
			JobData[jobid][jobDeliverActor] = CreateActor(JobData[jobid][jobActorSkin], JobData[jobid][jobDeliver][0], JobData[jobid][jobDeliver][1], JobData[jobid][jobDeliver][2], JobData[jobid][jobActorAngle]);
			JobData[jobid][jobActorCheck] = 1;
		}

		if(JobData[jobid][jobType] == SHARKJOB){

			format(string1, sizeof(string1), "[%s]\nกด 'Y' เพื่อเริ่มตกปลาฉลาม", Job_GetName(JobData[jobid][jobType]));
		    JobData[jobid][jobText3D][1] = CreateDynamic3DTextLabel(string1, 0xFF6203FF, JobData[jobid][jobPoint][0], JobData[jobid][jobPoint][1], JobData[jobid][jobPoint][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, JobData[jobid][jobPointWorld], JobData[jobid][jobPointInt]);
			JobData[jobid][jobPickups][1] = CreateDynamicPickup(1239, 23, JobData[jobid][jobPoint][0], JobData[jobid][jobPoint][1], JobData[jobid][jobPoint][2], JobData[jobid][jobPointWorld], JobData[jobid][jobPointInt]);

			format(string1, sizeof(string1), "[%s]\nกด 'Y' เพื่อขายปลาฉลาม", Job_GetName(JobData[jobid][jobType]));
			JobData[jobid][jobText3D][3] = CreateDynamic3DTextLabel(string1, 0xFF6203FF, JobData[jobid][jobDeliver][0], JobData[jobid][jobDeliver][1], JobData[jobid][jobDeliver][2]+1.2, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, JobData[jobid][jobDeliverWorld], JobData[jobid][jobDeliverInt]);
			JobData[jobid][jobDeliverActor] = CreateActor(JobData[jobid][jobActorSkin], JobData[jobid][jobDeliver][0], JobData[jobid][jobDeliver][1], JobData[jobid][jobDeliver][2], JobData[jobid][jobActorAngle]);
			JobData[jobid][jobActorCheck] = 1;
		}

		if(JobData[jobid][jobType] == PIZZAJOB){
			format(string1, sizeof(string1), "[%s]\nกด 'Y' เพื่อเริ่มทำพิซซ่า", Job_GetName(JobData[jobid][jobType]));
		    JobData[jobid][jobText3D][1] = CreateDynamic3DTextLabel(string1, 0xFF6203FF, JobData[jobid][jobPoint][0], JobData[jobid][jobPoint][1], JobData[jobid][jobPoint][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, JobData[jobid][jobPointWorld], JobData[jobid][jobPointInt]);
			JobData[jobid][jobPickups][1] = CreateDynamicPickup(1582, 23, JobData[jobid][jobPoint][0], JobData[jobid][jobPoint][1], JobData[jobid][jobPoint][2], JobData[jobid][jobPointWorld], JobData[jobid][jobPointInt]);
		}

		if(JobData[jobid][jobType] == DELIOILJOB){
			format(string1, sizeof string1, "[%s]\n กด 'Y' เพื่อเริ่มบรรจุน้ำมันใส่ถัง", Job_GetName(JobData[jobid][jobType]));
			JobData[jobid][jobText3D][1] = CreateDynamic3DTextLabel(string1, 0x2E9AFFFF, JobData[jobid][jobPoint][0], JobData[jobid][jobPoint][1], JobData[jobid][jobPoint][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, JobData[jobid][jobPointWorld], JobData[jobid][jobPointInt]);
			JobData[jobid][jobPickups][1] = CreateDynamicPickup(1239, 23, JobData[jobid][jobPoint][0], JobData[jobid][jobPoint][1], JobData[jobid][jobPoint][2], JobData[jobid][jobPointWorld], JobData[jobid][jobPointInt]);
		}
	}
	return 1;
}

Job_Delete(jobid)
{
	if (jobid != -1 && JobData[jobid][jobExists])
	{
	    new
	        string[64];

        Total_Jobs_Created--;

		format(string, sizeof(string), "DELETE FROM `jobs` WHERE `jobID` = '%d'", JobData[jobid][jobID]);
		mysql_tquery(dbCon, string);

        for (new i = 0; i < 3; i ++) {
			if (IsValidDynamic3DTextLabel(JobData[jobid][jobText3D][i]))
		    	DestroyDynamic3DTextLabel(JobData[jobid][jobText3D][i]);

			if (IsValidDynamicPickup(JobData[jobid][jobPickups][i]))
		    	DestroyDynamicPickup(JobData[jobid][jobPickups][i]);
		}
		JobData[jobid][jobExists] = false;
		JobData[jobid][jobType] = 0;
	    JobData[jobid][jobID] = 0;
	}
	return 1;
}

Job_Save(jobid)
{
	new
	    query[1536];

	format(query, sizeof(query), "UPDATE `jobs` SET `jobName` = '%s', `jobType` = '%d', `jobPosX` = '%.4f', `jobPosY` = '%.4f', `jobPosZ` = '%.4f', `jobInterior` = '%d', `jobWorld` = '%d', `jobPointX` = '%.4f', `jobPointY` = '%.4f', `jobPointZ` = '%.4f', `jobPoint2X` = '%.4f', `jobPoint2Y` = '%.4f', `jobPoint2Z` = '%.4f'",
		JobData[jobid][jobName],
		JobData[jobid][jobType],
		JobData[jobid][jobPos][0],
	    JobData[jobid][jobPos][1],
	    JobData[jobid][jobPos][2],
	    JobData[jobid][jobInterior],
	    JobData[jobid][jobWorld],
	    JobData[jobid][jobPoint][0],
	    JobData[jobid][jobPoint][1],
	    JobData[jobid][jobPoint][2],
		JobData[jobid][jobPoint2][0],
	    JobData[jobid][jobPoint2][1],
	    JobData[jobid][jobPoint2][2]
	);

	format(query, sizeof(query), "%s, `jobDeliverX` = '%.4f', `jobDeliverY` = '%.4f', `jobDeliverZ` = '%.4f', `jobPointInt` = '%d', `jobPointWorld` = '%d', `jobPoint2Int` = '%d', `jobPoint2World` = '%d', `jobDeliverInt` = '%d', `jobDeliverWorld` = '%d', `jobDeliverPrice` = '%d', `jobActorAngle` = '%f', `jobActorSkin` = '%d', `jobLevel` = '%d' WHERE `jobID` = '%d'",
		query,
		JobData[jobid][jobDeliver][0],
	    JobData[jobid][jobDeliver][1],
	    JobData[jobid][jobDeliver][2],
	    JobData[jobid][jobPointInt],
	    JobData[jobid][jobPointWorld],
		JobData[jobid][jobPoint2Int],
	    JobData[jobid][jobPoint2World],
		JobData[jobid][jobDeliverInt],
	    JobData[jobid][jobDeliverWorld],
		JobData[jobid][jobDeliverPrice],
		JobData[jobid][jobActorAngle],
		JobData[jobid][jobActorSkin],
		JobData[jobid][jobLevel],
	    JobData[jobid][jobID]
	);
	return mysql_tquery(dbCon, query);
}

Job_Create(playerid, type)
{
	new
	    Float:x,
	    Float:y,
	    Float:z;

	if (GetPlayerPos(playerid, x, y, z))
	{
		for (new i = 0; i != MAX_DYNAMIC_JOBS; i ++)
		{
	    	if (!JobData[i][jobExists])
	    	{
	        	JobData[i][jobExists] = true;
	        	JobData[i][jobType] = type;
				JobData[i][jobName] = Job_GetName(type);

				JobData[i][jobPos][0] = x;
	        	JobData[i][jobPos][1] = y;
	        	JobData[i][jobPos][2] = z;
	        	JobData[i][jobPoint][0] = 0.0;
	        	JobData[i][jobPoint][1] = 0.0;
	        	JobData[i][jobPoint][2] = 0.0;
				JobData[i][jobPoint2][0] = 0.0;
	        	JobData[i][jobPoint2][1] = 0.0;
	        	JobData[i][jobPoint2][2] = 0.0;
	        	JobData[i][jobDeliver][0] = 0.0;
	        	JobData[i][jobDeliver][1] = 0.0;
	        	JobData[i][jobDeliver][2] = 0.0;

	        	JobData[i][jobInterior] = GetPlayerInterior(playerid);
	        	JobData[i][jobWorld] = GetPlayerVirtualWorld(playerid);

                JobData[i][jobPointInt] = 0;
                JobData[i][jobPointWorld] = 0;

				JobData[i][jobPoint2Int] = 0;
                JobData[i][jobPoint2World] = 0;

				JobData[i][jobDeliverInt] = 0;
                JobData[i][jobDeliverWorld] = 0;

	        	Job_Refresh(i);
	        	mysql_tquery(dbCon, "INSERT INTO `jobs` (`jobInterior`) VALUES(0)", "OnJobCreated", "d", i);

	        	return i;
	        }
	    }
	}
	return -1;
}

forward OnJobCreated(jobid);
public OnJobCreated(jobid)
{
	if (jobid == -1 || !JobData[jobid][jobExists])
	    return 0;

	JobData[jobid][jobID] = cache_insert_id();
	Job_Save(jobid);

	return 1;
}

CMD:jobcmds(playerid, params[]){
	if(!LoggedIn[playerid]) return 0;
	if(PlayerData[playerid][pAdmin] < 1338)
		return ErrorMsg(playerid, "คุณไม่ได้รับอนุญาติ");

	SendClientMessage(playerid, COLOR_DARKGREEN, "|-------------------------------------------------------------------------------------------|");
	SendClientMessage(playerid, COLOR_GRAY, "[JOBCMDS]: /makejob, /removejob, /editjob, /gotojob, /jobrefresh");
	SendClientMessage(playerid, COLOR_DARKGREEN, "|-------------------------------------------------------------------------------------------|");
	return 1;
}

//CMD
CMD:gotojob(playerid, params[])
{
	if(!LoggedIn[playerid]) return 0;
	new
		id;

	if (PlayerData[playerid][pAdmin] < 1338)
		return SendClientMessage(playerid, -1, "คุณไม่ได้รับอนุญาตให้ใช้คำสั่งนี้");

	if (sscanf(params, "d", id))
		return SystemMsg(playerid, "/gotojob [job ID]");

	if ((id < 0 || id >= MAX_DYNAMIC_JOBS) || !JobData[id][jobExists])
		return SendClientMessage(playerid, -1, "คุณระบุ Job ID ไม่ถูกต้อง");

	SetPlayerPosEx(playerid, JobData[id][jobPos][0], JobData[id][jobPos][1], JobData[id][jobPos][2], JobData[id][jobInterior], JobData[id][jobWorld]);
	SendClientMessageEx(playerid, -1, "คุณได้เคลื่อนย้ายไปที่ Job ID: %d", id);
	return 1;
}

alias:makejob("สร้างงาน")
CMD:makejob(playerid, params[])
{
	if(!LoggedIn[playerid]) return 0;
	new
		id = -1,
		type,
		string[128];

	if (PlayerData[playerid][pAdmin] < 1338)
		return SendClientMessage(playerid, -1, "คุณไม่ได้รับอนุญาตให้ใช้คำสั่งนี้");

	if (sscanf(params, "d", type))
		return SystemMsg(playerid, "/makejob [type]");

	if (type < 1 || type > MAX_DYNAMIC_JOBS)
	{
		format(string, sizeof(string), "ประเภทที่ระบุไม่ถูกต้องต้องอยู่ในระหว่าง 1 ถึง %d", MAX_DYNAMIC_JOBS);
		SendClientMessage(playerid, -1, string);
		return 1;
	}

	id = Job_Create(playerid, type);

	if (id == -1)
		return SendClientMessage(playerid, -1, "เซิฟเวอร์นี้ได้สร้างอาชีพเกินขีดจำกัดแล้ว");

	format(string, sizeof(string), "คุณประสบความสำเร็จสร้างงานไอดี: %d", id);
	SendClientMessage(playerid, -1, string);
	return 1;
}

alias:removejob("ลบงาน")
CMD:removejob(playerid, params[])
{
	if(!LoggedIn[playerid]) return 0;
	new
		id = 0,
		string[128];

	if (PlayerData[playerid][pAdmin] < 1338)
		return SendClientMessage(playerid, -1, "คุณไม่ได้รับอนุญาตให้ใช้คำสั่งนี้");

	if (sscanf(params, "d", id))
		return SystemMsg(playerid, "/removejob [job id]");

	if ((id < 0 || id >= MAX_DYNAMIC_JOBS) || !JobData[id][jobExists])
		return SendClientMessage(playerid, -1, "คุณระบุไอดีงานผิดพลาด");

	Job_Delete(id);
	format(string, sizeof(string), "คุณประสบความสำเร็จในการทำลายงานไอดี: %d", id);
	SendClientMessage(playerid, -1, string);
	return 1;
}

CMD:jobrefresh(playerid)
{
	if(!LoggedIn[playerid]) return 0;
	if (PlayerData[playerid][pAdmin] < 1338)
		return SendClientMessage(playerid, -1, "คุณไม่ได้รับอนุญาตให้ใช้คำสั่งนี้");

	for(new i=0; i< MAX_DYNAMIC_JOBS;i++) if(JobData[i][jobExists]){
		Job_Refresh(i);
	}
	return 1;
}

forward RandomPriceJob();
public RandomPriceJob(){
	for(new i=0; i<MAX_DYNAMIC_JOBS; i++) if(JobData[i][jobExists]){
		new RandomEco1[4] = {10,20,30,40};
		new randomprice1 = random(sizeof(RandomEco1));
		if(JobData[i][jobType] == GARBAGEJOB){
			JobData[i][jobDeliverPrice] = RandomEco1[randomprice1];
		}

		new RandomEco2[3] = {100,120,130};
		new randomprice2 = random(sizeof(RandomEco2));
		if(JobData[i][jobType] == GASJOB){
			JobData[i][jobDeliverPrice] = RandomEco2[randomprice2];
		}

		new RandomEco3[3] = {5,10,15};
		new randomprice3 = random(sizeof(RandomEco3));
		if(JobData[i][jobType] == FISHJOB){
			JobData[i][jobDeliverPrice] = RandomEco3[randomprice3];
		}

		new RandomEco4[3] = {30,40,50};
		new randomprice4 = random(sizeof(RandomEco4));
		if(JobData[i][jobType] == ENGJOB){
			JobData[i][jobDeliverPrice] = RandomEco4[randomprice4];
		}

		new RandomEco5[2] = {10,20};
		new randomprice5 = random(sizeof(RandomEco5));
		if(JobData[i][jobType] == RUBBERJOB){
			JobData[i][jobDeliverPrice] = RandomEco5[randomprice5];
		}

		new RandomEco6[3] = {40,50,60};
		new randomprice6 = random(sizeof(RandomEco6));
		if(JobData[i][jobType] == CLOTHJOB){
			JobData[i][jobDeliverPrice] = RandomEco6[randomprice6];
		}

		new RandomEco7[5] = {1,2,5,8,10};
		new randomprice7 = random(sizeof(RandomEco7));
		if(JobData[i][jobType] == JELLYJOB){
			JobData[i][jobDeliverPrice] = RandomEco7[randomprice7];
		}

		new RandomEco8[3] = {50,60,70};
		new randomprice8 = random(sizeof(RandomEco8));
		if(JobData[i][jobType] == SEEKERJOB){
			JobData[i][jobDeliverPrice] = RandomEco8[randomprice8];
		}

		new RandomEco9[4] = {5,10,20,25};
		new randomprice9 = random(sizeof(RandomEco9));
		if(JobData[i][jobType] == FARMERJOB){
			JobData[i][jobDeliverPrice] = RandomEco9[randomprice9];
		}

		new RandomEco10[3] = {5,10,15};
		new randomprice10 = random(sizeof(RandomEco10));
		if(JobData[i][jobType] == BUILDJOB){
			JobData[i][jobDeliverPrice] = RandomEco10[randomprice10];
		}

		new RandomEco11[4] = {4,8,12,18};
		new randomprice11 = random(sizeof(RandomEco11));
		if(JobData[i][jobType] == COWJOB){
			JobData[i][jobDeliverPrice] = RandomEco11[randomprice11];
		}

		new RandomEco12[3] = {140,150,160};
		new randomprice12 = random(sizeof(RandomEco12));
		if(JobData[i][jobType] == GARDENER){
			JobData[i][jobDeliverPrice] = RandomEco12[randomprice12];
		}

		new RandomEco13[3] = {10,15,20};
		new randomprice13 = random(sizeof(RandomEco13));
		if(JobData[i][jobType] == OILJOB){
			JobData[i][jobDeliverPrice] = RandomEco13[randomprice13];
		}

		new RandomEco14[4] = {5,8,12,15};
		new randomprice14 = random(sizeof(RandomEco14));
		if(JobData[i][jobType] == SHELLJOB){
			JobData[i][jobDeliverPrice] = RandomEco14[randomprice14];
		}

		new RandomEco15[4] = {4,8,12,17};
		new randomprice15 = random(sizeof(RandomEco15));
		if(JobData[i][jobType] == ORANGEJOB){
			JobData[i][jobDeliverPrice] = RandomEco15[randomprice15];
		}

		new RandomEco16[3] = {10,25,30};
		new randomprice16 = random(sizeof(RandomEco16));
		if(JobData[i][jobType] == SHARKJOB){
			JobData[i][jobDeliverPrice] = RandomEco16[randomprice16];
		}

		new RandomEco17[3] = {400,450,500};
		new randomprice17 = random(sizeof(RandomEco17));
		if(JobData[i][jobType] == DELIOILJOB){
			JobData[i][jobDeliverPrice] = RandomEco17[randomprice17];
		}
		Job_Save(i);
	}
	SendClientMessageToAll(0x97FF00AA, "[ตลาด]: ราคาตลาดมีการเปลี่ยนแปลงโปรดไปเช็คที่ตลาดกลาง");
	return 1;
}

alias:editjob("แก้ไขงาน")
CMD:editjob(playerid, params[])
{
	if(!LoggedIn[playerid]) return 0;
	new
		id,
		type[24],
		string[128];

	if (PlayerData[playerid][pAdmin] < 1338)
		return SendClientMessage(playerid, -1, "คุณไม่ได้รับอนุญาตให้ใช้คำสั่งนี้");

	if (sscanf(params, "ds[24]S()[128]", id, type, string))
	{
		SystemMsg(playerid, "/editjob [id] [name]");
		SystemMsg(playerid, "[ตัวเลือก]:{FFFFFF} location, point, point2, deliver, type, price, npcangle, npcskin, level");
		return 1;
	}
	if ((id < 0 || id >= MAX_DYNAMIC_JOBS) || !JobData[id][jobExists])
		return SendClientMessage(playerid, -1, "คุณระบุไอดีงานไม่ถูกต้อง");

	if (!strcmp(type, "location", true)){
		new
			Float:x,
			Float:y,
			Float:z;

		GetPlayerPos(playerid, x, y, z);

		JobData[id][jobPos][0] = x;
		JobData[id][jobPos][1] = y;
		JobData[id][jobPos][2] = z;

		JobData[id][jobInterior] = GetPlayerInterior(playerid);
		JobData[id][jobWorld] = GetPlayerVirtualWorld(playerid);

		Job_Refresh(id);
		Job_Save(id);

		format(string, sizeof(string), "%s ได้ปรับตำแหน่งของงาน ไอดี: %d", ReturnRoleplayName(playerid), id);
		SendAdminsMessage(1, COLOR_GRAY, string);
	}
	else if (!strcmp(type, "type", true))
	{
		new typeint;

		if (sscanf(string, "d", typeint))
			return SendClientMessage(playerid, -1, "/editjob [id] [type] [new type]");

		if (typeint < 1 || typeint > 19)
			return SendClientMessage(playerid, -1, "ประเภทที่ระบุต้องอยู่ระหว่าง 1 ถึง 19");

		JobData[id][jobType] = typeint;

		Job_Refresh(id);
		Job_Save(id);

		format(string, sizeof(string), "%s ได้ปรับประเภทของงาน ไอดี: %d เป็น %d", ReturnRoleplayName(playerid), id, JobData[id][jobType]);
		SendAdminsMessage(1, COLOR_GRAY, string);
	}
	else if (!strcmp(type, "point", true))
	{
		new
			Float:x,
			Float:y,
			Float:z;

		GetPlayerPos(playerid, x, y, z);

		JobData[id][jobPoint][0] = x;
		JobData[id][jobPoint][1] = y;
		JobData[id][jobPoint][2] = z;
		JobData[id][jobPointInt] = GetPlayerInterior(playerid);
		JobData[id][jobPointWorld] = GetPlayerVirtualWorld(playerid);

		Job_Refresh(id);
		Job_Save(id);

		format(string, sizeof(string), "%s ได้ปรับตำแหน่ง Point ของงาน ไอดี: %d", ReturnRoleplayName(playerid), id);
		SendAdminsMessage(1, COLOR_GRAY, string);
	}
	else if (!strcmp(type, "point2", true))
	{
		new
			Float:x,
			Float:y,
			Float:z;

		GetPlayerPos(playerid, x, y, z);

		JobData[id][jobPoint2][0] = x;
		JobData[id][jobPoint2][1] = y;
		JobData[id][jobPoint2][2] = z;
		JobData[id][jobPoint2Int] = GetPlayerInterior(playerid);
		JobData[id][jobPoint2World] = GetPlayerVirtualWorld(playerid);

		Job_Refresh(id);
		Job_Save(id);

		format(string, sizeof(string), "%s ได้ปรับตำแหน่ง Point2 ของงาน ไอดี: %d", ReturnRoleplayName(playerid), id);
		SendAdminsMessage(1, COLOR_GRAY, string);
	}
	else if (!strcmp(type, "deliver", true))
	{
		new
			Float:x,
			Float:y,
			Float:z;

		GetPlayerPos(playerid, x, y, z);

		JobData[id][jobDeliver][0] = x;
		JobData[id][jobDeliver][1] = y;
		JobData[id][jobDeliver][2] = z;
		JobData[id][jobDeliverInt] = GetPlayerInterior(playerid);
		JobData[id][jobDeliverWorld] = GetPlayerVirtualWorld(playerid);

		Job_Refresh(id);
		Job_Save(id);

		format(string, sizeof(string), "%s ได้ปรับจุดจัดส่งของงาน ไอดี: %d", ReturnRoleplayName(playerid), id);
		SendAdminsMessage(1, COLOR_GRAY, string);
	}
	else if(!strcmp(type, "price", true)){
		new price;

		if(sscanf(string, "d", price))
			return SendClientMessage(playerid, -1, "/editjob [id] [price] [new price]");
			
		if(price <= 0)
			return ErrorMsg(playerid, "คุณต้องกรอกมากกว่า 0");

		JobData[id][jobDeliverPrice] = price;
		Job_Save(id);

		format(string, sizeof(string), "%s ได้ปรับราคาของงาน %s[%d] เป็น %s", ReturnName(playerid), Job_GetName(JobData[id][jobType]), id, FormatNumber(price));
		SendAdminsMessage(1, COLOR_GRAY, string);
	}
	else if (!strcmp(type, "npcskin", true))
	{
		new skin;
		if (sscanf(string, "d", skin))
			return SendClientMessage(playerid, -1, "/editjob [id] [npcskin] [skin]");

		JobData[id][jobActorSkin] = skin;
		Job_Refresh(id);
		Job_Save(id);

		format(string, sizeof(string), "%s ได้ปรับสกิน npc ของงาน ไอดี: %d เป็น %d", ReturnName(playerid), id, skin);
		SendAdminsMessage(1, COLOR_GRAY, string);
	}
	else if (!strcmp(type, "npcangle", true))
	{
		new Float:angle;
		if (sscanf(string, "f", angle))
			return SendClientMessage(playerid, -1, "/editjob [id] [npcangle] [angle]");

		JobData[id][jobActorAngle] = angle;
		Job_Refresh(id);
		Job_Save(id);

		format(string, sizeof(string), "%s ได้ปรับมุมของ NPC ของงาน ไอดี: %d เป็น %.2f", ReturnName(playerid), id, angle);
		SendAdminsMessage(1, COLOR_GRAY, string);
	}
	else if (!strcmp(type, "level", true))
	{
		new level;
		if (sscanf(string, "d", level))
			return SendClientMessage(playerid, -1, "/editjob [id] [level] [amount]");

		JobData[id][jobLevel] = level;
		Job_Refresh(id);
		Job_Save(id);

		format(string, sizeof(string), "%s ได้ปรับเลเวลของงาน ไอดี: %d เป็น %d", ReturnName(playerid), id, level);
		SendAdminsMessage(1, COLOR_GRAY, string);
	}
	return 1;
}