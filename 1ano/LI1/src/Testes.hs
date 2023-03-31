{-# OPTIONS_HADDOCK prune #-}
module Testes where

import Tarefa1 
import Tarefa2
import Tarefa3
import Datatype
import Hextuple as H

-- * Teste da Tarefa1
-- | Proporcoes
tT1proporcoes :: String
tT1proporcoes | (length(head(generateMaze 17 20 0)),length(generateMaze 17 20 0))==(17,20) 
                          = "Proporcoes corretas."
              | otherwise = "Proporcoes incorretas."

-- | Paredes superior e inferior
tT1paredeSupInf  :: String
tT1paredeSupInf  
 | head(generateMaze 17 20 1)==(replicate 17 Wall) && last(generateMaze 17 20 1)==(replicate 17 Wall) 
             = "Paredes superior e inferior bem colocadas."
 | otherwise = "Paredes superior e inferior mal colocadas."

coluna1 :: Maze -> [Piece]
coluna1 (x:xs) = map head (x:xs)

colunaUlt :: Maze -> [Piece]
colunaUlt x = map last x

-- | Paredes laterais e tunel 
tT1paredesComTunel :: String
tT1paredesComTunel |    coluna1(generateMaze 18 17 2)==concat[replicate 8 Wall,[Empty],replicate 8 Wall] 
                     && colunaUlt(generateMaze 18 17 2)==concat[replicate 8 Wall,[Empty],replicate 8 Wall] 
                     && coluna1(generateMaze 18 18 2)==concat[replicate 8 Wall,[Empty],[Empty],replicate 8 Wall] 
                     && colunaUlt(generateMaze 18 18 2)==concat[replicate 8 Wall,[Empty],[Empty],replicate 8 Wall] 
                               = "Paredes laterais e tuneis bem colocadas."                   
                   | otherwise = "Paredes laterais e tuneis mal colocadas."

-- | Casa dos fantasmas
tT1houseGhost :: String
tT1houseGhost |    (generateMaze 18 17 3)!!7 == [Wall,Food Little,Food Little,Food Little,Empty,Wall,Wall,Wall,Empty,Empty,Wall,Wall,Wall,Empty,Food Little,Food Little,Food Little,Wall]
                && (generateMaze 18 18 3)!!7 == [Wall,Food Little,Food Little,Food Little,Empty,Wall,Wall,Wall,Empty,Empty,Wall,Wall,Wall,Empty,Food Little,Food Little,Food Little,Wall]
                && (generateMaze 17 18 3)!!7 == [Wall,Food Little,Wall,Empty,Wall,Wall,Wall,Empty,Empty,Empty,Wall,Wall,Wall,Empty,Food Little,Food Little,Wall]
                && (generateMaze 17 17 3)!!7 == [Wall,Food Little,Wall,Empty,Wall,Wall,Wall,Empty,Empty,Empty,Wall,Wall,Wall,Empty,Food Little,Food Little,Wall]
                          = "Casa dos fantasmas bem colocadas no labirinto."
              | otherwise = "Casa dos fantasmas mal colocadas no labirinto."


plselect' :: Int -> State -> Player
plselect' n (State mz allpl l) = oldplayer n allpl


-- * Teste da Tarefa2
-- | Colizões com paredes
tT2colisaoParede :: String
tT2colisaoParede | plselect' 1 (play (Move 1 R) (State (generateMaze 20 20 9) [(Pacman (PacState (1,(3,4),1.0,R,0,0) 1.0 Open Normal))] 1)) == (Pacman (PacState (1,(3,4),1.0,R,0,0) 1.0 Open Normal)) 
                             = "Colisao do pacman com a parede correta."
                 | otherwise = "Colisao do pacman com a parede incorreta."

-- | Movimentos simples
tT2movimento :: String
tT2movimento |    coordspl(plselect' 1 (play (Move 1 R) (State (generateMaze 20 20 9) [(Pacman (PacState (1,(4,4),1.0,R,0,0) 1.0 Open Normal))] 1))) == (4,5)
               && coordspl(plselect' 1 (play (Move 1 L) (State (generateMaze 20 20 9) [(Pacman (PacState (1,(4,4),1.0,L,0,0) 1.0 Open Normal))] 1))) == (4,3)
               && coordspl(plselect' 1 (play (Move 1 U) (State (generateMaze 20 20 9) [(Pacman (PacState (1,(4,4),1.0,U,0,0) 1.0 Open Normal))] 1))) == (3,4)
               && coordspl(plselect' 1 (play (Move 1 D) (State (generateMaze 20 20 9) [(Pacman (PacState (1,(4,4),1.0,D,0,0) 1.0 Open Normal))] 1))) == (5,4)
                         = "Movimentos do pacman corretos."
             | otherwise = "Movimentos do pacman incorretos."

-- | Comer comida grande e pequena
tT2comerComidas :: String
tT2comerComidas |    (plselect' 1 (play (Move 1 R) (State (generateMaze 20 20 10) [(Pacman (PacState (1,(3,2),1.0,R,0,0) 1.0 Open Normal))] 1)))==(Pacman (PacState (1,(3,3),1.0,R,5,0) 1.0 Open Mega)) 
                  && (plselect' 1 (play (Move 1 U) (State (generateMaze 20 20 10) [(Pacman (PacState (1,(3,2),1.0,U,0,0) 1.0 Open Normal))] 1)))==(Pacman (PacState (1,(2,2),1.0,U,1,0) 1.0 Open Normal))
                            = "O pacman come a comida corretamente." 
                | otherwise = "O pacman nao come a comida corretamente." 

-- | Atravessar tunel
tT2atravessarTunel :: String
tT2atravessarTunel |    coordspl(plselect' 1 (play (Move 1 R) (State (generateMaze 20 20 9) [(Pacman (PacState (1,(10,19),1.0,R,0,0) 1.0 Open Normal))] 1))) == (10,0)
                     && coordspl(plselect' 1 (play (Move 1 L) (State (generateMaze 20 20 9) [(Pacman (PacState (1,(10,0),1.0,L,0,0) 1.0 Open Normal))] 1))) == (10,19)
                               = "Atravessa o tunel corretamente."
                   | otherwise = "Nao Atravessa o tunel corretamente."

-- |  Comer fantasma (estado Dead)
tT2comerGhost :: String 
tT2comerGhost |    (plselect' 1 (play (Move 1 R) (State (generateMaze 20 20 9) [(Pacman (PacState (1,(7,7),1.0,R,0,0) 1.0 Open Normal)), (Ghost (GhoState (2,(7,8),1.0,Null,0,3) Dead))] 1 )))==(Pacman (PacState (1,(7,8),1.0,R,10,0) 1.0 Open Normal))
                && (plselect' 2 (play (Move 1 R) (State (generateMaze 20 20 9) [(Pacman (PacState (1,(7,7),1.0,R,0,0) 1.0 Open Normal)), (Ghost (GhoState (2,(7,8),1.0,Null,0,3) Dead))] 1 )))==(Ghost (GhoState (2,(9,9),2.0,Null,0,3) Alive))
                && (plselect' 1 (play (Move 1 R) (State (generateMaze 21 20 9) [(Pacman (PacState (1,(7,7),1.0,R,0,0) 1.0 Open Normal)), (Ghost (GhoState (2,(7,8),1.0,Null,0,3) Dead))] 1 )))==(Pacman (PacState (1,(7,8),1.0,R,10,0) 1.0 Open Normal))
                && (plselect' 2 (play (Move 1 R) (State (generateMaze 21 20 9) [(Pacman (PacState (1,(7,7),1.0,R,0,0) 1.0 Open Normal)), (Ghost (GhoState (2,(7,8),1.0,Null,0,3) Dead))] 1 )))==(Ghost (GhoState (2,(9,10),2.0,Null,0,3) Alive))
                && (plselect' 1 (play (Move 1 R) (State (generateMaze 20 21 9) [(Pacman (PacState (1,(8,7),1.0,R,0,0) 1.0 Open Normal)), (Ghost (GhoState (2,(8,8),1.0,Null,0,3) Dead))] 1 )))==(Pacman (PacState (1,(8,8),1.0,R,10,0) 1.0 Open Normal))
                && (plselect' 2 (play (Move 1 R) (State (generateMaze 20 21 9) [(Pacman (PacState (1,(8,7),1.0,R,0,0) 1.0 Open Normal)), (Ghost (GhoState (2,(8,8),1.0,Null,0,3) Dead))] 1 )))==(Ghost (GhoState (2,(10,9),2.0,Null,0,3) Alive))
                && (plselect' 1 (play (Move 1 R) (State (generateMaze 21 21 9) [(Pacman (PacState (1,(8,7),1.0,R,0,0) 1.0 Open Normal)), (Ghost (GhoState (2,(8,8),1.0,Null,0,3) Dead))] 1 )))==(Pacman (PacState (1,(8,8),1.0,R,10,0) 1.0 Open Normal))
                && (plselect' 2 (play (Move 1 R) (State (generateMaze 21 21 9) [(Pacman (PacState (1,(8,7),1.0,R,0,0) 1.0 Open Normal)), (Ghost (GhoState (2,(8,8),1.0,Null,0,3) Dead))] 1 )))==(Ghost (GhoState (2,(10,10),2.0,Null,0,3) Alive))
                          = "O pacman come os fantasmas morto corretamente (pontuacao correta, coords do fantasma corretas)."
              | otherwise = "O pacman nao come morto o fantasma corretamente."

-- | Colisão com o fantasma no estado Alive
tT2colidirGhost :: String
tT2colidirGhost |     (plselect' 1 (play (Move 1 R) (State (generateMaze 20 20 9) [(Pacman (PacState (1,(7,7),1.0,R,0,1) 1.0 Open Normal)), (Ghost (GhoState (2,(7,8),1.0,Null,0,3) Alive))] 1 ))) == (Pacman (PacState (1,(7,8),1.0,R,0,0) 1.0 Open Normal))
                  &&  (plselect' 1 (play (Move 1 R) (State (generateMaze 20 20 9) [(Pacman (PacState (1,(7,7),1.0,R,0,0) 1.0 Open Normal)), (Ghost (GhoState (2,(7,8),1.0,Null,0,3) Alive))] 1 ))) == (Pacman (PacState (1,(7,8),1.0,R,0,0) 1.0 Open Dying))
                            = "A colisao contra o fantasma vivo esta correta."
                | otherwise = "A colisao contra o fantasma vivo esta correta."  


mz1=[[Wall,Wall,Wall,Wall],[Wall,Empty,Empty,Wall],[Wall,Empty,Empty,Wall],[Empty,Empty,Empty,Empty],[Wall,Empty,Empty,Wall],[Wall,Empty,Empty,Wall],[Wall,Wall,Wall,Wall]]
mz2=[[Wall,Wall,Wall],[Empty,Empty,Empty],[Empty,Wall,Empty],[Empty,Empty,Empty],[Wall,Wall,Wall]]
mz3=[[Wall,Wall,Wall],[Wall,Food Little,Wall],[Wall,Wall,Wall],[Empty,Food Big,Empty],[Wall,Wall,Wall],[Wall,Food Little,Wall],[Wall,Wall,Wall]]
-- * Teste da Tarefa3
-- | Varias compreções de labirintos 
tT3compMaze :: String
tT3compMaze |    compactMaze mz1 == [Instruct [(4,Wall)],Instruct [(1,Wall),(2,Empty),(1,Wall)],Repeat 1,Instruct [(4,Empty)],Repeat 1,Repeat 1,Repeat 0]
              && compactMaze mz2 ==[Instruct [(3,Wall)],Instruct [(3,Empty)],Instruct [(1,Empty),(1,Wall),(1,Empty)],Repeat 1,Repeat 0]
              && compactMaze mz3 == [Instruct [(3,Wall)],Instruct [(1,Wall),(1,Food Little),(1,Wall)],Repeat 0,Instruct [(1,Empty),(1,Food Big),(1,Empty)],Repeat 0,Repeat 1,Repeat 0]
                        ="Os labirintos estao comprimidos corretamente."
            | otherwise = "Os labirintos nao estao comprimidos corretamente."