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


img_variable_boite()
img_octet_binaire()
