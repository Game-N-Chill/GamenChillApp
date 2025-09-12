
#include "Render/Canva.hpp"
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;
namespace Generator::Render
{

static void loadImages(const json &content, std::map<std::string, SharedObject> &map)
{
    json images;
    try {
        images = content.at(CANVA_CATEGORY_IMAGE);
    } catch (const json::type_error &e) {
        std::cerr << e.what() << std::endl;
        return;
    } catch (const json::out_of_range &e) {
        std::cerr << e.what() << std::endl;
        return;
    }

    for (const auto &img : images) {
        std::shared_ptr<Image> object = std::make_shared<Image>();

        object->setPosition(
            img[CANVA_INDEX_POSITION]["x"],
            img[CANVA_INDEX_POSITION]["y"]
        );
        object->setScale(img[CANVA_INDEX_SCALE]);
        object->load(img[CANVA_INDEX_PATH]);

        map[img[CANVA_INDEX_NAME]] = object;
    }
}

static void loadTexts(const json &content, std::map<std::string, SharedObject> &map)
{
    json texts;
    try {
        texts = content.at(CANVA_CATEGORY_TEXT);
    } catch (const json::type_error &e) {
        std::cerr << e.what() << std::endl;
        return;
    } catch (const json::out_of_range &e) {
        std::cerr << e.what() << std::endl;
        return;
    }

    for (const auto &txt : texts) {
        std::shared_ptr<Text> object = std::make_shared<Text>();

        object->setPosition(
            txt[CANVA_INDEX_POSITION]["x"],
            txt[CANVA_INDEX_POSITION]["y"]
        );
        object->setColor(
            txt[CANVA_INDEX_COLOR]["r"],
            txt[CANVA_INDEX_COLOR]["g"],
            txt[CANVA_INDEX_COLOR]["b"]
        );
        object->setOutline(txt[CANVA_INDEX_OUTLINE]);
        object->setFontSize(txt[CANVA_INDEX_FONT_SIZE]);
        object->setAlignement(txt[CANVA_INDEX_ALIGNEMENT]);
        object->setFont(txt[CANVA_INDEX_PATH]);

        map[txt[CANVA_INDEX_NAME]] = object;
    }
}

Canva::Canva(std::string path, int width, int height)
{
    this->_canva = SDL_CreateSurface(width, height, SDL_PIXELFORMAT_RGBA32);
    if (this->_canva == nullptr) {
        throw std::runtime_error("failed to create canva");
    }

    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("failed to open file " + path);
    }

    file >> this->_json;
    file.close();

    loadImages(this->_json, this->_objects);
    loadTexts(this->_json, this->_objects);
}

Canva::~Canva()
{
    if (this->_canva != nullptr) {
        SDL_DestroySurface(this->_canva);
        this->_canva = nullptr;
    }
}

std::shared_ptr<AObject> Canva::get(std::string name)
{
    auto it = this->_objects.find(name);
    if (it == this->_objects.end()) {
        std::cerr << "can't find image " << name << std::endl;
        return nullptr;
    }
    return it->second;
}

std::shared_ptr<Image> Canva::getImage(std::string name)
{
    auto obj = get(name);
    if (obj == nullptr)
        return nullptr;
    return std::dynamic_pointer_cast<Image>(obj);
}

std::shared_ptr<Text> Canva::getText(std::string name)
{
    auto obj = get(name);
    if (obj == nullptr)
        return nullptr;
    return std::dynamic_pointer_cast<Text>(obj);
}

void Canva::draw(std::string name)
{
    auto obj = this->get(name);
    if (obj == nullptr) {
        std::cerr << "-- Drawing: Warning: can't find object: " << name << std::endl;
        return;
    }

    std::cout << "-- Drawing " << name << " on the canva" << std::endl;
    SDL_Rect dst = {obj->getPosition().x, obj->getPosition().y, obj->getSize().x, obj->getSize().y};
    SDL_BlitSurfaceScaled(obj->getSurface(), nullptr, this->_canva, &dst, SDL_SCALEMODE_LINEAR);
}

void Canva::save(std::string dirPath, std::string fileName)
{
    if (!fs::is_directory(dirPath)) {
        fs::create_directory(dirPath);
    }
    std::string imagePath = dirPath + '\\' + fileName + ".png";
    std::cout << "-- Generating image from canva at " << imagePath << std::endl;
    IMG_SavePNG(this->_canva, imagePath.c_str());
}

std::vector<std::string> Canva::getOrder() const
{
    return this->_json[CANVA_CATEGORY_ORDER].get<std::vector<std::string>>();
}

} // namespace MKTG::Render
