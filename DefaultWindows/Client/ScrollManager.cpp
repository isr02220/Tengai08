#include "framework.h"
#include "ScrollManager.h"

int CScrollManager::m_iScrollX = 0;
int CScrollManager::m_iScrollY = 0;
CScrollManager::CScrollManager()
{
}


CScrollManager::~CScrollManager()
{
}

void CScrollManager::LockScroll()
{
#if 0 // 스테이지 Width, Height 결정되면 추가
	// cout << "iScrollX = " << m_iScrollX << " , iScrollY : " << m_iScrollY << endl; 
	if (0 < m_iScrollX)
		m_iScrollX = 0; 
	if (0 < m_iScrollY)
		m_iScrollY = 0; 
	if ( WINCX - (TILECX * TILEX) > m_iScrollX)
		m_iScrollX = WINCX - (TILECX * TILEX);
	if (WINCY - (TILECY * TILEY) > m_iScrollY)
		m_iScrollY = WINCY - (TILECY * TILEY);
#endif
}
