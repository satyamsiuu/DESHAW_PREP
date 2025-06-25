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

int getsum(int node, int l, int r, int start, int end, vector<int> &tree, vector<int> &lazy)
{
    if (lazy[node] != 0)
    {
        tree[node] += (end - start + 1) * lazy[node];

        if (start != end)
        {
            lazy[2 * node + 1] += lazy[node];
            lazy[2 * node + 2] += lazy[node];
        }

        lazy[node] = 0;
    }

    if (end < l || start > r)
        return 0;

    if (start >= l && end <= r)
        return tree[node];

    int mid = (start + end) / 2;
    int left = getsum(2 * node + 1, l, r, start, mid, tree, lazy);
    int right = getsum(2 * node + 2, l, r, mid + 1, end, tree, lazy);
    return left + right;
}

void update(int val, int l, int r, int node, int start, int end, vector<int> &v, vector<int> &tree, vector<int> &lazy)
{
    if (lazy[node] != 0)
    {
        tree[node] += (end - start + 1) * lazy[node];
        if (start != end)
        {
            lazy[2 * node + 1] += lazy[node];
            lazy[2 * node + 2] += lazy[node];
        }
        lazy[node] = 0;
    }

    if (start > r || end < l)
        return;

    if (start >= l && end <= r)
    {
        tree[node] += (end - start + 1) * val;
        if (start != end)
        {
            lazy[2 * node + 1] += val;
            lazy[2 * node + 2] += val;
        }
        return;
    }

    int mid = (start + end) / 2;
    update(val, l, r, 2 * node + 1, start, mid, v, tree, lazy);
    update(val, l, r, 2 * node + 2, mid + 1, end, v, tree, lazy);
    tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
}

void print_tree(vector<int> &tree, int n)
{
    cout << "The Segment Tree Array is:-\n";
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

void print_lazy(vector<int> &lazy, int n)
{
    cout << "The Lazy Array is:-\n";
    int j = 0;
    for (int i : lazy)
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

    vector<int> lazy(4 * n, 0);
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
        cout << "2. Update range of values\n";
        cout << "3. Print segment tree\n";
        cout << "4. Print lazy array\n";
        cout << "5. Exit\n";

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
                    cout << "Sum of range [" << l << "," << r << "] = " << getsum(0, l, r, 0, n - 1, tree, lazy) << endl;
            }
            break;
        }

        case 2:
        {
            int start, end, val;
            cout << "Enter range of update: ";
            cin >> start >> end;
            cout << "Enter value to add: ";
            cin >> val;
            if (start < 0 || end >= n || start > end)
                cout << "Invalid range!\n";
            else
                update(val, start, end, 0, 0, n - 1, v, tree, lazy);
            break;
        }

        case 3:
            print_tree(tree, n);
            break;

        case 4:
            print_lazy(lazy, n);
            break;

        case 5:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != 5);

    return 0;
}
