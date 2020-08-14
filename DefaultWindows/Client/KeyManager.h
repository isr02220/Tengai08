#pragma once
#define KEY_CHECK(keyId) if (GetAsyncKeyState(keyMap[KEY::ID::##keyId]) & 0x8000) m_dwKey |= KEY::##keyId
namespace KEY {

	enum class ID {
		MoveUp         ,
		MoveRight      ,
		MoveLeft       ,
		MoveDown       ,
		PrimaryAction  ,
		SecondaryAction,
		SHIFT          ,
		CONTROL        ,
		ALT
	};
	const DWORD MoveUp          = 1 << (INT)ID::MoveUp         ;
	const DWORD MoveRight       = 1 << (INT)ID::MoveRight      ;
	const DWORD MoveLeft        = 1 << (INT)ID::MoveLeft       ;
	const DWORD MoveDown        = 1 << (INT)ID::MoveDown       ;
	const DWORD PrimaryAction   = 1 << (INT)ID::PrimaryAction  ;
	const DWORD SecondaryAction = 1 << (INT)ID::SecondaryAction;
	const DWORD SHIFT           = 1 << (INT)ID::SHIFT          ;
	const DWORD CONTROL         = 1 << (INT)ID::CONTROL        ;
	const DWORD ALT             = 1 << (INT)ID::ALT			   ;


};

class CKeyManager {
public:
	static CKeyManager* GetInstance();
	static void DestroyInstance();
private:
	CKeyManager();
	~CKeyManager();
public:
	void UpdateKeyManager();
	bool Release(DWORD dwKey) {
		if (m_dwKey & dwKey)
			return false;
		else
			return true;
	}

	bool Press(DWORD dwKey) {
		if (m_dwKey & dwKey)
			return true;
		else
			return false;
	}

	bool KeepPress(DWORD dwKey, DWORD time) {
		DWORD keyCode = 0;
		while (dwKey = dwKey >> 1) {
			keyCode++;
		}
		if (m_KeyStack[keyCode] > time)
			return true;
		else
			return false;
	}

	bool OnRelease(DWORD dwKey) {
		if (!(m_dwKey & dwKey) && (m_dwKeyEx & dwKey))
			return true;
		else
			return false;

		return false;

	}

	bool OnPress(DWORD dwKey) {
		if ((m_dwKey & dwKey) && !(m_dwKeyEx & dwKey))
			return true;
		else
			return false;

		return false;
	}
	void SetKey(KEY::ID _keyID, SHORT _newKey);
private:
	DWORD m_dwKey = 0;
	DWORD m_dwKeyEx = 0;
	DWORD m_KeyStack[32] = {};
	map<KEY::ID, SHORT> keyMap;
	static CKeyManager* m_pInstance;

};