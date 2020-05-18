class Dog{
	Private String name;

	Dog(String name){
		this.name = name;
	}
	public String getName(){
		return(this.name);
	}

	@Override
	public String toString(){
		return("Name: " + this.getName());
	}

	@Override
	public boolean equals(Object o){
		if(o instanceof Dog){
			Dog dog1 = (Dog)o;
			equals = dog1.getName().equals(this.getName());
		}
		return(equals);
	}
	
}