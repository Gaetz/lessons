#include "ofApp11f.h"

float ofApp::versLineaire(float c) { return pow(c / 255.0f, 2.2f); }
float ofApp::versSRGB(float l)     { return 255.0f * pow(ofClamp(l, 0, 1), 1.0f / 2.2f); }

void ofApp::setup() {
	ofSetWindowShape(774, 516);
	if (!source.load("pandaroux.jpg")) {
		ofLogError() << "pandaroux.jpg introuvable dans bin/data";
	}
	resultat.allocate(source.getWidth(), source.getHeight(), OF_IMAGE_COLOR);
	for (int c = 0; c < 256; c++) tableLineaire.push_back(versLineaire(c));
	matrice = std::vector<float>(9, 0);
}

// Une matrice 3 x 3 : chaque canal de sortie est un mélange pondéré des trois canaux d'entrée.
//   r' = m0 * r + m1 * g + m2 * b
//   g' = m3 * r + m4 * g + m5 * b
//   b' = m6 * r + m7 * g + m8 * b
// L'identité (vision normale) est 1 0 0 / 0 1 0 / 0 0 1. Les matrices ci-dessous (Machado et al., 2009)
// projettent les couleurs sur ce que perçoit un oeil auquel il manque un type de cône.
// Elles s'appliquent à la lumière linéaire (cours 11a), pas aux valeurs sRGB.
ofColor ofApp::simuler(ofColor c) {
	float r = tableLineaire[c.r], g = tableLineaire[c.g], b = tableLineaire[c.b];
	float r2 = matrice[0] * r + matrice[1] * g + matrice[2] * b;
	float g2 = matrice[3] * r + matrice[4] * g + matrice[5] * b;
	float b2 = matrice[6] * r + matrice[7] * g + matrice[8] * b;
	return ofColor(versSRGB(r2), versSRGB(g2), versSRGB(b2));
}

void ofApp::calculerImage() {
	std::vector<float> cible;
	switch (type) {
	case 1: cible = { 0.152286f,  1.052583f, -0.204868f,   0.114503f, 0.786281f, 0.099216f,  -0.003882f, -0.048116f, 1.051998f }; break;
	case 2: cible = { 0.367322f,  0.860646f, -0.227968f,   0.280085f, 0.672501f, 0.047413f,  -0.011820f,  0.042940f, 0.968881f }; break;
	case 3: cible = { 1.255528f, -0.076749f, -0.178779f,  -0.078411f, 0.930809f, 0.147602f,   0.004733f,  0.691367f, 0.303900f }; break;
	default: cible = { 1, 0, 0,  0, 1, 0,  0, 0, 1 };
	}
	// Sévérité : on interpole entre l'identité et la matrice cible, case par case.
	// (Une vraie déficience partielle, plus fréquente que l'absence totale, ressemble à ça.)
	std::vector<float> identite = { 1, 0, 0,  0, 1, 0,  0, 0, 1 };
	for (int i = 0; i < 9; i++) {
		matrice[i] = identite[i] + (cible[i] - identite[i]) * severite;
	}

	int w = source.getWidth();
	int h = source.getHeight();
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			resultat.setColor(x, y, simuler(source.getColor(x, y)));
		}
	}
	resultat.update();
}

void ofApp::update() {
	severite = mouseX / (float)ofGetWidth();
	if (type != dernierType || severite != derniereSeverite) {
		calculerImage();
		dernierType = type;
		derniereSeverite = severite;
	}
}

// Un bout d'interface de jeu : deux jauges. À gauche, l'information n'est portée QUE par la couleur.
// À droite, elle est aussi portée par un motif et un symbole : lisible quelle que soit la vision.
void ofApp::dessinerTest(float x, float y) {
	ofColor vie(40, 190, 60), danger(220, 40, 40);
	ofFill();
	ofSetColor(simuler(vie));    ofDrawRectangle(x, y, 120, 30);
	ofSetColor(simuler(danger)); ofDrawRectangle(x + 130, y, 120, 30);

	ofSetColor(simuler(vie));    ofDrawRectangle(x + 300, y, 120, 30);
	ofSetColor(simuler(danger)); ofDrawRectangle(x + 430, y, 120, 30);
	ofSetColor(simuler(ofColor(255)));
	for (int i = 0; i < 120; i += 10) ofDrawLine(x + 430 + i, y, x + 430 + i + 10, y + 30);   // hachures sur le danger
	ofDrawBitmapString("+", x + 355, y + 20);
	ofDrawBitmapString("!", x + 485, y + 20);

	ofSetColor(255, 200, 0);
	ofDrawBitmapString("couleur seule", x, y + 45);
	ofDrawBitmapString("couleur + motif + symbole", x + 300, y + 45);
}

void ofApp::draw() {
	ofSetColor(255);
	resultat.draw(0, 0);

	ofSetColor(0, 0, 0, 170);
	ofDrawRectangle(0, ofGetHeight() - 110, ofGetWidth(), 110);
	dessinerTest(20, ofGetHeight() - 95);

	ofSetColor(255, 200, 0);
	ofDrawBitmapString("Type " + ofToString(type) + " : " + noms[type] + "  " + frequence[type], 10, 20);
	ofDrawBitmapString("severite " + ofToString(severite, 2) + " (souris)     touches 0 a 3", 10, 40);
}

void ofApp::keyPressed(int key) {
	if (key >= '0' && key <= '3') type = key - '0';
}

// Exercices :
// - "daltoniser" : renforcer les différences que le type choisi ne voit pas, par exemple ajouter à b
//   une partie de (r - r') pour un deutéranope. C'est ce que font les modes daltoniens des jeux.
// - le sépia du cours 11 est une matrice : l'écrire dans ce programme comme type 4
// - vérifier une palette : afficher tes couleurs d'interface dans la vue deutéranopie ; deux couleurs
//   qui se confondent doivent différer aussi par la clarté (cours 11e) ou par un motif
// - la même matrice appliquée sans passer par le linéaire : comparer, la différence est petite mais réelle
