#include "ofApp04.h"
#include <iostream>

void ofApp::setup() {
	ofSetWindowShape(400, 400);
	ofBackground(30);

	// ---- Variables simples et affichage console ----
	// print(x) en Python => std::cout << x << std::endl; en C++
	// La console est visible en configuration Debug dans Visual Studio.
	// (ofLogNotice() << x; est l'équivalent openFrameworks, même destination.)
	int x { 50 };
	float pi { 3.14159f };
	std::string nom = "Gaetan";

	std::cout << x << std::endl;
	std::cout << pi << std::endl;
	std::cout << nom << std::endl;

	for (int i = 0; i < 10; i++) {
		x = x + i * 10;
		std::cout << x << std::endl;
	}

	std::cout << x + pi << std::endl;
	std::cout << "Hello " + nom << std::endl;   // concaténation de std::string

	// ---- Liste de chaînes ----
	// noms = [] en Python => déjà vide à la création en C++ (déclaré dans le .h)
	// noms.append("Annie") => noms.push_back("Annie")
	noms.push_back("Annie");
	noms.push_back("Brand");
	noms.push_back("Callista");
	noms.push_back("Diana");
	noms.push_back("Evelyn");
	noms.push_back("Fiora");
	noms.push_back("Garen");
	noms.push_back("Heimer");
	noms.push_back("Sona");

	// Accès par indice : le premier élément est à l'indice 0
	std::cout << "Deuxieme element : " << noms[1] << std::endl;
	std::cout << "Cinquieme element : " << noms[4] << std::endl;
	std::cout << "Premier element : " << noms[0] << std::endl;

	// Dernier élément : taille - 1 (len(noms) - 1 en Python)
	std::cout << "Dernier element : " << noms[noms.size() - 1] << std::endl;

	// ---- Liste de nombres construite par une boucle ----
	// Créer une liste contenant tous les chiffres entre 0 et 9 inclus
	int compteur { 0 };
	for (int i = 0; i < 10; i++) {
		chiffres.push_back(compteur);
		compteur = compteur + 1;
	}

	// Afficher toute la liste. Python : print(chiffres)
	// C++ ne sait pas afficher un vector directement : on boucle.
	for (int i = 0; i < chiffres.size(); i++) {
		std::cout << chiffres[i] << " ";
	}
	std::cout << std::endl;

	// Afficher un élément sur deux : indices 0, 2, 4, 6, 8
	for (int i = 0; i < 5; i++) {
		std::cout << noms[i * 2] << std::endl;
	}

	// Variante moderne de la boucle, à montrer une fois les indices maîtrisés :
	// for (const std::string& n : noms) { std::cout << n << std::endl; }
}

void ofApp::update() {

}

void ofApp::draw() {
	// Le même contenu affiché dans la fenêtre : ofDrawBitmapString(texte, x, y)
	ofSetColor(255);
	for (int i = 0; i < noms.size(); i++) {
		ofDrawBitmapString(ofToString(i) + " : " + noms[i], 20, 30 + i * 20);
	}

	// Construire une phrase dans une variable texte avant de l'afficher
	std::string ligne = "Chiffres : ";
	for (int i = 0; i < chiffres.size(); i++) {
		ligne = ligne + ofToString(chiffres[i]) + " ";
	}
	ofDrawBitmapString(ligne, 20, 260);
}
