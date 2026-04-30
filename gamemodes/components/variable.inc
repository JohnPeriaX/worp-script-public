

new ServerRestart = false;
new ServerSeconds;

new tmpobjid, BankVault;

new LoginAttempts[MAX_PLAYERS] = 0;
new bool: LoggedIn[MAX_PLAYERS];

#define ANTIBOT_IP_SLOTS (64)
#define ANTIBOT_IP_WINDOW_MS (10000)
#define ANTIBOT_IP_MAX_CONNECTS (4)
#define ANTIBOT_IP_BLOCK_MS (60000)
#define ANTIBOT_GLOBAL_WINDOW_MS (3000)
#define ANTIBOT_GLOBAL_MAX_CONNECTS (18)

new AntiBotIP[ANTIBOT_IP_SLOTS][16];
new AntiBotIPCount[ANTIBOT_IP_SLOTS];
new AntiBotIPWindowTick[ANTIBOT_IP_SLOTS];
new AntiBotIPBlockedUntil[ANTIBOT_IP_SLOTS];
new AntiBotGlobalWindowTick;
new AntiBotGlobalCount;

#define SECURITY_PACKET_WINDOW_MS (1000)
#define SECURITY_PACKET_MAX_PER_WINDOW (180)
#define SECURITY_RPC_WINDOW_MS (1000)
#define SECURITY_RPC_MAX_PER_WINDOW (80)

new SecurityPacketWindowTick[MAX_PLAYERS];
new SecurityPacketCount[MAX_PLAYERS];
new SecurityRPCWindowTick[MAX_PLAYERS];
new SecurityRPCCount[MAX_PLAYERS];
new SecurityLastNetWarn[MAX_PLAYERS];

new Float:vpos[MAX_VEHICLES][4];
new PlayerEnterTime[MAX_PLAYERS] = INVALID_VEHICLE_ID;

new Siren[MAX_VEHICLES];
new STREAMER_TAG_OBJECT:SirenObject[MAX_VEHICLES];

new TogHud[MAX_PLAYERS];

new levelexp = 50;

new levelexpweapondealer = 100;

new levelexpshark = 30;
new levelexpplant = 30;

new AdminManagePlayerID[MAX_PLAYERS];

new SelectCharTextDraw[MAX_PLAYERS];

new EnterCheckPointJob[MAX_PLAYERS];

new CheckToggleAlert[MAX_PLAYERS];

new SetPlayerPlane[MAX_PLAYERS];

new TargetChangePassID[MAX_PLAYERS];

new BarHpToggle[MAX_PLAYERS];

new CheckBoombox[MAX_PLAYERS];

new StartPlayerCountTimeLogin[MAX_PLAYERS];
new PlayerTimeOutLogin[MAX_PLAYERS];

new ghour;

new TopRankMoney[500];
new TopRankLevel[500];
new TopRankHour[500];
new TopRankWallet[500];
new TopRankGangMoney[500];
new TopRankBank[500];
new TopRankRedMoney[500];
new TopRankPointGang[500];
new TopRankRacingWin[500];
new TopRankRacingLose[500];

new PlayerIsDropMap[MAX_PLAYERS];

//new PlayerTogNameTag[MAX_PLAYERS];

new GetHomeIDTemp[MAX_PLAYERS];
new GetPlayerRentHome[MAX_PLAYERS];

new TimeMute[MAX_PLAYERS];

new STREAMER_TAG_3D_TEXT_LABEL:NameTag[MAX_PLAYERS];

new PlayerUsingPhone[MAX_PLAYERS];

new PlayerGetJobGPSID[MAX_PLAYERS];

new CountCheckCarJack[MAX_PLAYERS];

new TimeSleepPoint[MAX_PLAYERS];
new StartSleep[MAX_PLAYERS];

new RingShow[MAX_PLAYERS];

new MicEventOn[MAX_PLAYERS];

new PlayerInScreen[MAX_PLAYERS];

new FixJump[MAX_PLAYERS];
new CheckHoldFlower[MAX_PLAYERS];

new TimeCountLogout[MAX_PLAYERS];
new CheckingLogout[MAX_PLAYERS];

new RefuelTime[MAX_PLAYERS];

new GetTypeCarsells[MAX_PLAYERS];

new PlayerCheckSleepOnBed[MAX_PLAYERS];

enum skate{
	bool:sActive
};
new InfoSkate[MAX_PLAYERS][skate];

new bool:PlayerTradingItem[MAX_PLAYERS];

enum PlayerFlags:(<<= 1) {
	// It's important that you don't forget to put "= 1" on the first flag. If you don't, all flags will be 0.

