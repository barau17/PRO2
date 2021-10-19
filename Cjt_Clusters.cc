/** @file Cjt_Clusters.cc
    @brief Codi de la classe Cjt_Clusters
*/

#include "Cjt_Clusters.hh"
using namespace std;

// public

Cjt_Clusters::Cjt_Clusters() { }

void Cjt_Clusters::copia_cluster(string id1) 
{
    Cluster c1(id1);
    cjt_clusters.insert(make_pair(id1, c1));
}

void Cjt_Clusters::clear_cjt_cluster() 
{
    cjt_clusters.clear();
    nova_taula_distancies.clear();
    cjt_clusters = map<string, Cluster>();
    nova_taula_distancies = map<string, map<string, double>>();
}

void Cjt_Clusters::executa_pas_wpgma() 
{
    map<string, map<string, double>>::const_iterator it = nova_taula_distancies.begin();
    map<string, double>::const_iterator itt = it->second.begin();
    double distmin = 101.00; // max distance
    string id1 = it->first, id2 = itt->first;
    while (it != nova_taula_distancies.end()) {
        map<string, double>::const_iterator ittt = it->second.begin();
        while (ittt != it->second.end()) {
            if (ittt->second < distmin) {
                distmin = ittt->second;
                id1 = it->first;
                id2 = ittt->first;
            }
            ++ittt;
        }
        ++it;
    }
    Cluster a = cjt_clusters.find(id1)->second;
    Cluster b = cjt_clusters.find(id2)->second;

    Cluster total;
    total.unio(a, b, distmin);

    afegeix_cluster_a_taula(total, id1, id2);

    cjt_clusters.insert(make_pair(total.consultar_identificador_cluster(), total));
    
    cjt_clusters.erase(id1);
    cjt_clusters.erase(id2);
}

void Cjt_Clusters::afegeix_cluster_a_taula(Cluster& c1, string& id1, string& id2) 
{
    string idfinal = c1.consultar_identificador_cluster();
    double distance;
    map<string, double> inner;
    map<string, map<string, double>>::iterator it = nova_taula_distancies.begin();
    while (it->first < id2) {
        if (it->first > id1) {
            it->second.erase(id1);
            it->second.erase(id2);
        }
        else if (it->first < id1) {
            map<string, double>::iterator it1 = it->second.find(id1);
            map<string, double>::iterator it2 = it->second.find(id2);
            distance = (it1->second + it2->second)/2;
            it->second.insert(make_pair(idfinal, distance));
            it->second.erase(id1);
            it->second.erase(id2); 
        }
        else {
            for (map<string, double>::iterator it3 = it->second.begin(); it3 != it->second.end(); ++it3) {
                if (it3->first < id2) {
                    map<string, map<string, double>>::iterator it4 = nova_taula_distancies.find(it3->first);
                    map<string, double>::iterator it5 = it4->second.find(id2);
                    distance = (it5->second + it3->second)/2;
                    inner.insert(make_pair(it3->first, distance));
                }
                else if (it3->first > id2) {
                    map<string, map<string, double>>::iterator it6 = nova_taula_distancies.find(id2);
                    map<string, double>::iterator it7 = it6->second.find(it3->first);
                    distance = (it3->second + it7->second)/2;
                    inner.insert(make_pair(it3->first, distance));
                }
            }
        }
        ++it;
    }
    nova_taula_distancies.insert(make_pair(idfinal, inner));
    nova_taula_distancies.erase(id1);
    nova_taula_distancies.erase(id2);
}

void Cjt_Clusters::imprimeix_taula_distancia() 
{
   for (map<string, map<string, double> >::iterator it = nova_taula_distancies.begin(); it != nova_taula_distancies.end(); ++it) {
        cout << it->first << ':';
        for (map<string, double>::iterator itt = it->second.begin(); itt != it->second.end(); ++itt) {
            cout << ' ' << itt->first << " (" << itt->second << ")"; 
        }
        cout << endl;
    }
}


void Cjt_Clusters::afegeix_distancies(const string& id1, const string& id2, const double& distancia) 
{
    map<string, map<string, double> >::iterator it = nova_taula_distancies.find(id1);
    if (it != nova_taula_distancies.end()) {
        it->second.insert(make_pair(id2, distancia));
    }
    else {
        map<string, double> inner;
        inner.insert(make_pair(id2, distancia));
        nova_taula_distancies.insert(make_pair(id1, inner));
    }
}


bool Cjt_Clusters::existeix_cluster(string id1) 
{
    map<string, Cluster>::const_iterator it = cjt_clusters.find(id1);
    return it != cjt_clusters.end();
}

int Cjt_Clusters::conjunt_cluster_size() 
{
    return cjt_clusters.size();
}


void Cjt_Clusters::imprimeix_cluster(string id1) 
{
    map<string, Cluster>::iterator it = cjt_clusters.find(id1);
    it->second.escriure_cluster();
}

void Cjt_Clusters::imprimeix_arbre_filogenetic() 
{
    while (cjt_clusters.size() > 1) {
        executa_pas_wpgma();
    }
    map<string, Cluster>::iterator it = cjt_clusters.begin();
    it->second.escriure_cluster();
}

void Cjt_Clusters::afegeix_distancia_buida(const string& id1) 
{
    map<string, double> nothing;
    nova_taula_distancies.insert(make_pair(id1, nothing));
}