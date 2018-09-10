//
// Created by Patrick RUSSELL on 2018/08/21.
//

#include <iostream>
#include <Shaders.hpp>
#include "MainMenu.hpp"
#include "Game.hpp"

MainMenu::MainMenu()
{
	loadMenu();
}

MainMenu::~MainMenu()
{}

int MainMenu::show(Shaders & shader, Shaders & brightShader)
{
	moveOnScreen(shader);
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
				this->_menuItems[i].button->DrawScaledBy(shader, 1.1f);
		}
		if (Game::keyPressed() ==  eKeys::Up)
			this->_selected = ((this->_selected - 1) < 0) ? MenuResult::Play : static_cast<MenuResult>(this->_selected - 1);
		if (Game::keyPressed() == eKeys::Down)
			this->_selected = ((this->_selected + 1) > MenuResult::Exit) ? MenuResult::Exit : static_cast<MenuResult>(this->_selected + 1);
		if (Game::keyPressed() == eKeys::Select)
			break;
		if (Game::_window.closed() || Game::keyPressed() == eKeys::Escape)
		{
			this->_selected = MenuResult::Exit;
			break;
		}

		Game::_window.update();
	}
	moveOffScreen(shader);
	deleteMenu();
	return static_cast<int>(this->_selected);
}

void MainMenu::loadMenu()
{	
	MenuItem start;
	MenuItem options;
	MenuItem quit;
	
	Model_Sprite *temp = new Model_Sprite("../assets/buttons/start.obj");
	temp->Position(-20, -20, (Game::_window.Height() << 1) / 3);
	temp->Scale(10);
	start.button = temp;
	start.action = MenuResult::Play;

	temp = new Model_Sprite("../assets/buttons/option.obj");
	temp->Position(-20, -20, (Game::_window.Height() >> 1));
	temp->Scale(10);
	options.button = temp;
	options.action = MenuResult::Settings;

	temp = new Model_Sprite("../assets/buttons/quit.obj");
	temp->Position(-20, -20, (Game::_window.Height()) / 3);
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
	for (size_t i = 0; i < this->_menuItems.size(); i++)
		delete this->_menuItems[i].button;
	this->_menuItems.clear();
}

inline float MoveBy(float start, float end, float weighting)
{
	return (end - start) * weighting;
}

void MainMenu::moveOnScreen(Shaders & shader)
{
	float x = -40.0f;
	glm::mat4 projection = Game::_window.Projection();
	float weighting = 0.05f;
	while (0.05f < (Game::_window.Width() >> 1) - x)
	{
		Game::_window.clear(0.5f, 0.5f, 0.5f);
		shader.use();
		shader.setMat4("projection", projection);
		shader.setMat4("view", glm::mat4());
		shader.setVec3("light", glm::vec3(30, 30, 30));
		for (size_t i = 0; i < this->_menuItems.size(); i++)
		{
			this->_menuItems[i].button->Move(MoveBy(x , (Game::_window.Width() >> 1), weighting), 0);
			this->_menuItems[i].button->Draw(shader);
		}
		x += MoveBy(x , (Game::_window.Width() >> 1), weighting);
		Game::_window.update();
	}
}

void MainMenu::moveOffScreen(Shaders & shader)
{
	float x = (Game::_window.Width() >> 1);
	glm::mat4 projection = Game::_window.Projection();
	float weighting = 0.01f;
	float end = -(Game::_window.Width() >> 1);
	while (x - end > 0.05f)
	{
		Game::_window.clear(0.5f, 0.5f, 0.5f);
		shader.use();
		shader.setMat4("projection", projection);
		shader.setMat4("view", glm::mat4());
		shader.setVec3("light", glm::vec3(30, 30, 30));
		for (size_t i = 0; i < this->_menuItems.size(); i++)
		{
			this->_menuItems[i].button->Move(MoveBy(x , end, weighting), 0);
			this->_menuItems[i].button->Draw(shader);
		}
		x += MoveBy(x , end, weighting);
		Game::_window.update();
	}
}