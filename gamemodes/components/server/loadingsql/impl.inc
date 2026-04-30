#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

hook OnGameModeInit(){
    ConnectMySQL();
    return true;
}

ConnectMySQL(){
	mysql_log(ERROR | WARNING);
	new MySQLOpt: option_id = mysql_init_options();
	mysql_set_option(option_id, AUTO_RECONNECT, true);
	dbCon = mysql_connect(MYSQL_HOST, MYSQL_USER, MYSQL_PASS, MYSQL_DB, option_id);
	
	if (dbCon == MYSQL_INVALID_HANDLE || mysql_errno(dbCon) != 0){
		print("[MySQL]: Connection failed. Server is shutting down.");
		SendRconCommand("exit");
		return 1;
	}

	print("[MySQL]: Connection is successful.");
	return 1;
}

LoadingServer(){
    mysql_tquery(dbCon, "SELECT * FROM `dropped`", "Dropped_Load", "");
    mysql_tquery(dbCon, "SELECT * FROM `serverconfig`", "server_Load", "");
    mysql_tquery(dbCon, "SELECT * FROM `jobs`", "Job_Load", "");
    mysql_tquery(dbCon, "SELECT * FROM `sidejobs`", "SideJob_Load", "");
    mysql_tquery(dbCon, "SELECT * FROM `crafts`", "Craft_Load", "");
    mysql_tquery(dbCon, "SELECT * FROM `cows`", "Cow_Load", "");
	mysql_tquery(dbCon, "SELECT * FROM `cars`", "Car_Load", "");
    mysql_tquery(dbCon, "SELECT * FROM `woods`", "Wood_Load", "");
    mysql_tquery(dbCon, "SELECT * FROM `garages`", "Garage_Load", "");
    mysql_tquery(dbCon, "SELECT * FROM `entrances`", "Entrance_Load", "");
    mysql_tquery(dbCon, "SELECT * FROM `carsells`", "CarSell_Load", "");
    mysql_tquery(dbCon, "SELECT * FROM `groups`", "Group_Load", "");
    mysql_tquery(dbCon, "SELECT * FROM `drugpoints`", "Drug_Load", "");
    mysql_tquery(dbCon, "SELECT * FROM `arrests`", "Arrest_Load", "");
    mysql_tquery(dbCon, "SELECT * FROM `pumps`", "Pump_Load", "");
    mysql_tquery(dbCon, "SELECT * FROM `jellyfish`", "JellyFish_Load", "");
    mysql_tquery(dbCon, "SELECT * FROM `gates`", "Gate_Load", "");
    mysql_tquery(dbCon, "SELECT * FROM `cartunes`", "Cartune_Load", "");
    mysql_tquery(dbCon, "SELECT * FROM `weaponcrafts`", "WeaponCraft_Load", "");
    mysql_tquery(dbCon, "SELECT * FROM `homes`", "Home_Load", "");
    mysql_tquery(dbCon, "SELECT * FROM `atm`", "ATM_Load", "");
    mysql_tquery(dbCon, "SELECT * FROM `skinmales`", "SkinMale_Load", "");
    mysql_tquery(dbCon, "SELECT * FROM `skinfemales`", "SkinFeMale_Load", "");
    mysql_tquery(dbCon, "SELECT * FROM `gachas`", "GaCha_Load", "");
    mysql_tquery(dbCon, "SELECT * FROM `rubbers`", "Rubber_Load", "");
    mysql_tquery(dbCon, "SELECT * FROM `donateitems`", "DonateItem_Load", "");
    mysql_tquery(dbCon, "SELECT * FROM `safezones`", "SafeZone_Load", "");
    mysql_tquery(dbCon, "SELECT * FROM `gangzones`", "GangZone_Load", "");
    mysql_tquery(dbCon, "SELECT * FROM `oil`", "Oil_Load", "");
    mysql_tquery(dbCon, "SELECT * FROM `accshops`", "AccShop_Load", "");
    mysql_tquery(dbCon, "SELECT * FROM `hatitems`", "HatItem_Load", "");
    mysql_tquery(dbCon, "SELECT * FROM `glassesitems`", "GlassesItem_Load", "");
    mysql_tquery(dbCon, "SELECT * FROM `bodyitems`", "BodyItem_Load", "");
    mysql_tquery(dbCon, "SELECT * FROM `handsitems`", "HandsItem_Load", "");
    mysql_tquery(dbCon, "SELECT * FROM `upgradeweapons`", "UpgradeWeapon_Load", "");
    mysql_tquery(dbCon, "SELECT * FROM `casinos`", "Casino_Load", "");
    mysql_tquery(dbCon, "SELECT * FROM `deers`", "Deer_Load", "");
    mysql_tquery(dbCon, "SELECT * FROM `plants`", "Plant_Load", "");
    mysql_tquery(dbCon, "SELECT * FROM `bizs`", "Biz_Load", "");
    mysql_tquery(dbCon, "SELECT * FROM `newcows`", "NewCow_Load", "");
    mysql_tquery(dbCon, "SELECT * FROM `showers`", "Shower_Load", "");
    mysql_tquery(dbCon, "SELECT * FROM `story_gangs`", "StoryGang_Load", "");
    printf("Load Database Successfully");
    return 1;
}