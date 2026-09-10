# Génère les illustrations mémoire du cours 00 :
#   00-variable-boite.png  — une variable = une boîte étiquetée dans la mémoire
#   00-octet-binaire.png   — l'octet, les bits, compter en binaire
# Usage : python generer_d.py   (nécessite Pillow)
from PIL import Image, ImageDraw, ImageFont
import os

OUT = os.path.dirname(os.path.abspath(__file__))

ORANGE = (234, 80, 39)
BLEU = (15, 111, 165)
ENCRE = (20, 20, 20)
GRIS = (150, 150, 150)
GRIS_CLAIR = (235, 235, 230)
FOND = (255, 255, 255)


def font(size=14, bold=False):
    for name in (['/System/Library/Fonts/Menlo.ttc'] if not bold else ['/System/Library/Fonts/Menlo.ttc']):
        try:
            return ImageFont.truetype(name, size, index=1 if bold else 0)
        except Exception:
            pass
    return ImageFont.load_default(size=size)


def img_variable_boite():
    W, H = 960, 400
    im = Image.new('RGB', (W, H), FOND)
    d = ImageDraw.Draw(im)

    # La rangée de boîtes anonymes
    y0, bh = 170, 110
    xs = [70, 180, 290, 560, 680, 800]
    for x in xs:
        d.rectangle([x, y0, x + 100, y0 + bh], outline=GRIS, width=2)
        d.text((x + 50, y0 + bh / 2), '?', font=font(26), fill=GRIS, anchor='mm')

    # La boîte de la variable x, plus large (mise en avant)
    bx, bw = 400, 130
    d.rectangle([bx, y0, bx + bw, y0 + bh], outline=ORANGE, width=5)
    d.text((bx + bw / 2, y0 + bh / 2), '100', font=font(40, bold=True), fill=ENCRE, anchor='mm')

    # L'étiquette (le nom), accrochée au-dessus
    ex, ey, ew, eh = bx + bw / 2 - 45, y0 - 62, 90, 40
    d.line([bx + bw / 2, ey + eh, bx + bw / 2, y0], fill=ORANGE, width=3)
    d.rounded_rectangle([ex, ey, ex + ew, ey + eh], radius=8, fill=ORANGE)
    d.text((ex + ew / 2, ey + eh / 2), 'x', font=font(28, bold=True), fill=FOND, anchor='mm')

    # La taille, sous la boîte
    ty = y0 + bh + 26
    d.line([bx, ty, bx + bw, ty], fill=BLEU, width=3)
    d.line([bx, ty - 8, bx, ty + 8], fill=BLEU, width=3)
    d.line([bx + bw, ty - 8, bx + bw, ty + 8], fill=BLEU, width=3)
    d.text((bx + bw / 2, ty + 16), 'int : 4 octets', font=font(20), fill=BLEU, anchor='ma')

    # Annotations
    d.text((480, 30), 'la mémoire : une rangée de boîtes', font=font(20), fill=ENCRE, anchor='ma')
    d.text((250, 84), "l'étiquette : le NOM", font=font(18), fill=ORANGE, anchor='rm')
    d.line([260, 84, ex - 12, 84], fill=ORANGE, width=2)
    d.text((720, y0 + bh + 42), 'la taille : le TYPE', font=font(18), fill=BLEU, anchor='lm')
    d.line([710, y0 + bh + 42, bx + bw + 12, y0 + bh + 42], fill=BLEU, width=2)
    d.text((480, 360), 'int x { 100 };', font=font(24, bold=True), fill=ENCRE, anchor='ma')

    im.save(os.path.join(OUT, '00-variable-boite.png'))
    print('ok 00-variable-boite.png')


