#include <LoadingScreen.hpp>

LoadingScreen::LoadingScreen()
{
    this->_shader = new Shaders("../assets/shaders/vert/ShadedModelsVert.glsl", "../assets/shaders/frag/ShadedModelsFrag.glsl");
    loadModels();
}

LoadingScreen::~LoadingScreen()
{
    for (size_t i = 0; i < this->_models.size(); i++)
        delete this->_models[i];
    this->_models.clear();
    delete this->_shader;
}

void LoadingScreen::display()
{
    this->_models[this->_model]->Draw(*this->_shader);
    this->_model = (this->_model + 1) % this->_models.size();
}

void LoadingScreen::loadModels()
{
    this->_models.emplace_back(new Model_Sprite("../assets/buttons/Loading/loading_1.obj"));
    this->_models.emplace_back(new Model_Sprite("../assets/buttons/Loading/loading_2.obj"));
    this->_models.emplace_back(new Model_Sprite("../assets/buttons/Loading/loading_3.obj"));
    this->_models.emplace_back(new Model_Sprite("../assets/buttons/Loading/loading_4.obj"));
    this->_models.emplace_back(new Model_Sprite("../assets/buttons/Loading/loading_5.obj"));
    this->_models.emplace_back(new Model_Sprite("../assets/buttons/Loading/loading_6.obj"));
    this->_models.emplace_back(new Model_Sprite("../assets/buttons/Loading/loading_7.obj"));
    this->_models.emplace_back(new Model_Sprite("../assets/buttons/Loading/loading_8.obj"));
}