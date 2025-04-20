
#include "MKTG.hpp"

namespace MKTG::Render
{

Image::Image()
{
}

Image::Image(SDL_Point pos, SDL_Point size, float scale) :
    AObject(pos, size, scale)
{
}

void Image::load(std::string path)
{
    if (path.empty())
        return;

    this->_surface = IMG_Load(path.c_str());
    if (this->_surface == nullptr) {
        std::cerr << "ERROR: failed to create image " << path << std::endl;
        return;
    }

    this->_size.x = static_cast<int>(this->_surface->w * this->_scale);
    this->_size.y = static_cast<int>(this->_surface->h * this->_scale);
}

} // namespace MKTG::Render
