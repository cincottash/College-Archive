import java.util.*;


public class MyCompare3 {
	
	public static void main(String[] args) {
		
		List<Dog> dogs = new ArrayList<Dog>();
		dogs.add(new Dog("Fido", 4));
		dogs.add(new Dog("Fido", 3));
		dogs.add(new Dog("Alfie", 4));

		//System.out.println(dogs);
		for(Dog i : dogs){
			System.out.println(i.name);
		}

		Collections.sort(dogs, new Comparator<Animal>() {
			@Override
			public int compare(Animal a, Animal b){
			    return a.getLegs() - b.getLegs();
			}
		});

		//System.out.println(dogs);
		for(Dog i : dogs){
			System.out.println(i.name);
		}
	}
}
