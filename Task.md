# Develop C++ QT Window Application

Develop C++ QT window application, with multiple threads that communicate with each other.

There are three threads:

1. One thread is generating numbers incremented by one each time. You can start and stop this thread any time from GUI.

2. There is a queue (it is functioning as FIFO) that contains 20 numbers, if more than 20 numbers are received then oldest number is cleared, and replaced by a new number that came.

    This queue is located in a separate thread.

3. Third thread is taking numbers from the queue.

---

QT windows application should contain three list boxes, each listbox contains all numbers for a particular thread. Listboxes should be refreshed at least 3 times per second to reflect the latest state of each thread.

There should be the ability to start and stop separately the first and third threads from GUI, by clicking on a Start/Stop button.
