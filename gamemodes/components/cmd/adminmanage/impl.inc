#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

forward server_Load();
public server_Load(){
	static
	    rows;

	cache_get_row_count(rows);

	for (new i = 0; i < rows; i ++) if (i < 1){
		cache_get_value_name_int(i, "serverID", ServerData[serverID]);

		cache_get_value_name_float(i, "ServerNewbiePosXLS", ServerData[ServerNewbiePosLS][0]);
        cache_get_value_name_float(i, "ServerNewbiePosYLS", ServerData[ServerNewbiePosLS][1]);
        cache_get_value_name_float(i, "ServerNewbiePosZLS", ServerData[ServerNewbiePosLS][2]);
        cache_get_value_name_float(i, "ServerNewbiePosALS", ServerData[ServerNewbiePosLS][3]);

        cache_get_value_name_float(i, "ServerNewbiePosXSF", ServerData[ServerNewbiePosSF][0]);
        cache_get_value_name_float(i, "ServerNewbiePosYSF", ServerData[ServerNewbiePosSF][1]);
        cache_get_value_name_float(i, "ServerNewbiePosZSF", ServerData[ServerNewbiePosSF][2]);
        cache_get_value_name_float(i, "ServerNewbiePosASF", ServerData[ServerNewbiePosSF][3]);

        cache_get_value_name_float(i, "ServerNewbiePosXLV", ServerData[ServerNewbiePosLV][0]);
        cache_get_value_name_float(i, "ServerNewbiePosYLV", ServerData[ServerNewbiePosLV][1]);
        cache_get_value_name_float(i, "ServerNewbiePosZLV", ServerData[ServerNewbiePosLV][2]);
        cache_get_value_name_float(i, "ServerNewbiePosALV", ServerData[ServerNewbiePosLV][3]);

        cache_get_value_name_int(i, "ServerCanAttack", ServerData[ServerCanAttack]);
        cache_get_value_name_int(i, "ServerCanHoldGangZone", ServerData[ServerCanHoldGangZone]);
        cache_get_value_name_int(i, "ServerExp", ServerData[ServerExp]);
        cache_get_value_name_int(i, "ServerTax", ServerData[ServerTax]);
        cache_get_value_name_int(i, "ServerUseWeapon", ServerData[ServerUseWeapon]);

        cache_get_value_name_int(i, "ServerCanGiveMoney", ServerData[ServerCanGiveMoney]);
        cache_get_value_name_int(i, "ServerCanGiveWeapon", ServerData[ServerCanGiveWeapon]);
        cache_get_value_name_int(i, "ServerCanDropItem", ServerData[ServerCanDropItem]);
        cache_get_value_name_int(i, "ServerCanStoreHome", ServerData[ServerCanStoreHome]);
        cache_get_value_name_int(i, "ServerSkillGang", ServerData[ServerSkillGang]);
        cache_get_value_name_int(i, "ServerCanTrade", ServerData[ServerCanTrade]);
        cache_get_value_name_int(i, "ServerCanTradeSpecial", ServerData[ServerCanTradeSpecial]);
        cache_get_value_name_int(i, "ServerCanWdWeaponGang", ServerData[ServerCanWdWeaponGang]);
        cache_get_value_name_int(i, "ServerWeaponGangNotItem", ServerData[ServerWeaponGangNotItem]);
        cache_get_value_name_int(i, "ServerLocked", ServerData[ServerLocked]);
        cache_get_value_name(i, "ServerPassword", ServerData[ServerPassword], 64);
        cache_get_value_name_int(i, "ServerWarCityTime", ServerData[ServerWarCityTime]);
	}
	return 1;
}

