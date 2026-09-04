#include "ofApp11.h"

void ofApp::setup() {
	ofSetWindowShape(774, 516);
	if (!source.load("pandaroux.jpg")) {
		ofLogError() << "pandaroux.jpg introuvable dans bin/data";
	}
	// Deux images : on lit dans la source, on écrit dans le résultat.
	// On ne modifie jamais la source : sinon changer d'effet partirait d'une image déjà transformée.
	// allocate réserve une image vide de la même taille, en couleur (3 canaux).
	resultat.allocate(source.getWidth(), source.getHeight(), OF_IMAGE_COLOR);
}

ofColor ofApp::filtre(ofColor c, float p) {
	// Les composantes d'un ofColor sont des unsigned char : entiers de 0 à 255, et 250 + 10
	// ne donne pas 260 mais 4 (ça reboucle). On copie donc dans des float, on calcule,
	// et on borne avec ofClamp avant de reconstruire la couleur.
	float r = c.r;
	float g = c.g;
	float b = c.b;

	// Luminance : gris "perçu". L'oeil est bien plus sensible au vert qu'au bleu,
	// donc un vert pur paraît plus clair qu'un bleu pur de même intensité.
	float luminance = 0.299f * r + 0.587f * g + 0.114f * b;

	switch (effet) {

	case 1: // Négatif : chaque canal est retourné
		return ofColor(255 - r, 255 - g, 255 - b);

	case 2: { // Gris par moyenne : les trois canaux reçoivent la même valeur
		float gris = (r + g + b) / 3;
		return ofColor(gris, gris, gris);
	}

	case 3: // Gris par luminance (un seul argument à ofColor = gris)
		return ofColor(luminance);

	case 4: { // Luminosité : on ajoute la même valeur partout, de -128 à +128 selon la souris
		float k = (p - 0.5f) * 256;
		return ofColor(ofClamp(r + k, 0, 255), ofClamp(g + k, 0, 255), ofClamp(b + k, 0, 255));
	}

	case 5: { // Contraste : on écarte (k > 1) ou on rapproche (k < 1) chaque valeur du milieu 128
		float k = p * 3;
		return ofColor(ofClamp((r - 128) * k + 128, 0, 255),
		               ofClamp((g - 128) * k + 128, 0, 255),
		               ofClamp((b - 128) * k + 128, 0, 255));
	}

	case 6: // Seuil : noir ou blanc, rien entre les deux. Le seuil suit la souris.
		if (luminance < p * 255) return ofColor(0);
		else                     return ofColor(255);

	case 7: { // Postérisation : on arrondit chaque canal à un multiple de "pas".
		// Division entière (cours 01) : floor(137 / 32) * 32 = 128. Moins de niveaux = aplats.
		float pas = 8 + p * 120;              // 8 à 128
		return ofColor(floor(r / pas) * pas, floor(g / pas) * pas, floor(b / pas) * pas);
	}

	// ---- Deuxième partie : passer par HSB (cours 09) ----
	// Ces deux effets sont une ligne en HSB et une horreur en RGB.

	case 8: { // Rotation de teinte : on décale la teinte, saturation et luminosité inchangées
		float teinte = fmod(c.getHue() + p * 255, 255);
		return ofColor::fromHsb(teinte, c.getSaturation(), c.getBrightness());
	}

	case 9: { // Color splash : couleur conservée seulement autour d'une teinte cible, gris ailleurs
		float cible = p * 255;
		float ecart = fabs(c.getHue() - cible);
		if (ecart > 127) ecart = 255 - ecart;   // la roue est circulaire : 250 et 5 sont voisins
		if (ecart < 20) return c;
		return ofColor(luminance);
	}

	default: // 0 : image d'origine
		return c;
	}
}

void ofApp::update() {
	parametre = mouseX / (float)ofGetWidth();   // 0 à gauche, 1 à droite

	// Pour chaque ligne y, pour chaque colonne x : lire, transformer, écrire.
	// Cette double boucle revient en 12, sur une grille de 20 pixels au lieu de chaque pixel.
	for (int y = 0; y < source.getHeight(); y++) {
		for (int x = 0; x < source.getWidth(); x++) {
			ofColor c = source.getColor(x, y);
			resultat.setColor(x, y, filtre(c, parametre));
		}
	}
	// setColor modifie les pixels en mémoire ; update() envoie la nouvelle image à la carte graphique.
	resultat.update();

	// 774 x 516 = 400 000 pixels par frame : ça passe pour ces filtres.
	// Si ça rame : ne recalculer que quand la souris ou l'effet a changé (voir 17),
	// ou lire le tableau de pixels directement au lieu de getColor / setColor.
}

void ofApp::draw() {
	ofSetColor(255);
	resultat.draw(0, 0);

	ofSetColor(255, 200, 0);
	ofDrawBitmapString("Effet " + ofToString(effet) + " : " + noms[effet]
	                   + "   parametre = " + ofToString(parametre, 2), 10, 20);
	ofDrawBitmapString("Touches 0 a 9 : changer d'effet.  Souris : parametre.", 10, 40);
}

void ofApp::keyPressed(int key) {
	// key est le code du caractère : '0' vaut 48, '1' vaut 49... d'où la soustraction.
	if (key >= '0' && key <= '9') {
		effet = key - '0';
	}
}

// Exercices :
// - sépia : chaque canal de sortie mélange les trois canaux d'entrée
//     r' = 0.393 r + 0.769 g + 0.189 b, g' = 0.349 r + 0.686 g + 0.168 b, b' = 0.272 r + 0.534 g + 0.131 b
// - échange de canaux : ofColor(g, b, r). Isoler un canal : ofColor(r, 0, 0)
// - afficher la teinte, la saturation ou la luminosité seule, en niveaux de gris
// - gamma : 255 * pow(r / 255, k), même chose pour g et b
// - chromakey : si la teinte est proche du vert, remplacer le pixel par une autre image
