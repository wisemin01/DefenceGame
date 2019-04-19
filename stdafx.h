#pragma once

#include <functional>
#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <map>
#include <random>

using namespace std;

typedef D3DXVECTOR2 Vector2;
typedef D3DXVECTOR3 Vector3;

#define WINSIZEX 1280
#define WINSIZEY 720

#define V3CENTER Vector3(WINSIZEX / 2, WINSIZEY / 2, 0)
#define V2CENTER Vector2(WINSIZEX / 2, WINSIZEY / 2)
#define V3ZERO	 Vector3(0, 0, 0)
#define V2ZERO	 Vector2(0, 0)
#define COLORVALUE_DEFAULT {255,255,255,255}

#define CHEET_MODE TRUE

template <typename T>
void Lerp(T* target, const T& start, const T& end, float speed = 0.2f)
{ *target = start + (end - start) * speed; }

int GetRand(int min, int max);

#if DEBUG
#define CONSOLE_LOG(log) std::cout << log << std::endl;
#else
#define CONSOLE_LOG(log)  
#endif

#define MESSAGE_LOG(log) MessageBoxA(DXUTGetHWND(), log, " [MESSAGE_LOG] ", MB_OK);

#define GetNowTime() timeGetTime()

// MANAGERS

#include "CImageManager.h"
#include "CSceneManager.h"
#include "CInputManager.h"
#include "CCameraManager.h"
#include "CObjectManager.h"

// CUSTOM MANAGER

#include "CDataManager.h"
#include "CSkillManager.h"