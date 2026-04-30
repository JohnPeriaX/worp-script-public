#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

ResetPlayerCamping(playerid){
    PlayerIsPlaceCamping[playerid] = false;
    KillTimer(PlayerCampingProcessTimer[playerid]);
    PlayerCampingProcessTimer[playerid] = 0;
    PlayerCampingProcessPoint[playerid] = 0;
    PlayerUsingCamping[playerid] = 0;
    return 1;
}

hook OnGameModeInit(){
    CampingZone = GangZoneCreate(-1851, -2308.5, -1395, -1897.5);
    return 1;
}

StartProcessingDeer(playerid){
    if(!PlayerPickingupDeer[playerid]) return 1;
    LoadPlayerNewProgress(playerid);
    ShowPlayerProgressBar(playerid, NewProgressBar[playerid][0]);
    PlayerTextDrawShow(playerid, NewProgressText[playerid][0]);
    ClearAnimations(playerid);
    PlayerUsingCamping[playerid] = true;
    PlayerCampingProcessPoint[playerid] = 0;
    PlayerCampingProcessTimer[playerid] = SetTimerEx("PlayerCampingProcessing", 500, false, "i", playerid);
    return 1;
}

forward PlayerCampingProcessing(playerid);
public PlayerCampingProcessing(playerid){
    if(PlayerUsingCamping[playerid]){
        new string[64];
        if(PlayerPickingupDeer[playerid]){
            if(PlayerCampingProcessPoint[playerid] < 100){
                PlayerCampingProcessPoint[playerid] += 2;
                format(string, sizeof(string), "Processing Deer Meat %d/100", PlayerCampingProcessPoint[playerid]);
                PlayerTextDrawSetString(playerid, NewProgressText[playerid][0], string);
                SetPlayerProgressBarValue(playerid, NewProgressBar[playerid][0], PlayerCampingProcessPoint[playerid]);
                ApplyAnimation(playerid,"BOMBER","BOM_Plant",4.0,0 ,0,0,0,0,1);
                PlayerCampingProcessTimer[playerid] = SetTimerEx("PlayerCampingProcessing", 500, false, "i", playerid);
            }
            else{
                ClearAnimations(playerid);
                RemoveAttachedObject(playerid, 8);
                KillTimer(PlayerCampingProcessTimer[playerid]);
                PlayerCampingProcessPoint[playerid] = 0;
                PlayerPickingupDeer[playerid] = false;
                PlayerUsingCamping[playerid] = false;
                PlayerData[playerid][pStress]++;
                if(PlayerData[playerid][pStress] >= 200) PlayerData[playerid][pStress] = 200;
                new id = PlayerInventory_AddItem(playerid, "Raw Deer Meat", 19582, 4);
                if(id == -1) return ErrorMsg(playerid, "คุณมีช่องเก็บของไม่พอที่จะเก็บเนื้อแล้ว");

                SendClientMessage(playerid, 0xFF7400AA, "[แล่เนื้อ]: คุณได้รับ 'Raw Deer Meat (เนื้อกวางสด)' + 4");

                HidePlayerProgressBar(playerid, NewProgressBar[playerid][0]);
                PlayerTextDrawHide(playerid, NewProgressText[playerid][0]);

                DestroyPlayerProgressBar(playerid, NewProgressBar[playerid][0]);
                PlayerTextDrawDestroy(playerid, NewProgressText[playerid][0]);
            }
        }
    }
    return 1;
}

Dialog:CampingUseing(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        if(listitem == 0){
            if(!PlayerPickingupDeer[playerid]) return Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "{FF0000}เกิดข้อผิดพลาด", "{FF0000}คุณจะต้องมี 'กวาง' อยู่ในมือ", "ตกลง", "");
            StartProcessingDeer(playerid);
        }
    }
    return 1;
}

Dialog:CampingUseingOwner(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        if(listitem == 0){
            if(!PlayerPickingupDeer[playerid]) return Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "{FF0000}เกิดข้อผิดพลาด", "{FF0000}คุณจะต้องมี 'กวาง' อยู่ในมือ", "ตกลง", "");
            StartProcessingDeer(playerid);
        }
        if(listitem == 1){
            callcmd::decamping(playerid, "\1");
        }
    }
    return 1;
}

