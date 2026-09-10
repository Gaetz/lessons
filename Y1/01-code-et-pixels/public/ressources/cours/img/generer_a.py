# Génère les illustrations des cours 00 à 09, 12, 13, 15, 16 (formes et schémas).
# Usage : python generer_a.py   (nécessite Pillow et numpy)
from PIL import Image, ImageDraw, ImageFont
import numpy as np, math, random, colorsys, os

OUT = os.path.dirname(os.path.abspath(__file__))
DATA = os.path.join(OUT, '..', '..', 'data')

def font(size=14):
    try:
        return ImageFont.truetype('/System/Library/Fonts/Menlo.ttc', size)
    except Exception:
        return ImageFont.load_default(size=size)

def C(r, g, b, a=255):
    cl = lambda v: int(max(0, min(255, v)))
    return (cl(r), cl(g), cl(b), cl(a))

class Canvas:
    def __init__(self, w, h, bg=(0, 0, 0)):
        self.img = Image.new('RGBA', (w, h), C(*bg))
        self.d = ImageDraw.Draw(self.img)
    def _blend(self, bbox, fn):
        x0, y0 = int(math.floor(bbox[0])), int(math.floor(bbox[1]))
        x1, y1 = int(math.ceil(bbox[2])) + 1, int(math.ceil(bbox[3])) + 1
        x0, y0 = max(x0, 0), max(y0, 0)
        x1, y1 = min(x1, self.img.width), min(y1, self.img.height)
        if x1 <= x0 or y1 <= y0: return
        layer = Image.new('RGBA', (x1 - x0, y1 - y0), (0, 0, 0, 0))
        fn(ImageDraw.Draw(layer), -x0, -y0)
        self.img.alpha_composite(layer, dest=(x0, y0))
    def circle(self, x, y, r, fill=None, outline=None, width=1):
        self._blend((x - r - width, y - r - width, x + r + width, y + r + width),
                    lambda d, ox, oy: d.ellipse([x - r + ox, y - r + oy, x + r + ox, y + r + oy],
                                                fill=fill, outline=outline, width=width))
    def ellipse(self, x, y, w, h, fill=None, outline=None, width=1):
        self._blend((x - w / 2, y - h / 2, x + w / 2, y + h / 2),
                    lambda d, ox, oy: d.ellipse([x - w / 2 + ox, y - h / 2 + oy, x + w / 2 + ox, y + h / 2 + oy],
                                                fill=fill, outline=outline, width=width))
    def rect(self, x, y, w, h, fill=None, outline=None, width=1):
        self._blend((x - width, y - width, x + w + width, y + h + width),
                    lambda d, ox, oy: d.rectangle([x + ox, y + oy, x + w + ox, y + h + oy],
                                                  fill=fill, outline=outline, width=width))
    def line(self, x0, y0, x1, y1, fill, width=1):
        self.d.line([x0, y0, x1, y1], fill=fill, width=width)
    def dashed(self, x0, y0, x1, y1, fill, dash=6):
        L = math.hypot(x1 - x0, y1 - y0); n = max(1, int(L / dash))
        for k in range(0, n, 2):
            a, b = k / n, min(1, (k + 1) / n)
            self.d.line([x0 + (x1 - x0) * a, y0 + (y1 - y0) * a, x0 + (x1 - x0) * b, y0 + (y1 - y0) * b], fill=fill, width=1)
    def arrow(self, x0, y0, x1, y1, fill, width=2, head=10):
        self.d.line([x0, y0, x1, y1], fill=fill, width=width)
        a = math.atan2(y1 - y0, x1 - x0)
        p = [(x1, y1),
             (x1 - head * math.cos(a - 0.4), y1 - head * math.sin(a - 0.4)),
             (x1 - head * math.cos(a + 0.4), y1 - head * math.sin(a + 0.4))]
        self.d.polygon(p, fill=fill)
    def text(self, x, y, s, fill=(0, 0, 0, 255), size=14, anchor='la'):
        self.d.text((x, y), s, fill=fill, font=font(size), anchor=anchor)
    def save(self, name, scale=1.0):
        im = self.img.convert('RGB')
        if scale != 1.0:
            im = im.resize((int(im.width * scale), int(im.height * scale)), Image.LANCZOS)
        im.save(os.path.join(OUT, name), optimize=True)
        print('ok', name)

