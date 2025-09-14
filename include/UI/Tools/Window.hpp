
#pragma once

#include <QWidget>
#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

namespace GNCApp::UI::Tools
{

    #define WINDOW_TOOL_BUTTON_VALIDATE         (1 << 0)
    #define WINDOW_TOOL_BUTTON_CANCEL           (1 << 1)

class Window : public QDialog
{
    Q_OBJECT

    public:
        Window(const QString &title, QWidget *parent = nullptr, int buttons = WINDOW_TOOL_BUTTON_VALIDATE | WINDOW_TOOL_BUTTON_CANCEL);

        void operator()();
        bool hasValidate() const;

    protected:
        QVBoxLayout *_layout;

        QHBoxLayout *_btnLayout;
        QPushButton *_btnValidate;
        QPushButton *_btnCancel;

        QSize _sizeToAdd;

    private:
        bool _ret;
};

} // namespace GNCApp::UI
