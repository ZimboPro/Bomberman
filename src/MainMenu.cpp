//
// Created by Patrick RUSSELL on 2018/08/21.
//

#include "MainMenu.hpp"
#include <iostream>
#include <Shaders.hpp>
#include <Game.hpp>

MainMenu::MainMenu()
{
	this->_textures.emplace_back(new ModelTexture("../assets/buttons/start.obj"));
	this->_textures.emplace_back(new ModelTexture("../assets/buttons/option.obj"));
	this->_textures.emplace_back(new ModelTexture("../assets/buttons/quit.obj"));
	
	MenuItem start;
	MenuItem options;
	MenuItem quit;
	
	ModelSprite *temp = new ModelSprite(*this->_textures[0]);
	temp->Scale(0.02);
	temp->Position(0.5, 0.01);
	start.button = temp;
	start.action = MenuResult::Play;

	temp = new ModelSprite(*this->_textures[1]);
	temp->Scale(0.02);
	temp->Position(0.5, 0.11);
	options.button = temp;
	options.action = MenuResult::Settings;

	temp = new ModelSprite(*this->_textures[2]);
	temp->Scale(0.02);
	temp->Position(0.5, 0.21);
	quit.button = temp;
	quit.action = MenuResult::Exit;
	
	this->_menuItems.push_back(start);
	this->_menuItems.push_back(options);
	this->_menuItems.push_back(quit);

	this->_selected = MenuResult::Play;
}

MainMenu::~MainMenu()
{
	for (size_t i = 0; i < this->_textures.size(); i++)
		delete this->_textures[i];
	this->_textures.clear();

	for (size_t i = 0; i < this->_menuItems.size(); i++)
		delete this->_menuItems[i].button;
	this->_textures.clear();
}

MainMenu::MenuResult MainMenu::show(Shaders & shader, Shaders & brightShader)
{
	while (true)
	{
		shader.use();
		shader.setMat4("projection", Game::_window.Projection());
		shader.setMat4("view", glm::mat4());
		for (size_t i = 0; i < this->_menuItems.size(); i++)
		{
			if (this->_menuItems[i].action != this->_selected)
				this->_menuItems[i].button->Draw(shader);
		}
		brightShader.use();
		brightShader.setMat4("projection", Game::_window.Projection());
		brightShader.setMat4("view", glm::mat4());
		for (size_t i = 0; i < this->_menuItems.size(); i++)
		{
			if (this->_menuItems[i].action == this->_selected)
				this->_menuItems[i].button->Draw(brightShader);
		}
		if (Game::_window.isKeyPressed(GLFW_KEY_UP))
			this->_selected = (this->_selected - 1) < 0 ? MenuResult::Play : this->_selected - 1;
		if (Game::_window.isKeyPressed(GLFW_KEY_DOWN))
			this->_selected = (this->_selected + 1) >= MenuResult.size() ? MenuResult::Exit : this->_selected + 1;
		if (Game::_window.isKeyPressed(GLFW_KEY_ENTER))
			break;
	}
	return this->_selected;
}

MainMenu::MenuResult  MainMenu::handleClick(int x, int y)
{
	for(auto menuItem : _menuItems)
	{
		if (y >= menuItem.rect.top && y <= (menuItem.rect.top + menuItem.rect.height))
			if (x >= menuItem.rect.left && x <= (menuItem.rect.left + menuItem.rect.width))
			{
				return menuItem.action;
			}
	}
}

MainMenu::MenuResult MainMenu::getMenuResponse(sf::RenderWindow &window)
{
	sf::Event event;

	while(window.isOpen())
	{
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
					return MenuResult::Exit;
				case sf::Event::MouseButtonPressed:
					if (event.mouseButton.button == sf::Mouse::Left)
						return handleClick(event.mouseButton.x, event.mouseButton.y);
				default:
					break;
			}
		}
	}
}