#pragma once
#include "ofMain.h"

// 07 - Traînée : mémoriser les positions précédentes
// Sketch d'origine : Cours 3/sketch_05_First_special_fx
// Notions : std::vector comme historique, push_back / erase(begin()),
//           file de taille bornée, fonction de dessin réutilisée en boucle
// Variante écartée : Cours 2022-2023/rendu03 (même principe, couvert par 07 + 08)

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();

	void bear(float x, float y);

	float x { 0 };
	float y { 0 };
	// Deux listes parallèles : xCoords[i] et yCoords[i] forment une position.
	// (Étape suivante possible : un seul std::vector<glm::vec2>.)
	std::vector<float> xCoords;
	std::vector<float> yCoords;
};
