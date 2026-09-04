#pragma once
#include "ofMain.h"

// 04 - Listes : std::vector
// Sketches d'origine : Cours 2/04_First_lists + Cours 2024-2025/sketch_01a_list (fusionnés)
// Notions : std::vector, push_back, indexation [i], size(), boucle sur une liste,
//           std::string et concaténation, affichage console (std::cout) et à l'écran
// Sert de support aux exercices "Listes" (voir INDEX.md)

class ofApp : public ofBaseApp {
public:
	void setup();
	void draw();

	// En Python les listes étaient des variables globales.
	// En C++ on les déclare comme membres de la classe : accessibles
	// dans setup() ET dans draw(), sans mot-clé "global".
	std::vector<std::string> noms;
	std::vector<int> chiffres;
};
