# Génère les illustrations des cours 10, 11, 14, 17, 18 (traitement d'image sur pandaroux.jpg).
# Usage : python generer_b.py   (nécessite Pillow et numpy)
from PIL import Image, ImageDraw, ImageFont
import numpy as np, math, os, colorsys

OUT = os.path.dirname(os.path.abspath(__file__))
DATA = os.path.join(OUT, '..', '..', 'data')
def font(size=14):
    try: return ImageFont.truetype('/System/Library/Fonts/Menlo.ttc', size)
    except Exception: return ImageFont.load_default(size=size)
INK = (40, 40, 40); BLUE = (30, 90, 200); RED = (200, 40, 40); GREY = (150, 150, 150); PAPER = (250, 250, 250)

src_img = Image.open(os.path.join(DATA, 'pandaroux.jpg')).convert('RGB')
src = np.array(src_img).astype(np.float32)            # (516, 774, 3)
H, W = src.shape[:2]
lum = 0.299 * src[..., 0] + 0.587 * src[..., 1] + 0.114 * src[..., 2]

def to_img(a): return Image.fromarray(np.clip(a, 0, 255).astype(np.uint8))
def save(im, name): im.save(os.path.join(OUT, name), optimize=True); print('ok', name)

def sheet(items, cols, scale=0.5, label_h=26):
    tw, th = int(W * scale), int(H * scale); rows = math.ceil(len(items) / cols)
    out = Image.new('RGB', (cols * tw + (cols + 1) * 8, rows * (th + label_h) + (rows + 1) * 8), PAPER)
    d = ImageDraw.Draw(out)
    for k, (lab, im) in enumerate(items):
        r, c = divmod(k, cols); x = 8 + c * (tw + 8); y = 8 + r * (th + label_h + 8)
        out.paste(im.resize((tw, th), Image.LANCZOS), (x, y))
        d.text((x + tw / 2, y + th + label_h / 2), lab, fill=INK, font=font(14), anchor='mm')
    return out

# ---------- 10 : pixels ----------
def img10():
    im = Image.open(os.path.join(DATA, 'image2.png')).convert('RGB'); a = np.array(im)
    # fenêtre 12x12 avec le plus de couleurs différentes
    best, bx, by = -1, 0, 0
    for y in range(0, 200 - 12, 2):
        for x in range(0, 200 - 12, 2):
            n = len(np.unique(a[y:y + 12, x:x + 12].reshape(-1, 3), axis=0))
            if n > best: best, bx, by = n, x, y
    Z = 24; zoom = im.crop((bx, by, bx + 12, by + 12)).resize((12 * Z, 12 * Z), Image.NEAREST)
    out = Image.new('RGB', (200 + 40 + 12 * Z + 20, 12 * Z + 60), PAPER); d = ImageDraw.Draw(out)
    out.paste(im, (10, 20)); d.rectangle([10 + bx, 20 + by, 10 + bx + 12, 20 + by + 12], outline=RED, width=2)
    ox, oy = 250, 20; out.paste(zoom, (ox, oy))
    for k in range(13):
        d.line([ox + k * Z, oy, ox + k * Z, oy + 12 * Z], fill=(80, 80, 80), width=1); d.line([ox, oy + k * Z, ox + 12 * Z, oy + k * Z], fill=(80, 80, 80), width=1)
    px, py = 5, 6; col = tuple(int(v) for v in a[by + py, bx + px])
    d.rectangle([ox + px * Z, oy + py * Z, ox + (px + 1) * Z, oy + (py + 1) * Z], outline=RED, width=3)
    d.text((ox + 6 * Z, oy + 12 * Z + 12), 'pixel (%d, %d) : R=%d G=%d B=%d' % (bx + px, by + py, *col), fill=INK, font=font(14), anchor='mm')
    d.text((110, 20 + 200 + 12), 'image2.png (200 x 200)', fill=INK, font=font(13), anchor='mm')
    d.text((ox + 6 * Z, 8), 'zoom x24 : chaque case est UN pixel', fill=INK, font=font(13), anchor='mm')
    save(out, '10-pixels.png')

