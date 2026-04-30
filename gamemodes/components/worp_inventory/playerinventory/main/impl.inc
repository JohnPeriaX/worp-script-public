#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

hook Character_Reset(playerid){
	ResetPlayerInventoryData(playerid);
	ResetPlayerInventoryTextDraw(playerid);
	return true;
}

void:ResetPlayerInventoryData(playerid){
	for(new i=0; i<MAX_PLAYER_INVENTORY; i++){
		PlayerInventoryData[playerid][i][itemID] = 0;
		PlayerInventoryData[playerid][i][itemModel] = MODEL_NULL;
		format(PlayerInventoryData[playerid][i][itemName], 64, "NULL");
		PlayerInventoryData[playerid][i][itemOwner] = 0;
		PlayerInventoryData[playerid][i][itemQuantity] = 0;
		PlayerInventoryData[playerid][i][itemLevel] = 0;
		PlayerInventoryData[playerid][i][itemAmmo] = 0;
		PlayerInventoryData[playerid][i][itemWeight] = 0.00;
		PlayerInventoryData[playerid][i][itemSlot] = -1;
	}
	PlayerInventory_Page[playerid] = 1;
	Player_Inventory_Select_Rows[playerid] = -1;
	Player_Inventory_Select_Column[playerid] = -1;
	Player_Inventory_Select_Index[playerid] = -1;
	PlayerBlockSelectInventory[playerid] = false;
	PlayerInventory_MoveItem[playerid] = false;
	PlayerInventory_Type[playerid] = INVENTORY_DEFAULT;
}

hook OP_ClickPlayerTextDraw(playerid, PlayerText:playertextid){
	if(PlayerInventoryTextDrawShow[playerid] && LoggedIn[playerid]){
		if(playertextid == Player_Inventory_TextDraw[playerid][7]){ //  Page 1
			PlayerInventory_Page[playerid] = 1;

			PlayerTextDrawColor(playerid, Player_Inventory_TextDraw[playerid][7], 852308735);
			PlayerTextDrawShow(playerid, Player_Inventory_TextDraw[playerid][7]);

			PlayerTextDrawColor(playerid, Player_Inventory_TextDraw[playerid][8], 1296911871);
			PlayerTextDrawShow(playerid, Player_Inventory_TextDraw[playerid][8]);

			PlayerTextDrawColor(playerid, Player_Inventory_TextDraw[playerid][9], 1296911871);
			PlayerTextDrawShow(playerid, Player_Inventory_TextDraw[playerid][9]);

			if(Player_Inventory_Select_Rows[playerid] != -1 && Player_Inventory_Select_Column[playerid] != -1 && Player_Inventory_Select_Index[playerid] != -1){
				PlayerTextDrawBackgroundColor(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Model[playerid][Player_Inventory_Select_Rows[playerid]][Player_Inventory_Select_Column[playerid]]], 370546371);
				PlayerTextDrawShow(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Model[playerid][Player_Inventory_Select_Rows[playerid]][Player_Inventory_Select_Column[playerid]]]);
			}

			Player_Inventory_Render_Slot(playerid);
		}
		else if(playertextid == Player_Inventory_TextDraw[playerid][8]){ //  Page 2
			PlayerInventory_Page[playerid] = 2;

			PlayerTextDrawColor(playerid, Player_Inventory_TextDraw[playerid][7], 1296911871);
			PlayerTextDrawShow(playerid, Player_Inventory_TextDraw[playerid][7]);

			PlayerTextDrawColor(playerid, Player_Inventory_TextDraw[playerid][8], 852308735);
			PlayerTextDrawShow(playerid, Player_Inventory_TextDraw[playerid][8]);

			PlayerTextDrawColor(playerid, Player_Inventory_TextDraw[playerid][9], 1296911871);
			PlayerTextDrawShow(playerid, Player_Inventory_TextDraw[playerid][9]);

			if(Player_Inventory_Select_Rows[playerid] != -1 && Player_Inventory_Select_Column[playerid] != -1 && Player_Inventory_Select_Index[playerid] != -1){
				PlayerTextDrawBackgroundColor(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Model[playerid][Player_Inventory_Select_Rows[playerid]][Player_Inventory_Select_Column[playerid]]], 370546371);
				PlayerTextDrawShow(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Model[playerid][Player_Inventory_Select_Rows[playerid]][Player_Inventory_Select_Column[playerid]]]);
			}

			Player_Inventory_Render_Slot(playerid);
		}
		else if(playertextid == Player_Inventory_TextDraw[playerid][9]){ //  Page 3
			PlayerInventory_Page[playerid] = 3;

			PlayerTextDrawColor(playerid, Player_Inventory_TextDraw[playerid][7], 1296911871);
			PlayerTextDrawShow(playerid, Player_Inventory_TextDraw[playerid][7]);

			PlayerTextDrawColor(playerid, Player_Inventory_TextDraw[playerid][8], 1296911871);
			PlayerTextDrawShow(playerid, Player_Inventory_TextDraw[playerid][8]);

			PlayerTextDrawColor(playerid, Player_Inventory_TextDraw[playerid][9], 852308735);
			PlayerTextDrawShow(playerid, Player_Inventory_TextDraw[playerid][9]);

			if(Player_Inventory_Select_Rows[playerid] != -1 && Player_Inventory_Select_Column[playerid] != -1 && Player_Inventory_Select_Index[playerid] != -1){
				PlayerTextDrawBackgroundColor(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Model[playerid][Player_Inventory_Select_Rows[playerid]][Player_Inventory_Select_Column[playerid]]], 370546371);
				PlayerTextDrawShow(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Model[playerid][Player_Inventory_Select_Rows[playerid]][Player_Inventory_Select_Column[playerid]]]);
			}

			Player_Inventory_Render_Slot(playerid);
		}

		if(!PlayerBlockSelectInventory[playerid]){
			new index = 0;
			if(PlayerInventory_Page[playerid] == 1) index = 0;
			else if(PlayerInventory_Page[playerid] == 2) index = 36; 
			else if(PlayerInventory_Page[playerid] == 3) index = 72;
			for(new i=0; i<MAX_INV_SLOT_ROWS; i++){
				for(new j=0; j<MAX_INV_SLOT_COLUMN; j++){
					if(playertextid == Player_Inventory_Slot_TD[playerid][Player_Inventory_Model[playerid][i][j]]){
						if(PlayerInventoryData[playerid][index][itemModel] != MODEL_NULL && PlayerInventoryData[playerid][index][itemSlot] != -1){
							if(Player_Inventory_Select_Rows[playerid] != -1 && Player_Inventory_Select_Column[playerid] != -1 && Player_Inventory_Select_Index[playerid] != -1){
								PlayerTextDrawBackgroundColor(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Model[playerid][Player_Inventory_Select_Rows[playerid]][Player_Inventory_Select_Column[playerid]]], 370546371);
								PlayerTextDrawShow(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Model[playerid][Player_Inventory_Select_Rows[playerid]][Player_Inventory_Select_Column[playerid]]]);
							}

							Player_Inventory_Select_Rows[playerid] = i;
							Player_Inventory_Select_Column[playerid] = j;
							Player_Inventory_Select_Index[playerid] = index;
							PlayerTextDrawBackgroundColor(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Model[playerid][i][j]], COLOR_SERVER);
							PlayerTextDrawShow(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Model[playerid][i][j]]);
							PlayerInventoryShowDialog(playerid, index);
							return true;
						} else if(PlayerInventoryData[playerid][index][itemModel] == MODEL_NULL && PlayerInventoryData[playerid][index][itemSlot] == -1 && PlayerInventory_MoveItem[playerid]){
							if(Player_Inventory_Select_Rows[playerid] != -1 && Player_Inventory_Select_Column[playerid] != -1 && Player_Inventory_Select_Index[playerid] != -1){
								PlayerTextDrawBackgroundColor(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Model[playerid][Player_Inventory_Select_Rows[playerid]][Player_Inventory_Select_Column[playerid]]], 370546371);
								PlayerTextDrawShow(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Model[playerid][Player_Inventory_Select_Rows[playerid]][Player_Inventory_Select_Column[playerid]]]);
								Player_Inventory_SwapItem(playerid, Player_Inventory_Select_Index[playerid], index);
								return true;
							}
						}
					}
					index++;
				}
			}
		}
	}
	return true;
}

