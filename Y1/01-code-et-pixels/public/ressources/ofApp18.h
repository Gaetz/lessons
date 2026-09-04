#pragma once
#include "ofMain.h"

// 18 - Projet final : peinture par particules
// Nouveau : pas de sketch Processing d'origine
// Notions : synthèse de la série. Particules dans des vector (03, 04), déplacement par angle et
//           delta time (06, 13), toile qui ne s'efface pas (ofFbo, seule nouveauté), couleur lue
//           sous la particule (10), champ de direction par sin / cos (15), contours calculés une
//           fois avec un noyau (17), teinte et luminosité (09, 11), souris qui repousse (12), clavier.
// Ressources : bin/data/pandaroux.jpg, redpanda.jpg, chibi-redpanda.jpg
//
// Les six étapes du projet sont repérées dans le code. Les étapes 3 à 6 se (dés)activent avec
// les touches 3 à 6, pour voir ce que chacune apporte. Espace : effacer. i : image suivante. c : contours.

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);

	void chargerImage(std::string nom);
	void calculerContours();
	void recommencer();

	ofImage source;
	ofImage contours;         // niveaux de gris : 0 = zone uniforme, 255 = bord net (étape 4)
	ofFbo   toile;            // ce qui a déjà été peint (étape 2)

	std::vector<std::string> images = { "pandaroux.jpg", "redpanda.jpg", "chibi-redpanda.jpg" };
	int imageCourante = 0;

	// Étape 1 : une particule = une position et une direction (angle en radians)
	int nbParticules = 600;
	std::vector<float> posX;
	std::vector<float> posY;
	std::vector<float> angle;
	float vitesse = 80;       // pixels par seconde

	// Étapes activables
	bool champDirection = true;   // 3
	bool suivreFormes = true;     // 4
	bool couleurVivante = true;   // 5
	bool souris = true;           // 6

	bool effacer = false;
	bool montrerContours = false;
	float t = 0;
};
