-- Ex.1 

data BTree a = Empty 
             | Node a (BTree a) (BTree a)
        deriving Show



-- Ex.2
ex2 = (Node 7 (Node 4 (Node 1 Empty Empty)
                      (Node 6 (Node 5 Empty Empty) Empty) 
              ) 
              (Node 14 (Node 8 Empty Empty) 
                       (Node 20 Empty (Node 21 Empty Empty)
                       ) 
              ) 
      )
-- alinea a)
minimo :: Ord a => BTree a -> a
minimo (Node a Empty _) = a
minimo (Node a l r) = minimo l 

-- alinea b)
semMinimo :: Ord a => BTree a -> BTree a
semMinimo (Node a Empty Empty) = Empty
semMinimo (Node a l r) = Node a (semMinimo l) r

-- alinea c)
minSmin :: Ord a => BTree a -> (a,BTree a)
minSmin (Node a Empty _) = (a,Empty) 
minSmin (Node a l r) = (m, Node a b r)
    where
        (m,b) = minSmin l 

-- alinea d)
remove :: Ord a => a -> BTree a -> BTree a
remove x t@(Node a l r) | x==fst(minSmin t) = snd(minSmin t)  
                        | x<a = (Node a (remove x l) r)
                        | x>a = (Node a l (remove x r))
                        | x==a = Empty

-- Ex.3
type Aluno = (Numero,Nome,Regime,Classificacao)
type Numero = Int
type Nome = String
data Regime = ORD | TE | MEL deriving (Eq,Show)
data Classificacao = Aprov Int
                    | Rep
                    | Faltou
    deriving (Eq,Show)
type Turma = BTree Aluno -- árvore binário de procura (ordenada por número)
{--
exTurma :: BTree (a, b, c, d)
exTurma = (Node (7,a,b,c) (Node (4,a,b,c) (Node (1,a,b,c) Empty Empty)
                    (Node (6,a,b,c) (Node (5,a,b,c) Empty Empty) Empty) 
            ) 
            (Node (14,a,b,c) (Node (8,a,b,c) Empty Empty) 
                    (Node (20,a,b,c) Empty (Node (21,a,b,c) Empty Empty)
                    ) 
            ) 
    )
--}
-- alinea a)
inscNum :: Numero -> Turma ->  Bool
inscNum x (Node (n,_,_,_) l r) | x==n = True
                               | x<n = inscNum x l
                               | x>n = inscNum x r
                               | otherwise = False

-- alinea b)
inscNome :: Nome -> Turma -> Bool
inscNome x (Node (_,n,_,_) l r) | x==n = True
                                | x<n = inscNome x l
                                | x>n = inscNome x r
                                | otherwise = False

-- alinea c)
trabEst :: Turma -> [(Numero,Nome)]
trabEst (Node (num,nom,reg,_) l r) | reg==TE = [(num,nom)] ++ trabEst l ++ trabEst r
                                   | otherwise = trabEst l ++ trabEst r 
-- alinea d)
nota :: Numero -> Turma -> Maybe Classificacao
nota x (Node (num,_,_,clas) l r) | x == num = Just clas
                                 | x<num = nota x l
                                 | x>num = nota x r
                                 | otherwise = Nothing

-- alinea e)
percFaltas :: Turma -> Float
percFaltas t@(Node (_,_,_,clas) l r) | clas==Faltou = (1 + percFaltas l + percFaltas r) / total t
        where
                total (Node (_,_,_,clas) l r) = 1+ total l + total r 

{-- alinea f)
mediaAprov :: Turma -> Float
mediaAprov t@(Node (_,_,_,clas) l r) = if clas == Aprov n then (n+ mediaAprov l + mediaAprov r) / total t
                                                            else mediaAprov l + mediaAprov r
        where
                total (Node (_,_,_,clas) l r) = 1+ total l + total r 
 --}                   

-- alinea g)
approvAv :: Turma -> Float
approvAv = undefined