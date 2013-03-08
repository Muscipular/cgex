function Test1Npc_Init( Test1Npc_index )
	Char.SetData(Test1Npc_index, %�ﹳ_�ζH%, 100002);
	Char.SetData(Test1Npc_index, %�ﹳ_���%, 100002);
	Char.SetData(Test1Npc_index, %�ﹳ_�a������%, 0);
	Char.SetData(Test1Npc_index, %�ﹳ_�a��%, 1000);
	Char.SetData(Test1Npc_index, %�ﹳ_X%, 234);
	Char.SetData(Test1Npc_index, %�ﹳ_Y% ,83);
	Char.SetData(Test1Npc_index, %�ﹳ_��V%, %�k�U%);
	Char.SetData(Test1Npc_index, %�ﹳ_��W%, "���խ�1��");


	--�T�����ܨƥ�A���ƥ�p�G�����a�惡NPC���ܴN�|Ĳ�o
	if (Char.SetTalkedEvent(nil, "Test1Npc_Talked", Test1Npc_index) < 0) then
		print("Test1Npc_Talked ���U�ƥ󥢱ѡC");
		return false;
	end
	
	--�T�������ƥ�
	if (Char.SetWindowTalkedEvent(nil, "Test1Npc_WindowTalked", Test1Npc_index) < 0) then
		print("Test1Npc_WindowTalked ���U�ƥ󥢱ѡC");
		return false;
	end
	
	--�T�����ƥ�
	--if (Char.SetPostOverEvent(nil, "Test1Npc_PostOver", Test1Npc_index) < 0) then
	--	print("Test1Npc_PostOver ���U�ƥ󥢱ѡC");
	--	return false;
	--end
	
	--PVP �ܼ�
	Test1Npc_count = 0;
	Test1Npc_index1 = 0;
	Test1Npc_index2 = 0;
	
	return true;
end

function Test1Npc_PostOver( _MeIndex, _PlayerIndex)
	--NLG.TalkToCli(_PlayerIndex,"�A���ڤF, �n�h��!!", 4, 0, _MeIndex);
	for i = 0, 27 do
		local itemindex = Char.GetItemIndex(_PlayerIndex, i);
		if( itemindex >= 0 ) then
			local buf = "��m: " .. i .. ", ����: " .. itemindex .. ", �wŲ�w�W: " .. Item.GetData(itemindex, %�D��_�wŲ�w�W%);
			NLG.TalkToCli(_PlayerIndex, buf, 4, 0, _MeIndex);
		end
	end
	return ;
end

function Test1Npc_Talked( _MeIndex, _PlayerIndex)
	--�o���ˬd���a�O�_���bNPC���e
	if(NLG.CheckInFront(_PlayerIndex, _MeIndex, 1) == false) then
		return ;
	end 

	NLG.ShowWindowTalked(_PlayerIndex, %����_��ܮ�%, %���s_����%, 0, "2\n�п�ܿﶵ�G\n\n�@��J��\n�P���a�԰�\n�s�y�d��\n�R���d��\n�s�y�D��\n�R���D��",  _MeIndex);

	return ;
end

