/** @file Cluster.hh
    @brief Especificació de la classe Cluster
*/

#ifndef _CLUSTER_
#define _CLUSTER_

#ifndef NO_DIAGRAM
#include "BinTree.hh"
#include <string>
#include <iostream>
using namespace std;
#endif

/*
 * Classe Cluster
 */

/** @class Cluster
    @brief Representa un cluster especific
    
    Conté informació sobre el cluster com que cada cluster es un arbre binari, i les operacions relacionades amb els clusters 
*/

class Cluster {
    
private:

    /** @brief Tot cluster el creem com un arbre binari on en el node te un pair amb un identificador i una distancia */
    BinTree<pair<string, double> > cluster;

    /** @brief Funció auxiliar de l'escriptura de l'arbre filogenètic
      \pre cjt_clusters no buit
      \post imprimeix per el canal estàndard el arbre filogenètic
    */
    void escriure_cluster_arbre(const BinTree<pair<string, double> >& a) const;
    
public:
    
    // Constructores
	
  	/** @brief Creadora per defecte
		  @pre cert
      @post El resultat es un cluster buit
	  */
	  Cluster();

   /** @brief Creadora per defecte
		  @pre cert
		  @post El resultat es la creació d'un cluster amb un string
	  */
    Cluster(string &id1);
    
    // Consultores
  
    /** @brief Operació d'escriptura del id del cluster
      \pre cert
      \post retorna l'identificador del cluster indicat
    */
    string consultar_identificador_cluster();

    // Modificadores

    /** @brief Operació d'unió entre dos clusters
      \pre cert
      \post retorna un cluster format per la unió de dos altrea c1 i c2
    */
    void unio(Cluster& c1, Cluster& c2, double& distance);
    
    // Lectura i escriptura
    
    /** @brief Operació d'escriptura del cluster
      \pre cert
      \post S'escriu pel el canal de sortida estàndard el cluster indicat
    */
    void escriure_cluster();
    
};
#endif