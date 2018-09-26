#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Map.h"
#include <math.h>

j1Map::j1Map() : j1Module(), map_loaded(false)
{
	name.create("map");
}

// Destructor
j1Map::~j1Map()
{}

// Called before render is available
bool j1Map::Awake(pugi::xml_node& config)
{
	LOG("Loading Map Parser");
	bool ret = true;

	folder.create(config.child("folder").child_value());

	return ret;
}

void j1Map::Draw()
{
	if(map_loaded == false)
		return;

	// TODO 6: Iterate all tilesets and draw all their 
	// images in 0,0 (you should have only one tileset for now)

}

// Called before quitting
bool j1Map::CleanUp()
{
	LOG("Unloading map");

	// TODO 2: Make sure you clean up any memory allocated
	// from tilesets / map


	map_file.reset();

	return true;
}

// Load new map
bool j1Map::Load(const char* file_name)
{
	bool ret = true;
	p2SString tmp("%s%s", folder.GetString(), file_name);

	pugi::xml_parse_result result = map_file.load_file(tmp.GetString());

	if(result == NULL)
	{
		LOG("Could not load map xml file %s. pugi error: %s", file_name, result.description());
		ret = false;
	}

	if(ret == true)
	{
		LoadMap();
		// TODO 3: Create and call a private function to load and fill
		// all your map data

	}

	// TODO 4: Create and call a private function to load a tileset
	// remember to support more any number of tilesets!
	

	if(ret == true)
	{
		// TODO 5: LOG all the data loaded
		// iterate all tilesets and LOG everything
	}

	map_loaded = ret;

	return ret;
}

void j1Map::LoadMap()
{
	node = map_file.child("map");

	// Assign the orientation of the map

	p2SString orientationRead = node.attribute("orientation").as_string();

	if (orientationRead == "orthogonal")
		gameMap.orientation = ORTHOGONAL;

	else if (orientationRead == "isometric")
		gameMap.orientation = ISOMETRIC;

	else if (orientationRead == "hexagonal")
		gameMap.orientation = HEXAGONAL;

	// ---------------------------------

	// Assign the render order

	p2SString renderOrderRead = node.attribute("renderorder").as_string();

	if (renderOrderRead == "right-down")
		gameMap.renderorder = RIGHTDOWN;

	else if (renderOrderRead == "left-down")
		gameMap.renderorder = LEFTDOWN;

	else if (renderOrderRead == "right-up")
		gameMap.renderorder = RIGHTUP;

	else if (renderOrderRead == "left-up")
		gameMap.renderorder = LEFTUP;

	// ---------------------------------

	// Assign uint values

	gameMap.width		= node.attribute("width").as_uint();
	gameMap.height		= node.attribute("height").as_uint();
	gameMap.tilewidth	= node.attribute("tilewidth").as_uint();
	gameMap.tileheight	= node.attribute("tileheight").as_uint();

	// ---------------------------------

	// Load all tilesets

	LoadTileset();

	// ---------------------------------

	return;
}

void j1Map::LoadTileset()
{
	// Iterate tilesets while loading them into the list inside of map

	for (pugi::xml_node tilesetIterator = map_file.child("map").child("tileset"); tilesetIterator; tilesetIterator = tilesetIterator.next_sibling("tileset"))
	{
		tileset* newTileset = new tileset();

		node = node.child("tileset");

		newTileset->tilesetName	= node.attribute("name").as_string();
		newTileset->tilewidth	= node.attribute("tilewidth").as_uint();
		newTileset->tileheight	= node.attribute("tileheight").as_uint();
		newTileset->spacing		= node.attribute("spacing").as_uint();
		newTileset->margin		= node.attribute("margin").as_uint();

		gameMap.tilesets.add(*newTileset);
	}

	// ---------------------------------

	return;
}
