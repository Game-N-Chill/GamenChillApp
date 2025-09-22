
#include "UI/Tools/Browser.hpp"
#include <QFileDialog>

namespace GNCApp::UI::Tools
{

Browser::Browser(QWidget *parent, QWidget *additionalWidget) :
    QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);

    _lineEdit = new QLineEdit(this);
    _toolBtn = new QToolButton(this);
    _toolBtn->setText("...");

    layout->addWidget(_lineEdit);
    layout->addWidget(_toolBtn);
    if (additionalWidget != nullptr) {
        layout->addWidget(additionalWidget);
    }
}

QLineEdit *Browser::getLineEdit()
{
    return _lineEdit;
}

FileBrowser::FileBrowser(QWidget *parent, QWidget *additionalWidget) :
    Browser(parent, additionalWidget)
{
    connect(_toolBtn, &QToolButton::clicked, this, &FileBrowser::onClicked);
}

void FileBrowser::onClicked()
{
    QString file = QFileDialog::getOpenFileName(this, "Choose File");
    if (!file.isEmpty())
        _lineEdit->setText(file);
}

DirBrowser::DirBrowser(QWidget *parent, QWidget *additionalWidget) :
    Browser(parent, additionalWidget)
{
    connect(_toolBtn, &QToolButton::clicked, this, &DirBrowser::onClicked);
}

void DirBrowser::onClicked()
{
    QString file = QFileDialog::getExistingDirectory(this, "Choose Directory");
    if (!file.isEmpty())
        _lineEdit->setText(file);
}

} // namespace GNCApp::UI
