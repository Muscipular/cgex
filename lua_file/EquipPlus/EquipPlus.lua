function EquipPlus_Init( _MeIndex )
	Char.SetData(_MeIndex, %�ﹳ_�ζH%, 100003);
	Char.SetData(_MeIndex, %�ﹳ_���%, 100003);
	Char.SetData(_MeIndex, %�ﹳ_�a������%, 0);
	Char.SetData(_MeIndex, %�ﹳ_�a��%, 1000);
	Char.SetData(_MeIndex, %�ﹳ_X%, 232);
	Char.SetData(_MeIndex, %�ﹳ_Y%, 83);
	Char.SetData(_MeIndex, %�ﹳ_��V%, %�k�U%);
	Char.SetData(_MeIndex, %�ﹳ_��W%, "�Z���˳Ʈʰ��j�v");

	if (Char.SetTalkedEvent(nil, "EquipPlus_Talked", _MeIndex) < 0) then
		print("EquipPlus_Talked ���U�ƥ󥢱ѡC");
		return false;
	end
	if (Char.SetWindowTalkedEvent(nil, "EquipPlus_WindowTalked", _MeIndex) < 0) then
		print("pztestnpc_WindowTalked ���U�ƥ󥢱ѡC");
		return false;
	end

	return true;
end

--Talked�ƥ�
--�ثe�̰�SEQNO=13
function EquipPlus_Talked( _MeIndex, _PlayerIndex)
	--�o���ˬd���a�O�_���bNPC���e
	if(NLG.CheckInFront(_PlayerIndex, _MeIndex, 1) == false) then
		return ;
	end 
	--���V���a
	local i;
	i = Char.GetData(_PlayerIndex, %�ﹳ_��V%);
	if i >= 4 then 
		i = i - 4;
	else
		i = i + 4;		
	end
	Char.SetData(_MeIndex, %�ﹳ_��V%,i);
	NLG.UpChar( _MeIndex);
	NLG.ShowWindowTalked(_PlayerIndex, 2, 0, 1,
		 "2\n�@�@�@�@�@�@  ���˳ƥ[�j��"..
		 "\n�п��:" ..
	 	 "\n              �m �˳ƦC�� �n" ..
	 	 "\n              �m �D��C�� �n" ..
	 	 "\n               �m ���} �n",
		 _MeIndex);
return ;
end

-- WindowTalked �ƥ�
function EquipPlus_WindowTalked( _MeIndex, _TalkIndex, _Seqno, _Select, _Data)

	--�o���ˬd���a�O�_���bNPC���e
	if(NLG.CheckInFront(_TalkIndex, _MeIndex, 1) == false) then
		return ;
	end

	if _Seqno == 1 then
		if _Data == "1" then
			local pos = 0;
			--�ﻡ���ɤŲK��
			local TM_Buff = "1\n�п��:";
			local itemindex;
			local equip = {"�Y��","����","�k��","����","�}��","��1","��2","����"};

			while(pos <= 8)do
				if (pos == 8) then
					TM_Buff = TM_Buff .. "\n" .. "�@�@�@�@�@�@�@   �m�@���@�}�@�n";
					pos = pos + 1;
				else
					itemindex = Char.GetItemIndex( _TalkIndex, pos);
					if( itemindex > 0)then
						TM_Buff = TM_Buff.."\n".. equip[pos + 1] .. "�G" .. Item.GetData( itemindex, %�D��_�wŲ�w�W%);
					else
						TM_Buff = TM_Buff .. "\n" .. equip[pos + 1] .. "�G�L�˳�";
					end
					pos = pos + 1;
				end
			end
			NLG.ShowWindowTalked( _TalkIndex, 2, 0, 2, TM_Buff, _MeIndex);
			return;
		end
		
		if _Data == "2" then
			--�ﻡ���ɤŲK��
			local pos = 8;
			local TM_Buff = "1\n�п�ܹD��G";
			local itemindex;
			local itempos = {"�D����1","�D����2","�D����3","�D����4","�D����5","�D����6","�D����7","�D����8"};

			while(pos <= 16)do
				itemindex = Char.GetItemIndex( _TalkIndex, pos);
				if (pos == 16) then
					TM_Buff = TM_Buff .. "\n" .. "�@�@�@�@�@�@�@�m�@�U�@�@�@���@�n";
				else
					if( itemindex > 0)then
						TM_Buff = TM_Buff.."\n".. itempos[pos - 7] .. "�G" .. Item.GetData( itemindex, %�D��_�wŲ�w�W%);
					else
						TM_Buff = TM_Buff .. "\n" .. itempos[pos - 7] .. "�G�L�D��";
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
			--�ﻡ���ɤŲK��
			local pos = 16;
			local TM_Buff = "1\n�п�ܹD��G";
			local itemindex;
			local itempos = {"�D����9","�D����10","�D����11","�D����12","�D����13","�D����14","�D����15", "�D����16"};

			while(pos <= 24)do
				itemindex = Char.GetItemIndex( _TalkIndex, pos);
				if (pos == 24) then
				--TM_Buff = TM_Buff .. "\n" .. "�@�@�@�@�@�@�@   �m�@���@�}�@�n";
				TM_Buff = TM_Buff .. "\n" .. "�@�@�@�@�@�@�@�m�@�U�@�@�@���@�n";
				else
					if( itemindex > 0)then
						TM_Buff = TM_Buff.."\n".. itempos[pos - 15] .. "�G" .. Item.GetData( itemindex, %�D��_�wŲ�w�W%);
					else
						TM_Buff = TM_Buff .. "\n" .. itempos[pos - 15] .. "�G�L�D��";
					end
				end
				pos = pos + 1;
			end
			NLG.ShowWindowTalked( _TalkIndex, 2, 0, 4, TM_Buff, _MeIndex);
			
		elseif(_Seqno == 4 and _Data == "9") then
			local pos = 24;
			local TM_Buff = "1\n�п�ܹD��G";
			local itemindex;
			local itempos = {"�D����17","�D����18","�D����19","�D����20"};

			while(pos <= 28)do
				itemindex = Char.GetItemIndex( _TalkIndex, pos);
				if (pos == 28) then
				TM_Buff = TM_Buff .. "\n" .. "�@�@�@�@�@�@�@   �m�@���@�}�@�n";
				else
					if( itemindex > 0)then
						TM_Buff = TM_Buff.."\n".. itempos[pos - 23] .. "�G" .. Item.GetData( itemindex, %�D��_�wŲ�w�W%);
					else
						TM_Buff = TM_Buff .. "\n" .. itempos[pos - 23] .. "�G�L�D��";
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
			local itemid = Item.GetData(itemindex,%�D��_ID%);
