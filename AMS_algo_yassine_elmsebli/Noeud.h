
#include"Arc.h"
class Arc;
class Graphe; 
class Noeud
{
    friend Graphe;
    double id ;
    double x;
    double y;
    int degré;
    std::vector<Arc*> arc_e;
    std::vector<Arc*> arc_s;
    bool viste;
    public :
        Noeud(double id,double x,double y) ;
        void add_arc_e(Arc *e);
        void add_arc_s(Arc *s);
        void degre();
        //~Noeud() ;
        void affiche() ;
} ;