def hsb(h, s, b, a=255):
    r, g, bb = colorsys.hsv_to_rgb((h % 255) / 255, s / 255, b / 255)
    return C(r * 255, g * 255, bb * 255, a)

INK = (40, 40, 40, 255); BLUE = (30, 90, 200, 255); RED = (200, 40, 40, 255); GREY = (150, 150, 150, 255)
PAPER = (250, 250, 250)

# ---------- 00 : visage ----------
def img00():
    c = Canvas(800, 800, (110, 70, 190))
    x, y = 150, 150
    c.circle(200 + x, 200 + y, 225, fill=C(255, 255, 255, 100))
    c.rect(100 + x, 200 + y, 250, 50, fill=C(255, 255, 255, 100))
    c.circle(55 + x, 75 + y, 50, fill=C(255, 0, 0, 150))
    c.circle(375 + x, 75 + y, 50, fill=C(255, 0, 0, 150))
    c.save('00-visage.png', 0.5)

    c = Canvas(480, 330, PAPER)
    c.rect(40, 40, 400, 260, fill=C(235, 235, 235), outline=GREY)
    c.arrow(40, 40, 460, 40, INK); c.arrow(40, 40, 40, 320, INK)
    c.text(452, 48, 'x', INK, 18); c.text(48, 306, 'y', INK, 18)
    c.text(44, 22, '(0, 0)', INK, 14)
    for k in range(1, 5):
        c.line(40 + k * 100, 36, 40 + k * 100, 44, INK); c.text(40 + k * 100, 26, str(k * 100), INK, 12, 'mm')
    for k in range(1, 3):
        c.line(36, 40 + k * 100, 44, 40 + k * 100, INK); c.text(30, 40 + k * 100, str(k * 100), INK, 12, 'rm')
    px, py = 40 + 260, 40 + 150
    c.dashed(px, 40, px, py, BLUE); c.dashed(40, py, px, py, BLUE)
    c.circle(px, py, 6, fill=BLUE)
    c.text(px + 10, py - 8, '(260, 150)', BLUE, 15)
    c.text(240, 312, 'y augmente vers le BAS', RED, 13, 'mm')
    c.save('00-repere.png')

# ---------- 01 ----------
def img01():
    c = Canvas(400, 400, (200, 200, 200))
    c.circle(200, 300, 37.5, fill=C(255, 255, 255))
    for k in range(10):
        c.circle(k * 75, 100, 37.5, fill=C(255, 255, 255))
    c.save('01-cercles.png')

    c = Canvas(580, 260, PAPER)
    cx, cy, r = 130, 130, 90
    c.circle(cx, cy, r, outline=INK, width=3)
    c.circle(cx, cy, 4, fill=INK)
    c.arrow(cx, cy, cx + r - 2, cy, BLUE, 3); c.text(cx + 20, cy - 24, 'rayon = 37.5', BLUE, 15)
    c.arrow(cx - 60, cy - r, cx - 60, cy + r - 2, RED, 3); c.arrow(cx - 60, cy + r, cx - 60, cy - r + 2, RED, 3)
    c.text(cx - 220 + 180, cy + r + 18, 'diametre = 75', RED, 15, 'mm')
    c.text(250, 90, 'ofDrawCircle(x, y, rayon)', INK, 15)
    c.text(250, 120, 'Le 3e nombre est le RAYON,', INK, 13)
    c.text(250, 140, 'pas le diametre.', INK, 13)
    c.save('01-rayon-diametre.png')

# ---------- 02 ----------
def img02():
    c = Canvas(400, 400, (200, 200, 200))
    x = y = 0; taille = 10; b = 0
    for i in range(10):
        c.circle(x, y, taille / 2, fill=C(255, 0, b, 180))
        c.circle(x, y, taille / 2, outline=C(255, 150, 0), width=2)
        c.text(x + taille / 2 + 4, y - 8, 'i=%d' % i, INK, 12)
        x += 40; y += 40; taille += 20; b += 25
    c.save('02-boucle.png')

