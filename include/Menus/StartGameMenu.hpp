/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StartGameMenu.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpauwels <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 07:00:34 by cpauwels          #+#    #+#             */
/*   Updated: 2018/09/19 07:00:35 by cpauwels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STARTGAMEMENU_HPP
# define STARTGAMEMENU_HPP

#include <Model_Sprite.hpp>
#include <Model_Texture.hpp>
#include <vector>
#include "Menus/IMenu.hpp"

class StartGameMenu : public IMenu
{
    public:
        StartGameMenu();
        StartGameMenu(StartGameMenu const & src);
        ~StartGameMenu();

		enum MenuResult {Start, Load, Back };

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
};

#endif
