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



template <char t>
Parser<char> symbol (string xs)
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
/*
template<typename A,typename B>
Parser<T> por (A a, B b, string input)
{
    return f(input);
}*/

void pf(const char* s)
{
    if (s==nullptr) return;
    while (*s) {
        if (*s=='%' && *++s!='%')
            throw runtime_error("invalid format: missing arguments");
        std::cout << *s++;
    }
}

template<typename T, typename... Args>
void pf(const char* s, T value, Args... args)
{
    while (s && *s) {
        if (*s=='%' && *++s!='%') { // a for mat specifier (ignore which one it is)
            std::cout << value; // use first non-for mat argument
            return pf(++s, args...); // do a recursive call with the tail of the argument list
        }
        std::cout << *s++;
    }
    throw std::runtime_error("extra arguments provided to printf");
}

void a()
{
    std::cout << "A";
}

void b()
{
    std::cout << "B";
}

void c()
{
    std::cout << "C";
}

template<typename F>
void ss(F functor)
{
}

template<typename F, typename... Args>
void ss(F functor, Args... args)
{
   // functor();
    ss(args...);
}


/*COMBINATORS*/

template<typename R, typename F, typename P>
Parser<R> por (string input, F f, P p)
{
    auto r = p(input);
    auto f1 = f(r.result[0]->first);
    Parser<R> last;
    last.result.push_back(new pair<R,string>(f1, r.result[0]->second));
    return last;
}

template<typename R, typename F, typename P, typename... Args>
Parser<R> por (string input, F f, P p, Args... args)
{
    auto r = p(input);
    auto f1 = f(r.result[0]->first);
    return por<R>(r.result[0]->second, f1, args... );
}

int main()
{
   // string a = "dota2";
   // reverse(a.begin(),a.end());
   /* auto lambda = [] (string input,
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

   // Parser<string> p = seq<string>(lambda, a);
    //p.ptr();

    //pf("Hola %d %d %d ",121,13,"asd");

    ss(a,b,c);
    auto f1 = symbol<'d'>;
    string dota = "dota";
    reverse(dota.begin(),dota.end());
    auto resu = por<string>(dota, [](char a) { return ( [b = a](char c) { return to_str(b) + to_str(c); } ); },
        symbol<'d'>, symbol<'o'>
    );

    ss(symbol<'d'>, symbol<'o'>);

    resu.ptr();

    auto qwe = [](char a)  {return ([t = a](char q){return q+t;});};
    auto ter= qwe(1);
    auto qqq = ter(2);
    cout << qqq<<endl;




    return 0;
}