--[[
			if(EquipPlus_Check(itemid) > 0)then
				EquipPlus_PPlus(_PlayerIndex,itemindex,itemid, haveitemindex);
				return;
			else 
				NLG.TalkToCli(_PlayerIndex,"�ӹD��L�k�Q�[�j");
				return;
			end
]]--
			EquipPlus_PPlus(_PlayerIndex,itemindex,itemid, haveitemindex);
			return;
		end
	end
end

function EquipPlus_Check(_ItemID)
	local MAX = 20; --�U���C�����ؼ�
	local PlusItemIDTbl = {22870,22871,22872,22879,22880,22881,22888,22889,22890,22897,22898,22899,21056,21057,21058,21059,21060,21061,21062,21063}; --�i�H�[�j���D��ID

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
	--local buf = Item.GetData(itemindex,%�D��_��W%);
	local buf2 = Item.GetData(itemindex,%�D��_�wŲ�w�W%);
--[[
	--1~9�Żݭn���[�j����,�̫�@�����n��
	local itemtbl = {23679,23679,23679,23679,23679,23679,23680,23680,23680,-1};
	--1~9�Żݭn�����Ƽƶq,�̫�@�����n��
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
		NLG.TalkToCli(charaindex,"�L�k�A�[�j.");
		return;
	end
--[[
	if (Char.FindItemId(charaindex,itemtbl[level+1]) < itemnumtbl[level+1]) then
		NLG.TalkToCli(charaindex,"�ʤ֥[�j�һݹD��.");
		return;
	end
]]--
	if(Item.GetData(itemindex,%�D��_Ų�w%) == 0)  then
		NLG.TalkToCli(charaindex,"���D�㥼Ų�w.");
		return;
	elseif(string.find(Item.GetData(itemindex,%�D��_�wŲ�w�W%), "+") == nil) then
		local itemName = Item.GetData(itemindex,%�D��_�wŲ�w�W%);
		Item.SetData(itemindex, %�D��_��Ų�w�W% , itemName);
	end

	--�o�̬O���v,�{�b�O1/10,��10��2�h1/2�����v
	local randnum = math.floor(math.random(1, 1));
	if(randnum == 1)then
		if(level == 8 or level == 7)then
			--�o�O9�ť[�j
			Item.SetData(itemindex,%�D��_�믫%, Item.GetData(itemindex,%�D��_�믫%) + 15);
			Item.SetData(itemindex,%�D��_�^�_%, Item.GetData(itemindex,%�D��_�^�_%) + 15);
			Item.SetData(itemindex,%�D��_����%, Item.GetData(itemindex,%�D��_����%) + 15);
			Item.SetData(itemindex,%�D��_����%, Item.GetData(itemindex,%�D��_����%) + 15);
			Item.SetData(itemindex,%�D��_�R��%, Item.GetData(itemindex,%�D��_�R��%) + 15);
			Item.SetData(itemindex,%�D��_�{��%, Item.GetData(itemindex,%�D��_�{��%) + 15);
		else
			Item.SetData(itemindex,%�D��_�믫%, Item.GetData(itemindex,%�D��_�믫%) + 5);
			Item.SetData(itemindex,%�D��_�^�_%, Item.GetData(itemindex,%�D��_�^�_%) + 5);
			Item.SetData(itemindex,%�D��_����%, Item.GetData(itemindex,%�D��_����%) + 5);
			Item.SetData(itemindex,%�D��_����%, Item.GetData(itemindex,%�D��_����%) + 5);
			Item.SetData(itemindex,%�D��_�R��%, Item.GetData(itemindex,%�D��_�R��%) + 5);
			Item.SetData(itemindex,%�D��_�{��%, Item.GetData(itemindex,%�D��_�{��%) + 5);
		end
		local buff = Item.GetData(itemindex,%�D��_��Ų�w�W%).."+"..level+1;
		Item.SetData(itemindex,%�D��_�wŲ�w�W%,buff);
--[[
		local buff = Item.GetData(itemindex,%�D��_����%);
		if level == 0 then
			local i,j;
			i,j = string.find(buff,"���[�j");
			if(i ~=2 or j ~= 7)then
				buff = "1���[�j"..buff;
			else
				buff = string.gsub(buff,level,level+1);
			end
		else
			buff = string.gsub(buff,level,level+1);
		end
		Item.SetData(itemindex,%�D��_����%,buff);
]]--
--[[
		NLG.DelItem(charaindex,itemtbl[level+1],itemnumtbl[level+1]);
]]--
		--NLG.TalkToCli(charaindex,"�[�j����, �Э��s�n���H��s�D���ݩ�.");
		--NLG.TalkToCli(-1,"����"..Char.GetData(charaindex,%�ﹳ_��W%).."�����[�j�˳�"..Item.GetData(itemindex,%�D��_��Ų�w�W%)..",�{�b�O+"..level+1,%����%);
		Item.UpItem(charaindex, itempos);
		NLG.TalkToCli(charaindex, "�����[�j�˳�"..Item.GetData(itemindex,%�D��_��Ų�w�W%)..",�{�b�O+"..level+1,%����%);
		return;
	else
--[[
		NLG.DelItem(charaindex,itemtbl[level+1],itemnumtbl[level+1]);
]]--
		--���ŷ��v,�{�b�O1/2,��2��3�h�ܬ�1/3
		randnum = math.floor(math.random(1,2));
		if randnum == 1 then
			if(level == 0)then
			NLG.TalkToCli(charaindex,"�[�j�D�㥢��");
			return;
			end
			if(level == 8 or level == 7 or level == 6)then
				Item.SetData(itemindex,%�D��_�믫%, Item.GetData(itemindex,%�D��_�믫%) - 15*(level-7) - 5 * 7);
				Item.SetData(itemindex,%�D��_�^�_%, Item.GetData(itemindex,%�D��_�^�_%) - 15*(level-7) - 5 * 7);
				Item.SetData(itemindex,%�D��_����%, Item.GetData(itemindex,%�D��_����%) - 15*(level-7) - 5 * 7);
				Item.SetData(itemindex,%�D��_����%, Item.GetData(itemindex,%�D��_����%) - 15*(level-7) - 5 * 7);
				Item.SetData(itemindex,%�D��_�R��%, Item.GetData(itemindex,%�D��_�R��%) - 15*(level-7) - 5 * 7);
				Item.SetData(itemindex,%�D��_�{��%, Item.GetData(itemindex,%�D��_�{��%) - 15*(level-7) - 5 * 7);
				local buff = Item.GetData(itemindex,%�D��_��Ų�w�W%);
				Item.SetData(itemindex,%�D��_�wŲ�w�W%,buff);
--[[
				local buff = Item.GetData(itemindex,%�D��_����%);
				buff = string.gsub(buff,level,"0");
				Item.SetData(itemindex,%�D��_����%,buff);
]]--
				Item.UpItem(charaindex, itempos);
				NLG.TalkToCli(charaindex,"�[�j�D�㥢��,���ܹs��");
			else
				Item.SetData(itemindex,%�D��_�믫%, Item.GetData(itemindex,%�D��_�믫%) - 5);
				Item.SetData(itemindex,%�D��_�^�_%, Item.GetData(itemindex,%�D��_�^�_%) - 5);
				Item.SetData(itemindex,%�D��_����%, Item.GetData(itemindex,%�D��_����%) - 5);
				Item.SetData(itemindex,%�D��_����%, Item.GetData(itemindex,%�D��_����%) - 5);
				Item.SetData(itemindex,%�D��_�R��%, Item.GetData(itemindex,%�D��_�R��%) - 5);
				Item.SetData(itemindex,%�D��_�{��%, Item.GetData(itemindex,%�D��_�{��%) - 5);
				local buff = Item.GetData(itemindex,%�D��_��Ų�w�W%).."+"..level-1;
				Item.SetData(itemindex,%�D��_�wŲ�w�W%,buff);
--[[
				local buff = Item.GetData(itemindex,%�D��_����%);
				buff = string.gsub(buff,level,level-1);
				Item.SetData(itemindex,%�D��_����%,buff);
]]--
				Item.UpItem(charaindex, itempos);
				NLG.TalkToCli(charaindex,"�[�j�D�㥢��,���@��");
				end

			return;
		else
			NLG.TalkToCli(charaindex,"�[�j�D�㥢��");
		end




	end
end