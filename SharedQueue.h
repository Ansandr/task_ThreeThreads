#pragma once

#include <QObject>
#include <QQueue>
#include <QMutex>
#include <QWaitCondition>

class SharedQueue : public QObject
{
    Q_OBJECT
public:
    explicit SharedQueue(QObject *parent = nullptr);

    void enqueue(int number);
    int dequeue();
    bool isEmpty();
    int size();

signals:
    void queueUpdated(QList<int> currentItems); // qqueue can't be transferred through signal
    void enqueued(int number);
    void dequeued(int number);

private:
    QQueue<int> queue;
    QMutex mutex;
    QWaitCondition notEmpty;

    const int MAX_SIZE = 20;
};
