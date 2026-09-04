#pragma once
#include "ofMain.h"

// 11c - LUT et étalonnage
// Nouveau : pas de sketch Processing d'origine
// Notions : une LUT (look-up table) 1D = une table de 256 valeurs par canal ; toute courbe de
//           transfert du cours 11 en est une ; précalculer la table une fois, l'appliquer par
//           simple lecture lut[c] ; étalonnage (color grading) = trois courbes différentes ;
//           force du grading = interpolation entre identité et LUT
// Ressource : bin/data/pandaroux.jpg (774 x 516)

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);

	void construireLut();
	void appliquerLut();
	float courbeS(float t);      // 0-1 -> 0-1, en S

	ofImage source;
	ofImage resultat;
	std::vector<int> lutR, lutG, lutB;    // 256 entrées chacune

	int   look = 0;
	float force = 1;
	float derniereForce = -1;
	int   dernierLook = -1;
	std::vector<std::string> noms = { "identite", "contraste (courbe en S)", "teal & orange", "vintage (noirs releves)", "negatif" };
};
