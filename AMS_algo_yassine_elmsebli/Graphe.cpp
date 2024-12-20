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

  
            std::string name = "";
            std::string highway = "";
            double length = 0.0;
            bool oneway = false;
            bool reversed = false;
            int id = 0;
            int lanes = 0;
            int maxspeed = 0;

         
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
                    try {
                        value = std::stod(json.substr(start, end - start));
                    } catch (...) {
                        value = 0.0; 
                    }
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

            auto extractIntField = [](const std::string& json, const std::string& key, int& value) {
                size_t pos = json.find("'" + key + "': ");
                if (pos != std::string::npos) {
                    size_t start = pos + key.length() + 4;
                    size_t end = json.find(",", start);
                    try {
                        value = std::stoi(json.substr(start, end - start));
                    } catch (...) {
                        value = 0; 
                    }
                }
            };

            extractField(jsonField, "name", name);
            extractField(jsonField, "highway", highway);
            extractDoubleField(jsonField, "length", length);
            extractBoolField(jsonField, "oneway", oneway);
            extractBoolField(jsonField, "reversed", reversed);
            extractIntField(jsonField, "lanes", lanes);
            extractIntField(jsonField, "osmid", id);
            extractIntField(jsonField, "maxspeed", maxspeed);

            if (maxspeed == 0) {
                int counter = 0;
                int somme = 0;
                for (const auto& routeArc : route) {
                    if (routeArc->name == name) {
                        counter++;
                        somme += routeArc->maxspeed;
                    }
                }
                if (somme == 0 || counter == 0) {
                    maxspeed = 0;
                } else {
                    maxspeed = somme / counter;
                }
            }

            double vd = std::stod(first);
            double va = std::stod(second);
            Arc* nv = new Arc(id, highway, oneway, length, reversed, vd, va, lanes, name, maxspeed);
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
            if (route[j]->idvillea==ville[i]->id)
            {
                if (route[j]->oneway)
                {
                    ville[i]->add_arc_e(route[j]);
                }else{
                    ville[i]->add_arc_e(route[j]);
                    ville[i]->add_arc_s(route[j]);
                }
                
            }else if (route[j]->idvilled==ville[i]->id)
            {
                if (route[j]->oneway)
                {
                    ville[i]->add_arc_s(route[j]);
                }else{
                    ville[i]->add_arc_e(route[j]);
                    ville[i]->add_arc_s(route[j]);
                }
                
            }
            
        }
        
    }
    
}
void Graphe::degre(int n){
    Noeud * best;
    int n1;
    for (int i = 0; i < sizeof(ville); i++)
    {
        best=ville[i];
        best->degre();
        if (n1<n)
        {
            for (int j = 0; j < sizeof(ville)-n1; j++)
            {
                ville[j]->degre();
                if (ville[j]->degré>best->degré)
                {
                    best=ville[j];
                }
                
            }
        }else{
            break;
        }
        std::cout<<"plus au degre :"<<best->id;

    }
    
}
int Graphe::parcours(int id_depart,int id_arrive) {
        std::vector<Noeud*> pile;
        
        Noeud* arrive=nullptr;
        Noeud* depart = nullptr;
        for(Noeud* n : ville) {
            n->viste = false;
            if(n->id == id_depart) depart = n;
            if(n->id == id_arrive) arrive = n;
        }
        
        if(!depart) return 0;
        
        pile.push_back(depart);
        
        while(!pile.empty()) {
            Noeud* current = pile.back();
            pile.pop_back();
            
            if(!current->viste) {
                current->viste = true;
                current->affiche();
                
                
                for(Arc* arc : current->arc_s) {
                    Noeud *villea ;
                    for(Noeud * n:ville){
                        if (arc->idvillea==n->id)
                        {
                            villea=n;
                            break;
                        }
                        
                    }
                    if(!villea->viste) {
                        pile.push_back(villea);
                    }
                }
            }
        }
        return 1;
    }
int Graphe::parcours_pluscour(int iddepart, int idarrive) {
    // Réinitialiser les visites
    for (Noeud* n : ville) {
        n->viste = false;
    }
    
    // File pour le parcours en largeur
    std::queue<Noeud*> file;
    
    // Tableau pour stocker les prédécesseurs et les arcs empruntés
    std::vector<Noeud*> predecesseur(ville.size(), nullptr);
    std::vector<Arc*> arc_utilise(ville.size(), nullptr);
    
    // Trouver les noeuds de départ et d'arrivée
    Noeud *depart = nullptr;
    Noeud *arrivee = nullptr;
    
    for (Noeud* n : ville) {
        if (n->id == iddepart) depart = n;
        if (n->id == idarrive) arrivee = n;
    }
    
    // Vérifier que les noeuds existent
    if (!depart || !arrivee) {
        std::cout << "Départ ou arrivée non trouvé" << std::endl;
        return 0;
    }
    
    // Initialiser le parcours
    file.push(depart);
    depart->viste = true;
    
    bool trouve = false;
    while (!file.empty() && !trouve) {
        Noeud* courant = file.front();
        file.pop();
        
        // Parcourir les arcs sortants
        for (Arc* arc : courant->arc_s) {
            // Trouver le noeud d'arrivée de l'arc
            Noeud* suivant = nullptr;
            for (Noeud* n : ville) {
                if (n->id == arc->idvillea) {
                    suivant = n;
                    break;
                }
            }
            
            if (suivant && !suivant->viste) {
                file.push(suivant);
                suivant->viste = true;
                
                // Enregistrer le prédécesseur et l'arc
                for (size_t i = 0; i < ville.size(); i++) {
                    if (ville[i] == suivant) {
                        predecesseur[i] = courant;
                        arc_utilise[i] = arc;
                        break;
                    }
                }
                
                // Si on a trouvé l'arrivée
                if (suivant == arrivee) {
                    trouve = true;
                    break;
                }
            }
        }
    }
    
    // Si aucun chemin n'a été trouvé
    if (!trouve) {
        std::cout << "Aucun chemin trouvé entre " << iddepart << " et " << idarrive << std::endl;
        return 0;
    }
    
    // Reconstruire le chemin
    std::vector<Arc*> chemin;
    Noeud* noeud_courant = arrivee;
    
    while (noeud_courant != depart) {
        int index = 0;
        for (size_t i = 0; i < ville.size(); i++) {
            if (ville[i] == noeud_courant) {
                index = i;
                break;
            }
        }
        
        chemin.insert(chemin.begin(), arc_utilise[index]);
        noeud_courant = predecesseur[index];
    }
    
    // Afficher le chemin
    std::cout << "Chemin trouvé (" << chemin.size() << " arcs):" << std::endl;
    std::cout << "Départ: " << depart->id;
    
    for (Arc* arc : chemin) {
        std::cout << " -> " << arc->name << " -> " << arc->idvillea;
    }
    std::cout << std::endl;
    
    return chemin.size();
}
void Graphe::find(double vd,double va){
    for(Arc *ar : route){
        if (ar->idvillea==va && ar->idvilled==vd)
        {
            ar->affiche();
        }
        
    }    
}