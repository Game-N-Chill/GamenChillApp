
#include "UI/Windows/Common/ProgressBar.hpp"

namespace GNCApp::UI::Windows
{

ProgressBar::ProgressBar(const QString &title, int delay, QWidget *parent) :
    Window(title, parent)
{
    this->_label = new QLabel("progress text");

    this->_progressBar = new QProgressBar(this);
    this->_progressBar->setRange(0, 100);        // set range
    this->_progressBar->setValue(0);             // initial value
    this->_progressBar->setMinimumWidth(500);
    this->_progressBar->setTextVisible(false);   // hide percentage text (optional)

    this->_timer = new QTimer(this);
    connect(this->_timer, &QTimer::timeout, this, &ProgressBar::loop);
    this->_timer->start(delay);

    this->_layout->addWidget(this->_label);
    this->_layout->addWidget(this->_progressBar);
}

static std::pair<std::string, int> getCurrentProgressTask()
{
    auto instance = Logic::ProgressTask::getInstance();
    return std::make_pair(instance->getTaskName(), instance->getTaskValue());
}

void ProgressBar::loop()
{
    auto pair = getCurrentProgressTask();

    std::cout << pair.second << std::endl;
    if (pair.second >= 100) {
        this->close();
    } else {
        this->_label->setText(QString::fromStdString(pair.first));
        this->_progressBar->setValue(pair.second);
    }
}

void ProgressBar::open(const QString &title, std::function<void()> funcLoadTask, std::function<void()> funcLogicExec, int delay, QWidget *parent)
{
    ProgressBar windowProgress("Top 8 Generation", 10, parent);

    Logic::ProgressTask::getInstance()->reset();
    funcLoadTask();

    std::thread threadFunc(funcLogicExec);
    threadFunc.detach();

    windowProgress();
}

}
