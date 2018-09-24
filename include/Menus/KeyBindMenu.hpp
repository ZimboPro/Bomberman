/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KeyBindMenu.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpauwels <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 10:53:11 by cpauwels          #+#    #+#             */
/*   Updated: 2018/09/17 10:53:12 by cpauwels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYBINDMENU_HPP
# define KEYBINDMENU_HPP

#include <Model_Sprite.hpp>
#include <ModelGroup.hpp>
#include "IMenu.hpp"
#include <Model_Texture.hpp>
#include <vector>

class KeyBindMenu : public IMenu
{
    public:
        KeyBindMenu();
        KeyBindMenu(KeyBindMenu const & src);
        virtual ~KeyBindMenu();

        enum Options { WASD, Select, Bomb, Back };

        struct OptionsAction
        {
            Options action;
            Model_Sprite * button;
        };

        virtual int show(Shaders & shader, Shaders & brightShaders);

    private:
        void loadModels();
        void loadOptions();
        void deleteMenu();
        void loadActions(char * path);
        void moveOnScreen(Shaders & shader, float end);
        void setOptionsPositions();
        void setShader(Shaders & shader, glm::mat4 & projection);
        void changeSettings();
        void addModels(int index, int start, int end);
        void loadTexture(char * path);
        void drawSettings(Shaders & shader);
        void drawSelectedSetting(Shaders & shader);
        void drawNotSelectedSetting(Shaders & shader);
        void setGroupPositions(int groupIndex, int heightIndex);
        void showKeyBindMenu();

        std::vector<OptionsAction> _action;
        Options _selected;
        std::vector<Model_Texture *> _options;
        std::vector<ModelGroup *> _groups;
        IAudioProvider * _sound;
};

#endif
