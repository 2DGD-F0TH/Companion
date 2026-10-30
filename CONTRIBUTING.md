# Contributing to *2D Game Development: The Companion Repository*

Thanks for being here! This repository exists to be a companion to "2D Game Development: From Zero to Hero", as well as a companion on your game dev journey!

Contributions of all sizes are welcome - a one-character typo fix is a real contribution, and so is a whole new example set.

---

## Table of contents

- [Before you start](#before-you-start)
- [What makes a good example](#what-makes-a-good-example)
- [Example structure and conventions](#example-structure-and-conventions)
- [Style guide](#style-guide)
- [Submitting a pull request](#submitting-a-pull-request)
- [Licensing of contributions](#licensing-of-contributions)
- [Third-party code](#third-party-code)
- [Code of conduct](#code-of-conduct)
- [Getting help](#getting-help)

---

## Before you start

**Small, obvious fixes:** just open a pull request. Typos, broken links, wrong variable names, a comment that says the opposite of what the code does - no ceremony required.

**Anything larger:** open an issue first and describe what you want to do. This isn't gatekeeping; it's to save you from writing something that duplicates work in progress or doesn't fit the repository's scope. I don't want to be the one rejecting a PR because someone else is already working on it.

**Check for existing work.** Search open issues and pull requests before starting. If someone's already on it, offer to help rather than racing them.

**Scope check.** This repository accompanies a book, so examples should map to concepts the book actually covers. If you have a great idea for something adjacent but outside that scope, raise it in an issue - sometimes the answer is "yes, that belongs here," and sometimes not. I'm sure we'll find a compromise.

## What makes a good example

An example earns its place in this repository if it satisfies most of these:

- **It runs straight off the gate.** Clone, follow the local README, and it works. No manual patching, no "uncomment this line to make it compile."
- **It's complete.** Not a fragment.
- **It's commented where it counts.** Explain *why*, not *what*. `// increment x` is noise; `// wrap the sprite manually because the engine clamps at the screen edge` is useful.
- **It connects to the book.** The local README should say which chapter or principle or principles it relates to, and what the reader should take away.
- **It's not a duplicate of the book listing.** The book shows the concept in isolation. This repository shows it in a larger environment. If your example is a copy-paste of a book listing, you might be doing it wrong.
- **It teaches something via "hacking".** Ideally the reader can tweak one number or flag in the code and see the consequence. Interactive examples beat static ones.

Deliberately *not* required: production quality, performance optimisation, exhaustive error handling, or architectural elegance. These are teaching artifacts. Clarity over robustness: a slightly naive example that reads well is preferable to a clever one that doesn't.

---

## Example structure and conventions

```
example-name/
├── README.md          # what this set shows, mapping to the book
├── main.[ext]         # entry point
├── [assets/]          # only if needed; keep small
├── Makefile           # only if needed; allows to compile with one `make` command
└── README.md          # notes, gotchas, things to try
```

Conventions:

- **Entry point:** `main.[ext]` unless the language or engine dictates otherwise. If it does, say so in the local README.
- **Local READMEs are mandatory.** Every example directory gets one. Minimum contents: what it is, how to run it, and two or three "try changing this" suggestions.
- **Assets stay small.** If an example needs a sprite, a tile, or a sound, keep it under a few hundred kilobytes and prefer generated or public-domain assets. Document the asset's origin in the local README.
- **No shared state between examples.** An example must not depend on another example having been run first.

## Style guide

**Language and formatting**

- Follow your language's standard community style conventions.
- Consistent indentation within a file; preferably 4 spaces.
- Descriptive names for anything a reader will follow across more than a few lines. Single letters are fine for loop counters and throwaway maths.
- Comments in English, complete sentences, explaining intent.

**Consistency over preference**

If the surrounding code does something a particular way - naming, file layout, how it initialises the engine - match it, even if you'd do it differently. Consistency across examples is extremely valuable. If a convention is genuinely bad, propose changing it across the board in an issue rather than diverging in one file.

**Formatting your code**

Run your language's reference formatter before committing, if it has one. Don't reformat unrelated code in the same commit as your change - it makes the diff unreviewable.

## Submitting a pull request

Before you open it:

- [ ] The example runs from a clean clone, following its own README.
- [ ] A local README exists and covers running it, what to look at, and what to try changing.
- [ ] No unrelated reformatting or drive-by changes.
- [ ] No third-party code without documented, compatible licensing (see below).
- [ ] Assets are small and their origin is documented.

In the PR description, tell me:

- **What** you changed.
- **Why** - what was wrong, unclear, or missing.
- **How to verify** it - the commands to run and what to expect.
- **Which book chapter or principle** it connects to, if it's a new example.

Keep PRs focused. One example, one fix, one topic per PR. If you have three unrelated improvements, that's three PRs, and they'll each get reviewed faster.

Draft PRs are welcome if you want early feedback on a work in progress - mark it as draft and say what you're unsure about.

---

## Licensing of contributions

This is something worth reading carefully, because it differs from most repositories.

**This repository is licensed under the [PolyForm Noncommercial License 1.0.0](LICENSE).** It is *source-available*, not an OSI-approved open source. The restriction is narrow: nobody may sell access to the repository or a derivative copy of it. Using the code in games - including commercial games - is explicitly permitted.

By submitting a contribution, you agree that:

- Your contribution is licensed to the project and to everyone else under PolyForm Noncommercial 1.0.0;
- You are not granting an exclusive licence; you keep your copyright;
- You have the right to submit the code under these terms;
- Your contribution may be modified, redistributed, or removed by the maintainer as part of maintaining the repository.

**Please make sure you're comfortable with this before contributing.** If you want your code to be usable under an OSI-approved licence, this might not be the right venue, and that's completely reasonable - there are plenty of MIT and Apache-2.0 projects that would love your help.

**On relicensing.** Because PolyForm Noncommercial isn't open source, the maintainer can't unilaterally relicense your contribution to an open source licence later without your agreement. If relicensing ever becomes desirable, contributors will be asked individually. Your sign-off doesn't hand over that right.

---

## Third-party code

Only submit code you wrote, or code whose licence permits inclusion here.

**Generally fine:**

| Source licence                  | Can it go in? | Conditions                                                            |
| ---                             | ---           | ---                                                                   |
| Public domain / Unlicense / CC0 | ✅ Yes        | Note the origin in the local README                                   |
| MIT, BSD, ISC                   | ✅ Yes        | Retain the original copyright notice in the file or a nearby `NOTICE` |
| Apache-2.0                      | ✅ Yes        | Retain the notice; note any modified files                            |
| Your own prior work             | ✅ Yes        | Mention it so the provenance stays clear                              |

**Generally not fine:**

| Source licence                         | Can it go in? | Why                                                            |
| ---                                    | ---           | ---                                                            |
| GPL / LGPL / AGPL                      | ❌ No         | Copyleft terms can't be reconciled with PolyForm Noncommercial |
| CC BY-NC-ND                            | ❌ No         | No-derivatives conflicts with modifying the example            |
| "Free for personal use" / custom EULAs | ⚠️ Ask first  | Usually too vague to rely on                                   |
| Stack Overflow snippets                | ⚠️ Ask first  | CC BY-SA licensing, attribution and share-alike complications  |
| Anything you found without a licence   | ❌ No         | No licence means "all rights reserved"                         |

If you're unsure, open an issue and ask *before* writing the code. It's much easier to redirect a plan than to unwind a merged PR.

**On the repository's own provenance.** This repository was bootstrapped from two earlier projects by the same author, originally released under the Unlicense. Those original releases remain in the public domain, but the versions *in this repository* - including the heavy modifications - are under PolyForm Noncommercial. Don't assume code here is public domain just because an ancestor of it once was.

**AI-generated code.** See the [AI Policy](AI_POLICY.md).

---

## Code of conduct

Short version: be decent to people.

Specifically:

- Critique code and ideas, not people.
- Assume good faith. Most confusing contributions come from enthusiasm, not carelessness.
- Beginners are explicitly welcome. This repository accompanies an introductory book; "this is obvious" is never a useful review comment.
- No harassment, slurs, or personal attacks, in issues, PRs, or anywhere else associated with the project.
- Respect requests to drop a topic and move on.

Maintainers may edit, lock, or delete comments, close issues and PRs, or block accounts that make the project worse for other people. That's not a debate.

---

## Getting help

- **Unsure whether an idea fits?** Open an issue and ask. Half-formed ideas are fine.
- **Stuck on setup?** Open a discussion or open an issue with your OS, versions, and the exact command and error output.
- **Licensing question?** Ask before contributing, not after. I'd rather answer a question than reject a PR.
- **General chat about the book or the examples?** Use [Discussions](https://github.com/2DGD-F0TH/Companion/discussions).

And if you've read this far and you're still not sure where to start: fixing a typo in an example README is a perfectly good first contribution, and it will genuinely improve the repository.

---

*Thanks for reading. Now go break something and tell me about it.*