CMD:camping(playerid, const params[]){
    if(!LoggedIn[playerid]) return 1;

    if(PlayerInventory_AllCount(playerid, "Tent Backpack") == 0) return ErrorMsg(playerid, "คุณไม่มีกระเป๋าตั้งแคมป์");

    if(SkatePlayerUsing[playerid]) return ErrorMsg(playerid, "คุณจะต้องเก็บสเก็ตบอร์ดก่อน");

    if(IsPlayerInAnyVehicle(playerid)) return ErrorMsg(playerid, "คุณต้องลงจากยานพาหนะก่อน");

    new Float:x, Float:y, Float:z;
    GetPlayerPos(playerid, x, y, z);
    if(x > -1851 && x < -1395 && y > -2308.5 && y < -1897.5){
        if(!PlayerIsPlaceCamping[playerid]){
            if(Camping_Nearest(playerid) != -1) return ErrorMsg(playerid, "คุณไม่สามารถตั้งแคมป์ใกล้กับแคมป์ผู้อื่นได้");
            PlayerIsPlaceCamping[playerid] = true;
            new id = Camping_Create(playerid);
            if(id == -1) return ErrorMsg(playerid, "เซิฟเวอร์ได้ตั้ง แคมป์ จนเต็มแล้ว");
            ApplyAnimation(playerid,"BOMBER","BOM_Plant",4.0,0 ,0,0,0,0,1);
            SendClientMessage(playerid, 0xFF0000AA, "{FF0000}> [Camping]: {FF7000}คุณได้ประสบความสำเร็จในการตั้งแคมป์ของคุณแล้ว");
        }
        else return ErrorMsg(playerid, "คุณได้ตั้งแคมป์ไปแล้ว");
    }
    else ErrorMsg(playerid, "คุณไม่ได้อยู่ในพื้นที่ตั้งแคมป์");
    
    return 1;
}

CMD:decamping(playerid, const params[]){
    if(SkatePlayerUsing[playerid]) return ErrorMsg(playerid, "คุณจะต้องเก็บสเก็ตบอร์ดก่อน");
    if(IsPlayerInAnyVehicle(playerid)) return ErrorMsg(playerid, "คุณต้องลงจากยานพาหนะก่อน");
    new id = -1;
    if(PlayerIsPlaceCamping[playerid]){
        if(( id = Camping_Nearest(playerid)) != -1){
            if(CampData[id][campOwnerID] != playerid) return ErrorMsg(playerid, "นี่ไม่ใช่แคมป์ของคุณไม่สามารถเก็บได้");
            Camping_Delete(playerid, id);
            ApplyAnimation(playerid,"BOMBER","BOM_Plant",4.0,0 ,0,0,0,0,1);
            SendClientMessage(playerid, 0xFF0000AA, "{FF0000}> [Camping]: {FF7000}คุณได้ประสบความสำเร็จในการเก็บแคมป์ของคุณ");
        }
    }
    return 1;
}

CheckCampingIsPlayer(playerid){

    if(!PlayerIsPlaceCamping[playerid]) return 1;

    for(new i=0; i<MAX_CAMP; i++) if(CampData[i][campIsPlace]){
        if(CampData[i][campOwnerID] == playerid){
            Camping_Delete(playerid, i);
            break;
        }
    }
    return 1;
}

