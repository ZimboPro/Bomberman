//
// Created by Patrick RUSSELL on 2018/08/21.
//

#include <iostream>
#include <Shaders.hpp>
#include <Juicy.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Menus/MainMenu.hpp"
#include "Game.hpp"

MainMenu::MainMenu()
{
	_sound = ServiceLocator::getAudio();
	_sound->setSoundLevel(Game::_settings.volume * 20);
	_sound->stopAllSounds();
	if (Game::_settings.music)
		_sound->playSong("../../Assets/sounds/background_music/background_menu.wav", true);
	loadMenu();
}

MainMenu::~MainMenu()
{}

int MainMenu::show(Shaders & shader, Shaders & brightShader)
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
			this->_selected = ((this->_selected - 1) < 0) ? MenuResult::Exit : static_cast<MenuResult>(this->_selected - 1);
		if (Game::keyTyped() == eKeys::Down)
			this->_selected = ((this->_selected + 1) > MenuResult::Exit) ? MenuResult::Play : static_cast<MenuResult>(this->_selected + 1);
		if (Game::keyTyped() == eKeys::Select)
			break;
		if (Game::_window.closed() || Game::keyTyped() == eKeys::Escape)
		{
			this->_selected = MenuResult::Exit;
			break;
		}
		if (temp != _selected && Game::_settings.sound)
			_sound->playSound("../../Assets/sounds/button_press/select_settings.wav");
		Game::_window.update();
	}
	if (MenuResult::Exit == _selected && Game::_settings.sound)
		_sound->playSound("../../Assets/sounds/button_press/exit_button.wav");
	else if (Game::_settings.sound)
		_sound->playSound("../../Assets/sounds/button_press/start_game.wav");
	moveOnScreen(shader, -20.0f);
	deleteMenu();
	return static_cast<int>(this->_selected);
}

void MainMenu::loadMenu()
{	
	MenuItem start;
	MenuItem options;
	MenuItem quit;

	Game::_loadingScreen.reset();
	Game::_loadingScreen.display();
	Model_Sprite *temp = new Model_Sprite("../../Assets/buttons/start.obj");
	temp->Position(-20, -20, (Game::_window.Height() << 1) / 3);
	temp->Scale(10);
	temp->Rotate(15, glm::vec3(1, 0, 0));
	start.button = temp;
	start.action = MenuResult::Play;

	Game::_loadingScreen.display();
	temp = new Model_Sprite("../../Assets/buttons/option.obj");
	temp->Position(-20, -20, (Game::_window.Height() >> 1));
	temp->Scale(10);
	temp->Rotate(15, glm::vec3(0, 1, 0));
	options.button = temp;
	options.action = MenuResult::Settings;

	Game::_loadingScreen.display();
	temp = new Model_Sprite("../../Assets/buttons/quit.obj");
	temp->Position(-20, -20, (Game::_window.Height()) / 3);
	temp->Scale(10);
	temp->Rotate(15, glm::vec3(0, 1, 0));
	quit.button = temp;
	quit.action = MenuResult::Exit;
	
	Game::_loadingScreen.display();
	this->_menuItems.push_back(start);
	this->_menuItems.push_back(options);
	this->_menuItems.push_back(quit);

	this->_selected = MenuResult::Play;
}

void MainMenu::deleteMenu()
{
	for (size_t i = 0; i < this->_menuItems.size(); i++)
		delete this->_menuItems[i].button;
	this->_menuItems.clear();
}

void MainMenu::moveOnScreen(Shaders & shader, float end)
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