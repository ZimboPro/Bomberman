//
// Created by Patrick RUSSELL on 2018/08/21.
//

#include "MainMenu.hpp"
#include <iostream>
#include <Game.hpp>

MainMenu::MainMenu()
{}

MainMenu::~MainMenu()
{}

MainMenu::MenuResult MainMenu::show(Shaders & shader, Shaders & brightShader)
{
	loadMenu();
	glm::mat4 projection = Game::_window.Projection();
	while (true)
	{
		Game::_window.clear(0.5f, 0.5f, 0.5f);
		shader.use();
		shader.setMat4("projection", projection);
		shader.setMat4("view", glm::mat4());
		shader.setVec3("light", glm::vec3(30, 30, 30));
		for (size_t i = 0; i < this->_menuItems.size(); i++)
		{
			if (this->_menuItems[i].action != this->_selected)
				this->_menuItems[i].button->Draw(shader);
		}
		brightShader.use();
		brightShader.setMat4("projection", projection);
		brightShader.setMat4("view", glm::mat4());
		brightShader.setVec3("light", glm::vec3(30, 30, 30));
		for (size_t i = 0; i < this->_menuItems.size(); i++)
		{
			if (this->_menuItems[i].action == this->_selected)
				this->_menuItems[i].button->Draw(shader);
		}
		if (Game::keyPressed() ==  eKeys::Up)
			this->_selected = ((this->_selected - 1) < 0) ? MenuResult::Play : static_cast<MenuResult>(this->_selected - 1);
		if (Game::keyPressed() == eKeys::Down)
			this->_selected = ((this->_selected + 1) > MenuResult::Exit) ? MenuResult::Exit : static_cast<MenuResult>(this->_selected + 1);
		if (Game::keyPressed() == eKeys::Select)
			break;
		if (Game::_window.closed())
		{
			this->_selected = MenuResult::Exit;
			break;
		}

		Game::_window.update();
	}
	deleteMenu();
	return this->_selected;
}

void MainMenu::loadMenu()
{
	this->_textures.emplace_back(new Model_Texture("../assets/buttons/start.obj"));
	this->_textures.emplace_back(new Model_Texture("../assets/buttons/option.obj"));
	this->_textures.emplace_back(new Model_Texture("../assets/buttons/quit.obj"));
	
	MenuItem start;
	MenuItem options;
	MenuItem quit;
	
	Model_Sprite *temp = new Model_Sprite(*this->_textures[0]);
	temp->Position(Game::_window.Width() >> 1, -20, (Game::_window.Height() << 1) / 3);
	temp->Scale(10);
	start.button = temp;
	start.action = MenuResult::Play;

	temp = new Model_Sprite(*this->_textures[1]);
	temp->Position(Game::_window.Width() >> 1, -20, (Game::_window.Height() >> 1));
	temp->Scale(10);
	options.button = temp;
	options.action = MenuResult::Settings;

	temp = new Model_Sprite(*this->_textures[2]);
	temp->Position(Game::_window.Width() >> 1, -20, (Game::_window.Height()) / 3);
	temp->Scale(10);
	quit.button = temp;
	quit.action = MenuResult::Exit;
	
	this->_menuItems.push_back(start);
	this->_menuItems.push_back(options);
	this->_menuItems.push_back(quit);

	this->_selected = MenuResult::Play;
}

void MainMenu::deleteMenu()
{
	for (size_t i = 0; i < this->_textures.size(); i++)
		delete this->_textures[i];
	this->_textures.clear();

	for (size_t i = 0; i < this->_menuItems.size(); i++)
		delete this->_menuItems[i].button;
	this->_textures.clear();
}