def img_octet_binaire():
    W, H = 960, 520
    im = Image.new('RGB', (W, H), FOND)
    d = ImageDraw.Draw(im)

    # --- L'octet : 8 bits, avec la valeur de chaque case ---
    d.text((480, 24), 'un octet = 8 bits — chaque bit vaut 0 ou 1', font=font(20), fill=ENCRE, anchor='ma')
    bits = [0, 0, 1, 0, 1, 1, 0, 1]           # 32 + 8 + 4 + 1 = 45
    poids = [128, 64, 32, 16, 8, 4, 2, 1]
    bw, bh, x0, y0 = 90, 76, 80, 88
    for i, (b, p) in enumerate(zip(bits, poids)):
        x = x0 + i * (bw + 10)
        col = ORANGE if b else GRIS
        fill = (252, 233, 226) if b else FOND
        d.rectangle([x, y0, x + bw, y0 + bh], outline=col, width=4, fill=fill)
        d.text((x + bw / 2, y0 + bh / 2), str(b), font=font(36, bold=True),
               fill=ORANGE if b else GRIS, anchor='mm')
        d.text((x + bw / 2, y0 + bh + 12), str(p), font=font(18),
               fill=BLEU if b else GRIS, anchor='ma')
    d.text((x0, y0 + bh + 44), 'la valeur de chaque case double vers la gauche : 1, 2, 4, 8, 16…',
           font=font(17), fill=BLEU, anchor='la')
    d.text((480, y0 + bh + 84), 'on additionne les cases à 1 :   32 + 8 + 4 + 1 = 45',
           font=font(22, bold=True), fill=ENCRE, anchor='ma')

    # --- Compter en binaire ---
    ty = 330
    d.text((80, ty), 'compter en binaire :', font=font(20), fill=ENCRE, anchor='la')
    table = [('0', '0'), ('1', '1'), ('2', '10'), ('3', '11'), ('4', '100'), ('5', '101'), ('6', '110')]
    for i, (dec, bin_) in enumerate(table):
        x = 120 + i * 105
        d.text((x, ty + 44), dec, font=font(22, bold=True), fill=ENCRE, anchor='ma')
        d.text((x, ty + 78), bin_, font=font(22), fill=ORANGE, anchor='ma')
    d.line([100, ty + 70, 830, ty + 70], fill=GRIS, width=1)

    d.text((480, ty + 130), '8 bits → 256 nombres (0 à 255)     un int = 4 octets = 32 bits',
           font=font(19), fill=BLEU, anchor='ma')

    im.save(os.path.join(OUT, '00-octet-binaire.png'))
    print('ok 00-octet-binaire.png')


def img_sans_deltatime():
    # 06 : deux machines, même durée, sans delta time -> distances différentes
    W, H = 960, 430
    im = Image.new('RGB', (W, H), FOND)
    d = ImageDraw.Draw(im)

    d.text((480, 22), 'sans delta time :  posX = posX + 1  a chaque frame', font=font(20, bold=True), fill=ENCRE, anchor='ma')

    x0, x1 = 240, 700            # même axe de temps : UNE seconde pour les deux
    def piste(y, frames, col, l1, l2):
        d.line([x0, y, x1 + 120, y], fill=(220, 220, 215), width=2)
        step = (x1 - x0) / frames
        for k in range(frames + 1):
            x = x0 + k * step
            d.line([x, y - 5, x, y + 5], fill=col, width=2)
        # l'objet : il a parcouru "frames" unités -> position proportionnelle
        ox = x0 + (x1 - x0) * (frames / 12.0)
        d.ellipse([ox - 14, y - 14, ox + 14, y + 14], fill=col)
        d.text((30, y - 11), l1, font=font(17), fill=col, anchor='lm')
        d.text((30, y + 11), l2, font=font(15), fill=col, anchor='lm')
        return ox

    oa = piste(140, 12, ORANGE, 'machine A', '60 frames/s')
    ob = piste(260, 6, BLEU, 'machine B', '30 frames/s')

    d.text((x0, 96), 'chaque trait = une frame (un « +1 »)', font=font(15), fill=GRIS, anchor='lm')
    d.line([x0, 330, x1, 330], fill=ENCRE, width=2)
    d.line([x0, 322, x0, 338], fill=ENCRE, width=2)
    d.line([x1, 322, x1, 338], fill=ENCRE, width=2)
    d.text(((x0 + x1) / 2, 344), 'la MEME seconde s\'est ecoulee', font=font(16), fill=ENCRE, anchor='ma')

    d.text((oa, 108), '12 pas', font=font(15, bold=True), fill=ORANGE, anchor='mb')
    d.text((ob, 228), '6 pas seulement', font=font(15, bold=True), fill=BLEU, anchor='mb')

    d.text((480, 392), 'avec  posX = posX + vitesse * dt :  les deux machines arrivent au meme endroit',
           font=font(17, bold=True), fill=ENCRE, anchor='ma')

    im.save(os.path.join(OUT, '06-sans-deltatime.png'))
    print('ok 06-sans-deltatime.png')


