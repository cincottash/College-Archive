import java.util.*;

class Employee{
	private int age;
	private int salary;

	public Employee(int age, int salary){
		this.age = age;
		this.salary = salary;
	}//constructor

	public int getSalary(){
		return(this.salary);
	}

	public int getAge(){
		return(this.age);
	}

	public String toString(){
		return("Age: " + this.getAge() + " Salary: " + this.getSalary());
	}

}

class ageCompare implements Comparator<Employee>{
	@Override
	public int compare(Employee e1, Employee e2){
		return(e1.getAge() - e2.getAge());
	}
}

class salaryCompare implements Comparator<Employee>{
	@Override
	public int compare(Employee e1, Employee e2){
		return(e1.getSalary() - e2.getSalary());
	}
}

public class ComparatorExample{
	

	public static void main(String[] args){
		ArrayList<Employee> emparr = new ArrayList<>();
		
		Employee shane = new Employee(21, 60000);
		Employee klofta = new Employee(22, 0);

		emparr.add(shane);
		emparr.add(klofta);

		System.out.println(emparr);
		Collections.sort(emparr, new salaryCompare());
		System.out.println(emparr);
		Collections.sort(emparr, new ageCompare());
		System.out.println(emparr);



	}

}