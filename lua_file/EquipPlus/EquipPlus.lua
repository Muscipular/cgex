function EquipPlus_Init( _MeIndex )
	Char.SetData(_MeIndex, %對像_形象%, 100003);
	Char.SetData(_MeIndex, %對像_原形%, 100003);
	Char.SetData(_MeIndex, %對像_地圖類型%, 0);
	Char.SetData(_MeIndex, %對像_地圖%, 1000);
	Char.SetData(_MeIndex, %對像_X%, 232);
	Char.SetData(_MeIndex, %對像_Y%, 83);
	Char.SetData(_MeIndex, %對像_方向%, %右下%);
	Char.SetData(_MeIndex, %對像_原名%, "武器裝備晉陞大師");

	if (Char.SetTalkedEvent(nil, "EquipPlus_Talked", _MeIndex) < 0) then
		print("EquipPlus_Talked 註冊事件失敗。");
		return false;
	end
	if (Char.SetWindowTalkedEvent(nil, "EquipPlus_WindowTalked", _MeIndex) < 0) then
		print("pztestnpc_WindowTalked 註冊事件失敗。");
		return false;
	end

	return true;
end

--Talked事件
--目前最高SEQNO=13
function EquipPlus_Talked( _MeIndex, _PlayerIndex)
	--這裡檢查玩家是否站在NPC面前
	if(NLG.CheckInFront(_PlayerIndex, _MeIndex, 1) == false) then
		return ;
	end 
	--面向玩家
	local i;
	i = Char.GetData(_PlayerIndex, %對像_方向%);
	if i >= 4 then 
		i = i - 4;
	else
		i = i + 4;		
	end
	Char.SetData(_MeIndex, %對像_方向%,i);
	NLG.UpChar( _MeIndex);
	NLG.ShowWindowTalked(_PlayerIndex, 2, 0, 1,
		 "2\n　　　　　　  ☆裝備加強☆"..
		 "\n請選擇:" ..
	 	 "\n              《 裝備列表 》" ..
	 	 "\n              《 道具列表 》" ..
	 	 "\n               《 離開 》",
		 _MeIndex);
return ;
end

