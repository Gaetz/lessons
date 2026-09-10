#pragma once
#include "ofMain.h"

// 09 - Couleur : RGB, HSB, dégradés
// Nouveau : pas de sketch Processing d'origine
// Notions : ofColor comme valeur manipulable, espace RGB (un cube à trois axes) et espace HSB
//           (teinte / saturation / luminosité), ofColor::fromHsb, teinte selon le temps et
//           selon l'indice (relit la traînée de 08), interpolation entre deux couleurs (getLerped)

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();

	std::vector<float> prevX;
	std::vector<float> prevY;
	float t { 0 };
};
