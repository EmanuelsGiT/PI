module Ficha1 where

import Data.Char
--Ex.1
-- aline a)
perimetro1 :: Double -> Double
perimetro1 x = 2 * pi * x

--aline b) sem tulpos
dist1 :: Double -> Double -> Double -> Double -> Double
dist1 x1 y1 x2 y2 = sqrt(((x2 - x1)^2) + ((y2 - y1)^2))

--alinea b) com tuplos
dist2 :: (Double, Double) -> (Double, Double) -> Double
dist2 (x1, y1) (x2, y2) = sqrt (((x2 - x1)^2)+ ((y2 - y1)^2)) 

--alinea c)
primUlt :: [Double] -> (Double, Double)
primUlt l = ( head l , last l )

--alinea d)
multiplo :: Int -> Int -> Bool
multiplo m n = if mod m n == 0 
then True
else False

--alinea e)
truncaImpar :: [Double] -> [Double]
truncaImpar l = if mod (length l) 2 == 0
then l
else tail l

--alinea f)
max2 :: Int -> Int -> Int
max2 x1 x2 = if x1 > x2
then x1
else x2

--alinea g)
max3 :: Int -> Int -> Int -> Int
max3 x3 x1 x2 = if x3 > max2 x1 x2
then x3
else max2 x1 x2


--Ex2.a)
nRaizes :: Double -> Double -> Double -> Int
nRaizes a b c | b^2-4*a*c > 0 = 2
			  | b^2-4*a*c == 0 = 1
			  | otherwise = 0

--alinea b)
raizes :: Double -> Double -> Double -> [Double]
raizes a b c | nRaizes a b c == 2 = [((-1)*b+sqrt(b^2-4*a*c))/2*a, (((-1)*b-sqrt(b^2-4*a*c))/2*a)]
			 | nRaizes a b c == 1 = [((-1)*b+sqrt(b^2-4*a*c))/2*a]
			 | otherwise = []


--Ex3.a)
data Hora = H Int Int deriving Show
type Etapa = (Hora,Hora)
type Viagem = [Etapa]

hhora :: Hora -> Bool
hhora (H h m) = if 0 <= h && h <= 23 && 0<= m && m <= 59 
	then True
	else False
--or

thora :: Hora -> Bool
thora (H h m) | elem(h) [0..23] && elem(m) [0..59] = True
			  | otherwise = False

--alinea b)
comHora :: Hora -> Hora -> Bool
comHora (H h1 m1) (H h2 m2) | h1 > h2 = False
							| h1 < h2 = True
							| (h1 == h2) && (m1 >= m2) = False
					   		| otherwise = True		

--alinea c)
convhora :: Hora -> Int
convhora (H h m) = h*60+m

--alinea d)
convmin :: Int -> Hora
convmin m = (H (div m 60) (mod m 60)) 

--alinea e)
difhora :: Hora -> Hora -> Int
difhora (H h1 m1) (H h2 m2) = (h2*60+m2)-(h1*60+m1)

--alinea f)
adhora :: Hora -> Int -> Hora
adhora (H h m) x = (H h (m+x))


--Ex5.
data Semaforo = Verde | Amarelo | Vermelho deriving (Show,Eq) 

--aline a)
next :: Semaforo -> Semaforo
next Verde = Amarelo
next Amarelo = Vermelho
next Vermelho = Verde

--alinea b)
stop :: Semaforo -> Bool
stop Vermelho = True
stop Amarelo = False
stop Verde = False

stop''' Vermelho = True
stop''' x = False

--alinea c)
safe :: Semaforo -> Semaforo -> Bool
safe Verde Verde = False
safe Verde Amarelo = False
safe Amarelo Verde = False
safe Amarelo Amarelo = False
safe x y = True

--Ex6.
data Ponto = Cartesiano Double Double | Polar Double Double deriving (Show,Eq)

--alinea a)
posx :: Ponto -> Double
posx (Cartesiano x y) | x>=0 = x
					  | otherwise = -x


--alinea b)
posy :: Ponto -> Double
posy (Cartesiano x y) | y>=0 = y
					  | otherwise = -y

--alinea c)
raio :: Ponto -> Double
raio (Polar x y) | x>=0 = x
				 | x<0 = -x

--alinea d)
angulo :: Ponto -> Double
angulo (Polar x y) = y*(180/pi)

--alinea e)
dist :: Ponto -> Ponto -> Double
dist (Cartesiano x1 y1) (Cartesiano x2 y2) = sqrt((x2-x1)^2 + (y2-y1)^2)


--Ex7.
data Figura = Circulo Ponto Double
			|Retangulo Ponto Ponto 
			|Triangulo Ponto Ponto Ponto
			deriving (Show,Eq)

--aliena a)
poligono :: Figura -> Bool
poligono (Retangulo (Cartesiano x3 y3) (Cartesiano x4 y4)) = (x3/=x4 && y3/=y4)  
poligono (Circulo _ x) = x>0
poligono (Triangulo (Cartesiano x3 y3) (Cartesiano x4 y4) (Cartesiano x5 y5)) = (x3/=x4 && y3/=y4 && x3/=x5 && y3/=y5 && x4/=x5 && y4/=y5)

--alinea b)
vertices :: Figura -> [Ponto]
vertices (Retangulo (Cartesiano x1 y1) (Cartesiano x2 y2)) = [(Cartesiano x1 y1), (Cartesiano x2 y2), (Cartesiano x1 y2), (Cartesiano x2 y1)]
vertices (Circulo _ _) = []
vertices (Triangulo (Cartesiano x1 y1) (Cartesiano x2 y2) (Cartesiano x3 y3)) = [(Cartesiano x1 y1), (Cartesiano x2 y2), (Cartesiano x3 y3)]

{--alinea c)
area :: Figura -> Double
area (Triangulo p1 p2 p3) =
	let	a = dist p1 p2
		b = dist p2 p3
		c = dist p3 p1
		s = (a+b+c) / 2 -- semi-perimetro
	in sqrt(s*(s-a)*(s-b)*(s-c)) -- formula de Heron
--area Retangulo
--}

{--alinea d)
perimetro :: Figura -> Double
perimetro (Retangulo (Cartesiano x1 y1) (Cartesiano x2 y2)) = abs(x2-x1)*2 + abs(y2-y1)*2
perimetro (Circulo _ r) = 2*pi*r
perimetro (Triangulo (Cartesiano x1 y1) (Cartesiano x2 y2) (Cartesiano x3 y3)) = let q = sqrt((x2-x1)^2 + (y2-y1)^2) 
																					 w = sqrt((x3-x2)^2 + (y3-y2)^2)
																					 t = sqrt((x1-x3)^2 + (y1-y3)^2) 
																				  in q+w+t
--}

--Ex.8
--alinea a)
islower :: Char -> Bool
islower x = elem(ord x) [97..122]

--alinea b)
isdigit :: Char -> Bool
isdigit x = elem(ord x) [48..57]

--alinea c)
isalpha :: Char -> Bool
isalpha x = elem(ord x) [65..90] || elem(ord x) [97..122]

--alinea d)
toupper :: Char -> Char
toupper x = chr (ord x - 32)

--alinea e)
intoDigit :: Int -> Char
intoDigit x = chr (x + 48)

--alinea f)
digitoInt :: Char -> Int
digitoInt x = (ord x - 48)