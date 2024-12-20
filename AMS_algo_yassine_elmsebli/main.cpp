#include"Graphe.h"
int main(){
    Graphe ar("arctest.csv","nodetest.csv");
    ar.lecture_noeud();
    ar.lecture_arc();
    ar.find(152376.0,152380.0);
    
}