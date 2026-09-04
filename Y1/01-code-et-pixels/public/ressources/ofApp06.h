#pragma once
#include "ofMain.h"

// 06 - Animation, vitesse, rebond, conditions
// Sketch d'origine : Cours 2022-2023/rendu01_pde
// Notions : vitesse et déplacement, if / rebond sur les bords, delta time,
//           animation de couleur, séparation update() / draw()

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();

	// Position (décalage appliqué aux formes) et vitesse
	float decalageX = 0;
	float decalageY = 0;
	// Vitesses en PIXELS PAR SECONDE.
	// Le sketch Processing avançait de 1 et 2 pixels PAR FRAME (=> 60 et 120 px/s à 60 fps).
	float vx = 60;
	float vy = 120;

	// Couleur de fond et vitesses de variation (unités par seconde)
	float r = 0, g = 0, b = 0;
	float vr = 300, vg = 240, vb = 180;   // 5, 4, 3 par frame x 60
};
