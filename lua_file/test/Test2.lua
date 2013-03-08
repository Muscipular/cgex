function Test2Npc_Init( Test2Npc_index )
	Char.SetData(Test2Npc_index, %�ﹳ_�ζH%, 100002);
	Char.SetData(Test2Npc_index, %�ﹳ_���%, 100002);
	Char.SetData(Test2Npc_index, %�ﹳ_�a������%, 0);
	Char.SetData(Test2Npc_index, %�ﹳ_�a��%, 1000);
	Char.SetData(Test2Npc_index, %�ﹳ_X%, 231);
	Char.SetData(Test2Npc_index, %�ﹳ_Y% ,83);
	Char.SetData(Test2Npc_index, %�ﹳ_��V%, %�k�U%);
	Char.SetData(Test2Npc_index, %�ﹳ_��W%, "���խ�2��");


	--�T�����ܨƥ�A���ƥ�p�G�����a�惡NPC���ܴN�|Ĳ�o
	if (Char.SetTalkedEvent(nil, "Test2Npc_Talked", Test2Npc_index) < 0) then
		print("Test2Npc_Talked ���U�ƥ󥢱ѡC");
		return false;
	end
	
	--�T�������ƥ�
	if (Char.SetWindowTalkedEvent(nil, "Test2Npc_WindowTalked", Test2Npc_index) < 0) then
		print("Test2Npc_WindowTalked ���U�ƥ󥢱ѡC");
		return false;
	end
	
	return true;
end


function Test2Npc_Talked( _MeIndex, _PlayerIndex)
	--�o���ˬd���a�O�_���bNPC���e
	if(NLG.CheckInFront(_PlayerIndex, _MeIndex, 1) == false) then
		return ;
	end 

	NLG.ShowWindowTalked(_PlayerIndex, %����_��ܮ�%, %���s_����%, 0, "2\n�п�ܿﶵ�G\n\n���a�d���C��\n�����C��\nSQL�w����\nPet�w-�d��\nPet�w-�ק�",  _MeIndex);

	return ;
end

