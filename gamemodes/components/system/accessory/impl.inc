#if defined _inc_impl
	#undef _inc_impl
#endif

ShowPlayerAccessory(playerid){

    OnPlayerInventory_Close(playerid);

    new string[128];

    new hat[32], glasses[32], body[32], arms[32], allset[64];

    if(PlayerData[playerid][pAccessoryModelHat] != 0) format(hat, 32, PlayerData[playerid][pAccessoryNameHat]);
    else hat = "ไม่มี";
    
    if(PlayerData[playerid][pAccessoryModelGlasses] != 0) format(glasses, 32, PlayerData[playerid][pAccessoryNameGlasses]);
    else glasses = "ไม่มี";

    if(PlayerData[playerid][pAccessoryModelBody] != 0) format(body, 32, PlayerData[playerid][pAccessoryNameBody]);
    else body = "ไม่มี";

    if(PlayerData[playerid][pAccessoryModelArms] != 0) format(arms, 32, PlayerData[playerid][pAccessoryNameArms]);
    else arms = "ไม่มี";

    if(!strcmp(PlayerData[playerid][pAccessoryAllSet], "NULL", true)) allset = "ไม่มี";
    else format(allset, 64, PlayerData[playerid][pAccessoryAllSet]);

    format(string, sizeof(string), "- ส่วนหัว: [%s]\
    \n- ใบหน้า: [%s]\
    \n- ลำตัว: [%s]\
    \n- แขน: [%s]\
    \n- ชุดเซ็ท: [%s]", hat, glasses, body, arms, allset);
    Dialog_ShowEasy(playerid, AccessoryPlayer, DIALOG_STYLE_LIST, "เครื่องแต่งกาย", string, "เลือก", "ยกเลิก");
    return 1;
}

CheckItemIsAccessory(const name[]){
    for (new i = 0; i < MAX_ACC; i ++){

        if(HatDataItem[i][hatitemEx]){
            if (!strcmp(HatDataItem[i][hatitemName], name, true)){
                return 1;
            }
        }

        if(GlassesDataItem[i][glassesitemEx]){
            if (!strcmp(GlassesDataItem[i][glassesitemName], name, true)){
                return 2;
            }
        }
        
        if(BodyDataItem[i][bodyitemEx]){
            if (!strcmp(BodyDataItem[i][bodyitemName], name, true)){
                return 3;
            }
        }
        
        if(HandsDataItem[i][handsitemEx]){
            if (!strcmp(HandsDataItem[i][handsitemName], name, true)){
                return 4;
            }
        }
        
    }
    return -1;
}

forward ShowAccessoryScreen(playerid);
public ShowAccessoryScreen(playerid){

    if(ashowallset[playerid] == 0){
        if(acshowhat[playerid] == 1){
            if(acedithat[playerid] == 1){
                SetPlayerAttachedObject(playerid, 0, achat[playerid], 2, acposhat[playerid][0], acposhat[playerid][1], acposhat[playerid][2], acposhat[playerid][3], acposhat[playerid][4], acposhat[playerid][5], acposhat[playerid][6], acposhat[playerid][7], acposhat[playerid][8]);
            }
            else{
                SetPlayerAttachedObject(playerid, 0, achat[playerid], 2);
            }   
        }

        if(acshowglass[playerid] == 1){
            if(aceditglass[playerid] == 1){
                SetPlayerAttachedObject(playerid, 1, acglass[playerid], 2, acposglass[playerid][0], acposglass[playerid][1], acposglass[playerid][2], acposglass[playerid][3], acposglass[playerid][4], acposglass[playerid][5], acposglass[playerid][6], acposglass[playerid][7], acposglass[playerid][8]);
            }
            else{
                SetPlayerAttachedObject(playerid, 1, acglass[playerid], 2);
            }    
        }

        if(acshowbody[playerid] == 1){
            if(aceditbody[playerid] == 1){
                SetPlayerAttachedObject(playerid, 2, acbody[playerid], 1, acposbody[playerid][0], acposbody[playerid][1], acposbody[playerid][2], acposbody[playerid][3], acposbody[playerid][4], acposbody[playerid][5], acposbody[playerid][6], acposbody[playerid][7], acposbody[playerid][8]);
            }
            else{
                SetPlayerAttachedObject(playerid, 2, acbody[playerid], 1);
            }   
        }

        if(acshowarms[playerid] == 1){
            if(aceditarms[playerid] == 1){
                SetPlayerAttachedObject(playerid, 3, acarms[playerid], acctypearms[playerid], acposarms[playerid][0], acposarms[playerid][1], acposarms[playerid][2], acposarms[playerid][3], acposarms[playerid][4], acposarms[playerid][5], acposarms[playerid][6], acposarms[playerid][7], acposarms[playerid][8]);
            }
            else{
                SetPlayerAttachedObject(playerid, 3, acarms[playerid], acctypearms[playerid]);
            } 
        }
    }
    else{
        ShowPlayerAllSetAccessory(playerid, playerid);
    }
    
    return 1;
}

forward CheckAccessoryShow(playerid, targetid);
public CheckAccessoryShow(playerid, targetid){

    if(PlayerData[targetid][pAccessoryAllSetShow] == 0){
        if(PlayerData[targetid][pAccessoryShowHat] == 1){
            if(PlayerData[targetid][pAccessoryEditHat] == 1){
                SetPlayerAttachedObject(playerid, 0, PlayerData[targetid][pAccessoryModelHat], 2, AccessoryData[targetid][0][0], AccessoryData[targetid][0][1], AccessoryData[targetid][0][2], AccessoryData[targetid][0][3], AccessoryData[targetid][0][4], AccessoryData[targetid][0][5], AccessoryData[targetid][0][6], AccessoryData[targetid][0][7], AccessoryData[targetid][0][8]);
            }
            else{
                SetPlayerAttachedObject(playerid, 0, PlayerData[targetid][pAccessoryModelHat], 2);
            }   
        }

        if(PlayerData[targetid][pAccessoryShowGlasses] == 1){
            if(PlayerData[targetid][pAccessoryEditGlasses] == 1){
                SetPlayerAttachedObject(playerid, 1, PlayerData[targetid][pAccessoryModelGlasses], 2, AccessoryData[targetid][1][0], AccessoryData[targetid][1][1], AccessoryData[targetid][1][2], AccessoryData[targetid][1][3], AccessoryData[targetid][1][4], AccessoryData[targetid][1][5], AccessoryData[targetid][1][6], AccessoryData[targetid][1][7], AccessoryData[targetid][1][8]);
            }
            else{
                SetPlayerAttachedObject(playerid, 1, PlayerData[targetid][pAccessoryModelGlasses], 2);
            }    
        }

        if(PlayerData[targetid][pAccessoryShowBody] == 1){
            if(PlayerData[targetid][pAccessoryEditBody] == 1){
                SetPlayerAttachedObject(playerid, 2, PlayerData[targetid][pAccessoryModelBody], 1, AccessoryData[targetid][2][0], AccessoryData[targetid][2][1], AccessoryData[targetid][2][2], AccessoryData[targetid][2][3], AccessoryData[targetid][2][4], AccessoryData[targetid][2][5], AccessoryData[targetid][2][6], AccessoryData[targetid][2][7], AccessoryData[targetid][2][8]);
            }
            else{
                SetPlayerAttachedObject(playerid, 2, PlayerData[targetid][pAccessoryModelBody], 1);
            }   

            if(PlayerData[targetid][pAccessoryModelBody] == 19878){
                InfoSkate[targetid][sActive] = true;
            }
        }

        if(PlayerData[targetid][pAccessoryShowArms] == 1){
            if(PlayerData[targetid][pAccessoryEditArms] == 1){
                SetPlayerAttachedObject(playerid, 3, PlayerData[targetid][pAccessoryModelArms], PlayerData[targetid][pAccessoryArmsType], AccessoryData[targetid][3][0], AccessoryData[targetid][3][1], AccessoryData[targetid][3][2], AccessoryData[targetid][3][3], AccessoryData[targetid][3][4], AccessoryData[targetid][3][5], AccessoryData[targetid][3][6], AccessoryData[targetid][3][7], AccessoryData[targetid][3][8]);
            }
            else{
                SetPlayerAttachedObject(playerid, 3, PlayerData[targetid][pAccessoryModelArms], PlayerData[targetid][pAccessoryArmsType]);
            } 
        }
    }
    else if(PlayerData[targetid][pAccessoryAllSetShow] == 1){
        ShowPlayerAllSetAccessory(playerid, targetid);
    }
    
    return 1;
}

