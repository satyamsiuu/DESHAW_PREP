#include <bits/stdc++.h>
using namespace std;

// Get prefix sum from index 0 to given index
int getSum(const vector<int>& BITree, int index) {
    int sum = 0;
    index = index + 1;
    while (index > 0) {
        sum += BITree[index];
        index -= index & (-index);
    }
    return sum;
}

// Update the BITree at index with value
void updateBIT(vector<int>& BITree, int n, int index, int val) {
    index = index + 1;
    while (index <= n) {
        BITree[index] += val;
        index += index & (-index);
    }
}

// Construct BITree using reference
void constructBITree(const vector<int>& arr, vector<int>& BITree, int n) {
    for (int i = 0; i <= n; i++)
        BITree[i] = 0;

    for (int i = 0; i < n; i++)
        updateBIT(BITree, n, i, arr[i]);
}

// Print the contents of BITree
void printBITree(const vector<int>& BITree, int n) {
    cout << "BITree contents: ";
    for (int i = 1; i <= n; i++) {
        cout << BITree[i] << " ";
    }
    cout << endl;
}

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter elements of the array:\n";
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    vector<int> BITree(n + 1);  // BITree[0] unused

    constructBITree(arr, BITree, n);

    int choice;
    do {
        cout << "\n------ MENU ------\n";
        cout << "1. Get prefix sum (0 to index)\n";
        cout << "2. Update element at index\n";
        cout << "3. Print BITree\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int index;
                cout << "Enter index (0 to " << n - 1 << "): ";
                cin >> index;
                if (index >= 0 && index < n)
                    cout << "Prefix sum from 0 to " << index << " is " << getSum(BITree, index) << endl;
                else
                    cout << "Invalid index!\n";
                break;
            }

            case 2: {
                int index, val;
                cout << "Enter index (0 to " << n - 1 << "): ";
                cin >> index;
                if (index >= 0 && index < n) {
                    cout << "Enter value to add: ";
                    cin >> val;
                    arr[index] += val;
                    updateBIT(BITree, n, index, val);
                    cout << "Updated successfully.\n";
                } else {
                    cout << "Invalid index!\n";
                }
                break;
            }

            case 3:
                printBITree(BITree, n);
                break;

            case 4:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice! Please try again.\n";
        }

    } while (choice != 4);

    return 0;
}
