#pragma once

#include "game_sa\CTxdStore.h"

#define MAX_NO_TXDS 100

enum eTxdState
{
	FAILED_TO_LOAD,
	ALREADY_LOADED,
	READY_FOR_LOADING
};

struct tTxd
{
	char m_name[32];
	short m_id;
	bool m_isUsed;

	tTxd();
};

class TxdManager
{
public:
	tTxd m_aTxds[MAX_NO_TXDS];
	bool AddTxd(char *name, char *path);
	void CleanAll();
};

extern TxdManager txdManager;