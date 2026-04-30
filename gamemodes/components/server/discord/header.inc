#if defined _inc_header
	#undef _inc_header
#endif

new DCC_Channel:g_ReplyChannel;
new DCC_Channel:UseWeaponChannel;
new DCC_Channel:MoneyLogChannel;
new DCC_Channel:WithdrawPolice;
new DCC_Channel:WithdrawMedic;
new DCC_Channel:CraftWeapon;
new DCC_Channel:StoryGangChannel;
new DCC_Guild:guildName;
new DCC_Role:adminRole;

new TogAlertLog = true;