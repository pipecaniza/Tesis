import ParserType
import ParserDefine
import ParserCombinators


data S = Beside S S
		| Single
	deriving Show
		
data SA 	= 	ConsS Z | SingleS
		deriving Show
data Z  	=	ConsZ SA Z | SingleZ SA
		deriving Show
		
data P = Inside P | Empty
		deriving Show

sequenceOfS		:: 	Parser Char S
sequenceOfS 	=	Beside <$> sequenceOfS <*> sequenceOfS
					<|> const Single <$> symbol 's'
					
sequenceOfS'	:: Parser Char SA
sequenceOfS'	=	const ConsS <$> symbol 's' <*> parseZ
					<|> const SingleS <$> symbol 's'
				where parseZ = 	ConsZ <$> sequenceOfS' <*> parseZ
								<|> SingleZ <$> sequenceOfS'
								
paren	:: Parser Char P
paren 	=  	(\ _ x _ -> Inside x) <$> 
				symbol '(' <*> paren <*> symbol ')'  
			<|> 	succeed Empty