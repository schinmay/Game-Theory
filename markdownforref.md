---
title: "Game Theory"
date: 2017-10-07 17:50:00 +0530
author: Siddharth Nohria(160686), Jatin Jindal(160308), Siddharth Chinmay(160685)
tags:
 - semester project 2016-17(2nd semester) 
 - ACA project
categories: Game Theory
 - min-max algorithm 
 - alpha- beta pruning
 - heuristic function
 - zeromq
---
It includes zero sum games in which a person plays against computer or 2 persons play against each other using zeromq library. We made two games as part of this project- Tic-Tac-Toe and Connect4. 

The project consists of two games :-

* **Tic-Tac-Toe:** Tic-tac-toe is a 2-player game, in which both players take turns marking the spaces in a 3×3 grid alternately. The player who succeeds in placing three of their marks in a horizontal, vertical, or diagonal row wins the game. We first made it using brute force method, then we improved it's time efficiency using min-max algorithm. 
    

* **Connect4:** Connect4 is a two-player connection game in which the players first choose a color and then take turns dropping colored discs from the top into a seven-column, six-row vertically suspended grid. The pieces fall straight down, occupying the next available space within the column. The objective of the game is to be the first to form a horizontal, vertical, or diagonal line of four of one's own discs. It was first made using minmax algorithm and heuristic function. But that was not very efficient as we could check only upto depth 4. Then we optimized it using alpha-beta pruning.

#### Github: [Tic-Tac-Toe](https://github.com/siddharthnohria/ACA-Project/blob/master/ttt.c)
#### Github: [Connect4](https://github.com/jatinjindal/ACA-project/blob/master/project_connect4.c)

