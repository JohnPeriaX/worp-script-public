new CountRespawnCar = 0;

//650000
task CheckGroupOnline[650000](){
	new countpolice, countmedic, coutmechanic;
	foreach(new i : Player){
		if(!LoggedIn[i]) continue;
		if(GetGroupType(i) == GROUP_POLICE && BitFlag_Get(g_PlayerFlags[i], PLAYER_ONDUTY))
			countpolice++;
		if(GetGroupType(i) == GROUP_MEDIC)
			countmedic++;
		if(GetGroupType(i) == GROUP_MECHANIC)
			coutmechanic++;
	}
	SendClientMessageToAllEx(COLOR_SERVER, "{23D101}| [Government-Online]: {FFFFFF}ตำรวจ: %d คน | แพทย์/หมอ: %d คน | ช่างยนต์: %d คน", countpolice, countmedic, coutmechanic);
}

//600000
task ADTIME[600000](){

	for(new i=0; i< MAX_GREENFARM; i++){
		if(FarmGreen[i][FarmTaken] == 1){
			FarmGreen[i][FarmTaken] = 0;
			Farm_Refresh(i);
		}
	}

	new RandomMSG[][] =
	{
		"{23D101}[Announce]: {FFFFFF}ตัวช่วยสำหรับผู้เล่นใหม่ พิมพ์ '/help' เพื่อดูการช่วยเหลือต่างๆ",
		"{23D101}[Announce]: {FFFFFF}หากพบบัคหรือโปรแกรมช่วยเล่น พิมพ์ '/report' เพื่อแจ้งผู้ดูแลระบบ",
		"{23D101}[Announce]: {FFFFFF}เว็บไซต์ของเซิฟเวอร์: www.gta-worp.com",
		"{23D101}[Announce]: {FFFFFF}ติดต่อสอบถามปัญหาได้ทางแฟนเพจ หรือ Discord เท่านั้น",
		"{23D101}[Announce]: {FFFFFF}หากซื้อขายแล้วโดน 'เกรียน' แอดมินจะไม่รับผิดชอบใดๆทั้งสิ้น",
		"{23D101}[Announce]: {FFFFFF}ห้ามทำการซื้อขายของผิดกฏหมายแบบ OOC ทั้งสิ้น"
	};
	new COLOR = COLOR_SERVER; //
	new randMSG = random(sizeof(RandomMSG));
	SendClientMessageToAll(COLOR, RandomMSG[randMSG]);
}

//600000
task ADSaveData[600000](){
	SendClientMessageToAll(0x0075C1AA, "[Save-Data]: เซิฟเวอร์ได้ทำการเซฟข้อมูลผู้เล่นเรียบร้อยแล้ว");
}

ptask SaveData[1200000](playerid){
	if(LoggedIn[playerid] && !PlayerData[playerid][pFirstTime]) Character_Save(playerid);
}

//3600000
HourTime(){
	LoadTopRank();
	for(new i=0; i< MAX_WOODS; i++){
		if(WoodData[i][woodStill] != 1) continue;
		if(WoodData[i][woodAmount] < 100){
			WoodData[i][woodAmount] = 100;
			Wood_Refresh(i);
		}
	}

	for(new i=0; i<MAX_OILS; i++){
		if(!OilData[i][oilStill]) continue;
		if(OilData[i][oilAmount] < 300){
			OilData[i][oilAmount] = 300;
			Oil_Refresh(i);
			Oil_Save(i);
		}
	}

	for(new i=0; i<MAX_SHELLS; i++){
		if(!ShellData[i][shellEx]) continue;
		ShellData[i][shellAlive] = 1;
		ShellData[i][shellPlayerUse] = 0;
		Shell_Refresh(i);
	}

	for(new i=0; i< MAX_RUBBERTREE; i++){
		if(!RubberData[i][rubberEx]) continue;
		if(RubberData[i][rubberHealth] < 500){
			RubberData[i][rubberHealth] = 500;
			Rubber_Refresh(i);
		}
	}

	for(new i=0; i<MAX_ORANGE; i++){
		if(!OrangeData[i][orangeEx]) continue;
		OrangeData[i][orangeHealth] = 50;
		Refresh_Orange(i);
	}

	new
		query[64];

	for (new i = 0; i < MAX_DROPPED_ITEMS; i ++){
		if(Drop_Data[i][droppedObject] && Drop_Data[i][droppedModel]){
			Drop_Data[i][droppedModel] = 0;
			Drop_Data[i][droppedQuantity] = 0;
			Drop_Data[i][droppedPos][0] = 0.0;
			Drop_Data[i][droppedPos][1] = 0.0;
			Drop_Data[i][droppedPos][2] = 0.0;
			Drop_Data[i][droppedInt] = 0;
			Drop_Data[i][droppedWorld] = 0;

			if(IsValidDynamicObject(Drop_Data[i][droppedObject]) && Drop_Data[i][droppedObject] != -1) {
				DestroyDynamicObject(Drop_Data[i][droppedObject]);
				Drop_Data[i][droppedObject] = -1;
			}

			if(IsValidDynamic3DTextLabel(Drop_Data[i][droppedText3D]) && Drop_Data[i][droppedText3D]) {
				DestroyDynamic3DTextLabel(Drop_Data[i][droppedText3D]);
			}
				
			format(query, sizeof(query), "DELETE FROM `dropped` WHERE `ID` = '%d'", Drop_Data[i][droppedID]);
			mysql_tquery(dbCon, query);
		}
	}

	SendClientMessageToAll(COLOR_RED, "[ลบไอเท็มบนพื้น]: ระบบได้ทำการลบไอเท็มบนพื้นทั้งหมดแล้ว");

	foreach(new x : Player){
		if(!LoggedIn[x]) continue;
		Streamer_Update(x);
		AllRemoveTicket(x);
	
		if(PlayerData[x][pVip] == 0) continue;

		new tmphour, tmpminute, tmpsecond;
		gettime(tmphour, tmpminute, tmpsecond);
		new Day, Month, Year;
		getdate(Year, Month, Day);

		new vipstr[64], string[128];

		if(PlayerData[x][pVip] == 1) vipstr = "Bronze Member";
		else if(PlayerData[x][pVip] == 2) vipstr = "Silver Member";
		else if(PlayerData[x][pVip] == 3) vipstr = "Gold Member";

		if(Day >= PlayerData[x][pVipDay] && Month >= PlayerData[x][pVipMonth] && tmphour >= PlayerData[x][pVipHour]){
			format(string, sizeof(string), "%s ของ %s ได้หมดอายุแล้ว", vipstr, ReturnRoleplayName(x));
			SendAdminsMessage(1, 0x2F91FFAA, string);
			SendClientMessageEx(x, 0x2F91FFAA, "[หมดอายุ]: %s ของคุณได้หมดอายุแล้ว", vipstr);
			Log_Write("logs/vip_log.txt", "[%s] VIP %s's %s expire", ReturnDate(), vipstr, ReturnRoleplayName(x));
			PlayerData[x][pVip] = 0;
			PlayerData[x][pVipDay] = 0;
			PlayerData[x][pVipMonth] = 0;
			PlayerData[x][pVipHour] = 0;
		}
	}

	for(new i=0; i<MAX_DRUGPOINT; i++){
		if(!DrugData[i][drugEx]) continue;
		if(DrugData[i][drugAmount] < 200)
			DrugData[i][drugAmount] = 200;
	}

	for(new i=0; i<MAX_COWS; i++){
		if(!CowData[i][cowStill]) continue;
		SetDynamicObjectPos(CowData[i][cowObject], CowData[i][cowPos][0], CowData[i][cowPos][1], CowData[i][cowPos][2]);
		MoveDynamicObject(CowData[i][cowObject], CowData[i][cowPos][0], CowData[i][cowPos][1], CowData[i][cowPos][2], 2.0, 0.00000, 0.00000, CowData[i][cowPos][3]);
		CowData[i][cowDeath] = 0;
		CowData[i][cowPicking] = 0;
	}

	CountRespawnCar++;
	if(CountRespawnCar >= 3){
		StartRespawnCar = 1;
		TimerRespawnCar = 60;
		SendClientMessageToAll(COLOR_ORANGE, "[รียานพาหนะ]: อีก 1 นาที ระบบจะทำการรียานพาหนะภายในเซิฟเวอร์กลับจุดเดิม, หากยานพาหนะที่มีผู้ใช้อยู่จะไม่ถูกรีกลับจุดเดิม");
		CountRespawnCar = 0;
	}
	
	RandomPriceJob();
	RandomPlantPrice();
	RandomHunterJob();
	RandomPriceRedMoney();
	return 1;
}