timer UnlockBlockInventory[500](playerid){
	PlayerBlockSelectInventory[playerid] = false;
}

void:PlayerInventoryShowDialog(playerid, index){
	new title[128], caption[256];

	PlayerBlockSelectInventory[playerid] = true;

	inline const _response(response, listitem, string:inputtext[]){
		#pragma unused inputtext
		if(!response) {
			PlayerTextDrawBackgroundColor(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Model[playerid][Player_Inventory_Select_Rows[playerid]][Player_Inventory_Select_Column[playerid]]], 370546371);
			PlayerTextDrawShow(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Model[playerid][Player_Inventory_Select_Rows[playerid]][Player_Inventory_Select_Column[playerid]]]);
			Player_Inventory_Select_Rows[playerid] = -1;
			Player_Inventory_Select_Column[playerid] = -1;
			Player_Inventory_Select_Index[playerid] = -1;
			@return PlayerBlockSelectInventory[playerid] = false;
		}
		else {
			switch(listitem){
				case 0: {
					CallLocalFunction("PlayerInventoryUseItem", "ii", playerid, index);
				}
				case 1: {
					Player_Inventory_GiveItem(playerid, index);
				}
				case 2: {
					Player_Inventory_DropItem(playerid, index);
				}
				case 3: {
					PlayerInventory_MoveItem[playerid] = true;
					InventoryHint(playerid, "เลือกช่องที่ต้องการจะย้ายไอเท็ม '%s'", PlayerInventoryData[playerid][index][itemName]);
					defer UnlockBlockInventory(playerid);
				}
				case 4: {
					Player_Inventory_InfoItem(playerid, index);
				}
			}
		}
	}

	format(title, sizeof title, "[-] %s (%s)", PlayerInventoryData[playerid][index][itemName], FormatNumberNotMoney(PlayerInventoryData[playerid][index][itemQuantity]));
	format(caption, sizeof caption, "{28DC1C}[-] ใช้งาน (Use)\
	\n{FCB91F}[-] ให้ไอเท็ม (Give)\
	\n{FC1F1F}[-] ทิ้ง (Drop)\
	\n{4BAAFF}[-] เคลื่อนย้าย (Move)\
	\n{B0B0B0}[-] ข้อมูลไอเท็ม (Info)");
	Dialog_ShowCallback(playerid, using inline _response, DIALOG_STYLE_LIST, title, caption, "เลือก", "ปิด");
}

Player_Inventory_GiveItem(playerid, index){
	if(index != -1){
		new title[128], caption[128];

		inline const _response(response, listitem, string:inputtext[]){
			#pragma unused listitem
			if(!response){
				@return PlayerInventoryShowDialog(playerid, index);
			} else {
				new amount = strval(inputtext);
				if(amount <= 0 || amount > PlayerInventoryData[playerid][index][itemQuantity]){
					format(title, sizeof title, "%s (%s)", PlayerInventoryData[playerid][index][itemName], FormatNumberNotMoney(PlayerInventoryData[playerid][index][itemQuantity]));
					format(caption, sizeof caption, "[!] จำนวนไอเท็มผิดพลาด\n[-] ระบุจำนวนที่คุณต้องการจะให้: ");
					@return Dialog_ShowCallback(playerid, using inline _response, DIALOG_STYLE_INPUT, title, caption, "ต่อไป", "ย้อนกลับ");
				}

				inline const _inputPlayer(response2, listitem2, string:inputtext2[]){
					#pragma unused listitem2
					if(!response2){
						Player_Inventory_GiveItem(playerid, index);
						@return true;
					} else {
						new targetid;
						if(sscanf(inputtext2, "u", targetid)) {
							format(title, sizeof title, "%s (ให้ %s | จาก %s)", PlayerInventoryData[playerid][index][itemName], FormatNumberNotMoney(amount), FormatNumberNotMoney(PlayerInventoryData[playerid][index][itemQuantity]));
							format(caption, sizeof caption, "[-] ระบุ 'เลขไอดี/ชื่อ' ของผู้เล่นที่คุณต้องการจะให้: ");
							Dialog_ShowCallback(playerid, using inline _inputPlayer, DIALOG_STYLE_INPUT, title, caption, "ตกลง", "ย้อนกลับ");
							@return true;
						}

						if(targetid == INVALID_PLAYER_ID || !LoggedIn[targetid]){
							format(title, sizeof title, "%s (ให้ %s | จาก %s)", PlayerInventoryData[playerid][index][itemName], FormatNumberNotMoney(amount), FormatNumberNotMoney(PlayerInventoryData[playerid][index][itemQuantity]));
							format(caption, sizeof caption, "[!] ไม่พบผู้เล่นดังกล่าว ผู้เล่นนั้นอาจจะยังไม่ได้เข้าสู่ระบบ\n[-] ระบุ 'เลขไอดี/ชื่อ' ของผู้เล่นที่คุณต้องการจะให้: ");
							Dialog_ShowCallback(playerid, using inline _inputPlayer, DIALOG_STYLE_INPUT, title, caption, "ตกลง", "ย้อนกลับ");
							@return true;
						}

						if(!IsPlayerNearPlayer(playerid, targetid, 5.0)){
							format(title, sizeof title, "%s (ให้ %s | จาก %s)", PlayerInventoryData[playerid][index][itemName], FormatNumberNotMoney(amount), FormatNumberNotMoney(PlayerInventoryData[playerid][index][itemQuantity]));
							format(caption, sizeof caption, "[!] คุณไม่ได้อยู่ใกล้ผู้เล่นไอดี: %d, กรุณาลองใหม่อีกครั้ง\n[-] ระบุ 'เลขไอดี/ชื่อ' ของผู้เล่นที่คุณต้องการจะให้: ", targetid);
							Dialog_ShowCallback(playerid, using inline _inputPlayer, DIALOG_STYLE_INPUT, title, caption, "ตกลง", "ย้อนกลับ");
							@return true;
						}

						new additem = Player_Inventory_AddItem(targetid, PlayerInventoryData[playerid][index][itemName], PlayerInventoryData[playerid][index][itemModel], amount, PlayerInventoryData[playerid][index][itemLevel], PlayerInventoryData[playerid][index][itemAmmo], -1);
						if(additem == -1) return CommandFailInventory(playerid, "ผู้เล่นดังกล่าวไม่สามารถรับไอเท็ม '%s' ได้มากกว่านี้แล้ว!", PlayerInventoryData[playerid][index][itemName]);
						if(PlayerInventoryTextDrawShow[targetid]) Player_Inventory_Render_Slot(targetid, index);
						InventoryHint(targetid, "[+] คุณได้รับ ไอเท็ม '%s' จำนวน '%s' จากผู้เล่น '%s (%d)'", PlayerInventoryData[playerid][index][itemName], FormatNumberNotMoney(amount), ReturnRoleplayName(playerid), playerid);
						InventoryAlert(playerid, "[-] คุณได้เสีย ไอเท็ม '%s' จำนวน '%s (คงเหลือ: %s)' ให้กับผู้เล่น '%s (%d)'", PlayerInventoryData[playerid][index][itemName], FormatNumberNotMoney(amount), FormatNumberNotMoney(PlayerInventoryData[playerid][index][itemQuantity] - amount), ReturnRoleplayName(targetid), targetid);
						Player_Inventory_RemoveByIndex(playerid, index, amount);
					}
				}

				format(title, sizeof title, "%s (ให้ %s | จาก %s)", PlayerInventoryData[playerid][index][itemName], FormatNumberNotMoney(amount), FormatNumberNotMoney(PlayerInventoryData[playerid][index][itemQuantity]));
				format(caption, sizeof caption, "[-] ระบุ 'เลขไอดี/ชื่อ' ของผู้เล่นที่คุณต้องการจะให้: ");
				Dialog_ShowCallback(playerid, using inline _inputPlayer, DIALOG_STYLE_INPUT, title, caption, "ตกลง", "ย้อนกลับ");
			}
		}

		format(title, sizeof title, "%s (%s)", PlayerInventoryData[playerid][index][itemName], FormatNumberNotMoney(PlayerInventoryData[playerid][index][itemQuantity]));
		format(caption, sizeof caption, "[-] ระบุจำนวนที่คุณต้องการจะให้: ");
		Dialog_ShowCallback(playerid, using inline _response, DIALOG_STYLE_INPUT, title, caption, "ต่อไป", "ย้อนกลับ");
	}
	return true;
}

