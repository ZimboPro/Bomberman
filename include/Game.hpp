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
#include "Menus/IMenu.hpp"
#include "eScreen.hpp"
#include "eVolume.hpp"
#include "Map.hpp"
#include "GameInterface.hpp"

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
        static void loadSettings();
        static Window _window;
        static LoadingScreen _loadingScreen;
        static eKeys keyPressed();
        static eKeys keyTyped();
        static Camera _camera;
        static Settings _settings;
        static bool _KeyBind;
        static GameInterface _interface;

        static void save();
        static void load();

    private:
        static bool isExiting();
        static void gameLoop();
        static void showSplashScreen();
        static void showMenu();
        static void showPauseMenu();
        static void showOptions();
        static void showStartGameMenu();
        static void playGame();
        static void showCredits();

        enum eGameState { Uninitialized, ShowingSplash, Paused,
                ShowingMenu, ShowingOptions,ShowingStartGameMenu,
                Playing, Exiting };

        static eGameState _gameState;
        static int _keyPress;
        static std::map<eKeys, int> _keyConfiguration;
        static std::vector<std::vector<char> >  _savedMap;
};

#endif //BOMBERMAN_GAME_HPP