ptask UpdateTimerFiveMinutes[300000](x){
	if(LoggedIn[x]){
		if(PlayerData[x][pHunger] >= 0){
			if(AdminDuty[x] == 0)
				PlayerData[x][pHunger]--;

			if(PlayerData[x][pHunger] <= 0)
				PlayerData[x][pHunger] = 0;

			if(PlayerData[x][pHunger] <= 20){
				SendNearbyMessage(x, 30.0, COLOR_GRAY, "* ท้องร้อง เนื่องจาก หิว (( %s ))", ReturnRoleplayName(x));
				new Float:hp;
				GetPlayerHealth(x, hp);
				SetPlayerHealth(x, hp-5);
			}
		}

		if(PlayerData[x][pWater] >= 0){

			if(AdminDuty[x] == 0)
				PlayerData[x][pWater]--;

			if(PlayerData[x][pWater] <= 0)
				PlayerData[x][pWater] = 0;

			if(PlayerData[x][pWater] <= 20){
				SendNearbyMessage(x, 30.0, COLOR_GRAY, "* มีอาการเหนื่อย เนื่องจาก กระหายน้ำ (( %s ))", ReturnRoleplayName(x));
				new Float:hp;
				GetPlayerHealth(x, hp);
				SetPlayerHealth(x, hp-5);
			}
		}

		if(PlayerData[x][pEnergy] >= 0){
			
			if(AdminDuty[x] == 0)
				PlayerData[x][pEnergy] -= 2;

			if(PlayerData[x][pEnergy] <= 0)
				PlayerData[x][pEnergy] = 0;

			if(PlayerData[x][pEnergy] <= 20){
				SendNearbyMessage(x, 30.0, COLOR_GRAY, "* มีอาการเหนื่อย เนื่องจาก หมดแรง (( %s ))", ReturnRoleplayName(x));
				new Float:hp;
				GetPlayerHealth(x, hp);
				SetPlayerHealth(x, hp-5);
			}
		}

		if(PlayerData[x][pShower] <= 100){
			if(AdminDuty[x] == 0)
				PlayerData[x][pShower]++;

			if(PlayerData[x][pShower] >= 100)
				PlayerData[x][pShower] = 100;

			if(PlayerData[x][pShower] >= 80){
				SendNearbyMessage(x, 30.0, COLOR_GRAY, "* ตัวของเขาเริ่มมีกลิ่นแรง เนื่องจาก ไม่ได้ทำความสะอาด (( %s ))", ReturnRoleplayName(x));
				if(!IsPlayerInAnyVehicle(x)) ApplyAnimation(x, "FOOD", "EAT_Vomit_P", 4.1, 0, 0, 0, 0, 0, 1);
				new Float:hp;
				GetPlayerHealth(x, hp);
				SetPlayerHealth(x, hp-5);
			}
		}

		if(PlayerData[x][pStress] >= 180){
			SendNearbyMessage(x, 30.0, COLOR_GRAY, "* มีอาการเครียด เนื่องจาก เขาทำงานหนักหรือไม่ได้พักผ่อน (( %s ))", ReturnRoleplayName(x));
			if(!IsPlayerInAnyVehicle(x)) ApplyAnimation(x, "DODGE", "Crush_Jump", 4.1, 0, 1, 1, 0, 0, 1);
			SetPlayerWeather(x, -67);
			new Float:hp;
			GetPlayerHealth(x, hp);
			SetPlayerHealth(x, hp-5);
		}
	}
}

