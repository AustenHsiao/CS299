from AST import *
from Proof import (clear, step, premise, andI, andEL, andER, \
                   orIL, orIR, orE, assume, assumed, arrowI, arrowE, \
                   notI, notE, TI, FE, LEM)
def Q3_1():
	clear()
	A = Var("A")
	B = Var("B")
	p1 = premise(Or(A, B))

	return orE(p1, arrowI(assume(A), orIR(assumed(A), Or(B, A)), Arrow(A, Or(B, A))), arrowI(assume(B), orIL(assumed(B), Or(B, A)), Arrow(B, Or(B, A))), Or(B, A))
	
def Q3_2():
	clear()
	A = Var("A")
	B = Var("B")
	p1 = premise(Or(A, B))
	p2 = premise(Not(B))

	return orE(p1, Arrow(A,A), arrowI(assume(B), FE(notE(assumed(B), p2, false()), A), Arrow(B, A)), A)

def Q3_3():
	clear()
	A = Var("A")
	B = Var("B")
	p1 = premise(Or(Not(A), Not(B)))
	end = Not(And(A,B))
	A_B = And(A,B)
	
	return orE(p1, arrowI(assume(Not(A)), notI(arrowI(assume(A_B), notE(andEL(assumed(A_B), A), assumed(Not(A)), false()), Arrow(A_B, false())), Not(A_B)), Arrow(Not(A), Not(A_B))), arrowI(assume(Not(B)), notI(arrowI(assume(A_B), notE(andER(assumed(A_B), B), assumed(Not(B)), false()), Arrow(A_B, false())), Not(A_B)), Arrow(Not(B), Not(A_B))), end)

if __name__ == '__main__':
	#Q3_1().print_proof()
	Q3_2().print_proof()
	#Q3_3().print_proof()
