import Datatype
import Graphics.Gloss as G
import Graphics.Gloss.Interface.Pure.Game as G
import Graphics.Gloss.Juicy as G
import Data.Maybe
import Datatype
import Tarefa2
import Tarefa4
import Tarefa5
import Tarefa6
import Control.Monad.IO.Class


displayMode :: Display
displayMode = InWindow "Game" (800,800) (200,200)

greenCircle :: Picture
greenCircle = color green (ThickCircle 0 200)

yellowSquare :: Picture
yellowSquare = color yellow (Polygon [(0,0),(10,0),(10,10),(0,10),(0,0)])

yellowP :: Picture
yellowP = color yellow (Polygon [(0,0),(10,0),(10,10),(0,10),(0,0)])

redSquare :: Picture
redSquare = color red (Polygon [(0,0),(10,0),(10,10),(0,10),(0,0)]) 

rosinhaXPTOSquare :: Picture
rosinhaXPTOSquare = color magenta (Polygon [(0,0),(10,0),(10,10),(0,10),(0,0)])

pieceToPic :: Piece -> Picture
pieceToPic Wall=  color black (Polygon [(0,0),(15,0),(15,15),(0,15),(0,0)])
pieceToPic (Food Little) = color blue (Polygon [(0,0),(10,0),(10,10),(0,10),(0,0)])
pieceToPic (Food Big) = color cyan (Polygon [(0,0),(10,0),(10,10),(0,10),(0,0)])
pieceToPic Empty = Blank 

drawMap :: Maze -> (Int,Int) -> [Picture]
drawMap [] _ = []
drawMap (h:t) (x,y) = (Translate 0 (fromIntegral(y*(-15))) (Pictures (drawLine h x))):(drawMap t (x,y+1))

drawLine :: [Piece] -> Int -> [Picture]
drawLine [] _ = []
drawLine (h:t) x = (Translate (fromIntegral(x*15)) 0 (pieceToPic h)):(drawLine t (x+1))


drawPlayers :: Player -> Picture
drawPlayers (Pacman (PacState (_,(x,y),_,_,_,_) _ Open Normal )) = translate (fromIntegral y*15) (fromIntegral x*(-15)) yellowP
drawPlayers (Pacman (PacState (_,(x,y),_,_,_,_) _ Closed Normal )) = translate (fromIntegral y*15) (fromIntegral x*(-15)) yellowP
drawPlayers (Pacman (PacState (_,(x,y),_,_,_,_) _ Open Mega )) = translate (fromIntegral y*15) (fromIntegral x*(-15)) yellowP
drawPlayers (Pacman (PacState (_,(x,y),_,_,_,_) _ Closed Mega )) = translate (fromIntegral y*15) (fromIntegral x*(-15)) yellowP
drawPlayers (Ghost (GhoState (_,(x,y),_,_,_,_) Dead)) = translate (fromIntegral y*15) (fromIntegral x*(-15)) rosinhaXPTOSquare
drawPlayers (Ghost (GhoState (_,(x,y),_,_,_,_) Alive)) = translate (fromIntegral y*15) (fromIntegral x*(-15)) redSquare

drawState :: State -> Picture
drawState (State m pl l) = pictures ((drawMap m (0,0))++(map drawPlayers pl))

eventChange :: Event -> State -> State
eventChange (EventKey (SpecialKey k) Down _ _) (State mz allpl l) = case k of
        KeyRight -> if not(oriWall R) then (State mz (newList (setPlayerOri pac R) allpl) l)
                                      else (State mz (newList (setPlayerOri pac (oripl pac)) allpl) l)
        KeyLeft  -> if not(oriWall L) then (State mz (newList (setPlayerOri pac L) allpl) l)
                                      else (State mz (newList (setPlayerOri pac (oripl pac)) allpl) l)
        KeyUp    -> if not(oriWall U) then (State mz (newList (setPlayerOri pac U) allpl) l)
                                      else (State mz (newList (setPlayerOri pac (oripl pac)) allpl) l)
        KeyDown  -> if not(oriWall D) && not(doorGhost) then (State mz (newList (setPlayerOri pac D) allpl) l)
                                                        else (State mz (newList (setPlayerOri pac (oripl pac)) allpl) l)
 where oriWall ori = (Wall==(nextPiece mz (coordspl pac) ori))
       pac = singlePac allpl
       doorGhost   = elem (mudaCoord (coordspl pac) D) coordH
       coordH | even (length(mz)) = [(((div (length mz) 2)-2),x) | x <- [((div (length(head mz)) 2)-3)..((div (length(head mz)) 2)+1)]]
              | odd  (length(mz)) = [(((div (length mz) 2)-1),x) | x <- [((div (length(head mz)) 2)-3)..((div (length(head mz)) 2)+1)]]
