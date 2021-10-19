/** @mainpage Gestió i creació d'un arbre filogenètic
 * 
 *  En el mòdul program.cc es troba el programa principal.
    
	Per l'aplicació a un estudi d'especies, necesitarem un mòdul
	per representar els Clusters, un altre per les Especies, a més de dos mòduls per a
	cada conjunt d'aquests, Cjt_especies i Cjt_Clusters. 

*/

/** @file program.cc
    
    @brief Programa principal
    
    <em>Aplicació per a la construcció d'un arbre filogenètic</em>
 */

#include "Cjt_Especies.hh"
#include "Cjt_Clusters.hh"

#ifndef NO_DIAGRAM
#include <iostream>
using namespace std;
#endif

/** @brief Programa principal per la pràctica 2020 de Marc Falcón Barau <em>Creació d'un arbre filogenètic</em>.
*/
int main() 
{
    int k;
    cin >> k;
    
    Cjt_Clusters c;
    Cjt_especies e;

    e.llegir_k(k);

    string op;  // diverses operacions

    while (cin >> op & op != "fin") {
        string gen;     // nom del gen
        string id1, id2;   // identificadors, nombre d'especies, identificador cluster
        
        if (op == "crea_especie") {
            cin >> id1 >> gen;
            cout << "# crea_especie " << id1 << ' ' << gen << endl;
            if (e.existeix_especie(id1)) cout << "ERROR: La especie " << id1 << " ya existe." << endl;
            else e.crea_especie(id1, gen);
        }
        else if (op == "obtener_gen") {
            cin >> id1;
            cout << "# obtener_gen " << id1 << endl;
            if (e.existeix_especie(id1)) {
                e.obtenir_gen(id1);
            }
            else cout << "ERROR: La especie " << id1 << " no existe." << endl;
        }
        else if (op == "distancia") {
            cin >> id1 >> id2;
            cout << "# distancia " << id1 << ' ' << id2 << endl;
            if (not e.existeix_especie(id1) and not e.existeix_especie(id2)) {
                cout << "ERROR: La especie " << id1 << " y la especie " << id2 << " no existen." << endl;
            }
            else if (not e.existeix_especie(id1) and e.existeix_especie(id2)) {
                cout << "ERROR: La especie " << id1 << " no existe." << endl;
            }
            else if (e.existeix_especie(id1) and not e.existeix_especie(id2)) {
                cout << "ERROR: La especie " << id2 << " no existe." << endl;
            }
            else e.distancia(id1, id2);
        }
        else if (op == "elimina_especie") {
            cin >> id1;
            cout << "# elimina_especie " << id1 << endl;
            if (not e.existeix_especie(id1)) cout << "ERROR: La especie " << id1 << " no existe." << endl;
            else e.elimina_especie(id1);
        }
        else if (op == "existe_especie") {
            cin >> id1;
            cout << "# existe_especie" << ' ' << id1 << endl;
            if (e.existeix_especie(id1)) cout << "SI" << endl;
            else cout << "NO" << endl;
        }
        else if (op == "lee_cjt_especies") {
            cout << "# lee_cjt_especies" << endl;
            e.llegeix_cjt_especies();
            c.clear_cjt_cluster(); 
            
        }
        else if (op == "imprime_cjt_especies") {
            cout << "# imprime_cjt_especies" << endl;
            e.imprimeix_cjt_especies();
        }
        else if (op == "tabla_distancias") {
            cout << "# tabla_distancias" << endl;
            e.taula_distancies();

        }
        else if (op == "imprime_arbol_filogenetico") {
            cout << "# imprime_arbol_filogenetico" << endl;
            e.inicialitza_clusters(c);
            if (c.conjunt_cluster_size() != 0) {
                c.imprimeix_arbre_filogenetic();
                cout << endl;
            }
            else cout << "ERROR: El conjunto de clusters es vacio." << endl;
        }
        else if (op == "inicializa_clusters") { 
            cout << "# inicializa_clusters" << endl;
            e.inicialitza_clusters(c);
            e.taula_distancies();

        }
        else if (op == "ejecuta_paso_wpgma") {
            cout << "# ejecuta_paso_wpgma" << endl;
            if (c.conjunt_cluster_size() <= 1) cout << "ERROR: num_clusters <= 1" << endl;
            else {
                c.executa_pas_wpgma();
                c.imprimeix_taula_distancia();
            }
        }
        else if (op == "imprime_cluster") {
            cin >> id1;
            cout << "# imprime_cluster " << id1 << endl;
            if (c.existeix_cluster(id1)) {
                c.imprimeix_cluster(id1);
                cout << endl;
            } 
            else {
                cout << "ERROR: El cluster " << id1 << " no existe." << endl;
            }
        }
        cout << endl;
    }
}