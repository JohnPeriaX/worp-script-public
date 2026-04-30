#if defined _inc_impl
	#undef _inc_impl
#endif

Dialog:DIALOG_TYPE_MAIN(playerid, response, listitem, inputtext[])
{
	if(!response)
	{
		SetCameraBehindPlayer(playerid);
	}
	if(response)
	{
		switch(listitem)// Checking which list item was selected
		{
			case 0:// Paintjobs
			{
				Dialog_ShowEasy(playerid, DIALOG_TYPE_PAINTJOBS, DIALOG_STYLE_LIST, "Paintjobs", "Paint Job 1\nPaint Job 2\nPaint Job 3\n \nBack", "ตกลง", "ยกเลิก");
			}
			case 1: // colors
			{
				Dialog_ShowEasy(playerid, DIALOG_TYPE_COLORS, DIALOG_STYLE_INPUT, "เลือกสีที่ 1", "กรุณานำเลขสีที่ต้องการมาใส่:", "ตกลง", "กลับ");
			}
			case 2:{
				Dialog_ShowEasy(playerid, DIALOG_TYPE_COLORS2, DIALOG_STYLE_INPUT, "เลือกสีที่ 2", "กรุณานำเลขสีที่ต้องการมาใส่:", "ตกลง", "กลับ");
			}
			case 3: // Hoods
			{
				Dialog_ShowEasy(playerid, DIALOG_TYPE_HOODS, DIALOG_STYLE_LIST, "Hoods", "Fury\nChamp\nRace\nWorx\n \nBack", "ตกลง", "ยกเลิก");
			}
			case 4: // Vents
			{
				Dialog_ShowEasy(playerid, DIALOG_TYPE_VENTS, DIALOG_STYLE_LIST, "Vents", "Oval\nSquare\n \nBack", "ตกลง", "ยกเลิก");
			}
			case 5: // Lights
			{
				Dialog_ShowEasy(playerid, DIALOG_TYPE_LIGHTS, DIALOG_STYLE_LIST, "Lights", "Round\nSquare\n \nBack", "ตกลง", "ยกเลิก");
			}
			case 6: // Exhausts
			{
				Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
			}
			case 7: // Front Bumpers
			{
				Dialog_ShowEasy(playerid, DIALOG_TYPE_FBUMPS, DIALOG_STYLE_LIST,"Front Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow co. Chromer Bumper\nLow co. Slamin Bumper\n \nBack", "ตกลง", "ยกเลิก");
			}
			case 8: // Rear Bumpers
			{
				Dialog_ShowEasy(playerid, DIALOG_TYPE_RBUMPS, DIALOG_STYLE_LIST, "Rear Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow Co. Chromer Bumper\nLow Co. Slamin Bumper\n \nBack", "ตกลง", "ยกเลิก");
			}
			case 9: // Roofs
			{
				Dialog_ShowEasy(playerid, DIALOG_TYPE_ROOFS, DIALOG_STYLE_LIST, "Roofs", "Wheel Arc. Alien\nWheel Arc. X-Flow\nLow Co. Hardtop Roof\nLow Co. Softtop Roof\nTransfender Roof Scoop\n \nBack", "ตกลง", "ยกเลิก");
			}
			case 10: // Spoilers
			{
				Dialog_ShowEasy(playerid, DIALOG_TYPE_SPOILERS, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "ตกลง", "ยกเลิก");
			}
			case 11: // Side Skirts
			{
				Dialog_ShowEasy(playerid, DIALOG_TYPE_SIDESKIRTS, DIALOG_STYLE_LIST, "Side Skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n \nBack", "ตกลง", "ยกเลิก");
			}
			case 12: // Bullbars
			{
				Dialog_ShowEasy(playerid, DIALOG_TYPE_BULLBARS, DIALOG_STYLE_LIST, "Bullbars", "Locos Chrome Grill\nLocos Chrome Bars\nLocos Chrome Lights \nLocos Chrome Bullbar\n \nBack", "ตกลง", "ยกเลิก");
			}
			case 13: // Wheels
			{
				if(PlayerInventory_AllCount(playerid, "Wheel Car") < 4)
					return ErrorMsg(playerid, "คุณมี 'Wheel Car' ไม่พอ (4)");

				Dialog_ShowEasy(playerid, DIALOG_TYPE_WHEELS, DIALOG_STYLE_LIST, "Wheels", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nTrance\nShadow\nRimshine\nClassic\nCutter\nSwitch\nDollar\n \nBack", "ตกลง", "ยกเลิก");
			}
			case 14: // Car Stereo
			{
				Dialog_ShowEasy(playerid, DIALOG_TYPE_CSTEREO, DIALOG_STYLE_LIST, "Car Stereo", "Bass Boost\n \nBack", "ตกลง", "ยกเลิก");
			}
			case 15: // Hydraulics
			{
				Dialog_ShowEasy(playerid, DIALOG_TYPE_HYDRAULICS, DIALOG_STYLE_LIST, "Hydaulics", "Hydaulics\n \nBack", "ตกลง", "ยกเลิก");
			}
			case 16: // Nitrous Oxide
			{
				Dialog_ShowEasy(playerid, DIALOG_TYPE_NITRO, DIALOG_STYLE_LIST, "Nitrous Oxide", "2x Nitrous\n5x Nitrous\n10x Nitrous\n \nBack", "ตกลง", "ยกเลิก");
			}
		}
	}
	return 1;
}

Dialog:DIALOG_TYPE_NITRO(playerid, response, listitem, inputtext[])
{
	if(!response)
	{
		SetCameraBehindPlayer(playerid);
	}
	if(response)
	{
		switch(listitem)// Checking which list item was selected
		{
			case 0:
			{
				new car = GetPlayerVehicleID(playerid);
				AddVehicleComponent(car,1008);
				PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
				SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย ");
				Dialog_ShowEasy(playerid, DIALOG_TYPE_MAIN, DIALOG_STYLE_LIST, "Car Tuning Menu", "Paint Jobs\nColors1\nColors2\nHoods\nVents\nLights\nExhausts\nFront Bumpers\nRear Bumpers\nRoofs\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nHydraulics\nNitrous Oxide", "ตกลง", "ยกเลิก");

			}
			case 1:
			{
				new car = GetPlayerVehicleID(playerid);
				AddVehicleComponent(car,1009);
				PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
				SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
				Dialog_ShowEasy(playerid, DIALOG_TYPE_MAIN, DIALOG_STYLE_LIST, "Car Tuning Menu", "Paint Jobs\nColors1\nColors2\nHoods\nVents\nLights\nExhausts\nFront Bumpers\nRear Bumpers\nRoofs\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nHydraulics\nNitrous Oxide", "ตกลง", "ยกเลิก");

			}
			case 2:
			{
				new car = GetPlayerVehicleID(playerid);
				AddVehicleComponent(car,1010);
				PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
				SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
				Dialog_ShowEasy(playerid, DIALOG_TYPE_NITRO, DIALOG_STYLE_LIST, "Nitrous Oxide", "2x Nitrous\n5x Nitrous\n10x Nitrous\n \nBack", "ตกลง", "ยกเลิก");
			}
			case 3:
			{
				Dialog_ShowEasy(playerid, DIALOG_TYPE_NITRO, DIALOG_STYLE_LIST, "Nitrous Oxide", "2x Nitrous\n5x Nitrous\n10x Nitrous\n \nBack", "ตกลง", "ยกเลิก");
			}
			case 4:
			{
				Dialog_ShowEasy(playerid, DIALOG_TYPE_MAIN, DIALOG_STYLE_LIST, "Car Tuning Menu", "Paint Jobs\nColors1\nColors2\nHoods\nVents\nLights\nExhausts\nFront Bumpers\nRear Bumpers\nRoofs\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nHydraulics\nNitrous Oxide", "ตกลง", "ยกเลิก");
			}
		}
	}
	return 1;
}

Dialog:DIALOG_TYPE_HYDRAULICS(playerid, response, listitem, inputtext[])
{
	if(!response)
	{
		SetCameraBehindPlayer(playerid);
	}
	if(response)
	{
		switch(listitem)
		{
			case 0:
			{
				new car = GetPlayerVehicleID(playerid);
				AddVehicleComponent(car,1087);
				PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
				SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย ");
				Dialog_ShowEasy(playerid, DIALOG_TYPE_HYDRAULICS, DIALOG_STYLE_LIST, "Hydaulics", "Hydaulics\n \nBack", "ตกลง", "ยกเลิก");

			}
			case 1:
			{
				Dialog_ShowEasy(playerid, DIALOG_TYPE_HYDRAULICS, DIALOG_STYLE_LIST, "Hydaulics", "Hydaulics\n \nBack", "ตกลง", "ยกเลิก");
			}
			case 2:
			{
				Dialog_ShowEasy(playerid, DIALOG_TYPE_MAIN, DIALOG_STYLE_LIST, "Car Tuning Menu", "Paint Jobs\nColors1\nColors2\nHoods\nVents\nLights\nExhausts\nFront Bumpers\nRear Bumpers\nRoofs\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nHydraulics\nNitrous Oxide", "ตกลง", "ยกเลิก");
			}
		}
	}
	return 1;
}

Dialog:DIALOG_TYPE_CSTEREO(playerid, response, listitem, inputtext[])
{
	if(!response)
	{
		SetCameraBehindPlayer(playerid);
	}
	if(response)
	{
		switch(listitem)// Checking which list item was selected
		{
			case 0:
			{
				new car = GetPlayerVehicleID(playerid);
				AddVehicleComponent(car,1086);
				PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
				SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย ");
				Dialog_ShowEasy(playerid, DIALOG_TYPE_CSTEREO, DIALOG_STYLE_LIST, "Car Stereo", "Bass Boost\n \nBack", "ตกลง", "ยกเลิก");

			}
			case 1:
			{
				Dialog_ShowEasy(playerid, DIALOG_TYPE_CSTEREO, DIALOG_STYLE_LIST, "Car Stereo", "Bass Boost\n \nBack", "ตกลง", "ยกเลิก");
			}
			case 2:
			{
				Dialog_ShowEasy(playerid, DIALOG_TYPE_MAIN, DIALOG_STYLE_LIST, "Car Tuning Menu", "Paint Jobs\nColors1\nColors2\nHoods\nVents\nLights\nExhausts\nFront Bumpers\nRear Bumpers\nRoofs\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nHydraulics\nNitrous Oxide", "ตกลง", "ยกเลิก");
			}
		}
	}
	return 1;
}

Dialog:DIALOG_TYPE_WHEELS(playerid, response, listitem, inputtext[])
{
	if(!response)
	{
		SetCameraBehindPlayer(playerid);
	}
	if(response)
	{
		switch(listitem)// Checking which list item was selected
		{
			case 0:
			{
				new car = GetPlayerVehicleID(playerid);
				AddVehicleComponent(car,1025);
				PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
				SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
				Dialog_ShowEasy(playerid, DIALOG_TYPE_WHEELS, DIALOG_STYLE_LIST, "Wheels", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nTrance\nShadow\nRimshine\nClassic\nCutter\nSwitch\nDollar\n \nBack", "ตกลง", "ยกเลิก");

				PlayerInventory_Remove(playerid, "Wheel Car", 4);
			}
			case 1:
			{
				new car = GetPlayerVehicleID(playerid);
				AddVehicleComponent(car,1074);
				PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
				SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
				Dialog_ShowEasy(playerid, DIALOG_TYPE_WHEELS, DIALOG_STYLE_LIST, "Wheels", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nTrance\nShadow\nRimshine\nClassic\nCutter\nSwitch\nDollar\n \nBack", "ตกลง", "ยกเลิก");

				PlayerInventory_Remove(playerid, "Wheel Car", 4);
			}
			case 2:
			{
				new car = GetPlayerVehicleID(playerid);
				AddVehicleComponent(car,1076);
				PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
				SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
				Dialog_ShowEasy(playerid, DIALOG_TYPE_WHEELS, DIALOG_STYLE_LIST, "Wheels", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nTrance\nShadow\nRimshine\nClassic\nCutter\nSwitch\nDollar\n \nBack", "ตกลง", "ยกเลิก");

				PlayerInventory_Remove(playerid, "Wheel Car", 4);
			}
			case 3:
			{
				new car = GetPlayerVehicleID(playerid);
				AddVehicleComponent(car,1078);
				PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
				SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
				Dialog_ShowEasy(playerid, DIALOG_TYPE_WHEELS, DIALOG_STYLE_LIST, "Wheels", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nTrance\nShadow\nRimshine\nClassic\nCutter\nSwitch\nDollar\n \nBack", "ตกลง", "ยกเลิก");

				PlayerInventory_Remove(playerid, "Wheel Car", 4);
			}
			case 4:
			{
				new car = GetPlayerVehicleID(playerid);
				AddVehicleComponent(car,1081);
				PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
				SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
				Dialog_ShowEasy(playerid, DIALOG_TYPE_WHEELS, DIALOG_STYLE_LIST, "Wheels", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nTrance\nShadow\nRimshine\nClassic\nCutter\nSwitch\nDollar\n \nBack", "ตกลง", "ยกเลิก");

				PlayerInventory_Remove(playerid, "Wheel Car", 4);
			}
			case 5:
			{
				new car = GetPlayerVehicleID(playerid);
				AddVehicleComponent(car,1082);
				PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
				SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
				Dialog_ShowEasy(playerid, DIALOG_TYPE_WHEELS, DIALOG_STYLE_LIST, "Wheels", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nTrance\nShadow\nRimshine\nClassic\nCutter\nSwitch\nDollar\n \nBack", "ตกลง", "ยกเลิก");

				PlayerInventory_Remove(playerid, "Wheel Car", 4);
			}
			case 6:
			{
				new car = GetPlayerVehicleID(playerid);
				AddVehicleComponent(car,1085);
				PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
				SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
				Dialog_ShowEasy(playerid, DIALOG_TYPE_WHEELS, DIALOG_STYLE_LIST, "Wheels", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nTrance\nShadow\nRimshine\nClassic\nCutter\nSwitch\nDollar\n \nBack", "ตกลง", "ยกเลิก");

				PlayerInventory_Remove(playerid, "Wheel Car", 4);
			}
			case 7:
			{
				new car = GetPlayerVehicleID(playerid);
				AddVehicleComponent(car,1096);
				PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
				SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
				Dialog_ShowEasy(playerid, DIALOG_TYPE_WHEELS, DIALOG_STYLE_LIST, "Wheels", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nTrance\nShadow\nRimshine\nClassic\nCutter\nSwitch\nDollar\n \nBack", "ตกลง", "ยกเลิก");

				PlayerInventory_Remove(playerid, "Wheel Car", 4);
			}
			case 8:
			{
				new car = GetPlayerVehicleID(playerid);
				AddVehicleComponent(car,1097);
				PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
				SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
				Dialog_ShowEasy(playerid, DIALOG_TYPE_WHEELS, DIALOG_STYLE_LIST, "Wheels", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nTrance\nShadow\nRimshine\nClassic\nCutter\nSwitch\nDollar\n \nBack", "ตกลง", "ยกเลิก");

				PlayerInventory_Remove(playerid, "Wheel Car", 4);
			}
			case 9:
			{
				new car = GetPlayerVehicleID(playerid);
				AddVehicleComponent(car,1098);
				PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
				SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
				Dialog_ShowEasy(playerid, DIALOG_TYPE_WHEELS, DIALOG_STYLE_LIST, "Wheels", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nTrance\nShadow\nRimshine\nClassic\nCutter\nSwitch\nDollar\n \nBack", "ตกลง", "ยกเลิก");

				PlayerInventory_Remove(playerid, "Wheel Car", 4);
			}
			case 10:
			{
				new car = GetPlayerVehicleID(playerid);
				AddVehicleComponent(car,1084);
				PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
				SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
				Dialog_ShowEasy(playerid, DIALOG_TYPE_WHEELS, DIALOG_STYLE_LIST, "Wheels", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nTrance\nShadow\nRimshine\nClassic\nCutter\nSwitch\nDollar\n \nBack", "ตกลง", "ยกเลิก");

				PlayerInventory_Remove(playerid, "Wheel Car", 4);

			}
			case 11:
			{
				new car = GetPlayerVehicleID(playerid);
				AddVehicleComponent(car,1073);
				PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
				SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
				Dialog_ShowEasy(playerid, DIALOG_TYPE_WHEELS, DIALOG_STYLE_LIST, "Wheels", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nTrance\nShadow\nRimshine\nClassic\nCutter\nSwitch\nDollar\n \nBack", "ตกลง", "ยกเลิก");

				PlayerInventory_Remove(playerid, "Wheel Car", 4);
			}
			case 12:
			{
				new car = GetPlayerVehicleID(playerid);
				AddVehicleComponent(car,1075);
				PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
				SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
				Dialog_ShowEasy(playerid, DIALOG_TYPE_WHEELS, DIALOG_STYLE_LIST, "Wheels", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nTrance\nShadow\nRimshine\nClassic\nCutter\nSwitch\nDollar\n \nBack", "ตกลง", "ยกเลิก");

				PlayerInventory_Remove(playerid, "Wheel Car", 4);
			}
			case 13:
			{
				new car = GetPlayerVehicleID(playerid);
				AddVehicleComponent(car,1077);
				PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
				SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
				Dialog_ShowEasy(playerid, DIALOG_TYPE_WHEELS, DIALOG_STYLE_LIST, "Wheels", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nTrance\nShadow\nRimshine\nClassic\nCutter\nSwitch\nDollar\n \nBack", "ตกลง", "ยกเลิก");


				PlayerInventory_Remove(playerid, "Wheel Car", 4);
			}
			case 14:
			{
				new car = GetPlayerVehicleID(playerid);
				AddVehicleComponent(car,1079);
				PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
				SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
				Dialog_ShowEasy(playerid, DIALOG_TYPE_WHEELS, DIALOG_STYLE_LIST, "Wheels", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nTrance\nShadow\nRimshine\nClassic\nCutter\nSwitch\nDollar\n \nBack", "ตกลง", "ยกเลิก");

				PlayerInventory_Remove(playerid, "Wheel Car", 4);
			}
			case 15:
			{
				new car = GetPlayerVehicleID(playerid);
				AddVehicleComponent(car,1080);
				PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
				SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
				Dialog_ShowEasy(playerid, DIALOG_TYPE_WHEELS, DIALOG_STYLE_LIST, "Wheels", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nTrance\nShadow\nRimshine\nClassic\nCutter\nSwitch\nDollar\n \nBack", "ตกลง", "ยกเลิก");

				PlayerInventory_Remove(playerid, "Wheel Car", 4);
			}
			case 16:
			{
				new car = GetPlayerVehicleID(playerid);
				AddVehicleComponent(car,1083);
				PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
				SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
				Dialog_ShowEasy(playerid, DIALOG_TYPE_WHEELS, DIALOG_STYLE_LIST, "Wheels", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nTrance\nShadow\nRimshine\nClassic\nCutter\nSwitch\nDollar\n \nBack", "ตกลง", "ยกเลิก");

				PlayerInventory_Remove(playerid, "Wheel Car", 4);
			}
			case 17:
			{
				if(PlayerInventory_AllCount(playerid, "Wheel Car") < 4)
					return ErrorMsg(playerid, "คุณมี 'Wheel Car' ไม่พอ (4)");
					
				Dialog_ShowEasy(playerid, DIALOG_TYPE_WHEELS, DIALOG_STYLE_LIST, "Wheels", "Offroad\nMega\nWires\nTwist\nGrove\nImport\nAtomic\nAhab\nVirtual\nAccess\nTrance\nShadow\nRimshine\nClassic\nCutter\nSwitch\nDollar\n \nBack", "ตกลง", "ยกเลิก");
			}
			case 18:
			{
				Dialog_ShowEasy(playerid, DIALOG_TYPE_MAIN, DIALOG_STYLE_LIST, "Car Tuning Menu", "Paint Jobs\nColors1\nColors2\nHoods\nVents\nLights\nExhausts\nFront Bumpers\nRear Bumpers\nRoofs\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nHydraulics\nNitrous Oxide", "ตกลง", "ยกเลิก");
			}
		}
	}
	return 1;
}

Dialog:DIALOG_TYPE_BULLBARS(playerid, response, listitem, inputtext[])
{
	if(!response)
	{
		SetCameraBehindPlayer(playerid);
	}
	if(response)
	{
		switch(listitem)// Checking which list item was selected
		{
			case 0:
			{
			if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 534)

			{
				new car = GetPlayerVehicleID(playerid);
				if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 534) // Remington
				{
					AddVehicleComponent(car,1100);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_BULLBARS, DIALOG_STYLE_LIST, "Bullbars", "Locos Chrome Grill\nLocos Chrome Bars\nLocos Chrome Lights \nLocos Chrome Bullbar\n \nBack", "ตกลง", "ยกเลิก");
				}
				}
				else
				{
				SendClientMessage(playerid,COLOR_YELLOW,"คำเตือน!: ไม่สามารถแต่งกับยานพาหนะคันนี้ได้! ");
				Dialog_ShowEasy(playerid, DIALOG_TYPE_BULLBARS, DIALOG_STYLE_LIST, "Bullbars", "Locos Chrome Grill\nLocos Chrome Bars\nLocos Chrome Lights \nLocos Chrome Bullbar\n \nBack", "ตกลง", "ยกเลิก");
				}
			}
			case 1:
			{
			if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 534)

			{
				new car = GetPlayerVehicleID(playerid);
				if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 534) // Remington
				{
					AddVehicleComponent(car,1123);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_BULLBARS, DIALOG_STYLE_LIST, "Bullbars", "Locos Chrome Grill\nLocos Chrome Bars\nLocos Chrome Lights \nLocos Chrome Bullbar\n \nBack", "ตกลง", "ยกเลิก");
				}
				}
				else
				{
				SendClientMessage(playerid,COLOR_YELLOW,"คำเตือน!: ไม่สามารถแต่งกับยานพาหนะคันนี้ได้! ");
				Dialog_ShowEasy(playerid, DIALOG_TYPE_BULLBARS, DIALOG_STYLE_LIST, "Bullbars", "Locos Chrome Grill\nLocos Chrome Bars\nLocos Chrome Lights \nLocos Chrome Bullbar\n \nBack", "ตกลง", "ยกเลิก");
				}
			}
			case 2:
			{
			if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 534)

			{
				new car = GetPlayerVehicleID(playerid);
				if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 534) // Remington
				{
					AddVehicleComponent(car,1125);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_BULLBARS, DIALOG_STYLE_LIST, "Bullbars", "Locos Chrome Grill\nLocos Chrome Bars\nLocos Chrome Lights \nLocos Chrome Bullbar\n \nBack", "ตกลง", "ยกเลิก");
				}
				}
				else
				{
				SendClientMessage(playerid,COLOR_YELLOW,"คำเตือน!: ไม่สามารถแต่งกับยานพาหนะคันนี้ได้! ");
				Dialog_ShowEasy(playerid, DIALOG_TYPE_BULLBARS, DIALOG_STYLE_LIST, "Bullbars", "Locos Chrome Grill\nLocos Chrome Bars\nLocos Chrome Lights \nLocos Chrome Bullbar\n \nBack", "ตกลง", "ยกเลิก");
				}
			}
			case 3:
			{
			if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 535)

			{
				new car = GetPlayerVehicleID(playerid);
				if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 535) // Slamvan
				{
					AddVehicleComponent(car,1117);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_BULLBARS, DIALOG_STYLE_LIST, "Bullbars", "Locos Chrome Grill\nLocos Chrome Bars\nLocos Chrome Lights \nLocos Chrome Bullbar\n \nBack", "ตกลง", "ยกเลิก");
				}
				}
				else
				{
				SendClientMessage(playerid,COLOR_YELLOW,"คำเตือน!: ไม่สามารถแต่งกับยานพาหนะคันนี้ได้!");
				Dialog_ShowEasy(playerid, DIALOG_TYPE_BULLBARS, DIALOG_STYLE_LIST, "Bullbars", "Locos Chrome Grill\nLocos Chrome Bars\nLocos Chrome Lights \nLocos Chrome Bullbar\n \nBack", "ตกลง", "ยกเลิก");
				}
			}
			case 4:
			{
			Dialog_ShowEasy(playerid, DIALOG_TYPE_BULLBARS, DIALOG_STYLE_LIST, "Bullbars", "Locos Chrome Grill\nLocos Chrome Bars\nLocos Chrome Lights \nLocos Chrome Bullbar\n \nBack", "ตกลง", "ยกเลิก");
			}
			case 5:
			{
			Dialog_ShowEasy(playerid, DIALOG_TYPE_MAIN, DIALOG_STYLE_LIST, "Car Tuning Menu", "Paint Jobs\nColors1\nColors2\nHoods\nVents\nLights\nExhausts\nFront Bumpers\nRear Bumpers\nRoofs\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nHydraulics\nNitrous Oxide", "ตกลง", "ยกเลิก");
			}
		}
	}
	return 1;
}

Dialog:DIALOG_TYPE_SIDESKIRTS(playerid, response, listitem, inputtext[])
{
	if(!response)
	{
		SetCameraBehindPlayer(playerid);
	}
	if(response)
	{
		switch(listitem)// Checking which list item was selected
		{
			case 0:
			{
			if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 562 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 565 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 559 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 561 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 558 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 560)
			{

				new car = GetPlayerVehicleID(playerid);
				if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 562) // Elegy
				{
					AddVehicleComponent(car,1036);
					AddVehicleComponent(car,1040);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SIDESKIRTS, DIALOG_STYLE_LIST, "Side Skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n \nBack", "ตกลง", "ยกเลิก");
				}
				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 565) // Flash
				{
					AddVehicleComponent(car,1047);
					AddVehicleComponent(car,1051);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SIDESKIRTS, DIALOG_STYLE_LIST, "Side Skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n \nBack", "ตกลง", "ยกเลิก");
				}
				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 559) // Jester
				{
					AddVehicleComponent(car,1069);
					AddVehicleComponent(car,1071);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"[INFO] YComponent successfully added.");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SIDESKIRTS, DIALOG_STYLE_LIST, "Side Skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n \nBack", "ตกลง", "ยกเลิก");
				}
				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 561) // Stratum
				{
					AddVehicleComponent(car,1056);
					AddVehicleComponent(car,1062);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SIDESKIRTS, DIALOG_STYLE_LIST, "Side Skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n \nBack", "ตกลง", "ยกเลิก");
				}
				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 560) // Sultan
				{
					AddVehicleComponent(car,1026);
					AddVehicleComponent(car,1027);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SIDESKIRTS, DIALOG_STYLE_LIST, "Side Skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n \nBack", "ตกลง", "ยกเลิก");
				}
				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 558) // Uranus
				{
					AddVehicleComponent(car,1090);
					AddVehicleComponent(car,1094);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SIDESKIRTS, DIALOG_STYLE_LIST, "Side Skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n \nBack", "ตกลง", "ยกเลิก");
				}
				}
				else
				{
				SendClientMessage(playerid,COLOR_YELLOW,"คำเตือน!: ไม่สามารถแต่งกับยานพาหนะคันนี้ได้!");
				Dialog_ShowEasy(playerid, DIALOG_TYPE_SIDESKIRTS, DIALOG_STYLE_LIST, "Side Skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n \nBack", "ตกลง", "ยกเลิก");
				}
			}
			case 1:
			{
			if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 562 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 565 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 559 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 561 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 558 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 560)
			{


				new car = GetPlayerVehicleID(playerid);
				if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 562) // Elegy
				{
					AddVehicleComponent(car,1039);
					AddVehicleComponent(car,1041);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SIDESKIRTS, DIALOG_STYLE_LIST, "Side Skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n \nBack", "ตกลง", "ยกเลิก");
				}
				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 565) // Flash
				{
					AddVehicleComponent(car,1048);
					AddVehicleComponent(car,1052);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SIDESKIRTS, DIALOG_STYLE_LIST, "Side Skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n \nBack", "ตกลง", "ยกเลิก");
				}
				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 559) // Jetser
				{
					AddVehicleComponent(car,1070);
					AddVehicleComponent(car,1072);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SIDESKIRTS, DIALOG_STYLE_LIST, "Side Skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n \nBack", "ตกลง", "ยกเลิก");
				}
				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 561) // Stratum
				{
					AddVehicleComponent(car,1057);
					AddVehicleComponent(car,1063);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SIDESKIRTS, DIALOG_STYLE_LIST, "Side Skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n \nBack", "ตกลง", "ยกเลิก");
				}
				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 560) // Sultan
				{
					AddVehicleComponent(car,1031);
					AddVehicleComponent(car,1030);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SIDESKIRTS, DIALOG_STYLE_LIST, "Side Skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n \nBack", "ตกลง", "ยกเลิก");
				}
				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 558)  // Uranus
				{
					AddVehicleComponent(car,1093);
					AddVehicleComponent(car,1095);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SIDESKIRTS, DIALOG_STYLE_LIST, "Side Skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n \nBack", "ตกลง", "ยกเลิก");
				}
				}
				else
				{
				SendClientMessage(playerid,COLOR_YELLOW,"คำเตือน!: ไม่สามารถแต่งกับยานพาหนะคันนี้ได้!");
				Dialog_ShowEasy(playerid, DIALOG_TYPE_SIDESKIRTS, DIALOG_STYLE_LIST, "Side Skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n \nBack", "ตกลง", "ยกเลิก");
				}
			}
			case 2:
			{
			if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 575 ||
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 536 ||
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 576 ||
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 567)
				{
				new car = GetPlayerVehicleID(playerid);
				if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 575) // Brodway
				{
					AddVehicleComponent(car,1042);
					AddVehicleComponent(car,1099);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SIDESKIRTS, DIALOG_STYLE_LIST, "Side Skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n \nBack", "ตกลง", "ยกเลิก");
				}
				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 567) // Savanna
				{
					AddVehicleComponent(car,1102);
					AddVehicleComponent(car,1133);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SIDESKIRTS, DIALOG_STYLE_LIST, "Side Skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n \nBack", "ตกลง", "ยกเลิก");
				}
				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 576) // Tornado
				{
					AddVehicleComponent(car,1134);
					AddVehicleComponent(car,1137);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SIDESKIRTS, DIALOG_STYLE_LIST, "Side Skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n \nBack", "ตกลง", "ยกเลิก");
				}
				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 536) // Blade
				{
					AddVehicleComponent(car,1108);
					AddVehicleComponent(car,1107);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SIDESKIRTS, DIALOG_STYLE_LIST, "Side Skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n \nBack", "ตกลง", "ยกเลิก");
				}
				}
				else
				{
				SendClientMessage(playerid,COLOR_YELLOW,"คำเตือน!: ไม่สามารถแต่งกับยานพาหนะคันนี้ได้!");
				Dialog_ShowEasy(playerid, DIALOG_TYPE_SIDESKIRTS, DIALOG_STYLE_LIST, "Side Skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n \nBack", "ตกลง", "ยกเลิก");
				}
			}
			case 3:
			{
			if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 534 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 534)
			{
				new car = GetPlayerVehicleID(playerid);
				if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 534) // Remington
				{
					AddVehicleComponent(car,1122);
					AddVehicleComponent(car,1101);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SIDESKIRTS, DIALOG_STYLE_LIST, "Side Skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n \nBack", "ตกลง", "ยกเลิก");
				}
				}
				else
				{
				SendClientMessage(playerid,COLOR_YELLOW,"คำเตือน!: ไม่สามารถแต่งกับยานพาหนะคันนี้ได้!");
				Dialog_ShowEasy(playerid, DIALOG_TYPE_SIDESKIRTS, DIALOG_STYLE_LIST, "Side Skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n \nBack", "ตกลง", "ยกเลิก");
				}
			}
			case 4:
			{
			if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 534 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 534)
			{
				new car = GetPlayerVehicleID(playerid);
				if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 534) // Remington
				{
					AddVehicleComponent(car,1106);
					AddVehicleComponent(car,1124);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SIDESKIRTS, DIALOG_STYLE_LIST, "Side Skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n \nBack", "ตกลง", "ยกเลิก");
				}
				}
				else
				{
				SendClientMessage(playerid,COLOR_YELLOW,"คำเตือน!: ไม่สามารถแต่งกับยานพาหนะคันนี้ได้! ");
				Dialog_ShowEasy(playerid, DIALOG_TYPE_SIDESKIRTS, DIALOG_STYLE_LIST, "Side Skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n \nBack", "ตกลง", "ยกเลิก");
				}
			}
			case 5:
			{
			if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 535)

			{
				new car = GetPlayerVehicleID(playerid);
				if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 535) // Slamvan
				{
					AddVehicleComponent(car,1118);
					AddVehicleComponent(car,1120);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SIDESKIRTS, DIALOG_STYLE_LIST, "Side Skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n \nBack", "ตกลง", "ยกเลิก");
				}
				}
				else
				{
				SendClientMessage(playerid,COLOR_YELLOW,"คำเตือน!: ไม่สามารถแต่งกับยานพาหนะคันนี้ได้! ");
				Dialog_ShowEasy(playerid, DIALOG_TYPE_SIDESKIRTS, DIALOG_STYLE_LIST, "Side Skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n \nBack", "ตกลง", "ยกเลิก");
				}
			}
			case 6:
			{
			if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 535)

			{
				new car = GetPlayerVehicleID(playerid);
				if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 535) // Slamvan
				{
					AddVehicleComponent(car,1119);
					AddVehicleComponent(car,1121);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SIDESKIRTS, DIALOG_STYLE_LIST, "Side Skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n \nBack", "ตกลง", "ยกเลิก");
				}
				}
				else
				{
				SendClientMessage(playerid,COLOR_YELLOW,"คำเตือน!: ไม่สามารถแต่งกับยานพาหนะคันนี้ได้! ");
				Dialog_ShowEasy(playerid, DIALOG_TYPE_SIDESKIRTS, DIALOG_STYLE_LIST, "Side Skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n \nBack", "ตกลง", "ยกเลิก");
				}
			}
			case 7:
			{
			if(
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 401 ||
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 518 ||
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 527 ||
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 415 ||
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 589 ||
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 546 ||
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 517 ||
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 603 ||
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 436 ||
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 439 ||
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 580 ||
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 549 ||
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 477)
				{
					new car = GetPlayerVehicleID(playerid);
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 401)
					{
					AddVehicleComponent(car,1007);
					AddVehicleComponent(car,1017);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SIDESKIRTS, DIALOG_STYLE_LIST, "Side Skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 518)
					{
					AddVehicleComponent(car,1007);
					AddVehicleComponent(car,1017);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SIDESKIRTS, DIALOG_STYLE_LIST, "Side Skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 527)
					{
					AddVehicleComponent(car,1007);
					AddVehicleComponent(car,1017);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SIDESKIRTS, DIALOG_STYLE_LIST, "Side Skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 415)
					{
					AddVehicleComponent(car,1007);
					AddVehicleComponent(car,1017);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SIDESKIRTS, DIALOG_STYLE_LIST, "Side Skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 589)
					{
					AddVehicleComponent(car,1007);
					AddVehicleComponent(car,1017);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SIDESKIRTS, DIALOG_STYLE_LIST, "Side Skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 546)
					{
					AddVehicleComponent(car,1007);
					AddVehicleComponent(car,1017);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SIDESKIRTS, DIALOG_STYLE_LIST, "Side Skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 517)
					{
					AddVehicleComponent(car,1007);
					AddVehicleComponent(car,1017);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SIDESKIRTS, DIALOG_STYLE_LIST, "Side Skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 603)
					{
					AddVehicleComponent(car,1007);
					AddVehicleComponent(car,1017);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SIDESKIRTS, DIALOG_STYLE_LIST, "Side Skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 436)
					{
					AddVehicleComponent(car,1007);
					AddVehicleComponent(car,1017);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SIDESKIRTS, DIALOG_STYLE_LIST, "Side Skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 439)
					{
					AddVehicleComponent(car,1007);
					AddVehicleComponent(car,1017);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SIDESKIRTS, DIALOG_STYLE_LIST, "Side Skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 580)
					{
					AddVehicleComponent(car,1007);
					AddVehicleComponent(car,1017);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SIDESKIRTS, DIALOG_STYLE_LIST, "Side Skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 549)
					{
					AddVehicleComponent(car,1007);
					AddVehicleComponent(car,1017);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SIDESKIRTS, DIALOG_STYLE_LIST, "Side Skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 477)
					{
					AddVehicleComponent(car,1007);
					AddVehicleComponent(car,1017);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SIDESKIRTS, DIALOG_STYLE_LIST, "Side Skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n \nBack", "ตกลง", "ยกเลิก");
					}
				}
					else
					{
					SendClientMessage(playerid,COLOR_YELLOW,"คำเตือน!: ไม่สามารถแต่งกับยานพาหนะคันนี้ได้!");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SIDESKIRTS, DIALOG_STYLE_LIST, "Side Skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n \nBack", "ตกลง", "ยกเลิก");
					}
			}
			case 8:
			{
			Dialog_ShowEasy(playerid, DIALOG_TYPE_SIDESKIRTS, DIALOG_STYLE_LIST, "Side Skirts", "Wheel Arc. Alien Side Skirt\nWheel Arc. X-Flow Side Skirt\nLocos Chrome Strip\nLocos Chrome Flames\nLocos Chrome Arches \nLocos Chrome Trim\nLocos Wheelcovers\nTransfender Side Skirt\n \nBack", "ตกลง", "ยกเลิก");
			}
			case 9:
			{
			Dialog_ShowEasy(playerid, DIALOG_TYPE_MAIN, DIALOG_STYLE_LIST, "Car Tuning Menu", "Paint Jobs\nColors1\nColors2\nHoods\nVents\nLights\nExhausts\nFront Bumpers\nRear Bumpers\nRoofs\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nHydraulics\nNitrous Oxide", "ตกลง", "ยกเลิก");
			}
		}
	}
	return 1;
}

Dialog:DIALOG_TYPE_SPOILERS(playerid, response, listitem, inputtext[])
{
	if(!response)
	{
		SetCameraBehindPlayer(playerid);
	}
	if(response)
	{
		switch(listitem)// Checking which list item was selected
		{
			case 0:
			{
			if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 562 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 565 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 559 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 561 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 558 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 560)
			{

				new car = GetPlayerVehicleID(playerid);
				if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 562) // Elegy
				{
					AddVehicleComponent(car,1147);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SPOILERS, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "ตกลง", "ยกเลิก");
				}
				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 565) // Flash
				{
					AddVehicleComponent(car,1049);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SPOILERS, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "ตกลง", "ยกเลิก");
				}
				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 559) // Jester
				{
					AddVehicleComponent(car,1162);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SPOILERS, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "ตกลง", "ยกเลิก");
				}
				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 561) // Stratum
				{
					AddVehicleComponent(car,1158);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SPOILERS, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "ตกลง", "ยกเลิก");
				}
				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 560) // Sultan
				{
					AddVehicleComponent(car,1138);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SPOILERS, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "ตกลง", "ยกเลิก");
				}
				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 558) // Uranus
				{
					AddVehicleComponent(car,1164);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SPOILERS, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "ตกลง", "ยกเลิก");
				}
				}
				else
				{
				SendClientMessage(playerid,COLOR_YELLOW,"คำเตือน!: ไม่สามารถแต่งกับยานพาหนะคันนี้ได้!");
				Dialog_ShowEasy(playerid, DIALOG_TYPE_SPOILERS, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "ตกลง", "ยกเลิก");
				}
			}
			case 1:
			{
			if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 562 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 565 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 559 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 561 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 558 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 560)
			{


				new car = GetPlayerVehicleID(playerid);
				if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 562) // Elegy
				{
					AddVehicleComponent(car,1146);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SPOILERS, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "ตกลง", "ยกเลิก");
				}
				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 565) // Flash
				{
					AddVehicleComponent(car,1150);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SPOILERS, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "ตกลง", "ยกเลิก");
				}
				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 559) // Jetser
				{
					AddVehicleComponent(car,1158);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SPOILERS, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "ตกลง", "ยกเลิก");
				}
				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 561) // Stratum
				{
					AddVehicleComponent(car,1060);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SPOILERS, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "ตกลง", "ยกเลิก");
				}
				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 560) // Sultan
				{
					AddVehicleComponent(car,1139);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SPOILERS, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "ตกลง", "ยกเลิก");
				}
				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 558)  // Uranus
				{
					AddVehicleComponent(car,1163);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย.");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SPOILERS, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "ตกลง", "ยกเลิก");
				}
				}
				else
				{
				SendClientMessage(playerid,COLOR_YELLOW,"คำเตือน!: ไม่สามารถแต่งกับยานพาหนะคันนี้ได้!");
				Dialog_ShowEasy(playerid, DIALOG_TYPE_SPOILERS, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "ตกลง", "ยกเลิก");
				}
			}
			case 2:// Win
			{
			if(
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 401 ||//bravura
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 518 ||//buccaneer
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 527 ||//cadrona
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 415 ||//cheetah
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 546 ||//intruder
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 603 ||//phoenix
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 426 ||//premier
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 436 ||//previon
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 405 ||//sentinel
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 477 ||//stallion
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 580 ||//stafford
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 550 ||//sunrise
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 549)//tampa
				{
					new car = GetPlayerVehicleID(playerid);
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 401) // bravura
					{
					AddVehicleComponent(car,1001);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SPOILERS, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 518) // buccaneer
					{
					AddVehicleComponent(car,1001);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SPOILERS, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 527) // cadrona
					{
					AddVehicleComponent(car,1001);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SPOILERS, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 415) // cheetah
					{
					AddVehicleComponent(car,1001);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SPOILERS, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 546) // intruder
					{
					AddVehicleComponent(car,1001);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SPOILERS, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 603) // phoenix
					{
					AddVehicleComponent(car,1001);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SPOILERS, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 426) // premier
					{
					AddVehicleComponent(car,1001);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SPOILERS, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 436) // previon
					{
					AddVehicleComponent(car,1001);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SPOILERS, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 405) // sentinel
					{
					AddVehicleComponent(car,1001);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SPOILERS, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 477) // stallion
					{
					AddVehicleComponent(car,1001);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SPOILERS, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 580) // stafford
					{
					AddVehicleComponent(car,1001);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SPOILERS, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 550) // sunrise
					{
					AddVehicleComponent(car,1001);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SPOILERS, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 549) // tampa
					{
					AddVehicleComponent(car,1001);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SPOILERS, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "ตกลง", "ยกเลิก");
					}
				}
					else
					{
					SendClientMessage(playerid,COLOR_YELLOW,"คำเตือน!: ไม่สามารถแต่งกับยานพาหนะคันนี้ได้!");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SPOILERS, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "ตกลง", "ยกเลิก");
					}
			}
			case 3: // Fury
			{
					if(
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 518 ||//buccaneer
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 415 ||//cheetah
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 546 ||//intruder
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 517 ||//majestic
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 603 ||//phoenix
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 405 ||//sentinel
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 477 ||//stallion
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 580 ||//stafford
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 550 ||//sunrise
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 549)//tampa
				{
					new car = GetPlayerVehicleID(playerid);
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 518) // buccaneer
					{
					AddVehicleComponent(car,1023);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SPOILERS, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 415) // cheetah
					{
					AddVehicleComponent(car,1023);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SPOILERS, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 546) // intruder
					{
					AddVehicleComponent(car,1023);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SPOILERS, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 517) // majestic
					{
					AddVehicleComponent(car,1023);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SPOILERS, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 603) // phoenix
					{
					AddVehicleComponent(car,1023);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SPOILERS, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 405) // sentinel
					{
					AddVehicleComponent(car,1023);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SPOILERS, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 477) // stallion
					{
					AddVehicleComponent(car,1023);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SPOILERS, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 580) // stafford
					{
					AddVehicleComponent(car,1023);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SPOILERS, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 550) // sunrise
					{
					AddVehicleComponent(car,1023);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SPOILERS, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 549) // tampa
					{
					AddVehicleComponent(car,1023);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SPOILERS, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "ตกลง", "ยกเลิก");
					}
				}
					else
					{
					SendClientMessage(playerid,COLOR_YELLOW,"คำเตือน!: ไม่สามารถแต่งกับยานพาหนะคันนี้ได้!");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SPOILERS, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "ตกลง", "ยกเลิก");
					}
			}
			case 4: // Alpha
			{
					if(
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 518 ||//buccaneer
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 415 ||//cheetah
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 401 ||//bravura
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 517 ||//majestic
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 426 ||//premier
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 436 ||//previon
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 477 ||//stallion
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 547 ||//primo
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 550 ||//sunrise
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 549)//tampa
				{
					new car = GetPlayerVehicleID(playerid);
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 518) // buccaneer
					{
					AddVehicleComponent(car,1003);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SPOILERS, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 415) // cheetah
					{
					AddVehicleComponent(car,1003);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SPOILERS, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 401) // bravura
					{
					AddVehicleComponent(car,1003);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SPOILERS, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 517) // majestic
					{
					AddVehicleComponent(car,1003);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SPOILERS, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 426) // premier
					{
					AddVehicleComponent(car,1003);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SPOILERS, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 436) // previon
					{
					AddVehicleComponent(car,1003);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SPOILERS, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 477) // stallion
					{
					AddVehicleComponent(car,1003);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SPOILERS, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 547) // primo
					{
					AddVehicleComponent(car,1003);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SPOILERS, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 550) // sunrise
					{
					AddVehicleComponent(car,1003);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SPOILERS, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 549) // tampa
					{
					AddVehicleComponent(car,1003);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SPOILERS, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "ตกลง", "ยกเลิก");
					}
				}
					else
					{
					SendClientMessage(playerid,COLOR_YELLOW,"คำเตือน!: ไม่สามารถแต่งกับยานพาหนะคันนี้ได้!");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SPOILERS, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "ตกลง", "ยกเลิก");
					}
			}
			case 5: // Pro
			{
					if(
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 589 ||//club
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 492 ||//greenwood
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 547 ||//primo
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 405)//sentinel
				{
					new car = GetPlayerVehicleID(playerid);
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 518) // club
					{
					AddVehicleComponent(car,1000);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SPOILERS, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 492) // greenwood
					{
					AddVehicleComponent(car,1000);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SPOILERS, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 547) // primo
					{
					AddVehicleComponent(car,1000);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SPOILERS, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 405) // sentinel
					{
					AddVehicleComponent(car,1000);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SPOILERS, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "ตกลง", "ยกเลิก");
					}
				}
					else
					{
					SendClientMessage(playerid,COLOR_YELLOW,"คำเตือน!: ไม่สามารถแต่งกับยานพาหนะคันนี้ได้!");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SPOILERS, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "ตกลง", "ยกเลิก");
					}
			}
			case 6: // Champ
			{
					if(
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 527 ||//cadrona
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 542 ||//clover
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 405)//sentinel
				{
					new car = GetPlayerVehicleID(playerid);
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 527) // cadrona
					{
					AddVehicleComponent(car,1014);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SPOILERS, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 542) // clover
					{
					AddVehicleComponent(car,1014);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SPOILERS, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 405) // sentinel
					{
					AddVehicleComponent(car,1014);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SPOILERS, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "ตกลง", "ยกเลิก");
					}
				}
					else
					{
					SendClientMessage(playerid,COLOR_YELLOW,"คำเตือน!: ไม่สามารถแต่งกับยานพาหนะคันนี้ได้!");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SPOILERS, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "ตกลง", "ยกเลิก");
					}
			}
			case 7: // Race
			{
			if(
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 527 ||//cadrona
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 542)//clover
				{
					new car = GetPlayerVehicleID(playerid);
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 527) // cadrona
					{
					AddVehicleComponent(car,1014);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SPOILERS, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 542) // clover
					{
					AddVehicleComponent(car,1014);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SPOILERS, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "ตกลง", "ยกเลิก");
					}
				}
					else
					{
					SendClientMessage(playerid,COLOR_YELLOW,"คำเตือน!: ไม่สามารถแต่งกับยานพาหนะคันนี้ได้!");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SPOILERS, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "ตกลง", "ยกเลิก");
					}
			}
			case 8: // Drag
			{
			if(
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 546 ||//intruder
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 517)//majestic
				{
					new car = GetPlayerVehicleID(playerid);
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 546) // intruder
					{
					AddVehicleComponent(car,1002);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SPOILERS, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 517) // majestic
					{
					AddVehicleComponent(car,1002);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SPOILERS, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "ตกลง", "ยกเลิก");
					}
				}
					else
					{
					SendClientMessage(playerid,COLOR_YELLOW,"คำเตือน!: ไม่สามารถแต่งกับยานพาหนะคันนี้ได้!");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_SPOILERS, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "ตกลง", "ยกเลิก");
					}
			}
			case 9:
			{
			Dialog_ShowEasy(playerid, DIALOG_TYPE_SPOILERS, DIALOG_STYLE_LIST, "Spoilers", "Wheel Arc. Alien Spoiler\nWheel Arc. X-Flow Spoiler\nTransfender Win Spoiler\nTransfender Fury Spoiler\nTransfender Alpha Spoiler\nTransfender Pro Spoiler\nTransfender Champ Spoiler\nTransfender Race Spoiler\nTransfender Drag Spoiler\n \nBack", "ตกลง", "ยกเลิก");
			}
			case 10:
			{
			Dialog_ShowEasy(playerid, DIALOG_TYPE_MAIN, DIALOG_STYLE_LIST, "Car Tuning Menu", "Paint Jobs\nColors1\nColors2\nHoods\nVents\nLights\nExhausts\nFront Bumpers\nRear Bumpers\nRoofs\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nHydraulics\nNitrous Oxide", "ตกลง", "ยกเลิก");
			}
		}
	}
	return 1;
}