void:Player_Inventory_InfoItem(playerid, index){
	if(index != -1){
		new getitemindex = -1;
		for(new i=0; i<MAX_SERVER_ITEMS; i++){
			if(!strcmp(ServerItems[i][serveritemName], PlayerInventoryData[playerid][index][itemName], true) && ServerItems[i][serveritemModel] == PlayerInventoryData[playerid][index][itemModel]){
				getitemindex = i;
				break;
			}
		}

		new title[128], caption[128];

		inline const _response(response, listitem, string:inputtext[]){
			#pragma unused listitem, inputtext
			if(!response) {
				@return PlayerInventoryShowDialog(playerid, index);
			} else {
				PlayerTextDrawBackgroundColor(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Model[playerid][Player_Inventory_Select_Rows[playerid]][Player_Inventory_Select_Column[playerid]]], 370546371);
				PlayerTextDrawShow(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Model[playerid][Player_Inventory_Select_Rows[playerid]][Player_Inventory_Select_Column[playerid]]]);
				Player_Inventory_Select_Rows[playerid] = -1;
				Player_Inventory_Select_Column[playerid] = -1;
				Player_Inventory_Select_Index[playerid] = -1;
				defer UnlockBlockInventory(playerid);
				@return true;
			}
		}

		format(title, sizeof title, "%s (%s)", PlayerInventoryData[playerid][index][itemName], FormatNumberNotMoney(PlayerInventoryData[playerid][index][itemQuantity]));
		if(getitemindex != -1){
			format(caption, sizeof caption, "[-] %s\
			\n[น้ำหนัก]: %.2f KG\
			\n[น้ำหนักรวม] %s ชิ้น = %.2f KG", ServerItems[getitemindex][serveritemDetail], ServerItems[getitemindex][serveritemWeight], FormatNumberNotMoney(PlayerInventoryData[playerid][index][itemQuantity]), (PlayerInventoryData[playerid][index][itemQuantity] * ServerItems[getitemindex][serveritemWeight]));
		} else {
			format(caption, sizeof caption, "[-] ไม่พบรายละเอียด");
		}
		Dialog_ShowCallback(playerid, using inline _response, DIALOG_STYLE_MSGBOX, title, caption, "ตกลง", "ย้อนกลับ");
	}
}

