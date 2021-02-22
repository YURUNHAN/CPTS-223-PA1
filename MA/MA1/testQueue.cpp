
#include "testQueue.h"
#include "queue.h"

static void assertEquals(int expect, int actual)
{
    if (expect == actual)
    {
        cout << "Pass!";
    }
    else
    {
        cout << "Failed! Expect: " << expect << " Acutal: " << actual;
    }
    cout << endl;
}

void testEmpty()
{
    cout << "Test for queue::isEmpty " << endl;
    queue q;
    assertEquals(1, q.isEmpty());
    cout << "--------------------------------" << endl;
}

void testFull()
{
    cout << "Test for queue::isFull " << endl;
    queue q(3);
    assertEquals(0, q.isFull());
    cout << "--------------------------------" << endl;
}

void testSize()
{
    cout << "Test for queue::size " << endl;
    queue q(3);
    assertEquals(0, q.size());
    cout << "--------------------------------" << endl;
}

void testEnqueueForNonFullQueue()
{
    cout << "Test for queue::enqueue " << endl;
    queue q(2);
    cout << "Expect: Inserting 1" << endl;
    cout << "Actual: ";
    q.enqueue(1);
    cout << "Expect: Inserting 2" << endl;
    cout << "Actual: ";
    q.enqueue(2);
    cout << "--------------------------------" << endl;
}

void testEnqueueForFullQueue()
{
    cout << "Test for queue::enqueue " << endl;
    queue q(2);
    q.enqueue(1);
    q.enqueue(2);
    cout << "Expect: OverFlow\nProgram Terminated\n" << endl;
    cout << "Actual: ";
    q.enqueue(3);
    cout << "--------------------------------" << endl;
}

void testDequeueForNonEmptyQueue()
{
    cout << "Test for queue::dequeue " << endl;
    queue q(2);
    q.enqueue(1);
    cout << "Expect: Removing 1" << endl;
    cout << "Actual: ";
    q.dequeue();
    cout << "--------------------------------" << endl;
}

void testDequeueForEmptyQueue()
{
    cout << "Test for queue::dequeue " << endl;
    queue q(2);
    cout << "Expect: UnderFlow\nProgram Terminated\n" << endl;
    cout << "Actual: ";
    q.dequeue();
    cout << "--------------------------------" << endl;
}

void testPeekForNonEmptyQueue()
{
    cout << "Test for queue::peek " << endl;
    queue q(2);
    q.enqueue(1);
    assertEquals(1, q.peek());
    cout << "--------------------------------" << endl;
}

void testPeekForEmptyQueue()
{
    cout << "Test for queue::peek " << endl;
    queue q(2);
    cout << "Expect: UnderFlow\nProgram Terminated\n" << endl;
    cout << "Actual: ";
    q.peek();
    cout << "--------------------------------" << endl;
}





