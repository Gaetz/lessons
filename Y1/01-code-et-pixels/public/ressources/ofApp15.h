#pragma once
#include "ofMain.h"

// 15 - Trigonométrie : grille de points en rotation
// Sketch d'origine : Cours 5/TrigoFlag
// Notions : grille par double boucle, calcul d'un centre de case, rotation locale
//           par cos / sin, déphasage selon la position (effet de vague / drapeau)

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();

	void drawPoint(int i, int j, float angle);

	int   screenSize { 400 };
	int   rows { 15 };
	int   cols { 15 };
	float tileSize { 0 };      // calculé dans setup
	float radius { 0 };
	float speed { 2.4f };      // radians par seconde (0.04 rad/frame x 60)
	float globalAngle { 0 };
	float angleOffset { 75 };
};