//60000
ptask UpdateTimerMinutes[60000](x){
	if(LoggedIn[x]){
		if(!IsAFK{x}) PlayerData[x][pMinutes]++;
		if (PlayerData[x][pMinutes] >= 60){
			SetPlayerNameTag(x, x);
			SendClientMessage(x, COLOR_DARKGREEN, "|------------------------------------------------------|");
			SendClientMessage(x, COLOR_DARKGREEN, "[PayCheck]");

			if(PlayerData[x][pUseExpx2] > 0){
				if(PlayerData[x][pVip] == 0){
					new sumexp = 1 * ServerData[ServerExp] * 2;
					PlayerData[x][pExp] += sumexp;
					SendClientMessageEx(x, -1, "- คุณได้รับ Exp + %s", FormatNumberNotMoney(sumexp));
				}
				else if(PlayerData[x][pVip] == 1){
					new sumexp = 2 * ServerData[ServerExp] * 2;
					PlayerData[x][pExp] += sumexp;
					SendClientMessageEx(x, -1, "- คุณได้รับ Exp + %s เนื่องจากเป็น Bronze Member", FormatNumberNotMoney(sumexp));
				}
				else if(PlayerData[x][pVip] == 2){
					new sumexp = 3 * ServerData[ServerExp] * 2;
					PlayerData[x][pExp] += sumexp;
					SendClientMessageEx(x, -1, "- คุณได้รับ Exp + %s เนื่องจากเป็น Silver Member", FormatNumberNotMoney(sumexp));
				}
				else if(PlayerData[x][pVip] == 3){
					new sumexp = 4 * ServerData[ServerExp] * 2;
					PlayerData[x][pExp] += sumexp;
					SendClientMessageEx(x, -1, "- คุณได้รับ Exp + %s เนื่องจากเป็น Gold Member", FormatNumberNotMoney(sumexp));
				}

				PlayerData[x][pUseExpx2]--;
				if(Jdz_Exp_Show[x]){
					new expstring[64];
					format(expstring, sizeof expstring, "%d H", PlayerData[x][pUseExpx2]);
					PlayerTextDrawSetString(x, Exp_Hud[x][2], expstring);
				}
				if(PlayerData[x][pUseExpx2] <= 0){
					if(Jdz_Exp_Show[x]) Jdz_Exp_Hud_Hide(x);
					PlayerData[x][pUseExpx2] = 0;
				}
			}else{
				if(PlayerData[x][pVip] == 0){
					new sumexp = 1 * ServerData[ServerExp];
					PlayerData[x][pExp] += sumexp;
					SendClientMessageEx(x, -1, "- คุณได้รับ Exp + %s", FormatNumberNotMoney(sumexp));
				}
				else if(PlayerData[x][pVip] == 1){
					new sumexp = 2 * ServerData[ServerExp];
					PlayerData[x][pExp] += sumexp;
					SendClientMessageEx(x, -1, "- คุณได้รับ Exp + %s เนื่องจากเป็น Bronze Member", FormatNumberNotMoney(sumexp));
				}
				else if(PlayerData[x][pVip] == 2){
					new sumexp = 3 * ServerData[ServerExp];
					PlayerData[x][pExp] += sumexp;
					SendClientMessageEx(x, -1, "- คุณได้รับ Exp + %s เนื่องจากเป็น Silver Member", FormatNumberNotMoney(sumexp));
				}
				else if(PlayerData[x][pVip] == 3){
					new sumexp = 4 * ServerData[ServerExp];
					PlayerData[x][pExp] += sumexp;
					SendClientMessageEx(x, -1, "- คุณได้รับ Exp + %s เนื่องจากเป็น Gold Member", FormatNumberNotMoney(sumexp));
				}
			}
			
			if(PlayerData[x][pGroup] != -1){
				if(GroupData[PlayerData[x][pGroup]][groupSkills][3] == 1) {
					PlayerData[x][pExp] += 1;
					SendClientMessage(x, -1, "- คุณได้รับ Exp + 1 จากบัพสกิลแก๊ง Level 4");
				}

				if(GroupData[PlayerData[x][pGroup]][groupSkills][4] == 1) {
					PlayerData[x][pExp] += 2;
					SendClientMessage(x, -1, "- คุณได้รับ Exp + 2 จากบัพสกิลแก๊ง Level 5");
				}
			}

			SendClientMessage(x, -1, "- ชั่วโมงออนไลน์ + 1");

			if(PlayerData[x][pTimeQuitGang] > 0) {
				PlayerData[x][pTimeQuitGang]--;
				SendClientMessageEx(x, COLOR_YELLOW, "- คุณเหลือเวลาอีก %d ชั่วโมงที่จะเข้าร่วมกลุ่มอีกครั้ง", PlayerData[x][pTimeQuitGang]);
				if(PlayerData[x][pTimeQuitGang] == 0){
					SendClientMessage(x, COLOR_YELLOW, "- ขณะนี้คุณสามารถเข้าร่วมกับกลุ่มได้แล้ว");
				}
			}

			new moneylevel = PlayerData[x][pLevel] * LEVEL_MONEY;

			GiveMoney(x, moneylevel, "get paycheck level");

			SendClientMessageEx(x, -1, "- คุณได้รับเงิน %s จากการออนไลน์ครบชั่วโมง", FormatNumber(moneylevel));

			if(PlayerData[x][pLevel] >= 2){
				if(GetGroupType(x) != GROUP_POLICE && GetGroupType(x) != GROUP_MEDIC && GetGroupType(x) != GROUP_NATIONAL){
					GiveMoney(x, -ServerData[ServerTax], "pay tax");
					SendClientMessageEx(x, COLOR_RED, "- คุณได้เสียภาษีรายชั่วโมงให้กับรัฐบาลเป็นจำนวนเงิน %s", FormatNumber(ServerData[ServerTax]));
				}
			}

			SendClientMessage(x, COLOR_DARKGREEN, "|------------------------------------------------------|");
			PlayerData[x][pPlayerhour]++;
			PlayerData[x][pMinutes] = 0;

			new nxtlevel = PlayerData[x][pLevel]+1;
			new expamount = nxtlevel*levelexp;
			if(PlayerData[x][pExp] >= expamount)
			{
				if(PlayerData[x][pLevel] < 100)
				{
					PlayerData[x][pExp] -= expamount;
					PlayerData[x][pLevel]++;
					SendClientMessageEx(x, COLOR_GREY, "- ยินดีด้วยคุณเลเวลอัพเป็น %d แล้ว", PlayerData[x][pLevel]);
				}
				else if(PlayerData[x][pLevel] >= 100)
				{
					SendClientMessageEx(x, COLOR_GREY, "- คุณมีเลเวล %d แล้วซึ่งเลเวลของคุณได้ตันแล้ว!", PlayerData[x][pLevel]);
				}
			}
		}
	}
}

