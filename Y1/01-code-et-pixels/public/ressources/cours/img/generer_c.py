# Génère les illustrations des cours 09a et 11a à 11g (couleur avancée).
# Usage : python generer_c.py [09a 11a ...]   (nécessite Pillow, numpy)
from PIL import Image, ImageDraw, ImageFont
import numpy as np, math, os, colorsys

OUT = os.path.dirname(os.path.abspath(__file__))
DATA = os.path.join(OUT, '..', '..', 'data')
def font(size=14):
    try: return ImageFont.truetype('/System/Library/Fonts/Menlo.ttc', size)
    except Exception: return ImageFont.load_default(size=size)
INK = (40, 40, 40); BLUE = (30, 90, 200); RED = (200, 40, 40); GREY = (150, 150, 150); PAPER = (250, 250, 250); GOLD = (255, 200, 0)

src_img = Image.open(os.path.join(DATA, 'pandaroux.jpg')).convert('RGB')
src = np.array(src_img).astype(np.float32); H, W = src.shape[:2]
def to_img(a): return Image.fromarray(np.clip(a, 0, 255).astype(np.uint8))
def save(im, name): im.save(os.path.join(OUT, name), optimize=True); print('ok', name)
def lin(c): return np.power(np.clip(c, 0, 255) / 255.0, 2.2)
def srgb(l): return 255.0 * np.power(np.clip(l, 0, 1), 1 / 2.2)

def sheet(items, cols, scale=0.5, label_h=26):
    tw, th = int(W * scale), int(H * scale); rows = math.ceil(len(items) / cols)
    out = Image.new('RGB', (cols * tw + (cols + 1) * 8, rows * (th + label_h) + (rows + 1) * 8), PAPER); d = ImageDraw.Draw(out)
    for k, (lab, im) in enumerate(items):
        r, c = divmod(k, cols); x = 8 + c * (tw + 8); y = 8 + r * (th + label_h + 8)
        out.paste(im.resize((tw, th), Image.LANCZOS), (x, y)); d.text((x + tw / 2, y + th + label_h / 2), lab, fill=INK, font=font(14), anchor='mm')
    return out

