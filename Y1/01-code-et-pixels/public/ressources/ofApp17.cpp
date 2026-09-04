#include "ofApp17.h"

void ofApp::setup() {
	ofSetWindowShape(774, 516);
	if (!source.load("pandaroux.jpg")) {
		ofLogError() << "pandaroux.jpg introuvable dans bin/data";
	}
	resultat.allocate(source.getWidth(), source.getHeight(), OF_IMAGE_COLOR);
}

void ofApp::appliquerNoyau(std::vector<float> noyau, float biais) {
	int w = source.getWidth();
	int h = source.getHeight();

	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			// On accumule en float : la somme peut dépasser 255 ou passer sous 0 en cours de route
			float r = biais;
			float g = biais;
			float b = biais;

			// Les 9 voisins : dx et dy valent -1, 0 ou 1 (0, 0 est le pixel lui-même)
			for (int dy = -1; dy <= 1; dy++) {
				for (int dx = -1; dx <= 1; dx++) {
					// Problème des bords : le pixel (0, 0) n'a pas de voisin en (-1, -1).
					// Solution la plus simple : on reste dans l'image, le bord remplace le voisin manquant.
					int px = ofClamp(x + dx, 0, w - 1);
					int py = ofClamp(y + dy, 0, h - 1);
					ofColor v = source.getColor(px, py);

					// Poids de ce voisin. Le noyau est rangé ligne par ligne comme la grille
					// qu'il représente : indice = (dy + 1) * 3 + (dx + 1), de 0 à 8.
					float poids = noyau[(dy + 1) * 3 + (dx + 1)];
					r += v.r * poids;
					g += v.g * poids;
					b += v.b * poids;
				}
			}

			resultat.setColor(x, y, ofColor(ofClamp(r, 0, 255), ofClamp(g, 0, 255), ofClamp(b, 0, 255)));
		}
	}
	resultat.update();
}

// Un noyau = 9 poids. Le code au-dessus ne change jamais : seule la "recette" change.
void ofApp::calculer() {
	switch (effet) {

	case 1: // Flou boîte : moyenne des 9 voisins. Poids identiques, somme = 1.
		appliquerNoyau({ 1 / 9.0f, 1 / 9.0f, 1 / 9.0f,
		                 1 / 9.0f, 1 / 9.0f, 1 / 9.0f,
		                 1 / 9.0f, 1 / 9.0f, 1 / 9.0f }, 0);
		break;

	case 2: // Flou gaussien : le centre pèse plus que les coins. Somme = 16, d'où la division.
		appliquerNoyau({ 1 / 16.0f, 2 / 16.0f, 1 / 16.0f,
		                 2 / 16.0f, 4 / 16.0f, 2 / 16.0f,
		                 1 / 16.0f, 2 / 16.0f, 1 / 16.0f }, 0);
		break;

	case 3: // Netteté : le centre renforcé, les voisins retirés. Somme = 1 : la luminosité globale ne bouge pas.
		appliquerNoyau({  0, -1,  0,
		                 -1,  5, -1,
		                  0, -1,  0 }, 0);
		break;

	case 4: // Contours : somme = 0. Une zone uniforme donne 0 (noir), seules les différences restent.
		appliquerNoyau({ -1, -1, -1,
		                 -1,  8, -1,
		                 -1, -1, -1 }, 0);
		break;

	case 5: // Relief : différence entre un coin et son opposé. Biais 128 pour centrer sur le gris.
		appliquerNoyau({ -1, 0, 0,
		                  0, 0, 0,
		                  0, 0, 1 }, 128);
		break;

	default: // 0 : identité, seul le centre compte
		appliquerNoyau({ 0, 0, 0,
		                 0, 1, 0,
		                 0, 0, 0 }, 0);
	}
}

void ofApp::update() {
	// 400 000 pixels x 9 voisins = 3,6 millions de lectures : trop pour chaque frame.
	// On ne recalcule que quand l'effet a changé. Le résultat ne bouge pas entre deux touches.
	if (aRecalculer) {
		calculer();
		aRecalculer = false;
	}
}

void ofApp::draw() {
	ofSetColor(255);
	resultat.draw(0, 0);

	ofSetColor(255, 200, 0);
	ofDrawBitmapString("Effet " + ofToString(effet) + " : " + noms[effet], 10, 20);
	ofDrawBitmapString("Touches 0 a 5 : changer d'effet.", 10, 40);
}

void ofApp::keyPressed(int key) {
	if (key >= '0' && key <= '5') {
		effet = key - '0';
		aRecalculer = true;
	}
}

// Exercices :
// - dessin au crayon : le négatif des contours (reprendre le négatif de 11 sur le résultat)
// - appliquer deux fois le flou : il faut copier resultat dans source entre les deux passes
//   (source = resultat; puis calculer()), ou une troisième image
// - flou 5 x 5 : 25 poids, dx et dy de -2 à 2
// - noyau de Sobel (contours horizontaux -1 -2 -1 / 0 0 0 / 1 2 1), puis verticaux, puis les deux combinés
// - vitesse : remplacer getColor par la lecture directe du tableau source.getPixels(),
//   indice (y * w + x) * 3 pour le rouge, + 1 le vert, + 2 le bleu
