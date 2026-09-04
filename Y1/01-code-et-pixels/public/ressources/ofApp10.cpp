#include "ofApp10.h"

void ofApp::setup() {
	ofSetWindowShape(200, 200);

	// Le chemin est relatif au dossier bin/data du projet, jamais au fichier .cpp.
	// load() renvoie false si le fichier est introuvable : toujours vérifier.
	bool ok = img.load("image2.png");
	if (!ok) {
		ofLogError() << "image2.png introuvable dans bin/data";
	}
}

void ofApp::draw() {
	ofSetColor(255);            // sans ça, l'image est teintée par la dernière couleur
	img.draw(0, 0);

	// get(mouseX, mouseY) en Processing lit le pixel de l'écran.
	// Ici on lit le pixel de l'IMAGE : il faut rester dans ses limites.
	int px = ofClamp(mouseX, 0, img.getWidth() - 1);
	int py = ofClamp(mouseY, 0, img.getHeight() - 1);
	ofColor c = img.getColor(px, py);

	// red(c) / green(c) / blue(c) => c.r / c.g / c.b
	std::string texte = "R=" + ofToString(c.r) + " G=" + ofToString(c.g) + " B=" + ofToString(c.b);

	ofSetColor(255, 200, 0);
	ofDrawBitmapString(texte, 10, 10);

	// Petit carré de la couleur lue, à côté du curseur
	ofSetColor(c);
	ofDrawRectangle(mouseX + 10, mouseY + 10, 20, 20);
}
