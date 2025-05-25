#pragma once

#include "SharedQueue.h"

#include <QObject>
#include <QThread>
#include <QTimer>

class Consumer : public QObject
{
    Q_OBJECT
public:
    explicit Consumer(SharedQueue* queue, QObject *parent = nullptr);
    ~Consumer();

    int getValue();

public slots:
    void start();
    void stop();


    void consume(int value);

signals:
    void consumed(int value);

    void started();
    void stopped();

private:
    void work();

    int value;
    QTimer *timer;
    SharedQueue* queue = nullptr; // Queue refrence
    bool isRunning;
};
