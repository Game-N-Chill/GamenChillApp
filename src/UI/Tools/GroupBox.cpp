
#include "UI/Tools/GroupBox.hpp"

namespace GNCApp::UI::Tools
{

GroupBox::GroupBox(const QString &title, QWidget *parent) :
    QGroupBox(title, parent)
{
}

void GroupBox::addWidget(QWidget *widget)
{
    this->_layout->addWidget(widget);
}


HGroupBox::HGroupBox(const QString &title, QWidget *parent) :
    GroupBox(title, parent)
{
    this->_layout = new QHBoxLayout(this);
}

void HGroupBox::addLayout(QLayout *layout)
{
    dynamic_cast<QHBoxLayout *>(this->_layout)->addLayout(layout);
}

VGroupBox::VGroupBox(const QString &title, QWidget *parent) :
    GroupBox(title, parent)
{
    this->_layout = new QVBoxLayout(this);
}

void VGroupBox::addLayout(QLayout *layout)
{
    dynamic_cast<QVBoxLayout *>(this->_layout)->addLayout(layout);
}

FGroupBox::FGroupBox(const QString &title, QWidget *parent) :
    GroupBox(title, parent)
{
    this->_layout = new QFormLayout(this);
}

void FGroupBox::addRow(const QString &label, QWidget *widget)
{
    dynamic_cast<QFormLayout *>(this->_layout)->addRow(label, widget);
}

}
