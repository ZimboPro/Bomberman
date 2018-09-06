//
// Created by Patrick RUSSELL on 2018/08/21.
//

#ifndef BOMBERMAN_MAINMENU_HPP
#define BOMBERMAN_MAINMENU_HPP

#include <ModelSprite.hpp>
#include <ModelTexture.hpp>
#include <list>
#include <vector>

class Shaders;

class MainMenu {

public:
	enum MenuResult {Play, Settings, Exit };

	struct MenuItem
	{
	public:
		ModelSprite *button;
		MenuResult action;
	};

	MainMenu();
	~MainMenu();

	MenuResult show(Shaders & shader, Shaders & brightShader);

private:
	MenuResult getMenuResponse();
	std::list<MenuItem> _menuItems;
	MenuResult _selected;
	std::vector<ModelTexture *> _textures;
};


#endif //BOMBERMAN_MAINMENU_HPP
