/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Levels.cpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafernan   <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 11/30/15 by mafernan          #+#    #+#             */
/*   Updated: 2018/09/27 13:16:02 by mafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_generation/Levels.hpp"
#include "Error.hpp"
#include <cmath>

Levels::Levels() {}

Levels::Levels(Levels const & src)
{
	*this = src;	
}

Levels::~Levels() 
{
	for(size_t row = 0; row < _lastMap.size(); row++)
	{
		_lastMap[row].clear();
	}
	_lastMap.clear();
}

Levels & Levels::operator=(Levels const & src)
{
	if (this != &src)
		*this = src;
	return (*this);
}

// ========================================================================== //

// randomly select a type
char	Levels::populate(int row, int col )
{
	int random = static_cast<int>(rand() % 100);
	int spawnRadius = 4;

	if (random >= 80)
	{
		if (random >= 80 && random <= 90 && this->_gate == false)
		{
			this->_gate = true;
			return ('G');
		}
		if (rand() % 100 < 5)
		{
			this->_health += 1;
			return ('7');
		}
		else if (rand() % 100 < 7)
		{
			this->_power += 1;
			return ('6');
		}
		this->_bricks += 1;
		return ('2');
	}
	if (random > 20 && random <= 25 && this->_enemyTotal > 0 && distanceToPlayer(row, col) >= spawnRadius)
	{
		this->_enemyTotal -= 1;
		if (this->_lvl == 1)
			return ('4');
		else if (this->_lvl == 2)
			return (rand() % 10 <= 5 ? '4' : '5' );
		else if (this->_lvl == 3)
			return ('5');
	}
	return ('0');
}

int	Levels::distanceToPlayer(int row, int col)
{
	int distance;

	distance = sqrt(pow((col - 3), 2) + pow((row - 3), 2));
	return distance;
}

// generate a random map from seed
std::vector<std::vector<char> >	 Levels::makeMap( int seed )
{
	char			type = '0';
	int				enemyTotal = this->_enemyTotal;
	std::vector<std::vector<char> >	result;

	// _lvl = (rand() % 3) + 1;
	// check if seed number given is positive
	this->_gate = false;
	while (1)
	{
		if (seed > 0 && seed < 4)
		{
			this->_seed = seed;
			this->_lvl = seed;
		}
		else
			this->_seed = time(NULL);
		// set srand to generate psuedo seed
		srand(this->_seed);
		result.resize(this->_height + 1);
		if (this->_debug == 1)
			std::cout << "creating map" << std::endl;
		// loop thru vector and assign a type
		for (int row = 0; row <= this->_height; row++)
		{
			result[row].resize(this->_width);
			for (int col = 1; col <= this->_width; col++)
			{
				if (col == 3 && row == 3)
					type = '3';
				else if ((col == 4 && row == 3) || (col == 3 && row == 4))
					type = '0';
				else if ((col == 5 && row == 3) || (col == 3 && row == 5))
					type = '0';
				else if (col == 1 || col == this->_width || row == 1 || row == this->_height)
					type = '0';
				else if (row % 2 == 0 && col % 2 == 0)
					type = '1';
				else if ((col >= 2 && col <= this->_width -1) && (row == 2 || row == this->_height - 1))
					type = '1';
				else if ((row >= 2 && row <= this->_height - 1) && (col == 2 || col == this->_width - 1))
					type = '1';
				else if (row > 2 && row < this->_height && col > 2 && col < this->_width)
					type = populate(row, col);
				else
					type = '0';
				if (this->_debug == 1)
					std::cout << type << " ";
				result[row][col - 1] = type;
			}
			type = '0';
			if (this->_debug == 1)
				std::cout << " | " << row << std::endl;
		}
		// print out to see amount of blocks spawned
		if (this->_debug == 1)
		{
			std::cout << "Total enemies not spawned : " << this->_enemyTotal << std::endl;
			std::cout << "Total bricks spawned : " << this->_bricks << std::endl;
			std::cout << "Total health spawned : " << this->_health << std::endl;
			std::cout << "Total powers spawned : " << this->_power << std::endl;
		}
		// reset enemy total
		this->_enemyTotal = enemyTotal;
		// close file when done
		result.erase(result.begin());
		// save generated map
		if (findGate(result) == true)
			break ;
		else
			result.clear();
	}
	this->_lastMap = result;
	return (result);
}

bool		Levels::findGate(std::vector<std::vector<char> > map)
{
	for (size_t x = 0; x < map.size(); x++ )
		for (size_t y = 0; y < map[x].size(); y++ )
			if (map[x][y] == 'G')
				return (true);
	return (false);
}

// update current map with new map
void			Levels::fixMap(std::vector<std::vector<char> > map, int enemiesKilled)
{
	for (size_t y = 0; y < this->_lastMap.size(); y++)
	{
		for (size_t x = 0; x < this->_lastMap[y].size(); x++)
		{
			if (this->_lastMap[y][x] == '4' || this->_lastMap[y][x] == '5')
			{
				if (enemiesKilled > 0)
				{
					this->_lastMap[y][x] = '0';
					enemiesKilled--;
				}
				else
					this->_lastMap[y][x] = this->_lastMap[y][x];
			}
			else if (map[y][x] == '0' && this->_lastMap[y][x] != '3')
				this->_lastMap[y][x] = '0';
		}
	}
}

// save the map
void			Levels::save(std::vector<std::vector<char>> map, int enemyTotal, int health, int score, float timeLeft)
{
	// update current map to current game state
	fixMap(map, enemyTotal);
	// setup object to save to archive
	int seed = 0;
	if (_seed > 0 && _seed < 4)
		seed = _seed;
	else
		seed = 0;
	const Save	temp(this->_lastMap, health, score, timeLeft, enemyTotal, seed);
	const Save *pointer = & temp; 
	// open file stream
	std::ifstream ifs("save.data");
	if (ifs.good())
	{
		ifs.close();
		remove("save.data");
	}
	std::ofstream ofs("save.data");
	// create output archive object with stream
	boost::archive::text_oarchive oa(ofs);
	// write instance to archive
	oa << pointer;
	ofs.close();
}
// load the map
std::vector<std::vector<char> >			Levels::load( void )
{
	Save	*temp;
	// open a read stream
	std::ifstream ifs("save.data");
	if (!ifs.good())
	{
		throw Error::SaveNotFound();
	}
	// create the read archive class with the stream
	boost::archive::text_iarchive		ia(ifs);
	// load the read archive to map
	ia >> temp;
	this->_playerHealth = temp->getHealth();
	GameInterface::setLives(this->_playerHealth);
	this->_score = temp->getScore();
	GameInterface::setScore(this->_score);
	this->_timeLeft = temp->getTimeLeft();
	GameInterface::setTime(this->_timeLeft);
	this->_lastMap = temp->getSave();
	this->_enemiesKilled = temp->getEnemiesKilled();
	GameInterface::setNumEnemies(this->_enemiesKilled);
	this->_seed = temp->getSeed();
	return (temp->getSave());
}

// toggle Debug
void			Levels::debug( void )
{
	if (this->_debug == 0)
		this->_debug = 1;
	else
		this->_debug = 0;
}

// set difficulty
void			Levels::difficulty( int lvl)
{
	if (lvl >= 1 && lvl <= 3)
		this->_lvl = lvl;
	else
		throw MapError::InvalidDifficulty(std::to_string(lvl));
}

// get directory
std::string		Levels::getDir( void )
{
	return (this->_dir);
}

// change directory
void	Levels::changeDir( std::string dir)
{
	this->_dir = dir;
}

// set a width and height
void	Levels::dimension(int width, int height)
{
	if (width < 10)
		throw MapError::InvalidSize("Width");
	else if (height < 10)
		throw MapError::InvalidSize("Height");
	else
	{
		this->_width = width;
		this->_height = height;
	}
}

// get last seed generated
int		Levels::getSeed( void )
{
	return (this->_seed);
}

int		Levels::getScore( void )
{
	return (this->_score);
}

int		Levels::getHealth( void )
{
	return (this->_playerHealth);
}

float	Levels::getTimeLeft ( void )
{
	return (this->_timeLeft);
}

int		Levels::getEnemiesKilled ( void )
{
	return (this->_enemiesKilled);
}

void	Levels::setEnemiesKilled(int value)
{
	this->_enemiesKilled = value;
}

void	Levels::setTimeLeft(float value)
{
	this->_timeLeft = value;
}

void	Levels::setSeed(int value)
{
	this->_seed = value;
}

void	Levels::setScore(int value)
{
	this->_score = value;
}

void	Levels::setHealth(int value)
{
	this->_health = value;
}
