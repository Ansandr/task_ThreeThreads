#include "SharedQueue.h"

SharedQueue::SharedQueue(QObject *parent)
    : QObject{parent}
{}

// Adds value to the tail of the queue.
void SharedQueue::enqueue(int number)
{
    QMutexLocker locker(&mutex);

    if (queue.size() >= MAX_SIZE) {
        int num = queue.dequeue();
        emit dequeued(num);
    }

    queue.enqueue(number);
    emit queueUpdated(queue.toList());
    emit enqueued(number);
    notEmpty.wakeOne(); // Wake consumer
}

 // Removes the head item in the queue and returns it.
int SharedQueue::dequeue()
{
    QMutexLocker locker(&mutex);

    while (queue.isEmpty()) {
        notEmpty.wait(&mutex); // wait until the element appears
    }

    int num = queue.dequeue();
    emit dequeued(num);

    return num;
}

QList<int> SharedQueue::getAllItems()
{
    QMutexLocker locker(&mutex);
    return queue.toList();
}

bool SharedQueue::isEmpty()
{
    QMutexLocker locker(&mutex);
    return queue.isEmpty();
}

int SharedQueue::size()
{
    QMutexLocker locker(&mutex);
    return queue.size();
}
