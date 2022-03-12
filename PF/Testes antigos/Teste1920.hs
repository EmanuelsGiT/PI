-- ex4 teste19/20

data RTree a = R a [RTree a ] deriving (Show, Eq)

paths :: RTree a -> [[a]]
paths (R n []) = [[n]]
paths (R n l) = map (\x -> n : x) filhos 
    where filhos = concat (map paths l)


unpaths :: Eq a => [[a]] -> RTree a
unpaths [[n]] = R n []
unpaths l = R node (map unpaths restosAgrupados)
    where
        node = head (head l)
        restos = map tail l
        nodosFilhos = tiraRepetidos (map head restos)
        restosAgrupados = ragrAux restos nodosFilhos

ragrAUx :: Eq a => [[a]] -> [a] -> [[[a]]] 
ragrAUx [] = []
ragrAUx restos (x:xs) = (filter (\l-> (head l) == x) restos) : ragrAux restos xs

tiraRepetidos :: Eq a => [a] -> [a]
tiraRepetidos [] = []
tiraRepetidos (x:xs) = if elem x xs then tiraRepetidos xs else x: tiraRepetidos xs
