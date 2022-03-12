import Data.Char

--Ex.2
ex2d = [take n [1,1..] | n <- [1..5]]

ex2d' = [replicate n 1 | n <- [1..5]]

ex2e = [product [1..x] | x <- [1..6]]

--Ex.3
digitAlpha2 :: String -> (String,String)
digitAlpha2 "" = ("","")
digitAlpha2 (h:t)
    | isDigit h == True = (h:l1,l2)
    | isAlpha h == True = (l1,h:l2)
    | otherwise = (l1,l2)
    where (l1,l2) = digitAlpha2 t 

--ex4.
nzp :: [Int] -> (Int,Int,Int)
nzp [] = (0,0,0)
nzp (h:t)
    | h<0 = (l1+l1,l2,l3)
    | h==0 = (l1,l1+l2,l3)
    | h>0 = (l1,l2,l3)
    where (l1,l2,l3) = nzp t

--Ex.5
divMod2 :: Integral a => a -> a -> (a,a)
divMod2 x y = if x < y
                    then (0,x)
                    else (1+a,b)
                        where () = divMod2 (x-y) y


--Ex.6
fromD :: [Int] -> Int
fromD l = snd (fromDigits2 l)

fromDigits2 :: [Int] -> (Int,Int)
fromDigits2 [] = (0,0)
fromDigits2 (h:t) = (tamnho+1, h*10^tamanho + resto)
    where (tamanho, resto) = fromDigits2 t

--Ex.8
fib :: Int -> Int
fib n = fibAux n (0,1)

fibAux :: Int -> (Int,Int) -> (Int,Int)
fibAux 0 (nesimo,prox) = nesimo
fibAux n (nesimo, prox) = fibAux (n-1) (prox,nesimo+prox)