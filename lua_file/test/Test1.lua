function Test1Npc_Init( Test1Npc_index )
	Char.SetData(Test1Npc_index, %對像_形象%, 100002);
	Char.SetData(Test1Npc_index, %對像_原形%, 100002);
	Char.SetData(Test1Npc_index, %對像_地圖類型%, 0);
	Char.SetData(Test1Npc_index, %對像_地圖%, 1000);
	Char.SetData(Test1Npc_index, %對像_X%, 234);
	Char.SetData(Test1Npc_index, %對像_Y% ,83);
	Char.SetData(Test1Npc_index, %對像_方向%, %右下%);
	Char.SetData(Test1Npc_index, %對像_原名%, "測試員1號");


	--響應說話事件，此事件如果有玩家對此NPC說話就會觸發
	if (Char.SetTalkedEvent(nil, "Test1Npc_Talked", Test1Npc_index) < 0) then
		print("Test1Npc_Talked 註冊事件失敗。");
		return false;
	end
	
	--響應視窗事件
	if (Char.SetWindowTalkedEvent(nil, "Test1Npc_WindowTalked", Test1Npc_index) < 0) then
		print("Test1Npc_WindowTalked 註冊事件失敗。");
		return false;
	end
	
	--響應踐踏事件
	--if (Char.SetPostOverEvent(nil, "Test1Npc_PostOver", Test1Npc_index) < 0) then
	--	print("Test1Npc_PostOver 註冊事件失敗。");
	--	return false;
	--end
	
	--PVP 變數
	Test1Npc_count = 0;
	Test1Npc_index1 = 0;
	Test1Npc_index2 = 0;
	
	return true;
end

function Test1Npc_PostOver( _MeIndex, _PlayerIndex)
	--NLG.TalkToCli(_PlayerIndex,"你踩到我了, 好痛啊!!", 4, 0, _MeIndex);
	for i = 0, 27 do
		local itemindex = Char.GetItemIndex(_PlayerIndex, i);
		if( itemindex >= 0 ) then
			local buf = "位置: " .. i .. ", 索引: " .. itemindex .. ", 已鑑定名: " .. Item.GetData(itemindex, %道具_已鑑定名%);
			NLG.TalkToCli(_PlayerIndex, buf, 4, 0, _MeIndex);
		end
	end
	return ;
end

function Test1Npc_Talked( _MeIndex, _PlayerIndex)
	--這裡檢查玩家是否站在NPC面前
	if(NLG.CheckInFront(_PlayerIndex, _MeIndex, 1) == false) then
		return ;
	end 

	NLG.ShowWindowTalked(_PlayerIndex, %視窗_選擇框%, %按鈕_取消%, 0, "2\n請選擇選項：\n\n一般遇敵\n與玩家戰鬥\n製造寵物\n刪除寵物\n製造道具\n刪除道具",  _MeIndex);

	return ;
end

