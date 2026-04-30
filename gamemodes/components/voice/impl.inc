#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

hook OnGameModeInit() {
	//SvDebug(SV_TRUE);
	police = SvCreateGStream(0x006DD9FF, "Police");
	medic = SvCreateGStream(0xFFB760FF, "Medic");
	return 1;
}

LoadSpeakerTextDraw(playerid){
	SpeakerProgressBar[playerid][0] = CreatePlayerProgressBar(playerid, 548.500000, 36.000000, 62.000000, 4.000000, -8388353, 100.000000, 0);
}

hook OnPlayerConnect(playerid) {
	if (!SvGetVersion(playerid)) SendClientMessage(playerid, COLOR_RED, "[เกิดข้อผิดพลาด]: คุณไม่ได้ลง Plugin sampvoice");
	else if (!SvHasMicro(playerid)) SendClientMessage(playerid, COLOR_RED, "[เกิดข้อผิดพลาด]: คุณไม่มีไมค์");
	else if ((lstream[playerid] = SvCreateDLStreamAtPlayer(15.0, SV_INFINITY, playerid, 0xff0000ff, "Local"))){
		SendClientMessage(playerid, COLOR_SERVER, "{23D101}| {FFFFFF}คุณได้เชื่อมต่อ 'ไมโครโฟน' กับเซิฟเวอร์ของเราเรียบร้อยแล้ว");
		SvAddKey(playerid, 0x42);
	}
	PlayerUsingRadioPolice[playerid] = 0;
	PlayerUsingRadioMedic[playerid] = 0;
	PlayerTogSpeaker[playerid] = 0;
	return 1;
}

ShowSpeaker(playerid){
	if(PlayerTogSpeaker[playerid] == 0){
		LoadSpeakerTextDraw(playerid);
		SetPlayerProgressBarColour(playerid, SpeakerProgressBar[playerid][0], 0x00EA0EAA);
		ShowPlayerProgressBar(playerid, SpeakerProgressBar[playerid][0]);
		SetPlayerProgressBarValue(playerid, SpeakerProgressBar[playerid][0], 50.0);
	}
	return 1;
}

ShowMenuMic(playerid){
	if(!LoggedIn[playerid]) return 1;
	Dialog_ShowEasy(playerid, SetMic, DIALOG_STYLE_LIST, "รูปแบบไมค์โครโฟน", "- ระดับของเสียงไมค์\n- สำหรับหน่วยงาน", "ตกลง", "ยกเลิก");
	return 1;
}

Dialog:SetMic(playerid, response, listitem, inputtext[]){
	if(!response) return 1;
	if(response){
		if(listitem == 0){
			Dialog_ShowEasy(playerid, LevelMic, DIALOG_STYLE_LIST, "ระดับของเสียงไมค์", "- พูดแบบ กระซิบ\n- พูดแบบ ปกติ\n- พูดแบบ ตะโกน", "เลือก", "ยกเลิก");
		}
		if(listitem == 1){
			new caption[128];

			new groupid = PlayerData[playerid][pGroup];
			if(groupid == -1) return ErrorMsg(playerid, "คุณไม่ได้เป็นหน่วยงานใดๆอยู่เลย");
			if(GetGroupType(playerid) != GROUP_POLICE && GetGroupType(playerid) != GROUP_MEDIC) return ErrorMsg(playerid, "หน่วยของคุณยังไม่มีวิทยุ");

			format(caption, sizeof(caption), "วิทยุ หน่วยงาน: %s", Group_GetName(playerid));
			Dialog_ShowEasy(playerid, SetGroupMic, DIALOG_STYLE_LIST, caption, "- เปิด\n- ปิด", "เลือก", "ยกเลิก");
		}
	}
	return 1;
}

