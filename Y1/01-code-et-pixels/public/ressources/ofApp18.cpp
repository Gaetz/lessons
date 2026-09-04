#include "ofApp18.h"

void ofApp::setup() {
	ofSetCircleResolution(16);      // beaucoup de petits cercles : inutile d'être très rond
	chargerImage(images[imageCourante]);
}

void ofApp::chargerImage(std::string nom) {
	if (!source.load(nom)) {
		ofLogError() << nom << " introuvable dans bin/data";
	}
	int w = source.getWidth();
	int h = source.getHeight();
	ofSetWindowShape(w, h);

	// Étape 2 : la toile. Par défaut openFrameworks efface la fenêtre à chaque frame.
	// Un ofFbo est une image dans laquelle on peut dessiner : tout ce qui est dessiné entre
	// begin() et end() s'y accumule, et on l'affiche ensuite comme une ofImage.
	// (ofSetBackgroundAuto(false) donne le même résultat sans FBO, mais se comporte
	// différemment selon les plateformes ; le FBO est la méthode fiable.)
	toile.allocate(w, h, GL_RGB);

	calculerContours();     // étape 4 : une seule fois, c'est le calcul le plus lourd
	recommencer();
}

// Étape 4 : détection de contours, exactement le noyau de 17, mais sur la luminance seulement.
// Le résultat est une image en gris : noir dans les aplats, blanc sur les bords.
void ofApp::calculerContours() {
	int w = source.getWidth();
	int h = source.getHeight();
	contours.allocate(w, h, OF_IMAGE_GRAYSCALE);

	std::vector<float> noyau = { -1, -1, -1,
	                             -1,  8, -1,
	                             -1, -1, -1 };

	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			float somme = 0;
			for (int dy = -1; dy <= 1; dy++) {
				for (int dx = -1; dx <= 1; dx++) {
					int px = ofClamp(x + dx, 0, w - 1);
					int py = ofClamp(y + dy, 0, h - 1);
					ofColor v = source.getColor(px, py);
					float luminance = 0.299f * v.r + 0.587f * v.g + 0.114f * v.b;
					somme += luminance * noyau[(dy + 1) * 3 + (dx + 1)];
				}
			}
			// fabs : un bord clair -> sombre ou sombre -> clair compte pareil
			contours.setColor(x, y, ofColor(ofClamp(fabs(somme), 0, 255)));
		}
	}
	contours.update();
}

// Étape 1 : particules réparties au hasard, chacune avec sa direction
void ofApp::recommencer() {
	posX.clear();
	posY.clear();
	angle.clear();
	for (int i = 0; i < nbParticules; i++) {
		posX.push_back(ofRandom(0, source.getWidth()));
		posY.push_back(ofRandom(0, source.getHeight()));
		angle.push_back(ofRandom(0, TWO_PI));
	}
	effacer = true;
}

void ofApp::update() {
	float dt = ofGetLastFrameTime();
	t = ofGetElapsedTimef();
	int w = source.getWidth();
	int h = source.getHeight();

	for (int i = 0; i < nbParticules; i++) {
		float x = posX[i];
		float y = posY[i];

		// Étape 3 : champ de direction. L'angle ne dépend plus du hasard mais de la position :
		// deux particules voisines prennent presque la même direction, d'où des traits qui
		// s'enroulent (le déphasage de 15). Le temps fait dériver lentement le champ.
		if (champDirection) {
			angle[i] = (sin(x / 80.0f) + cos(y / 80.0f)) * PI + t * 0.1f;
		}

		// Étape 4 : sur un bord (contour fort), la particule ralentit et dévie au hasard.
		// Les traits se brisent en petites touches sur les détails, restent longs dans les aplats.
		float v = vitesse;
		if (suivreFormes) {
			int px = ofClamp(x, 0, w - 1);
			int py = ofClamp(y, 0, h - 1);
			float bord = contours.getColor(px, py).r / 255.0f;    // 0 : plat, 1 : bord net
			v = vitesse * (1 - 0.7f * bord);
			angle[i] += bord * ofRandom(-3, 3) * dt;
		}

		// Étape 6 : la souris repousse. atan2(dy, dx) donne l'angle du vecteur (dx, dy) :
		// c'est l'inverse de cos / sin. Ici le vecteur va de la souris vers la particule.
		if (souris) {
			float d = ofDist(mouseX, mouseY, x, y);
			if (d < 100 && d > 0) {
				angle[i] = atan2(y - mouseY, x - mouseX);
				v = vitesse * 3;
			}
		}

		// Déplacement (06) : la direction en cos / sin (13), la vitesse en pixels par seconde
		posX[i] += cos(angle[i]) * v * dt;
		posY[i] += sin(angle[i]) * v * dt;

		// Sortie de l'image : réapparition n'importe où, les traits restent répartis partout
		if (posX[i] < 0 || posX[i] >= w || posY[i] < 0 || posY[i] >= h) {
			posX[i] = ofRandom(0, w);
			posY[i] = ofRandom(0, h);
			angle[i] = ofRandom(0, TWO_PI);
		}
	}
}

