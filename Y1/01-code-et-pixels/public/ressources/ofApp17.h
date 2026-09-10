#pragma once
#include "ofMain.h"

// 17 - Convolution : la couleur d'un pixel dépend de ses voisins
// Nouveau : pas de sketch Processing d'origine
// Notions : noyau 3 x 3, somme pondérée des 9 voisins, un seul code pour flou / netteté /
//           contours / relief (seul le noyau change), problème des bords, coût du calcul
//           (recalcul uniquement quand c'est nécessaire), std::vector<float> comme tableau de poids
// Ressource : bin/data/pandaroux.jpg (774 x 516)

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);

	// Applique un noyau 3 x 3 (9 poids, ligne par ligne) à toute l'image.
	// biais est ajouté au résultat (utile quand le noyau donne des valeurs négatives).
	void appliquerNoyau(std::vector<float> noyau, float biais);
	void calculer();

	ofImage source;
	ofImage resultat;
	int  effet { 0 };
	bool aRecalculer { true };
	std::vector<std::string> noms = {
		"original", "flou boite", "flou gaussien", "nettete", "contours", "relief"
	};
};
