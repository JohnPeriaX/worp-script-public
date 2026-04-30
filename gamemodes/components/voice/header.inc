#if defined _inc_header
	#undef _inc_header
#endif

new SV_GSTREAM:police;
new SV_GSTREAM:medic;
new PlayerUsingRadioPolice[MAX_PLAYERS];
new PlayerUsingRadioMedic[MAX_PLAYERS];
new SV_LSTREAM:lstream[MAX_PLAYERS] = { SV_NULL, ... };
new SV_GSTREAM:OnPhone[MAX_PLAYERS];

new PlayerBar:SpeakerProgressBar[MAX_PLAYERS][1];
new PlayerTogSpeaker[MAX_PLAYERS];
new PlayerMicEvent[MAX_PLAYERS];