-- WindowTalked 事件
function EquipPlus_WindowTalked( _MeIndex, _TalkIndex, _Seqno, _Select, _Data)

	--這裡檢查玩家是否站在NPC面前
	if(NLG.CheckInFront(_TalkIndex, _MeIndex, 1) == false) then
		return ;
	end

	if _Seqno == 1 then
		if _Data == "1" then
			local pos = 0;
			--改說明時勿添行
			local TM_Buff = "1\n請選擇:";
			local itemindex;
			local equip = {"頭位","身位","右手","左手","腳位","飾1","飾2","水晶"};

			while(pos <= 8)do
				if (pos == 8) then
					TM_Buff = TM_Buff .. "\n" .. "　　　　　　　   《　離　開　》";
					pos = pos + 1;
				else
					itemindex = Char.GetItemIndex( _TalkIndex, pos);
					if( itemindex > 0)then
						TM_Buff = TM_Buff.."\n".. equip[pos + 1] .. "：" .. Item.GetData( itemindex, %道具_已鑑定名%);
					else
						TM_Buff = TM_Buff .. "\n" .. equip[pos + 1] .. "：無裝備";
					end
					pos = pos + 1;
				end
			end
			NLG.ShowWindowTalked( _TalkIndex, 2, 0, 2, TM_Buff, _MeIndex);
			return;
		end
		
		if _Data == "2" then
			--改說明時勿添行
			local pos = 8;
			local TM_Buff = "1\n請選擇道具：";
			local itemindex;
			local itempos = {"道具欄1","道具欄2","道具欄3","道具欄4","道具欄5","道具欄6","道具欄7","道具欄8"};

			while(pos <= 16)do
				itemindex = Char.GetItemIndex( _TalkIndex, pos);
				if (pos == 16) then
					TM_Buff = TM_Buff .. "\n" .. "　　　　　　　《　下　一　頁　》";
				else
					if( itemindex > 0)then
						TM_Buff = TM_Buff.."\n".. itempos[pos - 7] .. "：" .. Item.GetData( itemindex, %道具_已鑑定名%);
					else
						TM_Buff = TM_Buff .. "\n" .. itempos[pos - 7] .. "：無道具";
					end
				end
				pos = pos + 1;
			end
			NLG.ShowWindowTalked( _TalkIndex, 2, 0, 3, TM_Buff, _MeIndex);
			return;
		end
	end

	if(_Seqno == 3 or _Seqno == 2 or _Seqno == 4 or _Seqno == 5) then
		if (_Seqno == 3 and _Data == "9") then
			--改說明時勿添行
			local pos = 16;
			local TM_Buff = "1\n請選擇道具：";
			local itemindex;
			local itempos = {"道具欄9","道具欄10","道具欄11","道具欄12","道具欄13","道具欄14","道具欄15", "道具欄16"};

			while(pos <= 24)do
				itemindex = Char.GetItemIndex( _TalkIndex, pos);
				if (pos == 24) then
				--TM_Buff = TM_Buff .. "\n" .. "　　　　　　　   《　離　開　》";
				TM_Buff = TM_Buff .. "\n" .. "　　　　　　　《　下　一　頁　》";
				else
					if( itemindex > 0)then
						TM_Buff = TM_Buff.."\n".. itempos[pos - 15] .. "：" .. Item.GetData( itemindex, %道具_已鑑定名%);
					else
						TM_Buff = TM_Buff .. "\n" .. itempos[pos - 15] .. "：無道具";
					end
				end
				pos = pos + 1;
			end
			NLG.ShowWindowTalked( _TalkIndex, 2, 0, 4, TM_Buff, _MeIndex);
			
		elseif(_Seqno == 4 and _Data == "9") then
			local pos = 24;
			local TM_Buff = "1\n請選擇道具：";
			local itemindex;
			local itempos = {"道具欄17","道具欄18","道具欄19","道具欄20"};

			while(pos <= 28)do
				itemindex = Char.GetItemIndex( _TalkIndex, pos);
				if (pos == 28) then
				TM_Buff = TM_Buff .. "\n" .. "　　　　　　　   《　離　開　》";
				else
					if( itemindex > 0)then
						TM_Buff = TM_Buff.."\n".. itempos[pos - 23] .. "：" .. Item.GetData( itemindex, %道具_已鑑定名%);
					else
						TM_Buff = TM_Buff .. "\n" .. itempos[pos - 23] .. "：無道具";
					end
				end
				pos = pos + 1;
			end
			NLG.ShowWindowTalked( _TalkIndex, 2, 0, 5, TM_Buff, _MeIndex);
		else
			local sel = tonumber(_Data);
			EquipPlus_Plus(_TalkIndex,_Seqno-1,sel);
   		end
	end
end

function EquipPlus_Plus( _PlayerIndex,_Page,_Sel)
	local itemtbl = { {0,1,2,3,4,5,6,7,-1} , {8,9,10,11,12,13,14,15,-1} , {16,17,18,19,20,21,22,23,-1} , {24, 25, 26, 27,-1} };
	
	local haveitemindex = itemtbl[_Page][_Sel];

	if haveitemindex >= 0 then
		local itemindex = Char.GetItemIndex(_PlayerIndex,haveitemindex);
		if itemindex >= 0 then
			local itemid = Item.GetData(itemindex,%道具_ID%);
--[[
			if(EquipPlus_Check(itemid) > 0)then
				EquipPlus_PPlus(_PlayerIndex,itemindex,itemid, haveitemindex);
				return;
			else 
				NLG.TalkToCli(_PlayerIndex,"該道具無法被加強");
				return;
			end
]]--
			EquipPlus_PPlus(_PlayerIndex,itemindex,itemid, haveitemindex);
			return;
		end
	end
end

function EquipPlus_Check(_ItemID)
	local MAX = 20; --下面列表的項目數
	local PlusItemIDTbl = {22870,22871,22872,22879,22880,22881,22888,22889,22890,22897,22898,22899,21056,21057,21058,21059,21060,21061,21062,21063}; --可以加強的道具ID

	local i = 1;

	while(i<=MAX)do
		if _ItemID == PlusItemIDTbl[i] then
			return 1;
		end
		i = i + 1;
	end
	
	return 0;