ptask CheckPosition[1000](x){

	if(IsPlayerInRangeOfPoint(x, 5.0, 2497.0417,2773.2729,10.8251)){
		if(!doorlabelopen){
			doorlabelopen = true;
			MoveDynamicObject(doorlabel[0], 2497.447265, 2785.346679, 11.449273, 2.5, 0.000000, 0.000000, 90.000000);
			MoveDynamicObject(doorlabel[1], 2497.447265, 2785.346679, 11.449273, 2.5, 0.000000, 0.000000, 450.000000);
			doorlabeltime = 8;
		}
	}

	//ห้ามนำรถเข้า Market Center
	if(IsPlayerInRangeOfPoint(x, 10.0, 1128.4755,-1420.8707,14.6705)){
		if (IsPlayerInAnyVehicle(x)){
			SetVehiclePos(GetPlayerVehicleID(x), 1085.8369,-1369.2148,13.7813);
			SetVehicleZAngle(GetPlayerVehicleID(x), 179.8678);
			LinkVehicleToInterior(GetPlayerVehicleID(x), 0);
			SetPlayerInterior(x, 0);
			SetPlayerVirtualWorld(x, 0);
		}
	}

	//เซเว่น
	if(IsPlayerInRangeOfPoint(x, 4.0, 1928.6578,-1775.6096,13.5469)){
		if(timedoor24 <= 0){
			for(new i=0; i<30; i++) SendClientMessage(x, -1, " ");
			MoveDynamicObject(door24left[1], 1928.29346, -1777.55945, 13.56687, 2.5, 89.99999, 450.00000, -89.99997);
			MoveDynamicObject(door24right[1], 1928.30151, -1773.60046, 13.56687, 2.5, 89.99999, 450.00000, -89.99997);
			timedoor24 = 8;
		}
	}

	//ล่าสมบัติออกซิเจน
	if(IsPlayerInRangeOfPoint(x, 30.5, -1305.8270,2531.5310,87.7422)){
		new Float:hp;
		GetPlayerHealth(x, hp);
		if(GetToolAndClothSeeker[x] == 0){
			SetPlayerHealth(x, hp-3);
		}
		
		else if(GetToolAndClothSeeker[x] == 1){
			if(OxygenSeeker[x] <= 0)
				SetPlayerHealth(x, hp-3);
		}
	}

	//เล่นเพลง Merry Christmas
	if(IsPlayerInRangeOfPoint(x, 50.0, 484.6133,-1500.6644,20.3320)){
		if(!PlayerPlaySongChristmas[x]){
			PlayAudioStreamForPlayer(x, "http://154.202.2.10/songlist/lastchristmas.mp3", 484.6133,-1500.6644,20.3320, 50.0, true);
			PlayerPlaySongChristmas[x] = true;
		}
	}
	else{
		if(PlayerPlaySongChristmas[x]){
			StopAudioStreamForPlayer(x);
			PlayerPlaySongChristmas[x] = false;
		}
	}
}

task UpdateMine[1000](){
	for(new i=0; i < MAX_MINE; i++){
		if(MineData[i][mineStill]) continue;
		if(MineData[i][mineDelay] == 0) continue;
		if(MineData[i][mineDelay] > 0){
			MineData[i][mineDelay]--;
			if(MineData[i][mineDelay] == 0){
				MineData[i][mineStill] = true;
				Mine_Refresh(i);
			}
		}
	}
}

task BoomboxTimer[1000](){
	foreach(new i : Player){
		if(!LoggedIn[i]) continue;
		new boomboxid = Boombox_Nearest(i);
		if(PlayerData[i][pBoombox] != boomboxid) {
			PlayerData[i][pBoombox] = boomboxid;

			if(boomboxid == INVALID_PLAYER_ID) {
				StopAudioStreamForPlayer(i);
			} else if(strcmp(BoomboxData[boomboxid][boomboxURL], "None") != 0) {
				PlayAudioStreamForPlayer(i, BoomboxData[boomboxid][boomboxURL], BoomboxData[boomboxid][boomboxPos][0], BoomboxData[boomboxid][boomboxPos][1], BoomboxData[boomboxid][boomboxPos][2], 30.0, true);
			}
		}
	}
}

ptask UpdateWeaponOnBody[2000](x){
	//อาวุธติดตัว
	if(PlayerData[x][pMyWeapon][1] != 0){
		if(GetPlayerWeapon(x) != PlayerData[x][pMyWeapon][1]){
			if(!IsPlayerAttachedObjectSlotUsed(x,6)){
				new object = (PlayerData[x][pMyWeapon][1] == WEAPON_DEAGLE) ? 348 : 346;
				SetPlayerAttachedObject(x,6,object, 8, 0.000000,-0.055999,0.088000,-97.200004,0.000000,-14.000001,1.000000,1.000000,1.000000);

			}
		}
		else if(IsPlayerAttachedObjectSlotUsed(x, 6) && GetPlayerWeapon(x) == PlayerData[x][pMyWeapon][1]){
			RemovePlayerAttachedObject(x, 6);
		}
	}

	if(PlayerData[x][pMyWeapon][2] != 0){
		if(GetPlayerWeapon(x) != PlayerData[x][pMyWeapon][2]){
			if(!IsPlayerAttachedObjectSlotUsed(x,4)){
				new object;
				if(PlayerData[x][pMyWeapon][2] == WEAPON_BAT) object = 336;
				else if(PlayerData[x][pMyWeapon][2] == WEAPON_POOLSTICK) object = 338;
				else if(PlayerData[x][pMyWeapon][2] == WEAPON_KATANA) object = 339;
				else if(PlayerData[x][pMyWeapon][2] == WEAPON_CANE) object = 326;
				else if(PlayerData[x][pMyWeapon][2] == WEAPON_GOLFCLUB) object = 333;
				else if(PlayerData[x][pMyWeapon][2] == WEAPON_SHOVEL) object = 337;

				if(PlayerData[x][pMyWeapon][2] == WEAPON_BAT && PlayerUseSkinBaseHalloween[x]){
					SetPlayerAttachedObject(x, 5,2045,1,0.135000,-0.120999,0.000000,97.899993,-2.400000,50.199996,1.751999,1.674000,1.571999);
				}

				SetPlayerAttachedObject(x, 4, object, 1, 0.254999,-0.147999,-0.158999,0.000000,-50.499961,0.000000,1.000000,1.000000,1.000000);
			}
		}
		else if(IsPlayerAttachedObjectSlotUsed(x, 4) && PlayerData[x][pMyWeapon][2] == GetPlayerWeapon(x)){
			if(PlayerData[x][pMyWeapon][2] == WEAPON_BAT && PlayerUseSkinBaseHalloween[x]){
				SetPlayerAttachedObject(x,5,2045,6,0.046999,0.019000,0.247000,94.000007,0.000000,-0.899998,1.797999,1.885000,1.601000);
			}

			RemovePlayerAttachedObject(x, 4);
		}
	}
}

