#include "ofApp13.h"

void ofApp::setup() {
	ofSetWindowShape(800, 800);
	ofSetCircleResolution(64);
}

void ofApp::update() {
	// t oscille entre -1 et 1 : les cercles se rapprochent puis s'éloignent du centre
	t = cos(ofGetElapsedTimef() * 0.6f);
}

void ofApp::draw() {
	ofBackground(0);

	// translate(400, 400) : déplace l'origine au centre de la fenêtre.
	// ofPushMatrix / ofPopMatrix isolent la transformation : après le pop,
	// l'origine est de nouveau en haut à gauche.
	ofPushMatrix();
	ofTranslate(400, 400);

	// Processing : blendMode(DIFFERENCE). openFrameworks n'a pas DIFFERENCE :
	// modes disponibles : ALPHA, ADD, SUBTRACT, MULTIPLY, SCREEN, DISABLED.
	// ADD donne un mélange lumineux (rouge + vert = jaune, les trois = blanc).
	ofEnableBlendMode(OF_BLENDMODE_ADD);

	ofFill();
	for (int i = 0; i < nbCercles; i++) {
		// Couleur alternée selon le reste de la division par 3
		if (i % 3 == 0)      ofSetColor(255, 0, 0);
		else if (i % 3 == 1) ofSetColor(0, 255, 0);
		else                 ofSetColor(0, 0, 255);
		// Variante (cours 09) : la roue des couleurs EST un cercle. Teinte = position sur le tour,
		// le i-ème cercle prend le i-ème secteur de la roue (désactiver ADD pour bien voir) :
		//   ofSetColor(ofColor::fromHsb(i * 255.0f / nbCercles, 255, 255));

		// Angle du i-ème cercle : on divise le tour complet (2 PI) en nbCercles parts
		float angle = i * TWO_PI / nbCercles;
		float x = cos(angle) * rayonOrbite * t;
		float y = -sin(angle) * rayonOrbite * t;   // - car l'axe y de l'écran pointe vers le bas
		ofDrawCircle(x, y, 100);
	}

	ofEnableBlendMode(OF_BLENDMODE_ALPHA);         // retour au mode normal
	ofPopMatrix();

	// ---- Variante sketch_04a_circles ----
	// 120 cercles de rayon 10, fond blanc, OF_BLENDMODE_SUBTRACT,
	// avec un décalage sur x et y pour casser le cercle parfait :
	//   float x = cos(angle) * 400 * t + cos(i * 2.0f) * 20;
	//   float y = -sin(angle) * 400 * t + sin(i / 20.0f) * 100;
}
