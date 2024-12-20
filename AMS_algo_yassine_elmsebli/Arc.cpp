#include "Arc.h"

Arc::Arc(int id){
    this->id=id;
    this->lenght=0;
    this->type=' ';
}
Arc::Arc(int id, std::string type , bool one,int distance,bool reversed,float villed,float villea,int lanes,std::string name,int maxspeed){
    this->id=id;
    this->name=name;
    this->lenght=distance;
    this->type=type;
    this->oneway=one;
    this->lane=lanes;
    this->maxspeed=maxspeed;
    this->reversed=reversed;
    if (one)
    {
        if (reversed)
        {
            this->idvilled=villed;
            this->idvillea=villea;
        }else{
            this->idvilled=villea;
            this->idvillea=villed;
        }
        
    }
    

}
void Arc::affiche(){
    std::cout<<"id : "<<this->id<<std::endl<<"distance :"<<this->lenght<<std::endl;
}
