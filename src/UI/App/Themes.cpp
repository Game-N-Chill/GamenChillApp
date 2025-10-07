
#include "UI/App.hpp"
#include <QFile>

namespace GNCApp::UI
{

void setAppTheme(const char *path)
{
    setAppTheme(QString(path));
}

void setAppTheme(std::string path)
{
    setAppTheme(QString::fromStdString(path));
}

void setAppTheme(QString path)
{
    QFile file(path);

    if (file.open(QFile::ReadOnly)) {
        QString styleSheet = QString::fromUtf8(file.readAll());
        qApp->setStyleSheet(styleSheet);
    }
}

} // namespace name
