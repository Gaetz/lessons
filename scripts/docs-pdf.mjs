#!/usr/bin/env node
/**
 * Convertit les documents de cours markdown d'une leçon en PDF téléchargeables.
 *
 *   node scripts/docs-pdf.mjs Y1/01-code-et-pixels
 *
 * Lit   <leçon>/public/ressources/cours/*.md
 * Écrit <leçon>/public/ressources/cours/pdf/*.pdf
 *
 * Utilise markdown-it (dépendance de Slidev) et playwright-chromium (déjà
 * présent pour l'export Slidev). À relancer après toute modification des
 * documents (par exemple après cours/inserer_code.py).
 */
import { readdir, readFile, writeFile, mkdir, rm } from 'node:fs/promises'
import { join, resolve, basename } from 'node:path'
import { pathToFileURL } from 'node:url'
import { createRequire } from 'node:module'

const root = resolve(new URL('..', import.meta.url).pathname)
const lesson = process.argv[2]
if (!lesson) {
  console.error('usage : node scripts/docs-pdf.mjs <année>/<leçon>')
  process.exit(1)
}

const lessonDir = join(root, lesson)
const coursDir = join(lessonDir, 'public', 'ressources', 'cours')
const outDir = join(coursDir, 'pdf')

// playwright vient du node_modules de la leçon ; markdown-it est une
// dépendance transitive de Slidev, on la retrouve dans le store pnpm
const req = createRequire(join(lessonDir, 'package.json'))
const { chromium } = req('playwright-chromium')
const pnpmStore = join(root, 'node_modules', '.pnpm')
const mdDir = (await readdir(pnpmStore)).find(d => /^markdown-it@\d/.test(d))
if (!mdDir) { console.error('markdown-it introuvable dans le store pnpm'); process.exit(1) }
const MarkdownIt = req(join(pnpmStore, mdDir, 'node_modules', 'markdown-it'))

const md = new MarkdownIt({ html: true, linkify: false, typographer: false })

// Charte NDP/ARTFX, version imprimable
const CSS = `
  @page { margin: 0; }
  * { box-sizing: border-box; }
  body {
    font-family: 'Raleway', 'Helvetica Neue', Arial, sans-serif;
    font-size: 10.5pt; line-height: 1.55; color: #111;
    margin: 0; padding: 2cm 1.8cm;
  }
  h1 { font-size: 20pt; font-weight: 900; line-height: 1.15; margin: 0 0 .8em;
       padding-bottom: .35em; border-bottom: 2.5pt solid #EA5027; }
  h2 { font-size: 13.5pt; font-weight: 800; margin: 1.6em 0 .5em; color: #000; }
  h2::before { content: ''; display: inline-block; width: .55em; height: .55em;
       background: #EA5027; margin-right: .45em; }
  h3 { font-size: 11.5pt; font-weight: 700; margin: 1.2em 0 .4em; color: #444; }
  p { margin: .55em 0; }
  a { color: #0F6FA5; text-decoration: none; }
  blockquote { margin: .8em 0; padding: .5em .9em; background: #f4f4ef;
       border-left: 3pt solid #EA5027; }
  blockquote p { margin: .25em 0; }
  code { font-family: 'SF Mono', 'Cascadia Code', Consolas, Menlo, monospace;
       font-size: .88em; background: #f2f2ee; padding: .08em .3em; border-radius: 2px; }
  pre { background: #f6f6f2; border-left: 3pt solid #EA5027; border-radius: 2px;
       padding: .7em .9em; overflow-x: auto; page-break-inside: avoid; }
  pre code { background: none; padding: 0; font-size: 8.5pt; line-height: 1.5; }
  table { border-collapse: collapse; margin: .8em 0; width: 100%; font-size: 9.5pt; }
  th, td { border: .5pt solid #ccc; padding: .35em .6em; text-align: left; vertical-align: top; }
  th { background: #f2f2ee; font-weight: 700; }
  img { max-width: 100%; display: block; margin: .9em auto; page-break-inside: avoid; }
  li { margin: .3em 0; }
  hr { border: none; border-top: .5pt solid #ccc; margin: 1.5em 0; }
`

const files = (await readdir(coursDir)).filter(f => f.endsWith('.md')).sort()
await mkdir(outDir, { recursive: true })

const browser = await chromium.launch()
const page = await browser.newPage()

for (const f of files) {
  const src = await readFile(join(coursDir, f), 'utf8')
  const body = md.render(src)
  // <base> : les images relatives img/... se résolvent dans le dossier cours
  const html = `<!doctype html><html><head><meta charset="utf-8">
    <style>${CSS}</style></head><body>${body}</body></html>`
  // Un fichier temporaire DANS le dossier cours : les images relatives img/...
  // se chargent alors en file:// (interdit depuis une page setContent/about:blank).
  const tmp = join(coursDir, '.apercu-pdf.html')
  await writeFile(tmp, html)
  await page.goto(pathToFileURL(tmp).href, { waitUntil: 'networkidle' })
  const out = join(outDir, basename(f, '.md') + '.pdf')
  await page.pdf({
    path: out,
    format: 'A4',
    printBackground: true,
    displayHeaderFooter: true,
    headerTemplate: '<span></span>',
    footerTemplate: `<div style="width:100%; font-size:7pt; color:#888;
        font-family: Arial; padding: 0 1.8cm; display:flex; justify-content:space-between;">
        <span>Code et pixels — BTS SIO SLAM, NDP &times; ARTFX</span>
        <span><span class="pageNumber"></span> / <span class="totalPages"></span></span></div>`,
    margin: { top: '1.4cm', bottom: '1.6cm', left: '0', right: '0' },
  })
  console.log('pdf :', basename(out))
}

await rm(join(coursDir, '.apercu-pdf.html'), { force: true })
await browser.close()
console.log(`\n${files.length} PDF dans ${outDir.replace(root + '/', '')}`)
