/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.cpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafernan   <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 13/06/18 by mafernan          #+#    #+#             */
/*   Updated: 2018/09/05 13:15:44 by mafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Map.hpp"

Map::Map() {}

Map::Map(std::vector<std::vector<char>> map) {
	this->_map = map;
}

Map::Map(Map const & src) {
	*this = src;	
}

Map::~Map() {}

Map & Map::operator=(Map const & src) {
	if (this != &src)
    {
	*this = src;
    }
	return (*this);
}

std::vector<std::vector<char> >		Map::getMap( void )
{
	return (this->_map);
}
