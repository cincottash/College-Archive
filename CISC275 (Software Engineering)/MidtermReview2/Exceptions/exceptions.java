import java.util.*;

/*
1)  Write a method f1(x) that throws an XisFiveException1 if x is 5.  
	Call f1(5) from f2(), and when the exception is thrown, have f2 recover by calling f1(x+1).
2)  Rewrite  part  2  so  that  f2()  still  calls  f1(5),  
	but  no  longer  has  a  try-catch  block,  and  reflects  theexception to main where it is caught and printed.
*/

public class exceptions{
	public static void f1(Integer x){
		try{
			if(x == 5){
				throw new XisFiveException("x equals 5");
			}
			else{
				System.out.println("no exceptions here");
			}
			
		}
		catch(XisFiveException ex){
			System.out.println(ex);
			f1(x+1);
		}
	}

	public static void f2(){
		f1(5);
	}

	public static void main(String[] args){
		f2();
	}
}