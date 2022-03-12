import Data.Char
--import System.Random
-- Ex.1
-- a)
elemIndices2 :: Eq a => a -> [a] -> [Int]
elemIndices2 x (h:t) = aux x 0 (h:t)

aux :: Eq a => a -> Int -> [a] -> [Int]
aux x pos [] = []
aux x pos (h:t) | x==h = pos : aux x (pos + 1) t
                | otherwise = aux x (pos + 1) t
              
-- b)
isSubsequenceOf2 :: Eq a => [a] -> [a] -> Bool
isSubsequenceOf2 [] [] = True
isSubsequenceOf2 (x:y) [] = False
isSubsequenceOf2 [] (h:t) = True
isSubsequenceOf2 (x:y) (h:t) | x==h = isSubsequenceOf2 y t
                             | x/=h = isSubsequenceOf2 (x:y) t
                        
-- Ex.2
data BTree a = Empty | Node a (BTree a) (BTree a)

-- a)
lookupAP :: Ord a => a -> BTree (a,b) -> Maybe b
lookupAP x (Node (a,b) l r) | x==a = Just b
                            | x<a = lookupAP x l
                            | x>a = lookupAP x r

{-- b)
zipWithBT :: (a -> b -> c) -> BTree a -> BTree b -> BTree c
zipWithBT Empty Empty = Empty
zipWithBT _ Empty = Empty
zipWithBT Empty _ = Empty
zipWithBT (Node a l r) (Node b ls rs) = Node (a,b) lp rp
    where
        lp = zipWithBT l ls
        rp = zipWithBT r rs


-- Ex.3
digitAlpha2:: String -> (String,String)
digitAlpha2 "" = ("","")
digitAlpha2 l@(h:t) = (x,y)
    where
        --x = if isDigit h then h:(isDigit t) else (isDigit t)
        --y = if isAlpha h then h:(isAlpha t) else (isAlpha t) 
        x = isDigit l
        y = isAlpha l 


-- Ex.4
data Seq a = Nil | Cons a (Seq a) | App (Seq a) (Seq a)

-- a)
firstSeq :: Seq a -> a
firstSeq (Cons a Nil) = a
firstSeq (Cons a x) = firstSeq x
firstSeq (App l r) = firstSeq l 

-- b)
dropSeq :: Int -> Seq a -> Seq a
dropSeq n s | n==0 = s
            | otherwise = dropSeq (n-1) (drop 1 firstSeq s)

-}

{-- c)
instance Show (App a b) where
    show (App a b) = "<<" ++ show a ++ show b ++ ">>"
    show (Cons x a) = show x ++ "," ++ show a
    show (Cons x Nil) = show x
--}


-- Ex.5
type Mat a = [[a]]

exe1 :: Mat Int
exe1 = [[6,7,2],[1,5,9],[8,3,4]]

exe2 :: Mat Int
exe2 = [[16,9,6,3],[5,4,15,10],[11,14,1,8],[2,7,12,13]]

-- a)
getElem :: Mat a -> IO a
getElem m = do
    let altura = (length m)
        largura = (head m)
    l <- randomRIO (0, altura-1)
    c <- randomRIO (0, largura-1)
    return (m !! l !! c)
{--
magic :: Mat Int -> Bool
magic m = linhasOK && colunasOK && diagonaisOK
    where
        linhasOK = verificaLinhas m numeroMagico
        colunasOK = verificaColunas m numeroMagico
        diagonaisOK = diagonal1 m == numeroMagico && diagonal2 m == numeroMagico
        numeroMagico = sum (head m)

verificaLinhas :: Mat Int -> Int -> Bool
verificaLinhas [] _ = True
verificaLinhas (l:xs) n = (sum l ==n) && verificaLinhas xs n

verificaColunas :: Mat Int -> Int -> Bool
verificaColunas ([]:xs) _ = True
verificaColunas m n = sum coluna == n && verificaColunas resto n -- colunas mtz@(h:y) = [y | x <- [0, ((length mtz)-1)] , y <- [map (!! x) mtz]]
    where
        coluna = map head m
        resto =  map tail m

diagonal1 :: Mat Int -> Int
diagonal1 m = sum [m !! i !! i | i <- [0..tamanho-1]]
    where tamanho = length m

diagonal2 m = sum [m !! i!! j | i  <- [0..tamanho], let j = (tamanho -1 ) -i]
    where tamanho = length m
--}