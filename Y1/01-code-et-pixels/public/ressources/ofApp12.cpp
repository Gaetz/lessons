#include "ofApp12.h"

void ofApp::setup() {
	ofSetWindowShape(windowWidth, windowHeight);
	if (!img.load("pandaroux.jpg")) {
		ofLogError() << "pandaroux.jpg introuvable dans bin/data";
	}
}

void ofApp::update() {

}

// Distance entre deux points : théorème de Pythagore.
// (openFrameworks fournit ofDist(ax, ay, bx, by) qui fait exactement ceci.)
float ofApp::distance(float ax, float ay, float bx, float by) {
	float dx = bx - ax;
	float dy = by - ay;
	return sqrt(dx * dx + dy * dy);
}

void ofApp::draw() {
	ofBackground(0);

	// Le sketch Processing affichait l'image puis lisait ses pixels à l'écran.
	// Ici on lit directement les pixels de l'ofImage, donc pas besoin de l'afficher.

	float x = mouseX;
	float y = mouseY;

	ofFill();
	// Pour une ligne li qui va de 0 à la hauteur, de 20 en 20 :
	for (int li = 0; li < windowHeight; li += tailleCercle) {
		// Pour une colonne co qui va de 0 à la largeur, de 20 en 20 :
		for (int co = 0; co < windowWidth; co += tailleCercle) {

			float d = distance(x, y, co, li);

			// Près de la souris, les cercles rétrécissent proportionnellement à la distance
			float rayon = tailleCercle / 2.0f;
			if (d <= 150) {
				float proportion = d / 150.0f;
				rayon = rayon * proportion;
			}

			// Couleur du pixel à cet endroit de l'image
			ofColor c = img.getColor(co, li);
			ofSetColor(c);
			ofDrawCircle(co, li, rayon);
		}
	}

	// ---- Variante (sketch_03_image, 2024-2025) ----
	// Remplacer le cercle par un carré dont la taille dépend de la distance
	// à un anneau qui s'élargit avec le temps :
	//
	//   float t = ofGetElapsedTimef() * 60;   // le sketch comptait en frames
	//   float prop = d / (200.0f + t);
	//   ofDrawRectangle(co, li, tailleCercle * prop, tailleCercle * prop);
	//
	// Exercice : filtre local. Reprendre un filtre de 11 (négatif, gris, seuil...) et ne l'appliquer
	// qu'aux cercles situés à moins de 150 px de la souris : un filtre se combine avec un masque.
	// Variante : ne plus dessiner des cercles mais la couleur la plus proche parmi 5 couleurs
	// choisies, en comparant par distance dans le cube RGB (Pythagore en 3D, cours 09).
}
