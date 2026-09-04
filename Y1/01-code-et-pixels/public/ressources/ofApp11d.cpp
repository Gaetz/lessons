#include "ofApp11d.h"

void ofApp::setup() {
	ofSetWindowShape(774, 516);
	if (!source.load("pandaroux.jpg")) {
		ofLogError() << "pandaroux.jpg introuvable dans bin/data";
	}
	w = source.getWidth();
	h = source.getHeight();
	resultat.allocate(w, h, OF_IMAGE_COLOR);
	decomposer();
}

// RGB -> YCbCr (formules de la norme JPEG).
// Y  : la luminance, exactement le gris "luminance" du cours 11.
// Cb : à quel point la couleur tire vers le bleu (plutôt que le jaune), centré sur 128.
// Cr : à quel point elle tire vers le rouge (plutôt que le vert), centré sur 128.
void ofApp::decomposer() {
	Y  = std::vector<float>(w * h, 0);
	Cb = std::vector<float>(w * h, 0);
	Cr = std::vector<float>(w * h, 0);
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			ofColor c = source.getColor(x, y);
			int i = y * w + x;                    // deux coordonnées -> un indice (cours 17)
			Y[i]  =        0.299f    * c.r + 0.587f    * c.g + 0.114f    * c.b;
			Cb[i] = 128 -  0.168736f * c.r - 0.331264f * c.g + 0.5f      * c.b;
			Cr[i] = 128 +  0.5f      * c.r - 0.418688f * c.g - 0.081312f * c.b;
		}
	}
}

// YCbCr -> RGB, l'inverse exact
ofColor ofApp::recomposer(float y, float cb, float cr) {
	float r = y + 1.402f * (cr - 128);
	float g = y - 0.344136f * (cb - 128) - 0.714136f * (cr - 128);
	float b = y + 1.772f * (cb - 128);
	return ofColor(ofClamp(r, 0, 255), ofClamp(g, 0, 255), ofClamp(b, 0, 255));
}

// Valeur moyenne d'un canal sur le bloc n x n qui contient (x, y).
// Tous les pixels d'un même bloc reçoivent la même valeur : la résolution du canal est divisée par n.
float ofApp::moyenneBloc(std::vector<float>& canal, int x, int y, int n) {
	int x0 = x / n * n;                          // coin du bloc : division entière (cours 14)
	int y0 = y / n * n;
	float somme = 0;
	int compte = 0;
	for (int yy = y0; yy < y0 + n && yy < h; yy++) {
		for (int xx = x0; xx < x0 + n && xx < w; xx++) {
			somme += canal[yy * w + xx];
			compte++;
		}
	}
	return somme / compte;
}

void ofApp::calculerVue() {
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			int i = y * w + x;
			ofColor c;
			switch (vue) {
			case 1: c = ofColor(Y[i]); break;                           // la luminance seule : l'image en gris
			case 2: c = ofColor(Cb[i]); break;                          // Cb seul, en gris : peu de détails
			case 3: c = ofColor(Cr[i]); break;
			case 4: // la couleur en blocs, la luminance intacte : c'est ce que fait JPEG (blocs de 2)
				c = recomposer(Y[i], moyenneBloc(Cb, x, y, tailleBloc), moyenneBloc(Cr, x, y, tailleBloc));
				break;
			case 5: // l'inverse, pour comparer : la luminance en blocs, la couleur intacte
				c = recomposer(moyenneBloc(Y, x, y, tailleBloc), Cb[i], Cr[i]);
				break;
			default: c = recomposer(Y[i], Cb[i], Cr[i]);                // aller-retour : image d'origine
			}
			resultat.setColor(x, y, c);
		}
	}
	resultat.update();
}

void ofApp::update() {
	tailleBloc = 2 + (mouseX / (float)ofGetWidth()) * 30;      // 2 à 32
	if (vue != derniereVue || (vue >= 4 && tailleBloc != dernierBloc)) {
		calculerVue();
		derniereVue = vue;
		dernierBloc = tailleBloc;
	}
}

void ofApp::draw() {
	ofSetColor(255);
	resultat.draw(0, 0);
	ofSetColor(255, 200, 0);
	std::string titre = (vue == 0) ? "aller-retour RGB -> YCbCr -> RGB" : noms[vue];
	ofDrawBitmapString("Vue " + ofToString(vue) + " : " + titre, 10, 20);
	if (vue >= 4) ofDrawBitmapString("blocs de " + ofToString(tailleBloc) + " px (souris)", 10, 40);
	ofDrawBitmapString("Touches 0 a 5", 10, ofGetHeight() - 10);
}

void ofApp::keyPressed(int key) {
	if (key >= '0' && key <= '5') vue = key - '0';
}

// Exercices :
// - afficher Cb et Cr en couleur plutôt qu'en gris : recomposer(128, Cb[i], 128) et recomposer(128, 128, Cr[i])
// - écrire du texte rouge sur fond bleu dans une image, l'enregistrer en JPEG qualité basse, l'ouvrir :
//   les bords bavent. Explique pourquoi avec la vue 4.
// - flou (cours 17) sur Cb et Cr seulement, puis sur Y seulement : lequel abîme l'image ?
// - "chroma key" propre : sélectionner le vert dans le plan (Cb, Cr) plutôt que par teinte HSB