img_variable_boite()
img_octet_binaire()
img_sans_deltatime()


# ============================================================
# Série d'illustrations pédagogiques des cours 00 à 06
# ============================================================

def fleche(d, x0, y0, x1, y1, col, w=3, tete=9):
    d.line([x0, y0, x1, y1], fill=col, width=w)
    import math
    a = math.atan2(y1 - y0, x1 - x0)
    for s in (-0.45, 0.45):
        d.line([x1, y1, x1 - tete * math.cos(a + s) * 1.6, y1 - tete * math.sin(a + s) * 1.6], fill=col, width=w)


def img_anatomie_appel():
    W, H = 960, 340
    im = Image.new('RGB', (W, H), FOND)
    d = ImageDraw.Draw(im)
    txt = 'ofSetWindowShape(800, 800);'
    fs = 30
    f = font(fs, bold=True)
    tw = d.textlength(txt, font=f)
    x0 = (W - tw) / 2
    y = 160
    d.text((x0, y), txt, font=f, fill=ENCRE, anchor='lm')

    cw = tw / len(txt)
    def cx(i0, i1):
        return x0 + (i0 + i1) / 2 * cw

    # le nom (chars 0..15)
    nx = cx(0, 16)
    d.text((nx, 52), 'le NOM de la fonction', font=font(18, bold=True), fill=ORANGE, anchor='ma')
    fleche(d, nx, 82, nx, y - 26, ORANGE)
    # les paramètres (chars 17..24)
    px = cx(16, 26)
    d.text((px, 268), 'les PARAMETRES, separes par des virgules', font=font(18, bold=True), fill=BLEU, anchor='ma')
    fleche(d, px, 262, px, y + 26, BLEU)
    # le point-virgule (char 26)
    sx = cx(26, 27)
    d.text((sx + 60, 52), 'le ; termine', font=font(18, bold=True), fill=GRIS, anchor='ma')
    d.text((sx + 60, 76), "l'appel", font=font(18, bold=True), fill=GRIS, anchor='ma')
    fleche(d, sx + 60, 104, sx + 4, y - 26, GRIS)
    im.save(os.path.join(OUT, '00-anatomie-appel.png')); print('ok 00-anatomie-appel.png')


def img_opacite():
    W, H = 960, 360
    im = Image.new('RGBA', (W, H), FOND + (255,))
    d = ImageDraw.Draw(im)
    d.text((240, 30), 'opacite 255 : recouvre', font=font(19, bold=True), fill=ENCRE, anchor='ma')
    d.text((720, 30), 'opacite 150 : se melange', font=font(19, bold=True), fill=ENCRE, anchor='ma')
    # paire opaque
    d.ellipse([120, 100, 300, 280], fill=(235, 235, 230), outline=GRIS, width=2)
    d.ellipse([200, 100, 380, 280], fill=ORANGE)
    # paire transparente
    d.ellipse([600, 100, 780, 280], fill=(235, 235, 230), outline=GRIS, width=2)
    ov = Image.new('RGBA', (W, H), (0, 0, 0, 0))
    od = ImageDraw.Draw(ov)
    od.ellipse([680, 100, 860, 280], fill=ORANGE + (150,))
    im = Image.alpha_composite(im, ov)
    d = ImageDraw.Draw(im)
    d.text((240, 310), 'ofSetColor(234, 80, 39)', font=font(16), fill=GRIS, anchor='ma')
    d.text((720, 310), 'ofSetColor(234, 80, 39, 150)', font=font(16), fill=GRIS, anchor='ma')
    im.convert('RGB').save(os.path.join(OUT, '00-opacite.png')); print('ok 00-opacite.png')


