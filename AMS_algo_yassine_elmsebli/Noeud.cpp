#include "Noeud.h"

Noeud::Noeud(double id,double x , double y){
    this->id=id;
    this->x=x;
    this->y=y;
}
void Noeud::add_arc_e(Arc *e){
    arc_e.push_back(e);
}
void Noeud::add_arc_s(Arc *s){
    arc_s.push_back(s);
}
void Noeud::affiche(){
    std::cout<<"id ville :"<<this->id<<std::endl;
    
    if (sizeof(arc_e)>0)
    {
        for (int i = 0; i < arc_e.size(); i++)
        {
            arc_e[i]->affiche();
        }
    }
    if (sizeof(arc_s)>0)
    {
        for (int i = 0; i < arc_s.size(); i++)
        {
            arc_s[i]->affiche();
        }
    }
}
void Noeud::degre(){
    std::vector<Arc*>arc;
    bool unique=true;
    int cpt;
    for (int i = 0; i < sizeof(arc_e); i++)
    {
        for (int j = 0; j < sizeof(arc); j++)
        {
            if (arc[j]==arc_e[i])
            {
                unique=false;
            }
            
        }
        if (unique)
        {
            arc.push_back(arc_e[i]);
            cpt++;
        }
        
    }
    for (int i = 0; i < sizeof(arc_s); i++)
    {
        for (int j = 0; j < sizeof(arc); j++)
        {
            if (arc[j]==arc_s[i])
            {
                unique=false;
            }
            
        }
        if (unique)
        {
            arc.push_back(arc_s[i]);
            cpt++;
        }
        
    }
    degré=cpt;
}