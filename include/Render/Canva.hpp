
#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include <map>

#include "Image.hpp"
#include "Text.hpp"

namespace MKTG::Render
{

#define CANVA_PATH                  "Assets\\Data\\Canva.json"

#define CANVA_CATEGORY_IMAGE        "Images"
#define CANVA_CATEGORY_TEXT         "Texts"
#define CANVA_CATEGORY_ORDER        "Order"

#define CANVA_INDEX_NAME            "name"
#define CANVA_INDEX_PATH            "path"
#define CANVA_INDEX_POSITION        "position"
#define CANVA_INDEX_SCALE           "scale"
#define CANVA_INDEX_COLOR           "color"
#define CANVA_INDEX_STRING          "str"
#define CANVA_INDEX_OUTLINE         "outline"
#define CANVA_INDEX_FONT_SIZE       "fontSize"
#define CANVA_INDEX_ALIGNEMENT      "align"

class Canva
{
    public:
        Canva(std::string path);
        ~Canva();

        std::shared_ptr<AObject> get(std::string name);
        std::shared_ptr<Image> getImage(std::string name);
        std::shared_ptr<Text> getText(std::string name);

        void draw(std::string name);
        void save(std::string dirPath, std::string fileName);
        std::vector<std::string> getOrder() const;

    private:
        SDL_Surface *_canva;
        json _json;
        std::map<std::string, std::shared_ptr<AObject>> _objects;
};

} // namespace MKTG::Render
