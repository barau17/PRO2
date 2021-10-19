/** @file Cjt_Especies.cc
    @brief Codi de la classe Cjt_Especies
*/

#include "Cjt_Especies.hh"
using namespace std;

// public

Cjt_especies::Cjt_especies() 
{
    cjt_especie = map<string, Especie>();
    taula_de_distancies = general_map();
    k = 0;
}

bool Cjt_especies::existeix_especie(string id) const
{
    map<string, Especie>::const_iterator it = cjt_especie.find(id);
    return it != cjt_especie.end();
}

void Cjt_especies::inicialitza_clusters(Cjt_Clusters& c) 
{
    c.clear_cjt_cluster();
    for (map<string, Especie>::const_iterator it = cjt_especie.begin(); it != cjt_especie.end(); ++it) {
        c.copia_cluster(it->second.consultar_identificador());
    }
    for (general_map::iterator it = taula_de_distancies.begin(); it != taula_de_distancies.end(); ++it) {
        for (dins_map::iterator itt = it->second.begin(); itt != it->second.end(); ++itt) {
            c.afegeix_distancies(it->first, itt->first, itt->second);
        }
    }
    if (not cjt_especie.empty()) {
        map<string, Especie>::const_iterator it = --cjt_especie.end();
        c.afegeix_distancia_buida(it->first);
    }
}

void Cjt_especies::obtenir_gen(string id) const 
{
    map<string, Especie>::const_iterator it = cjt_especie.find(id);
    cout << it->second.consultar_gen() << endl;
}

void Cjt_especies::crea_especie(string id, string gen)
{   
    Especie esp(id, gen);
    esp.calcular_kmers(k);
    cjt_especie.insert(make_pair(esp.consultar_identificador(), esp));
    afegeix_taula_distancies(id);
}

void Cjt_especies::elimina_especie(string id) 
{
    cjt_especie.erase(id);
    eliminar_distancia(id);
}

void Cjt_especies::taula_distancies() const 
{
    for (general_map::const_iterator it = taula_de_distancies.begin(); it != taula_de_distancies.end(); ++it) {
        cout << it->first << ':';
        for (dins_map::const_iterator itt = it->second.begin(); itt != it->second.end(); ++itt) {
            cout << ' ' << itt->first << " (" << itt->second << ")"; 
        }
        cout << endl;
    }
}

void Cjt_especies::eliminar_distancia(string id1) 
{
    taula_de_distancies.erase(id1);
    for (general_map::iterator it = taula_de_distancies.begin(); it != taula_de_distancies.end(); ++it) {
        it->second.erase(id1);
    }
}

void Cjt_especies::llegeix_cjt_especies() 
{
    int n;
    cin >> n;
    if (not cjt_especie.empty()) {
        cjt_especie.clear();
        taula_de_distancies.clear();
    }
    for (int i = 0; i < n; ++i) {
        Especie esp;
        esp.llegir();
        esp.calcular_kmers(k);
        cjt_especie.insert(make_pair(esp.consultar_identificador(), esp));
        afegeix_taula_distancies(esp.consultar_identificador());
    }
}

void Cjt_especies::afegeix_taula_distancies(string id1) 
{
    map<string, double> distin;
    taula_de_distancies.insert(make_pair(id1, distin));
    for (general_map::iterator it = taula_de_distancies.begin(); it != taula_de_distancies.end(); ++it) {
        double distance = calcular_distancia(it->first, id1);
        if (it->first < id1) it->second.insert(make_pair(id1, distance));
        else if (it->first > id1) distin.insert(make_pair(it->first, distance));
    }
    general_map::iterator it = taula_de_distancies.find(id1);
    it->second = distin;
}

void Cjt_especies::imprimeix_cjt_especies() const
{
    for (map<string, Especie>::const_iterator it = cjt_especie.begin(); it != cjt_especie.end(); ++it) {
        it->second.escriure();
    }
}

void Cjt_especies::llegir_k(int k) 
{
    this->k = k;
}

double Cjt_especies::calcular_distancia(string id1, string id2) 
{
    map<string, Especie>::iterator it = cjt_especie.find(id1);
    map<string, Especie>::iterator itt = cjt_especie.find(id2);
    return it->second.calcula_distancia(itt->second);
}

void Cjt_especies::distancia(string id1, string id2) 
{
    map<string, Especie>::iterator it = cjt_especie.find(id1);
    map<string, Especie>::iterator itt = cjt_especie.find(id2);
    if (it != cjt_especie.end()) {
        if (itt != cjt_especie.end()) {
            if (id1 < id2) {
                general_map::iterator it1 = taula_de_distancies.find(id1);
                dins_map::iterator it2 = it1->second.find(id2);
                cout << it2->second << endl;
            }
            else {
                general_map::iterator it1 = taula_de_distancies.find(id2);
                dins_map::iterator it2 = it1->second.find(id1);
                cout << it2->second << endl;
            }
        }
    }    
}