
#pragma once

#include "Object.hpp"

namespace MKTG::Render
{

class Text : public AObject
{
    public:
        Text();
        Text(SDL_Point pos, SDL_Point size, float scale);
        virtual ~Text();

        void load(std::string path);


        SDL_Color getColor() const;
        int getOutline() const;
        float getFontSize() const;
        float getAlignement() const;
        TTF_Font *getFont() const;

        void setColor(SDL_Color color);
        void setColor(uint8_t r, uint8_t g, uint8_t b);
        void setOutline(int outline);
        void setFontSize(float size);
        void setAlignement(float align);
        void setFont(std::string path);

    private:
        TTF_Font *_font;

        SDL_Color _color;
        int _outline;
        float _fontSize;
        float _align;
};


} // namespace MKTG::Render
