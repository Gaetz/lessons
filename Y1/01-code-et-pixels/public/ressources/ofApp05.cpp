#include "ofApp05.h"

void ofApp::setup() {
	ofSetWindowShape(400, 400);
}

// Nouveau par rapport à Processing : la LOGIQUE va dans update(),
// le DESSIN va dans draw(). update() est appelée juste avant draw(), à chaque frame.
void ofApp::update() {
	// mouseX et mouseY sont des membres hérités de ofBaseApp,
	// mis à jour automatiquement par openFrameworks.
	x = mouseX;
	y = mouseY;
}

void ofApp::draw() {
	// background(255, 0, 0) en Processing : efface l'écran à chaque frame.
	// Sans cet appel, les cercles des frames précédentes resteraient visibles.
	ofBackground(255, 0, 0);

	ofSetColor(255);
	ofFill();
	ofDrawCircle(x, y, 50);     // circle(x, y, 100) => rayon 50
}
