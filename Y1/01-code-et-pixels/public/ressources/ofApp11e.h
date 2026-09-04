#pragma once
#include "ofMain.h"

// 11e - Espaces perceptuels : OKLab et OKLCH
// Nouveau : pas de sketch Processing d'origine
// Notions : HSB n'est pas uniforme (un jaune et un bleu de même "B" n'ont pas la même clarté) ;
//           OKLab est un espace où les distances correspondent à ce que l'oeil perçoit ;
//           L, a, b puis version polaire L, C, h (clarté, chroma, teinte) ; dégradés propres ;
//           palettes à clarté constante ; struct à trois float pour transporter une couleur
// Pas d'image : uniquement du dessin.

// Une couleur OKLab : trois nombres. On fabrique notre propre struct (cours 07).
struct Lab {
	float L;   // clarté 0-1
	float a;   // vert (-) / rouge (+)
	float b;   // bleu (-) / jaune (+)
};

class ofApp : public ofBaseApp {
public:
	void setup();
	void draw();
	void keyPressed(int key);

	float versLineaire(float c);
	float versSRGB(float l);
	Lab     versLab(ofColor c);
	ofColor versRGB(Lab lab);
	ofColor depuisLCH(float L, float C, float h);      // h en radians

	void bande(float y, int mode);      // dessine un dégradé de A vers B : 0 RGB, 1 HSB, 2 OKLab

	int paire = 1;
	ofColor A, B;
};
