#pragma once
#include "ofMain.h"

// 07a - Traînée évoluée : couleur, transparence, taille
// État final du cours 07 (deuxième partie, corrigé de l'Autonomie)
// Sketch d'origine : Cours 2024-2025/sketch_02_trail
// Notions : paramètres multiples, dégradé de transparence selon l'indice,
//           taille dépendant du temps et de l'indice, réutilisation de la première partie
// Variante écartée : sketch_02a_blqck_trail (identique, fond blanc et soustraction des couleurs)

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();

	void forme(float x, float y, int i, float t, float r, float g, float b);

	std::vector<float> prevX;
	std::vector<float> prevY;
	float r { 0 }, g { 0 }, b { 0 };
	float t { 0 };
};