Dialog:DIALOG_TYPE_ROOFS(playerid, response, listitem, inputtext[])
{
	if(!response)
	{
		SetCameraBehindPlayer(playerid);
	}
	if(response)
	{
		switch(listitem)// Checking which list item was selected
		{
			case 0:
			{
				if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 562 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 565 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 559 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 561 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 558 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 560)
			{

				new car = GetPlayerVehicleID(playerid);
				if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 562) // Elegy
				{
					AddVehicleComponent(car,1038);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_ROOFS, DIALOG_STYLE_LIST, "Roofs", "Wheel Arc. Alien\nWheel Arc. X-Flow\nLow Co. Hardtop Roof\nLow Co. Softtop Roof\nTransfender Roof Scoop\n \nBack", "ตกลง", "ยกเลิก");
				}
					else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 565) // Flash
				{
					AddVehicleComponent(car,1054);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_ROOFS, DIALOG_STYLE_LIST, "Roofs", "Wheel Arc. Alien\nWheel Arc. X-Flow\nLow Co. Hardtop Roof\nLow Co. Softtop Roof\nTransfender Roof Scoop\n \nBack", "ตกลง", "ยกเลิก");
				}
					else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 559) // Jester
				{
					AddVehicleComponent(car,1067);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_ROOFS, DIALOG_STYLE_LIST, "Roofs", "Wheel Arc. Alien\nWheel Arc. X-Flow\nLow Co. Hardtop Roof\nLow Co. Softtop Roof\nTransfender Roof Scoop\n \nBack", "ตกลง", "ยกเลิก");
				}
					else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 561) // Stratum
				{
					AddVehicleComponent(car,1055);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_ROOFS, DIALOG_STYLE_LIST, "Roofs", "Wheel Arc. Alien\nWheel Arc. X-Flow\nLow Co. Hardtop Roof\nLow Co. Softtop Roof\nTransfender Roof Scoop\n \nBack", "ตกลง", "ยกเลิก");
				}
					else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 560) // Sultan
				{
					AddVehicleComponent(car,1032);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_ROOFS, DIALOG_STYLE_LIST, "Roofs", "Wheel Arc. Alien\nWheel Arc. X-Flow\nLow Co. Hardtop Roof\nLow Co. Softtop Roof\nTransfender Roof Scoop\n \nBack", "ตกลง", "ยกเลิก");
				}
					else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 558) // Uranus
				{
					AddVehicleComponent(car,1088);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_ROOFS, DIALOG_STYLE_LIST, "Roofs", "Wheel Arc. Alien\nWheel Arc. X-Flow\nLow Co. Hardtop Roof\nLow Co. Softtop Roof\nTransfender Roof Scoop\n \nBack", "ตกลง", "ยกเลิก");
				}
				}
					else
				{
				SendClientMessage(playerid,COLOR_YELLOW,"คำเตือน!: ไม่สามารถแต่งกับยานพาหนะคันนี้ได้!");
				Dialog_ShowEasy(playerid, DIALOG_TYPE_ROOFS, DIALOG_STYLE_LIST, "Roofs", "Wheel Arc. Alien\nWheel Arc. X-Flow\nLow Co. Hardtop Roof\nLow Co. Softtop Roof\nTransfender Roof Scoop\n \nBack", "ตกลง", "ยกเลิก");
				}
			}
			case 1:
			{
				if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 562 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 565 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 559 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 561 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 558 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 560)
			{


				new car = GetPlayerVehicleID(playerid);
				if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 562) // Elegy
				{
					AddVehicleComponent(car,1035);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_ROOFS, DIALOG_STYLE_LIST, "Roofs", "Wheel Arc. Alien\nWheel Arc. X-Flow\nLow Co. Hardtop Roof\nLow Co. Softtop Roof\nTransfender Roof Scoop\n \nBack", "ตกลง", "ยกเลิก");
				}
					else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 565) // Flash
				{
					AddVehicleComponent(car,1053);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_ROOFS, DIALOG_STYLE_LIST, "Roofs", "Wheel Arc. Alien\nWheel Arc. X-Flow\nLow Co. Hardtop Roof\nLow Co. Softtop Roof\nTransfender Roof Scoop\n \nBack", "ตกลง", "ยกเลิก");
				}
					else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 559) // Jetser
				{
					AddVehicleComponent(car,1068);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_ROOFS, DIALOG_STYLE_LIST, "Roofs", "Wheel Arc. Alien\nWheel Arc. X-Flow\nLow Co. Hardtop Roof\nLow Co. Softtop Roof\nTransfender Roof Scoop\n \nBack", "ตกลง", "ยกเลิก");
				}
					else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 561) // Stratum
				{
					AddVehicleComponent(car,1061);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_ROOFS, DIALOG_STYLE_LIST, "Roofs", "Wheel Arc. Alien\nWheel Arc. X-Flow\nLow Co. Hardtop Roof\nLow Co. Softtop Roof\nTransfender Roof Scoop\n \nBack", "ตกลง", "ยกเลิก");
				}
					else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 560) // Sultan
				{
					AddVehicleComponent(car,1033);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_ROOFS, DIALOG_STYLE_LIST, "Roofs", "Wheel Arc. Alien\nWheel Arc. X-Flow\nLow Co. Hardtop Roof\nLow Co. Softtop Roof\nTransfender Roof Scoop\n \nBack", "ตกลง", "ยกเลิก");
				}
					else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 558)  // Uranus
				{
					AddVehicleComponent(car,1091);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_ROOFS, DIALOG_STYLE_LIST, "Roofs", "Wheel Arc. Alien\nWheel Arc. X-Flow\nLow Co. Hardtop Roof\nLow Co. Softtop Roof\nTransfender Roof Scoop\n \nBack", "ตกลง", "ยกเลิก");
				}
				}
					else
				{
				SendClientMessage(playerid,COLOR_YELLOW,"คำเตือน!: ไม่สามารถแต่งกับยานพาหนะคันนี้ได้!");
				Dialog_ShowEasy(playerid, DIALOG_TYPE_ROOFS, DIALOG_STYLE_LIST, "Roofs", "Wheel Arc. Alien\nWheel Arc. X-Flow\nLow Co. Hardtop Roof\nLow Co. Softtop Roof\nTransfender Roof Scoop\n \nBack", "ตกลง", "ยกเลิก");
				}
			}
			case 2:
			{
				if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 567 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 536)
			{
				new car = GetPlayerVehicleID(playerid);
				if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 567) // Savanna
				{
					AddVehicleComponent(car,1130);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_ROOFS, DIALOG_STYLE_LIST, "Roofs", "Wheel Arc. Alien\nWheel Arc. X-Flow\nLow Co. Hardtop Roof\nLow Co. Softtop Roof\nTransfender Roof Scoop\n \nBack", "ตกลง", "ยกเลิก");
				}
					else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 536) // Blade
				{
					AddVehicleComponent(car,1128);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_ROOFS, DIALOG_STYLE_LIST, "Roofs", "Wheel Arc. Alien\nWheel Arc. X-Flow\nLow Co. Hardtop Roof\nLow Co. Softtop Roof\nTransfender Roof Scoop\n \nBack", "ตกลง", "ยกเลิก");
				}
				}
					else
				{
				SendClientMessage(playerid,COLOR_YELLOW,"คำเตือน!: ไม่สามารถแต่งกับยานพาหนะคันนี้ได้!");
				Dialog_ShowEasy(playerid, DIALOG_TYPE_ROOFS, DIALOG_STYLE_LIST, "Roofs", "Wheel Arc. Alien\nWheel Arc. X-Flow\nLow Co. Hardtop Roof\nLow Co. Softtop Roof\nTransfender Roof Scoop\n \nBack", "ตกลง", "ยกเลิก");
				}
			}
			case 3:
			{
				if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 567 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 536)
			{
				new car = GetPlayerVehicleID(playerid);
				if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 567) // Savanna
				{
					AddVehicleComponent(car,1131);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_ROOFS, DIALOG_STYLE_LIST, "Roofs", "Wheel Arc. Alien\nWheel Arc. X-Flow\nLow Co. Hardtop Roof\nLow Co. Softtop Roof\nTransfender Roof Scoop\n \nBack", "ตกลง", "ยกเลิก");
				}
					else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 536) // Blade
				{
					AddVehicleComponent(car,1103);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_ROOFS, DIALOG_STYLE_LIST, "Roofs", "Wheel Arc. Alien\nWheel Arc. X-Flow\nLow Co. Hardtop Roof\nLow Co. Softtop Roof\nTransfender Roof Scoop\n \nBack", "ตกลง", "ยกเลิก");
				}
				}
					else
				{
				SendClientMessage(playerid,COLOR_YELLOW,"คำเตือน!: ไม่สามารถแต่งกับยานพาหนะคันนี้ได้!");
				Dialog_ShowEasy(playerid, DIALOG_TYPE_ROOFS, DIALOG_STYLE_LIST, "Roofs", "Wheel Arc. Alien\nWheel Arc. X-Flow\nLow Co. Hardtop Roof\nLow Co. Softtop Roof\nTransfender Roof Scoop\n \nBack", "ตกลง", "ยกเลิก");
				}
			}
			case 4:
			{
				if(
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 401 ||
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 518 ||
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 589 ||
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 492 ||
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 546 ||
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 603 ||
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 426 ||
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 436 ||
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 580 ||
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 550||
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 477)
				{
					new car = GetPlayerVehicleID(playerid);
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 401)
					{
					AddVehicleComponent(car,1006);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_ROOFS, DIALOG_STYLE_LIST, "Roofs", "Wheel Arc. Alien\nWheel Arc. X-Flow\nLow Co. Hardtop Roof\nLow Co. Softtop Roof\nTransfender Roof Scoop\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 518)
					{
					AddVehicleComponent(car,1006);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_ROOFS, DIALOG_STYLE_LIST, "Roofs", "Wheel Arc. Alien\nWheel Arc. X-Flow\nLow Co. Hardtop Roof\nLow Co. Softtop Roof\nTransfender Roof Scoop\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 589)
					{
					AddVehicleComponent(car,1006);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_ROOFS, DIALOG_STYLE_LIST, "Roofs", "Wheel Arc. Alien\nWheel Arc. X-Flow\nLow Co. Hardtop Roof\nLow Co. Softtop Roof\nTransfender Roof Scoop\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 492)
					{
					AddVehicleComponent(car,1006);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_ROOFS, DIALOG_STYLE_LIST, "Roofs", "Wheel Arc. Alien\nWheel Arc. X-Flow\nLow Co. Hardtop Roof\nLow Co. Softtop Roof\nTransfender Roof Scoop\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 546)
					{
					AddVehicleComponent(car,1006);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_ROOFS, DIALOG_STYLE_LIST, "Roofs", "Wheel Arc. Alien\nWheel Arc. X-Flow\nLow Co. Hardtop Roof\nLow Co. Softtop Roof\nTransfender Roof Scoop\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 603)
					{
					AddVehicleComponent(car,1006);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_ROOFS, DIALOG_STYLE_LIST, "Roofs", "Wheel Arc. Alien\nWheel Arc. X-Flow\nLow Co. Hardtop Roof\nLow Co. Softtop Roof\nTransfender Roof Scoop\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 426)
					{
					AddVehicleComponent(car,1006);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_ROOFS, DIALOG_STYLE_LIST, "Roofs", "Wheel Arc. Alien\nWheel Arc. X-Flow\nLow Co. Hardtop Roof\nLow Co. Softtop Roof\nTransfender Roof Scoop\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 436)
					{
					AddVehicleComponent(car,1006);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_ROOFS, DIALOG_STYLE_LIST, "Roofs", "Wheel Arc. Alien\nWheel Arc. X-Flow\nLow Co. Hardtop Roof\nLow Co. Softtop Roof\nTransfender Roof Scoop\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 580)
					{
					AddVehicleComponent(car,1006);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_ROOFS, DIALOG_STYLE_LIST, "Roofs", "Wheel Arc. Alien\nWheel Arc. X-Flow\nLow Co. Hardtop Roof\nLow Co. Softtop Roof\nTransfender Roof Scoop\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 550)
					{
					AddVehicleComponent(car,1006);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_ROOFS, DIALOG_STYLE_LIST, "Roofs", "Wheel Arc. Alien\nWheel Arc. X-Flow\nLow Co. Hardtop Roof\nLow Co. Softtop Roof\nTransfender Roof Scoop\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 477)
					{
					AddVehicleComponent(car,1006);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_ROOFS, DIALOG_STYLE_LIST, "Roofs", "Wheel Arc. Alien\nWheel Arc. X-Flow\nLow Co. Hardtop Roof\nLow Co. Softtop Roof\nTransfender Roof Scoop\n \nBack", "ตกลง", "ยกเลิก");
					}
				}
					else
					{
					SendClientMessage(playerid,COLOR_YELLOW,"คำเตือน!: ไม่สามารถแต่งกับยานพาหนะคันนี้ได้!");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_ROOFS, DIALOG_STYLE_LIST, "Roofs", "Wheel Arc. Alien\nWheel Arc. X-Flow\nLow Co. Hardtop Roof\nLow Co. Softtop Roof\nTransfender Roof Scoop\n \nBack", "ตกลง", "ยกเลิก");
					}
			}
			case 5:
			{
				Dialog_ShowEasy(playerid, DIALOG_TYPE_ROOFS, DIALOG_STYLE_LIST, "Roofs", "Wheel Arc. Alien\nWheel Arc. X-Flow\nLow Co. Hardtop Roof\nLow Co. Softtop Roof\nTransfender Roof Scoop\n \nBack", "ตกลง", "ยกเลิก");
			}
			case 6:
			{
			Dialog_ShowEasy(playerid, DIALOG_TYPE_MAIN, DIALOG_STYLE_LIST, "Car Tuning Menu", "Paint Jobs\nColors1\nColors2\nHoods\nVents\nLights\nExhausts\nFront Bumpers\nRear Bumpers\nRoofs\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nHydraulics\nNitrous Oxide", "Enter", "Close");
			}
		}
	}
	return 1;
}

Dialog:DIALOG_TYPE_RBUMPS(playerid, response, listitem, inputtext[])
{
	if(!response)
	{
		SetCameraBehindPlayer(playerid);
	}
	if(response)
	{
		switch(listitem)// Checking which list item was selected
		{
			case 0:
			{
				if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 562 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 565 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 559 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 561 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 558 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 560)
			{

				new car = GetPlayerVehicleID(playerid);
				if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 562) // Elegy
				{
					AddVehicleComponent(car,1149);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_RBUMPS, DIALOG_STYLE_LIST, "Rear Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow Co. Chromer Bumper\nLow Co. Slamin Bumper\n \nBack", "ตกลง", "ยกเลิก");
				}
				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 565) // Flash
				{
					AddVehicleComponent(car,1150);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_RBUMPS, DIALOG_STYLE_LIST, "Rear Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow Co. Chromer Bumper\nLow Co. Slamin Bumper\n \nBack", "ตกลง", "ยกเลิก");
				}
				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 559) // Jester
				{
					AddVehicleComponent(car,1159);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_RBUMPS, DIALOG_STYLE_LIST, "Rear Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow Co. Chromer Bumper\nLow Co. Slamin Bumper\n \nBack", "ตกลง", "ยกเลิก");
				}
				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 561) // Stratum
				{
					AddVehicleComponent(car,1154);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_RBUMPS, DIALOG_STYLE_LIST, "Rear Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow Co. Chromer Bumper\nLow Co. Slamin Bumper\n \nBack", "ตกลง", "ยกเลิก");
				}
				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 560) // Sultan
				{
					AddVehicleComponent(car,1141);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_RBUMPS, DIALOG_STYLE_LIST, "Rear Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow Co. Chromer Bumper\nLow Co. Slamin Bumper\n \nBack", "ตกลง", "ยกเลิก");
				}
				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 558) // Uranus
				{
					AddVehicleComponent(car,1168);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_RBUMPS, DIALOG_STYLE_LIST, "Rear Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow Co. Chromer Bumper\nLow Co. Slamin Bumper\n \nBack", "ตกลง", "ยกเลิก");
				}
				}
				else
				{
				SendClientMessage(playerid,COLOR_YELLOW,"คำเตือน!: ไม่สามารถแต่งกับยานพาหนะคันนี้ได้!");
				Dialog_ShowEasy(playerid, DIALOG_TYPE_RBUMPS, DIALOG_STYLE_LIST, "Rear Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow Co. Chromer Bumper\nLow Co. Slamin Bumper\n \nBack", "ตกลง", "ยกเลิก");
				}
			}
			case 1:
			{
				if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 562 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 565 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 559 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 561 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 558 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 560)
			{


				new car = GetPlayerVehicleID(playerid);
				if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 562) // Elegy
				{
					AddVehicleComponent(car,1148);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_RBUMPS, DIALOG_STYLE_LIST, "Rear Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow Co. Chromer Bumper\nLow Co. Slamin Bumper\n \nBack", "ตกลง", "ยกเลิก");
				}
				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 565) // Flash
				{
					AddVehicleComponent(car,1151);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_RBUMPS, DIALOG_STYLE_LIST, "Rear Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow Co. Chromer Bumper\nLow Co. Slamin Bumper\n \nBack", "ตกลง", "ยกเลิก");
				}
				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 559) // Jetser
				{
					AddVehicleComponent(car,1161);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_RBUMPS, DIALOG_STYLE_LIST, "Rear Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow Co. Chromer Bumper\nLow Co. Slamin Bumper\n \nBack", "ตกลง", "ยกเลิก");
				}
				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 561) // Stratum
				{
					AddVehicleComponent(car,1156);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_RBUMPS, DIALOG_STYLE_LIST, "Rear Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow Co. Chromer Bumper\nLow Co. Slamin Bumper\n \nBack", "ตกลง", "ยกเลิก");
				}
				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 560) // Sultan
				{
					AddVehicleComponent(car,1140);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_RBUMPS, DIALOG_STYLE_LIST, "Rear Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow Co. Chromer Bumper\nLow Co. Slamin Bumper\n \nBack", "ตกลง", "ยกเลิก");
				}
				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 558)  // Uranus
				{
					AddVehicleComponent(car,1167);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_RBUMPS, DIALOG_STYLE_LIST, "Rear Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow Co. Chromer Bumper\nLow Co. Slamin Bumper\n \nBack", "ตกลง", "ยกเลิก");
				}
				}
				else
				{
				SendClientMessage(playerid,COLOR_YELLOW,"คำเตือน!: ไม่สามารถแต่งกับยานพาหนะคันนี้ได้!");
				Dialog_ShowEasy(playerid, DIALOG_TYPE_RBUMPS, DIALOG_STYLE_LIST, "Rear Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow Co. Chromer Bumper\nLow Co. Slamin Bumper\n \nBack", "ตกลง", "ยกเลิก");
				}
			}
			case 2:
			{
				if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 575 ||
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 534 ||
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 567 ||
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 536 ||
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 576 ||
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 535)
				{
					new car = GetPlayerVehicleID(playerid);
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 575) // Brodway
					{
						AddVehicleComponent(car,1176);
						PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
						SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
						Dialog_ShowEasy(playerid, DIALOG_TYPE_RBUMPS, DIALOG_STYLE_LIST, "Rear Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow Co. Chromer Bumper\nLow Co. Slamin Bumper\n \nBack", "ตกลง", "ยกเลิก");
					}
					else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 534)// Remington
					{
						AddVehicleComponent(car,1180);
						PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
						SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
						Dialog_ShowEasy(playerid, DIALOG_TYPE_RBUMPS, DIALOG_STYLE_LIST, "Rear Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow Co. Chromer Bumper\nLow Co. Slamin Bumper\n \nBack", "ตกลง", "ยกเลิก");
					}
					else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 567)// Savanna
					{
						AddVehicleComponent(car,1187);
						PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
						SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
						Dialog_ShowEasy(playerid, DIALOG_TYPE_RBUMPS, DIALOG_STYLE_LIST, "Rear Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow Co. Chromer Bumper\nLow Co. Slamin Bumper\n \nBack", "ตกลง", "ยกเลิก");
					}
					else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 536) // Blade
					{
						AddVehicleComponent(car,1184);
						PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
						SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
						Dialog_ShowEasy(playerid, DIALOG_TYPE_RBUMPS, DIALOG_STYLE_LIST, "Rear Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow Co. Chromer Bumper\nLow Co. Slamin Bumper\n \nBack", "ตกลง", "ยกเลิก");
					}
					else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 535) // Slamvan
					{
						AddVehicleComponent(car,1109);
						PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
						SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
						Dialog_ShowEasy(playerid, DIALOG_TYPE_RBUMPS, DIALOG_STYLE_LIST, "Rear Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow Co. Chromer Bumper\nLow Co. Slamin Bumper\n \nBack", "ตกลง", "ยกเลิก");
					}
					else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 576) // Tornado
					{
						AddVehicleComponent(car,1192);
						PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
						SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
						Dialog_ShowEasy(playerid, DIALOG_TYPE_RBUMPS, DIALOG_STYLE_LIST, "Rear Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow Co. Chromer Bumper\nLow Co. Slamin Bumper\n \nBack", "ตกลง", "ยกเลิก");
					}
				}
				else
				{
					SendClientMessage(playerid,COLOR_YELLOW,"คำเตือน!: ไม่สามารถแต่งกับยานพาหนะคันนี้ได้!");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_RBUMPS, DIALOG_STYLE_LIST, "Rear Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow Co. Chromer Bumper\nLow Co. Slamin Bumper\n \nBack", "ตกลง", "ยกเลิก");
				}
			}
			case 3:
			{
				if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 575 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 534 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 567 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 536 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 576 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 535)
			{
				new car = GetPlayerVehicleID(playerid);
				if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 575) // Brodway
				{
					AddVehicleComponent(car,1177);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_RBUMPS, DIALOG_STYLE_LIST, "Rear Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow Co. Chromer Bumper\nLow Co. Slamin Bumper\n \nBack", "ตกลง", "ยกเลิก");
				}
					else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 534)// Remington
				{
					AddVehicleComponent(car,1178);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_RBUMPS, DIALOG_STYLE_LIST, "Rear Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow Co. Chromer Bumper\nLow Co. Slamin Bumper\n \nBack", "ตกลง", "ยกเลิก");
				}
					else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 567)// Savanna
				{
					AddVehicleComponent(car,1186);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_RBUMPS, DIALOG_STYLE_LIST, "Rear Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow Co. Chromer Bumper\nLow Co. Slamin Bumper\n \nBack", "ตกลง", "ยกเลิก");
				}
					else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 536) // Blade
				{
					AddVehicleComponent(car,1183);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_RBUMPS, DIALOG_STYLE_LIST, "Rear Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow Co. Chromer Bumper\nLow Co. Slamin Bumper\n \nBack", "ตกลง", "ยกเลิก");
				}

					else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 535) // Slamvan
				{
					AddVehicleComponent(car,1110);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_RBUMPS, DIALOG_STYLE_LIST, "Rear Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow Co. Chromer Bumper\nLow Co. Slamin Bumper\n \nBack", "ตกลง", "ยกเลิก");
				}

					else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 576) // Tornado
				{
					AddVehicleComponent(car,1193);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_RBUMPS, DIALOG_STYLE_LIST, "Rear Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow Co. Chromer Bumper\nLow Co. Slamin Bumper\n \nBack", "ตกลง", "ยกเลิก");
				}

				}
					else
				{
				SendClientMessage(playerid,COLOR_YELLOW,"คำเตือน!: ไม่สามารถแต่งกับยานพาหนะคันนี้ได้!");
				Dialog_ShowEasy(playerid, DIALOG_TYPE_RBUMPS, DIALOG_STYLE_LIST, "Rear Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow Co. Chromer Bumper\nLow Co. Slamin Bumper\n \nBack", "ตกลง", "ยกเลิก");
				}
			}
			case 4:
			{
				Dialog_ShowEasy(playerid, DIALOG_TYPE_RBUMPS, DIALOG_STYLE_LIST, "Rear Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow Co. Chromer Bumper\nLow Co. Slamin Bumper\n \nBack", "ตกลง", "ยกเลิก");
			}
			case 5:
			{
				Dialog_ShowEasy(playerid, DIALOG_TYPE_MAIN, DIALOG_STYLE_LIST, "Car Tuning Menu", "Paint Jobs\nColors1\nColors2\nHoods\nVents\nLights\nExhausts\nFront Bumpers\nRear Bumpers\nRoofs\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nHydraulics\nNitrous Oxide", "Enter", "Close");
			}
		}
	}
	return 1;
}

