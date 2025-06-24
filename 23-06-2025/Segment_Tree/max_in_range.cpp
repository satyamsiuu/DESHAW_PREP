#include<bits/stdc++.h>
using namespace std;

void create_tree(int node,int start,int end,vector<int> &v,vector<int> &tree)
{
    if(start==end)
    {
        tree[node] = v[start];
        return;
    }

    int mid = start + (end-start)/2;
    create_tree(2*node+1,start,mid,v,tree);
    create_tree(2*node+2,mid+1,end,v,tree);
    tree[node] = max(tree[2*node+1],tree[2*node+2]);

}

int query(int node, int start, int end, int l, int r, vector<int> tree)
{
    if(r<start || l>end)
        return INT_MIN;

    if(start>=l && end<=r)
        return tree[node];

    int mid = start + (end-start)/2;
    int left = query(2*node+1, start, mid, l, r, tree);
    int right = query(2*node+2, mid+1, end, l, r, tree);
    return max(left,right);
}

int main()
{
    int n;
    cout<<"Enter n: ";
    cin>>n;
    vector<int> v(n);
    cout<<"Enter elements in the array:-\n";
    for(int i=0;i<n;i++)
        cin>>v[i];
    
    vector<int> tree(4*n,0);
    create_tree(0,0,n-1,v,tree);
    cout<<"Created the Segment tree"<<endl;
    int i = 0;
    for(int j: tree)
    {
        cout<<j<<" ";
        i++;
        if(i==n)
        {
            cout<<endl;
            i=0;
        }
    }
    int Q;
    cout<<"Enter Q: ";
    cin>>Q;
    while(Q--)
    {
        int L,R;
        cout<<"L and R: ";
        cin>>L>>R;
        cout<<"Max Number: "<<query(1,0,n-1,L,R,tree)<<endl;
    }

    return 0;
}