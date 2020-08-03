#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
string lsubstr(const string & str){
    vector<string> vs;
    for (int i = 0; i < str.size(); i++)
        vs.push_back(str.substr(i));
    sort(vs.begin(), vs.end());
    int max = 0;
    int flag = 0;
    for (int i = 0; i <( vs.size()-1); i++)
    {
        int j = 0;
        while (vs[i][j] == vs[i + 1][j] && j<vs[i].size() && j<vs[i+1].size())
            j++;
        if (j>max)
        {
            max = j;
            flag = i;
        }          
    }
    return vs[flag].substr(0, max);
}
int main(){
    string test;
    getline(cin, test);
    cout << lsubstr(test).length() << endl;
}