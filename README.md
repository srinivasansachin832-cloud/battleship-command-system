# Battleship Command System

## Overview

This project is a Battleship-style grid simulation written in C. The program uses a 10x10 board, randomly places three hidden ships, accepts user-entered row and column coordinates, detects hits and misses, tracks sunk ships, and displays gameplay statistics.

## Features

- 10x10 grid
- 3 randomly placed ships
- Each ship covers 2 connected spots
- Horizontal and vertical ship placement
- Single-player gameplay
- User enters row and column coordinates
- Hit and miss detection
- Ship sinking detection
- Board updates after every turn
- Invalid input checking
- Duplicate shot prevention
- Total shots, hits, misses, accuracy, and longest hit streak
- Play-again loop

## Grid Legend

0 = Unknown  
1 = Miss  
2 = Hit  

## How to Compile

gcc -std=c99 -Wall -Wextra -o battleship main.c

## How to Run

./battleship

## Authors

Group 22

- Amarjot Singh
- Brendan Heos
- Sachin Srinivasan
