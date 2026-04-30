#if defined _inc_header
	#undef _inc_header
#endif

//----------------------[ playerinv ]--------------------//

#define MAX_INVENTORYTEXTDRAW       (100)
#define MAX_INVENTORYSLOTTEXTDRAW   (100)
#define MAX_INV_MENU_ROWS           (6)
#define MAX_INV_MENU_COLUMN         (6)
#define MAX_SLOTPAGE                (36)
#define MAX_INVENTORYPLAYERS        (108)
#define MAX_DROPPED_ITEMS           (1000)

#define MAX_VICINITYTEXTDRAW        (50)
#define MAX_VICINITY                (10)
#define MAX_VICINITY_ROWS           (2)
#define MAX_VICINITY_COLUMN         (5)

#define DROP_COLOR                  (0xFFBD00FF)

#define INVENTORY_TYPE              (0)
#define TRADE_TYPE                  (1)
#define HOME_TYPE                   (2)
#define WALLET_TYPE                 (3)
#define SAFE_TYPE                   (4)

#define THREAD_LOAD_INVENTORY       (1)

enum inventoryData{
    itemID,
    itemHave,
    itemKey,
    itemName[64],
    itemOwner,
    itemQuantity,
    itemLevel,
    itemAmmo,
    itemSlot
};
new Inventory_Player[MAX_PLAYERS][MAX_INVENTORYPLAYERS][inventoryData];

enum dropItems{
    droppedID,
    droppedItem[64],
    droppedModel,
    droppedQuantity,
    droppedAmmo,
    droppedWeaponLevel,
    Float:droppedPos[3],
    droppedInt,
    droppedWorld,
    STREAMER_TAG_OBJECT:droppedObject,
    STREAMER_TAG_3D_TEXT_LABEL:droppedText3D
};
new Drop_Data[MAX_DROPPED_ITEMS][dropItems];
new Iterator:Iter_DropItem<MAX_DROPPED_ITEMS>;


new PlayerText:PlayerInventoryTextDraw[MAX_PLAYERS][MAX_INVENTORYTEXTDRAW];
new PlayerText:PlayerSlotInventoryTextDraw[MAX_PLAYERS][MAX_INVENTORYSLOTTEXTDRAW];
new PlayerSlotInventoryCount[MAX_PLAYERS];
new PlayerSlotInventoryModel[MAX_PLAYERS][MAX_INV_MENU_ROWS][MAX_INV_MENU_COLUMN];
new PlayerSlotInventoryAmount[MAX_PLAYERS][MAX_INV_MENU_ROWS][MAX_INV_MENU_COLUMN];
new bool:PlayerInventoryStatus[MAX_PLAYERS];

new PlayerGetIndexSlotItem[MAX_PLAYERS], PlayerGetIndexNextSlotItem[MAX_PLAYERS];
new PlayerInvListItemRowsOld[MAX_PLAYERS], PlayerInvListItemColumnOld[MAX_PLAYERS];
new PlayerInvListItemRows[MAX_PLAYERS], PlayerInvListItemColumn[MAX_PLAYERS];

new PlayerInventoryType[MAX_PLAYERS];
new PlayerInventoryDropInput[MAX_PLAYERS];
new PlayerInventoryPage[MAX_PLAYERS];
new PlayerInventoryLastPage[MAX_PLAYERS];

new PlayerVicinity[MAX_PLAYERS];
new PlayerNearestItems[MAX_PLAYERS][MAX_VICINITY];
new PlayerText:PlayerVicinityTextDraw[MAX_PLAYERS][MAX_VICINITYTEXTDRAW];
new PlayerText:PlayerSlotVicinityTextDraw[MAX_PLAYERS][MAX_VICINITYTEXTDRAW];
new PlayerSlotVicinityCount[MAX_PLAYERS];
new PlayerSlotVicinityModel[MAX_PLAYERS][MAX_VICINITY_ROWS][MAX_VICINITY_COLUMN];
new PlayerSlotVicinityAmount[MAX_PLAYERS][MAX_VICINITY_ROWS][MAX_VICINITY_COLUMN];

new PlayerShowButton[MAX_PLAYERS];
new PlayerText:UseButton[MAX_PLAYERS];
new PlayerText:InfoButton[MAX_PLAYERS];

new Float:PlayerInvWeightTemp[MAX_PLAYERS];
new PlayerCantSelectTextDraw[MAX_PLAYERS];

new PlayerText:ArrowEditInv[MAX_PLAYERS][4];

new Timer:UpdateInventory[MAX_PLAYERS];

//-----------------------[ homeinv ]----------------------//

#define     MAX_HOMETD                   (13)
#define     MAX_HOMETD_SLOT              (100)
#define     MAX_HOME_MENU_ROWS           (6)
#define     MAX_HOME_MENU_COLUMN         (6)
#define     HOMEINV_TYPE                 (1)


new PlayerText:PlayerHomeInvTD[MAX_PLAYERS][MAX_HOMETD];

new PlayerText:PlayerHomeSlotTextDraw[MAX_PLAYERS][MAX_HOMETD_SLOT];
new PlayerHomeSlotCount[MAX_PLAYERS];
new PlayerHomeSlotModel[MAX_PLAYERS][MAX_HOME_MENU_ROWS][MAX_HOME_MENU_COLUMN];
new PlayerHomeSlotAmount[MAX_PLAYERS][MAX_HOME_MENU_ROWS][MAX_HOME_MENU_COLUMN];
new PlayerHomeInvPage[MAX_PLAYERS], PlayerHomeInvLastPage[MAX_PLAYERS];
new PlayerHomeInvType[MAX_PLAYERS];
new PlayerUsing_HomeInv[MAX_PLAYERS];

new PlayerGetIndexHomeSlotItem[MAX_PLAYERS], PlayerGetIndexNextHomeSlotItem[MAX_PLAYERS];
new PlayerHomeInvListItemRowsOld[MAX_PLAYERS], PlayerHomeInvListItemColumnOld[MAX_PLAYERS];
new PlayerHomeInvListItemRows[MAX_PLAYERS], PlayerHomeInvListItemColumn[MAX_PLAYERS];

new PlayerHomeShowButton[MAX_PLAYERS];
new PlayerText:HomeGetButton[MAX_PLAYERS];
new PlayerText:HomeInfoButton[MAX_PLAYERS];

new GetHomeItemIndex[MAX_PLAYERS], GetItemDropIndex[MAX_PLAYERS];

new bool:PlayerEditPositionInventory[MAX_PLAYERS], PlayerEditColorInventory[MAX_PLAYERS];
new PlayerInventoryCodeColor[MAX_PLAYERS], PlayerInventoryHoverCodeColor[MAX_PLAYERS];
new PlayerInventoryColorType[MAX_PLAYERS];
new Float:PlayerPositionInventoryX[MAX_PLAYERS], Float:PlayerPositionInventoryY[MAX_PLAYERS];
new PlayerInventoryColorR[MAX_PLAYERS], PlayerInventoryColorG[MAX_PLAYERS], PlayerInventoryColorB[MAX_PLAYERS];

//------------------------[ charinv ]----------------------//

#define         MAX_CHARTEXT        (32)

new PlayerText:PlayerCharacterTextDraw[MAX_PLAYERS][MAX_CHARTEXT];
new PlayerCharacterShow[MAX_PLAYERS];