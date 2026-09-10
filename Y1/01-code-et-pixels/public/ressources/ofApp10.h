#pragma once
#include "ofMain.h"

// 10 - Image et lecture de pixel
// Sketch d'origine : Cours 2022-2023/rendu02
// Notions : ofImage, chargement depuis bin/data, affichage, lecture de la couleur
//           d'un pixel (getColor), affichage de texte, conversion nombre -> texte
// Ressource : bin/data/image2.png

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();

	ofImage img;
};
