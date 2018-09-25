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
	if (node.append_attribute("orientation").as_string() == "orthogonal")
		gameMap.orientation = ORTHOGONAL;

	else if (node.append_attribute("orientation").as_string() == "isometric")
		gameMap.orientation = ISOMETRIC;

	else if (node.append_attribute("orientation").as_string() == "hexagonal")
		gameMap.orientation = HEXAGONAL;

	// ---------------------------------

	// Assign the render order
	if (node.append_attribute("renderorder").as_string() == "right-down")
		gameMap.renderorder = RIGHTDOWN;

	else if (node.append_attribute("renderorder").as_string() == "left-down")
		gameMap.renderorder = LEFTDOWN;

	else if (node.append_attribute("renderorder").as_string() == "right-up")
		gameMap.renderorder = RIGHTUP;

	else if (node.append_attribute("renderorder").as_string() == "left-up")
		gameMap.renderorder = LEFTUP;

	// ---------------------------------

	// Assign uint values

	gameMap.width = node.append_attribute("width").as_uint();
	gameMap.height = node.append_attribute("height").as_uint();
	gameMap.tilewidth = node.append_attribute("tilewidth").as_uint();
	gameMap.tileheight = node.append_attribute("tileheight").as_uint();

	// ---------------------------------

	return;
}