Dialog:SetGroupMic(playerid, response, listitem, inputtext[]){
	if(!response) return 1;
	if(response){
		new groupid = PlayerData[playerid][pGroup];
		if(groupid == -1) return ErrorMsg(playerid, "คุณไม่ได้เป็นหน่วยงานใดๆอยู่เลย");

		if(GetGroupType(playerid) != GROUP_POLICE && GetGroupType(playerid) != GROUP_MEDIC) return ErrorMsg(playerid, "หน่วยของคุณยังไม่มีวิทยุ");

		if(listitem == 0){
			if(GetGroupType(playerid) == GROUP_POLICE){
				PlayerUsingRadioPolice[playerid] = true;
				if (police && PlayerUsingRadioPolice[playerid]){
					SvAttachListenerToStream(police, playerid);
					SvAttachSpeakerToStream(police, playerid);
				}
				SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้เปิดวิทยุสำหรับหน่วยงาน %s เรียบร้อยแล้ว", Group_GetName(playerid));
			}
			if(GetGroupType(playerid) == GROUP_MEDIC){
				PlayerUsingRadioMedic[playerid] = true;
				if (medic && PlayerUsingRadioMedic[playerid]){
					SvAttachListenerToStream(medic, playerid);
					SvAttachSpeakerToStream(medic, playerid);
				}
				SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้เปิดวิทยุสำหรับหน่วยงาน %s เรียบร้อยแล้ว", Group_GetName(playerid));
			}
		}
		if(listitem == 1){
			if(GetGroupType(playerid) == GROUP_POLICE){
				PlayerUsingRadioPolice[playerid] = false;
				if (police && !PlayerUsingRadioPolice[playerid]){
					SvDetachListenerFromStream(police, playerid);
					SvDetachSpeakerFromStream(police, playerid);
				}
				SendClientMessageEx(playerid, COLOR_RED, "- คุณได้ปิดวิทยุสำหรับหน่วยงาน %s เรียบร้อยแล้ว", Group_GetName(playerid));
			}
			if(GetGroupType(playerid) == GROUP_MEDIC){
				PlayerUsingRadioMedic[playerid] = false;
				if (medic && !PlayerUsingRadioMedic[playerid]){
					SvDetachListenerFromStream(medic, playerid);
					SvDetachSpeakerFromStream(medic, playerid);
				}
				SendClientMessageEx(playerid, COLOR_RED, "- คุณได้ปิดวิทยุสำหรับหน่วยงาน %s เรียบร้อยแล้ว", Group_GetName(playerid));
			}
		}
		
	}
	return 1;
}

Dialog:LevelMic(playerid, response, listitem, inputtext[]){
	if(!response) return 1;
	if(response){
		if(listitem == 0){
			if(lstream[playerid]){
				SvUpdateDistanceForLStream(lstream[playerid], 5.0);
			}
			SendClientMessage(playerid, -1, "- คุณได้ปรับเสียงไมค์เป็นแบบ กระซิบ แล้ว");
			if(PlayerTogSpeaker[playerid] == 0){
				HidePlayerProgressBar(playerid, SpeakerProgressBar[playerid][0]);
				SetPlayerProgressBarValue(playerid, SpeakerProgressBar[playerid][0], 20.0);
				SetPlayerProgressBarColour(playerid, SpeakerProgressBar[playerid][0], 0xFFF703AA);
				ShowPlayerProgressBar(playerid, SpeakerProgressBar[playerid][0]);
			}
		}
		if(listitem == 1){
			if(lstream[playerid]){
				SvUpdateDistanceForLStream(lstream[playerid], 15.0);
			}
			SendClientMessage(playerid, -1, "- คุณได้ปรับเสียงไมค์เป็นแบบ ปกติ แล้ว");
			if(PlayerTogSpeaker[playerid] == 0){
				HidePlayerProgressBar(playerid, SpeakerProgressBar[playerid][0]);
				SetPlayerProgressBarValue(playerid, SpeakerProgressBar[playerid][0], 50.0);
				SetPlayerProgressBarColour(playerid, SpeakerProgressBar[playerid][0], 0x00EA0EAA);
				ShowPlayerProgressBar(playerid, SpeakerProgressBar[playerid][0]);
			}
		}
		if(listitem == 2){
			if(lstream[playerid]){
				SvUpdateDistanceForLStream(lstream[playerid], 30.0);
			}
			SendClientMessage(playerid, -1, "- คุณได้ปรับเสียงไมค์เป็นแบบ ตะโกน แล้ว");
			if(PlayerTogSpeaker[playerid] == 0){
				HidePlayerProgressBar(playerid, SpeakerProgressBar[playerid][0]);
				SetPlayerProgressBarValue(playerid, SpeakerProgressBar[playerid][0], 100.0);
				SetPlayerProgressBarColour(playerid, SpeakerProgressBar[playerid][0], 0xFF4200AA);
				ShowPlayerProgressBar(playerid, SpeakerProgressBar[playerid][0]);
			}
		}
	}
	return 1;
}

