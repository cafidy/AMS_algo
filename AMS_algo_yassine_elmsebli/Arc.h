

#include<string>
#include<vector>
#include<iostream>
#include<fstream>
#include<sstream>

class Noeud;
class Graphe; 

class Arc
{
    friend Graphe;
    std::string id ;
    double idvilled;
    double idvillea;
    std::string type ;
    bool onoway;
    bool es;
    int distance ;
    
    public :
        Arc(std::string id) ;
        Arc(std::string id, std::string type , bool one,int distance,float villed,float villea);
        //~Arc() ;
        void affiche() ;

} ;