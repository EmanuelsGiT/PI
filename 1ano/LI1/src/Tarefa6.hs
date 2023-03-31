module Tarefa6 where 

import Datatype
import Tarefa5
import Tarefa2

{- |
= Introdução

Na tarefa 6 tinhamos como objetivo implementar um robô que ao analisar o estado de jogo efetuava movimentos
 conforme essa analise.
Para calcuar qual o melhor movimento, nós comparamos as posições dos fantasmas com as possíveis posições 
para onde o pacman se poderia dirigir.

= Objetivos e Desenvolvimento

Para uma melhor análise do estado de jogo decidimos que o pacman iria apenas receber as posições dos fantasmas
 que estivessem mais próximos (ou seja, todos os fantasmas que estivessem a uma distância inferior ou igual a 7).

Establecemos que este robô tem duas formas diferentes de agir:

      - Se existirem fantasmas dentro da área establecida (a uma distância inferior ou igual a 7), o pacman decidirá 
      os seus movimentos de acordo com o seu "modo de fuga" ou seja, ele movimentar-se-á avaliando os movimentos possíveis 
      dos fanatasmas e escolhendo o melhor movimento para se afastar do fantasma mais próximo. Caso existam dois fantasmas à
      mesma distância do pacman, este irá movimentar-se calculando o ponto médio entre eles e afastar-se dessa posição.  

      - Caso não exista nenhum fantasma nas circunstâncias anteriores o pacman irá movimentar-se da mesma forma que os fantasmas 
      no estado Dead da Tarefa anterior (scatterMode).      

Caso não haja um movimento ideal (ou seja, caso todos os movimentos possíveis sejam igualmente desvantajosos) o pacman continuará 
com a orientação anterior o que fará com que a função bot devolva um Nothing.

= Discussão e Conlusão

Após a realização desta Tarefa, obtivemos um robô que se movimenta pelo mapa sem qualquer limitação, que decide
 sempre os seus movimentos de acordo com a posições dos fantasmas e, por isso, consegue sobreviver durante bastante tempo.

-} 

-- | Recbe o identificar do pacman e o estado de jogo e devolve a melhor jogada. (Função Principal)
bot :: Int -> State -> Maybe Play
bot id state@(State mz allpl l) | dist closeG (coordspl pacBot) <= 7 = scapeMode id state
                                | otherwise = Just (scatterMode state id)
 where pacBot = (oldplayer id allpl)
       closeG = head(closeGCoords (coordsGList allpl) coordsPac)
       coordsPac = coordspl (oldplayer id allpl)

-- | Recebe as jogadas do bot e devolve a orientação das jogadas. 
botOri :: Maybe Play -> Orientation
botOri (Just (Move id ori)) = ori

-- | Recebe a lista de jogadores e devolve a lista de coordenadas dos fantasmas. 
coordsGList :: [Player] -> [Coords]
coordsGList [] = []
coordsGList (g@(Ghost (GhoState ps gm)):t)      = coordspl g : coordsGList t
coordsGList ((Pacman (PacState ps tm o pac)):t) = coordsGList t

-- | Compara cada elemento da lista de coordenadas dos fantasmas com as coordenadas do pacman e devolve as coordenadas mais próximas ao pacman.
closeGCoords :: [Coords] -> Coords -> [Coords]
closeGCoords allG coordsPac = filter (\x -> (dist coordsPac x) == minC) allG
 where minC = minimum (map (`dist` coordsPac) allG)

-- | Recebe o identificador do pacman e o estdo de jogo e devolve a melhor jogada (caso não exista devolve Nothing).
scapeMode :: Int -> State -> Maybe Play
scapeMode id state@(State mz allpl l)
  | bOri == Null = Nothing
  | otherwise = Just (Move id bOri)
 where coordsPac = coordspl (oldplayer id allpl)
       bOri      = (bestOri (possibleOri state coordsPac) coordsPac (closeGCoords (coordsGList allpl) coordsPac))

-- | Recebe o estado de jogo e as coordenas do pacman e devolve as orientações que não coincidem com parede.
possibleOri :: State -> Coords -> [Orientation]
possibleOri (State mz allpl l) coords = [x | x <- [R,L,U,D] , Wall/=(nextPiece mz coords x)]

