#include "ofApp01.h"

// En Processing, size(400, 400) est le premier appel du sketch.
// En openFrameworks, la fenêtre existe déjà : on lui donne sa taille dans setup().
void ofApp::setup() {
	ofSetWindowShape(400, 400);
	ofBackground(200);          // gris clair, comme le fond par défaut de Processing
}

void ofApp::update() {

}

// Processing dessine ce sketch une seule fois (pas de draw()).
// openFrameworks appelle draw() 60 fois par seconde : un dessin statique
// est simplement redessiné à l'identique à chaque frame.
void ofApp::draw() {
	// Deux variables pour stocker la taille de l'écran.
	// En C++ chaque variable a un type : int pour un entier, float pour un décimal.
	int sizeX { 400 };
	int sizeY { 400 };

	// Coordonnée horizontale du milieu de l'écran
	float x = sizeX / 2.0f;
	// Coordonnée verticale aux 3/4 de l'écran
	float y = sizeY * 3 / 4.0f;
	// PIÈGE : en C++, 3 / 4 vaut 0 (division entière).
	// sizeY * 3 / 4 vaut 300 car la multiplication est faite d'abord (1200 / 4).
	// Écrire 4.0f force un calcul en décimal.

	ofSetColor(255);            // blanc = fill(255) de Processing
	ofFill();

	// ATTENTION : circle(x, y, 75) en Processing prend un DIAMÈTRE.
	// ofDrawCircle(x, y, r) prend un RAYON. 75 de diamètre = 37.5 de rayon.
	ofDrawCircle(x, y, 37.5f);

	// Dessiner 10 cercles de gauche à droite, au premier quart de l'écran.
	// Version "à la main", sans boucle : on répète le même code 10 fois.
	x = 0;
	float step { 75 };
	y = sizeY * 1 / 4.0f;
	ofDrawCircle(x, y, 37.5f);
	x = x + step;
	ofDrawCircle(x, y, 37.5f);
	x = x + step;
	ofDrawCircle(x, y, 37.5f);
	x = x + step;
	ofDrawCircle(x, y, 37.5f);
	x = x + step;
	ofDrawCircle(x, y, 37.5f);
	x = x + step;
	ofDrawCircle(x, y, 37.5f);
	x = x + step;
	ofDrawCircle(x, y, 37.5f);
	x = x + step;
	ofDrawCircle(x, y, 37.5f);
	x = x + step;
	ofDrawCircle(x, y, 37.5f);
	x = x + step;
	ofDrawCircle(x, y, 37.5f);

	// Exercice : reprendre le code ci-dessus pour espacer les cercles de 50.
	// Constat : 20 lignes pour 10 cercles. La boucle for (fichier 02) règle ça.
}
