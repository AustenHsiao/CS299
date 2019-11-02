from AST import (Pred, Forall, Exists, Var, true, false, And, Or, Not, Arrow)
from Parser import parse
from Exceptions import (ProofException, SubException, ParseException, LexException)
from Proof import (clear, step, premise, andI, andEL, andER, \
                   orIL, orIR, orE, assume, assumed, arrowI, arrowE, \
                   notI, notE, TI, FE, LEM, \
                   forallI, forallE, existsI, existsE)


# FA x. FA y. P(x,y) |-  FA y. FA x. P(x,y)
def forall_comm():
    return forallI(assume(Var("a")), forallI(assume(Var("b")), forallE(forallE(premise(parse("FA x. FA y. P(x, y)")), "b", parse("FA y. P(b, y)")), "a", parse("P(b, a)")), parse("FA x. P(x, a)")), parse("FA y. FA x. P(x, y)"))

#FA x. ~P(x) |- ~EX x. P(x)
def DM1():
    return notI( arrowI(assume(parse("EX x. P(x)")), notE(existsE(assume(parse("EX x. P(x)")), "a", arrowI(assume(parse("P(a)")), assumed(parse("P(a)")), Arrow(parse("P(a)"), parse("P(a)"))), parse("P(a)")), forallE(premise(parse("FA x. ~P(x)")), "a", Not(parse("P(a)"))), false()), Arrow(parse("EX x. P(x)"), false())), Not(parse("EX x. P(x)")))

#EX x. ~P(x) |- ~FA x. P(x)
def DM2():
    return notI(arrowI(assume(parse("FA x. P(x)")), notE(forallE(assumed(parse("FA x. P(x)")), "a", parse("P(a)")), existsE(premise(parse("EX x. ~P(x)")), "a", arrowI(assume(Not(parse("P(a)"))), assumed(Not(parse("P(a)"))), Arrow(Not(parse("P(a)")), Not(parse("P(a)")))), Not(parse("P(a)"))), false()), (Arrow(parse("FA x. P(x)"), false()))), Not(parse("FA x. P(x)")))

#~ EX x. P(x) |- FA x. ~P(x)
def DM3():
    return forallI(assume(Var("a")), notI(arrowI(assume(parse("P(a)")), notE(existsI(assumed(parse("P(a)")), "a", parse("EX x. P(x)")), premise(Not(parse("EX x. P(x)"))), false()), Arrow(parse("P(a)"), false())), Not(parse("P(a)"))), parse("FA x. ~P(x)"))

#FA x. P(x) -> Q |- (EX x. P(x)) -> Q$
def contra():
    return arrowI(assume(parse("EX x. P(x)")), arrowE(existsE(assumed(parse("EX x. P(x)")), "a",  arrowI(assume(parse("P(a)")), assumed(parse("P(a)")), Arrow(parse("P(a)"), parse("P(a)"))), parse("P(a)")), forallE(premise(parse("FA x. (P(x)->Q)")), "a", parse("P(a)->Q")), Var("Q")), Arrow(parse("EX x. P(x)"), Var("Q")))

def main():
    try:
        clear()
        forall_comm().print_proof()
        clear()
        DM1().print_proof()
        clear()
        DM2().print_proof()
        clear()
        DM3().print_proof()
        clear()
        contra().print_proof()

    except (ParseException, LexException) as e:
        print(str(e))
    except (ProofException) as e:
        e.print()
    except Exception as e:
        print(e)

if __name__ == "__main__":
    main()
