#include "Txd.h"
#include "game_sa\CTxdStore.h"
#include "game_sa\CPools.h"
#include "TxdManager.h"

// 0D42=2,load_txd %1s% from %2s% // IF and SET
// 0D42: load_txd "rlogos" from "MODELS\\RLOGOS.TXD" // IF and SET
// LOAD_TXD
OpcodeResult WINAPI Txd::LoadTxd(CScriptThread* thread)
{
	OpcodeParams params(thread, 2);
	char name[100], path[100]; int index; bool result;
	params >> name >> path;
	if(txdManager.AddTxd(name, path))
		params << orTrue;
	else
		params << orFalse;
	return OR_CONTINUE;
}

// 0D43=2,%2d% = txd %1s% id
// 0D43: 0@ = txd "rlogos" id
// GET_TXD_ID
OpcodeResult WINAPI Txd::GetTxdId(CScriptThread* thread)
{
	OpcodeParams params(thread, 2);
	char name[100];
	params >> name;
	params << CTxdStore::FindTxdSlot(name);
	return OR_CONTINUE;
}

// 0D44=3,%3d% = find_texture %1s% in_dictionary %2s% // IF and SET
// 0D44: 0@ = find_texture "radio_wctr" in_dictionary "rlogos" // IF and SET
// FIND_TEXTURE_IN_TXD_WITH_NAME
OpcodeResult WINAPI Txd::FindTextureInTxdWithName(CScriptThread* thread)
{
	OpcodeParams params(thread, 3);
	char texName[100], txdName[100]; int index; RwTexDictionary *dictionary; RwTexture *texture;
	params >> texName >> txdName;
	index = CTxdStore::FindTxdSlot(txdName);
	if(index != -1)
	{
		TxdDef *txd = CTxdStore::ms_pTxdPool->GetAt(index);
		if(txd && txd->m_pRwDictionary)
		{
			dictionary = txd->m_pRwDictionary;
			texture = RwTexDictionaryFindNamedTexture(dictionary, texName);
			if(texture)
			{
				params << texture << orTrue;
				return OR_CONTINUE;
			}
		}
	}
	params << NULL << orFalse;
	return OR_CONTINUE;
}

// 0D46=3,%3d% = find_texture %1s% in_dictionary %2d% // IF and SET
// 0D46: 0@ = find_texture "radio_wctr" in_dictionary 1@ // IF and SET
// FIND_TEXTURE_IN_TXD_WITH_ID
OpcodeResult WINAPI Txd::FindTextureInTxdWithId(CScriptThread* thread)
{
	OpcodeParams params(thread, 3);
	char texName[100]; int index; RwTexDictionary *dictionary; RwTexture *texture;
	params >> texName >> index;
	if(index != -1)
	{
		TxdDef *txd = CTxdStore::ms_pTxdPool->GetAt(index);
		if(txd && txd->m_pRwDictionary)
		{
			dictionary = txd->m_pRwDictionary;
			texture = RwTexDictionaryFindNamedTexture(dictionary, texName);
			if(texture)
			{
				params << texture << orTrue;
				return OR_CONTINUE;
			}
		}
	}
	params << NULL << orFalse;
	return OR_CONTINUE;
}