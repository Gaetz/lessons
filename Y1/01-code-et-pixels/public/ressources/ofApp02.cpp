#include "ofApp02.h"

void ofApp::setup() {
	ofSetWindowShape(400, 400);
	ofBackground(200);
}

void ofApp::draw() {
	float x = 0;
	float y = 0;
	float taille = 10;      // diamètre, comme dans le sketch Processing
	int   b = 0;

	// Syntaxe C++ de la boucle : for (initialisation; condition; incrément)
	// Équivalent de : for i in range(0, 10):
	for (int i = 0; i < 10; i++) {

		// Processing dessine remplissage + contour en un seul appel circle().
		// openFrameworks n'a pas de "stroke" séparé : on dessine deux fois.

		// 1) le remplissage — fill(255, 0, b, 180)
		ofFill();
		ofSetColor(255, 0, b, 180);
		ofDrawCircle(x, y, taille / 2);

		// 2) le contour — stroke(255, 150, 0)
		ofNoFill();
		ofSetColor(255, 150, 0);
		ofDrawCircle(x, y, taille / 2);

		x = x + 40;
		y = y + 40;
		taille = taille + 20;
		b = b + 25;
	}
	// fin boucle for

	// Note : ofSetCircleResolution(64) dans setup() lisse les grands cercles.
}