# ---------- 11 : filtres par pixel ----------
def hsv_shift(arr_img, fn):
    hsv = np.array(arr_img.convert('HSV')).astype(np.float32); hsv = fn(hsv)
    return Image.fromarray(np.clip(hsv, 0, 255).astype(np.uint8), 'HSV').convert('RGB')

def img11():
    items = [('0 original', src_img), ('1 negatif', to_img(255 - src)), ('3 gris (luminance)', to_img(np.repeat(lum[..., None], 3, -1))),
             ('5 contraste k = 2', to_img((src - 128) * 2 + 128)), ('6 seuil 128', to_img(np.repeat((lum >= 128)[..., None] * 255.0, 3, -1))),
             ('7 posterisation pas = 64', to_img(np.floor(src / 64) * 64))]
    def rot(h): h[..., 0] = (h[..., 0] + 128) % 256; return h
    items.append(('8 rotation de teinte +128', hsv_shift(src_img, rot)))
    def splash(h):
        cible = 20; ecart = np.abs(h[..., 0] - cible); ecart = np.where(ecart > 128, 256 - ecart, ecart)
        h[..., 1] = np.where(ecart < 20, h[..., 1], 0); return h
    items.append(('9 color splash (teinte orange)', hsv_shift(src_img, splash)))
    save(sheet(items, 4, 0.42), '11-filtres.png')

    # courbes de transfert
    n = 5; S = 150; pad = 34; out = Image.new('RGB', (n * (S + pad) + pad, S + 2 * pad + 10), PAPER); d = ImageDraw.Draw(out)
    xs = np.arange(256)
    curves = [('negatif', 255 - xs), ('luminosite +60', np.clip(xs + 60, 0, 255)), ('contraste k = 2', np.clip((xs - 128) * 2 + 128, 0, 255)),
              ('seuil 128', np.where(xs < 128, 0, 255)), ('posterisation 64', np.floor(xs / 64) * 64)]
    for k, (lab, ys) in enumerate(curves):
        ox = pad + k * (S + pad); oy = pad + S
        d.rectangle([ox, oy - S, ox + S, oy], outline=GREY); d.line([ox, oy, ox + S, oy - S], fill=(200, 200, 200))
        pts = [(ox + x / 255 * S, oy - y / 255 * S) for x, y in zip(xs, ys)]
        d.line(pts, fill=RED, width=2)
        d.text((ox + S / 2, oy + 14), lab, fill=INK, font=font(12), anchor='mm')
        d.text((ox + S / 2, oy - S - 12), 'sortie', fill=GREY, font=font(10), anchor='mm') if k == 0 else None
    d.text((pad + S / 2, pad + S + 28), 'entree 0..255 ->', fill=GREY, font=font(10), anchor='mm')
    save(out, '11-courbes.png')

