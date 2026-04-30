#if defined _inc_impl
	#undef _inc_impl
#endif

CMD:animcmds(playerid, params[])
{
	if(!LoggedIn[playerid]) return 0;
	SendClientMessage(playerid, COLOR_CLIENT, "ANIMATION:{FFFFFF} /handsup, /bat, /slap, /bar, /wash, /lay, /workout, /blowjob, /bomb.");
	SendClientMessage(playerid, COLOR_CLIENT, "ANIMATION:{FFFFFF} /carry, /crack, /sleep, /jump, /deal, /dancing, /eating, /puke, /gsign, /chat.");
	SendClientMessage(playerid, COLOR_CLIENT, "ANIMATION:{FFFFFF} /goggles, /spray, /throw, /swipe, /office, /kiss, /knife, /scratch, /point.");
	SendClientMessage(playerid, COLOR_CLIENT, "ANIMATION:{FFFFFF} /cheer, /wave, /strip, /smoke, /reload, /taichi, /wank, /cower, /drunk.");
	SendClientMessage(playerid, COLOR_CLIENT, "ANIMATION:{FFFFFF} /cry, /tired, /sit, /crossarms, /fucku, /walk, /piss, /stopanim.");
	return 1;
}

ShowMenuAnimation(playerid){
	if(PlayerEnterWarFlag[playerid]) return ErrorMsg(playerid, "อย่าหาทำข้อร้อง");

	new string[1024];
	format(string, sizeof(string), "\nยกมือขึ้น\nล้างมือ\nก้มเก็บ\nทำความเคารพ\nกระโดดหลบ\nฉี่\nโยนทิ้ง\nรูดบัตร\nก้มหมอบ\nเมา\nร้องไห้\nให้ fucku\nหยุดท่าทาง");
	Dialog_ShowEasy(playerid, AnimationList, DIALOG_STYLE_LIST, "ท่าทางต่างๆ", string, "เลือก", "ยกเลิก");
	return 1;
}

Dialog:AnimationList(playerid, response, listitem, inputtext[]){
	if(!response) return 1;
	if(response){

		if(listitem == 0){
			ClearAnimations(playerid);
			callcmd::handsup(playerid, "\1");
		}
		if(listitem == 1){
			ClearAnimations(playerid);
			callcmd::wash(playerid, "\1");
		}
		if(listitem == 2){
			ClearAnimations(playerid);
			callcmd::bomb(playerid, "\1");
		}
		if(listitem == 3){
			ClearAnimations(playerid);
			callcmd::salute(playerid, "\1");
		}
		if(listitem == 4){
			ClearAnimations(playerid);
			callcmd::jump(playerid, "\1");
		}
		if(listitem == 5){
			ClearAnimations(playerid);
			callcmd::piss(playerid, "\1");
		}
		if(listitem == 6){
			ClearAnimations(playerid);
			callcmd::throw(playerid, "\1");
		}
		if(listitem == 7){
			ClearAnimations(playerid);
			callcmd::swipe(playerid, "\1");
		}
		if(listitem == 8){
			ClearAnimations(playerid);
			callcmd::cower(playerid, "\1");
		}
		if(listitem == 9){
			ClearAnimations(playerid);
			callcmd::drunk(playerid, "\1");
		}
		if(listitem == 10){
			ClearAnimations(playerid);
			callcmd::cry(playerid, "\1");
		}
		if(listitem == 11){
			ClearAnimations(playerid);
			callcmd::fucku(playerid, "\1");
		}
		if(listitem == 12){
			ClearAnimations(playerid);
			PlayerData[playerid][pLoopAnim] = 0;
		}
	}
	return 1;
}

/*CMD:dance(playerid, params[])
{
	new type;

	if (!AnimationCheck(playerid))
	    return ErrorMsg(playerid, "คุณไม่สามารถใช้อนิเมชั่นได้ในขณะนี้");

	if (sscanf(params, "d", type))
	    return SystemMsg(playerid, "/dance [1-4]");

	if (type < 1 || type > 4)
	    return ErrorMsg(playerid, "ระบุรูปแบบไม่ถูกต้อง");

	switch (type) {
		case 1: SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DANCE1);
	    case 2: SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DANCE2);
	    case 3: SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DANCE3);
	    case 4: SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DANCE4);
	}
	return 1;
}*/

CMD:handsup(playerid, const params[])
{
	if(!LoggedIn[playerid]) return 0;

	if(PlayerEnterWarFlag[playerid]) return ErrorMsg(playerid, "อย่าหาทำข้อร้อง");

    if (!AnimationCheck(playerid))
	    return ErrorMsg(playerid, "คุณไม่สามารถใช้อนิเมชั่นได้ในขณะนี้");

	if (PlayerData[playerid][pInjured])
        return ErrorMsg(playerid, "คุณไม่สามารถใช้คำสั่งได้ในขณะนี้");

	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_HANDSUP);
	return 1;
}

CMD:stopanim(playerid, const params[])
{
	if(!LoggedIn[playerid]) return 0;
	if (!AnimationCheck(playerid))
	    return ErrorMsg(playerid, "คุณไม่จำเป็นต้องใช้คำสั่งนี้ในขณะนี้");

    if (PlayerData[playerid][pInjured])
        return ErrorMsg(playerid, "คุณไม่สามารถใช้คำสั่งได้ในขณะนี้");

	ClearAnimations(playerid, 1);
	if(StartSleep[playerid] == 1){
		StartSleep[playerid] = 0;
		TimeSleepPoint[playerid] = 0;
	}
	PlayerData[playerid][pLoopAnim] = 0;
	return 1;
}

CMD:weaponanim(playerid, params[]){
	if(!LoggedIn[playerid]) return 0;

	if(PlayerEnterWarFlag[playerid]) return ErrorMsg(playerid, "อย่าหาทำข้อร้อง");

	ApplyAnimation(playerid, "rifle", "rifle_fire_poor", 4.1, 1, 0, 0, 0, 0, 1);
	return 1;
}

CMD:bat(playerid, params[])
{
	if(!LoggedIn[playerid]) return 0;
    new type;

	if(PlayerEnterWarFlag[playerid]) return ErrorMsg(playerid, "อย่าหาทำข้อร้อง");

	if (!AnimationCheck(playerid))
	    return ErrorMsg(playerid, "คุณไม่สามารถใช้อนิเมชั่นได้ในขณะนี้");

	if (sscanf(params, "d", type))
	    return SystemMsg(playerid, "/bat [1-5]");

	if (type < 1 || type > 5)
	    return ErrorMsg(playerid, "ระบุรูปแบบไม่ถูกต้อง");

	switch (type) {
	    case 1: ApplyAnimation(playerid, "BASEBALL", "Bat_1", 4.1, 0, 1, 1, 0, 0, 1);
	    case 2: ApplyAnimation(playerid, "BASEBALL", "Bat_2", 4.1, 0, 1, 1, 0, 0, 1);
	    case 3: ApplyAnimation(playerid, "BASEBALL", "Bat_3", 4.1, 0, 1, 1, 0, 0, 1);
	    case 4: ApplyAnimation(playerid, "BASEBALL", "Bat_4", 4.1, 0, 0, 0, 0, 0, 1);
	    case 5: ApplyAnimationEx(playerid, "BASEBALL", "Bat_IDLE", 4.1, 1, 0, 0, 0, 0, 1);
	}
	PlayerData[playerid][pLoopAnim] = 1;
	return 1;
}

CMD:slap(playerid, params[])
{
	if(!LoggedIn[playerid]) return 0;
	if(PlayerEnterWarFlag[playerid]) return ErrorMsg(playerid, "อย่าหาทำข้อร้อง");
    if (!AnimationCheck(playerid))
	    return ErrorMsg(playerid, "คุณไม่สามารถใช้อนิเมชั่นได้ในขณะนี้");

	ApplyAnimation(playerid, "BASEBALL", "Bat_M", 4.1, 0, 0, 0, 0, 0, 1);
	PlayerData[playerid][pLoopAnim] = 1;
	return 1;
}

