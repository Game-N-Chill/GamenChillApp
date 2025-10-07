
#include "UI/Tools/Window.hpp"

namespace GNCApp::UI::Tools
{

Window::Window(const QString &title, QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle(title);

    _layout = new QVBoxLayout(this);
    _btnLayout = new QHBoxLayout;
    _btnLayout->addStretch();
}

void Window::addButton(QPushButton *button)
{
    this->_btnLayout->addWidget(button);
    this->_btnList.push_back(button);
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