# ---------- 03 ----------
def img03():
    random.seed(42)
    c = Canvas(800, 800, (200, 200, 200))
    for i in range(50):
        c.circle(random.uniform(0, 800), random.uniform(0, 800), random.uniform(10, 50) / 2, fill=C(255, 255, 255))
    for i in range(0, 50, 5):
        c.circle(i * 16, 100, i / 2, fill=C(0, 0, 255))
    for i in range(50):
        c.circle(200, 800 - i * 16, i / 2, fill=C(255, 0, 0))
    for i in range(50):
        c.circle(i * 16, 800 - i * 16, random.uniform(5, 40) / 2, fill=C(255, 255, 0))
    c.save('03-aleatoire.png', 0.5)

# ---------- 04 ----------
def img04():
    noms = ['Annie', 'Brand', 'Callista', 'Diana', 'Evelyn', 'Fiora', 'Garen', 'Heimer', 'Sona']
    c = Canvas(700, 230, PAPER)
    bw = 72
    for i, n in enumerate(noms):
        x = 20 + i * bw
        c.rect(x, 70, bw, 50, fill=C(230, 240, 255), outline=INK, width=2)
        c.text(x + bw / 2, 95, n, INK, 13, 'mm')
        c.text(x + bw / 2, 55, str(i), BLUE, 14, 'mm')
    c.text(20, 22, 'indice :', BLUE, 14)
    c.text(20 + 9 * bw + 8, 95, 'size() = 9', INK, 14, 'lm')
    c.arrow(20 + 1 * bw + bw / 2, 175, 20 + 1 * bw + bw / 2, 124, RED, 2)
    c.text(20 + 1 * bw + bw / 2, 190, 'noms[1]', RED, 14, 'mm')
    c.arrow(20 + 8 * bw + bw / 2, 175, 20 + 8 * bw + bw / 2, 124, RED, 2)
    c.text(20 + 8 * bw + bw / 2, 190, 'noms[noms.size() - 1]', RED, 14, 'mm')
    c.text(20 + 0 * bw + bw / 2, 212, 'le premier est a 0', GREY, 12, 'lm')
    c.save('04-vector.png')

# ---------- 05 ----------
def img05():
    c = Canvas(600, 230, PAPER)
    def box(x, y, w, h, s, col):
        c.rect(x, y, w, h, fill=col, outline=INK, width=2); c.text(x + w / 2, y + h / 2, s, INK, 16, 'mm')
    box(20, 80, 130, 60, 'setup()', C(255, 235, 200))
    box(230, 80, 130, 60, 'update()', C(220, 240, 255))
    box(430, 80, 130, 60, 'draw()', C(220, 255, 220))
    c.arrow(150, 110, 228, 110, INK); c.arrow(360, 110, 428, 110, INK)
    c.d.line([495, 140, 495, 190, 295, 190, 295, 142], fill=INK, width=2); c.arrow(295, 160, 295, 142, INK)
    c.text(395, 205, '60 fois par seconde', INK, 14, 'mm')
    c.text(85, 60, 'une fois, au lancement', GREY, 12, 'mm')
    c.text(295, 60, 'calculs, positions', GREY, 12, 'mm')
    c.text(495, 60, 'dessin', GREY, 12, 'mm')
    c.save('05-cycle.png')

    c = Canvas(400, 400, (255, 0, 0))
    c.circle(260, 180, 50, fill=C(255, 255, 255))
    p = [(260, 180), (260, 205), (267, 199), (275, 213), (280, 210), (272, 197), (281, 196)]
    c.d.polygon(p, fill=(0, 0, 0, 255), outline=(255, 255, 255, 255))
    c.save('05-souris.png')

