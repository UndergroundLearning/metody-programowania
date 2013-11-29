#include <iostream>

using namespace std;

class figura{
	protected:
		string *kol;
	public:
 		figura():kol(new string ("brak")){}
 		figura(const string &k):kol(new string(k)){}

  		string &kolor(){return *kol;}
  		const string &kolor()const{return *kol;}
  	 
 	 	ostream &wypisz(ostream &out=cout) const{
    		out<<*kol<<" ";
    		return out;}

  virtual double pole()const=0;
  virtual ~figura(){delete kol;}
};



ostream &operator<<(ostream &out, const figura &o){return o.wypisz(out);}





class kolo: public figura{
	private:
  		int r;
	public:
  		kolo():r(0){}
  		kolo(const string &ko, int pr):figura(ko),r(pr){}

  		int &promien(){return r;}
  		const int &promien()const{return r;}

  		double pole()const{return (3.14*(r*r));}
  		ostream &wypisz(ostream &out=cout)const{
                        figura::wypisz();
                        out<<r<<" "<<pole();
                        return out;}

  //~kolo(){}
};


class prost:public figura{
      protected:
               int a,b;
      public:
               prost():a(0),b(0){}
               prost(const string &ko, int p1, int p2):figura(ko),a(p1),b(p2){}

               int &bok1()      {return a;}
            	const int &bok1()const {return a;}

               int &bok2()     {return b;}
               const int &bok2()const{return b;}

               double pole()const{return (a*b);}

               ostream &wypisz(ostream &out=cout)const{
                     figura::wypisz();
                     out<<a<<" "<<b<<" "<<pole();
                     return out;}

        //    ~prost(){}
};


class prostop:public prost{
      private:
		int h;
      public:
      		prostop():h(0){}
      		prostop(const string &ko, int p1, int p2,int p3):prost(ko,p1,p2),h(p3){}

        	int &wysokosc(){return h;}
        	const int &wysokosc()const {return h;}

        	double pole()const{return (2*a*b+2*b*h+2*a*h);}

        	ostream &wypisz(ostream &out=cout)const{
                  	figura::wypisz();
                  	out<<a<<" "<<b<<" "<<" "<<h<<" "<<pole();
                  	return out;}


       //     ~prostop(){}
};


int main()
{
    figura *tab[5];
    const kolo test1("czarny",100);
    const prostop test2("szary",2,2,2);
    tab[0]=new kolo("czerwony",1);
    tab[1]=new kolo;
    tab[2]=new prost("niebieski",1,1);
    tab[3]=new prostop("zielony",1,1,1);
    tab[4]=new prostop;
    for (int i=0; i<5; ++i)
    cout << tab[i]->pole() << endl ;
    cout << "******* 3 *******" << endl;


    for(int i=0;i<5;++i)
    cout<< *tab[i]<<tab[i]->pole()<<endl;



return 0;
}

