#if defined _inc_header
	#undef _inc_header
#endif

#define MAX_SHELLS (13)
enum shellData{
    shellID,
    shellEx,
    shellAlive,
    shellTimeAlive,
    shellPlayerUse,
    Float:shellPos[3],
    STREAMER_TAG_OBJECT:shellObject,
    STREAMER_TAG_3D_TEXT_LABEL:shellText
};
new ShellData[MAX_SHELLS][shellData];

new ShellTimer[MAX_PLAYERS];
new ShellPoint[MAX_PLAYERS];
new PlayerPickingUpShell[MAX_PLAYERS];
new PlayerGetShellID[MAX_PLAYERS];