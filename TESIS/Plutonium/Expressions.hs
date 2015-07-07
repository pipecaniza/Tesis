data Expr 	= 	Con Int
			| 	Var String
			|	Fun String[Expr]
			|	Expr :+: Expr
			|	Expr :-: Expr
			|	Expr :*: Expr
			|	Expr :/: Expr
			
fact :: Parser Char Expr
fact = 	Con <$> integer
	<|>	Var <$> identifier
	<|> Fun <$> identifier <*> parenthesised (commaList expr)
	<|> parenthesised expr

integer :: Parser Char Int
integer = (const negate <$> (symbol '-')) 'option' id <*> natural

term :: Parser Char Expr
term chainl fact
			(	const (:*:) <$> symbol '*'
			<|> const (:/:) <$> symbol '/'
			)
			
expr :: Parser Char Expr
expr chainl term
			(	const (:+:) <$> symbol '+'
			<|> const (:-:) <$> symbol '-'
			)