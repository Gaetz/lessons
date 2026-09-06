#include "ofApp00a.h"

void ofApp::setup() {
	ofSetWindowShape(800, 800);
}

void ofApp::update() {

}

// Une tête dessinée autour du point (x, y).
// Chaque nombre est une position ou une taille : change-les et regarde ce qui bouge.
void ofApp::funnyFace(int x, int y) {
	// Le visage
	ofSetColor(255, 255, 255, 255);
	ofDrawCircle(200 + x, 200 + y, 225);
	// La bouche
	ofDrawRectangle(100 + x, 200 + y, 250, 50);

	// Les yeux : rouge semi-transparent — essaie (0, 255, 0, 150)
	ofSetColor(255, 0, 0, 150);
	ofDrawCircle(55 + x, 75 + y, 50);
	ofDrawCircle(375 + x, 75 + y, 50);
}

void ofApp::draw() {
	ofBackground(30);                // repeint le fond : sans lui, des traînées
	funnyFace(mouseX, mouseY);       // remplace mouseX, mouseY par 100, 100 : que se passe-t-il ?
}
