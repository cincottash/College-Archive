import java.util.*;


public class Employee implements Comparable<Employee>{
	
	private String name;
	private int age;
	private int salary;

	public String getName(){
		return name;
	}

	public int getAge(){
		return age;
	}

	public int getSalary(){
		return salary;
	}

	public Employee(String name, int age, int salary){
		this.name = name;
		this.age = age;
		this.salary = salary;
	}//constructor


	@Override
	public int compareTo(Employee emp){
		//lets sort by age
		//return -1, 0, 1 for LEQ, EQ, GEQ
		return(this.salary - emp.salary);

	}

	@Override
	public String toString(){
		return("Name " + this.name + " age " + this.age + " salary " + this.salary);
	}

	public static void main(String[] args){
		ArrayList<Employee> empArr = new ArrayList<Employee>();
	
		Employee shane = new Employee("Shane", 21, 10);
		Employee enahs = new Employee("Enahs", 12, 0);
		Employee jim = new Employee("Jim", 56, 104000);
	
		empArr.add(shane);
		empArr.add(enahs);
		empArr.add(jim);

		//before sorting
		for(Employee i : empArr){
			System.out.println(i);
		}

		//using compareTo to sort by salary
		Collections.sort(empArr);

		for(Employee i : empArr){
			System.out.println(i);
		}

	}
}