Dialog:DIALOG_TYPE_FBUMPS(playerid, response, listitem, inputtext[])
{
	if(!response)
	{
		SetCameraBehindPlayer(playerid);
	}
	if(response)
	{
		switch(listitem)// Checking which list item was selected
		{
			case 0:
			{
				if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 562 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 565 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 559 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 561 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 558 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 560)
			{
				new car = GetPlayerVehicleID(playerid);
				if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 562) // Elegy
				{
					AddVehicleComponent(car,1171);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_FBUMPS, DIALOG_STYLE_LIST,"Front Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow co. Chromer Bumper\nLow co. Slamin Bumper\n \nBack", "ตกลง", "ยกเลิก");
				}
				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 565) // Flash
				{
					AddVehicleComponent(car,1153);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_FBUMPS, DIALOG_STYLE_LIST,"Front Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow co. Chromer Bumper\nLow co. Slamin Bumper\n \nBack", "ตกลง", "ยกเลิก");
				}
				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 559) // Jester
				{
					AddVehicleComponent(car,1160);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_FBUMPS, DIALOG_STYLE_LIST,"Front Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow co. Chromer Bumper\nLow co. Slamin Bumper\n \nBack", "ตกลง", "ยกเลิก");
				}
				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 561) // Stratum
				{
					AddVehicleComponent(car,1155);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_FBUMPS, DIALOG_STYLE_LIST,"Front Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow co. Chromer Bumper\nLow co. Slamin Bumper\n \nBack", "ตกลง", "ยกเลิก");
				}
				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 560) // Sultan
				{
					AddVehicleComponent(car,1169);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_FBUMPS, DIALOG_STYLE_LIST,"Front Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow co. Chromer Bumper\nLow co. Slamin Bumper\n \nBack", "ตกลง", "ยกเลิก");
				}
				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 558) // Uranus
				{
					AddVehicleComponent(car,1166);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_FBUMPS, DIALOG_STYLE_LIST,"Front Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow co. Chromer Bumper\nLow co. Slamin Bumper\n \nBack", "ตกลง", "ยกเลิก");
				}
				}
				else
				{
				SendClientMessage(playerid,COLOR_YELLOW,"คำเตือน!: ไม่สามารถแต่งกับยานพาหนะคันนี้ได้!");
				Dialog_ShowEasy(playerid, DIALOG_TYPE_FBUMPS, DIALOG_STYLE_LIST,"Front Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow co. Chromer Bumper\nLow co. Slamin Bumper\n \nBack", "ตกลง", "ยกเลิก");
				}
			}
			case 1:
			{
				if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 562 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 565 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 559 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 561 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 558 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 560)
			{

				new car = GetPlayerVehicleID(playerid);
				if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 562) // Elegy
				{
					AddVehicleComponent(car,1172);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_FBUMPS, DIALOG_STYLE_LIST,"Front Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow co. Chromer Bumper\nLow co. Slamin Bumper\n \nBack", "ตกลง", "ยกเลิก");
				}
				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 565) // Flash
				{
					AddVehicleComponent(car,1152);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_FBUMPS, DIALOG_STYLE_LIST,"Front Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow co. Chromer Bumper\nLow co. Slamin Bumper\n \nBack", "ตกลง", "ยกเลิก");
				}
				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 559) // Jetser
				{
					AddVehicleComponent(car,1173);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_FBUMPS, DIALOG_STYLE_LIST,"Front Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow co. Chromer Bumper\nLow co. Slamin Bumper\n \nBack", "ตกลง", "ยกเลิก");
				}
				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 561) // Stratum
				{
					AddVehicleComponent(car,1157);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_FBUMPS, DIALOG_STYLE_LIST,"Front Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow co. Chromer Bumper\nLow co. Slamin Bumper\n \nBack", "ตกลง", "ยกเลิก");
				}
				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 560) // Sultan
				{
					AddVehicleComponent(car,1170);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_FBUMPS, DIALOG_STYLE_LIST,"Front Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow co. Chromer Bumper\nLow co. Slamin Bumper\n \nBack", "ตกลง", "ยกเลิก");
				}
				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 558)  // Uranus
				{
					AddVehicleComponent(car,1165);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_FBUMPS, DIALOG_STYLE_LIST,"Front Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow co. Chromer Bumper\nLow co. Slamin Bumper\n \nBack", "ตกลง", "ยกเลิก");
				}
				}
				else
				{
				SendClientMessage(playerid,COLOR_YELLOW,"คำเตือน!: ไม่สามารถแต่งกับยานพาหนะคันนี้ได้!");
				Dialog_ShowEasy(playerid, DIALOG_TYPE_FBUMPS, DIALOG_STYLE_LIST,"Front Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow co. Chromer Bumper\nLow co. Slamin Bumper\n \nBack", "ตกลง", "ยกเลิก");
				}
			}
			case 2:
			{
				if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 575 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 534 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 567 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 536 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 576 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 535)
			{
				new car = GetPlayerVehicleID(playerid);
				if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 575) // Brodway
				{
					AddVehicleComponent(car,1174);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_FBUMPS, DIALOG_STYLE_LIST,"Front Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow co. Chromer Bumper\nLow co. Slamin Bumper\n \nBack", "ตกลง", "ยกเลิก");
				}
				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 534)// Remington
				{
					AddVehicleComponent(car,1179);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_FBUMPS, DIALOG_STYLE_LIST,"Front Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow co. Chromer Bumper\nLow co. Slamin Bumper\n \nBack", "ตกลง", "ยกเลิก");
				}
				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 567)// Savanna
				{
					AddVehicleComponent(car,1189);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_FBUMPS, DIALOG_STYLE_LIST,"Front Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow co. Chromer Bumper\nLow co. Slamin Bumper\n \nBack", "ตกลง", "ยกเลิก");
				}
				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 536) // Blade
				{
					AddVehicleComponent(car,1182);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_FBUMPS, DIALOG_STYLE_LIST,"Front Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow co. Chromer Bumper\nLow co. Slamin Bumper\n \nBack", "ตกลง", "ยกเลิก");
				}
				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 535) // Slamvan
				{
					AddVehicleComponent(car,1115);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_FBUMPS, DIALOG_STYLE_LIST,"Front Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow co. Chromer Bumper\nLow co. Slamin Bumper\n \nBack", "ตกลง", "ยกเลิก");
				}
				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 576) // Tornado
				{
					AddVehicleComponent(car,1191);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_FBUMPS, DIALOG_STYLE_LIST,"Front Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow co. Chromer Bumper\nLow co. Slamin Bumper\n \nBack", "ตกลง", "ยกเลิก");
				}
				}
				else
				{
				SendClientMessage(playerid,COLOR_YELLOW,"คำเตือน!: ไม่สามารถแต่งกับยานพาหนะคันนี้ได้!");
				Dialog_ShowEasy(playerid, DIALOG_TYPE_FBUMPS, DIALOG_STYLE_LIST,"Front Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow co. Chromer Bumper\nLow co. Slamin Bumper\n \nBack", "ตกลง", "ยกเลิก");
				}
			}
			case 3:
			{
				if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 575 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 534 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 567 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 535 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 536 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 576 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 576)
			{
				new car = GetPlayerVehicleID(playerid);
				if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 575) // Brodway
				{
					AddVehicleComponent(car,1175);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_FBUMPS, DIALOG_STYLE_LIST,"Front Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow co. Chromer Bumper\nLow co. Slamin Bumper\n \nBack", "ตกลง", "ยกเลิก");
				}
				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 534)// Remington
				{
					AddVehicleComponent(car,1185);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_FBUMPS, DIALOG_STYLE_LIST,"Front Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow co. Chromer Bumper\nLow co. Slamin Bumper\n \nBack", "ตกลง", "ยกเลิก");
				}
				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 567)// Savanna
				{
					AddVehicleComponent(car,1188);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_FBUMPS, DIALOG_STYLE_LIST,"Front Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow co. Chromer Bumper\nLow co. Slamin Bumper\n \nBack", "ตกลง", "ยกเลิก");
				}
				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 536) // Blade
				{
					AddVehicleComponent(car,1181);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_FBUMPS, DIALOG_STYLE_LIST,"Front Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow co. Chromer Bumper\nLow co. Slamin Bumper\n \nBack", "ตกลง", "ยกเลิก");
				}

				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 535) // Slamvan
				{
					AddVehicleComponent(car,1116);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_FBUMPS, DIALOG_STYLE_LIST,"Front Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow co. Chromer Bumper\nLow co. Slamin Bumper\n \nBack", "ตกลง", "ยกเลิก");
				}
				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 576) // Tornado
				{
					AddVehicleComponent(car,1190);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_FBUMPS, DIALOG_STYLE_LIST,"Front Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow co. Chromer Bumper\nLow co. Slamin Bumper\n \nBack", "ตกลง", "ยกเลิก");
				}

				}
				else
				{
				SendClientMessage(playerid,COLOR_YELLOW,"คำเตือน!: ไม่สามารถแต่งกับยานพาหนะคันนี้ได้!");
				Dialog_ShowEasy(playerid, DIALOG_TYPE_FBUMPS, DIALOG_STYLE_LIST,"Front Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow co. Chromer Bumper\nLow co. Slamin Bumper\n \nBack", "ตกลง", "ยกเลิก");
				}
			}
			case 4:
			{
			Dialog_ShowEasy(playerid, DIALOG_TYPE_FBUMPS, DIALOG_STYLE_LIST,"Front Bumpers", "Wheel Arc. Alien Bumper\nWheel Arc. X-Flow Bumper\nLow co. Chromer Bumper\nLow co. Slamin Bumper\n \nBack", "ตกลง", "ยกเลิก");
			}
			case 5:
			{
			Dialog_ShowEasy(playerid, DIALOG_TYPE_MAIN, DIALOG_STYLE_LIST, "Car Tuning Menu", "Paint Jobs\nColors1\nColors2\nHoods\nVents\nLights\nExhausts\nFront Bumpers\nRear Bumpers\nRoofs\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nHydraulics\nNitrous Oxide", "Enter", "Close");
			}
		}
	}
	return 1;
}