void:Player_Inventory_DropItem(playerid, index){
	if(index != -1){	
		new title[128], caption[128], query[512];
		if(PlayerInventoryData[playerid][index][itemQuantity] > 1){
			inline const _response(response, listitem, string:inputtext[]){
				#pragma unused listitem
				if(!response) @return PlayerInventoryShowDialog(playerid, index);
				else {
					new amount = strval(inputtext);
					if(amount <= 0 || amount > PlayerInventoryData[playerid][index][itemQuantity]) {
						format(title, sizeof title, "%s (%s)", PlayerInventoryData[playerid][index][itemName], FormatNumberNotMoney(PlayerInventoryData[playerid][index][itemQuantity]));
						format(caption, sizeof caption, "[!] ระบุจำนวนไม่ถูกต้อง\n[-] กรุณากรอกจำนวนที่คุณต้องการจะทิ้ง: ");
						Dialog_ShowCallback(playerid, using inline _response, DIALOG_STYLE_INPUT, title, caption, "ตกลง", "ย้อนกลับ");
						@return true;
					}

					inline const _dropItem(response2, listitem2, string:inputtext2[]){
						#pragma unused listitem2, inputtext2
						if(!response2){
							format(title, sizeof title, "%s (%s)", PlayerInventoryData[playerid][index][itemName], FormatNumberNotMoney(PlayerInventoryData[playerid][index][itemQuantity]));
							format(caption, sizeof caption, "[-] กรุณากรอกจำนวนที่คุณต้องการจะทิ้ง: ");
							Dialog_ShowCallback(playerid, using inline _response, DIALOG_STYLE_INPUT, title, caption, "ตกลง", "ย้อนกลับ");
							@return true;
						} else {
							InventoryAlert(playerid, "คุณได้ทิ้งไอเท็ม '%s' จำนวน '%s' เรียบร้อยแล้ว", PlayerInventoryData[playerid][index][itemName], FormatNumberNotMoney(amount));
							if(PlayerInventoryData[playerid][index][itemQuantity] - amount > 0){
								new Float:findWeight = (PlayerInventoryData[playerid][index][itemWeight] / PlayerInventoryData[playerid][index][itemQuantity]);
								PlayerInventoryData[playerid][index][itemQuantity] -= amount;
								PlayerInventoryData[playerid][index][itemWeight] -= findWeight * amount;
								mysql_format(dbCon, query, sizeof query, "UPDATE `inventory` SET `itemQuantity` = '%d', `itemWeight` = '%f' WHERE `itemID` = '%d' AND `itemOwner` = '%d'", PlayerInventoryData[playerid][index][itemQuantity], PlayerInventoryData[playerid][index][itemWeight], PlayerInventoryData[playerid][index][itemID], PlayerData[playerid][pID]);
								mysql_query(dbCon, query);

								Player_Inventory_Render_Slot(playerid, index);
								PlayerTextDrawBackgroundColor(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Model[playerid][Player_Inventory_Select_Rows[playerid]][Player_Inventory_Select_Column[playerid]]], 370546371);
								PlayerTextDrawShow(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Model[playerid][Player_Inventory_Select_Rows[playerid]][Player_Inventory_Select_Column[playerid]]]);
								Player_Inventory_Select_Rows[playerid] = -1;
								Player_Inventory_Select_Column[playerid] = -1;
								Player_Inventory_Select_Index[playerid] = -1;
								defer UnlockBlockInventory(playerid);
							} else {
								mysql_format(dbCon, query, sizeof query, "DELETE FROM `inventory` WHERE `itemID` = '%d' AND `itemOwner` = '%d' LIMIT 1", PlayerInventoryData[playerid][index][itemID], PlayerData[playerid][pID]);
								mysql_query(dbCon, query);

								PlayerInventoryData[playerid][index][itemID] = 0;
								PlayerInventoryData[playerid][index][itemModel] = MODEL_NULL;
								format(PlayerInventoryData[playerid][index][itemName], 64, "NULL");
								PlayerInventoryData[playerid][index][itemQuantity] = 0;
								PlayerInventoryData[playerid][index][itemLevel] = 0;
								PlayerInventoryData[playerid][index][itemAmmo] = 0;
								PlayerInventoryData[playerid][index][itemWeight] = 0.00;
								PlayerInventoryData[playerid][index][itemSlot] = -1;

								Player_Inventory_Render_Slot(playerid, index);
								PlayerTextDrawBackgroundColor(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Model[playerid][Player_Inventory_Select_Rows[playerid]][Player_Inventory_Select_Column[playerid]]], 370546371);
								PlayerTextDrawShow(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Model[playerid][Player_Inventory_Select_Rows[playerid]][Player_Inventory_Select_Column[playerid]]]);
								Player_Inventory_Select_Rows[playerid] = -1;
								Player_Inventory_Select_Column[playerid] = -1;
								Player_Inventory_Select_Index[playerid] = -1;
								defer UnlockBlockInventory(playerid);
							}
						}
					}

					format(caption, sizeof caption, "[-] คุณแน่ใจหรือไม่ที่ต้องการจะทิ้งไอเท็ม '%s' จำนวน '%s' ชิ้น\
					\n[!] หากกด 'ยืนยัน' แล้วไอเท็มจะถูกลบทันทีจะไม่ทำการ Spawn บนพื้นแต่อย่างใด", PlayerInventoryData[playerid][index][itemName], FormatNumberNotMoney(amount));
					Dialog_ShowCallback(playerid, using inline _dropItem, DIALOG_STYLE_MSGBOX, title, caption, "ยืนยัน", "ย้อนกลับ");
				}
			}

			format(title, sizeof title, "%s (%s)", PlayerInventoryData[playerid][index][itemName], FormatNumberNotMoney(PlayerInventoryData[playerid][index][itemQuantity]));
			format(caption, sizeof caption, "[-] กรุณากรอกจำนวนที่คุณต้องการจะทิ้ง: ");
			Dialog_ShowCallback(playerid, using inline _response, DIALOG_STYLE_INPUT, title, caption, "ตกลง", "ย้อนกลับ");

		} else if(PlayerInventoryData[playerid][index][itemQuantity] == 1){
			inline const _dropItemOne(response3, listitem3, string:inputtext3[]){
				#pragma unused listitem3, inputtext3
				if(!response3) @return PlayerInventoryShowDialog(playerid, index);
				else {
					InventoryAlert(playerid, "คุณได้ทิ้งไอเท็ม '%s' จำนวน '%s' เรียบร้อยแล้ว", PlayerInventoryData[playerid][index][itemName], FormatNumberNotMoney(PlayerInventoryData[playerid][index][itemQuantity]));
					mysql_format(dbCon, query, sizeof query, "DELETE FROM `inventory` WHERE `itemID` = '%d' AND `itemOwner` = '%d' LIMIT 1", PlayerInventoryData[playerid][index][itemID], PlayerData[playerid][pID]);
					mysql_query(dbCon, query);

					PlayerInventoryData[playerid][index][itemID] = 0;
					PlayerInventoryData[playerid][index][itemModel] = MODEL_NULL;
					format(PlayerInventoryData[playerid][index][itemName], 64, "NULL");
					PlayerInventoryData[playerid][index][itemQuantity] = 0;
					PlayerInventoryData[playerid][index][itemLevel] = 0;
					PlayerInventoryData[playerid][index][itemAmmo] = 0;
					PlayerInventoryData[playerid][index][itemWeight] = 0.00;
					PlayerInventoryData[playerid][index][itemSlot] = -1;

					Player_Inventory_Render_Slot(playerid, index);
					PlayerTextDrawBackgroundColor(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Model[playerid][Player_Inventory_Select_Rows[playerid]][Player_Inventory_Select_Column[playerid]]], 370546371);
					PlayerTextDrawShow(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Model[playerid][Player_Inventory_Select_Rows[playerid]][Player_Inventory_Select_Column[playerid]]]);
					Player_Inventory_Select_Rows[playerid] = -1;
					Player_Inventory_Select_Column[playerid] = -1;
					Player_Inventory_Select_Index[playerid] = -1;
					defer UnlockBlockInventory(playerid);
				}
			}

			format(title, sizeof title, "%s (%s)", PlayerInventoryData[playerid][index][itemName], FormatNumberNotMoney(PlayerInventoryData[playerid][index][itemQuantity]));
			format(caption, sizeof caption, "[-] คุณแน่ใจหรือไม่ที่ต้องการจะทิ้งไอเท็ม '%s' จำนวน '%s' ชิ้น\
			\n[!] หากกด 'ยืนยัน' แล้วไอเท็มจะถูกลบทันทีจะไม่ทำการ Spawn บนพื้นแต่อย่างใด", PlayerInventoryData[playerid][index][itemName], FormatNumberNotMoney(PlayerInventoryData[playerid][index][itemQuantity]));
			Dialog_ShowCallback(playerid, using inline _dropItemOne, DIALOG_STYLE_MSGBOX, title, caption, "ยืนยัน", "ย้อนกลับ");
		}
	}
}

void:Player_Inventory_SwapItem(playerid, oldslot, newslot){
	if(oldslot != -1 && newslot != -1){
		PlayerInventoryData[playerid][newslot][itemID] = PlayerInventoryData[playerid][oldslot][itemID];
		PlayerInventoryData[playerid][newslot][itemModel] = PlayerInventoryData[playerid][oldslot][itemModel];
		format(PlayerInventoryData[playerid][newslot][itemName], 64, PlayerInventoryData[playerid][oldslot][itemName]);
		PlayerInventoryData[playerid][newslot][itemQuantity] = PlayerInventoryData[playerid][oldslot][itemQuantity];
		PlayerInventoryData[playerid][newslot][itemLevel] = PlayerInventoryData[playerid][oldslot][itemLevel];
		PlayerInventoryData[playerid][newslot][itemAmmo] = PlayerInventoryData[playerid][oldslot][itemAmmo];
		PlayerInventoryData[playerid][newslot][itemWeight] = PlayerInventoryData[playerid][oldslot][itemWeight];
		PlayerInventoryData[playerid][newslot][itemSlot] = newslot;

		PlayerInventoryData[playerid][oldslot][itemID] = 0;
		PlayerInventoryData[playerid][oldslot][itemModel] = MODEL_NULL;
		format(PlayerInventoryData[playerid][oldslot][itemName], 64, "NULL");
		PlayerInventoryData[playerid][oldslot][itemQuantity] = 0;
		PlayerInventoryData[playerid][oldslot][itemLevel] = 0;
		PlayerInventoryData[playerid][oldslot][itemAmmo] = 0;
		PlayerInventoryData[playerid][oldslot][itemWeight] = 0.00;
		PlayerInventoryData[playerid][oldslot][itemSlot] = -1;

		Player_Inventory_Render_Slot(playerid, oldslot);
		Player_Inventory_Render_Slot(playerid, newslot);

		//Update SQL
		new query[512];
		mysql_format(dbCon, query, sizeof query, "UPDATE `inventory` SET `itemSlot` = '%d' WHERE `itemID` = '%d'",
			PlayerInventoryData[playerid][newslot][itemSlot],
			PlayerInventoryData[playerid][newslot][itemID]
		);
		mysql_query(dbCon, query);

		if(Player_Inventory_Select_Rows[playerid] != -1 && Player_Inventory_Select_Column[playerid] != -1 && Player_Inventory_Select_Index[playerid] != -1){
			PlayerTextDrawBackgroundColor(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Model[playerid][Player_Inventory_Select_Rows[playerid]][Player_Inventory_Select_Column[playerid]]], 370546371);
			PlayerTextDrawShow(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Model[playerid][Player_Inventory_Select_Rows[playerid]][Player_Inventory_Select_Column[playerid]]]);
			Player_Inventory_Select_Rows[playerid] = -1;
			Player_Inventory_Select_Column[playerid] = -1;
			Player_Inventory_Select_Index[playerid] = -1;
		}

		PlayerInventory_MoveItem[playerid] = false;
	}
}

