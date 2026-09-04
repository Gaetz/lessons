#include "ofApp09.h"

void ofApp::setup() {
	ofSetWindowShape(800, 600);
	ofSetCircleResolution(64);
}

void ofApp::update() {
	t = ofGetElapsedTimef();

	// Même traînée qu'en 07 / 08 : 25 dernières positions de la souris
	prevX.push_back(mouseX);
	prevY.push_back(mouseY);
	if (prevX.size() > 25) {
		prevX.erase(prevX.begin());
		prevY.erase(prevY.begin());
	}
}

void ofApp::draw() {
	ofBackground(30);
	float largeur = ofGetWidth();

	// ---- 1. Les trois axes de HSB, une bande par axe ----
	// Jusqu'ici une couleur = trois quantités de lumière (rouge, vert, bleu) : c'est l'espace RGB,
	// un cube dont les trois axes vont de 0 à 255. Pratique pour l'écran, pénible pour l'humain :
	// "la même couleur, un peu plus claire" ne se calcule pas facilement en RGB.
	// HSB décrit la couleur comme on la nomme : une teinte (position sur la roue des couleurs),
	// une saturation (du gris à la couleur pure) et une luminosité (du noir à la couleur pure).
	// ATTENTION : en openFrameworks les trois vont de 0 à 255, la teinte n'est pas en degrés.
	// ofColor::fromHsb(h, s, b) construit la couleur ; on lui passe le résultat à ofSetColor.
	float teinteChoisie = mouseX / largeur * 255;   // la souris choisit la teinte des bandes 2 et 3

	for (int x = 0; x < largeur; x++) {
		float p = x / largeur * 255;                   // 0 à gauche, 255 à droite

		// Teinte : on fait le tour de la roue, saturation et luminosité au maximum
		ofSetColor(ofColor::fromHsb(p, 255, 255));
		ofDrawLine(x, 20, x, 60);

		// Saturation : du gris (0) à la couleur pure (255), teinte fixée par la souris
		ofSetColor(ofColor::fromHsb(teinteChoisie, p, 255));
		ofDrawLine(x, 70, x, 110);

		// Luminosité : du noir (0) à la couleur pure (255)
		ofSetColor(ofColor::fromHsb(teinteChoisie, 255, p));
		ofDrawLine(x, 120, x, 160);
	}
	ofSetColor(255);
	ofDrawBitmapString("teinte (H)", 10, 15);
	ofDrawBitmapString("saturation (S)", 10, 68);
	ofDrawBitmapString("luminosite (B)", 10, 118);

	// ---- 2. Animer une couleur : la méthode de 08 contre HSB ----
	// En 08, trois cosinus déphasés sur r, g, b : ça bouge, mais on ne contrôle rien
	// (la couleur passe par des gris, des teintes sales, on ne sait pas laquelle vient après).
	float r = (cos(t * 1.2f) / 2 + 0.5f) * 255;
	float g = (cos(t * 1.0f) / 2 + 0.5f) * 255;
	float b = (cos(t * 0.86f) / 2 + 0.5f) * 255;
	ofSetColor(r, g, b);
	ofDrawCircle(150, 260, 60);

	// En HSB : la teinte avance avec le temps, saturation et luminosité restent pleines.
	// fmod est le modulo des float : la teinte repasse à 0 après 255 et fait le tour de la roue.
	float teinte = fmod(t * 40, 255);
	ofSetColor(ofColor::fromHsb(teinte, 255, 255));
	ofDrawCircle(400, 260, 60);

	// ---- 3. Dégradé entre deux couleurs : interpolation ----
	// depart.getLerped(arrivee, p) : p = 0 donne depart, p = 1 donne arrivee, 0.5 le milieu.
	// Chaque canal est interpolé séparément : c'est une droite dans le cube RGB.
	ofColor depart(255, 80, 0);
	ofColor arrivee(0, 120, 255);
	for (int x = 520; x < 780; x++) {
		float p = (x - 520) / 260.0f;
		ofSetColor(depart.getLerped(arrivee, p));
		ofDrawLine(x, 200, x, 320);
	}

	// ---- 4. Teinte selon l'indice : la traînée de 08 avec une seule ligne de couleur ----
	// 25 éléments x 10 = 250 : la traînée parcourt presque toute la roue
	for (int i = 0; i < prevX.size(); i++) {
		ofSetColor(ofColor::fromHsb(i * 10, 255, 255));
		ofDrawCircle(prevX[i], prevY[i], 5 + i);
	}

	// À retenir pour la suite (lecture d'une couleur existante, utilisé en 11) :
	//   c.getHue(), c.getSaturation(), c.getBrightness()   : lire les trois axes HSB d'un ofColor
	//   c.setHue(h)                                        : changer la teinte sans toucher au reste
	//   c.r, c.g, c.b                                      : les trois axes RGB (déjà vus en 06)
	// Comme une couleur est un point dans un cube, la distance entre deux couleurs se calcule
	// comme la distance entre deux points : Pythagore en 3D. On s'en servira en 12.

	// Exercices :
	// - reprendre le rendu de 08 et remplacer les trois cosinus par une teinte qui avance
	// - faire tourner la teinte de la traînée avec le temps (i * 10 + t * 40)
	// - dégradé entre deux couleurs en passant par HSB (interpoler la teinte) : comparer avec getLerped
}
