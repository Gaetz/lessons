#pragma once
#include "ofMain.h"

// 14 - Filtres géométriques : la formule porte sur les coordonnées, pas sur la couleur
// Nouveau : pas de sketch Processing d'origine
// Notions : lecture "à l'envers" (pour chaque pixel du résultat, où aller le chercher dans la source),
//           resultat(x, y) = source(f(x, y)), bornage des coordonnées, miroir, pixelisation
//           (division entière), vagues avec sin et le temps (relit 13), décalage des canaux (glitch)
// Ressource : bin/data/pandaroux.jpg (774 x 516)

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);

	// Lecture dans la source avec des coordonnées bornées
	ofColor lire(float x, float y);

	ofImage source;
	ofImage resultat;
	int   effet = 0;
	float parametre = 0.5f;
	float t = 0;
	std::vector<std::string> noms = {
		"original", "miroir", "rotation 180", "pixelisation", "vagues", "glitch (canaux decales)"
	};
};
