function GMSV_NPC_Init()
	if (M_WindowTalk_index == nil) then					--這句檢查NPC是否已經創建，防止重複創建
		--創建NPC 第一個參數是 WindowTalk_Init函數 所在的文件 第二個參數是NPC初始化時候會調用的函數
		M_WindowTalk_index = NL.CreateNpc("./data/lua/test/WindowTalk.lua", "WindowTalk_Init");
		--向NPC周圍的玩家發送NPC數據更新封包
		NLG.UpChar(M_WindowTalk_index);
	end
	
	if (M_Test1Npc_index == nil) then
		M_Test1Npc_index = NL.CreateNpc("./data/lua/test/Test1.lua", "Test1Npc_Init");
		NLG.UpChar(M_Test1Npc_index);
	end
	
	if (M_Test2Npc_index == nil) then
		M_Test2Npc_index = NL.CreateNpc("./data/lua/test/Test2.lua", "Test2Npc_Init");
		NLG.UpChar(M_Test2Npc_index);
	end
	
	if (RandomWalkNpc_index == nil) then
		RandomWalkNpc_index = NL.CreateNpc("./data/lua/test/RandomWalk.lua", "RandomWalkNpc_Init");
		NLG.UpChar(RandomWalkNpc_index);
	end
	
	if (EquipPlus_index == nil) then
		EquipPlus_index = NL.CreateNpc("./data/lua/EquipPlus/EquipPlus.lua", "EquipPlus_Init");
		NLG.UpChar(EquipPlus_index);
	end
	
	NL.RegBattleOverEvent("./data/lua/nl.lua","MyBattleOverEvent");
	NL.RegBattleStartEvent("./data/lua/nl.lua","MyBattleStartEvent");
	NL.RegLevelUpEvent("./data/lua/nl.lua","MyLevelUpEvent");
	NL.RegLoginEvent("./data/lua/nl.lua","MyLoginEvent");
	NL.RegLoginGateEvent("./data/lua/nl.lua","MyLoginGateEvent");
	NL.RegLogoutEvent("./data/lua/nl.lua","MyLogoutEvent");
	NL.RegTalkEvent("./data/lua/nl.lua","MyTalkEvent");
	NL.RegTitleChangedEvent("./data/lua/nl.lua","TitleChangedEvent");
	NL.RegWarpEvent("./data/lua/nl.lua","MyWarpEvent");
end

--隨機種子
math.randomseed(os.time());
GMSV_NPC_Init();
