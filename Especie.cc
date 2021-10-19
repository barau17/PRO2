/** @file Especie.cc
    @brief Codi de la classe Especie
*/

#include "Especie.hh"
using namespace std;

//public

Especie::Especie() 
{
    id = "";
    gen = "";
    tgen = false;
}

Especie::Especie(string id, string gen) 
{
    this->id = id;
    this->gen = gen;
    tgen = true;
}

string Especie::consultar_identificador() const
{
    return id;
}

string Especie::consultar_gen() const 
{
    return gen;
}

bool Especie::te_gen() const 
{
    return tgen;
}

map<string, int> Especie::consultar_kmers() const 
{
    return kmers;
}

void Especie::llegir() 
{
    cin >> id >> gen;
    tgen = true;
}

void Especie::escriure() const
{
    cout << id << ' ' << gen << endl;
}

void Especie::calcular_kmers(int k)
{
    string gen_total = gen;
    string::iterator it = gen_total.begin();
    while (it != gen_total.end() && gen_total.size() >= k) {
        string kmer = gen_total.substr(0, k);
        gen_total = gen_total.substr(1, gen_total.length());
        map<string, int>::iterator itt = kmers.find(kmer);
        if (itt != kmers.end()) {
            itt->second += 1;
        }
        else {
            kmers.insert(make_pair(kmer, 1));
        }
        it = gen_total.begin();
    }
} 

double Especie::calcula_distancia(const Especie& e2) 
{
    double equal_kmers = 0;
    double total_kmers = 0;
    map<string, int>::const_iterator it = kmers.begin();
    map<string, int>::const_iterator itt = e2.kmers.begin();
    while (it != kmers.end() && itt != e2.kmers.end()) {
        if (it->first == itt->first) {
            if (it->second <= itt->second) {
                equal_kmers += it->second;
                total_kmers += itt->second;
            }
            else {
                equal_kmers += itt->second;
                total_kmers += it->second;
            }
            ++it;
            ++itt;
        }
        else if (it->first < itt->first) {
            total_kmers += it->second;
            ++it;
        }
        else if (itt->first < it->first) {
            total_kmers += itt->second;
            ++itt;
        }
    }
    while (it != kmers.end()) {
        total_kmers += it->second;
        ++it;
    }
    while (itt != e2.kmers.end()) {
        total_kmers += itt->second;
        ++itt;
    }
    double distancia = (1.0-(equal_kmers/total_kmers))*100.0;
    return distancia;
}