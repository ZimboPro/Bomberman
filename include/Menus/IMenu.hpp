#ifndef IMENU_HPP
#define IMENU_HPP

class Shaders;

class IMenu
{
    public:
        virtual ~IMenu()
        {}

        virtual int show(Shaders & shader, Shaders & brightShader) = 0;
};

#endif