forward PlayerLoadInventory(playerid);
public PlayerLoadInventory(playerid){
	if(!LoggedIn[playerid]) return 0;
	new rows;
	cache_get_row_count(rows);
	for (new i = 0; i < rows && i < MAX_PLAYER_INVENTORY; i++) {
		new getitemslot = -1;
		cache_get_value_name_int(i, "itemSlot", getitemslot);
		if(getitemslot > -1){
			for(new j=0; j<MAX_PLAYER_INVENTORY; j++){
				if(j == getitemslot){
					cache_get_value_name_int(i, "itemID", PlayerInventoryData[playerid][j][itemID]);
					cache_get_value_name(i, "itemName", PlayerInventoryData[playerid][j][itemName], 64);
					cache_get_value_name(i, "itemOwner", PlayerInventoryData[playerid][j][itemOwner]);
					cache_get_value_name_int(i, "itemKey", PlayerInventoryData[playerid][j][itemModel]);
					cache_get_value_name_int(i, "itemQuantity", PlayerInventoryData[playerid][j][itemQuantity]);
					cache_get_value_name_int(i, "itemLevel", PlayerInventoryData[playerid][j][itemLevel]);
					cache_get_value_name_int(i, "itemAmmo", PlayerInventoryData[playerid][j][itemAmmo]);
					cache_get_value_name_float(i, "itemWeight", PlayerInventoryData[playerid][j][itemWeight]);
					cache_get_value_name_int(i, "itemSlot", PlayerInventoryData[playerid][j][itemSlot]);
					break;
				}
			}
		}

		if(i >= 108) break;
	}
	return true;
}

Float:Player_Inventory_FindWeight(playerid){
	new Float:totalWeight;
	for(new i=0; i<MAX_PLAYER_INVENTORY; i++){
		if(PlayerInventoryData[playerid][i][itemModel] == MODEL_NULL) continue;
		totalWeight += PlayerInventoryData[playerid][i][itemWeight];
	}
	return totalWeight;
}

Player_Inventory_Empty(playerid){
	for(new i=0; i<MAX_PLAYER_INVENTORY; i++){
		if(PlayerInventoryData[playerid][i][itemModel] != MODEL_NULL) continue;
		if(PlayerInventoryData[playerid][i][itemSlot] != -1) continue;
		return i;
	}
	return -1;
}

Player_Inventory_ItemHas(playerid, const checkitemName[], checkitemModel){
	for(new i=0; i<MAX_PLAYER_INVENTORY; i++){
		if(PlayerInventoryData[playerid][i][itemSlot] == -1) continue;
		if(!strcmp(PlayerInventoryData[playerid][i][itemName], checkitemName, true) && PlayerInventoryData[playerid][i][itemModel] == checkitemModel){
			return i;
		}
	}
	return -1;
}

Player_Inventory_RemoveByIndex(playerid, itemid, amount = 1){
	if(itemid != -1){
		new query[512];
		if(PlayerInventoryData[playerid][itemid][itemQuantity] - amount > 0){
			new Float:findWeight = (PlayerInventoryData[playerid][itemid][itemWeight] / PlayerInventoryData[playerid][itemid][itemQuantity]);
			PlayerInventoryData[playerid][itemid][itemQuantity] -= amount;
			PlayerInventoryData[playerid][itemid][itemWeight] -= findWeight * amount;
			mysql_format(dbCon, query, sizeof query, "UPDATE `inventory` SET `itemQuantity` = '%d', `itemWeight` = '%f' WHERE `itemID` = '%d' AND `itemOwner` = '%d'", PlayerInventoryData[playerid][itemid][itemQuantity], PlayerInventoryData[playerid][itemid][itemWeight], PlayerInventoryData[playerid][itemid][itemID], PlayerData[playerid][pID]);
			mysql_query(dbCon, query);

			Player_Inventory_Render_Slot(playerid, itemid);
			PlayerTextDrawBackgroundColor(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Model[playerid][Player_Inventory_Select_Rows[playerid]][Player_Inventory_Select_Column[playerid]]], 370546371);
			PlayerTextDrawShow(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Model[playerid][Player_Inventory_Select_Rows[playerid]][Player_Inventory_Select_Column[playerid]]]);
			Player_Inventory_Select_Rows[playerid] = -1;
			Player_Inventory_Select_Column[playerid] = -1;
			Player_Inventory_Select_Index[playerid] = -1;
			defer UnlockBlockInventory(playerid);
			return itemid;
		} else {
			mysql_format(dbCon, query, sizeof query, "DELETE FROM `inventory` WHERE `itemID` = '%d' AND `itemOwner` = '%d' LIMIT 1", PlayerInventoryData[playerid][itemid][itemID], PlayerData[playerid][pID]);
			mysql_query(dbCon, query);

			PlayerInventoryData[playerid][itemid][itemID] = 0;
			PlayerInventoryData[playerid][itemid][itemModel] = MODEL_NULL;
			format(PlayerInventoryData[playerid][itemid][itemName], 64, "NULL");
			PlayerInventoryData[playerid][itemid][itemQuantity] = 0;
			PlayerInventoryData[playerid][itemid][itemLevel] = 0;
			PlayerInventoryData[playerid][itemid][itemAmmo] = 0;
			PlayerInventoryData[playerid][itemid][itemWeight] = 0.00;
			PlayerInventoryData[playerid][itemid][itemSlot] = -1;
			Player_Inventory_Render_Slot(playerid, itemid);
			PlayerTextDrawBackgroundColor(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Model[playerid][Player_Inventory_Select_Rows[playerid]][Player_Inventory_Select_Column[playerid]]], 370546371);
			PlayerTextDrawShow(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Model[playerid][Player_Inventory_Select_Rows[playerid]][Player_Inventory_Select_Column[playerid]]]);
			Player_Inventory_Select_Rows[playerid] = -1;
			Player_Inventory_Select_Column[playerid] = -1;
			Player_Inventory_Select_Index[playerid] = -1;
			defer UnlockBlockInventory(playerid);
			return itemid;
		}
	}
	return -1;
}

