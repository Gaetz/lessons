#!/usr/bin/env node
/**
 * Lance une commande Slidev sur une leçon, depuis la racine du repo.
 *
 *   pnpm lesson dev    Y1/00-rentree
 *   pnpm lesson build  Y1/00-rentree
 *   pnpm lesson export Y1/00-rentree
 *   pnpm list
 */
import { spawn } from 'node:child_process'
import { readdirSync, existsSync } from 'node:fs'
import { join } from 'node:path'

const root = new URL('..', import.meta.url).pathname
const YEARS = ['Y1', 'Y2', 'Y3', 'Y4', 'Y5']

function lessons() {
  const out = []
  for (const y of YEARS) {
    const dir = join(root, y)
    if (!existsSync(dir)) continue
    for (const d of readdirSync(dir, { withFileTypes: true })) {
      if (d.isDirectory() && existsSync(join(dir, d.name, 'slides.md'))) out.push(`${y}/${d.name}`)
    }
  }
  return out
}

const [cmd, target] = process.argv.slice(2)

if (!cmd || cmd === '--list') {
  const all = lessons()
  console.log(all.length ? all.join('\n') : 'aucune leçon pour l’instant')
  process.exit(0)
}

if (!target) {
  console.error(`usage: pnpm lesson <dev|build|export> <année/leçon>\n\nleçons :\n  ${lessons().join('\n  ')}`)
  process.exit(1)
}

const dir = join(root, target)
if (!existsSync(join(dir, 'slides.md'))) {
  console.error(`pas de slides.md dans ${target}`)
  process.exit(1)
}

spawn('npm', ['run', cmd], { cwd: dir, stdio: 'inherit' })
  .on('exit', (c) => process.exit(c ?? 0))
