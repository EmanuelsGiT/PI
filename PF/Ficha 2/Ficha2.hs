import Data.Char

--Ex.2
--alinea a)
dobros :: [Float] -> [Float]
dobros [] = []
dobros (h:t) = [h*2] ++ dobros t

--alinea b)
numOcorre :: Char -> String -> Int
numOcorre _ [] = 0
numOcorre x (h:t) | toUpper x == toUpper h = 1 + numOcorre x (t) 
				  | otherwise = numOcorre x (t)

--alinea c)
positivos :: [Int] -> Bool
positivos [] = True
positivos [h] = if h>0 then True else False
positivos (h:t) | h>0 = positivos t
				| otherwise = False

--alinea d)
soPos :: [Int] -> [Int]
soPos [] = []
soPos (h:t) | h > 0 = h : soPos t
			| otherwise = soPos (t)

--alinea e)
somaNeg :: [Int] -> Int
somaNeg [] = 0
somaNeg (h:t) | h < 0 = h + somaNeg t
			  | otherwise = somaNeg t

--alinea f)
tresUlt :: [a] -> [a]
tresUlt (h:t) | length(h:t) <= 3 = (h:t)
			  | otherwise = tresUlt(drop(length(h:t)-3) (h:t))

--alinea g)
segundos :: [(a,b)] -> [b]
segundos ((x,y):t) = y:snd(unzip t)

--alinea h)
nosPrimeiros :: (Eq a) => a -> [(a,b)] -> Bool
nosPrimeiros _ [] = False
nosPrimeiros x ((a,b):t) = elem x (a:fst(unzip t)) 

--alinea i)
sumTriplos :: (Num a, Num b, Num c) => [(a,b,c)] -> (a,b,c)
sumTriplos [] = (0,0,0)
sumTriplos [(a,b,c)] = (a,b,c)
sumTriplos ((a,b,c):(x,y,z):t) = sumTriplos((a+x,b+y,c+z):t)

--Ex.3
--aliena a)
soDigitos :: [Char] -> [Char]
soDigitos [] = []
soDigitos (h:t) | elem(ord h) [48..57] == True = (h : soDigitos t)
				| otherwise = (soDigitos t)

--alinea b)
minusculas :: [Char] -> Int
minusculas [] = 0
minusculas (h:t) | elem(ord h) [97..122] == True = 1 + minusculas t
				 | otherwise = minusculas t

--alinea c)
nums :: String -> [Int]
nums [] = []
nums (h:t) | ord h > 48 && ord h < 57 = ord(h)-48 : nums t
		   | otherwise = nums t 


--Ex.4

type Polinomio = [Monomio]
type Monomio = (Float,Int)

--alinea a)
conta :: Int -> Polinomio -> Int
conta _ [] = 0
conta n ((x,y):t) | n == y = 1 + conta n t
				  | otherwise = conta n t  

--alinea b)
grau :: Polinomio -> Int
grau [] = 0
grau ((x,y):t) = maximum (y:snd(unzip t))

--alinea c)
selgrau :: Int -> Polinomio -> Polinomio
selgrau _ [] = []
selgrau n ((x,y):t) | n == y = (x,y) : selgrau n t
					| otherwise = selgrau n t
					
--alinea d)
deriv :: Polinomio -> Polinomio
deriv [] = []
deriv ((x,y):t) = (x*(fromIntegral y), y-1): deriv t 

--alinea e)
calcula :: Float -> Polinomio -> Float
calcula _ [] = 0
calcula n ((x,y):t) = x*(n^fromIntegral y) + calcula n t

--alinea f)
simp :: Polinomio -> Polinomio
simp [] = []
simp ((x,y):t) | x /= 0 = (x,y) : simp t
			   | otherwise = simp t 

--alinea g)
mult :: Monomio -> Polinomio -> Polinomio
mult _ [] = []
mult (x,y) ((a,b):t) = (x*a,y+b) : mult (x,y) t

--alinea h)
normaliza :: Polinomio -> Polinomio
normaliza [] = []
normaliza (h:t) = normalizaux h (normaliza t)

normalizaux :: Monomio -> Polinomio -> Polinomio
normalizaux x [] = [x]
normalizaux (x,xs) ((y,ys):z) | xs==ys = [(x+y,ys)] ++ z
							  | otherwise = (y,ys) : normalizaux (x,xs) z

--alinea i)
soma :: Polinomio -> Polinomio -> Polinomio
soma [] [] = []
soma x [] = x
soma (x:xs) (y:ys) = normaliza ((x:xs) ++ (y:ys)) 

--alinea j)
produto :: Polinomio -> Polinomio -> Polinomio
produto [] [] = []
produto x [] = []
produto [] y = []
produto ((x,xs):t) ((y,ys):z) = [(x*y,xs+ys)] ++ produto t z 

--alinea k)
ordena :: Polinomio -> Polinomio
ordena [] = []
ordena [x] = [x]
ordena (h:t) | snd h <= snd(head t) = h:ordena t
             | otherwise = (ordena t)  h