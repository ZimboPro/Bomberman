/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.hpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafernan   <marvin@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 13/06/18 by mafernan          #+#    #+#             */
/*   Updated: 2018/09/06 08:26:42 by mafernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		MAP_HPP
# define	MAP_HPP

# include <vector>
# include <boost/archive/text_oarchive.hpp>
# include <boost/archive/text_iarchive.hpp>
# include <boost/serialization/vector.hpp>

class Map {
	private:
		std::vector<std::vector<char>> _map;
		friend class boost::serialization::access;

		template<class Archive>
			void serialize(Archive & ar, const unsigned int version)
			{
				(void)version;
				ar & _map;
			}

	public:
		Map();
		Map(Map const & src);
		Map(std::vector<std::vector<char>> map);
		~Map();
		Map & operator=(Map const & src);

		std::vector<std::vector<char> >		getMap( void );
};

#endif
