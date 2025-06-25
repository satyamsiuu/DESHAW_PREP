#include <iostream>
using namespace std;

class TrieNode {
public:
    bool isWord;
    TrieNode* child[26];

    TrieNode() {
        isWord = false;
        for (int i = 0; i < 26; i++)
            child[i] = nullptr;
    }

    ~TrieNode() {
        for (int i = 0; i < 26; i++)
            delete child[i];
    }

    bool isEmpty() {
        for (int i = 0; i < 26; i++)
            if (child[i] != nullptr)
                return false;
        return !isWord;
    }
};

class Trie {
private:
    TrieNode* root;

    TrieNode* deleteUtils(TrieNode* node, const string& str, int depth) {
        if (node == nullptr) return nullptr;

        if (depth == str.size()) {
            node->isWord = false;
            if (node->isEmpty()) {
                delete node;
                return nullptr;
            }
            return node;
        }

        int index = str[depth] - 'a';
        node->child[index] = deleteUtils(node->child[index], str, depth + 1);

        if (node->isEmpty()) {
            delete node;
            return nullptr;
        }

        return node;
    }

public:
    Trie() {
        root = new TrieNode();
    }

    ~Trie() {
        delete root;
    }

    void insert(const string& str) {
        TrieNode* node = root;
        for (char ch : str) {
            int idx = ch - 'a';
            if (node->child[idx] == nullptr)
                node->child[idx] = new TrieNode();
            node = node->child[idx];
        }
        node->isWord = true;
    }

    bool search(const string& str, bool verbose = true) {
        TrieNode* node = root;
        for (char ch : str) {
            int idx = ch - 'a';
            if (node->child[idx] == nullptr) {
                if (verbose) cout << str << " is not in trie\n";
                return false;
            }
            node = node->child[idx];
        }

        if (!node->isWord) {
            if (verbose) cout << str << " is not in trie but as a substring\n";
            return false;
        }

        return true;
    }

    void softDelete(const string& str) {
        TrieNode* node = root;
        for (char ch : str) {
            int idx = ch - 'a';
            if (node->child[idx] == nullptr)
                return;
            node = node->child[idx];
        }
        node->isWord = false;
    }

    void hardDelete(const string& str) {
        root = deleteUtils(root, str, 0);
        if (root == nullptr) {
            root = new TrieNode();
            cout << "Trie is now empty. Head node reinitialized." << endl;
        } else {
            cout << "Hard Deleted" << endl;
        }
    }
};

int main() {
    int Q, ch;
    string str;
    Trie trie;

    cout << "Enter Queries: ";
    cin >> Q;

    while (Q--) {
        cout << "Menu\n1. Insert\n2. Search\n3. Soft Delete\n4. Hard Delete\nEnter your choice: ";
        cin >> ch;

        switch (ch) {
            case 1:
                cout << "Enter string: ";
                cin >> str;
                trie.insert(str);
                cout << "String inserted\n";
                break;

            case 2:
                cout << "Enter a string: ";
                cin >> str;
                if (trie.search(str))
                    cout << str << " is in trie\n";
                break;

            case 3:
                cout << "Enter a string to soft delete: ";
                cin >> str;
                if (trie.search(str, false)) {
                    trie.softDelete(str);
                    cout << "Soft Deleted\n";
                }
                break;

            case 4:
                cout << "Enter a string to hard delete: ";
                cin >> str;
                if (trie.search(str, false)) {
                    trie.hardDelete(str);
                }
                break;

            default:
                cout << "Invalid Choice\n";
        }
    }

    return 0;
}