Camping_Create(playerid){
    new
	    Float:x,
	    Float:y,
	    Float:z,
        Float:a,
        string[128];

    GetPlayerPos(playerid, x, y, z);
    GetPlayerFacingAngle(playerid, a);
    x = x + (2.0 * floatsin(-a, degrees));
    y = y + (2.0 * floatcos(-a, degrees));

    for(new i=0; i<MAX_CAMP; i++) if(!CampData[i][campIsPlace]){
        CampData[i][campIsPlace] = true;
        CampData[i][campOwnerID] = playerid;
        CampData[i][campPos][0] = x;
        CampData[i][campPos][1] = y;
        CampData[i][campPos][2] = z;
        CampData[i][campPos][3] = a;
        CampData[i][campInt] = GetPlayerInterior(playerid);
        CampData[i][campWorld] = GetPlayerVirtualWorld(playerid);
        format(CampData[i][campOwnerName], 64, ReturnRoleplayName(playerid));
        CreateObjectCamp(i, x, y, z, a);
        
        format(string, sizeof(string), "[แคมป์ของ: %s]\nกดปุ่ม 'Y' เพื่อใช้งาน", CampData[i][campOwnerName]);
        CampData[i][campText3D] = CreateDynamic3DTextLabel(string, 0xFF3600FF, x, y, z+1.5, 8.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, CampData[i][campInt], CampData[i][campWorld]);
        Count_Camp++;
        return i;
    }
    return -1;
}

Camping_Delete(playerid, campid){
	if (campid != -1 && CampData[campid][campIsPlace]){
        if (IsValidDynamic3DTextLabel(CampData[campid][campText3D]) && CampData[campid][campText3D])
            DestroyDynamic3DTextLabel(CampData[campid][campText3D]);

        Count_Camp--;
        for(new index=0; index<MAX_CAMP_OBJECT; index++) {
            if(IsValidObject(CampDataObject[campid][index]) && CampDataObject[campid][index])
                DestroyObject(CampDataObject[campid][index]);
        }
		CampData[campid][campIsPlace] = false;
        CampData[campid][campOwnerID] = INVALID_PLAYER_ID;
        format(CampData[campid][campOwnerName], 64, "NULL");
        PlayerIsPlaceCamping[playerid] = false;
	}
	return 1;
}

Camping_Nearest(playerid)
{
    for (new i = 0; i != MAX_CAMP; i ++) if (CampData[i][campIsPlace] && IsPlayerInRangeOfPoint(playerid, 6.0, CampData[i][campPos][0], CampData[i][campPos][1], CampData[i][campPos][2]))
	{
		if (GetPlayerInterior(playerid) == CampData[i][campInt] && GetPlayerVirtualWorld(playerid) == CampData[i][campWorld])
			return i;
	}
	return -1;
}
 
