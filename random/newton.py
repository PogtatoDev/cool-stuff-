from derivative import derivative

def manual_newton(f, df, guess, eps=0.00001, term_cap=500):        
    next=0
    old=0
    old=guess-(f(guess)/df(guess))
    i=0
    while i < term_cap:
        next=old-(f(old)/df(old))
        if abs(next-old) < eps or abs(f(next)) < eps:
            break
        old=next
        i+=1
    return next

def newton(f, guess, eps=0.00001, term_cap=500):
    df = derivative(f)
    next=0
    old=0
    old=guess-(f(guess)/df(guess))
    i=0
    while i < term_cap:
        next=old-(f(old)/df(old))
        if abs(next-old) < eps or abs(f(next)) < eps:
            break
        old=next
        i+=1
    return next