# ---------- 09a ----------
def img09a():
    # pipeline
    out = Image.new('RGB', (960, 230), PAPER); d = ImageDraw.Draw(out)
    steps = [('scene reelle\nou rendu 3D', 'lumiere lineaire,\nsans limite (HDR)', (255, 240, 200)),
             ('exposition +\ntone mapping', 'ramener sous 1\n(11b)', (220, 240, 255)),
             ('etalonnage', 'LUT, look\n(11c)', (230, 255, 230)),
             ('encodage', 'sRGB gamma 2.2,\n8 bits (11a, banding)', (255, 230, 230)),
             ('compression', 'JPEG, video :\nYCbCr 4:2:0 (11d)', (240, 230, 255)),
             ('ecran', 'gamut sRGB, P3...\n(09a)', (235, 235, 235)),
             ('oeil', 'perception\n(11e, 11f)', (255, 250, 210))]
    bw, gap, x = 120, 16, 12
    for i, (t, s, col) in enumerate(steps):
        d.rectangle([x, 50, x + bw, 120], fill=col, outline=INK, width=2)
        d.multiline_text((x + bw / 2, 85), t, fill=INK, font=font(13), anchor='mm', align='center')
        d.multiline_text((x + bw / 2, 160), s, fill=(90, 90, 90), font=font(11), anchor='mm', align='center')
        if i < len(steps) - 1:
            d.line([x + bw, 85, x + bw + gap, 85], fill=INK, width=2); d.polygon([(x + bw + gap, 85), (x + bw + gap - 6, 81), (x + bw + gap - 6, 89)], fill=INK)
        x += bw + gap
    d.text((480, 22), 'Le voyage de la couleur, et la lecon qui en parle', fill=INK, font=font(15), anchor='mm')
    d.text((480, 210), 'A gauche des valeurs de lumiere sans limite ; a droite 256 niveaux par canal et un oeil qui ne les voit pas tous pareil.', fill=(90, 90, 90), font=font(12), anchor='mm')
    save(out, '09a-pipeline.png')

    # gamut : diagramme de chromaticité approximatif
    locus = [(0.1741,0.0050),(0.1733,0.0048),(0.1714,0.0051),(0.1644,0.0109),(0.1566,0.0177),(0.1440,0.0297),(0.1241,0.0578),(0.0913,0.1327),
             (0.0454,0.2950),(0.0082,0.5384),(0.0139,0.7502),(0.0743,0.8338),(0.1547,0.8059),(0.2296,0.7543),(0.3016,0.6923),(0.3731,0.6245),
             (0.4441,0.5547),(0.5125,0.4866),(0.5752,0.4242),(0.6270,0.3725),(0.6658,0.3340),(0.6915,0.3083),(0.7079,0.2920),(0.7190,0.2809),(0.7260,0.2740),(0.7347,0.2653)]
    S = 560; pad = 50
    def P(x, y): return (pad + x * (S - 2 * pad) / 0.8, S - pad - y * (S - 2 * pad) / 0.9)
    # remplissage coloré du fer à cheval
    yy, xx = np.mgrid[0:S, 0:S]; cx = (xx - pad) * 0.8 / (S - 2 * pad); cy = (S - pad - yy) * 0.9 / (S - 2 * pad)
    Yv = np.ones_like(cx); Xv = cx / np.maximum(cy, 1e-4) * Yv; Zv = (1 - cx - cy) / np.maximum(cy, 1e-4) * Yv
    M = np.array([[3.2406, -1.5372, -0.4986], [-0.9689, 1.8758, 0.0415], [0.0557, -0.2040, 1.0570]])
    rgb = np.einsum('ij,jhw->hwi', M, np.stack([Xv, Yv, Zv])); rgb = np.clip(rgb, 0, None); rgb = rgb / np.maximum(rgb.max(-1, keepdims=True), 1e-6)
    rgb = (np.power(rgb, 1 / 2.2) * 255).astype(np.uint8)
    mask = Image.new('L', (S, S), 0); ImageDraw.Draw(mask).polygon([P(x, y) for x, y in locus], fill=255)
    out = Image.new('RGB', (S + 300, S), PAPER); out.paste(Image.fromarray(rgb), (0, 0), mask); d = ImageDraw.Draw(out)
    d.line([P(x, y) for x, y in locus] + [P(*locus[0])], fill=INK, width=2)
    for name, tri, col in [('sRGB / Rec.709', [(0.64, 0.33), (0.30, 0.60), (0.15, 0.06)], (0, 0, 0)),
                           ('DCI-P3 (cinema, iPhone, Mac)', [(0.68, 0.32), (0.265, 0.69), (0.15, 0.06)], (0, 90, 200)),
                           ('Rec.2020 (HDR, UHD)', [(0.708, 0.292), (0.17, 0.797), (0.131, 0.046)], (200, 0, 0))]:
        d.line([P(*p) for p in tri] + [P(*tri[0])], fill=col, width=3)
    wx, wy = P(0.3127, 0.3290); d.ellipse([wx - 5, wy - 5, wx + 5, wy + 5], fill=(255, 255, 255), outline=INK, width=2)
    d.text((wx + 10, wy), 'blanc D65', fill=INK, font=font(12), anchor='lm')
    for lam, (x, y) in zip([460, 480, 500, 520, 550, 580, 600, 620, 700], [locus[5], locus[7], locus[9], locus[11], locus[14], locus[17], locus[19], locus[21], locus[25]]):
        px, py = P(x, y); d.text((px - 14 if x < 0.3 else px + 14, py), str(lam), fill=INK, font=font(11), anchor='mm')
    d.text((S + 10, 60), 'Diagramme de chromaticite', fill=INK, font=font(15))
    d.text((S + 10, 85), 'CIE 1931 (approximatif)', fill=(90, 90, 90), font=font(12))
    for i, (t, col) in enumerate([('sRGB / Rec.709', (0, 0, 0)), ('DCI-P3', (0, 90, 200)), ('Rec.2020', (200, 0, 0))]):
        d.rectangle([S + 10, 130 + i * 28, S + 30, 130 + i * 28 + 14], fill=col); d.text((S + 40, 137 + i * 28), t, fill=INK, font=font(13), anchor='lm')
    d.multiline_text((S + 10, 240), 'Le fer a cheval : toutes les\ncouleurs visibles. Chaque\ntriangle : celles qu un ecran\nsait afficher (son gamut).\nLes nombres : longueur\nd onde en nm.\n\nLes couleurs affichees ici\nsont elles-memes limitees\nau sRGB de ton ecran.', fill=INK, font=font(12))
    save(out, '09a-gamut.png')

    # banding
    Wd, Hb = 720, 90; xs = np.linspace(0, 255, Wd)
    rows = [('8 bits : 256 niveaux', xs), ('4 bits : 16 niveaux (banding)', np.floor(xs / 16) * 17)]
    bayer = np.array([[0, 8, 2, 10], [12, 4, 14, 6], [3, 11, 1, 9], [15, 7, 13, 5]]) / 16 - 0.5
    g = np.tile(xs[None, :], (Hb, 1)); dth = g + bayer[np.arange(Hb)[:, None] % 4, np.arange(Wd)[None, :] % 4] * 17
    rows.append(('4 bits + dithering (11g)', np.clip(np.floor(dth / 16) * 17, 0, 255)))
    out = Image.new('RGB', (Wd + 20, len(rows) * (Hb + 30) + 10), PAPER); d = ImageDraw.Draw(out)
    for i, (lab, v) in enumerate(rows):
        arr = np.tile(v[None, :], (Hb, 1)) if v.ndim == 1 else v
        out.paste(Image.fromarray(np.repeat(np.clip(arr, 0, 255)[..., None], 3, -1).astype(np.uint8)), (10, 10 + i * (Hb + 30)))
        d.text((10, 10 + i * (Hb + 30) + Hb + 6), lab, fill=INK, font=font(13))
    save(out, '09a-banding.png')