function Test2Npc_WindowTalked( _MeIndex, _TalkIndex, _Seqno, _Select, _Data)
	--�u�^��seqno == 0
	if(_Seqno ~= 0 ) then
		return;
	end

	--�ഫ_Data�r�ꬰ���
	local option = tonumber(_Data);

	if (option == 1) then
		local buf = "���a�d���C��G\n";
		for i = 0, 4 do
			local PetIndex = Char.GetPetIndex(_TalkIndex, i);
			if(PetIndex >=0) then
				buf = buf .. "��m" .. i .. ": " ..  Char.GetData(PetIndex, %�ﹳ_��W%) .. ", ID: " .. Char.GetPetEnemyId(_TalkIndex, i) .. "\n";
			else
				buf = buf .. "��m" .. i .. ": �L�d��\n";
			end
		end
		NLG.ShowWindowTalked(_TalkIndex, %����_�T����%, %���s_�T�w%, 1, buf,  _MeIndex);
	elseif (option == 2) then
		local buf = "�ն��Ҧ�: " .. Char.GetData(_TalkIndex, %�ﹳ_�ն��Ҧ�%) .. ", �����C��G\n";
		for i = 1, 4 do
			local ParIndex = Char.GetTeamIndex(_TalkIndex, i);
			if(ParIndex >=0) then
				buf = buf .. "��m" .. i .. ": " ..  Char.GetData(ParIndex, %�ﹳ_��W%)  .. "\n";
			else
				buf = buf .. "��m" .. i .. ": �L����\n";
			end
		end
		NLG.ShowWindowTalked(_TalkIndex, %����_�T����%, %���s_�T�w%, 1, buf,  _MeIndex);
	elseif (option == 3) then
		local query = "SELECT * from `tbl_character` WHERE cdkey='" .. %�ﹳ_�b��% ..  "';";
		local resset = SQL.Run(query);
		if(type(resset)=="table")then
			local buf = "���O: " .. query .. "\n";
			buf = buf .. "row�ƶq: " .. resset["row"] .. ", field�ƶq: " ..  resset["field"] .. "\n\n";
			buf = buf .. "��0�C, ��0��: " .. resset["0_0"] .. "\n";
			buf = buf .. "��0�C, ��2��: " .. resset["0_2"] .. "\n";
			NLG.ShowWindowTalked(_TalkIndex, %����_�T����%, %���s_�T�w%, 1, buf,  _MeIndex);
		else
			NLG.TalkToCli(_TalkIndex, NL.GetErrorStr(), 4, 0, _MeIndex);
		end
	elseif (option == 4) then
		local buf = "Pet�w, �d�ɬd�ߡG\n";
		for i = 0, 4 do
			local PetIndex = Char.GetPetIndex(_TalkIndex, i);
			if(PetIndex >=0) then
				buf = buf .. "��m" .. i .. ": " ..  Char.GetData(PetIndex, %�ﹳ_��W%) .. ", ID: " .. Char.GetPetEnemyId(_TalkIndex, i) .. "\n";
				buf = buf .. "�馨��: " .. Pet.GetArtRank(PetIndex, %�d��_�馨%) .. ", ��: " .. Pet.FullArtRank(PetIndex, %�d��_�馨%) .. "\n";
				buf = buf .. "�O����: " .. Pet.GetArtRank(PetIndex, %�d��_�O��%) .. ", ��: " .. Pet.FullArtRank(PetIndex, %�d��_�O��%) .. "\n";
				buf = buf .. "�j����: " .. Pet.GetArtRank(PetIndex, %�d��_�j��%) .. ", ��: " .. Pet.FullArtRank(PetIndex, %�d��_�j��%) .. "\n";
				buf = buf .. "�t����: " .. Pet.GetArtRank(PetIndex, %�d��_�t��%) .. ", ��: " .. Pet.FullArtRank(PetIndex, %�d��_�t��%) .. "\n";
				buf = buf .. "�]����: " .. Pet.GetArtRank(PetIndex, %�d��_�]��%) .. ", ��: " .. Pet.FullArtRank(PetIndex, %�d��_�]��%) .. "\n";
				break;
			end
		end
		NLG.ShowWindowTalked(_TalkIndex, %����_�T����%, %���s_�T�w%, 1, buf,  _MeIndex);
	elseif (option == 5) then
		local buf = "Pet�w, �d�ɭק�G\n";
		for i = 0, 4 do
			local PetIndex = Char.GetPetIndex(_TalkIndex, i);
			if(PetIndex >=0) then
				buf = buf .. "��m" .. i .. ": " ..  Char.GetData(PetIndex, %�ﹳ_��W%) .. ", ID: " .. Char.GetPetEnemyId(_TalkIndex, i) .. "\n";
				local vital = math.random(10, 20);
				Pet.SetArtRank(PetIndex, %�d��_�馨%, vital);
				buf = buf .. "�馨��: " .. vital ..  "\n";
				
				local str = math.random(10, 20);
				Pet.SetArtRank(PetIndex, %�d��_�O��%, str);
				buf = buf .. "�O����: " .. str ..  "\n";
				
				local tough = math.random(10, 20);
				Pet.SetArtRank(PetIndex, %�d��_�j��%, tough);
				buf = buf .. "�j����: " .. tough ..  "\n";
				
				local quick = math.random(10, 20);
				Pet.SetArtRank(PetIndex, %�d��_�t��%, quick);
				buf = buf .. "�t����: " .. quick ..  "\n";
				
				local magic = math.random(10, 20);
				Pet.SetArtRank(PetIndex, %�d��_�]��%, magic);
				buf = buf .. "�]����: " .. magic ..  "\n";

				break;
			end
		end
		NLG.ShowWindowTalked(_TalkIndex, %����_�T����%, %���s_�T�w%, 1, buf,  _MeIndex);
	elseif (option == 6) then

	end
		
return ;
end
