function MyBattleOverEvent( _battleIndex)
	print("MyBattleOverEvent, BattleIndex: " .. _battleIndex .. "\n"); --��X��Gmsv������x�ɭ�
	return 0;
end

function MyBattleStartEvent( _battleIndex)
	print("MyBattleStartEvent, BattleIndex: " .. _battleIndex .. "\n"); --��X��Gmsv������x�ɭ�
	return 0;
end

function MyLevelUpEvent( _charaIndex)
	NLG.TalkToCli(_charaIndex, "���ߧA�ɯ��o! �i��oShen���˿ˤ@��!");
	return 0;
end

function MyLoginEvent( _charaIndex)
	NLG.TalkToCli(_charaIndex, "�w��ϥ� CG EX �M��!");
	return 0;
end

function MyLoginGateEvent( _charaIndex)
	NLG.TalkToCli(_charaIndex, "�n�X�^������I��");
	return 0;
end

function MyLogoutEvent( _charaIndex)
	print("MyLogoutEvent, CdKey: " .. Char.GetData(_charaIndex, %�ﹳ_�b��%) .. "\n");
	return 0;
end

function MyTalkEvent( _charaIndex, _msg, _color, _range, _size)
	print("���a���ܤ��e��:".._msg );--��X��Gmsv������x�ɭ�
	return 0;
end

function TitleChangedEvent(_charaIndex, _oldID, newID)
	NLG.TalkToCli(_charaIndex,"�ٸ�ID�q".._oldID.."�ܧ�"..newID);
	return 0;
end

function MyWarpEvent(_charaIndex, _mapID, _floorID, _x, _y)
	NLG.TalkToCli(_charaIndex, "�q mapID: " .. _mapID .. ", floorID: " .. _floorID .. ", X: " .. _x .. ", Y:" .. _y);
	return 0;
end