# ---------- 11a ----------
def img11a():
    Wd = 760; xs = np.linspace(0, 1, Wd)
    out = Image.new('RGB', (Wd + 20, 300), (30, 30, 30)); d = ImageDraw.Draw(out)
    a = np.tile((xs * 255)[None, :], (100, 1)); b = np.tile(srgb(xs)[None, :], (100, 1))
    out.paste(Image.fromarray(np.repeat(a[..., None], 3, -1).astype(np.uint8)), (10, 30)); out.paste(Image.fromarray(np.repeat(b[..., None], 3, -1).astype(np.uint8)), (10, 170))
    d.text((10, 12), 'valeur 0 -> 255 : le milieu (128) parait deja tres clair', fill=GOLD, font=font(13))
    d.text((10, 152), 'lumiere 0 -> 100 % : le milieu est a la valeur 186', fill=GOLD, font=font(13))
    d.line([10 + Wd / 2, 130, 10 + Wd / 2, 170], fill=GOLD, width=2)
    d.text((10 + Wd / 2, 285), 'milieu', fill=GOLD, font=font(12), anchor='mm')
    save(out, '11a-degrades.png')

    out = Image.new('RGB', (700, 260), (30, 30, 30)); d = ImageDraw.Draw(out)
    yy, xx = np.mgrid[0:200, 0:200]; chk = ((xx // 2 + yy // 2) % 2 == 0)
    dam = np.where(chk[..., None], np.array([255, 0, 0]), np.array([0, 255, 0])).astype(np.uint8)
    out.paste(Image.fromarray(dam), (20, 40)); d.rectangle([250, 40, 450, 240], fill=(128, 128, 0)); v = int(srgb(0.5)); d.rectangle([480, 40, 680, 240], fill=(v, v, 0))
    d.text((120, 22), 'damier 2 px (recule-toi)', fill=GOLD, font=font(12), anchor='mm'); d.text((350, 22), 'moyenne des valeurs : 128', fill=GOLD, font=font(12), anchor='mm'); d.text((580, 22), 'moyenne de la lumiere : 186', fill=GOLD, font=font(12), anchor='mm')
    save(out, '11a-melange.png')

    f = 0.5; naive = src * f; juste = srgb(lin(src) * f)
    both = np.where((np.arange(W) < W // 2)[None, :, None], naive, juste); im = to_img(both); d = ImageDraw.Draw(im)
    d.line([W // 2, 0, W // 2, H], fill=GOLD, width=2); d.text((10, 10), 'naif : valeurs x 0.5', fill=GOLD, font=font(14)); d.text((W // 2 + 10, 10), 'juste : lumiere x 0.5', fill=GOLD, font=font(14))
    save(im, '11a-image.png')

# ---------- 11b ----------
def reinhard(x): return x / (1 + x)
def aces(x): return np.clip((x * (2.51 * x + 0.03)) / (x * (2.43 * x + 0.59) + 0.14), 0, 1)
def img11b():
    L = lin(src); items = []
    for expo in [1, 4]:
        for lab, fn in [('couper', lambda x: np.clip(x, 0, 1)), ('Reinhard', reinhard), ('ACES', aces)]:
            items.append(('%s, exposition x%d' % (lab, expo), to_img(srgb(fn(L * expo)))))
    save(sheet(items, 3, 0.4), '11b-tonemapping.png')
    out = Image.new('RGB', (520, 300), PAPER); d = ImageDraw.Draw(out); ox, oy, gw, gh = 50, 250, 440, 200
    d.line([ox, oy, ox + gw, oy], fill=INK, width=2); d.line([ox, oy, ox, oy - gh], fill=INK, width=2)
    d.line([ox + gw / 4, oy, ox + gw / 4, oy - gh], fill=(200, 200, 200)); d.text((ox + gw / 4, oy + 12), 'entree = 1 (blanc ecran)', fill=GREY, font=font(11), anchor='mm')
    d.line([ox, oy - gh, ox + gw, oy - gh], fill=(200, 200, 200)); d.text((ox - 6, oy - gh), '1', fill=INK, font=font(12), anchor='rm'); d.text((ox - 6, oy), '0', fill=INK, font=font(12), anchor='rm')
    xs = np.linspace(0, 4, 400)
    for lab, fn, col in [('couper', lambda x: np.clip(x, 0, 1), (120, 120, 120)), ('Reinhard  x / (1 + x)', reinhard, BLUE), ('ACES', aces, RED)]:
        pts = [(ox + x / 4 * gw, oy - fn(x) * gh) for x in xs]; d.line(pts, fill=col, width=3)
    for i, (t, col) in enumerate([('couper (clamp)', (120, 120, 120)), ('Reinhard  x / (1 + x)', BLUE), ('ACES (filmique)', RED)]):
        d.line([ox + 200, 30 + i * 20, ox + 230, 30 + i * 20], fill=col, width=3); d.text((ox + 240, 30 + i * 20), t, fill=INK, font=font(12), anchor='lm')
    d.text((ox + gw, oy + 26), 'lumiere d entree (0 a 4)', fill=INK, font=font(12), anchor='rm'); d.text((ox + 4, oy - gh - 14), 'lumiere de sortie', fill=INK, font=font(12), anchor='lm')
    save(out, '11b-courbes.png')

# ---------- 11c ----------
def img11c():
    t = np.arange(256) / 255.0
    def sS(t): return t * t * (3 - 2 * t)
    looks = {'identite': (t, t, t), 'contraste (courbe en S)': (sS(t),) * 3,
             'teal & orange': (np.clip(t + 0.12 * np.sin(t * np.pi), 0, 1), t, np.clip(t - 0.12 * np.sin(t * np.pi) + 0.10 * (1 - t), 0, 1)),
             'vintage': (0.12 + t * 0.80 + 0.04, 0.12 + t * 0.80, 0.12 + t * 0.76)}
    items = []
    for lab, (r, g, b) in looks.items():
        lr, lg, lb = [np.clip(v * 255, 0, 255).astype(np.uint8) for v in (r, g, b)]
        s = src.astype(np.uint8); im = to_img(np.stack([lr[s[..., 0]], lg[s[..., 1]], lb[s[..., 2]]], -1))
        d = ImageDraw.Draw(im); gx, gy, gs = W - 170, 15, 150
        d.rectangle([gx - 6, gy - 6, gx + gs + 6, gy + gs + 6], fill=(0, 0, 0)); d.line([gx, gy + gs, gx + gs, gy], fill=(90, 90, 90))
        for v, col in [(lr, (255, 80, 80)), (lg, (80, 255, 80)), (lb, (100, 140, 255))]:
            d.line([(gx + i * gs / 255, gy + gs - int(v[i]) * gs / 255) for i in range(256)], fill=col, width=2)
        items.append((lab, im))
    save(sheet(items, 2, 0.48), '11c-looks.png')

    out = Image.new('RGB', (720, 200), PAPER); d = ImageDraw.Draw(out)
    d.text((20, 20), 'Une LUT 1D = une table de 256 cases. L entree est l INDICE, la sortie est le CONTENU.', fill=INK, font=font(13))
    vals = [int(sS(i / 255) * 255) for i in range(256)]; shown = [0, 1, 2, '...', 100, 101, 102, '...', 253, 254, 255]
    x = 20
    for s in shown:
        d.rectangle([x, 70, x + 56, 110], fill=(230, 240, 255) if s != '...' else PAPER, outline=INK if s != '...' else PAPER)
        d.text((x + 28, 55), str(s), fill=BLUE, font=font(12), anchor='mm'); d.text((x + 28, 90), str(vals[s]) if s != '...' else '...', fill=INK, font=font(13), anchor='mm'); x += 62
    d.text((20, 125), 'indice = valeur d entree (c.r)', fill=BLUE, font=font(12)); d.text((20, 145), 'contenu = valeur de sortie (lut[c.r])', fill=INK, font=font(12))
    d.text((20, 172), 'Ici la courbe en S : 100 devient %d, 200 devient %d. Calculee une fois, lue 400 000 fois.' % (vals[100], vals[200]), fill=(90, 90, 90), font=font(12))
    save(out, '11c-lut.png')

# ---------- 11d ----------
def img11d():
    r, g, b = src[..., 0], src[..., 1], src[..., 2]
    Y = 0.299 * r + 0.587 * g + 0.114 * b; Cb = 128 - 0.168736 * r - 0.331264 * g + 0.5 * b; Cr = 128 + 0.5 * r - 0.418688 * g - 0.081312 * b
    def rec(Y, Cb, Cr):
        R = Y + 1.402 * (Cr - 128); G = Y - 0.344136 * (Cb - 128) - 0.714136 * (Cr - 128); B = Y + 1.772 * (Cb - 128); return to_img(np.stack([R, G, B], -1))
    gray = lambda a: to_img(np.repeat(a[..., None], 3, -1))
    save(sheet([('Y : luminance', gray(Y)), ('Cb : bleu / jaune', gray(Cb)), ('Cr : rouge / vert', gray(Cr))], 3, 0.42), '11d-ycbcr.png')
    def blocs(a, n):
        h2, w2 = H // n * n, W // n * n; out = a.copy(); m = a[:h2, :w2].reshape(h2 // n, n, w2 // n, n).mean((1, 3)); out[:h2, :w2] = np.repeat(np.repeat(m, n, 0), n, 1); return out
    n = 16
    save(sheet([('couleur (Cb, Cr) en blocs de 16, Y intacte', rec(Y, blocs(Cb, n), blocs(Cr, n))), ('luminance Y en blocs de 16, couleur intacte', rec(blocs(Y, n), Cb, Cr))], 2, 0.48), '11d-blocs.png')

# ---------- 11e ----------
def lab_from_rgb(c):
    r, g, b = lin(np.array(c, dtype=float))
    l = 0.4122214708 * r + 0.5363325363 * g + 0.0514459929 * b; m = 0.2119034982 * r + 0.6806995451 * g + 0.1073969566 * b; s = 0.0883024619 * r + 0.2817188376 * g + 0.6299787005 * b
    l, m, s = np.cbrt(l), np.cbrt(m), np.cbrt(s)
    return np.array([0.2104542553 * l + 0.7936177850 * m - 0.0040720468 * s, 1.9779984951 * l - 2.4285922050 * m + 0.4505937099 * s, 0.0259040371 * l + 0.7827717662 * m - 0.8086757660 * s])
def rgb_from_lab(L, a, b):
    l = L + 0.3963377774 * a + 0.2158037573 * b; m = L - 0.1055613458 * a - 0.0638541728 * b; s = L - 0.0894841775 * a - 1.2914855480 * b
    l, m, s = l ** 3, m ** 3, s ** 3
    return srgb(np.array([4.0767416621 * l - 3.3077115913 * m + 0.2309699292 * s, -1.2684380046 * l + 2.6097574011 * m - 0.3413193965 * s, -0.0041960863 * l - 0.7034186147 * m + 1.7076147010 * s]))
def img11e():
    A, B = (0, 60, 255), (255, 230, 0); Wd = 700
    out = Image.new('RGB', (Wd + 40, 270), (30, 30, 30)); d = ImageDraw.Draw(out)
    hA, sA, vA = colorsys.rgb_to_hsv(*(np.array(A) / 255)); hB, sB, vB = colorsys.rgb_to_hsv(*(np.array(B) / 255))
    dh = hB - hA; dh = dh - 1 if dh > 0.5 else (dh + 1 if dh < -0.5 else dh)
    la, lb = lab_from_rgb(A), lab_from_rgb(B)
    for x in range(Wd):
        p = x / Wd
        c0 = tuple(int(A[k] + (B[k] - A[k]) * p) for k in range(3))
        c1 = tuple(int(v * 255) for v in colorsys.hsv_to_rgb((hA + dh * p) % 1, sA + (sB - sA) * p, vA + (vB - vA) * p))
        c2 = tuple(int(v) for v in np.clip(rgb_from_lab(*(la + (lb - la) * p)), 0, 255))
        for i, c in enumerate([c0, c1, c2]): d.line([20 + x, 35 + i * 80, 20 + x, 85 + i * 80], fill=c)
    for i, t in enumerate(['RGB (getLerped) : passe par un gris terne', 'HSB (chemin le plus court sur la roue) : passe par des verts hors sujet', 'OKLab : la clarte evolue regulierement, la couleur reste propre']):
        d.text((20, 20 + i * 80), t, fill=GOLD, font=font(12))
    save(out, '11e-degrades.png')

    out = Image.new('RGB', (800, 300), (30, 30, 30)); d = ImageDraw.Draw(out)
    d.text((20, 12), '8 teintes HSB, S = 255, B = 255 : meme "luminosite" HSB. Dessous : leur clarte OKLab (L) en gris.', fill=GOLD, font=font(12))
    for i in range(8):
        c = tuple(int(v * 255) for v in colorsys.hsv_to_rgb(i / 8, 1, 1)); L = lab_from_rgb(c)[0]
        d.rectangle([20 + i * 95, 30, 110 + i * 95, 90], fill=c); gv = int(srgb(L ** 3)); d.rectangle([20 + i * 95, 92, 110 + i * 95, 117], fill=(gv, gv, gv)); d.text((25 + i * 95, 130), 'L=%.2f' % L, fill=GOLD, font=font(11))
    d.text((20, 165), '8 teintes OKLCH, L = 0.75, C = 0.12 : toutes de la meme clarte percue.', fill=GOLD, font=font(12))
    for i in range(8):
        h = i * 2 * math.pi / 8; c = tuple(int(v) for v in np.clip(rgb_from_lab(0.75, 0.12 * math.cos(h), 0.12 * math.sin(h)), 0, 255)); d.rectangle([20 + i * 95, 185, 110 + i * 95, 245], fill=c)
    d.text((20, 265), 'Une palette d interface se construit comme ca : meme L, teintes espacees regulierement.', fill=GOLD, font=font(12))
    save(out, '11e-clarte.png')

# ---------- 11f ----------
MATS = {'protanopie': [0.152286, 1.052583, -0.204868, 0.114503, 0.786281, 0.099216, -0.003882, -0.048116, 1.051998],
        'deuteranopie': [0.367322, 0.860646, -0.227968, 0.280085, 0.672501, 0.047413, -0.011820, 0.042940, 0.968881],
        'tritanopie': [1.255528, -0.076749, -0.178779, -0.078411, 0.930809, 0.147602, 0.004733, 0.691367, 0.303900]}
def simul(a, m):
    M = np.array(m).reshape(3, 3); L = lin(a); return srgb(np.einsum('ij,...j->...i', M, L))
def img11f():
    items = [('vision normale', src_img)] + [(k, to_img(simul(src, m))) for k, m in MATS.items()]
    save(sheet(items, 2, 0.45), '11f-daltonisme.png')
    out = Image.new('RGB', (760, 250), (30, 30, 30)); d = ImageDraw.Draw(out)
    vie, danger = np.array([40, 190, 60.0]), np.array([220, 40, 40.0])
    def row(y, m, label):
        f = (lambda c: tuple(int(v) for v in c)) if m is None else (lambda c: tuple(int(v) for v in np.clip(simul(np.array(c)[None, None, :], m)[0, 0], 0, 255)))
        d.text((20, y - 18), label, fill=GOLD, font=font(12))
        d.rectangle([20, y, 140, y + 30], fill=f(vie)); d.rectangle([150, y, 270, y + 30], fill=f(danger))
        d.rectangle([330, y, 450, y + 30], fill=f(vie)); d.rectangle([460, y, 580, y + 30], fill=f(danger))
        for i in range(0, 120, 10): d.line([460 + i, y, 470 + i, y + 30], fill=f((255, 255, 255)))
        d.text((385, y + 15), '+', fill=f((255, 255, 255)), font=font(16), anchor='mm'); d.text((515, y + 15), '!', fill=f((255, 255, 255)), font=font(16), anchor='mm')
    row(45, None, 'vision normale : vie (vert) et danger (rouge)'); row(125, MATS['deuteranopie'], 'deuteranopie : a gauche les deux jauges se confondent, a droite le motif et le symbole restent')
    d.text((80, 200), 'couleur seule', fill=GOLD, font=font(12), anchor='mm'); d.text((455, 200), 'couleur + motif + symbole', fill=GOLD, font=font(12), anchor='mm')
    save(out, '11f-interface.png')

# ---------- 11g ----------
PALS = {'Game Boy': [(15, 56, 15), (48, 98, 48), (139, 172, 15), (155, 188, 15)],
        'PICO-8': [(0, 0, 0), (29, 43, 83), (126, 37, 83), (0, 135, 81), (171, 82, 54), (95, 87, 79), (194, 195, 199), (255, 241, 232), (255, 0, 77), (255, 163, 0), (255, 236, 39), (0, 228, 54), (41, 173, 255), (131, 118, 156), (255, 119, 168), (255, 204, 170)]}
BAYER = np.array([[0, 8, 2, 10], [12, 4, 14, 6], [3, 11, 1, 9], [15, 7, 13, 5]], dtype=float) / 16 - 0.5
def nearest(a, pal):
    p = np.array(pal, dtype=float); d = ((a[..., None, :] - p[None, None, :, :]) ** 2).sum(-1); return p[d.argmin(-1)]
def quantize(small, pal, method):
    h, w = small.shape[:2]; ecart = 255.0 / len(pal)
    if method == 'plus proche': return nearest(small, pal)
    if method == 'Bayer':
        off = BAYER[np.arange(h)[:, None] % 4, np.arange(w)[None, :] % 4] * ecart; return nearest(small + off[..., None], pal)
    a = small.copy(); out = np.zeros_like(a); p = np.array(pal, dtype=float)
    for j in range(h):
        for i in range(w):
            c = np.clip(a[j, i], 0, 255); q = p[((p - c) ** 2).sum(-1).argmin()]; out[j, i] = q; e = c - q
            if i + 1 < w: a[j, i + 1] += e * 7 / 16
            if j + 1 < h:
                if i > 0: a[j + 1, i - 1] += e * 3 / 16
                a[j + 1, i] += e * 5 / 16
                if i + 1 < w: a[j + 1, i + 1] += e * 1 / 16
    return out
def img11g():
    n = 3; small = src[n // 2::n, n // 2::n][:H // n, :W // n]
    items = []
    for pal_name, methods in [('Game Boy', ['plus proche', 'Bayer', 'Floyd-Steinberg']), ('PICO-8', ['plus proche', 'Bayer', 'Floyd-Steinberg'])]:
        for m in methods:
            q = quantize(small, PALS[pal_name], m); big = np.repeat(np.repeat(q, n, 0), n, 1)
            items.append(('%s, %s' % (pal_name, m), to_img(big)))
    save(sheet(items, 3, 0.4), '11g-dithering.png')
    out = Image.new('RGB', (760, 250), PAPER); d = ImageDraw.Draw(out); cs = 40
    for j in range(4):
        for i in range(4):
            v = int((BAYER[j, i] + 0.5) * 16); g = 255 - v * 16
            d.rectangle([20 + i * cs, 40 + j * cs, 20 + (i + 1) * cs, 40 + (j + 1) * cs], fill=(g, g, g), outline=INK); d.text((20 + i * cs + cs / 2, 40 + j * cs + cs / 2), str(v), fill=(255, 0, 0) if g < 128 else INK, font=font(13), anchor='mm')
    d.text((100, 22), 'matrice de Bayer 4 x 4', fill=INK, font=font(13), anchor='mm')
    xs = np.linspace(0, 255, 520); g = np.tile(xs[None, :], (60, 1))
    for k, (lab, arr) in enumerate([('degrade seuille a 128 : deux zones', np.where(g < 128, 0, 255)), ('le meme, avec Bayer : la trame rend les gris intermediaires', np.where(g + BAYER[np.arange(60)[:, None] % 4, np.arange(520)[None, :] % 4] * 255 < 128, 0, 255))]):
        out.paste(Image.fromarray(np.repeat(arr[..., None], 3, -1).astype(np.uint8)), (220, 40 + k * 95)); d.text((220, 105 + k * 95), lab, fill=INK, font=font(12))
    d.text((20, 215), 'Chaque case ajoute un decalage different avant le seuil : deux pixels voisins de meme valeur peuvent tomber de part et d autre.', fill=(90, 90, 90), font=font(11))
    save(out, '11g-bayer.png')

if __name__ == '__main__':
    import sys
    todo = [img09a, img11a, img11b, img11c, img11d, img11e, img11f, img11g]
    if len(sys.argv) > 1: todo = [globals()['img' + a] for a in sys.argv[1:]]
    for f in todo: f()
