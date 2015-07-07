module ParserCombinatorsEBNF where

import ParserType
import ParserDefine
import ParserCombinators

option :: Parser s a -> a -> Parser s a
option p d = p <|> succeed d

many :: Parser s a -> Parser s [a]
many p = (:) <$> p <*> many p <|> succeed[]

many1 :: Parser s a -> Parser s [a]
many1 p = (:) <$> p <*> many p

pack :: Parser s a -> Parser s b -> Parser s c -> Parser s b
pack p r q = (\ x -> x) <$> p <*> r <*> q

listOf :: Parser s a -> Parser s b -> Parser s [a]
listOf p s = (:) <$> p <*> many ((\ x -> x) <$> s <*> p)

--Auxiliary functions
first :: Parser s b -> Parser s b
first p xs 	| null r		= []
			| otherwise		= [head r]
		where r = p xs

greedy, greedy1 :: Parser s b -> Parser s [b]
greedy 	= first . many
greedy1 = first . many1