#pragma once
#include "ofMain.h"

// 00 - Premier contact : une tête (version minimale)
// Objectif : créer quelque chose dès la première séance, par modification du code.
// On y rencontre les trois idées fondatrices : appeler une fonction, lui donner
// des paramètres, nommer un nombre dans une variable.
// La version complète (souris + fond animé) est dans ofApp00a.

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
};
