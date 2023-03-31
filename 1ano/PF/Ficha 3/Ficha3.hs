import  Ficha1

--Ex.1
--data Hora = H Int Int deriving Show
--type Etapa = (Hora,Hora)
--type Viagem = [Etapa]

--alinea a)
etapaValida :: Etapa -> Bool
etapaValida (x,y) = thora x && thora y && comHora x y

--alinea b)
viagemValida :: Viagem -> Bool
viagemValida [] = True
viagemValida [e1] = etapaValida e1
viagemValida ((e1@(p1, c1)):(e2@(p2, c2)):t) = not (comHora p2 c1) && etapaValida (p1, c1) && etapaValida (p2,c2) && viagemValida (e2:t)

--alinea c)
partidaChegada :: Viagem -> (Hora, Hora)
partidaChegada l = (fst(head l),snd(last l))

--alinea d)
tempoViagem :: Viagem -> Int
tempoViagem [] = 0
tempoViagem ((p, c):t) = tempo + tempoViagem t 
			where tempo = difhora c p

--alinea e)
tempoEspera :: Viagem -> Int
tempoEspera [] = 0
tempoEspera ((p, c):(p2, c2):t) = tempo2 + tempoEspera t 
		where tempo2 = difhora p2 c

--alinea f)
tempoTotal :: Viagem -> Int
tempoTotal [] = 0
tempoTotal l = tempoEspera l + tempoViagem l


--Ex.2
type Poligonal = [Ponto]

--alinea a)
comprimento :: Poligonal -> Double
comprimento [] = 0
comprimento [x] = 0
comprimento (h:hs:t) = dist h hs + comprimento (hs:t)

--alinea b)

--Ex.3
data Contacto = Casa Integer
			 | Trab Integer
			 | Tlm Integer
			 | Email String
			 deriving Show

type Nome = String
type Agenda = [(Nome, [Contacto])]

--alinea a)
acrescEmail :: Nome -> String ->  Agenda -> Agenda
acrescEmail "" _ x = x
acrescEmail _ "" x = x
acrescEmail x y [] = [(x,[Email y])]
acrescEmail x y ((nome, contactos):t) | x == nome = (nome,(Email y):contactos):t
									  | otherwise = (nome,contactos) : (acrescEmail x y t)

--alinea b)
verEmails :: Nome -> Agenda -> Maybe [String]
verEmails n [] = Nothing
verEmails n ((nome, contactos): t) | n == nome = Just (getEmails contactos)
								   | otherwise = verEmails n t

getEmails :: [Contacto] -> [String]
getEmails [] = []
getEmails ((Email x):xs) = x : getEmails xs
getEmails (x:xs) = getEmails xs 

--alinea c)
consTelefs :: [Contacto] -> [Integer]
consTelefs [] = []
consTelefs (h:t) = case h of
	Casa x -> x : consTelefs t
	Trab x -> x : consTelefs t
	Tlm x -> x : consTelefs t
	otherwise -> consTelefs t 

--alinea d)
casa :: Nome -> Agenda -> Maybe Integer
casa n [] = Nothing
casa n ((nome, contactos):xs) | n == nome = getCasa contactos
							  | otherwise = casa n xs

getCasa :: [Contacto] -> Maybe Integer
getCasa [] = Nothing
getCasa ((Casa x):xs) = Just x
getCasa (x:xs) = getCasa xs

--Ex.4
type Dia = Int
type Mes = Int
type Ano = Int
type Nome = String

data Data = D Dia Mes Ano
		  deriving Show

type  TabDN = [(Nome,Data)]

--alinea a)