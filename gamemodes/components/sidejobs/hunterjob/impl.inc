#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

ResetDeerPlayer(playerid){
    PlayerPickingupDeer[playerid] = false;
    return 1;
}

hook OnGameModeInit(){
    RandomHunterJob();
    return 1;
}

forward Deer_Load();
public Deer_Load(){
    new
	    rows;

	cache_get_row_count(rows);

    for (new i = 0; i < rows; i ++) if (i < MAX_DEERS)
	{
	    DeerData[i][deerEx] = true;
        DeerData[i][deerScared] = false;
        DeerData[i][deerIsDead] = false;
        DeerData[i][deerIsPickup] = false;
        DeerData[i][deerDeathTime] = 0;
        KillTimer(DeerData[i][deerTimer]);
        DeerData[i][deerTimer] = 0;
	    cache_get_value_name_float(i, "deerPosX", DeerData[i][deerPos][0]);
	    cache_get_value_name_float(i, "deerPosY", DeerData[i][deerPos][1]);
	    cache_get_value_name_float(i, "deerPosZ", DeerData[i][deerPos][2]);
        cache_get_value_name_float(i, "deerPosA", DeerData[i][deerPos][3]);

        Deer_Count++;

        Deer_RenderRefresh(i);
 	    Deer_Refresh(i);

	}
	printf("(( [MYSQL]: Load %d Deers Successfully ))", Deer_Count);
    return 1;
}

forward SetDeerIsHide(deerid);
public SetDeerIsHide(deerid){
    if(deerid != -1){
        Deer_Refresh(deerid);
    }
}

Deer_RenderRefresh(deerid){
    if(deerid != -1 && DeerData[deerid][deerEx]){
        if(!DeerData[deerid][deerScared] && !DeerData[deerid][deerIsDead]){
            DeerData[deerid][deerObject] = CreateDynamicObject(19315, DeerData[deerid][deerPos][0], DeerData[deerid][deerPos][1], DeerData[deerid][deerPos][2]-0.5, 0, 0, DeerData[deerid][deerPos][3], 0, 0);
            MoveDynamicObject(DeerData[deerid][deerObject], DeerData[deerid][deerPos][0], DeerData[deerid][deerPos][1], DeerData[deerid][deerPos][2]-0.5, 8.0, 0.00000, 0.00000, DeerData[deerid][deerPos][3]);
        }
    }
    return 1;
}

Deer_Refresh(deerid){
    if(deerid != -1 && DeerData[deerid][deerEx]){
        if(!DeerData[deerid][deerIsDead]){
            MoveDynamicObject(DeerData[deerid][deerObject], DeerData[deerid][deerPos][0], DeerData[deerid][deerPos][1], DeerData[deerid][deerPos][2]-0.5, 3.0, 0.00000, 0.00000, DeerData[deerid][deerPos][3]);
        }
        else{
            MoveDynamicObject(DeerData[deerid][deerObject], DeerData[deerid][deerPos][0], DeerData[deerid][deerPos][1], DeerData[deerid][deerPos][2]-0.5-10.0, 3.0, 0.00000, 0.00000, DeerData[deerid][deerPos][3]);
        }
    }
    return 1;
}

ShowDeerSeller(playerid){
    new string[128];
    format(string, sizeof(string), "คุณมีเนื้อกวางอยู่: %d ชิ้น\nกรอกจำนวนเนื้อกวางที่ต้องการขาย", PlayerInventory_AllCount(playerid, "Raw Deer Meat"));
    Dialog_ShowEasy(playerid, SellDeer, DIALOG_STYLE_INPUT, "ขายเนื้อกวาง", string, "ขาย", "ยกเลิก");
    return 1;
}

