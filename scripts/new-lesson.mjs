#!/usr/bin/env node
/**
 * Crée une leçon à partir de _template/.
 *
 *   pnpm new Y2 03-pipeline-usd "Pipeline et USD"
 */
import { cp, readFile, writeFile, mkdir } from 'node:fs/promises'
import { existsSync } from 'node:fs'
import { join } from 'node:path'

const root = new URL('..', import.meta.url).pathname
const [year, slug, ...titleParts] = process.argv.slice(2)
const title = titleParts.join(' ')

if (!year || !slug || !title) {
  console.error('usage: pnpm new <Y1..Y5> <NN-slug> "<Titre de la leçon>"')
  process.exit(1)
}
if (!/^Y[1-5]$/.test(year)) { console.error('année invalide : Y1 à Y5'); process.exit(1) }

const dest = join(root, year, slug)
if (existsSync(dest)) { console.error(`${year}/${slug} existe déjà`); process.exit(1) }

await mkdir(join(root, year), { recursive: true })
await cp(join(root, '_template'), dest, { recursive: true })

for (const f of ['package.json', 'slides.md']) {
  const p = join(dest, f)
  const s = (await readFile(p, 'utf8'))
    .replaceAll('__SLUG__', slug)
    .replaceAll('__YEAR__', year)
    .replaceAll('__TITLE__', title)
  await writeFile(p, s)
}

console.log(`${year}/${slug} créée.\n\n  pnpm install\n  pnpm lesson dev ${year}/${slug}`)
