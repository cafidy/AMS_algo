
#include"Arc.h"
class Arc;
class Graphe; 
class Noeud
{
    friend Graphe;
    double id ;
    double x;
    double y;
    std::vector<Arc*> arc_e;
    std::vector<Arc*> arc_s;
    public :
        Noeud(double id,double x,double y) ;
        void add_arc_e(Arc *e);
        void add_arc_s(Arc *s);
        //~Noeud() ;
        void affiche() ;
} ;