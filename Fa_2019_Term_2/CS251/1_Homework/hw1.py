##########################
#Austen Hsiao            #
#Homework 1, Q6, CS251   #
#Instructor: Steven Libby#
##########################

from AST import *

def Q4_1(A, B, C):
	return Arrow(And(A, B), And(B, C)) 	

def Q4_2(A, B, C):
	return Arrow(A, Arrow(And(B, B), C))

def Q4_3(A, B, C, D):
	return Arrow(Or(And(Not(A), B), C) , D)

def Q4_4(A, B):
	return Or(Not(Not(A)), Not(Not(B)))

def Q4_5(A, B):
	return Or(Arrow(A, B), Arrow(B, A))

if __name__ == '__main__':
	A = "A"
	B = "B"
	C = "C"
	D = "D"

	print(Q4_1(A, B, C))
	print(Q4_2(A, B, C))
	print(Q4_3(A, B, C, D))
	print(Q4_4(A, B))
	print(Q4_5(A, B))
