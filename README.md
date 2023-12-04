# HexGrid

Strategy board game where two players compete on a hexagonal grid. The players alternate placing red/blue markers (red markers for Red player and blue markers
for Blue player) on unoccupied hexagonal spaces Once a marker is placed, it remains until the game terminates. The goal for each player is to form a connected path of their
own markers linking the opposing sides of the board marked by their colours. The first player to complete his or her connection wins the game.

The game can be played Player vs Player and Player vs AI. 
When selecting an AI opponent, there are four AI variations to choose from:
    1. Random: Selects tiles at random
    2. Smart: Attempts to create a straightfoward path and block the player
    3. MonteCarlo: Algorithm which calculates the best strategic path to win
    
Currently, the Monte Carlo AI is only 50% implemented.
