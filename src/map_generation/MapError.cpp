
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Error.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 14:30:50 by mafernan          #+#    #+#             */
/*   Updated: 2018/09/06 14:39:22 by mafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_generation/MapError.hpp"

// invalid Dimension sizes
MapError::InvalidSize::InvalidSize(const std::string & line)
{
	e_msg = std::string("Invalid Dimension size : " + line + " too small. Make it bigger than 10.");
}

const char * MapError::InvalidSize::what() const throw ()
{
	return e_msg.c_str();
}

// invalid difficulty
MapError::InvalidDifficulty::InvalidDifficulty(const std::string & line)
{
	e_msg = std::string("Invalid Difficulty level : " + line + " is not accepted. choose between 1-3.");
}

const char * MapError::InvalidDifficulty::what() const throw ()
{
	return e_msg.c_str();
}