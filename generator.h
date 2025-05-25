#pragma once

#include <QObject>
#include <QTimer>

class Generator : public QObject
{
    Q_OBJECT
public:
    explicit Generator(QObject *parent = nullptr);
    ~Generator();

public slots:
    void start();
    void stop();

signals:
    void produced(int value);

    void started();
    void stopped();

private:
    void work();

    int value;
    QTimer *timer;
    bool isRunning;
};
