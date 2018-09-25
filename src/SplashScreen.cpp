//
// Created by Patrick RUSSELL on 2018/08/21.
//

#include <Shaders.hpp>
#include <SpriteRender.hpp>
#include <TextureImages.hpp>
#include "SplashScreen.hpp"
#include "Game.hpp"
#include <chrono>
#include <thread>
#include <string>

SplashScreen::SplashScreen()
{}

SplashScreen::SplashScreen(SplashScreen const & src)
{
	*this = src;
}

SplashScreen::~SplashScreen()
{}

void SplashScreen::show(Shaders & shader, std::string file, int number)
{
	this->_fps = 13.0f;
    this->_timePerFPS = 1.0f / this->_fps;
    this->_time = 0.0f;
	float currentTime;
	SpriteRender render(shader);
	std::string jpg(".jpg");
	glm::vec2 pos(0, 0);
	glm::vec2 size(Game::_window.Width(), Game::_window.Height());
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(Game::_window.Width()), 0.0f, static_cast<GLfloat>(Game::_window.Height()));
	// float elapsed = glfwGetTime();
	// int fps = 0;
	TextureImages texture;
	for (int i = 1; i < number; i++)
	{
		texture.Load(file + std::to_string(i) + jpg);
		currentTime = glfwGetTime();
		if (currentTime - this->_time < this->_timePerFPS)
			std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<signed int>((currentTime - this->_time) * 1000)));

		Game::_window.clear();
		shader.use();
        shader.setMat4Ptr("projection", projection);
		render.DrawSprite(texture, pos, size);
		Game::_window.update();
		this->_time = currentTime;
	}
}
