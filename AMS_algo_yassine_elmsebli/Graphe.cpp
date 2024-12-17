#include "Graphe.h"


Graphe::Graphe(std::string file_arc,std::string file_noeud){
    this->file_arc=file_arc;
    this->file_noeud=file_noeud;
}

void Graphe::affiche(){

    for (int i = 0; i < sizeof(ville)-1; i++)
    {
        ville[i]->affiche();
    }
    
}

int Graphe::lecture_arc() {
    std::ifstream file(file_arc);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file!" << std::endl;
        return 0;
    }

    int number = 0;
    std::string line;
    while (std::getline(file, line)) {
        try {
            if (line.empty() || line.length() > 2000) {
                std::cerr << "Skipping invalid or overly large line." << std::endl;
                continue;
            }

            std::istringstream lineStream(line);
            std::string first, second, jsonField;

            std::getline(lineStream, first, ',');
            std::getline(lineStream, second, ',');
            std::getline(lineStream, jsonField);

            std::string name, highway;
            double length = 0.0;
            bool oneway = false;

            auto extractField = [](const std::string& json, const std::string& key, std::string& value) {
                size_t pos = json.find("'" + key + "': ");
                if (pos != std::string::npos) {
                    size_t start = json.find("'", pos + key.length() + 4) + 1;
                    size_t end = json.find("'", start);
                    value = json.substr(start, end - start);
                }
            };

            auto extractDoubleField = [](const std::string& json, const std::string& key, double& value) {
                size_t pos = json.find("'" + key + "': ");
                if (pos != std::string::npos) {
                    size_t start = pos + key.length() + 4;
                    size_t end = json.find(",", start);
                    value = std::stod(json.substr(start, end - start));
                }
            };

            auto extractBoolField = [](const std::string& json, const std::string& key, bool& value) {
                size_t pos = json.find("'" + key + "': ");
                if (pos != std::string::npos) {
                    size_t start = pos + key.length() + 4;
                    size_t end = json.find(",", start);
                    std::string boolStr = json.substr(start, end - start);
                    value = (boolStr == "True");
                }
            };

            extractField(jsonField, "name", name);
            extractField(jsonField, "highway", highway);
            extractDoubleField(jsonField, "length", length);
            extractBoolField(jsonField, "oneway", oneway);

            double vd=std::stod(first);
            double va=std::stod(second);
            Arc* nv = new Arc(name, highway, oneway, length,vd,va);
            route.push_back(nv);

            number++;

        } catch (const std::exception& e) {
            std::cerr << "Error parsing line: " << e.what() << std::endl;
        }
    }

    file.close();
    return number;
}
int Graphe::lecture_noeud(){
        std::ifstream file(file_noeud);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file!" << std::endl;
        return 0;
    }

    int number = 0;
    std::string line;
    while (std::getline(file, line)) {
        try {

            if (line.empty() || line.length() > 2000) {
                std::cerr << "Skipping invalid or overly large line." << std::endl;
                continue;
            }

            std::istringstream lineStream(line);
            std::string first,jsonField;

            std::getline(lineStream, first, ',');
            std::getline(lineStream, jsonField);

            double x,y;



            auto extractxField = [](const std::string& json, const std::string& key, double& value) {
                size_t pos = json.find("'" + key + "': ");
                if (pos != std::string::npos) {
                    size_t start = pos + key.length() + 4;
                    size_t end = json.find(",", start);
                    value = std::stod(json.substr(start, end - start));
                }
            };
            auto extractyField = [](const std::string& json, const std::string& key, double& value) {
                size_t pos = json.find("'" + key + "': ");
                if (pos != std::string::npos) {
                    size_t start = pos + key.length() + 4;
                    size_t end = json.find(",", start);
                    value = std::stod(json.substr(start, end - start));
                }
            };

            extractxField(jsonField,"x",x);
            extractxField(jsonField,"y",y);
            
            double id=std::stod(first);
            Noeud* nf=new Noeud(id,x,y);
            ville.push_back(nf);
            number++;

        } catch (const std::exception& e) {
            std::cerr << "Error parsing line: " << e.what() << std::endl;
        }
    }

    file.close();
    return number;
}
void Graphe::mj_incidence(){
    for (int i = 0; i < sizeof(ville); i++)
    {
        for (int j = 0; j < sizeof(route); j++)
        {
            if (ville[i]->id==route[j]->idvillea)
            {
                if (route[j]->onoway!=true)
                {
                    ville[i]->add_arc_e(route[j]);
                    ville[i]->add_arc_s(route[j]);
                }else{
                    ville[i]->add_arc_e(route[i]);
                }

            }else if (ville[i]->id==route[j]->idvilled)
            {
                    if (route[j]->onoway!=true)
                    {
                        ville[i]->add_arc_e(route[j]);
                        ville[i]->add_arc_s(route[j]);
                    }else{
                        ville[i]->add_arc_s(route[i]);
                    }
            }
        }
        
    }
    
}