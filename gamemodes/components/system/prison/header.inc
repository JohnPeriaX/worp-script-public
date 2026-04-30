#if defined _inc_header
	#undef _inc_header
#endif

enum prisonData {
	prisonDoors[3],
	prisonCells[24],
	prisonDoorOpened[3],
	prisonCellOpened[24]
};
new PrisonData[prisonData];
new Float:PrisonCells[24][3];

new BuildPrison[13];

#define PRISON_WORLD (10000)

new GotoSendBox[MAX_PLAYERS];
new StartDeliverBox[MAX_PLAYERS];

#define pricejobprison (5)