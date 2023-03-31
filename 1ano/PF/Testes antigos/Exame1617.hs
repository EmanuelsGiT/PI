-- Ex. 1
-- a)
unlines2 :: [String] -> String
unlines2 [] = ""
unlines2 [x] = x
unlines2 (h:t) = h ++ "\n" ++ unlines2 t

-- b) 
retira :: (Eq a) => [a] -> [a] -> [a]
retira [] _ = []
retira l [] = l
retira (h:t) (x:xs) = retira (aux (h:t) x) xs

aux :: (Eq a) => [a] -> a -> [a]
aux [] _ = []
aux (h:t) x | x==h = t
            | otherwise = h: aux t x
                    
-- Ex. 2
data Seq a = Nil | Inicio a (Seq a) | Fim (Seq a) a

-- a)
primeiro :: Seq a -> a
primeiro (Inicio x _) = x
primeiro (Fim x _) = primeiro x

-- b)
semUltimo :: Seq a -> Seq a 
semUltimo (Inicio a x) = Inicio a (semUltimo x)
semUltimo (Fim Nil a) = Nil
semUltimo (Fim x a) = Fim (semUltimo x) a

-- Ex.3
data BTree a = Empty | Node a (BTree a) (BTree a)

-- a)
prune :: Int -> BTree a -> BTree a
prune a (Node x l r) | a==0 = Empty
                     | otherwise = Node x (prune (a-1) l) (prune (a-1) r) 

-- b)
semMinimo :: (Ord a) => BTree a -> BTree a
semMinimo (Node x Empty Empty) = Empty
semMinimo (Node x Empty r) = Node x Empty (semMinimo r) 
semMinimo (Node x l Empty) = Node x (semMinimo l) Empty
semMinimo (Node x l r) = Node x (semMinimo l) r

-- Ex. 4
type Tabuleiro = [String]

ex :: Tabuleiro
ex = [ "..R.",
       "....",
       ".RR.",
       "...."]

-- a)
posicoes :: Tabuleiro -> [(Int,Int)]
posicoes t = [(x,y) | x <- [0..(length (head t)-1)], y <- [0..((length t)-1)], t!!x!!y == 'R']

-- b)
valido :: Tabuleiro -> Bool
valido t = li (posicoes t) && diag (posicoes t) && ()

li :: [(Int,Int)] -> Bool
li [] = True 
li [x] = True
li (h:t) | (snd h) /= (head t)
            | otherwise = False

diag :: [(Int,Int)] -> Bool
diag [] = True
diag [x] = True
diag (h:t) = undefined