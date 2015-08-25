#include <bits/stdc++.h>

#define x_(xs) xs.back()

using namespace std;

string to_str(char& a)
{
    string as;
    as.push_back(a);
    return as;
}

struct P{
    P* P1;
    string val;

    P(string v){

    }
};

template<typename R>
struct Parser{
    vector<pair<R,string>* > result;

    void operator | (Parser<R> t)
    {
        this->result.push_back(t.result[0]);
    }

    void operator * (Parser<R>* t)
    {

        cout << (this->result[this->result.size()-1]->first) + (t->result[t->result.size()-1]->first) << endl<<t->result[t->result.size()-1]->first<<endl;
        string asd = this->result[this->result.size()-1]->first;
        string asd2 = t->result[t->result.size()-1]->first;// (t->result[t->result.size()-1]->first);
        this->result[this->result.size()-1]->first = asd + " " + asd2;
        this->result[this->result.size()-1]->second = t->result[t->result.size()-1]->second;
    }

    void ptr()
    {
        cout << "[ ";
        for(int i = 0; i < result.size(); ++i){
            if(result[i] == nullptr)
                break;
            cout << "("<<result[i]->first << " ," << result[i]->second<<"),";
        }
        cout << " ]";
    }
};

template<typename T,typename Functor>
Parser<T> seq (Functor f, string input)
{
    return f(input);
}



//template<char>
Parser<char> symbol (char t, string xs)
{
    Parser<char> parser;
    auto x = x_(xs) == t;
    switch(x)
    {
    case true:
        {
        xs.pop_back();
        pair<char,string>* result = new pair<char,string>(t,xs);
        parser.result.push_back(result);
        break;
        }
    default:
        parser.result.push_back(nullptr);
        break;
    }
    return parser;
}

template<typename A,typename B>
Parser<T> por (A a, B b, string input)
{
    return f(input);
}

int main()
{
    string a = "dota2";
    reverse(a.begin(),a.end());
    auto lambda = [] (string input,
                      Parser<char> (*P1)(char,string) = &symbol,
                      Parser<char> (*P2)(char,string) = &symbol,
                      Parser<char> (*P3)(char,string) = &symbol,
                      Parser<char> (*P4)(char,string) = &symbol )
                      {
                          Parser<string> result;
                          auto r1 = P1('d', input);
                          auto r2 = P2('o', r1.result[0]->second);
                          auto r3 = P2('t', r2.result[0]->second);
                          auto r4 = P2('a', r3.result[0]->second);
                          string r5;
                          r5.push_back(r1.result[0]->first);
                          r5.push_back(r2.result[0]->first);
                          r5.push_back(r3.result[0]->first);
                          r5.push_back(r4.result[0]->first);
                          result.result.push_back(new pair<string,string>(r5, r4.result[0]->second));
                          return result;
                      };

   /* Parser <char> as = symbol('h', a);
    Parser <char> a2 = symbol('h', a);
    as.ptr();
    symbol('h', a) | symbol('h', a);*/

    Parser<string> p = seq<string>(lambda, a);
    p.ptr();

    return 0;
}
