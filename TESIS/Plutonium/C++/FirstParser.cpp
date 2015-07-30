#include <bits/stdc++.h>

using namespace std;

string to_str(char& a)
{
    string as;
    as.push_back(a);
    return as;
}

template<typename S, typename R>
struct Parser{
    S symbol;
    vector<pair<R,S>> result;

    Parser* operator >> (Parser* q)
    {

    }

    void ptr()
    {
        cout << "[ ";
        for(int i = 0; i < result.size(); ++i){
            cout << "("<<result[i].first << " ," << result[i].second<<")";
        }
        cout << " ]";
    }
};

template<typename S, typename R>
void func (Parser<S,R>* p, char a)
{
    if(p->symbol.back() == a){
        string _r = to_str(p->symbol.back());
        p->symbol.pop_back();
        p->result.push_back(make_pair(_r,p->symbol));
    }
}

int main()
{
   /* string resp = "hola", ans = "";
    func<string,string>(resp, ans);*/
    Parser<string,string> asd;
    asd.symbol = "olaH";
    func(&asd, 'H');
    func(&asd, 'a');
    asd.ptr();
    return 0;
}
