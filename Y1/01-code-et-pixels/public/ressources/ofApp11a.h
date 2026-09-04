#pragma once
#include "ofMain.h"

// 11a - Gamma et espace linéaire
// Nouveau : pas de sketch Processing d'origine
// Notions : les valeurs 0-255 d'une image ne sont pas proportionnelles à la quantité de lumière
//           (courbe sRGB, "gamma 2.2") ; passer en linéaire pour calculer, revenir en sRGB pour
//           afficher ; table précalculée (256 entrées) pour éviter pow() sur chaque pixel ;
//           recalcul seulement quand le paramètre change
// Ressource : bin/data/pandaroux.jpg (774 x 516)

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);

	float versLineaire(float c);   // 0-255 sRGB  -> 0-1 lumière
	float versSRGB(float l);       // 0-1 lumière -> 0-255 sRGB
	void  calculerImage();

	ofImage source;
	ofImage resultat;
	std::vector<float> tableLineaire;   // tableLineaire[c] = versLineaire(c), précalculé

	int   vue = 1;                 // 1 dégradés, 2 mélange, 3 image
	float facteur = 0.5f;          // multiplicateur de lumière piloté par la souris (vue 3)
	float dernierFacteur = -1;
};
