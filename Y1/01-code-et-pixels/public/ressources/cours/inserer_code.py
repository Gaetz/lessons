# Insère (ou remplace) dans chaque cours la section « Le code complet, pas à pas »,
# construite à partir des fichiers ofAppNN.h / ofAppNN.cpp du dossier parent.
# Usage : python3 inserer_code.py     (à relancer après toute modification du code)
import io, os, re

ICI = os.path.dirname(os.path.abspath(__file__))
RACINE = os.path.join(ICI, '..')

LECONS = {
    # Cours 00 à 18 : exclus — ces leçons construisent le code pas à pas
    # elles-mêmes (versions successives d'ofApp.h/.cpp), la section
    # « code complet » y ferait doublon. Ne restent que les leçons du bloc
    # couleur avancée, encore au format concepts + code en annexe.
    '11a-gamma.md': 'ofApp11a', '11b-tone-mapping.md': 'ofApp11b', '11c-lut.md': 'ofApp11c',
    '11d-ycbcr.md': 'ofApp11d', '11e-oklab.md': 'ofApp11e', '11f-daltonisme.md': 'ofApp11f',
    '11g-palette-dithering.md': 'ofApp11g',
}

INTROS = {
    'setup': "Exécuté une fois au lancement : la fenêtre, les chargements, les valeurs de départ.",
    'update': "Exécuté à chaque frame, avant le dessin : tout ce qui change.",
    'draw': "Exécuté à chaque frame, après `update()` : uniquement du dessin.",
    'keyPressed': "Appelé automatiquement à chaque touche pressée.",
}
DEBUT_FONCTION = re.compile(r'^(void|float|int|bool|ofColor|Lab)\s+ofApp::(\w+)\s*\(')

def decouper(lignes):
    """Rend une liste de (nom, lignes). Le premier bloc est l'en-tête (include + commentaires),
    chaque fonction emporte le bloc de commentaires collé juste au-dessus d'elle,
    et un éventuel bloc de commentaires final est rendu à part."""
    debuts = []
    for i, l in enumerate(lignes):
        m = DEBUT_FONCTION.match(l)
        if m:
            j = i
            while j > 0 and lignes[j - 1].startswith('//'):
                j -= 1
            debuts.append((j, m.group(2)))
    blocs = []
    if not debuts:
        return [('fichier', lignes)]
    blocs.append(('entete', lignes[:debuts[0][0]]))
    for k, (j, nom) in enumerate(debuts):
        fin = debuts[k + 1][0] if k + 1 < len(debuts) else len(lignes)
        corps = lignes[j:fin]
        # détacher un bloc de commentaires final (après la dernière accolade fermante)
        if k == len(debuts) - 1:
            idx = max(i for i, l in enumerate(corps) if l.startswith('}'))
            queue = corps[idx + 1:]
            corps = corps[:idx + 1]
            blocs.append((nom, corps))
            if any(l.strip() for l in queue):
                blocs.append(('fin', queue))
        else:
            blocs.append((nom, corps))
    return blocs

def nettoyer(lignes):
    while lignes and not lignes[0].strip(): lignes = lignes[1:]
    while lignes and not lignes[-1].strip(): lignes = lignes[:-1]
    return lignes

def description(nom, corps):
    if nom in INTROS:
        return INTROS[nom]
    for l in corps:
        if l.startswith('//'):
            phrase = l[2:].strip().rstrip(' :.,;')
            return phrase + '.' if phrase else "Fonction `%s()`." % nom
        break
    return "Fonction `%s()`." % nom

def section(base):
    h = io.open(os.path.join(RACINE, base + '.h'), encoding='utf-8').read().splitlines()
    cpp = io.open(os.path.join(RACINE, base + '.cpp'), encoding='utf-8').read().splitlines()
    out = ["## Le code complet, pas à pas", "",
           "Le programme entier, dans l'ordre des fichiers. Les blocs ci-dessous mis bout à bout donnent exactement `%s.cpp`." % base, "",
           "### Le fichier `%s.h`" % base, "",
           "La table des matières du programme : les blocs qui existent et les variables partagées entre eux, avec leurs valeurs de départ.", "",
           "```cpp", *nettoyer(h), "```", ""]
    etape = 0
    for nom, corps in decouper(cpp):
        corps = nettoyer(corps)
        if not corps:
            continue
        if nom == 'entete':
            titre, desc = "En tête du fichier `%s.cpp`" % base, "L'inclusion du `.h`, qui rend visibles les variables partagées et les blocs déclarés."
        elif nom == 'fin':
            titre, desc = "En fin de fichier", "Les notes et pistes laissées en commentaire dans le code."
        else:
            etape += 1
            titre = "Étape %d — `%s()`" % (etape, nom)
            desc = description(nom, corps)
        out += ["### " + titre, "", desc, "", "```cpp", *corps, "```", ""]
    return "\n".join(out).rstrip() + "\n\n"

MARQUE = "## Le code complet, pas à pas"

for doc, base in LECONS.items():
    chemin = os.path.join(ICI, doc)
    texte = io.open(chemin, encoding='utf-8').read()
    # retirer une version précédente
    if MARQUE in texte:
        debut = texte.index(MARQUE)
        suite = re.search(r'^## (?!Le code complet)', texte[debut + len(MARQUE):], re.M)
        fin = debut + len(MARQUE) + suite.start() if suite else len(texte)
        texte = texte[:debut] + texte[fin:]
    # insérer avant la dernière section de résumé
    m = None
    for m in re.finditer(r'^## Ce qu.*$', texte, re.M):
        pass
    if m is None:
        texte = texte.rstrip() + "\n\n" + section(base)
    else:
        texte = texte[:m.start()] + section(base) + texte[m.start():]
    io.open(chemin, 'w', encoding='utf-8').write(texte)
    print('ok', doc)
