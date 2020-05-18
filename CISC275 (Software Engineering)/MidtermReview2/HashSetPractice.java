import java.util.*;

class Cow{
	String name;

	Cow(String name){
		this.name = name;
	}
	public String toString(){
		return("Name: " + this.name);
	}

	@Override
	public int hashCode(){
		System.out.println("Fuck");
		return(name.hashCode());
	}

	@Override
	public boolean equals(Object x){
		if(x instanceof Cow){
			System.out.println("This shit");
		}
		return(false);
	}
}

public class HashSetPractice{
	public static void main(String[] args){
		HashSet<Cow> herd = new HashSet<Cow>();
		herd.add(new Cow("A"));
		System.out.println();
		herd.add(new Cow("Alba"));
		System.out.println();
		herd.add(new Cow("A"));
		System.out.println();
		herd.add(new Cow("Aga"));
		System.out.println();
		herd.add(new Cow("A"));
		System.out.println();
		System.out.println(herd.size());
	}	
}