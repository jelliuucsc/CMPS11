//-----------------------------------------------------------------------------
//  Jerry Liu
//  jelliu 
//  CMPS101
//  pa3
//  Matrix.java
//  An ADT that uses lists to create the rows of the matrix.
//-----------------------------------------------------------------------------

class Matrix {
	private class Entry {
		int column;
		double value;

		// Constructor
		Entry(int column, double value) {
			this.column = column;
			this.value = value;
		}

		// toString(): overrides Object's toString() method
		public String toString() {
			return "(" + column + ", " + value + ")";
		}

		// equals(): overrides Object's equals() method
		public boolean equals(Object x) {
			boolean eq = false;
			Entry that;
			if (x instanceof Entry) {
				that = (Entry) x;
				eq = ((this.column == that.column) && (this.value == that.value));
			}
			return eq;
		}

	}

	// Fields
	private int dimension;
	private List[] arrayList;

	// Constructor
	// Makes a new n x n zero Matrix. pre: n>=1
	Matrix(int n) {
		if (n < 1) {
			throw new RuntimeException("Matrix Error: Matrix called on an empty matrix");
		}
		dimension = n;
		arrayList = new List[dimension];
		for (int i = 0; i < dimension; i++) {
			arrayList[i] = new List();
		}
	}

	// Access functions
	// Returns n, the number of rows and columns of this Matrix
	int getSize() {

		return dimension;
	}

	// Returns the number of non-zero entries in this Matrix
	int getNNZ() {
		int counter = 0;
		for (int i = 0; i < dimension; i++) {
			counter += arrayList[i].length();
		}
		return counter;
	}

	// overrides Object's equals() method
	public boolean equals(Object x) {
		boolean eq = false;
		Matrix that;
		if (x instanceof Matrix) {
			that = (Matrix) x;
			eq = (this.dimension == that.dimension);
			if (eq == false) {
				return false;
			} else {
				for (int i = 0; i < dimension; i++) {
					eq = (this.arrayList[i].equals(that.arrayList[i]));
					if (eq == false) {
						break;
					}
				}
			}
		}
		return eq;
	}

	// Manipulation procedures
	// sets this Matrix to the zero state
	void makeZero() {
		for (int i = 0; i < dimension; i++) {
			arrayList[i].clear();
		}
	}

	// returns a new Matrix having the same entries as this Matrix
	Matrix copy() {
		Matrix copyMatrix = new Matrix(dimension);
		for (int i = 0; i < dimension; i++) {
			List listA = arrayList[i];
			List listC = listA.copy();
			copyMatrix.arrayList[i] = listC;
		}
		return copyMatrix;
	}

	// changes ith row, jth column of this Matrix to x
	// pre: 1<=i<=getSize(), 1<=j<=getSize()
	void changeEntry(int i, int j, double x) {

		if (i >= 1 && i <= getSize() && j >= 1 && j <= getSize()) {
			if (x == 0) {
				return;
			}
			boolean flag = false;
			Entry newEntry = new Entry(j, x);
			for (arrayList[i - 1].moveFront(); arrayList[i - 1].index() >= 0; arrayList[i - 1].moveNext()) {
				Entry entry = (Entry) arrayList[i - 1].get();
				if (entry.column > j) {
					arrayList[i - 1].insertBefore(newEntry);
					flag = true;
				} else if (entry.column == j) {
					entry.value = x;
					flag = true;
				}
			}
			if (!flag) {
				arrayList[i - 1].append(newEntry);
			}
		} else {
			throw new RuntimeException("Matrix Error: changeEntry call on an out of bound index");
		}
	}

	// returns a new Matrix that is the scalar product of this Matrix with x
	Matrix scalarMult(double x) {
		Matrix scalMatrix = new Matrix(dimension);
		if (x == 0) {
			scalMatrix.makeZero();
		} else {
			for (int i = 0; i < dimension; i++) {
				List listA = arrayList[i];
				List listB = scalMatrix.arrayList[i];
				listA.moveFront();
				for (listA.moveFront(); listA.index() >= 0; listA.moveNext()) {
					Entry entryA = (Entry) listA.get();
					Entry entryB = new Entry(entryA.column, x * entryA.value);
					listB.append(entryB);
				}

			}
		}
		return scalMatrix;
	}