end

function EquipPlus_PPlus(charaindex,itemindex,itemid, itempos)
	--local buf = Item.GetData(itemindex,%道具_原名%);
	local buf2 = Item.GetData(itemindex,%道具_已鑑定名%);
--[[
	--1~9級需要的加強材料,最後一項不要改
	local itemtbl = {23679,23679,23679,23679,23679,23679,23680,23680,23680,-1};
	--1~9級需要的材料數量,最後一項不要改
	local itemnumtbl = {1,1,1,1,1,1,1,1,1,1};
]]--
	local level = 0;
	if( string.find(buf2, "+1") ~= nil)then
		level = 1;
	elseif( string.find(buf2, "+2") ~= nil)then
		level = 2;
	elseif( string.find(buf2, "+3") ~= nil)then
		level = 3;
	elseif( string.find(buf2, "+4") ~= nil)then
		level = 4;
	elseif( string.find(buf2, "+5") ~= nil)then
		level = 5;
	elseif( string.find(buf2, "+6") ~= nil)then
		level = 6;
	elseif( string.find(buf2, "+7") ~= nil)then
		level = 7;
	elseif( string.find(buf2, "+8") ~= nil)then
		level = 8;
	elseif( string.find(buf2, "+9") ~= nil)then
		level = 9;
	end
	if(level == 9)then
		NLG.TalkToCli(charaindex,"無法再加強.");
		return;
	end
--[[
	if (Char.FindItemId(charaindex,itemtbl[level+1]) < itemnumtbl[level+1]) then
		NLG.TalkToCli(charaindex,"缺少加強所需道具.");
		return;
	end
]]--
	if(Item.GetData(itemindex,%道具_鑑定%) == 0)  then
		NLG.TalkToCli(charaindex,"此道具未鑑定.");
		return;
	elseif(string.find(Item.GetData(itemindex,%道具_已鑑定名%), "+") == nil) then
		local itemName = Item.GetData(itemindex,%道具_已鑑定名%);
		Item.SetData(itemindex, %道具_未鑑定名% , itemName);
	end

	--這裡是概率,現在是1/10,改10為2則1/2的概率
	local randnum = math.floor(math.random(1, 1));
	if(randnum == 1)then
		if(level == 8 or level == 7)then
			--這是9級加強
			Item.SetData(itemindex,%道具_精神%, Item.GetData(itemindex,%道具_精神%) + 15);
			Item.SetData(itemindex,%道具_回復%, Item.GetData(itemindex,%道具_回復%) + 15);
			Item.SetData(itemindex,%道具_必殺%, Item.GetData(itemindex,%道具_必殺%) + 15);
			Item.SetData(itemindex,%道具_反擊%, Item.GetData(itemindex,%道具_反擊%) + 15);
			Item.SetData(itemindex,%道具_命中%, Item.GetData(itemindex,%道具_命中%) + 15);
			Item.SetData(itemindex,%道具_閃躲%, Item.GetData(itemindex,%道具_閃躲%) + 15);
		else
			Item.SetData(itemindex,%道具_精神%, Item.GetData(itemindex,%道具_精神%) + 5);
			Item.SetData(itemindex,%道具_回復%, Item.GetData(itemindex,%道具_回復%) + 5);
			Item.SetData(itemindex,%道具_必殺%, Item.GetData(itemindex,%道具_必殺%) + 5);
			Item.SetData(itemindex,%道具_反擊%, Item.GetData(itemindex,%道具_反擊%) + 5);
			Item.SetData(itemindex,%道具_命中%, Item.GetData(itemindex,%道具_命中%) + 5);
			Item.SetData(itemindex,%道具_閃躲%, Item.GetData(itemindex,%道具_閃躲%) + 5);
		end
		local buff = Item.GetData(itemindex,%道具_未鑑定名%).."+"..level+1;
		Item.SetData(itemindex,%道具_已鑑定名%,buff);
