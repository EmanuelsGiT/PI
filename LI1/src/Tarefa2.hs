{-# OPTIONS_HADDOCK prune #-}

module Tarefa2 where

import Datatype
import Tarefa1
import Hextuple as H

{- |
= Introdução

Esta Tarefa 2 tinhamos como objetivo implementar a opção de efetuar jogadas. 

= Objetivos e Desenvolvimento

Esta tarefa é uma das mais importantes deste jogo pois é a partir dela que podemos movimentar o pacman pelo labririnto, perder vidas,
passar para o modo normal, Mega ou Dying do pacman, trocar o modo dos fanstasmas (seja ele vivo ou morto), impossibilitar a entrada
do pacman na casa dos fantasmas, o pacman ter a possibilidade de comer os fantasmas e estes regressarem à sua casa, adicionar pontuação
caso o pacman coma comida pequena ou grande e/ou fantasmas e atualizar o estado do labrinto apgando por exemplo a comida que o pacman
comeu. 

= Discussão e Conlusão

Esta tarefa foi sem dúvida a mais trabalhosa no entanto recompensadora porque a partir deste momento é possível movimentar o pacman 
pelo labririnto.

-}

-- | Realiza o movimento do jogador no labririnto. (Função Principal)
play :: Play -- ^ Jogada a ser realizada
     -> State -- ^ Estado do jogo antes do movimento do jogador
     -> State -- ^ Estado de jogo após o movimento do jogador
play (Move npl ori) (State mz allpl l)  
  | gotunel && pacPlayer                               = (State mz (ifNotMegaSetAlive(newList (lessTimeMega(openCloseMouth(putCoords plselect (coordTunel (coordspl plselect) mz)))) allpl)) l)     
  | gotunel                                            = (State mz (ifNotMegaSetAlive(newList (putCoords plselect (coordTunel (coordspl plselect) mz)) allpl)) l)                                           
  | doorGhost && pacPlayer                             = (State mz (ifNotMegaSetAlive(newList (lessTimeMega(setPlayerOri plselect ori)) allpl)) l)   
  | pacMove && (ghost Alive)                           = (State mz (ifNotMegaSetAlive(newList (lessTimeMega(openCloseMouth((lesslife(putCoords plselect (mudaCoord (coordspl plselect) ori)))))) allpl)) l)    
  | pacMove && (ghost Dead) && pieceType (Food Little) = (State (deletePiece mz (mudaCoord (coordspl(plselect)) ori)) (ifNotMegaSetAlive(newList (putCoords (doublespeed(aliveghost(setPlayerOri selectghost U))) (y,x)) (newList (lessTimeMega(openCloseMouth(addscore 11 (putCoords plselect (mudaCoord (coordspl plselect) ori))))) allpl))) l)   
  | pacMove && (ghost Dead) && pieceType (Food Big)    = (State (deletePiece mz (mudaCoord (coordspl(plselect)) ori)) (ifNotMegaSetAlive(newList (putCoords (doublespeed(aliveghost(setPlayerOri selectghost U))) (y,x)) (allghostdead(newList (openCloseMouth(setmega(addscore 15 (putCoords plselect (mudaCoord (coordspl plselect) ori))))) allpl)))) l)   
  | pacMove && (ghost Dead)                            = (State mz (ifNotMegaSetAlive(newList (putCoords (doublespeed(aliveghost(setPlayerOri selectghost U))) (y,x)) (newList (lessTimeMega(openCloseMouth(addscore 10 (putCoords plselect (mudaCoord (coordspl plselect) ori))))) allpl))) l)                                                                                               
  | pacMove && pieceType (Food Little)                 = (State (deletePiece mz (mudaCoord (coordspl(plselect)) ori)) (ifNotMegaSetAlive(newList (lessTimeMega(openCloseMouth(addscore 1 (putCoords plselect (mudaCoord (coordspl plselect) ori))))) allpl)) l) 
  | pacMove && pieceType (Food Big)                    = (State (deletePiece mz (mudaCoord (coordspl(plselect)) ori)) (ifNotMegaSetAlive(allghostdead(halfspeed(newList (openCloseMouth(addscore 5 (setmega(putCoords plselect (mudaCoord (coordspl plselect) ori))))) allpl)))) l)   
  | pacMove                                            = (State mz (ifNotMegaSetAlive(newList (lessTimeMega(openCloseMouth(putCoords plselect (mudaCoord (coordspl plselect) ori)))) allpl)) l)
  | pacPlayer                                          = (State mz (ifNotMegaSetAlive(newList (lessTimeMega(setPlayerOri plselect ori)) allpl)) l) 
  | existMove && hitPacAlive                           = (State mz (ifNotMegaSetAlive( newList (lesslife selectpac) (newList (putCoords plselect (mudaCoord (coordspl plselect) ori)) allpl))) l)    --                                
  | existMove && hitPacDead                            = (State mz (ifNotMegaSetAlive( newList (addscore 10 selectpac) (newList (putCoords (doublespeed(aliveghost(setPlayerOri plselect U))) (y,x)) allpl))) l)
  | existMove                                          = (State mz (ifNotMegaSetAlive(newList (putCoords plselect (mudaCoord (coordspl plselect) ori)) allpl)) l)                                    
  | otherwise                                          = (State mz (ifNotMegaSetAlive(newList (lessTimeMega(setPlayerOri plselect ori)) allpl)) l)                                                                         
 where plselect    = (oldplayer npl allpl)
       pacPlayer   = bePacman plselect
       existMove   =  ori==(oripl(oldplayer npl allpl)) && not(Wall==(nextPiece mz (coordspl(oldplayer npl allpl)) ori))
       pacMove     = existMove && pacPlayer
       hitPacAlive = sameOriPacman allpl (mudaCoord (coordspl selectpac) ori) && Alive==typeghost plselect
       hitPacDead  = sameOriPacman allpl (mudaCoord (coordspl selectpac) ori) && Dead==typeghost plselect
       pieceType a = (a==(nextPiece mz (coordspl(oldplayer npl allpl)) ori))
       gotunel     = nonextPiece mz (coordspl(plselect)) ori
       ghost b     = sameOriGhost allpl (mudaCoord (coordspl plselect) ori) && b==typeghost selectghost
       selectghost = (selectOriplayer allpl (mudaCoord (coordspl plselect) ori))
       selectpac   = singlePac allpl
       (y,x) | odd (length mz) && odd (length(head mz))   = ((div (length mz) 2),(div (length(head mz)) 2))
             | odd (length mz) && even (length(head mz))  = ((div (length mz) 2),(div (length(head mz)) 2)-1)
             | even (length mz) && odd (length(head mz))  = ((div (length mz) 2)-1,(div (length(head mz)) 2))
             | even (length mz) && even (length(head mz)) = ((div (length mz) 2)-1,(div (length(head mz)) 2)-1)
       doorGhost   = elem (mudaCoord (coordspl plselect) ori) coordH
       coordH | even (length(mz)) = [(((div (length mz) 2)-2),x) | x <- [((div (length(head mz)) 2)-3)..((div (length(head mz)) 2)+1)]]
              | odd  (length(mz)) = [(((div (length mz) 2)-1),x) | x <- [((div (length(head mz)) 2)-3)..((div (length(head mz)) 2)+1)]]


-- | Recebe o número identificador do player e devolve o player correspondente.
oldplayer :: Int -- ^ Número identificador do player
          -> [Player] -- ^ Lista de jogadores
          -> Player -- ^ Jogador obtido
oldplayer npl (p@(Pacman (PacState ps tm o pac)):t) | H.get1 ps == npl = p
oldplayer npl (p@(Ghost (GhoState ps gm)):t)        | H.get1 ps == npl = p
oldplayer npl (h:t)                                                    = oldplayer npl t 

-- | Recebe um jogador, uma orientação e devolve um jogador com a orientação fornecida.  
setPlayerOri :: Player -> Orientation -> Player
setPlayerOri (Pacman (PacState ps t o pac)) ori = (Pacman (PacState (H.set4 ori ps) t o pac))
setPlayerOri (Ghost (GhoState ps gm)) ori = (Ghost (GhoState (H.set4 ori ps) gm))

-- | Substitui o jogador na lista de jogadores.
newList :: Player -- ^ Jogador modificado 
        ->  [Player] -- ^ Lista dos jogadores 
        -> [Player] -- ^ Lista dos jogadores atualizada
newList p [] = []
newList p@(Pacman (PacState ps1 t1 o1 pac1)) ((Pacman (PacState ps2 t2 o2 pac2)):t) | H.get1 ps1 == H.get1 ps2 = p:t
newList p@(Ghost (GhoState ps1 gm1)) (Ghost (GhoState ps2 gm2):t)                   | H.get1 ps1 == H.get1 ps2 = p:t
newList p (h:t)                                                                                                = h:(newList p t) 

-- | Recebe um jogador e devolve a sua orientação.
oripl :: Player -> Orientation
oripl (Pacman (PacState ps t o pac)) = H.get4 ps
oripl (Ghost (GhoState ps gm)) = H.get4 ps

-- | Devolve a peça que se encontra na coordenada modificada pela orientação fornecida.
nextPiece :: Maze -- ^ Labirinto
          -> Coords -- ^ Coordenadas 
          -> Orientation -- ^ Orientação  
          -> Piece -- ^ Peça com as coordenadas atualizadas
nextPiece mz (y,x) ori = case ori of 
                                R -> (mz!!(y))!!(x+1)
                                L -> (mz!!(y))!!(x-1)
                                U -> (mz!!(y-1))!!(x)
                                D -> (mz!!(y+1))!!(x)
                                otherwise -> (mz!!(y)!!(x))

-- | Verifica se, de acordo com as coordenadas e a orientação fornecida, existe peças nesse local. 
nonextPiece :: Maze -- ^ Labririnto 
            -> Coords -- ^ Coordenadas
            -> Orientation -- ^ Orientação
            -> Bool -- ^ Verdadeiro ou Falso                                 
nonextPiece mz (y,x) ori | x==0 && L==ori = True
                         | x==(length(head mz)-1) && R==ori = True
                         | otherwise = False

-- | Troca as coordenadas de um lado tunel para o outro
coordTunel :: Coords -- ^ Coordenadas de um lado do tunel
           -> Maze -- ^ Labririnto
           -> Coords -- ^ Coordenadas do lado oposto do tunel
coordTunel (y,x) mz | x==0 = (y,(length(head mz))-1)
                    | x==(length(head mz))-1 = (y,0)

-- | Redefine as coordenadas de acordo com a orientação.
mudaCoord :: Coords -> Orientation -> Coords 
mudaCoord (y,x) ori = case ori of R -> (y,x+1)
                                  L -> (y,x-1)
                                  U -> (y-1,x)
                                  D -> (y+1,x)
                                  otherwise -> (y,x)

-- | Recebe um jogador e devolve as suas coordenadas.
coordspl :: Player -> Coords
coordspl (Pacman (PacState ps t o pac)) = H.get2 ps
coordspl (Ghost (GhoState ps gm)) = H.get2 ps

-- | Recebe um jogador, as novas coordenadas e devolve o jogador com as coordenadas atualizadas. 
putCoords :: Player -> Coords -> Player 
putCoords (Pacman (PacState ps t o pac)) coord = (Pacman (PacState (H.set2 coord ps) t o pac))
putCoords (Ghost (GhoState ps gm)) coord = (Ghost (GhoState (H.set2 coord ps) gm))

-- | Elimina a peça nas coodenadas fornecidas.
deletePiece :: Maze -- ^ Labirinto antes da alteração
            -> Coords -- ^ Coordenada da peça a ser substituída por Empty
            -> Maze -- ^ Labririnto atualizado
deletePiece mz (y,x) = replaceElemInMaze (y,x) (Empty) mz

-- | Verifica a existência de um fantasma em determinadas coordenadas.
sameOriGhost :: [Player] -- ^ Lista dos jogadores
             -> Coords -- ^ Possíveis coordenadas do fantasma 
             -> Bool -- ^ Verdadeiro ou Falso
sameOriGhost [] coords = False
sameOriGhost (plh:plst) coords = (coordspl plh)==coords || rest
 where rest = sameOriGhost plst coords

-- | Verifica se existe um pacman numa determinada coordenada.
sameOriPacman :: [Player] -- ^ Lista dos jogadores
             -> Coords -- ^ Possíveis coordenadas do pacman
             -> Bool -- ^ Verdadeiro ou Falso
sameOriPacman [] coords = False
sameOriPacman (plh:plst) coords = (coordspl plh)==coords || rest
 where rest = sameOriPacman plst coords

-- | Seleciona o fantasma da lista dos jogadores nas coordenadas fornecidas.
selectOriplayer :: [Player] -- ^ Lista dos jogadores
               -> Coords -- ^ Coordenadas da possível localização 
               -> Player -- ^ Fantasma seleccionado
selectOriplayer (plh:plt) coords  | coordspl(plh)==coords = plh
                                  | otherwise = selectOriplayer plt coords

-- | Recebe a lista de jogadores e devolve o pacman.
singlePac :: [Player] -> Player
singlePac ((Pacman (PacState ps tm o pac)):t) = (Pacman (PacState ps tm o pac)) 
singlePac ((Ghost (GhoState ps gm)):t) = singlePac t

-- | Verifica se o estado do pacman é Mega.
beMega :: Player -> Bool
beMega (Pacman (PacState ps tm o Mega)) = True
beMega _ = False

-- | Recebe a lista de jogadores e caso não exista nenhum pacman no estado Mega, altera todos os estados dos ghosts para Alive. 
ifNotMegaSetAlive :: [Player] -> [Player]
ifNotMegaSetAlive pll | or (map beMega pll) =  pll
                      | otherwise = allghostAlive pll

-- | Recebe um Fantasma e devolve o seu modo. 
typeghost :: Player -> GhostMode
typeghost (Ghost (GhoState ps gm)) = gm
                                                                                              
-- | Testa se o player é um pacman
bePacman :: Player -> Bool
bePacman (Pacman (PacState ps t o pac)) = True
bePacman _ = False

typepacman :: Player -> PacMode
typepacman (Pacman (PacState ps t o pac)) = pac
typepacman _ = Dying

-- | Recebe um número inteiro que será adiconado à pontuação do jogador selecionado.
addscore :: Int -> Player -> Player
addscore n (Pacman (PacState ps t o pac)) = (Pacman (PacState (H.set5 ((+n) (H.get5(ps))) ps) t o pac))

-- | Recebe um pacman e altera o seu estado para Mega.
setmega :: Player -> Player 
setmega (Pacman (PacState ps t o pac)) = (Pacman (PacState ps 8 o Mega))

-- | Diminui o tempo do pacman caso esteja em Mega  (velocidade 1)
lessTimeMega :: Player -> Player
lessTimeMega pl@(Pacman (PacState ps t o pac)) | pac == Mega && t-0.25 > 0 = (Pacman (PacState ps (t-0.25) o pac))
                                               | pac == Mega = (Pacman (PacState ps 0 o Normal))
                                               | otherwise = pl
lessTimeMega pl = pl

-- | Recebe um jogador ao qual será retirada uma vida e, caso tenha 0 vidas altera os seu estado para Dying.
lesslife :: Player -> Player 
lesslife (Pacman (PacState ps t o pac)) | H.get6 ps > 0 = (Pacman (PacState (H.set6 ((+(-1)) (H.get6(ps))) ps) t o pac))
                                        | otherwise = (Pacman (PacState ps t o Dying))

-- | Recebe a lista de jogadores e reduz para metade a velocidade de todos os fantasmas.
halfspeed :: [Player] -> [Player]
halfspeed [] = []
halfspeed ((Ghost (GhoState ps gm)):r) = ((Ghost (GhoState (H.set3 ((/2) (H.get3(ps))) ps) gm))):(halfspeed r)
halfspeed ((Pacman (PacState ps t o pac)):r) = (Pacman (PacState ps t o pac)):(halfspeed r)

-- | Recebe um fantasma e duplica a sua velocidade.
doublespeed :: Player -> Player
doublespeed (Ghost (GhoState ps gm)) = (Ghost (GhoState (H.set3 ((*2) (H.get3(ps))) ps) gm))

-- | Recebe a lista de jogadores e altera o estado de todos os fantasmas para Alive.
allghostAlive :: [Player] -> [Player]
allghostAlive [] = []
allghostAlive ((Ghost (GhoState ps gm)):r) = (Ghost (GhoState ps Alive)):(allghostAlive r)
allghostAlive ((Pacman (PacState ps t o pac)):r) = (Pacman (PacState ps t o pac)):(allghostAlive r)


-- | Recebe a lista de jogadores e altera o estado de todos os fantasmas para Dead.
allghostdead :: [Player] -> [Player]
allghostdead [] = []
allghostdead ((Ghost (GhoState ps gm)):r) = (Ghost (GhoState (H.set4 (invertOri (H.get4(ps))) ps) Dead)):(allghostdead r)
allghostdead ((Pacman (PacState ps t o pac)):r) = (Pacman (PacState ps t o pac)):(allghostdead r)

-- | Recebe uma orientação e devolve-a invertida.
invertOri :: Orientation -> Orientation
invertOri ori | ori == R = L
              | ori == L = R
              | ori == U = D
              | ori == D = U

-- | Recebe um fantasma e altera o seu estado para Alive.     
aliveghost :: Player -> Player
aliveghost (Ghost (GhoState ps gm)) = (Ghost (GhoState ps Alive))

-- | Abre e fecha a boca do pacman
openCloseMouth :: Player -> Player
openCloseMouth (Pacman (PacState ps t Open pac)) = (Pacman (PacState ps t Closed pac))
openCloseMouth (Pacman (PacState ps t Closed pac)) = (Pacman (PacState ps t Open pac))