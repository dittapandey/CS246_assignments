#include<bits/stdc++.h>
using namespace std;

template<typename T>
void print_vec(vector<T>& v){
    for(int i=0;i<v.size();i++){
        cout<<v[i]<<" ";
    }
    cout<<endl;
}

int getSetFromString(string str){
    vector<int>pos;
    pos.push_back(-1);
    for(int i=0;i<str.size();i++){
        if(str[i]==' '){
            pos.push_back(i);
        }
    }
    pos.push_back(str.size());
    // cout<<"Spaces at:";
    // print_vec(pos);
    int set=0;
    for(int i=0;i<pos.size()-1;i++){
        int value=0;
        int k=1;
        for(int j=pos[i+1]-1;j>pos[i];j--){
            value+=(k*(str[j]-48));
            // cout<<"character considered: "<<str[j]<<endl;
            k*=10;
        }
        // cout<<"value: "<<(1<<(value-1))<<endl;
        
        set = set + (1<<(value-1));
    }
    return set;
}

vector<string> getStringFromCandidateKey(vector<int>& keys){
    vector<string>ans;
    for(int i=0;i<keys.size();i++){
        int temp = keys[i];
        string a="";
        int count =0;
        while(temp!=0){
            if(temp%2==1){
                a = a+to_string(count+1)+" ";
            }
            temp=temp/2;
            count++;
        }
        // cout<<a<<endl;
        ans.push_back(a);
    }
    return ans;
}

int main(){
    int n,m;
    cin>>n>>m;
    map<int, vector<int> >dependency;
    map<int,int>closure;
    vector<int>candidate_key;
    for(int i=0;i<m;i++){
        string s1,s2;
        getline(cin>>ws, s1);
        getline(cin>>ws, s2);
        int x = getSetFromString(s1);
        int y = getSetFromString(s2);
        dependency[x].push_back(y);
    }
    map<int, vector<int> >::iterator x = dependency.begin();
    for(x = dependency.begin();x!=dependency.end();x++){
        (*x).second.push_back((*x).first);
    }

    for(int set=0;set<(1<<n);set++){
        bool flag = 0;
        for(int j = 0; j<candidate_key.size(); j++){
            // cout<<(set|candidate_key[j] == set) && (set&candidate_key[j]==candidate_key[j])<<endl;
            if(((set|candidate_key[j]) == set) && ((set&candidate_key[j])==candidate_key[j])){
                flag=1;
            }
            if(flag) break;
        }
        if(flag) continue;
        int closure=0;
        // closure from set currently being considered
        for(int i=0;i<=set;i++){
            if(((set|i) == set) && ((set&i)==i)){
                for(int k=0;k<dependency[i].size();k++){
                    closure = (closure)|(dependency[i][k]);
                }
            }
        }
        // using transitive property
        int prev_closure = closure;
        do{
            prev_closure = closure;
            int temp_set = closure;
            for(int i=0;i<=temp_set;i++){
                if(((temp_set|i) == temp_set) && ((temp_set&i)==i)){
                    for(int k=0;k<dependency[i].size();k++){
                        closure = closure|dependency[i][k];
                    }
                }
        
            }
        }while(closure != prev_closure);

        if(closure == (1<<n)-1){
            candidate_key.push_back(set);
        }
    }
    vector<string>ans = getStringFromCandidateKey(candidate_key);
    cout<<ans.size()<<endl;
    for(int i=0;i<ans.size();i++){
        cout<<ans[i]<<endl;
    }
}