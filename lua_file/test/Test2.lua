function Test2Npc_Init( Test2Npc_index )
	Char.SetData(Test2Npc_index, %對像_形象%, 100002);
	Char.SetData(Test2Npc_index, %對像_原形%, 100002);
	Char.SetData(Test2Npc_index, %對像_地圖類型%, 0);
	Char.SetData(Test2Npc_index, %對像_地圖%, 1000);
	Char.SetData(Test2Npc_index, %對像_X%, 231);
	Char.SetData(Test2Npc_index, %對像_Y% ,83);
	Char.SetData(Test2Npc_index, %對像_方向%, %右下%);
	Char.SetData(Test2Npc_index, %對像_原名%, "測試員2號");


	--響應說話事件，此事件如果有玩家對此NPC說話就會觸發
	if (Char.SetTalkedEvent(nil, "Test2Npc_Talked", Test2Npc_index) < 0) then
		print("Test2Npc_Talked 註冊事件失敗。");
		return false;
	end
	
	--響應視窗事件
	if (Char.SetWindowTalkedEvent(nil, "Test2Npc_WindowTalked", Test2Npc_index) < 0) then
		print("Test2Npc_WindowTalked 註冊事件失敗。");
		return false;
	end
	
	return true;
end


function Test2Npc_Talked( _MeIndex, _PlayerIndex)
	--這裡檢查玩家是否站在NPC面前
	if(NLG.CheckInFront(_PlayerIndex, _MeIndex, 1) == false) then
		return ;
	end 

	NLG.ShowWindowTalked(_PlayerIndex, %視窗_選擇框%, %按鈕_取消%, 0, "2\n請選擇選項：\n\n玩家寵物列表\n隊員列表\nSQL庫測試\nPet庫-查詢\nPet庫-修改",  _MeIndex);

	return ;
end

function Test2Npc_WindowTalked( _MeIndex, _TalkIndex, _Seqno, _Select, _Data)
	--只回應seqno == 0
	if(_Seqno ~= 0 ) then
		return;
	end

	--轉換_Data字串為整數
	local option = tonumber(_Data);

	if (option == 1) then
		local buf = "玩家寵物列表：\n";
		for i = 0, 4 do
			local PetIndex = Char.GetPetIndex(_TalkIndex, i);
			if(PetIndex >=0) then
				buf = buf .. "位置" .. i .. ": " ..  Char.GetData(PetIndex, %對像_原名%) .. ", ID: " .. Char.GetPetEnemyId(_TalkIndex, i) .. "\n";
			else
				buf = buf .. "位置" .. i .. ": 無寵物\n";
			end
		end
		NLG.ShowWindowTalked(_TalkIndex, %視窗_訊息框%, %按鈕_確定%, 1, buf,  _MeIndex);
	elseif (option == 2) then
		local buf = "組隊模式: " .. Char.GetData(_TalkIndex, %對像_組隊模式%) .. ", 隊員列表：\n";
		for i = 1, 4 do
			local ParIndex = Char.GetTeamIndex(_TalkIndex, i);
			if(ParIndex >=0) then
				buf = buf .. "位置" .. i .. ": " ..  Char.GetData(ParIndex, %對像_原名%)  .. "\n";
			else
				buf = buf .. "位置" .. i .. ": 無隊員\n";
			end
		end
		NLG.ShowWindowTalked(_TalkIndex, %視窗_訊息框%, %按鈕_確定%, 1, buf,  _MeIndex);
	elseif (option == 3) then
		local query = "SELECT * from `tbl_character` WHERE cdkey='" .. %對像_帳號% ..  "';";
		local resset = SQL.Run(query);
		if(type(resset)=="table")then
			local buf = "指令: " .. query .. "\n";
			buf = buf .. "row數量: " .. resset["row"] .. ", field數量: " ..  resset["field"] .. "\n\n";
			buf = buf .. "第0列, 第0行: " .. resset["0_0"] .. "\n";
			buf = buf .. "第0列, 第2行: " .. resset["0_2"] .. "\n";
			NLG.ShowWindowTalked(_TalkIndex, %視窗_訊息框%, %按鈕_確定%, 1, buf,  _MeIndex);
		else
			NLG.TalkToCli(_TalkIndex, NL.GetErrorStr(), 4, 0, _MeIndex);
		end
	elseif (option == 4) then
		local buf = "Pet庫, 寵檔查詢：\n";
		for i = 0, 4 do
			local PetIndex = Char.GetPetIndex(_TalkIndex, i);
			if(PetIndex >=0) then
				buf = buf .. "位置" .. i .. ": " ..  Char.GetData(PetIndex, %對像_原名%) .. ", ID: " .. Char.GetPetEnemyId(_TalkIndex, i) .. "\n";
				buf = buf .. "體成長: " .. Pet.GetArtRank(PetIndex, %寵檔_體成%) .. ", 滿: " .. Pet.FullArtRank(PetIndex, %寵檔_體成%) .. "\n";
				buf = buf .. "力成長: " .. Pet.GetArtRank(PetIndex, %寵檔_力成%) .. ", 滿: " .. Pet.FullArtRank(PetIndex, %寵檔_力成%) .. "\n";
				buf = buf .. "強成長: " .. Pet.GetArtRank(PetIndex, %寵檔_強成%) .. ", 滿: " .. Pet.FullArtRank(PetIndex, %寵檔_強成%) .. "\n";
				buf = buf .. "速成長: " .. Pet.GetArtRank(PetIndex, %寵檔_速成%) .. ", 滿: " .. Pet.FullArtRank(PetIndex, %寵檔_速成%) .. "\n";
				buf = buf .. "魔成長: " .. Pet.GetArtRank(PetIndex, %寵檔_魔成%) .. ", 滿: " .. Pet.FullArtRank(PetIndex, %寵檔_魔成%) .. "\n";
				break;
			end
		end
		NLG.ShowWindowTalked(_TalkIndex, %視窗_訊息框%, %按鈕_確定%, 1, buf,  _MeIndex);
	elseif (option == 5) then
		local buf = "Pet庫, 寵檔修改：\n";
		for i = 0, 4 do
			local PetIndex = Char.GetPetIndex(_TalkIndex, i);
			if(PetIndex >=0) then
				buf = buf .. "位置" .. i .. ": " ..  Char.GetData(PetIndex, %對像_原名%) .. ", ID: " .. Char.GetPetEnemyId(_TalkIndex, i) .. "\n";
				local vital = math.random(10, 20);
				Pet.SetArtRank(PetIndex, %寵檔_體成%, vital);
				buf = buf .. "體成長: " .. vital ..  "\n";
				
				local str = math.random(10, 20);
				Pet.SetArtRank(PetIndex, %寵檔_力成%, str);
				buf = buf .. "力成長: " .. str ..  "\n";
				
				local tough = math.random(10, 20);
				Pet.SetArtRank(PetIndex, %寵檔_強成%, tough);
				buf = buf .. "強成長: " .. tough ..  "\n";
				
				local quick = math.random(10, 20);
				Pet.SetArtRank(PetIndex, %寵檔_速成%, quick);
				buf = buf .. "速成長: " .. quick ..  "\n";
				
				local magic = math.random(10, 20);
				Pet.SetArtRank(PetIndex, %寵檔_魔成%, magic);
				buf = buf .. "魔成長: " .. magic ..  "\n";

				break;
			end
		end
		NLG.ShowWindowTalked(_TalkIndex, %視窗_訊息框%, %按鈕_確定%, 1, buf,  _MeIndex);
	elseif (option == 6) then

	end
		
return ;
end