Dialog:AccessoryPlayer(playerid, response, listitem, inputtext[]){
    if(!response){
        PlayerOpenAccessoryMenu[playerid] = true;
        return 1;
    }
    if(response){
        new caption[128];
        if(listitem == 0){
            if(PlayerData[playerid][pAccessoryModelHat] == 0) return ErrorMsg(playerid, "เกิดข้อผิดพลาด");
            format(caption, sizeof(caption), "%s", PlayerData[playerid][pAccessoryNameHat]);
            Dialog_ShowEasy(playerid, EditHat, DIALOG_STYLE_LIST, caption, "- แสดง/ซ่อน\n- ปรับแต่ง\n- ถอดออก", "เลือก", "ยกเลิก");
        }
        if(listitem == 1){
            if(PlayerData[playerid][pAccessoryModelGlasses] == 0) return ErrorMsg(playerid, "เกิดข้อผิดพลาด");
            format(caption, sizeof(caption), "%s", PlayerData[playerid][pAccessoryNameGlasses]);
            Dialog_ShowEasy(playerid, EditGlasses, DIALOG_STYLE_LIST, caption, "- แสดง/ซ่อน\n- ปรับแต่ง\n- ถอดออก", "เลือก", "ยกเลิก");
        }
        if(listitem == 2){
            if(PlayerData[playerid][pAccessoryModelBody] == 0) return ErrorMsg(playerid, "เกิดข้อผิดพลาด");
            format(caption, sizeof(caption), "%s", PlayerData[playerid][pAccessoryNameBody]);
            Dialog_ShowEasy(playerid, EditBody, DIALOG_STYLE_LIST, caption, "- แสดง/ซ่อน\n- ปรับแต่ง\n- ถอดออก", "เลือก", "ยกเลิก");
        }
        if(listitem == 3){
            if(PlayerData[playerid][pAccessoryModelArms] == 0) return ErrorMsg(playerid, "เกิดข้อผิดพลาด");
            format(caption, sizeof(caption), "%s", PlayerData[playerid][pAccessoryNameArms]);
            Dialog_ShowEasy(playerid, EditArms, DIALOG_STYLE_LIST, caption, "- แสดง/ซ่อน\n- ปรับแต่ง\n- เปลี่ยนข้างของแขน\n- ถอดออก", "เลือก", "ยกเลิก");
        }
        if(listitem == 4){
            if(!strcmp(PlayerData[playerid][pAccessoryAllSet], "NULL", true)) return ErrorMsg(playerid, "เกิดข้อผิดพลาด");
            format(caption, sizeof(caption), "%s", PlayerData[playerid][pAccessoryAllSet]);
            Dialog_ShowEasy(playerid, EditAllSet, DIALOG_STYLE_LIST, caption, "- แสดง/ซ่อน\n- ถอดออก", "เลือก", "ยกเลิก");
        }
    }
    return 1;
}

Dialog:EditAllSet(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        if(listitem == 0){
            if(PlayerData[playerid][pAccessoryAllSetShow] == 0){
                PlayerData[playerid][pAccessoryAllSetShow] = 1;
                RemoveAttachedObject(playerid, 0);
                RemoveAttachedObject(playerid, 1);
                RemoveAttachedObject(playerid, 2);
                RemoveAttachedObject(playerid, 3);

                PlayerData[playerid][pAccessoryShowHat] = 0;
                PlayerData[playerid][pAccessoryShowBody] = 0;
                PlayerData[playerid][pAccessoryShowGlasses] = 0;
                PlayerData[playerid][pAccessoryShowArms] = 0;

                ShowPlayerAllSetAccessory(playerid, playerid);
            }
            else{
                PlayerData[playerid][pAccessoryAllSetShow] = 0;
                RemoveAttachedObject(playerid, 0);
                RemoveAttachedObject(playerid, 1);
                RemoveAttachedObject(playerid, 2);
                RemoveAttachedObject(playerid, 3);
                SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้ซ่อน '%s' ของคุณแล้ว", PlayerData[playerid][pAccessoryAllSet]);
            }
        }
        if(listitem == 1){
            if(ServerRestart) return ErrorMsg(playerid, "ฟังก์ชั่นนี้ถูกปิดใช้งานชั่วคราว");
            if(!strcmp(PlayerData[playerid][pAccessoryAllSet], "NULL", true)) return ErrorMsg(playerid, "เกิดข้อผิดพลาดกรุณาแจ้งผู้ดูแลระบบ");
            SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้ถอด '%s' ออกเรียบร้อยแล้ว", PlayerData[playerid][pAccessoryAllSet]);

            new id = PlayerInventory_AddItem(playerid, PlayerData[playerid][pAccessoryAllSet], 2386, 1);
			if (id == -1){
				return SendClientMessageEx(playerid, COLOR_RED, "[ระบบ] {FFFFFF}ความจุของกระเป๋าไม่เพียงพอ (%d/%d) หรือ จำนวนไอเท็มชิ้นนั้นของคุณเต็มแล้ว", PlayerInventory_Items(playerid), PlayerData[playerid][pMaxItem]);
			}
            format(PlayerData[playerid][pAccessoryAllSet], 64, "NULL");
            PlayerData[playerid][pAccessoryAllSetShow] = 0;
            RemoveAttachedObject(playerid, 0);
            RemoveAttachedObject(playerid, 1);
            RemoveAttachedObject(playerid, 2);
            RemoveAttachedObject(playerid, 3);
        }
    }
    return 1;
}

Dialog:EditHat(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        if(listitem == 0){
            if(PlayerData[playerid][pAccessoryShowHat] == 0){

                if(PlayerData[playerid][pAccessoryAllSetShow] == 1) return ErrorMsg(playerid, "คุณต้องปิดชุดเซ็ทก่อน");

                PlayerData[playerid][pAccessoryShowHat] = 1;
                if(PlayerData[playerid][pAccessoryEditHat] == 1){
                    SetPlayerAttachedObject(playerid, 0, PlayerData[playerid][pAccessoryModelHat], 2, AccessoryData[playerid][0][0], AccessoryData[playerid][0][1], AccessoryData[playerid][0][2], AccessoryData[playerid][0][3], AccessoryData[playerid][0][4], AccessoryData[playerid][0][5], AccessoryData[playerid][0][6], AccessoryData[playerid][0][7], AccessoryData[playerid][0][8]);
                }
                else{
                    SetPlayerAttachedObject(playerid, 0, PlayerData[playerid][pAccessoryModelHat], 2);
                }   
                SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้เปิดแสดง '%s' ของคุณแล้ว", PlayerData[playerid][pAccessoryNameHat]);
            }
            else if(PlayerData[playerid][pAccessoryShowHat] == 1){
                PlayerData[playerid][pAccessoryShowHat] = 0;
                RemoveAttachedObject(playerid, 0);
                SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้ซ่อน '%s' ของคุณแล้ว", PlayerData[playerid][pAccessoryNameHat]);
            }
            ClearAnimations(playerid);
            ApplyAnimation(playerid, "goggles", "goggles_put_on", 4.1, 0, 0, 0, 0, 0, 1);
        }
        if(listitem == 1){
            if(PlayerData[playerid][pAccessoryShowHat] == 0) return ErrorMsg(playerid, "คุณต้องกด 'แสดง' หมวกของคุณก่อน");
            if(IsAndroidPlayer(playerid)){
                LoadPlayerTextDrawMoveObject(playerid);
                PlayerEditObjectSlot[playerid] = 0;
                PlayerEditObjectType[playerid] = 1;
                EditingObjectMobile(playerid);
            }
            else{
                SetPVarInt(playerid, "EditHat", 1);
                EditAttachedObject(playerid, 0);
                SendClientMessage(playerid, COLOR_ORANGE, "[คำแนะนำ]: หากต้องการหมุนมุมกล้องให้กดปุ่ม 'SpaceBar' ค้างไว้แล้วหมุนเมาส์");
            }
        }
        if(listitem == 2){
            if(ServerRestart) return ErrorMsg(playerid, "ฟังก์ชั่นนี้ถูกปิดใช้งานชั่วคราว");
            if(!strcmp(PlayerData[playerid][pAccessoryNameHat], "NULL", true)) return ErrorMsg(playerid, "เกิดข้อผิดพลาดกรุณาแจ้งผู้ดูแลระบบ");
            SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้ถอด '%s' ออกเรียบร้อยแล้ว", PlayerData[playerid][pAccessoryNameHat]);

            new id = PlayerInventory_AddItem(playerid, PlayerData[playerid][pAccessoryNameHat], PlayerData[playerid][pAccessoryModelHat], 1);
			if (id == -1){
				return SendClientMessageEx(playerid, COLOR_RED, "[ระบบ] {FFFFFF}ความจุของกระเป๋าไม่เพียงพอ (%d/%d) หรือ จำนวนไอเท็มชิ้นนั้นของคุณเต็มแล้ว", PlayerInventory_Items(playerid), PlayerData[playerid][pMaxItem]);
			}
            PlayerData[playerid][pAccessoryModelHat] = 0;
            format(PlayerData[playerid][pAccessoryNameHat], 32, "NULL");
            PlayerData[playerid][pAccessoryShowHat] = 0;
            RemoveAttachedObject(playerid, 0);
        }
    }
    return 1;
}

