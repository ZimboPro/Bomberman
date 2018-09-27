/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KeyBindMenu.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpauwels <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 10:52:56 by cpauwels          #+#    #+#             */
/*   Updated: 2018/09/17 10:52:58 by cpauwels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Shaders.hpp>
#include <Juicy.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Game.hpp"
#include "Menus/KeyBindMenu.hpp"

KeyBindMenu::KeyBindMenu() 
{
	_sound = ServiceLocator::getAudio();
	_sound->setSoundLevel(Game::_settings.volume * 20);
	_sound->stopAllSounds();
	if (Game::_settings.music)
		_sound->playSong("../../Assets/sounds/background_music/background_menu.wav", true);
    loadModels();
}

KeyBindMenu::KeyBindMenu(KeyBindMenu const & src) 
{
    *this = src;
}

KeyBindMenu::~KeyBindMenu()
{}


int KeyBindMenu::show(Shaders & shader, Shaders & brightShader)
{
	glm::mat4 projection = Game::_window.Projection();
	moveOnScreen(shader, (Game::_window.Width() >> 2));
	Options temp;
	while (true)
	{
		temp = this->_selected;
		Game::_window.clear(0.2588f, 0.7961f, 0.8196f);
		setShader(shader, projection);
		for (size_t i = 0; i < this->_action.size(); i++)
		{
			if (this->_action[i].action != this->_selected)
				this->_action[i].button->Draw(shader);
		}
		drawNotSelectedSetting(shader);
		setShader(brightShader, projection);
		for (size_t i = 0; i < this->_action.size(); i++)
		{
			if (this->_action[i].action == this->_selected)
				this->_action[i].button->DrawScaledBy(brightShader, 1.1f);
		}
		drawSelectedSetting(brightShader);
		if (Game::keyTyped() ==  eKeys::Up)
			this->_selected = ((this->_selected - 1) < 0) ? Options::Back : static_cast<Options>(0);
		if (Game::keyTyped() == eKeys::Down)
			this->_selected = ((this->_selected + 1) > Options::Back) ? Options::WASD : static_cast<Options>(3);
		if (Game::keyTyped() == eKeys::Select)
		{
			if (this->_selected == Options::Back)
				break;
			changeSettings();
		}
		if (Game::keyTyped() == eKeys::Escape)
		{
			this->_selected = Options::Back;
			break;
		}
		if (temp != _selected && Game::_settings.sound)
			_sound->playSound("../../Assets/sounds/button_press/select_settings.wav");
		Game::_window.update();
	}
	if (Options::Back == _selected && Game::_settings.sound)
		_sound->playSound("../../Assets/sounds/button_press/exit_button.wav");
	else if (Game::_settings.sound)
		_sound->playSound("../../Assets/sounds/button_press/start_game.wav");
	moveOnScreen(shader, -((Game::_window.Width() >> 1) + 40.0f));
	deleteMenu();
	Game::loadKeys();
	return static_cast<int>(this->_selected);
}

void KeyBindMenu::showKeyBindMenu()
{
	KeyBindMenu menu;

	Shaders brightShader("../assets/shaders/vert/ShadedModelsVert.glsl", "../assets/shaders/frag/ShadedModelsFrag.glsl");
	Shaders shader("../assets/shaders/vert/ShadedModelsVert.glsl", "../assets/shaders/frag/DarkShadedModelsFrag.glsl");
	
	int selection = menu.show(shader, brightShader);
}

void KeyBindMenu::drawSettings(Shaders & shader)
{
	this->_groups[0]->_models[Game::_KeyBind]->Draw(shader);
	this->_groups[1]->_models[0]->Draw(shader);
	this->_groups[2]->_models[0]->Draw(shader);
}

void KeyBindMenu::drawSelectedSetting(Shaders & shader)
{
	if (this->_selected == Options::WASD)
		this->_groups[0]->_models[Game::_KeyBind]->DrawScaledBy(shader, 1.1f);
}

void KeyBindMenu::drawNotSelectedSetting(Shaders & shader)
{
	if (this->_selected != Options::WASD)
		this->_groups[0]->_models[Game::_KeyBind]->Draw(shader);
	if (this->_selected != Options::Select)
		this->_groups[1]->_models[0]->Draw(shader);
	if (this->_selected != Options::Bomb)
		this->_groups[2]->_models[0]->Draw(shader);
}

void KeyBindMenu::changeSettings()
{
	if (Game::_settings.sound)
		_sound->playSound("../../Assets/sounds/button_press/start_game.wav");
	if (this->_selected == Options::WASD)
	{
		Game::_KeyBind = !Game::_KeyBind;
	}
}

void KeyBindMenu::loadActions(char * path)
{
	Game::_loadingScreen.display();
	OptionsAction temp;
	temp.button = new Model_Sprite(path);
	this->_action.emplace_back(temp);
}

void KeyBindMenu::loadModels()
{   
    this->_selected = Options::WASD;
	Game::_loadingScreen.reset();
    loadActions("../../Assets/buttons/wasd.obj");
    loadActions("../../Assets/buttons/select.obj");
    loadActions("../../Assets/buttons/bomb_btn.obj");
    loadActions("../../Assets/buttons/back.obj");
    for (size_t i = 0; i < this->_action.size(); i++)
    {
        this->_action[i].action = static_cast<Options>(i);
        this->_action[i].button->Position(-40.0f, -20.0f, (Game::_window.Height() / 9 ) * (9 - (2 * (i + 1))));
		if (i == 0 || i == 3)
        	this->_action[i].button->Scale(7);
		else
        	this->_action[i].button->Scale(5);
    }
	loadOptions();
}

void KeyBindMenu::loadOptions()
{
	loadTexture("../../Assets/buttons/off.obj");
	loadTexture("../../Assets/buttons/on.obj");
	loadTexture("../../Assets/buttons/enter.obj");
	loadTexture("../../Assets/buttons/space.obj");

	for (int i = 0; i < 3; i++)
		this->_groups.emplace_back(new ModelGroup());

	addModels(0, 0, 1);
	addModels(1, 2, 2);
	addModels(2, 3, 3);

	setOptionsPositions();
}

void KeyBindMenu::loadTexture(char * path)
{
	Game::_loadingScreen.display();
	this->_options.emplace_back(new Model_Texture(path));
}

void KeyBindMenu::addModels(int index, int start, int end)
{
	Game::_loadingScreen.display();
	for (int i = start; i <= end; i++)
		this->_groups[index]->_models.push_back(new Model_Sprite(*this->_options[i]));
}

void KeyBindMenu::setOptionsPositions()
{
	setGroupPositions(0, 0);
	setGroupPositions(1, 1);
	setGroupPositions(2, 2);
}

void KeyBindMenu::setGroupPositions(int groupIndex, int heightIndex)
{
	for (size_t i = 0; i < this->_groups[groupIndex]->_models.size(); i++)
	{
		this->_groups[groupIndex]->_models[i]->Position(-40.0f, -20.0f, (Game::_window.Height() / 9 ) * (9 - (2 * (heightIndex + 1))));
		this->_groups[groupIndex]->_models[i]->Scale(7);
		if (groupIndex == 0)
        	this->_groups[groupIndex]->_models[i]->Scale(7);
		else
        	this->_groups[groupIndex]->_models[i]->Scale(5);
	}
}

void KeyBindMenu::deleteMenu()
{
	for (size_t i = 0; i < this->_action.size(); i++)
		delete this->_action[i].button;
    this->_action.clear();

	for (size_t i = 0; i < this->_groups.size(); i++)
	{
		for (size_t j = 0; j < this->_groups[i]->_models.size(); j++)
			delete this->_groups[i]->_models[j];
		this->_groups[i]->_models.clear();
		delete this->_groups[i];
	}
    this->_groups.clear();

	for (size_t i = 0; i < this->_options.size(); i++)
		delete this->_options[i];
    this->_options.clear();
}

void KeyBindMenu::moveOnScreen(Shaders & shader, float end)
{
	glm::mat4 projection = Game::_window.Projection();
	float weighting = 0.05f;
	glm::vec3 temp(end, this->_action[0].button->GetPosition().y, -60.0f);
	glm::vec3 temp1(end + (Game::_window.Width() >> 1), this->_action[0].button->GetPosition().y, -60.0f);
	while (0.1f < glm::distance(temp, this->_action[0].button->GetPosition()))
	{
		Game::_window.clear(0.2588f, 0.7961f, 0.8196f);
		setShader(shader, projection);
		for (size_t i = 0; i < this->_action.size(); i++)
		{
			temp.y = this->_action[i].button->GetPosition().y;
			Juicy::Tweening(*this->_action[i].button, temp, weighting);
			Juicy::TweeingRotation(*this->_action[i].button, 10.0f, weighting);
			this->_action[i].button->Draw(shader);
		}
		for (size_t i = 0; i < this->_groups.size(); i++)
		{
			for (size_t j = 0; j < this->_groups[i]->_models.size(); j++)
			{
				temp1.y = this->_groups[i]->_models[j]->GetPosition().y;
				Juicy::Tweening(*this->_groups[i]->_models[j], temp1, weighting);
				Juicy::TweeingRotation(*this->_groups[i]->_models[j], -10.0f, weighting);
			}
		}
		temp.y = this->_action[0].button->GetPosition().y;
		drawSettings(shader);
		Game::_window.update();	
	}
}

void KeyBindMenu::setShader(Shaders & shader, glm::mat4 & projection)
{
	shader.use();
	shader.setMat4("projection", projection);
	shader.setMat4("view", glm::mat4());
	shader.setVec3("light", glm::vec3(30, 30, 30));
}