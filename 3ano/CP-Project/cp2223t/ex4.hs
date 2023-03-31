import Cp
import Nat
import Rose
import List
import Svg
import Control.Concurrent
import NEList


type Team = String
type Group = [Team]
type Match = (Team, Team) 
group = last groups


groups :: [Group]
groups = [["Qatar", "Ecuador"], ["Senegal", "Netherlands"],
          ["England", "Iran"], ["USA", "Wales"],
          ["Argentina", "Saudi Arabia"], ["Mexico", "Poland"],
          ["France", "Denmark"], ["Tunisia", "Australia"],
          ["Spain", "Germany"], ["Japan", "Costa Rica"],
          ["Belgium", "Canada"], ["Morocco", "Croatia"],
          ["Brazil", "Serbia"], ["Switzerland", "Cameroon"],
          ["Portugal", "Ghana"], ["Uruguay", "Korea Republic"]]



matchResult :: (Match -> Maybe Team) -> Match -> [(Team, Int)]
matchResult f m@(t1,t2) | f m == Just t1 = [(t1,3), (t2,0)]
                        | f m == Just t2 = [(t1,0), (t2,3)]
                        | otherwise = [(t1, 1), (t2,1)]


pairup :: Eq b => [b] -> [(b,b)]
pairup xs = [(x,y) | x <- xs, y <- xs, x/= y]


l = [("Por", 3), ("Por",1), ("Por",3)]

groupWinners criteria = best 2 . consolidate . (>>= matchResult criteria)

best n = map fst . take n . reverse . presort p2

consolidate :: (Num d, Eq d, Eq b) => [(b,d)] -> [(b,d)]
consolidate = map (id><sum) . collect

