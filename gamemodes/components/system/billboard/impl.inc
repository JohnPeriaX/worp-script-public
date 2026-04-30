#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>
hook OnGameModeInit(){
    LoadMapBillboard();
    return 1;
}

LoadMapBillboard(){
	tmpobjid = CreateDynamicObject(7914, 1082.967285, -1402.352783, 31.991550, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(tmpobjid, 0, 14584, "ab_abbatoir01", "carpet5kb", 0x00000000);
	boardtext1 = CreateDynamicObject(7914, 1082.977050, -1402.473876, 33.847442, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(boardtext1, 0, 14789, "ab_sfgymmain", "gun_ceiling2_128", 0x00000000);
	SetDynamicObjectMaterialText(boardtext1, 0, "{FFFFFF}ป้ายโฆษณา", 130, "Ariel", 100, 1, 0x00000000, 0x00000000, 1);
	boardtext2 = CreateDynamicObject(7914, 1082.977050, -1402.473876, 30.367397, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00); 
	SetDynamicObjectMaterial(boardtext2, 0, 14789, "ab_sfgymmain", "gun_ceiling2_128", 0x00000000);
	SetDynamicObjectMaterialText(boardtext2, 0, "{FFFFFF}รอการอัพเดท", 130, "Ariel", 100, 1, 0x00000000, 0x00000000, 1);
	tmpobjid = CreateDynamicObject(1259, 1083.638549, -1404.198974, 25.421058, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); 
}

CMD:editboard1(playerid, params[]){
    if(PlayerData[playerid][pAdmin] < 1338) return 1;
    Dialog_ShowEasy(playerid, EditBoard1, DIALOG_STYLE_INPUT, "ป้ายโฆษณา", "ใส่รายละเอียดป้ายโฆษณา: ", "ตกลง", "ยกเลิก");
    return 1;
}

CMD:editboard2(playerid, params[]){
    if(PlayerData[playerid][pAdmin] < 1338) return 1;
    Dialog_ShowEasy(playerid, EditBoard2, DIALOG_STYLE_INPUT, "ป้ายโฆษณา", "ใส่รายละเอียดป้ายโฆษณา: ", "ตกลง", "ยกเลิก");
    return 1;
}

Dialog:EditBoard1(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){   
        new tmptext[128];
        strcat(tmptext, inputtext, 128);
        SetDynamicObjectMaterialText(boardtext1, 0, tmptext, 130, "Ariel", 100, 1, 0x00000000, 0x00000000, 1);
        SendClientMessageEx(playerid, COLOR_YELLOW, "คุณได้ปรับป้ายโฆษณาที่ 1 เป็น %s", inputtext);
    }   
    return 1;
}

Dialog:EditBoard2(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){   
        new tmptext[128];
        strcat(tmptext, inputtext, 128);
        SetDynamicObjectMaterialText(boardtext2, 0, tmptext, 130, "Ariel", 100, 1, 0x00000000, 0x00000000, 1);
        SendClientMessageEx(playerid, COLOR_YELLOW, "คุณได้ปรับป้ายโฆษณาที่ 1 เป็น %s", inputtext);
    }   
    return 1;
}