ptask UpdateMedicCheckPoint[2500](x){
	if(MedicToMe[x] != -1 && PlayerEnterCheckPointMedic[x]){
		new Float:xx, Float:yy, Float:zz;
		GetPlayerPos(MedicToMe[x], xx, yy, zz);
		SetPlayerCheckpoint(x, xx, yy, zz, 5.0);

		if(!LoggedIn[MedicToMe[x]]){
			DisablePlayerCheckpoint(x);
			MedicToMe[x] = -1;
			PlayerEnterCheckPointMedic[x] = 0;
		}
	}
}

ptask UpdateInjured[1000](x){
	new string[128];
	if(PlayerData[x][pInHospital] == 1 && PlayerData[x][pInjured] == 0 && SetStartTimeHospital[x] == 1){
		HospitalHealth[x] += 2;
		format(string,sizeof(string),"~n~~n~~n~~n~~n~~n~~n~~n~~r~Health: %d", HospitalHealth[x]);
		GameTextForPlayer(x, string, 1000, 3);

		if(HospitalHealth[x] >= 80){
			TogglePlayerSpectating(x, 0);
			PlayerData[x][pInHospital] = 0;
			SetStartTimeHospital[x] = 0;
		}
	}

	if(TimeInjuredStart[x] == 1 && PlayerData[x][pInjured] == 1){
		if(PlayerData[x][pInjuredTime] > 0){
			PlayerData[x][pInjuredTime]--;

			format(string, sizeof(string), "( ผู้เล่นนี้บาดเจ็บ | /damages %d )", x);
			SetPlayerChatBubble(x, string, 0xFF7800DD, 10.0, 1000);

			format(string,sizeof(string),"~n~~n~~n~~n~~n~~n~~r~Time to Die: %d Seconds~n~~w~Press 'Y' Call Medic~n~~w~Press 'N' To Die", PlayerData[x][pInjuredTime]);
			GameTextForPlayer(x, string, 1000, 3);
		}

		if(GetPlayerState(x) == PLAYER_STATE_ONFOOT){
			ApplyAnimation(x, "SWEET", "Sweet_injuredloop", 4.0, 1, 0, 0, 0, 0); 
		}
	}
}

ptask UpdateSleepBed[5000](x){
	if(PlayerCheckSleepOnBed[x]){
		new Float:hp;
		GetPlayerHealth(x, hp);
		if(hp < 100){
			SetPlayerHealth(x, hp+5);
		}
		else if(hp >= 100){
			SendClientMessageEx(x, 0xFF73FBAA, "- คุณได้จ่ายเงินค่านอนรักษาเตียง $500");
			GiveMoney(x, -500, "pay sleepbed");
			PlayerCheckSleepOnBed[x] = false;
			TogglePlayerControllable(x, 1);
			ClearAnimations(x);
		}
	}
}

ptask UpdateSleep[1000](x){
	if(StartSleep[x] == 1){
		if(TimeSleepPoint[x] < 100){
			TimeSleepPoint[x] += 2;
		}
		else if(TimeSleepPoint[x] >= 100){
			TimeSleepPoint[x] = 0;
			if(PlayerData[x][pEnergy] < 98){
				PlayerData[x][pEnergy] += 2;
				SendClientMessageEx(x, COLOR_YELLOW, "- คุณได้นอนพักผ่อนและได้รับค่าพลังงาน (Energy) + 2");

				if(PlayerData[x][pStress] > 0){
					PlayerData[x][pStress]--;
				}

			}
			else if(PlayerData[x][pEnergy] >= 98){
				PlayerData[x][pEnergy] = 100;
				StartSleep[x] = 0;
				SendClientMessageEx(x, COLOR_YELLOW, "- คุณได้นอนพักผ่อนจนเต็มอิ่มแล้ว");

				if(PlayerData[x][pStress] < 180){
					SetPlayerWeather(x, g_serverWeather);
				}

				if(PlayerData[x][pStress] < 0){
					PlayerData[x][pStress] = 0;
				}
			}
		}
	}
}

ptask UpdatePhoneTime[1000](x){
	new string[128];
	if(PlayerUsingPhone[x] == 1){
		new tmphourx;
		new tmpminutex;
		new tmpsecondx;
		gettime(tmphourx, tmpminutex, tmpsecondx);
		format(string, sizeof(string), "%02d:%02d", tmphourx, tmpminutex);
		PlayerTextDrawSetString(x, PlayerPhoneTD[x][9], string);
	}
}

ptask UpdateJailTime[1000](x){
	new string[128];
	if(PlayerData[x][pJail] == 1){
		if(PlayerData[x][pJailTime] > 0){
			PlayerData[x][pJailTime]--;
			format(string, sizeof(string), "~r~Jail Time: %d", PlayerData[x][pJailTime]);
			GameTextForPlayer(x, string, 1000, 3);
		}
		else if(PlayerData[x][pJailTime] <= 0){
			PlayerData[x][pJailTime] = 0;
			PlayerData[x][pJail] = 0;
			BitFlag_Off(g_PlayerFlags[x],PLAYER_PHONE_OFF);
			SetPlayerPosEx(x, 273.2697,1382.4161,11.1408, 0, 0);
			SetPlayerFacingAngle(x, 265.3359);
			SetPlayerSkin(x, PlayerData[x][pSkin]);
		}
	}
}

