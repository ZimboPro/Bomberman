//
// Created by Patrick RUSSELL on 2018/08/21.
//

#ifndef BOMBERMAN_MAINMENU_HPP
#define BOMBERMAN_MAINMENU_HPP

#include <Model_Sprite.hpp>
#include <Model_Texture.hpp>
#include <vector>
#include "IMenu.hpp"
#include "ServiceLocator.hpp"

class MainMenu : public IMenu
{
	public:
		enum MenuResult {Play, Settings, Exit };

		struct MenuItem
		{
		public:
			Model_Sprite *button;
			MenuResult action;
		};

		MainMenu();
		virtual ~MainMenu();

		virtual int show(Shaders & shader, Shaders & brightShader);

	private:
		void loadMenu();
		void deleteMenu();
		void moveOnScreen(Shaders & shader, float end);
		std::vector<MenuItem> _menuItems;
		MenuResult _selected;
		IAudioProvider * _sound;
};


#endif //BOMBERMAN_MAINMENU_HPP
