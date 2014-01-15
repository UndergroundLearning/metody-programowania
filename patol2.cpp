#include <iostream>

using namespace std;

template <class typ> typ zero(typ a)
{
	return typ(0);
}

template <class typ>
class vec
{
	unsigned roz;
	typ* tab;
	public:
	vec(): roz(0), tab(0){}
	vec(const unsigned r): roz(r), tab(roz ? new typ[roz] : 0)
	{
		for(unsigned i=0; i<roz; i++)
		{
			tab[i] = zero(tab[i]);
		}
	}
	const unsigned& size() const {return roz;}
	typ& operator[](const unsigned i) {return tab[i];}
	friend ostream& operator << (ostream& out, const vec<typ>& wektor)
	{
		for(unsigned i=0; i<wektor.roz; i++)
		{
			out << wektor.tab[i] << " ";
		}
		out << endl;
		return out;
	}
	vec(const typ* b, const typ* e): roz(e-b > 0 ? e-b : 0), tab(roz ? new typ[roz] : 0)
	{
		for(unsigned i=0; i<roz; i++)
			tab[i] = b[i];
	}
	vec(const vec& drugi): roz(drugi.roz), tab(roz ? new typ[roz] : 0)
	{
		for(unsigned i=0; i<roz; i++)
			tab[i] = drugi.tab[i];
	}
	vec& operator = (const vec& drugi)
	{
		if(this!=&drugi)
		{
			roz = drugi.roz;
			tab = roz ? new typ[roz] : 0;
			for(unsigned i=0; i<roz; i++)
				tab[i] = drugi.tab[i];
		}
		return *this;
	}
	~vec(){delete[] tab;}
};

int main()
{
	vec<int> t1(4);
for (unsigned i = 0; i < t1.size(); ++i) {
std::cout << t1[i];
t1[i] = i;
}
std::cout << t1;
std::string s[] = {"Ala", "ma", "kota"};
const vec<std::string> s1(s, s+3);
std::cout << s1;
vec<int> t2(t1);
std::cout << t2;
vec<std::string> s2;
s2 = s1;
std::cout << s2;
}
