
#pragma once

#include <QWidget>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QToolButton>

namespace GNCApp::UI::Tools
{

class Browser : public QWidget
{
    Q_OBJECT

    public:
        Browser(QWidget *parent = nullptr, QWidget *additionalWidget = nullptr);

        QLineEdit *getLineEdit();

    protected:
        QLineEdit *_lineEdit;
        QToolButton *_toolBtn;
};

class FileBrowser : public Browser
{
    Q_OBJECT

    public:
        FileBrowser(QWidget *parent = nullptr, QWidget *additionalWidget = nullptr);

    private slots:
        void onClicked();
};

class DirBrowser : public Browser
{
    Q_OBJECT

    public:
        DirBrowser(QWidget *parent = nullptr, QWidget *additionalWidget = nullptr);

    private slots:
        void onClicked();
};

} // namespace GNCApp::UI
