#include "ofApp00.h"

void ofApp::setup() {
	ofSetWindowShape(800, 800);      // taille de la fenêtre : essaie 400, 400
}

void ofApp::update() {

}

void ofApp::draw() {
	// Deux variables : elles décalent toute la tête d'un coup.
	// Essaie x { 100 }, puis y { -50 }.
	int x { 0 };
	int y { 0 };

	// Le visage : ofDrawCircle est une fonction toute faite,
	// on l'appelle avec des paramètres (position x, position y, rayon).
	ofSetColor(255, 255, 255, 255);
	ofDrawCircle(200 + x, 200 + y, 225);
	// La bouche
	ofDrawRectangle(100 + x, 200 + y, 250, 50);

	// Les yeux : rouge (255, 0, 0) — essaie (0, 255, 0)
	ofSetColor(255, 0, 0, 150);
	ofDrawCircle(55 + x, 75 + y, 50);
	ofDrawCircle(375 + x, 75 + y, 50);
}
