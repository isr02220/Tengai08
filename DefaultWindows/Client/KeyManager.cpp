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
	keyMap.insert(map<KEY::ID, SHORT>::value_type(KEY::ID::Inventory      , 'E'));
	keyMap.insert(map<KEY::ID, SHORT>::value_type(KEY::ID::Jump           , VK_SPACE));
	keyMap.insert(map<KEY::ID, SHORT>::value_type(KEY::ID::Reload         , 'R'));
	keyMap.insert(map<KEY::ID, SHORT>::value_type(KEY::ID::Action         , 'F'));
	keyMap.insert(map<KEY::ID, SHORT>::value_type(KEY::ID::PrimaryAction  , VK_LBUTTON));
	keyMap.insert(map<KEY::ID, SHORT>::value_type(KEY::ID::SecondaryAction, VK_RBUTTON));

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
	KEY_CHECK(Inventory);
	KEY_CHECK(Jump);
	KEY_CHECK(Reload);
	KEY_CHECK(Action);
	KEY_CHECK(PrimaryAction);
	KEY_CHECK(SecondaryAction);

	KEY_CHECK(SHIFT);
	KEY_CHECK(CONTROL);
	KEY_CHECK(ALT);
}

void CKeyManager::SetKey(KEY::ID _keyID, SHORT _newKey) { keyMap[_keyID] = _newKey; }