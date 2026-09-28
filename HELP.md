# Simple Line Editor (Minimal Edition) — Help

A command-line line editor. Type a command name (case-insensitive) at
the `editor>` prompt, followed by any arguments. Line numbers are
**1-indexed** (the first line is line 1). Text matching inside the
document (FIND, REPLACE) is **case-sensitive**, even though the command
names themselves are not.

Type `HELP` at any time inside the editor to see the command list again.

**Limits:** up to 500 lines, up to 255 characters per line.

---

## Commands

### `SHOW` — Display the document
Prints every line with its line number.

```
editor> SHOW
--- DOCUMENT START ---
  1 | The Quick Brown Fox
  2 | jumps over the lazy dog
--- DOCUMENT END ---
```

If the document is empty:

```
editor> SHOW
[ Document is empty ]
```

### `INS <line#> <text>` — Insert a line
Inserts `text` at `line#`, shifting that line and everything below it
down by one. `line#` may be any value from `1` to `(current line count + 1)`
— using the highest value appends to the end.

```
editor> INS 1 The Quick Brown Fox
Inserted line 1.
```

### `DEL <line#>` — Delete a line
Deletes the line at `line#`, shifting the lines below it up by one.

```
editor> DEL 2
Deleted line 2.
```

### `EDIT <line#> <text>` — Replace a whole line
Overwrites the **entire** content of `line#` with new `text`. This is
different from `REPLACE`, which only swaps out a matching word or phrase
— `EDIT` replaces the whole line at once.

```
editor> EDIT 1 A totally new first line
Updated line 1.
```

### `SAVE <filename>` — Save to file
Writes the document to a text file, one line per document line.

```
editor> SAVE mydoc.txt
Saved to mydoc.txt.
```

### `LOAD <filename>` — Load from file
Reads a text file, **replacing** the current document with its contents.
If the file can't be opened, the current document is left unchanged.

```
editor> LOAD mydoc.txt
Loaded 2 line(s).
```

### `FIND <phrase>` — Search
Searches every line for `phrase` (a word *or* multi-word phrase — anything
you type after `FIND ` is treated as the whole search term) and reports
every matching line.

```
editor> FIND Brown Fox
Line   1: The Quick Brown Fox
Found 1 match(es).
```

If nothing matches, it still reports the count:

```
editor> FIND zzz
Found 0 match(es).
```

### `REPLACE <target> <replacement>` — Find & replace
Replaces every occurrence of `target` with `replacement`, **across the
whole document** (this version does not support replacing on a single
line only). `target` must be a single word (no spaces); `replacement`
can contain spaces.

```
editor> REPLACE the THE
Replaced 1 occurrence(s).
```

### `STATS` — Document statistics
Reports total line count, word count (words are split on spaces/tabs),
and total character count (not including line breaks).

```
editor> STATS
Lines: 2 | Words: 9 | Chars: 42
```

### `UNDO` — Undo the last change
Reverses the most recent `INS`, `DEL`, `EDIT`, `LOAD`, `REPLACE`,
`CLEAR`, `UPPER`, or `LOWER`. This is a **single-level** undo — it
restores the document to exactly how it looked before that one change.
Undoing twice in a row with no new change in between has nothing left
to undo.

```
editor> UNDO
Undone.
editor> UNDO
Nothing to undo.
```

### `CLEAR` — Clear the document
Empties the entire document. Undoable with `UNDO`.

```
editor> CLEAR
Cleared.
```

### `UPPER` / `LOWER` — Change case
Converts every line in the document to uppercase or lowercase.
Undoable with `UNDO`.

```
editor> UPPER
Converted to UPPERCASE.
editor> LOWER
Converted to lowercase.
```

### `HELP` — Command list
Prints a one-line summary of all available commands.

### `EXIT` — Quit
Exits the editor.

---

## Error Handling

The editor doesn't crash on bad input:

- Inserting/deleting/editing at a line number outside the valid range
  prints an `Error/Usage:` message showing the valid range, and the
  document is left unchanged.
- `INS` and `EDIT` require text to be given — an empty argument is
  rejected with a usage message.
- `SAVE`/`LOAD` with a file that can't be opened prints an error instead
  of crashing; a failed `LOAD` leaves the current document intact.
- `REPLACE` and `FIND` that match nothing still report a result
  (`Replaced 0 occurrence(s).` / `Found 0 match(es).`) rather than
  failing silently.
- `UNDO` with nothing to restore prints `Nothing to undo.` instead of
  crashing.
- Unknown commands print `Unknown command. Type HELP for usage.`
