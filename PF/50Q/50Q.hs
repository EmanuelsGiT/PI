import Data.Char

--Ex.1
enumFromTo2 :: Int -> Int -> [Int]
enumFromTo2 x y | x>y = []
				| otherwise = x:enumFromTo2 (x+1) y 

--Ex.2
enumFromThenTo2:: Int -> Int -> Int -> [Int]
enumFromThenTo2 x y z | (x<y && x<=z) || (x>y && x>=z) = x : enumFromThenTo2 y (y+(y-x)) z
                      | otherwise = []

--Ex.3 
juntar :: [a] -> [a] -> [a]
juntar [] y = y
juntar (x:xs) y = x:juntar xs y  

--Ex.4
seleciona :: [a] -> Int -> a
seleciona (h:t) x | x==0 = h
				  | otherwise = seleciona t (x-1)

--Ex.5
reverse2 :: [a] -> [a]
reverse2 [] = []
reverse2 x = last x : reverse2 (init x) 
 
--Ex.6
take2 :: Int -> [a] -> [a]
take2 _ [] = []
take2 x (h:t) | x /= 1 = h:take2 (x-1) t 
			  | otherwise = [h]

--Ex.7
drop2 :: Int -> [a] -> [a]
drop2 _ [] = []
drop2 0 l = l
drop2 x (h:t) | x<=0 = (h:t)
              | otherwise = drop2 (x-1) t

--Ex.8
zip2 :: [a] -> [b] -> [(a,b)]
zip2 _ [] = []
zip2 [] _ = []
zip2 (x:xs) (y:ys)  = [(x,y)] ++ zip2 xs ys

--Ex.9
elem2 ::  Eq a => a -> [a] -> Bool
elem2 _ [] = False
elem2 x  (h:t) | x == h = True
			   | otherwise = elem2 x t 

--Ex.10
replicate2 :: Int -> a -> [a]
replicate2 0 _ = []
replicate2 x a =  a : replicate2 (x-1) a

--Ex.11
intersperce2 :: a -> [a] -> [a]
intersperce2 _ [] = []
intersperce2 x [h] = [h] 
intersperce2 x (h:t) = h : [x] ++ (intersperce2 x t)

--Ex.12
group2 :: Eq a => [a] -> [[a]]
group2 [] = []
group2 (x:xs) = (x:aux xs):aux2 xs
	where 
		aux [] = []
		aux (y:ys) | y==x = y:aux ys
				   | otherwise = []
		aux2 [] = []
		aux2 (z:zs) | z==x = aux2 zs
					| otherwise = group2 (z:zs)  


group' :: Eq a => [a] -> [[a]]
group' [] = []
group' (h:t) = (h:takeWhile (== h) t) : group' (dropWhile (== h) t)

--Ex.13
concat2 :: [[a]] -> [a]
concat2 [] = []
concat2 (h:t) = h ++ concat2 t

--Ex.14
inits2 :: [a] -> [[a]] 
inits2 [] = []
inits2 l = inits2 (init l) ++ [l]

--Ex.15
tails2 :: [a] -> [[a]] 
tails2 [] = []
tails2 l = [l] ++ tails2 (tail l)

---Ex.16
isPrefixOf2 :: Eq a => [a] -> [a] -> Bool
isPrefixOf2 [] _ = True
isPrefixOf2 _ [] = False
isPrefixOf2 (x:xs) (y:ys) = x == y && isPrefixOf2 xs ys

--Ex.17
isSuffixOf2 :: Eq a => [a] -> [a] -> Bool 
isSuffixOf2 [] _ = True
isSuffixOf2 _ [] = False
isSuffixOf2 x y = last x == last y && isSuffixOf2 (init x) (init y)

--Ex.18
isSubsequenceOf2 :: Eq a => [a] -> [a] -> Bool
isSubsequenceOf2 [] _ = True
isSubsequenceOf2 _ [] = False
isSubsequenceOf2 x y | elem (head x) y && isSubsequenceOf2 (tail x) (tail y) = True
					 | otherwise = False

--Ex.19
elemIndices2 :: Eq a => a -> [a] -> [Int]
elemIndices2 _ [] = []
elemIndices2 x l = [n | n <- [ 0..(length l - 1)], x == (l !! n)]

--Ex.20 
nub2 :: Eq a => [a] -> [a]
nub2 [] = []
nub2 (h:t) | elem h t = nub2 t
		   | otherwise = h:nub2 t 

