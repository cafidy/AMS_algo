
#include"Noeud.h"

class Noeud ;
class Arc ;

class Graphe
{
    std::vector<Noeud*> ville;
    std::vector<Arc*> route;
    int nnoeud;
    int narc;
    std::string file_arc;
    std::string file_noeud;
    public:
        Graphe(std::string file_arc,std::string fie_noeud);
        //~Graphe();
        void affiche();
        int lecture_arc();
        int lecture_noeud();
        void mj_incidence();
        void degre(int n);
        int parcours(int iddepart,int idarrive);
        int parcours_pluscour(int iddepart, int idarrive);
        void find(double id_vd,double id_va);
} ;