#include"Graphe.h"
int main(){
    Graphe ar("arctest.csv","nodetest.csv");
    ar.lecture_noeud();
    ar.lecture_arc();
    ar.mj_incidence();
    ar.affiche();
    
}