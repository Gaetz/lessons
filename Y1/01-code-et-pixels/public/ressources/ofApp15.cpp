#include "ofApp15.h"

void ofApp::setup() {
	ofSetWindowShape(screenSize, screenSize);
	tileSize = screenSize / (float)rows;
	radius = tileSize / 2;
}

void ofApp::update() {
	globalAngle = globalAngle + speed * ofGetLastFrameTime();
}

// Dessine un point qui tourne autour du centre de la case (i, j)
void ofApp::drawPoint(int i, int j, float angle) {
	// Déphasage : chaque case a un angle légèrement différent de ses voisines
	angle = angle + i * angleOffset + j * angleOffset;

	// Centre de la case
	float x0 = i * tileSize + tileSize / 2;
	float y0 = j * tileSize + tileSize / 2;

	// Point sur le cercle de rayon "radius" autour de ce centre
	float x = radius * cos(angle) + x0;
	float y = radius * sin(angle) + y0;

	// Décommenter pour visualiser la construction :
	// ofNoFill(); ofSetColor(180); ofDrawCircle(x0, y0, radius);
	// ofDrawLine(x0, y0, x, y);

	ofFill();
	ofSetColor(0);
	ofDrawCircle(x, y, 5);
}

void ofApp::draw() {
	ofBackground(220);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			drawPoint(i, j, globalAngle);
		}
	}
}
