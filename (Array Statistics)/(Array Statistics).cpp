#include<bits/stdc++.h>

using namespace std;

int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);
#endif
	
    int n;cin >> n;
    int arr[n];
    map<int,int>freq;
    int mode = 0,x = 0, range, sum = 0;
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
        freq[arr[i]]++;
        sum+=arr[i];
    }
    for(auto it:freq){
        if(it.second>x){x = it.second;mode = it.first;}
    }
    sort(arr, arr+n);
    double median, mean;
    mean = (double)sum/n;
    range = arr[n-1]-arr[0];
    if(n%2==0)median = (double)(arr[n/2]+arr[n/2-1])/2;
    else median = arr[n/2];
    cout << mean << '\n'<< median<<'\n'<<mode <<'\n'<< range;
}