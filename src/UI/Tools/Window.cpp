
#include "UI/Tools/Window.hpp"

namespace Generator::UI::Tools
{

Window::Window(const QString &title, QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle(title);

    _layout = new QVBoxLayout(this);

    _btnValidate = new QPushButton("OK", this);
    _btnCancel = new QPushButton("Cancel", this);

    _btnLayout = new QHBoxLayout;
    _btnLayout->addStretch();
    _btnLayout->addWidget(_btnValidate);
    _btnLayout->addWidget(_btnCancel);

    connect(_btnValidate, &QPushButton::clicked, this, &QDialog::accept);
    connect(_btnCancel, &QPushButton::clicked, this, &QDialog::reject);
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