CMD:bar(playerid, params[])
{
    new type;

	if(!LoggedIn[playerid]) return 0;
	if(PlayerEnterWarFlag[playerid]) return ErrorMsg(playerid, "อย่าหาทำข้อร้อง");
	if (!AnimationCheck(playerid))
	    return ErrorMsg(playerid, "คุณไม่สามารถใช้อนิเมชั่นได้ในขณะนี้");

	if (sscanf(params, "d", type))
	    return SystemMsg(playerid, "/bar [1-8]");

	if (type < 1 || type > 8)
	    return ErrorMsg(playerid, "ระบุรูปแบบไม่ถูกต้อง");

	switch (type) {
	    case 1: ApplyAnimation(playerid, "BAR", "Barserve_bottle", 4.1, 0, 0, 0, 0, 0, 1);
	    case 2: ApplyAnimation(playerid, "BAR", "Barserve_give", 4.1, 0, 0, 0, 0, 0, 1);
	    case 3: ApplyAnimation(playerid, "BAR", "Barserve_glass", 4.1, 0, 0, 0, 0, 0, 1);
	    case 4: ApplyAnimation(playerid, "BAR", "Barserve_in", 4.1, 0, 0, 0, 0, 0, 1);
	    case 5: ApplyAnimation(playerid, "BAR", "Barserve_order", 4.1, 0, 0, 0, 0, 0, 1);
	    case 6: ApplyAnimationEx(playerid, "BAR", "BARman_idle", 4.1, 1, 0, 0, 0, 0, 1);
	    case 7: ApplyAnimationEx(playerid, "BAR", "dnk_stndM_loop", 4.1, 0, 0, 0, 0, 0, 1);
	    case 8: ApplyAnimationEx(playerid, "BAR", "dnk_stndF_loop", 4.1, 0, 0, 0, 0, 0, 1);
	}
	PlayerData[playerid][pLoopAnim] = 1;
	return 1;
}

CMD:wash(playerid, const params[])
{
	if(!LoggedIn[playerid]) return 0;
	if(PlayerEnterWarFlag[playerid]) return ErrorMsg(playerid, "อย่าหาทำข้อร้อง");
    if (!AnimationCheck(playerid))
	    return ErrorMsg(playerid, "คุณไม่สามารถใช้อนิเมชั่นได้ในขณะนี้");

	ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 0, 1);
	PlayerData[playerid][pLoopAnim] = 1;
	return 1;
}

CMD:lay(playerid, params[])
{
	if(!LoggedIn[playerid]) return 0;
	if(PlayerEnterWarFlag[playerid]) return ErrorMsg(playerid, "อย่าหาทำข้อร้อง");
    new type;

	if (!AnimationCheck(playerid))
	    return ErrorMsg(playerid, "คุณไม่สามารถใช้อนิเมชั่นได้ในขณะนี้");

	if (sscanf(params, "d", type))
	    return SystemMsg(playerid, "/lay [1-5]");

	if (type < 1 || type > 5)
	    return ErrorMsg(playerid, "ระบุรูปแบบไม่ถูกต้อง");

	switch (type) {
	    case 1: ApplyAnimationEx(playerid, "BEACH", "bather", 4.1, 1, 0, 0, 0, 0, 1);
	    case 2: ApplyAnimationEx(playerid, "BEACH", "Lay_Bac_Loop", 4.1, 1, 0, 0, 0, 0, 1);
	    case 3: ApplyAnimationEx(playerid, "BEACH", "ParkSit_M_loop", 4.1, 1, 0, 0, 0, 0, 1);
	    case 4: ApplyAnimationEx(playerid, "BEACH", "ParkSit_W_loop", 4.1, 1, 0, 0, 0, 0, 1);
	    case 5: ApplyAnimationEx(playerid, "BEACH", "SitnWait_loop_W", 4.1, 1, 0, 0, 0, 0, 1);
	}
	PlayerData[playerid][pLoopAnim] = 1;
	return 1;
}



CMD:workout(playerid, params[])
{
	if(!LoggedIn[playerid]) return 0;
	if(PlayerEnterWarFlag[playerid]) return ErrorMsg(playerid, "อย่าหาทำข้อร้อง");
    new type;

	if (!AnimationCheck(playerid))
	    return ErrorMsg(playerid, "คุณไม่สามารถใช้อนิเมชั่นได้ในขณะนี้");

	if (sscanf(params, "d", type))
	    return SystemMsg(playerid, "/workout [1-7]");

	if (type < 1 || type > 7)
	    return ErrorMsg(playerid, "ระบุรูปแบบไม่ถูกต้อง");

	switch (type) {
	    case 1: ApplyAnimation(playerid, "benchpress", "gym_bp_celebrate", 4.1, 0, 0, 0, 0, 0, 1);
	    case 2: ApplyAnimationEx(playerid, "benchpress", "gym_bp_down", 4.1, 0, 0, 0, 1, 0, 1);
	    case 3: ApplyAnimation(playerid, "benchpress", "gym_bp_getoff", 4.1, 0, 0, 0, 0, 0, 1);
	    case 4: ApplyAnimationEx(playerid, "benchpress", "gym_bp_geton", 4.1, 0, 0, 0, 1, 0, 1);
	    case 5: ApplyAnimationEx(playerid, "benchpress", "gym_bp_up_A", 4.1, 0, 0, 0, 1, 0, 1);
	    case 6: ApplyAnimationEx(playerid, "benchpress", "gym_bp_up_B", 4.1, 0, 0, 0, 1, 0, 1);
	    case 7: ApplyAnimationEx(playerid, "benchpress", "gym_bp_up_smooth", 4.1, 0, 0, 0, 1, 0, 1);
	}
	PlayerData[playerid][pLoopAnim] = 1;
	return 1;
}

CMD:blowjob(playerid, params[])
{
	if(!LoggedIn[playerid]) return 0;
	if(PlayerEnterWarFlag[playerid]) return ErrorMsg(playerid, "อย่าหาทำข้อร้อง");
    new type;

	if (!AnimationCheck(playerid))
	    return ErrorMsg(playerid, "คุณไม่สามารถใช้อนิเมชั่นได้ในขณะนี้");

	if (sscanf(params, "d", type))
	    return SystemMsg(playerid, "/blowjob [1-4]");

	if (type < 1 || type > 4)
	    return ErrorMsg(playerid, "ระบุรูปแบบไม่ถูกต้อง");

	switch (type) {
	    case 1: ApplyAnimationEx(playerid, "BLOWJOBZ", "BJ_COUCH_LOOP_W", 4.1, 1, 0, 0, 0, 0, 1);
	    case 2: ApplyAnimationEx(playerid, "BLOWJOBZ", "BJ_COUCH_LOOP_P", 4.1, 1, 0, 0, 0, 0, 1);
	    case 3: ApplyAnimationEx(playerid, "BLOWJOBZ", "BJ_STAND_LOOP_W", 4.1, 1, 0, 0, 0, 0, 1);
	    case 4: ApplyAnimationEx(playerid, "BLOWJOBZ", "BJ_STAND_LOOP_P", 4.1, 1, 0, 0, 0, 0, 1);
	}
	PlayerData[playerid][pLoopAnim] = 1;
	return 1;
}

CMD:bomb(playerid, const params[])
{
	if(!LoggedIn[playerid]) return 0;
	if(PlayerEnterWarFlag[playerid]) return ErrorMsg(playerid, "อย่าหาทำข้อร้อง");
    if (!AnimationCheck(playerid))
	    return ErrorMsg(playerid, "คุณไม่สามารถใช้อนิเมชั่นได้ในขณะนี้");

	ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.1, 0, 0, 0, 0, 0, 1);
	PlayerData[playerid][pLoopAnim] = 1;
	return 1;
}

