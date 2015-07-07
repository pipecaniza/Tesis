module ParserDefine where

type Parser symbol result = [symbol] -> [(result,[symbol])]