--Ex.21
delete2 :: Eq a => a -> [a] -> [a]
delete2 _ [] = []
delete2 x (h:t) | x == h = t
			    | otherwise = h : delete2 x t

--Ex.22
delete3 :: Eq a => [a] -> [a] -> [a]
delete3 [] _ = []
delete3 x [] = x
delete3 (x:xs) (y:ys) | y == x = delete3 xs ys
					  | otherwise = (x:delete3 xs (y:ys))

--Ex.23
union2 :: Eq a => [a] -> [a] -> [a]
union2 [] [] = []
union2 [] x = x
union2 x [] = x
union2 x (y:ys) | elem y x =  union2 x ys
			 	| otherwise = union2 (x ++ [y]) ys

--Ex.24
intersect2 :: Eq a => [a] -> [a] -> [a]
intersect2 [] [] = []
intersect2 x [] = []
intersect2 [] x = []
intersect2 x y | elem (head y) x == True && elem (head x) y == True = (head x : intersect2 (tail x)  y)  
               | otherwise = intersect2 (tail x) (tail y)

--Ex.25
insert2 :: Ord a => a -> [a] -> [a]
insert2 x [] = [x]
insert2 x (h:t) | x == h = (h:x:t)
 				| x < h = (x:h:t)
 				| otherwise = h:(insert2 x t)

--Ex.26
unwords2 :: [String] -> String
unwords2 [] = ""
unwords2 [x] = x
unwords2 (h:t) = h ++ " " ++ unwords2 t

--Ex.27
unlines2 :: [String] -> String
unlines2 [] = ""
unlines2 [x] = x
unlines2 (h:t) = h ++ "\n" ++ unlines2 t

--Ex.28 
pMaior ::  Ord a => [a] -> Int
pMaior [] = error "empty list"
pMaior [x] = 0
pMaior (h:t) | h > (seleciona t p) = 0
			 | otherwise = p +1 
			 where p = pMaior t

--Ex.29
temRepetidos :: Eq a => [a] -> Bool
temRepetidos [] = False
temRepetidos (h:t) | elem h t == True = True
				   | otherwise = temRepetidos t 

--Ex.30
algarismos :: [Char] -> [Char]
algarismos [] = []
algarismos (h:t) | elem (ord h) [48..57] == True = (h:algarismos t)
				 | otherwise = algarismos t

--Ex.31
posImpares :: [a] -> [a]
posImpares [] = []
posImpares (h:t) = [head t] ++ posImpares (tail t)

--Ex.32
posPares :: [a] -> [a]
posPares [] = []
posPares (h:t) = [h] ++ posPares (tail t)

--Ex.33
isSorted2 :: Ord a => [a] -> Bool
isSorted2 [] = True
isSorted2 (h:t) | h <= (head t) && isSorted2 t = True
			    | otherwise = False

--Ex.34
iSort :: Ord a => [a] -> [a]
iSort [] = []
iSort [x] = [x]
iSort (h:t) | h <= (head t) = h: iSort t
			| otherwise = insert h t
			where
				insert :: Ord a => a -> [a] -> [a]
				insert x [] = [x]
				insert x y | x>=(head y) = (head y):insert x (tail y)
						   | otherwise = x:iSort y

--Ex.35
menor :: String -> String -> Bool
menor "" "" = False
menor "" _ = True
menor (x:xs) (y:ys) | ord x < ord y = True
					| ord x == ord y = menor xs ys
					| otherwise = False  

--Ex.36
elemMSet :: Eq a => a -> [(a,Int)] -> Bool
elemMSet _ [] = False
elemMSet x l | elem x (fst(unzip l)) == True = True
			 | otherwise = False

--Ex.37
lengthMSet :: [(a,Int)] -> Int
lengthMSet [] = 0
lengthMSet l = sum(snd(unzip l))

--Ex.38
convertMSet :: [(a,Int)] -> [a]
convertMSet [] = []
convertMSet ((a,b):t) = replicate b a ++ convertMSet t

--Ex.39
insereMSet :: Eq a => a -> [(a,Int)] -> [(a,Int)]
insereMSet x [] = [(x,1)]
insereMSet x ((a,b):t) | x == a = [(a,b+1)] ++ t
					   | otherwise = [(a,b)] ++ insereMSet x t
					   
--Ex.40
removeMSet :: Eq a => a -> [(a,Int)] -> [(a,Int)]
removeMSet x [] = []
removeMSet x ((a,b):t) | x == a && b-1 == 0 = t
					   | x == a && b-1 /= 0 = [(a,b-1)] ++ t
					   | otherwise = [(a,b)] ++ removeMSet x t
					   
