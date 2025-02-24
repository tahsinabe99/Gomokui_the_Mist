# Gomoku in the mist

## Introduction
This project is a C-based command-line game controller for Gomoku in the Mist, a variant of the classic Gomoku board game. 
The controller manages game logic, enforces rules, and provides a text-based interface for two players to compete.
Unlike traditional Gomoku, this version introduces a "Mist" mechanic, limiting players' visibility to a 7×7 window on the board that shifts dynamically after each move.

## Features
Command-line game controller: Interacts with players through commands.
Dynamic Mist system: Limits visibility while allowing unrestricted moves.
Full rule enforcement: Validates moves, enforces turns, and detects wins.
Error handling: Rejects invalid commands, incorrect inputs, and occupied positions.
Game history tracking: Stores and displays all previous moves.

## Commands
who → Displays the current player (B for Black, W for White).
view → Shows the visible portion of the board.
place <C><R> → Places a stone at the specified coordinate (e.g., place A1).
history → Displays all moves made so far.
resign → Allows a player to resign, giving victory to the opponent.
term → Forces the game to terminate immediately.

## Game Mechanics
Played on a 19×19 board.
Players alternate turns, placing stones (Black goes first).
The Mist obscures most of the board except for a 7×7 visible area.
The visibility window moves based on the last placed stone.
A player wins by forming a row of five or more stones (horizontal, vertical, or diagonal).
If the board is full with no winner, the game ends in a draw.