CreateObjectCamp(campid, Float:x, Float:y, Float:z, Float:a){
    CampDataObject[campid][0]=CreateObject(19300, 309.64999, 1827.71790, 16.63540,   0.00000, 0.00000, 0.00000);
    CampDataObject[campid][1]=CreateObject(841, 309.22369, 1831.88953, 16.69970,   0.00000, 0.00000, 0.00000);
    CampDataObject[campid][2]=CreateObject(841, 309.22369, 1831.88953, 16.69970,   0.00000, 0.00000, 76.00000);
    CampDataObject[campid][3]=CreateObject(841, 309.22369, 1831.88953, 16.69970,   0.00000, 0.00000, 149.00000);
    CampDataObject[campid][5]=CreateObject(18688, 309.12091, 1831.89697, 15.53580,   0.00000, 0.00000, 0.00000); // fire
    CampDataObject[campid][6]=CreateObject(1281, 307.06400, 1825.51147, 17.43860,   0.00000, 0.00000, 90.00000);
    CampDataObject[campid][7]=CreateObject(3119, 306.98322, 1825.67725, 17.72950,   0.00000, 0.00000, -55.00000);
    CampDataObject[campid][8]=CreateObject(1370, 314.04535, 1824.03284, 17.20480,   0.00000, 0.00000, 0.00000);
    CampDataObject[campid][9]=CreateObject(1220, 313.99738, 1822.29041, 17.00860,   0.00000, 0.00000, 0.00000);
    CampDataObject[campid][10]=CreateObject(1220, 314.13629, 1823.18933, 17.00860,   0.00000, 0.00000, -11.00000);
    CampDataObject[campid][11]=CreateObject(1220, 314.00919, 1827.55420, 17.00860,   0.00000, 0.00000, 0.00000);
    CampDataObject[campid][12]=CreateObject(1220, 310.41464, 1827.40930, 17.00860,   0.00000, 0.00000, 0.00000);
    CampDataObject[campid][13]=CreateObject(3119, 314.37982, 1830.49329, 16.94750,   0.00000, 0.00000, -156.00000);
    CampDataObject[campid][14]=CreateObject(1220, 314.07486, 1828.73547, 17.00860,   0.00000, 0.00000, 40.00000);
    CampDataObject[campid][15]=CreateObject(349, 312.55099, 1826.56604, 17.19990,   69.00000, -4.00000, 86.00000);
    CampDataObject[campid][16]=CreateObject(347, 313.96811, 1827.36511, 17.34890,   69.00000, 33.00000, 86.00000);
    CampDataObject[campid][17]=CreateObject(347, 314.11807, 1827.25049, 17.34890,   69.00000, 33.00000, 86.00000);
    CampDataObject[campid][18]=CreateObject(1220, 309.07526, 1822.31531, 17.00860,   0.00000, 0.00000, 11.00000);
    CampDataObject[campid][19]=CreateObject(1220, 309.11325, 1823.18738, 17.00860,   0.00000, 0.00000, -2.00000);
    CampDataObject[campid][20]=CreateObject(2226, 307.81601, 1826.09961, 17.11780,   0.00000, 0.00000, 99.00000);
    CampDataObject[campid][21]=CreateObject(1265, 309.27954, 1828.07727, 17.07260,   0.00000, 0.00000, 0.00000);
    CampDataObject[campid][22]=CreateObject(2674, 308.82733, 1828.01672, 16.67070,   0.00000, 0.00000, 280.00000);
    CampDataObject[campid][23]=CreateObject(2674, 308.59909, 1822.75769, 16.67070,   0.00000, 0.00000, 280.00000);
    CampDataObject[campid][24]=CreateObject(2675, 314.76166, 1826.96948, 16.71070,   0.00000, 0.00000, 215.00000);
    CampDataObject[campid][25]=CreateObject(2674, 306.85934, 1831.50134, 16.67070,   0.00000, 0.00000, 280.00000);
    CampDataObject[campid][26]=CreateObject(2674, 311.39514, 1832.03796, 16.67070,   0.00000, 0.00000, 280.00000);
    CampDataObject[campid][27]=CreateObject(1544, 307.23172, 1830.62488, 17.20720,   0.00000, 0.00000, 0.00000);
    CampDataObject[campid][28]=CreateObject(1544, 311.27390, 1831.59717, 17.20720,   0.00000, 0.00000, 0.00000);
    CampDataObject[campid][29]=CreateObject(1544, 311.04810, 1832.66846, 16.64720,   0.00000, 0.00000, 0.00000);
    CampDataObject[campid][30]=CreateObject(1544, 311.44269, 1832.80554, 16.64720,   0.00000, 0.00000, 0.00000);
    CampDataObject[campid][31]=CreateObject(2114, 307.06149, 1826.76563, 16.75140,   0.00000, 0.00000, 0.00000);
    CampDataObject[campid][32]=CreateObject(2114, 306.64496, 1826.91589, 16.75140,   0.00000, 0.00000, 0.00000);
    CampDataObject[campid][33]=CreateObject(2805, 307.63596, 1833.62769, 17.18640,   0.00000, 0.00000, 0.00000);
    CampDataObject[campid][34]=CreateObject(2804, 309.65308, 1831.65540, 18.46040,   -90.00000, 0.00000, -32.00000);
    CampDataObject[campid][35]=CreateObject(2804, 309.31732, 1831.97778, 18.46040,   -90.00000, 0.00000, -32.00000);
    CampDataObject[campid][36]=CreateObject(2804, 308.98053, 1832.27246, 18.46040,   -90.00000, 0.00000, -32.00000);
    CampDataObject[campid][37]=CreateObject(18632, 306.55414, 1830.47681, 16.74740,   180.00000, 26.00000, 207.00000);
    CampDataObject[campid][38]=CreateObject(18632, 306.60620, 1830.36890, 16.74740,   180.00000, 26.00000, 207.00000);
    CampDataObject[campid][39]=CreateObject(18632, 306.64035, 1830.25195, 16.74740,   180.00000, 26.00000, 207.00000);
    CampDataObject[campid][40]=CreateObject(2864, 306.93115, 1825.70532, 17.45210,   0.00000, 0.00000, 0.00000);
    CampDataObject[campid][41]=CreateObject(2863, 306.76468, 1825.27625, 17.45210,   0.00000, 0.00000, 0.00000);
    CampDataObject[campid][42]=CreateObject(2852, 310.45197, 1827.41333, 17.35810,   0.00000, 0.00000, 0.00000);
    CampDataObject[campid][43]=CreateObject(2844, 312.00867, 1826.49011, 16.65310,   0.00000, 0.00000, 0.00000);
    CampDataObject[campid][44]=CreateObject(2843, 310.91702, 1826.76746, 16.65310,   0.00000, 0.00000, -178.00000);
    CampDataObject[campid][45]=CreateObject(323, 310.27969, 1823.99805, 16.94830,   0.00000, 90.00000, 76.00000);
    CampDataObject[campid][46]=CreateObject(321, 310.41483, 1824.22131, 16.94830,   0.00000, 90.00000, 76.00000);
    //bolsos carpa
    CampDataObject[campid][47]=CreateObject(1550, 310.25449, 1826.72754, 17.03370,   0.00000, 0.00000, 0.00000);
    CampDataObject[campid][48]=CreateObject(1550, 310.16809, 1826.17139, 16.82970,   0.00000, 90.00000, 265.00000);
    //sillas
    CampDataObject[campid][49]=CreateObject(2121, 310.02151, 1829.67651, 17.15670,   0.00000, 0.00000, 179.00000);
    CampDataObject[campid][50]=CreateObject(2121, 309.18134, 1829.70996, 17.15670,   0.00000, 0.00000, 200.00000);
    CampDataObject[campid][51]=CreateObject(2121, 311.36627, 1831.60779, 17.15670,   0.00000, 0.00000, -112.00000);
    CampDataObject[campid][52]=CreateObject(2121, 311.33826, 1832.58765, 17.15670,   0.00000, 0.00000, -91.00000);
    CampDataObject[campid][53]=CreateObject(2121, 307.19360, 1830.67285, 17.15670,   0.00000, 0.00000, 113.00000);
    CampDataObject[campid][54]=CreateObject(2121, 307.08627, 1831.59216, 17.15670,   0.00000, 0.00000, 76.00000);
    CampDataObject[campid][55]=CreateObject(2121, 312.73245, 1826.76624, 17.15670,   0.00000, 0.00000, -90.00000);
    for(new index=49; index<56; index++) SetObjectMaterial(CampDataObject[campid][index], 0, 1281, "benches", "pierdoor02_law", 0xFFFFFFFF);
    //cuerdas
    CampDataObject[campid][56]=CreateObject(19087, 307.79419, 1833.44189, 18.78920,   0.00000, 90.00000, 135.00000);
    CampDataObject[campid][57]=CreateObject(19087, 308.87219, 1832.36987, 18.78920,   0.00000, 90.00000, 135.00000);
    CampDataObject[campid][58]=CreateObject(19089, 311.72137, 1828.64319, 19.62920,   0.00000, -42.00000, 90.00000);
    CampDataObject[campid][59]=CreateObject(19089, 311.72141, 1822.50464, 19.62920,   0.00000, 42.00000, 90.00000);
    CampDataObject[campid][60]=CreateObject(19089, 311.67493, 1823.13049, 19.86420,   0.00000, -53.00000, 0.00000);
    CampDataObject[campid][61]=CreateObject(19089, 311.67303, 1827.79321, 19.86420,   0.00000, -53.00000, 0.00000);
    CampDataObject[campid][62]=CreateObject(19089, 311.65009, 1827.76843, 19.86420,   0.00000, -53.00000, 180.00000);
    CampDataObject[campid][63]=CreateObject(19089, 311.63867, 1823.11316, 19.86420,   0.00000, -53.00000, 180.00000);
    for(new index=56; index<64; index++) SetObjectMaterial(CampDataObject[campid][index], 0, -1, "none", "none", 0xFF808484);
    //palos fogata
    CampDataObject[campid][64]=CreateObject(1251, 310.61270, 1830.58606, 15.53550,   90.00000, 0.00000, 0.00000);
    CampDataObject[campid][65]=CreateObject(1251, 307.87411, 1833.35156, 15.53550,   90.00000, 0.00000, 0.00000);
    for(new index=64; index<67; index++) SetObjectMaterial(CampDataObject[campid][index], 0, 841, "gta_brokentrees", "CJ_bark", 0xFFFFFFFF);
    //camas carpa
    CampDataObject[campid][67]=CreateObject(1646, 310.20544, 1823.86487, 16.78320,   0.00000, 0.00000, 180.00000);
    CampDataObject[campid][68]=CreateObject(1646, 312.31110, 1824.50134, 16.78320,   0.00000, 0.00000, -90.00000);
    CampDataObject[campid][69]=CreateObject(1646, 312.31107, 1825.72351, 16.78320,   0.00000, 0.00000, -90.00000);
    CampDataObject[campid][70]=CreateObject(1646, 314.25800, 1830.57471, 16.78320,   0.00000, 0.00000, -154.00000);
    for(new index=67; index<71; index++) SetObjectMaterial(CampDataObject[campid][index], 25, -1, "none", "none", -1);
    for(new index=67; index<71; index++) SetObjectMaterial(CampDataObject[campid][index], 26, -1, "none", "none", -1);
    //carpa
    CampDataObject[campid][71]=CreateObject(19325, 312.76309, 1825.48145, 18.11690,   0.00000, -32.00000, 0.00000);
    CampDataObject[campid][72]=CreateObject(19325, 310.53009, 1825.48145, 18.11690,   0.00000, 34.00000, 0.00000);
    CampDataObject[campid][73]=CreateObject(19325, 311.59631, 1825.51514, 16.65890,   0.00000, 90.00000, 0.00000);
    for(new index=71; index<74; index++) SetObjectMaterial(CampDataObject[campid][index], 0, 3066, "ammotrx", "ammotrn92tarp128", 0xFFFFFFFF);
    //entrada carpa
    CampDataObject[campid][74]=CreateObject(2068, 310.92621, 1829.37927, 14.26150,   138.00000, 105.00000, 78.00000);
    CampDataObject[campid][75]=CreateObject(2068, 312.47238, 1821.60352, 14.26150,   138.00000, 105.00000, 260.00000);
    CampDataObject[campid][76]=CreateObject(2068, 312.40381, 1828.17834, 14.26150,   138.00000, 105.00000, -99.00000);
    CampDataObject[campid][77]=CreateObject(2068, 311.01590, 1822.85583, 14.26150,   138.00000, 105.00000, 79.00000);
    for(new index=74; index<78; index++) SetObjectMaterial(CampDataObject[campid][index], 0, -1, "none", "none", 0xFF808484);
    //luces carpa
    CampDataObject[campid][78]=CreateObject(2074, 311.69241, 1824.52930, 19.50400,   0.00000, 0.00000, 0.00000);
    CampDataObject[campid][79]=CreateObject(2074, 311.71283, 1826.09229, 19.50400,   0.00000, 0.00000, 0.00000);
    
    for(new index=1; index<MAX_CAMP_OBJECT; index++){
        new Float:pos[2][6];
        GetObjectPos(CampDataObject[campid][0],pos[0][0],pos[0][1],pos[0][2]);
        GetObjectPos(CampDataObject[campid][index],pos[1][0],pos[1][1],pos[1][2]);
        GetObjectRot(CampDataObject[campid][index],pos[1][3],pos[1][4],pos[1][5]);

        AttachObjectToObject(CampDataObject[campid][index], CampDataObject[campid][0], floatsub(pos[1][0], pos[0][0]),floatsub(pos[1][1], pos[0][1]),floatsub(pos[1][2], pos[0][2]), pos[1][3],pos[1][4],pos[1][5], 1);
    }
    SetObjectPos(CampDataObject[campid][0],x,y,z-0.9);
    SetObjectRot(CampDataObject[campid][0],0.00000, 0.00000, a-180);
    return true;
}