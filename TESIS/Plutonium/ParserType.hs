module ParserType where

import ParserDefine

symbol 	:: Eq s => s -> Parser s s
symbol a []					= []
symbol a (x:xs) | x == a	= [(x,xs)]
				| otherwise = []

satisfy :: (s -> Bool) -> Parser s s
satisfy p []					= []
satisfy p (x:xs) 	| p x		= [(x,xs)]
					| otherwise	= []

token :: Eq s => [s] -> Parser s [s]
token k xs	| k == take n xs 	= [(k, drop n xs)]
			| otherwise			= []
		where n = length k

failp :: Parser s a
failp xs = []

succeed :: a -> Parser s a
succeed r xs = [(r, xs)]

epsilon :: Parser s ()
epsilon xs = [((),xs)]

digit :: Parser Char Char
digit  = satisfy isDigit 

isDigit :: Char -> Bool
isDigit x = '0' <= x && x <= '9'

