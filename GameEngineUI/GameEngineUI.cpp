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
	wstring sLevel;
	
	//game tile dimensions.
	int nLevelWidth;
	int nLevelHeight;

	//2D camera.
	float fCameraPosX = 0.0f;
	float fCameraPosY = 0.0f;

protected:
	virtual bool OnUserCreate() {
		
		//initialize game tile dimension.
		nLevelHeight = 64;
		nLevelHeight = 16;

		//symbolic level map.
		sLevel += L".............................................................";
		sLevel += L".............................................................";
		sLevel += L".............................................................";
		sLevel += L".....................###.....................................";
		sLevel += L"...................#.............#.#.........................";
		sLevel += L".................#...........................................";
		sLevel += L"############################.################################";
		sLevel += L".............................................................";
		sLevel += L"............................#................................";
		sLevel += L"...........................#.................................";
		sLevel += L"..........................#..................................";
		sLevel += L".......................#.....................................";
		sLevel += L"........................####.................................";
		sLevel += L".............................................................";
		sLevel += L".............................................................";
		sLevel += L".............................................................";
		

		return true;
	}

	virtual bool OnUserUpdate(float fElapsedtime) {
		
		//Draw level.
		int nTileWidth = 16;
		int nTileHeight = 64;

		int nVisibleTilesX = ScreenWidth() / nTileWidth;
		int nVisibleTilesY = ScreenHeight() / nTileHeight;

		// Calculate Top-Leftmost visible tile.
		float fOffsetX = fCameraPosX - (float)nVisibleTilesX / 2.0f;
		float fOffsetY = fCameraPosY - (float)nVisibleTilesY / 2.0f;
		
		// Clamp camera to game boundaries.
		if (fOffsetX < 0) fOffsetX = 0;
		if (fOffsetY < 0) fOffsetY = 0;

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
 