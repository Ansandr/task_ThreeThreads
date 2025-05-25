#include "Consumer.h"

Consumer::Consumer(QObject *parent)
    : QObject{parent}
{
    value = 0;
    isRunning = false;
}

Consumer::~Consumer()
{}

void Consumer::start()
{
    if (isRunning) return;
    isRunning = true;

    emit started();
}

void Consumer::stop()
{
    if (!isRunning) return;
    isRunning = false;

    emit stopped();
}

void Consumer::consume(int value)
{
    if (isRunning) {
        this->value = value;
        emit consumed(value);
    }
}