CMD:carry(playerid, params[])
{
	if(!LoggedIn[playerid]) return 0;
	if(PlayerEnterWarFlag[playerid]) return ErrorMsg(playerid, "อย่าหาทำข้อร้อง");
    new type;

	if (!AnimationCheck(playerid))
	    return ErrorMsg(playerid, "คุณไม่สามารถใช้อนิเมชั่นได้ในขณะนี้");

	if (sscanf(params, "d", type))
	    return SystemMsg(playerid, "/carry [1-6]");

	if (type < 1 || type > 6)
	    return ErrorMsg(playerid, "ระบุรูปแบบไม่ถูกต้อง");

	switch (type) {
	    case 1: ApplyAnimation(playerid, "CARRY", "liftup", 4.1, 0, 0, 0, 0, 0, 1);
	    case 2: ApplyAnimation(playerid, "CARRY", "liftup05", 4.1, 0, 0, 0, 0, 0, 1);
	    case 3: ApplyAnimation(playerid, "CARRY", "liftup105", 4.1, 0, 0, 0, 0, 0, 1);
	    case 4: ApplyAnimation(playerid, "CARRY", "putdwn", 4.1, 0, 0, 0, 0, 0, 1);
	    case 5: ApplyAnimation(playerid, "CARRY", "putdwn05", 4.1, 0, 0, 0, 0, 0, 1);
	    case 6: ApplyAnimation(playerid, "CARRY", "putdwn105", 4.1, 0, 0, 0, 0, 0, 1);
	}
	PlayerData[playerid][pLoopAnim] = 1;
	return 1;
}

CMD:crack(playerid, params[])
{
	if(!LoggedIn[playerid]) return 0;
	if(PlayerEnterWarFlag[playerid]) return ErrorMsg(playerid, "อย่าหาทำข้อร้อง");
    new type;

	if (!AnimationCheck(playerid))
	    return ErrorMsg(playerid, "คุณไม่สามารถใช้อนิเมชั่นได้ในขณะนี้");

	if (sscanf(params, "d", type))
	    return SystemMsg(playerid, "/crack [1-6]");

	if (type < 1 || type > 6)
	    return ErrorMsg(playerid, "ระบุรูปแบบไม่ถูกต้อง");

	switch (type) {
	    case 1: ApplyAnimationEx(playerid, "CRACK", "crckdeth1", 4.1, 0, 0, 0, 1, 0, 1);
	    case 2: ApplyAnimationEx(playerid, "CRACK", "crckdeth2", 4.1, 1, 0, 0, 0, 0, 1);
	    case 3: ApplyAnimationEx(playerid, "CRACK", "crckdeth3", 4.1, 0, 0, 0, 1, 0, 1);
	    case 4: ApplyAnimationEx(playerid, "CRACK", "crckidle1", 4.1, 0, 0, 0, 1, 0, 1);
	    case 5: ApplyAnimationEx(playerid, "CRACK", "crckidle2", 4.1, 0, 0, 0, 1, 0, 1);
	    case 6: ApplyAnimationEx(playerid, "CRACK", "crckidle3", 4.1, 0, 0, 0, 1, 0, 1);
	}
	PlayerData[playerid][pLoopAnim] = 1;
	return 1;
}

CMD:salute(playerid, const params[])
{
	if(!LoggedIn[playerid]) return 0;
	if(PlayerEnterWarFlag[playerid]) return ErrorMsg(playerid, "อย่าหาทำข้อร้อง");
	if (!AnimationCheck(playerid))
	    return ErrorMsg(playerid, "คุณไม่สามารถใช้อนิเมชั่นได้ในขณะนี้");
	    
   	ApplyAnimationEx(playerid, "ON_LOOKERS", "Pointup_loop", 4.0, 1, 0, 0, 0, 0);
   	return 1;
}

CMD:lean(playerid, params[])
{
	if(!LoggedIn[playerid]) return 0;
	if(PlayerEnterWarFlag[playerid]) return ErrorMsg(playerid, "อย่าหาทำข้อร้อง");
    new type;

	if (!AnimationCheck(playerid))
	    return ErrorMsg(playerid, "คุณไม่สามารถใช้อนิเมชั่นได้ในขณะนี้");

	if(sscanf(params, "i", type)) return SendClientMessage(playerid, COLOR_WHITE, "[Usage]: /lean [1-2]");
	
	switch (type)
	{
		case 1: ApplyAnimationEx(playerid,"GANGS","leanIDLE",4.1,0,0,0,1,0);
		case 2: ApplyAnimationEx(playerid,"MISC","Plyrlean_loop",4.1,0,0,0,1,0);
	}
	PlayerData[playerid][pLoopAnim] = 1;
	return 1;
}

CMD:sleep(playerid, params[])
{
	if(!LoggedIn[playerid]) return 0;
	if(PlayerEnterWarFlag[playerid]) return ErrorMsg(playerid, "อย่าหาทำข้อร้อง");
    new type;

	if (!AnimationCheck(playerid))
	    return ErrorMsg(playerid, "คุณไม่สามารถใช้อนิเมชั่นได้ในขณะนี้");

	if (sscanf(params, "d", type))
	    return SystemMsg(playerid, "/sleep [1-2]");

	if (type < 1 || type > 2)
	    return ErrorMsg(playerid, "ระบุรูปแบบไม่ถูกต้อง");

	switch (type) {
	    case 1: ApplyAnimationEx(playerid, "CRACK", "crckdeth4", 4.1, 0, 0, 0, 1, 0, 1);
	    case 2: ApplyAnimationEx(playerid, "CRACK", "crckidle4", 4.1, 0, 0, 0, 1, 0, 1);
	}

	if(StartSleep[playerid] == 0){
		if(Home_Inside(playerid) != -1){
			StartSleep[playerid] = 1;
		}
	}
	

	PlayerData[playerid][pLoopAnim] = 1;
	return 1;
}

CMD:jump(playerid, const params[])
{
	if(!LoggedIn[playerid]) return 0;
	if(PlayerEnterWarFlag[playerid]) return ErrorMsg(playerid, "อย่าหาทำข้อร้อง");
    if (!AnimationCheck(playerid))
	    return ErrorMsg(playerid, "คุณไม่สามารถใช้อนิเมชั่นได้ในขณะนี้");

	ApplyAnimation(playerid, "DODGE", "Crush_Jump", 4.1, 0, 1, 1, 0, 0, 1);
	PlayerData[playerid][pLoopAnim] = 1;
	return 1;
}

CMD:deal(playerid, params[])
{
	if(!LoggedIn[playerid]) return 0;
	if(PlayerEnterWarFlag[playerid]) return ErrorMsg(playerid, "อย่าหาทำข้อร้อง");
    new type;

	if (!AnimationCheck(playerid))
	    return ErrorMsg(playerid, "คุณไม่สามารถใช้อนิเมชั่นได้ในขณะนี้");

	if (sscanf(params, "d", type))
	    return SystemMsg(playerid, "/deal [1-6]");

	if (type < 1 || type > 6)
	    return ErrorMsg(playerid, "ระบุรูปแบบไม่ถูกต้อง");

	switch (type) {
	    case 1: ApplyAnimation(playerid, "DEALER", "DEALER_DEAL", 4.1, 0, 0, 0, 0, 0, 1);
	    case 2: ApplyAnimation(playerid, "DEALER", "DRUGS_BUY", 4.1, 0, 0, 0, 0, 0, 1);
	    case 3: ApplyAnimation(playerid, "DEALER", "shop_pay", 4.1, 0, 0, 0, 0, 0, 1);
	    case 4: ApplyAnimationEx(playerid, "DEALER", "DEALER_IDLE_01", 4.1, 1, 0, 0, 0, 0, 1);
	    case 5: ApplyAnimationEx(playerid, "DEALER", "DEALER_IDLE_02", 4.1, 1, 0, 0, 0, 0, 1);
	    case 6: ApplyAnimationEx(playerid, "DEALER", "DEALER_IDLE_03", 4.1, 1, 0, 0, 0, 0, 1);
	}
	PlayerData[playerid][pLoopAnim] = 1;
	return 1;
}