Player_Inventory_RemoveByName(playerid, const removeItemName[], amount = 1){
	new getitemindex = -1;
	for(new i=0; i<MAX_PLAYER_INVENTORY; i++){
		if(!strcmp(PlayerInventoryData[playerid][i][itemName], removeItemName, true)){
			getitemindex = i;
			break;
		}
	}

	if(getitemindex != -1){
		new query[512];
		if(PlayerInventoryData[playerid][getitemindex][itemQuantity] - amount > 0){
			new Float:findWeight = (PlayerInventoryData[playerid][getitemindex][itemWeight] / PlayerInventoryData[playerid][getitemindex][itemQuantity]);
			PlayerInventoryData[playerid][getitemindex][itemQuantity] -= amount;
			PlayerInventoryData[playerid][getitemindex][itemWeight] -= findWeight * amount;
			mysql_format(dbCon, query, sizeof query, "UPDATE `inventory` SET `itemQuantity` = '%d', `itemWeight` = '%f' WHERE `itemID` = '%d' AND `itemOwner` = '%d'", PlayerInventoryData[playerid][getitemindex][itemQuantity], PlayerInventoryData[playerid][getitemindex][itemWeight], PlayerInventoryData[playerid][getitemindex][itemID], PlayerData[playerid][pID]);
			mysql_query(dbCon, query);

			Player_Inventory_Render_Slot(playerid, getitemindex);
			PlayerTextDrawBackgroundColor(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Model[playerid][Player_Inventory_Select_Rows[playerid]][Player_Inventory_Select_Column[playerid]]], 370546371);
			PlayerTextDrawShow(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Model[playerid][Player_Inventory_Select_Rows[playerid]][Player_Inventory_Select_Column[playerid]]]);
			Player_Inventory_Select_Rows[playerid] = -1;
			Player_Inventory_Select_Column[playerid] = -1;
			Player_Inventory_Select_Index[playerid] = -1;
			defer UnlockBlockInventory(playerid);
			return getitemindex;
		} else {
			mysql_format(dbCon, query, sizeof query, "DELETE FROM `inventory` WHERE `itemID` = '%d' AND `itemOwner` = '%d' LIMIT 1", PlayerInventoryData[playerid][getitemindex][itemID], PlayerData[playerid][pID]);
			mysql_query(dbCon, query);

			PlayerInventoryData[playerid][getitemindex][itemID] = 0;
			PlayerInventoryData[playerid][getitemindex][itemModel] = MODEL_NULL;
			format(PlayerInventoryData[playerid][getitemindex][itemName], 64, "NULL");
			PlayerInventoryData[playerid][getitemindex][itemQuantity] = 0;
			PlayerInventoryData[playerid][getitemindex][itemLevel] = 0;
			PlayerInventoryData[playerid][getitemindex][itemAmmo] = 0;
			PlayerInventoryData[playerid][getitemindex][itemWeight] = 0.00;
			PlayerInventoryData[playerid][getitemindex][itemSlot] = -1;
			Player_Inventory_Render_Slot(playerid, getitemindex);
			PlayerTextDrawBackgroundColor(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Model[playerid][Player_Inventory_Select_Rows[playerid]][Player_Inventory_Select_Column[playerid]]], 370546371);
			PlayerTextDrawShow(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Model[playerid][Player_Inventory_Select_Rows[playerid]][Player_Inventory_Select_Column[playerid]]]);
			Player_Inventory_Select_Rows[playerid] = -1;
			Player_Inventory_Select_Column[playerid] = -1;
			Player_Inventory_Select_Index[playerid] = -1;
			defer UnlockBlockInventory(playerid);
			return getitemindex;
		}
	}
	return -1;
}

