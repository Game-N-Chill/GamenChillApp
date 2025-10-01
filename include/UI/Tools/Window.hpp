
#pragma once

#include <QWidget>
#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <list>

namespace GNCApp::UI::Tools
{

    #define WINDOW_TOOL_BUTTON_VALIDATE         (1 << 0)
    #define WINDOW_TOOL_BUTTON_CANCEL           (1 << 1)
    #define WINDOW_TOOL_BUTTON_OPEN_DIR         (1 << 2)

class Window : public QDialog
{
    Q_OBJECT

    public:
        Window(const QString &title, QWidget *parent = nullptr);

        void addButton(QPushButton *button);

        void operator()();
        bool hasValidate() const;

        static void callbackOpenDirectory();

    protected:
        QVBoxLayout *_layout;

        QHBoxLayout *_btnLayout;
        std::list<QPushButton *> _btnList;

        QSize _sizeToAdd;

    private:
        QPushButton *createButton(QString title, QString iconPath, int minWidth);

        bool _ret;
};

} // namespace GNCApp::UI
