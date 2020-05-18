import java.util.*;

public class Cow{
	private String name;

	public Cow(String name){
		this.name = name;
	}

	public String getName(){
		return name;
	}

	public String toString(){
		return("Name: " + name);
	}

	public static void main(String[] args){
		ArrayList<Cow> cowArr = new ArrayList<Cow>();
		Cow shane = new Cow("Shane");
		Cow james = new Cow("James");
		cowArr.add(shane);
		cowArr.add(james);

		System.out.println("Before itr");
		System.out.println(cowArr);

		Iterator itr = cowArr.iterator();

		while(itr.hasNext()){
			 System.out.println(itr.next());
			 itr.remove();
		}
		System.out.println("After itr");
		System.out.println(cowArr);


	}
}