
#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <variant>
#include <QImage>
#include <QPainter>
#include <QPoint>
#include <QColor>
#include <QFont>
#include <QFontDatabase>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

namespace Generator::Logic
{

#define CANVA_SOLO_PATH                     "Assets\\Data\\CanvaSolo.json"
#define CANVA_DUO_PATH                      "Assets\\Data\\CanvaDuo.json"

#define CANVA_CATEGORY_IMAGE                "Images"
#define CANVA_CATEGORY_TEXT                 "Texts"
#define CANVA_CATEGORY_ORDER                "Order"

#define CANVA_INDEX_NAME                    "name"
#define CANVA_INDEX_PATH                    "path"
#define CANVA_INDEX_POSITION                "position"
#define CANVA_INDEX_SCALE                   "scale"
#define CANVA_INDEX_COLOR                   "color"
#define CANVA_INDEX_STRING                  "str"
#define CANVA_INDEX_OUTLINE                 "outline"
#define CANVA_INDEX_OUTLINE_COLOR           "outlineColor"
#define CANVA_INDEX_FONT_SIZE               "fontSize"
#define CANVA_INDEX_ALIGNEMENT              "align"

#define CANVA_DEFAULT_IMAGE_WIDTH           1920
#define CANVA_DEFAULT_IMAGE_HEIGHT          1080

struct Image
{
    QImage image;
    QPoint pos;
    float scale;
};

struct Text
{
    QFont font;
    QString str;
    float size;
    QRect rect;
    QColor color;
    Qt::Alignment alignement;

    int outline;
    QColor outlineColor;
    float outlineAlignement;

    Text(QString fontPath, int fontSize);
};

typedef std::variant<Image, Text> Object;

class Canva
{
    public:
        Canva(std::string path, int width = CANVA_DEFAULT_IMAGE_WIDTH, int height = CANVA_DEFAULT_IMAGE_HEIGHT);
        ~Canva() = default;

        Object &getObject(std::string name);
        Image &getImage(std::string name);
        Text &getText(std::string name);

        void draw();
        bool save(std::string dirPath, std::string fileName);
        std::vector<std::string> getOrder() const;

    private:
        QImage _canva;
        QPainter _painter;

        std::vector<std::string> _order;
        std::map<std::string, Object> _objects;
};

} // namespace MKTG::Render