eventChange _ s = s

timeChange :: Float -> State -> State
timeChange f (state) = passTime (round (f/8)) state


main :: IO()
main = do G.play displayMode (greyN 0.8) 4 stateIn drawState eventChange timeChange


stateIn :: State 
stateIn = State mz allpl 1

allpl :: [Player]
allpl =[Ghost (GhoState {ghostState = (2,(7,17),0.0,Null,0,1), ghostMode = Alive}),Ghost (GhoState {ghostState = (1,(7,9),0.0,Null,0,1), ghostMode = Alive}),Pacman (PacState {pacState = (0,(1,1),1.0,R,0,1), timeMega = 0.0, openClosed = Open, pacmanMode = Normal})]
mz :: Maze
mz = [[Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall],[Wall,Empty,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Wall,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Wall],[Wall,Food Little,Wall,Wall,Wall,Wall,Food Little,Wall,Wall,Wall,Wall,Wall,Food Little,Wall,Food Little,Wall,Wall,Wall,Wall,Wall,Food Little,Wall,Wall,Wall,Wall,Food Little,Wall],[Wall,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Wall],[Wall,Food Little,Wall,Wall,Wall,Wall,Food Little,Wall,Food Little,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Food Little,Wall,Food Little,Wall,Wall,Wall,Wall,Food Little,Wall],[Wall,Food Big,Food Little,Food Little,Food Little,Food Little,Food Little,Wall,Food Little,Food Little,Food Little,Food Little,Food Little,Wall,Food Little,Food Little,Food Little,Food Little,Food Little,Wall,Food Little,Food Little,Food Little,Food Little,Food Little,Food Big,Wall],[Wall,Wall,Wall,Wall,Wall,Wall,Food Little,Wall,Wall,Wall,Wall,Wall,Empty,Wall,Empty,Wall,Wall,Wall,Wall,Wall,Food Little,Wall,Wall,Wall,Wall,Wall,Wall],[Wall,Empty,Empty,Empty,Empty,Wall,Food Little,Wall,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Wall,Food Little,Wall,Empty,Empty,Empty,Empty,Wall],[Wall,Wall,Wall,Wall,Wall,Wall,Food Little,Wall,Empty,Wall,Wall,Wall,Empty,Empty,Empty,Wall,Wall,Wall,Empty,Wall,Food Little,Wall,Wall,Wall,Wall,Wall,Wall],[Empty,Empty,Empty,Empty,Empty,Empty,Food Little,Empty,Empty,Wall,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Wall,Empty,Empty,Food Little,Empty,Empty,Empty,Empty,Empty,Empty],[Wall,Wall,Wall,Wall,Wall,Wall,Food Little,Wall,Empty,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Empty,Wall,Food Little,Wall,Wall,Wall,Wall,Wall,Wall],[Wall,Food Little,Food Little,Food Little,Food Little,Wall,Food Little,Wall,Empty,Wall,Food Little,Food Little,Food Little,Food Big,Food Little,Food Little,Food Little,Wall,Empty,Wall,Food Little,Wall,Food Little,Food Little,Food Little,Food Little,Wall],[Wall,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Wall,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Wall],[Wall,Food Little,Wall,Wall,Wall,Wall,Food Little,Wall,Wall,Wall,Wall,Wall,Food Little,Wall,Food Little,Wall,Wall,Wall,Wall,Wall,Food Little,Wall,Wall,Wall,Wall,Food Little,Wall],[Wall,Food Big,Food Little,Food Little,Food Little,Wall,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Wall,Food Little,Food Little,Food Little,Food Big,Wall],[Wall,Wall,Wall,Wall,Food Little,Wall,Food Little,Wall,Food Little,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Food Little,Wall,Food Little,Wall,Food Little,Wall,Wall,Wall,Wall],[Wall,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Wall,Food Little,Food Little,Food Little,Food Little,Food Little,Wall,Food Little,Food Little,Food Little,Food Little,Food Little,Wall,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Wall],[Wall,Food Little,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Food Little,Wall,Food Little,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Food Little,Wall],[Wall,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Food Little,Wall],[Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall,Wall]]