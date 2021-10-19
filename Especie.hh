/** @file Especie.hh
    @brief Especificació de la classe Especie
*/

#ifndef _ESPECIE_HH
#define _ESPECIE_HH

#ifndef NO_DIAGRAM
#include <map>
#include <string> 
#include <iostream>
using namespace std;
#endif

/*
 * Classe Especie
 */

/** @class Especie
    @brief Representa una especie en concret
    
    Conté informació sobre l'especie, es a dir el seu id, el seu gen, i les operacions relacionades amb les especies
*/

class Especie {
    
private:

	/** @brief Algunes de les declaracions de elements per a dur a terme les operacions de Especie */
    string id;  // id de la nostre especie
    string gen; // gen de la nostre especie
    bool tgen = false; // boolea que ens indica si la especie te gen

    /** @brief Conjunt de kmers de cada especie */
    map<string, int> kmers;
    
    
public:

    // Constructores
	
	/** @brief Creadora per defecte
		@pre cert
		@post El resultat es una especie buida
	*/
    Especie();
    
    /** @brief Creadora per defecte
		@pre cert
		@post El resultat es una especie amb el seu id i el seu gen 
	*/
    Especie(string id, string gen);
    
    // Consultores
    
    /** @brief Consultora del identificador de la especie
		\pre cert
		\post retorna el identificador de la especie
	*/
    string consultar_identificador() const;
    
    /** @brief Consultora de gen de la especie
		\pre cert
		\post retorna el gen de la especie
	*/
    string consultar_gen() const;
	
	/** @brief Consultora de gen de la especie
		\pre cert
		\post retorna si te gen o no
	*/
	bool te_gen() const;

	/** @brief Consulta els kmers de la especie
		\pre cert
		\post retorna els kmers de la especie indicada
	*/
	map<string, int> consultar_kmers() const;

	/** @brief Calcula la distancia entre dues especies
		\pre cert
		\post retorna la distancia resultant
	*/
	double calcula_distancia(const Especie& e2);

	/** @brief Calcula els kmers de cada especie
		\pre cert
		\post guarda al map de kmers tots els kmers de cada especie per a despres poder fer operacions amb ells
	*/
	void calcular_kmers(int k);
    
    // Lectura i escriptura
    
    /** @brief Operació de lectura
		\pre cert
		\post Llegim la especie que tenim al parametre implicit
	*/
	void llegir();
    
     /** @brief Operació de escriptura
		\pre cert
		\post Escribim la especie que hem identificat
	*/
    void escriure() const;
    
};
#endif