void ofApp::draw() {
	int w = source.getWidth();
	int h = source.getHeight();

	// Étape 2 : tout le dessin des particules va dans la toile, jamais dans la fenêtre
	toile.begin();
	if (effacer) {
		ofClear(0);           // le seul effacement : à la demande
		effacer = false;
	}

	for (int i = 0; i < nbParticules; i++) {
		int px = ofClamp(posX[i], 0, w - 1);
		int py = ofClamp(posY[i], 0, h - 1);

		// Étape 2 : la couleur du pixel de la source sous la particule (10)
		ofColor c = source.getColor(px, py);
		float taille = 3;

		// Étape 4 : touches fines sur les bords, larges dans les aplats
		if (suivreFormes) {
			float bord = contours.getColor(px, py).r / 255.0f;
			taille = 6 - 5 * bord;
		}

		// Étape 5 : chaque particule décale un peu la teinte (09), ce qui casse l'uniformité
		// des aplats, et les zones claires reçoivent des touches plus larges
		if (couleurVivante) {
			float decalage = (i % 21) - 10;                     // -10 à +10 selon la particule
			float teinte = fmod(c.getHue() + decalage + 255, 255);
			c = ofColor::fromHsb(teinte, c.getSaturation(), c.getBrightness());
			taille = taille * (0.5f + c.getBrightness() / 255.0f);
		}

		// Un peu de transparence : les passages successifs se mélangent au lieu de se recouvrir
		ofSetColor(c, 180);
		ofDrawCircle(posX[i], posY[i], taille);
	}
	toile.end();

	ofSetColor(255);
	if (montrerContours) contours.draw(0, 0);
	else                 toile.draw(0, 0);

	ofSetColor(255, 200, 0);
	std::string etat = std::string("3 champ:") + (champDirection ? "on" : "off")
	                 + "  4 formes:" + (suivreFormes ? "on" : "off")
	                 + "  5 couleur:" + (couleurVivante ? "on" : "off")
	                 + "  6 souris:" + (souris ? "on" : "off");
	ofDrawBitmapString(etat + "   espace: effacer   i: image   c: contours", 10, 20);
}

void ofApp::keyPressed(int key) {
	if (key == ' ') effacer = true;
	if (key == '3') champDirection = !champDirection;
	if (key == '4') suivreFormes = !suivreFormes;
	if (key == '5') couleurVivante = !couleurVivante;
	if (key == '6') souris = !souris;
	if (key == 'c') montrerContours = !montrerContours;
	if (key == 'i') {
		imageCourante = (imageCourante + 1) % images.size();    // modulo : retour à 0 après la dernière
		chargerImage(images[imageCourante]);
	}
}

// Pour aller plus loin :
// - remplacer le cercle par un trait : garder la position précédente et tracer ofDrawLine
// - ajouter sa propre image dans bin/data et dans la liste "images"
// - un champ de direction qui suit vraiment les formes : noyau de Sobel horizontal et vertical (17),
//   l'angle du contour est atan2(sobelY, sobelX), la particule prend cet angle + PI / 2
// - remplacer la source par une webcam (ofVideoGrabber) : la peinture suit ce qui bouge
// - sauvegarder la toile : toile.readToPixels(pixels); puis ofSaveImage(pixels, "peinture.png")
