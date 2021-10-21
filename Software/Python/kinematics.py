import sympy as sym

DeltaX = 250
DeltaY = 250
Radius = 12.15/2

'''
AlphaP1,AlphaP2 = sym.symbols('x,y')
eq1 = sym.Eq(1/2 * ((AlphaP1 * Radius) - (AlphaP2 * Radius)),DeltaX)
eq2 = sym.Eq(1/2 * ((AlphaP1 * Radius) + (AlphaP2 * Radius)),DeltaY)

result = sym.solve([eq1, eq2], (AlphaP1,AlphaP2))

TestAlphaP1 = result[AlphaP1]
TestAlphaP2 = result[AlphaP2]

print(TestAlphaP1)
print(TestAlphaP2)
'''

'''
Above is using sympy to solve
Below is the derived eqn for Alpha1 and Alpha 2, have to do tests to see which is faster, should be the derived eqn
'''
MEAlphaP1 = (DeltaX + DeltaY)/Radius
MEAlphaP2 = (DeltaY - DeltaX)/Radius

print(MEAlphaP1)
print(MEAlphaP2)