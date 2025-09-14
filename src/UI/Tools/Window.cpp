
#include "UI/Tools/Window.hpp"

namespace GNCApp::UI::Tools
{

Window::Window(const QString &title, QWidget *parent, int buttons) :
    QDialog(parent)
{
    setWindowTitle(title);

    _layout = new QVBoxLayout(this);
    _btnLayout = new QHBoxLayout;
    _btnLayout->addStretch();

    if ((buttons & WINDOW_TOOL_BUTTON_VALIDATE) == WINDOW_TOOL_BUTTON_VALIDATE) {
        _btnValidate = new QPushButton("OK", this);
        connect(_btnValidate, &QPushButton::clicked, this, &QDialog::accept);
        _btnLayout->addWidget(_btnValidate);
    }

    if ((buttons & WINDOW_TOOL_BUTTON_CANCEL) == WINDOW_TOOL_BUTTON_CANCEL) {
        _btnCancel = new QPushButton("Cancel", this);
        connect(_btnCancel, &QPushButton::clicked, this, &QDialog::reject);
        _btnLayout->addWidget(_btnCancel);
    }
}

void Window::operator()()
{
    _layout->addLayout(_btnLayout);
    setLayout(_layout);
    adjustSize();
    setFixedSize(size());

    _ret = exec();
}

bool Window::hasValidate() const
{
    return _ret;
}

}
