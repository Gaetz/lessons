#!/usr/bin/env node
/**
 * Recupere les assets lourds listes dans le assets.json de la lecon courante.
 * Ils ne sont PAS dans git : public/heavy/ est ignore.
 *   pnpm assets        (depuis le dossier de la lecon)
 */
import { readFile, mkdir, writeFile, access } from 'node:fs/promises'
import { dirname, join } from 'node:path'

const lesson = process.cwd()
const manifest = JSON.parse(await readFile(join(lesson, 'assets.json'), 'utf8'))
const entries = Object.entries(manifest.files ?? {})

if (!entries.length) { console.log('aucun asset lourd declare'); process.exit(0) }

for (const [dest, url] of entries) {
  const out = join(lesson, 'public', 'heavy', dest)
  try { await access(out); console.log('ok   ', dest); continue } catch {}
  console.log('fetch', dest)
  const res = await fetch(url)
  if (!res.ok) { console.error(`  echec ${res.status} - ${url}`); continue }
  await mkdir(dirname(out), { recursive: true })
  await writeFile(out, Buffer.from(await res.arrayBuffer()))
}
