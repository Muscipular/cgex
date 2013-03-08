function MyBattleOverEvent( _battleIndex)
	print("MyBattleOverEvent, BattleIndex: " .. _battleIndex .. "\n"); --輸出到Gmsv的控制台界面
	return 0;
end

function MyBattleStartEvent( _battleIndex)
	print("MyBattleStartEvent, BattleIndex: " .. _battleIndex .. "\n"); --輸出到Gmsv的控制台界面
	return 0;
end

function MyLevelUpEvent( _charaIndex)
	NLG.TalkToCli(_charaIndex, "恭喜你升級囉! 可獲得Shen的親親一個!");
	return 0;
end

function MyLoginEvent( _charaIndex)
	NLG.TalkToCli(_charaIndex, "歡迎使用 CG EX 套件!");
	return 0;
end

function MyLoginGateEvent( _charaIndex)
	NLG.TalkToCli(_charaIndex, "登出回到紀錄點啦");
	return 0;
end

function MyLogoutEvent( _charaIndex)
	print("MyLogoutEvent, CdKey: " .. Char.GetData(_charaIndex, %對像_帳號%) .. "\n");
	return 0;
end

function MyTalkEvent( _charaIndex, _msg, _color, _range, _size)
	print("玩家說話內容為:".._msg );--輸出到Gmsv的控制台界面
	return 0;
end

function TitleChangedEvent(_charaIndex, _oldID, newID)
	NLG.TalkToCli(_charaIndex,"稱號ID從".._oldID.."變更為"..newID);
	return 0;
end

function MyWarpEvent(_charaIndex, _mapID, _floorID, _x, _y)
	NLG.TalkToCli(_charaIndex, "從 mapID: " .. _mapID .. ", floorID: " .. _floorID .. ", X: " .. _x .. ", Y:" .. _y);
	return 0;
end