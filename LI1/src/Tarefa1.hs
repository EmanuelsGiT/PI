module Tarefa1 where

import System.Random
import Datatype

{- |

= Introdução

Nesta Tarefa 1 tinhamos como objetivo gerar labirintos aleatórios para o jogo do Pacman.

= Objetivos e Desenvolvimento

Para a criação destes labirintos tinhamos de obedecer a certas regras tais como: o labrinto ser rodeado 
por paredes exceto no túnel e este túnel deveria ser a faixa mais central do labirinto. Para além disto,
todos os corredores deveriam ter o mesmo comprimento e a casa dos fantasmas deveria estar localizada no meio do labrinito.

Para a construção dos labrintos, de forma a construir os labirintos corretamente, tivemos de construir 
duas casas de fantasmas pois de acordo com a altura do labririnto, caso esta fosse par ou ímpar teria de ser colocada de forma diferente.

= Discussão e Conlusão

Sendo esta a primeira tarefa e o primeiro contacto com a formação do jogo Pacman, este deixou-nos 
bastante empenhados e com uma visão diferente na estruturação de um jogo.
-}

-- | Gera o Labririnto. (Função Principal)
generateMaze :: Int -- ^ Variável da largura 
             -> Int -- ^ Variável do comprimento
             -> Int -- ^ Seed do labririnto
             -> Maze -- ^ Labririnto
generateMaze x y z = putHouse x y (limMaze x y z)

-- | Junta as funções relativas às paredes de forma a criar um labrinto correto.
limMaze :: Int -- ^ Variável da largura 
        -> Int -- ^ Variável do comprimento
        -> Int -- ^ Seed do labrinto
        -> Maze -- ^ Labririnto
limMaze x y z = (walls x) : (walls2 (y-2) (genMaze (x-2) (y-2) z)) ++ [(walls x)]

-- | Altera as listas de forma a criar as Paredes superior e infeior.
walls :: Int -- ^ Variável da largura
      -> Corridor -- ^ Lista de paredes
walls x = replicate x Wall   

-- | Altera as listas de forma a criar as paredes laterais e o túnel.
walls2 :: Int -- ^ Variável da altura
       -> Maze -- ^ Labirinto já criado
       -> Maze -- ^ Labirinto com as paredes laterais corretas e túnel
walls2 y [] = []
walls2 y (x:xs) | even y && length (x:xs) == (div y 2) = concat[[Empty],x,[Empty]] : walls2 y xs
                | even y && length (x:xs) == ((div y 2)+1) = concat[[Empty],x,[Empty]] : walls2 y xs
                | even y = concat[[Wall],x,[Wall]] : walls2 y xs 
                | odd y && length (x:xs) == ((div y 2)+1) = concat[[Empty],x,[Empty]] : walls2 y xs
                | otherwise = concat[[Wall],x,[Wall]] : walls2 y xs 


-- | Define o local da casa dos fantasmas no labririnto. 
putHouse :: Int -- ^ Variável da largura
         -> Int -- ^ Variável do  comprimento
         -> Maze -- ^ Labrinto já construído
         -> Maze -- ^ Labrinto modificado com a casa dos fantasmas
putHouse x1 y [] = [] 
putHouse x1 y (x:xs) | even y && length (x:xs) == (div y 2) -1 = escolheParte x1 4 x : putHouse x1 y xs 
                     | even y && length (x:xs) == (div y 2)+0  = escolheParte x1 3 x : putHouse x1 y xs 
                     | even y && length (x:xs) == (div y 2)+1  = escolheParte x1 2 x : putHouse x1 y xs 
                     | even y && length (x:xs) == (div y 2)+2  = escolheParte x1 1 x : putHouse x1 y xs 
                     | even y && length (x:xs) == (div y 2)+3  = escolheParte x1 0 x : putHouse x1 y xs 
                     | even y = [x] ++ putHouse x1 y xs 
                     | odd y && length (x:xs) == (div y 2)-1  = escolheParte x1 4 x : putHouse x1 y xs 
                     | odd y && length (x:xs) == (div y 2)+0  = escolheParte x1 3 x : putHouse x1 y xs 
                     | odd y && length (x:xs) == (div y 2)+1  = escolheParte x1 2 x : putHouse x1 y xs 
                     | odd y && length (x:xs) == (div y 2)+2  = escolheParte x1 1 x : putHouse x1 y xs 
                     | odd y && length (x:xs) == (div y 2)+3  = escolheParte x1 0 x : putHouse x1 y xs 
                     | otherwise = [x] ++ putHouse x1 y xs 
                     
