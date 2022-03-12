-- Ex. 1
type MSet a = [(a,Int)]

-- a)
cardMSet :: MSet a -> Int
cardMSet [] = 0
cardMSet (h:t) = (snd h) + cardMSet t

-- b)
moda :: MSet a -> [a]
moda [] = []
moda [(x,y)] = (replicate y x)
moda (h:t) | (snd h) <= (snd(head t)) = moda t
           | otherwise = moda (h:(tail t))

-- c)
convertMSet :: MSet a -> [a]
convertMSet [] = []
convertMSet (h:t) = (replicate (snd h) (fst h)) ++ convertMSet t

-- d)
addNcopies :: Eq a => MSet a -> a -> Int -> MSet a
addNcopies [] x y = [(x,y)]
addNcopies ((a,b):t) x y | x==a = aux ((a,b+y):t)
                         | otherwise = aux ([(a,b)] ++ addNcopies t x y)

aux :: MSet a -> MSet a
aux [] = []
aux [x] = [x]
aux (h:t) | (snd h) >= snd(head t) = (h : aux t)
          | otherwise = ([head t] ++ aux (h:tail t))

-- Ex. 2
data SReais = AA Double Double | FF Double Double
            | AF Double Double | FA Double Double
            | Uniao SReais SReais

-- a)
instance Show (Uniao a b) where
    show (Uniao a b) = "(" ++ show a ++ "U" ++ show b ++ ")" 
    show intervalo = par1 ++ num1 ++ "," ++ num2 ++ par2
        where 
            (par1,num1,num2,par2) case intervalo of AA a b -> "]" ++ a ++ "," ++ b ++ "[" 
                                                    FF a b -> "[" ++ a ++ "," ++ b ++ "]"
                                                    AF a b -> "]" ++ a ++ "," ++ b ++ "]"
                                                    FA a b -> "[" ++ a ++ "," ++ b ++ "["

{-- b)
pertence :: Double -> SReais -> Bool
pertence = undefine
-}

-- Ex. 3 
data RTree a = R a [RTree a]

-- a)
percorre :: [Int] -> RTree a -> Maybe [a]