server_Save()
{
	new
	    query[2056];

	format(query, sizeof(query), "UPDATE `serverconfig` SET  `ServerNewbiePosXLS` = '%f', `ServerNewbiePosYLS` = '%f', `ServerNewbiePosZLS` = '%f', `ServerNewbiePosALS` = '%f', `ServerCanAttack` = '%d', `ServerCanHoldGangZone` = '%d', `ServerExp` = '%d', `ServerTax` = '%d'",
		ServerData[ServerNewbiePosLS][0],
        ServerData[ServerNewbiePosLS][1],
        ServerData[ServerNewbiePosLS][2],
        ServerData[ServerNewbiePosLS][3],
        ServerData[ServerCanAttack],
        ServerData[ServerCanHoldGangZone],
        ServerData[ServerExp],
        ServerData[ServerTax]
	);

    format(query, sizeof(query), "%s, `ServerNewbiePosXSF` = '%f', `ServerNewbiePosYSF` = '%f', `ServerNewbiePosZSF` = '%f', `ServerNewbiePosASF` = '%f', `ServerNewbiePosXLV` = '%f', `ServerNewbiePosYLV` = '%f', `ServerNewbiePosZLV` = '%f', `ServerNewbiePosALV` = '%f', `ServerUseWeapon` = '%d'",
        query,
        ServerData[ServerNewbiePosSF][0],
        ServerData[ServerNewbiePosSF][1],
        ServerData[ServerNewbiePosSF][2],
        ServerData[ServerNewbiePosSF][3],
        ServerData[ServerNewbiePosLV][0],
        ServerData[ServerNewbiePosLV][1],
        ServerData[ServerNewbiePosLV][2],
        ServerData[ServerNewbiePosLV][3],
        ServerData[ServerUseWeapon]
	);

    format(query, sizeof(query), "%s, `ServerCanGiveMoney` = '%d', `ServerCanGiveWeapon` = '%d', `ServerCanDropItem` = '%d', `ServerCanStoreHome` = '%d', `ServerSkillGang` = '%d', `ServerCanTrade` = '%d', `ServerCanTradeSpecial` = '%d', `ServerCanWdWeaponGang` = '%d', `ServerWeaponGangNotItem` = '%d'",
        query,
        ServerData[ServerCanGiveMoney],
        ServerData[ServerCanGiveWeapon],
        ServerData[ServerCanDropItem],
        ServerData[ServerCanStoreHome],
        ServerData[ServerSkillGang],
        ServerData[ServerCanTrade],
        ServerData[ServerCanTradeSpecial],
        ServerData[ServerCanWdWeaponGang],
        ServerData[ServerWeaponGangNotItem]
	);

    mysql_format(dbCon, query, sizeof(query), "%s, `ServerLocked` = '%d', `ServerPassword` = '%e', `ServerWarCityTime` = '%d' WHERE `serverID` = '%d'",
        query,
        ServerData[ServerLocked],
        ServerData[ServerPassword],
        ServerData[ServerWarCityTime],
        ServerData[serverID]
	);
	return mysql_tquery(dbCon, query);
}

CMD:manageserver(playerid, params[]){

    if(!LoggedIn[playerid]) return 0;

    if(PlayerData[playerid][pAdmin] < 1338) return ErrorMsg(playerid, "คุณไม่ได้รับอนุญาติ");

    ManageServer(playerid);
    return 1;
}

