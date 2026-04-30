#if defined _inc_header
	#undef _inc_header
#endif

enum gateData {
	gateID,
	gateExists,
	gateOpened,
	gateModel,
	Float:gateSpeed,
	Float:gateRadius,
	gateTime,
	Float:gatePos[6],
	gateInterior,
	gateWorld,
	Float:gateMove[6],
	gateLinkID,
	gateFaction,
	gatePass[32],
	gateTimer,
	STREAMER_TAG_OBJECT:gateObject,
	gateSlow,
};

new CountGate = 0;

new GateData[MAX_GATES][gateData];