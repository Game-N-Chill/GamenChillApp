
#include "MKTG.hpp"

namespace MKTG::Render
{

Text::Text()
{
}

Text::Text(SDL_Point pos, SDL_Point size, float scale) :
    AObject(pos, size, scale)
{
}

void Text::load(std::string path)
{

}

} // namespace MKTG::Render