ManageServer(playerid){
    new caption[128], dialog_str[1024];
    new attackstats[32];
    new gangzonestats[32];
    new weaponstring[32];
    new givemoneystring[32];
    new giveweaponstring[32];
    new dropitemstring[32];
    new homestorestring[32];
    new damageskillgang[32];
    new cantrade[32];
    new cantradespec[32];
    new weapongang[32];
    new weapongangitem[32];
    new serverstatus[32];

    if(ServerData[ServerCanAttack] == 0)
        attackstats = "ปิดใช้งาน";
    else
        attackstats = "เปิดใช้งาน";

    if(ServerData[ServerCanHoldGangZone] == 0)
        gangzonestats = "ปิดใช้งาน";
    else
        gangzonestats = "เปิดใช้งาน";

    if(ServerData[ServerUseWeapon] == 0) weaponstring = "เปิดใช้งาน";
    else weaponstring = "ปิดใช้งาน";

    if(ServerData[ServerCanGiveMoney] == 0) givemoneystring = "เปิดใช้งาน";
    else givemoneystring = "ปิดใช้งาน";

    if(ServerData[ServerCanGiveWeapon] == 0) giveweaponstring = "เปิดใช้งาน";
    else giveweaponstring = "ปิดใช้งาน";

    if(ServerData[ServerCanDropItem] == 0) dropitemstring = "เปิดใช้งาน";
    else dropitemstring = "ปิดใช้งาน";

    if(ServerData[ServerCanStoreHome] == 0) homestorestring = "เปิดใช้งาน";
    else homestorestring = "ปิดใช้งาน";

    if(ServerData[ServerSkillGang] == 0) damageskillgang = "เปิดใช้งาน";
    else damageskillgang = "ปิดใช้งาน";

    if(ServerData[ServerCanTrade] == 0) cantrade = "เปิดใช้งาน";
    else cantrade = "ปิดใช้งาน";

    if(ServerData[ServerCanTradeSpecial] == 0) cantradespec = "เปิดใช้งาน";
    else cantradespec = "ปิดใช้งาน";

    if(ServerData[ServerCanWdWeaponGang] == 0) weapongang = "เปิดใช้งาน";
    else weapongang = "ปิดใช้งาน";

    if(ServerData[ServerWeaponGangNotItem] == 0) weapongangitem = "เปิดใช้งาน";
    else weapongangitem = "ปิดใช้งาน";

    if(!ServerData[ServerLocked]) serverstatus = "ปลดล็อค";
    else serverstatus = "ล็อค";

    format(caption, sizeof(caption), "ระบบจัดการเซิฟเวอร์");
    format(dialog_str, sizeof dialog_str, "- แก้ไขจุดเกิดเด็กใหม่เมือง LS\n- แก้ไขจุดเกิดเด็กใหม่เมือง SF\n- แก้ไขจุดเกิดเด็กใหม่เมือง LV\n- ระบบกันทำดาเมจ [%s]\n- การยึดโซนแก๊ง [%s]\n- ปรับ EXP ของเซิฟเวอร์ [%s]\
    \n- ปรับภาษีรายชั่วโมง [%s]\n- ระบบอนุญาตใช้อาวุธ [%s]\n- ระบบอนุญาตให้เงิน [%s]\n- ระบบอนุญาตให้อาวุธ [%s]\n- ระบบอนุญาตดรอปไอเท็ม [%s]\n- ระบบอนุญาตการฝากของในบ้าน [%s]\n- ระบบบัพดาเมจแก๊ง [%s]\n- ระบบแลกเปลี่ยนไอเท็ม [%s]\n- แลกเปลี่ยนอาวุธและยาเกราะ [%s]\
    \n- ระบบอนุญาติเบิกอาวุธแก๊ง [%s]\n- ระบบเบิกอาวุธแก๊งไม่เสียของ [%s]\n- สถานะเซิฟเวอร์ [%s]\n- รหัสผ่านเข้าเซิฟเวอร์ [%s]\n- เวลาในการยึดวอเมือง [%d วินาที]", attackstats, gangzonestats, FormatNumberNotMoney(ServerData[ServerExp]), FormatNumber(ServerData[ServerTax]), weaponstring, givemoneystring, giveweaponstring
    , dropitemstring, homestorestring, damageskillgang, cantrade, cantradespec, weapongang, weapongangitem, serverstatus, ServerData[ServerPassword], ServerData[ServerWarCityTime]);
    Dialog_ShowEasy(playerid, EditServer, DIALOG_STYLE_TABLIST, caption, dialog_str, "เลือก", "ปิด");
    return 1;
}

