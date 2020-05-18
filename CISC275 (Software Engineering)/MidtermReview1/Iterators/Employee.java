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


	public static void main(String[] args){

		ArrayList<Employee> empArr = new ArrayList<Employee>();
	
		Employee shane = new Employee("Shane", 21, 10);
		Employee enahs = new Employee("Enahs", 12, 0);
		Employee jim = new Employee("Jim", 56, 104000);
	
		empArr.add(shane);
		empArr.add(enahs);
		empArr.add(jim);

		Iterator itr = empArr.iterator();

		while(itr.hasNext()){
			System.out.println("Hello World!!");
			itr.next();
		}
	}

}