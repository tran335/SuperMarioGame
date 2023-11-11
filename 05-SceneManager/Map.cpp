#include "Map.h"

CMap::CMap(LPCWSTR mapFilePath, LPCWSTR tilesetFilePath, int texId, int width_map, int height_map, int columns, int rows)
{
	this->mapFilePath = mapFilePath;
	this->tilesetFilePath = tilesetFilePath;
	this->width_map = width_map;
	this->height_map = height_map;
	this->columns = columns;
	this->rows = rows;
	this->texId = texId;
}

void CMap::LoadResourceMap()
{
	// import data map
	ifstream f;
	f.open(mapFilePath);

	for (int i = 0; i < height_map; i++)
	{
		for (int j = 0; j < width_map; j++)
		{
			f >> map[i][j];

			DebugOut(L"map: %d \n", map[i][j]);
		}
	}

	f.close();

	// load tileset

	CTextures* textures = CTextures::GetInstance();

	textures->Add(texId, tilesetFilePath);

	CSprites* sprites = CSprites::GetInstance();

	LPTEXTURE tileMap = textures->Get(texId);



	int spriteId = 1;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			CSprites::GetInstance()->Add(spriteId, tileHeight * j, tileWidth * i, tileHeight * (j + 1) - 1, tileWidth * (i + 1) - 1, tileMap);
			spriteId++;
		}
	}
}

void CMap::Render()
{
	for (int i = 0; i < height_map; i++)
	{
		for (int j = 0; j < width_map; j++)
		{
			if (map[i][j] != 0)
			{
				CSprites::GetInstance()->Get(map[i][j])->Draw((float)j * TILE_WIDTH, (float)i * TILE_HEIGHT);

			}
		}
	}
}
