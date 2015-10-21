#include "Sprite.h"
#include <vector>

class Map
{
public:

	Map();
	~Map();

	void Init();
	bool InitWithFile(const char* file);

	// 0 = no collision, 1 = pill, 2 = wall
	int CheckCollision(int x, int y);
	
	void Draw();

protected:

private:

	// For now we'll use a fixed size map, later it'll be dynamic
	// Sprites that are used to draw the map

	std::vector<Sprite*> m_Level;
	char m_collisionMap[28][36];
};