CMD:addmic(playerid, params[]){
	if(!LoggedIn[playerid]) return 1;
	if(PlayerData[playerid][pAdmin] < 1337) return 1;
	new userid;
	if(sscanf(params, "u", userid)) return SystemMsg(playerid, "/addmic [playerid]");
	if(userid == INVALID_PLAYER_ID) return 1;
	if(!LoggedIn[userid]) return 1;
	if(!PlayerMicEvent[userid]){
		if(lstream[userid]){
			SvUpdateDistanceForLStream(lstream[userid], 100.0);
		}
		SendClientMessageEx(playerid, COLOR_YELLOW, "คุณได้ปรับไมค์ของ %s(%d) ให้ดังขึ้นแล้ว", ReturnRoleplayName(userid), userid);
	}else{
		if(lstream[userid]){
			SvUpdateDistanceForLStream(lstream[userid], 15.0);
		}
		SendClientMessageEx(playerid, COLOR_YELLOW, "คุณได้ปรับไมค์ของ %s(%d) ให้เป็นปกติแล้ว", ReturnRoleplayName(userid), userid);
	}
	return 1;
}

CMD:mutemic(playerid, params[]){
	if(!LoggedIn[playerid]) return 1;
	if(PlayerData[playerid][pAdmin] < 5) return 1;
	new userid;
	if(sscanf(params, "u", userid)) return SystemMsg(playerid, "/mutemic [playerid]");
	if(userid == INVALID_PLAYER_ID) return 1;
	if(!LoggedIn[userid]) return ErrorMsg(playerid, "ผู้เล่นนั้นยังไม่ได้ล็อคอิน");
	SvMutePlayerEnable(userid);
	PlayerData[userid][pMicMute] = 1;
	SendClientMessageToAllEx(0xFF6100AA, "ผู้ดูแลระบบ ได้ทำการ 'ปิดไมค์' ผู้เล่น '%s(%d)'", ReturnRoleplayName(userid), userid);
	return 1;
}

CMD:unmutemic(playerid, params[]){
	if(!LoggedIn[playerid]) return 1;
	if(PlayerData[playerid][pAdmin] < 5) return 1;
	new userid;
	if(sscanf(params, "u", userid)) return SystemMsg(playerid, "/unmutemic [playerid]");
	if(userid == INVALID_PLAYER_ID) return 1;
	if(!LoggedIn[userid]) return ErrorMsg(playerid, "ผู้เล่นนั้นยังไม่ได้ล็อคอิน");
	SvMutePlayerDisable(userid);
	PlayerData[userid][pMicMute] = 0;
	SendClientMessageToAllEx(0xFF6100AA, "ผู้ดูแลระบบ ได้ทำการ 'เปิดไมค์' ผู้เล่น '%s(%d)'", ReturnRoleplayName(userid), userid);
	return 1;
}

ResetPlayerVoice(playerid){
	if (lstream[playerid]) {
		SvDetachSpeakerFromStream(lstream[playerid], playerid);
		SvDetachListenerFromStream(lstream[playerid], playerid);
	}
	if (OnPhone[playerid]) {
		SvDetachSpeakerFromStream(OnPhone[playerid], playerid);
		SvDetachListenerFromStream(OnPhone[playerid], playerid);
	}
	if(PlayerUsingRadioPolice[playerid]){
		SvDetachSpeakerFromStream(police, playerid);
		SvDetachListenerFromStream(police, playerid);
	} 
	if(PlayerUsingRadioMedic[playerid]) {
		SvDetachSpeakerFromStream(medic, playerid);
		SvDetachListenerFromStream(medic, playerid);
	}
	PlayerUsingRadioPolice[playerid] = 0;
	PlayerUsingRadioMedic[playerid] = 0;
	PlayerTogSpeaker[playerid] = 0;
	return 1;
}