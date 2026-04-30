#if defined _inc_impl
	#undef _inc_impl
#endif


//ประตูด่านหน้า 2471.63 2390.82 -52.0894
//ประตูด่านหน้าเลื่อน 2471.63 2390.82 -54.9493
//model 9823


CMD:openval(playerid){
	if(!IsPlayerConnected(playerid)) return SendClientMessage(playerid, COLOR_GREY, "คุณต้องเข้าสู่ระบบก่อนที่จะใช้คำสั่งต่าง ๆ");
    if(PlayerData[playerid][pAdmin] < 1338) return ErrorMsg(playerid, "คุณไม่ได้รับอนุญาติ");
	if(!IsPlayerInRangeOfPoint(playerid, 3, 2472.0635,2371.3918,-51.9697)) return SendClientMessage(playerid, COLOR_GREY, "คุณไม่ได้อยู่ตรงประตูนิรภัย");
    MoveDynamicObject(BankVault, 2470.96,2371.59,-51.45, 5, 0.0000000,0.0000000,109.4000000);
	return 1;
}

CMD:closeval(playerid){
	if(!IsPlayerConnected(playerid)) return SendClientMessage(playerid, COLOR_GREY, "คุณต้องเข้าสู่ระบบก่อนที่จะใช้คำสั่งต่าง ๆ");
    if(PlayerData[playerid][pAdmin] < 1338) return ErrorMsg(playerid, "คุณไม่ได้รับอนุญาติ");
    if(!IsPlayerInRangeOfPoint(playerid, 3, 2472.0635,2371.3918,-51.9697)) return SendClientMessage(playerid, COLOR_GREY, "คุณไม่ได้อยู่ตรงประตูนิรภัย");
    MoveDynamicObject(BankVault, 2472.1,2370.5,-51.422, 5, 0.0000000,0.0000000,0.0000000);
	return 1;
}