#include "Consumer.h"

Consumer::Consumer(SharedQueue* queue, QObject *parent)
    : QObject(parent), queue(queue)
{
    value = 0;

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Consumer::work);
    isRunning = false;
}

Consumer::~Consumer()
{}

int Consumer::getValue()
{
    return value;
}

void Consumer::start()
{
    if (isRunning) return;
    isRunning = true;

    timer->setInterval(100);
    timer->start();

    emit started();
}

void Consumer::stop()
{
    if (!isRunning) return;
    isRunning = false;

    timer->stop();

    emit stopped();
}

void Consumer::consume(int value)
{
    if (isRunning) {
        this->value = value;
        emit consumed(value);
    }
}

void Consumer::work()
{
    if (!isRunning  || queue == nullptr) return;

    if (!queue->isEmpty()) {
        int val = queue->dequeue();
        value = val;
        emit consumed(val);
    }

}
