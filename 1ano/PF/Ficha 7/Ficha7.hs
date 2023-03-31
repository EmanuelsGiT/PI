 -- Ex.1

data ExpInt = Const Int
             | Simetrico ExpInt
             | Mais ExpInt ExpInt
             | Menos ExpInt ExpInt
             | Mult ExpInt ExpInt

-- alinea a)
calcula :: ExpInt -> Int
calcula (Const x) = x
calcula (Simetrico e)  = -1 * calcula e
calcula (Mais e1 e2) = calcula e1 + calcula e2
calcula (Menos e1 e2) = calcula e1 - calcula e2
calcula (Mult e1 e2) = calcula e1 * calcula e2

ex1 = (Mais (Const 3) (Menos (Const 2 ) (Const 5)))

ex2 = (Mult (Mais (Const 1) (Const 2)) (Menos (Const 3) (Const 4)))

-- alinea b)
infixa :: ExpInt -> String
infixa (Const x) = show x
infixa (Simetrico e) = "-(" ++ infixa e ++ ")"
infixa (Mais e1 e2) = "(" ++ infixa e1 ++ " + " ++ infixa e2 ++ ")"
infixa (Menos e1 e2) = "(" ++ infixa e1 ++ " - " ++ infixa e2 ++ ")"
infixa (Mult e1 e2) = "(" ++ infixa e1 ++ " * " ++ infixa e2 ++ ")"

-- alinea c)
posfixa :: ExpInt -> String
posfixa (Const x) = show x
posfixa (Simetrico e) = "-(" ++ posfixa e ++ ")"
posfixa (Mais e1 e2) = posfixa e1 ++ " " ++ posfixa e2 ++ "+"
posfixa (Menos e1 e2) = posfixa e1 ++ " " ++ posfixa e2 ++ "-"
posfixa (Mult e1 e2) = posfixa e1 ++ " " ++ posfixa e2 ++ "*"

-- Ex.2

data RTree a = R a [RTree a] deriving Show

ex4 = R 3 [
            R 1 [
                    R 2 [] ,
                    R 6 []
                    ] ,
            R 7 [] ,
            R 4 []
            ] 

-- alinea a)
soma :: Num a => RTree a -> a
soma (R n l) = n + sum (map soma l)  

-- alinea b)
altura :: RTree a -> Int
altura (R n []) = 1
altura (R n l) = 1 + maximum (map altura l)

-- alinea c)
prune :: Int -> RTree a -> RTree a
prune 0 (R n l) = R n []
prune p (R n l) = R n (map (\r -> prune (p-1) r) l)

-- alinea d)
mirror :: RTree a -> RTree a
mirror (R n l) = R n (reverse (map mirror l))

--alinea e)
postorder :: RTree a -> [a]
postorder (R n l) = concat (map postorder l) ++ [n]

pretorder :: RTree a -> [a]
pretorder (R n l) = n : concat (map pretorder l)

-- Ex.3

data BTree a = Empty | Node a (BTree a) (BTree a)
data LTree a = Tip a | Fork (LTree a) (LTree a) deriving Show

ex5 = Fork 
            (Fork 
                (Tip 1) 
                (Tip 2)) 
            (Fork 
                (Tip 3) 
                (Fork 
                    (Tip 4) 
                    (Tip 5)))

-- alinea a)
ltSum :: Num a => LTree a -> a
ltSum (Tip n) = n
ltSum (Fork lt rt) = ltSum lt + ltSum rt

-- alinea b)
listaLT :: LTree a -> [a]
listaLT (Tip n) = [n]
listaLT (Fork lt rt) = listaLT lt ++ listaLT rt

-- alinea c)
ltHeight ::  LTree a -> Int
ltHeight (Tip n) = 1
ltHeight (Fork lt rt) = 1 + max (ltHeight lt) (ltHeight rt)

-- Ex.4
data FTree a b = Leaf b | No a (FTree a b) (FTree a b)

ex6 :: FTree Char Int
ex6 = No 'a' 
        (No 'b' 
            (Leaf 1) 
            (Leaf 2)) 
        (No 'c' 
            (Leaf 3) 
            (No 'd' 
                (Leaf 4) 
                (Leaf 5)))

-- alinea a)
splitFTree :: FTree a b -> (BTree a, LTree b)
splitFTree (Leaf b) = (Empty, Tip b)
splitFTree ( No a lt rt) = (Node a bleft bright, Fork lleft lright)
    where (bleft, lleft) = splitFTree lt
          (bright, lright) = splitFTree rt

-- alinea b)
joinTrees :: BTree a -> LTree b -> Maybe (FTree a b)
joinTrees Empty (Tip b) = Just (Leaf b)
joinTrees (Node a bl br) (Fork ll lr) = case joinedl of
                                            Nothing -> Nothing
                                            Just l -> case joinedr of
                                                Nothing -> Nothing
                                                Just r -> Just (No a l r)
    where joinedl = joinTrees bl ll
          joinedr = joinTrees br lr

joinTrees Empty (Fork l r) = Nothing
joinTrees (Node a l r) (Tip b)= Nothing

--or

joinTrees x y = Nothing