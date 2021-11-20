module Hextuple where

get1 (a,b,c,d,e,f) = a
get2 (a,b,c,d,e,f) = b
get3 (a,b,c,d,e,f) = c
get4 (a,b,c,d,e,f) = d
get5 (a,b,c,d,e,f) = e
get6 (a,b,c,d,e,f) = f

set1 x (a,b,c,d,e,f) = (x,b,c,d,e,f)
set2 x (a,b,c,d,e,f) = (a,x,c,d,e,f)
set3 x (a,b,c,d,e,f) = (a,b,x,d,e,f)
set4 x (a,b,c,d,e,f) = (a,b,c,x,e,f)
set5 x (a,b,c,d,e,f) = (a,b,c,d,x,f)
set6 x (a,b,c,d,e,f) = (a,b,c,d,e,x)

ap1 f tuple = set1 (f tuple) tuple
ap2 f tuple = set2 (f tuple) tuple
ap3 f tuple = set3 (f tuple) tuple
ap4 f tuple = set4 (f tuple) tuple
ap5 f tuple = set5 (f tuple) tuple
ap6 f tuple = set6 (f tuple) tuple