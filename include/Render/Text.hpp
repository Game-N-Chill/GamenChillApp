
#pragma once

#include "Object.hpp"

namespace MKTG::Render
{

class Text : public AObject
{
    public:
        Text();
        Text(SDL_Point pos, SDL_Point size, float scale);
        virtual ~Text() = default;

        void load(std::string path);

    private:
};


} // namespace MKTG::Render
