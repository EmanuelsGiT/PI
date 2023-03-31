-- Ex. 1
pos :: [a] -> Int -> a
pos [] _ = error "nao da assim"
pos (h:t) x | x==0 = h
            | otherwise = pos t (x-1)

-- Ex. 2
data Movimento = Norte | Sul | Este | Oeste deriving Show

posicao :: (Int,Int) -> [Movimento] -> (Int,Int)
posicao (x,y) [] = (x,y)
posicao (x,y) (m:ms) = posicao (case m of Norte -> (x,y+1)
                                          Sul -> (x,y-1)
                                          Este -> (x+1,y)
                                          Oeste -> (x-1,y)) ms

-- Ex. 3
any2 :: (a->Bool) -> [a] -> Bool
any2 f [] = False
any2 f (h:t) | f h = True
             | otherwise = any2 f t

-- Ex. 4
type Mat a = [[a]]

tripSum :: Num a => Mat a -> Bool
tripSum = undefined

-- Ex. 5
--movimenta :: IO (Int,Int) 

-- Ex. 6
data Imagem = Quadrado Int
            | Mover (Int,Int) Imagem
            | Juntar [Imagem]

ex :: Imagem
ex = Mover (5,5) (Juntar [Mover (0,1) (Quadrado 5),
                         Quadrado 4,
                         Mover (4,3) (Quadrado 2)])

-- a)
vazia :: Imagem -> Bool
vazia (Quadrado x) = False
vazia (Mover (_,_) i) = (vazia i)
vazia (Juntar (h:t)) | (vazia h) = (vazia (head t))  
                     | otherwise = False

-- b)
maior :: Imagem -> Maybe Int
maior x = if (vazia x)==True then error "Não existem quadrados"
                             else | x = Quadrado 

-- c)