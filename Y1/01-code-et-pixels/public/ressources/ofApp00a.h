#pragma once
#include "ofMain.h"

// 00a - Premier contact : une tête qui suit la souris (version complète)
// État final du cours 00 : la figure rangée dans une fonction (funnyFace),
// la souris (mouseX / mouseY), le fond repeint à chaque frame (ofBackground).
// update() est encore vide : les nombres y changeront tout seuls dès le cours 05.

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();

	void funnyFace(int x, int y);
};
