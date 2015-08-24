symbol 	:: Eq s => s -> Parser s s
symbol a []					= []
symbol a (x:xs) | x == a	= [(x,xs)]
				| otherwise = []

failp :: Parser s a
failp xs = []

succeed :: a -> Parser s a
succeed r xs = [(r, xs)]