def mini_tete(d, cx, cy, s, alpha_bg=None):
    # une tête simplifiée à l'échelle s (s = rayon du visage)
    d.ellipse([cx - s, cy - s, cx + s, cy + s], fill=(240, 240, 236), outline=ENCRE, width=2)
    r = s * 0.22
    for ex in (-s * 0.45, s * 0.45):
        d.ellipse([cx + ex - r, cy - s * 0.35 - r, cx + ex + r, cy - s * 0.35 + r], fill=ORANGE)
    d.rectangle([cx - s * 0.5, cy + s * 0.3, cx + s * 0.5, cy + s * 0.55], fill=ENCRE)


def img_fonction_tampon():
    W, H = 960, 400
    im = Image.new('RGB', (W, H), FOND)
    d = ImageDraw.Draw(im)
    # la fonction = un tampon
    d.rounded_rectangle([60, 90, 340, 330], radius=14, outline=ORANGE, width=5)
    d.text((200, 66), 'void funnyFace(int x, int y)', font=font(17, bold=True), fill=ORANGE, anchor='ma')
    mini_tete(d, 200, 205, 70)
    d.text((200, 296), 'le dessin, ecrit UNE fois', font=font(15), fill=GRIS, anchor='ma')
    # la fenêtre où on tamponne
    d.rectangle([520, 60, 900, 360], outline=ENCRE, width=3)
    mini_tete(d, 620, 150, 52)
    mini_tete(d, 800, 280, 52)
    d.text((620, 216), 'funnyFace(100, 100)', font=font(14, bold=True), fill=BLEU, anchor='ma')
    d.text((800, 346 - 130), 'funnyFace(400, 400)', font=font(14, bold=True), fill=BLEU, anchor='ma')
    fleche(d, 350, 160, 555, 140, ORANGE)
    fleche(d, 350, 250, 735, 280, ORANGE)
    d.text((430, 178), 'un appel =', font=font(15, bold=True), fill=ORANGE, anchor='ma')
    d.text((430, 200), 'un tampon', font=font(15, bold=True), fill=ORANGE, anchor='ma')
    im.save(os.path.join(OUT, '00-fonction-tampon.png')); print('ok 00-fonction-tampon.png')


def img_deduire():
    W, H = 960, 460
    im = Image.new('RGB', (W, H), FOND)
    d = ImageDraw.Draw(im)
    d.text((480, 20), 'float x = sizeX / 2.0f;   ...   ofDrawCircle(x, y, 37.5f);', font=font(19, bold=True), fill=ENCRE, anchor='ma')
    def fenetre(x0, y0, taille, label):
        d.rectangle([x0, y0, x0 + taille, y0 + taille], outline=ENCRE, width=3, fill=(235, 235, 230))
        cx, cy = x0 + taille / 2, y0 + taille * 0.75
        r = taille * 0.09
        d.ellipse([cx - r, cy - r, cx + r, cy + r], fill=ORANGE)
        d.line([cx, y0, cx, y0 + taille], fill=BLEU, width=1)
        d.text((x0 + taille / 2, y0 + taille + 12), label, font=font(16), fill=ENCRE, anchor='ma')
    fenetre(140, 80, 180, 'fenetre 400 x 400')
    fenetre(480, 60, 300, 'fenetre 800 x 800 : MEME code')
    d.text((480, H - 30), 'le cercle reste au milieu : la position est DEDUITE, pas devinee', font=font(17, bold=True), fill=BLEU, anchor='ma')
    im.save(os.path.join(OUT, '01-deduire.png')); print('ok 01-deduire.png')


