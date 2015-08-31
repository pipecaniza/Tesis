module Gram where

import ParserType
import ParserDefine
import ParserCombinators

data Expr 	= Func Expr
			| Params String Expr
			| Params1 String
			| Empty
		deriving(Show)

open = symbol '('
close = symbol ')'
func = token "function"

function	:: Parser Char Expr
function 	= 	(\_ _ x _ -> Func x) <$> func <*> open <*> parameters <*> close

parameters 	:: Parser Char Expr
parameters	=	(\x _ y -> Params x y) <$> var <*> symbol ',' <*> parameters
			<|> (\x -> Params1 x) <$> var 
			<|> succeed Empty

var 		:: Parser Char String
var xs		=	[head.var1 $ xs]

var1		::	Parser Char String
var1		= 	(\q y -> q : y)	<$> satisfy isString <*> var
			<|> succeed []

isString	:: 	Char -> Bool
isString x 	=	x >= 'a' && x <= 'z'