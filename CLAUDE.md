# q1-mac-on-windows

Tier: **sketch** (project-kit 2026-11-12). QMK firmware, a VIA definition and an
AutoHotkey script for using a Keychron Q1 V2 on Windows with Mac habits.

Stack: QMK (C) on Keychron's `playground` branch, VIA JSON, AutoHotkey v2, GitHub Actions.
Runs on: Windows (the keyboard works anywhere; the script is Windows only).

## Rules

- Commit straight to `main` unless I ask for a branch. Small commits, messages that say
  what changed and why.
- Keep it simple: no CI, docs or process this project doesn't need. The README says what
  it is and how to use it; that's enough.
- This repo is public. Keep personal details out of committed files: local paths,
  usernames, machine names, anything about my own setup beyond what the project is.
  Secrets never. PC-specific notes go in my private `pc-setup` repo.
- Firmware binaries are never committed. CI builds them; a `v*` tag attaches the `.bin`
  and the VIA file to a release.
- Licence: GPL-2.0-or-later (derived from QMK). Don't fork Keychron's repo; CI clones it.
- Record a decision worth remembering as one line in the README's "Decisions" list.

## Essentials

These repeat my global defaults for sessions where `~/.claude/CLAUDE.md` isn't loaded
(cloud sessions).

- Commit as `Bobby Filippopoulos <22924908+bflip12@users.noreply.github.com>` in this
  repo, so no personal email lands in its public history. Times in Alberta time.
- Plan before building anything bigger than a small fix, and wait for "go".
- Verify tool behaviour instead of trusting memory. Flag what's unverified.
- Walk me through manual steps one at a time, with click paths, and confirm each.
- Voice: plain and short, no em-dashes, no editorializing adverbs.

## Commands

- Build: push to `main` (artifact) or push a `v*` tag (release). Local build steps are in
  `firmware/README.md`.
- Flash: QMK Toolbox, steps in `firmware/README.md`.

## Gotchas

<!-- Add as they're found: the symptom, the cause, what to do instead. -->
