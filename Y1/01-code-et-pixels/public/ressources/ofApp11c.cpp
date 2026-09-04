#include "ofApp11c.h"

void ofApp::setup() {
	ofSetWindowShape(774, 516);
	if (!source.load("pandaroux.jpg")) {
		ofLogError() << "pandaroux.jpg introuvable dans bin/data";
	}
	resultat.allocate(source.getWidth(), source.getHeight(), OF_IMAGE_COLOR);
	lutR = std::vector<int>(256, 0);
	lutG = std::vector<int>(256, 0);
	lutB = std::vector<int>(256, 0);
}

// Courbe en S : écrase un peu les extrêmes, étire le milieu. t * t * (3 - 2 t) est la
// "smoothstep" : vaut 0 en 0, 1 en 1, pente nulle aux deux bouts.
float ofApp::courbeS(float t) {
	return t * t * (3 - 2 * t);
}

// Construire les trois tables. Pour chaque valeur d'entrée i (0-255), on calcule la sortie.
// C'est le "filtre" du cours 11, mais calculé UNE fois pour les 256 valeurs possibles
// au lieu de 400 000 fois par image.
void ofApp::construireLut() {
	for (int i = 0; i < 256; i++) {
		float t = i / 255.0f;          // 0-1
		float r = t, g = t, b = t;     // identité par défaut

		switch (look) {
		case 1: // Contraste : la même courbe en S sur les trois canaux
			r = g = b = courbeS(t);
			break;
		case 2: // Teal & orange, le look du cinéma d'action : les hautes lumières tirent vers
			// l'orange (rouge monte, bleu descend), les ombres vers le bleu-vert (bleu monte, rouge descend)
			r = ofClamp(t + 0.12f * sin(t * PI), 0, 1);               // bosse au milieu : plus de rouge
			g = t;
			b = ofClamp(t - 0.12f * sin(t * PI) + 0.10f * (1 - t), 0, 1); // moins de bleu en clair, plus en sombre
			break;
		case 3: // Vintage : les noirs ne descendent pas sous 12 %, les blancs pas au-dessus de 92 %,
			// et un léger voile chaud
			r = 0.12f + t * 0.80f + 0.04f;
			g = 0.12f + t * 0.80f;
			b = 0.12f + t * 0.76f;
			break;
		case 4: // Négatif : la preuve que les filtres du cours 11 sont des LUT
			r = g = b = 1 - t;
			break;
		}

		// Force : on interpole entre l'identité (t) et le look (r). force = 0.5 => grading à moitié.
		lutR[i] = ofClamp((t + (r - t) * force) * 255, 0, 255);
		lutG[i] = ofClamp((t + (g - t) * force) * 255, 0, 255);
		lutB[i] = ofClamp((t + (b - t) * force) * 255, 0, 255);
	}
}

// Appliquer : plus aucun calcul par pixel, trois lectures de table
void ofApp::appliquerLut() {
	int w = source.getWidth();
	int h = source.getHeight();
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			ofColor c = source.getColor(x, y);
			resultat.setColor(x, y, ofColor(lutR[c.r], lutG[c.g], lutB[c.b]));
		}
	}
	resultat.update();
}

void ofApp::update() {
	force = mouseX / (float)ofGetWidth();
	if (force != derniereForce || look != dernierLook) {
		construireLut();
		appliquerLut();
		derniereForce = force;
		dernierLook = look;
	}
}

void ofApp::draw() {
	ofSetColor(255);
	resultat.draw(0, 0);

	// ---- Les trois courbes : entrée en x, sortie en y ----
	int gx = 600, gy = 20, gs = 150;
	ofSetColor(0, 0, 0, 160);
	ofDrawRectangle(gx - 6, gy - 6, gs + 12, gs + 12);
	ofSetColor(90);
	ofDrawLine(gx, gy + gs, gx + gs, gy);          // la diagonale = identité
	for (int i = 0; i < 255; i++) {
		float x0 = gx + i * gs / 255.0f, x1 = gx + (i + 1) * gs / 255.0f;
		ofSetColor(255, 80, 80);  ofDrawLine(x0, gy + gs - lutR[i] * gs / 255.0f, x1, gy + gs - lutR[i + 1] * gs / 255.0f);
		ofSetColor(80, 255, 80);  ofDrawLine(x0, gy + gs - lutG[i] * gs / 255.0f, x1, gy + gs - lutG[i + 1] * gs / 255.0f);
		ofSetColor(100, 140, 255); ofDrawLine(x0, gy + gs - lutB[i] * gs / 255.0f, x1, gy + gs - lutB[i + 1] * gs / 255.0f);
	}

	ofSetColor(255, 200, 0);
	ofDrawBitmapString("Look " + ofToString(look) + " : " + noms[look] + "   force " + ofToString(force, 2), 10, 20);
	ofDrawBitmapString("Touches 0 a 4 : look.  Souris : force du grading.", 10, ofGetHeight() - 10);
}

void ofApp::keyPressed(int key) {
	if (key >= '0' && key <= '4') look = key - '0';
}

// Exercices :
// - charger une LUT depuis une image : une bande de 256 x 1 pixels, lutR[i] = bande.getColor(i, 0).r
// - créer sa LUT dans un logiciel de retouche : appliquer ses réglages à un dégradé 256 x 1 et l'exporter
// - le seuil, la postérisation et le gamma du cours 11 : tous en LUT
// - LUT 3D (le vrai format .cube du cinéma) : une grille 17 x 17 x 17 de couleurs, chaque (r, g, b)
//   pointe vers la case la plus proche. Une LUT 1D par canal ne peut pas désaturer ; une 3D si.