	PLAYER_IS_LOGGED_IN = 1,   // 0b00000000000000000000000000000001
	PLAYER_HAS_KILLED,           // 0b00000000000000000000000000000010
	PLAYER_DRIVING_TEST, // 0b00000000000000000000000000000100
	PLAYER_DUTY_TAXI,           // 0b00000000000000000000000000001000
	PLAYER_MINING,           // 0b00000000000000000000000000010000
	PLAYER_CRAFTING,           // 0b00000000000000000000000000100000
	PLAYER_ONDUTY,           // 0b00000000000000000000000001000000
	PLAYER_HOUSE_LIGHTS,           // 0b00000000000000000000000010000000
	PLAYER_ENTRANCE_LIGHTS,
	PLAYER_HARVESTING,           // 0b00000000000000000000000100000000
	PLAYER_PICKUPING,
	PLAYER_COOKMEAT,
	PLAYER_PHONE_OFF,           // 0b00000000000000000000001000000000
	PLAYER_TAZER,           // 0b00000000000000000000010000000000
	PLAYER_BEANBAG,           // 0b00000000000000000000100000000000
    PLAYER_CHAINSAW,
	PLAYER_CUFFED,          // 0b00000000000000000001000000000000
	PLAYER_DRAGGED,          // 0b00000000000000000010000000000000
	PLAYER_PICKING,          // 0b00000000000000000100000000000000
	PLAYER_CAN_TELEPORT,
	PLAYER_DISABLE_OOC,
    PLAYER_DISABLE_TWITTER,
	PLAYER_DISABLE_VAD,
	PLAYER_DISABLE_NEWBIE,
	PLAYER_DISABLE_PM,
	PLAYER_DISABLE_FACTION,
	PLAYER_DISABLE_TESTER,
	PLAYER_DISABLE_BC,
	PLAYER_FPS

};

new
	// Create an array with the same tag as the enum
	PlayerFlags:g_PlayerFlags[MAX_PLAYERS]
;

enum systemE
{
	reportSystem,
}
new systemVariables[systemE];

new TogOOC = 0;
new TogTwitter = 0;
new TogVad = 0;
new TogNewbie = 0;

new g_serverWeather = 0;

new TimeInjuredStart[MAX_PLAYERS];
new SetStartTimeHospital[MAX_PLAYERS];
new HospitalHealth[MAX_PLAYERS];

new AdminDuty[MAX_PLAYERS];

new GetJobID[MAX_PLAYERS];

new GetConfirmJoinJob[MAX_PLAYERS];

new IDPlayerGetVIP[MAX_PLAYERS];

new TogVehSpeedo[MAX_PLAYERS];

new DelayOOCandTW[MAX_PLAYERS];
new DelayNewbie[MAX_PLAYERS];

new PlayerToggleRightVehSpeedo[MAX_PLAYERS];
new PlayerToggleLeftVehSpeedo[MAX_PLAYERS];

new DrunkTime[MAX_PLAYERS];

new Timer:StopWalkScreen[MAX_PLAYERS];
new Timer:RunWalk[MAX_PLAYERS];

new bool:IsAFK[ MAX_PLAYERS char ];
new AFKTimer[MAX_PLAYERS];

new GetCarIDGarage[MAX_PLAYERS][MAX_OWNABLE_CARS];

new PlayerEnterCheckPoint[MAX_PLAYERS];
new PlayerEnterCheckPointMedic[MAX_PLAYERS];

new CheckPlayerStunFromDamage[MAX_PLAYERS];

new GetBodyID[MAX_PLAYERS];
new StartingTakeBody[MAX_PLAYERS];
new TakeBodyPoint[MAX_PLAYERS];

new GetPlayerGiveMoneyID[MAX_PLAYERS];

new EditCarIDSell[MAX_PLAYERS];
new GetCarBuy[MAX_PLAYERS];

new StartRespawnCar = 0;
new TimerRespawnCar = 0;

new CanFriskHome[MAX_PLAYERS];
new CanFriskHomeTime[MAX_PLAYERS];

new bool:PlayerEnterWarFlag[MAX_PLAYERS];

new ToggleLogo[MAX_PLAYERS];

new CheckEnterCutWood[MAX_PLAYERS];
new CheckEnterMine[MAX_PLAYERS];

new CallMedic[MAX_PLAYERS];
new MedicToMe[MAX_PLAYERS];

new STREAMER_TAG_OBJECT:GasOnVeh[MAX_VEH];
new IsGasOnVeh[MAX_VEH];