function Test1Npc_WindowTalked( _MeIndex, _TalkIndex, _Seqno, _Select, _Data)
	--�ഫ_Data�r�ꬰ���
	local option = tonumber(_Data);

	if (option == 1) then
		--[[
		local TM_EnemyIdAr = {102, 102, 102, 102, 102}; --�Ǫ��ע�
		local TM_BaseLevel = {0, 0, 0, 0, 0}; --�Ǫ�����
		local battleindex = NLG.CreateBattle(_TalkIndex, _MeIndex, nil, TM_EnemyIdAr, TM_BaseLevel);
		]]--
		local TM_EnemyIdAr = {959};
		NLG.CreateBattle(_TalkIndex, _MeIndex, nil, TM_EnemyIdAr, nil, nil);
		Battle.SetWinEvent( nil, "Test1Npc_BattleWinCallback", battleindex);
		--NLG.TalkToCli(-1,"Battle.GetPlayIndex: " .. Battle.GetPlayIndex(battleindex, 0, 0) .. ", " .. Battle.GetPlayIndex(battleindex, 0, 1) .. ", " .. Battle.GetPlayIndex(battleindex, 0, 2) .. ", " .. Battle.GetPlayIndex(battleindex, 0, 3) .. ", " .. Battle.GetPlayIndex(battleindex, 0, 4) .. ", " .. Battle.GetPlayIndex(battleindex, 0, 5) .. ", " .. Battle.GetPlayIndex(battleindex, 0, 6) .. ", " .. Battle.GetPlayIndex(battleindex, 0, 7) .. ", " .. Battle.GetPlayIndex(battleindex, 0, 8) .. ", " .. Battle.GetPlayIndex(battleindex, 0, 9) );
		--NLG.TalkToCli(-1,"Battle.GetPlayIndex: " .. Battle.GetPlayIndex(battleindex, 1, 0) .. ", " .. Battle.GetPlayIndex(battleindex, 1, 1) .. ", " .. Battle.GetPlayIndex(battleindex, 1, 2) .. ", " .. Battle.GetPlayIndex(battleindex, 1, 3) .. ", " .. Battle.GetPlayIndex(battleindex, 1, 4) .. ", " .. Battle.GetPlayIndex(battleindex, 1, 5) .. ", " .. Battle.GetPlayIndex(battleindex, 1, 6) .. ", " .. Battle.GetPlayIndex(battleindex, 1, 7) .. ", " .. Battle.GetPlayIndex(battleindex, 1, 8) .. ", " .. Battle.GetPlayIndex(battleindex, 1, 9), 1 );
		for i = 0,9 do
			local charIndex = Battle.GetPlayIndex(battleindex, 0, i);
			if(Char.GetData( charIndex, %�ﹳ_����%) == %�ﹳ_���a%) then
				NLG.TalkToCli(-1 , Char.GetData( charIndex, %�ﹳ_��W%) .. ", " .. Char.GetData(charIndex, %�ﹳ_����%) .. ", �i�J�԰�!!", 3);
			end
		end
		elseif (option == 2) then
		if(Test1Npc_count==0) then
			Test1Npc_index1 = _TalkIndex;
			NLG.TalkToCli(_TalkIndex,"���W�԰������A�е��ݾ԰��}�l�C");
			Test1Npc_count = Test1Npc_count + 1;
		elseif(Test1Npc_count==1) then
			if(Test1Npc_index1 == _TalkIndex) then
				NLG.TalkToCli(_TalkIndex,"�A�w�g���W�L�԰��C");
			else
				Test1Npc_index2 = _TalkIndex;
				NLG.TalkToCli(_TalkIndex,"���W�԰������A�԰��}�l�C");
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
			NLG.TalkToCli(_TalkIndex,"���ID: 11���d���A����m:" .. petPos .. "�C");
			NLG.DelPet(_TalkIndex, 11, 1, 1);
		else
			NLG.TalkToCli(_TalkIndex,"�䤣��ID: 11���d���C");
		end
	elseif (option == 5) then
		NLG.GiveItem(_TalkIndex, 15613, 1020);
	elseif (option == 6) then
		local itemPos = Char.FindItemId(_TalkIndex, 15613);
		if(itemPos >= 0) then
			NLG.TalkToCli(_TalkIndex,"���ID: 15613���D��A����m:" .. itemPos .. "�C");
			NLG.DelItem(_TalkIndex, 15613, 600);
		else
			NLG.TalkToCli(_TalkIndex,"�䤣��ID: 15613���D��C");
		end
	end
		
return ;
end

function Test1Npc_BattleWinCallback(_BattleIndex, _CreatePtr)
	for i = 0,9 do
		local charIndex = Battle.GetPlayIndex(_BattleIndex, 0, i);
		if(Char.GetData( charIndex, %�ﹳ_����%) == %�ﹳ_���a%) then
			NLG.TalkToCli(charIndex ,"��Ĺ�԰�!!", 1);
		end
	end
	return ;
end

function GMSV_NPC_Init()
	if (Test1Npc_index == nil) then	--�o�y�ˬdNPC�O�_�w�g�ЫءA����ƳЫ�
		Test1Npc_index = NL.CreateNpc(nil, "Test1Npc_Init");	--�Ы�NPC: �Ĥ@�ӰѼƬOTestNpc_Init��ƩҦb�����, �ĤG�ӰѼƬONPC��l�ƮɭԷ|�եΪ����
		NLG.UpChar(Test1Npc_index);
	end
end
