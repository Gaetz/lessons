#pragma once
#include "ofMain.h"

// 00 - Premier contact : une tête qui suit la souris
// Sketch d'origine : Cours 2024-2025/sketch_01_funny_face
// Objectif : créer quelque chose dès la première séance, par modification du code.
// Aucune notion n'est expliquée ici : on observe, on change des nombres, on relance.
// Les explications viennent dans les fichiers suivants (couleurs animées : 06, fonctions : 07).

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();

	void funnyFace(float x, float y);

	float r = 0;
	float g = 0;
	float b = 0;
};
