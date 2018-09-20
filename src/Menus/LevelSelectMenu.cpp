/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LevelSelectMenu.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpauwels <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 07:30:47 by cpauwels          #+#    #+#             */
/*   Updated: 2018/09/20 07:30:48 by cpauwels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Menus/LevelSelectMenu.hpp"
#include "Game.hpp"
#include <Juicy.hpp>

LevelSelectMenu::LevelSelectMenu()
{
    loadMenu();
}

LevelSelectMenu::LevelSelectMenu(LevelSelectMenu const & src)
{
    *this= src;
}

LevelSelectMenu::~LevelSelectMenu()
{}

int LevelSelectMenu::show(Shaders & shader, Shaders & brightShader)
{
	moveOnScreen(shader, (Game::_window.Width() >> 1));
	glm::mat4 projection = Game::_window.Projection();
	while (true)
	{
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
			this->_selected = ((this->_selected + 1) > MenuResult::Back) ? MenuResult::Random : static_cast<MenuResult>(this->_selected + 1);
		if (Game::keyTyped() == eKeys::Select)
		{
            if (_selected == MenuResult::Back)
                break;
        }
		Game::_window.update();
	}
	moveOnScreen(shader, -20.0f);
	deleteMenu();
	return static_cast<int>(this->_selected);
}

void LevelSelectMenu::loadMenu()
{	
	MenuItem random;
	MenuItem lvl1;
	MenuItem lvl2;
	MenuItem lvl3;
	MenuItem back;

    Game::_loadingScreen.reset();
	Game::_loadingScreen.display();
	Model_Sprite *temp = new Model_Sprite("../../Assets/buttons/random.obj");
	temp->Position(-20, -20, (Game::_window.Height() / 6) * 5);
	temp->Scale(10);
	temp->Rotate(15, glm::vec3(1, 0, 0));
	random.button = temp;
	random.action = MenuResult::Random;

	Game::_loadingScreen.reset();
	Game::_loadingScreen.display();
	temp = new Model_Sprite("../../Assets/buttons/lvl1.1.obj");
	temp->Position(-20, -20, (Game::_window.Height() / 6) * 4);
	temp->Scale(10);
	temp->Rotate(15, glm::vec3(1, 0, 0));
	lvl1.button = temp;
	lvl1.action = MenuResult::lvl1;

	Game::_loadingScreen.display();
	temp = new Model_Sprite("../../Assets/buttons/lvl1.2.obj");
	temp->Position(-20, -20, (Game::_window.Height() / 6) * 3);
	temp->Scale(10);
	temp->Rotate(15, glm::vec3(0, 1, 0));
	lvl2.button = temp;
	lvl2.action = MenuResult::lvl2;

    Game::_loadingScreen.display();
	temp = new Model_Sprite("../../Assets/buttons/lvl1.3.obj");
	temp->Position(-20, -20, (Game::_window.Height() / 6) * 2);
	temp->Scale(10);
	temp->Rotate(15, glm::vec3(0, 1, 0));
	lvl3.button = temp;
	lvl3.action = MenuResult::lvl3;

	Game::_loadingScreen.display();
	temp = new Model_Sprite("../../Assets/buttons/back.obj");
	temp->Position(-20, -20, (Game::_window.Height() / 6));
	temp->Scale(10);
	temp->Rotate(15, glm::vec3(0, 1, 0));
	back.button = temp;
	back.action = MenuResult::Back;
	
	Game::_loadingScreen.display();
	this->_menuItems.push_back(random);
	this->_menuItems.push_back(lvl1);
	this->_menuItems.push_back(lvl2);
	this->_menuItems.push_back(lvl3);
	this->_menuItems.push_back(back);

	this->_selected = MenuResult::Random;
}

void LevelSelectMenu::deleteMenu()
{
	for (size_t i = 0; i < this->_menuItems.size(); i++)
		delete this->_menuItems[i].button;
	this->_menuItems.clear();
}

void LevelSelectMenu::moveOnScreen(Shaders & shader, float end)
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
