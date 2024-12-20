

#include<string>
#include<vector>
#include<iostream>
#include<fstream>
#include<sstream>
#include<queue>

class Noeud;
class Graphe; 

class Arc
{
    friend Graphe;
    int id ;
    bool oneway;
    int lane;
    std::string name;
    std::string type ;
    bool reversed;
    bool lenght ;
    int maxspeed;

    double idvilled;
    double idvillea;
    public :
        Arc(int id) ;
        Arc(int id, std::string type , bool one,int distance,bool reversed,float villed,float villea,int lanes,std::string name,int maxspeed);
        //~Arc() ;
        void affiche() ;

} ;