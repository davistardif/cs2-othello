sample text
davis is a daddy

Team Members: Eric, Davis


During the first week:
Eric contributed by writing the weightMove method and finding weights for each of the corners. Eric also contributed by writing part of minimax. Eric experimented with different weights to optimize winning.

Davis wrote initialization of the board, doMove function, finished the minimax function and also implemented alpha/beta pruning. Davis also literally debugged everything and is a fantastic human. He also write the test_script which allows us to easily test our AI in many games all at once, allowing us to better see results. 

First change we made to make our bot tournament ready was to look up research studies on Othello and find what was the best static weights table for the board. We found a Static Weights Heuristic Function by the Univesity of Washington which helped us improve what weights belonged in which places on the board. From there, we optimized our weightMove function to best combine this weight, as well as considering the mobility of our next moves, and the simple heuristic that just considers number of white/black pieces on the board. We also included a weight for mobility to emphasize early game moblity. Alpha/Beta pruning was the largest change that we made to make our AI tournament ready. It increased our efficiency allowing us to devote more time to calculating more effective moves.  