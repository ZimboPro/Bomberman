/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MapError.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckatz <ckatz@student.wethinkcode.co.za>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 14:26:47 by mafernan          #+#    #+#             */
/*   Updated: 2018/09/10 16:33:17 by ckatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_ERROR_HPP
# define MAP_ERROR_HPP

# include <exception>
# include <iostream>

class MapError {
	public:
		MapError( void );
		~MapError( void );
		class InvalidSize : public std::exception {
			public:
				std::string		e_msg;
				InvalidSize(const std::string & line);
				virtual const char * what() const throw();
		};
		class InvalidDifficulty : public std::exception {
			public:
				std::string		e_msg;
				InvalidDifficulty(const std::string & line);
				virtual const char * what() const throw();
		};
};

#endif
