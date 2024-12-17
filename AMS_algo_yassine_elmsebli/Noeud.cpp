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

}
