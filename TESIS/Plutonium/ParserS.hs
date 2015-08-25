import ParserType
import ParserDefine
import ParserCombinators

data S = Inside S 
		| Empty
		deriving Show

open  = symbol '('
close = symbol ')'

parenthesis 	::	Parser Char S
parenthesis 	=	(\_ x _  -> Inside x ) 
						<$> open <*> parenthesis <*> close
					<|> succeed Empty
