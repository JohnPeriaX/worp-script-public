#if defined _inc_header
	#undef _inc_header
#endif

#define MAX_PHONETEXT (32)
new PlayerText:PlayerPhoneTD[MAX_PLAYERS][MAX_PHONETEXT];

new PlayerGetNumberSMS[MAX_PLAYERS];
new PlayerEnterCamera[MAX_PLAYERS];
new PlayerCameraType[MAX_PLAYERS];

#define MAX_CONTACTS (20)

enum contactData {
	contactID,
	contactExists,
	contactName[32],
	contactNumber
};
new ContactData[MAX_PLAYERS][MAX_CONTACTS][contactData];
new ListedContacts[MAX_PLAYERS][MAX_CONTACTS];