def img_division_entiere():
    W, H = 960, 340
    im = Image.new('RGB', (W, H), FOND)
    d = ImageDraw.Draw(im)
    # côté int
    d.text((240, 60), 'int : 7 / 2', font=font(26, bold=True), fill=ENCRE, anchor='ma')
    fleche(d, 240, 110, 240, 150, ENCRE)
    d.text((240, 160), '3', font=font(40, bold=True), fill=ORANGE, anchor='ma')
    # la virgule à la poubelle
    d.text((330, 200), ',5', font=font(24, bold=True), fill=GRIS, anchor='ma')
    fleche(d, 335, 190, 355, 240, GRIS, w=2)
    d.rectangle([330, 245, 390, 300], outline=GRIS, width=3)
    d.line([322, 245, 398, 245], fill=GRIS, width=3)
    d.text((240, 250), 'la partie apres la virgule', font=font(15), fill=GRIS, anchor='ra')
    d.text((240, 272), 'est JETEE', font=font(15, bold=True), fill=GRIS, anchor='ra')
    # séparateur
    d.line([480, 40, 480, 300], fill=(220, 220, 215), width=2)
    # côté float
    d.text((720, 60), 'float : 7 / 2.0f', font=font(26, bold=True), fill=ENCRE, anchor='ma')
    fleche(d, 720, 110, 720, 150, ENCRE)
    d.text((720, 160), '3.5', font=font(40, bold=True), fill=BLEU, anchor='ma')
    d.text((720, 250), 'un float dans la division', font=font(15), fill=BLEU, anchor='ma')
    d.text((720, 272), 'sauve la virgule', font=font(15, bold=True), fill=BLEU, anchor='ma')
    im.save(os.path.join(OUT, '01-division-entiere.png')); print('ok 01-division-entiere.png')


def img_deroule_boucle():
    W, H = 960, 360
    im = Image.new('RGB', (W, H), FOND)
    d = ImageDraw.Draw(im)
    d.text((480, 22), 'for (int i = 0; i < 10; i++) { corps }', font=font(20, bold=True), fill=ENCRE, anchor='ma')
    y = 150
    xs = [70, 230, 390, 550, 660, 810]
    labels = ['i = 0', 'i = 1', 'i = 2', '...', 'i = 9', 'i = 10']
    for k, (x, lab) in enumerate(zip(xs, labels)):
        last = (k == len(xs) - 1)
        col = ORANGE if not last else (180, 30, 30)
        if lab == '...':
            d.text((x + 30, y + 27), '...', font=font(24, bold=True), fill=GRIS, anchor='ma')
        else:
            d.rounded_rectangle([x, y, x + 105, y + 68], radius=10, outline=col, width=4)
            d.text((x + 52, y + 22), lab, font=font(19, bold=True), fill=col, anchor='mm')
            d.text((x + 52, y + 48), '10<10 FAUX' if last else 'corps', font=font(13), fill=col, anchor='mm')
        if k < len(xs) - 1:
            x_next = xs[k + 1]
            fleche(d, x + (105 if lab != '...' else 62), y + 34, x_next - 8, y + 34, GRIS, w=2)
    d.text((862, y + 96), 'SORTIE : le corps ne tourne pas', font=font(15, bold=True), fill=(180, 30, 30), anchor='ra')
    d.text((480, 290), 'le corps tourne 10 fois, i valant 0 a 9 - JAMAIS 10', font=font(18, bold=True), fill=ENCRE, anchor='ma')
    im.save(os.path.join(OUT, '02-deroule-boucle.png')); print('ok 02-deroule-boucle.png')