ptask DrunkTimer[1000](x){
	if(DrunkTime[x] > 0){
		DrunkTime[x]--;
		if(DrunkTime[x] == 0){
			new
				time[3];

			gettime(time[0], time[1], time[2]);
			SetPlayerTime(x, time[0], time[1]);
			SetPlayerDrunkLevel(x, 500);
			SetPlayerWeather(x, g_serverWeather);
			DrunkTime[x] = 0;
			ClearAnimations(x);
		}
	}
}

ptask CheckAFKTimer[1000](x){
	if(AFKTimer[x] > 0){
		AFKTimer[x]--;
		if(AFKTimer[x] <= 0){
			AFKTimer[x] = 0;
			IsAFK{x} = true;
			SetPlayerNameTag(x, x);
		}
	}
}

ptask CheckLogoutTimer[1000](x){
	if(CheckingLogout[x] == 1){
		new string[64];
		if(TimeCountLogout[x] > 0){
			TimeCountLogout[x]--;
			format(string, sizeof(string), "~n~~n~~y~Logout In %d seconds", TimeCountLogout[x]);
			GameTextForPlayer(x,string,1000,3);
		}
		else if(TimeCountLogout[x] == 0){
			CheckingLogout[x] = 0;
			TimeCountLogout[x] = 0;
			PlayerLogout(x);
		}
	}
}

ptask UpdateStatsVehicle[1000](playerid){
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER){
		new vehicleid = GetPlayerVehicleID(playerid);
		if(IsEngineVehicle(vehicleid) && GetEngineStatus(vehicleid)){
			if(!isABikeVehicle(vehicleid)){
				new carid = Car_GetID(vehicleid);
				if(carid != -1){
					if(fuel_interval[vehicleid] <= 0){
						CarData[carid][carFuel] -= 3;
						fuel_interval[vehicleid] = 180;

						if (CarData[carid][carFuel] >= 1 && CarData[carid][carFuel] <= 5){
							SendClientMessage(GetVehicleDriver(CarData[carid][carVehicle]), COLOR_RED, "[WARNING]:{FFFFFF} ยานพาหนะคันนี้เชื่อเพลิงใกล้หมดแล้ว คุณต้องไปที่ปั้มน้ำมัน!");
						}
					}
					else if(fuel_interval[vehicleid] > 0){
						fuel_interval[vehicleid] --;
					}

					if (CarData[carid][carFuel] <= 0){
						CarData[carid][carFuel] = 0;
						SetEngineStatus(CarData[carid][carVehicle], false);
					}
				}
			}

			new Float:fHealth;
			GetVehicleHealth(vehicleid, fHealth);
			if (fHealth < 310.0) {
				SetVehicleHealth(vehicleid, 310.0);
				SetEngineStatus(vehicleid, false);
				if(IsPlayerInVehicle(playerid, vehicleid)){
					if(TogVehSpeedo[playerid] == 0){
						PlayerTextDrawHide(playerid, VehSpeedo[playerid][9]);
						PlayerTextDrawColor(playerid, VehSpeedo[playerid][9], -1);
						PlayerTextDrawShow(playerid, VehSpeedo[playerid][9]);
					}
					SendNearbyMessage(playerid, 30.0, COLOR_RP, "** %s เครื่องยนต์หยุดทำงาน", ReturnRoleplayName(playerid));
				}
			}
		}
	}
}

Float:GetVehicleSpeed(vehicleid)
{
    new Float:V[3];
    GetVehicleVelocity(vehicleid, V[0], V[1], V[2]);
    return floatmul(floatsqroot(floatadd(floatadd(floatpower(V[0], 2), floatpower(V[1], 2)),  floatpower(V[2], 2))), 181.5);
}

ptask UpdateTimeVehHud[1000](playerid){
	if(!IsPlayerNPC(playerid)){
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER && !TogVehSpeedo[playerid] && !PlayerData[playerid][pJail] && !PlayerData[playerid][pInHospital]){
			new carid = PlayerCarGetID[playerid];
			if(!CoreVehicles[CarData[carid][carVehicle]][vehTemporary]){
				if(carid != -1){
					new Float:vehhp;
					GetVehicleHealth(CarData[carid][carVehicle], vehhp);

					if(IsEngineVehicle(CarData[carid][carVehicle]) && GetEngineStatus(CarData[carid][carVehicle])){
						PlayerTextDrawSetString(playerid, VehSpeedo[playerid][2], sprintf("%d KM/H", floatround(GetVehicleSpeed(CarData[carid][carVehicle]))));
					}
					if(vehhp > 0) SetPlayerProgressBarValue(playerid, VehSpeedoBar[playerid][1], vehhp);
					SetPlayerProgressBarValue(playerid, VehSpeedoBar[playerid][0], CarData[carid][carFuel]);
				}
			}
			else{
				new vehicleid = GetPlayerVehicleID(playerid);
				new Float:vehhp;
				GetVehicleHealth(vehicleid, vehhp);

				if(IsEngineVehicle(vehicleid) && GetEngineStatus(vehicleid)){
					PlayerTextDrawSetString(playerid, VehSpeedo[playerid][2], sprintf("%d KM/H", floatround(GetVehicleSpeed(vehicleid))));
				}
				if(vehhp > 0) SetPlayerProgressBarValue(playerid, VehSpeedoBar[playerid][1], vehhp);
				SetPlayerProgressBarValue(playerid, VehSpeedoBar[playerid][0], 0);
			}
		}
	}
}

ptask UpdateTimer[1000](x){
	if(TimeEnterInterior[x] > 0) TimeEnterInterior[x]--;
	if(PlayerData[x][pDelayWeapon][0] > 0) PlayerData[x][pDelayWeapon][0]--;
	if(PlayerData[x][pDelayWeapon][1] > 0) PlayerData[x][pDelayWeapon][1]--;
	if(PlayerData[x][pDelayWeapon][2] > 0) PlayerData[x][pDelayWeapon][2]--;
	if(TimeMute[x] > 0) TimeMute[x]--;
	if(DelayOOCandTW[x] > 0) DelayOOCandTW[x]--;
	if(DelayNewbie[x] > 0) DelayNewbie[x]--;
	if(PlayerDelayFlagWar[x] > 0) PlayerDelayFlagWar[x]--;

//	if(PlayerIsPickupCoinKathongTime[x] > 0) PlayerIsPickupCoinKathongTime[x]--;

	if (PlayerData[x][pStunned] > 0){
		PlayerData[x][pStunned]--;

		if (GetPlayerAnimationIndex(x) != 388)
			ApplyAnimation(x, "CRACK", "crckdeth4", 4.0, 0, 0, 0, 1, 0, 1);

		if (!PlayerData[x][pStunned]){
			TogglePlayerControllable(x, 1);
		}
	}

	if(CanFriskHome[x] != 0){
		if(CanFriskHomeTime[x] > 0) CanFriskHomeTime[x]--;
		if(CanFriskHomeTime[x] == 0) {
			CanFriskHome[x] = 0;
			CanFriskHomeTime[x] = 0;
		}
	}
}