-- | Recebe a lista de orientações possíveis, as corrdenadas do pacman e a lista das coordenadas dos fantasmas mais próximos e devolve a melhor orientação.
bestOri :: [Orientation] -- ^ Lista de orientções possíveis.
        -> Coords        -- ^ Coordenadas do pacman.
        -> [Coords]      -- ^ Lista das coordenadas dos fantasmas mais próximos.
        -> Orientation   -- ^ Melhor orientação
bestOri oriL (y1,x1) [(y2,x2)]  | x1 >= x2 && y1 > y2 && abs(y1-y2) >= abs(x1-x2) && (R `elem` oriL) = R
                                | x1 >= x2 && y1 > y2 && abs(y1-y2) >= abs(x1-x2) && (D `elem` oriL) = D
                                | x1 >= x2 && y1 > y2 && abs(y1-y2) >= abs(x1-x2) && (U `elem` oriL) = U
                                
                                | x1 > x2 && y1 >= y2 && abs(y1-y2) < abs(x1-x2) && (D `elem` oriL) = D
                                | x1 > x2 && y1 >= y2 && abs(y1-y2) < abs(x1-x2) && (R `elem` oriL) = R
                                | x1 > x2 && y1 >= y2 && abs(y1-y2) < abs(x1-x2) && (L `elem` oriL) = L


                                | x1 >= x2 && y1 < y2 && abs(y1-y2) >= abs(x1-x2) && (R `elem` oriL) = R
                                | x1 >= x2 && y1 < y2 && abs(y1-y2) >= abs(x1-x2) && (U `elem` oriL) = U
                                | x1 >= x2 && y1 < y2 && abs(y1-y2) >= abs(x1-x2) && (D `elem` oriL) = D

                                | x1 > x2 && y1 <= y2 && abs(y1-y2) < abs(x1-x2) && (U `elem` oriL) = U
                                | x1 > x2 && y1 <= y2 && abs(y1-y2) < abs(x1-x2) && (R `elem` oriL) = R
                                | x1 > x2 && y1 <= y2 && abs(y1-y2) < abs(x1-x2) && (L `elem` oriL) = L


                                | x1 <= x2 && y1 > y2 && abs(y1-y2) >= abs(x1-x2) && (L `elem` oriL) = L
                                | x1 <= x2 && y1 > y2 && abs(y1-y2) >= abs(x1-x2) && (D `elem` oriL) = D
                                | x1 <= x2 && y1 > y2 && abs(y1-y2) >= abs(x1-x2) && (U `elem` oriL) = U                                  
                            
                                | x1 < x2 && y1 >= y2 && abs(y1-y2) < abs(x1-x2) && (D `elem` oriL) = D
                                | x1 < x2 && y1 >= y2 && abs(y1-y2) < abs(x1-x2) && (L `elem` oriL) = L
                                | x1 < x2 && y1 >= y2 && abs(y1-y2) < abs(x1-x2) && (R `elem` oriL) = R


                                | x1 <= x2 && y1 < y2 && abs(y1-y2) >= abs(x1-x2) && (L `elem` oriL) = L 
                                | x1 <= x2 && y1 < y2 && abs(y1-y2) >= abs(x1-x2) && (D `elem` oriL) = U
                                | x1 <= x2 && y1 < y2 && abs(y1-y2) >= abs(x1-x2) && (U `elem` oriL) = D

                                | x1 < x2 && y1 <= y2 && abs(y1-y2) < abs(x1-x2) && (U `elem` oriL) = U
                                | x1 < x2 && y1 <= y2 && abs(y1-y2) < abs(x1-x2) && (L `elem` oriL) = L
                                | x1 < x2 && y1 <= y2 && abs(y1-y2) < abs(x1-x2) && (R `elem` oriL) = R
bestOri oriL (y1,x1) [(y2,x2),(y3,x3)] | (x1-x2)+(y1-y2)+(x1-x3)+(y1-y3)==0 = Null
                                       | otherwise = bestOri oriL (y1,x1) [(div (y2+y3) 2 , div (x2+x3) 2)]
bestOri _ _ _ = Null