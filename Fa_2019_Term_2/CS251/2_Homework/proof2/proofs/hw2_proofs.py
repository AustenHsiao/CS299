from sys import argv
from AST import (truth_table, Var, true, false, And, Or, Not, Arrow)
from Parser import parse
from Exceptions import (ProofException, EvalException, ParseException, LexException)
from Proof import (clear, step, premise, andI, andEL, andER, orIL, orIR, orE, assume, assumed, arrowI, arrowE, notI, notE, TI, FE, LEM)

# ¬¬a |- a
# This is a proof from class.
# but, I've modified it so you can use it as a proof rule
# p is the proof of ¬¬A, and a is the expression A.
def doubleNeg(p, a):
	l1 = LEM(Or(a,Not(a)))
	l2 = assume(a)
	l3 = assumed(a)
	l4 = arrowI(l2,l3,Arrow(a,a))
	l5 = assume(Not(a))
	l6 = assumed(Not(a))
	l7 = notE(l6, p, false())
	l8 = FE(l7,a)
	l9 = arrowI(l5,l8,Arrow(Not(a),a))
	l10 = orE(l1,l4,l9,a)
	return l10

#a ∨  b |- b ∨  a
def orComm():
	A = Var("a")
	B = Var("b")
	p1 = premise(Or(A, B)) 

	return orE(p1, arrowI(assume(A), orIR(assumed(A), Or(B, A)), Arrow(A, Or(B, A))), arrowI(assume(B), orIL(assumed(B), Or(B, A)), Arrow(B, Or(B, A))), Or(B, A))	

#a ∨ b, ¬ b |- a
def disSyl():
	A = Var("a")
	B = Var("b")
	p1 = premise(Or(A, B)) 
	p2 = premise(Not(B))
	

	return orE(p1, arrowI(assume(A), assumed(A), Arrow(A,A)), arrowI(assume(B), FE(notE(assumed(B), p2, false()), A), Arrow(B, A)), A)

#¬ a ∨  ¬ b |- ¬ (a ∧ b)
def DM1():
	A = Var("a")
	B = Var("b")
	p1 = premise(Or(Not(A), Not(B)))
	end = Not(And(A,B))
	A_B = And(A,B)
	#I condensed parts of the proofs so I could substitute in things that made sense to me, otherwise I was going nuts
    
	return orE(p1, arrowI(assume(Not(A)), notI(arrowI(assume(A_B), notE(andEL(assumed(A_B), A), assumed(Not(A)), false()), Arrow(A_B, false())), Not(A_B)), Arrow(Not(A), Not(A_B))), arrowI(assume(Not(B)), notI(arrowI(assume(A_B), notE(andER(assumed(A_B), B), assumed(Not(B)), false()), Arrow(A_B, false())), Not(A_B)), Arrow(Not(B), Not(A_B))), end)

#DL1: ¬(¬ a ∨  ¬ b) |- a
# we want to re-use this later,
# so we'll pass in a proof of ¬(¬ a ∨  ¬ b)
# If we want to use this as a general proof
# then we just pass in ¬(¬ a ∨  ¬ b) as a premise
#
# DL1(premise(¬(¬ a ∨  ¬ b))).print_proof()
def DL1(p1):
	a = Var("a")
	b = Var("b")
	
	return doubleNeg(notI(arrowI(assume(Not(a)), notE(orIL(assumed(Not(a)), Or(Not(a), Not(b))), p1, false()), Arrow(Not(a), false())), Not(Not(a))), a)

#DL2: ¬(¬ a ∨  ¬ b) |- b
def DL2(p1):
	a = Var("a")
	b = Var("b")
	
	return doubleNeg(notI(arrowI(assume(Not(b)), notE(orIR(assumed(Not(b)), Or(Not(a), Not(b))), p1, false()), Arrow(Not(b), false())), Not(Not(b))), b)

#¬(a ∧ b) |- ¬ a ∨  ¬ b
def DM2():
	a = Var("a")
	b = Var("b")
	prem = premise(Not(And(a, b))) #The original premise, ~(A && B)
	d1 = premise(Not(Or(Not(a), Not(b)))) #d1 is the phrase required to run DL1 and DL2. I ran it as a premise, but it is assumed, NOT a premise
	
	return doubleNeg(notI(arrowI(assume(Not(Or(Not(a), Not(b)))), notE(andI(DL1(d1), DL2(d1), And(a, b)), prem, false()), Arrow(Not(Or(Not(a), Not(b))), false())), Not(Not(Or(Not(a), Not(b))))), Or(Not(a), Not(b)))

def main():
	try:
		clear()
		orComm().print_proof()
		clear()
		disSyl().print_proof()
		clear()
		DM1().print_proof()
		clear()
		a = Var("a")
		b = Var("b")
		dlPrem = premise(Not(Or(Not(a), Not(b))))
		DL1(dlPrem).print_proof()
		clear()
		dlPrem = premise(Not(Or(Not(a), Not(b))))
		DL2(dlPrem).print_proof()
		clear()
		DM2().print_proof()
	except (ProofException) as e:
		e.print()

if __name__ == "__main__":
    main()
