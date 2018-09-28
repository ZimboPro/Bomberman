/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LevelSelectMenu.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpauwels <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 07:31:14 by cpauwels          #+#    #+#             */
/*   Updated: 2018/09/20 07:31:16 by cpauwels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEVELSELECTMENU_HPP
# define LEVELSELECTMENU_HPP

#include <Model_Sprite.hpp>
#include <Model_Texture.hpp>
#include <vector>
#include "IMenu.hpp"

class LevelSelectMenu : public IMenu
{
    public:
        LevelSelectMenu();
        LevelSelectMenu(LevelSelectMenu const & src);
        virtual ~LevelSelectMenu();

		enum MenuResult { Infinite, Classic, Back };

		struct MenuItem
		{
            public:
                Model_Sprite *button;
                MenuResult action;
        };

		virtual int show(Shaders & shader, Shaders & brightShader);

    private:
		void loadMenu();
		void deleteMenu();
		void moveOnScreen(Shaders & shader, float end);
		std::vector<MenuItem> _menuItems;
		MenuResult _selected;
        IAudioProvider * _sound;
};


#endif
