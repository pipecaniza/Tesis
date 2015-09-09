option :: Parser s a -> a -> Parser s a
option p d = p <|> succeed d

many :: Parser s a -> Parser s [a]
many p = (:) <$> p <*> many p <|> succeed[]

many1 :: Parser s a -> Parser s [a]
many1 p = (:) <$> p <*> many p