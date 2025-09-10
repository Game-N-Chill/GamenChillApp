
#pragma once

#include <QWidget>
#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

namespace Generator::UI::Tools
{

class Window : public QDialog
{
    Q_OBJECT

    public:
        Window(const QString &title, QWidget *parent = nullptr);

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

} // namespace Generator::UI
