#include "Generator.h"

Generator::Generator(QObject *parent)
    : QObject{parent}
{
    value = 0;
    isRunning = false;

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Generator::work);
}

Generator::~Generator()
{}

void Generator::start()
{
    if (isRunning) return;
    isRunning = true;

    timer->setInterval(100);
    timer->start();
    emit started();
}

void Generator::stop()
{
    if (!isRunning) return;
    isRunning = false;
    timer->stop();
    emit stopped();
}

void Generator::work()
{
    if (!isRunning) return;
    value++;
    emit produced(value);
}
