/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Levels.hpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafernan   <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 11/30/15 by mafernan          #+#    #+#             */
/*   Updated: 2018/09/06 14:34:39 by mafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		LEVELS_HPP
# define	LEVELS_HPP

# include <iostream>
# include <fstream>
# include <vector>
# include "MapError.hpp"

class Levels {
	public:

		Levels();
		Levels(Levels const & src);
		~Levels();
		Levels & operator=(Levels const & src);

		std::vector<std::vector<char> >		makeMap( int seed );
		// std::vector<std::vector<char> >		load( void );
		std::string							getDir( void );

		// void			save(std::vector<std::vector<char> > map);
		void			dimension(int width, int height);
		void			difficulty( int lvl );
		void			changeDir( std::string dir);
		void			debug( void );

		char			populate( void );

		int				getSeed( void );

	private:

		int				_seed = 0;
		int				_debug = 0;
		int				_width = 33;
		int				_height = 15;
		int				_enemyTotal = 5;
		int				_bricks = 0;
		int				_health = 0;
		int				_power = 0;
		int				_lvl = 1;

		std::string		_dir = ".";
};

#endif
