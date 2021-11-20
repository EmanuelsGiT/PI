{-# OPTIONS_HADDOCK prune #-} 
module Tarefa3 where

import Datatype
import Tarefa2
import Tarefa1

{- |
= Introdução

Esta Tarefa 3 tínhamos como objetivo compactar o labririnto. 

= Objetivos e Desenvolvimento

Nesta tarefa 3 criamos funções que analisavam o labirinto feito e o colocavam na forma de pares em que o 
primeiro elemento seria no número de vezes que essa peça seria repetida num determinado corredor e o segundo
elemento a peça.  

Para completar esta compactação, caso houvesse corredores idênticos estes seriam mostrados como Repeat x, 
sendo este x o número da linha anterior com um corredor igual.

= Discussão e Conlusão

Com a finalização desta tarefa somos capaz de compactar qualquer labirinto eficazmente e desta forma fazer 
com que este ocupe menos espaço.

-}

compactMaze :: Maze -> Instructions
compactMaze m = mazeSmall (mazeNormal(m)) (mazeNormal(m))

-- | O primeiro labirinto é um valor fixo que serve apenas para comparar com o segundo labirindo para que depois da primeira volta, a função recursiva ainda tenha como se comparar ao labirindo inicial.
mazeSmall :: [[(Int, Piece)]] -- ^ Labirinto fixo
          -> [[(Int, Piece)]] -- ^ Labirinto alterável
          -> [Instruction]    -- ^ Labirinto comprimido 
mazeSmall x [] = []
mazeSmall x (h:t) | nSame h (take ((length x)-(length(h:t))+1)  x) ==1 = (Instruct h):mazeSmall x t 
                  | otherwise = (Repeat (fstCorridor h x)):mazeSmall x t 

-- | Calcula quantos corredores iguais ao corredor selecionado existem no labirinto.
nSame :: [(Int, Piece)] -- ^ Corredor comprimido
      -> [[(Int, Piece)]] -- ^ Conjunto de corredores comprimidos (labirinto)
      -> Int -- ^ Número de corredores iguais
nSame a [] = 0
nSame a (h:t) | a==h = 1+ nSame a t
              | otherwise = 0 + nSame a t 

-- | Calcula o indice do primeiro corredor igual ao corredor selecionada dentro do labirinto.
fstCorridor :: [(Int, Piece)] -- ^ Corredor comprimido
            -> [[(Int, Piece)]] -- ^ Conjunto de corredores comprimidos (labirinto)
            -> Int -- ^ Indice do primeiro
fstCorridor a (h:t) | a==h = 0
                    | otherwise = 1 + fstCorridor a t 
 
-- | Transforma um labirinto numa lista de corredores comprimidos.
mazeNormal :: Maze -> [[(Int, Piece)]] 
mazeNormal [] = []
mazeNormal (h:t) = (corridorSmall(corridorNormal h)):(mazeNormal t)

-- | Junta os pares (1,peça) com o segundo membro igual somando o primeiro membro.
corridorSmall :: [(Int ,Piece)] -> [(Int ,Piece)]
corridorSmall [] = []
corridorSmall [(a,b)] = [(a,b)]
corridorSmall ((a,b):(c,d):t) | b==d = corridorSmall((a+c,d):t)
                              | otherwise = (a,b):corridorSmall((c,d):t)
  

-- | Transforma cada peça de um corredor (lista de peças) em pares (1,peça).
corridorNormal :: [Piece] -> [(Int, Piece)]
corridorNormal [] = []
corridorNormal (h:t) = ((1,h):corridorNormal t)