Dialog:DIALOG_TYPE_EXHAUSTS(playerid, response, listitem, inputtext[])
{
	if(!response)
	{
		SetCameraBehindPlayer(playerid);
	}
	if(response)
	{
		switch(listitem)
		{
			case 0:
			{
				if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 562 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 565 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 559 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 558 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 561 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 560)
			{
				new car = GetPlayerVehicleID(playerid);
				if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 562)
				{
					AddVehicleComponent(car,1034);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
				}
				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 565)
				{
					AddVehicleComponent(car,1046);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
				}
				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 559)
				{
					AddVehicleComponent(car,1065);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
				}
				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 561)
				{
					AddVehicleComponent(car,1064);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
				}
				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 560)
				{
					AddVehicleComponent(car,1028);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
				}
				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 558)
				{
					AddVehicleComponent(car,1089);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
				}
				}
				else
				{
				SendClientMessage(playerid,COLOR_YELLOW,"คำเตือน!: ไม่สามารถแต่งกับยานพาหนะคันนี้ได้!");
				Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
				}
			}
			case 1:
			{
				if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 562 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 565 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 559 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 561 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 558 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 560)

			{
				new car = GetPlayerVehicleID(playerid);
				if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 562)
				{
					AddVehicleComponent(car,1037);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
				}
				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 565)
				{
					AddVehicleComponent(car,1045);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
				}
				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 559)
				{
					AddVehicleComponent(car,1066);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
				}
				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 561)
				{
					AddVehicleComponent(car,1059);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
				}
				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 560)
				{
					AddVehicleComponent(car,1029);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
				}
				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 558)
				{
					AddVehicleComponent(car,1092);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
				}
				}
				else
				{
				SendClientMessage(playerid,COLOR_YELLOW,"คำเตือน!: ไม่สามารถแต่งกับยานพาหนะคันนี้ได้!");
				Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
				}
			}
			case 2:
			{
				if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 575 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 534 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 567 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 536 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 576 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 535)

			{
				new car = GetPlayerVehicleID(playerid);
				if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 575) // Brodway
				{
					AddVehicleComponent(car,1044);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
				}
				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 534)// Remington
				{
					AddVehicleComponent(car,1126);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
				}
				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 567)// Savanna
				{
					AddVehicleComponent(car,1129);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
				}
				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 536) // Blade
				{
					AddVehicleComponent(car,1104);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
				}
				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 535) // Slamvan
				{
					AddVehicleComponent(car,1113);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
				}
				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 576) // Tornado
				{
					AddVehicleComponent(car,1136);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
				}
				}
				else
				{
				SendClientMessage(playerid,COLOR_YELLOW,"คำเตือน!: ไม่สามารถแต่งกับยานพาหนะคันนี้ได้!");
				Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
				}
			}
			case 3:
			{
				if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 575 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 534 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 567 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 536 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 576 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 535)
			{
				new car = GetPlayerVehicleID(playerid);
				if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 575) // Brodway
				{
					AddVehicleComponent(car,1043);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
				}
				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 534)// Remington
				{
					AddVehicleComponent(car,1127);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
				}
				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 567)// Savanna
				{
					AddVehicleComponent(car,1132);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
				}
				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 536) // Blade
				{
					AddVehicleComponent(car,1105);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย.");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
				}

				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 535) // Slamvan
				{
					AddVehicleComponent(car,1114);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
				}

				else if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 576) // Tornado
				{
					AddVehicleComponent(car,1135);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
				}

				}
				else
				{
				SendClientMessage(playerid,COLOR_YELLOW,"คำเตือน!: ไม่สามารถแต่งกับยานพาหนะคันนี้ได้!");
				Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
				}
			}
			case 4:// Large
			{
				if(
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 401 ||//bravura
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 518 ||//buccaneer
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 527 ||//cadrona
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 542 ||//clover
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 589 ||//club
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 400 ||//landstalker
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 517 ||//majestic
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 603 ||//phoenix
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 426 ||//premier
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 547 ||//primo
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 405 ||//sentinel
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 580 ||//stafford
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 550 ||//sunrise
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 549 ||//tampa
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 477)//zr-350
				{
					new car = GetPlayerVehicleID(playerid);
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 401) // bravura
					{
					AddVehicleComponent(car,1020);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 518) // buccaneer
					{
					AddVehicleComponent(car,1020);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 527) // cadrona
					{
					AddVehicleComponent(car,1020);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 542) // clover
					{
					AddVehicleComponent(car,1020);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 589) // club
					{
					AddVehicleComponent(car,1020);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 400) // landstalker
					{
					AddVehicleComponent(car,1020);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 603) // phoenix
					{
					AddVehicleComponent(car,1020);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 436) // previon
					{
					AddVehicleComponent(car,1020);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 547) // primo
					{
					AddVehicleComponent(car,1020);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 405) // sentinel
					{
					AddVehicleComponent(car,1020);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 580) // stafford
					{
					AddVehicleComponent(car,1020);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 550) // sunrise
					{
					AddVehicleComponent(car,1020);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 549) // tampa
					{
					AddVehicleComponent(car,1020);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 477) // zr-350
					{
					AddVehicleComponent(car,1020);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 517) // majestic
					{
					AddVehicleComponent(car,1020);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
					}
				}
				else
					{
					SendClientMessage(playerid,COLOR_YELLOW,"คำเตือน!: ไม่สามารถแต่งกับยานพาหนะคันนี้ได้!");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
					}
			}
			case 5: // Medium
			{
					if(
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 527 ||//cadrona
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 542 ||//clover
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 400 ||//landstalker
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 426 ||//premier
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 436 ||//previon
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 547 ||//primo
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 405 ||//sentinel
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 477)//zr-350
				{
					new car = GetPlayerVehicleID(playerid);
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 527) // cadrona
					{
					AddVehicleComponent(car,1021);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 542) // clover
					{
					AddVehicleComponent(car,1021);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 400) // landstalker
					{
					AddVehicleComponent(car,1021);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 426) // premier
					{
					AddVehicleComponent(car,1021);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 436) // previon
					{
					AddVehicleComponent(car,1021);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 547) // primo
					{
					AddVehicleComponent(car,1021);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 405) // sentinel
					{
					AddVehicleComponent(car,1021);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 477) // zr350
					{
					AddVehicleComponent(car,1021);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
					}
				}
					else
					{
					SendClientMessage(playerid,COLOR_YELLOW,"คำเตือน!: ไม่สามารถแต่งกับยานพาหนะคันนี้ได้!");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
					}
			}
			case 6: // Small
			{
					if(
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 436)//previon
				{
					new car = GetPlayerVehicleID(playerid);
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 436) // previon
					{
					AddVehicleComponent(car,1022);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
					}
				}
					else
					{
					SendClientMessage(playerid,COLOR_YELLOW,"คำเตือน!: ไม่สามารถแต่งกับยานพาหนะคันนี้ได้!");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
					}
			}
			case 7: // Twin
			{
					if(
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 518 ||//buccaneer
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 415 ||//cheetah
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 542 ||//clover
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 546 ||//intruder
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 400 ||//landstalker
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 517 ||//majestic
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 603 ||//phoenix
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 426 ||//premier
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 436 ||//previon
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 547 ||//primo
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 405 ||//sentinel
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 550 ||//sunrise
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 549 ||//tampa
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 477)//zr-350
				{
					new car = GetPlayerVehicleID(playerid);
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 518) // buccaneer
					{
					AddVehicleComponent(car,1019);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 415) // cheetah
					{
					AddVehicleComponent(car,1019);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 542) // clover
					{
					AddVehicleComponent(car,1019);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 546) // intruder
					{
					AddVehicleComponent(car,1019);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 400) // landstalker
					{
					AddVehicleComponent(car,1019);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 517) // majestic
					{
					AddVehicleComponent(car,1019);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 603) // phoenix
					{
					AddVehicleComponent(car,1019);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 426) // premier
					{
					AddVehicleComponent(car,1019);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 436) // previon
					{
					AddVehicleComponent(car,1019);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 547) // primo
					{
					AddVehicleComponent(car,1019);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 405 ) // sentinel
					{
					AddVehicleComponent(car,1019);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 550) // sunrise
					{
					AddVehicleComponent(car,1019);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 549) // tampa
					{
					AddVehicleComponent(car,1019);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 477) // zr-350
					{
					AddVehicleComponent(car,1019);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
					}
				}
					else
					{
					SendClientMessage(playerid,COLOR_YELLOW,"คำเตือน!: ไม่สามารถแต่งกับยานพาหนะคันนี้ได้!");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
					}
			}
			case 8: // Upswept
			{
					if(
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 401 ||//bravura
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 518 ||//buccaneer
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 415 ||//cheetah
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 542 ||//clover
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 546 ||//intruder
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 400 ||//landstalker
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 517 ||//majestic
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 603 ||//phoenix
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 426 ||//premier
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 415 ||//cheetah
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 547 ||//primo
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 405 ||//sentinel
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 550 ||//sunrise
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 549 ||//tampa
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 477)//zr-350
				{
					new car = GetPlayerVehicleID(playerid);
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 415) // cheetah
					{
					AddVehicleComponent(car,1018);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 518) // buccaneer
					{
					AddVehicleComponent(car,1018);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 527) // cadrona
					{
					AddVehicleComponent(car,1018);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 542) // clover
					{
					AddVehicleComponent(car,1018);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 589) // club
					{
					AddVehicleComponent(car,1018);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 400) // landstalker
					{
					AddVehicleComponent(car,1018);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 603) // phoenix
					{
					AddVehicleComponent(car,1018);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 546) // intruder
					{
					AddVehicleComponent(car,1018);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 547) // primo
					{
					AddVehicleComponent(car,1018);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 405) // sentinel
					{
					AddVehicleComponent(car,1018);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 580) // stafford
					{
					AddVehicleComponent(car,1018);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 550) // sunrise
					{
					AddVehicleComponent(car,1018);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 549) // tampa
					{
					AddVehicleComponent(car,1018);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 477) // zr-350
					{
					AddVehicleComponent(car,1018);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 517) // majestic
					{
					AddVehicleComponent(car,1018);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
					}
				}
					else
					{
					SendClientMessage(playerid,COLOR_YELLOW,"คำเตือน!: ไม่สามารถแต่งกับยานพาหนะคันนี้ได้!");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
					}
			}
			case 9: // _
			{
			Dialog_ShowEasy(playerid, DIALOG_TYPE_EXHAUSTS, DIALOG_STYLE_LIST, "Exhausts", "Wheel Arc. Alien exhaust\nWheel Arc. X-Flow exhaust\nLow Co. Chromer exhaust\nLow Co. Slamin exhaust\nTransfender Large exhaust\nTransfender Medium exhaust\nTransfender Small exhaust\nTransfender Twin exhaust\nTransfender Upswept exhaust\n \nBack", "ตกลง", "ยกเลิก");
			}
			case 10: // Back
			{
			Dialog_ShowEasy(playerid, DIALOG_TYPE_MAIN, DIALOG_STYLE_LIST, "Car Tuning Menu", "Paint Jobs\nColors1\nColors2\nHoods\nVents\nLights\nExhausts\nFront Bumpers\nRear Bumpers\nRoofs\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nHydraulics\nNitrous Oxide", "Enter", "Close");
			}
		}
	}
	return 1;
}

