
#pragma once

#include "Object.hpp"

namespace MKTG::Render
{

class Image : public AObject
{
    public:
        Image();
        Image(SDL_Point pos, SDL_Point size, float scale);
        virtual ~Image() = default;

        void load(std::string path);

    private:
};


} // namespace MKTG::Render
