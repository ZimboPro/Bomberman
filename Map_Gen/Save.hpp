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
		friend class boost::serialization::access;

		template<class Archive>
			void serialize(Archive & ar, const unsigned int version)
			{
				(void)version;
				ar & _Save;
			}

	public:
		Save();
		Save(Save const & src);
		Save(std::vector<std::vector<char>> Save);
		~Save();
		Save & operator=(Save const & src);

		std::vector<std::vector<char> >		getSave( void );
};

#endif
