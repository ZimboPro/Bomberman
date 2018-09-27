#include <Shaders.hpp>
#include <Juicy.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Menus/OptionsMenu.hpp"
#include "Game.hpp"
#include "Menus/KeyBindMenu.hpp"

OptionsMenu::OptionsMenu()
{
	_sound = ServiceLocator::getAudio();
	_sound->setSoundLevel(Game::_settings.volume * 20);
	_sound->stopAllSounds();
	if (Game::_settings.music)
		_sound->playSong("../../Assets/sounds/background_music/background_menu.wav", true);
    loadModels();
}

OptionsMenu::~OptionsMenu()
{}

int OptionsMenu::show(Shaders & shader, Shaders & brightShader)
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
			this->_selected = ((this->_selected - 1) < 0) ? Options::Back : static_cast<Options>(this->_selected - 1);
		if (Game::keyTyped() == eKeys::Down)
			this->_selected = ((this->_selected + 1) > Options::Back) ? Options::WindowSize : static_cast<Options>(this->_selected + 1);
		if (Game::keyTyped() == eKeys::Select)
		{
			if (this->_selected == Options::Keys) 
			{
				showKeyBindMenu();
			}				
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
	Game::loadSettings();
	return static_cast<int>(this->_selected);
}

void OptionsMenu::showKeyBindMenu()
{
	KeyBindMenu menu;

	Shaders brightShader("../assets/shaders/vert/ShadedModelsVert.glsl", "../assets/shaders/frag/ShadedModelsFrag.glsl");
	Shaders shader("../assets/shaders/vert/ShadedModelsVert.glsl", "../assets/shaders/frag/DarkShadedModelsFrag.glsl");
	
	int selection = menu.show(shader, brightShader);
}

void OptionsMenu::drawSettings(Shaders & shader)
{
	this->_groups[0]->_models[Game::_settings.size]->Draw(shader);
	this->_groups[1]->_models[Game::_settings.fullscreen]->Draw(shader);
	this->_groups[2]->_models[Game::_settings.sound]->Draw(shader);
	this->_groups[3]->_models[Game::_settings.music]->Draw(shader);
	this->_groups[4]->_models[Game::_settings.volume]->Draw(shader);
}

void OptionsMenu::drawSelectedSetting(Shaders & shader)
{
	if (this->_selected == Options::WindowSize)
		this->_groups[0]->_models[Game::_settings.size]->DrawScaledBy(shader, 1.1f);
	if (this->_selected == Options::WindowMode)
		this->_groups[1]->_models[Game::_settings.fullscreen]->DrawScaledBy(shader, 1.1f);
	if (this->_selected == Options::Sound)
		this->_groups[2]->_models[Game::_settings.sound]->DrawScaledBy(shader, 1.1f);
	if (this->_selected == Options::Music)
		this->_groups[3]->_models[Game::_settings.music]->DrawScaledBy(shader, 1.1f);
	if (this->_selected == Options::Volume)
		this->_groups[4]->_models[Game::_settings.volume]->DrawScaledBy(shader, 1.1f);
}

void OptionsMenu::drawNotSelectedSetting(Shaders & shader)
{
	if (this->_selected != Options::WindowSize)
		this->_groups[0]->_models[Game::_settings.size]->Draw(shader);
	if (this->_selected != Options::WindowMode)
		this->_groups[1]->_models[Game::_settings.fullscreen]->Draw(shader);
	if (this->_selected != Options::Sound)
		this->_groups[2]->_models[Game::_settings.sound]->Draw(shader);
	if (this->_selected != Options::Music)
		this->_groups[3]->_models[Game::_settings.music]->Draw(shader);
	if (this->_selected != Options::Volume)
		this->_groups[4]->_models[Game::_settings.volume]->Draw(shader);
}

void OptionsMenu::changeSettings()
{
	if (Game::_settings.sound)
		_sound->playSound("../../Assets/sounds/button_press/start_game.wav");
	if (this->_selected == Options::WindowSize)
		Game::_settings.size = static_cast<eScreen>((Game::_settings.size + 1) % (eScreen::s1024 + 1));
	else if (this->_selected == Options::WindowMode)
		Game::_settings.fullscreen = (Game::_settings.fullscreen + 1) % 2;
	else if (this->_selected == Options::Sound)
		Game::_settings.sound = (Game::_settings.sound + 1) % 2;
	else if (this->_selected == Options::Music)
		Game::_settings.music = (Game::_settings.music + 1) % 2;
	else if (this->_selected == Options::Volume)
		Game::_settings.volume = static_cast<eVolume>((Game::_settings.volume + 1) % (eVolume::v100 + 1));
}

