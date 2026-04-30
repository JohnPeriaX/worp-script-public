#if defined _inc_header
	#undef _inc_header
#endif

enum jobData {
	jobID,
	jobExists,
	jobName[32],
	jobType,
	Float:jobPos[3],
	Float:jobPoint[3],
	Float:jobPoint2[3],
	Float:jobDeliver[3],
	jobInterior,
	jobWorld,
	jobPointInt,
	jobPointWorld,
	jobPoint2Int,
	jobPoint2World,
	jobDeliverInt,
	jobDeliverWorld,
	STREAMER_TAG_PICKUP:jobPickups[4],
	STREAMER_TAG_3D_TEXT_LABEL:jobText3D[4],
	jobDeliverPrice,
	jobDeliverActor,
	jobActorSkin,
	Float:jobActorAngle,
	jobCPDynamic,
	jobActorCheck,
	jobLevel
};
new JobData[MAX_DYNAMIC_JOBS][jobData],Total_Jobs_Created;