Dialog:DIALOG_TYPE_LIGHTS(playerid, response, listitem, inputtext[])
{
	if(!response)
	{
		SetCameraBehindPlayer(playerid);
	}
	if(response)
	{
		switch(listitem)// Checking which list item was selected
		{
			case 0:// round
			{
				if(
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 401 ||//bravura
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 518 ||//buccaneer
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 589 ||//club
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 400 ||//landstalker
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 436 ||//previon
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 439)//stallion
				{
					new car = GetPlayerVehicleID(playerid);
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 401) // bravura
					{
					AddVehicleComponent(car,1013);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_LIGHTS, DIALOG_STYLE_LIST, "Lights", "Round\nSquare\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 518) // buccaneer
					{
					AddVehicleComponent(car,1013);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_LIGHTS, DIALOG_STYLE_LIST, "Lights", "Round\nSquare\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 589) // club
					{
					AddVehicleComponent(car,1013);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_LIGHTS, DIALOG_STYLE_LIST, "Lights", "Round\nSquare\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 400) // landstalker
					{
					AddVehicleComponent(car,1013);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_LIGHTS, DIALOG_STYLE_LIST, "Lights", "Round\nSquare\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 436) // previon
					{
					AddVehicleComponent(car,1013);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_LIGHTS, DIALOG_STYLE_LIST, "Lights", "Round\nSquare\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 439) // stallion
					{
					AddVehicleComponent(car,1013);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_LIGHTS, DIALOG_STYLE_LIST, "Lights", "Round\nSquare\n \nBack", "ตกลง", "ยกเลิก");
					}
				}
				else
					{
					SendClientMessage(playerid,COLOR_YELLOW,"คำเตือน!: ไม่สามารถแต่งกับยานพาหนะคันนี้ได้!");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_LIGHTS, DIALOG_STYLE_LIST, "Lights", "Round\nSquare\n \nBack", "ตกลง", "ยกเลิก");
					}
			}
			case 1: // Square
			{
				if(
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 589 ||//club
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 603 ||//phoenix
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 400)//landstalker
				{
					new car = GetPlayerVehicleID(playerid);
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 589) // club
					{
					AddVehicleComponent(car,1024);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_VENTS, DIALOG_STYLE_LIST, "Vents", "Oval\nSquare\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 603) // phoenix
					{
					AddVehicleComponent(car,1024);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_VENTS, DIALOG_STYLE_LIST, "Vents", "Oval\nSquare\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 400) // landstalker
					{
					AddVehicleComponent(car,1024);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_VENTS, DIALOG_STYLE_LIST, "Vents", "Oval\nSquare\n \nBack", "ตกลง", "ยกเลิก");
					}
				}
				else
					{
					SendClientMessage(playerid,COLOR_YELLOW,"คำเตือน!: ไม่สามารถแต่งกับยานพาหนะคันนี้ได้!");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_LIGHTS, DIALOG_STYLE_LIST, "Lights", "Round\nSquare\n \nBack", "ตกลง", "ยกเลิก");
					}
			}
			case 2: // _
			{
			Dialog_ShowEasy(playerid, DIALOG_TYPE_LIGHTS, DIALOG_STYLE_LIST, "Lights", "Round\nSquare\n \nBack", "ตกลง", "ยกเลิก");
			}
			case 3: // Back
			{
			Dialog_ShowEasy(playerid, DIALOG_TYPE_MAIN, DIALOG_STYLE_LIST, "Car Tuning Menu", "Paint Jobs\nColors1\nColors2\nHoods\nVents\nLights\nExhausts\nFront Bumpers\nRear Bumpers\nRoofs\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nHydraulics\nNitrous Oxide", "ตกลง", "ยกเลิก");
			}
		}
	}
	return 1;
}

Dialog:DIALOG_TYPE_VENTS(playerid, response, listitem, inputtext[])
{
	if(!response)
	{
		SetCameraBehindPlayer(playerid);
	}
	if(response)
	{
		switch(listitem)// Checking which list item was selected
		{
			case 0:// Oval
			{
				if(
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 401 ||//bravura
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 518 ||//buccaneer
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 546 ||//intruder
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 517 ||//majestic
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 603 ||//phoenix
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 547 ||//primo
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 439 ||//stallion
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 550 ||//sunrise
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 549)//tampa
				{
					new car = GetPlayerVehicleID(playerid);
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 401) // bravura
					{
					AddVehicleComponent(car,1142);
					AddVehicleComponent(car,1143);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_VENTS, DIALOG_STYLE_LIST, "Vents", "Oval\nSquare\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 518) // buccaneer
					{
					AddVehicleComponent(car,1142);
					AddVehicleComponent(car,1143);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_VENTS, DIALOG_STYLE_LIST, "Vents", "Oval\nSquare\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 546) // intruder
					{
					AddVehicleComponent(car,1142);
					AddVehicleComponent(car,1143);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_VENTS, DIALOG_STYLE_LIST, "Vents", "Oval\nSquare\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 517) // majestic
					{
					AddVehicleComponent(car,1142);
					AddVehicleComponent(car,1143);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_VENTS, DIALOG_STYLE_LIST, "Vents", "Oval\nSquare\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 603) // phoenix
					{
					AddVehicleComponent(car,1142);
					AddVehicleComponent(car,1143);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_VENTS, DIALOG_STYLE_LIST, "Vents", "Oval\nSquare\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 547) // primo
					{
					AddVehicleComponent(car,1142);
					AddVehicleComponent(car,1143);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_VENTS, DIALOG_STYLE_LIST, "Vents", "Oval\nSquare\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 439) // stallion
					{
					AddVehicleComponent(car,1142);
					AddVehicleComponent(car,1143);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_VENTS, DIALOG_STYLE_LIST, "Vents", "Oval\nSquare\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 550) // sunrise
					{
					AddVehicleComponent(car,1142);
					AddVehicleComponent(car,1143);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_VENTS, DIALOG_STYLE_LIST, "Vents", "Oval\nSquare\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 549) // tampa
					{
					AddVehicleComponent(car,1142);
					AddVehicleComponent(car,1143);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_VENTS, DIALOG_STYLE_LIST, "Vents", "Oval\nSquare\n \nBack", "ตกลง", "ยกเลิก");
					}
				}
				else
					{
						SendClientMessage(playerid,COLOR_YELLOW,"คำเตือน!: ไม่สามารถแต่งกับยานพาหนะคันนี้ได้!");
						Dialog_ShowEasy(playerid, DIALOG_TYPE_VENTS, DIALOG_STYLE_LIST, "Vents", "Oval\nSquare\n \nBack", "ตกลง", "ยกเลิก");
					}
			}
			case 1: // Square
			{
			if(
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 401 ||//bravura
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 518 ||//buccaneer
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 589 ||//club
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 546 ||//intruder
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 517 ||//majestic
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 603 ||//phoenix
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 439 ||//stallion
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 550 ||//sunrise
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 549)//tampa
				{
					new car = GetPlayerVehicleID(playerid);
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 401) // bravura
					{
					AddVehicleComponent(car,1144);
					AddVehicleComponent(car,1145);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_VENTS, DIALOG_STYLE_LIST, "Vents", "Oval\nSquare\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 518) // buccaneer
					{
					AddVehicleComponent(car,1144);
					AddVehicleComponent(car,1145);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_VENTS, DIALOG_STYLE_LIST, "Vents", "Oval\nSquare\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 589) // club
					{
					AddVehicleComponent(car,1144);
					AddVehicleComponent(car,1145);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_VENTS, DIALOG_STYLE_LIST, "Vents", "Oval\nSquare\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 546) // intruder
					{
					AddVehicleComponent(car,1144);
					AddVehicleComponent(car,1145);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_VENTS, DIALOG_STYLE_LIST, "Vents", "Oval\nSquare\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 517) // majestic
					{
					AddVehicleComponent(car,1144);
					AddVehicleComponent(car,1145);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_VENTS, DIALOG_STYLE_LIST, "Vents", "Oval\nSquare\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 603) // phoenix
					{
					AddVehicleComponent(car,1144);
					AddVehicleComponent(car,1145);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_VENTS, DIALOG_STYLE_LIST, "Vents", "Oval\nSquare\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 439) // stallion
					{
					AddVehicleComponent(car,1144);
					AddVehicleComponent(car,1145);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_VENTS, DIALOG_STYLE_LIST, "Vents", "Oval\nSquare\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 550) // sunrise
					{
					AddVehicleComponent(car,1144);
					AddVehicleComponent(car,1145);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_VENTS, DIALOG_STYLE_LIST, "Vents", "Oval\nSquare\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 549) // tampa
					{
					AddVehicleComponent(car,1144);
					AddVehicleComponent(car,1145);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_VENTS, DIALOG_STYLE_LIST, "Vents", "Oval\nSquare\n \nBack", "ตกลง", "ยกเลิก");
					}
				}
					else
					{
					SendClientMessage(playerid,COLOR_YELLOW,"คำเตือน!: ไม่สามารถแต่งกับยานพาหนะคันนี้ได้!");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_VENTS, DIALOG_STYLE_LIST, "Vents", "Oval\nSquare\n \nBack", "ตกลง", "ยกเลิก");
					}
			}
			case 2: // _
			{
			Dialog_ShowEasy(playerid, DIALOG_TYPE_VENTS, DIALOG_STYLE_LIST, "Vents", "Oval\nSquare\n \nBack", "ตกลง", "ยกเลิก");
			}
			case 3: // Back
			{
			Dialog_ShowEasy(playerid, DIALOG_TYPE_MAIN, DIALOG_STYLE_LIST, "Car Tuning Menu", "Paint Jobs\nColors1\nColors2\nHoods\nVents\nLights\nExhausts\nFront Bumpers\nRear Bumpers\nRoofs\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nHydraulics\nNitrous Oxide", "ตกลง", "ยกเลิก");
			}
		}
	}
	return 1;
}

Dialog:DIALOG_TYPE_HOODS(playerid, response, listitem, inputtext[])
{
	if(!response)
	{
		SetCameraBehindPlayer(playerid);
	}
	if(response)
	{
		switch(listitem)// Checking which list item was selected
		{
			case 0:// fury
			{
				if(
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 401 ||
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 518 ||
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 589 ||
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 492 ||
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 426 ||
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 550)
				{
					new car = GetPlayerVehicleID(playerid);
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 401) // bravura
					{
					AddVehicleComponent(car,1005);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_HOODS, DIALOG_STYLE_LIST, "Hoods", "Fury\nChamp\nRace\nWorx\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 518) // buccaneer
					{
					AddVehicleComponent(car,1005);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_HOODS, DIALOG_STYLE_LIST, "Hoods", "Fury\nChamp\nRace\nWorx\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 589) // club
					{
					AddVehicleComponent(car,1005);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_HOODS, DIALOG_STYLE_LIST, "Hoods", "Fury\nChamp\nRace\nWorx\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 492) // greenwood
					{
					AddVehicleComponent(car,1005);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_HOODS, DIALOG_STYLE_LIST, "Hoods", "Fury\nChamp\nRace\nWorx\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 426) // premier
					{
					AddVehicleComponent(car,1005);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_HOODS, DIALOG_STYLE_LIST, "Hoods", "Fury\nChamp\nRace\nWorx\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 550) // sunrise
					{
					AddVehicleComponent(car,1005);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_HOODS, DIALOG_STYLE_LIST, "Hoods", "Fury\nChamp\nRace\nWorx\n \nBack", "ตกลง", "ยกเลิก");
					}
				}
				else
				{
				SendClientMessage(playerid,COLOR_YELLOW,"คำเตือน!: ไม่สามารถแต่งกับยานพาหนะคันนี้ได้!");
				Dialog_ShowEasy(playerid, DIALOG_TYPE_HOODS, DIALOG_STYLE_LIST, "Hoods", "Fury\nChamp\nRace\nWorx\n \nBack", "ตกลง", "ยกเลิก");
				}
			}
			case 1: // Champ
			{
			if(
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 401 ||
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 492 ||
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 546 ||
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 426 ||
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 550)
				{
					new car = GetPlayerVehicleID(playerid);
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 401) // bravura
					{
					AddVehicleComponent(car,1004);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_HOODS, DIALOG_STYLE_LIST, "Hoods", "Fury\nChamp\nRace\nWorx\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 546) // intruder
					{
					AddVehicleComponent(car,1004);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_HOODS, DIALOG_STYLE_LIST, "Hoods", "Fury\nChamp\nRace\nWorx\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 492) // greenwood
					{
					AddVehicleComponent(car,1004);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_HOODS, DIALOG_STYLE_LIST, "Hoods", "Fury\nChamp\nRace\nWorx\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 426) // premier
					{
					AddVehicleComponent(car,1004);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_HOODS, DIALOG_STYLE_LIST, "Hoods", "Fury\nChamp\nRace\nWorx\n \nBack", "ตกลง", "ยกเลิก");
					}
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 550) // sunrise
					{
					AddVehicleComponent(car,1004);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_HOODS, DIALOG_STYLE_LIST, "Hoods", "Fury\nChamp\nRace\nWorx\n \nBack", "ตกลง", "ยกเลิก");
					}
				}
				else
				{
				SendClientMessage(playerid,COLOR_YELLOW,"คำเตือน!: ไม่สามารถแต่งกับยานพาหนะคันนี้ได้!");
				Dialog_ShowEasy(playerid, DIALOG_TYPE_HOODS, DIALOG_STYLE_LIST, "Hoods", "Fury\nChamp\nRace\nWorx\n \nBack", "ตกลง", "ยกเลิก");
				}
			}
			case 2: // Race
			{
			if(
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 549)
				{
					new car = GetPlayerVehicleID(playerid);
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 549) // tampa
					{
					AddVehicleComponent(car,1011);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_HOODS, DIALOG_STYLE_LIST, "Hoods", "Fury\nChamp\nRace\nWorx\n \nBack", "ตกลง", "ยกเลิก");
					}
				}
				else
				{
				SendClientMessage(playerid,COLOR_YELLOW,"คำเตือน!: ไม่สามารถแต่งกับยานพาหนะคันนี้ได้!");
				Dialog_ShowEasy(playerid, DIALOG_TYPE_HOODS, DIALOG_STYLE_LIST, "Hoods", "Fury\nChamp\nRace\nWorx\n \nBack", "ตกลง", "ยกเลิก");
				}
			}
			case 3: // Worx
			{
			if(
				GetVehicleModel(GetPlayerVehicleID(playerid)) == 549)
				{
					new car = GetPlayerVehicleID(playerid);
					if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 549) // tampa
					{
					AddVehicleComponent(car,1012);
					PlayerPlaySound(playerid, 1133, 0.0, 0.0, 0.0);
					SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
					Dialog_ShowEasy(playerid, DIALOG_TYPE_HOODS, DIALOG_STYLE_LIST, "Hoods", "Fury\nChamp\nRace\nWorx\n \nBack", "ตกลง", "ยกเลิก");
					}
				}
				else
				{
				SendClientMessage(playerid,COLOR_YELLOW,"คำเตือน!: ไม่สามารถแต่งกับยานพาหนะคันนี้ได้!");
				Dialog_ShowEasy(playerid, DIALOG_TYPE_HOODS, DIALOG_STYLE_LIST, "Hoods", "Fury\nChamp\nRace\nWorx\n \nBack", "ตกลง", "ยกเลิก");
				}
			}
			case 4:
			{
			Dialog_ShowEasy(playerid, DIALOG_TYPE_HOODS, DIALOG_STYLE_LIST, "Hoods", "Fury\nChamp\nRace\nWorx\n \nBack", "ตกลง", "ยกเลิก");
			}
			case 5: // Back
			{
			Dialog_ShowEasy(playerid, DIALOG_TYPE_MAIN, DIALOG_STYLE_LIST, "Car Tuning Menu", "Paint Jobs\nColors1\nColors2\nHoods\nVents\nLights\nExhausts\nFront Bumpers\nRear Bumpers\nRoofs\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nHydraulics\nNitrous Oxide", "ตกลง", "ยกเลิก");
			}
		}
	}
	return 1;
}

Dialog:DIALOG_TYPE_COLORS(playerid, response, listitem, inputtext[])
{
	if(!response){
		return Dialog_ShowEasy(playerid, DIALOG_TYPE_MAIN, DIALOG_STYLE_LIST, "Car Tuning Menu", "Paint Jobs\nColors1\nColors2\nHoods\nVents\nLights\nExhausts\nFront Bumpers\nRear Bumpers\nRoofs\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nHydraulics\nNitrous Oxide", "Enter", "Close");
	}
	if(response){
		new car = GetPlayerVehicleID(playerid);
		new carid = Car_GetID(car);
		new color1 = strval(inputtext);
		SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
		Dialog_ShowEasy(playerid, DIALOG_TYPE_COLORS, DIALOG_STYLE_INPUT, "เลือกสีที่ 1", "กรุณานำเลขสีที่ต้องการมาใส่:", "ตกลง", "กลับ");
		PlayerPlaySound(playerid, 1134, 0.0, 0.0, 0.0);
		if(carid != -1)
		{
			CarData[carid][carColor1] = color1;
			ChangeVehicleColor(CarData[carid][carVehicle],CarData[carid][carColor1],CarData[carid][carColor2]);
			Car_Save(carid);
		}
	}
	return 1;
}

Dialog:DIALOG_TYPE_COLORS2(playerid, response, listitem, inputtext[])
{
	if(!response){
		return Dialog_ShowEasy(playerid, DIALOG_TYPE_MAIN, DIALOG_STYLE_LIST, "Car Tuning Menu", "Paint Jobs\nColors1\nColors2\nHoods\nVents\nLights\nExhausts\nFront Bumpers\nRear Bumpers\nRoofs\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nHydraulics\nNitrous Oxide", "Enter", "Close");
	}
	if(response){
		new car = GetPlayerVehicleID(playerid);
		new carid = Car_GetID(car);
		new color2 = strval(inputtext);
		SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
		Dialog_ShowEasy(playerid, DIALOG_TYPE_COLORS2, DIALOG_STYLE_INPUT, "เลือกสีที่ 2", "กรุณานำเลขสีที่ต้องการมาใส่:", "ตกลง", "กลับ");
		PlayerPlaySound(playerid, 1134, 0.0, 0.0, 0.0);
		if(carid != -1){
			CarData[carid][carColor2] = color2;
			ChangeVehicleColor(CarData[carid][carVehicle],CarData[carid][carColor1],CarData[carid][carColor2]);
			Car_Save(carid);
		}
	}
	return 1;
}

Dialog:DIALOG_TYPE_PAINTJOBS(playerid, response, listitem, inputtext[])
{
	if(!response)
	{
		SetCameraBehindPlayer(playerid);
	}
	if(response)
	{
		new car = GetPlayerVehicleID(playerid);
		new carid = Car_GetID(car);
		switch(listitem)// Checking which list item was selected
		{
			case 0:// Paintjobs
			{
				if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 562 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 565 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 559 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 561 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 560 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 575 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 534 || // Broadway
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 567 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 536 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 535 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 576 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 558)
			{
				ChangeVehiclePaintjob(car,0);
				if(carid != -1){
					CarData[carid][carPaintjob] = 0;
					Car_Save(carid);
				}
				SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
				Dialog_ShowEasy(playerid, DIALOG_TYPE_PAINTJOBS, DIALOG_STYLE_LIST, "Paintjobs", "Paint Job 1\nPaint Job 2\nPaint Job 3\n \nBack", "ตกลง", "ยกเลิก");
				PlayerPlaySound(playerid, 1134, 0.0, 0.0, 0.0);
			}
				else
			{
				SendClientMessage(playerid,COLOR_WHITE,"คำสั่งนี้สำหรับยานพาหนะที่มี 4 ล้อเท่านั้น");
				Dialog_ShowEasy(playerid, DIALOG_TYPE_PAINTJOBS, DIALOG_STYLE_LIST, "Paintjobs", "Paint Job 1\nPaint Job 2\nPaint Job 3\n \nBack", "ตกลง", "ยกเลิก");
			}
			}
			case 1: // Colors
			{
				if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 562 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 565 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 559 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 561 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 560 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 575 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 534 || // Broadway
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 567 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 536 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 535 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 576 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 558)
			{
				ChangeVehiclePaintjob(car,1);
				if(carid != -1){
					CarData[carid][carPaintjob] = 1;
					Car_Save(carid);
				}
				SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
				Dialog_ShowEasy(playerid, DIALOG_TYPE_PAINTJOBS, DIALOG_STYLE_LIST, "Paintjobs", "Paint Job 1\nPaint Job 2\nPaint Job 3\n \nBack", "ตกลง", "ยกเลิก");
				PlayerPlaySound(playerid, 1134, 0.0, 0.0, 0.0);
			}
				else
			{
				SendClientMessage(playerid,COLOR_WHITE,"คำสั่งนี้สำหรับยานพาหนะที่มี 4 ล้อเท่านั้น");
				Dialog_ShowEasy(playerid, DIALOG_TYPE_PAINTJOBS, DIALOG_STYLE_LIST, "Paintjobs", "Paint Job 1\nPaint Job 2\nPaint Job 3\n \nBack", "ตกลง", "ยกเลิก");
			}
			}
			case 2: // Exhausts
			{
				if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 562 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 565 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 559 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 561 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 560 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 575 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 534 || // Broadway
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 567 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 536 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 535 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 576 ||
			GetVehicleModel(GetPlayerVehicleID(playerid)) == 558)
			{
				ChangeVehiclePaintjob(car,2);
				if(carid != -1){
					CarData[carid][carPaintjob] = 2;
					Car_Save(carid);
				}
				SendClientMessage(playerid,COLOR_WHITE,"คุณได้แต่งยานพาหนะของคุณเรียบร้อย");
				Dialog_ShowEasy(playerid, DIALOG_TYPE_PAINTJOBS, DIALOG_STYLE_LIST, "Paintjobs", "Paint Job 1\nPaint Job 2\nPaint Job 3\n \nBack", "ตกลง", "ยกเลิก");
				PlayerPlaySound(playerid, 1134, 0.0, 0.0, 0.0);
			}
				else
			{
				SendClientMessage(playerid,COLOR_WHITE,"คำสั่งนี้สำหรับยานพาหนะที่มี 4 ล้อเท่านั้น");
				Dialog_ShowEasy(playerid, DIALOG_TYPE_PAINTJOBS, DIALOG_STYLE_LIST, "Paintjobs", "Paint Job 1\nPaint Job 2\nPaint Job 3\n \nBack", "ตกลง", "ยกเลิก");
			}
			}
			case 3:
			{
				Dialog_ShowEasy(playerid, DIALOG_TYPE_PAINTJOBS, DIALOG_STYLE_LIST, "Paintjobs", "Paint Job 1\nPaint Job 2\nPaint Job 3\n \nBack", "ตกลง", "ยกเลิก");
			}
			case 4:
			{
				Dialog_ShowEasy(playerid, DIALOG_TYPE_MAIN, DIALOG_STYLE_LIST, "Car Tuning Menu", "Paint Jobs\nColors1\nColors2\nHoods\nVents\nLights\nExhausts\nFront Bumpers\nRear Bumpers\nRoofs\nSpoilers\nSide Skirts\nBullbars\nWheels\nCar Stereo\nHydraulics\nNitrous Oxide", "Enter", "Close");
			}
		}
	}
	return 1;
}