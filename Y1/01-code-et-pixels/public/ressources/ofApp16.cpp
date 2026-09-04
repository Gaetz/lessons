#include "ofApp16.h"

void ofApp::setup() {
	ofSetWindowShape(400, 400);
	// Une rotation par fleur, toutes à 0 au départ.
	// Python : rotations.append(0) dans une boucle. C++ : constructeur avec taille + valeur.
	rotations = std::vector<float>(nbFlowers, 0.0f);
}

void ofApp::update() {
	float dt = ofGetLastFrameTime();
	for (int f = 0; f < nbFlowers; f++) {
		// Une fleur sur deux tourne dans l'autre sens
		float sens = (f % 2 == 0) ? 1.0f : -1.0f;
		// Le sketch ajoutait f * 0.002 par frame => f * 0.12 rad/s
		float speed = f * 0.12f * sens;
		rotations[f] = rotations[f] + speed * dt;
	}
}

// Une fleur = un polygone de nbPoints sommets.
// Pour chaque sommet : un angle régulier, et un rayon r modulé par un cosinus.
void ofApp::drawFlower(int fIndex, float r, float rotation) {
	ofBeginShape();
	for (int i = 0; i < nbPoints; i++) {
		float angle = i * TWO_PI / nbPoints;
		// cos(angle * period) oscille "period" fois sur un tour => "period" pétales
		float fRadius = amplitude * cos(angle * period);
		// Polaire -> cartésien
		float x = (r + fRadius) * cos(angle + rotation);
		float y = (r + fRadius) * sin(angle + rotation);
		ofVertex(x, y);
	}
	ofEndShape(true);     // true = fermer la forme (CLOSE en Processing)
}

void ofApp::draw() {
	ofBackground(0);

	ofPushMatrix();
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);

	// Processing : blendMode(DIFFERENCE), qui inverse là où les fleurs se recouvrent.
	// Sans équivalent direct en openFrameworks : on alterne deux couleurs en ADD,
	// ce qui rend les recouvrements lisibles. (Un vrai DIFFERENCE se fera plus tard en shader.)
	ofEnableBlendMode(OF_BLENDMODE_ADD);
	ofFill();
	for (int f = 0; f < nbFlowers; f++) {
		if (f % 2 == 0) ofSetColor(60, 20, 90);
		else            ofSetColor(20, 60, 90);
		drawFlower(f, 150 - f * 10, rotations[f]);
	}
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);

	ofPopMatrix();

	// Alternative moderne à ofBeginShape : construire une ofPolyline
	// (polyline.addVertex(x, y) ... polyline.close() ; polyline.draw())
	// ou un ofPath pour un remplissage. À montrer quand on aborde les objets.

	// Exercice (image) : loupe et tourbillon, avec la lecture "à l'envers" de 14.
	// Pour chaque pixel (x, y) du résultat :
	//   1. cartésien -> polaire autour de la souris : dx = x - mouseX, dy = y - mouseY,
	//      r = sqrt(dx * dx + dy * dy), angle = atan2(dy, dx)
	//   2. modifier : loupe = r * 0.5 si r < R ; tourbillon = angle + k * (1 - r / R) si r < R
	//   3. polaire -> cartésien : sx = mouseX + r * cos(angle), sy = mouseY + r * sin(angle)
	//   4. lire la source en (sx, sy), écrire dans le résultat en (x, y)
}
