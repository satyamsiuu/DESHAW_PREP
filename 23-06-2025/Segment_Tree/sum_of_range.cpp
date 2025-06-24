#include <bits/stdc++.h>
using namespace std;

void build(int node, int start, int end, vector<int> &v, vector<int> &tree)
{
    if (start == end)
    {
        tree[node] = v[start];
        return;
    }
    int mid = (start + end) / 2;
    build(2 * node + 1, start, mid, v, tree);
    build(2 * node + 2, mid + 1, end, v, tree);
    tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
}

int getsum(int node, int l, int r, int start, int end, vector<int> &tree)
{
    if (end < l || start > r)
        return 0;
    if (start >= l && end <= r)
        return tree[node];

    int mid = (start + end) / 2;
    int left = getsum(2 * node + 1, l, r, start, mid, tree);
    int right = getsum(2 * node + 2, l, r, mid + 1, end, tree);
    return left + right;
}

void update(int val, int idx, int node, int start, int end, vector<int> &v, vector<int> &tree)
{
    if (start == end)
    {
        v[idx] = val;
        tree[node] = val;
        return;
    }

    int mid = (start + end) / 2;
    if (idx <= mid)
        update(val, idx, 2 * node + 1, start, mid, v, tree);
    else
        update(val, idx, 2 * node + 2, mid + 1, end, v, tree);

    tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
}

void print_tree(vector<int> &tree, int n)
{
    int j = 0;
    for (int i : tree)
    {
        cout << i << " ";
        j++;
        if (j % n == 0)
        {
            cout << endl;
            j = 0;
        }
    }
    cout << endl;
}

int main()
{
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> tree(4 * n, 0);
    vector<int> v(n);

    cout << "Enter array elements:\n";
    for (int i = 0; i < n; i++)
        cin >> v[i];

    build(0, 0, n - 1, v, tree);

    int choice;
    do
    {
        cout << "\nMenu:\n";
        cout << "1. Query sum for multiple ranges\n";
        cout << "2. Update value at index\n";
        cout << "3. Print segment tree\n";
        cout << "4. Exit\n";
        
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            int q;
            cout << "Enter number of queries: ";
            cin >> q;
            while (q--)
            {
                int l, r;
                cout << "Enter L and R: ";
                cin >> l >> r;
                if (l < 0 || r >= n || l > r)
                    cout << "Invalid range!\n";
                else
                    cout << "Sum of range [" << l << "," << r << "] = " << getsum(0, l, r, 0, n - 1, tree) << endl;
            }
            break;
        }

        case 2:
        {
            int idx, val;
            cout << "Enter index and new value: ";
            cin >> idx >> val;
            if (idx < 0 || idx >= n)
                cout << "Invalid index!\n";
            else
                update(val, idx, 0, 0, n - 1, v, tree);
            break;
        }

        case 3:
            print_tree(tree, n);
            break;

        case 4:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != 4);

    return 0;
}
