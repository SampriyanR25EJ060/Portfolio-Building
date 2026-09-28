Simple Line Editor (Minimal Edition)

A lightweight, terminal-based line text editor written in C. It allows users to create, view, edit, search, and manage plain text documents line-by-line directly from an interactive command prompt.

Features
Line-based Editing: Insert, delete, or overwrite specific lines by line number.
File I/O: Load external text files into memory and save modifications back to disk.
Search & Replace: Quick phrase search (FIND) and bulk string replacement (REPLACE).
Single-Level Undo: Revert the last destructive action (INS, DEL, EDIT, LOAD, REPLACE, CLEAR, UPPER).
Text Utilities: Convert entire document cases (UPPER/LOWER) and calculate document metrics (STATS).
Safe Boundary Handling: Validates line numbers and buffer bounds to prevent crashes.

Technical Specifications
Max Capacity: 500 lines
Max Line Length: 256 characters
Indexing: 1-based (Line 1 to N)
Command Names: Case-insensitive (e.g., show, SHOW, Show)
Text Matching: Case-sensitive

Command Reference
SHOW: Displays all lines with 1-based line numbers.
INS <line#> : Inserts text at the given line number, pushing lower lines down.
DEL <line#>: Deletes the specified line and shifts lower lines up.
EDIT <line#> : Overwrites the full content of an existing line.
SAVE : Writes the current document state to disk.
LOAD : Replaces current buffer contents with a file from disk.
FIND : Searches and prints all lines containing the phrase.
REPLACE  : Replaces occurrences of target across all lines.
STATS: Displays total count of lines, words, and characters.
UNDO: Restores the document state prior to the last edit operation.
CLEAR: Empties the entire document memory.
UPPER: Converts all document text to uppercase.
LOWER: Converts all document text to lowercase.
HELP: Prints a summary list of available commands.
EXIT: Exits the editor shell.

Usage Example
=========================================
Simple Line Editor (Minimal Edition)
Type HELP for available commands.
editor> INS 1 Hello World
Inserted line 1.
editor> INS 2 C Programming is fast.
Inserted line 2.
editor> SHOW
--- DOCUMENT START ---
1 | Hello World
2 | C Programming is fast.
--- DOCUMENT END ---
editor> STATS
Lines: 2 | Words: 6 | Chars: 33
editor> SAVE test.txt
Saved to test.txt.
editor> EXIT