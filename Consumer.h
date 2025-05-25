#pragma once

#include <QObject>
#include <QThread>

class Consumer : public QObject
{
    Q_OBJECT
public:
    explicit Consumer(QObject *parent = nullptr);
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
    int value;
    bool isRunning;
};