CMD:dancing(playerid, params[])
{
	if(!LoggedIn[playerid]) return 0;
	if(PlayerEnterWarFlag[playerid]) return ErrorMsg(playerid, "อย่าหาทำข้อร้อง");
    new type;

	if (!AnimationCheck(playerid))
	    return ErrorMsg(playerid, "คุณไม่สามารถใช้อนิเมชั่นได้ในขณะนี้");

	if (sscanf(params, "d", type))
	    return SystemMsg(playerid, "/dancing [1-10]");

	if (type < 1 || type > 10)
	    return ErrorMsg(playerid, "ระบุรูปแบบไม่ถูกต้อง");

	switch (type) {
	    case 1: ApplyAnimationEx(playerid, "DANCING", "dance_loop", 4.1, 1, 0, 0, 0, 0, 1);
	    case 2: ApplyAnimationEx(playerid, "DANCING", "DAN_Left_A", 4.1, 1, 0, 0, 0, 0, 1);
	    case 3: ApplyAnimationEx(playerid, "DANCING", "DAN_Right_A", 4.1, 1, 0, 0, 0, 0, 1);
	    case 4: ApplyAnimationEx(playerid, "DANCING", "DAN_Loop_A", 4.1, 1, 0, 0, 0, 0, 1);
	    case 5: ApplyAnimationEx(playerid, "DANCING", "DAN_Up_A", 4.1, 1, 0, 0, 0, 0, 1);
	    case 6: ApplyAnimationEx(playerid, "DANCING", "DAN_Down_A", 4.1, 1, 0, 0, 0, 0, 1);
	    case 7: ApplyAnimationEx(playerid, "DANCING", "dnce_M_a", 4.1, 1, 0, 0, 0, 0, 1);
	    case 8: ApplyAnimationEx(playerid, "DANCING", "dnce_M_e", 4.1, 1, 0, 0, 0, 0, 1);
	    case 9: ApplyAnimationEx(playerid, "DANCING", "dnce_M_b", 4.1, 1, 0, 0, 0, 0, 1);
	    case 10: ApplyAnimationEx(playerid, "DANCING", "dnce_M_c", 4.1, 1, 0, 0, 0, 0, 1);
	}
	PlayerData[playerid][pLoopAnim] = 1;
	return 1;
}

CMD:eating(playerid, params[])
{
	if(!LoggedIn[playerid]) return 0;
	if(PlayerEnterWarFlag[playerid]) return ErrorMsg(playerid, "อย่าหาทำข้อร้อง");
    new type;

	if (!AnimationCheck(playerid))
	    return ErrorMsg(playerid, "คุณไม่สามารถใช้อนิเมชั่นได้ในขณะนี้");

	if (sscanf(params, "d", type))
	    return SystemMsg(playerid, "/eating [1-3]");

	if (type < 1 || type > 3)
	    return ErrorMsg(playerid, "ระบุรูปแบบไม่ถูกต้อง");

	switch (type) {
	    case 1: ApplyAnimation(playerid, "FOOD", "EAT_Burger", 4.1, 0, 0, 0, 0, 0, 1);
	    case 2: ApplyAnimation(playerid, "FOOD", "EAT_Chicken", 4.1, 0, 0, 0, 0, 0, 1);
	    case 3: ApplyAnimation(playerid, "FOOD", "EAT_Pizza", 4.1, 0, 0, 0, 0, 0, 1);
	}
	PlayerData[playerid][pLoopAnim] = 1;
	return 1;
}

CMD:piss(playerid, const params[])
{
    if (!AnimationCheck(playerid))
	    return ErrorMsg(playerid, "คุณไม่สามารถใช้อนิเมชั่นได้ในขณะนี้");

	if(PlayerEnterWarFlag[playerid]) return ErrorMsg(playerid, "อย่าหาทำข้อร้อง");

	SetPlayerSpecialAction(playerid, 68);
	return 1;
}

CMD:puke(playerid, params[])
{
	if(!LoggedIn[playerid]) return 0;
	if(PlayerEnterWarFlag[playerid]) return ErrorMsg(playerid, "อย่าหาทำข้อร้อง");
    if (!AnimationCheck(playerid))
	    return ErrorMsg(playerid, "คุณไม่สามารถใช้อนิเมชั่นได้ในขณะนี้");

	ApplyAnimation(playerid, "FOOD", "EAT_Vomit_P", 4.1, 0, 0, 0, 0, 0, 1);
	PlayerData[playerid][pLoopAnim] = 1;
	return 1;
}

CMD:gsign(playerid, params[])
{
	if(!LoggedIn[playerid]) return 0;
	if(PlayerEnterWarFlag[playerid]) return ErrorMsg(playerid, "อย่าหาทำข้อร้อง");
    new type;

	if (!AnimationCheck(playerid))
	    return ErrorMsg(playerid, "คุณไม่สามารถใช้อนิเมชั่นได้ในขณะนี้");

	if (sscanf(params, "d", type))
	    return SystemMsg(playerid, "/gsign [1-15]");

	if (type < 1 || type > 15)
	    return ErrorMsg(playerid, "ระบุรูปแบบไม่ถูกต้อง");

	switch (type) {
		case 1: ApplyAnimation(playerid, "GHANDS", "gsign1", 4.1, 0, 0, 0, 0, 0, 1);
		case 2: ApplyAnimation(playerid, "GHANDS", "gsign1LH", 4.1, 0, 0, 0, 0, 0, 1);
		case 3: ApplyAnimation(playerid, "GHANDS", "gsign2", 4.1, 0, 0, 0, 0, 0, 1);
		case 4: ApplyAnimation(playerid, "GHANDS", "gsign2LH", 4.1, 0, 0, 0, 0, 0, 1);
		case 5: ApplyAnimation(playerid, "GHANDS", "gsign3", 4.1, 0, 0, 0, 0, 0, 1);
		case 6: ApplyAnimation(playerid, "GHANDS", "gsign3LH", 4.1, 0, 0, 0, 0, 0, 1);
		case 7: ApplyAnimation(playerid, "GHANDS", "gsign4", 4.1, 0, 0, 0, 0, 0, 1);
		case 8: ApplyAnimation(playerid, "GHANDS", "gsign4LH", 4.1, 0, 0, 0, 0, 0, 1);
		case 9: ApplyAnimation(playerid, "GHANDS", "gsign5", 4.1, 0, 0, 0, 0, 0, 1);
		case 10: ApplyAnimation(playerid, "GHANDS", "gsign5", 4.1, 0, 0, 0, 0, 0, 1);
		case 11: ApplyAnimation(playerid, "GHANDS", "gsign5LH", 4.1, 0, 0, 0, 0, 0, 1);
		case 12: ApplyAnimation(playerid, "GANGS", "Invite_No", 4.1, 0, 0, 0, 0, 0, 1);
		case 13: ApplyAnimation(playerid, "GANGS", "Invite_Yes", 4.1, 0, 0, 0, 0, 0, 1);
		case 14: ApplyAnimation(playerid, "GANGS", "prtial_gngtlkD", 4.1, 0, 0, 0, 0, 0, 1);
		case 15: ApplyAnimation(playerid, "GANGS", "smkcig_prtl", 4.1, 0, 0, 0, 0, 0, 1);
	}
	PlayerData[playerid][pLoopAnim] = 1;
	return 1;
}

CMD:chat(playerid, params[])
{
	if(!LoggedIn[playerid]) return 0;
	if(PlayerEnterWarFlag[playerid]) return ErrorMsg(playerid, "อย่าหาทำข้อร้อง");
    new type;

	if (!AnimationCheck(playerid))
	    return ErrorMsg(playerid, "คุณไม่สามารถใช้อนิเมชั่นได้ในขณะนี้");

	if (sscanf(params, "d", type))
	    return SystemMsg(playerid, "/chat [1-6]");

	if (type < 1 || type > 6)
	    return ErrorMsg(playerid, "ระบุรูปแบบไม่ถูกต้อง");

	switch (type) {
		case 1: ApplyAnimation(playerid, "GANGS", "prtial_gngtlkA", 4.1, 0, 0, 0, 0, 0, 1);
		case 2: ApplyAnimation(playerid, "GANGS", "prtial_gngtlkB", 4.1, 0, 0, 0, 0, 0, 1);
		case 3: ApplyAnimation(playerid, "GANGS", "prtial_gngtlkE", 4.1, 0, 0, 0, 0, 0, 1);
		case 4: ApplyAnimation(playerid, "GANGS", "prtial_gngtlkF", 4.1, 0, 0, 0, 0, 0, 1);
		case 5: ApplyAnimation(playerid, "GANGS", "prtial_gngtlkG", 4.1, 0, 0, 0, 0, 0, 1);
		case 6: ApplyAnimation(playerid, "GANGS", "prtial_gngtlkH", 4.1, 0, 0, 0, 0, 0, 1);
	}
	PlayerData[playerid][pLoopAnim] = 1;
	return 1;
}