Dialog:EditGlasses(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        if(listitem == 0){
            if(PlayerData[playerid][pAccessoryShowGlasses] == 0){

                if(PlayerData[playerid][pAccessoryAllSetShow] == 1) return ErrorMsg(playerid, "คุณต้องปิดชุดเซ็ทก่อน");

                PlayerData[playerid][pAccessoryShowGlasses] = 1;
                if(PlayerData[playerid][pAccessoryEditGlasses] == 1){
                    SetPlayerAttachedObject(playerid, 1, PlayerData[playerid][pAccessoryModelGlasses], 2, AccessoryData[playerid][1][0], AccessoryData[playerid][1][1], AccessoryData[playerid][1][2], AccessoryData[playerid][1][3], AccessoryData[playerid][1][4], AccessoryData[playerid][1][5], AccessoryData[playerid][1][6], AccessoryData[playerid][1][7], AccessoryData[playerid][1][8]);
                }
                else{
                    SetPlayerAttachedObject(playerid, 1, PlayerData[playerid][pAccessoryModelGlasses], 2);
                }   
                SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้เปิดแสดง '%s' ของคุณแล้ว", PlayerData[playerid][pAccessoryNameGlasses]);
            }
            else if(PlayerData[playerid][pAccessoryShowGlasses] == 1){
                PlayerData[playerid][pAccessoryShowGlasses] = 0;
                RemoveAttachedObject(playerid, 1);
                SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้ซ่อน '%s' ของคุณแล้ว", PlayerData[playerid][pAccessoryNameGlasses]);
            }
            ClearAnimations(playerid);
            ApplyAnimation(playerid, "goggles", "goggles_put_on", 4.1, 0, 0, 0, 0, 0, 1);
        }
        if(listitem == 1){
            if(PlayerData[playerid][pAccessoryShowGlasses] == 0) return ErrorMsg(playerid, "คุณต้องกด 'แสดง' แว่นตาหรือผ้าปิดปากของคุณก่อน");
            if(IsAndroidPlayer(playerid)){
                LoadPlayerTextDrawMoveObject(playerid);
                PlayerEditObjectSlot[playerid] = 1;
                PlayerEditObjectType[playerid] = 1;
                EditingObjectMobile(playerid);
            }
            else{
                SetPVarInt(playerid, "EditGlasses", 1);
                EditAttachedObject(playerid, 1);
                SendClientMessage(playerid, COLOR_ORANGE, "[คำแนะนำ]: หากต้องการหมุนมุมกล้องให้กดปุ่ม 'SpaceBar' ค้างไว้แล้วหมุนเมาส์");
            }
        }
        if(listitem == 2){
            if(ServerRestart) return ErrorMsg(playerid, "ฟังก์ชั่นนี้ถูกปิดใช้งานชั่วคราว");
            if(!strcmp(PlayerData[playerid][pAccessoryNameGlasses], "NULL", true)) return ErrorMsg(playerid, "เกิดข้อผิดพลาดกรุณาแจ้งผู้ดูแลระบบ");
            SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้ถอด '%s' ออกเรียบร้อยแล้ว", PlayerData[playerid][pAccessoryNameGlasses]);

            new id = PlayerInventory_AddItem(playerid, PlayerData[playerid][pAccessoryNameGlasses], PlayerData[playerid][pAccessoryModelGlasses], 1);
			if (id == -1){
				return SendClientMessageEx(playerid, COLOR_RED, "[ระบบ] {FFFFFF}ความจุของกระเป๋าไม่เพียงพอ (%d/%d) หรือ จำนวนไอเท็มชิ้นนั้นของคุณเต็มแล้ว", PlayerInventory_Items(playerid), PlayerData[playerid][pMaxItem]);
			}
            PlayerData[playerid][pAccessoryModelGlasses] = 0;
            format(PlayerData[playerid][pAccessoryNameGlasses], 32, "NULL");
            PlayerData[playerid][pAccessoryShowGlasses] = 0;
            RemoveAttachedObject(playerid, 1);
        }
    }
    return 1;
}

Dialog:EditBody(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        if(listitem == 0){
            if(PlayerData[playerid][pAccessoryShowBody] == 0){
                
                if(PlayerData[playerid][pAccessoryAllSetShow] == 1) return ErrorMsg(playerid, "คุณต้องปิดชุดเซ็ทก่อน");

                PlayerData[playerid][pAccessoryShowBody] = 1;
                if(PlayerData[playerid][pAccessoryEditBody] == 1){
                    SetPlayerAttachedObject(playerid, 2, PlayerData[playerid][pAccessoryModelBody], 1, AccessoryData[playerid][2][0], AccessoryData[playerid][2][1], AccessoryData[playerid][2][2], AccessoryData[playerid][2][3], AccessoryData[playerid][2][4], AccessoryData[playerid][2][5], AccessoryData[playerid][2][6], AccessoryData[playerid][2][7], AccessoryData[playerid][2][8]);
                }
                else{
                    SetPlayerAttachedObject(playerid, 2, PlayerData[playerid][pAccessoryModelBody], 1);
                }   

                if(PlayerData[playerid][pAccessoryModelBody] == 19878){
                    InfoSkate[playerid][sActive] = true;
                }

                SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้เปิดแสดง '%s' ของคุณแล้ว", PlayerData[playerid][pAccessoryNameBody]);
            }
            else if(PlayerData[playerid][pAccessoryShowBody] == 1){
                SetTimerEx("FixAnimationPickupSkate", 100, false, "i", playerid);
                ResetSkateBoard(playerid);

                PlayerData[playerid][pAccessoryShowBody] = 0;
                RemoveAttachedObject(playerid, 2);
                SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้ซ่อน '%s' ของคุณแล้ว", PlayerData[playerid][pAccessoryNameBody]);
            }
            ClearAnimations(playerid);
            ApplyAnimation(playerid, "CARRY", "putdwn105", 4.1, 0, 0, 0, 0, 0, 1);
        }
        if(listitem == 1){
            if(PlayerData[playerid][pAccessoryShowBody] == 0) return ErrorMsg(playerid, "คุณต้องกด 'แสดง' ลำตัวของคุณก่อน");
            if(IsAndroidPlayer(playerid)){
                LoadPlayerTextDrawMoveObject(playerid);
                PlayerEditObjectSlot[playerid] = 2;
                PlayerEditObjectType[playerid] = 1;
                EditingObjectMobile(playerid);
            }
            else{
                SetPVarInt(playerid, "EditBody", 1);
                EditAttachedObject(playerid, 2);
                SendClientMessage(playerid, COLOR_ORANGE, "[คำแนะนำ]: หากต้องการหมุนมุมกล้องให้กดปุ่ม 'SpaceBar' ค้างไว้แล้วหมุนเมาส์");
            }
        }
        if(listitem == 2){
            if(ServerRestart) return ErrorMsg(playerid, "ฟังก์ชั่นนี้ถูกปิดใช้งานชั่วคราว");
            if(!strcmp(PlayerData[playerid][pAccessoryNameBody], "NULL", true)) return ErrorMsg(playerid, "เกิดข้อผิดพลาดกรุณาแจ้งผู้ดูแลระบบ");
            SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้ถอด '%s' ออกเรียบร้อยแล้ว", PlayerData[playerid][pAccessoryNameBody]);

            SetTimerEx("FixAnimationPickupSkate", 100, false, "i", playerid);
            ResetSkateBoard(playerid);

            new id = PlayerInventory_AddItem(playerid, PlayerData[playerid][pAccessoryNameBody], PlayerData[playerid][pAccessoryModelBody], 1);
			if (id == -1){
				return SendClientMessageEx(playerid, COLOR_RED, "[ระบบ] {FFFFFF}ความจุของกระเป๋าไม่เพียงพอ (%d/%d) หรือ จำนวนไอเท็มชิ้นนั้นของคุณเต็มแล้ว", PlayerInventory_Items(playerid), PlayerData[playerid][pMaxItem]);
			}
            PlayerData[playerid][pAccessoryModelBody] = 0;
            format(PlayerData[playerid][pAccessoryNameBody], 32, "NULL");
            PlayerData[playerid][pAccessoryShowBody] = 0;
            RemoveAttachedObject(playerid, 2);
        }
    }
    return 1;
}

