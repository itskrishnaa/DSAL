#include <iostream>
#include <climits>
using namespace std;
#define SIZE 10
class OBST
{
    int p[SIZE], a[SIZE];
    int w[SIZE][SIZE], c[SIZE][SIZE], r[SIZE][SIZE];
    int n;

public:
    void get_data()
    {
        cout << "\nOptimal Binary Search Tree\n";
        cout << "Enter The Number Of Nodes: ";
        cin >> n;
        cout << "Enter the Data (Keys):\n";
        for (int i = 1; i <= n; i++)
        {
            cout << "a[" << i << "]: ";
            cin >> a[i];
        }
        cout << "Enter the Success Probabilities:\n";
        for (int i = 1; i <= n; i++)
        {
            cout << "p[" << i << "]: ";
            cin >> p[i];
        }
    }
    int min_value(int i, int j)
    {
        int minCost = INT_MAX, k = i;
        for (int m = r[i][j - 1]; m <= r[i + 1][j]; m++)
        {
            if (m >= j)
                break;
            int cost = c[i][m] + c[m + 1][j];
            if (cost < minCost)
            {
                minCost = cost;
                k = m;
            }
        }
        return k;
    }
    void build_obst()
    {
        for (int i = 0; i <= n; i++)
        {
            w[i][i] = 0;
            c[i][i] = 0;
            r[i][i] = 0;
        }
        for (int i = 1; i <= n; i++)
        {
            w[i - 1][i] = p[i];
            c[i - 1][i] = p[i];
            r[i - 1][i] = i;
        }
        for (int m = 2; m <= n; m++)
        {
            for (int i = 0; i <= n - m; i++)
            {
                int j = i + m;
                w[i][j] = w[i][j - 1] + p[j];
                int k = min_value(i, j);
                c[i][j] = w[i][j] + c[i][k] + c[k + 1][j];
                r[i][j] = k;
            }
        }
    }
    void build_tree(int i, int j)
    {
        if (i >= j)
            return;
        int root = r[i][j];
        if (root == 0)
            return;
        cout << "\n\t" << a[root];
        if (root - 1 >= i && r[i][root - 1] != 0)
            cout << "\t\t" << a[r[i][root - 1]];
        else
            cout << "\t\t-";
        if (root + 1 <= j && r[root + 1][j] != 0)
            cout << "\t\t" << a[r[root + 1][j]];
        else
            cout << "\t\t-";
        build_tree(i, root - 1);
        build_tree(root + 1, j);
    }
    void display_tree()
    {
        cout << "\nThe Optimal Binary Search Tree for the Given Node is:\n";
        cout << "The Root of this OBST is: " << a[r[0][n]] << endl;
        cout << "The Cost of this OBST is: " << c[0][n] << endl;
        cout << "\n\n\t NODE \t LEFT CHILD \t RIGHT CHILD\n";
        build_tree(0, n);
    }
};
int main()
{
    OBST obj;
    obj.get_data();
    obj.build_obst();
    obj.display_tree();
    return 0;
}