Player_Inventory_AddItem(playerid, const additemName[], additemModel, additemAmount = 1, additemLevel = 0, additemAmmo = 0, additemSlot = -1){
	if(additemModel == MODEL_NULL) return -1;

	new Float:totalWeight = Player_Inventory_FindWeight(playerid);
	if(totalWeight > PlayerData[playerid][pInvMaxWeight]) {
		InventoryAlert(playerid, "กระเป๋าของคุณน้ำหนักเต็มไม่สามารถรับไอเท็มได้มากกว่านี้แล้ว");
		return -1;
	}
	
	new getItemServer = -1, query[512];
	for(new i=0; i<MAX_SERVER_ITEMS; i++){
		if(ServerItems[i][serveritemModel] == MODEL_NULL) continue;
		if(!strcmp(ServerItems[i][serveritemName], additemName, true)){
			getItemServer = i;
			break;
		}
	}

	if(getItemServer != -1){
		new itemid = -1;
		if(additemSlot == -1){
			if((itemid = Player_Inventory_ItemHas(playerid, additemName, additemModel)) != -1){
				if(totalWeight + (additemAmount * ServerItems[getItemServer][serveritemWeight]) > PlayerData[playerid][pInvMaxWeight]){
					InventoryAlert(playerid, "กระเป๋าของคุณน้ำหนักเต็มไม่สามารถรับไอเท็มได้มากกว่านี้แล้ว");
					return -1;
				}

				PlayerInventoryData[playerid][itemid][itemQuantity] += additemAmount;
				PlayerInventoryData[playerid][itemid][itemWeight] += (additemAmount * ServerItems[getItemServer][serveritemWeight]);

				//Update SQL
				mysql_format(dbCon, query, sizeof query, "UPDATE `inventory` SET `itemQuantity` = '%d', `itemWeight` = '%.2f' WHERE `itemID` = '%d'",
					PlayerInventoryData[playerid][itemid][itemQuantity],
					PlayerInventoryData[playerid][itemid][itemWeight],
					PlayerInventoryData[playerid][itemid][itemID]
				);
				mysql_query(dbCon, query);
				Player_Inventory_Render_Slot(playerid, itemid);
				return itemid;
			} else {
				if((itemid = Player_Inventory_Empty(playerid)) != -1){
					if(totalWeight + (additemAmount * ServerItems[getItemServer][serveritemWeight]) > PlayerData[playerid][pInvMaxWeight]){
						InventoryAlert(playerid, "กระเป๋าของคุณน้ำหนักเต็มไม่สามารถรับไอเท็มได้มากกว่านี้แล้ว");
						return -1;
					}

					PlayerInventoryData[playerid][itemid][itemModel] = additemModel;
					format(PlayerInventoryData[playerid][itemid][itemName], 64, additemName);
					PlayerInventoryData[playerid][itemid][itemOwner] = PlayerData[playerid][pID];
					PlayerInventoryData[playerid][itemid][itemQuantity] = additemAmount;
					PlayerInventoryData[playerid][itemid][itemLevel] = additemLevel;
					PlayerInventoryData[playerid][itemid][itemAmmo] = additemAmmo;
					PlayerInventoryData[playerid][itemid][itemWeight] = (additemAmount * ServerItems[getItemServer][serveritemWeight]);
					PlayerInventoryData[playerid][itemid][itemSlot] = itemid;

					//Insert SQL
					mysql_format(dbCon, query, sizeof query, "INSERT INTO `inventory` (`itemOwner`, `itemName`, `itemKey`, `itemQuantity`, `itemAmmo`, `itemDate`, `itemLevel`, `itemWeight`, `itemSlot`) \
					VALUES ('%d', '%e', '%d', '%d', '%d', '%e', '%d', '%f', '%d')",
						PlayerInventoryData[playerid][itemid][itemOwner],
						PlayerInventoryData[playerid][itemid][itemName],
						PlayerInventoryData[playerid][itemid][itemModel],
						PlayerInventoryData[playerid][itemid][itemQuantity],
						PlayerInventoryData[playerid][itemid][itemAmmo],
						ReturnDate(),
						PlayerInventoryData[playerid][itemid][itemLevel],
						PlayerInventoryData[playerid][itemid][itemWeight],
						PlayerInventoryData[playerid][itemid][itemSlot]
					);
					mysql_tquery(dbCon, query, "OnPlayerInventory_Add", "ii", playerid, itemid);
					Player_Inventory_Render_Slot(playerid, itemid);
					return itemid;
				}
			}
		} else if(additemSlot > -1) {
			if(PlayerInventoryData[playerid][additemSlot][itemModel] == MODEL_NULL && PlayerInventoryData[playerid][additemSlot][itemSlot] == -1){
				if(totalWeight + (additemAmount * ServerItems[getItemServer][serveritemWeight]) > PlayerData[playerid][pInvMaxWeight]){
					InventoryAlert(playerid, "กระเป๋าของคุณน้ำหนักเต็มไม่สามารถรับไอเท็มได้มากกว่านี้แล้ว");
					return -1;
				}

				PlayerInventoryData[playerid][additemSlot][itemModel] = additemModel;
				format(PlayerInventoryData[playerid][additemSlot][itemName], 64, additemName);
				PlayerInventoryData[playerid][additemSlot][itemOwner] = PlayerData[playerid][pID];
				PlayerInventoryData[playerid][additemSlot][itemQuantity] = additemAmount;
				PlayerInventoryData[playerid][additemSlot][itemLevel] = additemLevel;
				PlayerInventoryData[playerid][additemSlot][itemAmmo] = additemAmmo;
				PlayerInventoryData[playerid][additemSlot][itemWeight] = (additemAmount * ServerItems[getItemServer][serveritemWeight]);
				PlayerInventoryData[playerid][additemSlot][itemSlot] = additemSlot;

				//Insert SQL
				mysql_format(dbCon, query, sizeof query, "INSERT INTO `inventory` (`itemOwner`, `itemName`, `itemKey`, `itemQuantity`, `itemAmmo`, `itemDate`, `itemLevel`, `itemWeight`, `itemSlot`) \
				VALUES ('%d', '%e', '%d', '%d', '%d', '%e', '%d', '%f', '%d')",
					PlayerInventoryData[playerid][additemSlot][itemOwner],
					PlayerInventoryData[playerid][additemSlot][itemName],
					PlayerInventoryData[playerid][additemSlot][itemModel],
					PlayerInventoryData[playerid][additemSlot][itemQuantity],
					PlayerInventoryData[playerid][additemSlot][itemAmmo],
					ReturnDate(),
					PlayerInventoryData[playerid][additemSlot][itemLevel],
					PlayerInventoryData[playerid][additemSlot][itemWeight],
					PlayerInventoryData[playerid][additemSlot][itemSlot]
				);
				mysql_tquery(dbCon, query, "OnPlayerInventory_Add", "ii", playerid, additemSlot);
				Player_Inventory_Render_Slot(playerid, additemSlot);
				return additemSlot;
			} else if(PlayerInventoryData[playerid][additemSlot][itemModel] == additemModel &&
				!strcmp(PlayerInventoryData[playerid][additemSlot][itemName], additemName, true) &&
				PlayerInventoryData[playerid][additemSlot][itemLevel] == additemLevel &&
				PlayerInventoryData[playerid][additemSlot][itemAmmo] == additemAmmo
 			) {
				if(totalWeight + (additemAmount * ServerItems[getItemServer][serveritemWeight]) > PlayerData[playerid][pInvMaxWeight]){
					InventoryAlert(playerid, "กระเป๋าของคุณน้ำหนักเต็มไม่สามารถรับไอเท็มได้มากกว่านี้แล้ว");
					return -1;
				}

				PlayerInventoryData[playerid][additemSlot][itemQuantity] += additemAmount;
				PlayerInventoryData[playerid][additemSlot][itemWeight] += (additemAmount * ServerItems[getItemServer][serveritemWeight]);

				//Update SQL
				mysql_format(dbCon, query, sizeof query, "UPDATE `inventory` SET `itemQuantity` = '%d', `itemWeight` = '%.2f' WHERE `itemID` = '%d'",
					PlayerInventoryData[playerid][additemSlot][itemQuantity],
					PlayerInventoryData[playerid][additemSlot][itemWeight],
					PlayerInventoryData[playerid][additemSlot][itemID]
				);
				mysql_query(dbCon, query);
				Player_Inventory_Render_Slot(playerid, additemSlot);
				return additemSlot;
			}
		}
	}
	return -1;
}

forward OnPlayerInventory_Add(playerid, itemid);
public OnPlayerInventory_Add(playerid, itemid){
	PlayerInventoryData[playerid][itemid][itemID] = cache_insert_id();
	return true;
}

CMD:giveitem(playerid, params[]){
	if(LoggedIn[playerid]){
		if(PlayerData[playerid][pAdmin] >= 1337){
			new userid, itemname[64], amount, level;
			new string[128];
			if(sscanf(params, "us[64]I(1)I(0)", userid, itemname, amount, level)) return CommandHintInventory(playerid, "/giveitem [ไอดี/ชื่อผู้เล่น] [ชื่อไอเท็ม] [จำนวน (1)] [ระดับ (0)]");
			if(!LoggedIn[userid] && userid == INVALID_PLAYER_ID) return CommandFailInventory(playerid, "ไม่พบผู้เล่นดังกล่าวหรือผู้เล่นนั้นยังไม่ได้เข้าสู่ระบบ!");
			if(isnull(itemname)) return CommandFailInventory(playerid, "กรุณระบุชื่อไอเท็มที่ต้องการจะให้ด้วย!");
			if(amount > 0){
				for(new i=0; i<MAX_SERVER_ITEMS; i++){
					if(ServerItems[i][serveritemModel] == MODEL_NULL) continue;
					if(!strcmp(ServerItems[i][serveritemName], itemname, true)){
						new additem = Player_Inventory_AddItem(playerid, ServerItems[i][serveritemName], ServerItems[i][serveritemModel], amount, level, 0, -1);
						if(additem == -1) return CommandFailInventory(playerid, "ผู้เล่นดังกล่าวไม่สามารถรับไอเท็มได้มากกว่านี้แล้ว หรือ อาจจะเกิดข้อผิดพลาดบางอย่าง!");
						SendClientMessageEx(userid, COLOR_YELLOW, "[-] คุณได้รับไอเท็ม '%s' จำนวน '%s' จากผู้ดูแลระบบ", ServerItems[i][serveritemName], FormatNumberNotMoney(amount));
						format(string, sizeof(string), "ผู้ดูแล %s ได้ให้ไอเท็ม '%s' จำนวน '%s' กับผู้เล่น '%s(%d)'", ReturnRoleplayName(playerid), ServerItems[i][serveritemName], FormatNumberNotMoney(amount), ReturnRoleplayName(userid), userid);
						SendAdminsMessage(1, COLOR_GRAY, string);
						break;
					}
				}
			} 
		}
	}
	return true;
}

