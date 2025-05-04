#include <iostream>
#include <string>
using namespace std;
#define MAX 100

struct Patient
{
    string name;
    int priority;
};

class PriorityQueue
{
private:
    Patient heap[MAX];
    int size = 0;

    void swap(Patient &a, Patient &b)
    {
        Patient temp = a;
        a = b;
        b = temp;
    }

    void heapifyUp(int index)
    {
        while (index > 0 && heap[index].priority > heap[(index - 1) / 2].priority)
        {
            swap(heap[index], heap[(index - 1) / 2]);
            index = (index - 1) / 2;
        }
    }

    void heapifyDown(int index)
    {
        int largest = index, left = 2 * index + 1, right = 2 * index + 2;
        if (left < size && heap[left].priority > heap[largest].priority)
            largest = left;
        if (right < size && heap[right].priority > heap[largest].priority)
            largest = right;
        if (largest != index)
        {
            swap(heap[index], heap[largest]);
            heapifyDown(largest);
        }
    }

public:
    void insert(string name, int priority)
    {
        if (size >= MAX)
            return void(cout << "Queue is full!\n");
        heap[size++] = {name, priority};
        heapifyUp(size - 1);
    }

    void extractMax()
    {
        if (size == 0)
            return void(cout << "Queue is empty!\n");
        cout << "Serving patient: " << heap[0].name << " with priority: " << heap[0].priority << endl;
        heap[0] = heap[--size];
        heapifyDown(0);
    }

    void display()
    {
        if (size == 0)
            return void(cout << "Queue is empty!\n");
        cout << "Patients in the queue:\n";
        for (int i = 0; i < size; i++)
            cout << "Name: " << heap[i].name << " | Priority: "
                 << (heap[i].priority == 10 ? "Serious" : heap[i].priority == 5 ? "Non-serious"
                                                                                : "Checkup")
                 << endl;
    }
};

int main()
{
    PriorityQueue pq;
    int choice, priority;
    string name;

    do
    {
        cout << "\n1. Insert Patient\n2. Serve Patient\n3. Display Queue\n0. Exit\nChoice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Name: ";
            cin >> name;
            cout << "Priority (10/5/1): ";
            cin >> priority;
            pq.insert(name, priority);
            break;
        case 2:
            pq.extractMax();
            break;
        case 3:
            pq.display();
            break;
        case 0:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 0);

    return 0;
}