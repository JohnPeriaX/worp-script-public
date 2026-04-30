#if defined _inc_header
	#undef _inc_header
#endif

#define MAX_DRUGPOINT (10)
enum drugdata{
    drugID,
    drugEx,
    drugType,
    Float:drugPos[3],
    Float:drugProcessPos[3],
    drugWorld,
    drugInt,
    drugProcessWorld,
    drugProcessInt,
    drugAmount,
    STREAMER_TAG_3D_TEXT_LABEL:drugText3D[3],
    drugMapicon[2],
    drugPrice,
    Float:drugDeliverPos[3],
    drugDeliverWorld,
    drugDeliverInt
};
new DrugData[MAX_DRUGPOINT][drugdata], drug_count;

new StartPickupDrug[MAX_PLAYERS];
new DrugTimer[MAX_PLAYERS];
new DrugPoint[MAX_PLAYERS];
new PlayerGetDrug[MAX_PLAYERS];
new StartProcessDrug[MAX_PLAYERS];

new TradeTimer[MAX_PLAYERS];
new TradePoint[MAX_PLAYERS];
new StartTradeMoney[MAX_PLAYERS];
new OpenMenuCraftDrug[MAX_PLAYERS];
new StartCraftMixedDrug[MAX_PLAYERS];
new CraftMixedDrugPoint[MAX_PLAYERS];
new CraftDrugTimer[MAX_PLAYERS];
new PlayerGetDrugType[MAX_PLAYERS];