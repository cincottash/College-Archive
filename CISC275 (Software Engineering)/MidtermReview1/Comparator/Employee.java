import java.util.*;

public class Employee{

	private String name;
	private int age;
	private int salary;

	public Employee(String name, int age, int salary){
		this.age = age;
		this.name = name;
		this.salary = salary;
	}//constructor

	public String getName(){
		return(name);
	}

	public int getAge(){
		return(age);
	}

	public int getSalary(){
		return(salary);
	}

	public String toString(){
		return("Age: " + this.age + " Name: " + this.name + " Salary: " + this.salary);
	}

	public static Comparator<Employee> ageComparator = new Comparator<Employee>(){
		@Override
		public int compare(Employee e1, Employee e2){
			return(e1.age - e2.age);
		}
	};

	public static Comparator<Employee> nameComparator = new Comparator<Employee>(){
		@Override
		public int compare(Employee e1, Employee e2){
			return(0);
		}


	};


	public static void main(String[] args){

		ArrayList<Employee> empArr = new ArrayList<Employee>();
	
		Employee shane = new Employee("Shane", 21, 10);
		Employee enahs = new Employee("Enahs", 12, 0);
		Employee jim = new Employee("Jim", 56, 104000);
	
		empArr.add(shane);
		empArr.add(enahs);
		empArr.add(jim);

		System.out.println(empArr);

		Collections.sort(empArr, ageComparator);

		System.out.println(empArr);

	}

}