Dialog:EditArms(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        if(listitem == 0){
            if(PlayerData[playerid][pAccessoryShowArms] == 0){

                if(PlayerData[playerid][pAccessoryAllSetShow] == 1) return ErrorMsg(playerid, "คุณต้องปิดชุดเซ็ทก่อน");

                PlayerData[playerid][pAccessoryShowArms] = 1;
                if(PlayerData[playerid][pAccessoryEditArms] == 1){
                    SetPlayerAttachedObject(playerid, 3, PlayerData[playerid][pAccessoryModelArms], PlayerData[playerid][pAccessoryArmsType], AccessoryData[playerid][3][0], AccessoryData[playerid][3][1], AccessoryData[playerid][3][2], AccessoryData[playerid][3][3], AccessoryData[playerid][3][4], AccessoryData[playerid][3][5], AccessoryData[playerid][3][6], AccessoryData[playerid][3][7], AccessoryData[playerid][3][8]);
                }
                else{
                    SetPlayerAttachedObject(playerid, 3, PlayerData[playerid][pAccessoryModelArms], PlayerData[playerid][pAccessoryArmsType]);
                }   
                SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้เปิดแสดง '%s' ของคุณแล้ว", PlayerData[playerid][pAccessoryNameArms]);
            }
            else if(PlayerData[playerid][pAccessoryShowArms] == 1){
                PlayerData[playerid][pAccessoryShowArms] = 0;
                RemoveAttachedObject(playerid, 3);
                SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้ซ่อน '%s' ของคุณแล้ว", PlayerData[playerid][pAccessoryNameArms]);
            }
            ClearAnimations(playerid);
            ApplyAnimation(playerid, "BD_FIRE", "wash_up", 4.1, 0, 0, 0, 0, 0, 1);
        }
        if(listitem == 1){
            if(PlayerData[playerid][pAccessoryShowArms] == 0) return ErrorMsg(playerid, "คุณต้องกด 'แสดง' มือของคุณก่อน");
            if(IsAndroidPlayer(playerid)){
                LoadPlayerTextDrawMoveObject(playerid);
                PlayerEditObjectSlot[playerid] = 3;
                PlayerEditObjectType[playerid] = 1;
                EditingObjectMobile(playerid);
            }
            else{
                SetPVarInt(playerid, "EditArms", 1);
                EditAttachedObject(playerid, 3);
                SendClientMessage(playerid, COLOR_ORANGE, "[คำแนะนำ]: หากต้องการหมุนมุมกล้องให้กดปุ่ม 'SpaceBar' ค้างไว้แล้วหมุนเมาส์");
            }
            
            
        }
        if(listitem == 2){
            if(PlayerData[playerid][pAccessoryShowArms] == 1) return ErrorMsg(playerid, "คุณต้องกด 'ปิดการแสดง' มือของคุณก่อน");
            if(PlayerData[playerid][pAccessoryArmsType] == 6){
                PlayerData[playerid][pAccessoryArmsType] = 5;
                SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้เปลี่ยน '%s' ของคุณไปไว้ที่ 'มือซ้าย' แล้ว", PlayerData[playerid][pAccessoryNameArms]);
            }
            else if(PlayerData[playerid][pAccessoryArmsType] == 5){
                PlayerData[playerid][pAccessoryArmsType] = 6;
                SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้เปลี่ยน '%s' ของคุณไปไว้ที่ 'มือขวา' แล้ว", PlayerData[playerid][pAccessoryNameArms]);
            }
            PlayerData[playerid][pAccessoryEditArms] = 0;
            AccessoryData[playerid][3][0] = 0.0;
            AccessoryData[playerid][3][1] = 0.0;
            AccessoryData[playerid][3][2] = 0.0;
            AccessoryData[playerid][3][3] = 0.0;
            AccessoryData[playerid][3][4] = 0.0;
            AccessoryData[playerid][3][5] = 0.0;
            AccessoryData[playerid][3][6] = 0.0;
            AccessoryData[playerid][3][7] = 0.0;
            AccessoryData[playerid][3][8] = 0.0;
        }
        if(listitem == 3){
            if(ServerRestart) return ErrorMsg(playerid, "ฟังก์ชั่นนี้ถูกปิดใช้งานชั่วคราว");
            if(!strcmp(PlayerData[playerid][pAccessoryNameArms], "NULL", true)) return ErrorMsg(playerid, "เกิดข้อผิดพลาดกรุณาแจ้งผู้ดูแลระบบ");
            SendClientMessageEx(playerid, COLOR_YELLOW, "- คุณได้ถอด '%s' ออกเรียบร้อยแล้ว", PlayerData[playerid][pAccessoryNameArms]);

            new id = PlayerInventory_AddItem(playerid, PlayerData[playerid][pAccessoryNameArms], PlayerData[playerid][pAccessoryModelArms], 1);
			if (id == -1){
				return SendClientMessageEx(playerid, COLOR_RED, "[ระบบ] {FFFFFF}ความจุของกระเป๋าไม่เพียงพอ (%d/%d) หรือ จำนวนไอเท็มชิ้นนั้นของคุณเต็มแล้ว", PlayerInventory_Items(playerid), PlayerData[playerid][pMaxItem]);
			}
            PlayerData[playerid][pAccessoryModelArms] = 0;
            format(PlayerData[playerid][pAccessoryNameArms], 32, "NULL");
            PlayerData[playerid][pAccessoryShowArms] = 0;
            PlayerData[playerid][pAccessoryArmsType] = 0;
            RemoveAttachedObject(playerid, 3);
        }
    }
    return 1;
}

HideEditingObject(playerid){
    for(new i=0; i<MAX_MOVEOBJECT_TEXT; i++){
        PlayerTextDrawHide(playerid, MoveObjectTextDraw[playerid][i]);
        PlayerTextDrawDestroy(playerid, MoveObjectTextDraw[playerid][i]);
    }
    CancelSelectTextDraw(playerid);
    if(PlayerEditObjectSlot[playerid] == 0){
        if(PlayerData[playerid][pAccessoryEditHat] == 0){
            PlayerData[playerid][pAccessoryEditHat] = 1;
        }
    }
    if(PlayerEditObjectSlot[playerid] == 1){
        if(PlayerData[playerid][pAccessoryEditGlasses] == 0){
            PlayerData[playerid][pAccessoryEditGlasses] = 1;
        }
    }
    if(PlayerEditObjectSlot[playerid] == 2){
        if(PlayerData[playerid][pAccessoryEditBody] == 0){
            PlayerData[playerid][pAccessoryEditBody] = 1;
        }
    }
    if(PlayerEditObjectSlot[playerid] == 3){
        if(PlayerData[playerid][pAccessoryEditArms] == 0){
            PlayerData[playerid][pAccessoryEditArms] = 1;
        }
    }
    PlayerEditingObject[playerid] = 0;
	PlayerEditObjectSlot[playerid] = -1;
	PlayerEditObjectType[playerid] = 0;
    return 1;
}

