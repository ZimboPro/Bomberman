/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Save.cpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafernan   <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 13/06/18 by mafernan          #+#    #+#             */
/*   Updated: 2018/09/05 13:15:44 by mafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_generation/Save.hpp"

Save::Save() {}

Save::Save(std::vector<std::vector<char>> Save, int health, int score, float timeLeft, int enemiesKilled, int seed)
{
	this->_Save = Save;
	this->_score = score;
	this->_health = health;
	this->_timeLeft = timeLeft;
	this->_enemiesKilled = enemiesKilled;
	this->_seed = seed;
}

Save::Save(Save const & src) 
{
	*this = src;	
}

Save::~Save() {}

Save & Save::operator=(Save const & src) 
{
	if (this != &src)
		*this = src;
	return (*this);
}

std::vector<std::vector<char> >		Save::getSave( void )
{
	return (this->_Save);
}

int			Save::getHealth( void )
{
	return (this->_health);
}

int			Save::getScore( void )
{
	return (this->_score);
}

float		Save::getTimeLeft ( void )
{
	return (this->_timeLeft);
} 

int			Save::getEnemiesKilled ( void )
{
	return (this->_enemiesKilled);
}

int			Save::getSeed( void )
{
	return (this->_seed);
}
