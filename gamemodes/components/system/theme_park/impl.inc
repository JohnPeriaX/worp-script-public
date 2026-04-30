#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

hook OnGameModeInit(){
    CreateDynamic3DTextLabel("[แข่งรถ]\nกด 'Y' เพื่อเริ่มเล่น", 0x4689FFFF, 844.4230,-2056.6907,12.8672, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0);
    return 1;
}

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys){
    if(!LoggedIn[playerid]) return 1;
    if(newkeys & KEY_YES){
        if(IsPlayerInRangeOfPoint(playerid, 3.0, 844.4230,-2056.6907,12.8672)){ // แข่งรถ
            Dialog_ShowEasy(playerid, SelectTypeRacing, DIALOG_STYLE_LIST, "การแข่งขัน Racing", "สร้างห้อง\nเข้าร่วมห้อง", "เลือก", "ยกเลิก");
        }
    }
    return 1;
}