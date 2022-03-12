-- Ex. 1
-- a)
isSorted2 :: (Ord a) => [a] -> Bool
isSorted2 [x] = True
isSorted2 (h:t) | h<=head t = isSorted2 t
                | otherwise = False

-- b)
inits2 :: [a] -> [[a]]
inits2 [] = [[]]
inits2 l = (inits2 (init l)) ++ [l]

{-- Ex. 2
maximumMB :: (Ord a) => [Maybe a] -> Maybe a
maximumMB (h:t) | h<=(head t) = maximumMB t
                   | otherwise = 0

aux :: (Ord a) => [Maybe a] -> [Maybe a]
aux [] = [Nothing]
aux (h:t) | h==Nothing = aux t
          | otherwise = h:aux t
-}

-- Ex. 3
data LTree a = Tip a | Fork (LTree a) (LTree a)

-- a)
listaLT :: LTree a -> [a]
listaLT (Tip a) = [a]
listaLT (Fork l r) = (listaLT l) ++ (listaLT r)

-- b)
--instance Show = undefined