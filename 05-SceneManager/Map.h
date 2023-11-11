#pragma once
#include "Textures.h"
#include "Sprites.h"
#include <fstream>
#include "debug.h"

#define TILE_WIDTH 48
#define TILE_HEIGHT 48
#define ID_MAP_TILE_SET 100;
#define MAX_TILE 200

class CMap
{
	int columns;
	int rows;

	int tileWidth = TILE_WIDTH;
	int tileHeight = TILE_HEIGHT;

	int width_map;
	int height_map;

	LPCWSTR tilesetFilePath;
	LPCWSTR mapFilePath;
	int map[MAX_TILE][MAX_TILE];
	int texId;

public:
	CMap(LPCWSTR mapFilePath, LPCWSTR tilesetFilePath, int texId, int width_map, int height_map, int columns, int rows);
	void LoadResourceMap();
	void Render();
};

