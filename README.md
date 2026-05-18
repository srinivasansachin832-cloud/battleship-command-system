# Battleship Command System

## Overview

The Battleship Command System is a single-player grid-based targeting simulation written in the C programming language. The project models a simplified Battleship game using a 10x10 board, randomly placed ships, user-entered firing coordinates, hit/miss detection, ship-sinking logic, and gameplay statistics.

Although the project is presented as a game, it demonstrates several important computer engineering concepts. These include two-dimensional array storage, state tracking, randomized initialization, input validation, loop-based control flow, modular function design, and runtime performance analysis.

The player attempts to locate and destroy three hidden enemy ships. Each ship occupies two connected grid positions. The program stores the visible game board, tracks hidden ship locations internally, validates user input, prevents repeated shots, updates the board after every turn, and determines when all ships have been destroyed.

---

## Computer Engineering Relevance

This project connects directly to computer engineering because it uses C to model an interactive state-based system. The board is represented in memory using two-dimensional arrays, similar to how engineers may represent sensor grids, memory maps, display buffers, or hardware state tables.

The program uses a hidden ship map to store internal system data and a visible player board to show only the information available to the user. This separation between internal state and external output reflects a common software design concept used in embedded systems, simulations, and control applications.

The project also includes input validation and duplicate-shot prevention, which improve program reliability. The statistics system collects runtime data such as total shots, hits, misses, accuracy, and longest hit streak. These metrics allow the user to evaluate system performance after each round.

---

## Features

- 10x10 grid-based board
- Three hidden ships
- Each ship covers two connected grid spaces
- Randomized ship placement
- Horizontal and vertical ship placement
- Ship overlap prevention
- Single-player terminal gameplay
- User coordinate input
- Hit and miss detection
- Ship-sinking detection
- Board updates after every turn
- Invalid coordinate checking
- Duplicate shot prevention
- Total shot tracking
- Hit and miss tracking
- Accuracy percentage calculation
- Longest hit streak tracking
- Play-again loop
- Cumulative session statistics

---

## Grid Legend

```text
0 = Unknown position
1 = Missed shot
2 = Successful hit
