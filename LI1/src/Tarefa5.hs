module Tarefa5 where 

import Datatype
import Tarefa2
import Hextuple as H

{- |
= Introdução

Na tarefa 5 criamos a lógica necessária para a movimentação dos fantasmas de forma a que um usuário possa ter um desafio durante o jogo. 

= Objetivos e Desenvolvimento

Como principal objetivo desta tarefa tinhamos de implementar um comportamento para os fantasmas nos seus variados modos.

Existem apenas dois tipos de comportamentos possíveis sendo eles o chaseMode (modo de perseguição) e o scatterMode (modo de fuga). 

Tanto no chaseMode como no scatterMode o fantasma redireciona-se sempre que se depara com uma parede de maneira a aproximar-se do 
pacman ou a movimentar-se para a sua direita.

= Discussão e Conlusão

Com a concretização desta Tarefa temos um robô capaz de seguir o pacman com poucas dificuldades proporcionando assim alguma dificuldade 
ao usuário ou ao robô pacman desenvolvido na Tarefa seguinte.

-}

-- | Recebe um estado de jogo e devolve os movimentos de todos os fantasmas. (Função Principal)
ghostPlay :: State -> [Play]
ghostPlay (State mz [] l) = []
ghostPlay state@(State mz ((Pacman (PacState ps tm o pac)):t) l) = ghostPlay (State mz t l)
ghostPlay state@(State mz ((Ghost (GhoState ps Alive)):t) l)     = chaseMode state iD : ghostPlay (State mz t l)
 where iD = H.get1 ps
ghostPlay state@(State mz ((Ghost (GhoState ps Dead)):t) l)      = scatterMode state iD : ghostPlay (State mz t l)
 where iD = H.get1 ps

-- | Recebe um fantasma e o estado de jogo e devolve a melhor orientação para perseguir o pacman (esta apenas muda de direção quando o fantasma embate numa parede).
idealChaseOri :: Player -> State -> Orientation
idealChaseOri (ghost@(Ghost (GhoState ps gm))) (State mz allpl l) 
  | H.get4 ps == L && gotunel L      = L
  | H.get4 ps == R && gotunel R      = R
  | H.get4 ps == R && not(oriWall R) = R            
  | H.get4 ps == L && not(oriWall L) = L          
  | H.get4 ps == U && not(oriWall U) = U           
  | H.get4 ps == D && not(oriWall D) = D           
  | H.get4 ps == Null                = U
  | H.get4 ps == U && (oriWall R)    = L
  | H.get4 ps == U && (oriWall L)    = R
  | H.get4 ps == U                   = minOri (dist (mudaCoord (coordspl ghost) R) (coordspl pac)) R (dist (mudaCoord (coordspl ghost) L) (coordspl pac)) L
  | H.get4 ps == D && (oriWall R)    = L
  | H.get4 ps == D && (oriWall L)    = R
  | H.get4 ps == D                   = minOri (dist (mudaCoord (coordspl ghost) R) (coordspl pac)) R (dist (mudaCoord (coordspl ghost) L) (coordspl pac)) L
  | H.get4 ps == R && (oriWall U)    = D
  | H.get4 ps == R && (oriWall D)    = U
  | H.get4 ps == R                   = minOri (dist (mudaCoord (coordspl ghost) U) (coordspl pac)) U (dist (mudaCoord (coordspl ghost) D) (coordspl pac)) D
  | H.get4 ps == L && (oriWall U)    = D
  | H.get4 ps == L && (oriWall D)    = U
  | H.get4 ps == L                   = minOri (dist (mudaCoord (coordspl ghost) U) (coordspl pac)) U (dist (mudaCoord (coordspl ghost) D) (coordspl pac)) D
 where pac = singlePac allpl 
       oriWall ori = (Wall==(nextPiece mz (coordspl ghost) ori))
       gotunel ori = nonextPiece mz (coordspl ghost) ori


-- | Calcula a distância entre dois pontos
dist :: Coords -> Coords -> Double
dist (y1, x1) (y2, x2) = sqrt (fromIntegral((x1 - x2)^2 + (y1 - y2)^2))

-- | Compara a distância de duas orientações e devolve a orientação com menor distância. 
minOri :: Double -> Orientation -> Double -> Orientation -> Orientation
minOri n1 o1 n2 o2 | min n1 n2 == n1 = o1
                   | otherwise       = o2

-- | Recebe o estado de jogo e o identificador do fantasma e devolve a melhor jogada de perseguição quando o fantasma embate numa parede. 
chaseMode :: State -> Int -> Play
chaseMode state@(State mz allpl l) id = Move id (idealChaseOri (oldplayer id allpl) state)

-- | Muda de orientação num eixo de -90º.
rightOri :: Orientation -> Orientation
rightOri ori | ori == U = R
             | ori == R = D
             | ori == D = L
             | ori == L = U

-- | Muda de orientação num eixo de +90º.
leftOri :: Orientation -> Orientation
leftOri ori  | ori == U = L
             | ori == R = U
             | ori == D = R
             | ori == L = D

-- | Recebe um fantasma e o estado de jogo e devolve uma orientação (em que o fantasma sempre que se depare com uma parede, este se mova para a sua direita caso seja possível).
idealScatterOri :: Player -> State -> Orientation
idealScatterOri (ghost@(Ghost (GhoState ps gm))) (State mz allpl l) 
  | H.get4 ps == R && not(oriWall R) = R            
  | H.get4 ps == L && not(oriWall L) = L          
  | H.get4 ps == U && not(oriWall U) = U           
  | H.get4 ps == D && not(oriWall D) = D  
  | (oriWall (rightOri(H.get4 ps)))  = leftOri (H.get4 ps)
  | otherwise                        = rightOri (H.get4 ps)
 where oriWall ori = (Wall==(nextPiece mz (coordspl ghost) ori))   
idealScatterOri (pac@(Pacman (PacState ps t o pc))) (State mz allpl l) 
  | H.get4 ps == R && not(oriWall R) = R            
  | H.get4 ps == L && not(oriWall L) = L          
  | H.get4 ps == U && not(oriWall U) = U           
  | H.get4 ps == D && not(oriWall D) = D  
  | (oriWall (rightOri(H.get4 ps)))    = leftOri (H.get4 ps)
  | otherwise                        = rightOri (H.get4 ps)
 where oriWall ori = (Wall==(nextPiece mz (coordspl pac) ori))   

-- | Recebe um estado e o identificador do fantasma e deolve uma jogada (em que o fantasma sempre que se depare com uma parede, este se mova para a sua direita caso seja possível).
scatterMode :: State -> Int -> Play
scatterMode state@(State mz allpl l) id = Move id (idealScatterOri (oldplayer id allpl) state)