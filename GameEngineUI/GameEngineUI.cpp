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

	//player position coordinates.
	float fPlayerPosX = 0.0f;
	float fPlayerPosY = 0.0f;

	//player position coordinates.
	float fPlayerVelX = 0.0f;
	float fPlayerVelY = 0.0f;

	//2D camera.
	float fCameraPosX = 0.0f;
	float fCameraPosY = 0.0f;

protected:
	virtual bool OnUserCreate() {
		
		//initialize game tile dimension.
		nLevelWidth = 64;
		nLevelHeight = 16;

		//symbolic level map.
		sLevel += L"...............................................................";
		sLevel += L"...............................................................";
		sLevel += L"...............................................................";
		sLevel += L".....................###.......................................";
		sLevel += L"...................#.............#.#...........................";
		sLevel += L".................#.............................................";
		sLevel += L"############################.################################..";
		sLevel += L"...............................................................";
		sLevel += L"............................#..................................";
		sLevel += L"...........................#...................................";
		sLevel += L"..........................#....................................";
		sLevel += L".......................#.......................................";
		sLevel += L"........................####...................................";
		sLevel += L"...............................................................";
		sLevel += L"...............................................................";
		sLevel += L"...............................................................";
		

		return true;
	}

	virtual bool OnUserUpdate(float fElapsedtime) {
		//Utility lambdas.
		auto GetTile = [&](int x, int y) {
			if (x >= 0 && x < nLevelWidth && y >= 0 && y < nLevelHeight) {
				return sLevel[y * nLevelWidth + x];
			}
			else {
				return L' ';
			}
		};

		auto SetTile = [&](int x, int y, wchar_t c) {
			if (x >= 0 && x < nLevelWidth && y >= 0 && y < nLevelHeight) {
				return sLevel[y * nLevelWidth + x] = c;
			}
		};

		fPlayerVelX = 0.0f;
		fPlayerVelY = 0.0f;

		//Handle input.
		if (IsFocused()) {
			if (GetKey(VK_UP).bHeld) {
				fPlayerVelY = -6.0f;
			}

			if (GetKey(VK_LEFT).bHeld) {
				fPlayerVelX = -6.0f;
			}

			if (GetKey(VK_DOWN).bHeld) {
				fPlayerVelY = 6.0f;
			}

			if (GetKey(VK_RIGHT).bHeld) {
				fPlayerVelX = 6.0f;
			}
		}

		fPlayerPosX = fPlayerPosX + fPlayerVelX * fElapsedtime;
		fPlayerPosY = fPlayerPosY + fPlayerVelY * fElapsedtime; 
		
		fCameraPosX = fPlayerPosX;
		fCameraPosY = fPlayerPosY;

		//Draw level.
		int nTileWidth = 16;
		int nTileHeight = 16;
		int nVisibleTilesX = ScreenWidth() / nTileWidth;
		int nVisibleTilesY = ScreenHeight() / nTileHeight;

		// Calculate Top-Leftmost visible tile.
		float fOffsetX = fCameraPosX - (float)nVisibleTilesX / 2.0f;
		float fOffsetY = fCameraPosY - (float)nVisibleTilesY / 2.0f;
		
		// Clamp camera to game boundaries.
		if (fOffsetX < 0) fOffsetX = 0;
		if (fOffsetY < 0) fOffsetY = 0;

		if (fOffsetX > nLevelWidth - nVisibleTilesX) fOffsetX = nLevelWidth - nVisibleTilesX;
		if (fOffsetY > nLevelHeight - nVisibleTilesY) fOffsetY = nLevelHeight - nVisibleTilesY;

		// Draw tiles map.
		for (int x = -1; x < nVisibleTilesX +1; x++)
		{
			for (int y = -1; y < nVisibleTilesY +1; y++)
			{
				wchar_t sTileID = GetTile(x +fOffsetX, y + fOffsetY);

				//decide what to draw on the tile.
				switch (sTileID)
				{
				case L'.':
					Fill(x * nTileWidth, y * nTileHeight, (x + 1) * nTileWidth, (y + 1) * nTileHeight, PIXEL_SOLID, FG_CYAN);
					break;
				case L'#':
					Fill(x * nTileWidth, y * nTileHeight, (x + 1) * nTileWidth, (y + 1) * nTileHeight, PIXEL_SOLID, FG_RED);
					break;
				default:
					break;
				}
			}
		}

		//Draw Player.
		Fill((fPlayerPosX - fOffsetX) * nTileWidth, (fPlayerPosY - fOffsetY) * nTileHeight, (fPlayerPosX - fOffsetX + 1.0f) * nTileWidth, (fPlayerPosY - fOffsetY + 1.0f) * nTileHeight, PIXEL_SOLID, FG_RED);

		return true;
	}
};


int main()
{
	OneLoneCoder_Platform game;
	if (game.ConstructConsole(160, 120, 4, 4))
		game.Start();

	return 0;
}
 