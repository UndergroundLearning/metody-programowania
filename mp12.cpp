#include<iostream>
using namespace std;

template <class typ> typ zero (typ a) {return typ(0);}
template <> string zero <string> (string a) {return string("zero");}
template <class T>

class vec 
{

int r;
T* wsk;

public:
  vec(): r(0), wsk(0) {}
  vec(int rozm): r(rozm), wsk(r ? new T[r] : 0) {for (int i = 0; i < r ; i++) wsk[i] = zero(T());}

  vec(const T* p, const T* k): r(k-p), wsk(r ? new T[r] : 0){ for (int i = 0; i < r ; i++) wsk[i] = p[i]; }
  vec(const vec<T> & re): r(re.r), wsk(r ? new T[r] : 0){ for (int i = 0; i < r ; i++) wsk[i] = re[i]; }
  
vec<T>& operator = (const vec<T> & re)
  {
    if (this != &re) {
      delete [] wsk;
      r=re.r;
      wsk = r?new T[re.r]:0;
      for (int i = 0; i < r ; i++) 
        wsk[i] = re.wsk[i];
    } 
    return *this;
  }





int const size() {return r;} 
  T& operator [] (int i)throw (string) { 
    if(i<0) throw string("one ");
    if(i>r-1) throw string("two ");
    return wsk[i];
  }

  const T& operator [] (int i)const throw (string) {
     if(i<0) throw string("buukukuku "); 
    if(i>r-1) throw string("kukukuku ");
    return wsk[i];
  }


template <class x>
friend
ostream & operator << (ostream &, const vec<x> &);


~vec() {delete [] wsk;}
};


template <class x>
ostream & operator << (ostream & out, const vec<x> & re)
{for (int i =0 ; i < re.r; i++) out << re.wsk[i] << " ";
return out; }




int main ()
{

vec<int> t1(4);
for (int i = 0; i < t1.size(); ++i) {
  cout << t1[i];
  t1[i] = i;
}

cout << t1;
string s[] = {"Ala", "ma", "kota"};
const vec<string> s1(s, s+3);
cout << s1;
vec<int> t2(t1);
cout << t2;
vec<string> s2;
s2 = s1;
cout << s2;


return 0;



}
