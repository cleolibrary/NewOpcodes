#include "TxdManager.h"
#include "game_sa\CTxdStore.h"

TxdManager txdManager;

tTxd::tTxd()
{
	m_isUsed = false;
	m_name[0] = '\0';
}

bool TxdManager::AddTxd(char *name, char *path)
{
	tTxd *freeTxd = NULL;
	for(int i = 0; i < MAX_NO_TXDS; i++)
	{
		if(!m_aTxds[i].m_isUsed)
		{
			if(!freeTxd)
				freeTxd = &m_aTxds[i];
		}
		else if(!_strcmpi(m_aTxds[i].m_name, name))
			return true;
	}
	if(freeTxd)
	{
		freeTxd->m_isUsed = true;
		strcpy(freeTxd->m_name, name);
		freeTxd->m_id = CTxdStore::AddTxdSlot(name);
		CTxdStore::LoadTxd(freeTxd->m_id, path);
		CTxdStore::AddRef(freeTxd->m_id);
		return true;
	}
	else
		return false;
}

void TxdManager::CleanAll()
{
	for(int i = 0; i < MAX_NO_TXDS; i++)
	{
		if(m_aTxds[i].m_isUsed)
		{
			if(m_aTxds[i].m_id != -1)
			{
				TxdDef *txd = CTxdStore::ms_pTxdPool->GetAt(m_aTxds[i].m_id);
				if(txd)
				{
					// Balances the AddRef call from AddTxd.
					CTxdStore::RemoveRef(m_aTxds[i].m_id);
					txd = CTxdStore::ms_pTxdPool->GetAt(m_aTxds[i].m_id);
					if(txd)
						CTxdStore::RemoveTxdSlot(m_aTxds[i].m_id);
				}
			}
			m_aTxds[i].m_isUsed = false;
			m_aTxds[i].m_id = -1;
		}
	}
}