/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Levels.hpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafernan   <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 11/30/15 by mafernan          #+#    #+#             */
/*   Updated: 2018/09/27 12:56:01 by mafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		LEVELS_HPP
# define	LEVELS_HPP

# include <iostream>
# include <fstream>
# include <vector>
# include "MapError.hpp"
# include "Save.hpp"
# include "GameInterface.hpp"

class Levels {
	public:

		Levels();
		Levels(Levels const & src);
		~Levels();
		Levels & operator=(Levels const & src);

		std::vector<std::vector<char> >		makeMap( int seed );
		std::vector<std::vector<char> >		load( void );
		std::string							getDir( void );

		void			fixMap(std::vector<std::vector<char> > currentMap, int enemiesKilled);
		void			save(std::vector<std::vector<char> > map, int enemyTotal, int health, int score, float timeLeft);
		void			dimension(int width, int height);
		void			difficulty( int lvl );
		void			changeDir( std::string dir);
		void			debug( void );

		char			populate(int row, int col );

		int				getSeed( void );
		float			getTimeLeft ( void );
		int				getScore( void );
		int				getHealth( void );
		int				distanceToPlayer(int row, int col);
		int				getEnemiesKilled ( void );		

		void				setSeed( int value );
		void				setTimeLeft (  float value );
		void				setScore(  int value );
		void				setHealth(  int value );
		void				setEnemiesKilled (  int value );		

		bool			findGate(std::vector<std::vector<char> > map);

	private:
		bool			_gate = false;
		int				_seed = 0;
		int				_debug = 0;
		int				_width = 15;
		int				_height = 33;
		int				_enemyTotal = 5;
		int				_enemiesKilled = 0;
		int				_bricks = 0;
		int				_health = 0;
		float			_timeLeft = 0;
		int				_power = 0;
		int				_lvl = 1;
		int				_score;
		int				_playerHealth;
		std::vector<std::vector<char> > _lastMap;

		std::string		_dir = ".";
};

#endif
