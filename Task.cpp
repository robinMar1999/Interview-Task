#include<bits/stdc++.h>
using namespace std;

int dayofweek(string s){
    int d=0,m=0,y=0;
    y = 1000*(s[0]-'0') + 100*(s[1]-'0') + 10*(s[2]-'0') + (s[3]-'0');
    m = 10*(s[5]-'0') + (s[6]-'0');
    d = 10*(s[8]-'0') + (s[9]-'0');

    // sakamoto algorithm
    static int t[]={0,3,2,5,0,3,5,1,4,6,2,4};
    if(m<3){
        y--;
    }
    return (y + y/4 - y/100 + y/400 + t[m-1] + d-1+7)%7;
}

vector<pair<string,int>> calc(vector<pair<string,int>> &dic){
    map<int,string> mp;
    mp[0]="Mon";
    mp[1]="Tue";
    mp[2]="Wed";
    mp[3]="Thu";
    mp[4]="Fri";
    mp[5]="Sat";
    mp[6]="Sun";
    vector<pair<string,int>> res;        // result vector
    vector<int> vis(7,0);         // visited array
    for(int i=0;i<=6;i++){
        res.push_back({mp[i],0});
    }
    for(auto p:dic){
        int w=dayofweek(p.first);
        res[w].second+=p.second;
        vis[w]=1;
    }
    // now to find average for vacant places
    int i=0;
    while(i<7){
        // find first place where it is vacant
        while(i<7 and vis[i]==1){
            i++;
        }
        int prev=i-1;
        // now find the first place where it is filled
        while(i<7 and vis[i]==0){
            i++;
        }
        int curr=i;
        i++;
        // find common difference between prev and curr values
        int cd=(res[curr].second-res[prev].second)/(curr-prev);
        int val=res[prev].second;
        for(int j=prev+1;j<curr;j++){
            res[j].second=val+cd;
            val=res[j].second;
        }
    }
    return res;
}

int main(){
    int n;
    cin>>n;
    vector<pair<string,int>> dic;
    for(int i=0;i<n;i++){
        string s;
        int k;
        cin>>s>>k;
        dic.push_back({s,k});
    }
    vector<pair<string,int>> res=calc(dic);
    for(auto p:res){
        cout<<p.first<<" "<<p.second<<endl;
    }
}
