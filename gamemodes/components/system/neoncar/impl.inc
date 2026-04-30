#if defined _inc_impl
	#undef _inc_impl
#endif


/*  {"Neon Card", 1277}

    CoreVehicles[vehicleid][vehNeonStatus] = 0;
    CoreVehicles[vehicleid][vehNeonColor] = 0;

    CarData[i][carNeonStatus] = 0;
    CarData[i][carNeonColor] = 0;

    //จุดติด Neon
    1017.6605,-917.6010,42.1797
*/

ShowMenuInstallNeon(playerid){
    if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER) return ErrorMsg(playerid, "คุณจะต้องเป็นคนขับ");
    
    new vehicleid = GetPlayerVehicleID(playerid),
        carid = Car_GetID(vehicleid);


    if(CarData[carid][carNeonStatus] != 0 || CoreVehicles[vehicleid][vehNeonStatus] != 0){
        Dialog_ShowEasy(playerid, UnstallNeon, DIALOG_STYLE_MSGBOX, "ยกเลิก Neon สำหรับยานพาหนะ", "คุณแน่ใจหรือไม่? ที่จะยกเลิกการติดตั้ง Neon", "ตกลง", "ยกเลิก");
    }
    else{
        if(PlayerInventory_AllCount(playerid, "Neon Card") < 1) return Dialog_ShowEasy(playerid, ShowOnly, DIALOG_STYLE_MSGBOX, "เกิดข้อผิดพลาด", "คุณไม่มีบัตรติด Neon!", "ตกลง", "");
        new string[128];
        format(string, sizeof(string), "- สีน้ำเงิน\
        \n- สีแดง\
        \n- สีเขียว\
        \n- สีขาว\
        \n- สีชมพู\
        \n- สีเหลือง");
        Dialog_ShowEasy(playerid, InstallNeon, DIALOG_STYLE_LIST, "ติดตั้ง Neon สำหรับยานพาหนะ", string, "ตกลง", "ยกเลิก");
    }
    return 1;
}

Dialog:UnstallNeon(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){
        new vehicleid = GetPlayerVehicleID(playerid), carid = Car_GetID(vehicleid);

        if(carid != -1){

            if(!CarData[carid][carNeonStatus]) return ErrorMsg(playerid, "ยานพาหนะนี้ไม่ได้ติดตั้ง Neon");

            if (!Car_IsOwner(playerid, carid)) return ErrorMsg(playerid, "คุณไม่ใช่เจ้าของรถ");
            CoreVehicles[CarData[carid][carVehicle]][vehNeonStatus] = 0;
            CoreVehicles[CarData[carid][carVehicle]][vehNeonColor] = 0;
            CarData[carid][carNeonStatus] = 0;
            CarData[carid][carNeonColor] = 0;
            for(new i=0; i<4; i++){
                if(IsValidDynamicObject(NeonVehicle[CarData[carid][carVehicle]][i]) && NeonVehicle[CarData[carid][carVehicle]][i]) DestroyDynamicObject(NeonVehicle[CarData[carid][carVehicle]][i]);
                NeonVehicle[CarData[carid][carVehicle]][i] = -1;
            }
            Car_Save(carid);
            SendClientMessage(playerid, COLOR_YELLOW, "- คุณได้ยกเลิกการติดตั้ง Neon เรียบร้อยแล้ว");
        }
    }
    return 1;
}

