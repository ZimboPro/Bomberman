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
        /**
         * @brief Construct a new Start Game Menu object
         * 
         */
        StartGameMenu();
        /**
         * @brief Construct a new Start Game Menu object
         * 
         * @param src instance of StartGameMenu
         */
        StartGameMenu(StartGameMenu const & src);
        virtual ~StartGameMenu();
    
		enum MenuResult {Start, Load, Back };

		struct MenuItem
		{
            public:
                Model_Sprite *button;
                MenuResult action;
        };
        /**
         * @brief Displays Menu
         * 
         * @param shader 
         * @param brightShader 
         * @return int Describes option selected
         */
		virtual int show(Shaders & shader, Shaders & brightShader);

    private:
		void loadMenu();
		void deleteMenu();
		void moveOnScreen(Shaders & shader, float end);
        void showLevelSelect();
		std::vector<MenuItem> _menuItems;
		MenuResult _selected;
        IAudioProvider * _sound;
};

#endif