def img_graine():
    W, H = 960, 420
    im = Image.new('RGB', (W, H), FOND)
    d = ImageDraw.Draw(im)
    suites = {42: ['0.73', '0.12', '0.58', '0.91', '0.34'], 43: ['0.28', '0.66', '0.05', '0.49', '0.87']}
    points = {42: [(18, 30), (64, 12), (40, 52), (78, 44), (10, 66)], 43: [(70, 20), (22, 40), (55, 60), (12, 14), (82, 68)]}
    def rangee(y, graine, note, col):
        d.text((40, y + 40), 'ofSeedRandom(%d)' % graine, font=font(18, bold=True), fill=col, anchor='lm')
        fleche(d, 285, y + 40, 330, y + 40, GRIS, w=2)
        d.text((350, y + 40), ' '.join(suites[graine]), font=font(18), fill=ENCRE, anchor='lm')
        fleche(d, 640, y + 40, 685, y + 40, GRIS, w=2)
        d.rectangle([700, y, 800, y + 80], outline=col, width=3, fill=(245, 245, 242))
        for px, py in points[graine]:
            d.ellipse([700 + px - 4, y + py * 80 / 80 - 4, 700 + px + 4, y + py + 4], fill=col)
        d.text((820, y + 40), note, font=font(15, bold=True), fill=col, anchor='lm')
    rangee(40, 42, 'un dessin', ORANGE)
    rangee(150, 42, 'LE MEME', ORANGE)
    rangee(260, 43, 'un autre', BLEU)
    d.text((480, 380), 'meme graine -> meme suite -> meme dessin', font=font(19, bold=True), fill=ENCRE, anchor='ma')
    im.save(os.path.join(OUT, '03-graine.png')); print('ok 03-graine.png')


def img_trajet_listes():
    W, H = 960, 400
    im = Image.new('RGB', (W, H), FOND)
    d = ImageDraw.Draw(im)
    def boite(x, titre, soustitre, col):
        d.rounded_rectangle([x, 90, x + 260, 290], radius=12, outline=col, width=4)
        d.text((x + 130, 66), titre, font=font(19, bold=True), fill=col, anchor='ma')
        d.text((x + 130, 300), soustitre, font=font(14), fill=GRIS, anchor='ma')
        return x + 130
    c1 = boite(40, 'ofApp.h', 'DECLARER - une fois', ENCRE)
    c2 = boite(350, 'setup()', 'REMPLIR - une fois', ORANGE)
    c3 = boite(660, 'draw()', 'LIRE - 60 fois par seconde', BLEU)
    # contenu : la liste vide, remplie, lue
    d.text((c1, 140), 'std::vector<float> xs;', font=font(13), fill=ENCRE, anchor='ma')
    for k in range(3):
        d.rectangle([c1 - 60 + k * 40, 180, c1 - 24 + k * 40, 216], outline=GRIS, width=2)
    d.text((c1, 232), 'vide', font=font(13), fill=GRIS, anchor='ma')
    d.text((c2, 140), 'xs.push_back(ofRandom(...));', font=font(12), fill=ENCRE, anchor='ma')
    for k, v in enumerate(['312', '87', '649']):
        d.rectangle([c2 - 60 + k * 40, 180, c2 - 24 + k * 40, 216], outline=ORANGE, width=2)
        d.text((c2 - 42 + k * 40, 198), v, font=font(11), fill=ORANGE, anchor='mm')
    d.text((c2, 232), 'les tirages, stockes', font=font(13), fill=GRIS, anchor='ma')
    d.text((c3, 140), 'ofDrawCircle(xs[i], ...);', font=font(12), fill=ENCRE, anchor='ma')
    for k, v in enumerate(['312', '87', '649']):
        d.rectangle([c3 - 60 + k * 40, 180, c3 - 24 + k * 40, 216], outline=BLEU, width=2)
        d.text((c3 - 42 + k * 40, 198), v, font=font(11), fill=BLEU, anchor='mm')
    d.text((c3, 232), 'relues a chaque frame', font=font(13), fill=GRIS, anchor='ma')
    fleche(d, 300, 190, 345, 190, ENCRE)
    fleche(d, 610, 190, 655, 190, ENCRE)
    im.save(os.path.join(OUT, '04-trajet-listes.png')); print('ok 04-trajet-listes.png')