# ---------- 06 ----------
def img06():
    c = Canvas(400, 400, (120, 200, 90))
    dx, dy = 120, 40
    c.rect(dx + 100, dy + 100, 100, 100, fill=C(255, 255, 255))
    c.ellipse(dx + 50, dy + 150, 200, 150, fill=C(255, 255, 255))
    c.arrow(dx + 150, dy + 150, dx + 150 + 60, dy + 150, RED, 3); c.text(dx + 215, dy + 140, 'vx', RED, 16)
    c.arrow(dx + 150, dy + 150, dx + 150, dy + 150 + 90, BLUE, 3); c.text(dx + 158, dy + 235, 'vy', BLUE, 16)
    c.save('06-rebond.png')

    c = Canvas(520, 260, PAPER)
    ox, oy, W, H = 50, 220, 440, 180
    c.arrow(ox, oy, ox + W + 10, oy, INK); c.arrow(ox, oy, ox, oy - H - 10, INK)
    c.text(ox + W, oy + 14, 'temps (s)', INK, 13, 'rm'); c.text(ox - 6, oy - H - 4, 'r', INK, 14, 'rm')
    c.dashed(ox, oy - H, ox + W, oy - H, GREY); c.text(ox - 6, oy - H, '255', GREY, 12, 'rm'); c.text(ox - 6, oy, '0', GREY, 12, 'rm')
    pts = []; r = 0; vr = 300; dt = 1 / 60
    for k in range(int(4 / dt)):
        pts.append((ox + k * dt / 4 * W, oy - r / 255 * H))
        r += vr * dt
        if r >= 255: vr = -vr
        if r <= 0: vr = -vr
    c.d.line(pts, fill=RED, width=3)
    for s in range(5):
        c.line(ox + s / 4 * W, oy - 4, ox + s / 4 * W, oy + 4, INK); c.text(ox + s / 4 * W, oy + 8, str(s), INK, 12, 'ma')
    c.text(ox + 0.85 * W / 4, oy - H - 14, 'vr = -vr', BLUE, 13, 'mm')
    c.text(ox + 1.7 * W / 4, oy + 22, 'vr = -vr', BLUE, 13, 'mm')
    c.save('06-allers-retours.png')

# ---------- 07 ----------
def bear(c, x, y, col):
    c.circle(x - 25, y - 25, 25, fill=col); c.circle(x + 25, y - 25, 25, fill=col)
    c.circle(x, y, 50, fill=col); c.circle(x, y, 10, fill=col)
    c.circle(x - 30, y - 20, 10, fill=col); c.circle(x + 30, y - 20, 10, fill=col)
    c.rect(x, y + 20, 50, 10, fill=col)

def path(n, w=400, h=400):
    return [(w * 0.15 + i * (w * 0.7) / n, h * 0.55 + h * 0.22 * math.sin(i / n * 5)) for i in range(n)]

def img07():
    c = Canvas(400, 400, (0, 0, 0))
    for (x, y) in path(50):
        bear(c, x, y, C(255, 255, 255))
    c.save('07-trainee.png')

    c = Canvas(400, 400, (0, 0, 0))
    pts = path(50)
    for k, (x, y) in enumerate(pts):
        g = 60 + 195 * k / 49
        bear(c, x, y, C(g, g, g))
    c.text(pts[0][0], pts[0][1] - 70, 'i = 0 (le plus ancien)', C(200, 200, 200), 12, 'mm')
    c.text(pts[-1][0], pts[-1][1] + 45, 'i = 49', C(255, 255, 255), 12, 'mm')
    c.save('07-trainee-indices.png')

# ---------- 08 ----------
def img08():
    c = Canvas(800, 800, (0, 0, 0))
    t = 2.0
    r = (math.cos(t * 1.2) / 2 + 0.5) * 255; g = (math.cos(t * 1.0) / 2 + 0.5) * 255; b = (math.cos(t * 0.86) / 2 + 0.5) * 255
    for i, (x, y) in enumerate(path(25, 800, 800)):
        off = i * 10
        taille = (math.cos(i / 5) + 5) * 20
        variation = (math.cos(t * 1.2) + 5) * 100
        tf = taille + variation * (25 - i) / 50
        c.circle(x, y, tf / 2, fill=C(r + off, g + off, b + off, off))
        c.circle(x, y, tf / 2, outline=C(r + off, g + off, b + off, 255 - off), width=2)
    c.save('08-trainee.png', 0.5)