function Test1Npc_WindowTalked( _MeIndex, _TalkIndex, _Seqno, _Select, _Data)
	--轉換_Data字串為整數
	local option = tonumber(_Data);

	if (option == 1) then
		--[[
		local TM_EnemyIdAr = {102, 102, 102, 102, 102}; --怪物ＩＤ
		local TM_BaseLevel = {0, 0, 0, 0, 0}; --怪物等級
		local battleindex = NLG.CreateBattle(_TalkIndex, _MeIndex, nil, TM_EnemyIdAr, TM_BaseLevel);
		]]--
		local TM_EnemyIdAr = {959};
		NLG.CreateBattle(_TalkIndex, _MeIndex, nil, TM_EnemyIdAr, nil, nil);
		Battle.SetWinEvent( nil, "Test1Npc_BattleWinCallback", battleindex);
		--NLG.TalkToCli(-1,"Battle.GetPlayIndex: " .. Battle.GetPlayIndex(battleindex, 0, 0) .. ", " .. Battle.GetPlayIndex(battleindex, 0, 1) .. ", " .. Battle.GetPlayIndex(battleindex, 0, 2) .. ", " .. Battle.GetPlayIndex(battleindex, 0, 3) .. ", " .. Battle.GetPlayIndex(battleindex, 0, 4) .. ", " .. Battle.GetPlayIndex(battleindex, 0, 5) .. ", " .. Battle.GetPlayIndex(battleindex, 0, 6) .. ", " .. Battle.GetPlayIndex(battleindex, 0, 7) .. ", " .. Battle.GetPlayIndex(battleindex, 0, 8) .. ", " .. Battle.GetPlayIndex(battleindex, 0, 9) );
		--NLG.TalkToCli(-1,"Battle.GetPlayIndex: " .. Battle.GetPlayIndex(battleindex, 1, 0) .. ", " .. Battle.GetPlayIndex(battleindex, 1, 1) .. ", " .. Battle.GetPlayIndex(battleindex, 1, 2) .. ", " .. Battle.GetPlayIndex(battleindex, 1, 3) .. ", " .. Battle.GetPlayIndex(battleindex, 1, 4) .. ", " .. Battle.GetPlayIndex(battleindex, 1, 5) .. ", " .. Battle.GetPlayIndex(battleindex, 1, 6) .. ", " .. Battle.GetPlayIndex(battleindex, 1, 7) .. ", " .. Battle.GetPlayIndex(battleindex, 1, 8) .. ", " .. Battle.GetPlayIndex(battleindex, 1, 9), 1 );
		for i = 0,9 do
			local charIndex = Battle.GetPlayIndex(battleindex, 0, i);
			if(Char.GetData( charIndex, %對像_類型%) == %對像_玩家%) then
				NLG.TalkToCli(-1 , Char.GetData( charIndex, %對像_原名%) .. ", " .. Char.GetData(charIndex, %對像_類型%) .. ", 進入戰鬥!!", 3);
			end
		end
		elseif (option == 2) then
		if(Test1Npc_count==0) then
			Test1Npc_index1 = _TalkIndex;
			NLG.TalkToCli(_TalkIndex,"報名戰鬥完成，請等待戰鬥開始。");
			Test1Npc_count = Test1Npc_count + 1;
		elseif(Test1Npc_count==1) then
			if(Test1Npc_index1 == _TalkIndex) then
				NLG.TalkToCli(_TalkIndex,"你已經報名過戰鬥。");
			else
				Test1Npc_index2 = _TalkIndex;
				NLG.TalkToCli(_TalkIndex,"報名戰鬥完成，戰鬥開始。");
				NLG.CreateBattlePvP(Test1Npc_index1, Test1Npc_index2);
				Test1Npc_count =0;
				Test1Npc_index1 =0;
				Test1Npc_index2 =0;
			end
		end
	elseif (option == 3) then
		NLG.GivePet(_TalkIndex, 11, 1);
	elseif (option == 4) then
		local petPos = Char.FindPetEnemyId(_TalkIndex, 11);
		if(petPos >=0 ) then
			NLG.TalkToCli(_TalkIndex,"找到ID: 11的寵物，位於位置:" .. petPos .. "。");
			NLG.DelPet(_TalkIndex, 11, 1, 1);
		else
			NLG.TalkToCli(_TalkIndex,"找不到ID: 11的寵物。");
		end
	elseif (option == 5) then
		NLG.GiveItem(_TalkIndex, 15613, 1020);
	elseif (option == 6) then
		local itemPos = Char.FindItemId(_TalkIndex, 15613);
		if(itemPos >= 0) then
			NLG.TalkToCli(_TalkIndex,"找到ID: 15613的道具，位於位置:" .. itemPos .. "。");
			NLG.DelItem(_TalkIndex, 15613, 600);
		else
			NLG.TalkToCli(_TalkIndex,"找不到ID: 15613的道具。");
		end
	end
		
return ;
end

function Test1Npc_BattleWinCallback(_BattleIndex, _CreatePtr)
	for i = 0,9 do
		local charIndex = Battle.GetPlayIndex(_BattleIndex, 0, i);
		if(Char.GetData( charIndex, %對像_類型%) == %對像_玩家%) then
			NLG.TalkToCli(charIndex ,"打贏戰鬥!!", 1);
		end
	end
	return ;
end

function GMSV_NPC_Init()
	if (Test1Npc_index == nil) then	--這句檢查NPC是否已經創建，防止重複創建
		Test1Npc_index = NL.CreateNpc(nil, "Test1Npc_Init");	--創建NPC: 第一個參數是TestNpc_Init函數所在的文件, 第二個參數是NPC初始化時候會調用的函數
		NLG.UpChar(Test1Npc_index);
	end
end
