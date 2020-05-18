import java.util.*;


class Dog extends Animal{

	public Dog(String dogName, Integer dogLegs){
		this.name = dogName;
		this.legs = dogLegs;

	}

	/*
	static Comparator<Animal> dogComparator = new Comparator<Animal>(){
		@Override
		public int compare(Dog d1, Dog d2){
			System.out.println(d1.getName());
			return 1;

		}
	};
	*/

}