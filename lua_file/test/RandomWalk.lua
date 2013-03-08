function RandomWalkNpc_Init( RandomWalkNpc_index )
	Char.SetData(RandomWalkNpc_index , %�ﹳ_�ζH%,100002);	--�]�mNPC���ζH��100002
	Char.SetData(RandomWalkNpc_index , %�ﹳ_���%,100002);	--�P�W
	Char.SetData(RandomWalkNpc_index , %�ﹳ_�a������%,0);	--�]�mNPC��MAP ID��0
	Char.SetData(RandomWalkNpc_index , %�ﹳ_�a��%,1000);	--�]�mNPC��Floor ID��1000,�Y�k����
	Char.SetData(RandomWalkNpc_index , %�ﹳ_X%,72);	--�]�mNPC��X���Ь�72
	Char.SetData(RandomWalkNpc_index , %�ﹳ_Y%,88);	--�]�mNPC��Y���Ь�88
	Char.SetData(RandomWalkNpc_index, %�ﹳ_��W%, "�ܷR�������p��");

	--��NPC���U�@�Ӵ`���ƥ�,�`���ե�RandomWalkNpc_Loop_Func���,�`�����j��1000�@��(1��)
	--if (Char.SetLoopEvent(nil, "RandomWalkNpc_Loop_Func", RandomWalkNpc_index, 1000) < 0) then
	--	print("RandomWalkNpc_Loop_Func ���U�ƥ󥢱ѡC");
	--end
	
	--�T�����ƥ�
	if (Char.SetPostOverEvent(nil, "RandomWalkNpc_PostOver", RandomWalkNpc_index) < 0) then
		print("BattleNpc_PostOver ���U�ƥ󥢱ѡC");
		return false;
	end
	
	return true;
end

function RandomWalkNpc_PostOver( _MeIndex, _PlayerIndex)
	NLG.TalkToCli(_PlayerIndex,"���n���ڰ�!!", 4, 0, _MeIndex);
	
	--�w�q�@���H���ƺؤl,�o�˨����H���ƨC�����|���@��
	math.randomseed(os.time());
	--���@��0-7���H����,�N��NPC���ʪ���V
	local dir= math.random(0, 7);
	--�]�mNPC���A������
	local walk = 1;
	NLG.SetAction(_MeIndex,walk);
	--��NPC���@�B
	NLG.WalkMove(_MeIndex,dir);
	--��s���A
	--NLG.UpChar(_MeIndex);
	--�����eNPC���s������
	local x = Char.GetData(_MeIndex, %�ﹳ_X%);
	local y = Char.GetData(_MeIndex, %�ﹳ_Y%);
	--�w�q�@��NPC�����ܤ��e,�׳��ۤv����m
	local buf = "�ڥثe����m�O["..x..","..y.."]�@."
	--��NPC��o�y�ܧi�D���Ҧ����a,-1��ܹ�Ҧ����a,0,0��ܦr��M�C��,�o�̬O���q�r��M�զ�r
	--NLG.TalkToCli(-1,buf,0,0,_MeIndex);
	--��NPC��o�y�ܧi�D�a��1000�����a
	NLG.TalkToFloor(0, 1000, buf,0,0,_MeIndex);
	return ;
end

--NPC���`�����,�Y�H���������
function RandomWalkNpc_Loop_Func(_MeIndex)
	--�w�q�@���H���ƺؤl,�o�˨����H���ƨC�����|���@��
	math.randomseed(os.time());
	--���@��0-7���H����,�N��NPC���ʪ���V
	local dir= math.random(0, 7);
	--�]�mNPC���A������
	local walk = 1;
	NLG.SetAction(_MeIndex,walk);
	--��NPC���@�B
	NLG.WalkMove(_MeIndex,dir);
	--��s���A
	--NLG.UpChar(_MeIndex);
	--�����eNPC���s������
	local x = Char.GetData(_MeIndex, %�ﹳ_X%);
	local y = Char.GetData(_MeIndex, %�ﹳ_Y%);
	--�w�q�@��NPC�����ܤ��e,�׳��ۤv����m
	local buf = "�ڥثe����m�O["..x..","..y.."]�@."
	--��NPC��o�y�ܧi�D���Ҧ����a,-1��ܹ�Ҧ����a,0,0��ܦr��M�C��,�o�̬O���q�r��M�զ�r
	--NLG.TalkToCli(-1,buf,0,0,_MeIndex);
	--��NPC��o�y�ܧi�D�a��1000�����a
	NLG.TalkToFloor(0, 1000, buf);
end
