#pragma once

#include "Consumer.h"
#include "Generator.h"
#include "SharedQueue.h"

#include <QMainWindow>
#include <QApplication>
#include <QThread>
#include <QObject>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QThread* gThread;
    Generator* generator;

    QThread* qThread;
    SharedQueue* queue;

    QThread* cThread;
    Consumer* consumer;

};
