//-----------------------------------------------------------------------------
//  Jerry Liu
//  jelliu ID:1410172
//  CMPS101
//  pa1
//  Lex.java
//  A test client for the List ADT. Use this to test your list module.
//-----------------------------------------------------------------------------

import java.io.*;
import java.util.Scanner;

public class Lex {
	public final static void main(String args[]) throws IOException{
		 Scanner in = null;
	      PrintWriter out = null;
	      
	      int lineNumber = 0;

	      if(args.length < 2) {
	         System.err.println("Usage: FileIO infile outfile");
	         System.exit(1);
	      }
	      
	      in = new Scanner(new File(args[0]));
	      out = new PrintWriter(new FileWriter(args[1]));

	      while( in.hasNextLine() ){
	         lineNumber++;
	         in.nextLine();
	      }
	      
	      in.close();
	      System.out.println("total lines: " + lineNumber);
	      String[] strArray = new String[lineNumber];
	      in = new Scanner(new File(args[0]));
	      lineNumber = 0;
	      while( in.hasNextLine() ){
	    	  strArray[lineNumber] = in.nextLine();
		      lineNumber++;
		  }
	      in.close();

	      
	     
	   
		//String [] strArray = {"one", "two", "three", "four", "five"};
	   
		List l = new List();
		
		for (int i = 0; i < strArray.length; i++) {
			boolean isInsert = false;
			for (l.moveFront(); l.index() >= 0; l.moveNext() ) {
				if (strArray[i].compareTo(strArray[l.get()]) < 0) {
					l.insertBefore(i);
					isInsert = true;
					break;
				}
			}
			if (!isInsert) {
				l.append(i);
			}
		}
		
		System.out.println(l);
		for (l.moveFront(); l.index() >= 0; l.moveNext() ) {
			out.println(strArray[l.get()]);
		}
		out.close();
	}
}

