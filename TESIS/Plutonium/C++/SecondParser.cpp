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

    void operator | (Parser<R>* t)
    {
        this->result.push_back(t->result[0]);
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



//template<char>
Parser<char>* symbol (char t, string xs)
{
    Parser<char>* parser = new Parser<char>();
    auto x = x_(xs) == t;
    switch(x)
    {
    case true:
        {
        xs.pop_back();
        pair<char,string>* result = new pair<char,string>(t,xs);
        parser->result.push_back(result);
        break;
        }
    default:
        parser->result.push_back(nullptr);
        break;
    }
    cout << parser<<endl;
    return parser;
}

int main()
{
    string a = "hola";
    reverse(a.begin(),a.end());
    Parser <char>* as = symbol('h', a);
    Parser <char>* a2 = symbol('o',as->result[0]->second);
    cout << as<<endl;
    cout << &(*(as)) <<endl;
    *(as) * symbol('o',as->result[0]->second);
    as->ptr();
    return 0;
}
