module Tarefa4 where 

import Datatype
import Tarefa2
import Tarefa5
import Hextuple as H

{- |
= Introdução

Na Tarefa 4 introduziu-se a noção de tempo no jogo, permitindo assim a possibilidade de criar várias jogadas ao longo do tempo.

= Objetivos e Desenvolvimento

Como objetivos desta tarefa tinhamos que efetuar a passagem do tempo num estado do jogo.
Tentamos escrever o código o mais compacto possível e também a deixá-lo mais otimizado. 

Visto que o jogo tinha apenas duas velocidades (pacman e fantasma vivo com  velocidade 1 e fantasma morto com velocidade 0.5), 
decidimos dividir a função passTime em duas partes: quando o step é par e quando o step é ímpar. Com isto, quando o step é par 
todos os jogadores excutam uma jogada e quando um step é ímpar apenas os jogadores com velocidade igual a 1.

= Discussão e Conlusão

Durante a execução da tarefa 4 tivemos algumas dificuldades na compreensão da função principal (passTime). No entanto após a total
compreensão da função passTime, o seu código tornou-se relativamente fácil de escrever.

Em jeito de conclusão, a realização desta tarefa foi bastante simples, apesar dos seus pequenos contratempos inicialmente. 

-}

-- | Recebe um step e o estado de jogo e altera o estado em uma iteração. (Função Principal)
passTime :: Int -> State -> State
passTime step state@(State mz allpl l) | odd step  = playsOdd allpl state 
                                       | even step = playsEven allpl state

-- | Recebe a lista de jogadores e o estado de jogo e excuta as jogadas para todos os jogadores. 
playsEven :: [Player] -> State -> State
playsEven [] state@(State mz allpl l)                                    = state
playsEven ((Pacman (PacState ps tm o pac)):plt) state@(State mz allpl l) = playsEven plt (play (Move iD (oripl(oldplayer iD allpl))) (State mz allpl l))
 where iD = H.get1 ps
playsEven ((Ghost (GhoState ps Alive)):plt) state@(State mz allpl l)     = playsEven plt (play (chaseMode state iD) (State mz allpl l)) 
 where iD = H.get1 ps
playsEven ((Ghost (GhoState ps Dead)):plt) state@(State mz allpl l)      = playsEven plt (play (scatterMode state iD) (State mz allpl l)) 
 where iD = H.get1 ps

-- | Recebe a lista de jogadores e o estado de jogo e excuta as jogadas para todos os jogadores com velocidade igual a 1.
playsOdd :: [Player] -> State -> State
playsOdd [] state@(State mz allpl l)                                    = state
playsOdd ((Pacman (PacState ps tm o pac)):plt) state@(State mz allpl l) = playsOdd plt (play (Move iD (oripl(oldplayer iD allpl))) (State mz allpl l))
 where iD = H.get1 ps
playsOdd ((Ghost (GhoState ps Alive)):plt) state@(State mz allpl l)     = playsOdd plt (play (chaseMode state iD) (State mz allpl l)) 
 where iD = H.get1 ps
playsOdd (pl1:plt) state@(State mz allpl l)                             = playsOdd plt state

defaultDelayTime = 250 -- 250 ms