Dialog:EditServer(playerid, response, listitem, inputtext[]){
    if(!response)
        return 1;

    if(response){
        new string[128];
        if(listitem == 0){
            new Float:x, Float:y, Float:z, Float:a;
            GetPlayerPos(playerid, x, y, z);
            GetPlayerFacingAngle(playerid, a);
            ServerData[ServerNewbiePosLS][0] = x;
            ServerData[ServerNewbiePosLS][1] = y;
            ServerData[ServerNewbiePosLS][2] = z;
            ServerData[ServerNewbiePosLS][3] = a;
            format(string, sizeof(string), "ผู้ดูแล %s ได้ปรับจุดเกิดเมือง LS มายังจุดของเขาแล้ว", ReturnRoleplayName(playerid));
		    SendAdminsMessage(1, COLOR_GRAY, string);
            server_Save();
        }
        if(listitem == 1){
            new Float:x, Float:y, Float:z, Float:a;
            GetPlayerPos(playerid, x, y, z);
            GetPlayerFacingAngle(playerid, a);
            ServerData[ServerNewbiePosSF][0] = x;
            ServerData[ServerNewbiePosSF][1] = y;
            ServerData[ServerNewbiePosSF][2] = z;
            ServerData[ServerNewbiePosSF][3] = a;
            format(string, sizeof(string), "ผู้ดูแล %s ได้ปรับจุดเกิดเมือง SF มายังจุดของเขาแล้ว", ReturnRoleplayName(playerid));
		    SendAdminsMessage(1, COLOR_GRAY, string);
            server_Save();
        }
        if(listitem == 2){
            new Float:x, Float:y, Float:z, Float:a;
            GetPlayerPos(playerid, x, y, z);
            GetPlayerFacingAngle(playerid, a);
            ServerData[ServerNewbiePosLV][0] = x;
            ServerData[ServerNewbiePosLV][1] = y;
            ServerData[ServerNewbiePosLV][2] = z;
            ServerData[ServerNewbiePosLV][3] = a;
            format(string, sizeof(string), "ผู้ดูแล %s ได้ปรับจุดเกิดเมือง LV มายังจุดของเขาแล้ว", ReturnRoleplayName(playerid));
		    SendAdminsMessage(1, COLOR_GRAY, string);
            server_Save();
        }
        if(listitem == 3){
            if(ServerData[ServerCanAttack] == 0){
                ServerData[ServerCanAttack] = 1;
                SendClientMessageToAllEx(0xFF0000AA, "- ผู้ดูแลระบบได้ 'เปิด' ระบบกันทำดาเมจ เรียบร้อยแล้ว");
            }
            else{
                ServerData[ServerCanAttack] = 0;
                SendClientMessageToAllEx(0xFF0000AA, "- ผู้ดูแลระบบได้ 'ปิด' ระบบกันทำดาเมจ เรียบร้อยแล้ว");
            }
            server_Save();
        }
        if(listitem == 4){
            if(ServerData[ServerCanHoldGangZone] == 0){
                ServerData[ServerCanHoldGangZone] = 1;
                SendClientMessageToAllEx(0xFF0000AA, "- ผู้ดูแลระบบได้ 'เปิด' การยึดโซนแก๊ง เรียบร้อยแล้ว");

                foreach(new x : Player){
                    if(!LoggedIn[x]) continue;
                    SetGroupColor(x);
                    SetPlayerNameTag(x, x);
                }

            }
            else{
                ServerData[ServerCanHoldGangZone] = 0;
                SendClientMessageToAllEx(0xFF0000AA, "- ผู้ดูแลระบบได้ 'ปิด' การยึดโซนแก๊ง เรียบร้อยแล้ว");
                
                foreach(new x : Player){
                    if(!LoggedIn[x]) continue;
                    SetPlayerColor(x, 0xFFFFFF00);
                }
            }
            server_Save();
        }
        if(listitem == 5){
            new caption[128];
            format(caption, sizeof(caption), "ขณะนี้ EXP x %s", FormatNumberNotMoney(ServerData[ServerExp]));
            Dialog_ShowEasy(playerid, EditExp, DIALOG_STYLE_INPUT, caption, "กรุณากรอก Exp ที่จะคูณ: ", "ตกลง", "ยกเลิก");
        }
        if(listitem == 6){
            new caption[128];
            format(caption, sizeof(caption), "ขณะนี้ภาษีรายชั่วโมงคือ %s", FormatNumber(ServerData[ServerTax]));
            Dialog_ShowEasy(playerid, EditTax, DIALOG_STYLE_INPUT, caption, "กรุณากรอก ภาษี ที่ต้องการ: ", "ตกลง", "ยกเลิก");
        }
        if(listitem == 7){
            if(ServerData[ServerUseWeapon] == 0){
                ServerData[ServerUseWeapon] = 1;
                format(string, sizeof(string), "ผู้ดูแล %s ได้ทำการปิดระบบอนุญาตการใช้อาวุธ");
		        SendAdminsMessage(1, COLOR_RED, string);
            }
            else{
                ServerData[ServerUseWeapon] = 0;
                format(string, sizeof(string), "ผู้ดูแล %s ได้ทำการเปิดระบบอนุญาตการใช้อาวุธ");
		        SendAdminsMessage(1, COLOR_YELLOW, string);
            }
            server_Save();
        }
        if(listitem == 8){
            if(ServerData[ServerCanGiveMoney] == 0){
                ServerData[ServerCanGiveMoney] = 1;
                format(string, sizeof(string), "ผู้ดูแล %s ได้ทำการปิดระบบอนุญาตการให้เงิน");
		        SendAdminsMessage(1, COLOR_RED, string);
            }
            else{
                ServerData[ServerCanGiveMoney] = 0;
                format(string, sizeof(string), "ผู้ดูแล %s ได้ทำการเปิดระบบอนุญาตการให้เงิน");
		        SendAdminsMessage(1, COLOR_YELLOW, string);
            }
            server_Save();
        }
        if(listitem == 9){
            if(ServerData[ServerCanGiveWeapon] == 0){
                ServerData[ServerCanGiveWeapon] = 1;
                format(string, sizeof(string), "ผู้ดูแล %s ได้ทำการปิดระบบอนุญาตการให้อาวุธ");
		        SendAdminsMessage(1, COLOR_RED, string);
            }
            else{
                ServerData[ServerCanGiveWeapon] = 0;
                format(string, sizeof(string), "ผู้ดูแล %s ได้ทำการเปิดระบบอนุญาตการให้อาวุธ");
		        SendAdminsMessage(1, COLOR_YELLOW, string);
            }
            server_Save();
        }
        if(listitem == 10){
            if(ServerData[ServerCanDropItem] == 0){
                ServerData[ServerCanDropItem] = 1;
                format(string, sizeof(string), "ผู้ดูแล %s ได้ทำการปิดระบบอนุญาตการทิ้งไอเท็ม");
		        SendAdminsMessage(1, COLOR_RED, string);
            }
            else{
                ServerData[ServerCanDropItem] = 0;
                format(string, sizeof(string), "ผู้ดูแล %s ได้ทำการเปิดระบบอนุญาตการทิ้งไอเท็ม");
		        SendAdminsMessage(1, COLOR_YELLOW, string);
            }
            server_Save();
        }
        if(listitem == 11){
            if(ServerData[ServerCanStoreHome] == 0){
                ServerData[ServerCanStoreHome] = 1;
                format(string, sizeof(string), "ผู้ดูแล %s ได้ทำการปิดระบบอนุญาตการฝากของในบ้าน");
		        SendAdminsMessage(1, COLOR_RED, string);
            }
            else{
                ServerData[ServerCanStoreHome] = 0;
                format(string, sizeof(string), "ผู้ดูแล %s ได้ทำการเปิดระบบอนุญาตการฝากของในบ้าน");
		        SendAdminsMessage(1, COLOR_YELLOW, string);
            }
            server_Save();
        }
        if(listitem == 12){
            if(ServerData[ServerSkillGang] == 0){
                ServerData[ServerSkillGang] = 1;
                format(string, sizeof(string), "ผู้ดูแล %s ได้ทำการปิดบัพสกิลของแก๊ง");
		        SendAdminsMessage(1, COLOR_RED, string);
            }
            else{
                ServerData[ServerSkillGang] = 0;
                format(string, sizeof(string), "ผู้ดูแล %s ได้ทำการเปิดบัพสกิลของแก๊ง");
		        SendAdminsMessage(1, COLOR_YELLOW, string);
            }
            server_Save();
        }
        if(listitem == 13){
            if(ServerData[ServerCanTrade] == 0){
                ServerData[ServerCanTrade] = 1;
                format(string, sizeof(string), "ผู้ดูแล %s ได้ทำการปิดระบบแลกเปลี่ยนไอเท็ม");
		        SendAdminsMessage(1, COLOR_RED, string);
            }
            else{
                ServerData[ServerCanTrade] = 0;
                format(string, sizeof(string), "ผู้ดูแล %s ได้ทำการเปิดระบบแลกเปลี่ยนไอเท็ม");
		        SendAdminsMessage(1, COLOR_YELLOW, string);
            }
            server_Save();
        }
        if(listitem == 14){
            if(ServerData[ServerCanTradeSpecial] == 0){
                ServerData[ServerCanTradeSpecial] = 1;
                format(string, sizeof(string), "ผู้ดูแล %s ได้ทำการปิดระบบแลกเปลี่ยนอาวุธและยาเกราะ");
		        SendAdminsMessage(1, COLOR_RED, string);
            }
            else{
                ServerData[ServerCanTradeSpecial] = 0;
                format(string, sizeof(string), "ผู้ดูแล %s ได้ทำการเปิดระบบแลกเปลี่ยนอาวุธและยาเกราะ");
		        SendAdminsMessage(1, COLOR_YELLOW, string);
            }
            server_Save();
        }
        if(listitem == 15){
            if(ServerData[ServerCanWdWeaponGang] == 0){
                ServerData[ServerCanWdWeaponGang] = 1;
                format(string, sizeof(string), "ผู้ดูแล %s ได้ทำการปิดระบบเบิกอาวุธแก๊ง");
		        SendAdminsMessage(1, COLOR_RED, string);
            }
            else{
                ServerData[ServerCanWdWeaponGang] = 0;
                format(string, sizeof(string), "ผู้ดูแล %s ได้ทำการเปิดระบบเบิกอาวุธแก๊ง");
		        SendAdminsMessage(1, COLOR_YELLOW, string);
            }
            server_Save();
        }
        if(listitem == 16){
            if(ServerData[ServerWeaponGangNotItem] == 0){
                ServerData[ServerWeaponGangNotItem] = 1;
                format(string, sizeof(string), "ผู้ดูแล %s ได้ทำการปิดระบบเบิกอาวุธแก๊งเสียของ");
		        SendAdminsMessage(1, COLOR_RED, string);
            }
            else{
                ServerData[ServerWeaponGangNotItem] = 0;
                format(string, sizeof(string), "ผู้ดูแล %s ได้ทำการเปิดระบบเบิกอาวุธแก๊งเสียของ");
		        SendAdminsMessage(1, COLOR_YELLOW, string);
            }
            server_Save();
        }
        if(listitem == 17){
            if(!ServerData[ServerLocked]){
                ServerData[ServerLocked] = true;
                SendRconCommand("password 0");
                new str[64];
                format(str, sizeof(str), "password %s", ServerData[ServerPassword]);
                SendRconCommand(str);
                format(string, sizeof(string), "ผู้ดูแล %s ได้ทำการล็อคเซิฟเวอร์ด้วยรหัสผ่าน %s เรียบร้อยแล้ว", ReturnRoleplayName(playerid), ServerData[ServerPassword]);
		        SendAdminsMessage(1, COLOR_YELLOW, string);
                server_Save();
            }
            else{
                ServerData[ServerLocked] = 0;
                SendRconCommand("password 0");
                format(string, sizeof(string), "ผู้ดูแล %s ได้ทำการปลดล็อคเซิฟเวอร์เรียบร้อยแล้ว");
		        SendAdminsMessage(1, COLOR_YELLOW, string);
                server_Save();
            }
        }
        if(listitem == 18){
            Dialog_ShowEasy(playerid, PasswordServer, DIALOG_STYLE_INPUT, "รหัสผ่านเข้าเซิฟเวอร์", "กรุณากรอกรหัสผ่านเข้าเซิฟเวอร์: ", "ตกลง", "ปิด");
        }
        if(listitem == 19){
            Dialog_ShowEasy(playerid, SetTimeWarCity, DIALOG_STYLE_INPUT, "เวลาสำหรับการวอยึดเมือง", "กรุณากรอกเวลาในวอยึดเมือง: ", "ตกลง", "ยกเลิก");
        }
    }
    return 1;
}

