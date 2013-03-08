--[[
	�`�N �ƥ��T����ƥ����ϥΫ��w���ѼƮ榡�p�U�������
	�ӥB�C�بƥ��T����ƪ��ѼƮ榡�����@�w�@��
	��M�ѼƦW�i�H�۩w�q
--]]

--Init�ƥ��^�Ȭ� true �� false
--_MePtr �O��NPC������
function WindowTalk_Init( _MePtr )
	--�]�mNPC�ζH �]�m�����ɪ��ˤl
	Char.SetData(_MePtr, %�ﹳ_�ζH%, 100020);
	Char.SetData(_MePtr, %�ﹳ_���%, 100020);

	--�]�mNPC�Ҧb�a������
	Char.SetData(_MePtr, %�ﹳ_�a������%, 0);
	
	--�]�mNPC�Ҧb�a��
	Char.SetData(_MePtr, %�ﹳ_�a��%, 1000);

	--�]�mX����
	Char.SetData(_MePtr, %�ﹳ_X%, 233);

	--�]�mY����
	Char.SetData(_MePtr, %�ﹳ_Y%, 83);

	--�]�mNPC��V
	Char.SetData(_MePtr, %�ﹳ_��V%, %�k�U%);

	--�]�mNPC�W��
	Char.SetData(_MePtr, %�ﹳ_��W%, "��ܮش��խ�");


	--�T�����ܨƥ�A���ƥ�p�G�����a�惡NPC���ܴN�|Ĳ�o
	if (Char.SetTalkedEvent(nil, "WindowTalk_Talked", _MePtr) < 0) then
		print("WindowTalk_Talked ���U�ƥ󥢱ѡC");
		return false;
	end
	
	--�T�������ƥ�
	if (Char.SetWindowTalkedEvent(nil, "WindowTalk_WindowTalked", _MePtr) < 0) then
		print("WindowTalk_WindowTalked ���U�ƥ󥢱ѡC");
		return false;
	end
	
	
	--�̫�n��^�ާ@���G
	return true;
end

--Talked�ƥ󤣻ݭn��^�ȩҥH return ; �J�i
--_MePtr �O��NPC������
--_PlayerPtr Ĳ�o�ƥ󪺪��a����

function WindowTalk_Talked( _MePtr, _PlayerPtr)
	--�o���ˬd���a�O�_���bNPC���e
	if(NLG.CheckInFront(_PlayerPtr, _MePtr, 1) == false) then
		return ;
	end 

	NLG.ShowWindowTalked(_PlayerPtr, 1, %���s_�T�w%+ %���s_����%, 0, "�ڬO��ܮش��խ��A�п�J�A�Q���}����ܮؽs���C\n\n 0, 1, 2, 5, 6, 7, 37���w����ܮءC",  _MePtr);

	return ;
end

function WindowTalk_WindowTalked( _MePtr, _TalkPtr, _Seqno, _Select, _Data)
	--����
	if(_Select == %���s_����%) then
		return;
	end
	
	--�ഫ_Data�r�ꬰ���
	local windowType = tonumber(_Data);
	if (_Seqno == 0) then 
		if(windowType==0 or windowType==1) then
			NLG.ShowWindowTalked(_TalkPtr, windowType, %���s_�T�w% + %���s_����%, 1, "�o�O" .. _Data .. "����ܮ�!", _MePtr); 
		elseif (windowType == 2) then
			NLG.ShowWindowTalked(_TalkPtr, windowType, %���s_�T�w% + %���s_����%, 1, "2\n�o�O2����ܮ�!\n\n�ﶵ�@\n�ﶵ�G", _MePtr); 
		elseif (windowType == 5) then
			NLG.ShowWindowTalked(_TalkPtr, windowType, %���s_�T�w%, 1, "14089|�o�O5����ܮ�!|\\n����...\\S|3", _MePtr); 
		elseif (windowType == 37) then
			NLG.ShowWindowTalked(_TalkPtr, windowType, %���s_�T�w% + %���s_����%, 1, "100000|�o�O37����ܮ�!", _MePtr); 
		else
			NLG.ShowWindowTalked(_TalkPtr, windowType, %���s_�T�w% + %���s_����%, 1, "100000|�o�O" .. _Data .. "����ܮ�!", _MePtr); 
		end
	elseif (_Seqno == 1) then
		NLG.ShowWindowTalked(_TalkPtr, 1, %���s_�T�w% + %���s_����%, 0, "�ڬO��ܮش��խ��A�п�J�A�Q���}����ܮؽs���C\n\n 0, 1, 2, 5, 6, 7, 37���w����ܮءC",  _MePtr);
	end
		
return ;
end