EditingObjectMobile(playerid){
    for(new i=0; i<MAX_MOVEOBJECT_TEXT; i++){
        PlayerTextDrawShow(playerid, MoveObjectTextDraw[playerid][i]);
    }

    PlayerEditingObject[playerid] = 1;

    SelectTextDraw(playerid, 0xFF7800AA);
    SendClientMessage(playerid, -1, "------------------------------------------------------");
    SendClientMessage(playerid, COLOR_YELLOW, "- หากคุณต้องการหมุนให้คลิกที่ 'ROTATE' เพื่อเปลี่ยนระบบเป็นการหมุนเครื่องแต่งกาย");
    SendClientMessage(playerid, COLOR_RED, "- หากคุณทำการแต่งเสร็จแล้วให้กดปุ่ม 'SAVE' เพื่อทำการเซฟตำแหน่งของเครื่องแต่งกาย");
    SendClientMessage(playerid, -1, "------------------------------------------------------");

    if(PlayerEditObjectSlot[playerid] == 0){
        if(PlayerData[playerid][pAccessoryEditHat] == 0){
            AccessoryData[playerid][0][0] = 0.1600;
            AccessoryData[playerid][0][1] = -0.0199;
            AccessoryData[playerid][0][2] = 0.0050;
            AccessoryData[playerid][0][3] = 173.3999;
            AccessoryData[playerid][0][4] = 0.0000;
            AccessoryData[playerid][0][5] = 18.7000;
            AccessoryData[playerid][0][6] = 1.1000;
            AccessoryData[playerid][0][7] = 1.1360;
            AccessoryData[playerid][0][8] = 1.2680;
            SetPlayerAttachedObject(playerid, 0, PlayerData[playerid][pAccessoryModelHat], 2, AccessoryData[playerid][0][0], AccessoryData[playerid][0][1], AccessoryData[playerid][0][2], AccessoryData[playerid][0][3], AccessoryData[playerid][0][4], AccessoryData[playerid][0][5], AccessoryData[playerid][0][6], AccessoryData[playerid][0][7], AccessoryData[playerid][0][8]);
        }
    }

    if(PlayerEditObjectSlot[playerid] == 1){
        if(PlayerData[playerid][pAccessoryEditGlasses] == 0){
            AccessoryData[playerid][1][0] = 0.0850;
            AccessoryData[playerid][1][1] = 0.0470;
            AccessoryData[playerid][1][2] = -0.0100;
            AccessoryData[playerid][1][3] = 9.0000;
            AccessoryData[playerid][1][4] = 89.9000;
            AccessoryData[playerid][1][5] = 83.9000;
            AccessoryData[playerid][1][6] = 1.0000;
            AccessoryData[playerid][1][7] = 1.0000;
            AccessoryData[playerid][1][8] = 1.0000;
            SetPlayerAttachedObject(playerid, 1, PlayerData[playerid][pAccessoryModelGlasses], 2, AccessoryData[playerid][1][0], AccessoryData[playerid][1][1], AccessoryData[playerid][1][2], AccessoryData[playerid][1][3], AccessoryData[playerid][1][4], AccessoryData[playerid][1][5], AccessoryData[playerid][1][6], AccessoryData[playerid][1][7], AccessoryData[playerid][1][8]);
        }
    }

    if(PlayerEditObjectSlot[playerid] == 2){
        if(PlayerData[playerid][pAccessoryEditBody] == 0){
            AccessoryData[playerid][2][0] = 0.0370;
            AccessoryData[playerid][2][1] = 0.0509;
            AccessoryData[playerid][2][2] = 0.0000;
            AccessoryData[playerid][2][3] = 0.0000;
            AccessoryData[playerid][2][4] = -2.2000;
            AccessoryData[playerid][2][5] = 0.0000;
            AccessoryData[playerid][2][6] = 1.1269;
            AccessoryData[playerid][2][7] = 1.1900;
            AccessoryData[playerid][2][8] = 1.1260;
            SetPlayerAttachedObject(playerid, 2, PlayerData[playerid][pAccessoryModelBody], 1, AccessoryData[playerid][2][0], AccessoryData[playerid][2][1], AccessoryData[playerid][2][2], AccessoryData[playerid][2][3], AccessoryData[playerid][2][4], AccessoryData[playerid][2][5], AccessoryData[playerid][2][6], AccessoryData[playerid][2][7], AccessoryData[playerid][2][8]);
        }
    }

    if(PlayerEditObjectSlot[playerid] == 3){
        if(PlayerData[playerid][pAccessoryEditArms] == 0){

            if(PlayerData[playerid][pAccessoryArmsType] == 6){
                AccessoryData[playerid][3][0] = 0.0799;
                AccessoryData[playerid][3][1] = 0.0549;
                AccessoryData[playerid][3][2] = 0.0000;
                AccessoryData[playerid][3][3] = 93.8999;
                AccessoryData[playerid][3][4] = 0.0000;
                AccessoryData[playerid][3][5] = 0.0000;
                AccessoryData[playerid][3][6] = 1.0000;
                AccessoryData[playerid][3][7] = 1.0000;
                AccessoryData[playerid][3][8] = 1.0000;
            }
            if(PlayerData[playerid][pAccessoryArmsType] == 5){
                AccessoryData[playerid][3][0] = 0.0939;
                AccessoryData[playerid][3][1] = 0.0579;
                AccessoryData[playerid][3][2] = 0.0000;
                AccessoryData[playerid][3][3] = -114.2000;
                AccessoryData[playerid][3][4] = 0.0000;
                AccessoryData[playerid][3][5] = 0.0000;
                AccessoryData[playerid][3][6] = 1.0000;
                AccessoryData[playerid][3][7] = 1.0000;
                AccessoryData[playerid][3][8] = 1.0000;
            }
            SetPlayerAttachedObject(playerid, 3, PlayerData[playerid][pAccessoryModelArms], PlayerData[playerid][pAccessoryArmsType], AccessoryData[playerid][3][0], AccessoryData[playerid][3][1], AccessoryData[playerid][3][2], AccessoryData[playerid][3][3], AccessoryData[playerid][3][4], AccessoryData[playerid][3][5], AccessoryData[playerid][3][6], AccessoryData[playerid][3][7], AccessoryData[playerid][3][8]);
        }
    }
    return 1;
}

ShowPlayerAllSetAccessory(playerid, targetid){
    if(!strcmp(PlayerData[targetid][pAccessoryAllSet], "Lupin Set", true)){
        SetPlayerAttachedObject(playerid,0,19352,2,0.102999,0.000000,0.000000,0.000000,86.600021,92.200004,1.266999,1.069999,1.441999);
        SetPlayerAttachedObject(playerid,1,19349,2,0.083999,0.102000,0.036999,-76.300086,177.599990,97.500030,1.000000,1.000000,1.000000);
        SetPlayerAttachedObject(playerid,2,19348,5,-0.054999,-0.120999,-0.322999,-25.500011,17.800003,9.700005,1.358999,1.301998,1.105998);
        SetPlayerAttachedObject(playerid,3,19351,2,0.024000,0.112999,0.000000,0.000000,0.000000,-81.900032,1.000000,1.775999,1.243999);
    }
    return 1;
}