# ---------- 09 ----------
def img09():
    c = Canvas(800, 600, (30, 30, 30))
    teinteChoisie = 30
    for x in range(800):
        p = x / 800 * 255
        c.line(x, 20, x, 60, hsb(p, 255, 255)); c.line(x, 80, x, 120, hsb(teinteChoisie, p, 255)); c.line(x, 140, x, 180, hsb(teinteChoisie, 255, p))
    W = (255, 255, 255, 255)
    c.text(10, 4, 'teinte (H)', W, 13); c.text(10, 64, 'saturation (S)', W, 13); c.text(10, 124, 'luminosite (B)', W, 13)
    t = 2.0
    r = (math.cos(t * 1.2) / 2 + 0.5) * 255; g = (math.cos(t * 1.0) / 2 + 0.5) * 255; b = (math.cos(t * 0.86) / 2 + 0.5) * 255
    c.circle(150, 260, 60, fill=C(r, g, b)); c.text(150, 335, 'RGB : 3 cosinus (08)', W, 13, 'mm')
    c.circle(400, 260, 60, fill=hsb((t * 40) % 255, 255, 255)); c.text(400, 335, 'HSB : teinte = temps', W, 13, 'mm')
    a, bcol = (255, 80, 0), (0, 120, 255)
    for x in range(520, 780):
        p = (x - 520) / 260
        c.line(x, 200, x, 320, C(*(a[k] + (bcol[k] - a[k]) * p for k in range(3))))
    c.text(650, 335, 'getLerped', W, 13, 'mm')
    for i, (x, y) in enumerate([(120 + i * 22, 470 + 60 * math.sin(i / 4)) for i in range(25)]):
        c.circle(x, y, 5 + i, fill=hsb(i * 10, 255, 255))
    c.save('09-hsb.png')

    # roue des teintes
    n = 320; arr = np.zeros((n, n, 3), dtype=np.uint8) + 250
    yy, xx = np.mgrid[0:n, 0:n]; dx, dy = xx - n / 2, yy - n / 2
    rr = np.hypot(dx, dy); ang = (np.arctan2(-dy, dx) % (2 * math.pi)) / (2 * math.pi)
    mask = (rr > 85) & (rr < 140)
    import matplotlib.colors as mc  # optionnel
    hsv = np.stack([ang, np.ones_like(ang), np.ones_like(ang)], -1)
    rgb = (mc.hsv_to_rgb(hsv) * 255).astype(np.uint8)
    arr[mask] = rgb[mask]
    c = Canvas(n, n, PAPER); c.img = Image.fromarray(arr).convert('RGBA'); c.d = ImageDraw.Draw(c.img)
    for h, lab in [(0, '0'), (64, '64'), (128, '128'), (192, '192')]:
        a = h / 255 * 2 * math.pi
        c.text(n / 2 + 152 * math.cos(a), n / 2 - 152 * math.sin(a), lab, INK, 13, 'mm')
    c.text(n / 2, n / 2 - 10, 'teinte', INK, 15, 'mm'); c.text(n / 2, n / 2 + 10, '0 -> 255', INK, 13, 'mm')
    c.save('09-roue.png')

    # cube RGB
    c = Canvas(360, 340, PAPER)
    O = (110, 250); ex = (170, 0); ey = (0, -170); ez = (85, -60)
    P = lambda r, g, b: (O[0] + r * ex[0] + g * ey[0] + b * ez[0], O[1] + r * ex[1] + g * ey[1] + b * ez[1])
    edges = [((0,0,0),(1,0,0)),((0,0,0),(0,1,0)),((0,0,0),(0,0,1)),((1,0,0),(1,1,0)),((1,0,0),(1,0,1)),((0,1,0),(1,1,0)),
             ((0,1,0),(0,1,1)),((0,0,1),(1,0,1)),((0,0,1),(0,1,1)),((1,1,0),(1,1,1)),((1,0,1),(1,1,1)),((0,1,1),(1,1,1))]
    for a, b in edges:
        c.line(*P(*a), *P(*b), GREY, 2)
    for r in (0, 1):
        for g in (0, 1):
            for b in (0, 1):
                x, y = P(r, g, b); c.circle(x, y, 11, fill=C(r * 255, g * 255, b * 255), outline=INK, width=1)
    c.text(P(1, 0, 0)[0] + 16, P(1, 0, 0)[1], 'R', RED, 16, 'lm'); c.text(P(0, 1, 0)[0], P(0, 1, 0)[1] - 18, 'G', C(0, 150, 0), 16, 'mm')
    c.text(P(0, 0, 1)[0] + 14, P(0, 0, 1)[1] - 4, 'B', BLUE, 16, 'lm')
    c.text(P(0, 0, 0)[0] - 12, P(0, 0, 0)[1] + 12, '(0,0,0) noir', INK, 12, 'la'); c.text(P(1, 1, 1)[0] + 14, P(1, 1, 1)[1], '(255,255,255) blanc', INK, 12, 'lm')
    c.save('09-cube-rgb.png')

