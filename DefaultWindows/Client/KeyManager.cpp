#include "framework.h"
#include "KeyManager.h"

CKeyManager* CKeyManager::m_pInstance = nullptr;

CKeyManager* CKeyManager::GetInstance() {
	if (nullptr == m_pInstance)
		m_pInstance = new CKeyManager();

	return m_pInstance;
}

void CKeyManager::DestroyInstance() {
	if (m_pInstance) {
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

CKeyManager::CKeyManager() {
	keyMap.insert(map<KEY::ID, SHORT>::value_type(KEY::ID::MoveUp         , 'W'));
	keyMap.insert(map<KEY::ID, SHORT>::value_type(KEY::ID::MoveRight      , 'D'));
	keyMap.insert(map<KEY::ID, SHORT>::value_type(KEY::ID::MoveLeft       , 'A'));
	keyMap.insert(map<KEY::ID, SHORT>::value_type(KEY::ID::MoveDown       , 'S'));
	keyMap.insert(map<KEY::ID, SHORT>::value_type(KEY::ID::PrimaryAction  , 'J'));
	keyMap.insert(map<KEY::ID, SHORT>::value_type(KEY::ID::SecondaryAction, 'K'));

	keyMap.insert(map<KEY::ID, SHORT>::value_type(KEY::ID::SHIFT          , VK_SHIFT));
	keyMap.insert(map<KEY::ID, SHORT>::value_type(KEY::ID::CONTROL        , VK_CONTROL));
	keyMap.insert(map<KEY::ID, SHORT>::value_type(KEY::ID::ALT            , VK_MENU));
}


CKeyManager::~CKeyManager() {
	DestroyInstance();
}

void CKeyManager::UpdateKeyManager() {
	m_dwKeyEx = m_dwKey;
	m_dwKey = 0;
	KEY_CHECK(MoveUp);
	KEY_CHECK(MoveRight);
	KEY_CHECK(MoveLeft);
	KEY_CHECK(MoveDown);
	KEY_CHECK(PrimaryAction);
	KEY_CHECK(SecondaryAction);

	KEY_CHECK(SHIFT);
	KEY_CHECK(CONTROL);
	KEY_CHECK(ALT);

	for (size_t i = 0; i < 32; i++) {
		if (m_dwKey & 0x00000001 << i) {
			m_KeyStack[i]++;
		}
		else {
			m_KeyStack[i] = 0;
		}
	}
}

void CKeyManager::SetKey(KEY::ID _keyID, SHORT _newKey) { keyMap[_keyID] = _newKey; }