Dialog:SetTimeWarCity(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response) {
        new string[128];
        new time = strval(inputtext);
        if(time < 0) return Dialog_ShowEasy(playerid, SetTimeWarCity, DIALOG_STYLE_INPUT, "เวลาสำหรับการวอยึดเมือง", "[!] คุณจำเป็นต้องกรอกเวลามากกว่า 0 วินาที\nกรุณากรอกเวลาในวอยึดเมือง: ", "ตกลง", "ยกเลิก");
        ServerData[ServerWarCityTime] = time;
        server_Save();
        format(string, sizeof(string), "ผู้ดูแล %s ได้ทำการปรับเวลาการยึดวอเมืองเป็น %d วินาทีแล้ว", ReturnRoleplayName(playerid), ServerData[ServerWarCityTime]);
        SendAdminsMessage(1, COLOR_YELLOW, string);
    }
    return 1;
}

Dialog:PasswordServer(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        new string[64];
		if(isnull(inputtext) || strlen(inputtext) >= 64) {
			format(string, sizeof(string), "ความยาวของชื่อต้องมากกว่า 0 และไม่เกิน 3642", ServerData[ServerPassword]);
			Dialog_ShowEasy(playerid, PasswordServer, DIALOG_STYLE_INPUT, "รหัสผ่านเข้าเซิฟเวอร์", "กรุณากรอกรหัสผ่านเข้าเซิฟเวอร์", "ตกลง", "ปิด");
			return true;
		}
		format(ServerData[ServerPassword], 64, inputtext);
        new name[32];
        format(name, sizeof(name), "password %s", ServerData[ServerPassword]);
        SendRconCommand(name);
		server_Save();
        format(string, sizeof(string), "ผู้ดูแล %s ได้ทำการเปลี่ยนรหัสผ่านเข้าเซิฟเวอร์เป็น %s", ReturnRoleplayName(playerid), ServerData[ServerPassword]);
        SendAdminsMessage(1, COLOR_YELLOW, string);
    }
    return 1;
}

