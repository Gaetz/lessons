#pragma once
#include "ofMain.h"

// 11 - Filtres : une formule appliquée à chaque pixel
// Nouveau : pas de sketch Processing d'origine
// Notions : double boucle sur tous les pixels (lignes / colonnes), image source et image résultat,
//           setColor + update(), débordement des unsigned char (calcul en float puis ofClamp),
//           paramètre à la souris, choix de l'effet au clavier (keyPressed, switch),
//           deuxième partie : les filtres qui passent par HSB (relit 09)
// Ressource : bin/data/pandaroux.jpg (774 x 516)

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);

	// Un pixel entre, un pixel sort. p est le paramètre (0 à 1) piloté par la souris.
	ofColor filtre(ofColor c, float p);

	ofImage source;
	ofImage resultat;
	int   effet = 0;
	float parametre = 0.5f;
	std::vector<std::string> noms = {
		"original", "negatif", "gris (moyenne)", "gris (luminance)", "luminosite",
		"contraste", "seuil", "posterisation", "rotation de teinte", "color splash"
	};
};
