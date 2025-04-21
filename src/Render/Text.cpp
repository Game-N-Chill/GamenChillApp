
#include "MKTG.hpp"

namespace MKTG::Render
{

Text::Text()
{
    this->_font = nullptr;
    this->_color = SDL_Color{255, 255, 255, 255};
    this->_outline = 0;
    this->_fontSize = 20.0f;
    this->_align = TTF_HORIZONTAL_ALIGN_CENTER;
}

Text::Text(SDL_Point pos, SDL_Point size, float scale) :
    AObject(pos, size, scale)
{
    this->_font = nullptr;
    this->_color = SDL_Color{255, 255, 255, 255};
    this->_outline = 0;
    this->_fontSize = 20.0f;
    this->_align = TTF_HORIZONTAL_ALIGN_CENTER;
}

Text::~Text()
{
    if (this->_font != nullptr) {
        TTF_CloseFont(this->_font);
        this->_font = nullptr;
    }
}


void Text::load(std::string str)
{
    TTF_SetFontDirection(this->_font, TTF_DIRECTION_LTR);
    TTF_SetFontHinting(this->_font, TTF_HINTING_NORMAL);
    TTF_SetFontKerning(this->_font, true);
    TTF_SetFontStyle(this->_font, TTF_STYLE_NORMAL);
    TTF_SetFontWrapAlignment(this->_font, TTF_HORIZONTAL_ALIGN_LEFT);

    TTF_SetFontSize(this->_font,            this->_fontSize);
    TTF_SetFontOutline(this->_font,         this->_outline);

    this->_surface = TTF_RenderText_Solid(this->_font, str.c_str(), 0, this->_color);
    if (this->_surface == nullptr) {
        std::cerr << "ERROR: failed to create text surface " << str << " (" << SDL_GetError() << ")" << std::endl;
        return;
    }

    this->_size.x = static_cast<int>(this->_surface->w);
    this->_size.y = static_cast<int>(this->_surface->h);

    this->_pos.x -= static_cast<int>(this->_size.x * this->_align);
    this->_pos.y -= static_cast<int>(this->_size.y * this->_align);
}


SDL_Color Text::getColor() const
{
    return this->_color;
}

int Text::getOutline() const
{
    return this->_outline;
}

float Text::getFontSize() const
{
    return this->_fontSize;
}

float Text::getAlignement() const
{
    return this->_align;
}

TTF_Font *Text::getFont() const
{
    return this->_font;
}


void Text::setColor(SDL_Color color)
{
    this->_color = color;
}

void Text::setColor(uint8_t r, uint8_t g, uint8_t b)
{
    this->_color = SDL_Color{r, g, b, 255};
}

void Text::setOutline(int outline)
{
    this->_outline = outline;
}

void Text::setFontSize(float size)
{
    this->_fontSize = size;
}

void Text::setAlignement(float align)
{
    this->_align = align;
}

void Text::setFont(std::string path)
{
    if (path.empty())
        return;

    if (this->_font != nullptr) {
        TTF_CloseFont(this->_font);
    }

    this->_font = TTF_OpenFont(path.c_str(), 24.0f);
    if (this->_font == nullptr) {
        std::cerr << "ERROR: failed to load font " << path << " (" << SDL_GetError() << ")" << std::endl;
        return;
    }
}


} // namespace MKTG::Render
