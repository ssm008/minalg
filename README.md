## Minimal Linear Algebra

The goal is to create a minimal set of useful linear algebra functions in C.

## Using it
In minalg.h there are definitions of vectors and matrices. Also a macro for each (VEC and MATRIX) that will place a vector or matrix on the stack in a function.

The VEC\_MAX\_LEN macro will decide how big these vectors and matrices can be. If the max length is set to 4, the VEC/MATRIX macros will put a 4-length empty vector or a 4x4-size empty matrix on the stack. The "usable" length of that is defined by the "len" element in vector or "nr" and "nc" in the matrix case.

If you make a zeroed 2x2 matrix this way the layout will be as follows:
	
	0 0 x x
	0 0 x x
	x x x x
	x x x x

Where x is all the unitialized values in the matrix on the stack. But the functions will only operate on the 2x2 region.

Matrix objects must therefore be accessed with the MatPtr(&mat, row, column) function.

This code is still in development

## TODO
 * Improve tests
 * Take vector orientation seriously. Currently Vec are treated as both row and column vector.
 * MAYBE add checks for vector and matrix sizes, so that operations are legal. Currently it is entirly up to developer to not mess it up (which is minimal, actually)
