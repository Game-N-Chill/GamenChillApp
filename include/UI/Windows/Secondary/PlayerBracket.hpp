
#pragma once

#include <iostream>
#include <memory>
#include <array>

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>

#include "UI/Tools/Window.hpp"
#include "UI/Windows/Common/Shared.hpp"
#include "Data/Data.hpp"

namespace GNCApp::UI::Windows
{

class PlayerBracket : public Tools::Window
{
    Q_OBJECT

    public:
        PlayerBracket(const QString &title, QWidget *parent);

        QString getNameString() const;

        void onLineEdited();
        void setupInfo(QPushButton *buttonPtr, bool buttonEnabled, QString playerName);

    private:
        QLabel *_label;
        QLineEdit *_line;

        QPushButton *_btnPtr;
};

}
