--[[
	注意 事件響應函數必須使用指定的參數格式如下面的函數
	而且每種事件的響應函數的參數格式都不一定一樣
	當然參數名可以自定義
--]]

--Init事件返回值為 true 或 false
--_MePtr 是本NPC的指標
function WindowTalk_Init( _MePtr )
	--設置NPC形象 設置成紅暴的樣子
	Char.SetData(_MePtr, %對像_形象%, 100020);
	Char.SetData(_MePtr, %對像_原形%, 100020);

	--設置NPC所在地圖類型
	Char.SetData(_MePtr, %對像_地圖類型%, 0);
	
	--設置NPC所在地圖
	Char.SetData(_MePtr, %對像_地圖%, 1000);

	--設置X坐標
	Char.SetData(_MePtr, %對像_X%, 233);

	--設置Y坐標
	Char.SetData(_MePtr, %對像_Y%, 83);

	--設置NPC方向
	Char.SetData(_MePtr, %對像_方向%, %右下%);

	--設置NPC名稱
	Char.SetData(_MePtr, %對像_原名%, "對話框測試員");


	--響應說話事件，此事件如果有玩家對此NPC說話就會觸發
	if (Char.SetTalkedEvent(nil, "WindowTalk_Talked", _MePtr) < 0) then
		print("WindowTalk_Talked 註冊事件失敗。");
		return false;
	end
	
	--響應視窗事件
	if (Char.SetWindowTalkedEvent(nil, "WindowTalk_WindowTalked", _MePtr) < 0) then
		print("WindowTalk_WindowTalked 註冊事件失敗。");
		return false;
	end
	
	
	--最後要返回操作結果
	return true;
end

--Talked事件不需要返回值所以 return ; 既可
--_MePtr 是本NPC的指標
--_PlayerPtr 觸發事件的玩家指標

function WindowTalk_Talked( _MePtr, _PlayerPtr)
	--這裡檢查玩家是否站在NPC面前
	if(NLG.CheckInFront(_PlayerPtr, _MePtr, 1) == false) then
		return ;
	end 

	NLG.ShowWindowTalked(_PlayerPtr, 1, %按鈕_確定%+ %按鈕_取消%, 0, "我是對話框測試員，請輸入你想打開的對話框編號。\n\n 0, 1, 2, 5, 6, 7, 37為已知對話框。",  _MePtr);

	return ;
end

function WindowTalk_WindowTalked( _MePtr, _TalkPtr, _Seqno, _Select, _Data)
	--取消
	if(_Select == %按鈕_取消%) then
		return;
	end
	
	--轉換_Data字串為整數
	local windowType = tonumber(_Data);
	if (_Seqno == 0) then 
		if(windowType==0 or windowType==1) then
			NLG.ShowWindowTalked(_TalkPtr, windowType, %按鈕_確定% + %按鈕_取消%, 1, "這是" .. _Data .. "號對話框!", _MePtr); 
		elseif (windowType == 2) then
			NLG.ShowWindowTalked(_TalkPtr, windowType, %按鈕_確定% + %按鈕_取消%, 1, "2\n這是2號對話框!\n\n選項一\n選項二", _MePtr); 
		elseif (windowType == 5) then
			NLG.ShowWindowTalked(_TalkPtr, windowType, %按鈕_確定%, 1, "14089|這是5號對話框!|\\n註解...\\S|3", _MePtr); 
		elseif (windowType == 37) then
			NLG.ShowWindowTalked(_TalkPtr, windowType, %按鈕_確定% + %按鈕_取消%, 1, "100000|這是37號對話框!", _MePtr); 
		else
			NLG.ShowWindowTalked(_TalkPtr, windowType, %按鈕_確定% + %按鈕_取消%, 1, "100000|這是" .. _Data .. "號對話框!", _MePtr); 
		end
	elseif (_Seqno == 1) then
		NLG.ShowWindowTalked(_TalkPtr, 1, %按鈕_確定% + %按鈕_取消%, 0, "我是對話框測試員，請輸入你想打開的對話框編號。\n\n 0, 1, 2, 5, 6, 7, 37為已知對話框。",  _MePtr);
	end
		
return ;
end