CMD:goggles(playerid, params[])
{
	if(!LoggedIn[playerid]) return 0;
	if(PlayerEnterWarFlag[playerid]) return ErrorMsg(playerid, "อย่าหาทำข้อร้อง");
    if (!AnimationCheck(playerid))
	    return ErrorMsg(playerid, "คุณไม่สามารถใช้อนิเมชั่นได้ในขณะนี้");

	ApplyAnimation(playerid, "goggles", "goggles_put_on", 4.1, 0, 0, 0, 0, 0, 1);
	PlayerData[playerid][pLoopAnim] = 1;
	return 1;
}

CMD:spray(playerid, params[])
{
	if(!LoggedIn[playerid]) return 0;
	if(PlayerEnterWarFlag[playerid]) return ErrorMsg(playerid, "อย่าหาทำข้อร้อง");
    if (!AnimationCheck(playerid))
	    return ErrorMsg(playerid, "คุณไม่สามารถใช้อนิเมชั่นได้ในขณะนี้");

 	ApplyAnimationEx(playerid, "GRAFFITI", "spraycan_fire", 4.1, 1, 0, 0, 0, 0, 1);
	PlayerData[playerid][pLoopAnim] = 1;
	return 1;
}

CMD:throw(playerid, const params[])
{
	if(!LoggedIn[playerid]) return 0;
	if(PlayerEnterWarFlag[playerid]) return ErrorMsg(playerid, "อย่าหาทำข้อร้อง");
    if (!AnimationCheck(playerid))
	    return ErrorMsg(playerid, "คุณไม่สามารถใช้อนิเมชั่นได้ในขณะนี้");

	ApplyAnimation(playerid, "GRENADE", "WEAPON_throw", 4.1, 0, 0, 0, 0, 0, 1);
	PlayerData[playerid][pLoopAnim] = 1;
	return 1;
}

CMD:swipe(playerid, const params[])
{
	if(!LoggedIn[playerid]) return 0;
	if(PlayerEnterWarFlag[playerid]) return ErrorMsg(playerid, "อย่าหาทำข้อร้อง");
    if (!AnimationCheck(playerid))
	    return ErrorMsg(playerid, "คุณไม่สามารถใช้อนิเมชั่นได้ในขณะนี้");

	ApplyAnimation(playerid, "HEIST9", "Use_SwipeCard", 4.1, 0, 0, 0, 0, 0, 1);
	PlayerData[playerid][pLoopAnim] = 1;
	return 1;
}

CMD:office(playerid, params[])
{
	if(!LoggedIn[playerid]) return 0;
	if(PlayerEnterWarFlag[playerid]) return ErrorMsg(playerid, "อย่าหาทำข้อร้อง");
    new type;

	if (!AnimationCheck(playerid))
	    return ErrorMsg(playerid, "คุณไม่สามารถใช้อนิเมชั่นได้ในขณะนี้");

	if (sscanf(params, "d", type))
	    return SystemMsg(playerid, "/office [1-6]");

	if (type < 1 || type > 6)
	    return ErrorMsg(playerid, "ระบุรูปแบบไม่ถูกต้อง");

	switch (type) {
		case 1: ApplyAnimationEx(playerid, "INT_OFFICE", "OFF_Sit_Bored_Loop", 4.1, 1, 0, 0, 0, 0, 1);
		case 2: ApplyAnimationEx(playerid, "INT_OFFICE", "OFF_Sit_Crash", 4.1, 1, 0, 0, 0, 0, 1);
		case 3: ApplyAnimationEx(playerid, "INT_OFFICE", "OFF_Sit_Drink", 4.1, 1, 0, 0, 0, 0, 1);
		case 4: ApplyAnimationEx(playerid, "INT_OFFICE", "OFF_Sit_Read", 4.1, 1, 0, 0, 0, 0, 1);
		case 5: ApplyAnimationEx(playerid, "INT_OFFICE", "OFF_Sit_Type_Loop", 4.1, 1, 0, 0, 0, 0, 1);
		case 6: ApplyAnimationEx(playerid, "INT_OFFICE", "OFF_Sit_Watch", 4.1, 1, 0, 0, 0, 0, 1);
	}
	PlayerData[playerid][pLoopAnim] = 1;
	return 1;
}

CMD:kiss(playerid, params[])
{
	if(!LoggedIn[playerid]) return 0;
	if(PlayerEnterWarFlag[playerid]) return ErrorMsg(playerid, "อย่าหาทำข้อร้อง");
    new type;

	if (!AnimationCheck(playerid))
	    return ErrorMsg(playerid, "คุณไม่สามารถใช้อนิเมชั่นได้ในขณะนี้");

	if (sscanf(params, "d", type))
	    return SystemMsg(playerid, "/kiss [1-6]");

	if (type < 1 || type > 6)
	    return ErrorMsg(playerid, "ระบุรูปแบบไม่ถูกต้อง");

	switch (type) {
		case 1: ApplyAnimation(playerid, "KISSING", "Grlfrd_Kiss_01", 4.1, 0, 0, 0, 0, 0, 1);
		case 2: {
			ApplyAnimation(playerid, "KISSING", "Grlfrd_Kiss_02", 4.1, 0, 0, 0, 0, 0, 1);
			foreach(new i : Player){
				if(!LoggedIn[i]) continue;
				if(i == playerid) continue;
				if(IsPlayerNearPlayer(playerid, i, 3.0)){
					if(PlayerData[playerid][pMarrySQLID] == PlayerData[i][pID]){
						if(PlayerData[playerid][pMarryKissed] == 0 && PlayerData[i][pMarryKissed] == 0){
							if(PlayerData[playerid][pMarryLevel] < 100 && PlayerData[i][pMarryLevel] < 100){
								PlayerData[playerid][pMarryLevel] += 1;
								PlayerData[i][pMarryLevel] += 1;
								PlayerData[playerid][pMarryKissed] = 1;
								PlayerData[i][pMarryKissed] = 1;
								PlayerData[playerid][pMarryGetGift] = 0;
								PlayerData[i][pMarryGetGift] = 0;
								SendClientMessage(playerid, COLOR_YELLOW, "แต้มเลเวลคู่รักของคุณ +1");
								SendClientMessage(i, COLOR_YELLOW, "แต้มเลเวลคู่รักของคุณ +1");
							}
						}
					}
					break;
				}
			}
		}
		case 3: ApplyAnimation(playerid, "KISSING", "Grlfrd_Kiss_03", 4.1, 0, 0, 0, 0, 0, 1);
		case 4: ApplyAnimation(playerid, "KISSING", "Playa_Kiss_01", 4.1, 0, 0, 0, 0, 0, 1);
		case 5: ApplyAnimation(playerid, "KISSING", "Playa_Kiss_02", 4.1, 0, 0, 0, 0, 0, 1);
		case 6: ApplyAnimation(playerid, "KISSING", "Playa_Kiss_03", 4.1, 0, 0, 0, 0, 0, 1);
	}
	PlayerData[playerid][pLoopAnim] = 1;
	return 1;
}

CMD:knife(playerid, params[])
{
	if(!LoggedIn[playerid]) return 0;
	if(PlayerEnterWarFlag[playerid]) return ErrorMsg(playerid, "อย่าหาทำข้อร้อง");
    new type;

	if (!AnimationCheck(playerid))
	    return ErrorMsg(playerid, "คุณไม่สามารถใช้อนิเมชั่นได้ในขณะนี้");

	if (sscanf(params, "d", type))
	    return SystemMsg(playerid, "/knife [1-8]");

	if (type < 1 || type > 8)
	    return ErrorMsg(playerid, "ระบุรูปแบบไม่ถูกต้อง");

	switch (type) {
		case 1: ApplyAnimation(playerid, "KNIFE", "knife_1", 4.1, 0, 1, 1, 0, 0, 1);
		case 2: ApplyAnimation(playerid, "KNIFE", "knife_2", 4.1, 0, 1, 1, 0, 0, 1);
		case 3: ApplyAnimation(playerid, "KNIFE", "knife_3", 4.1, 0, 1, 1, 0, 0, 1);
		case 4: ApplyAnimation(playerid, "KNIFE", "knife_4", 4.1, 0, 1, 1, 0, 0, 1);
		case 5: ApplyAnimationEx(playerid, "KNIFE", "WEAPON_knifeidle", 4.1, 1, 0, 0, 0, 0, 1);
		case 6: ApplyAnimation(playerid, "KNIFE", "KILL_Knife_Player", 4.1, 0, 0, 0, 0, 0, 1);
		case 7: ApplyAnimation(playerid, "KNIFE", "KILL_Knife_Ped_Damage", 4.1, 0, 0, 0, 0, 0, 1);
		case 8: ApplyAnimation(playerid, "KNIFE", "KILL_Knife_Ped_Die", 4.1, 0, 0, 0, 0, 0, 1);
	}
	PlayerData[playerid][pLoopAnim] = 1;
	return 1;
}