# ---------- 14 : géométrie ----------
def img14():
    ys, xs = np.mgrid[0:H, 0:W]
    def read(sx, sy):
        sx = np.clip(sx.astype(int), 0, W - 1); sy = np.clip(sy.astype(int), 0, H - 1); return to_img(src[sy, sx])
    items = [('0 original', src_img), ('1 miroir', read(W - 1 - xs, ys)), ('2 rotation 180', read(W - 1 - xs, H - 1 - ys)),
             ('3 pixelisation n = 20', read(xs // 20 * 20, ys // 20 * 20)), ('4 vagues', read(xs + 25 * np.sin(ys / 20.0), ys))]
    d = 15; g = np.array(read(xs - d, ys)); c = np.array(src_img); r = np.array(read(xs + d, ys))
    items.append(('5 glitch d = 15', Image.fromarray(np.stack([g[..., 0], c[..., 1], r[..., 2]], -1))))
    save(sheet(items, 3, 0.42), '14-geometrie.png')

    # lecture à l'envers
    out = Image.new('RGB', (620, 330), PAPER); d = ImageDraw.Draw(out); n = 8; cs = 26
    def grid(ox, oy, title, hi, col):
        for i in range(n):
            for j in range(n):
                d.rectangle([ox + i * cs, oy + j * cs, ox + (i + 1) * cs, oy + (j + 1) * cs], fill=(235, 235, 235), outline=GREY)
        d.rectangle([ox + hi[0] * cs, oy + hi[1] * cs, ox + (hi[0] + 1) * cs, oy + (hi[1] + 1) * cs], fill=col, outline=INK, width=2)
        d.text((ox + n * cs / 2, oy - 14), title, fill=INK, font=font(14), anchor='mm')
    grid(40, 50, 'resultat', (2, 3), (255, 200, 200)); grid(370, 50, 'source', (5, 3), (200, 220, 255))
    d.line([40 + 3 * cs, 50 + 3.5 * cs, 370 + 5 * cs, 50 + 3.5 * cs], fill=RED, width=3)
    d.polygon([(370 + 5 * cs, 50 + 3.5 * cs), (370 + 5 * cs - 14, 50 + 3.5 * cs - 7), (370 + 5 * cs - 14, 50 + 3.5 * cs + 7)], fill=RED)
    d.text((310, 50 + 3.5 * cs - 18), 'ou lire ?', fill=RED, font=font(14), anchor='mm')
    d.text((40 + 2.5 * cs, 50 + n * cs + 16), '(x, y) = (2, 3)', fill=INK, font=font(13), anchor='mm')
    d.text((370 + n * cs, 50 + n * cs + 16), 'miroir : (w - 1 - x, y) = (5, 3)', fill=INK, font=font(13), anchor='rm')
    d.text((310, 305), 'Pour CHAQUE pixel du resultat, on calcule ou aller chercher sa couleur dans la source.', fill=INK, font=font(12), anchor='mm')
    save(out, '14-lecture-inverse.png')

# ---------- 17 : convolution ----------
def convolve(a, k, biais=0):
    k = np.array(k, dtype=np.float32).reshape(3, 3); p = np.pad(a, ((1, 1), (1, 1), (0, 0)), mode='edge'); out = np.full_like(a, biais)
    for dy in range(3):
        for dx in range(3):
            out += k[dy, dx] * p[dy:dy + H, dx:dx + W]
    return out

def img17():
    items = [('0 original', src_img), ('1 flou boite', to_img(convolve(src, [1 / 9] * 9))),
             ('2 flou gaussien', to_img(convolve(src, [1, 2, 1, 2, 4, 2, 1, 2, 1]) / 16)),
             ('3 nettete', to_img(convolve(src, [0, -1, 0, -1, 5, -1, 0, -1, 0]))),
             ('4 contours', to_img(convolve(src, [-1] * 4 + [8] + [-1] * 4))),
             ('5 relief', to_img(convolve(src, [-1, 0, 0, 0, 0, 0, 0, 0, 1], 128)))]
    save(sheet(items, 3, 0.42), '17-convolution.png')

    out = Image.new('RGB', (700, 260), PAPER); d = ImageDraw.Draw(out); cs = 46
    vals = [[120, 130, 125], [118, 140, 128], [122, 126, 124]]; ks = [[0, -1, 0], [-1, 5, -1], [0, -1, 0]]
    def grid(ox, oy, m, title, fmt):
        for j in range(3):
            for i in range(3):
                col = (255, 230, 200) if (i, j) == (1, 1) else (235, 235, 235)
                d.rectangle([ox + i * cs, oy + j * cs, ox + (i + 1) * cs, oy + (j + 1) * cs], fill=col, outline=INK)
                d.text((ox + i * cs + cs / 2, oy + j * cs + cs / 2), fmt % m[j][i], fill=INK, font=font(14), anchor='mm')
        d.text((ox + 1.5 * cs, oy - 16), title, fill=INK, font=font(13), anchor='mm')
    grid(30, 60, vals, 'pixel et ses 8 voisins', '%d'); d.text((190, 60 + 1.5 * cs), 'x', fill=INK, font=font(24), anchor='mm')
    grid(220, 60, ks, 'noyau (poids)', '%d'); d.text((380, 60 + 1.5 * cs), '=', fill=INK, font=font(24), anchor='mm')
    s = sum(vals[j][i] * ks[j][i] for i in range(3) for j in range(3))
    d.rectangle([420, 60 + cs, 420 + cs, 60 + 2 * cs], fill=(255, 230, 200), outline=INK, width=2); d.text((420 + cs / 2, 60 + 1.5 * cs), str(int(s)), fill=INK, font=font(14), anchor='mm')
    d.text((420 + cs / 2, 60 - 16), 'nouveau pixel', fill=INK, font=font(13), anchor='mm')
    d.text((350, 225), 'somme = 140*5 - 130 - 118 - 128 - 126 = %d  (le centre ressort : plus net)' % s, fill=INK, font=font(13), anchor='mm')
    d.text((350, 245), 'chaque voisin est multiplie par son poids, on additionne tout', fill=GREY, font=font(12), anchor='mm')
    save(out, '17-noyau.png')

# ---------- 18 : peinture par particules ----------
def img18():
    rng = np.random.default_rng(1)
    edge = np.abs(convolve(np.repeat(lum[..., None], 3, -1), [-1] * 4 + [8] + [-1] * 4))[..., 0]
    edge = np.clip(edge, 0, 255) / 255.0
    save(to_img(edge * 255).convert('L'), '18-contours.png')
    hsv = np.array(src_img.convert('HSV')).astype(np.float32)
    N = 600; px = rng.uniform(0, W, N); py = rng.uniform(0, H, N); ang = rng.uniform(0, 2 * math.pi, N)
    canvas = np.zeros((H, W, 3), dtype=np.float32); dt = 1 / 60; vitesse = 80
    masks = {}
    def disc(r):
        key = round(r * 2) / 2
        if key not in masks:
            R = int(math.ceil(key)); yy, xx = np.mgrid[-R:R + 1, -R:R + 1]; masks[key] = ((xx ** 2 + yy ** 2) <= key ** 2 + 0.25).astype(np.float32)
        return masks[key]
    def paint(x, y, col, r, alpha=180 / 255):
        m = disc(r); R = m.shape[0] // 2; x, y = int(x), int(y)
        x0, y0, x1, y1 = max(x - R, 0), max(y - R, 0), min(x + R + 1, W), min(y + R + 1, H)
        if x1 <= x0 or y1 <= y0: return
        mm = m[y0 - (y - R):y1 - (y - R), x0 - (x - R):x1 - (x - R)][..., None] * alpha
        canvas[y0:y1, x0:x1] = canvas[y0:y1, x0:x1] * (1 - mm) + np.array(col, dtype=np.float32) * mm
    frames = 900; t = 0
    for f in range(frames):
        t += dt
        ang = (np.sin(px / 80) + np.cos(py / 80)) * math.pi + t * 0.1
        ix = np.clip(px.astype(int), 0, W - 1); iy = np.clip(py.astype(int), 0, H - 1)
        bord = edge[iy, ix]; v = vitesse * (1 - 0.7 * bord); ang = ang + bord * rng.uniform(-3, 3, N) * dt
        for i in range(N):
            c = src[iy[i], ix[i]]; h, s, b = hsv[iy[i], ix[i]]
            dec = (i % 21) - 10; rr, gg, bb = colorsys.hsv_to_rgb(((h + dec) % 256) / 255, s / 255, b / 255)
            taille = (6 - 5 * bord[i]) * (0.5 + b / 255)
            paint(px[i], py[i], (rr * 255, gg * 255, bb * 255), taille)
        px = px + np.cos(ang) * v * dt; py = py + np.sin(ang) * v * dt
        out = (px < 0) | (px >= W) | (py < 0) | (py >= H)
        px[out] = rng.uniform(0, W, out.sum()); py[out] = rng.uniform(0, H, out.sum())
        if f == 90: save(to_img(canvas), '18-peinture-debut.png')
    save(to_img(canvas), '18-peinture.png')
    # détail agrandi
    crop = to_img(canvas).crop((150, 120, 450, 320)).resize((600, 400), Image.LANCZOS); save(crop, '18-peinture-detail.png')

if __name__ == '__main__':
    import sys
    todo = [img10, img11, img14, img17, img18]
    if len(sys.argv) > 1: todo = [globals()['img' + a] for a in sys.argv[1:]]
    for fn in todo:
        fn()
