#include "ofApp11e.h"

float ofApp::versLineaire(float c) { return pow(c / 255.0f, 2.2f); }
float ofApp::versSRGB(float l)     { return 255.0f * pow(ofClamp(l, 0, 1), 1.0f / 2.2f); }

// sRGB -> OKLab (Björn Ottosson, 2020). Trois étapes :
// 1. sRGB -> lumière linéaire (cours 11a)
// 2. mélange linéaire vers trois réponses "l, m, s" proches des trois types de cônes de l'oeil
// 3. racine cubique (l'oeil répond de façon compressée) puis mélange vers L, a, b
Lab ofApp::versLab(ofColor c) {
	float r = versLineaire(c.r), g = versLineaire(c.g), bl = versLineaire(c.b);
	float l = 0.4122214708f * r + 0.5363325363f * g + 0.0514459929f * bl;
	float m = 0.2119034982f * r + 0.6806995451f * g + 0.1073969566f * bl;
	float s = 0.0883024619f * r + 0.2817188376f * g + 0.6299787005f * bl;
	l = cbrt(l); m = cbrt(m); s = cbrt(s);
	Lab out;
	out.L = 0.2104542553f * l + 0.7936177850f * m - 0.0040720468f * s;
	out.a = 1.9779984951f * l - 2.4285922050f * m + 0.4505937099f * s;
	out.b = 0.0259040371f * l + 0.7827717662f * m - 0.8086757660f * s;
	return out;
}

// OKLab -> sRGB : les mêmes étapes à l'envers
ofColor ofApp::versRGB(Lab lab) {
	float l = lab.L + 0.3963377774f * lab.a + 0.2158037573f * lab.b;
	float m = lab.L - 0.1055613458f * lab.a - 0.0638541728f * lab.b;
	float s = lab.L - 0.0894841775f * lab.a - 1.2914855480f * lab.b;
	l = l * l * l; m = m * m * m; s = s * s * s;
	float r  =  4.0767416621f * l - 3.3077115913f * m + 0.2309699292f * s;
	float g  = -1.2684380046f * l + 2.6097574011f * m - 0.3413193965f * s;
	float bl = -0.0041960863f * l - 0.7034186147f * m + 1.7076147010f * s;
	return ofColor(versSRGB(r), versSRGB(g), versSRGB(bl));
}

// Version polaire de OKLab, comme HSB est la version polaire de RGB : L clarté, C chroma
// (distance au gris : 0 gris, 0.3 très saturé), h teinte en radians (cours 13 et 16).
ofColor ofApp::depuisLCH(float L, float C, float h) {
	Lab lab;
	lab.L = L;
	lab.a = C * cos(h);
	lab.b = C * sin(h);
	return versRGB(lab);
}

void ofApp::setup() {
	ofSetWindowShape(800, 620);
	keyPressed('1');
}

void ofApp::bande(float y, int mode) {
	float w = ofGetWidth() - 40;
	for (int x = 0; x < w; x++) {
		float p = x / w;
		ofColor c;
		if (mode == 0) {
			// RGB : une ligne droite dans le cube (cours 09). Passe souvent par un gris terne.
			c = A.getLerped(B, p);
		} else if (mode == 1) {
			// HSB : on interpole la teinte par le chemin le plus court sur la roue, plus S et B
			float h1 = A.getHue(), h2 = B.getHue();
			float d = h2 - h1;
			if (d > 127.5f) d -= 255;
			if (d < -127.5f) d += 255;
			float h = fmod(h1 + d * p + 255, 255);
			c = ofColor::fromHsb(h, A.getSaturation() + (B.getSaturation() - A.getSaturation()) * p,
			                        A.getBrightness() + (B.getBrightness() - A.getBrightness()) * p);
		} else {
			// OKLab : ligne droite dans un espace perceptuel. La clarté évolue régulièrement.
			Lab la = versLab(A), lb = versLab(B);
			Lab m;
			m.L = la.L + (lb.L - la.L) * p;
			m.a = la.a + (lb.a - la.a) * p;
			m.b = la.b + (lb.b - la.b) * p;
			c = versRGB(m);
		}
		ofSetColor(c);
		ofDrawLine(20 + x, y, 20 + x, y + 50);
	}
}

void ofApp::draw() {
	ofBackground(30);
	ofSetColor(255, 200, 0);
	ofDrawBitmapString("Degrade entre deux couleurs (touches 1 a 4 pour changer la paire)", 20, 20);
	ofDrawBitmapString("RGB (getLerped)", 20, 45);   bande(50, 0);
	ofSetColor(255, 200, 0);
	ofDrawBitmapString("HSB (teinte par le chemin le plus court)", 20, 120);  bande(125, 1);
	ofSetColor(255, 200, 0);
	ofDrawBitmapString("OKLab", 20, 195);  bande(200, 2);

	// ---- Même "luminosité" HSB, clartés très différentes ----
	ofSetColor(255, 200, 0);
	ofDrawBitmapString("8 teintes HSB avec S = 255 et B = 255 (meme 'luminosite' HSB). Dessous : leur clarte OKLab en gris.", 20, 290);
	for (int i = 0; i < 8; i++) {
		ofColor c = ofColor::fromHsb(i * 255 / 8.0f, 255, 255);
		ofSetColor(c);
		ofDrawRectangle(20 + i * 95, 300, 90, 60);
		float L = versLab(c).L;
		ofSetColor(versSRGB(L * L * L));          // L^3 ~ lumière : on l'affiche comme un gris
		ofDrawRectangle(20 + i * 95, 362, 90, 25);
		ofSetColor(255, 200, 0);
		ofDrawBitmapString("L=" + ofToString(L, 2), 25 + i * 95, 405);
	}

	// ---- Palette à clarté constante en OKLCH : ce que HSB ne sait pas faire ----
	ofDrawBitmapString("8 teintes OKLCH avec L = 0.75 et C = 0.12 : toutes de la meme clarte percue", 20, 450);
	for (int i = 0; i < 8; i++) {
		ofSetColor(depuisLCH(0.75f, 0.12f, i * TWO_PI / 8));
		ofDrawRectangle(20 + i * 95, 460, 90, 60);
	}
	ofSetColor(255, 200, 0);
	ofDrawBitmapString("C'est ainsi qu'on fabrique une palette d'interface ou de graphique lisible :", 20, 550);
	ofDrawBitmapString("meme L pour que rien ne 'crie', et des teintes espacees regulierement.", 20, 570);
}

void ofApp::keyPressed(int key) {
	if (key == '1') { A = ofColor(0, 60, 255);    B = ofColor(255, 230, 0);  paire = 1; }   // bleu -> jaune
	if (key == '2') { A = ofColor(255, 0, 0);     B = ofColor(0, 200, 0);    paire = 2; }   // rouge -> vert
	if (key == '3') { A = ofColor(20, 20, 120);   B = ofColor(255, 255, 255); paire = 3; }  // bleu nuit -> blanc
	if (key == '4') { A = ofColor(255, 0, 255);   B = ofColor(0, 255, 255);  paire = 4; }   // magenta -> cyan
}

// Exercices :
// - la rotation de teinte du cours 11 en OKLCH : convertir chaque pixel, ajouter à h, revenir. Comparer avec HSB.
// - trier une liste de couleurs par clarté L, puis par teinte h
// - "quelle couleur de texte, noir ou blanc, sur ce fond ?" : L > 0.6 => noir, sinon blanc
// - distance entre deux couleurs = distance dans OKLab (cours 12) : refaire la réduction à 5 couleurs avec cette distance
