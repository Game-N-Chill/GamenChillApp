
#include "Data/Assets.hpp"
#include <QStringList>
#include <QDir>

namespace GNCApp::Data
{

Assets::Assets()
{
    for (const auto &entry : std::filesystem::recursive_directory_iterator(PATH_ASSETS_FONTS)) {
        if (entry.is_regular_file()) {
            std::string path = entry.path().string();
            std::string name = path.substr(path.find_last_of('/') + 1);

            std::cout << name << std::endl;

            int id = QFontDatabase::addApplicationFont(QString::fromStdString(path));
            if (id == -1) {
                std::cerr << "ERROR: can't load font: " << path << std::endl;
                continue;
            }
            this->_fonts[QString::fromStdString(name)] = id;
        }
    }
}

QString Assets::getFont(std::string fontName)
{
    std::map<QString, int>::iterator it = this->_fonts.find(fontName.c_str());
    if (it == this->_fonts.end()) {
        std::cerr << "can't find font name: " << fontName << std::endl;
        return "";
    }

    QStringList families = QFontDatabase::applicationFontFamilies(it->second);
    return families[0];
}

} // namespace Assets::Data
