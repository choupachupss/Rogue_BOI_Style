#ifndef CONSTANTES_H
#define CONSTANTES_H

#pragma warning(push, 0)
#include <string>
#pragma warning(pop)

#define VERBOSE 
#define MAZE_LOG_PATH "Maze_Generation.log"
#define RENDERING_PATH "Rendering.log"
#define NUMBER_OF_ROOMS 5

namespace infos
{
	const std::string sprite_path("Rogue_BOI_Style//data//sprite Sheets//");
	const std::string pool_path(sprite_path + "pool_image.txt");
	bool log(const std::string& path, const std::string& message, bool new_line = true);
}

#endif