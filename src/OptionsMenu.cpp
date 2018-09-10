#include <Shaders.hpp>
#include "OptionsMenu.hpp"
#include "Game.hpp"

OptionsMenu::OptionsMenu()
{
    loadModels();
}

OptionsMenu::~OptionsMenu()
{}

int OptionsMenu::show(Shaders & shader, Shaders & brightShader)
{
	glm::mat4 projection = Game::_window.Projection();
	while (true)
	{
		Game::_window.clear(0.5f, 0.5f, 0.5f);
		shader.use();
		shader.setMat4("projection", projection);
		shader.setMat4("view", glm::mat4());
		shader.setVec3("light", glm::vec3(30, 30, 30));
		for (size_t i = 0; i < this->_action.size(); i++)
		{
			if (this->_action[i].action != this->_selected)
				this->_action[i].button->Draw(shader);
		}
		brightShader.use();
		brightShader.setMat4("projection", projection);
		brightShader.setMat4("view", glm::mat4());
		brightShader.setVec3("light", glm::vec3(30, 30, 30));
		for (size_t i = 0; i < this->_action.size(); i++)
		{
			if (this->_action[i].action == this->_selected)
				this->_action[i].button->DrawScaledBy(shader, 1.1f);
		}
		if (Game::keyPressed() ==  eKeys::Up)
			this->_selected = ((this->_selected - 1) < 0) ? Options::WindowSize : static_cast<Options>(this->_selected - 1);
		if (Game::keyPressed() == eKeys::Down)
			this->_selected = ((this->_selected + 1) > Options::Back) ? Options::Back : static_cast<Options>(this->_selected + 1);
		if (Game::keyPressed() == eKeys::Select)
			break;
		if (Game::keyPressed() == eKeys::Escape)
		{
			this->_selected = Options::Back;
			break;
		}
		Game::_window.update();
	}
	deleteMenu();
	return static_cast<int>(this->_selected);
}

void OptionsMenu::loadModels()
{   
    this->_selected = Options::WindowSize;

    OptionsAction size;
    size.button = new Model_Sprite("../assets/buttons/screen_resolution.obj");
    this->_action.emplace_back(size);

    OptionsAction mode;
    mode.button = new Model_Sprite("../assets/buttons/start.obj");
    this->_action.emplace_back(mode);

    OptionsAction keys;
    keys.button = new Model_Sprite("../assets/buttons/keybind.obj");
    this->_action.emplace_back(keys);

    OptionsAction sound;
    sound.button = new Model_Sprite("../assets/buttons/sound.obj");
    this->_action.emplace_back(sound);

    OptionsAction volume;
    volume.button = new Model_Sprite("../assets/buttons/start.obj");
    this->_action.emplace_back(volume);

    OptionsAction music;
    music.button = new Model_Sprite("../assets/buttons/start.obj");
    this->_action.emplace_back(music);

    OptionsAction back;
    back.button = new Model_Sprite("../assets/buttons/back.obj");
    this->_action.emplace_back(back);

    for (size_t i = 0; i < this->_action.size(); i++)
    {
        this->_action[i].action = static_cast<Options>(i);
        this->_action[i].button->Position(Game::_window.Width() >> 2, -20.0f, (((Game::_window.Height() >> 3) * (this->_action.size() - i)) - (Game::_window.Height() >> 4)));
        this->_action[i].button->Scale(10);
    }
}

void OptionsMenu::deleteMenu()
{
	for (size_t i = 0; i < this->_action.size(); i++)
		delete this->_action[i].button;
    this->_action.clear();
}