# ---------- 12 ----------
def img12():
    src = Image.open(os.path.join(DATA, 'pandaroux.jpg')).convert('RGB')
    c = Canvas(774, 516, (0, 0, 0)); mx, my = 620, 380
    for li in range(0, 516, 20):
        for co in range(0, 774, 20):
            d = math.hypot(co - mx, li - my); ray = 10
            if d <= 150: ray = ray * d / 150
            c.circle(co, li, ray, fill=C(*src.getpixel((co, li))))
    c.save('12-pointillisme.png')

    c = Canvas(420, 260, PAPER)
    A, B = (70, 210), (330, 70)
    c.d.polygon([A, (B[0], A[1]), B], outline=INK, fill=C(235, 240, 255)); c.d.line([A, (B[0], A[1]), B, A], fill=INK, width=2)
    c.circle(*A, 5, fill=INK); c.circle(*B, 5, fill=INK)
    c.text(A[0] - 10, A[1] + 12, 'A (ax, ay)', INK, 13, 'la'); c.text(B[0] + 10, B[1] - 8, 'B (bx, by)', INK, 13, 'la')
    c.text((A[0] + B[0]) / 2, A[1] + 12, 'dx = bx - ax', RED, 14, 'ma'); c.text(B[0] + 10, (A[1] + B[1]) / 2, 'dy = by - ay', BLUE, 14, 'lm')
    c.text((A[0] + B[0]) / 2 - 30, (A[1] + B[1]) / 2 - 20, 'd = sqrt(dx*dx + dy*dy)', C(0, 120, 0), 14, 'mm')
    c.save('12-pythagore.png')

# ---------- 13 ----------
def img13():
    acc = np.zeros((800, 800, 3), dtype=np.int32); t = 1.0
    for i in range(12):
        col = [(255, 0, 0), (0, 255, 0), (0, 0, 255)][i % 3]
        a = i * 2 * math.pi / 12; x = 400 + math.cos(a) * 200 * t; y = 400 - math.sin(a) * 200 * t
        layer = Image.new('RGB', (800, 800), (0, 0, 0)); ImageDraw.Draw(layer).ellipse([x - 100, y - 100, x + 100, y + 100], fill=col)
        acc += np.array(layer, dtype=np.int32)
    Image.fromarray(np.clip(acc, 0, 255).astype(np.uint8)).resize((400, 400), Image.LANCZOS).save(os.path.join(OUT, '13-cercles.png')); print('ok 13-cercles.png')

    c = Canvas(400, 380, PAPER); cx, cy, R = 200, 200, 130; a = math.radians(40)
    c.circle(cx, cy, R, outline=GREY, width=2); c.line(cx - 170, cy, cx + 170, cy, INK); c.line(cx, cy - 170, cx, cy + 170, INK)
    px, py = cx + R * math.cos(a), cy - R * math.sin(a)
    c.line(cx, cy, px, py, INK, 2); c.circle(px, py, 6, fill=RED)
    c.d.arc([cx - 40, cy - 40, cx + 40, cy + 40], start=-40, end=0, fill=BLUE, width=2); c.text(cx + 48, cy - 22, 'angle', BLUE, 14)
    c.line(px, py, px, cy, RED); c.line(px, py, cx, py, BLUE)
    c.text((cx + px) / 2, cy + 10, 'x = cos(angle) * rayon', RED, 13, 'ma'); c.text(cx - 8, (cy + py) / 2, 'y = -sin(angle) * rayon', BLUE, 13, 'rm')
    c.text(cx + R / 2 * math.cos(a) - 30, cy - R / 2 * math.sin(a) - 16, 'rayon', INK, 13, 'mm')
    c.text(200, 360, "- devant sin : l'axe y de l'ecran pointe vers le bas", INK, 12, 'mm')
    c.save('13-trigo.png')