LoadPlayerTextDrawMoveObject(playerid){
    MoveObjectTextDraw[playerid][0] = CreatePlayerTextDraw(playerid, 241.000000, 147.000000, "MOVE");
    PlayerTextDrawFont(playerid, MoveObjectTextDraw[playerid][0], 2);
    PlayerTextDrawLetterSize(playerid, MoveObjectTextDraw[playerid][0], 0.229166, 1.300000);
    PlayerTextDrawTextSize(playerid, MoveObjectTextDraw[playerid][0], 16.500000, 45.500000);
    PlayerTextDrawSetOutline(playerid, MoveObjectTextDraw[playerid][0], 1);
    PlayerTextDrawSetShadow(playerid, MoveObjectTextDraw[playerid][0], 0);
    PlayerTextDrawAlignment(playerid, MoveObjectTextDraw[playerid][0], 2);
    PlayerTextDrawColor(playerid, MoveObjectTextDraw[playerid][0], -1);
    PlayerTextDrawBackgroundColor(playerid, MoveObjectTextDraw[playerid][0], 255);
    PlayerTextDrawBoxColor(playerid, MoveObjectTextDraw[playerid][0], 100);
    PlayerTextDrawUseBox(playerid, MoveObjectTextDraw[playerid][0], 1);
    PlayerTextDrawSetProportional(playerid, MoveObjectTextDraw[playerid][0], 1);
    PlayerTextDrawSetSelectable(playerid, MoveObjectTextDraw[playerid][0], 1);

    MoveObjectTextDraw[playerid][1] = CreatePlayerTextDraw(playerid, 317.000000, 147.000000, "ROTATE");
    PlayerTextDrawFont(playerid, MoveObjectTextDraw[playerid][1], 2);
    PlayerTextDrawLetterSize(playerid, MoveObjectTextDraw[playerid][1], 0.229166, 1.300000);
    PlayerTextDrawTextSize(playerid, MoveObjectTextDraw[playerid][1], 16.500000, 45.500000);
    PlayerTextDrawSetOutline(playerid, MoveObjectTextDraw[playerid][1], 1);
    PlayerTextDrawSetShadow(playerid, MoveObjectTextDraw[playerid][1], 0);
    PlayerTextDrawAlignment(playerid, MoveObjectTextDraw[playerid][1], 2);
    PlayerTextDrawColor(playerid, MoveObjectTextDraw[playerid][1], -1);
    PlayerTextDrawBackgroundColor(playerid, MoveObjectTextDraw[playerid][1], 255);
    PlayerTextDrawBoxColor(playerid, MoveObjectTextDraw[playerid][1], 100);
    PlayerTextDrawUseBox(playerid, MoveObjectTextDraw[playerid][1], 1);
    PlayerTextDrawSetProportional(playerid, MoveObjectTextDraw[playerid][1], 1);
    PlayerTextDrawSetSelectable(playerid, MoveObjectTextDraw[playerid][1], 1);

    MoveObjectTextDraw[playerid][2] = CreatePlayerTextDraw(playerid, 391.000000, 147.000000, "SAVE");
    PlayerTextDrawFont(playerid, MoveObjectTextDraw[playerid][2], 2);
    PlayerTextDrawLetterSize(playerid, MoveObjectTextDraw[playerid][2], 0.229166, 1.300000);
    PlayerTextDrawTextSize(playerid, MoveObjectTextDraw[playerid][2], 16.500000, 45.500000);
    PlayerTextDrawSetOutline(playerid, MoveObjectTextDraw[playerid][2], 1);
    PlayerTextDrawSetShadow(playerid, MoveObjectTextDraw[playerid][2], 0);
    PlayerTextDrawAlignment(playerid, MoveObjectTextDraw[playerid][2], 2);
    PlayerTextDrawColor(playerid, MoveObjectTextDraw[playerid][2], -1);
    PlayerTextDrawBackgroundColor(playerid, MoveObjectTextDraw[playerid][2], 255);
    PlayerTextDrawBoxColor(playerid, MoveObjectTextDraw[playerid][2], 100);
    PlayerTextDrawUseBox(playerid, MoveObjectTextDraw[playerid][2], 1);
    PlayerTextDrawSetProportional(playerid, MoveObjectTextDraw[playerid][2], 1);
    PlayerTextDrawSetSelectable(playerid, MoveObjectTextDraw[playerid][2], 1);

    MoveObjectTextDraw[playerid][3] = CreatePlayerTextDraw(playerid, 189.000000, 240.000000, "_");
    PlayerTextDrawFont(playerid, MoveObjectTextDraw[playerid][3], 1);
    PlayerTextDrawLetterSize(playerid, MoveObjectTextDraw[playerid][3], 0.600000, 9.250002);
    PlayerTextDrawTextSize(playerid, MoveObjectTextDraw[playerid][3], 298.500000, 80.500000);
    PlayerTextDrawSetOutline(playerid, MoveObjectTextDraw[playerid][3], 1);
    PlayerTextDrawSetShadow(playerid, MoveObjectTextDraw[playerid][3], 0);
    PlayerTextDrawAlignment(playerid, MoveObjectTextDraw[playerid][3], 2);
    PlayerTextDrawColor(playerid, MoveObjectTextDraw[playerid][3], -1);
    PlayerTextDrawBackgroundColor(playerid, MoveObjectTextDraw[playerid][3], 255);
    PlayerTextDrawBoxColor(playerid, MoveObjectTextDraw[playerid][3], 135);
    PlayerTextDrawUseBox(playerid, MoveObjectTextDraw[playerid][3], 1);
    PlayerTextDrawSetProportional(playerid, MoveObjectTextDraw[playerid][3], 1);
    PlayerTextDrawSetSelectable(playerid, MoveObjectTextDraw[playerid][3], 0);

    MoveObjectTextDraw[playerid][4] = CreatePlayerTextDraw(playerid, 179.000000, 247.000000, "ld_beat:up");
    PlayerTextDrawFont(playerid, MoveObjectTextDraw[playerid][4], 4);
    PlayerTextDrawLetterSize(playerid, MoveObjectTextDraw[playerid][4], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, MoveObjectTextDraw[playerid][4], 19.500000, 21.500000);
    PlayerTextDrawSetOutline(playerid, MoveObjectTextDraw[playerid][4], 1);
    PlayerTextDrawSetShadow(playerid, MoveObjectTextDraw[playerid][4], 0);
    PlayerTextDrawAlignment(playerid, MoveObjectTextDraw[playerid][4], 1);
    PlayerTextDrawColor(playerid, MoveObjectTextDraw[playerid][4], -1);
    PlayerTextDrawBackgroundColor(playerid, MoveObjectTextDraw[playerid][4], 255);
    PlayerTextDrawBoxColor(playerid, MoveObjectTextDraw[playerid][4], 50);
    PlayerTextDrawUseBox(playerid, MoveObjectTextDraw[playerid][4], 1);
    PlayerTextDrawSetProportional(playerid, MoveObjectTextDraw[playerid][4], 1);
    PlayerTextDrawSetSelectable(playerid, MoveObjectTextDraw[playerid][4], 1);

    MoveObjectTextDraw[playerid][5] = CreatePlayerTextDraw(playerid, 179.000000, 295.000000, "ld_beat:down");
    PlayerTextDrawFont(playerid, MoveObjectTextDraw[playerid][5], 4);
    PlayerTextDrawLetterSize(playerid, MoveObjectTextDraw[playerid][5], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, MoveObjectTextDraw[playerid][5], 19.500000, 21.500000);
    PlayerTextDrawSetOutline(playerid, MoveObjectTextDraw[playerid][5], 1);
    PlayerTextDrawSetShadow(playerid, MoveObjectTextDraw[playerid][5], 0);
    PlayerTextDrawAlignment(playerid, MoveObjectTextDraw[playerid][5], 1);
    PlayerTextDrawColor(playerid, MoveObjectTextDraw[playerid][5], -1);
    PlayerTextDrawBackgroundColor(playerid, MoveObjectTextDraw[playerid][5], 255);
    PlayerTextDrawBoxColor(playerid, MoveObjectTextDraw[playerid][5], 50);
    PlayerTextDrawUseBox(playerid, MoveObjectTextDraw[playerid][5], 1);
    PlayerTextDrawSetProportional(playerid, MoveObjectTextDraw[playerid][5], 1);
    PlayerTextDrawSetSelectable(playerid, MoveObjectTextDraw[playerid][5], 1);

    MoveObjectTextDraw[playerid][6] = CreatePlayerTextDraw(playerid, 157.000000, 271.000000, "ld_beat:left");
    PlayerTextDrawFont(playerid, MoveObjectTextDraw[playerid][6], 4);
    PlayerTextDrawLetterSize(playerid, MoveObjectTextDraw[playerid][6], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, MoveObjectTextDraw[playerid][6], 19.500000, 21.500000);
    PlayerTextDrawSetOutline(playerid, MoveObjectTextDraw[playerid][6], 1);
    PlayerTextDrawSetShadow(playerid, MoveObjectTextDraw[playerid][6], 0);
    PlayerTextDrawAlignment(playerid, MoveObjectTextDraw[playerid][6], 1);
    PlayerTextDrawColor(playerid, MoveObjectTextDraw[playerid][6], -1);
    PlayerTextDrawBackgroundColor(playerid, MoveObjectTextDraw[playerid][6], 255);
    PlayerTextDrawBoxColor(playerid, MoveObjectTextDraw[playerid][6], 50);
    PlayerTextDrawUseBox(playerid, MoveObjectTextDraw[playerid][6], 1);
    PlayerTextDrawSetProportional(playerid, MoveObjectTextDraw[playerid][6], 1);
    PlayerTextDrawSetSelectable(playerid, MoveObjectTextDraw[playerid][6], 1);

    MoveObjectTextDraw[playerid][7] = CreatePlayerTextDraw(playerid, 200.000000, 271.000000, "ld_beat:right");
    PlayerTextDrawFont(playerid, MoveObjectTextDraw[playerid][7], 4);
    PlayerTextDrawLetterSize(playerid, MoveObjectTextDraw[playerid][7], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, MoveObjectTextDraw[playerid][7], 19.500000, 21.500000);
    PlayerTextDrawSetOutline(playerid, MoveObjectTextDraw[playerid][7], 1);
    PlayerTextDrawSetShadow(playerid, MoveObjectTextDraw[playerid][7], 0);
    PlayerTextDrawAlignment(playerid, MoveObjectTextDraw[playerid][7], 1);
    PlayerTextDrawColor(playerid, MoveObjectTextDraw[playerid][7], -1);
    PlayerTextDrawBackgroundColor(playerid, MoveObjectTextDraw[playerid][7], 255);
    PlayerTextDrawBoxColor(playerid, MoveObjectTextDraw[playerid][7], 50);
    PlayerTextDrawUseBox(playerid, MoveObjectTextDraw[playerid][7], 1);
    PlayerTextDrawSetProportional(playerid, MoveObjectTextDraw[playerid][7], 1);
    PlayerTextDrawSetSelectable(playerid, MoveObjectTextDraw[playerid][7], 1);

    MoveObjectTextDraw[playerid][8] = CreatePlayerTextDraw(playerid, 188.000000, 216.000000, "MOVE");
    PlayerTextDrawFont(playerid, MoveObjectTextDraw[playerid][8], 2);
    PlayerTextDrawLetterSize(playerid, MoveObjectTextDraw[playerid][8], 0.258332, 1.750000);
    PlayerTextDrawTextSize(playerid, MoveObjectTextDraw[playerid][8], 16.500000, 90.500000);
    PlayerTextDrawSetOutline(playerid, MoveObjectTextDraw[playerid][8], 1);
    PlayerTextDrawSetShadow(playerid, MoveObjectTextDraw[playerid][8], 0);
    PlayerTextDrawAlignment(playerid, MoveObjectTextDraw[playerid][8], 2);
    PlayerTextDrawColor(playerid, MoveObjectTextDraw[playerid][8], -1);
    PlayerTextDrawBackgroundColor(playerid, MoveObjectTextDraw[playerid][8], 255);
    PlayerTextDrawBoxColor(playerid, MoveObjectTextDraw[playerid][8], 110);
    PlayerTextDrawUseBox(playerid, MoveObjectTextDraw[playerid][8], 1);
    PlayerTextDrawSetProportional(playerid, MoveObjectTextDraw[playerid][8], 1);
    PlayerTextDrawSetSelectable(playerid, MoveObjectTextDraw[playerid][8], 0);

    MoveObjectTextDraw[playerid][9] = CreatePlayerTextDraw(playerid, 477.000000, 240.000000, "_");
    PlayerTextDrawFont(playerid, MoveObjectTextDraw[playerid][9], 1);
    PlayerTextDrawLetterSize(playerid, MoveObjectTextDraw[playerid][9], 0.600000, 9.250001);
    PlayerTextDrawTextSize(playerid, MoveObjectTextDraw[playerid][9], 298.500000, 80.500000);
    PlayerTextDrawSetOutline(playerid, MoveObjectTextDraw[playerid][9], 1);
    PlayerTextDrawSetShadow(playerid, MoveObjectTextDraw[playerid][9], 0);
    PlayerTextDrawAlignment(playerid, MoveObjectTextDraw[playerid][9], 2);
    PlayerTextDrawColor(playerid, MoveObjectTextDraw[playerid][9], -1);
    PlayerTextDrawBackgroundColor(playerid, MoveObjectTextDraw[playerid][9], 255);
    PlayerTextDrawBoxColor(playerid, MoveObjectTextDraw[playerid][9], 135);
    PlayerTextDrawUseBox(playerid, MoveObjectTextDraw[playerid][9], 1);
    PlayerTextDrawSetProportional(playerid, MoveObjectTextDraw[playerid][9], 1);
    PlayerTextDrawSetSelectable(playerid, MoveObjectTextDraw[playerid][9], 0);

    MoveObjectTextDraw[playerid][10] = CreatePlayerTextDraw(playerid, 466.000000, 247.000000, "ld_beat:up");
    PlayerTextDrawFont(playerid, MoveObjectTextDraw[playerid][10], 4);
    PlayerTextDrawLetterSize(playerid, MoveObjectTextDraw[playerid][10], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, MoveObjectTextDraw[playerid][10], 19.500000, 21.500000);
    PlayerTextDrawSetOutline(playerid, MoveObjectTextDraw[playerid][10], 1);
    PlayerTextDrawSetShadow(playerid, MoveObjectTextDraw[playerid][10], 0);
    PlayerTextDrawAlignment(playerid, MoveObjectTextDraw[playerid][10], 1);
    PlayerTextDrawColor(playerid, MoveObjectTextDraw[playerid][10], -1);
    PlayerTextDrawBackgroundColor(playerid, MoveObjectTextDraw[playerid][10], 255);
    PlayerTextDrawBoxColor(playerid, MoveObjectTextDraw[playerid][10], 50);
    PlayerTextDrawUseBox(playerid, MoveObjectTextDraw[playerid][10], 1);
    PlayerTextDrawSetProportional(playerid, MoveObjectTextDraw[playerid][10], 1);
    PlayerTextDrawSetSelectable(playerid, MoveObjectTextDraw[playerid][10], 1);

    MoveObjectTextDraw[playerid][11] = CreatePlayerTextDraw(playerid, 466.000000, 295.000000, "ld_beat:down");
    PlayerTextDrawFont(playerid, MoveObjectTextDraw[playerid][11], 4);
    PlayerTextDrawLetterSize(playerid, MoveObjectTextDraw[playerid][11], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, MoveObjectTextDraw[playerid][11], 19.500000, 21.500000);
    PlayerTextDrawSetOutline(playerid, MoveObjectTextDraw[playerid][11], 1);
    PlayerTextDrawSetShadow(playerid, MoveObjectTextDraw[playerid][11], 0);
    PlayerTextDrawAlignment(playerid, MoveObjectTextDraw[playerid][11], 1);
    PlayerTextDrawColor(playerid, MoveObjectTextDraw[playerid][11], -1);
    PlayerTextDrawBackgroundColor(playerid, MoveObjectTextDraw[playerid][11], 255);
    PlayerTextDrawBoxColor(playerid, MoveObjectTextDraw[playerid][11], 50);
    PlayerTextDrawUseBox(playerid, MoveObjectTextDraw[playerid][11], 1);
    PlayerTextDrawSetProportional(playerid, MoveObjectTextDraw[playerid][11], 1);
    PlayerTextDrawSetSelectable(playerid, MoveObjectTextDraw[playerid][11], 1);

    MoveObjectTextDraw[playerid][12] = CreatePlayerTextDraw(playerid, 477.000000, 216.000000, "UP AND DOWN");
    PlayerTextDrawFont(playerid, MoveObjectTextDraw[playerid][12], 2);
    PlayerTextDrawLetterSize(playerid, MoveObjectTextDraw[playerid][12], 0.258332, 1.750000);
    PlayerTextDrawTextSize(playerid, MoveObjectTextDraw[playerid][12], 16.500000, 90.500000);
    PlayerTextDrawSetOutline(playerid, MoveObjectTextDraw[playerid][12], 1);
    PlayerTextDrawSetShadow(playerid, MoveObjectTextDraw[playerid][12], 0);
    PlayerTextDrawAlignment(playerid, MoveObjectTextDraw[playerid][12], 2);
    PlayerTextDrawColor(playerid, MoveObjectTextDraw[playerid][12], -1);
    PlayerTextDrawBackgroundColor(playerid, MoveObjectTextDraw[playerid][12], 255);
    PlayerTextDrawBoxColor(playerid, MoveObjectTextDraw[playerid][12], 110);
    PlayerTextDrawUseBox(playerid, MoveObjectTextDraw[playerid][12], 1);
    PlayerTextDrawSetProportional(playerid, MoveObjectTextDraw[playerid][12], 1);
    PlayerTextDrawSetSelectable(playerid, MoveObjectTextDraw[playerid][12], 0);

    MoveObjectTextDraw[playerid][13] = CreatePlayerTextDraw(playerid, 332.000000, 370.000000, "_");
    PlayerTextDrawFont(playerid, MoveObjectTextDraw[playerid][13], 1);
    PlayerTextDrawLetterSize(playerid, MoveObjectTextDraw[playerid][13], 0.600000, 3.899996);
    PlayerTextDrawTextSize(playerid, MoveObjectTextDraw[playerid][13], 298.500000, 215.500000);
    PlayerTextDrawSetOutline(playerid, MoveObjectTextDraw[playerid][13], 1);
    PlayerTextDrawSetShadow(playerid, MoveObjectTextDraw[playerid][13], 0);
    PlayerTextDrawAlignment(playerid, MoveObjectTextDraw[playerid][13], 2);
    PlayerTextDrawColor(playerid, MoveObjectTextDraw[playerid][13], -1);
    PlayerTextDrawBackgroundColor(playerid, MoveObjectTextDraw[playerid][13], 255);
    PlayerTextDrawBoxColor(playerid, MoveObjectTextDraw[playerid][13], 135);
    PlayerTextDrawUseBox(playerid, MoveObjectTextDraw[playerid][13], 1);
    PlayerTextDrawSetProportional(playerid, MoveObjectTextDraw[playerid][13], 1);
    PlayerTextDrawSetSelectable(playerid, MoveObjectTextDraw[playerid][13], 0);

    MoveObjectTextDraw[playerid][14] = CreatePlayerTextDraw(playerid, 230.000000, 379.000000, "ld_beat:left");
    PlayerTextDrawFont(playerid, MoveObjectTextDraw[playerid][14], 4);
    PlayerTextDrawLetterSize(playerid, MoveObjectTextDraw[playerid][14], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, MoveObjectTextDraw[playerid][14], 19.500000, 21.500000);
    PlayerTextDrawSetOutline(playerid, MoveObjectTextDraw[playerid][14], 1);
    PlayerTextDrawSetShadow(playerid, MoveObjectTextDraw[playerid][14], 0);
    PlayerTextDrawAlignment(playerid, MoveObjectTextDraw[playerid][14], 1);
    PlayerTextDrawColor(playerid, MoveObjectTextDraw[playerid][14], -1);
    PlayerTextDrawBackgroundColor(playerid, MoveObjectTextDraw[playerid][14], 255);
    PlayerTextDrawBoxColor(playerid, MoveObjectTextDraw[playerid][14], 50);
    PlayerTextDrawUseBox(playerid, MoveObjectTextDraw[playerid][14], 1);
    PlayerTextDrawSetProportional(playerid, MoveObjectTextDraw[playerid][14], 1);
    PlayerTextDrawSetSelectable(playerid, MoveObjectTextDraw[playerid][14], 1);

    MoveObjectTextDraw[playerid][15] = CreatePlayerTextDraw(playerid, 262.000000, 379.000000, "ld_beat:right");
    PlayerTextDrawFont(playerid, MoveObjectTextDraw[playerid][15], 4);
    PlayerTextDrawLetterSize(playerid, MoveObjectTextDraw[playerid][15], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, MoveObjectTextDraw[playerid][15], 19.500000, 21.500000);
    PlayerTextDrawSetOutline(playerid, MoveObjectTextDraw[playerid][15], 1);
    PlayerTextDrawSetShadow(playerid, MoveObjectTextDraw[playerid][15], 0);
    PlayerTextDrawAlignment(playerid, MoveObjectTextDraw[playerid][15], 1);
    PlayerTextDrawColor(playerid, MoveObjectTextDraw[playerid][15], -1);
    PlayerTextDrawBackgroundColor(playerid, MoveObjectTextDraw[playerid][15], 255);
    PlayerTextDrawBoxColor(playerid, MoveObjectTextDraw[playerid][15], 50);
    PlayerTextDrawUseBox(playerid, MoveObjectTextDraw[playerid][15], 1);
    PlayerTextDrawSetProportional(playerid, MoveObjectTextDraw[playerid][15], 1);
    PlayerTextDrawSetSelectable(playerid, MoveObjectTextDraw[playerid][15], 1);

    MoveObjectTextDraw[playerid][16] = CreatePlayerTextDraw(playerid, 305.000000, 379.000000, "ld_beat:left");
    PlayerTextDrawFont(playerid, MoveObjectTextDraw[playerid][16], 4);
    PlayerTextDrawLetterSize(playerid, MoveObjectTextDraw[playerid][16], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, MoveObjectTextDraw[playerid][16], 19.500000, 21.500000);
    PlayerTextDrawSetOutline(playerid, MoveObjectTextDraw[playerid][16], 1);
    PlayerTextDrawSetShadow(playerid, MoveObjectTextDraw[playerid][16], 0);
    PlayerTextDrawAlignment(playerid, MoveObjectTextDraw[playerid][16], 1);
    PlayerTextDrawColor(playerid, MoveObjectTextDraw[playerid][16], -1);
    PlayerTextDrawBackgroundColor(playerid, MoveObjectTextDraw[playerid][16], 255);
    PlayerTextDrawBoxColor(playerid, MoveObjectTextDraw[playerid][16], 50);
    PlayerTextDrawUseBox(playerid, MoveObjectTextDraw[playerid][16], 1);
    PlayerTextDrawSetProportional(playerid, MoveObjectTextDraw[playerid][16], 1);
    PlayerTextDrawSetSelectable(playerid, MoveObjectTextDraw[playerid][16], 1);

    MoveObjectTextDraw[playerid][17] = CreatePlayerTextDraw(playerid, 338.000000, 379.000000, "ld_beat:right");
    PlayerTextDrawFont(playerid, MoveObjectTextDraw[playerid][17], 4);
    PlayerTextDrawLetterSize(playerid, MoveObjectTextDraw[playerid][17], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, MoveObjectTextDraw[playerid][17], 19.500000, 21.500000);
    PlayerTextDrawSetOutline(playerid, MoveObjectTextDraw[playerid][17], 1);
    PlayerTextDrawSetShadow(playerid, MoveObjectTextDraw[playerid][17], 0);
    PlayerTextDrawAlignment(playerid, MoveObjectTextDraw[playerid][17], 1);
    PlayerTextDrawColor(playerid, MoveObjectTextDraw[playerid][17], -1);
    PlayerTextDrawBackgroundColor(playerid, MoveObjectTextDraw[playerid][17], 255);
    PlayerTextDrawBoxColor(playerid, MoveObjectTextDraw[playerid][17], 50);
    PlayerTextDrawUseBox(playerid, MoveObjectTextDraw[playerid][17], 1);
    PlayerTextDrawSetProportional(playerid, MoveObjectTextDraw[playerid][17], 1);
    PlayerTextDrawSetSelectable(playerid, MoveObjectTextDraw[playerid][17], 1);

    MoveObjectTextDraw[playerid][18] = CreatePlayerTextDraw(playerid, 382.000000, 379.000000, "ld_beat:left");
    PlayerTextDrawFont(playerid, MoveObjectTextDraw[playerid][18], 4);
    PlayerTextDrawLetterSize(playerid, MoveObjectTextDraw[playerid][18], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, MoveObjectTextDraw[playerid][18], 19.500000, 21.500000);
    PlayerTextDrawSetOutline(playerid, MoveObjectTextDraw[playerid][18], 1);
    PlayerTextDrawSetShadow(playerid, MoveObjectTextDraw[playerid][18], 0);
    PlayerTextDrawAlignment(playerid, MoveObjectTextDraw[playerid][18], 1);
    PlayerTextDrawColor(playerid, MoveObjectTextDraw[playerid][18], -1);
    PlayerTextDrawBackgroundColor(playerid, MoveObjectTextDraw[playerid][18], 255);
    PlayerTextDrawBoxColor(playerid, MoveObjectTextDraw[playerid][18], 50);
    PlayerTextDrawUseBox(playerid, MoveObjectTextDraw[playerid][18], 1);
    PlayerTextDrawSetProportional(playerid, MoveObjectTextDraw[playerid][18], 1);
    PlayerTextDrawSetSelectable(playerid, MoveObjectTextDraw[playerid][18], 1);

    MoveObjectTextDraw[playerid][19] = CreatePlayerTextDraw(playerid, 414.000000, 379.000000, "ld_beat:right");
    PlayerTextDrawFont(playerid, MoveObjectTextDraw[playerid][19], 4);
    PlayerTextDrawLetterSize(playerid, MoveObjectTextDraw[playerid][19], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, MoveObjectTextDraw[playerid][19], 19.500000, 21.500000);
    PlayerTextDrawSetOutline(playerid, MoveObjectTextDraw[playerid][19], 1);
    PlayerTextDrawSetShadow(playerid, MoveObjectTextDraw[playerid][19], 0);
    PlayerTextDrawAlignment(playerid, MoveObjectTextDraw[playerid][19], 1);
    PlayerTextDrawColor(playerid, MoveObjectTextDraw[playerid][19], -1);
    PlayerTextDrawBackgroundColor(playerid, MoveObjectTextDraw[playerid][19], 255);
    PlayerTextDrawBoxColor(playerid, MoveObjectTextDraw[playerid][19], 50);
    PlayerTextDrawUseBox(playerid, MoveObjectTextDraw[playerid][19], 1);
    PlayerTextDrawSetProportional(playerid, MoveObjectTextDraw[playerid][19], 1);
    PlayerTextDrawSetSelectable(playerid, MoveObjectTextDraw[playerid][19], 1);

    MoveObjectTextDraw[playerid][20] = CreatePlayerTextDraw(playerid, 254.000000, 351.000000, "SIZE X");
    PlayerTextDrawFont(playerid, MoveObjectTextDraw[playerid][20], 2);
    PlayerTextDrawLetterSize(playerid, MoveObjectTextDraw[playerid][20], 0.199998, 1.250000);
    PlayerTextDrawTextSize(playerid, MoveObjectTextDraw[playerid][20], 16.500000, 45.500000);
    PlayerTextDrawSetOutline(playerid, MoveObjectTextDraw[playerid][20], 1);
    PlayerTextDrawSetShadow(playerid, MoveObjectTextDraw[playerid][20], 0);
    PlayerTextDrawAlignment(playerid, MoveObjectTextDraw[playerid][20], 2);
    PlayerTextDrawColor(playerid, MoveObjectTextDraw[playerid][20], -1);
    PlayerTextDrawBackgroundColor(playerid, MoveObjectTextDraw[playerid][20], 255);
    PlayerTextDrawBoxColor(playerid, MoveObjectTextDraw[playerid][20], 110);
    PlayerTextDrawUseBox(playerid, MoveObjectTextDraw[playerid][20], 1);
    PlayerTextDrawSetProportional(playerid, MoveObjectTextDraw[playerid][20], 1);
    PlayerTextDrawSetSelectable(playerid, MoveObjectTextDraw[playerid][20], 0);

    MoveObjectTextDraw[playerid][21] = CreatePlayerTextDraw(playerid, 332.000000, 351.000000, "SIZE Y");
    PlayerTextDrawFont(playerid, MoveObjectTextDraw[playerid][21], 2);
    PlayerTextDrawLetterSize(playerid, MoveObjectTextDraw[playerid][21], 0.199998, 1.250000);
    PlayerTextDrawTextSize(playerid, MoveObjectTextDraw[playerid][21], 16.500000, 45.500000);
    PlayerTextDrawSetOutline(playerid, MoveObjectTextDraw[playerid][21], 1);
    PlayerTextDrawSetShadow(playerid, MoveObjectTextDraw[playerid][21], 0);
    PlayerTextDrawAlignment(playerid, MoveObjectTextDraw[playerid][21], 2);
    PlayerTextDrawColor(playerid, MoveObjectTextDraw[playerid][21], -1);
    PlayerTextDrawBackgroundColor(playerid, MoveObjectTextDraw[playerid][21], 255);
    PlayerTextDrawBoxColor(playerid, MoveObjectTextDraw[playerid][21], 110);
    PlayerTextDrawUseBox(playerid, MoveObjectTextDraw[playerid][21], 1);
    PlayerTextDrawSetProportional(playerid, MoveObjectTextDraw[playerid][21], 1);
    PlayerTextDrawSetSelectable(playerid, MoveObjectTextDraw[playerid][21], 0);

    MoveObjectTextDraw[playerid][22] = CreatePlayerTextDraw(playerid, 409.000000, 351.000000, "SIZE Z");
    PlayerTextDrawFont(playerid, MoveObjectTextDraw[playerid][22], 2);
    PlayerTextDrawLetterSize(playerid, MoveObjectTextDraw[playerid][22], 0.199998, 1.250000);
    PlayerTextDrawTextSize(playerid, MoveObjectTextDraw[playerid][22], 16.500000, 45.500000);
    PlayerTextDrawSetOutline(playerid, MoveObjectTextDraw[playerid][22], 1);
    PlayerTextDrawSetShadow(playerid, MoveObjectTextDraw[playerid][22], 0);
    PlayerTextDrawAlignment(playerid, MoveObjectTextDraw[playerid][22], 2);
    PlayerTextDrawColor(playerid, MoveObjectTextDraw[playerid][22], -1);
    PlayerTextDrawBackgroundColor(playerid, MoveObjectTextDraw[playerid][22], 255);
    PlayerTextDrawBoxColor(playerid, MoveObjectTextDraw[playerid][22], 110);
    PlayerTextDrawUseBox(playerid, MoveObjectTextDraw[playerid][22], 1);
    PlayerTextDrawSetProportional(playerid, MoveObjectTextDraw[playerid][22], 1);
    PlayerTextDrawSetSelectable(playerid, MoveObjectTextDraw[playerid][22], 0);
    return 1;
}