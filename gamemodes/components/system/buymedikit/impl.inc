#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

hook OnGameModeInit(){
    CreateDynamic3DTextLabel("[ร้านขายยา]\nกด 'Y' เพื่อซื้อ", 0xFF6060FF, 1386.9414,-20.6183,1001.0047, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, -1, -1);
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys){
    if(!LoggedIn[playerid]) return 1;
    if(newkeys & KEY_YES){
        if(IsPlayerInRangeOfPoint(playerid, 3.0, 1386.9414,-20.6183,1001.0047)){
            ShowPlayerMenuBuyMedikit(playerid);
        }
    }
    return 1;
}

ResetPlayerHealing(playerid){
    stop HealingTimer[playerid];
    PlayerHealing[playerid] = false;
    return 1;
}

ShowPlayerMenuBuyMedikit(playerid){
    new string[128];
    format(string, sizeof string, "| ผ้าพันแผล [$3,500/ชิ้น]");
    Dialog_ShowEasy(playerid, BuyMedikit, DIALOG_STYLE_LIST, "ร้านขายยา", string, "เลือก", "ยกเลิก");
    return 1;
}

Dialog:BuyMedikit(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        if(PlayerData[playerid][pPlayerhour] < 30) return ErrorMsg(playerid, "คุณต้องมีชั่วโมงออนไลน์มากกว่าหรือเท่ากับ 30");
        Dialog_ShowEasy(playerid, BuyingBandage, DIALOG_STYLE_INPUT, "ซื้อถุงเลือด", "กรุณาใส่จำนวนที่ต้องการจะซื้อ: ", "ตกลง", "กลับ");
    }
    return 1;
}

Dialog:BuyingBandage(playerid, response, listitem, inputtext[]){
    if(!response) return ShowPlayerMenuBuyMedikit(playerid);
    if(response){
        new amount = strval(inputtext);
        if(amount <= 0 || amount > 5) return Dialog_ShowEasy(playerid, BuyingBandage, DIALOG_STYLE_INPUT, "ซื้อถุงเลือด", "[!] คุณต้องใส่จำนวนมากกว่า 0 และซื้อได้ไม่เกินรอบละ 5 ชิ้นเท่านั้น\nกรุณาใส่จำนวนที่ต้องการจะซื้อ: ", "ตกลง", "กลับ");
        new price = amount * 3500;
        if(GetMoney(playerid) < price) return Dialog_ShowEasy(playerid, BuyingBandage, DIALOG_STYLE_INPUT, "ซื้อถุงเลือด", "[!] คุณมีเงินไม่พอที่จะซื้อจำนวนที่ใส่\nกรุณาใส่จำนวนที่ต้องการจะซื้อ: ", "ตกลง", "กลับ");
        
        if(PlayerData[playerid][pBandageBuying] + amount > 5) return SendClientMessageEx(playerid, COLOR_RED, "| คุณสามารถซื้อได้วันละ 5 ชิ้นเท่านั้น (สามารถซื้อได้อีก %d ชิ้น)", 5 - PlayerData[playerid][pBandageBuying]);
        PlayerData[playerid][pBandageBuying] += amount;
        new itemid = PlayerInventory_AddItem(playerid, "Bandage", 11747, amount);
        if(itemid == -1) return ErrorMsg(playerid, "กระเป๋าของคุณเต็มไม่สามารถเก็บไอเท็มเพิ่มได้อีก");
        GiveMoney(playerid, -price, "ซื้อ Bandage จากโรงพยาบาล");
        new string[128];
        format(string, sizeof string, "| คุณได้ซื้อ Bandage จำนวน %d ชิ้นในราคา %s เรียบร้อยแล้ว", amount, FormatNumber(price));
        Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "การซื้อสำเร็จ", string, "ตกลง", "");
    }
    return 1;
}

timer PlayerAnimation[300](playerid){
    ApplyAnimation(playerid,"BOMBER","BOM_Plant",4.1,1,0,0,0,0,1);
}

timer HealingTime[50](playerid){
    if(PlayerHealing[playerid] && LoggedIn[playerid]){
        new Float:value, string[128];
        value = GetPlayerProgressBarValue(playerid, ProgressbarJob[playerid]);
        if(value < 100.0){
            value += 1.0;
            SetPlayerProgressBarValue(playerid, ProgressbarJob[playerid], value);
            format(string,sizeof(string),"Healing... (%.0f)", value);
            PlayerTextDrawSetString(playerid, PlayerTextDrawJob[playerid], string);
        }
        else{
            ResetPlayerHealing(playerid);
            DestroyPlayerProgressbar_Job(playerid);
            SetPlayerHealth(playerid, 100.0);
            TogglePlayerControllable(playerid, 1);
            ClearAnimations(playerid);
            PlayerInventory_Remove(playerid, "Bandage", 1);
        }
    }
}

SetPlayerHealingWithBandage(playerid){
    CreatePlayerProgressbar_Job(playerid, 0xFF3030AA);
    ResetPlayerHealing(playerid);
    PlayerHealing[playerid] = true;
    TogglePlayerControllable(playerid, 0);
    defer PlayerAnimation(playerid);
    HealingTimer[playerid] = repeat HealingTime(playerid);
    return 1;
}