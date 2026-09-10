#include "ofApp03.h"

void ofApp::setup() {
	ofSetWindowShape(800, 800);
	ofBackground(200);
}

void ofApp::update() {

}

void ofApp::draw() {
	// En Processing ce sketch n'a pas de draw() : il est exécuté UNE fois,
	// donc les cercles aléatoires restent en place.
	// En openFrameworks draw() tourne 60 fois par seconde : sans précaution,
	// les cercles changeraient de place à chaque frame (scintillement).
	//
	// Solution simple ici : réinitialiser la graine aléatoire à chaque frame.
	// Même graine => même suite de nombres => même dessin.
	// (Solution propre, vue au fichier 04 : générer une fois dans setup(),
	//  stocker dans un std::vector, dessiner dans draw().)
	ofSeedRandom(42);

	ofFill();
	ofSetColor(255);

	// 50 cercles aléatoires
	for (int i = 0; i < 50; i++) {
		float x = ofRandom(0, 800);
		float y = ofRandom(0, 800);
		float taille = ofRandom(10, 50);
		ofDrawCircle(x, y, taille / 2);
	}

	// Ligne de cercles de gauche à droite, du plus petit au plus grand.
	// range(0, 50, 5) en Python => i += 5 en C++
	ofSetColor(0, 0, 255);
	for (int i = 0; i < 50; i += 5) {
		ofDrawCircle(i * 16, 100, i / 2.0f);
	}

	// Colonne de cercles rouges de haut en bas, du plus grand au plus petit
	ofSetColor(255, 0, 0);
	for (int i = 0; i < 50; i++) {
		ofDrawCircle(200, 800 - i * 16, i / 2.0f);
	}

	// Diagonale bas-gauche -> haut-droite, tailles aléatoires entre 5 et 40
	ofSetColor(255, 255, 0);
	for (int i = 0; i < 50; i++) {
		float taille = ofRandom(5, 40);
		ofDrawCircle(i * 16, 800 - i * 16, taille / 2);
	}
}
