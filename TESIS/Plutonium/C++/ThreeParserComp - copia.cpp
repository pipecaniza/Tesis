#include <bits/stdc++.h>

#define x_(xs) xs.back()

using namespace std;

string to_str(char a)
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

    Parser<R>& operator | (Parser<R> t)
    {
        for(int i = 0; i < t.result.size(); ++i)
            this->result.push_back(t.result[i]);

        //cout<< "OR\n";
        //this->ptr();
        return *this;
    }
    void Add(Parser<R> np)
    {
        for(int i = 0; i < np.result.size(); ++i)
            result.push_back(np.result[i]);
    }

    Parser<R> get(int i)
    {
        Parser<R> r;
        r.result.push_back(result[i]);
        return r;
    }

    ~Parser()
    {
        result.clear();
    }

    void ptr()
    {
        cout << "[ ";
        for(int i = 0; i < result.size(); ++i){
            if(result[i] == nullptr)
                break;
            cout << "("<<result[i]->first << ",\"" << result[i]->second<<"\"),";
        }
        cout << " ]\n" ;
    }
};



template <char t>
Parser<char> symbol (string xs)
{
  //  cout << "to parser: "<<xs<<endl;
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
        //parser.result.push_back(nullptr);
        break;
    }
    return parser;
}

template<char t>
Parser<char> succeded(string xs)
{
    Parser<char> parser;
    parser.result.push_back(new pair<char,string>(t,xs));
    return parser;
}


/*COMBINATORS*/

template<typename R, typename F, typename P>
Parser<R> seq (string input, F f, P p)
{
  //  cout << "p\n";
  //cout << "in: "<<input<<endl;
 // if(input == ")(")cout << "THIS\n";
    auto r = p(input);
    if(r.result.size() == 0){
        Parser<R> r1;
        return r1;
    }
    auto f1 = f(r);
    //f1.ptr();
   // cout <<"FINAL ___ parseado: "<< r.result[0]->first<<"    Queda: "<<r.result[0]->second<<endl;
    return f1;
}

template<typename R, typename F, typename P, typename... Args>
Parser<R> seq (string input, F f, P p, Args... args)
{
    auto r = p(input);
    if(r.result.size() == 0){
        Parser<R> r1;
        return r1;
    }
    Parser<R> final_result;

    for(int i = 0; i < r.result.size(); ++i){
        //cout <<"parseado: "<< r.result[0]->first<<"    Queda: "<<r.result[0]->second<<endl;
        //r.ptr();
        auto f1 = f(r.get(i));
        final_result.Add(seq<R>(r.result[i]->second, f1, args... ));
    }
   // final_result.ptr();
    return final_result;
}

auto l = [](Parser<char> a){
            return [](Parser<string> b){
                return [b](Parser<char> c){
                    return [b] (Parser<string> d){
                        Parser<string> q;
                        q.result.push_back(new pair<string,string>("Inside ("  + b.result[0]->first + d.result[0]->first + ") ", d.result[0]->second));
                        return q;
                    };
                };
            };
        };

auto l2 = [](Parser<char> a){
            Parser<string> q;
            q.result.push_back(new pair<string,string>("Empty ", a.result[0]->second));
            return q;
};

Parser<string> parenthesis(string input)
{
    auto result =   seq<string>(input, l , symbol<'('>, parenthesis, symbol<')'>, parenthesis)
                    |   seq<string>(input, l2, succeded<'e'>);
    //result.ptr();
    return result;
}

string S(string input)
{
    char a = input.back(); input.pop_back();
    if(a == '(')
    {
        string q = S(input);
        a = input.back();input.pop_back();
        if(a != ')')
            return q;
        else{
            return "Inside " + q;
        }
    }
    else{
        return "Empty";
    }
}

int main()
{
    auto f1 = symbol<'d'>;
    string dota = "(())()";
    reverse(dota.begin(),dota.end());cout << dota<<endl;

//   resu.ptr();

    auto result = parenthesis(dota);
    result.ptr();

   // cout << S(dota)<< endl;

    return 0;
}



