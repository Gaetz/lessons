#include "ofApp07.h"

// Un ours dessiné autour du point (x, y)
void ofApp::bear(float x, float y) {
	ofDrawCircle(x - 25, y - 25, 25);
	ofDrawCircle(x + 25, y - 25, 25);
	ofDrawCircle(x, y, 50);
	ofDrawCircle(x, y, 10);
	ofDrawCircle(x - 30, y - 20, 10);
	ofDrawCircle(x + 30, y - 20, 10);
	ofDrawRectangle(x, y + 20, 50, 10);
}

void ofApp::setup() {
	ofSetWindowShape(400, 400);
}

void ofApp::update() {
	// Mémoriser la position courante AVANT de la mettre à jour
	xCoords.push_back(x);
	yCoords.push_back(y);

	// Si la liste dépasse 50 éléments, retirer le plus ancien (le premier).
	// Python : x_coords.pop(0)
	// C++    : xCoords.erase(xCoords.begin())
	if (xCoords.size() >= 50) {
		xCoords.erase(xCoords.begin());
		yCoords.erase(yCoords.begin());
	}

	// Nouvelle position = souris
	x = mouseX;
	y = mouseY;
}

void ofApp::draw() {
	ofBackground(0);
	ofFill();
	ofSetColor(255);

	// Redessiner toutes les positions mémorisées, de la plus ancienne à la plus récente
	for (int i = 0; i < xCoords.size(); i++) {
		bear(xCoords[i], yCoords[i]);
	}

	// Puis la position courante
	bear(x, y);
}

// ---------- Raisonnement d'origine (conservé du sketch) ----------
// Dessiner un cercle suivi des 50 précédents :
//   plutôt que 4 variables pour 2 positions précédentes,
//   stocker toutes les x dans une liste et toutes les y dans une autre,
//   puis dessiner les 50 cercles avec ces coordonnées.
// Exercice : faire varier la couleur et la taille selon i (voir fichier 08).
