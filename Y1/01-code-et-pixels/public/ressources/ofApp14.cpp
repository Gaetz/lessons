#include "ofApp14.h"

void ofApp::setup() {
	ofSetWindowShape(774, 516);
	if (!source.load("pandaroux.jpg")) {
		ofLogError() << "pandaroux.jpg introuvable dans bin/data";
	}
	resultat.allocate(source.getWidth(), source.getHeight(), OF_IMAGE_COLOR);
}

// Demander le pixel -5 ou le pixel 800 lirait n'importe quoi en mémoire (ou planterait) :
// on ramène toujours les coordonnées dans l'image. Le bord est alors "étiré".
ofColor ofApp::lire(float x, float y) {
	int px = ofClamp((int)x, 0, source.getWidth() - 1);
	int py = ofClamp((int)y, 0, source.getHeight() - 1);
	return source.getColor(px, py);
}

void ofApp::update() {
	parametre = mouseX / (float)ofGetWidth();
	t = ofGetElapsedTimef();
	int w = source.getWidth();
	int h = source.getHeight();

	// En 11 la boucle transformait la COULEUR d'un pixel qui restait à sa place.
	// Ici la couleur ne change pas : pour chaque pixel (x, y) du résultat, on calcule
	// à quel endroit de la source aller la chercher. On raisonne toujours depuis la sortie,
	// jamais depuis l'entrée : ainsi chaque pixel du résultat est rempli exactement une fois.
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			ofColor c;

			switch (effet) {

			case 1: // Miroir horizontal : la colonne x vient de la colonne opposée
				c = lire(w - 1 - x, y);
				break;

			case 2: // Rotation de 180 degrés : les deux axes retournés
				c = lire(w - 1 - x, h - 1 - y);
				break;

			case 3: { // Pixelisation : tous les pixels d'une case de n x n lisent le coin de la case.
				// x / n * n n'est pas x : division ENTIÈRE (cours 01). 137 / 20 * 20 = 120.
				int n = 2 + parametre * 40;
				c = lire(x / n * n, y / n * n);
				break;
			}

			case 4: { // Vagues : chaque ligne est décalée d'un sinus qui dépend de y et du temps
				float amplitude = parametre * 40;
				float dx = amplitude * sin(y / 20.0f + t * 3);
				c = lire(x + dx, y);
				break;
			}

			case 5: { // Glitch : les trois canaux ne sont pas lus au même endroit
				float d = parametre * 30;
				ofColor gauche = lire(x - d, y);
				ofColor centre = lire(x, y);
				ofColor droite = lire(x + d, y);
				c = ofColor(gauche.r, centre.g, droite.b);
				break;
			}

			default: // 0 : identité, on lit au même endroit
				c = lire(x, y);
			}

			resultat.setColor(x, y, c);
		}
	}
	resultat.update();
}

void ofApp::draw() {
	ofSetColor(255);
	resultat.draw(0, 0);

	ofSetColor(255, 200, 0);
	ofDrawBitmapString("Effet " + ofToString(effet) + " : " + noms[effet]
	                   + "   parametre = " + ofToString(parametre, 2), 10, 20);
	ofDrawBitmapString("Touches 0 a 5 : changer d'effet.  Souris : parametre.", 10, 40);
}

void ofApp::keyPressed(int key) {
	if (key >= '0' && key <= '5') {
		effet = key - '0';
	}
}

// Exercices :
// - miroir vertical, puis miroir "kaléidoscope" : la moitié droite est le reflet de la moitié gauche
// - vagues verticales (décaler y selon x), puis les deux à la fois
// - répéter au lieu d'étirer : dans lire(), remplacer ofClamp par un modulo (attention aux négatifs)
// - glitch aléatoire : décaler des lignes entières d'une valeur ofRandom, avec ofSeedRandom (cours 03)
// - loupe et tourbillon : ils demandent les coordonnées polaires, on y revient à la fin de 16