--[[
		local buff = Item.GetData(itemindex,%道具_說明%);
		if level == 0 then
			local i,j;
			i,j = string.find(buff,"次加強");
			if(i ~=2 or j ~= 7)then
				buff = "1次加強"..buff;
			else
				buff = string.gsub(buff,level,level+1);
			end
		else
			buff = string.gsub(buff,level,level+1);
		end
		Item.SetData(itemindex,%道具_說明%,buff);
]]--
--[[
		NLG.DelItem(charaindex,itemtbl[level+1],itemnumtbl[level+1]);
]]--
		--NLG.TalkToCli(charaindex,"加強完成, 請重新登陸以更新道具屬性.");
		--NLG.TalkToCli(-1,"恭喜"..Char.GetData(charaindex,%對像_原名%).."完成加強裝備"..Item.GetData(itemindex,%道具_未鑑定名%)..",現在是+"..level+1,%紅色%);
		Item.UpItem(charaindex, itempos);
		NLG.TalkToCli(charaindex, "完成加強裝備"..Item.GetData(itemindex,%道具_未鑑定名%)..",現在是+"..level+1,%紅色%);
		return;
	else
--[[
		NLG.DelItem(charaindex,itemtbl[level+1],itemnumtbl[level+1]);
]]--
		--降級概率,現在是1/2,改2為3則變為1/3
		randnum = math.floor(math.random(1,2));
		if randnum == 1 then
			if(level == 0)then
			NLG.TalkToCli(charaindex,"加強道具失敗");
			return;
			end
			if(level == 8 or level == 7 or level == 6)then
				Item.SetData(itemindex,%道具_精神%, Item.GetData(itemindex,%道具_精神%) - 15*(level-7) - 5 * 7);
				Item.SetData(itemindex,%道具_回復%, Item.GetData(itemindex,%道具_回復%) - 15*(level-7) - 5 * 7);
				Item.SetData(itemindex,%道具_必殺%, Item.GetData(itemindex,%道具_必殺%) - 15*(level-7) - 5 * 7);
				Item.SetData(itemindex,%道具_反擊%, Item.GetData(itemindex,%道具_反擊%) - 15*(level-7) - 5 * 7);
				Item.SetData(itemindex,%道具_命中%, Item.GetData(itemindex,%道具_命中%) - 15*(level-7) - 5 * 7);
				Item.SetData(itemindex,%道具_閃躲%, Item.GetData(itemindex,%道具_閃躲%) - 15*(level-7) - 5 * 7);
				local buff = Item.GetData(itemindex,%道具_未鑑定名%);
				Item.SetData(itemindex,%道具_已鑑定名%,buff);
--[[
				local buff = Item.GetData(itemindex,%道具_說明%);
				buff = string.gsub(buff,level,"0");
				Item.SetData(itemindex,%道具_說明%,buff);
]]--
				Item.UpItem(charaindex, itempos);
				NLG.TalkToCli(charaindex,"加強道具失敗,降至零級");
			else
				Item.SetData(itemindex,%道具_精神%, Item.GetData(itemindex,%道具_精神%) - 5);
				Item.SetData(itemindex,%道具_回復%, Item.GetData(itemindex,%道具_回復%) - 5);
				Item.SetData(itemindex,%道具_必殺%, Item.GetData(itemindex,%道具_必殺%) - 5);
				Item.SetData(itemindex,%道具_反擊%, Item.GetData(itemindex,%道具_反擊%) - 5);
				Item.SetData(itemindex,%道具_命中%, Item.GetData(itemindex,%道具_命中%) - 5);
				Item.SetData(itemindex,%道具_閃躲%, Item.GetData(itemindex,%道具_閃躲%) - 5);
				local buff = Item.GetData(itemindex,%道具_未鑑定名%).."+"..level-1;
				Item.SetData(itemindex,%道具_已鑑定名%,buff);
--[[
				local buff = Item.GetData(itemindex,%道具_說明%);
				buff = string.gsub(buff,level,level-1);
				Item.SetData(itemindex,%道具_說明%,buff);
]]--
				Item.UpItem(charaindex, itempos);
				NLG.TalkToCli(charaindex,"加強道具失敗,降一級");
				end

			return;
		else
			NLG.TalkToCli(charaindex,"加強道具失敗");
		end




	end
end