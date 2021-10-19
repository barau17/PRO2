/** @file Cjt_especies.hh
    @brief Especificació de la classe Cjt_especies
*/

#ifndef _CJT_ESPECIES_HH
#define _CJT_ESPECIES_HH

#include "Especie.hh"
#include "Cjt_Clusters.hh"

#ifndef NO_DIAGRAM
#include <map>
#include <string>
typedef map<string, double> dins_map;
typedef map<string, dins_map> general_map;
using namespace std;
#endif


/*
 * Classe Cjt_especies
 */

/** @class Cjt_especies
	@brief Representa el conjunt d'especies que utilitzarem
	
	Farem operacions associades a aquest conjunt com per exemple crear, eliminar i escriure especies. 
*/

class Cjt_especies {
    
private:

	/** @brief k global per al calcul de kmers */
	int k;
    
    /** @brief Diccionari de les especies */
    map<string, Especie> cjt_especie;

	/** @brief Mapa general per la impresió de la taula de distancies */ 
	general_map taula_de_distancies;
    
public:

    // Constructora
    
    /** @brief Creadora per defecte
		@pre cert
		@post El resultat es un Cjt_especies buit
	*/
    Cjt_especies();
    
    // Modificadores
    
    /** @brief Modificadora del conjunt d'especies
		\pre cert
		\post s'afegeix una nova especie al Cjt_especies si aquesta no hi era amb el seu especific id i gen
	*/
    void crea_especie(string id, string gen);
    
    /** @brief Modificadora del conjunt d'especies
		\pre cert
		\post s'elimina del Cjt_especies la especie amb identificador = id
	*/
    void elimina_especie(string id);

	/** @brief Modificadora de la taula de distancies
		\pre la especie id1 es a la taula de distancies
		\post borra la distancia amb les altres especies i la borra de la taula de distancies
	*/
	void eliminar_distancia(string id1);

	/** @brief Modificadora de la taula de distancies
		\pre la especie amb id1 no està a la taula de distancies
		\post calculem les distancies necessaries amb les altres especies i afegim la especie id1 a la taula de distancies
	*/
	void afegeix_taula_distancies(string id1);

	/** @brief Inicialitza els clusters amb la informació del Cjt_Especie
		@pre Incialitza el conjunt de clusters amb el conjunt d'especies en l'estat en el que es trobi en aquell moment.
		@post Imprimeix la taula de distancies entre clusters, aixi com guarda a Cjt_Cluster la informació de les especies.
	*/
	void inicialitza_clusters(Cjt_Clusters& c);
    
    // Consultores
    
    /** @brief Consulta el gen de la especie
		\pre cert
		\post Imprimeix el gen associat a la especie
	*/
    void obtenir_gen(string id) const;
    
    /** @brief Consulta la taula de distancies del Cjt_especies
		\pre cert
		\post imprimeix la taula de distancies entre cada par d'especies d'aquest conjunt
	*/
    void taula_distancies() const;

	/** @brief Consulta la distancia entre dos especies 
		\pre les dos especies existexen
		\post retorna la distancia entre la especie amb id1 i la especie amb id2
	*/
	double calcular_distancia(string id1, string id2);
    
    /** @brief Consulta si la especie identificada existeix
		\pre cert
		\post indica si existeix la especie
	*/
    bool existeix_especie(string id) const;	
    
    // Lectura i escriptura
    
    /** @brief Operació de lectura del conjunt d'especies
		\pre llegeix del canal estàndard un enter n>=0 i una secuencia de n especies(par d'identificadors-gen, diferents entre si)
		\post les n especies llegides s'agregen al Cjt_especies
	*/
    void llegeix_cjt_especies();
    
    /** @brief Operació de escriptura del conjunt d'especies 
		\pre conjunt no buit
		\post Imprimeix al canal estàndard de sortida el Cjt_especies
	*/
    void imprimeix_cjt_especies() const;

	/** @brief Distancia entre dos id's
		\pre cert
		\post Imprimeix la distancia entre les dos especies
	*/
    void distancia(string id1, string id2);

	/** @brief Lectura de la k imposada per el programa 
		\pre cert
		\post tenim una k per a tot el problema per a calcular els kmers
	*/
	void llegir_k(int k);

};
#endif 