	// returns a new Matrix that is the sum of this Matrix with M
	// pre: getSize()==M.getSize()
	Matrix add(Matrix M) {
		Matrix addMatrix = new Matrix(dimension);
		for (int i = 0; i < dimension; i++) {
			List listA = arrayList[i];
			List listB = M.arrayList[i];
			List listC = addMatrix.arrayList[i];

			listA.moveFront();
			listB.moveFront();

			while (true) {
				if (listA.index() < 0) {
					if (listB.index() < 0) {
						break;
					} else {
						Entry entryB = (Entry) listB.get();
						Entry entryC = new Entry(entryB.column, entryB.value);
						listC.append(entryC);
						listB.moveNext();
						continue;
					}
				} else if (listB.index() < 0) {
					if (listA.index() < 0) {
						break;
					} else {
						Entry entryA = (Entry) listA.get();
						Entry entryC = new Entry(entryA.column, entryA.value);
						listC.append(entryC);
						listA.moveNext();
						continue;
					}
				} else {
					Entry entryA = (Entry) listA.get();
					Entry entryB = (Entry) listB.get();
					if (entryA.column == entryB.column) {
						Entry entryC = new Entry(entryA.column, (entryA.value + entryB.value));
						listC.append(entryC);
						listA.moveNext();
						listB.moveNext();
						continue;
					} else if (entryA.column < entryB.column) {
						Entry entryC = new Entry(entryA.column, entryA.value);
						listC.append(entryC);
						listA.moveNext();
						continue;
					} else {
						Entry entryC = new Entry(entryB.column, entryB.value);
						listC.append(entryC);
						listB.moveNext();
						continue;
					}

				}
			}
		}

		return addMatrix;
	}

	// returns a new Matrix that is the difference of this Matrix with M
	// pre: getSize()==M.getSize()
	Matrix sub(Matrix M) {
		Matrix subMatrix = new Matrix(dimension);
		for (int i = 0; i < dimension; i++) {
			List listA = arrayList[i];
			List listB = M.arrayList[i];
			List listC = subMatrix.arrayList[i];

			listA.moveFront();
			listB.moveFront();

			while (true) {
				if (listA.index() < 0) {
					if (listB.index() < 0) {
						break;
					} else {
						Entry entryB = (Entry) listB.get();
						Entry entryC = new Entry(entryB.column, entryB.value);
						listC.append(entryC);
						listB.moveNext();
						continue;
					}
				} else if (listB.index() < 0) {
					if (listA.index() < 0) {
						break;
					} else {
						Entry entryA = (Entry) listA.get();
						Entry entryC = new Entry(entryA.column, -(entryA.value));
						listC.append(entryC);
						listA.moveNext();
						continue;
					}
				} else {
					Entry entryA = (Entry) listA.get();
					Entry entryB = (Entry) listB.get();
					if (entryA.column == entryB.column) {
						Entry entryC = new Entry(entryA.column, (entryB.value - entryA.value));
						listC.append(entryC);
						listA.moveNext();
						listB.moveNext();
						continue;
					} else if (entryA.column < entryB.column) {
						Entry entryC = new Entry(entryA.column, -(entryA.value));
						listC.append(entryC);
						listA.moveNext();
						continue;
					} else {
						Entry entryC = new Entry(entryB.column, entryB.value);
						listC.append(entryC);
						listB.moveNext();
						continue;
					}

				}
			}
		}

		return subMatrix;

	}

	// returns a new Matrix that is the transpose of this Matrix
	Matrix transpose() {
		Matrix transMatrix = new Matrix(dimension);
		for (int i = 0; i < dimension; i++) {
			List l = arrayList[i];
			for (l.moveFront(); l.index() >= 0; l.moveNext()) {
				Entry entryL = (Entry) l.get();
				Entry entryT = new Entry(i + 1, entryL.value);
				transMatrix.arrayList[entryL.column - 1].append(entryT);
			}
		}
		return transMatrix;
	}

	// returns a new Matrix that is the product of this Matrix with M
	// pre: getSize()==M.getSize()
	Matrix mult(Matrix M) {
		Matrix multMatrix = new Matrix(dimension);
		Matrix B = M.transpose();
		double total;
		for (int i = 0; i < dimension; i++) {
			List listA = arrayList[i];
			List listC = multMatrix.arrayList[i];

			for (int j = 0; j < dimension; j++) {
				List listB = B.arrayList[j];
				listA.moveFront();
				listB.moveFront();
				total = 0;

				while (true) {
					if (listA.index() < 0 || listB.index() < 0) {
						break;

					} else {
						Entry entryA = (Entry) listA.get();
						Entry entryB = (Entry) listB.get();
						if (entryA.column < entryB.column) {
							listA.moveNext();
							continue;
						} else if (entryA.column > entryB.column) {
							listB.moveNext();
							continue;
						} else {
							total += entryA.value * entryB.value;
							listA.moveNext();
							listB.moveNext();
							continue;
						}
					}
				} // end of while loop
				if (total != 0) {
					Entry entryC = new Entry(j + 1, total);
					listC.append(entryC);
				}

			}
		}
		return multMatrix;
	}

	// Other functions
	// overrides Object's toString() method
	public String toString() {
		String s = "";
		for (int i = 0; i < dimension; i++) {
			if (arrayList[i].length() != 0) {
				s += (i + 1) + ":"+ arrayList[i].toString() + "\n";
			}
		}
		return s;
	}

}