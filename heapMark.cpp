#include <iostream>
using namespace std;

class heap
{
public:
    void MAX_HEAPIFY(int a[], int i, int n)
    {
        int largest = i;
        int l = 2 * i;
        int r = 2 * i + 1;

        if (l <= n && a[l] > a[largest])
            largest = l;
        if (r <= n && a[r] > a[largest])
            largest = r;

        if (largest != i)
        {
            swap(a[i], a[largest]);
            MAX_HEAPIFY(a, largest, n);
        }
    }

    void BUILD_MAX_HEAP(int a[], int n)
    {
        for (int k = n / 2; k >= 1; k--)
        {
            MAX_HEAPIFY(a, k, n);
        }
    }

    void HEAPSORT(int a[], int n)
    {
        BUILD_MAX_HEAP(a, n);
        for (int i = n; i >= 2; i--)
        {
            swap(a[1], a[i]);
            MAX_HEAPIFY(a, 1, i - 1);
        }
    }

    void accept()
    {
        int n;
        cout << "Enter the number of students: ";
        cin >> n;

        int a[n + 1]; // 1-based indexing
        cout << "Enter the marks of the students:\n";
        for (int i = 1; i <= n; i++)
            cin >> a[i];

        HEAPSORT(a, n);
        display(a, n);
    }

    void display(int a[], int n)
    {
        cout << "\nSORTED MARKS (Ascending):\n";
        for (int i = 1; i <= n; i++)
            cout << a[i] << " ";

        cout << "\nMinimum marks obtained: " << a[1];
        cout << "\nMaximum marks obtained: " << a[n] << endl;
    }
};

int main()
{
    heap h;
    h.accept();
    return 0;
}