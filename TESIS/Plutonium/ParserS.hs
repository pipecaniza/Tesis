import ParserType
import ParserDefine
import ParserCombinators

data S = Inside S S 
		| Empty
		deriving Show

open  = symbol '('
close = symbol ')'

parenthesis 	::	Parser Char S
parenthesis 	=	(\_ x _ y  -> Inside x y) 
						<$> open <*> parenthesis <*> close <*> parenthesis
					<|> succeed Empty
