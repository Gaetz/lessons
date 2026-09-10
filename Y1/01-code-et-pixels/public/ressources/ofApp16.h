#pragma once
#include "ofMain.h"

// 16 - Trigonométrie : fleurs en coordonnées polaires
// Sketch d'origine : Cours 5/TrigoFlower
// Notions : coordonnées polaires (angle, rayon) -> cartésiennes, modulation du rayon
//           par un cosinus (pétales), forme libre ofBeginShape / ofVertex / ofEndShape,
//           plusieurs instances animées à des vitesses différentes.
//           Exercice final : loupe et tourbillon sur image (polaire -> cartésien appliqué à 14)
// Correction : le sketch d'origine utilisait "flower_index" au lieu de "f_index" dans draw()

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();

	void drawFlower(int fIndex, float r, float speed);

	int   nbPoints { 200 };
	float amplitude { 15 };     // hauteur des pétales
	int   period { 7 };         // nombre de pétales
	int   nbFlowers { 14 };
	std::vector<float> rotations;
};
