#include "LoadingScreen.hpp"
#include "Game.hpp"

LoadingScreen::LoadingScreen()
{
    this->_shader = new Shaders("../assets/shaders/vert/ShadedModelsVert.glsl", "../assets/shaders/frag/ShadedModelsFrag.glsl");
    this->_model = 0;
    this->_light = glm::vec3(30);
    // loadModels();
}

LoadingScreen::LoadingScreen(LoadingScreen const & src)
{
    *this = src;
}

LoadingScreen::~LoadingScreen()
{
    for (size_t i = 0; i < this->_models.size(); i++)
        delete this->_models[i];
    this->_models.clear();
    delete this->_shader;
}

void LoadingScreen::reset()
{
    this->_model = 0;
    for (size_t i = 0; i < this->_models.size(); i++)
    {
        this->_models[i]->Reset();
        this->_models[i]->Position((Game::_window.Width() >> 1), -20.0f, (Game::_window.Height() >> 1));
        this->_models[i]->Scale(10);
    }
}

void LoadingScreen::display()
{
    this->_proj = Game::_window.Projection();
    Game::_window.clear();
    this->_shader->use();
    this->_shader->setMat4("projection", this->_proj);
	this->_shader->setMat4("view", this->_view);
	this->_shader->setVec3("light", this->_light);
    this->_models[this->_model]->Draw(*this->_shader);
    this->_model = (this->_model + 1) % this->_models.size();
    Game::_window.update();
}

void LoadingScreen::loadModels()
{
    this->_models.reserve(8);
    this->_models.push_back(new Model_Sprite("../../Assets/buttons/Loading/loading_1.obj"));
    this->_models.push_back(new Model_Sprite("../../Assets/buttons/Loading/loading_2.obj"));
    this->_models.push_back(new Model_Sprite("../../Assets/buttons/Loading/loading_3.obj"));
    this->_models.push_back(new Model_Sprite("../../Assets/buttons/Loading/loading_4.obj"));
    this->_models.push_back(new Model_Sprite("../../Assets/buttons/Loading/loading_5.obj"));
    this->_models.push_back(new Model_Sprite("../../Assets/buttons/Loading/loading_6.obj"));
    this->_models.push_back(new Model_Sprite("../../Assets/buttons/Loading/loading_7.obj"));
    this->_models.push_back(new Model_Sprite("../../Assets/buttons/Loading/loading_8.obj"));
}