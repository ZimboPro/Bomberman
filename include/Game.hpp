//
// Created by Patrick RUSSELL on 2018/08/17.
//

#ifndef BOMBERMAN_GAME_HPP
#define BOMBERMAN_GAME_HPP

#include <Window.hpp>
#include <map>
#include "GameObjectManager.hpp"
#include "Camera.hpp"
#include "eKeys.hpp"
#include "LoadingScreen.hpp"
#include "Menus/ IMenu.hpp"
#include "eScreen.hpp"
#include "eVolume.hpp"

struct Settings
{
    eScreen size;
    bool fullscreen;
    bool sound;
    eVolume volume;
    bool music;
};

class Game
{
    public:
        Game();
        Game(Game const & src);
        ~Game();
        static void start();
        static int getKeyConfigured(eKeys key);
        static bool setKeyConfigured(eKeys key, int keycode);
        static void loadKeys();
        static Window _window;
        static LoadingScreen _loadingScreen;
        static eKeys keyPressed();
        static eKeys keyTyped();
        static Camera _camera;
        static Settings _settings;
        static bool _KeyBind;

    private:
        static bool isExiting();
        static void gameLoop();
        static void showSplashScreen();
        static void showMenu();
        static void showOptions();
        static void showStartGameMenu();
        static void playGame();

        enum eGameState { Uninitialized, ShowingSplash, Paused,
                ShowingMenu, ShowingOptions, Playing, Exiting };

        static eGameState _gameState;
        static int _keyPress;
        static std::map<eKeys, int> _keyConfiguration;
};

#endif //BOMBERMAN_GAME_HPP
