// twitter.cpp : DLL �A�v���P�[�V�����p�ɃG�N�X�|�[�g�����֐����`���܂��B
//

#include "stdafx.h"
#include "twitter.h"
#include "../Common/Util.h"
#include "TwitterMain.h"

map<DWORD, CTwitterMain*> g_List;
DWORD g_nextID = 1;

DWORD GetNextID()
{
	DWORD nextID = 0xFFFFFFFF;

	map<DWORD, CTwitterMain*>::iterator itr;
	itr = g_List.find(g_nextID);
	if( itr == g_List.end() ){
		nextID = g_nextID;
		g_nextID++;
		if( g_nextID == 0 || g_nextID == 0xFFFFFFFF){
			g_nextID = 1;
		}
	}else{
		for( DWORD i=1; i<0xFFFFFFFF; i++ ){
			itr = g_List.find(g_nextID);
			if( itr == g_List.end() ){
				nextID = g_nextID;
				g_nextID++;
				if( g_nextID == 0 || g_nextID == 0xFFFFFFFF){
					g_nextID = 1;
				}
				break;
			}else{
				g_nextID++;
			}
			if( g_nextID == 0 || g_nextID == 0xFFFFFFFF){
				g_nextID = 1;
			}
		}
	}

	return nextID;
}

//DLL�̏�����
//�߂�l�F
// �G���[�R�[�h
//�����F
// id				[OUT]����ID
DWORD WINAPI InitializeTW(
	DWORD* id
	)
{
	if( id == NULL ){
		return ERR_INVALID_ARG;
	}

	CTwitterMain* main = new CTwitterMain;
	DWORD err = main->Initialize();
	if( err == NO_ERR ){
		*id = GetNextID();
		g_List.insert(pair<DWORD, CTwitterMain*>(*id, main));
	}
	return err;
}

//DLL�̊J��
//�߂�l�F
// �G���[�R�[�h
//�����F
// id		[IN]����ID InitializeEP�̖߂�l
DWORD WINAPI UnInitializeTW(
	DWORD id
	)
{
	map<DWORD, CTwitterMain*>::iterator itr;
	itr = g_List.find(id);
	if( itr == g_List.end() ){
		return ERR_NOT_INIT;
	}

	DWORD err = itr->second->UnInitialize();

	SAFE_DELETE(itr->second);

	g_List.erase(itr);

	return err;
}


//IE��Proxy�ݒ���擾����
//�߂�l�F
// TRUE�i�֐������j�AFALSE�i�֐����s�j
//�����F
// proxyConfig		[OUT]IE��Proxy�ݒ�̏��i����API�ďo���܂Ń������m�ہj
BOOL WINAPI GetIEProxyConfigTW(
	DWORD id,
	CURRENT_USER_IE_PROXY_CONFIG** proxyConfig
	)
{
	map<DWORD, CTwitterMain*>::iterator itr;
	itr = g_List.find(id);
	if( itr == g_List.end() ){
		return FALSE;
	}

	return itr->second->GetIEProxyConfig(proxyConfig);
}

//�����I�Ɍ��o��Proxy�̃A�h���X���擾����
//�߂�l�F
// TRUE�i�֐������j�AFALSE�i�֐����s�j
//�����F
// proxyConfig		[OUT]Proxy�̏��i����API�ďo���܂Ń������m�ہj
BOOL WINAPI GetProxyAutoDetectTW(
	DWORD id,
	PROXY_CONFIG** proxyConfig
	)
{
	map<DWORD, CTwitterMain*>::iterator itr;
	itr = g_List.find(id);
	if( itr == g_List.end() ){
		return FALSE;
	}

	return itr->second->GetProxyAutoDetect(proxyConfig);
}

//�����\���X�N���v�g��Proxy�̃A�h���X���擾����
//�߂�l�F
// TRUE�i�֐������j�AFALSE�i�֐����s�j
//�����F
// scriptURL		[IN]�����\���X�N���v�g��URL
// proxyConfig		[OUT]Proxy�̏��i����API�ďo���܂Ń������m�ہj
BOOL WINAPI GetProxyAutoScriptTW(
	DWORD id,
	LPCWSTR scriptURL,
	PROXY_CONFIG** proxyConfig
	)
{
	map<DWORD, CTwitterMain*>::iterator itr;
	itr = g_List.find(id);
	if( itr == g_List.end() ){
		return FALSE;
	}

	return itr->second->GetProxyAutoScript(scriptURL, proxyConfig);
}