forward CountTimeoutLogin(playerid);
public CountTimeoutLogin(playerid){
	if(!IsPlayerNPC(playerid)){
		if(PlayerTimeOutLogin[playerid] < 120){
			PlayerTimeOutLogin[playerid]++;
			StartPlayerCountTimeLogin[playerid] = SetTimerEx("CountTimeoutLogin", 1000, false, "i", playerid);
		}
		else if(PlayerTimeOutLogin[playerid] >= 120){
			ErrorMsg(playerid, "คุณไม่ได้ทำการเข้าสู่ระบบเป็นเวลา 120 วินาที ระบบจึงทำการเตะออกจากเซิฟเวอร์");
			KillTimer(StartPlayerCountTimeLogin[playerid]);
			PlayerTimeOutLogin[playerid] = 0;
			KickPlayer(playerid);
		}
	}
	return 1;
}

/*UpdateTimeHostServer(tmphour, tmpminute, tmpsecond, day, month, year){
	new hour = 23-tmphour, minute = 59-tmpminute, second = 59-tmpsecond;
	new stringhostname[128], stringtime[64], stringtext[128];

	new newhour[32], newminute[32], newsecond[32];

	if(second == 60) format(stringtime, sizeof stringtime, "%d:%d:00", hour, minute);
	else{
		if(hour >= 0 && hour <= 9) format(newhour, sizeof newhour, "0%d", hour);
		else format(newhour, sizeof newhour, "%d", hour);

		if(minute >= 0 && minute <= 9) format(newminute, sizeof newminute, "0%d", minute);
		else format(newminute, sizeof newminute, "%d", minute);

		if(second >= 0 && second <= 9) format(newsecond, sizeof newsecond, "0%d", second);
		else format(newsecond, sizeof newsecond, "%d", second);

		format(stringtime, sizeof stringtime, "%s:%s:%s", newhour, newminute, newsecond);
	}
	
	if(tmphour >= 0 && tmpminute >= 0 && tmpsecond >= 0 && day == 1, month == 1, year == 2022){
		format(stringtime, sizeof stringtime, "Happy New Year 2022", newhour, newminute, newsecond);
		format(stringtext, sizeof stringtext, "{FFF000}%s", stringtime);
		format(stringhostname, sizeof(stringhostname), "hostname %s | %s", SERVER_NAME, stringtime);
		SetDynamicObjectMaterialText(textnewyear, 0, stringtext, 50, "Calibri", 35, 1, 0x00000000, 0x00000000, 0);
	}else{
		format(stringhostname, sizeof(stringhostname), "hostname %s | %s", SERVER_NAME, stringtime);
		format(stringtext, sizeof stringtext, "{FFF000}%s", stringtime);
		SetDynamicObjectMaterialText(textnewyear, 0, stringtext, 50, "Calibri", 35, 1, 0x00000000, 0x00000000, 0);
	}
	
	SendRconCommand(stringhostname);
	return 1;
}*/

