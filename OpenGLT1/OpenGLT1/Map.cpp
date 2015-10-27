#include "Map.h"

#include <fstream>
#include <string>
#include <iostream>

using namespace std;

Map::Map()
{

}

Map::~Map()
{
	m_Level.resize(0);
}

void Map::Init()
{
	m_Level.resize(0);
	// Initialize the map
	for (int x = 0; x < 29; x++)
	{
		for (int y = 0; y < 36; y++)
		{
				m_collisionMap[x][y] = 'e';
		}
	}
}

bool Map::InitWithFile(const char* file)
{
	ifstream infile(file);
	string line;
	int y = 0;
	char buff[1024];

	if ( !infile.bad() )
	{
		while (std::getline(infile, line) )
		{
			strncpy(buff, line.c_str(), sizeof(buff));
			buff[sizeof(buff) - 1] = 0;

			for (size_t x = 0; x < line.length(); x++)
			{
				if ((buff[x] != '\r') || (buff[x] != '*'))
				{
					// Characters
					if (buff[x] == '*')
					{
						m_collisionMap[x][y] = 'w';

						Sprite* tSprite = new Sprite(x * 16, y * 16, 16, 16);
						tSprite->LoadTexture("Data\\Textures\\wall.tga");
						m_Level.push_back(tSprite);
						
					}

					// Characters
					else if (buff[x] == '-')
					{
						m_collisionMap[x][y] = 'e';
					}

					else if (buff[x] == 'o')
					{
						m_collisionMap[x][y] = 'p';
						Sprite* tSprite = new Sprite(x * 16, y * 16, 16, 16);
						tSprite->LoadTexture("Data\\Textures\\pill.tga");
						m_Level.push_back(tSprite);
					}
				}
			}
			y++;
			line.clear();
		}
	}
	else
	{
		return false;
	}

	return true;
}

int Map::CheckCollision(int x, int y)
{
	if (m_collisionMap[x][y] == 'p')
	{
		// TODO: increase score later;
		m_collisionMap[x][y] = 'e';

		return 1;
	}
	else if (m_collisionMap[x][y] == 'w')
	{
		return 2;
	}
	else
	{
		return 0;
	}

	return 5;
}

void Map::Draw()
{
	vector<Sprite*>::iterator i = m_Level.begin();
	while (i != m_Level.end())
	{
		(*i)->Draw();
		++i;
	}
}