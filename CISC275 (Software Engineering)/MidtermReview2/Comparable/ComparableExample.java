import java.util.*;

class Employee implements Comparable<Employee>{
	private int age;
	private int salary;

	Employee(int age, int salary){
		this.age = age;
		this.salary = salary;
	}//constructor

	int getSalary(){
		return(this.salary);
	}

	int getAge(){
		return(this.age);
	}

	public String toString(){
		return("Age: " + this.getAge() + " Salary: " + this.getSalary());
	}

	@Override
	public int compareTo(Employee e1){
		return(this.getSalary() - e1.getSalary());
	}
}

public class ComparableExample{
	public static void main(String[] args){
		ArrayList<Employee> emparr = new ArrayList<>();

		Employee shane = new Employee(21, 60000);
		Employee rick = new Employee(22, 30000);
	
		emparr.add(shane);
		emparr.add(rick);
		System.out.println(emparr);
		Collections.sort(emparr);
		System.out.println(emparr);
	}
}