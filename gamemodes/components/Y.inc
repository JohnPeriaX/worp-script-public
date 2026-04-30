#if defined _inc_Y
	#undef _inc_Y
#endif

#if !defined Y_@@@@_HEADER
	#include "variable"

	#include "core\header"

	#include "logger\header"
	#include "dynamic\header"
	#include "playerdata\header"
	#include "inventory\header"
	#include "server\header"
	#include "cmd\header"
	#include "groups\header"
	#include "jobs\header"
	#include "sidejobs\header"
	#include "system\header"
	#include "worp_inventory\header"

	#include "voice\header"
	#define Y_@@@@_HEADER
#elseif !defined Y_@@@@_END
	
	#include "core\impl"

	#include "logger\impl"
	#include "dynamic\impl"
	#include "playerdata\impl"
	#include "inventory\impl"
	#include "server\impl"
	#include "cmd\impl"
	#include "groups\impl"
	#include "jobs\impl"
	#include "sidejobs\impl"
	#include "system\impl"
	#include "worp_inventory\impl"
    
	#include "voice\impl"

	#include "reset"
	#include "stock"
	#include "public"
	#include "timer"
	#include "callback"
	#define Y_@@@@_END
#else
	#error Y core already set up
#endif