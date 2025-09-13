
// #include "Render/Object.hpp"

// namespace Generator::Render
// {

// AObject::AObject()
// {
//     this->_pos = SDL_Point{0, 0};
//     this->_size = SDL_Point{0, 0};
//     this->_scale = 1.0f;
//     this->_surface = nullptr;
// }

// AObject::AObject(SDL_Point pos, SDL_Point size, float scale)
// {
//     setPosition(pos);
//     setSize(size);
//     setScale(scale);
//     this->_surface = nullptr;
// }

// AObject::~AObject()
// {
//     if (this->_surface != nullptr) {
//         SDL_DestroySurface(this->_surface);
//         this->_surface = nullptr;
//     }
// }



// void AObject::setPosition(int x, int y)
// {
//     this->_pos.x = x;
//     this->_pos.y = y;
// }

// void AObject::setPosition(SDL_Point pos)
// {
//     this->_pos = pos;
// }

// void AObject::setSize(int x, int y)
// {
//     this->_size.x = x;
//     this->_size.y = y;
// }

// void AObject::setSize(SDL_Point size)
// {
//     this->_size = size;
// }

// void AObject::setScale(float scale)
// {
//     this->_scale = scale;
// }


// SDL_Point AObject::getPosition() const
// {
//     return this->_pos;
// }

// SDL_Point AObject::getSize() const
// {
//     return this->_size;
// }

// float AObject::getScale() const
// {
//     return this->_scale;
// }


// SDL_Surface *AObject::getSurface()
// {
//     return this->_surface;
// }


// } // namespace MKTG::Render
