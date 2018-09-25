#ifndef __j1MAP_H__
#define __j1MAP_H__

#include "PugiXml/src/pugixml.hpp"
#include "p2List.h"
#include "p2Point.h"
#include "j1Module.h"

// TODO 2: Create a struct to hold information for a TileSet
// Ignore Terrain Types and Tile Types for now, but we want the image!
// ----------------------------------------------------


// TODO 1: Create a struct needed to hold the information to Map node

struct map
{
	enum orientationType
	{
		UNIDENTIFIED_ORIENTATION,
		ORTHOGONAL,
		ISOMETRIC,
		HEXAGONAL,
	};
	enum renderOrderType
	{
		UNIDENTIFIED_RENDERORDER,
		RIGHTDOWN,
		LEFTDOWN,
		RIGHTUP,
		LEFTUP,
	};
	orientationType orientation = UNIDENTIFIED_ORIENTATION;
	renderOrderType renderorder = UNIDENTIFIED_RENDERORDER;
	uint width = 0, height = 0, tilewidth = 0, tileheight = 0;
};

struct tileset
{
	char* tilesetName = "unidentified";
	uint tilewidth = 0, tileheight = 0, spacing = 0, margin = 0, width = 0, height = 0;
	char* sourceAdress = "unidentified";
};

// ----------------------------------------------------
class j1Map : public j1Module
{
public:

	j1Map();

	// Destructor
	virtual ~j1Map();

	// Called before render is available
	bool Awake(pugi::xml_node& conf);

	// Called each loop iteration
	void Draw();

	// Called before quitting
	bool CleanUp();

	// Load new map
	bool Load(const char* path);

private:

	void LoadMap();

public:

	// TODO 1: Add your struct for map info as public for now
	map scene1;

private:

	pugi::xml_document	map_file;
	p2SString			folder;
	bool				map_loaded;
};

#endif // __j1MAP_H__