def img_trainee():
    W, H = 960, 380
    im = Image.new('RGB', (W, H), FOND)
    d = ImageDraw.Draw(im)
    d.text((250, 26), 'sans ofBackground', font=font(19, bold=True), fill=ORANGE, anchor='ma')
    d.text((710, 26), 'avec ofBackground en tete de draw()', font=font(19, bold=True), fill=BLEU, anchor='ma')
    d.rectangle([70, 70, 430, 330], outline=ENCRE, width=3, fill=(40, 40, 40))
    d.rectangle([530, 70, 890, 330], outline=ENCRE, width=3, fill=(40, 40, 40))
    # traînée de cercles fantômes
    for k in range(5):
        g = 70 + k * 45
        x, y = 130 + k * 55, 260 - k * 38
        d.ellipse([x - 30, y - 30, x + 30, y + 30], fill=(g, g, g))
    # un seul cercle propre
    d.ellipse([760 - 30, 130 - 30, 760 + 30, 130 + 30], fill=(245, 245, 245))
    d.text((250, 344), 'les frames s\'accumulent : la trainee', font=font(15), fill=GRIS, anchor='ma')
    d.text((710, 344), 'chaque frame repart d\'un fond propre', font=font(15), fill=GRIS, anchor='ma')
    im.save(os.path.join(OUT, '05-trainee.png')); print('ok 05-trainee.png')


def img_rebond():
    W, H = 960, 340
    im = Image.new('RGB', (W, H), FOND)
    d = ImageDraw.Draw(im)
    # le couloir
    m0, m1, y = 160, 800, 170
    d.line([m0, 70, m0, 270], fill=ENCRE, width=6)
    d.line([m1, 70, m1, 270], fill=ENCRE, width=6)
    # aller
    fleche(d, m0 + 60, y - 40, m1 - 60, y - 40, ORANGE, w=4)
    d.text(((m0 + m1) / 2, y - 76), 'vx = +60', font=font(19, bold=True), fill=ORANGE, anchor='ma')
    # le rebond (arc)
    d.arc([m1 - 90, y - 40, m1 - 10, y + 40], start=270, end=90, fill=ENCRE, width=3)
    # retour
    fleche(d, m1 - 60, y + 40, m0 + 60, y + 40, BLEU, w=4)
    d.text(((m0 + m1) / 2, y + 52), 'vx = -60', font=font(19, bold=True), fill=BLEU, anchor='ma')
    # la balle
    d.ellipse([m0 + 150 - 18, y - 40 - 18, m0 + 150 + 18, y - 40 + 18], fill=ORANGE)
    # les if aux murs
    d.text((m1 - 10, 296), 'if (posX > 250) vx = -vx;', font=font(16, bold=True), fill=ENCRE, anchor='ra')
    d.text((m0 + 10, 296), 'if (posX < 0) vx = -vx;', font=font(16, bold=True), fill=ENCRE, anchor='la')
    d.text((480, 30), 'rebondir = inverser la vitesse', font=font(20, bold=True), fill=ENCRE, anchor='ma')
    im.save(os.path.join(OUT, '06-rebond-vitesse.png')); print('ok 06-rebond-vitesse.png')


img_anatomie_appel()
img_opacite()
img_fonction_tampon()
img_deduire()
img_division_entiere()
img_deroule_boucle()
img_graine()
img_trajet_listes()
img_trainee()
img_rebond()