CMD:cpranim(playerid, params[])
{
	if(!LoggedIn[playerid]) return 0;
	if(PlayerEnterWarFlag[playerid]) return ErrorMsg(playerid, "อย่าหาทำข้อร้อง");
    if (!AnimationCheck(playerid))
	    return ErrorMsg(playerid, "คุณไม่สามารถใช้อนิเมชั่นได้ในขณะนี้");

	ApplyAnimation(playerid, "MEDIC", "CPR", 4.1, 0, 0, 0, 0, 0, 1);
	PlayerData[playerid][pLoopAnim] = 1;
	return 1;
}

CMD:scratch(playerid, params[])
{
	if(!LoggedIn[playerid]) return 0;
	if(PlayerEnterWarFlag[playerid]) return ErrorMsg(playerid, "อย่าหาทำข้อร้อง");
    new type;

	if (!AnimationCheck(playerid))
	    return ErrorMsg(playerid, "คุณไม่สามารถใช้อนิเมชั่นได้ในขณะนี้");

	if (sscanf(params, "d", type))
	    return SystemMsg(playerid, "/scratch [1-4]");

	if (type < 1 || type > 4)
	    return ErrorMsg(playerid, "ระบุรูปแบบไม่ถูกต้อง");

	switch (type) {
    	case 1: ApplyAnimationEx(playerid, "SCRATCHING", "scdldlp", 4.1, 1, 0, 0, 0, 0, 1);
		case 2: ApplyAnimationEx(playerid, "SCRATCHING", "scdlulp", 4.1, 1, 0, 0, 0, 0, 1);
		case 3: ApplyAnimationEx(playerid, "SCRATCHING", "scdrdlp", 4.1, 1, 0, 0, 0, 0, 1);
		case 4: ApplyAnimationEx(playerid, "SCRATCHING", "scdrulp", 4.1, 1, 0, 0, 0, 0, 1);
	}
	PlayerData[playerid][pLoopAnim] = 1;
	return 1;
}

CMD:point(playerid, params[])
{
	if(!LoggedIn[playerid]) return 0;
	if(PlayerEnterWarFlag[playerid]) return ErrorMsg(playerid, "อย่าหาทำข้อร้อง");
    new type;

	if (!AnimationCheck(playerid))
	    return ErrorMsg(playerid, "คุณไม่สามารถใช้อนิเมชั่นได้ในขณะนี้");

	if (sscanf(params, "d", type))
	    return SystemMsg(playerid, "/point [1-4]");

	if (type < 1 || type > 4)
	    return ErrorMsg(playerid, "ระบุรูปแบบไม่ถูกต้อง");

	switch (type) {
	    case 1: ApplyAnimationEx(playerid, "PED", "ARRESTgun", 4.1, 0, 0, 0, 1, 0, 1);
	    case 2: ApplyAnimationEx(playerid, "SHOP", "ROB_Loop_Threat", 4.1, 1, 0, 0, 0, 0, 1);
    	case 3: ApplyAnimationEx(playerid, "ON_LOOKERS", "point_loop", 4.1, 1, 0, 0, 0, 0, 1);
		case 4: ApplyAnimationEx(playerid, "ON_LOOKERS", "Pointup_loop", 4.1, 1, 0, 0, 0, 0, 1);
	}
	PlayerData[playerid][pLoopAnim] = 1;
	return 1;
}

CMD:cheer(playerid, params[])
{
	if(!LoggedIn[playerid]) return 0;
	if(PlayerEnterWarFlag[playerid]) return ErrorMsg(playerid, "อย่าหาทำข้อร้อง");
    new type;

	if (!AnimationCheck(playerid))
	    return ErrorMsg(playerid, "คุณไม่สามารถใช้อนิเมชั่นได้ในขณะนี้");

	if (sscanf(params, "d", type))
	    return SystemMsg(playerid, "/cheer [1-8]");

	if (type < 1 || type > 8)
	    return ErrorMsg(playerid, "ระบุรูปแบบไม่ถูกต้อง");

	switch (type) {
		case 1: ApplyAnimation(playerid, "ON_LOOKERS", "shout_01", 4.1, 0, 0, 0, 0, 0, 1);
		case 2: ApplyAnimation(playerid, "ON_LOOKERS", "shout_02", 4.1, 0, 0, 0, 0, 0, 1);
		case 3: ApplyAnimation(playerid, "ON_LOOKERS", "shout_in", 4.1, 0, 0, 0, 0, 0, 1);
		case 4: ApplyAnimationEx(playerid, "RIOT", "RIOT_ANGRY_B", 4.1, 1, 0, 0, 0, 0, 1);
		case 5: ApplyAnimation(playerid, "RIOT", "RIOT_CHANT", 4.1, 0, 0, 0, 0, 0, 1);
		case 6: ApplyAnimation(playerid, "RIOT", "RIOT_shout", 4.1, 0, 0, 0, 0, 0, 1);
		case 7: ApplyAnimation(playerid, "STRIP", "PUN_HOLLER", 4.1, 0, 0, 0, 0, 0, 1);
		case 8: ApplyAnimation(playerid, "OTB", "wtchrace_win", 4.1, 0, 0, 0, 0, 0, 1);
	}
	PlayerData[playerid][pLoopAnim] = 1;
	return 1;
}

CMD:strip(playerid, params[])
{
	if(!LoggedIn[playerid]) return 0;
	if(PlayerEnterWarFlag[playerid]) return ErrorMsg(playerid, "อย่าหาทำข้อร้อง");
    new type;

	if (!AnimationCheck(playerid))
	    return ErrorMsg(playerid, "คุณไม่สามารถใช้อนิเมชั่นได้ในขณะนี้");

	if (sscanf(params, "d", type))
	    return SystemMsg(playerid, "/strip [1-7]");

	if (type < 1 || type > 7)
	    return ErrorMsg(playerid, "ระบุรูปแบบไม่ถูกต้อง");

	switch (type) {
		case 1: ApplyAnimationEx(playerid, "STRIP", "strip_A", 4.1, 1, 0, 0, 0, 0, 1);
		case 2: ApplyAnimationEx(playerid, "STRIP", "strip_B", 4.1, 1, 0, 0, 0, 0, 1);
		case 3: ApplyAnimationEx(playerid, "STRIP", "strip_C", 4.1, 1, 0, 0, 0, 0, 1);
		case 4: ApplyAnimationEx(playerid, "STRIP", "strip_D", 4.1, 1, 0, 0, 0, 0, 1);
		case 5: ApplyAnimationEx(playerid, "STRIP", "strip_E", 4.1, 1, 0, 0, 0, 0, 1);
		case 6: ApplyAnimationEx(playerid, "STRIP", "strip_F", 4.1, 1, 0, 0, 0, 0, 1);
		case 7: ApplyAnimationEx(playerid, "STRIP", "strip_G", 4.1, 1, 0, 0, 0, 0, 1);
	}
	PlayerData[playerid][pLoopAnim] = 1;
	return 1;
}

