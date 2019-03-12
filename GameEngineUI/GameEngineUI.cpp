// GameEngineUI.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
using namespace std;

#include "olcConsoleGameEngine.h"

class OneLoneCoder_Platform : public olcConsoleGameEngine
{
public:
	OneLoneCoder_Platform() {
		m_sAppName = L"Tile Based Platform Game";
	}
private:

protected:
	virtual bool OnUserCreate() {
		return true;
	}

	virtual bool OnUserUpdate(float fElapsedtime) {
		return true;
	}
};


int main()
{
	OneLoneCoder_Platform game;
	if (game.ConstructConsole(200, 120, 8, 8))
		game.Start();

	return 0;
}
 