//Proxy�g�p��ݒ�
//�߂�l�F
// �G���[�R�[�h
//�����F
// useProxy			[IN]Proxy�g�����ǂ����iTRUE:Proxy�g���j
// proxyInfo		[IN]Proxy�g���ꍇ�̐ݒ���
void WINAPI SetProxyTW(
	DWORD id,
	BOOL useProxy,
	USE_PROXY_INFO* proxyInfo
	)
{
	map<DWORD, CTwitterMain*>::iterator itr;
	itr = g_List.find(id);
	if( itr == g_List.end() ){
		return ;
	}

	itr->second->SetProxy(useProxy, proxyInfo);
}

//�F�ؗp���O�C��URL���擾����
//�߂�l�F
// �G���[�R�[�h
//�����F
// url			[OUT]�F�ؗp���O�C��URL�i����API�ďo���܂Ń������m�ہj
DWORD WINAPI GetAuthorizationUrlTW(
	DWORD id,
	WCHAR** url
	)
{
	map<DWORD, CTwitterMain*>::iterator itr;
	itr = g_List.find(id);
	if( itr == g_List.end() ){
		return FALSE;
	}

	return itr->second->GetAuthorizationUrl(url);
}

//�F�،��ʂ̈Ïؔԍ���ݒ肷��
//������GetAuthorizationUrl�Ŏ擾�����l���g�p����̂ŁA��A�̗���Őݒ肷��K�v����
//�߂�l�F
// �G���[�R�[�h
//�����F
// password		[IN]�Ïؔԍ�
DWORD WINAPI SetAuthorizationPWDTW(
	DWORD id,
	LPCWSTR password
	)
{
	map<DWORD, CTwitterMain*>::iterator itr;
	itr = g_List.find(id);
	if( itr == g_List.end() ){
		return FALSE;
	}

	return itr->second->SetAuthorizationPWD(password);
}

//�c�C�[�g����
//�߂�l�F
// �G���[�R�[�h
//�����F
// asyncMode	[IN]�񓯊��ő��M
// text			[IN]�c�C�[�g���e
DWORD WINAPI SendTweetTW(
	DWORD id,
	BOOL asyncMode,
	LPCWSTR text
	)
{
	map<DWORD, CTwitterMain*>::iterator itr;
	itr = g_List.find(id);
	if( itr == g_List.end() ){
		return FALSE;
	}

	return itr->second->SendTweet(asyncMode, text);
}

//�񓯊��c�C�[�g�̎c����擾����
//�߂�l�F
// ��
//�����F
DWORD WINAPI GetTweetQueTW(
	DWORD id
	)
{
	map<DWORD, CTwitterMain*>::iterator itr;
	itr = g_List.find(id);
	if( itr == g_List.end() ){
		return FALSE;
	}

	return itr->second->GetTweetQue();
}

//�X�g���[�~���O���J�n����
//�߂�l�F
// �G���[�R�[�h
//�����F
// track		[IN]filter��track
// streamingID	[OUT]�X�g���[�~���O����ID
DWORD WINAPI StartTweetStreamingTW(
	DWORD id,
	LPCWSTR track,
	TW_CALLBACK_Streaming callbackFunc,
	void* callbackFuncParam,
	DWORD* streamingID
	)
{
	map<DWORD, CTwitterMain*>::iterator itr;
	itr = g_List.find(id);
	if( itr == g_List.end() ){
		return FALSE;
	}

	return itr->second->StartTweetStreaming(track, callbackFunc, callbackFuncParam, streamingID);
}

//�X�g���[�~���O���~����
//�߂�l�F
// �G���[�R�[�h
//�����F
// streamingID	[IN]�X�g���[�~���O����ID
DWORD WINAPI StopTweetStreamingTW(
	DWORD id,
	DWORD streamingID
	)
{
	map<DWORD, CTwitterMain*>::iterator itr;
	itr = g_List.find(id);
	if( itr == g_List.end() ){
		return FALSE;
	}

	return itr->second->StopTweetStreaming(streamingID);
}
