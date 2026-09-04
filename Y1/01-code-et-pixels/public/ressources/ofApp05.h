#pragma once
#include "ofMain.h"

// 05 - setup / draw et souris
// Sketch d'origine : Cours 1/03_Circle_follows_mouse
// Notions : cycle setup() / update() / draw(), position de la souris (mouseX, mouseY),
//           variables membres persistantes entre deux frames

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();

	// Python : x = 0 / y = 0 en global, puis "global x, y" dans draw()
	// C++    : membres de la classe, visibles partout dans ofApp
	float x = 0;
	float y = 0;
};
