#include "ofApp06.h"

void ofApp::setup() {
	ofSetWindowShape(400, 400);
}

void ofApp::update() {
	// Delta time : durée de la frame précédente, en secondes (~0.0167 à 60 fps).
	// Multiplier une vitesse par dt rend l'animation indépendante du framerate :
	// même vitesse visible sur une machine à 30 fps et sur une à 144 fps.
	float dt = ofGetLastFrameTime();

	// ---- Déplacement ----
	posX = posX + vx * dt;
	posY = posY + vy * dt;

	// ---- Rebonds : on inverse la vitesse quand on dépasse une limite ----
	if (posY > 180) vy = -vy;
	if (posY < -80) vy = -vy;
	if (posX > 250) vx = -vx;
	if (posX < 0)   vx = -vx;

	// ---- Couleur qui fait des allers-retours entre 0 et 255 ----
	r = r + vr * dt;
	if (r >= 255) vr = -vr;
	if (r <= 0)   vr = -vr;

	g = g + vg * dt;
	if (g >= 255) vg = -vg;
	if (g <= 0)   vg = -vg;

	b = b + vb * dt;
	if (b >= 255) vb = -vb;
	if (b <= 0)   vb = -vb;
}

void ofApp::draw() {
	ofBackground(r, g, b);

	ofSetColor(255);
	ofFill();
	// rect(x, y, w, h) : coin haut-gauche, comme ofDrawRectangle par défaut
	ofDrawRectangle(posX + 100, posY + 100, 100, 100);
	// ellipse(x, y, w, h) : centrée, comme ofDrawEllipse
	ofDrawEllipse(posX + 50, posY + 150, 200, 150);
}
