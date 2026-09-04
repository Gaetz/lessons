#pragma once
#include "ofMain.h"

// 11d - YCbCr : luminance, chrominance et compression
// Nouveau : pas de sketch Processing d'origine
// Notions : séparer une image en luminance (Y) et deux canaux de couleur (Cb, Cr) ; l'oeil voit
//           la luminance finement et la couleur grossièrement ; JPEG et la vidéo réduisent la
//           résolution de Cb et Cr (sous-échantillonnage 4:2:0) ; trois vector<float> comme
//           images intermédiaires, indice y * w + x ; moyenne par blocs
// Ressource : bin/data/pandaroux.jpg (774 x 516)

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);

	void  decomposer();                       // source -> Y, Cb, Cr
	ofColor recomposer(float y, float cb, float cr);
	float moyenneBloc(std::vector<float>& canal, int x, int y, int n);
	void  calculerVue();

	ofImage source;
	ofImage resultat;
	int w = 0, h = 0;
	std::vector<float> Y, Cb, Cr;             // trois "images" de w * h valeurs

	int   vue = 1;
	int   tailleBloc = 2;
	int   dernierBloc = -1, derniereVue = -1;
	std::vector<std::string> noms = { "", "Y seule (luminance)", "Cb seul", "Cr seul", "couleur en blocs (Y intacte)", "luminance en blocs (couleur intacte)" };
};