CMD:wave(playerid, params[])
{
	if(!LoggedIn[playerid]) return 0;
    new type;
	if(PlayerEnterWarFlag[playerid]) return ErrorMsg(playerid, "อย่าหาทำข้อร้อง");

	if (!AnimationCheck(playerid))
	    return ErrorMsg(playerid, "คุณไม่สามารถใช้อนิเมชั่นได้ในขณะนี้");

	if (sscanf(params, "d", type))
	    return SystemMsg(playerid, "/wave [1-3]");

	if (type < 1 || type > 3)
	    return ErrorMsg(playerid, "ระบุรูปแบบไม่ถูกต้อง");

	switch (type) {
	    case 1: ApplyAnimation(playerid, "PED", "endchat_03", 4.1, 0, 0, 0, 0, 0, 1);
	    case 2: ApplyAnimation(playerid, "KISSING", "gfwave2", 4.1, 0, 0, 0, 0, 0, 1);
	    case 3: ApplyAnimationEx(playerid, "ON_LOOKERS", "wave_loop", 4.1, 1, 0, 0, 0, 0, 1);
	}
	PlayerData[playerid][pLoopAnim] = 1;
	return 1;
}

CMD:smoke(playerid, params[])
{
	if(!LoggedIn[playerid]) return 0;
	if(PlayerEnterWarFlag[playerid]) return ErrorMsg(playerid, "อย่าหาทำข้อร้อง");
    new type;

	if (!AnimationCheck(playerid))
	    return ErrorMsg(playerid, "คุณไม่สามารถใช้อนิเมชั่นได้ในขณะนี้");

	if (sscanf(params, "d", type))
	    return SystemMsg(playerid, "/smoke [1-3]");

	if (type < 1 || type > 3)
	    return ErrorMsg(playerid, "ระบุรูปแบบไม่ถูกต้อง");

	switch (type) {
	    case 1: ApplyAnimation(playerid, "SMOKING", "M_smk_drag", 4.1, 0, 0, 0, 0, 0, 1);
	    case 2: ApplyAnimationEx(playerid, "SMOKING", "M_smklean_loop", 4.1, 1, 0, 0, 0, 0, 1);
	    case 3: ApplyAnimation(playerid, "SMOKING", "M_smkstnd_loop", 4.1, 0, 0, 0, 0, 0, 1);
	}
	PlayerData[playerid][pLoopAnim] = 1;
	return 1;
}

CMD:reload(playerid, params[])
{
	if(!LoggedIn[playerid]) return 0;
	if(PlayerEnterWarFlag[playerid]) return ErrorMsg(playerid, "อย่าหาทำข้อร้อง");
    new type;

	if (!AnimationCheck(playerid))
	    return ErrorMsg(playerid, "คุณไม่สามารถใช้อนิเมชั่นได้ในขณะนี้");

	if (sscanf(params, "d", type))
	    return SystemMsg(playerid, "/reload [1-4]");

	if (type < 1 || type > 4)
	    return ErrorMsg(playerid, "ระบุรูปแบบไม่ถูกต้อง");

	switch (type) {
		case 1: ApplyAnimation(playerid, "BUDDY", "buddy_reload", 4.1, 0, 0, 0, 0, 0, 1);
		case 2: ApplyAnimation(playerid, "UZI", "UZI_reload", 4.1, 0, 0, 0, 0, 0, 1);
		case 3: ApplyAnimation(playerid, "COLT45", "colt45_reload", 4.1, 0, 0, 0, 0, 0, 1);
		case 4: ApplyAnimation(playerid, "RIFLE", "rifle_load", 4.1, 0, 0, 0, 0, 0, 1);
	}
	PlayerData[playerid][pLoopAnim] = 1;
	return 1;
}

CMD:taichi(playerid, params[])
{
	if(!LoggedIn[playerid]) return 0;
	if(PlayerEnterWarFlag[playerid]) return ErrorMsg(playerid, "อย่าหาทำข้อร้อง");
    if (!AnimationCheck(playerid))
	    return ErrorMsg(playerid, "คุณไม่สามารถใช้อนิเมชั่นได้ในขณะนี้");

	ApplyAnimationEx(playerid, "PARK", "Tai_Chi_Loop", 4.1, 1, 0, 0, 0, 0, 1);
	PlayerData[playerid][pLoopAnim] = 1;
	return 1;
}

CMD:wank(playerid, params[])
{
	if(!LoggedIn[playerid]) return 0;
	if(PlayerEnterWarFlag[playerid]) return ErrorMsg(playerid, "อย่าหาทำข้อร้อง");
    new type;

	if (!AnimationCheck(playerid))
	    return ErrorMsg(playerid, "คุณไม่สามารถใช้อนิเมชั่นได้ในขณะนี้");

	if (sscanf(params, "d", type))
	    return SystemMsg(playerid, "/wank [1-3]");

	if (type < 1 || type > 3)
	    return ErrorMsg(playerid, "ระบุรูปแบบไม่ถูกต้อง");

	switch (type) {
		case 1: ApplyAnimationEx(playerid, "PAULNMAC", "wank_loop", 4.1, 1, 0, 0, 0, 0, 1);
		case 2: ApplyAnimation(playerid, "PAULNMAC", "wank_in", 4.1, 0, 0, 0, 0, 0, 1);
		case 3: ApplyAnimation(playerid, "PAULNMAC", "wank_out", 4.1, 0, 0, 0, 0, 0, 1);
	}
	PlayerData[playerid][pLoopAnim] = 1;
	return 1;
}

CMD:cower(playerid, const params[])
{
	if(!LoggedIn[playerid]) return 0;
	if(PlayerEnterWarFlag[playerid]) return ErrorMsg(playerid, "อย่าหาทำข้อร้อง");
    if (!AnimationCheck(playerid))
	    return ErrorMsg(playerid, "คุณไม่สามารถใช้อนิเมชั่นได้ในขณะนี้");

	ApplyAnimationEx(playerid, "PED", "cower", 4.1, 0, 0, 0, 1, 0, 1);
	PlayerData[playerid][pLoopAnim] = 1;
	return 1;
}

CMD:drunk(playerid, const params[])
{
	if(!LoggedIn[playerid]) return 0;
	if(PlayerEnterWarFlag[playerid]) return ErrorMsg(playerid, "อย่าหาทำข้อร้อง");
    if (!AnimationCheck(playerid))
	    return ErrorMsg(playerid, "คุณไม่สามารถใช้อนิเมชั่นได้ในขณะนี้");

	ApplyAnimationEx(playerid, "PED", "WALK_drunk", 4.1, 1, 1, 1, 1, 1, 1);
	PlayerData[playerid][pLoopAnim] = 1;
	return 1;
}

CMD:cry(playerid, const params[])
{
	if(!LoggedIn[playerid]) return 0;
	if(PlayerEnterWarFlag[playerid]) return ErrorMsg(playerid, "อย่าหาทำข้อร้อง");
    if (!AnimationCheck(playerid))
	    return ErrorMsg(playerid, "คุณไม่สามารถใช้อนิเมชั่นได้ในขณะนี้");

	ApplyAnimationEx(playerid, "GRAVEYARD", "mrnF_loop", 4.1, 1, 0, 0, 0, 0, 1);
	PlayerData[playerid][pLoopAnim] = 1;
    return 1;
}

CMD:tired(playerid, params[])
{
	if(!LoggedIn[playerid]) return 0;
	if(PlayerEnterWarFlag[playerid]) return ErrorMsg(playerid, "อย่าหาทำข้อร้อง");
    new type;

	if (!AnimationCheck(playerid))
	    return ErrorMsg(playerid, "คุณไม่สามารถใช้อนิเมชั่นได้ในขณะนี้");

	if (sscanf(params, "d", type))
	    return SystemMsg(playerid, "/tired [1-2]");

	if (type < 1 || type > 2)
	    return ErrorMsg(playerid, "ระบุรูปแบบไม่ถูกต้อง");

	switch (type) {
	    case 1: ApplyAnimationEx(playerid, "PED", "IDLE_tired", 4.1, 1, 0, 0, 0, 0, 1);
	    case 2: ApplyAnimationEx(playerid, "FAT", "IDLE_tired", 4.1, 1, 0, 0, 0, 0, 1);
	}
	PlayerData[playerid][pLoopAnim] = 1;
	return 1;
}

