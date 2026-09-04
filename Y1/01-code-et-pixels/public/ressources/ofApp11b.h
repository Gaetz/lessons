#pragma once
#include "ofMain.h"

// 11b - HDR, exposition et tone mapping (Reinhard, ACES)
// Nouveau : pas de sketch Processing d'origine
// Notions : une scène réelle a des lumières bien au-dessus de 1 (HDR), l'écran s'arrête à 1 ;
//           l'exposition multiplie la lumière ; le tone mapping est la courbe qui ramène tout
//           sous 1 en écrasant les hautes lumières au lieu de les couper ; tracer une courbe
//           avec ofDrawLine ; f(x) sous forme de fonction qui renvoie un float
// Ressource : bin/data/pandaroux.jpg (774 x 516)

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);

	float versLineaire(float c);
	float versSRGB(float l);
	float toneMap(float x);       // lumière HDR (0 à l'infini) -> lumière écran (0-1)
	void  calculerImage();

	ofImage source;
	ofImage resultat;
	std::vector<float> tableLineaire;

	int   methode = 1;            // 1 couper, 2 Reinhard, 3 ACES
	float exposition = 1;
	float derniereExposition = -1;
	int   derniereMethode = -1;
	std::vector<std::string> noms = { "", "couper (clamp)", "Reinhard", "ACES (courbe filmique)" };
};
