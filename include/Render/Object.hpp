
// #pragma once

// #include <iostream>
// #include <SDL3/SDL.h>

// namespace Generator::Render
// {

// class IObject
// {
//     public:
//         virtual ~IObject() = default;

//         virtual void setPosition(float x, float y) = 0;
//         virtual void setPosition(SDL_Point pos) = 0;
//         virtual void setSize(float x, float y) = 0;
//         virtual void setSize(SDL_Point size) = 0;
//         virtual void setScale(float scale) = 0;

//         virtual SDL_Point getPosition() const = 0;
//         virtual SDL_Point getSize() const = 0;
//         virtual float getScale() const = 0;

//         virtual SDL_Surface *getSurface() = 0;

//         virtual void load(std::string path) = 0;
// };

// class AObject
// {
//     public:
//         AObject();
//         AObject(SDL_Point pos, SDL_Point size, float scale);
//         virtual ~AObject();

//         void setPosition(int x, int y);
//         void setPosition(SDL_Point pos);
//         void setSize(int x, int y);
//         void setSize(SDL_Point size);
//         void setScale(float scale);

//         SDL_Point getPosition() const;
//         SDL_Point getSize() const;
//         float getScale() const;

//         SDL_Surface *getSurface();

//         void load(std::string path);

//     protected:
//         SDL_Point _pos;
//         SDL_Point _size;
//         float _scale;

//         SDL_Surface *_surface;
// };

// typedef std::shared_ptr<AObject>    SharedObject;

// } // namespace MKTG::Render
