#include "Arc.h"

Arc::Arc(std::string id){
    this->id=id;
    this->distance=0;
    this->type=' ';
}
Arc::Arc(std::string id, std::string type , bool one,int distance,float villed,float villea){
    this->id=id;
    this->distance=distance;
    idvillea=villea;
    idvilled=villed;
    this->type=type;
    this->onoway=one;

}
void Arc::affiche(){
    std::cout<<"id : "<<this->id<<std::endl<<"distance :"<<this->distance<<std::endl;
}
