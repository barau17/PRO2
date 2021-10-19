/** @file Cjt_Clusters.hh
    @brief Especificació de la classe Cjt_Clusters
*/

#ifndef _CJT_CLUSTERS_
#define _CJT_CLUSTERS_

#include "Cluster.hh"

#ifndef NO_DIAGRAM
#include "BinTree.hh"
#include <iostream>
#include <map>
using namespace std;
#endif


/** 
  Classe Cjt_Clusters
 */

/** @class Cjt_Clusters
	@brief Representa el conjunt de clusters d'un experiment.
	
	Ofereix les operacions associades amb els clusters ja siguin escriptura i consultes.
*/


class Cjt_Clusters {

private:
    
    /** @brief Llista de clústers
		Ordenada creixentment segons el seu identificador de manera lexicogràfica. */
    map<string, Cluster> cjt_clusters;

	/** @brief Conjunt de distancies entre totes les especies */
	map<string, map<string, double> > nova_taula_distancies;	
    
public:
    
    // Constructora
    
    /** @brief Creadora per defecte
		@pre cert
		@post El resultat es un Cjt_clusters buit
	*/
	Cjt_Clusters();
    
    // Modificadores

	/** @brief Modificadora auxiliar per a copiar les especies i utilitzar-les com a clusters
		@pre cjt_clusters buit
		@post copiat el cjt_especie a cjt_cluster, i pasades les especies com a clusters
	*/
	void copia_cluster(string id1);
    
    /** @brief Fusiona els dos clusters a menor distancia en un nou.
		@pre cert
		@post executa un pas de l'algortime wpgma i imprimeix la taula de distancies entre clusters resultant.
	*/
    void executa_pas_wpgma();

	/** @brief Afegim el nou cluster format per el pas wpgma a la taula de distancies
		@pre cert
		@post hem afegit el nou cluster a la taula i hem borrat els seus dos integrants per separat de la taula
	*/
	void afegeix_cluster_a_taula(Cluster &c1, string& id1, string& id2);

	/** @brief Reseteja completament tot el Cjt_Clusters
		@pre Cjt_clusters not empty
		@post el cjt_clusters i el conjunt de distancies queda buit esperant a nous elements
	*/
	void clear_cjt_cluster();

    // Consultores
    
    /** @brief Consultora de mida del conjunt de clusters
		\pre cert
		\post retorna la mida del conjunt format per clusters 
	*/
    int conjunt_cluster_size();
    
    /** @brief Consultora de la existencia d'un cluster
		\pre cert
		\post retorna si existeix el cluster amb identificador id1 dins el nostre conjunt
	*/
    bool existeix_cluster(string id1);

	/** @brief Afegim un inner map buit per a l'ultim valor dins de la taula de distancies 
		\pre cert
		\post quan imprimim la taula aquesta s'imprimeix correctament gracies a l'afegiment de el map inner map buit 
	*/
	void afegeix_distancia_buida(const string& id1);
    
    // Lectura i escriptura
    
    /** @brief Operació d'escriptura dels clusters
      \pre cert
      \post S'escriu pel el canal de sortida estàndard el cluster amb id1
    */
	void imprimeix_cluster(string id1);
    
    /** @brief Operació d'escriptura del arbre filogenètic
      \pre cert
      \post S'escriu pel el canal de sortida estàndard l'arbre filogenètic format per el cjt de clusters
    */
	void imprimeix_arbre_filogenetic();

	/** @brief Lectura de distancies
		\pre cert
		\post es llegeixen les distancies entre cada especie i es guarden en el map designat. Pas de cjt_especie a cjt_cluster
	*/
	void afegeix_distancies(const string& id1, const string& id2, const double& distancia);

	/** @brief Imprimeix la taula amb els valors actuals dels clusters 
		\pre cert
		\post imprimeix per el canal estàndard la taula de distancies actualitzada amb els clusters adients
	*/
	void imprimeix_taula_distancia();	
	  
};
#endif