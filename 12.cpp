#include <iostream>

using namespace std;

template <class T> T zero(T a)
{
	return T(0);
}

template <class T>
class vec
{
	unsigned roz;
	T* tab;
	public:
	vec(): roz(0), tab(0){}
	vec(const unsigned rozmiar): roz(rozmiar), tab(roz ? new T[roz] : 0)
	{
		for(unsigned i=0; i<roz; i++)
			tab[i] = zero(tab[i]);
	}
	vec(const T* b, const T* e): roz(e-b > 0 ? e-b : 0), tab(roz ? new T[roz] : 0)
	{
		for(unsigned i=0; i<roz; i++)
			tab[i] = b[i];
	}
	vec(const vec& drugi): roz(drugi.roz), tab(roz ? new T[roz] : 0)
	{
		for(unsigned i=0; i<roz; i++)
			tab[i] = drugi.tab[i];
	}
	const unsigned size() const {return roz;}
	T& operator[](const unsigned i){return tab[i];}
	friend ostream& operator << (ostream& out, const vec<T>& wektor)
	{
		for(unsigned i=0; i<wektor.roz; i++)
			out << wektor.tab[i] << " ";
		out << endl;
		return out;
	}
	vec& operator=(const vec& drugi)
	{
		if(this!=&drugi)
		{
			roz = drugi.roz;
			tab = roz ? new T[roz] : 0;
			for(unsigned i=0; i<roz; i++)
				tab[i] = drugi.tab[i];
		}
		return *this;
	}
	~vec(){delete[] tab; cout << "Destruktor!" << endl;}
};

int main()
{
	vec<int> t1(4); 
	for (unsigned i = 0; i < t1.size(); ++i) { 
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
}
