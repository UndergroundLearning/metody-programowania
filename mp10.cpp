#include<iostream>

using namespace std;

class operacja{
	protected:
		string naz;
 		unsigned licz;
  	public:
		operacja(): naz("0"), licz(0){}
  		operacja(const string &n, unsigned l): naz(n), licz(l){}

  		unsigned & liczba() {return licz;}
   		string & nazwa() { return naz;}

   		const unsigned & liczba() const {return licz;}
   		const string & nazwa() const {return naz;}
};

ostream& operator<< (ostream& out, const operacja& r){return out<< r.nazwa()<< "  " << r.liczba();}

class robot{
	protected:
		unsigned l;
 	public:
  		robot():l(0){}
   		robot(unsigned n):l(n){}
    		
		virtual void praca() const=0;
   		virtual ~robot(){};
};

class podajnik: public robot{
	public:
		podajnik(){}
		podajnik(unsigned n): robot(n){}
		void praca() const {cout << "Prace wykonal podajnik nr: " << l << endl;}
};

class robot1r: public robot{
	protected:
		unsigned l;
		operacja * tab;
	public:
		robot1r():l(0),tab(0){}

		robot1r(unsigned n, const operacja*p, const operacja *k): robot(n), l(k-p), tab(l? new operacja[l]:0)
		{for(unsigned i=0;i<l;i++) tab[i]=p[i];}
  
		robot1r(const robot1r &r): robot(r), l(r.l), tab(r.l? new operacja[r.l]:0)
  		{for(unsigned i=0;i<r.l;i++) tab[i]=r.tab[i];}

		robot1r & operator= (const robot1r &r){if(this != &r){delete [] tab; l=r.l; tab=r.l? new operacja[r.l]:0;
    		{for(unsigned i=0;i<r.l;i++) tab[i]=r.tab[i];}}return * this;}
  
		void praca() const{cout << "prace wykonal robot1r nr:" << l << endl; for(unsigned i=0;i<l;i++) cout << tab[i] << endl;}

	~robot1r(){delete [] tab;}
};

class robot2r: public robot1r{
	protected:
		unsigned l2;
		operacja * tab2;
	public:
		robot2r():l2(0),tab2(0){}
		robot2r(unsigned n, const operacja*p, const operacja *k, const
		operacja*p2, const operacja *k2): robot1r(n,p,k), l2(k2-p2), tab2(l2?
		new operacja[l2]:0) {for(unsigned i=0;i<l2;i++) tab2[i]=p2[i];}
   		robot2r(const robot2r &r): robot1r(r), l2(r.l2), tab2(r.l2? new operacja[r.l2]:0) {for(unsigned i=0;i<r.l2;i++) tab2[i]=r.tab2[i];}

   		robot2r & operator= (const robot2r &r){if(this != &r)
   		robot1r::operator=(r); {delete [] tab2; l2=r.l2; tab2=r.l2? new operacja[r.l2]:0; {for(unsigned i=0;i<r.l2;i++) tab2[i]=r.tab2[i];}}return * this;}


		void praca() const {cout << "prace wykonal robot2r nr:" << l << endl;
   			for(unsigned i=0;i<l;i++) cout << tab[i] << endl;
    			for(unsigned i=0;i<l2;i++) cout << tab2[i] << endl;}

	~robot2r(){delete [] tab2;}
};



/*

void wykonaj(robot** p, robot** k){

  for(unsigned i=0;i<k-p;i++)
    p[i]->praca();
}

*/



int main(){




operacja o[] = {
operacja("w lewo", 12), operacja("obrot", 8),
operacja("w gore", 32), operacja("obrot", 10),
operacja("w prawo", 5), operacja("w dol", 25),
operacja("obrot", 32), operacja("w gore", 21),
operacja("obrot", 11), operacja("w prawo", 6)
};

robot* linia[] = {
new podajnik(0), new robot1R(1, o, o+3),
new podajnik(2), new robot2R(3, o+2, o+5, o+3, o+6),
new podajnik(4), new robot2R(5, o, o+4, o+2, o+6),
new podajnik(6), new robot1R(7, o+7, o+10),
new podajnik(8)
};





//wykonaj(linia, linia+9);



return 0;
}
