
#include "Logic/Render.hpp"
#include "Data/Assets.hpp"
#include <fstream>
#include <filesystem>
#include <QPainterPath>

namespace fs = std::filesystem;
namespace GNCApp::Logic
{

Text::Text(QString fontPath, int fontSize) :
    font(fontPath, fontSize)
{
}

static void loadImages(const json &content, std::map<std::string, Object> &map)
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
        QString path = QString::fromStdString(img[CANVA_INDEX_PATH]);
        Image object;

        if (!path.isEmpty()) {
            object.image.load(path);
        }
        object.pos.setX(img[CANVA_INDEX_POSITION]["x"]);
        object.pos.setY(img[CANVA_INDEX_POSITION]["y"]);
        object.scale = img[CANVA_INDEX_SCALE];

        map[img[CANVA_INDEX_NAME]] = object;
    }
}

static void loadTexts(const json &content, std::map<std::string, Object> &map)
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

    auto assets = Data::Assets::getInstance();
    for (const auto &txt : texts) {
        Text object(assets->getFont(txt[CANVA_INDEX_PATH]), txt[CANVA_INDEX_FONT_SIZE]);

        object.rect.setX(txt[CANVA_INDEX_POSITION]["x"]);
        object.rect.setY(txt[CANVA_INDEX_POSITION]["y"]);
        object.rect.setWidth(txt[CANVA_INDEX_POSITION]["w"]);
        object.rect.setHeight(txt[CANVA_INDEX_POSITION]["h"]);
        object.color.setRed(txt[CANVA_INDEX_COLOR]["r"]);
        object.color.setGreen(txt[CANVA_INDEX_COLOR]["g"]);
        object.color.setBlue(txt[CANVA_INDEX_COLOR]["b"]);
        float alignementValue = txt[CANVA_INDEX_ALIGNEMENT];
        if (alignementValue == 0.0f) {
            object.alignement = Qt::AlignLeft | Qt::AlignVCenter;
        } else if (alignementValue == 0.5f) {
            object.alignement = Qt::AlignCenter;
        } else if (alignementValue == 1.0f) {
            object.alignement = Qt::AlignRight | Qt::AlignVCenter;
        } else {
            object.alignement = Qt::AlignCenter;
        }
        object.outlineAlignement = alignementValue;
        object.outline = txt[CANVA_INDEX_OUTLINE];
        object.outlineColor.setRed(txt[CANVA_INDEX_OUTLINE_COLOR]["r"]);
        object.outlineColor.setGreen(txt[CANVA_INDEX_OUTLINE_COLOR]["g"]);
        object.outlineColor.setBlue(txt[CANVA_INDEX_OUTLINE_COLOR]["b"]);

        map[txt[CANVA_INDEX_NAME]] = object;
    }
}

Canva::Canva(std::string path, int width, int height) :
    _canva(width, height, QImage::Format_ARGB32),
    _painter(&this->_canva)
{
    _painter.setRenderHint(QPainter::Antialiasing);

    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("failed to open file " + path);
    }

    json jsonFile;
    file >> jsonFile;
    file.close();

    this->_order = jsonFile[CANVA_CATEGORY_ORDER].get<std::vector<std::string>>();
    loadImages(jsonFile, this->_objects);
    loadTexts(jsonFile, this->_objects);
}

Object &Canva::getObject(std::string name)
{
    return this->_objects[name];
}

Image &Canva::getImage(std::string name)
{
    return std::get<Image>(getObject(name));
}

Text &Canva::getText(std::string name)
{
    return std::get<Text>(getObject(name));
}


static void drawImage(QPainter &painter, Image object)
{
    QRect rect(
        object.pos.x(),
        object.pos.y(),
        object.image.width() * object.scale,
        object.image.height() * object.scale
    );
    painter.drawImage(rect, object.image);
}

static void drawText(QPainter &painter, Text object)
{

    if (object.outline > 0) {
        QFontMetrics metrics(object.font);
        QSize textSize = metrics.size(Qt::TextSingleLine, object.str);

        QPoint outlinePos(
            object.rect.x() + (object.rect.width() - textSize.width()) * object.outlineAlignement,
            object.rect.y() + object.rect.height() - metrics.descent()
        );

        QPainterPath path;
        path.addText(outlinePos.x(), outlinePos.y(), object.font, object.str);
        painter.strokePath(path, QPen(object.outlineColor, object.outline));
        painter.fillPath(path, QBrush(object.color));
    } else {
        painter.setFont(object.font);
        painter.setPen(object.color);
        painter.drawText(object.rect, object.alignement, object.str);
    }

}

void Canva::draw()
{
    for (auto &name : this->_order) {
        Object obj;

        try {
            obj = this->getObject(name);
        } catch (const std::out_of_range &e) {
            std::cerr << e.what() << std::endl;
            continue;
        }

        std::cout << "-- Drawing " << name << " on the canva" << std::endl;
        try {
            drawImage(this->_painter, std::get<Image>(obj));
            continue;
        } catch (std::bad_variant_access) {}

        try {
            drawText(this->_painter, std::get<Text>(obj));
            continue;
        } catch (std::bad_variant_access) {}

        std::cerr << "ERROR: can't find either image or text for: " << name << std::endl;
    }

    this->_painter.end();
}

bool Canva::save(std::string dirPath, std::string fileName)
{
    if (!fs::is_directory(dirPath)) {
        fs::create_directory(dirPath);
    }
    std::string imagePath = dirPath + '/' + fileName + ".png";
    std::cout << "-- Generating image from canva at " << imagePath << std::endl;
    return this->_canva.save(imagePath.c_str());
}

} // namespace MKTG::Render
