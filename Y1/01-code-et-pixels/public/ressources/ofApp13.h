#pragma once
#include "ofMain.h"

// 13 - Trigonométrie : cercles sur un cercle et modes de fusion
// Sketch d'origine : Cours 2024-2025/sketch_04_circles
// Variantes écartées (même principe) : sketch_04a_circles (120 petits cercles, SUBTRACT sur fond blanc),
//                                      Cours 5/TrigoBlend (9 cercles, ADD)
// Notions : cos / sin pour placer un point sur un cercle, angle en radians (2 PI = tour complet),
//           modulo pour alterner les couleurs, ofTranslate + ofPushMatrix / ofPopMatrix,
//           ofEnableBlendMode. Variante : teinte selon l'angle (relit 09)

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();

	int   nbCercles = 12;
	float rayonOrbite = 200;
	float t = 1;
};