void OptionsMenu::loadActions(char * path)
{
	Game::_loadingScreen.display();
	OptionsAction temp;
	temp.button = new Model_Sprite(path);
	this->_action.emplace_back(temp);
}

void OptionsMenu::loadModels()
{   
    this->_selected = Options::WindowSize;
	Game::_loadingScreen.reset();
    loadActions("../../Assets/buttons/window_size.obj");
    loadActions("../../Assets/buttons/fullscreen.obj");
    loadActions("../../Assets/buttons/keybind.obj");
    loadActions("../../Assets/buttons/sound.obj");
    loadActions("../../Assets/buttons/volume.obj");
    loadActions("../../Assets/buttons/music.obj");
    loadActions("../../Assets/buttons/back_options.obj");
    for (size_t i = 0; i < this->_action.size(); i++)
    {
        this->_action[i].action = static_cast<Options>(i);
        this->_action[i].button->Position(-(Game::_window.Height() >> 2) - 40.0f, -20.0f, (((Game::_window.Height() >> 3) * (this->_action.size() - i)) - (Game::_window.Height() >> 4)));
        this->_action[i].button->Scale(7);
    }
	loadOptions();
}

void OptionsMenu::loadOptions()
{
	loadTexture("../../Assets/buttons/1920x1080.obj");
	loadTexture("../../Assets/buttons/1080x720.obj");
	loadTexture("../../Assets/buttons/1024x768.obj");
	loadTexture("../../Assets/buttons/off.obj");
	loadTexture("../../Assets/buttons/on.obj");
	loadTexture("../../Assets/options_menu/volume_0.obj");
	loadTexture("../../Assets/options_menu/volume_1.obj");
	loadTexture("../../Assets/options_menu/volume_2.obj");
	loadTexture("../../Assets/options_menu/volume_3.obj");
	loadTexture("../../Assets/options_menu/volume_4.obj");
	loadTexture("../../Assets/options_menu/volume_5.obj");
	

	for (int i = 0; i < 5; i++)
		this->_groups.emplace_back(new ModelGroup());

	addModels(0, 0, 2);
	addModels(1, 3, 4);
	addModels(2, 3, 4);
	addModels(3, 3, 4);
	addModels(4, 5, 10);

	setOptionsPositions();
}

void OptionsMenu::loadTexture(char * path)
{
	Game::_loadingScreen.display();
	this->_options.emplace_back(new Model_Texture(path));
}

void OptionsMenu::addModels(int index, int start, int end)
{
	Game::_loadingScreen.display();
	for (int i = start; i <= end; i++)
		this->_groups[index]->_models.push_back(new Model_Sprite(*this->_options[i]));
}

void OptionsMenu::setOptionsPositions()
{
	setGroupPositions(0, 0);
	setGroupPositions(1, 1);
	setGroupPositions(2, 3);
	setGroupPositions(3, 5);
	setGroupPositions(4, 4);
}

void OptionsMenu::setGroupPositions(int groupIndex, int heightIndex)
{
	for (size_t i = 0; i < this->_groups[groupIndex]->_models.size(); i++)
	{
		this->_groups[groupIndex]->_models[i]->Position(-40.0f, -20.0f, (((Game::_window.Height() >> 3) * (this->_action.size() - heightIndex)) - (Game::_window.Height() >> 4)));
		this->_groups[groupIndex]->_models[i]->Scale(7);
	}
}

void OptionsMenu::deleteMenu()
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

void OptionsMenu::moveOnScreen(Shaders & shader, float end)
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

void OptionsMenu::setShader(Shaders & shader, glm::mat4 & projection)
{
	shader.use();
	shader.setMat4("projection", projection);
	shader.setMat4("view", glm::mat4());
	shader.setVec3("light", glm::vec3(30, 30, 30));
}