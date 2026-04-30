#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

hook OnGameModeInit(){
    LoadShipObject();
    LoadMapRoger();
    repeat ShipUpdate();
    return 1;
}

ResetPlayerRogerPlant(playerid){
    PlayerHarvesrRogerPlant[playerid] = false;
    stop HarvestRogerPlantTime[playerid];
    return 1;
}

LoadMapRoger(){
    RogerPlant[0][rogerPlantPos][0] = -2164.989257;
    RogerPlant[0][rogerPlantPos][1] = 1881.778930;
    RogerPlant[0][rogerPlantPos][2] = 8.686772;
    
    RogerPlant[1][rogerPlantPos][0] = -2179.332763;
    RogerPlant[1][rogerPlantPos][1] = 1883.508300;
    RogerPlant[1][rogerPlantPos][2] = 7.986756;

    RogerPlant[2][rogerPlantPos][0] = -2187.804931;
    RogerPlant[2][rogerPlantPos][1] = 1886.008789;
    RogerPlant[2][rogerPlantPos][2] = 8.356753;

    RogerPlant[3][rogerPlantPos][0] = -2117.064697;
    RogerPlant[3][rogerPlantPos][1] = 1860.727172;
    RogerPlant[3][rogerPlantPos][2] = 7.236714;

    RogerPlant[4][rogerPlantPos][0] = -2107.805664;
    RogerPlant[4][rogerPlantPos][1] = 1924.988891;
    RogerPlant[4][rogerPlantPos][2] = 8.756722;

    for(new i=0; i<MAX_ROGERPLANT; i++){
        RogerPlant[i][rogerPlantStill] = true;
        RogerPlant[i][rogerPlantObject] = CreateDynamicObject(19473, RogerPlant[i][rogerPlantPos][0], RogerPlant[i][rogerPlantPos][1], RogerPlant[i][rogerPlantPos][2], 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
        SetDynamicObjectMaterial(RogerPlant[i][rogerPlantObject], 0, -1, "none", "none", 0xFFFF0000);
        SetDynamicObjectMaterial(RogerPlant[i][rogerPlantObject], 3, -1, "none", "none", 0xFFFF0000);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    tmpobjid = CreateDynamicObject(10166, -2117.989746, 1909.491210, -1.486497, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(10166, -2117.989746, 1854.671142, -1.486497, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(10166, -2172.731933, 1893.755126, -1.486497, 0.000000, 0.000000, 128.899978, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(623, -2120.275878, 1917.098876, 5.652240, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(624, -2102.538085, 1865.378906, 9.683287, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(621, -2182.013183, 1856.539916, 5.869951, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(3524, -2144.421386, 1927.698730, 2.544919, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(3434, -2136.044189, 1838.305175, 12.456427, 0.000000, 0.000000, -10.900000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(8483, -2161.284912, 1829.779907, 5.077090, 0.000000, -14.699996, -113.500045, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(17030, -2154.099853, 1829.433593, -1.952878, 0.000000, 0.000000, -175.099868, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1550, -2149.234863, 1899.538818, 0.457565, 0.000000, -30.699995, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1550, -2149.471435, 1899.779541, 0.296879, 0.000000, -30.699995, 71.300003, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(2969, -2148.366210, 1899.146484, 0.347565, 0.000000, 0.000000, -148.099945, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1271, -2152.774414, 1903.524291, 0.427565, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1271, -2152.774414, 1903.524291, 1.097564, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1271, -2152.121826, 1903.524291, 0.397564, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(1462, -2100.878662, 1898.285034, 0.348165, -41.799999, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(933, -2079.257080, 1857.389770, 7.090741, -95.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
    tmpobjid = CreateDynamicObject(2359, -2103.106445, 1866.616088, 10.646774, -28.600008, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); 
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys){
    if(!LoggedIn[playerid]) return 1;
    if(newkeys & KEY_YES){
        new id = -1;
        if((id = RogerPlant_Nearest(playerid)) != -1){
            if(!PlayerHarvesrRogerPlant[playerid]){
                if(RogerPlant[id][rogerPlantUsing]) return ErrorMsg(playerid, "ต้นนี้มีคนกำลังเก็บอยู่");
                SetPlayerHarvestRogerPlant(playerid, id);
            }
        }
    }
    return 1;
}

timer UpdateHarvestRogerPlant[300](playerid){
    if(PlayerHarvesrRogerPlant[playerid]){
        new Float:currentValueMine = GetPlayerProgressBarValue(playerid, NewProgressBar[playerid][0]);
        if(currentValueMine < 100.0){
            currentValueMine++;
            SetPlayerProgressBarValue(playerid, NewProgressBar[playerid][0], currentValueMine);
        }
        else{
            HarvestRoger_Success(playerid);
        }
    }
}

HarvestRoger_Success(playerid){
    new id = GetPVarInt(playerid, "RogerPlant");
    if(id != -1){
        new Float:x, Float:y, Float:z;
        GetPlayerPos(playerid, x, y, z);
        SetPlayerPos(playerid, x-1.0, y, z+1.5);

        RogerPlant[id][rogerPlantUsing] = false;
        RogerPlant[id][rogerPlantStill] = false;
        MoveDynamicObject(RogerPlant[id][rogerPlantObject], RogerPlant[id][rogerPlantPos][0], RogerPlant[id][rogerPlantPos][1], RogerPlant[id][rogerPlantPos][2]-7.0, 5.0, 0.000000, 0.000000, 0.000000);

        ResetPlayerRogerPlant(playerid);
        TogglePlayerControllable(playerid, 1);
        ClearAnimations(playerid);
        SetPlayerProgressBarValue(playerid, NewProgressBar[playerid][0], 0.0);
        HidePlayerProgressBar(playerid, NewProgressBar[playerid][0]);
        PlayerTextDrawHide(playerid, NewProgressText[playerid][0]);
        DestroyPlayerProgressBar(playerid, NewProgressBar[playerid][0]);
        PlayerTextDrawDestroy(playerid, NewProgressText[playerid][0]);

        new itemid = PlayerInventory_AddItem(playerid, "Red Plant of Roger", 2245, 1);
        if(itemid == -1) return ErrorMsg(playerid, "ช่องเก็บของคุณเต็มไม่สามารถเก็บได้อีก");
        SendClientMessage(playerid, 0xFFB23BAA, "[การขุดแร่]:{FFFFFF} คุณได้รับ 'พืชสีแดงของโรเจอร์ (Red Plant of Roger)' + 1");
    }
    return 1;
}

SetPlayerHarvestRogerPlant(playerid, id){
    if(id != -1){
        RogerPlant[id][rogerPlantUsing] = true;
        SetPVarInt(playerid, "RogerPlant", id);
        PlayerHarvesrRogerPlant[playerid] = true;
        TogglePlayerControllable(playerid, 0);
        LoadPlayerNewProgress(playerid);
        ShowPlayerProgressBar(playerid, NewProgressBar[playerid][0]);
        SetPlayerProgressBarColour(playerid, NewProgressBar[playerid][0], 0xDA0000AA);
        SetPlayerProgressBarValue(playerid, NewProgressBar[playerid][0], 0.0);
        ApplyAnimation(playerid,"BOMBER","BOM_Plant",4.1,1,0,0,0,0,1);
        HarvestRogerPlantTime[playerid] = repeat UpdateHarvestRogerPlant(playerid);
    }
}

RogerPlant_Nearest(playerid, Float:radius = 3.0){
    for (new i = 0; i < MAX_ROGERPLANT; i ++) if (RogerPlant[i][rogerPlantStill] && IsPlayerInRangeOfPoint(playerid, radius, RogerPlant[i][rogerPlantPos][0], RogerPlant[i][rogerPlantPos][1], RogerPlant[i][rogerPlantPos][2])) {
		return i;
	}
	return -1;
}

timer ShipUpdate[1000](){
    new Float:x, Float:y, Float:z;
    GetDynamicObjectPos(Ship, x, y, z);
    if(ShipStep == 1 && !ShipMoving){
        MoveDynamicObject(Ship, 1797.133789, 518.085998, 15.994377, 20.0, 0.000000, 0.000000, 89.900047);
        //printf("[Ship]: Move Step 1");
        ShipMoving = true;
    }
    else if(ShipStep == 1 && ShipMoving){
        if(x == 1797.13378 && y == 518.085998 && z == 15.994377){
            MoveDynamicObject(Ship, 1797.133789, 518.085998, 15.994377, 20.0, 0.000000, 0.000000, 77.200012);
            MoveDynamicObject(Ship, 1661.743652, 518.321533, 15.994377, 20.0, 0.000000, 0.000000, 77.200012);
            //printf("[Ship]: Move Step 2");
            ShipStep = 2;
        }
    }
    else if(ShipStep == 2){
        if(x == 1661.743652 && y == 518.321533 && z == 15.994377){
            MoveDynamicObject(Ship, 1661.743652, 518.321533, 15.994377, 20.0, 0.000000, 0.000000, 77.200012);
            MoveDynamicObject(Ship, 1123.500122, 640.606445, 15.994377, 20.0, 0.000000, 0.000000, 77.200012);
            //printf("[Ship]: Move Step 3");
            ShipStep = 3;
        }
    }
    else if(ShipStep == 3){
        if(x == 1123.500122 && y == 640.606445 && z == 15.994377){
            MoveDynamicObject(Ship, 1123.500122, 640.606445, 15.994377, 20.0, 0.000000, 0.000000, 77.200012);
            MoveDynamicObject(Ship, 950.883117, 613.576721, 15.994377, 20.0, 0.000000, 0.000000, 102.899803);
            //printf("[Ship]: Move Step 4");
            ShipStep = 4;
        }
    }
    else if(ShipStep == 4){
        if(x == 950.883117 && y == 613.576721 && z == 15.994377){
            MoveDynamicObject(Ship, 950.883117, 613.576721, 15.994377, 20.0, 0.000000, 0.000000, 102.899803);
            MoveDynamicObject(Ship, 431.324920, 494.583435, 15.994377, 20.0, 0.000000, 0.000000, 102.899803);
            //printf("[Ship]: Move Step 5");
            ShipStep = 5;
        }
    }
    else if(ShipStep == 5){
        if(x == 431.324920 && y == 494.583435 && z == 15.994377){
            MoveDynamicObject(Ship, 431.324920, 494.583435, 15.994377, 20.0, 0.000000, 0.000000, 102.899803);
            MoveDynamicObject(Ship, -122.368980, 367.772125, 15.994377, 20.0, 0.000000, 0.000000, 102.899803);
            //printf("[Ship]: Move Step 6");
            ShipStep = 6;
        }
    }
    else if(ShipStep == 6){
        if(x == -122.368980 && y == 367.772125 && z == 15.994377){
            MoveDynamicObject(Ship, -122.368980, 367.772125, 15.994377, 20.0, 0.000000, 0.000000, 102.899803);
            MoveDynamicObject(Ship, -219.586761, 378.357513, 16.754369, 20.0, 0.000000, 0.000000, 77.899856);
            //printf("[Ship]: Move Step 7");
            ShipStep = 7;
        }
    }
    else if(ShipStep == 7){
        if(x == -219.586761 && y == 378.357513 && z == 16.754369){
            MoveDynamicObject(Ship, -219.586761, 378.357513, 16.754369, 20.0, 0.000000, 0.000000, 77.899856);
            MoveDynamicObject(Ship, -847.323669, 512.934326, 16.754369, 20.0, 0.000000, 0.000000, 77.899856);
            //printf("[Ship]: Move Step 8");
            ShipStep = 8;
        }
    }
    else if(ShipStep == 8){
        if(x == -847.323669 && y == 512.934326 && z == 16.754369){
            MoveDynamicObject(Ship, -847.323669, 512.934326, 16.754369, 20.0, 0.000000, 0.000000, 77.899856);
            MoveDynamicObject(Ship, -1316.986816, 817.938049, 16.754369, 20.0, 0.000000, 0.000000, 56.999916);
            //printf("[Ship]: Move Step 9");
            ShipStep = 9;
        }
    }
    else if(ShipStep == 9){
        if(x == -1316.986816 && y == 817.938049 && z == 16.754369){
            MoveDynamicObject(Ship, -1316.986816, 817.938049, 16.754369, 20.0, 0.000000, 0.000000, 56.999916);
            MoveDynamicObject(Ship, -1408.349731, 1388.338012, 16.754369, 20.0, 0.000000, 0.000000, 9.099933);
            //printf("[Ship]: Move Step 10");
            ShipStep = 10;
        }
    }
    else if(ShipStep == 10){
        if(x == -1408.349731 && y == 1388.338012 && z == 16.754369){
            MoveDynamicObject(Ship, -1408.349731, 1388.338012, 16.754369, 20.0, 0.000000, 0.000000, 9.099933);
            MoveDynamicObject(Ship, -1835.780029, 1694.350219, 16.754369, 20.0, 0.000000, 0.000000, 54.399898);
            //printf("[Ship]: Move Step 11");
            ShipStep = 11;
        }
    }
    else if(ShipStep == 11){
        if(x == -1835.780029 && y == 1694.350219 && z == 16.754369){
            MoveDynamicObject(Ship, -1835.780029, 1694.350219, 16.754369, 20.0, 0.000000, 0.000000, 54.399898);
            MoveDynamicObject(Ship, -1994.968994, 1808.318481, 16.754369, 20.0, 0.000000, 0.000000, 54.399898);
            //printf("[Ship]: Move Step 12");
            ShipStep = 12;
        }
    }
    else if(ShipStep == 12){
        if(x == -1994.968994 && y == 1808.318481 && z == 16.754369){
            MoveDynamicObject(Ship, -1994.968994, 1808.318481, 16.754369, 20.0, 0.000000, 0.000000, 54.399898);
            MoveDynamicObject(Ship, -2071.462402, 1837.099609, 17.430854, 20.0, 0.000000, 0.000000, 130.000030);
            //printf("[Ship]: Move Step 13");
            ShipStep = 13;
        }
    }
    else if(ShipStep == 13 && !ShipStop){
        if(x == -2071.462402 && y == 1837.099609 && z == 17.430854){
            ShipStop = true;
            defer ShipStopRoger();
            //printf("Ship Stop Roger");
        }
    }
    else if(ShipStep == 14){
        if(x == -2202.942382 && y == 1725.994628 && z == 17.430854){
            MoveDynamicObject(Ship, -2202.942382, 1725.994628, 17.430854, 20.0, 0.000000, 0.000000, 130.000030);
            MoveDynamicObject(Ship, -2200.838623, 1639.847900, 17.430854, 20.0, 0.000000, 0.000000, -178.600082);
            //printf("[Ship]: Move Step 15");
            ShipStep = 15;
        }
    }
    else if(ShipStep == 15){
        if(x == -2200.838623 && y == 1639.847900 && z == 17.430854){
            MoveDynamicObject(Ship, -2200.838623, 1639.847900, 17.430854, 20.0, 0.000000, 0.000000, -178.600082);
            MoveDynamicObject(Ship, -2073.596435, 1643.044555, 17.430854, 20.0, 0.000000, 0.000000, -87.400169);
            //printf("[Ship]: Move Step 16");
            ShipStep = 16;
        }
    }
    else if(ShipStep == 16){
        if(x == -2073.596435 && y == 1643.044555 && z == 17.430854){
            MoveDynamicObject(Ship, -2073.596435, 1643.044555, 17.430854, 20.0, 0.000000, 0.000000, -87.400169);
            MoveDynamicObject(Ship, -1796.562133, 1655.623291, 17.430854, 20.0, 0.000000, 0.000000, -87.400169);
            //printf("[Ship]: Move Step 17");
            ShipStep = 17;
        }
    }
    else if(ShipStep == 17){
        if(x == -1796.562133 && y == 1655.623291 && z == 17.430854){
            MoveDynamicObject(Ship, -1796.562133, 1655.623291, 17.430854, 20.0, 0.000000, 0.000000, -87.400169);
            MoveDynamicObject(Ship, -1435.004882, 1380.189819, 17.430854, 20.0, 0.000000, 0.000000, -127.300117);
            //printf("[Ship]: Move Step 18");
            ShipStep = 18;
        }
    }
    else if(ShipStep == 18){
        if(x == -1435.004882 && y == 1380.189819 && z == 17.430854){
            MoveDynamicObject(Ship, -1435.004882, 1380.189819, 17.430854, 20.0, 0.000000, 0.000000, -127.300117);
            MoveDynamicObject(Ship, -1276.166137, 765.999084, 17.430854, 20.0, 0.000000, 0.000000, -165.500198);
            //printf("[Ship]: Move Step 19");
            ShipStep = 19;
        }
    }
    else if(ShipStep == 19){
        if(x == -1276.166137 && y == 765.999084 && z == 17.430854){
            MoveDynamicObject(Ship, -1276.166137, 765.999084, 17.430854, 20.0, 0.000000, 0.000000, -165.500198);
            MoveDynamicObject(Ship, -1095.987304, 625.732666, 17.430854, 20.0, 0.000000, 0.000000, -127.900047);
            //printf("[Ship]: Move Step 20");
            ShipStep = 20;
        }
    }
    else if(ShipStep == 20){
        if(x == -1095.987304 && y == 625.732666 && z == 17.430854){
            MoveDynamicObject(Ship, -1095.987304, 625.732666, 17.430854, 20.0, 0.000000, 0.000000, -127.900047);
            MoveDynamicObject(Ship, -961.290588, 520.874206, 17.430854, 20.0, 0.000000, 0.000000, -127.900047);
            //printf("[Ship]: Move Step 21");
            ShipStep = 21;
        }
    }
    else if(ShipStep == 21){
        if(x == -961.290588 && y == 520.874206 && z == 17.430854){
            MoveDynamicObject(Ship, -961.290588, 520.874206, 17.430854, 20.0, 0.000000, 0.000000, -127.900047);
            MoveDynamicObject(Ship, -220.573440, 373.701660, 17.040847, 20.0, 0.000000, 0.000000, -99.800094);
            //printf("[Ship]: Move Step 22");
            ShipStep = 22;
        }
    }
    else if(ShipStep == 22){
        if(x == -220.573440 && y == 373.701660 && z == 17.040847){
            MoveDynamicObject(Ship, -220.573440, 373.701660, 17.040847, 20.0, 0.000000, 0.000000, -99.800094);
            MoveDynamicObject(Ship, -108.030082, 354.261932, 16.980854, 20.0, 0.000000, 0.000000, -99.800094);
            //printf("[Ship]: Move Step 23");
            ShipStep = 23;
        }
    }
    else if(ShipStep == 23){
        if(x == -108.030082 && y == 354.261932 && z == 16.980854){
            MoveDynamicObject(Ship, -108.030082, 354.261932, 16.980854, 20.0, 0.000000, 0.000000, -99.800094);
            MoveDynamicObject(Ship, 581.608703, 530.847229, 16.980854, 20.0, 0.000000, 0.000000, -74.700088);
            //printf("[Ship]: Move Step 24");
            ShipStep = 24;
        }
    }
    else if(ShipStep == 24){
        if(x == 581.608703 && y == 530.847229 && z == 16.980854){
            MoveDynamicObject(Ship, 581.608703, 530.847229, 16.980854, 20.0, 0.000000, 0.000000, -74.700088);
            MoveDynamicObject(Ship, 984.794189, 641.145507, 16.980854, 20.0, 0.000000, 0.000000, -74.700088);
            //printf("[Ship]: Move Step 25");
            ShipStep = 25;
        }
    }
    else if(ShipStep == 25){
        if(x == 984.794189 && y == 641.145507 && z == 16.980854){
            MoveDynamicObject(Ship, 984.794189, 641.145507, 16.980854, 20.0, 0.000000, 0.000000, -74.700088);
            MoveDynamicObject(Ship, 1860.187866, 518.117065, 16.980854, 20.0, 0.000000, 0.000000, -98.000038);
            //printf("[Ship]: Move Step 26");
            ShipStep = 26;
        }
    }
    else if(ShipStep == 26){
        if(x == 1860.187866 && y == 518.117065 && z == 16.980854){
            MoveDynamicObject(Ship, 1860.187866, 518.117065, 16.980854, 20.0, 0.000000, 0.000000, -98.000038);
            MoveDynamicObject(Ship, 2349.845458, 449.299835, 16.980854, 20.0, 0.000000, 0.000000, -98.000038);
            //printf("[Ship]: Move Step 27");
            ShipStep = 27;
        }
    }
    else if(ShipStep == 27){
        if(x == 2349.845458 && y == 449.299835 && z == 16.980854){
            MoveDynamicObject(Ship, 2349.845458, 449.299835, 16.980854, 20.0, 0.000000, 0.000000, -98.000038);
            MoveDynamicObject(Ship, 2343.282226, 506.865722, 16.980854, 20.0, 0.000000, 0.000000, 55.399955);
            //printf("[Ship]: Move Step 28");
            ShipStep = 28;
        }
    }
    else if(ShipStep == 28){
        if(x == 2343.282226 && y == 506.865722 && z == 16.980854){
            MoveDynamicObject(Ship, 2343.282226, 506.865722, 16.980854, 20.0, 0.000000, 0.000000, 55.399955);
            MoveDynamicObject(Ship, 2285.638183, 517.506347, 15.990831, 20.0, 0.000000, 0.000000, 88.899925);
            //printf("[Ship]: Move Step 29");
            ShipStep = 29;
        }
    }
    else if(ShipStep == 29 && !ShipStop){
        if(x == 2285.638183 && y == 517.506347 && z == 15.990831){
            //printf("Ship Stopped");
            ShipStop = true;
            defer ShipReloadTime();
        }
    }
}

timer ShipStopRoger[20000](){
    ShipStop = false;
    //printf("[Ship]: Move Step 14");
    MoveDynamicObject(Ship, -2071.462402, 1837.099609, 17.430854, 20.0, 0.000000, 0.000000, 130.000030);
    MoveDynamicObject(Ship, -2202.942382, 1725.994628, 17.430854, 20.0, 0.000000, 0.000000, 130.000030);
    ShipStep = 14;
}

timer ShipReloadTime[20000](){
    ShipMoving = false;
    ShipStop = false;
    ShipStep = 1;
}

CMD:shipmove(playerid, params[]){
    repeat ShipUpdate();
    return 1;
}