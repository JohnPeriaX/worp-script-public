#if defined _inc_impl
	#undef _inc_impl
#endif

ResetClothJob(playerid){
    GetBoxCloth[playerid] = false;
    EnterCheckPointClothJob[playerid] = false;
    UseCheckpointDeliver[playerid] = false;
    ClothJobStartDeliver[playerid] = false;
    GetStartJobCloth[playerid] = false;
    return 1;
}

ViewClothShop(playerid)
{
	new string[2048], menu[20], count;

	format(string, sizeof(string), "%s{B4B5B7}หน้า 1\n", string);

	SetPVarInt(playerid, "pageclothshop", 1);

	for(new i=0; i<MAX_ENTRANCES; i++)
	{
	    if(EntranceData[i][entranceExists] && EntranceData[i][entranceType] == 3)
	    {
            if(count == 20)
            {
                format(string, sizeof(string), "%s{B4B5B7}หน้า 2\n", string);
                break;
            }
            format(menu, 20, "menuclothshop%d", ++count);
            SetPVarInt(playerid, menu, i);
            format(string, sizeof(string), "%s[%d]\t%s  [สินค้าคงเหลือในคลัง: %d/%d]\n", string, i+1, EntranceData[i][entranceName], EntranceData[i][entranceProducts], MAX_PRODUCTS);
		}
	}
	if(!count) Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "ร้านเสื้อผ้า", "ไม่พบร้านเสื้อผ้า..", "ปิด", "");
	else Dialog_ShowEasy(playerid, SendPlayerToClothShop, DIALOG_STYLE_LIST, "ร้านเสื้อผ้า", string, "เลือก", "ปิด");
	return 1;
}

SetPlayerToClothShop(playerid){
    new doorid = GetPVarInt(playerid, "clothshopID");
    UseCheckpointDeliver[playerid] = true;
    SetPlayerCheckpoint(playerid, EntranceData[doorid][entrancePos][0], EntranceData[doorid][entrancePos][1], EntranceData[doorid][entrancePos][2], 3.0);
    SendClientMessageEx(playerid, -1,"คุณได้เปิด GPS ไปยัง ร้านเสื้อผ้า %s", EntranceData[doorid][entranceName]);
    return 1;
}

Dialog:SendPlayerToClothShop(playerid, response, listitem, inputtext[])
{
	if(response) {

		new menu[20];
		//Navigate
		if(listitem != 0 && listitem != 21) {
			new str_biz[20];
			format(str_biz, 20, "menuclothshop%d", listitem);

			SetPVarInt(playerid, "clothshopID", GetPVarInt(playerid, str_biz));
			SetPlayerToClothShop(playerid);
			return 1;
		}

		new currentPage = GetPVarInt(playerid, "pageclothshop");
		if(listitem==0) {
			if(currentPage>1) currentPage--;
		}
		else if(listitem == 21) currentPage++;

		new string[2048], count;
		format(string, sizeof(string), "%s{B4B5B7}หน้า %d\n", string, (currentPage==1) ? 1 : currentPage-1);

		SetPVarInt(playerid, "pageclothshop", currentPage);

		new skipitem = (currentPage-1) * 20;

		for(new i=0; i<MAX_ENTRANCES; i++)
        {
            if(EntranceData[i][entranceExists] && EntranceData[i][entranceType] == 3)
            {
                if(skipitem)
                {
                    skipitem--;
                    continue;
                }
                if(count == 20)
                {
                    format(string, sizeof(string), "%s{B4B5B7}หน้า 2\n", string);
                    break;
                }
                format(menu, 20, "menuclothshop%d", ++count);
                SetPVarInt(playerid, menu, i);
                format(string, sizeof(string), "%s[%d]\t%s  [สินค้าคงเหลือในคลัง: %s]\n", string, i+1, EntranceData[i][entranceName], FormatNumberNotMoney(EntranceData[i][entranceProducts]));
			}
		}

		Dialog_ShowEasy(playerid, SendPlayerToClothShop, DIALOG_STYLE_LIST, "ร้านเสื้อผ้า", string, "เลือก", "ปิด");
	}
	return 1;
}

PlayerGetBoxCloth(playerid){
    if(PlayerData[playerid][pJob] == CLOTHJOB){
        GetBoxCloth[playerid] = true;
        SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
        SetPlayerAttachedObject(playerid,7,2654,6,-0.015999,0.096999,-0.232000,-109.999992,-29.799995,-10.899980,0.786999,0.616999,0.883000);
        SendClientMessage(playerid, COLOR_YELLOW, "[คำแนะนำ]: กด 'ต่อย' หลังรถเพื่อนำกล่องใส่ และ กด 'N' เพื่อทิ้งกล่อง");
    }
    return 1;
}