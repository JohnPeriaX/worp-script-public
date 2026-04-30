#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

hook OnGameModeInit(){
	Logger_Log("[components/logger : OnGameModeInit] setting up...");
    Logger_ToggleDebug(PLAYER_DEBUG_HANDLER, true);
    return 1;
}