# ---------- 15 ----------
def img15():
    c = Canvas(400, 400, (220, 220, 220)); rows = 15; tile = 400 / rows; rad = tile / 2; ga = 1.0; off = 75
    for i in range(rows):
        for j in range(rows):
            a = ga + i * off + j * off; x0 = i * tile + tile / 2; y0 = j * tile + tile / 2
            x = rad * math.cos(a) + x0; y = rad * math.sin(a) + y0
            if (i, j) in [(3, 3), (3, 4), (4, 3), (4, 4)]:
                c.circle(x0, y0, rad, outline=C(150, 150, 150), width=1); c.line(x0, y0, x, y, C(150, 150, 150))
            c.circle(x, y, 5, fill=C(0, 0, 0))
    c.save('15-grille.png')

# ---------- 16 ----------
def img16():
    acc = np.zeros((400, 400, 3), dtype=np.int32); t = 3.0; nbP, amp, per = 200, 15, 7
    for f in range(14):
        sens = 1 if f % 2 == 0 else -1; rot = f * 0.12 * sens * t; r = 150 - f * 10
        pts = []
        for i in range(nbP):
            a = i * 2 * math.pi / nbP; fr = amp * math.cos(a * per)
            pts.append((200 + (r + fr) * math.cos(a + rot), 200 + (r + fr) * math.sin(a + rot)))
        layer = Image.new('RGB', (400, 400), (0, 0, 0)); ImageDraw.Draw(layer).polygon(pts, fill=(60, 20, 90) if f % 2 == 0 else (20, 60, 90))
        acc += np.array(layer, dtype=np.int32)
    Image.fromarray(np.clip(acc, 0, 255).astype(np.uint8)).save(os.path.join(OUT, '16-fleurs.png')); print('ok 16-fleurs.png')

    c = Canvas(600, 420, PAPER); cx, cy, r, amp, per = 300, 200, 120, 18, 7
    c.circle(cx, cy, r, outline=GREY, width=1)
    pts = [(cx + (r + amp * math.cos(a * per)) * math.cos(a), cy + (r + amp * math.cos(a * per)) * math.sin(a)) for a in np.linspace(0, 2 * math.pi, 400)]
    c.d.line(pts + [pts[0]], fill=BLUE, width=3)
    a = math.radians(-25); rr = r + amp * math.cos(a * per); px, py = cx + rr * math.cos(a), cy + rr * math.sin(a)
    c.line(cx, cy, px, py, RED, 2); c.circle(px, py, 6, fill=RED); c.circle(cx, cy, 4, fill=INK)
    c.d.arc([cx - 40, cy - 40, cx + 40, cy + 40], start=-25, end=0, fill=INK, width=2); c.text(cx + 46, cy - 6, 'angle', INK, 13)
    c.text(cx, cy + r + 30, 'rouge : rayon = r + amplitude * cos(angle * period)', RED, 12, 'mm')
    c.text(cx, cy + r + 50, 'gris : cercle de rayon r    bleu : la fleur (period = 7 petales)', INK, 12, 'mm')
    c.text(cx, cy + r + 70, 'x = rayon * cos(angle)   y = rayon * sin(angle)', BLUE, 12, 'mm')
    c.save('16-polaire.png')

if __name__ == '__main__':
    import sys
    todo = [img00, img01, img02, img03, img04, img05, img06, img07, img08, img09, img12, img13, img15, img16]
    if len(sys.argv) > 1: todo = [globals()['img' + a] for a in sys.argv[1:]]
    for f in todo:
        f()