--Ex.41
constroiMSet :: Ord a => [a] -> [(a,Int)]
constroiMSet [] = []
constroiMSet (h:t) = insereMSet h (constroiMSet t) 

--Ex.42
partitionEithers ::  [Either a b] -> ([a],[b])
partitionEithers l = (partitionLefts l, partitionRights l)
    where partitionLefts [] = []
          partitionLefts ((Left x):ls) = x:partitionLefts ls
          partitionLefts ((Right _):ls) = partitionLefts ls
          partitionRights [] = []
          partitionRights ((Left _):ls) = partitionRights ls
          partitionRights ((Right x):ls) = x:partitionRights ls

partitionEithers' :: [Either a b] -> ([a],[b])
partitionEithers' [] = ([],[])
partitionEithers' ((Left a):t) = (a:as,bs)
    where (as,bs) = partitionEithers' t
partitionEithers' ((Right b):t) = (as,b:bs)
    where (as,bs) = partitionEithers' t  

--Ex.43
catMaybes :: [Maybe a] -> [a]
catMaybes [] = []
catMaybes (m:ms) = case m of Nothing -> catMaybes ms
                             Just x -> x:catMaybes ms

catMaybes2 :: [Maybe a] -> [a]
catMaybes2 [] = []
catMaybes2 ((Just a):ms) = a:catMaybes2 ms
catMaybes2 (Nothing:ms) = catMaybes2 ms

--Ex.44
data Movimento = Norte | Sul | Este | Oeste deriving Show

posicao :: (Int,Int) -> [Movimento] -> (Int,Int)
posicao p [] = p
posicao (x, y) (m:ms) = posicao (case m of Norte -> (x, y + 1)
                                           Sul -> (x, y - 1)
                                           Este -> (x + 1, y)
                                           Oeste -> (x - 1, y)) ms

-- Ex.45
caminho :: (Int, Int) -> (Int, Int) -> [Movimento]
caminho (x, y) (xs, ys) | x < xs   = Este : caminho (x + 1, y) (xs, ys)
                          | x > xs   = Oeste : caminho (x - 1, y) (xs, ys)
                          | y < ys   = Norte : caminho (x, y + 1) (xs, ys)
                          | y > ys   = Sul : caminho (x, y - 1) (xs, ys)
                          | otherwise = []

--Ex.46
vertical :: [Movimento] -> Bool
vertical [] = True
vertical (l:ls) = case l of Este -> False
                            Oeste -> False
                            _ -> vertical ls

--Ex.47
data Posicao = Pos Int Int deriving Show

maisCentral ::  [Posicao] -> Posicao
maisCentral = foldl1 (\(Pos xacc yacc) (Pos x y) -> if (xacc^2 + yacc^2) > (x^2 + y^2) then Pos x y else Pos xacc yacc)

maisCentral2 :: [Posicao] -> Posicao
maisCentral2 [Pos x y] = Pos x y
maisCentral2 ((Pos x y):(Pos a b):ps) = if (x^2 + y^2) < (a^2 + b^2) then maisCentral (Pos x y : ps) else maisCentral (Pos a b : ps)

--Ex.48
vizinhos ::  Posicao -> [Posicao] -> [Posicao]
vizinhos (Pos x y) = filter (\(Pos a b) -> abs (a - x) + abs (b - y) == 1)

vizinhos2 :: Posicao -> [Posicao] -> [Posicao]
vizinhos2 _ [] = []
vizinhos2 (Pos x y) ((Pos xv yv):ps) = if abs (x - xv) == 1 && y == yv || abs (y - yv) == 1 && x == xv 
                                       then Pos xv yv : vizinhos2 (Pos x y) ps 
                                       else vizinhos2 (Pos x y) ps

--Ex.49
mesmaOrdenada :: [Posicao] -> Bool
mesmaOrdenada [] = True
mesmaOrdenada [Pos _ _] = True
mesmaOrdenada ((Pos _ y):(Pos x2 y2):ps) = y == y2 && mesmaOrdenada (Pos x2 y2 : ps)

mesmaOrdenada2 :: [Posicao] -> Bool
mesmaOrdenada2 [] = True
mesmaOrdenada2 (Pos _ y:t) = all ((==) y . (\(Pos _ yy) -> yy)) t 

--Ex.50
data Semaforo = Verde | Amarelo | Vermelho deriving Show

interseccaoOK :: [Semaforo] -> Bool
interseccaoOK x = length [y | y <- x, case y of Vermelho -> False; _ -> True] < 2