#pragma once
#include "ofMain.h"

// 11g - Palette indexée et dithering
// Nouveau : pas de sketch Processing d'origine
// Notions : réduire une image à une palette de quelques couleurs (couleur la plus proche par
//           distance RGB, cours 12) ; le dithering casse les aplats en mélangeant deux couleurs
//           de la palette : ordonné (matrice de Bayer) et par diffusion d'erreur (Floyd-Steinberg) ;
//           travailler sur une grille de gros pixels (rendu rétro) ; vector<ofColor> comme palette
// Ressource : bin/data/pandaroux.jpg (774 x 516)

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);

	void    choisirPalette();
	ofColor plusProche(float r, float g, float b);
	void    calculerImage();

	ofImage source;
	ofImage resultat;
	std::vector<ofColor> palette;
	int   numPalette = 0;
	std::vector<std::string> nomsPalette = { "Game Boy (4 verts)", "noir et blanc (2)", "CGA (4)", "PICO-8 (16)" };

	int   methode = 1;               // 1 plus proche, 2 Bayer, 3 Floyd-Steinberg
	int   taillePixel = 3;
	int   derniereMethode = -1, dernierPixel = -1, dernierePalette = -1;
	std::vector<std::string> noms = { "", "couleur la plus proche", "dithering ordonne (Bayer 4x4)", "dithering par diffusion d'erreur (Floyd-Steinberg)" };
};
