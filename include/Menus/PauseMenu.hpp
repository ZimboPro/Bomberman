/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PauseMenu.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpauwels <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 08:24:27 by cpauwels          #+#    #+#             */
/*   Updated: 2018/09/19 08:24:28 by cpauwels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAUSEMENU_HPP
# define PAUSEMENU_HPP

#include <Model_Sprite.hpp>
#include <Model_Texture.hpp>
#include <vector>
#include "IMenu.hpp"

class PauseMenu : public IMenu
{
    public:
        PauseMenu();
        PauseMenu(PauseMenu const & src);
        virtual ~PauseMenu();

		enum MenuResult { Paused, Resume, Save, Options, Quit };

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
        void showOptionsMenu();
		std::vector<MenuItem> _menuItems;
		MenuResult _selected;
        IAudioProvider * _sound;
};

#endif

