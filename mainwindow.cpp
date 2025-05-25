#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QThread::currentThread()->setObjectName("Main thread");

    // Creating threads
    // generator
    gThread = new QThread();
    gThread->setObjectName("Generator thread");

    generator = new Generator();
    generator->moveToThread(gThread);

    QObject::connect(gThread, &QThread::started, generator, &Generator::start);

    // queue
    qThread = new QThread();
    qThread->setObjectName("Queue thread");

    queue = new SharedQueue();
    queue->moveToThread(qThread);

    // cosumer
    cThread = new QThread();
    cThread->setObjectName("Consumer thread");

    consumer = new Consumer();
    consumer->moveToThread(cThread);

    QObject::connect(cThread, &QThread::started, consumer, &Consumer::start);


    // GENERATOR connections
    // Update list widget
    connect(generator, &Generator::produced, this, [this](int val) {
        ui->listGenerator->clear();
        ui->listGenerator->addItem(QString::number(val));
    });

    // Update label when status change
    connect(generator, &Generator::started, this, [=]() {
        ui->label_status_generator->setText("Running");
    });
    connect(generator, &Generator::stopped, this, [=]() {
        ui->label_status_generator->setText("Stopped");
    });

    // QUEUE connections
    connect(generator, &Generator::produced, queue, &SharedQueue::enqueue);
    connect(queue, &SharedQueue::queueUpdated, this, [=](const QList<int>& items) {
        ui->listQueue->clear();
        for (int val : items)
            ui->listQueue->addItem(QString::number(val));
    });

    // CONSUMER connections
    // coonect queue with consumer
    connect(queue, &SharedQueue::dequeued, consumer, &Consumer::consume);

    // Update list widget
    connect(consumer, &Consumer::consumed, this, [this](int val) {
        ui->listConsumer->clear();
        ui->listConsumer->addItem(QString::number(val));
    });

    // Update label when status change
    connect(consumer, &Consumer::started, this, [=]() {
        ui->label_status_consumer->setText("Running");
    });
    connect(consumer, &Consumer::stopped, this, [=]() {
        ui->label_status_consumer->setText("Stopped");
    });

    // buttons
    connect(ui->btnStartGenerator, &QPushButton::clicked, generator, &Generator::start);
    connect(ui->btnStopGenerator, &QPushButton::clicked, generator, &Generator::stop);
    connect(ui->btnStartConsumer, &QPushButton::clicked, consumer, &Consumer::start);
    connect(ui->btnStopConsumer, &QPushButton::clicked, consumer, &Consumer::stop);

    // starting all threads
    gThread->start();
    qThread->start();
    cThread->start();

}

MainWindow::~MainWindow()
{
    delete ui;
}
