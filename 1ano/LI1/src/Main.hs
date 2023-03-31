module Main where

import Data.Time.Clock.POSIX
import Control.Monad.IO.Class
import UI.NCurses
import Datatype
import FileUtils
import Tarefa1
import Tarefa2
import Tarefa3
import Tarefa4
import Tarefa5
import Tarefa6


loadManager :: Manager
loadManager = ( Manager (loadMaze "maps/1.txt") 0 0 0 0 defaultDelayTime )

updateControlledPlayer :: Key -> Manager -> Manager
updateControlledPlayer k (Manager state@(State mz allpl l) pid step before delta delay) = case k of 
                                                                            KeyUpArrow    -> if not(oriWall U) then (Manager (State mz (newList (setPlayerOri pac U) allpl) l) pid step before delta delay)
                                                                                                               else (Manager (State mz (newList (setPlayerOri pac (oripl pac)) allpl) l) pid step before delta delay)
                                                                            KeyDownArrow  -> if not(oriWall D) && not(doorGhost) then (Manager (State mz (newList (setPlayerOri pac D) allpl) l) pid step before delta delay)
                                                                                                               else (Manager (State mz (newList (setPlayerOri pac (oripl pac)) allpl) l) pid step before delta delay)
                                                                            KeyLeftArrow  -> if not(oriWall L) then (Manager (State mz (newList (setPlayerOri pac L) allpl) l) pid step before delta delay)
                                                                                                               else (Manager (State mz (newList (setPlayerOri pac (oripl pac)) allpl) l) pid step before delta delay)
                                                                            KeyRightArrow -> if not(oriWall R) then (Manager (State mz (newList (setPlayerOri pac R) allpl) l) pid step before delta delay)
                                                                                                               else (Manager (State mz (newList (setPlayerOri pac (oripl pac)) allpl) l) pid step before delta delay)
 where oriWall ori = (Wall==(nextPiece mz (coordspl pac) ori))
       pac = (oldplayer pid allpl)
       doorGhost   = elem (mudaCoord (coordspl pac) D) coordH
       coordH | even (length(mz)) = [(((div (length mz) 2)-2),x) | x <- [((div (length(head mz)) 2)-3)..((div (length(head mz)) 2)+1)]]
              | odd  (length(mz)) = [(((div (length mz) 2)-1),x) | x <- [((div (length(head mz)) 2)-3)..((div (length(head mz)) 2)+1)]]

updateBotPlayer :: Manager -> Manager
updateBotPlayer (Manager state@(State mz allpl l) pid step before delta delay) 
 | bot pid state == Nothing = (Manager (State mz (newList (setPlayerOri pac (oripl pac)) allpl) l) pid step before delta delay)
 | otherwise                = (Manager (State mz (newList (setPlayerOri pac (botOri(bot pid state))) allpl) l) pid step before delta delay)
 where pac = (oldplayer pid allpl)

updateScreen :: Window  -> ColorID -> Manager -> Curses ()
updateScreen w a man =
                  do
                    updateWindow w $ do
                      clear
                      setColor a
                      moveCursor 0 0 
                      drawString $ show (state man)
                    render

currentTime :: IO Integer 
currentTime = fmap ( round . (* 1000) ) getPOSIXTime

updateTime :: Integer -> Manager -> Manager
updateTime now (Manager state@(State mz allpl l) pid step before delta delay) | now - before < delay = (Manager state pid step before (now-before) delay)
                                                                              | otherwise = (Manager (passTime step state) pid (step+1) now 0 delay)
                                                                              
nextFrame :: Integer -> Manager -> Manager
nextFrame now (Manager (State mz allpl l) pid step before delta delay) = (Manager (play (Move pid (oripl(oldplayer pid allpl))) (State mz allpl l)) pid step before delta delay)

loop :: Window -> Manager -> Curses ()
loop w man@(Manager (State mz allpl l) pid step bf delt del ) = do 
  color_schema <- newColorID ColorBlue ColorDefault  10
  now <- liftIO  currentTime
  updateScreen w  color_schema man
  if pacDead allpl then closeWindow w
                   else if ( delt > del )
                          then loop w $ nextFrame now man
                          else do
                             ev <- getEvent w $ Just 0
                             case ev of
                                Nothing -> loop w (updateTime now man)
                                Just (EventSpecialKey arrow ) -> loop w $ updateControlledPlayer arrow (updateTime now man)
                                Just (EventCharacter 'b') -> loop w $ updateBotPlayer (updateTime now man)
                                Just ev' ->
                                  if (ev' == EventCharacter 'q')
                                    then return ()
                                    else loop w (updateTime now man)

pacDead :: [Player] -> Bool 
pacDead [] = False
pacDead ((Pacman (PacState ps tm o Dying)):t) = True
pacDead (h:t) = pacDead t

main :: IO ()
main =
  runCurses $ do
    setEcho False
    setCursorMode CursorInvisible
    w <- defaultWindow
    loop w loadManager

