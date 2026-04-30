#include <a_samp>
#include <YSF>

#pragma semicolon 1

// YSI
#define CGEN_MEMORY (30000)
#define YSI_NO_OPTIMISATION_MESSAGE
#define YSI_YES_VERSION_CHECK
#define YSI_NO_CACHE_MESSAGE
#define YSI_NO_HEAP_MALLOC
#define YSI_NO_MODE_CACHE
#define SAMP_CONST_CORRECT

#include <YSI_Coding\y_timers>
#include <YSI_Data\y_iterate>

#include <samp_bcrypt>

#include <YSI_Visual\y_dialog>
#include <YSI_Players\y_android>

#include "config"

#include <streamer>
#include <a_mysql>
#include <sscanf2>
#include <progress2>
#include <eSelection>
#include <mapandreas>
#include <Pawn.CMD>
#include <Pawn.Regex>
#include <Pawn.RakNet>
#include <GPS>
#include <samp-player-gangzones>
#include <nex-ac>
#include <weapon-config>
#include <crashdetect>
#include <RGB>

#if defined RUN_TESTS
	#include <YSI_Core\y_testing>
#endif

#define  cec_auto
#include <cec>
#include <discord-connector>
#include <easyDialog>
#include <sampvoice>
#include <FCNPC>
#include <strlib>


DEFINE_HOOK_REPLACEMENT__(OnPlayer, OP_);

#include "components\Y"

#include "components\Y"
main(){
	bcrypt_set_thread_limit(3);
	print("\n----------------------------------");
	print(" - Gta Worp City 5.0");
	print(" - Deverlop by JustinzDev");
	print("----------------------------------\n");
}
