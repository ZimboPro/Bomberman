/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StartGameMenu.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpauwels <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 07:00:19 by cpauwels          #+#    #+#             */
/*   Updated: 2018/09/19 07:00:23 by cpauwels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Menus/StartGameMenu.hpp"
#include "Menus/LevelSelectMenu.hpp"
#include "Game.hpp"
#include <Juicy.hpp>

StartGameMenu::StartGameMenu()
{
	_sound = ServiceLocator::getAudio();
	_sound->setSoundLevel(Game::_settings.volume * 20);
	_sound->stopAllSounds();
	if (Game::_settings.music)
		_sound->playSong("../../Assets/sounds/background_music/background_menu.wav", true);
    loadMenu();
}

StartGameMenu::StartGameMenu(StartGameMenu const & src)
{
    *this= src;
}

StartGameMenu::~StartGameMenu()
{}

int StartGameMenu::show(Shaders & shader, Shaders & brightShader)
{
	moveOnScreen(shader, (Game::_window.Width() >> 1));
	glm::mat4 projection = Game::_window.Projection();
	MenuResult temp;
	while (true)
	{
		temp = _selected;
		Game::_window.clear(0.2588f, 0.7961f, 0.8196f);
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
				this->_menuItems[i].button->DrawScaledBy(shader, 1.1f);
		}
		if (Game::keyTyped() ==  eKeys::Up)
			this->_selected = ((this->_selected - 1) < 0) ? MenuResult::Back : static_cast<MenuResult>(this->_selected - 1);
		if (Game::keyTyped() == eKeys::Down)
			this->_selected = ((this->_selected + 1) > MenuResult::Back) ? MenuResult::Start : static_cast<MenuResult>(this->_selected + 1);
		if (Game::keyTyped() == eKeys::Select)
		{
			break;
        }
		if (temp != _selected && Game::_settings.sound)
			_sound->playSound("../../Assets/sounds/button_press/select_settings.wav");
		Game::_window.update();
	}
	if (MenuResult::Back == _selected && Game::_settings.sound)
		_sound->playSound("../../Assets/sounds/button_press/exit_button.wav");
	else if (Game::_settings.sound)
		_sound->playSound("../../Assets/sounds/button_press/start_game.wav");
	moveOnScreen(shader, -20.0f);
	deleteMenu();
	return static_cast<int>(this->_selected);
}

void StartGameMenu::loadMenu()
{	
	MenuItem start;
	MenuItem load;
	MenuItem back;

	Game::_loadingScreen.reset();
	Game::_loadingScreen.display();
	Model_Sprite *temp = new Model_Sprite("../../Assets/buttons/new.obj");
	temp->Position(-20, -20, (Game::_window.Height() << 1) / 3);
	temp->Scale(10);
	temp->Rotate(15, glm::vec3(1, 0, 0));
	start.button = temp;
	start.action = MenuResult::Start;

	Game::_loadingScreen.display();
	temp = new Model_Sprite("../../Assets/buttons/load.obj");
	temp->Position(-20, -20, (Game::_window.Height() >> 1));
	temp->Scale(10);
	temp->Rotate(15, glm::vec3(0, 1, 0));
	load.button = temp;
	load.action = MenuResult::Load;

	Game::_loadingScreen.display();
	temp = new Model_Sprite("../../Assets/buttons/back.obj");
	temp->Position(-20, -20, (Game::_window.Height()) / 3);
	temp->Scale(10);
	temp->Rotate(15, glm::vec3(0, 1, 0));
	back.button = temp;
	back.action = MenuResult::Back;
	
	Game::_loadingScreen.display();
	this->_menuItems.push_back(start);
	this->_menuItems.push_back(load);
	this->_menuItems.push_back(back);

	this->_selected = MenuResult::Start;
}

void StartGameMenu::deleteMenu()
{
	for (size_t i = 0; i < this->_menuItems.size(); i++)
		delete this->_menuItems[i].button;
	this->_menuItems.clear();
}

void StartGameMenu::moveOnScreen(Shaders & shader, float end)
{
	glm::mat4 projection = Game::_window.Projection();
	float weighting = 0.05f;
	glm::vec3 temp(end, this->_menuItems[0].button->GetPosition().y, -60.0f);
	while (0.1f < glm::distance(temp, this->_menuItems[0].button->GetPosition()))
	{
		Game::_window.clear(0.2588f, 0.7961f, 0.8196f);
		shader.use();
		shader.setMat4("projection", projection);
		shader.setMat4("view", glm::mat4());
		shader.setVec3("light", glm::vec3(30, 30, 30));
		for (size_t i = 0; i < this->_menuItems.size(); i++)
		{
			temp.y = this->_menuItems[i].button->GetPosition().y;
			Juicy::Tweening(*this->_menuItems[i].button, temp, weighting);
			Juicy::TweeingRotation(*this->_menuItems[i].button, 15.0f, weighting);
			this->_menuItems[i].button->Draw(shader);
		}
		Game::_window.update();
		temp.y = this->_menuItems[0].button->GetPosition().y;
	}
}