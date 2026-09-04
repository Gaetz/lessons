#include "ofApp00a.h"

void ofApp::setup() {
	ofSetWindowShape(800, 800);      // taille de la fenêtre : essaie 400, 400
}

void ofApp::update() {
	// La couleur du fond change toute seule avec le temps.
	// Essaie de remplacer 1.5f par 0.2f, puis par 10.0f.
	float t = ofGetElapsedTimef();
	r = (cos(t * 1.5f) / 2 + 0.5f) * 255;
	g = (cos(t * 0.75f) / 2 + 0.5f) * 255;
	b = (cos(t * 1.0f) / 2 + 0.5f) * 255;
}

// Une tête dessinée autour du point (x, y).
// Chaque nombre est une position ou une taille : change-les et regarde ce qui bouge.
void ofApp::funnyFace(float x, float y) {
	// Le visage : blanc à moitié transparent (le dernier nombre, 100, est la transparence sur 255)
	ofSetColor(255, 255, 255, 100);
	ofDrawCircle(200 + x, 200 + y, 225);
	// La bouche
	ofDrawRectangle(100 + x, 200 + y, 250, 50);

	// Les yeux : rouge (255, 0, 0) — essaie (0, 255, 0)
	ofSetColor(255, 0, 0, 150);
	ofDrawCircle(55 + x, 75 + y, 50);
	ofDrawCircle(375 + x, 75 + y, 50);

	// À toi : ajoute deux oreilles avec ofDrawCircle, puis un nez avec ofDrawRectangle.
}

void ofApp::draw() {
	ofBackground(r, g, b);           // remplace par ofBackground(0); pour un fond noir fixe
	funnyFace(mouseX, mouseY);       // remplace mouseX, mouseY par 100, 100 : que se passe-t-il ?
}
