#pragma once
class CScrollManager
{
public:
	CScrollManager();
	~CScrollManager();
public:
	static const int& GetScrollX() { return m_iScrollX; }
	static void SetScrollX(int iScrollX) { m_iScrollX += iScrollX; }
	static const int& GetScrollY() { return m_iScrollY; }
	static void SetScrollY(int iScrollY) { m_iScrollY += iScrollY; }
	static void LockScroll();
private:
	static int m_iScrollX;
	static int m_iScrollY;
};