Dialog:EditExp(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        new string[128];
        new amount = strval(inputtext);
        if(amount <= 0) return ErrorMsg(playerid, "Exp ไม่ถูกต้อง");
        ServerData[ServerExp] = amount;
        format(string, sizeof(string), "ผู้ดูแล %s ได้ทำการปรับ EXP เป็น x %s เรียบร้อยแล้ว", ReturnRoleplayName(playerid), FormatNumberNotMoney(ServerData[ServerExp]));
        SendAdminsMessage(1, COLOR_YELLOW, string);
        SendClientMessageToAllEx(COLOR_ORANGE, "[ค่าประสบการณ์]: ขณะนี้ค่าประสบการณ์ EXP คูณ %s", FormatNumberNotMoney(ServerData[ServerExp]));
        server_Save();
    }
    return 1;
}

Dialog:EditTax(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        new string[128];
        new amount = strval(inputtext);
        if(amount <= 0) return ErrorMsg(playerid, "ภาษี ไม่ถูกต้อง");
        ServerData[ServerTax] = amount;
        format(string, sizeof(string), "ผู้ดูแล %s ได้ทำการปรับ ภาษีรายชั่วโมง เป็น %s เรียบร้อยแล้ว", ReturnRoleplayName(playerid), FormatNumber(ServerData[ServerTax]));
        SendAdminsMessage(1, COLOR_YELLOW, string);
        SendClientMessageToAllEx(COLOR_ORANGE, "[ค่าประสบการณ์]: ขณะนี้ภาษีรายชั่วโมงคือ %s", FormatNumber(ServerData[ServerTax]));
        server_Save();
    }
    return 1;
}