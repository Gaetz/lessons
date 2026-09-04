#include "ofApp11a.h"

// Une valeur sRGB c (0-255) ne mesure pas une quantité de lumière : 128 n'est pas la moitié de 255
// en lumière, mais environ 22 %. La relation est approximativement lumiere = (c / 255) ^ 2.2.
// (La vraie courbe sRGB est en deux morceaux, linéaire près de 0 puis puissance 2.4 ;
//  l'approximation 2.2 suffit largement pour comprendre et pour la plupart des effets.)
float ofApp::versLineaire(float c) {
	return pow(c / 255.0f, 2.2f);
}

float ofApp::versSRGB(float l) {
	l = ofClamp(l, 0, 1);
	return 255.0f * pow(l, 1.0f / 2.2f);
}

void ofApp::setup() {
	ofSetWindowShape(774, 516);
	if (!source.load("pandaroux.jpg")) {
		ofLogError() << "pandaroux.jpg introuvable dans bin/data";
	}
	resultat.allocate(source.getWidth(), source.getHeight(), OF_IMAGE_COLOR);

	// pow() est lent. Il n'y a que 256 valeurs d'entrée possibles : on calcule une fois
	// les 256 résultats dans une table, et on lit la table au lieu de recalculer.
	for (int c = 0; c < 256; c++) {
		tableLineaire.push_back(versLineaire(c));
	}
}

// Vue 3 : diviser (ou multiplier) la lumière. À gauche le calcul naïf sur les valeurs sRGB,
// à droite le calcul juste : sRGB -> linéaire, multiplier, linéaire -> sRGB.
void ofApp::calculerImage() {
	int w = source.getWidth();
	int h = source.getHeight();
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			ofColor c = source.getColor(x, y);
			ofColor sortie;
			if (x < w / 2) {
				// Naïf : on multiplie directement les valeurs 0-255
				sortie = ofColor(ofClamp(c.r * facteur, 0, 255), ofClamp(c.g * facteur, 0, 255), ofClamp(c.b * facteur, 0, 255));
			} else {
				// Juste : on multiplie la LUMIÈRE
				float r = tableLineaire[c.r] * facteur;
				float g = tableLineaire[c.g] * facteur;
				float b = tableLineaire[c.b] * facteur;
				sortie = ofColor(versSRGB(r), versSRGB(g), versSRGB(b));
			}
			resultat.setColor(x, y, sortie);
		}
	}
	resultat.update();
}

void ofApp::update() {
	// 0.25 à 4 : la souris au milieu donne 1 (image inchangée)
	facteur = pow(2.0f, (mouseX / (float)ofGetWidth()) * 4 - 2);
	if (vue == 3 && facteur != dernierFacteur) {
		calculerImage();
		dernierFacteur = facteur;
	}
}

void ofApp::draw() {
	ofBackground(30);
	float w = ofGetWidth();
	ofSetColor(255, 200, 0);

	if (vue == 1) {
		// ---- Dégradés : les valeurs contre la lumière ----
		for (int x = 0; x < w; x++) {
			float p = x / w;                           // 0 à 1
			// Haut : la VALEUR augmente régulièrement. Le milieu (128) paraît déjà très clair.
			ofSetColor(p * 255);
			ofDrawLine(x, 60, x, 180);
			// Bas : la LUMIÈRE augmente régulièrement, donc la valeur suit la courbe inverse.
			// Le milieu paraît à peu près à mi-chemin entre noir et blanc.
			ofSetColor(versSRGB(p));
			ofDrawLine(x, 220, x, 340);
		}
		ofSetColor(255, 200, 0);
		ofDrawBitmapString("valeur 0 -> 255 (ce que l'on ecrit dans ofSetColor)", 10, 50);
		ofDrawBitmapString("lumiere 0 -> 100 % (ce que l'oeil recoit)", 10, 210);
		ofDrawLine(w / 2, 180, w / 2, 220);
		ofDrawBitmapString("milieu : valeur 128 = 22 % de lumiere   |   50 % de lumiere = valeur 186", 10, 380);
	}

	if (vue == 2) {
		// ---- Mélange : damier rouge / vert vu de loin, contre les deux calculs ----
		// Le damier a des cases de 2 px : l'oeil moyenne la LUMIÈRE des deux couleurs.
		for (int y = 100; y < 300; y += 2) {
			for (int x = 60; x < 260; x += 2) {
				bool pair = ((x / 2) + (y / 2)) % 2 == 0;
				if (pair) ofSetColor(255, 0, 0); else ofSetColor(0, 255, 0);
				ofDrawRectangle(x, y, 2, 2);
			}
		}
		// Moyenne naïve : (255 + 0) / 2 = 128 sur chaque canal
		ofSetColor(128, 128, 0);
		ofDrawRectangle(290, 100, 200, 200);
		// Moyenne en lumière : 0.5 de lumière = valeur 186
		float v = versSRGB(0.5f);
		ofSetColor(v, v, 0);
		ofDrawRectangle(520, 100, 200, 200);

		ofSetColor(255, 200, 0);
		ofDrawBitmapString("damier 2 px (recule-toi)", 60, 90);
		ofDrawBitmapString("moyenne des valeurs : 128", 290, 90);
		ofDrawBitmapString("moyenne de la lumiere : 186", 520, 90);
		ofDrawBitmapString("Un flou, un degrade, une transparence : tout melange de couleurs a ce probleme.", 60, 340);
		ofDrawBitmapString("Les moteurs de jeu calculent en lineaire pour que le milieu ressemble au damier.", 60, 360);
	}

	if (vue == 3) {
		ofSetColor(255);
		resultat.draw(0, 0);
		ofSetColor(255, 200, 0);
		ofDrawLine(w / 2, 0, w / 2, ofGetHeight());
		ofDrawBitmapString("naif : valeurs x " + ofToString(facteur, 2), 10, 20);
		ofDrawBitmapString("juste : lumiere x " + ofToString(facteur, 2), w / 2 + 10, 20);
		ofDrawBitmapString("souris : facteur (x0.25 a gauche, x4 a droite, x1 au milieu)", 10, ofGetHeight() - 10);
	}

	ofSetColor(255, 200, 0);
	ofDrawBitmapString("Touches 1 degrades, 2 melange, 3 image", 10, ofGetHeight() - 30);
}

void ofApp::keyPressed(int key) {
	if (key >= '1' && key <= '3') {
		vue = key - '0';
		dernierFacteur = -1;   // force le recalcul de la vue 3
	}
}

// Exercices :
// - remplacer l'approximation 2.2 par la vraie courbe sRGB :
//     lineaire = s <= 0.04045 ? s / 12.92 : pow((s + 0.055) / 1.055, 2.4)
// - refaire le flou boîte du cours 17 en linéaire et comparer sur des zones très contrastées
// - un dégradé entre deux couleurs (cours 09, getLerped) calculé en linéaire : plus lumineux au milieu
