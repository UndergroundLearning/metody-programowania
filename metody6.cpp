#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

class point
{
	double x, y;
	point(): x(0), y(0){};
	double odleglosc(const point& drugi)
	{
		return sqrt((x-drugi.x)*(x-drugi.x)+(y-drugi.y)*(y-drugi.y));
	}
	friend class polygon;
};

class polygon
{
	unsigned liczbaWezlow;
	point* tabxy;
	unsigned* order;
	public:
	polygon(): liczbaWezlow(0), tabxy(0), order(0){};
	polygon(const polygon& drugi): liczbaWezlow(drugi.liczbaWezlow), tabxy(new point(*drugi.tabxy)), order(new unsigned(*drugi.order)){}
	polygon& operator =(const polygon&);
	~polygon()
	{
		liczbaWezlow = 0;
		delete [] tabxy;
		delete [] order;
	}
	bool read(ifstream&);
	const double obwod() const
	{
		double tmp(0);
		for(unsigned i=0; i<liczbaWezlow - 1; i++)
			tmp+=tabxy[order[i]-1].odleglosc(tabxy[order[i+1]-1]);
		tmp+=tabxy[order[0]].odleglosc(tabxy[order[liczbaWezlow-1]]);
		return tmp;
	}
	const double pole() const
	{
		double tmp(0);
		for(unsigned i=0; i<liczbaWezlow - 1; i++)
			tmp+=tabxy[order[i]-1].x*tabxy[order[i+1]-1].y - tabxy[order[i+1]-1].x*tabxy[order[i]-1].y;
		return tmp/2;
	}
};

polygon& polygon::operator =(const polygon& drugi)
{
	if(this!=&drugi)
	{
		liczbaWezlow = drugi.liczbaWezlow;
		*tabxy = *drugi.tabxy;
		*order = *drugi.order;
		return *this;
	}
	else
		return *this;
}

bool polygon::read(ifstream& plik)
{
	string line;
	unsigned n(0);
	try
	{
		getline(plik, line);
		n++;
		if(line!="[POLYGON]" && line!="[polygon]") throw string("Blad w naglowku [POLYGON]."); cout << line << endl;
		getline(plik, line);
		n++;
		if(line!="[NUMBER OF NODES]" && line!="[number of nodes]") throw string("Blad w naglowku [NUMBER OF NODES]."); cout << line << endl;
		plik >> liczbaWezlow;
		n++;
		if(!plik.good()) throw string("Blad we wczytywaniu liczby wezlow."); cout << liczbaWezlow << endl;
		getline(plik, line);
		getline(plik, line);
		n++;
		if(line!="[NODES]" && line!="[nodes]") throw string("Blad w naglowku [NODES]."); cout << line << endl;
		tabxy = new point[liczbaWezlow];
		order = new unsigned[liczbaWezlow];
		unsigned lp(0);
		n++;
		for(unsigned i=0; i<liczbaWezlow; i++)
		{
			plik >> lp;
			if(!plik.good()) throw string("Blad we wczytywaniu liczby porzadkowej."); cout << lp << " ";
			plik >> tabxy[lp-1].x;
			if(!plik.good()) throw string("Blad we wczytywaniu zmiennej x."); cout << tabxy[lp-1].x << " ";
			plik >> tabxy[lp-1].y;
			if(!plik.good()) throw string("Blad we wczytywaniu zmiennej y."); cout << tabxy[lp-1].y << endl;
			n++;
		}
		getline(plik, line);
		getline(plik, line);
		n++;
		if(line!="[POLYGON]" && line!="[polygon]") throw string("Blad w naglowku [POLYGON]."); cout << line << endl;
		n++;
		for(unsigned i=0; i<liczbaWezlow; i++)
		{
			plik >> order[i];
			if(!plik.good()) throw string("Blad we wczytywaniu kolejnosci wezlow."); cout << order[i] << " ";
		}
		cout << endl;
		return true;
	}
	catch(string blad)
	{
		cerr << blad << " Linia: " << n << endl;
		return false;
	}
}

int main(int argc, char* argv[])
try{
	string name;
	try
	{
		if(argc!=2) throw int(1);
		else
		name = argv[1];
		if(name.substr(name.size()-3) != "txt") throw int(2);
	}
	catch(int a)
	{
		switch(a)
		{
			case 1:
				cerr << "Brak nazwy pliku wejsciowego w argumentach wywolania." << endl;
				cerr << "Podaj nazwe pliku: ";
				cin >> name;
				if(name.substr(name.size()-3) == "txt")
					break;
				else
			case 2:
				cerr << "Zle rozszerzenie pliku wejsciowego." << endl;
				do
				{
					cerr << "Podaj nazwe pliku z prawidlowym rozszerzeniem: ";
					cin >> name;
				}
				while(name.substr(name.size()-3) != "txt");
		}
	}
	ifstream plik(name.c_str());
	try
	{
		if(!plik.good()) throw int(1);
		polygon wielobok;
		if(!wielobok.read(plik)) throw int(2);
		cout << endl;
		cout << "Obwod tego wielokata wynosi: " << wielobok.obwod() << endl;
		cout << "Pole tego wielokata wynosi: " << wielobok.pole() << endl;	
		plik.close();
	}
	catch(int a)
	{
		switch(a)
		{
			case 1:
				cerr << "Nie mozna otworzyc pliku." << endl;
				plik.ignore();
				plik.clear();
				plik.close();
				break;
			case 2:
				cerr << "Blad wczytywania pliku." << endl;
				plik.ignore();
				plik.clear();
				plik.close();
				break;
		}
	}
	
	return 0;
}
catch(...)
{
	cerr << "Nieznany blad" << endl;
}

//P.S Walcie sie ! <3
//fakaj bąka A.G. :P
