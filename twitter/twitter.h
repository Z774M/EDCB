#ifndef __TWITTER_H__
#define __TWITTER_H__

#include "../Common/NWStructDef.h"


//SetAVTransportURI
//�߂�l�F
// �G���[�R�[�h(DMR_CALLBACK_ERR_INVALID_ARGS, DMR_CALLBACK_ERR_MIMETYPE, DMR_CALLBACK_ERR_BUSY, DMR_CALLBACK_ERR_NOT_FOUND, DMR_CALLBACK_ERR_INVALID_ID)
//�����F
// param			[IN] DLNAM_INIT_PARAM_DMR��SetAVTransportURIFuncParam
// streamingID		[IN] ����ID
// json				[IN] json�`���̎�M�f�[�^
typedef int (CALLBACK *TW_CALLBACK_Streaming)(void* param, DWORD streamingID, const char* data, DWORD dataSize);


//DLL�̏�����
//�߂�l�F
// �G���[�R�[�h
//�����F
// id				[OUT]����ID
__declspec(dllexport)
DWORD WINAPI InitializeTW(
	DWORD* id
	);

//DLL�̊J��
//�߂�l�F
// �G���[�R�[�h
//�����F
// id		[IN]����ID
__declspec(dllexport)
DWORD WINAPI UnInitializeTW(
	DWORD id
	);

//IE��Proxy�ݒ���擾����
//�߂�l�F
// TRUE�i�֐������j�AFALSE�i�֐����s�j
//�����F
// proxyConfig		[OUT]IE��Proxy�ݒ�̏��i����API�ďo���܂Ń������m�ہj
__declspec(dllexport)
BOOL WINAPI GetIEProxyConfigTW(
	DWORD id,
	CURRENT_USER_IE_PROXY_CONFIG** proxyConfig
	);

//�����I�Ɍ��o��Proxy�̃A�h���X���擾����
//�߂�l�F
// TRUE�i�֐������j�AFALSE�i�֐����s�j
//�����F
// proxyConfig		[OUT]Proxy�̏��i����API�ďo���܂Ń������m�ہj
__declspec(dllexport)
BOOL WINAPI GetProxyAutoDetectTW(
	DWORD id,
	PROXY_CONFIG** proxyConfig
	);

//�����\���X�N���v�g��Proxy�̃A�h���X���擾����
//�߂�l�F
// TRUE�i�֐������j�AFALSE�i�֐����s�j
//�����F
// scriptURL		[IN]�����\���X�N���v�g��URL
// proxyConfig		[OUT]Proxy�̏��i����API�ďo���܂Ń������m�ہj
__declspec(dllexport)
BOOL WINAPI GetProxyAutoScriptTW(
	DWORD id,
	LPCWSTR scriptURL,
	PROXY_CONFIG** proxyConfig
	);

//Proxy�g�p��ݒ�
//�߂�l�F
// �G���[�R�[�h
//�����F
// useProxy			[IN]Proxy�g�����ǂ����iTRUE:Proxy�g���j
// proxyInfo		[IN]Proxy�g���ꍇ�̐ݒ���
__declspec(dllexport)
void WINAPI SetProxyTW(
	DWORD id,
	BOOL useProxy,
	USE_PROXY_INFO* proxyInfo
	);

//�F�ؗp���O�C��URL���擾����
//�߂�l�F
// �G���[�R�[�h
//�����F
// url			[OUT]�F�ؗp���O�C��URL�i����API�ďo���܂Ń������m�ہj
__declspec(dllexport)
DWORD WINAPI GetAuthorizationUrlTW(
	DWORD id,
	WCHAR** url
	);

//�F�،��ʂ̈Ïؔԍ���ݒ肷��
//������GetAuthorizationUrl�Ŏ擾�����l���g�p����̂ŁA��A�̗���Őݒ肷��K�v����
//�߂�l�F
// �G���[�R�[�h
//�����F
// password		[IN]�Ïؔԍ�
__declspec(dllexport)
DWORD WINAPI SetAuthorizationPWDTW(
	DWORD id,
	LPCWSTR password
	);

//�c�C�[�g����
//�߂�l�F
// �G���[�R�[�h
//�����F
// asyncMode	[IN]�񓯊��ő��M
// text			[IN]�c�C�[�g���e
__declspec(dllexport)
DWORD WINAPI SendTweetTW(
	DWORD id,
	BOOL asyncMode,
	LPCWSTR text
	);

//�񓯊��c�C�[�g�̎c����擾����
//�߂�l�F
// ��
//�����F
__declspec(dllexport)
DWORD WINAPI GetTweetQueTW(
	DWORD id
	);

//�X�g���[�~���O���J�n����
//�߂�l�F
// �G���[�R�[�h
//�����F
// track		[IN]filter��track
// streamingID	[OUT]�X�g���[�~���O����ID
__declspec(dllexport)
DWORD WINAPI StartTweetStreamingTW(
	DWORD id,
	LPCWSTR track,
	TW_CALLBACK_Streaming callbackFunc,
	void* callbackFuncParam,
	DWORD* streamingID
	);

//�X�g���[�~���O���~����
//�߂�l�F
// �G���[�R�[�h
//�����F
// streamingID	[IN]�X�g���[�~���O����ID
__declspec(dllexport)
DWORD WINAPI StopTweetStreamingTW(
	DWORD id,
	DWORD streamingID
	);

#endif