Dialog:InstallNeon(playerid, response, listitem, inputtext[]){
    if(!response) return 1;
    if(response){

        new vehicleid = GetPlayerVehicleID(playerid),
            carid = Car_GetID(vehicleid);

        if(carid != -1){

            if (!Car_IsOwner(playerid, carid)) return ErrorMsg(playerid, "คุณไม่ใช่เจ้าของรถ");

            if(listitem == 0){
                if(IsPlayerOnBike(carid)){
                    NeonVehicle[CarData[carid][carVehicle]][0] = CreateDynamicObject(18648,0,0,0,0,0,0);
                    NeonVehicle[CarData[carid][carVehicle]][1] = CreateDynamicObject(18648,0,0,0,0,0,0);
                    AttachDynamicObjectToVehicle(NeonVehicle[CarData[carid][carVehicle]][0], CarData[carid][carVehicle], -0.909999, -0.009999, -0.549999, 0.000000, 0.000000, 0.000000);
                    AttachDynamicObjectToVehicle(NeonVehicle[CarData[carid][carVehicle]][1], CarData[carid][carVehicle], 0.914999, -0.009999, -0.549999, 0.000000, 0.000000, 0.000000);
                    GameTextForPlayer(playerid,"~b~~h~blue neon~n~~b~~h~added",2000,3);

                    CoreVehicles[CarData[carid][carVehicle]][vehNeonStatus] = 1;
                    CoreVehicles[CarData[carid][carVehicle]][vehNeonColor] = 1;
                    CarData[carid][carNeonStatus] = 1;
                    CarData[carid][carNeonColor] = 1;
                    Car_Save(carid);
                }
                else{
                    NeonVehicle[CarData[carid][carVehicle]][0] = CreateDynamicObject(18648,0,0,0,0,0,0);
                    NeonVehicle[CarData[carid][carVehicle]][1] = CreateDynamicObject(18648,0,0,0,0,0,0);
                    NeonVehicle[CarData[carid][carVehicle]][2] = CreateDynamicObject(18648,0,0,0,0,0,0);
                    NeonVehicle[CarData[carid][carVehicle]][3] = CreateDynamicObject(18648,0,0,0,0,0,0);
                    AttachDynamicObjectToVehicle(NeonVehicle[CarData[carid][carVehicle]][0], CarData[carid][carVehicle], -0.909999, -0.009999, -0.649999, 0.000000, 0.000000, 0.000000);
                    AttachDynamicObjectToVehicle(NeonVehicle[CarData[carid][carVehicle]][1], CarData[carid][carVehicle], 0.914999, -0.009999, -0.649999, 0.000000, 0.000000, 0.000000);
                    AttachDynamicObjectToVehicle(NeonVehicle[CarData[carid][carVehicle]][2], CarData[carid][carVehicle], 0.034999, 2.225003, -0.629999, 0.000000, 0.000000, -88.589958);
                    AttachDynamicObjectToVehicle(NeonVehicle[CarData[carid][carVehicle]][3], CarData[carid][carVehicle], 0.034999, -2.034998, -0.629999, 0.000000, 0.000000, -88.589958);
                    GameTextForPlayer(playerid,"~b~~h~blue neon~n~~b~~h~added",2000,3);

                    CoreVehicles[CarData[carid][carVehicle]][vehNeonStatus] = 1;
                    CoreVehicles[CarData[carid][carVehicle]][vehNeonColor] = 1;
                    CarData[carid][carNeonStatus] = 1;
                    CarData[carid][carNeonColor] = 1;
                    Car_Save(carid);
                }
                PlayerInventory_Remove(playerid, "Neon Card", 1);
            }
            if(listitem == 1){
                if(IsPlayerOnBike(carid)){
                    NeonVehicle[CarData[carid][carVehicle]][0] = CreateDynamicObject(18647,0,0,0,0,0,0);
                    NeonVehicle[CarData[carid][carVehicle]][1] = CreateDynamicObject(18647,0,0,0,0,0,0);
                    AttachDynamicObjectToVehicle(NeonVehicle[CarData[carid][carVehicle]][0], CarData[carid][carVehicle], -0.909999, -0.009999, -0.549999, 0.000000, 0.000000, 0.000000);
                    AttachDynamicObjectToVehicle(NeonVehicle[CarData[carid][carVehicle]][1], CarData[carid][carVehicle], 0.914999, -0.009999, -0.549999, 0.000000, 0.000000, 0.000000);
                    GameTextForPlayer(playerid,"~r~~h~red neon~n~~r~~h~added",2000,3);

                    CoreVehicles[CarData[carid][carVehicle]][vehNeonStatus] = 1;
                    CoreVehicles[CarData[carid][carVehicle]][vehNeonColor] = 2;
                    CarData[carid][carNeonStatus] = 1;
                    CarData[carid][carNeonColor] = 2;
                    Car_Save(carid);
                }
                else{
                    NeonVehicle[CarData[carid][carVehicle]][0] = CreateDynamicObject(18647,0,0,0,0,0,0);
                    NeonVehicle[CarData[carid][carVehicle]][1] = CreateDynamicObject(18647,0,0,0,0,0,0);
                    NeonVehicle[CarData[carid][carVehicle]][2] = CreateDynamicObject(18647,0,0,0,0,0,0);
                    NeonVehicle[CarData[carid][carVehicle]][3] = CreateDynamicObject(18647,0,0,0,0,0,0);
                    AttachDynamicObjectToVehicle(NeonVehicle[CarData[carid][carVehicle]][0], CarData[carid][carVehicle], -0.909999, -0.009999, -0.649999, 0.000000, 0.000000, 0.000000);
                    AttachDynamicObjectToVehicle(NeonVehicle[CarData[carid][carVehicle]][1], CarData[carid][carVehicle], 0.914999, -0.009999, -0.649999, 0.000000, 0.000000, 0.000000);
                    AttachDynamicObjectToVehicle(NeonVehicle[CarData[carid][carVehicle]][2], CarData[carid][carVehicle], 0.034999, 2.225003, -0.629999, 0.000000, 0.000000, -88.589958);
                    AttachDynamicObjectToVehicle(NeonVehicle[CarData[carid][carVehicle]][3], CarData[carid][carVehicle], 0.034999, -2.034998, -0.629999, 0.000000, 0.000000, -88.589958);
                    GameTextForPlayer(playerid,"~r~~h~red neon~n~~r~~h~added",2000,3);

                    CoreVehicles[CarData[carid][carVehicle]][vehNeonStatus] = 1;
                    CoreVehicles[CarData[carid][carVehicle]][vehNeonColor] = 2;
                    CarData[carid][carNeonStatus] = 1;
                    CarData[carid][carNeonColor] = 2;
                    Car_Save(carid);
                }
                PlayerInventory_Remove(playerid, "Neon Card", 1);
            }
            if(listitem == 2){
                if(IsPlayerOnBike(carid)){
                    NeonVehicle[CarData[carid][carVehicle]][0] = CreateDynamicObject(18649,0,0,0,0,0,0);
                    NeonVehicle[CarData[carid][carVehicle]][1] = CreateDynamicObject(18649,0,0,0,0,0,0);
                    AttachDynamicObjectToVehicle(NeonVehicle[CarData[carid][carVehicle]][0], CarData[carid][carVehicle], -0.909999, -0.009999, -0.549999, 0.000000, 0.000000, 0.000000);
                    AttachDynamicObjectToVehicle(NeonVehicle[CarData[carid][carVehicle]][1], CarData[carid][carVehicle], 0.914999, -0.009999, -0.549999, 0.000000, 0.000000, 0.000000);
                    GameTextForPlayer(playerid,"~g~~h~green neon~n~~g~~h~added",2000,3);

                    CoreVehicles[CarData[carid][carVehicle]][vehNeonStatus] = 1;
                    CoreVehicles[CarData[carid][carVehicle]][vehNeonColor] = 3;
                    CarData[carid][carNeonStatus] = 1;
                    CarData[carid][carNeonColor] = 3;
                    Car_Save(carid);
                }
                else{
                    NeonVehicle[CarData[carid][carVehicle]][0] = CreateDynamicObject(18649,0,0,0,0,0,0);
                    NeonVehicle[CarData[carid][carVehicle]][1] = CreateDynamicObject(18649,0,0,0,0,0,0);
                    NeonVehicle[CarData[carid][carVehicle]][2] = CreateDynamicObject(18649,0,0,0,0,0,0);
                    NeonVehicle[CarData[carid][carVehicle]][3] = CreateDynamicObject(18649,0,0,0,0,0,0);
                    AttachDynamicObjectToVehicle(NeonVehicle[CarData[carid][carVehicle]][0], CarData[carid][carVehicle], -0.909999, -0.009999, -0.649999, 0.000000, 0.000000, 0.000000);
                    AttachDynamicObjectToVehicle(NeonVehicle[CarData[carid][carVehicle]][1], CarData[carid][carVehicle], 0.914999, -0.009999, -0.649999, 0.000000, 0.000000, 0.000000);
                    AttachDynamicObjectToVehicle(NeonVehicle[CarData[carid][carVehicle]][2], CarData[carid][carVehicle], 0.034999, 2.225003, -0.629999, 0.000000, 0.000000, -88.589958);
                    AttachDynamicObjectToVehicle(NeonVehicle[CarData[carid][carVehicle]][3], CarData[carid][carVehicle], 0.034999, -2.034998, -0.629999, 0.000000, 0.000000, -88.589958);
                    GameTextForPlayer(playerid,"~g~~h~green neon~n~~g~~h~added",2000,3);

                    CoreVehicles[CarData[carid][carVehicle]][vehNeonStatus] = 1;
                    CoreVehicles[CarData[carid][carVehicle]][vehNeonColor] = 3;
                    CarData[carid][carNeonStatus] = 1;
                    CarData[carid][carNeonColor] = 3;
                    Car_Save(carid);
                }
                PlayerInventory_Remove(playerid, "Neon Card", 1);
            }
            if(listitem == 3){
                if(IsPlayerOnBike(carid)){
                    NeonVehicle[CarData[carid][carVehicle]][0] = CreateDynamicObject(18652,0,0,0,0,0,0);
                    NeonVehicle[CarData[carid][carVehicle]][1] = CreateDynamicObject(18652,0,0,0,0,0,0);
                    AttachDynamicObjectToVehicle(NeonVehicle[CarData[carid][carVehicle]][0], CarData[carid][carVehicle], -0.909999, -0.009999, -0.549999, 0.000000, 0.000000, 0.000000);
                    AttachDynamicObjectToVehicle(NeonVehicle[CarData[carid][carVehicle]][1], CarData[carid][carVehicle], 0.914999, -0.009999, -0.549999, 0.000000, 0.000000, 0.000000);
                    GameTextForPlayer(playerid,"~w~~h~white neon~n~~w~~h~added",2000,3);

                    CoreVehicles[CarData[carid][carVehicle]][vehNeonStatus] = 1;
                    CoreVehicles[CarData[carid][carVehicle]][vehNeonColor] = 4;
                    CarData[carid][carNeonStatus] = 1;
                    CarData[carid][carNeonColor] = 4;
                    Car_Save(carid);
                }
                else{
                    NeonVehicle[CarData[carid][carVehicle]][0] = CreateDynamicObject(18652,0,0,0,0,0,0);
                    NeonVehicle[CarData[carid][carVehicle]][1] = CreateDynamicObject(18652,0,0,0,0,0,0);
                    NeonVehicle[CarData[carid][carVehicle]][2] = CreateDynamicObject(18652,0,0,0,0,0,0);
                    NeonVehicle[CarData[carid][carVehicle]][3] = CreateDynamicObject(18652,0,0,0,0,0,0);
                    AttachDynamicObjectToVehicle(NeonVehicle[CarData[carid][carVehicle]][0], CarData[carid][carVehicle], -0.909999, -0.009999, -0.649999, 0.000000, 0.000000, 0.000000);
                    AttachDynamicObjectToVehicle(NeonVehicle[CarData[carid][carVehicle]][1], CarData[carid][carVehicle], 0.914999, -0.009999, -0.649999, 0.000000, 0.000000, 0.000000);
                    AttachDynamicObjectToVehicle(NeonVehicle[CarData[carid][carVehicle]][2], CarData[carid][carVehicle], 0.034999, 2.225003, -0.629999, 0.000000, 0.000000, -88.589958);
                    AttachDynamicObjectToVehicle(NeonVehicle[CarData[carid][carVehicle]][3], CarData[carid][carVehicle], 0.034999, -2.034998, -0.629999, 0.000000, 0.000000, -88.589958);
                    GameTextForPlayer(playerid,"~w~~h~white neon~n~~w~~h~added",2000,3);

                    CoreVehicles[CarData[carid][carVehicle]][vehNeonStatus] = 1;
                    CoreVehicles[CarData[carid][carVehicle]][vehNeonColor] = 4;
                    CarData[carid][carNeonStatus] = 1;
                    CarData[carid][carNeonColor] = 4;
                    Car_Save(carid);
                }
                PlayerInventory_Remove(playerid, "Neon Card", 1);
            }
            if(listitem == 4){
                if(IsPlayerOnBike(carid)){
                    NeonVehicle[CarData[carid][carVehicle]][0] = CreateDynamicObject(18651,0,0,0,0,0,0);
                    NeonVehicle[CarData[carid][carVehicle]][1] = CreateDynamicObject(18651,0,0,0,0,0,0);
                    AttachDynamicObjectToVehicle(NeonVehicle[CarData[carid][carVehicle]][0], CarData[carid][carVehicle], -0.909999, -0.009999, -0.549999, 0.000000, 0.000000, 0.000000);
                    AttachDynamicObjectToVehicle(NeonVehicle[CarData[carid][carVehicle]][1], CarData[carid][carVehicle], 0.914999, -0.009999, -0.549999, 0.000000, 0.000000, 0.000000);
                    GameTextForPlayer(playerid,"~p~~h~pink neon~n~~p~~h~added",2000,3);

                    CoreVehicles[CarData[carid][carVehicle]][vehNeonStatus] = 1;
                    CoreVehicles[CarData[carid][carVehicle]][vehNeonColor] = 5;
                    CarData[carid][carNeonStatus] = 1;
                    CarData[carid][carNeonColor] = 5;
                    Car_Save(carid);
                }
                else{
                    NeonVehicle[CarData[carid][carVehicle]][0] = CreateDynamicObject(18651,0,0,0,0,0,0);
                    NeonVehicle[CarData[carid][carVehicle]][1] = CreateDynamicObject(18651,0,0,0,0,0,0);
                    NeonVehicle[CarData[carid][carVehicle]][2] = CreateDynamicObject(18651,0,0,0,0,0,0);
                    NeonVehicle[CarData[carid][carVehicle]][3] = CreateDynamicObject(18651,0,0,0,0,0,0);
                    AttachDynamicObjectToVehicle(NeonVehicle[CarData[carid][carVehicle]][0], CarData[carid][carVehicle], -0.909999, -0.009999, -0.649999, 0.000000, 0.000000, 0.000000);
                    AttachDynamicObjectToVehicle(NeonVehicle[CarData[carid][carVehicle]][1], CarData[carid][carVehicle], 0.914999, -0.009999, -0.649999, 0.000000, 0.000000, 0.000000);
                    AttachDynamicObjectToVehicle(NeonVehicle[CarData[carid][carVehicle]][2], CarData[carid][carVehicle], 0.034999, 2.225003, -0.629999, 0.000000, 0.000000, -88.589958);
                    AttachDynamicObjectToVehicle(NeonVehicle[CarData[carid][carVehicle]][3], CarData[carid][carVehicle], 0.034999, -2.034998, -0.629999, 0.000000, 0.000000, -88.589958);
                    GameTextForPlayer(playerid,"~p~~h~pink neon~n~~p~~h~added",2000,3);

                    CoreVehicles[CarData[carid][carVehicle]][vehNeonStatus] = 1;
                    CoreVehicles[CarData[carid][carVehicle]][vehNeonColor] = 5;
                    CarData[carid][carNeonStatus] = 1;
                    CarData[carid][carNeonColor] = 5;
                    Car_Save(carid);
                }
                PlayerInventory_Remove(playerid, "Neon Card", 1);
            }
            if(listitem == 5){
                if(IsPlayerOnBike(carid)){
                    NeonVehicle[CarData[carid][carVehicle]][0] = CreateDynamicObject(18650,0,0,0,0,0,0);
                    NeonVehicle[CarData[carid][carVehicle]][1] = CreateDynamicObject(18650,0,0,0,0,0,0);
                    AttachDynamicObjectToVehicle(NeonVehicle[CarData[carid][carVehicle]][0], CarData[carid][carVehicle], -0.909999, -0.009999, -0.549999, 0.000000, 0.000000, 0.000000);
                    AttachDynamicObjectToVehicle(NeonVehicle[CarData[carid][carVehicle]][1], CarData[carid][carVehicle], 0.914999, -0.009999, -0.549999, 0.000000, 0.000000, 0.000000);
                    GameTextForPlayer(playerid,"~y~~h~yellow neon~n~~y~~h~added",2000,3);

                    CoreVehicles[CarData[carid][carVehicle]][vehNeonStatus] = 1;
                    CoreVehicles[CarData[carid][carVehicle]][vehNeonColor] = 6;
                    CarData[carid][carNeonStatus] = 1;
                    CarData[carid][carNeonColor] = 6;
                    Car_Save(carid);
                }
                else{
                    NeonVehicle[CarData[carid][carVehicle]][0] = CreateDynamicObject(18650,0,0,0,0,0,0);
                    NeonVehicle[CarData[carid][carVehicle]][1] = CreateDynamicObject(18650,0,0,0,0,0,0);
                    NeonVehicle[CarData[carid][carVehicle]][2] = CreateDynamicObject(18650,0,0,0,0,0,0);
                    NeonVehicle[CarData[carid][carVehicle]][3] = CreateDynamicObject(18650,0,0,0,0,0,0);
                    AttachDynamicObjectToVehicle(NeonVehicle[CarData[carid][carVehicle]][0], CarData[carid][carVehicle], -0.909999, -0.009999, -0.649999, 0.000000, 0.000000, 0.000000);
                    AttachDynamicObjectToVehicle(NeonVehicle[CarData[carid][carVehicle]][1], CarData[carid][carVehicle], 0.914999, -0.009999, -0.649999, 0.000000, 0.000000, 0.000000);
                    AttachDynamicObjectToVehicle(NeonVehicle[CarData[carid][carVehicle]][2], CarData[carid][carVehicle], 0.034999, 2.225003, -0.629999, 0.000000, 0.000000, -88.589958);
                    AttachDynamicObjectToVehicle(NeonVehicle[CarData[carid][carVehicle]][3], CarData[carid][carVehicle], 0.034999, -2.034998, -0.629999, 0.000000, 0.000000, -88.589958);
                    GameTextForPlayer(playerid,"~y~~h~yellow neon~n~~y~~h~added",2000,3);

                    CoreVehicles[CarData[carid][carVehicle]][vehNeonStatus] = 1;
                    CoreVehicles[CarData[carid][carVehicle]][vehNeonColor] = 6;
                    CarData[carid][carNeonStatus] = 1;
                    CarData[carid][carNeonColor] = 6;
                    Car_Save(carid);
                }
                PlayerInventory_Remove(playerid, "Neon Card", 1);
            }
        }
    }
    return 1;
}

IsPlayerOnBike(carid){
    new vehicleclass = GetVehicleModel(CarData[carid][carVehicle]);
    switch(vehicleclass){
        case 448:return 1;
        case 461:return 1;
        case 462:return 1;
        case 463:return 1;
        case 468:return 1;
        case 521:return 1;
        case 522:return 1;
        case 523:return 1;
        case 581:return 1;
        case 586:return 1;
        case 471:return 1;
    }
	return 0;
}

// IsPlayerMotorcycle(vehicle){
//     new vehicleclass = GetVehicleModel(vehicle);
//     switch(vehicleclass){
//         case 448:return 1;
//         case 461:return 1;
//         case 462:return 1;
//         case 463:return 1;
//         case 468:return 1;
//         case 521:return 1;
//         case 522:return 1;
//         case 523:return 1;
//         case 581:return 1;
//         case 586:return 1;
//         case 471:return 1;
//     }
// 	return 0;
// }