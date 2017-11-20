# Genome-Pattern-Search
Matching against a compressed string


Introduction:

Burrows-Wheeler transform makes an input string Text well compressible, especially for a long string of 
genome which only is composed of 'A', 'C', 'T' and 'G'. The Burrows-Wheeler Transform also allows one to
solve the pattern matching problem using the compressed strings instead of the initial string.

The algorithm BWMatching counts the total number of matches of Pattern in Text, where the only information that
we are given is FirstColumn and Last Column = BWT(Text) in addition to the Last-to-First mapping. The 
top and bottom updated to narrow the target region. 

The pseudocode is in the following:
//Assume last_column is given with a symbol of '$'
BWMatching (first_column, last_column, pattern, last_to_first):
top <-0
bottom <- |last_column|-1 
while top <= bottom:
	if Pattern is nonempty
		symbol <- last letter in Pattern
		remove last letter from pattern
		
		if positions from top to bottom in last_column contain an occurrence of symbol:
		top_index <- first position of symbol among positions from top to bottom in last_column
		bottom_indec <- last position of symbol among positions from top to bottom in last_column
		top <- last_to_first(top_index)
		bottom <- last_to_first(bottom_indec)
		
		else 
			return 0
	else
		return bottom - top +1
		
