
import java.io.*;
import java.util.Scanner;

public class Sparse {
	public final static void main(String args[]) throws IOException {
		Scanner in = null;
		PrintWriter out = null;

		int lineNumber = 0;

		if (args.length < 2) {
			System.err.println("Usage: FileIO infile outfile");
			System.exit(1);
		}

		in = new Scanner(new File(args[0]));
		out = new PrintWriter(new FileWriter(args[1]));

		int n = in.nextInt();
		int a = in.nextInt();
		int b = in.nextInt();

		Matrix A = new Matrix(n);
		Matrix B = new Matrix(n);

		for (int i = 0; i < a; i++) {
			int row = in.nextInt();
			int column = in.nextInt();
			double value = in.nextDouble();
			A.changeEntry(row, column, value);
		}

		for (int i = 0; i < b; i++) {
			int row = in.nextInt();
			int column = in.nextInt();
			double value = in.nextDouble();
			B.changeEntry(row, column, value);
		}

		in.close();
		
		out.println("A has " + A.getNNZ() + " non-zero entries:");
		out.println(A.toString());
		out.println("A has " + B.getNNZ() + " non-zero entries:");
		out.println(B.toString());
		out.println("(1.5)*A =");
		out.println(A.scalarMult(1.5));
		out.println("A+B =");
		out.println(A.add(B));
		out.println("A+A =");
		out.println(A.add(A));
		out.println("B-A =");
		out.println(A.sub(B));
		out.println("A-A =");
		out.println(A.sub(A));
		out.println("Transpose(A) =");
		out.println(A.transpose());
		out.println("A*B =");
		out.println(A.mult(B));
		out.println("B*B =");
		out.println(B.mult(B));
		out.close();
		
	}
}
