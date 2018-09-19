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

Save::Save(std::vector<std::vector<char>> Save) {
	this->_Save = Save;
}

Save::Save(Save const & src) {
	*this = src;	
}

Save::~Save() {}

Save & Save::operator=(Save const & src) {
	if (this != &src)
    {
	*this = src;
    }
	return (*this);
}

std::vector<std::vector<char> >		Save::getSave( void )
{
	return (this->_Save);
}
