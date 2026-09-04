#include "ofApp11g.h"

void ofApp::setup() {
	ofSetWindowShape(774, 516);
	if (!source.load("pandaroux.jpg")) {
		ofLogError() << "pandaroux.jpg introuvable dans bin/data";
	}
	resultat.allocate(source.getWidth(), source.getHeight(), OF_IMAGE_COLOR);
	choisirPalette();
}

void ofApp::choisirPalette() {
	palette.clear();
	switch (numPalette) {
	case 1:
		palette = { ofColor(0), ofColor(255) };
		break;
	case 2: // CGA, palette 1 : noir, cyan, magenta, blanc
		palette = { ofColor(0, 0, 0), ofColor(85, 255, 255), ofColor(255, 85, 255), ofColor(255, 255, 255) };
		break;
	case 3: // PICO-8, la console imaginaire
		palette = { ofColor(0, 0, 0), ofColor(29, 43, 83), ofColor(126, 37, 83), ofColor(0, 135, 81),
		            ofColor(171, 82, 54), ofColor(95, 87, 79), ofColor(194, 195, 199), ofColor(255, 241, 232),
		            ofColor(255, 0, 77), ofColor(255, 163, 0), ofColor(255, 236, 39), ofColor(0, 228, 54),
		            ofColor(41, 173, 255), ofColor(131, 118, 156), ofColor(255, 119, 168), ofColor(255, 204, 170) };
		break;
	default: // Game Boy : quatre nuances de vert
		palette = { ofColor(15, 56, 15), ofColor(48, 98, 48), ofColor(139, 172, 15), ofColor(155, 188, 15) };
	}
}

// La couleur de la palette la plus proche : distance dans le cube RGB (cours 09, 12)
ofColor ofApp::plusProche(float r, float g, float b) {
	float meilleure = 1e9;
	ofColor gagnante = palette[0];
	for (int i = 0; i < palette.size(); i++) {
		float dr = r - palette[i].r, dg = g - palette[i].g, db = b - palette[i].b;
		float d = dr * dr + dg * dg + db * db;       // pas besoin de sqrt pour comparer
		if (d < meilleure) {
			meilleure = d;
			gagnante = palette[i];
		}
	}
	return gagnante;
}

void ofApp::calculerImage() {
	int w = source.getWidth();
	int h = source.getHeight();
	int n = taillePixel;
	int gw = w / n, gh = h / n;                 // la grille de gros pixels

	// Copie flottante de l'image réduite : on aura besoin de modifier les valeurs (diffusion d'erreur)
	std::vector<float> R(gw * gh), G(gw * gh), B(gw * gh);
	for (int j = 0; j < gh; j++) {
		for (int i = 0; i < gw; i++) {
			ofColor c = source.getColor(i * n + n / 2, j * n + n / 2);    // le pixel au centre de la case
			R[j * gw + i] = c.r; G[j * gw + i] = c.g; B[j * gw + i] = c.b;
		}
	}

	// Matrice de Bayer 4 x 4 : 16 seuils répartis "en désordre ordonné", valeurs 0 à 15
	int bayer[16] = { 0, 8, 2, 10,  12, 4, 14, 6,  3, 11, 1, 9,  15, 7, 13, 5 };
	float ecart = 255.0f / palette.size();     // amplitude du décalage : l'écart entre deux couleurs de la palette

	for (int j = 0; j < gh; j++) {
		for (int i = 0; i < gw; i++) {
			int k = j * gw + i;
			// On borne : l'erreur diffusée (méthode 3) peut pousser une valeur hors de 0-255,
			// et une couleur que la palette ne sait pas représenter ferait grossir l'erreur sans fin.
			float r = ofClamp(R[k], 0, 255), g = ofClamp(G[k], 0, 255), b = ofClamp(B[k], 0, 255);

			if (methode == 2) {
				// Ordonné : on décale la couleur d'une valeur qui dépend de la position dans la grille 4 x 4,
				// entre -ecart/2 et +ecart/2. Deux pixels voisins de même couleur d'origine peuvent alors
				// tomber sur deux couleurs différentes de la palette : vu de loin, ça se mélange.
				float d = (bayer[(j % 4) * 4 + (i % 4)] / 16.0f - 0.5f) * ecart;
				r += d; g += d; b += d;
			}

			ofColor q = plusProche(r, g, b);

			if (methode == 3) {
				// Diffusion d'erreur : ce que la palette n'a pas pu représenter (l'erreur) est ajouté
				// aux voisins pas encore traités (à droite, et la ligne du dessous). L'erreur ne se perd pas,
				// elle se compense localement : le ton moyen est respecté.
				float er = r - q.r, eg = g - q.g, eb = b - q.b;
				if (i + 1 < gw)              { R[k + 1]      += er * 7 / 16; G[k + 1]      += eg * 7 / 16; B[k + 1]      += eb * 7 / 16; }
				if (j + 1 < gh && i > 0)     { R[k + gw - 1] += er * 3 / 16; G[k + gw - 1] += eg * 3 / 16; B[k + gw - 1] += eb * 3 / 16; }
				if (j + 1 < gh)              { R[k + gw]     += er * 5 / 16; G[k + gw]     += eg * 5 / 16; B[k + gw]     += eb * 5 / 16; }
				if (j + 1 < gh && i + 1 < gw){ R[k + gw + 1] += er * 1 / 16; G[k + gw + 1] += eg * 1 / 16; B[k + gw + 1] += eb * 1 / 16; }
			}

			// Remplir la case n x n du résultat
			for (int y = j * n; y < j * n + n; y++) {
				for (int x = i * n; x < i * n + n; x++) {
					resultat.setColor(x, y, q);
				}
			}
		}
	}
	resultat.update();
}

void ofApp::update() {
	taillePixel = 1 + (mouseX / (float)ofGetWidth()) * 7;      // 1 à 8
	if (methode != derniereMethode || taillePixel != dernierPixel || numPalette != dernierePalette) {
		calculerImage();
		derniereMethode = methode;
		dernierPixel = taillePixel;
		dernierePalette = numPalette;
	}
}

void ofApp::draw() {
	ofSetColor(255);
	resultat.draw(0, 0);

	// La palette en bas à droite
	for (int i = 0; i < palette.size(); i++) {
		ofSetColor(palette[i]);
		ofDrawRectangle(ofGetWidth() - 20 * palette.size() - 10 + i * 20, ofGetHeight() - 30, 20, 20);
	}

	ofSetColor(255, 200, 0);
	ofDrawBitmapString("Methode " + ofToString(methode) + " : " + noms[methode], 10, 20);
	ofDrawBitmapString("palette : " + nomsPalette[numPalette] + "   pixels de " + ofToString(taillePixel) + " (souris)", 10, 40);
	ofDrawBitmapString("Touches 1 a 3 : methode.  p : palette suivante.", 10, ofGetHeight() - 10);
}

void ofApp::keyPressed(int key) {
	if (key >= '1' && key <= '3') methode = key - '0';
	if (key == 'p') {
		numPalette = (numPalette + 1) % nomsPalette.size();
		choisirPalette();
	}
}

// Exercices :
// - ta propre palette de 8 couleurs, choisies avec le cours 11e pour couvrir les clartés de 0.2 à 0.9
// - la distance en OKLab (11e) au lieu de RGB dans plusProche : les verts et les peaux sont mieux rendus
// - Bayer 8 x 8 (64 seuils) : trame plus fine
// - moyenne de la case n x n au lieu du pixel central (cours 11d, moyenneBloc)
// - dithering en noir et blanc d'un dégradé : la trame rend visible ce que fait chaque méthode
