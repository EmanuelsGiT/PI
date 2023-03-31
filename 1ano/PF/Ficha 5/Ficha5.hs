import Data.List

--Ex.1
--alinea a)
any2 :: (a -> Bool) -> [a] -> Bool
any2 f [] = False
any2 f (x:xs) = if (f x) then True else any2 f xs

--alinea b)
zipWith2 :: (a->b->c) -> [a] -> [b] -> [c]
zipWith2 f [] [] = []
zipWith2 f l [] = []
zipWith2 f [] l = []
zipWith2 f (x:xs) (y:ys) = f x y : zipWith2 f xs ys

fibs = 0 :1 : zipWith2 (+) fibs (tail fibs)

--alinea c)
takeWhile2 :: (a->Bool) -> [a] -> [a] 
takeWhile2 f [] = []
takeWhile2 f (x:xs) | f x = x:takeWhile2 f xs
                    | otherwise = []

--alinea d)
dropWhile2 :: (a->Bool) -> [a] -> [a]
dropWhile2 f [] = []
dropWhile2 f (x:xs) | f x = dropWhile2 f xs
                    | otherwise = (x:xs)

--alinea e)
span2 :: (a->Bool) -> [a] -> ([a],[a])
span2 f [] = ([],[])
span2 f (x:xs) | f x = (x:a, b) 
               | otherwise = ([], x:xs)
               where (a,b) = span2 f xs

deleteBy2 :: (a -> a -> Bool) -> a -> [a] -> [a]
deleteBy2 f x [] = []
deleteBy2 f x (h:t)
    | f x h = t
    | otherwise = h : deleteBy2 f x t

sortOn2 :: Ord b => (a->b) -> [a] -> [a]
sortOn2 f [] = []
sortOn2 f [x] = [x]
sortOn2 f (x:xs) = (sortOn2 f lowers) ++ [x] ++ (sortOn2 f uppers)
    where (lowers, uppers) = parte f x xs

parte :: Ord b => (a->b) -> a -> [a] -> ([a],[a])
parte f x [] = ([], [])
parte f x (h:t) | (f h) < (f x) = (h:lowers, uppers)  
                | otherwise = (lowers, h:uppers)
                where (lowers, uppers) = parte f x t


--Ex.2
type Polinomio = [Monomio]
type Monomio = (Float,Int)

ex2 :: Polinomio
ex2 = [(1,1),(11,2),((-1),3),(2,4)]

--a)
selgrau  :: Int -> Polinomio -> Polinomio
selgrau n p = filter (\x -> snd x == n) p

--b)
conta :: Int -> Polinomio -> Int
conta n p = length $ filter (\x -> snd x == n) p 

--c)
grau :: Polinomio -> Int
grau l = (maximum . snd . unzip) l

--d)
deriv :: Polinomio -> Polinomio
deriv l = filter (\x -> snd x > 0) (map (\(x,y)->(x*(fromIntegral y),y-1)) l)

--e)
calcula :: Float -> Polinomio -> Float
calcula a p = sum(map (\(x,y) -> x*(a^y)) p) 

--f)
simp :: Polinomio -> Polinomio
simp l = filter (\x -> fst x == 0) l

--g)
mult :: Monomio -> Polinomio -> Polinomio
mult (a,b) p = map (\(x,y) -> (x*a,y+b)) p

--h)
ordena :: Polinomio -> Polinomio
ordena p = sortOn snd p

--i)
normaliza :: Polinomio -> Polinomio
normaliza [] = []
normaliza p@(h:t) = aux (filter (\x -> snd h == snd x) p) : normaliza (filter (\x -> snd h /= snd x) p)

aux :: Polinomio -> Monomio
aux x = (sum(fst (unzip x)),(head(snd(unzip x))))

--j)
soma :: Polinomio -> Polinomio -> Polinomio
soma 