#if defined _inc_impl
	#undef _inc_impl
#endif

ResetGasJob(playerid){
    CarryGas[playerid] = 0;
    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
    RemoveAttachedObject(playerid, 8);
    return 1;
}

forward PickupGas(playerid);
public PickupGas(playerid){
    
    if(CarryGas[playerid] == 1)
        return ErrorMsg(playerid, "คุณกำลังถือ Gas อยู่ไม่สามารถหยิบได้อีก");

    CarryGas[playerid] = 1;
    SendClientMessage(playerid, COLOR_YELLOW, "[แนะนำ]: กด 'N' เพื่อทิ้งถังแก๊สที่ถืออยู่");
    SendClientMessage(playerid, COLOR_YELLOW, "[แนะนำ]: ให้ขึ้นไปบนรถและเปิด Trunk เพื่อเปิดหลังรถ และ กด 'ต่อย' ท้ายรถเพื่อนำแก๊สใส่");
    SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CARRY);
    ApplyAnimation(playerid, "CARRY", "liftup", 4.1, 0, 0, 0, 0, 0, 1);
    SetPlayerAttachedObject(playerid, 8, 1348,1,0.248999,0.503000,0.006000,-93.700035,80.499900,-83.400001,0.474000,0.603999,0.433999);
    return 1;
}

stock IsLoadGasVehicle(vehicleid)
{
	new modelid = GetVehicleModel(vehicleid);

	if (GetVehicleTrailer(vehicleid))
	    modelid = GetVehicleModel(GetVehicleTrailer(vehicleid));

	switch (modelid) {
	    case 478: return 1;
	}
	return 0;
}

forward LoadGasOnVeh(vehicleid);
public LoadGasOnVeh(vehicleid){
    GasOnVeh[vehicleid] = CreateDynamicObject(1348,0,0,-1000,0,0,0,0);
    AttachDynamicObjectToVehicle(GasOnVeh[vehicleid], vehicleid, 0.000000,-1.800000,0.675000,-2.700001,0.000000,-0.000035);
    return 1;
}