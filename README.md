# CS-F214_Assignment-1
Developed a Logical Framework to check the Proof of Natural Deduction in Propositional Logic in C language

A tool for verifying whether a certain proof of a given sequent is valid or not. In order to keep it simple, in this assignment we allowed only the usage of 
the following proof rules:

1. `Premise` 
2. `AND introduction/elimination` 
3. `OR introduction`
4. `IMPLIES elimination` 
5. `MT (Modus Tollens)`

## Definitions:
`<statement> ::= p | ¬p | ¬(<statement>) | (<statement> ∧ <statement>) | (<statement> ∨ <statement>) | (<statement> → <statement>)`
`<rule> ::= ∧i | ∧e1 | ∧e2 | ∨i1 | ∨i2 | →e |P`

## Input:
First line: `n` (number of statements) </br>
Next n lines: `<statement>/<rule>[/line1[/line2]]` (parameter in [ ] is optional whose existence will be determined by <rule>)

## Output:
`Valid Proof (or) Invalid Proof`

## Assumptions:
1. Line number starts from 1.
2. `<statement>` should be perfectly parenthesized, e.g. `((a ∧ b) ∧ c)` is valid, `(a ∧ b) ∧ c` is invalid, `((a ∧ b))` is invalid, `(a ∧ b)` is valid, `(a ∧ b ∧ c)` is invalid, `p` is valid, `(p)` is invalid.
3. `¬` can be succeeded by a literal or `(` only.

## Sample test case:

Input: </br>
`3` </br>
`a/P` </br>
`b/P` </br>
`(a ∧ b)/∧i/1/2`

Output: </br>
`Valid Proof`
___
> Generated the documentation of the code using Doxygen 