CMD:sit(playerid,params[])
{
	if(!LoggedIn[playerid]) return 0;
	if(PlayerEnterWarFlag[playerid]) return ErrorMsg(playerid, "อย่าหาทำข้อร้อง");
	new type;

	if (!AnimationCheck(playerid))
	    return ErrorMsg(playerid, "คุณไม่สามารถใช้อนิเมชั่นได้ในขณะนี้");

	if (sscanf(params, "d", type))
	    return SystemMsg(playerid, "/sit [1-6]");

	if (type < 1 || type > 6)
	    return ErrorMsg(playerid, "ระบุรูปแบบไม่ถูกต้อง");

    switch (type) {
		case 1: ApplyAnimationEx(playerid, "BEACH", "bather", 4.0, 1, 0, 0, 0, 0);
		case 2: ApplyAnimationEx(playerid, "BEACH", "Lay_Bac_Loop", 4.0, 1, 0, 0, 0, 0);
		case 3: ApplyAnimationEx(playerid, "BEACH", "ParkSit_W_loop", 4.0, 1, 0, 0, 0, 0);
		case 4: ApplyAnimationEx(playerid, "BEACH", "SitnWait_loop_W", 4.0, 1, 0, 0, 0, 0);
		case 5: ApplyAnimationEx(playerid, "BEACH", "ParkSit_M_loop", 4.0, 1, 0, 0, 0, 0);
		case 6: ApplyAnimationEx(playerid, "PED", "SEAT_down", 4.0, 0, 1, 1, 1, 0);
	}
	PlayerData[playerid][pLoopAnim] = 1;
	return 1;
}

CMD:sitdown(playerid, params[])
{
	if(!LoggedIn[playerid]) return 0;
	if(PlayerEnterWarFlag[playerid]) return ErrorMsg(playerid, "อย่าหาทำข้อร้อง");
    new type;

	if (!AnimationCheck(playerid))
	    return ErrorMsg(playerid, "คุณไม่สามารถใช้อนิเมชั่นได้ในขณะนี้");

	if (sscanf(params, "d", type))
	    return SystemMsg(playerid, "/sit [1-6]");

	if (type < 1 || type > 6)
	    return ErrorMsg(playerid, "ระบุรูปแบบไม่ถูกต้อง");

	switch (type) {
		case 1: ApplyAnimationEx(playerid, "CRIB", "PED_Console_Loop", 4.1, 1, 0, 0, 0, 0);
		case 2: ApplyAnimationEx(playerid, "INT_HOUSE", "LOU_In", 4.1, 0, 0, 0, 1, 0);
		case 3: ApplyAnimationEx(playerid, "MISC", "SEAT_LR", 4.1, 1, 0, 0, 0, 0);
		case 4: ApplyAnimationEx(playerid, "MISC", "Seat_talk_01", 4.1, 1, 0, 0, 0, 0);
		case 5: ApplyAnimationEx(playerid, "MISC", "Seat_talk_02", 4.1, 1, 0, 0, 0, 0);
		case 6: ApplyAnimationEx(playerid, "ped", "SEAT_down", 4.1, 0, 0, 0, 1, 0);
	}
	PlayerData[playerid][pLoopAnim] = 1;
	return 1;
}

CMD:crossarms(playerid, params[])
{
	if(!LoggedIn[playerid]) return 0;
	if(PlayerEnterWarFlag[playerid]) return ErrorMsg(playerid, "อย่าหาทำข้อร้อง");
	
    new type;

	if (!AnimationCheck(playerid))
	    return ErrorMsg(playerid, "คุณไม่สามารถใช้อนิเมชั่นได้ในขณะนี้");

	if (sscanf(params, "d", type))
	    return SystemMsg(playerid, "/crossarms [1-4]");

	if (type < 1 || type > 4)
	    return ErrorMsg(playerid, "ระบุรูปแบบไม่ถูกต้อง");

	switch (type) {
	    case 1: ApplyAnimationEx(playerid, "COP_AMBIENT", "Coplook_loop", 4.1, 0, 1, 1, 1, 0, 1);
	    case 2: ApplyAnimationEx(playerid, "GRAVEYARD", "prst_loopa", 4.1, 1, 0, 0, 0, 0, 1);
	    case 3: ApplyAnimationEx(playerid, "GRAVEYARD", "mrnM_loop", 4.1, 1, 0, 0, 0, 0, 1);
	    case 4: ApplyAnimationEx(playerid, "DEALER", "DEALER_IDLE", 4.1, 0, 1, 1, 1, 0, 1);
	}
	PlayerData[playerid][pLoopAnim] = 1;
	return 1;
}

CMD:fucku(playerid, const params[])
{
	if(!LoggedIn[playerid]) return 0;
	if(PlayerEnterWarFlag[playerid]) return ErrorMsg(playerid, "อย่าหาทำข้อร้อง");
    if (!AnimationCheck(playerid))
	    return ErrorMsg(playerid, "คุณไม่สามารถใช้อนิเมชั่นได้ในขณะนี้");

	ApplyAnimation(playerid, "PED", "fucku", 4.1, 0, 0, 0, 0, 0);
	PlayerData[playerid][pLoopAnim] = 1;
	return 1;
}

CMD:walk(playerid, params[])
{
	if(!LoggedIn[playerid]) return 0;
	if(PlayerEnterWarFlag[playerid]) return ErrorMsg(playerid, "อย่าหาทำข้อร้อง");
    new type;

	if (!AnimationCheck(playerid))
	    return ErrorMsg(playerid, "คุณไม่สามารถใช้อนิเมชั่นได้ในขณะนี้");

	if (sscanf(params, "d", type))
	    return SystemMsg(playerid, "/walk [1-16]");

	if (type < 1 || type > 17)
	    return ErrorMsg(playerid, "ระบุรูปแบบไม่ถูกต้อง");

	switch (type) {
	    case 1: ApplyAnimationEx(playerid, "FAT", "FatWalk", 4.1, 1, 1, 1, 1, 1, 1);
	    case 2: ApplyAnimationEx(playerid, "MUSCULAR", "MuscleWalk", 4.1, 1, 1, 1, 1, 1, 1);
	    case 3: ApplyAnimationEx(playerid, "PED", "WALK_armed", 4.1, 1, 1, 1, 1, 1, 1);
	    case 4: ApplyAnimationEx(playerid, "PED", "WALK_civi", 4.1, 1, 1, 1, 1, 1, 1);
	    case 5: ApplyAnimationEx(playerid, "PED", "WALK_fat", 4.1, 1, 1, 1, 1, 1, 1);
	    case 6: ApplyAnimationEx(playerid, "PED", "WALK_fatold", 4.1, 1, 1, 1, 1, 1, 1);
	    case 7: ApplyAnimationEx(playerid, "PED", "WALK_gang1", 4.1, 1, 1, 1, 1, 1, 1);
	    case 8: ApplyAnimationEx(playerid, "PED", "WALK_gang2", 4.1, 1, 1, 1, 1, 1, 1);
	    case 9: ApplyAnimationEx(playerid, "PED", "WALK_player", 4.1, 1, 1, 1, 1, 1, 1);
	    case 10: ApplyAnimationEx(playerid, "PED", "WALK_old", 4.1, 1, 1, 1, 1, 1, 1);
	    case 11: ApplyAnimationEx(playerid, "PED", "WALK_wuzi", 4.1, 1, 1, 1, 1, 1, 1);
	    case 12: ApplyAnimationEx(playerid, "PED", "WOMAN_walkbusy", 4.1, 1, 1, 1, 1, 1, 1);
	    case 13: ApplyAnimationEx(playerid, "PED", "WOMAN_walkfatold", 4.1, 1, 1, 1, 1, 1, 1);
	    case 14: ApplyAnimationEx(playerid, "PED", "WOMAN_walknorm", 4.1, 1, 1, 1, 1, 1, 1);
	    case 15: ApplyAnimationEx(playerid, "PED", "WOMAN_walksexy", 4.1, 1, 1, 1, 1, 1, 1);
	    case 16: ApplyAnimationEx(playerid, "PED", "WOMAN_walkshop", 4.1, 1, 1, 1, 1, 1, 1);
	}
	PlayerData[playerid][pLoopAnim] = 1;
	return 1;
}