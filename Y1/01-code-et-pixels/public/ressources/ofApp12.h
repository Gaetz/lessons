#pragma once
#include "ofMain.h"

// 12 - Pointillisme : boucles imbriquées, distance, image
// Sketch d'origine : Cours 2022-2023/rendu04
// Variante intégrée : Cours 2024-2025/sketch_03_image (carrés, anneau qui s'étend avec le temps)
// Notions : double boucle for (celle de 11, avec un pas de 20), distance euclidienne (Pythagore),
//           proportion, lecture de pixel dans une grille, effet local autour de la souris
// Ressource : bin/data/pandaroux.jpg (774 x 516)

class ofApp : public ofBaseApp {
public:
	void setup();
	void draw();

	float distance(float ax, float ay, float bx, float by);

	ofImage img;
	int windowWidth = 774;
	int windowHeight = 516;
	int tailleCercle = 20;
};
