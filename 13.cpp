#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

template <class t1, class t2> class para
{
	t1 elem1;
	t2 elem2;
	public:
	para(): elem1(0), elem2(0){}
	para(const t1& pierwszy, const t2& drugi): elem1(pierwszy), elem2(drugi){}
	t1& elementPierwszy () {return elem1;}
	t2& elementDrugi () {return elem2;}
	const t1& elementPierwszy () const {return elem1;}
	const t2& elementDrugi () const {return elem2;}
	friend bool operator > (const para& a, const para& b)
	{
		if(a.elem2 > b.elem2)
			return true;
		else
			return false;
	}
	friend bool operator < (const para& a, const para& b)
	{
		if(a.elem2 < b.elem2)
			return true;
		else
			return false;
	}
};

template <class t1, class t2> bool wczytaj(istream& in, vector<para<t1, t2> >& tab)
{
	t1 temp1;
	t2 temp2;
	while(in >> temp1 >> temp2)
	{
		tab.push_back(para<t1, t2>(temp1, temp2));
	}
	return true;
}

template <class t1, class t2> void wyswietl(vector<para<t1, t2> > tab)
{
	for(unsigned i=0; i<tab.size(); i++)
		cout << tab[i].elementPierwszy() << " " << tab[i].elementDrugi() << endl;
}

typedef para<unsigned, unsigned> studenty;
typedef para<string, double> skoczki;

int main()
try
{
	string naz1("data1.txt"), naz2("data2.txt");
	ifstream plik1(naz1.c_str());
	if(!plik1) throw string("Blad otwarcia pliku 1");
	ifstream plik2(naz2.c_str());
	if(!plik2) throw string("Blad otwarcia pliku 2");
	vector<studenty> tab1;
	if(wczytaj(plik1, tab1))
	{
		cout << "Studenty:" << endl << endl;
		wyswietl(tab1);
		cout << endl << endl;
		sort(tab1.begin(), tab1.end(), greater<studenty>());
		cout << "Studenty po sortowaniu:" << endl << endl;
		wyswietl(tab1);
	}
	cout << endl;
	vector<skoczki> tab2;
	if(wczytaj(plik2, tab2))
	{
		cout << "Skoczki:" << endl << endl;
		wyswietl(tab2);
		cout << endl << endl;
		sort(tab2.begin(), tab2.end());
		cout << "Skoczki po sortowaniu:" << endl << endl;
		wyswietl(tab2);
	}
	plik1.close();
	plik2.close();
	return 0;
}catch(const string& err){
	cout << err << endl;
}
