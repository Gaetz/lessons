#include "ofApp08.h"

// i : indice dans la traînée (0 = le plus ancien). t : temps en secondes.
void ofApp::forme(float x, float y, int i, float t, float r, float g, float b) {
	float offset = i * 10;

	// Taille de base qui ondule selon l'indice, plus une variation temporelle
	// plus forte pour les éléments anciens ((25 - i) / 25).
	float taille = (cos(i / 5.0f) + 5) * 20;
	float variation = (cos(t * 1.2f) + 5) * 100;
	float tailleFinale = taille + variation * (25 - i) / 50.0f;

	// Remplissage : couleur éclaircie et alpha croissant avec i
	ofFill();
	ofSetColor(r + offset, g + offset, b + offset, offset);
	ofDrawCircle(x, y, tailleFinale / 2);

	// Contour : alpha décroissant avec i
	ofNoFill();
	ofSetColor(r + offset, g + offset, b + offset, 255 - offset);
	ofDrawCircle(x, y, tailleFinale / 2);
}

void ofApp::setup() {
	ofSetWindowShape(800, 800);
	ofSetCircleResolution(64);
}

void ofApp::update() {
	t = ofGetElapsedTimef();
	// Le sketch Processing utilisait t en frames : cos(t / 50.0).
	// À 60 fps, t/50 frames == temps * 1.2 secondes.
	r = (cos(t * 1.2f) / 2 + 0.5f) * 255;
	g = (cos(t * 1.0f) / 2 + 0.5f) * 255;
	b = (cos(t * 0.86f) / 2 + 0.5f) * 255;

	prevX.push_back(mouseX);
	prevY.push_back(mouseY);
	if (prevX.size() > 25) {
		prevX.erase(prevX.begin());
		prevY.erase(prevY.begin());
	}
}

void ofApp::draw() {
	ofBackground(0);

	for (int i = 0; i < prevX.size(); i++) {
		forme(prevX[i], prevY[i], i, t, r, g, b);
	}

	// Pistes d'amélioration proposées aux étudiants dans le sketch d'origine :
	// - améliorer couleurs et contours de la traînée et du premier cercle
	// - utiliser la transparence
	// - jouer avec les tailles
	// - remplacer le cercle par une fonction dessinant une forme plus complexe
	// - utiliser des conditions pour faire varier les formes
}
