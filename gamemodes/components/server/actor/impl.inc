#if defined _inc_impl
	#undef _inc_impl
#endif

LoadActorServer(){
    Marry[0] = CreateActor(240, 1120.1317,-1495.3914,22.7690,358.8514);
    SetPlayerInterior(Marry[0], 0);
    SetActorVirtualWorld(Marry[0], 0);

    Marry[1] = CreateActor(91, 1119.4319,-1495.4098,22.7690,359.2010);
    SetPlayerInterior(Marry[1], 0);
    SetActorVirtualWorld(Marry[1], 0);
    return 1;
}