/** @file Cluster.cc
    @brief Codi de la classe Cluster
*/

#include "Cluster.hh"
using namespace std;

// private

void Cluster::escriure_cluster_arbre(const BinTree<pair<string, double>>& filo) const
{
    if (not filo.left().empty()) {
        cout << '[' << '(' << filo.value().first << ", " << filo.value().second << ") ";
        escriure_cluster_arbre(filo.left());
        escriure_cluster_arbre(filo.right());
        cout << ']';
    }
    else cout << '[' << filo.value().first << ']';
}

// public

Cluster::Cluster() 
{
    cluster = BinTree<pair<string, double> >();
}

Cluster::Cluster(string &id1) 
{
    cluster = BinTree<pair<string, double> >(make_pair(id1, 0.00));
}

void Cluster::unio(Cluster& c1, Cluster& c2, double& distance)
{
    string idfinal = c1.consultar_identificador_cluster() + c2.consultar_identificador_cluster();
    cluster = BinTree<pair<string, double>>(make_pair(idfinal, distance/2), c1.cluster, c2.cluster);
}

void Cluster::escriure_cluster()
{
    escriure_cluster_arbre(cluster);
}

string Cluster::consultar_identificador_cluster() 
{
    return cluster.value().first;
}