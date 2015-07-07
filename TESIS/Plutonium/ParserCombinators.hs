module ParserCombinators where

import ParserType
import ParserDefine

infixl 7 <$>
infixl 6 <*>
infixl 4 <|>

(<|>)		:: Parser s a -> Parser s a -> Parser s a
(p <|> q) xs =	p xs ++ q xs

(<*>)		:: Parser s (b ->a) -> Parser s b -> Parser s a
(p <*> q) xs =	[ (f x, zs)
				| (f  , ys) <- p xs
				, (  x, zs) <- q ys
				]
				
(<$>)		:: (a -> b) -> Parser s a -> Parser s b
(f <$> p) xs = 	[ (f y, ys)
				| (  y, ys) <- p xs
				]