task SyncTime[1000](){
	new string[64];

	if(doorlabeltime > 0) doorlabeltime--;
	else if(doorlabeltime <= 0){
		MoveDynamicObject(doorlabel[0], 2497.447265, 2777.656250, 11.449273, 2.5, 0.000000, 0.000000, 90.000000);
		MoveDynamicObject(doorlabel[1], 2497.447265, 2768.803222, 11.449273, 2.5, 0.000000, 0.000000, 450.000000);
		doorlabelopen = false;
		doorlabeltime = 0;
	}

	if(timedoor24 > 0) timedoor24--;
	else if(timedoor24 <= 0){
		timedoor24 = 0;
		MoveDynamicObject(door24left[1], 1928.30774, -1776.53833, 13.56687, 2.5, 89.99999, 450.00000, -89.9999);
		MoveDynamicObject(door24right[1], 1928.30933, -1774.60168, 13.56687, 2.5, 89.99999, 450.00000, -89.99997);
	}

	new tmphour, tmpminute, tmpsecond;
	new year, month, day;
	gettime(tmphour, tmpminute, tmpsecond);
	getdate(year, month, day);

	//UpdateTimeHostServer(tmphour, tmpminute, tmpsecond, day, month, year);
	FixHour(tmphour);
	tmphour = shifthour;
	if ((tmphour > ghour) || (tmphour == 0 && ghour == 23)){
		format(string, sizeof(string), "Server: ขณะนี้เวลา %d.00 น.",tmphour);
		SendClientMessageToAll(COLOR_WHITE,string);
		ghour = tmphour;
		HourTime();

		for(new i=0; i<MAX_STORY_GANG; i++){
			if(Story_Gang[i][story_State] == 0) continue;
			if(Story_Gang[i][story_Mygang] == -1) continue;
			if(Story_Gang[i][story_Enemy] == -1) continue;

			if(Story_Gang[i][story_TimeHour]+1 == tmphour && Story_Gang[i][story_Days] == 0){
				if(!strcmp(Story_Gang[i][story_GangWinName], "NULL", true)){
					Story_Gang[i][story_State] = Story_Timeout;
					Story_Save(i);
					SendClientMessageToAllEx(0xFFAA01FF, "[สตอรี่แก๊ง]: สตอรี่ระหว่าง แก๊ง '%s' กับ แก๊ง '%s' ได้จบลงเนื่องจากหมดเวลาสตอรี่", Story_Gang[i][story_MygangName], Story_Gang[i][story_EnemyName]);
					Story_TimeoutState(i);
				}
			}
			if(Story_Gang[i][story_Days] > 0) Story_Gang[i][story_Days]--;
		}
	//====================================================================//

		if(tmphour == 0 && tmpminute == 0 && tmpsecond == 0){
			foreach(new i : Player){
				if(!LoggedIn[i]) continue;
				PlayerData[i][pMarryKissed] = 0;
				PlayerData[i][pRepairKitBuying] = 0;
				PlayerData[i][pBandageBuying] = 0;
			}
			mysql_tquery(dbCon, "UPDATE `characters` SET `MarryKissed` = '0'");
			mysql_tquery(dbCon, "UPDATE `characters` SET `RepairKitBuying` = '0'");
			mysql_tquery(dbCon, "UPDATE `characters` SET `BandageBuying` = '0'");
			SendClientMessageToAll(0xFFB1EFAA, "[คู่รัก]: คู่รักทุกคู่สามารถจูบเพื่อเพิ่มแต้มเลเวลของคู่รักกันได้แล้ว");
			CabaraIsOpen = true;
		}
		else if(tmphour == 0){
			SetWorldTime(5);
			SetWeather(0);
			CabaraIsOpen = true;
		}
		else if(tmphour == 1){
			SetWorldTime(5);
			SetWeather(0);
			CabaraIsOpen = true;
		}
		else if(tmphour == 2){
			SetWorldTime(5);
			SetWeather(0);
			CabaraIsOpen = true;
		}
		else if(tmphour == 3){
			SetWorldTime(5);
			SetWeather(0);
			CabaraIsOpen = false;
		}
		else if(tmphour == 4){
			SetWorldTime(5);
			SetWeather(0);
			CabaraIsOpen = false;
		}
		else if(tmphour == 5){
			SetWorldTime(5);
			SetWeather(0);
			CabaraIsOpen = false;
		}
		else if(tmphour == 6){
			SetWorldTime(5);
			SetWeather(0);
			CabaraIsOpen = false;
		}
		else if(tmphour == 7){
			//OpenFlagWar();
			SetWorldTime(7);
			SetWeather(0);
			CabaraIsOpen = false;
		}
		else if(tmphour == 8){
			//OpenFlagWar();
			SetWorldTime(8);
			SetWeather(0);
			CabaraIsOpen = false;
		}
		else if(tmphour == 9){
			//OpenFlagWar();
			SetWorldTime(9);
			SetWeather(0);
			CabaraIsOpen = false;
		}
		else if(tmphour == 10){
			//OpenFlagWar();
			SetWorldTime(10);
			SetWeather(0);
			CabaraIsOpen = false;
		}
		else if(tmphour == 11){
			SetWorldTime(11);
			SetWeather(0);
			CabaraIsOpen = false;
		}
		else if(tmphour == 12){
			SetWorldTime(12);
			SetWeather(0);
			CabaraIsOpen = true;
		}
		else if(tmphour == 13){
			SetWorldTime(13);
			SetWeather(0);
			CabaraIsOpen = true;
		} 
		else if(tmphour == 14){
			SetWorldTime(14);
			SetWeather(0);
			CabaraIsOpen = false;
		}
		else if(tmphour == 15){
			SetWorldTime(15);
			SetWeather(0);
			CabaraIsOpen = false;
		}
		else if(tmphour == 16){
			//OpenFlagWar();
			SetWorldTime(16);
			SetWeather(0);
			CabaraIsOpen = false;
		}
		else if(tmphour == 17){
			//OpenFlagWar();
			SetWorldTime(19);
			SetWeather(0);
			CabaraIsOpen = false;
		}
		else if(tmphour == 18){
			//OpenFlagWar();
			SetWorldTime(0);
			SetWeather(0);
			CabaraIsOpen = true;
		}
		else if(tmphour == 19){
			//OpenFlagWar();
			SetWorldTime(0);
			SetWeather(0);
			CabaraIsOpen = true;
		}
		else if(tmphour == 20){
			//OpenFlagWar();
			SetWorldTime(1);
			SetWeather(0);
			CabaraIsOpen = false;
		}
		else if(tmphour == 21){
			//OpenFlagWar();
			SetWorldTime(2);
			SetWeather(0);
			CabaraIsOpen = false;
		}
		else if(tmphour == 22){
			//OpenFlagWar();
			SetWorldTime(2);
			SetWeather(0);
			CabaraIsOpen = false;
		}
		else if(tmphour == 23){
			SetWorldTime(4);
			SetWeather(0);
			CabaraIsOpen = true;
		}
		else if(tmphour == 24){
			SetWorldTime(5);
			SetWeather(0);
			CabaraIsOpen = false;
		}
	}
}

//Party System
/*if(PlayerEnterCheckPoint[x] == 0 && EnterCheckPointJob[x] == 0)
	UpdatePlayerMarker(x);

if(PlayerInParty[x] && PlayerPartyGetID[x] != -1){
	new Float:hp;
	if(PartyData[PlayerPartyGetID[x]][partyMember][0] != -1){
		GetPlayerHealth(PartyData[PlayerPartyGetID[x]][partyMember][0], hp);
		SetPlayerProgressBarValue(x, PartyProgress[x][0], hp);
	}
	if(PartyData[PlayerPartyGetID[x]][partyMember][1] != -1){
		GetPlayerHealth(PartyData[PlayerPartyGetID[x]][partyMember][1], hp);
		SetPlayerProgressBarValue(x, PartyProgress[x][1], hp);
	}
	if(PartyData[PlayerPartyGetID[x]][partyMember][2] != -1){
		GetPlayerHealth(PartyData[PlayerPartyGetID[x]][partyMember][2], hp);
		SetPlayerProgressBarValue(x, PartyProgress[x][2], hp);
	}
	if(PartyData[PlayerPartyGetID[x]][partyMember][3] != -1){
		GetPlayerHealth(PartyData[PlayerPartyGetID[x]][partyMember][3], hp);
		SetPlayerProgressBarValue(x, PartyProgress[x][3], hp);
	}
	if(PartyData[PlayerPartyGetID[x]][partyMember][4] != -1){
		GetPlayerHealth(PartyData[PlayerPartyGetID[x]][partyMember][4], hp);
		SetPlayerProgressBarValue(x, PartyProgress[x][4], hp);
	}
}*/