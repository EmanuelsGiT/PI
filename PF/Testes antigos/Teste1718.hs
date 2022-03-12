-- Ex. 1
insert2 :: Ord a => a -> [a] -> [a]
insert2 x [] = [x]
insert2 x l@(h:t) | x<=h = x:l
                  | otherwise = h : (insert2 x t)

-- Ex. 2
catMaybes2 :: [Maybe a] -> [a]
catMaybes2 [] = []
catMaybes2 (h:t) = case h of (Just x) -> [x] ++ catMaybes2 t
                             (Nothing) -> catMaybes2 t

-- Ex. 3
data Exp a = Const a
           | Var String
           | Mais (Exp a) (Exp a)
           | Mult (Exp a) (Exp a)

-- Ex. 4
sortOn2 :: Ord b => (a->b) -> [a] -> [a]
sortOn2 f [] = []
sortOn2 f (h:t) = undefined

-- Ex. 5
-- a)
amplitude :: [Int] -> Int
amplitude [] = 0
amplitude l = b - a
            where 
                a = abs(minimum l)
                b = abs(maximum l)

{-- b)
parte :: [Int] -> ([Int],[Int])
parte [] = ([],[])
parte l@(h:t) = ([take 2 x], [drop 2 x])
    where x = (sort l)

sort :: Ord Int => [Int] -> [Int]
sort [] = []
sort [x] = [x]
sort (h:t) | h <= (head t) = h : sort t
           | otherwise = (sort t) ++ [h]
-}

-- Ex. 6
data Imagem = Quadrado Int
            | Mover (Int,Int) Imagem
            | Juntar [Imagem]

ex :: Imagem
ex = Mover (5,5) (Juntar [Mover (0,1) (Quadrado 5),
                          Quadrado 4,
                          Mover (4,3) (Quadrado 2)])

-- a)
conta :: Imagem -> Int
conta (Quadrado x) = 1
conta (Mover _ i) = conta i
conta (Juntar l) = sum (map conta l)

-- b)
apaga :: Imagem -> IO Imagem
apaga (Quadrado _ ) = return (Juntar [])
apaga (Mover c i) = do
    iNova <- apaga i
    return (Mover c iNova)
apaga (Juntar l) = do
    let tamanho = length l
    indice <- randomRIO (0, tamanho-1)
    apagaAux l indice

apagaAux :: [Imagem] -> Int -> [Imagem]
apagaAux (x:xs) 0 = xs
apagaAux (x:xs) n = x : apagaAux xs (n-1)