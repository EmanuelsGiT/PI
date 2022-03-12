import System.Random
import Data.List

-- a) 
bingo :: IO ()
bingo = do 
    putStr "Bem-vindos ao"
    putStr "jogo do Bingo.\n" -- ou putStrLn "jogo do Bingo."
    bingoAux [] 

bingoAux :: [Int] -> IO()
bingoAux l = do
    k <- getChar
    novoValor <- randomNaoRepetido (1,90) l --randomRIO (1,90)
    putStr "Novo Valor Gerado: "
    print novoValor -- print x == putStrLn (show 3)
    if (length (novoValor : l) < 90) 
        then bingoAux (novoValor : l)
        else putStrLn "FIM."

randomNaoRepetido :: (Int,Int) -> [Int] -> IO Int
randomNaoRepetido gama lista = do 
    novoValor <- randomRIO gama
    if (novoValor `elem` lista)
        then randomNaoRepetido gama lista
        else return novoValor 

-- b)
mastermind :: IO ()
mastermind = do
    putStrLn "MasterMind!!"
    digitos <- geraDigitos
    putStrLn "Números gerados!"
    -- print digitos
    guessing digitos

main = mastermind

guessing :: [Int] -> IO ()
guessing l@[d1,d2,d3,d4] = do
    putStrLn "Insira 4 digitos: "
    input <- getLine -- supondo q o utilizador escreve 1 2 3 4
    let listDigits = words input
    let listDigits'@[d1',d2',d3',d4'] = map read listDigits
    if (listDigits' == l) then putStrLn "Ganhou!"
                          else do
                              putStrLn "Nope"
                              let acertados = length (filter (==True)(zipWith (==) l listDigits'))      
                              --let foraDoSitio = length (filter (\x -> elem x l) listDigits') - acertados -- \x -> elem x l e equivalente  f x = elem x l 
                              let foraDoSitio = calcForaSitio l listDigits'
                              putStr "Acertados: "
                              print acertados
                              putStr "Fora do Sitio: "
                              print foraDoSitio
                              guessing l

calcForaSitio :: [Int] -> [Int] -> Int
calcForaSitio [] _ = 0
calcForaSitio (x:xs) l = if x `elem` l
                            then 1 + calcForaSitio xs (delete x l)
                            else calcForaSitio xs l

geraDigitos :: IO [Int]
geraDigitos = do
    digit1 <- randomRIO (1,9)
    digit2 <- randomRIO (1,9)
    digit3 <- randomRIO (1,9)
    digit4 <- randomRIO (1,9)
    return ([digit1,digit2,digit3,digit4])

{- ao inves do acertados
contaIguais :: [Int] -> [Int] -> Int
contaIguais [] [] = 0
contaIguais (x:xs) (y:ys)
    | x==y = 1 + conatIguais xs ys
    | otherwise = contaIguais xs ys  


 outras respostas possíveis
fazCenas :: IO Int
fazCenas = do 
    a <- randomRIO (1,10)
    b <- randomRIO (1,10)
    return (a+b)

fazCenasFeias :: IO Int
fazCenasFeias = randomRIO (1,10) >>= \k -> randomRIO (1,10)
>>= \j -> return (j+k) 
-}

-- Ex. 2
data Aposta = Ap [Int] (Int, Int)

-- a)
valida :: Aposta -> Bool
valida (Ap l (e1,e2)) = tamanhoValido && dentroAceites && semRepetidos
    where tamanhoValido = length l == 5
          dentroAceites = e1 >= 1 && e1 <= 9 && e2 >= 1 && e2 >= 1 && e2 <= 9&&
                    length l == length (filter (\x -> x >= 1 && x <=50) l)
          semRepetidos = e1 /= e2 && semRepetidosAux l
          semRepetidosAux [] = True
          semRepetidosAux (x:xs) = not (elem  x xs) && semRepetidosAux xs 
-- b)
comuns :: Aposta -> Aposta -> (Int,Int)
comuns (Ap l (e1,e2)) (Ap lc (e1c,e2c)) = (numsCorretos, estrelasCorretas)
    where numsCorretos      = numsCorretosAux l
          estrelasCorretas  = (if e1 == e1c then 1 else 0) +
                              (if e2 == e2c then 1 else 0) +
                              (if e1 == e2c then 1 else 0) +
                              (if e2 == e1c then 1 else 0)
          numsCorretosAux [] = 0
          numsCorretosAux (x:xs) = if x `elem` lc then 1 + numsCorretosAux xs
                                                  else numsCorretosAux xs  
-- c)
instance Eq Aposta where
    (==) ap1 ap2 = comuns ap1 ap2 == (5,2)

premio :: Aposta -> Aposta -> Maybe Int
premio ap chave =  case (comuns ap chave) of
    (5,2) -> Just 1
    (5,1) -> Just 2
    (5,0) -> Just 3
    (4,2) -> Just 4
    (4,1) -> Just 5
    (4,0) -> Just 6
    (3,2) -> Just 7
    (2,2) -> Just 8
    (3,1) -> Just 9
    (3,0) -> Just 10
    (1,2) -> Just 11
    (2,1) -> Just 12
    (2,0) -> Just 13
    otherwise -> Nothing


leAposta :: IO Aposta
leAposta = do
    putStrLn "Insira uma aposta"
    line <- getLine
    let  numbers  = map read (words line)
    if (length numbers /= 7)
        then do 
            putStrLn "Numero inválido de números!"
            leAposta
        else do
            let [x1,x2,x3,x4,x5,x6,x7] = numbers
                aposta = Ap [x1,x2,x3,x4,x5] (x6,x7)
            if not (valida aposta)
                then do 
                    putStrLn "Aposta inválida!"
                    leAposta
                else return aposta

--  d)
joga :: Aposta -> IO ()
joga chave = do
    aposta <- leAposta
    putStrLn ("O seu prémio é o prémio" ++ show (premio aposta chave))

-- e)
geraChave :: IO Aposta
geraChave = do
    nums <- geraNums 5 []
    estrelas@[e1,e2] <- geraNums 2 []
    return (Ap nums (e1,e2)) 

geraNums :: Int -> [Int] -> IO [Int]
geraNums 0 l = return []
geraNums x l = do
  n <- randomRIO (1,50)
  if (elem n l) then geraNums x l
  else do
    ls <- geraNums (x-1) (n:l)
    return (n:ls)

geraNumsEntre :: Int -> (Int,Int) -> [Int] -> IO [Int]
geraNumsEntre 0 r l = return []
geraNumsEntre x r l = do
    n <- randomRIO r
    if (n `elem` l) then geraNumsEntre n r l
                    else do 
                        ls <- geraNumsEntre (x-1) r (n:l)
                        return (n:ls)

geraEstrelas :: Int -> [Int] -> IO [Int]
geraEstrelas 0 l = return []
geraEstrelas x l = do 
    n <- randomRIO (1,9)
    if (n `elem` l) then geraEstrelas n l
                    else do
                        ls <- geraEstrelas (x-1) (n:l)
                        return (n:ls) 

{-- f)
main :: IO ()
main = do
    ch <- geraChave
    ciclo ch

menu :: IO String
menu = do
    { putStrLn menutxt
    ; putStr "Opção: "
    ; c <- getLine
    ; return c
    }
    where menutxt = unlines ["",
                             "Apostar ........... 1"
                             "Gerar nova chave .. 2"
                             "",
                             "Sair ...............0"]
                             -}