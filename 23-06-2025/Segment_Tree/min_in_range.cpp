#include<bits/stdc++.h>
using namespace std;

void build(int node,int start,int end,vector<int> &v,vector<int> &tree)
{
    if(start==end)
    {
        tree[node] = v[start];
        return;
    }
    int mid = start + (end-start)/2;
    build(2*node+1,start,mid,v,tree);
    build(2*node+2,mid+1,end,v,tree);
    tree[node] =  min(tree[2*node+1],tree[2*node+2]);

}

int query(int node,int l,int r,int start,int end,vector<int>&tree)
{
    if(r<start || l>end) return INT_MAX;
    if(start>=l && end<=r)  return tree[node];
    int mid = start + (end-start)/2;
    int left = query(2*node+1,l,r,start,mid,tree);
    int right = query(2*node+2,l,r,mid+1,end,tree);
    return min(left,right);
}

int main()
{
    int n;
    cin>>n;
    vector<int> tree(4*n,INT_MAX);
    vector<int> v(n);
    for(int i=0;i<n;i++)
        cin>>v[i];

    cout<<endl;
    build(0,0,n-1,v,tree);
    // int j=0;
    // for(int i:tree)
    // {   
    //     if(i==INT_MAX)
    //         cout<<"N ";
    //     else
    //         cout<<i<<" ";
    //     j++;
    //     if(j%n==0)
    //     {
    //         cout<<endl;
    //         j=0;
    //     }
    // }
    int Q;
    cout<<"Q: ";
    cin>>Q;
    while(Q--)
    {
        int l,r;
        cout<<"L and R: ";
        cin>>l>>r;
        cout<<"Min in range: "<<query(0,l,r,0,n-1,tree)<<endl;
    }
    return 0;
}