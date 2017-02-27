//-----------------------------------------------------------------------------

//  MatrixTest.java
//  A test client for the Matrix ADT
//-----------------------------------------------------------------------------

public class MatrixTest{
   public static void main(String[] args){
      int i, j, n = 5; //n=100000;
      Matrix A = new Matrix(n);
      Matrix B = new Matrix(n);

      A.changeEntry(1,1,12); B.changeEntry(1,1,10);
      A.changeEntry(1,2,5); B.changeEntry(1,2,23);
      A.changeEntry(1,3,34); B.changeEntry(1,3,16);
      A.changeEntry(2,1,76); B.changeEntry(2,1,54);
      A.changeEntry(2,2,21); B.changeEntry(2,2,13);
      A.changeEntry(2,3,7); B.changeEntry(2,3,65);
      A.changeEntry(3,1,4); B.changeEntry(3,1,26);
      A.changeEntry(3,2,2); B.changeEntry(3,2,34);
      A.changeEntry(3,3,64); B.changeEntry(3,3,71);

      System.out.println(A.getNNZ());
      System.out.println(A);
      
      System.out.println(B.getNNZ());
      System.out.println(B);

      
      Matrix C = A.scalarMult(1.5);
      System.out.println(C.getNNZ());
      System.out.println(C);
     
      Matrix D = A.add(B);
      System.out.println(D.getNNZ());
      System.out.println(D);
      
      
      Matrix E = A.sub(A);
      System.out.println(E.getNNZ());
      System.out.println(E);
	
      Matrix F = B.transpose();
      System.out.println(F.getNNZ());
      System.out.println(F);
      
      Matrix G = B.mult(B);
      System.out.println(G.getNNZ());
      System.out.println(G);
     
      Matrix H = A.copy();
      System.out.println(H.getNNZ());
      System.out.println(H);
      System.out.println(A.equals(H));
      System.out.println(A.equals(B));
      System.out.println(A.equals(A));

      A.makeZero();
      System.out.println(A.getNNZ());
      System.out.println(A);
   }
}