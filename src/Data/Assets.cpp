
#include "Data/Assets.hpp"
#include <QStringList>
#include <QDir>

namespace Generator::Data
{

Assets::Assets()
{
    QDir dir(":/fonts");
    QStringList list = dir.entryList(QDir::Files);

    for (auto &it : list) {
        int id = QFontDatabase::addApplicationFont(it);
        if (id == -1) {
            std::cerr << "ERROR: can't load font: " << it.toStdString() << std::endl;
            continue;
        }
        this->_fonts[it] = id;
        std::cout << "add: " << it.toStdString() << std::endl;
    }
}

QString Assets::getFont(QString fontName)
{
    std::map<QString, int>::iterator it = this->_fonts.find(fontName);
    if (it == this->_fonts.end()) {
        std::cerr << "can't find font name: " << fontName.toStdString() << std::endl;
        return "";
    }

    QStringList families = QFontDatabase::applicationFontFamilies(it->second);
    return families[0];
}

} // namespace Assets::Data