-- | Introduz a Casa dos Fantasmas no Labirinto.           
escolheParte :: Int -- ^ Variável da largura 
             -> Int -- ^ Variável do  comprimento
             -> Corridor -- ^ Corredor que será substituído
             -> Corridor -- ^ Corredor substituído pelo corredor correspondente da casa dos fantasmas
escolheParte x1 n x | even x1 = take (div (x1-10) 2) x ++ ((ghostHouse x1) !! n) ++ drop (x1 - div (x1-10) 2) x
                    | otherwise = take (div (x1-11) 2) x ++ ((ghostHouse x1) !! n) ++ drop (x1 - div (x1-11) 2) x

-- | Peças da casa dos Fantasmas caso a largura do labririnto seja par ou ímpar.
ghostHouse :: Int -- ^ Variável da largura
           -> Maze -- ^ Labirinto com a casa dos fantasmas
ghostHouse x
    | even x = [[Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty],
                [Empty,Wall,Wall,Wall,Empty,Empty,Wall,Wall,Wall,Empty],
                [Empty,Wall,Empty,Empty,Empty,Empty,Empty,Empty,Wall,Empty],
                [Empty,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Empty],
                [Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty]]
    | otherwise = [[Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty],
                   [Empty,Wall,Wall,Wall,Empty,Empty,Empty,Wall,Wall,Wall,Empty],
                   [Empty,Wall,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Wall,Empty],
                   [Empty,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Empty],
                   [Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty]]


-- | Função que gera o Labirinto.
genMaze :: Int -- ^ Variável da Largura
        -> Int -- ^ Variável do comprimento
        -> Int -- ^ Variável da seed 
        -> Maze -- ^ Labirinto gerado
genMaze x y z =
                 let random_nrs = geraAl (x*y) z in
                 convMaze                
                 $ subLista x random_nrs 

-- | Dado uma seed, retorna um inteiro gerado aleatóriamente.
nrAleatorio :: Int -> Int
nrAleatorio seed = head $ geraAl 1 seed

-- | Com a seed fornecida, retorna uma lista de n inteiros gerados aleatóriamente.
geraAl :: Int  -> Int -> [Int]
geraAl n seed = let gen = mkStdGen seed 
                in take n $ randomRs (0,99) gen 

-- | Converte uma lista em uma lista de listas de tamanho n.
subLista :: Int -> [a] -> [[a]]
subLista _ [] = []
subLista n l = take n l: subLista n (drop n l)

-- | Junta todas as listas de forma a criar um Labririnto
convMaze :: [[Int]] -> Maze
convMaze [] = []
convMaze (x:xs) = convCorredor x : convMaze xs

-- | Converte uma lista de inteiros num corredor
convCorredor :: [Int] -> Corridor
convCorredor [] = []
convCorredor (x:xs) = convPiece x : convCorredor xs

-- | Converte um número inteiro numa peça
convPiece :: Int -> Piece
convPiece x 
    | x ==3 = Food Big
    | x >= 0 && x < 70 = Food Little
    | otherwise = Wall

-- | Converte um labirinto em IO()
printMaze' :: Maze -> IO ()
printMaze' x = putStrLn (mazeToString x)

-- | Transforma o Labirinto criado em uma string
mazeToString :: Maze -> String
mazeToString [] = ""
mazeToString (x:xs) = corridorToString x ++ mazeToString xs

-- | Converte um Corredor em uma string
corridorToString :: Corridor -> String 
corridorToString [] = "\n"
corridorToString (x:xs) = show x ++ corridorToString xs
