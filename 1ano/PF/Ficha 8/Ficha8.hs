-- Ex.1
data Frac = F Integer Integer

-- a)
normaliza :: Frac -> Frac
normaliza (F a b) = if b<0 then F (-1*(div a x)) (-1*(div b x))
                           else F (div a x) (div b x)
    where x = mdc (abs a) (abs b)

mdc :: Integer -> Integer -> Integer
mdc x y 
    | x==y = x 
    | x<y = mdc x (y-x)
    | x>y = mdc (x-y) y

-- b)
instance Eq Frac where
    f1 == f2 = a==c && c==d
     where (F a b) = normaliza f1
           (F c d) = normaliza f2

-- c)
instance Ord Frac where
    (F a b) <= (F c d) = ((fromIntegral a) /(fromIntegral b)) <= ((fromIntegral c) /(fromIntegral d))

-- d)
instance Show Frac where
    show (F a b) = (show a) ++ "/" ++ (show b)

-- e)
instance Num Frac where
    (F a b) + (F c d) = normaliza (F (a*d+c*d) (b*d))
    (F a b) - (F c d) = normaliza (F (a*d-c*d) (b*d))
    (F a b) * (F c d) = normaliza (F (a*c) (b*d))
    abs (F a b) = F (abs a) (abs b)
    signum (F a b) = F ((signum a) * (signum b)) 1
    fromInteger x = F x 1
    negate (F a b) = F (-1*a) b

-- f)
maiorQueDobro :: Frac -> [Frac] -> [Frac]
maiorQueDobro f l = filter (\x -> x > (2*f)) l

-- Ex.2
data Exp a = Const a
            | Simetrico (Exp a)
            | Mais (Exp a) (Exp a)
            | Menos (Exp a) (Exp a)
            | Mult (Exp a) (Exp a)

-- a)
instance Show a => Show (Exp a) where
    show (Const a) = show a
    show (Simetrico a) = "-" ++ show a
    show (Mais a b) = "(" ++ show a ++ " + " ++ show b ++ ")"
    show (Menos a b) = "(" ++ show a ++ " - " ++ show b ++ ")"
    show (Mult a b) = "(" ++ show a ++ " * " ++ show b ++ ")"

ex2 = Mult (Mais (Const 1)(Const 2)) (Const 3)
ex3 = Simetrico (Mais ( Const 1)(Const 2))

-- b)
instance (Num a, Eq a) => Eq (Exp a) where
 exp1 == exp2 = calcula exp1 == calcula exp2

calcula :: Num a => Exp a -> a
calcula (Const a) = a
calcula (Simetrico e) = -1 * calcula e
calcula (Mais e1 e2) = calcula e1 + calcula e2
calcula (Menos e1 e2) = calcula e1 - calcula e2
calcula (Mult e1 e2) = calcula e1 * calcula e2

-- c)


-- Ex.3
data Movimento = Credito Float | Debito Float
data Data = D Int Int
data Extracto = Ext Float [(Data, String, Movimento)] 
