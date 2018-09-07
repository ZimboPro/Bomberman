//
// Created by Patrick RUSSELL on 2018/08/21.
//

#ifndef BOMBERMAN_MAINMENU_HPP
#define BOMBERMAN_MAINMENU_HPP

#include <Model_Sprite.hpp>
#include <Model_Texture.hpp>
#include <list>
#include <vector>
#include <Shaders.hpp>

class MainMenu {

public:
	enum MenuResult {Play, Settings, Exit };

	struct MenuItem
	{
	public:
		Model_Sprite *button;
		MenuResult action;
	};

	MainMenu();
	~MainMenu();

	MenuResult show(Shaders & shader, Shaders & brightShader);

private:
	void loadMenu();
	void deleteMenu();
	std::vector<MenuItem> _menuItems;
	MenuResult _selected;
	std::vector<Model_Texture *> _textures;
};


#endif //BOMBERMAN_MAINMENU_HPP
