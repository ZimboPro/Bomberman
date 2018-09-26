/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Save.hpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafernan   <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 13/06/18 by mafernan          #+#    #+#             */
/*   Updated: 2018/09/06 08:26:42 by mafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		SAVE_HPP
# define	SAVE_HPP

# include <vector>
# include <boost/archive/text_oarchive.hpp>
# include <boost/archive/text_iarchive.hpp>
# include <boost/serialization/vector.hpp>

class Save {
	private:
		std::vector<std::vector<char>> _Save;
		int		_health = 0;
		int		_score = 0;
		float	_timeLeft = 0;
		int		_enemiesKilled = 0;
		int		_seed = 0;

		friend class boost::serialization::access;
		template<class Archive>
			void serialize(Archive & ar, const unsigned int version)
			{
				(void)version;
				ar & _Save;
				ar & _health;
				ar & _score;
				ar & _timeLeft;
				ar & _enemiesKilled;
				ar & _seed;
			}

	public:
		Save();
		Save(Save const & src);
		Save(std::vector<std::vector<char>> Save, int health, int score, float timeLeft, int enemiesKilled, int seed);
		~Save();
		Save & operator=(Save const & src);

		std::vector<std::vector<char> >		getSave( void );
		int			getScore( void );
		int			getHealth( void );
		float		getTimeLeft ( void );
		int			getEnemiesKilled ( void );
		int			getSeed( void );

};

#endif
