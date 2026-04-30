#if defined _inc_impl
	#undef _inc_impl
#endif

CheckPlayerNotSendGps(playerid){
	if(CheckEnterCutWood[playerid] == 1 || CheckEnterMine[playerid] == 1 || ChangeSkinEngJob[playerid] == 1 || CheckEnterPointEngJob[playerid] == 1 || CheckEnterPointGarbageJob[playerid] == 1
	||	StartChangeSkinBuildJob[playerid] == 1 || StartGardenerJob[playerid] == 1 || PlayerStartDeliverOil[playerid])
		return 1;

	return -1;
}

CheckPlayerNotOpenInv(playerid){
	if(StartProcessFarmer[playerid] == 1 || PlayerPressYToFishing[playerid] == 1 || PickingUpCow[playerid] == 1 || StartProcessMeat[playerid] == 1 ||
	StartingCutWood[playerid] == 1 || PlayerData[playerid][pInHospital] == 1 || PlayerData[playerid][pInjured] == 1 || PlayerData[playerid][pFirstTime] == 1 ||
	StartProcessOil[playerid] || StartDrill[playerid] || GotoSendBox[playerid] || CheckPlayerStunFromDamage[playerid] || PlayerPickingUpShell[playerid] || CheckSpawnDontPressH[playerid] ||
	StartingWashTreasure[playerid] || Player_Orange_InCrate[playerid] || Player_GetID_Orange[playerid] != -1 || PlayerStart_UpgradeWeapon[playerid] == 1 || Open_UpgradeMenu[playerid] || Open_UpgradeMenuFinish[playerid] ||
	StartPickupDrug[playerid] || StartProcessDrug[playerid] || IsOpeningGaCha[playerid] || StartFishingShark[playerid] || PlayerStartMine[playerid] || PlayerStartProcessMine[playerid] ||
	TimeCountLogout[playerid] > 0 || PlayerEnterWarFlag[playerid] || Player_Watering[playerid] || PlayerEnterRacing[playerid] || PlayerTradingItem[playerid] || StartRepair[playerid] || StartRefill[playerid] || StartCraftMixedDrug[playerid] || 
	StartingCraftWeapon[playerid] || OpenMenuCraftDrug[playerid] || PlayerOpenPizzaMenu[playerid] || PlayerOpenCraftWeaponMenu[playerid] ||
    PlayerOpeningMenuCabara[playerid] || PlayerOpenFoodShop[playerid] || PlayerShowSkinShopMenu[playerid] || PlayerOpenAccessoryMenu[playerid] || PlayerHealing[playerid])
		return 1;
		
	return -1;
}

Item_CantDrop(const itemname[]){

    if(!strcmp(itemname, "Box Level", true) 
    || !strcmp(itemname, "Id Card", true)
    || !strcmp(itemname, "Mobile Phone", true)
    || !strcmp(itemname, "Agency Card", true)
    || !strcmp(itemname, "Driving Card", true)
    || !strcmp(itemname, "Marry Card", true)
    || !strcmp(itemname, "Marry Ring", true)
    || !strcmp(itemname, "Marry Flower", true)
    || !strcmp(itemname, "Dealer Card", true)
    || !strcmp(itemname, "Medkit", true)
    || !strcmp(itemname, "Blood bag", true)
    || !strcmp(itemname, "Halloween Pumpkin", true)
    || !strcmp(itemname, "Christmas Box", true))
        return 1;

    return -1;
}

Item_CantPickup(const itemname[]){

    if(!strcmp(itemname, "Id Card", true)
    || !strcmp(itemname, "Mobile Phone", true)
    || !strcmp(itemname, "Box Level", true)
    || !strcmp(itemname, "Dealer Card", true)
    || !strcmp(itemname, "Christmas Box", true))
        return 1;

    return -1;
}

Item_CantPutHome(const itemname[]){

    if(!strcmp(itemname, "Box Level", true) 
    || !strcmp(itemname, "Mobile Phone", true)
    || !strcmp(itemname, "Marry Card", true)
    || !strcmp(itemname, "Marry Ring", true)
    || !strcmp(itemname, "Marry Flower", true)
    || !strcmp(itemname, "Medkit", true)
    || !strcmp(itemname, "Blood bag", true)
    || !strcmp(itemname, "Dealer Card", true)
    || !strcmp(itemname, "Halloween Pumpkin", true)
    || !strcmp(itemname, "Christmas Box", true))
        return 1;

    return -1;
}