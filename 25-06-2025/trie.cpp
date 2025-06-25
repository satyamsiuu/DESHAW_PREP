#include<bits/stdc++.h>
using namespace std;

struct Node
{
    bool isWord;
    Node* child[26];
};

Node* newnode()
{
    Node *temp = new Node();
    temp->isWord = false;
    for(int i=0;i<26;i++)
        temp->child[i] = NULL;
    return temp;
}

void insert(Node* root,string str)
{
    int n = str.length();
    for(int i=0;i<n;i++)
    {
        if(root->child[str[i]-'a']==NULL)
            root->child[str[i]-'a'] = newnode();
        root = root->child[str[i]-'a'];
    }
    root->isWord = true;
}

bool search(Node *root, string str)
{
    int n = str.length();
    for(int i=0;i<n;i++)
    {
        if(root->child[str[i]-'a']==NULL)
        {
            cout<<" is not in trie "<<endl;
            return false;
        } 
        root = root->child[str[i]-'a'];
    }

    if(root->isWord==false)
    {
        cout<<" is not in trie but as a substring\n";
        return false;
    }

    return root->isWord;
}

void delete1(Node* root,string str) // Soft Delete
{
    int n = str.length();
    for(int i =0;i<n;i++)
    {
        if(root->child[str[i]-'a']==NULL)
            return;
        root = root->child[str[i]-'a'];
    }
    root->isWord = false;
}

bool check(Node *root)
{
    for(int i=0;i< 26;i++)
    {
        if(root->child[i]!=NULL)
            return false;
    }
    return !root->isWord;
}

Node* deleteUtils(Node* root,string str, int n, int i)
{
    if(root==NULL)
        return NULL;

    if(i==n)
    {
        root->isWord = false;
        if(check(root))
        {
            delete root;
            return NULL;
        }
        else
            return root;
    }

    Node *temp = deleteUtils(root->child[str[i]-'a'],str,n,i+1);

    if(temp==NULL)
    {
        root->child[str[i]-'a'] =NULL;
        if(check(root))
        {
            delete root;    
            return NULL;
        }
    }
    
    return root;
}

void delete2(Node* &root,string str) // Hard Delete
{
    int n = str.length();
    root = deleteUtils(root,str,n,0);
}

void deleteAll(Node* root) 
{
    if (!root) 
        return;

    for (int i = 0; i < 26; i++)
        deleteAll(root->child[i]);
    delete root;
}

int main()
{
    int Q,ch;
    Node * head = newnode();
    cout<<"Enter Queries: ";
    cin>>Q;
    string str;
    while(Q--)
    {
        cout<<"Menu\n1. Insert\n2. Search\n3. Soft Delete\n4. Hard Delete\nEnter your choice: ";
        cin>>ch;
        switch(ch)
        {
            case 1: cout<<"Enter string: ";
                    cin>>str;
                    insert(head,str);
                    cout<<"String inserted"<<endl;
            break;

            case 2: cout<<"Enter a string: ";
                    cin>>str;
                    cout<<str;
                    if(search(head,str))
                        cout<<" is in trie"<<endl;
            break;

            case 3: cout<<"Enter a string to soft delete: ";
                    cin>>str;
                    if(search(head,str))
                    {
                        delete1(head,str);
                        cout<<"Soft Deleted"<<endl;
                    }
                        
            break;

            case 4: cout<<"Enter a string to hard delete: ";
                    cin>>str;
                    if(search(head,str))
                    {
                        delete2(head,str);
                        if(head==NULL)
                        {
                            head = newnode();
                            cout << "Trie is now empty. Head node reinitialized." << endl;
                        }
                        else
                            cout << "Hard Deleted" << endl;
                    }
                        
            break;

            default: cout<<"Invalid Choice";
        }
    }
    deleteAll(head);
    return 0;
}