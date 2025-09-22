
#pragma once

#include <QGroupBox>
#include <QFormLayout>
#include <QVBoxLayout>

namespace GNCApp::UI::Tools
{

class GroupBox : public QGroupBox
{
    Q_OBJECT

    public:
        explicit GroupBox(const QString &title, QWidget *parent = nullptr);

        void addWidget(QWidget *widget);

    protected:
        QLayout *_layout;
};

class HGroupBox : public GroupBox
{
    Q_OBJECT

    public:
        explicit HGroupBox(const QString &title, QWidget *parent = nullptr);

        void addLayout(QLayout *layout);
};

class VGroupBox : public GroupBox
{
    Q_OBJECT

    public:
        explicit VGroupBox(const QString &title, QWidget *parent = nullptr);

        void addLayout(QLayout *layout);
};

class FGroupBox : public GroupBox
{
    Q_OBJECT

    public:
        explicit FGroupBox(const QString &title, QWidget *parent = nullptr);

        void addRow(const QString &label, QWidget *widget);
};

}
