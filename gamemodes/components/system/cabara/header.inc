#if defined _inc_header
	#undef _inc_header
#endif

new Text:TextDrawCabara[15];
new CabaraIsOpen = false;
new ScorePlayer = 0, ScoreBanker = 0;
new TotalMoneyPlayer = 0, TotalMoneyTie = 0, TotalMoneyBanker = 0;
new PlayerMoneyDown[MAX_PLAYERS], PlayerSelectTeam[MAX_PLAYERS];
new PlayerOpeningMenuCabara[MAX_PLAYERS];
new TimingCountCabara = 30, CabaraStart = 0, CabaraStarting = 0, CheckWhoWin;

#define MAX_CASINO (10)

enum casinodata{
    casinoID,
    casinoEx,
    Float:casinoPos[3],
    casinoInt,
    casinoWorld,
    STREAMER_TAG_3D_TEXT_LABEL:casinoText3D,
    casinoPickup
};
new CasinoData[MAX_CASINO][casinodata], Count_Casino;