CMD:playerinv(playerid, params[]){
	PlayerInventory_Type[playerid] = INVENTORY_DEFAULT;
	OP_InventoryOpen(playerid);
	return true;
}

CMD:safeinv(playerid, params[]){
	PlayerInventory_Type[playerid] = INVENTORY_SAFE;
	Jdz_Hunger_Hide(playerid);
	Jdz_Water_Hide(playerid);
	Jdz_Stamina_Hide(playerid);
	Jdz_Shower_Hide(playerid);
	Jdz_Stress_Hide(playerid);
	OP_InventoryOpen(playerid);
	return true;
}

void:OP_InventoryOpen(playerid){
	CreatePlayerInventoryTextDraw(playerid);
	CreatePlayerInventorySlotTD(playerid);

	if(PlayerInventory_Page[playerid] == 1){
		PlayerTextDrawColor(playerid, Player_Inventory_TextDraw[playerid][7], 852308735);
		PlayerTextDrawShow(playerid, Player_Inventory_TextDraw[playerid][7]);

		PlayerTextDrawColor(playerid, Player_Inventory_TextDraw[playerid][8], 1296911871);
		PlayerTextDrawShow(playerid, Player_Inventory_TextDraw[playerid][8]);

		PlayerTextDrawColor(playerid, Player_Inventory_TextDraw[playerid][9], 1296911871);
		PlayerTextDrawShow(playerid, Player_Inventory_TextDraw[playerid][9]);
	} else if(PlayerInventory_Page[playerid] == 2){
		PlayerTextDrawColor(playerid, Player_Inventory_TextDraw[playerid][7], 1296911871);
		PlayerTextDrawShow(playerid, Player_Inventory_TextDraw[playerid][7]);

		PlayerTextDrawColor(playerid, Player_Inventory_TextDraw[playerid][8], 852308735);
		PlayerTextDrawShow(playerid, Player_Inventory_TextDraw[playerid][8]);

		PlayerTextDrawColor(playerid, Player_Inventory_TextDraw[playerid][9], 1296911871);
		PlayerTextDrawShow(playerid, Player_Inventory_TextDraw[playerid][9]);
	} else if(PlayerInventory_Page[playerid] == 3){
		PlayerTextDrawColor(playerid, Player_Inventory_TextDraw[playerid][7], 1296911871);
		PlayerTextDrawShow(playerid, Player_Inventory_TextDraw[playerid][7]);

		PlayerTextDrawColor(playerid, Player_Inventory_TextDraw[playerid][8], 1296911871);
		PlayerTextDrawShow(playerid, Player_Inventory_TextDraw[playerid][8]);

		PlayerTextDrawColor(playerid, Player_Inventory_TextDraw[playerid][9], 852308735);
		PlayerTextDrawShow(playerid, Player_Inventory_TextDraw[playerid][9]);
	}

	InventoryHint(playerid, "Inventory 5.0");
	TogglePlayerControllable(playerid, 0);
}

void:Player_Inventory_Render_Slot(playerid, slot = -1){
	if(PlayerInventoryTextDrawShow[playerid]){
		new index = 0, string[128];
		if(PlayerInventory_Page[playerid] == 1) index = 0;
		else if(PlayerInventory_Page[playerid] == 2) index = 36; 
		else if(PlayerInventory_Page[playerid] == 3) index = 72;
		if(slot == -1){
			for(new i=0; i<MAX_INV_SLOT_ROWS; i++){
				for(new j=0; j<MAX_INV_SLOT_COLUMN; j++){
					if(PlayerInventoryData[playerid][index][itemModel] == MODEL_NULL){
						PlayerTextDrawSetPreviewModel(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Model[playerid][i][j]], MODEL_NULL);
						PlayerTextDrawSetPreviewRot(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Model[playerid][i][j]], 0.000000, 0.000000, 0.000000, 0.000000);
						PlayerTextDrawShow(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Model[playerid][i][j]]);
						PlayerTextDrawHide(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Name[playerid][i][j]]);
						PlayerTextDrawHide(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Amount[playerid][i][j]]);
					} else if(PlayerInventoryData[playerid][index][itemModel] != MODEL_NULL) {
						PlayerTextDrawSetPreviewModel(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Model[playerid][i][j]], PlayerInventoryData[playerid][index][itemModel]);
						PlayerTextDrawSetPreviewRot(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Model[playerid][i][j]], -28.000000, 0.000000, -20.000000, 1.000000);
						
						format(string, sizeof string, "%s", PlayerInventoryData[playerid][index][itemName]);
						PlayerTextDrawSetString(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Name[playerid][i][j]], string);

						format(string, sizeof string, "%s", FormatNumberNotMoney(PlayerInventoryData[playerid][index][itemQuantity]));
						PlayerTextDrawSetString(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Amount[playerid][i][j]], string);
						
						PlayerTextDrawShow(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Model[playerid][i][j]]);
						PlayerTextDrawShow(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Name[playerid][i][j]]);
						PlayerTextDrawShow(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Amount[playerid][i][j]]);
					}
					index++;
				}
			}
		} else if(slot != -1){
			for(new i=0; i<MAX_INV_SLOT_ROWS; i++){
				for(new j=0; j<MAX_INV_SLOT_COLUMN; j++){
					if(slot == index){
						if(PlayerInventoryData[playerid][index][itemModel] != MODEL_NULL && PlayerInventoryData[playerid][index][itemSlot] != -1){
							PlayerTextDrawSetPreviewModel(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Model[playerid][i][j]], PlayerInventoryData[playerid][index][itemModel]);
							PlayerTextDrawSetPreviewRot(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Model[playerid][i][j]], -28.000000, 0.000000, -20.000000, 1.000000);
							
							format(string, sizeof string, "%s", PlayerInventoryData[playerid][index][itemName]);
							PlayerTextDrawSetString(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Name[playerid][i][j]], string);

							format(string, sizeof string, "%s", FormatNumberNotMoney(PlayerInventoryData[playerid][index][itemQuantity]));
							PlayerTextDrawSetString(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Amount[playerid][i][j]], string);
							
							PlayerTextDrawShow(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Model[playerid][i][j]]);
							PlayerTextDrawShow(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Name[playerid][i][j]]);
							PlayerTextDrawShow(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Amount[playerid][i][j]]);

						} else if(PlayerInventoryData[playerid][index][itemModel] == MODEL_NULL && PlayerInventoryData[playerid][index][itemSlot] == -1){

							PlayerTextDrawSetPreviewModel(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Model[playerid][i][j]], MODEL_NULL);
							PlayerTextDrawSetPreviewRot(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Model[playerid][i][j]], 0.000000, 0.000000, 0.000000, 0.000000);
							PlayerTextDrawShow(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Model[playerid][i][j]]);
							PlayerTextDrawHide(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Name[playerid][i][j]]);
							PlayerTextDrawHide(playerid, Player_Inventory_Slot_TD[playerid][Player_Inventory_Amount[playerid][i][j]]);
						}
					}	
					index++;
				}
			}
		}

		new Float:totalWeight = Player_Inventory_FindWeight(playerid);
		SetPlayerProgressBarValue(playerid, PlayerInventoryWeightBar[playerid], totalWeight);
		format(string, sizeof string, "%.2f/%.2f", totalWeight, PlayerData[playerid][pInvMaxWeight]);
		PlayerTextDrawSetString(playerid, Player_Inventory_TextDraw[playerid][6], string);
	}
}