Dialog:SellDeer(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        new amount = strval(inputtext);
        new string[128];
        if(amount < 0){
            format(string, sizeof(string), "* คุณต้องกรอกจำนวนมากกว่า 0 *\nคุณมีเนื้อกวางอยู่: %d ชิ้น\nกรอกจำนวนเนื้อกวางที่ต้องการขาย", PlayerInventory_AllCount(playerid, "Raw Deer Meat"));
            Dialog_ShowEasy(playerid, SellDeer, DIALOG_STYLE_INPUT, "ขายเนื้อกวาง", string, "ขาย", "ยกเลิก");
            return 1;
        }

        if(amount > PlayerInventory_AllCount(playerid, "Raw Deer Meat")){
            format(string, sizeof(string), "* คุณมีจำนวนเนื้อกวางไม่พอกับจำนวนที่กรอก *\nคุณมีเนื้อกวางอยู่: %d ชิ้น\nกรอกจำนวนเนื้อกวางที่ต้องการขาย", PlayerInventory_AllCount(playerid, "Raw Deer Meat"));
            Dialog_ShowEasy(playerid, SellDeer, DIALOG_STYLE_INPUT, "ขายเนื้อกวาง", string, "ขาย", "ยกเลิก");
            return 1;
        }

        new price = amount * Deer_Price;
        PlayerInventory_Remove(playerid, "Raw Deer Meat", amount);
        GiveMoney(playerid, price, "sell raw deer meat");
        SendClientMessageEx(playerid, 0xFF7000AA, "> คุณได้ขายเนื้อวัวจำนวน %d ชิ้นและได้รับเงิน %s", amount, FormatNumber(price));
    }
    return 1;
}

forward RandomHunterJob();
public RandomHunterJob(){
    new RandomDeer[3] = {30, 40, 50};
    new randomdeerprice = random(sizeof(RandomDeer));
    Deer_Price = RandomDeer[randomdeerprice];
	return 1;
}

forward ReviveDeer(deerid);
public ReviveDeer(deerid){
    if(deerid != -1){
        if(DeerData[deerid][deerDeathTime] > 0){
            DeerData[deerid][deerDeathTime]--;
            DeerData[deerid][deerTimer] = SetTimerEx("ReviveDeer", 1000, false, "i", deerid);
        } 
        else if(DeerData[deerid][deerDeathTime] == 0){
            DeerData[deerid][deerScared] = false;
            DeerData[deerid][deerIsDead] = false;
            DeerData[deerid][deerIsPickup] = false;
            DeerData[deerid][deerDeathTime] = 0;
            KillTimer(DeerData[deerid][deerTimer]);
            Deer_Refresh(deerid);
        }
    }
    return 1;
}

forward SetDeerOnHand(playerid);
public SetDeerOnHand(playerid){
    SetPlayerAttachedObject(playerid,8,19315,5,0.489001,-0.028000,0.212000,0.000000,-14.899993,0.000000,1.000000,1.000000,1.000000);
    return 1;
}

CMD:editdeer(playerid, params[]){
    new Float: rx, Float: ry;
    if(PlayerData[playerid][pAdmin] >= 1338){
        if(sscanf(params, "ff", rx, ry)) return 1;
        for(new i=0; i<MAX_DEERS; i++){
            if(DeerData[i][deerEx] && !DeerData[i][deerScared]){
                if(IsPlayerInRangeOfPoint(playerid, 3.0, DeerData[i][deerPos][0], DeerData[i][deerPos][1], DeerData[i][deerPos][2]))
                    MoveDynamicObject(DeerData[i][deerObject], DeerData[i][deerPos][0], DeerData[i][deerPos][1], DeerData[i][deerPos][2], 8.0, rx, ry, DeerData[i][deerPos][3]);
            }
        }
    }
    return 1;
}

CMD:reloaddeer(playerid, params[]){
    if(!LoggedIn[playerid]) return 1;
    if(PlayerData[playerid][pAdmin] >= 1338){
        mysql_tquery(dbCon, "SELECT * FROM `deers`", "Deer_Load", "");
    }
    return 1;
}