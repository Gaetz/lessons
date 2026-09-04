#pragma once
#include "ofMain.h"

// 11f - Daltonisme et accessibilité
// Nouveau : pas de sketch Processing d'origine
// Notions : simuler la vision d'un daltonien avec une matrice 3 x 3 appliquée à chaque pixel
//           (chaque canal de sortie est un mélange des trois canaux d'entrée, comme le sépia) ;
//           les trois types (protanopie, deutéranopie, tritanopie) ; sévérité par interpolation
//           avec l'identité ; règle d'accessibilité : ne jamais coder une information par la
//           couleur seule ; std::vector<float> de 9 valeurs comme matrice, indice ligne * 3 + colonne
// Ressource : bin/data/pandaroux.jpg (774 x 516)

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);

	float   versLineaire(float c);
	float   versSRGB(float l);
	ofColor simuler(ofColor c);
	void    calculerImage();
	void    dessinerTest(float x, float y);

	ofImage source;
	ofImage resultat;
	std::vector<float> matrice;      // 9 valeurs, ligne par ligne
	std::vector<float> tableLineaire;

	int   type = 0;                  // 0 normal, 1 protanopie, 2 deutéranopie, 3 tritanopie
	float severite = 1;
	int   dernierType = -1;
	float derniereSeverite = -1;
	std::vector<std::string> noms = { "vision normale", "protanopie (pas de cones rouges)", "deuteranopie (pas de cones verts)", "tritanopie (pas de cones bleus)" };
	std::vector<std::string> frequence = { "", "~1 % des hommes", "~6 % des hommes (la plus courante)", "tres rare" };
};
