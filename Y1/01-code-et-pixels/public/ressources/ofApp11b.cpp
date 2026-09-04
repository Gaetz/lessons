#include "ofApp11b.h"

float ofApp::versLineaire(float c) { return pow(c / 255.0f, 2.2f); }
float ofApp::versSRGB(float l)     { return 255.0f * pow(ofClamp(l, 0, 1), 1.0f / 2.2f); }

// x est une quantité de lumière qui peut dépasser 1 (le blanc de l'écran).
// Chaque méthode décide quoi faire de ce qui dépasse.
float ofApp::toneMap(float x) {
	switch (methode) {
	case 2:
		// Reinhard : x / (1 + x). Ne dépasse jamais 1, mais y tend doucement.
		// 0.5 -> 0.33, 1 -> 0.5, 4 -> 0.8, 100 -> 0.99. Tout s'aplatit un peu, rien ne brûle.
		return x / (1.0f + x);
	case 3: {
		// ACES : la courbe "filmique" utilisée par Unreal et Unity (approximation de Narkowicz).
		// Comme une pellicule : les ombres sont un peu écrasées, les tons moyens contrastés,
		// les hautes lumières compressées en douceur.
		float a = 2.51f, b = 0.03f, c = 2.43f, d = 0.59f, e = 0.14f;
		return ofClamp((x * (a * x + b)) / (x * (c * x + d) + e), 0, 1);
	}
	default:
		// Couper : tout ce qui dépasse 1 devient 1. Les zones claires deviennent des taches blanches.
		return ofClamp(x, 0, 1);
	}
}

void ofApp::setup() {
	ofSetWindowShape(774, 516);
	if (!source.load("pandaroux.jpg")) {
		ofLogError() << "pandaroux.jpg introuvable dans bin/data";
	}
	resultat.allocate(source.getWidth(), source.getHeight(), OF_IMAGE_COLOR);
	for (int c = 0; c < 256; c++) tableLineaire.push_back(versLineaire(c));
}

void ofApp::calculerImage() {
	int w = source.getWidth();
	int h = source.getHeight();
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			ofColor c = source.getColor(x, y);
			// 1. sRGB -> lumière   2. exposition   3. tone mapping   4. lumière -> sRGB
			float r = toneMap(tableLineaire[c.r] * exposition);
			float g = toneMap(tableLineaire[c.g] * exposition);
			float b = toneMap(tableLineaire[c.b] * exposition);
			resultat.setColor(x, y, ofColor(versSRGB(r), versSRGB(g), versSRGB(b)));
		}
	}
	resultat.update();
}

void ofApp::update() {
	// Exposition de x0.25 à x16, en "stops" : chaque stop double la lumière (comme en photo)
	float stops = (mouseX / (float)ofGetWidth()) * 6 - 2;    // -2 à +4
	exposition = pow(2.0f, stops);
	if (exposition != derniereExposition || methode != derniereMethode) {
		calculerImage();
		derniereExposition = exposition;
		derniereMethode = methode;
	}
}

void ofApp::draw() {
	ofSetColor(255);
	resultat.draw(0, 0);

	// ---- La courbe : lumière d'entrée (0 à 4) en x, lumière de sortie (0 à 1) en y ----
	int gx = 570, gy = 20, gw = 190, gh = 120;
	ofSetColor(0, 0, 0, 160);
	ofFill();
	ofDrawRectangle(gx - 6, gy - 6, gw + 12, gh + 30);
	ofSetColor(120);
	ofDrawRectangle(gx, gy, gw, 1); ofDrawRectangle(gx, gy + gh, gw, 1);
	ofDrawRectangle(gx + gw / 4, gy, 1, gh);            // entrée = 1 : le blanc de l'écran
	ofSetColor(255, 200, 0);
	for (int i = 0; i < gw - 1; i++) {
		float x0 = i / (float)gw * 4, x1 = (i + 1) / (float)gw * 4;
		ofDrawLine(gx + i, gy + gh - toneMap(x0) * gh, gx + i + 1, gy + gh - toneMap(x1) * gh);
	}
	ofDrawBitmapString("entree 0..4   sortie 0..1", gx, gy + gh + 16);

	ofDrawBitmapString("Methode " + ofToString(methode) + " : " + noms[methode], 10, 20);
	ofDrawBitmapString("exposition x" + ofToString(exposition, 2) + "  (souris : -2 a +4 stops)", 10, 40);
	ofDrawBitmapString("Touches 1 couper, 2 Reinhard, 3 ACES", 10, ofGetHeight() - 10);
}

void ofApp::keyPressed(int key) {
	if (key >= '1' && key <= '3') methode = key - '0';
}

// Exercices :
// - une quatrième méthode : Reinhard "étendu" x * (1 + x / (Lb * Lb)) / (1 + x), où Lb est la lumière
//   qui doit devenir exactement blanche (essaie Lb = 4)
// - appliquer le tone mapping sur la luminance seulement et garder les rapports r/g/b : les couleurs
//   saturées ne virent plus au blanc
// - une vraie image HDR : ofFloatImage img; img.load("x.exr" ou ".hdr") donne des valeurs > 1 directement