new pricevehdestroy[MAX_PLAYERS];

//gacha.pwn
enum boxname{
    boxName[64]
};
new BoxNameData[MAX_PLAYERS][boxname];

new GetIndexItemWeapon[MAX_PLAYERS];
new GetUserIDItemWeapon[MAX_PLAYERS];

new TimeEnterInterior[MAX_PLAYERS];

new StartRandom[MAX_PLAYERS];
new PlayerGetBoxType[MAX_PLAYERS];

new CarIDInstallTracker[MAX_PLAYERS];

new CountGetVehicle[MAX_PLAYERS];

new GetPlayerShareLocation[MAX_PLAYERS];

new CheckSpawnDontPressH[MAX_PLAYERS];

new PlayerCarGetID[MAX_PLAYERS];

new PlayerEnterBoxing[MAX_PLAYERS];

new PlayerUseSkinBaseHalloween[MAX_PLAYERS];

new RandomPriceCowMilk;

new PlayerClickCharList[MAX_PLAYERS];

new achat[MAX_PLAYERS], acglass[MAX_PLAYERS], acbody[MAX_PLAYERS], acarms[MAX_PLAYERS], ashowallset[MAX_PLAYERS];
new Float:acposhat[MAX_PLAYERS][9], Float:acposglass[MAX_PLAYERS][9], Float:acposbody[MAX_PLAYERS][9], Float:acposarms[MAX_PLAYERS][9];
new acedithat[MAX_PLAYERS], aceditglass[MAX_PLAYERS], aceditbody[MAX_PLAYERS], aceditarms[MAX_PLAYERS];
new acshowhat[MAX_PLAYERS], acshowglass[MAX_PLAYERS], acshowbody[MAX_PLAYERS], acshowarms[MAX_PLAYERS], acctypearms[MAX_PLAYERS];

new Timer:LoadObjectCharScreen[MAX_PLAYERS];

new PlayerShoutVoice[MAX_PLAYERS];

new AllSoundPlayerd = 0;
new Float:AllSoundPosition[3];

new PlayerText:FoodShop[MAX_PLAYERS][14];
new PlayerOpenFoodShop[MAX_PLAYERS];
new TablePizza[MAX_PLAYERS];
new PlayerCarryFoodType[MAX_PLAYERS];
new PlayerCarryFood[MAX_PLAYERS];
new PlayerSitTable[MAX_PLAYERS];
new PlayerTable[MAX_PLAYERS];
new Timer:PlayerUpdateFood[MAX_PLAYERS];

new PlayerTempHunger[MAX_PLAYERS], PlayerTempWater[MAX_PLAYERS];

new PlayerSpeedoShowing[MAX_PLAYERS];
new PlayerTextColorGold[MAX_PLAYERS];

new PlayerPlaySongChristmas[MAX_PLAYERS];
new ToolType[MAX_PLAYERS];

new PlayerHaveStoryID[MAX_PLAYERS];

new playerClickFetchCharacter[MAX_PLAYERS];

new playerLoadInventory[MAX_PLAYERS];

new Food1 = 150;
new Food2 = 200;
new EnergyDrink = 100;

new Zone1, Zone2, LabelZone;

new timeshift = 0;
new shifthour;

#define SECURITY_AC_CHECK_MS (1000)
#define SECURITY_AC_ALERT_COOLDOWN_MS (10000)
#define SECURITY_AC_NEX_COOLDOWN_MS (5000)
#define SECURITY_AC_MAX_WARNINGS (4)

new SecurityACLastCheckTick[MAX_PLAYERS];
new SecurityACLastAlertTick[MAX_PLAYERS];
new SecurityACWarnings[MAX_PLAYERS];
new SecurityACGraceUntil[MAX_PLAYERS];
new SecurityACLastNexTick[MAX_PLAYERS];
new SecurityACLastNexCode[MAX_PLAYERS];
new Float:SecurityACLastX[MAX_PLAYERS];
new Float:SecurityACLastY[MAX_PLAYERS];
new Float:SecurityACLastZ[MAX_PLAYERS];
new SecurityACLastInterior[MAX_PLAYERS];
new SecurityACLastWorld[MAX_PLAYERS];
new bool:SecurityACPosReady[MAX_PLAYERS];

#define SECURITY_AC_SHOT_WINDOW_MS (1000)
#define SECURITY_AC_MAX_SHOTS_PER_WINDOW (28)

new SecurityACShotWindowTick[MAX_PLAYERS];
new SecurityACShotCount[MAX_PLAYERS];
