#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

hook OnPlayerEnterVehicle(playerid, vehicleid, ispassenger){
	if(vehicleid != INVALID_VEHICLE_ID){
		if(playerGetDragID[playerid] != INVALID_PLAYER_ID){
			ResetPlayerDrag(playerid);
		}
	}
}

timer ClearAnimationDrag[1500](targetid){
	ClearAnimations(targetid);
}

void:ResetPlayerDrag(playerid){
	if(playerGetDragID[playerid] != INVALID_PLAYER_ID){
		if(playerIsDraged[playerid]){
			playerIsDraging[playerGetDragID[playerid]] = false;
			playerGetDragID[playerGetDragID[playerid]] = INVALID_PLAYER_ID;

			playerIsDraged[playerid] = false;
			playerGetDragID[playerid] = INVALID_PLAYER_ID;

			stop playerDragTimer[playerid];
		}

		if(playerIsDraging[playerid]){
			stop playerDragTimer[playerGetDragID[playerid]];

			ClearAnimations(playerGetDragID[playerid]);
			ApplyAnimation(playerGetDragID[playerid], "PED", "IDLE_tired", 4.1, 1, 0, 0, 0, 0, 1);

			defer ClearAnimationDrag(playerGetDragID[playerid]);

			playerIsDraged[playerGetDragID[playerid]] = false;
			playerGetDragID[playerGetDragID[playerid]] = INVALID_PLAYER_ID;

			playerIsDraging[playerid] = false;
			playerGetDragID[playerid] = INVALID_PLAYER_ID;
		}
	}

	playerGetDragID[playerid] = INVALID_PLAYER_ID;
	playerIsDraged[playerid] = false;
	playerIsDraging[playerid] = false;
	playerDragIdle[playerid] = false;
	stop playerDragTimer[playerid];
}

stock Float:SetPlayerFacingAngleToPlayer(playerid, targetid){
    new Float:x1, Float:y1, Float:z1;
    new Float:x2, Float:y2, Float:z2;
    GetPlayerPos(playerid, x1, y1, z1);
    GetPlayerPos(targetid, x2, y2, z2);
    new Float:angle = atan2(y2 - y1, x2 - x1) - 90.0;
	return angle;
} 

timer TimeUpdateDrag[500](targetid){
	if(playerIsDraged[targetid] && playerGetDragID[targetid] != INVALID_PLAYER_ID && LoggedIn[playerGetDragID[targetid]]){
		new
	        Float:fX,
	        Float:fY,
	        Float:fZ,
			Float:fAngle;

		GetPlayerPos(playerGetDragID[targetid], fX, fY, fZ);
		GetPlayerFacingAngle(playerGetDragID[targetid], fAngle);
		fX -= 3.0 * floatsin(-fAngle, degrees);
		fY -= 3.0 * floatcos(-fAngle, degrees);

		if(GetPlayerInterior(targetid) != GetPlayerInterior(playerGetDragID[targetid]) || GetPlayerVirtualWorld(targetid) != GetPlayerVirtualWorld(playerGetDragID[targetid])){
			SetPlayerPos(targetid, fX, fY, fZ);
		}

		SetPlayerFacingAngle(targetid, SetPlayerFacingAngleToPlayer(targetid, playerGetDragID[targetid]));
		SetPlayerInterior(targetid, GetPlayerInterior(playerGetDragID[targetid]));
		SetPlayerVirtualWorld(targetid, GetPlayerVirtualWorld(playerGetDragID[targetid]));

		if(IsPlayerNearPlayer(targetid, playerGetDragID[targetid], 5.0)) {
			if(!playerDragIdle[targetid]){
				playerDragIdle[targetid] = true;
				ClearAnimations(targetid);
				ApplyAnimation(targetid, "PED", "IDLE_tired", 4.1, 1, 0, 0, 0, 0, 1);
				defer ClearAnimationDrag(targetid);
			}
		}
		else {
			if(playerDragIdle[targetid]) playerDragIdle[targetid] = false;
			ApplyAnimation(targetid, "PED", "run_player", 4.1, 1, 1, 1, 1, 1, 1);
		}
	}
}

SetPlayerDraging(playerid, targetid){
	if(playerGetDragID[playerid] == INVALID_PLAYER_ID && playerGetDragID[targetid] == INVALID_PLAYER_ID){
		TogglePlayerControllable(targetid, 1);
		playerIsDraging[playerid] = true;
		playerIsDraged[targetid] = true;
		playerGetDragID[playerid] = targetid;
		playerGetDragID[targetid] = playerid;

		playerDragTimer[targetid] = repeat TimeUpdateDrag(targetid);
	} else if(playerGetDragID[playerid] == targetid && playerGetDragID[targetid] == playerid){
		stop playerDragTimer[targetid];

		TogglePlayerControllable(targetid, 0);
		ClearAnimations(targetid);
		ApplyAnimation(targetid, "PED", "IDLE_tired", 4.1, 1, 0, 0, 0, 0, 1);

		defer ClearAnimationDrag(targetid);

		playerIsDraging[playerid] = false;
		playerIsDraged[targetid] = false;
		playerGetDragID[playerid] = INVALID_PLAYER_ID;
		playerGetDragID[targetid] = INVALID_PLAYER_ID;

	}
	return true;
}