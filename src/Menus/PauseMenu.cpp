/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PauseMenu.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpauwels <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 08:25:56 by cpauwels          #+#    #+#             */
/*   Updated: 2018/09/19 08:26:02 by cpauwels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Menus/PauseMenu.hpp"
#include "Game.hpp"
#include "Menus/OptionsMenu.hpp"
#include <Juicy.hpp>

PauseMenu::PauseMenu()
{
	_sound = ServiceLocator::getAudio();
	_sound->setSoundLevel(Game::_settings.volume * 20);
	_sound->stopAllSounds();
	if (Game::_settings.music)
		_sound->playSong("../../Assets/sounds/background_music/background_menu.wav", true);
    loadMenu();
}

PauseMenu::PauseMenu(PauseMenu const & src)
{
    *this= src;
}

PauseMenu::~PauseMenu()
{}

int PauseMenu::show(Shaders & shader, Shaders & brightShader)
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
			if (this->_menuItems[i].action != this->_selected && i != 0)
				this->_menuItems[i].button->Draw(shader);
		}
		brightShader.use();
		brightShader.setMat4("projection", projection);
		brightShader.setMat4("view", glm::mat4());
		brightShader.setVec3("light", glm::vec3(30, 30, 30));
		for (size_t i = 0; i < this->_menuItems.size(); i++)
		{
			if (this->_menuItems[i].action == this->_selected || i == 0)
				this->_menuItems[i].button->DrawScaledBy(shader, 1.1f);
		}
		if (Game::keyTyped() ==  eKeys::Up)
			this->_selected = ((this->_selected - 1) < 1) ? MenuResult::Quit : static_cast<MenuResult>(this->_selected - 1);
		if (Game::keyTyped() == eKeys::Down)
			this->_selected = ((this->_selected + 1) > MenuResult::Quit) ? MenuResult::Resume : static_cast<MenuResult>(this->_selected + 1);
		if (Game::keyTyped() == eKeys::Select)
		{
            if (_selected == MenuResult::Options)
                showOptionsMenu();
			else 
				break;
        }
		if (temp != _selected && Game::_settings.sound)
			_sound->playSound("../../Assets/sounds/button_press/select_settings.wav");
		Game::_window.update();
	}
	if (MenuResult::Quit == _selected && Game::_settings.sound)
		_sound->playSound("../../Assets/sounds/button_press/exit_button.wav");
	else if (Game::_settings.sound)
		_sound->playSound("../../Assets/sounds/button_press/start_game.wav");
	moveOnScreen(shader, -20.0f);
	deleteMenu();
	return static_cast<int>(this->_selected);
}

void PauseMenu::showOptionsMenu()
{
	OptionsMenu menu;

	Shaders brightShader("../assets/shaders/vert/ShadedModelsVert.glsl", "../assets/shaders/frag/ShadedModelsFrag.glsl");
	Shaders shader("../assets/shaders/vert/ShadedModelsVert.glsl", "../assets/shaders/frag/DarkShadedModelsFrag.glsl");
	
	int selection = menu.show(shader, brightShader);
}

void PauseMenu::loadMenu()
{	
    MenuItem paused;
	MenuItem resume;
	MenuItem save;
	MenuItem options;
	MenuItem back;

	Game::_loadingScreen.reset();
	Game::_loadingScreen.display();
	Model_Sprite *temp = new Model_Sprite("../../Assets/buttons/paused.obj");
	temp->Position(-20, -20, ((Game::_window.Height() / 7) * 6));
	temp->Scale(10);
	temp->Rotate(15, glm::vec3(1, 0, 0));
	paused.button = temp;
	paused.action = MenuResult::Paused;

	Game::_loadingScreen.reset();
	Game::_loadingScreen.display();
	temp = new Model_Sprite("../../Assets/buttons/resume.obj");
	temp->Position(-20, -20, (Game::_window.Height() / 7) * 4);
	temp->Scale(8);
	temp->Rotate(15, glm::vec3(1, 0, 0));
	resume.button = temp;
	resume.action = MenuResult::Resume;

	Game::_loadingScreen.reset();
	Game::_loadingScreen.display();
	temp = new Model_Sprite("../../Assets/buttons/save.obj");
	temp->Position(-20, -20, (Game::_window.Height() / 7) * 3);
	temp->Scale(8);
	temp->Rotate(15, glm::vec3(1, 0, 0));
	save.button = temp;
	save.action = MenuResult::Save;

	Game::_loadingScreen.display();
	temp = new Model_Sprite("../../Assets/buttons/option.obj");
	temp->Position(-20, -20, (Game::_window.Height() / 7) * 2);
	temp->Scale(8);
	temp->Rotate(15, glm::vec3(0, 1, 0));
	options.button = temp;
	options.action = MenuResult::Options;

	Game::_loadingScreen.display();
	temp = new Model_Sprite("../../Assets/buttons/quit.obj");
	temp->Position(-20, -20, (Game::_window.Height() / 7) * 1);
	temp->Scale(8);
	temp->Rotate(15, glm::vec3(0, 1, 0));
	back.button = temp;
	back.action = MenuResult::Quit;
	
	Game::_loadingScreen.display();
    this->_menuItems.push_back(paused);
	this->_menuItems.push_back(resume);
	this->_menuItems.push_back(save);
	this->_menuItems.push_back(options);
	this->_menuItems.push_back(back);

	this->_selected = MenuResult::Resume;
}

void PauseMenu::deleteMenu()
{
	for (size_t i = 0; i < this->_menuItems.size(); i++)
		delete this->_menuItems[i].button;
	this->_menuItems.clear();
}

void PauseMenu::moveOnScreen(Shaders & shader, float end)
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
