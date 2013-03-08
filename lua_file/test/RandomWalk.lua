function RandomWalkNpc_Init( RandomWalkNpc_index )
	Char.SetData(RandomWalkNpc_index , %對像_形象%,100002);	--設置NPC的形象為100002
	Char.SetData(RandomWalkNpc_index , %對像_原形%,100002);	--同上
	Char.SetData(RandomWalkNpc_index , %對像_地圖類型%,0);	--設置NPC的MAP ID為0
	Char.SetData(RandomWalkNpc_index , %對像_地圖%,1000);	--設置NPC的Floor ID為1000,即法蘭城
	Char.SetData(RandomWalkNpc_index , %對像_X%,72);	--設置NPC的X坐標為72
	Char.SetData(RandomWalkNpc_index , %對像_Y%,88);	--設置NPC的Y坐標為88
	Char.SetData(RandomWalkNpc_index, %對像_原名%, "很愛走路的小傑");

	--給NPC註冊一個循環事件,循環調用RandomWalkNpc_Loop_Func函數,循環間隔為1000毫秒(1秒)
	--if (Char.SetLoopEvent(nil, "RandomWalkNpc_Loop_Func", RandomWalkNpc_index, 1000) < 0) then
	--	print("RandomWalkNpc_Loop_Func 註冊事件失敗。");
	--end
	
	--響應踐踏事件
	if (Char.SetPostOverEvent(nil, "RandomWalkNpc_PostOver", RandomWalkNpc_index) < 0) then
		print("BattleNpc_PostOver 註冊事件失敗。");
		return false;
	end
	
	return true;
end

function RandomWalkNpc_PostOver( _MeIndex, _PlayerIndex)
	NLG.TalkToCli(_PlayerIndex,"不要擠我啦!!", 4, 0, _MeIndex);
	
	--定義一個隨機數種子,這樣取的隨機數每次都會不一樣
	math.randomseed(os.time());
	--取一個0-7的隨機數,代表NPC移動的方向
	local dir= math.random(0, 7);
	--設置NPC狀態為走路
	local walk = 1;
	NLG.SetAction(_MeIndex,walk);
	--讓NPC走一步
	NLG.WalkMove(_MeIndex,dir);
	--更新狀態
	--NLG.UpChar(_MeIndex);
	--獲取當前NPC的新的坐標
	local x = Char.GetData(_MeIndex, %對像_X%);
	local y = Char.GetData(_MeIndex, %對像_Y%);
	--定義一個NPC的說話內容,匯報自己的位置
	local buf = "我目前的位置是["..x..","..y.."]哦."
	--讓NPC把這句話告訴給所有玩家,-1表示對所有玩家,0,0表示字體和顏色,這裡是普通字體和白色字
	--NLG.TalkToCli(-1,buf,0,0,_MeIndex);
	--讓NPC把這句話告訴地圖1000的玩家
	NLG.TalkToFloor(0, 1000, buf,0,0,_MeIndex);
	return ;
end

--NPC的循環函數,即隨機走路函數
function RandomWalkNpc_Loop_Func(_MeIndex)
	--定義一個隨機數種子,這樣取的隨機數每次都會不一樣
	math.randomseed(os.time());
	--取一個0-7的隨機數,代表NPC移動的方向
	local dir= math.random(0, 7);
	--設置NPC狀態為走路
	local walk = 1;
	NLG.SetAction(_MeIndex,walk);
	--讓NPC走一步
	NLG.WalkMove(_MeIndex,dir);
	--更新狀態
	--NLG.UpChar(_MeIndex);
	--獲取當前NPC的新的坐標
	local x = Char.GetData(_MeIndex, %對像_X%);
	local y = Char.GetData(_MeIndex, %對像_Y%);
	--定義一個NPC的說話內容,匯報自己的位置
	local buf = "我目前的位置是["..x..","..y.."]哦."
	--讓NPC把這句話告訴給所有玩家,-1表示對所有玩家,0,0表示字體和顏色,這裡是普通字體和白色字
	--NLG.TalkToCli(-1,buf,0,0,_MeIndex);
	--讓NPC把這句話告訴地圖1000的玩家
	NLG.TalkToFloor(0, 1000, buf);
end
